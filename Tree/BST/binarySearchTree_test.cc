#include "binarySearchTree.h"

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
    random_shuffle(__v.begin(), __v.end());

    msh::binarySearchTree<int> __tree;
    for (int i = 0; i < 10; ++i)
    {
        cout << __v[i] << " ";
        __tree.insert(__v[i]);
    }
    cout << endl;

    cout << __tree.find(5) << " " << __tree.find(11) << endl;

    __tree.inorderTraverse();

    return 0;
}