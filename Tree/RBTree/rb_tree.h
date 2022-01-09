#ifndef __RB_TREE_H__
#define __RB_TREE_H__

namespace msh
{
    enum COLOR
    {
        RED,
        BLACK
    };
    /**
     * @brief 红黑树节点的定义
     * 
     */
    class RB_TREE_NODE
    {
    public:
        RB_TREE_NODE() : __left(nullptr), __right(nullptr), __parent(nullptr) {}
        RB_TREE_NODE *__left;
        RB_TREE_NODE *__right;
        RB_TREE_NODE *__parent;
        int __key;
        int __value;
        COLOR __color;
    };
    /**
     * @brief 红黑树的定义
     * 
     */
    class RB_TREE
    {
    private:
        RB_TREE_NODE *__nullNode;
        RB_TREE_NODE *__root;

    public:
        RB_TREE();
        ~RB_TREE();

        RB_TREE(const RB_TREE &) = delete;
        const RB_TREE &operator=(const RB_TREE &) = delete;

    public:
        bool empty();

        RB_TREE_NODE *find(int key);

        bool insert(int key, int value);

        bool erase(int key);

        void inorderTranverse();

    private:
        void __destroy(RB_TREE_NODE *node);

        void __insert_fixup(RB_TREE_NODE *node);

        void __erase_fixup(RB_TREE_NODE *node);

        bool __rotate_left(RB_TREE_NODE *node);

        bool __rotate_right(RB_TREE_NODE *node);
    };

    /**
     * @brief 红黑树成员函数的实现
     * 
     */

    RB_TREE::RB_TREE()
    {
        __nullNode = new RB_TREE_NODE();
        __root = __nullNode;
        __nullNode->__left = __root;
        __nullNode->__right = __root;
        __nullNode->__parent = __root;
        __nullNode->__color = BLACK;
    }

    RB_TREE::~RB_TREE()
    {
        __destroy(__root);
        delete __nullNode;
    }

    bool RB_TREE::empty()
    {
        if (__root == __nullNode)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    RB_TREE_NODE *RB_TREE::find(int key)
    {
        RB_TREE_NODE *__index = __root;
        while (__index != __nullNode)
        {
            if (key < __index->__key)
            {
                __index = __index->__left;
            }
            else if (key > __index->__key)
            {
                __index = __index->__right;
            }
            else
            {
                break;
            }
        }
        return __index;
    }
} //namespace msh

#endif //__RB_TREE_H__