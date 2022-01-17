#include "trieTree.h"

#include <iostream>

using namespace std;

int main()
{
    msh::TrieTree __tree;
    __tree.insert("red-dandelion");
    cout << "startWith:" << __tree.startWith("red") << endl;
    cout << "search: " << __tree.search("red") << endl;
    cout << "search: " << __tree.search("red-dandelion") << endl;

    return 0;
}