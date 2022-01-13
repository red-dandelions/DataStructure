#ifndef __TRIETREE_H__
#define __TRIETREE_H__

#include <string>
#include <unordered_map>

namespace msh
{
    struct TrieNode
    {
        bool __end;
        std::unordered_map<char, TrieNode*> __children;
        TrieNode() : __end(false) {}
    };

    class TrieTree
    {
    private:
        TrieNode *__root;
    public:
        TrieTree();
        ~TrieTree();

    public:
        bool insert(std::string __word);
        bool search(std::string __word);
        bool startWith(std::string __prefix);
    
    private:
        void __destroy(TrieNode *__node);
    };

    TrieTree::TrieTree()
    {
        __root = new TrieNode();
    }

    TrieTree::~TrieTree()
    {
        __destroy(__root);
    }

    bool TrieTree::insert(std::string __s)
    {
        TrieNode *__tmp = __root;
        for (const char &ch : __s)
        {
            if (__tmp->__children.find(ch) == __tmp->__children.end())
            {
                __tmp->__children[ch] = new TrieNode();
            }
            __tmp = __tmp->__children[ch];
        }
        __tmp->__end = true;
        return true;
    }

    bool TrieTree::search(std::string __s)
    {
        TrieNode *__tmp = __root;
        for (const char &ch : __s)
        {
            if (__tmp->__children.find(ch) != __tmp->__children.end())
            {
                __tmp = __tmp->__children[ch];
            }
            else
            {
                return false;
            }
        }
        return __tmp->__end;
    }

    bool TrieTree::startWith(std::string __s)
    {
        TrieNode *__tmp = __root;
        for (const char &ch : __s)
        {
            if (__tmp->__children.find(ch) != __tmp->__children.end())
            {
                __tmp = __tmp->__children[ch];
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    void TrieTree::__destroy(TrieNode *__node)
    {
        if (__node == nullptr)
        {
            return;
        }

        for (auto __p : __node->__children)
        {
            __destroy(__p.second);
        }

        delete __node;
    }
} //namespace msh

#endif //__TRIETREE_H__