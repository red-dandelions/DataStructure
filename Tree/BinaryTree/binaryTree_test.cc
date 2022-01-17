#include "binaryTree.h"

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

    msh::binaryTree<int> __tree(__v);

    cout << "preorder: ";
    __tree.preOrderTraverse();

    cout << "inorder: ";
    __tree.inOrderTraverse();

    cout << "postorder: ";
    __tree.postOrderTraverse();

    cout << "levelorder: ";
    __tree.levelOrderTraverse();

    return 0;
}