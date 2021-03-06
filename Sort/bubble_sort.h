#ifndef __BUBBLE_SORT_H__
#define __BUBBLE_SORT_H__

#include <vector>

namespace msh
{
    template <typename _Tp>
    void bubbleSort(std::vector<_Tp> &__v)
    {
        int __n = __v.size();
        for (int i = 0; i < __n; ++i)
        {
            for (int j = 1; j < __n - i; ++j)
            {
                if (__v[j - 1] > __v[j])
                {
                    std::swap(__v[j - 1], __v[j]);
                }
            }
        }
    }

} //namespace msh

#endif //__BUBBLE_SORT_H__