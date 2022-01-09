#ifndef __STACK_H__
#define __STACK_H__

#include <stdexcept>
#include <vector>

namespace msh
{

    template <typename _Tp>
    struct Node
    {
        _Tp __value;
        Node *__prev;
        Node *__next;

        Node() : __prev(nullptr), __next(nullptr) {}
        Node(_Tp value) : __value(value), __prev(nullptr), __next(nullptr) {}
    };

    template <typename _Tp>
    class Stack
    {
    private:
        size_t __size;
        Node<_Tp> *__top;

    public:
        Stack();
        ~Stack();

        Stack(const Stack &) = delete;
        Stack &operator=(const Stack &) = delete;

    public:
        bool empty();
        size_t size();
        _Tp top();
        bool push(_Tp __val);
        bool pop();

    private:
        void __destroy();
    };

    template <typename _Tp>
    Stack<_Tp>::Stack()
    {
        __size = 0;
        __top = nullptr;
    }

    template <typename _Tp>
    Stack<_Tp>::~Stack()
    {
        if (!this->empty())
        {
            this->__destroy();
        }
    }

    template <typename _Tp>
    bool Stack<_Tp>::empty()
    {
        return __size == 0;
    }

    template <typename _Tp>
    size_t Stack<_Tp>::size()
    {
        return __size;
    }

    template <typename _Tp>
    _Tp Stack<_Tp>::top()
    {
        if (this->empty())
        {
            throw std::runtime_error("stack is empty!");
        }
        return __top->__value;
    }

    template <typename _Tp>
    bool Stack<_Tp>::push(_Tp __val)
    {
        if (this->empty())
        {
            __top = new Node<_Tp>(__val);
        }
        else
        {
            Node<_Tp> *__insert_node = new Node<_Tp>(__val);
            __insert_node->__prev = __top;
            __top->__next = __insert_node;

            __top = __insert_node;
        }
        ++__size;
        return true;
    }

    template <typename _Tp>
    bool Stack<_Tp>::pop()
    {
        if (this->empty())
        {
            throw std::runtime_error("Stack is empty!");
        }
        Node<_Tp> *__erase_node = __top;

        __top = __top->__prev;

        delete __erase_node;
        --__size;
        return true;
    }

    template <typename _Tp>
    void Stack<_Tp>::__destroy()
    {
        while (__size)
        {
            Node<_Tp> *__erase_node = __top;
            __top = __top->__prev;

            delete __erase_node;
            --__size;
        }
    }

} //namespace msh

#endif //__STACK_H__