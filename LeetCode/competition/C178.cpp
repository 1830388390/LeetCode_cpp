//
// Created by Administrator on 2020/3/1 0001.
//
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int> &nums) {
        vector<int> tmp;
        for (auto &i : nums) {
            tmp.push_back(i);
        }
        sort(tmp.begin(), tmp.end());
        vector<int> res;
        for (auto &i : nums) {
            int index = findFirst(tmp, i);
            res.push_back(index);
        }
        return res;
    }

    int findFirst(vector<int> &nums, int k) {
        int l = 0;
        int r = nums.size() - 1;
        while (l <= r) {
            int m = (l + r) >> 1;
            if (nums[m] == k && (m - 1 < 0 || nums[m - 1] != k)) {
                return r;
            } else if (nums[m] >= k) {
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        return l;
    }

    string rankTeams(vector<string> &votes) {
        vector<vector<int>> dw(27, vector<int>(27, 0));
        string res;
        for (auto p : votes) {
            for (int i = 0; i < p.length(); i++) {
                //i是名次 p[i]是选择的队伍
                dw[p[i] - 'A'][i]++;
                dw[p[i] - 'A'].back() = 26 - (p[i] - 'A');
            }
        }
        sort(dw.begin(), dw.end(), greater<vector<int>>());

        for (int i = 0; i < dw.size(); i++) {
            if (dw[i].back() != 0)
                res.push_back(26 - (dw[i].back() - 'A'));
        }
        return res;

    }
/**
 * Definition for singly-linked list.

 */
/**
 * Definition for a binary tree node.

 */

    class TreeNode {
    public:
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    class ListNode {
    public:
        int val;
        ListNode *next;

        ListNode(int x) : val(x), next(NULL) {}
    };


    bool isSubPath(ListNode *head, TreeNode *root) {
        if (head == nullptr) {
            return true;
        }
        if (root == nullptr) {
            return false;
        }
        //先判断当前的节点，如果不对，再看左子树和右子树呗
        return isSub(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }

    bool isSub(ListNode *head, TreeNode *node) {
        //特判：链表走完了，返回true
        if (head == nullptr) {
            return true;
        }
        //特判：链表没走完，树走完了，这肯定不行，返回false
        if (node == nullptr) {
            return false;
        }
        //如果值不同，必定不是啊
        if (head->val != node->val) {
            return false;
        }
        //如果值相同，继续看，左边和右边有一个满足即可
        return isSub(head->next, node->left) || isSub(head->next, node->right);
    }


    bool DFS(ListNode *root, ListNode *cur, TreeNode *tree) {
        if (cur == nullptr) {
            return true;
        }
        if (tree == nullptr) {
            return false;
        }
        bool res = false;
        if (tree->val == root->val) {
            res = res || DFS(root, root->next, tree->left);
            res = res || DFS(root, root->next, tree->right);
        }
        if (cur->val == tree->val) {
            res = res || DFS(root, cur->next, tree->left);
            res = res || DFS(root, cur->next, tree->right);
        }
        res = res || DFS(root, root, tree->left);
        res = res || DFS(root, root, tree->right);
        return res;
    }

    bool BFS(ListNode *head, TreeNode *root) {
        using pp = pair<ListNode *, TreeNode *>;
        queue<pp> q;
        pp r = make_pair(head, root);
        q.push(r);
        while (!q.empty()) {
            pp tmp = q.front();
            q.pop();
            if (tmp.first == nullptr) {
                return true;
            }
            if (tmp.second == nullptr) {
                continue;
            }
            q.push(make_pair(tmp.first->next, tmp.second->left));
            q.push(make_pair(tmp.first->next, tmp.second->right));
            q.push(make_pair(head, tmp.second->left));
            q.push(make_pair(head, tmp.second->right));
        }
        return false;
    }

    int dis[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};
    int minCost(vector<vector<int>>& grid) {
        
    }


};