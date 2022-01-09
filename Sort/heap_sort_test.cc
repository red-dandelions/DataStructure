#include "heap_sort.h"

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> __arr;
    for (int i = 0; i < 20; ++i)
    {
       __arr.push_back(i);
    }
    random_shuffle(__arr.begin(), __arr.end());
    for (const int &val : __arr)
    {
        cout << val << " ";
    }
    cout << endl;

    msh::heapSort(__arr);
    for (const int &val : __arr)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}