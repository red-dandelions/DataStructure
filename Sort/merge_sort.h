#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

#include <vector>

namespace msh
{
    template <typename _Tp>
    static void merge(std::vector<_Tp> &__v, int __left, int __mid, int __right)
    {
        int __len1 = __mid  - __left;
        int __len2 = __right - __mid + 1;
        _Tp __a[__len1];
        _Tp __b[__len2];
        for (int i = 0; i < __len1; ++i)
        {
            __a[i] = __v[__left + i];
        }
        for (int i = 0; i < __len2; ++i)
        {
            __b[i] = __v[__mid + i];
        }
        int __index = __left;
        int __i = 0, __j = 0;
        while (__index < __right)
        {
            if (__i < __len1 && __j < __len2)
            {
                if (__a[__i] < __b[__j])
                {
                    __v[__index] = __a[__i];
                    ++__i;
                }
                else
                {
                    __v[__index] = __b[__j];
                    ++__j;
                }
            }
            else if (__i < __len1)
            {
                __v[__index] = __a[__i];
                ++__i;
            }
            else
            {
                __v[__index] = __a[__j];
                ++__j;
            }
            ++__index;
        }
    }

    template <typename _Tp>
    void mergeSort(std::vector<_Tp> &__v, int __start, int __end)
    {
        if (__start < __end)
        {
            int __mid = __start + ((__end - __start) >> 1);
            mergeSort(__v, __start, __mid);
            mergeSort(__v, __mid, __end);
            merge(__v, __start, __mid, __end);
        }
    }

} //namespace msh

#endif //__MERGE_SORT_H__