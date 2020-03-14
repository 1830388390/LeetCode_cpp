//
// Created by Administrator on 2020/3/1 0001.
//

#include <clocale>

class ListNode {
public:
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class TreeNode {
public:
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};