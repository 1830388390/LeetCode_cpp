//
// Created by Administrator on 2020/2/8 0008.
//
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    int numberOfSteps(int num) {
        if (num == 0) {
            return 0;
        }
        int k = num % 2 == 0 ? num >> 1 : num - 1;
        return numberOfSteps(k) + 1;
    }

    int numOfSubarrays(vector<int> &arr, int k, int threshold) {
        vector<int> prifx; // 前缀和
        prifx[1] = arr[0];
        for (int i = 1; i < arr.size(); i++) {
            prifx[i + 1] = prifx[i] + arr[i];
        }
        int left = 0;
        int res = 0;
        while (left < arr.size() && left + k < arr.size()) {
            // 检验是否满足条件,满足条件res++,无论是否满足left都要向后移动
            if ((prifx[left + k] - prifx[left]) / k < threshold) {
                left++;
                continue;
            }
            res++;
        }
        return res;
    }

    double angleClock(int hour, int minutes) {
        double min = minutes * 6 >= 360 ? minutes * 6 - 360 : minutes * 6;
        double hor = hour * 30 + minutes / (float) 2 >= 360
                ? hour * 30 + minutes / (float) 2 - 360 : hour * 30 +minutes /(float) 2;
        double a = abs(min - hor);
        double b = abs(hor - min);
        a = a > b ? b : a;
        return a > 180 ? (float) 180 - a : a;
    }

    int minJumps(vector<int> &arr) {
        if (arr.size() == 1) {
            return 0;
        }
        vector<int> narr; // 新数组
        narr.push_back(arr[0]);
        /**
         * 将相同的数合并,创造新数组.
         * [7,7,2]这种数组合并后为[7,2]输出为1,正确答案为2,
         * 为了防止第一个相同的数被消除,设置标志f
         */
        int f = 0;
        for (int i = 1; i < arr.size(); i++) {
            if(f == 0){
                narr.push_back(arr[i]);
                f = 2;
                continue;
            }
            if (arr[i] != arr[i - 1]) {
                narr.push_back(arr[i]);
            }
        }
        if (narr.size() == 1) {
            return 0;
        }
        unordered_map<int, vector<int>> same; // 记录相同的数所在的不同的位置
        for (int i = 0; i < narr.size(); i++) {
            if (same.find(narr[i]) == same.end()) {
                same[narr[i]] = vector<int>();
                same[narr[i]].push_back(i);
            } else {
                same[narr[i]].push_back(i);
            }
        }
        queue<int> BFS;
        BFS.push(0);
        int path = 0;
        vector<int> used(narr.size(), 0); // 记忆数组
        while (!BFS.empty()) {
            int size = BFS.size();
            for (int i = 0; i < size; ++i) {
                int k = BFS.front();
                BFS.pop();
                // 遍历到最后,返回答案
                if (k == narr.size()) {
                    return path;
                }
                // 将k-1放入
                if (k - 1 >= 0 && used[k - 1] == 0) {
                    BFS.push(k - 1);
                    used[k - 1] = 1;
                }
                // 将k+1放入
                if (k + 1 < narr.size() && used[k + 1] == 0) {
                    BFS.push(k + 1);
                    used[k + 1] = 1;
                }
                // 将遍历相同数字的坐标放入
                for (int z : same[narr[k]]) {
                    if(z == k) continue;
                    if(used[z] == 0){
                        BFS.push(z);
                        used[z] = 1;
                    }
                }
            }
            path++;
        }
        return 0;
    }
};
