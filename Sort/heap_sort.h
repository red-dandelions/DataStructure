#ifndef __HEAP_SORT_H__
#define __HEAP_SORT_H__

#include <vector>

namespace msh
{
    template <typename _Tp>
    static void heapify(std::vector<_Tp> &__arr, int __parent, int __end)
    {
        int __child = 2 * __parent + 1;
        while (__child < __end)
        {
            if (__child + 1 < __end && __arr[__child] < __arr[__child + 1])
            {
                ++__child;
            }
            if (__arr[__parent] < __arr[__child])
            {
                std::swap(__arr[__parent], __arr[__child]);
            }
            __parent = __child;
            __child = 2 * __parent + 1;
        }
    }
    template <typename _Tp>
    void heapSort(std::vector<_Tp> &__arr)
    {
        int __n = __arr.size();
        for (int i = __n / 2 - 1; i >= 0; --i)
        {
            heapify(__arr, i, __n);
        }
        for (int i = __n - 1; i > 0; --i)
        {
            std::swap(__arr[0], __arr[i]);
            heapify(__arr, 0, i);
        }
    }
}

#endif //__HEAP_SORT_H__