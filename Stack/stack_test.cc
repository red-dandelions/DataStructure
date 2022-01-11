#include "stack.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    msh::Stack<int> __stack;
    for (int i = 0; i < 10; ++i)
    {
        __stack.push(i);
    }
    
    while (!__stack.empty())
    {
        cout << __stack.top() << " ";
        __stack.pop();
    }
    cout << endl;

    return 0;
}