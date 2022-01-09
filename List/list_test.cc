#include "list.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> __v;
    for (int i = 0; i < 10; ++i)
    {
        __v.emplace_back(i);
    }
    
    msh::List<int> __list(__v);

    __list.traverse();

    return 0;
}