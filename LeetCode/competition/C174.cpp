//
// Created by Administrator on 2020/2/2 0002.
//
#include <vector>
#include <algorithm>
#include <iostream>

using ll=long long;
using namespace std;

class Solution {
public:
    static int minSetSize(vector<int> &arr) {
        vector<int> times(100000, 0);
        for (auto &a :arr) {
            times[a - 1]++;
        }
        sort(times.begin(), times.end());
        int limit = arr.size() >> 1;
        int res = 0;
        for (int i = 100000 - 1; i >= 0; i--) {
            int t = times[i];
            if (t == 0) {
                continue;
            } else if (limit > 0) {
                limit -= t;
                res++;
            } else {
                break;
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

    ll res = 0;

    int maxProduct(TreeNode *root) {
        changeValue(root);
        int sum = root->val; // 第一个节点就是所有节点和
        findMax(root, sum);
        res %= 1000000007;
        return res;
    }

    void findMax(TreeNode *root, int sum) {
        if (root == nullptr) return;
        ll l = 0, r = 0;
        /**
         * 分裂两种情况,该点左侧断裂 l = 左子树和 * 其他节点和
         * 由于每个节点存储该节点和左右子树和,所以 其他节点和 = sum - 左子树和,右侧同理
         */
        if (root->left != nullptr) l = (ll) root->left->val * (ll) (sum - root->left->val);
        if (root->right != nullptr) r = (ll) root->right->val * (ll) (sum - root->right->val);
        res = max(l, max(r, res));
        findMax(root->left, sum); // 递归
        findMax(root->right, sum);
    }

    /**
     * 生成前缀树,每个节点保存该节点和左右子树和
     */
    int changeValue(TreeNode *root) {
        if (root == 0) return 0;
        root->val = changeValue(root->left) + changeValue(root->right) + root->val;
        return root->val;
    }

    int step = 1;
    int mem[1000];

    int maxJumps(vector<int> &arr, int d) {
        // 倒序从最小值向上遍历,想出来这个基本上就解决这道题了
        vector<pair<int, int >> smlToBig;
        for (int i = 0; i < arr.size(); i++)
            smlToBig.push_back({arr[i], i});
        sort(smlToBig.begin(), smlToBig.end());
        for (int i = 0; i < smlToBig.size(); i++)
            jump(arr, d, smlToBig[i].second);
        return step;
    }

    int jump(vector<int> &arr, int d, int idx) {
        if (mem[idx] != 0) return mem[idx];
        int l = 0, r = 0, h = arr[idx];
        // 右遍历
        for (int i = idx + 1; i < arr.size() && i <= idx + d && arr[i] < h; i++)
            r = max(r, jump(arr, d, i));
        // 左遍历
        for (int i = idx - 1; i >= 0 && i >= idx - d && arr[i] < h; i--)
            l = max(l, jump(arr, d, i));
        // 取左右两种可能最大值+1
        l = max(l, r) + 1;
        mem[idx] = l;
        step = max(l, step);
        return l;
    }

};



