#ifndef __SELECT_SORT_H__
#define __SELECT_SORT_H__

#include <vector>

namespace msh
{
    template <typename _Tp>
    void selectSort(std::vector<_Tp> &__v)
    {
        int __n = __v.size();
        for (int i = 0; i < __n; ++i)
        {
            _Tp __value = __v[i];
            int __index = i;
            for (int j = i + 1; j < __n; ++j)
            {
                if (__v[j] < __value)
                {
                    __value = __v[j];
                    __index = j;
                }
            }
            std::swap(__v[i], __v[__index]);
        }
    }
} //namespace msh

#endif //__SELECT_SORT_H__