//
// Created by hubao on 2017/9/24.
//

#ifndef MYACCOUNT_BUSINESSHANDLER_H
#define MYACCOUNT_BUSINESSHANDLER_H

/*
 * 示例类
 */
class Basket {
    typedef bool (*Comp)(const Sales_item&, const Sales_item&);

public:
    /*
     * 构造函数，默认用 compare 比较器构造
     */
    Basket(): items(compare) { }

    void add_item(const Sales_item &item) {
        items.insert(item);
    }

    std::multiset<Sales_item, Comp>::size_type size(const Sales_item &i) const {
        return items.count(i);
    }

    double total() const {
        double sum = 0.0;

        // 记住 std::multiset upper_bound 的使用
        for (std::multiset<Sales_item, Comp>::const_iterator iter = items.begin();
             iter != items.end(); iter = items.upper_bound(*iter)){

            // 记住 std::multiset count 的使用
            sum += (*iter)->net_price(items.count(*iter));
            return sum;
        }
    }

private:
    std::multiset<Sales_item, Comp> items;
};


template <class Type>
class Queue {
public:

    Queue(): head(0), tail(0) { }
    Queue(const Queue &Q): head(0), tail(0){
        copy_elems(Q);
    }
    template <class It> Queue(It beg, It end): head(0), tail(0) {
        copy_elems(beg, end);
    }

    template <class Iter> void assign(Iter, Iter);

    Queue& operator=(const Queue&);
    ~Queue() { destroy(); }

    Type& front(){
        return head->item;
    }

    const Type &front() const {
        return head->item;
    }

    void push(const Type &){
        QueueItem<Type> *pt = new QueueItem<Type>(val);
        if (empty())
            head = tail = pt;
        else {
            tail->next = pt;
            tail = pt;
        }
    }

    void pop (){
        QueueItem<Type>* p = head;
        head = head->next;
        delete p;
    }

    bool empty () const {
        return head == 0;
    }

private:
    QueueItem<Type> *head;
    QueueItem<Type> *tail;

    void destroy(){
        while (!empty())
            pop();
    }

    void copy_elems(const Queue&){
        for (QueueItem<Type> *pt = orig.head; pt; pt = pt->next)
            push(pt->item);
    }

    template <class Iter> void copy_elems(Iter, Iter);
};

#endif //MYACCOUNT_BUSINESSHANDLER_H
