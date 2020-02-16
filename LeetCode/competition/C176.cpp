//
// Created by Administrator on 2020/2/16 0016.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution {
public:
    int countNegatives(vector<vector<int>> &grid) {
        int res = 0;
        for (auto &y : grid) {
            for (auto &x : y) {
                if (x < 0) {
                    res++;
                }
            }
        }
        return res;
    }

    class ProductOfNumbers {
    public:
        vector<int> mult;

        ProductOfNumbers() {
            mult.push_back(1);
        }

        void add(int num) {
            if (num == 0) {
                mult.clear();
                mult.push_back(1);
                return;
            }
            int n = mult[mult.size() - 1];
            mult.push_back(n * num);
        }

        int getProduct(int k) {
            if (k >= mult.size()) {
                return 0;
            }
            return mult[mult.size() - 1] / mult[mult.size() - 1 - k];
        }
    };


    int maxEvents(vector<vector<int>> &events) {
        sort(events.begin(), events.end(), [](const vector<int> &e1, const vector<int> &e2) {
            return e1[1] < e2[1];
        });

        unordered_set<int> res;
        for (vector<int> e: events) {
            for (int d = e[0]; d <= e[1]; d++) {
                if (res.find(d) == res.end()) {
                    res.insert(d);
                    break;
                }
            }
        }

        return res.size();
    }

    bool isPossible(vector<int> &target) {
        if (target.size() == 1) return target[0] == 1;     // 首先讨论数组长度只有 1 的情况
        priority_queue<int> heap;                          // 构建最大堆
        for (int val : target) {
            if (val <= 0) return false;                    // 不可能有任何元素小于零
            heap.push(val);
        }
        long long tmp_sum = 0;
        for (int val : target) tmp_sum += val;              // 记录每次数组的和，用 sum(target) 初始化
        while (tmp_sum > target.size()) {                   // 如果数组仍然不是 [1, 1, ..., 1]，即数组和仍然不是数组长度，则循环
            int top_val = heap.top();
            heap.pop();           // 记录数组的最大值，并弹出最大值
            long long tmp_sum_minus = (tmp_sum - top_val);  // 譬如 [5, 9, 17] 的情况，则 tmp_sum_minus = 5 + 9 = 14
            if (top_val <= tmp_sum_minus) return false;     // 如果最大值 17 小于或等于要被减去的数 14，那么这题就是无解的
            heap.push(top_val - tmp_sum_minus);             // 当然 [5, 9, 17] 有解，因此把 17 - 14 = 3 代入到最大堆中
            tmp_sum -= tmp_sum_minus;                       // 最后别忘记把数组和更新一下
        }
        return true;
    }
};