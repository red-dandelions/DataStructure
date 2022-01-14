#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <iostream>
#include <stack>

namespace msh
{

    template <typename _Tp>
    struct bstNode
    {
        _Tp __value;
        bstNode *__left;
        bstNode *__right;

        bstNode() : __left(nullptr), __right(nullptr) {}
        bstNode(_Tp value) : __value(value), __left(nullptr), __right(nullptr) {}
    };

    template <typename _Tp>
    class binarySearchTree
    {
    private:
        bstNode<_Tp> *__root;

    public:
        binarySearchTree();
        ~binarySearchTree();

    public:
        bool insert(_Tp __value);
        bool find(_Tp __value);
        void inorderTraverse();

    private:
        void __destroy(bstNode<_Tp> *__node);
    };

    template <typename _Tp>
    binarySearchTree<_Tp>::binarySearchTree()
    {
        __root = nullptr;
    }

    template <typename _Tp>
    binarySearchTree<_Tp>::~binarySearchTree()
    {
        __destroy(__root);
    }

    template <typename _Tp>
    bool binarySearchTree<_Tp>::insert(_Tp __value)
    {
        bstNode<_Tp> *__tmp = __root;
        if (__tmp == nullptr)
        {
            __root = new bstNode(__value);
            return true;
        }

        bstNode<_Tp> *__x = nullptr;
        while (__tmp)
        {
            __x = __tmp;
            if (__tmp->__value == __value)
            {
                return false;
            }
            if (__tmp->__value < __value)
            {
                __tmp = __tmp->__right;
            }
            else
            {
                __tmp = __tmp->__left;
            }
        }
        __tmp = new bstNode(__value);
        if (__x->__value < __value)
        {
            __x->__right = __tmp;
        }
        else
        {
            __x->__left = __tmp;
        }
        return true;
    }

    template <typename _Tp>
    bool binarySearchTree<_Tp>::find(_Tp __value)
    {
        bstNode<_Tp> *__tmp = __root;
        while (__tmp)
        {
            if (__tmp->__value == __value)
            {
                return true;
            }
            if (__tmp->__value < __value)
            {
                __tmp = __tmp->__right;
            }
            else
            {
                __tmp = __tmp->__left;
            }
        }
        return false;
    }

    template <typename _Tp>
    void binarySearchTree<_Tp>::inorderTraverse()
    {
        std::stack<bstNode *> st;
        bstNode<_Tp> *__tmp = __root;
        while (__tmp || !st.empty())
        {
            while (__tmp)
            {
                st.push(__tmp);
                __tmp = __tmp->__left;
            }
            __tmp = st.top();
            st.pop();

            std::cout << __tmp->__value << " ";
            __tmp = __tmp->__right;
        }
        std::cout << std::endl;
    }

    template <typename _Tp>
    void binarySearchTree<_Tp>::__destroy(bstNode<_Tp> *__node)
    {
        if (__node == nullptr)
        {
            return;
        }
        __destroy(__node->__left);
        __destroy(__node->__right);
        delete __node;
    }
} //namespace msh

#endif //__BINARY_SEARCH_TREE_H__