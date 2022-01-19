#include <string>
#include <unordered_set>

using namespace std;

//滚动字符hash
int strHash(string s, int x)
{
    const uint64_t b = 97755331;
    uint64_t hash = 0, p = 1;
    //计算长度为x的string哈希值
    for (int i = 0; i < x; ++i)
    {
        hash = hash * b + s[i];
        p *= b;
    }
    //存入集合中
    unordered_set<uint64_t> hashset{hash};

    //从下标index = 1开始一次计算长度为x的string哈希值，存入集合中
    //如果存在，返回(index + x)
    for (int i = x; i < s.size(); ++i)
    {
        hash = hash * b - p * s[i - x] + s[i];
        if (hashset.find(hash) != hashset.end())
            return i;
        hashset.insert(hash);
    }
    return 0;
}

string solve(string s)
{
    int left = 0, right = s.size() - 1;
    int ans = 0;
    while (left < right)
    {
        int mid = (left + right + 1) >> 1, ret;
        (ret = strHash(s, mid)) ? left = mid : right = mid - 1;
        ret ? ans = ret : ans;
    }
    return s.substr(ans - left + 1, left);
}