#ifndef __GCD_H__
#define __GCD_H__

namespace msh
{
    //递归
    int __gcd_EUCLID(int __a, int __b)
    {
        if (__b == 0)
        {
            return __a;
        }
        return __gcd_EUCLID(__b, __a % __b);
    }
} //namespace msh

#endif //__GCD_H__