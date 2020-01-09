//
// Created by Administrator on 2020/1/5 0005.
//
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> res = vector<int>(n);
        int index = 0;
        int num = 1;
        if (n % 2 == 1) {
            res[index++] = 0;
        }

        for (; index < n; index++) {
            res[index] = num;
            if (num < 0) {
                num = -num + 1;
            } else {
                num = -num;
            }
        }
        return res;
    }

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    vector<int> getAllElements(TreeNode *root1, TreeNode *root2) {
        vector<int> v1 = vector<int>(); // 树1数组
        vector<int> v2 = vector<int>(); // 树2数组
        stack<TreeNode *> sequentialTraversal = stack<TreeNode *>(); // 中序遍历栈

        /**
         * 中序遍历
         */
        while (!sequentialTraversal.empty() || root1 != nullptr) {
            while (root1 != nullptr) {
                sequentialTraversal.push(root1);
                root1 = root1->left;
            }
            root1 = sequentialTraversal.top();
            sequentialTraversal.pop();
            v1.push_back(root1->val);
            root1 = root1->right;
        }

        /**
         * 中序遍历
         */
        while (!sequentialTraversal.empty() || root2 != nullptr) {
            while (root2 != nullptr) {
                sequentialTraversal.push(root2);
                root2 = root2->left;
            }
            root2 = sequentialTraversal.top();
            sequentialTraversal.pop();
            v2.push_back(root2->val);
            root2 = root2->right;
        }

        /**
         * merge 与分治算法merge过程相同
         */
        int i1 = 0;
        int i2 = 0;
        vector<int> res = vector<int>();
        while (i1 <= v1.size() || i2 <= v2.size()) {
            if (i1 == v1.size()) { // 数组1遍历空
                for (int i = i2; i2 < v2.size(); i2++) {
                    res.push_back(v2[i2]);
                }
                break;
            }

            if (i2 == v2.size()) { // 数组2遍历空
                for (int i = i1; i1 < v1.size(); i1++) {
                    res.push_back(v1[i1]);
                }
                break;
            }

            if (v1[i1] >= v2[i2]) {
                res.push_back(v2[i2]);
                i2++;
            } else {
                res.push_back(v1[i1]);
                i1++;
            }
        }
        return res;
    }


    bool canReach2(vector<int> &arr, int start) {
        queue<int> BFS = queue<int>(); // 创建BFS队列
        BFS.push(start);
        while (!BFS.empty()) {
            int cur = BFS.front();
            BFS.pop();
            int tmp = arr[cur];
            if (arr[cur] == 0) { // 遇见0直接返回true
                return true;
            } else if (arr[cur] == -1) { // 遍历过则跳过当前点
                continue;
            } else {
                arr[cur] = -1; // 设置为已遍历过
            }

            /**
             * 防止出界
             */
            if (cur - tmp >= 0) {
                BFS.push(cur - tmp);
            }
            if (cur + tmp < arr.size()) {
                BFS.push(cur + tmp);
            }
        }
        return false;
    }


    bool canReach(vector<int> &arr, int start) {
        // 出界或已遍历过则返回false
        if (start < 0 || start >= arr.size() || arr[start] == -1) return false;
        // 遇到0直接返回true
        if (arr[start] == 0) return true;
        int tmp = arr[start];
        // 标记已遍历过
        arr[start] = -1;
        // DFS
        return canReach(arr, start + tmp) || canReach(arr, start - tmp);
    }

    int wordMapping[26] = {0};   // 字母对应的数字映射
    int isFirst[26] = {0};       // 是否是第一个字母(不允许前导0)
    int weight[26] = {0};        // 字母总共的系数
    int isNumUsed[10] = {0};     // 记录数字是否被用过

    bool isSolvable(vector<string> &words, string result) {

        string str = ""; // 出现过的全部字母(无重复)
        int k = 1;       // 系数

        /**
         * 记录系数 + 判断是否是第一个字母
         */
        for (string s : words) {
            for (int i = s.size() - 1; i >= 0; i--) {
                weight[s[i] - 'A'] += k;
                k *= 10;
                if (i == 0) {
                    isFirst[s[i] - 'A'] = 1;
                }
            }
            k = 1;
        }
        for (int i = result.size() - 1; i >= 0; i--) {
            weight[result[i] - 'A'] -= k;
            k *= 10;
            if (i == 0) {
                isFirst[result[i] - 'A'] = 1;
            }
        }

        bool res = false;
        string word = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for (int i = 0; i < 26; i++) {
            if (weight[i] != 0) {
                str.push_back(word[i]);
            }
        }

        for (int num = 0; num < 10; num++) {
            // 若前导为0 或 已经有正确结果, 则不用向下计算
            if ((num == 0 && isFirst[str[0] - 'A'] == 1) || res) {
                continue;
            } else {
                wordMapping[str[0] - 'A'] = num;
                // 和 = 字母的数字映射 * 字母的系数
                int sum = wordMapping[str[0] - 'A'] * weight[str[0] - 'A'];

                //回溯
                isNumUsed[num] = 1;
                res = DFS(str, 1, sum);
                isNumUsed[num] = 0;
            }
        }
        return res;
    }

    bool DFS(string str, int index, int sum) {
        // 字母全分配完数字映射, 判断sum是否等于零
        if (index == str.size()) {
            return sum == 0;
        }
        char c = str[index];
        bool res = false;
        for (int num = 0; num < 10; num++) {
            // 若前导为0 或 数字已经被用过 或 已经有正确结果, 则不用向下计算
            if ((num == 0 && isFirst[c - 'A'] == 1) || isNumUsed[num] == 1 || res) {
                continue;
            } else {
                wordMapping[c - 'A'] = num;
                int add = wordMapping[c - 'A'] * weight[c - 'A'];

                //回溯
                isNumUsed[num] = 1;
                res = DFS(str, index + 1, sum + add);
                isNumUsed[num] = 0;
            }
        }
        return res;
    }
};


