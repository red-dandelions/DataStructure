#include "rb_tree.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    msh::RB_TREE __tree;
    vector<int> __arr;
    for (int i = 0; i < 20; ++i)
    {
        __arr.emplace_back(i);
    }
    random_shuffle(__arr.begin(), __arr.end());
    for (const int &val : __arr)
    {
        cout << val << " ";
    }
    cout << endl;

    cout << "insert: ";
    for (int i = 0; i < __arr.size(); ++i)
    {
        __tree.insert(__arr[i], i);
        cout << __arr[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < __arr.size(); ++i)
    {
        cout << "erase: " << __arr[i] << endl;
        __tree.erase(__arr[i]);
        __tree.inorderTranverse();
    }
    cout << endl;
    __tree.inorderTranverse();

    return 0;
}