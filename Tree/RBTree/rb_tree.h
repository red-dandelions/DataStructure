#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <stack>
#include <iostream>

/**
 * 红黑树性质：
 * 1. 每个节点是红色或者黑色
 * 2. 根节点是黑色的
 * 3. 每个叶子节点是黑色的
 * 4. 如果一个节点是红色的，则它的两个子节点都是黑色的
 * 5. 对于每个节点，从该节点到所有后代叶节点的简单路径上，黑色节点数目相同
 * 
 * 红黑树节点定义：
 * 1. 左孩子
 * 2. 右孩子
 * 3. 父节点
 * 4. key值
 * 5. 颜色值
 * 6. value值（根据需求，可选）
 */

namespace msh
{
    enum COLOR
    {
        RED,
        BLACK
    };

    struct RB_TREE_NODE
    {
        RB_TREE_NODE() : __left(nullptr), __right(nullptr), __parent(nullptr) {}
        RB_TREE_NODE *__left;
        RB_TREE_NODE *__right;
        RB_TREE_NODE *__parent;
        int __key;
        int __value;
        COLOR __color;
    };

    class RB_TREE
    {
    private:
        RB_TREE_NODE *__nullNode;
        RB_TREE_NODE *__root;

    public:
        RB_TREE();
        ~RB_TREE();

        RB_TREE(const RB_TREE &) = delete;
        RB_TREE &operator=(const RB_TREE &) = delete;

    public:
        bool empty();
        RB_TREE_NODE *find(int key);
        bool insert(int key, int value);
        bool erase(int key);
        void inorderTraverse();

