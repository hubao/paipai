//
// Created by hubao on 2017/12/24.
//

#ifndef MYACCOUNT_BASECACHEDOBJ_H
#define MYACCOUNT_BASECACHEDOBJ_H
template <class T>
class CachedObj {
public:
    void *operator new(std::size_t);
    void operator delete(void *, std::size_t);
    virtual ~CachedObj() { }
protected:
    T *next;
private:
    static void add_to_freelist(T*);
    static std::allocator<T> alloc_mem;
    static T *freeStore;
    static const std::size_t chunk;
};

/*
 * operator new 函数只能被继承类调用，且继承类不能是基类（因为基类不能确定new的size）
 * 每次只能分配一个对象
 */
template <class T>
void *CachedObj<T>::operator new(size_t sz)
{
    if (sz != sizeof(T))
        throw std::runtime_error("CachedObj: wrong size object in operator new");

    if (!freeStore) {
        T * array = alloc_mem.allocate(chunk);
        for (size_t i = 0; i != chunk; ++i)
            add_to_freelist(&array[i]);
    }

    T *p = freeStore;
    freeStore = freeStore->CachedObj<T>::next;

    return p;
}

/*
 * 继承类的析构函数中已经撤销类对象本身
 * 所以 operator delete函数只需要回收内存
 */
template <class T>
void CachedObj<T>::operator delete(void *p, size_t)
{
    if (p != 0)
        add_to_freelist(static_cast<T*>(p));
}

/*
 *
 */
template <class T>
void CachedObj<T>::add_to_freelist(T *p)
{
    p->CachedObj<T>::next = freeStore;
    freeStore = p;
}

/*
 * 从 CachedObj 类派生普通类
 */
class Screen: public CachedObj<Screen> {
    // interface and implementation members of class Screen are unchanged
};

/*
 * 从 CachedObj 类派生模版类
 * 因为 QueueItem 是一个模板类型，从 CachedObj 类派生它有点复杂
 */
template <class Type>
class QueueItem: public CachedObj< QueueItem<Type> > {
    // remainder of class declaration and all member definitions unchanged
};

#endif //MYACCOUNT_BASECACHEDOBJ_H
