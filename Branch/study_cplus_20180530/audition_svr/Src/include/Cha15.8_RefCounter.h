//
// Created by hubao on 2017/9/24.
//

#ifndef MYACCOUNT_REFCOUNTER_H
#define MYACCOUNT_REFCOUNTER_H

#include "RpcConnectPool.h"
/*
 *  ***********************************************************************
 *  迄今为止，我们已经使用过的使用计数式类，都使用一个伙伴类来存储指针和相关的使用计数
 *  ***********************************************************************
 */
class U_Ptr {
public:
    friend class HasPtr;

    int *ip;
    size_t use;

    U_Ptr(int *p): ip(p), use(1) { }
    ~U_Ptr() { delete ip; }
};

class HasPtr {
public:
    // 构造函数
    HasPtr(int *p, int i) : ptr(new U_Ptr(p)), val(i) { }

    // 复制构造函数
    HasPtr(const HasPtr &orig) : ptr(orig.ptr), val(orig.val) {
        ++ptr->use;
    }

    // 赋值操作符，同另一种指针型句柄的赋值操作符类似
    HasPtr& operator=(const HasPtr& rhs){
        ++rhs.ptr->use;         // 右（操作数）加左（操作数）减，防止自身赋值
        if (--ptr->use == 0)
            delete ptr;

        ptr = rhs.ptr;          // 赋值
        val = rhs.val;
        return *this;           // 返回左操作数的引用。
    }

    U_Ptr* operator->(){
        return ptr;
    }
    
    const U_Ptr* operator->() const{
        return ptr;
    }
    
    ~HasPtr() {
        if (--ptr->use == 0) delete ptr;
    }

private:
    U_Ptr *ptr;        // points to use-counted U_Ptr class
    int val;
};



/*
 *  *************************************************************
 *  Sales_item类将有两个数据成员，都是指针: 一个指针将指向Item_base对象，而另一个将指向使用计数。
 *  Item_base 指针可以指向Item_base对象也可以指向Item_base派生类型的对象。通过指向使用计数，多个Sales_item对象可以共享同一计数器。
 *  *************************************************************
 */
class Item_base {
public:
    virtual Item_base* clone() const{
        return new Item_base(*this);
    }
    
    double net_price(size_t cnt) const {
        if (cnt >= min_qty)
            return cnt * (1 - discount) * price;
        else
            return cnt * price;
    }
private:
    int discount;
    int price;
    size_t min_qty;
};

class Bulk_item : public Item_base {
public:
    /*
     * 虚函数在继承层次中定义要求完全相同，此处例外
     * 如果虚函数 的基类实例返回类类型的引用或指针，则该虚函数的派生类实例可以返回基类实例返回的类型的派生类(或者是类类型的指针或引用)
     */
    Bulk_item* clone() const{
        return new Bulk_item(*this);
    }
    
};

class Sales_item {
public:
    // 构造函数
    Sales_item(): p(0), use(new std::size_t(1)) { }

    // Sales_item(const Item_base& rhs) : p(&rhs), use(new std::size_t(1)){} 错误的版本，不能期望从外界创建对象，那样的话也应由外界销毁，失去了句柄类管理对象的价值

    /*
     * 关键点：在Item_base 的继承层次中为每个类创建一个clone函数，返回自身类的指针。
     */
    Sales_item(const Item_base &item) : p(item.clone()), use(new std::size_t(1)) { }

    // 复制构造函数
    Sales_item(const Sales_item &i) : p(i.p), use(i.use) {
        ++*use;
    }

    // 赋值操作符，同另一种指针型句柄的赋值操作符类似
    Sales_item& operator=(const Sales_item& rhs){
        ++*rhs.use;    // 右（操作数）加左（操作数）减，防止自身赋值
        if (--*use == 0) {
            delete p;
            delete use;
        }

        p = rhs.p;     // 赋值
        use = rhs.use;
        return *this;  // 返回左操作数的引用。
    }

    ~Sales_item() {
        if (--*use == 0) { delete p; delete use; }
    }

    // 重载指针操作符，返回指针，进行动态绑定
    const Item_base *operator->() const {
        if (p) return p;
        else throw std::logic_error("unbound Sales_item");
    }

    // 重载解引用操作符，返回引用，进行动态绑定
    const Item_base &operator*() const {
        if (p) return *p;
        else throw std::logic_error("unbound Sales_item");
    }

private:
    Item_base *p;        // pointer to shared item
    std::size_t *use;    // pointer to shared use count
};

inline bool compare(const Sales_item &lhs, const Sales_item &rhs)
{
    return true;
}

class Basket {
    typedef bool (*Comp)(const Sales_item&, const Sales_item&);
public:
    typedef std::multiset<Sales_item, Comp> set_type;
    typedef set_type::size_type size_type;
    typedef set_type::const_iterator const_iter;
    
    Basket(): items(compare) { }
    void add_item(const Sales_item &item){
        items.insert(item);
    }
    
    size_type size(const Sales_item &i) const {
        return items.count(i);
    }
    
    double total() const{
        double sum = 0.0;
        for (const_iter iter = items.begin(); iter != items.end();
             iter = items.upper_bound(*iter)) {
            sum += (*iter)->net_price(items.count(*iter));
        }
        return sum;
    }
    
private:
    std::multiset<Sales_item, Comp> items;
};


/*
 *  *************************************************************
 *  泛型句柄类，对Sales_item的重新定义
 *  *************************************************************
 */
template <class Type>
class Handle {
public:
    Handle(Type *p = 0): ptr(p), use(new size_t(1)) { }
    Handle(const Handle& h): ptr(h.ptr), use(h.use) {
        ++*use;
    }
    Handle& operator=(const Handle& rhs){
        cout << "ref++"<< endl;
        ++*rhs.use;
        rem_ref();

        ptr = rhs.ptr;
        use = rhs.use;
        return *this;
    }

    ~Handle() { rem_ref(); cout << "ref--"<< endl;}

    Type& operator*(){
        if (ptr) return *ptr;
        throw std::runtime_error("dereference of unbound Handle");
    }
    Type* operator->(){
        if (ptr) return ptr;
        throw std::runtime_error("dereference of unbound Handle");
    }

    const Type& operator*() const{
        if (ptr) return *ptr;
        throw std::runtime_error("dereference of unbound Handle");
    }
    const Type* operator->() const{
        if (ptr) return ptr;
        throw std::runtime_error("access through unbound Handle");
    }

private:
    Type* ptr;          // shared object
    size_t *use;     // count of how many Handle spointto *ptr
    void rem_ref() {
        if (--*use == 0) { delete ptr; delete use; }
    }
};

class Sales_item_v2 {
    // 基于 Handle 的 Sales_item 版本有一个数据成员，该数据成员是关联传给构造函数的 Item_base 对象的副本上的 Handle 对象。
    // 因为 Sales_item 的这个版本没有指针成员，所以不需要复制控制成员，Sales_item 的这个版本可以安全地使用合成的复制控制成员。管理使用计数和相关 Item_base 对象的工作在 Handle 内部完成。

public:
    Sales_item_v2(): p() { }
    Sales_item_v2(const Item_base &item): p(item.clone()) { }

    const Item_base& operator*() const { return *p; }
    const Item_base* operator->() const { return p.operator->(); }

private:
    Handle<Item_base> p;
};


#endif //MYACCOUNT_REFCOUNTER_H