    private:
        void __insert_fixup(RB_TREE_NODE *node);
        void __erase_fixup(RB_TREE_NODE *node);
        void __rotate_left(RB_TREE_NODE *node);
        void __rotate_right(RB_TREE_NODE *node);
        void __inorderTraverse(RB_TREE_NODE* node);
        void __destroy(RB_TREE_NODE *node);
    };

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
        return __root == __nullNode;
    }

    RB_TREE_NODE* RB_TREE::find(int __key)
    {
        RB_TREE_NODE *__index = __root;
        while (__index != __nullNode)
        {
            if (__index->__key == __key)
            {
                return __index;
            }
            else if (__index->__key < __key)
            {
                __index = __index->__right;
            }
            else
            {
                __index = __index->__left;
            }
        }
        return nullptr;
    }

    bool RB_TREE::insert(int __key, int __value)
    {
        RB_TREE_NODE *__x = __root;
        RB_TREE_NODE *__y = __nullNode;

        //找到插入节点的父节点
        while (__x != __nullNode)
        {
            __y = __x;
            if (__key < __x->__key)
            {
                __x = __x->__left;
            }
            else if (__key > __x->__key)
            {
                __x = __x->__right;
            }
            else
            {
                return false;
            }
        }

        //生成插入节点
        RB_TREE_NODE *__insert_node = new RB_TREE_NODE();
        __insert_node->__parent = __y;
        __insert_node->__key = __key;
        __insert_node->__value = __value;
        __insert_node->__left = __nullNode;
        __insert_node->__right = __nullNode;
        __insert_node->__color = RED;

        //判断插入节点在哪个位置
        if (__y == __nullNode)
        {
            __root = __insert_node;
        }
        else if (__insert_node->__key < __y->__key)
        {
            __y->__left = __insert_node;
        }
        else
        {
            __y->__right = __insert_node;
        }

        //调用辅助函数重新着色并旋转
        __insert_fixup(__insert_node);
        return true;
    }

    bool RB_TREE::erase(int __key)
    {
        //用另一棵子树替换一棵子树并成为其双亲的孩子节点。用__v替换__u
        auto __rb_transplant = [&](RB_TREE_NODE* __u, RB_TREE_NODE* __v) 
        {
            if (__u->__parent == __nullNode)
            {
                //__u是根节点
                __root = __v;
            }
            else if (__u == __u->__parent->__left)
            {
                //__u是左孩子
                __u->__parent->__left = __v;
            }
            else
            {
                //__u是右孩子
                __u->__parent->__right = __v;
            }

            //更新__v的父节点
            __v->__parent = __u->__parent;
        };
        //寻找子树的最小节点
        auto __tree_minimum = [&](RB_TREE_NODE* __index_node) -> RB_TREE_NODE*
        {
            RB_TREE_NODE* __res = __index_node;
            while (__res->__left != __nullNode)
            {
                __res = __res->__left;
            }
            return __res;
        };

        auto __erase_node = find(__key);
        //如果没有找到相应的key，则返回false
        if (__erase_node == __nullNode)
        {
            return false;
        }

        //记录删除节点的颜色，后续用来判断是否需要调整红黑树
        COLOR __ori_color = __erase_node->__color;
        
        //记录哪个节点代替了__erase_node，后续如果需要调整红黑树，则从该节点开始
        RB_TREE_NODE* __start_fixup_node;

        //case 1：删除节点左孩子为空，直接用右孩子代替__erase_node
        if (__erase_node->__left == __nullNode)
        {
            __start_fixup_node = __erase_node->__right;
            __rb_transplant(__erase_node, __erase_node->__right);
        }
        //case 2：删除节点右孩子为空，直接用左孩子代替__erase_node
        else if (__erase_node->__right == __nullNode)
        {
            __start_fixup_node = __erase_node->__left;
            __rb_transplant(__erase_node, __erase_node->__left);
        }
        //case 3：删除节点有左右孩子
        else
        {
            //找到删除节点右子树的最小节点
            auto __replace_node = __tree_minimum(__erase_node->__right);

            __ori_color = __replace_node->__color;
            __start_fixup_node = __replace_node->__right;

            //case 1：删除节点的右孩子没有左孩子
            if (__replace_node->__parent == __erase_node)
            {
                __start_fixup_node->__parent = __replace_node;
            }
            //case 2：删除节点的右子树最小节点不是删除节点的右孩子
            else
            {
                __rb_transplant(__replace_node, __replace_node->__right);
                __replace_node->__right = __erase_node->__right;
                __replace_node->__right->__parent = __replace_node;
            }

            //用__replace_node代替__erase_node并调整__erase_node左孩子和__replace_node之间的关系
            __rb_transplant(__erase_node, __replace_node);
            __replace_node->__left = __erase_node->__left;
            __replace_node->__left->__parent = __replace_node;
            __replace_node->__color = __erase_node->__color;
        }
        
        //如果删除的节点是黑色的，则需要调整红黑树
        if (__ori_color == BLACK)
        {
            __erase_fixup(__start_fixup_node);
        }
        delete __erase_node;
        return true;
    }

    void RB_TREE::inorderTraverse()
    {
        //迭代
        RB_TREE_NODE* __x = __root;
        std::stack<RB_TREE_NODE*> __st;
        while (__x != __nullNode || !__st.empty())
        {
            while (__x != __nullNode)
            {
                __st.push(__x);
                __x = __x->__left;
            }
            __x = __st.top();
            __st.pop();
            std::cout << __x->__key << " ";
            __x = __x->__right;
        }
        std::cout << std::endl;
    }

    void RB_TREE::__insert_fixup(RB_TREE_NODE *__insert_node)
    {
        while (__insert_node->__parent->__color == RED)
        {
            //父节点位于爷爷节点的左孩子
            if (__insert_node->__parent == __insert_node->__parent->__parent->__left)
            {
                //获得uncle节点
                RB_TREE_NODE *__uncle = __insert_node->__parent->__parent->__right;
                if (__uncle->__color == RED)
                {
                    //case 1: uncle节点是红的话， 父节点和uncle节点变为黑，上移insert节点为爷爷节点
                    __insert_node->__parent->__color = BLACK;
                    __uncle->__parent->__color = BLACK;
                    __insert_node->__parent->__parent->__color = RED;
                    __insert_node = __insert_node->__parent->__parent;
                }
                else if (__insert_node == __insert_node->__parent->__right)
                {
                    //case 2: uncle节点为黑并且__insert_node位于右孩子，上移insert节点为父节点，然后左旋
                    __insert_node = __insert_node->__parent;
                    __rotate_left(__insert_node);
                }
                else {
                    //case 3: uncle节点为黑并且__insert_node位于左孩子，父节点变黑，爷爷节点变红，然后右旋
                    __insert_node->__parent->__color = BLACK;
                    __insert_node->__parent->__parent->__color = RED;
                    __rotate_right(__insert_node->__parent->__parent);
                }
            }
            else
            {
                RB_TREE_NODE *__uncle = __insert_node->__parent->__parent->__left;
                if (__uncle->__color == RED)
                {
                    //case 1: 父节点和uncle节点变为黑，上移insert节点
                    __insert_node->__parent->__color = BLACK;
                    __uncle->__parent->__color = BLACK;
                    __insert_node->__parent->__parent->__color = RED;
                    __insert_node = __insert_node->__parent->__parent;
                }
                else if (__insert_node == __insert_node->__parent->__left)
                {
                    __insert_node = __insert_node->__parent;
                    __rotate_right(__insert_node);
                }
                else {
                    __insert_node->__parent->__color = BLACK;
                    __insert_node->__parent->__parent->__color = RED;
                    __rotate_left(__insert_node->__parent->__parent);
                }
            }
        }
        __root->__color = BLACK;
    }

    void RB_TREE::__erase_fixup(RB_TREE_NODE *__fixup_node)
    {
        while (__fixup_node != __root && __fixup_node->__color == BLACK)
        {
            if (__fixup_node = __fixup_node->__parent->__left)
            {
                auto __brother = __fixup_node->__parent->__right;
                if (__brother->__color == RED)
                {
                    __brother->__color = BLACK;
                    __fixup_node->__parent->__color = RED;
                    __rotate_left(__fixup_node->__parent);
                    __brother = __fixup_node->__parent->__right;
                }
                if (__brother->__left->__color == BLACK && __brother->__right->__color == BLACK)
                {
                    __brother->__color = RED;
                    __fixup_node = __fixup_node->__parent;
                }
                else if (__brother->__right->__color == BLACK)
                {
                    __brother->__left->__color = BLACK;
                    __brother->__color = RED;
                    __rotate_right(__brother);
                    __brother = __fixup_node->__parent->__right;
                }
                else
                {
                    __brother->__color = __fixup_node->__parent->__color;
                    __fixup_node->__parent->__color = BLACK;
                    __brother->__right->__color = BLACK;
                    __rotate_left(__fixup_node->__parent);
                    __fixup_node = __root;
                }
            }
            else
            {
                auto __brother = __fixup_node->__parent->__left;
                if (__brother->__color == RED)
                {
                    __brother->__color = BLACK;
                    __fixup_node->__parent->__color = RED;
                    __rotate_left(__fixup_node->__parent);
                    __brother = __fixup_node->__parent->__left;
                }
                if (__brother->__left->__color == BLACK && __brother->__right->__color == BLACK)
                {
                    __brother->__color = RED;
                    __fixup_node = __fixup_node->__parent;
                }
                else if (__brother->__left->__color == BLACK)
                {
                    __brother->__right->__color = BLACK;
                    __brother->__color = RED;
                    __rotate_left(__brother);
                    __brother = __fixup_node->__parent->__left;
                }
                else
                {
                    __brother->__color = __fixup_node->__parent->__color;
                    __fixup_node->__parent->__color = BLACK;
                    __brother->__left->__color = BLACK;
                    __rotate_left(__fixup_node->__parent);
                    __fixup_node = __root;
                }
            }
        }
        __fixup_node->__color = BLACK;
    }

    void RB_TREE::__rotate_left(RB_TREE_NODE *__x)
    {
        RB_TREE_NODE *__y = __x->__right;
        __x->__right = __y->__left;
        if (__y->__left != __nullNode)
        {
            __y->__left->__parent = __x;
        }
        __y->__parent = __x->__parent;
        if (__x->__parent == __nullNode)
        {
            __root = __y;
        }
        else if (__x == __x->__parent->__left)
        {
            __x->__parent->__left = __y;
        }
        else
        {
            __x->__parent->__right = __y;
        }
        __y->__left = __x;
        __x->__parent = __y;
    }

    void RB_TREE::__rotate_right(RB_TREE_NODE *__x)
    {
        RB_TREE_NODE *__y = __x->__left;
        __x->__left = __y->__right;
        if (__y->__right != __nullNode)
        {
            __y->__right->__parent = __x;
        }
        __y->__parent = __x->__parent;
        if (__x->__parent == __nullNode)
        {
            __root = __y;
        }
        else if (__x == __x->__parent->__left)
        {
            __x->__parent->__left = __y;
        }
        else
        {
            __x->__parent->__right = __y;
        }
        __y->__right = __x;
        __x->__parent = __y;
    }

    void RB_TREE::__inorderTraverse(RB_TREE_NODE *__x)
    {
        if (__x == __nullNode)
        {
            return;
        }
        __inorderTraverse(__x->__left);
        std::cout << __x->__key << " ";
        __inorderTraverse(__x->__right);
    }

    void RB_TREE::__destroy(RB_TREE_NODE *__x)
    {
        if (__x == __nullNode)
        {
            return;
        }
        __destroy(__x->__left);
        __destroy(__x->__right);
        delete __x;
    }

}

#endif //__RB_TREE_H__