#ifndef __SHELL_SORT_H__
#define __SHELL_SORT_H__

#include <vector>

namespace msh
{
    template <typename _Tp>
    void shellSort(std::vector<_Tp> &__v)
    {
        int __n = __v.size();
        for (int __d = __v >> 1; __d >= 1; __d >>= 1)
        {
            for (int i = __d; i < __n; ++i)
            {
                int j = i;
                while (j > 0)
                {
                    if (__v[j - __d] > __v[j])
                    {
                        std::swap(__v[j - 1], __v[j]);
                    }
                    else
                    {
                        break;
                    }
                    j -= __d;
                }
            }
        }
    }

} //namespace msh

#endif //__SHELL_SORT_H__