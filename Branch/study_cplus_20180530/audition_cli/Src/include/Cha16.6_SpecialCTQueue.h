/*
 * Created by hubao on 2017/10/22.
 * 说明：为了让 Queue 类可以用于 const char* 的 push 和 pop 操作，有两种实现方案
 *  1 定义通用Queue模版类，用于非 const char* 的操作，同时定义特化的 Queue 类用于 const char* 的操作
 *  2 定义通用Queue模版类，用于非 const char* 的操作，同时特化 push 和 pop 函数用于支持对 const char* 的操作
 */

#ifndef MYACCOUNT_QUEUE_H
#define MYACCOUNT_QUEUE_H

///////////////////////////////////////////////////////////////
// 方案一 特化类
///////////////////////////////////////////////////////////////

/*
 * Queue 类
 */
template <class Type>
class Queue {
public:
    Queue(): head(0), tail(0) { }
    Queue(const Queue &Q): head(0), tail(0) { copy_elems(Q); }
    Queue& operator=(const Queue&);
    ~Queue() { destroy(); }

    Type& front() { return head->item; }
    const Type &front() const { return head->item; }

    void push(const Type &) {
        // allocate a new QueueItem object
        QueueItem<Type> *pt = new QueueItem<Type>(val);
        // put item onto existing queue
        if (empty())
            head = tail = pt; // the queue now has only one element
        else {
            tail->next = pt; // add new element to end of the queue
            tail = pt;
        }
    }

    void pop (){
        // pop is unchecked: Popping off an empty Queue is undefined
        QueueItem<Type>* p = head; // keep pointer to head so we can delete it
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
    void copy_elems(const Queue&) {
        // copy elements from orig into this Queue
        // loop stops when pt == 0, which happens when we reach orig.tail
        for (QueueItem<Type> *pt = orig.head; pt; pt = pt->next)
            push(pt->item); // copy the element
    }
};

/*
 * 特化后的 Queue 类
 */
template<>
class Queue<const char*> {
public:
    // no copy control: Synthesized versions work for this class
    // similarly, no need for explicit default constructor either
    void push(const char*);
    void pop() {
        real_queue.pop();
    }

    bool empty() const {
        return real_queue.empty();
    }

    // Note: return type does not match template parameter type
    std::string front() {
        return real_queue.front();
    }

    const std::string &front() const {
        return real_queue.front();
    }

private:
    // forward calls to real_queue
    Queue<std::string> real_queue;
};

// 在特化类外部定义成员时，不加空模版形参说明符（ template<>）
void Queue<const char*>::push(const char* val)
{
    return real_queue.push(val);
}


///////////////////////////////////////////////////////////////
// 方案二 特化成员而不特化类
///////////////////////////////////////////////////////////////

/*
 * Queue 类
 */
template <class Type>
class Queue {
public:
    Queue(): head(0), tail(0) { }
    Queue(const Queue &Q): head(0), tail(0) { copy_elems(Q); }
    Queue& operator=(const Queue&);
    ~Queue() { destroy(); }

    Type& front() { return head->item; }
    const Type &front() const { return head->item; }

    void push(const Type &) {
        // allocate a new QueueItem object
        QueueItem<Type> *pt = new QueueItem<Type>(val);
        // put item onto existing queue
        if (empty())
            head = tail = pt; // the queue now has only one element
        else {
            tail->next = pt; // add new element to end of the queue
            tail = pt;
        }
    }

    void pop (){
        // pop is unchecked: Popping off an empty Queue is undefined
        QueueItem<Type>* p = head; // keep pointer to head so we can delete it
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
    void copy_elems(const Queue&) {
        // copy elements from orig into this Queue
        // loop stops when pt == 0, which happens when we reach orig.tail
        for (QueueItem<Type> *pt = orig.head; pt; pt = pt->next)
            push(pt->item); // copy the element
    }
};

template <>
void Queue<const char*>::push(const char *const &val)
{
    // allocate a new character array and copy characters from val
    char* new_item = new char[strlen(val) + 1];
    strncpy(new_item, val, strlen(val) + 1);

    // store pointer to newly allocated and initialized element
    QueueItem<const char*> *pt = new QueueItem<const char*>(new_item);

    // put item onto existing queue
    if (empty())
        head = tail = pt; // queue has only one element
    else {
        tail->next = pt;  // add new element to end of queue
        tail = pt;
    }
}

template <>
void Queue<const char*>::pop()
{
    // remember head so we can delete it
    QueueItem<const char*> *p = head;
    delete head->item; // delete the array allocated in push
    head = head->next; // head now points to next element

    delete p;          // delete old head element
}

#endif //MYACCOUNT_QUEUE_H
