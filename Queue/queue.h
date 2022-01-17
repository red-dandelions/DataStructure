#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <vector>
#include <stdexcept>

namespace msh
{
    template <typename _Tp>
    struct Node
    {
        _Tp __value;
        Node<_Tp> *__prev;
        Node<_Tp> *__next;
        Node() : __prev(nullptr), __next(nullptr) {}
        Node(_Tp value) : __value(value), __prev(nullptr), __next(nullptr) {}
    };

    template <typename _Tp>
    class Queue
    {
    private:
        Node<_Tp> *__head;
        Node<_Tp> *__tail;
        size_t __size;

    public:
        Queue();
        Queue(std::vector<_Tp> &__v);
        ~Queue();

    public:
        bool empty();
        size_t size();
        _Tp front();
        _Tp back();
        void push(_Tp __value);
        void pop();

    private:
        void __destroy(Node<_Tp> *__node);
    };

    template <typename _Tp>
    Queue<_Tp>::Queue()
    {
        __head = new Node<_Tp>();
        __tail = new Node<_Tp>();
        __size = 0;

        __head->__next = __tail;
        __tail->__prev = __head;
    }

    template <typename _Tp>
    Queue<_Tp>::Queue(std::vector<_Tp> &__v)
    {
        size_t __n = __v.size();
        
        __head = new Node<_Tp>();
        __tail = new Node<_Tp>();
        __size = __n;
        
        __head->__next = __tail;
        __tail->__prev = __head;

        for (size_t __i = 0; __i < __n; ++__i)
        {
            Node<_Tp> *__tmp = new Node<_Tp>(__v[i]);

            __tmp->__prev = __tail->__prev;
            __tmp->__prev->__next = __tmp;

            __tmp->__next = __tail;
            __tail->__prev = __tmp;
        }
    }

    template <typename _Tp>
    Queue<_Tp>::~Queue()
    {
        Node<_Tp> *__cur = __head;
        while (__cur)
        {
            Node<_Tp> *__tmp = __cur;
            __cur = __cur->__next;

            __destroy(__tmp);
        }
    }


    template <typename _Tp>
    bool Queue<_Tp>::empty()
    {
        return __size == 0;
    }

    template <typename _Tp>
    size_t Queue<_Tp>::size()
    {
        return __size;
    }

    template <typename _Tp>
    _Tp Queue<_Tp>::front()
    {
        if (this->empty())
        {
            throw std::runtime_error("Queue::front() error, Queue is emptyy()!");
        }
        return __head->__next->__value;
    }

    template <typename _Tp>
    _Tp Queue<_Tp>::back()
    {
        if (this->empty())
        {
            throw std::runtime_error("Queue::back() error, Queue is empty()!");
        }
        return __tail->__prev->__value;
    }
    
    template <typename _Tp>
    void Queue<_Tp>::push(_Tp __value)
    {
        Node<_Tp> *__tmp = new Node<_Tp>(__value);
        ++__size;

        __tmp->__prev = __tail->__prev;
        __tmp->__prev->__next = __tmp;

        __tmp->__next = __tail;
        __tail->__prev = __tmp;
    }

    template <typename _Tp>    
    void Queue<_Tp>::pop()
    {
        if (this->empty())
        {
            throw std::runtime_error("Queue::pop() error, Queue is empty()!");
        }
        --__size;
        Node<_Tp> *__tmp = __tail->__prev;

        __tmp->__prev->__next = __tail;
        __tail->__prev = __tmp->__prev;

        __tmp->__prev = nullptr;
        __tmp->__next = nullptr;
        __destroy(__tmp);
    }

    template <typename _Tp>
    void Queue<_Tp>::__destroy(Node<_Tp> *__node)
    {
        delete __node;
        __node = nullptr;
    }
} //namespace msh

#endif //__QUEUE_H__