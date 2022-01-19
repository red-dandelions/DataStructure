#ifndef __BINARY_SEARCH_H__
#define __BINARY_SEARCH_H__

#include <vector>

namespace msh
{
    template <typename _Tp>
    bool binarySearch(const std::vector<_Tp> &__v, _Tp __value)
    {
        int __left = 0;
        int __right = __v.size() - 1;
        int __mid;
        while (__left <= __right)
        {
            __mid = __left + ((__right - __left) >> 1);
            if (__v[__mid] == __value)
            {
                return true;
            }
            if (__v[__mid] < __value)
            {
                __right = __mid - 1;
            }
            else
            {
                __left = __mid + 1;
            }
        }
        return false;
    }
} //namespace msh

#endif //__BINARY_SEARCH_H__