//
// Created by Administrator on 2020/1/12 0012.
//
#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

class C171 {
public:

    int path = INT_MAX;
    int wordIndex[26][2] = {
            {0, 0},
            {0, 1},
            {0, 2},
            {0, 3},
            {0, 4},
            {0, 5},
            {1, 0},
            {1, 1},
            {1, 2},
            {1, 3},
            {1, 4},
            {1, 5},
            {2, 0},
            {2, 1},
            {2, 2},
            {2, 3},
            {2, 4},
            {2, 5},
            {3, 0},
            {3, 1},
            {3, 2},
            {3, 3},
            {3, 4},
            {3, 5},
            {4, 0},
            {4, 1}
    };


    int minimumDistanceDFS(string word) {
        DFS(wordIndex[word[0] - 'A'][0], wordIndex[word[0] - 'A'][1], -1, -1, word, 1, 0);
        return path;
    }

    void DFS(int y1, int x1, int y2, int x2, string &word, int index, int tmpPath) {
        if (index == word.size()) {
            path = min(tmpPath, path);
            return;
        }
        int Y = wordIndex[word[index] - 'A'][0];
        int X = wordIndex[word[index] - 'A'][1];
        int distance1 = abs(Y - y1) + abs(X - x1);
        int distance2 = abs(Y - y2) + abs(X - x2);
        if (y2 == -1) {
            DFS(Y, X, y2, x2, word, index + 1, tmpPath + distance1);
            DFS(y1, x1, Y, X, word, index + 1, tmpPath);
        } else {
            DFS(y1, x1, Y, X, word, index + 1, tmpPath + distance2);
            DFS(Y, X, y2, x2, word, index + 1, tmpPath + distance1);
        }
    }

    int minimumDistance(string word) {

        /**
         * DP[i][l][r] 代表以第i个字母结尾,左手恰好在l位置,右手恰好在r位置时最少的步数
         * 为了方便表示未开始时,手指放置的位置以及对应的路径,设置 i = i + 1
         * 初始化DP数组,DP第0行为未开始时左右手的位置,路径为0
         */
        vector<vector<vector<int> > > DP(word.size() + 1, vector<vector<int> >(26, vector<int>(26, 0)));
        for (int i = 1; i <= word.size(); i++) {
            for (int l = 0; l < 26; l++) {
                for (int r = 0; r < 26; r++) {
                    DP[i][l][r] = INT_MAX;
                }
            }
        }

        int res = INT_MAX;
        for (int cur = 1; cur <= word.size(); cur++) {
            // 当前字母
            int curCharInd = word[cur - 1] - 'A';
            // 遍历每一种左右手指所对应的字母情况
            for (int left = 0; left < 26; left++) {
                for (int right = 0; right < 26; right++) {

                    if (DP[cur - 1][left][right] != INT_MAX) { // 存在上一种情况
                        // 左手指从left移动到curCharInd花费的路径
                        DP[cur][curCharInd][right] = min(DP[cur][curCharInd][right],
                                                         DP[cur - 1][left][right] + getDis(left, curCharInd));

                        // 右手指从right移动到curCharInd花费的路径
                        DP[cur][left][curCharInd] = min(DP[cur][left][curCharInd],
                                                        DP[cur - 1][left][right] + getDis(right, curCharInd));
                    }

                    if (cur == word.size()) {
                        res = min(res,
                                  min(DP[cur][curCharInd][right], DP[cur][left][curCharInd])
                                // 左右手指分别移动的最小情况
                        );
                    }
                }
            }
        }
        return res;
    }

    int getDis(int A, int B) {
        int xa = A % 6, ya = A / 6;
        int xb = B % 6, yb = B / 6;
        return abs(xa - xb) + abs(ya - yb);
    }

    vector<int> father; // father[i] 表示以i为下标的父亲节点
    vector<int> child; // 每个节点的孩子数量
    int num; // 全连通需要的最少线缆数

    void initUnionFind(int n) {
        this->father = vector<int>(n);
        this->child = vector<int>(n, 1);
        this->num = n - 1;
        for (int i = 0; i < n; ++i) {
            father[i] = i;
        }
    }

    int find(int n) {
        if (n != father[n]) {
            father[n] = find(father[n]);
        }
        return father[n];
    }

    void unionFather(int a, int b) {
        int i = find(a);
        int j = find(b);
        if (i == j) {
            return;
        }
        if (child[i] < child[j]) {
            father[i] = father[j];
            child[j] += child[i];
        } else {
            father[j] = father[i];
            child[i] += child[j];
        }
    }

    int makeConnected(int n, vector<vector<int>> &connections) {
        // 不满足最低线缆数
        if (connections.size() < n - 1) {
            return -1;
        }
        initUnionFind(n);
        for (auto &v  : connections) {
            int a = v[0];
            int b = v[1];
            if (find(a) != find(b)) {
                // 关键节点必须用线缆,所以线缆数总数-1
                num--;
            }
            unionFather(a, b);
        }
        return this->num;
    }

    int minFlips(int a, int b, int c) {
        int times = 0;
        int d = a | b;
        int k = 1;
        for (int i = 0; i < 31; ++i) {
            if ((d & k) == (c & k)) {

            } else if ((d & k) == 0 && (c & k) == k) {
                times++;
            } else {
                if ((a & k) == k) {
                    times++;
                }
                if ((b & k) == k) {
                    times++;
                }
            }
            k = k << 1;
        }
        return times;
    }
};