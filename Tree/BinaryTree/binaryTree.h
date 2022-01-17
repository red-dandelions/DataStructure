#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

#include <iostream>
#include <stack>
#include <queue>

namespace msh
{
    template <typename _Tp>
    struct Node
    {
        _Tp __value;
        Node<_Tp> *__left;
        Node<_Tp> *__right;
        Node() : __left(nullptr), __right(nullptr) {}
        Node(_Tp value) : __value(value), __left(nullptr), __right(nullptr) {}
    };

    template <typename _Tp>
    class binaryTree
    {
    private:
        Node<_Tp> *__root;

    public:
        binaryTree() : __root(nullptr) {}
        binaryTree(std::vector<_Tp> __v);
        ~binaryTree();

    public:
        bool empty();
        void preOrderTraverse();
        void inOrderTraverse();
        void postOrderTraverse();
        void levelOrderTraverse();

    private:
        void __destroy(Node<_Tp> *__node);
    };

    template <typename _Tp>
    binaryTree<_Tp>::binaryTree(std::vector<_Tp> __v)
    {
        int __n = __v.size();
        if (__n == 0)
        {
            return;
        }
        int __index = 0;
        __root = new Node<_Tp>(__v[__index]);
        std::queue<Node<_Tp> *> __q;
        __q.push(__root);
        while (!__q.empty())
        {
            int __len = __q.size();
            while (__len--)
            {
                Node<_Tp> *__cur = __q.front();
                __q.pop();
                if (__index * 2 + 1 < __n)
                {
                    Node<_Tp> *__node = new Node<_Tp>(__v[__index * 2 + 1]);
                    __cur->__left = __node;
                    __q.push(__node);
                }
                if (__index * 2 + 2 < __n)
                {
                    Node<_Tp> *__node = new Node<_Tp>(__v[__index * 2 + 2]);
                    __cur->__right = __node;
                    __q.push(__node);
                }
                ++__index;
            }
        }
    }

    template <typename _Tp>
    binaryTree<_Tp>::~binaryTree()
    {
        __destroy(__root);
    }

    template <typename _Tp>
    bool binaryTree<_Tp>::empty()
    {
        return __root == nullptr;
    }

    /*
    改进的非递归实现：

    二叉树前序遍历非递归的关键
    在前序遍历完某结点的左子树后，如何找到
    该结点的右子树的根？
    这就需要栈：保存当前结点，然后当该结点的左子树访问完毕后，当前结点出栈，获得其右孩子，以访问它的右子树。
    1）如果当前结点非空
    访问当前结点
    当前结点入栈；
    将当前结点的左孩子作为当前结点；
    2）如果当前结点为空
    栈顶结点出栈，
    将该结点的右孩子作为当前结点；

    反复执行1）2)，直到当前结点 = NULL && 栈空.
    */
    template <typename _Tp>
    void binaryTree<_Tp>::preOrderTraverse()
    {
        if (this->empty())
        {
            return;
        }
        std::stack<Node<_Tp> *> __st;
        Node<_Tp> *__tmp = __root;
        while (__tmp || !__st.empty())
        {
            while (__tmp)
            {
                std::cout << __tmp->__value << " ";
                __st.push(__tmp);
                __tmp = __tmp->__left;
            }
            __tmp = __st.top();
            __st.pop();

            __tmp = __tmp->__right;
        }
        std::cout << std::endl;
    }

    //非递归实现
    /*
        1）如果当前结点非空
        当前结点入栈；
        将当前结点的左孩子作为当前结点；
        2）如果当前结点为空
        栈顶结点出栈，
        访问当前结点
        将该结点的右孩子作为当前结点；
        反复执行1）2)，直到当前结点NULL && 栈空
    */
    template <typename _Tp>
    void binaryTree<_Tp>::inOrderTraverse()
    {
        if (this->empty())
        {
            return;
        }
        std::stack<Node<_Tp> *> __st;
        Node<_Tp> *__tmp = __root;
        while (__tmp || !__st.empty())
        {
            while (__tmp)
            {
                __st.push(__tmp);
                __tmp = __tmp->__left;
            }
            __tmp = __st.top();
            __st.pop();
            std::cout << __tmp->__value << " ";
            __tmp = __tmp->__right;
        }
        std::cout << std::endl;
    }

    //非递归
    /*
        后序遍历的过程
        1.当前结点指针!=nullptr时，入栈，遍历左子树;
        2.当前结点指针==nullptr时，将当前结点为栈顶，退栈：
            (1) 若当前结点没有右孩子或当前结点的右孩子标记为prev，
                打印当前结点，将当前结点标记为prev，当前结点置为nullptr；
            (2) 若当前结点有右孩子并且右孩子没有遍历过，
                将当前结点入栈，当前结点置为当前结点的右孩子；
        反复执行1）2）直到栈空。
    */
    template <typename _Tp>
    void binaryTree<_Tp>::postOrderTraverse()
    {
        if (this->empty())
        {
            return;
        }
        std::stack<Node<_Tp> *> __st;
        Node<_Tp> *__tmp = __root;
        Node<_Tp> *__prev = nullptr;
        while (__tmp || !__st.empty())
        {
            while (__tmp)
            {
                __st.push(__tmp);
                __tmp = __tmp->__left;
            }
            __tmp = __st.top();
            __st.pop();
            if (!__tmp->__right || __tmp->__right == __prev)
            {
                std::cout << __tmp->__value << " ";
                __prev = __tmp;
                __tmp = nullptr;
            }
            else
            {
                __st.push(__tmp);
                __tmp = __tmp->__right;
            }
        }
        std::cout << std::endl;
    }

    template <typename _Tp>
    void binaryTree<_Tp>::levelOrderTraverse()
    {
        if (this->empty())
        {
            return;
        }
        Node<_Tp> *__tmp = __root;
        std::queue<Node<_Tp> *> __q;
        __q.push(__tmp);
        while (!__q.empty())
        {
            int __len = __q.size();
            while (__len--)
            {
                Node<_Tp> *__cur = __q.front();
                __q.pop();

                std::cout << __cur->__value << " ";

                if (__cur->__left)
                {
                    __q.push(__cur->__left);
                }
                if (__cur->__right)
                {
                    __q.push(__cur->__right);
                }
            }
        }
        std::cout << std::endl;
    }

    template <typename _Tp>
    void binaryTree<_Tp>::__destroy(Node<_Tp> *__node)
    {
        if (__node != nullptr)
        {
            __destroy(__node->__left);  // 释放左子树
            __destroy(__node->__right); // 释放右子树
            delete __node;              // 释放根结点
        }
    }

} //namespace msh
#endif // __BINARY_TREE_H__