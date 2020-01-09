//
// Created by Administrator on 2020/1/9 0009.
//
#include <clocale>
#include <unordered_set>
using namespace std;
/**
 * Definition for a binary tree node.

 */
class Solution {
public:
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    unordered_set<int > nums = unordered_set<int>();
    bool findTarget(TreeNode *root, int k) {
        if (root == nullptr){
            return false;
        }
        if (nums.find(k - root->val)!=nums.end()){
            return true;
        }
        nums.insert(root->val);
        return findTarget(root->left,k) || findTarget(root->right,k);
    }
};