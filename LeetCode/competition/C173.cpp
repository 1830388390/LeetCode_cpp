//
// Created by Administrator on 2020/1/26 0026.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <cstring>

using namespace std;

class Solution {
public:
    // 餐馆 1 [id=1, rating=4, veganFriendly=1, price=40, distance=10]
    vector<int> filterRestaurants(vector<vector<int>> &restaurants, int veganFriendly, int maxPrice, int maxDistance) {
        vector<vector<int>> idAndRating;
        vector<int> ids;
        for (auto &tmp : restaurants) {
            int id = tmp[0];
            int rating = tmp[1];
            int veganFriendlyT = tmp[2];
            int priceT = tmp[3];
            int distanceT = tmp[4];
            if ((veganFriendly == 0 || veganFriendlyT == veganFriendly)
                && priceT <= maxPrice && distanceT <= maxDistance) {
                idAndRating.push_back({id, rating});
            }
        }
        sort(idAndRating.begin(), idAndRating.end(), [](const auto &p, const auto &q) {
            if (q[1] == p[1]) {
                return q[0] < p[0];
            } else {
                return q[1] < p[1];
            }
        });
        for (auto &id : idAndRating) {
            ids.push_back(id[0]);
        }
        return ids;
    }

    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold) {
        vector<vector<int>> dis(n, vector<int>(n, INT_MAX));
        vector<vector<pair<int, int>>> graph(n);
        for (auto &e : edges) {
            graph[e[0]].push_back(make_pair(e[1], e[2]));
            graph[e[1]].push_back(make_pair(e[0], e[2]));
        }
        // init
        for (int i = 0; i < n; ++i) dis[i][i] = 0;

        // dijkstra
        for (int v = 0; v < n; ++v) {
            priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
            pq.push(make_pair(0, v));

            while (!pq.empty()) {
                int from = pq.top().second;
                pq.pop();
                for (auto &e : graph[from]) {
                    int to = e.first;
                    int cost = e.second;
                    if (dis[v][to] > dis[v][from] + cost) {
                        dis[v][to] = dis[v][from] + cost;
                        pq.push(make_pair(dis[v][to], to));
                    }
                }
            }
        }

        // 统计每个点在阈值内可到达的点数
        vector<int> cnt(n, 0);
        for (int i = 0; i < n; ++i) {
            for (auto &d : dis[i])
                if (d <= distanceThreshold) cnt[i]++;
        }

        // 找出数量最少，编号最大的点
        int minval = INT_MAX;
        for (auto &val : cnt) minval = min(minval, val);

        int res = n - 1;
        for (; res >= 0; res--) if (cnt[res] == minval) break;

        return res;
    }

    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int maxi[310][310];
        int dp[15][310];
        int n = jobDifficulty.size();
        if (d > n) return -1;
        memset(maxi, 0, sizeof(maxi));
        memset(dp, 0x3f, sizeof(dp));

        for (int i = 0; i < n; i++) {
            maxi[i][i] = jobDifficulty[i];
            for (int j = i + 1; j < n; j++)
                maxi[i][j] = max(maxi[i][j - 1], jobDifficulty[j]);
        }
        dp[0][0] = 0;
        for (int day = 1; day <= d; day++) {
            for (int j = day; j <= n; j++) {
                for (int k = day-1; k < j; k++) {
                    dp[day][j] = min(dp[day][j], dp[day - 1][k] + maxi[k][j - 1]);
                }
            }
        }
        return dp[d][n];
    }

};
