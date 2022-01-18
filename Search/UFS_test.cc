#include "UFS.h"

#include <iostream>
#include <vector>

using namespace std;
/**
 * 树可以看成是一个连通且 无环 的 无向 图。
 * 给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。
 * 添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于树中已存在的边。
 * 图的信息记录于长度为 n 的二维数组 edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。
 * 请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个节点的树。
 * 如果有多个答案，则返回数组 edges 中最后出现的边。
 * case1:
 *      edges = [[1,2], [1,3], [2,3]]
 *  output: [2,3]
 * case2:
 *      edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
 *  output: [1,4]
 */

class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        int n = edges.size();
        msh::UF __uf(n + 1);
        vector<int> ans;
        for(auto v : edges) {
            if(!__uf.FindAndUnit(v[0],v[1]))
                ans = v;
        }
        return ans;
    }
};

int main()
{
    Solution __s;
    vector<vector<int>> __m;
    auto __v = __s.findRedundantConnection(__m);

    return 0;
}