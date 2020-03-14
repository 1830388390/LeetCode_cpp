//
// Created by Administrator on 2020/3/14 0014.
//
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution {
public:

    double frogPosition(int n, vector<vector<int>> &edges, int t, int target) {
        if (edges.size() == 0) {
            return 1;
        }

        using pp = pair<double, double>; // 当前位置,上一个位置
        /**
         * 生成树
         */
        vector<vector<int>> tree(n + 1, vector<int>());
        for (auto &l : edges) {
            int a = l[0];
            int b = l[1];
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
        queue<pp> q;
        q.push(make_pair(1, 0));
        double k = tree[1].size(); // 基底
        int time = -2;
        bool find = false;
        while (time < t) {
            time++;
            int size = q.size();
            for (int i = 0; i < size; i++) {
                pp tmp = q.front();
                q.pop();
                bool b = false;
                for (auto n : tree[tmp.first]) {
                    if (n == tmp.second) continue;
                    b = true;
                    q.push(make_pair(n, tmp.first));
                }
                if ((!b && tmp.first == target) || (time + 2 == t && tmp.first == target)) {
                    find = true;
                    break;
                }
            }
            if (find) break;
        }
        if (!find) return 0;
        if (k == 1) return 1;
        for (int i = 0; i < time; i++) k *= 2;
        return 1 / k;
    }
};