#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <chrono>

using namespace std;

class Solution {
public:
    string solve(int a, int b, int c) {
        string __ans;
        vector<pair<int, char>> __arr = {{a, 'a'}, {b, 'b'}, {c, 'c'}};
        while (true) {
            sort(__arr.begin(), __arr.end(), [](const pair<int, char> &__a, const pair<int, char> &__b) {
                return __a.first > __b.first;
            });

            bool __next = false;
            for (auto &p : __arr) {
                int __len = __ans.size();
                if (p.first <= 0) {
                    break;
                }
                if (__len >= 2 && __ans[__len - 2] == p.second && __ans[__len - 1] == p.second) {
                    continue;
                }
                __next = true;
                __ans.push_back(p.second);
                p.first--;
                break;
            }
            if (!__next) {
                break;
            }
        }
        return __ans;
    }
};

int main() {
    Solution __s;
    ifstream fin("./input.txt");
    int a, b, c;
    chrono::milliseconds __ms(0);
    while (fin >> a >> b >> c) {
        chrono::high_resolution_clock::time_point __start = chrono::high_resolution_clock::now();
        auto __ans = __s.solve(a, b, c);
        chrono::high_resolution_clock::time_point __end = chrono::high_resolution_clock::now();
        auto __tmp = chrono::duration_cast<chrono::milliseconds> (__end - __start);
        __ms += __tmp;
        cout << __ans << endl;
    }
    cout << "cost: " << __ms.count() << "ms." << endl;
    return 0;
}