#ifndef __LIST_H__
#define __LIST_H__

#include <vector>
#include <iostream>
#include <stdexcept>

/**
 * @brief 链表的定义和操作见list.md，这里实现带头节点和尾节点的双向链表
 */

namespace msh
{
    /**
     * @brief 链表节点的定义
     * __value: 存放的值
     * __prev:  指向前一个节点
     * __next:  指向后一个节点
     * 
     * @tparam _Tp 
     */
    template <typename _Tp>
    struct ListNode
    {
        _Tp __value;
        ListNode *__prev;
        ListNode *__next;

        //构造函数
        ListNode() : __prev(nullptr), __next(nullptr) {}
        ListNode(_Tp value) : __value(value), __prev(nullptr), __next(nullptr) {}
    };

    /**
     * @brief List类的实现
     * 
     * data member:
     *      1. __head   //头节点
     *      2. __tail   //尾节点
     *      3. __size   //链表长度
     * functoions:
     *      1. empty();
     *      2. size();
     *      3. front();
     *      4. back();
     *      5. get();
     *      6. push_back();
     *      7. push_front();
     *      8. pop_front();
     *      9. pop_back();
     *      10. insert();
     *      11. erase();
     *      12. traverse();
     * @tparam _Tp 
     */
    template <typename _Tp>
    class List
    {
    private:
        ListNode<_Tp> *__head;
        ListNode<_Tp> *__tail;
        size_t __size;

    public:
        List();
        List(std::vector<_Tp> &__v);
        ~List();

        //禁止拷贝构造函数和赋值运算符
        List(const List &) = delete;
        List &operator=(const List &) = delete;

    public:
        bool empty();
        size_t size();
        _Tp front();
        _Tp back();
        _Tp get(int __index);
        bool push_front(_Tp __val);
        bool push_back(_Tp __val);
        bool pop_front();
        bool pop_back();
        bool insert(int __index, _Tp __val);
        bool erase(int __index);
        ;

        void traverse();

    private:
        void __destroy();
    };

    template <typename _Tp>
    List<_Tp>::List()
    {
        __head = new ListNode<_Tp>();
        __tail = new ListNode<_Tp>();
        __size = 0;

        __head->__prev = nullptr;
        __head->__next = __tail;
        __tail->__prev = __head;
        __tail->__next = nullptr;
    }

    template <typename _Tp>
    List<_Tp>::List(std::vector<_Tp> &__v)
    {
        __head = new ListNode<_Tp>();
        __tail = new ListNode<_Tp>();
        __size = __v.size();

        __head->__prev = nullptr;
        __head->__next = __tail;
        __tail->__prev = __head;
        __tail->__next = nullptr;

        //尾插法
        for (const _Tp &__val : __v)
        {
            ListNode<_Tp> *__insert_node = new ListNode<_Tp>(__val);
            __insert_node->__prev = __tail->__prev;
            __tail->__prev->__next = __insert_node;

            __insert_node->__next = __tail;
            __insert_node->__next->__prev = __insert_node;
        }
    }

    template <typename _Tp>
    List<_Tp>::~List()
    {
        __destroy();

        delete __head;
        delete __tail;
    }

    template <typename _Tp>
    bool List<_Tp>::empty()
    {
        return __size == 0;
    }

    template <typename _Tp>
    size_t List<_Tp>::size()
    {
        return __size;
    }

    template <typename _Tp>
    _Tp List<_Tp>::front()
    {
        if (this->empty())
        {
            throw std::runtime_error("List is empty!");
        }
        return __head->__next->__value;
    }

    template <typename _Tp>
    _Tp List<_Tp>::back()
    {
        if (this->empty())
        {
            throw std::runtime_error("List is empty!");
        }
        return __tail->__prev->__value;
    }

    template <typename _Tp>
    _Tp List<_Tp>::get(int __index)
    {
        if (__index < 1 || __index > __size)
        {
            throw std::out_of_range("index out of range!");
        }
        ListNode<_Tp> *__cur = __head;
        while (__index--)
        {
            __cur = __cur->__next;
        }
        return __cur->__value;
    }

    template <typename _Tp>
    bool List<_Tp>::push_front(_Tp __val)
    {
        ListNode<_Tp> *__insert_node = new ListNode<_Tp>(__val);

        __insert_node->__next = __head->__next;
        __insert_node->__next->__prev = __insert_node;

        __head->__next = __insert_node;
        __insert_node->__prev = __head;

        ++__size;
        return true;
    }

    template <typename _Tp>
    bool List<_Tp>::push_back(_Tp __val)
    {
        ListNode<_Tp> *__insert_node = new ListNode<_Tp>(__val);

        __insert_node->__prev = __tail->__prev;
        __tail->__prev->__next = __insert_node;

        __insert_node->__next = __tail;
        __tail->__prev = __insert_node;

        ++__size;
        return true;
    }

    template <typename _Tp>
    bool List<_Tp>::pop_front()
    {
        if (this->empty())
        {
            return false;
        }
        ListNode<_Tp> *__cur = __head->__next;

        __head->__next = __head->__next->__next;
        __head->__next->__prev = __head;

        delete __cur;
        --__size;
        return true;
    }

    template <typename _Tp>
    bool List<_Tp>::pop_back()
    {
        if (this->empty())
        {
            return false;
        }
        ListNode<_Tp> *__cur = __tail->__prev;
        __tail->__prev = __tail->__prev->__prev;
        __tail->__prev->__next = __tail;

        delete __cur;
        --__size;
        return true;
    }

    template <typename _Tp>
    bool List<_Tp>::insert(int __index, _Tp __val)
    {
        if (__index <= 1)
        {
            this->push_front(__val);
        }
        else if (__index >= __size)
        {
            this->push_back(__val);
        }
        else
        {
            ListNode<_Tp> *__insert_node = new ListNode<_Tp>(__val);
            ListNode<_Tp> *__cur = __head;
            while (--__index)
            {
                __cur = __cur->__next;
            }
            __insert_node->__next = __cur->__next;
            __cur->__next->__prev = __insert_node;

            __cur->__next = __insert_node;
            __insert_node->__prev = __cur;
        }
        ++__size;
        return true;
    }

    template <typename _Tp>
    bool List<_Tp>::erase(int __index)
    {
        if (__index < 1 || __index > __size)
        {
            throw std::out_of_range("index out of range");
        }
        ListNode<_Tp> *__cur = __head;
        while (__index--)
        {
            __cur = __cur->__next;
        }

        __cur->__next->__prev = __cur->__prev;
        __cur->__prev->__next = __cur->__next;

        delete __cur;
        --__size;
        return true;
    }

    template <typename _Tp>
    void List<_Tp>::traverse()
    {
        ListNode<_Tp> *__cur = __head->__next;
        while (__cur != __tail)
        {
            std::cout << __cur->__value << " ";
            __cur = __cur->__next;
        }
        std::cout << std::endl;
    }

    template <typename _Tp>
    void List<_Tp>::__destroy()
    {
        ListNode<_Tp> *__cur = __head->__next;
        ListNode<_Tp> *__tmp;
        while (__cur != __tail)
        {
            __tmp = __cur;
            __cur = __cur->__next;

            delete __tmp;
        }
    }

} //namespace msh

#endif //__LIST_H__