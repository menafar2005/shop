#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

template <class T>
class queue
{
private:
    struct q
    {   T *thiselement;
        q *thischild;     };
protected:
    size_t TotalSize = 0;
    q *FirstObject = nullptr;
    q *LastObject = nullptr;
    bool isEmpty = true;
public:
    queue() { TotalSize = 0; }
    queue(const queue &arg);
    queue(queue &&arg);
    queue &push(const T &ExternalElement);
    T &getLast() const;
    T &getFirst() const;
    T &getSpecific(int IndexToGet) const;
    size_t size() const;
    void clearAll();
};

template <typename T>
queue<T>& queue<T>::push(const T &ExternalElement) {
    if(isEmpty!=true) {
        TotalSize++;
        q *t = LastObject;
        LastObject = new q{new T{ExternalElement},nullptr};
        t->thischild = LastObject;
        return *this;
    }
    else {
        isEmpty=false;
        TotalSize = 1;
        LastObject = FirstObject = new q{new T {ExternalElement},nullptr};
        return *this;
    }
}

template <typename T>
T& queue<T>::getLast() const {
    if (isEmpty!=true)
    {  return *LastObject->thiselement;  }
    else
    {  throw std::out_of_range("Queue::getLast() is impossible: The queue is empty ER:QUEUE1");  }
}

template <typename T>
T& queue<T>::getFirst() const {
    if (isEmpty!=true)
    {  return *FirstObject->thiselement;  }
    else
    {  throw std::out_of_range("Queue::getFirst() is impossible: The queue is empty ER:QUEUE1");  }
}

template <typename T>
T& queue<T>::getSpecific(int IndexToGet) const {
    if (IndexToGet > TotalSize-1) {
        throw std::out_of_range("Queue::getSpecific(int) is impossible: Given index(int) is greater than amount of elements in the queue ER:QUEUE2");
    }
    if (isEmpty!=true) {
        if (TotalSize == 1)
        { return *FirstObject->thiselement;  }
        else {
            q *child = FirstObject->thischild;
            for (int i = 1; i <= IndexToGet; i++) {
                q *next = child->thischild;
                if (i == IndexToGet)
                    return *child->thiselement;
                child = next;
            }
        }
    }
    else
    {  throw std::out_of_range("Queue::getSpecific(int) is impossible: The queue is empty ER:QUEUE1");  }
    return getFirst();
}

template <typename T>
size_t queue<T>::size() const
{
    if (isEmpty!=true)
    {
        return TotalSize*sizeof(T);
    }
    return 0;
}

// description of clearAll() is redundant! however it works
template <typename T>
void queue<T>::clearAll()
{
    TotalSize = 0;
    if (isEmpty!=true)
    {
        q *child = FirstObject->thischild;
        while(child)
        {
            delete child->thiselement;
            q *next = child->thischild;
            delete child;
            child = next;
        }
        delete FirstObject;
        FirstObject = LastObject = nullptr;
        isEmpty = true;
    }
}
#endif // QUEUE_H
