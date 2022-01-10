#ifndef __INSERT_SORT_H__
#define __INSERT_SORT_H__

#include <vector>

namespace msh
{
    template <typename _Tp>
    void insertSort(std::vector<_Tp> &__v)
    {
        int __n = __v.size();
        for (int i = 1; i < __n; ++i)
        {
            int j = i;
            while (j > 0)
            {
                if (__v[j - 1] > __v[j])
                {
                    std::swap(__v[j - 1], __v[j]);
                }
                else
                {
                    break;
                }
                --j;
            }
        }
    }
} //namespace msh

#endif //__INSERT_SORT_H__