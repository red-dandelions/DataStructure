#ifndef __UFS_H__
#define __UFS_H__

#include <vector>
#include <numeric>

namespace msh
{
    //并查集
    class UF
    {
    private:
        std::vector<int> __father;
        std::vector<int> __size; //__size存储每个并查集的大小。
        int __n;
        int __cap; //存储有多少个并查集

    public:
        UF(int n) : __n(n), __cap(n), __father(n), __size(n, 1)
        {
            //将[0, n - 1]填充到__father
            std::iota(__father.begin(), __father.end(), 0);
        }

    public:

        int size()
        {
            //返回并查集个数
            return __cap;
        }

        int FindAndSet(int __value)
        {
            //递归寻找根结点, 返回根结点
            return __father[__value] == __value ? __value : __father[__value] = FindAndSet(__father[__value]);
        }

        void Unit(int __x, int __y)
        {
            //同一个集合合并，减少并查集个数
            if (__size[__x] < __size[__y])
            {
                std::swap(__x, __y);
            }
            __father[__y] = __x;
            __size[__x] += __size[__y];
            --__cap;
        }

        bool FindAndUnit(int __x, int __y)
        {
            //__x, __y不在同一个集合，返回true，否则返回false
            int __a = FindAndSet(__x);
            int __b = FindAndSet(__y);
            if (__a != __b)
            {
                Unit(__a, __b);
                return true;
            }
            return false;
        }
    };

} //namespace msh

#endif //__UFS_H__