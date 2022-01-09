#ifndef __QUICK_SORT_H__
#define __QUICK_SORT_H__

#include <vector>

namespace msh
{

    template <typename _Tp>
    static int partition(std::vector<_Tp> &__arr, int __left, int __right)
    {
        int __index = __left + rand() % (__right - __left + 1);
        std::swap(__arr[__left], __arr[__index]);

        int __val = __arr[__left];
        while (__left < __right)
        {
            while (__left < __right && __val <= __arr[__right])
            {
                --__right;
            }
            std::swap(__arr[__left], __arr[__right]);

            while (__left < __right && __arr[__left] <= __val)
            {
                ++__left;
            }
            std::swap(__arr[__left], __arr[__right]);
        }
        __arr[__left] = __val;
        return __left;
    }

    template <typename _Tp>
    void quickSort(std::vector<_Tp> &__arr, int __start, int __end)
    {
        if (__start < __end)
        {
            int __mid = partition(__arr, __start, __end);
            quickSort(__arr, __start, __mid - 1);
            quickSort(__arr, __mid + 1, __end);
        }
    }

} //namespace msh

#endif //__QUICK_SORT_H__