//
// Created by Administrator on 2020/1/20 0020.
//
#include <string.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

class Solution {
public:


    int maximum69Number(int num) {
        stack<int> nums;
        while (num != 0) {
            nums.push(num % 10);
            num /= 10;
        }
        int res = 0;
        bool isSix = false;
        while (!nums.empty()) {
            int t = nums.top();nums.pop();
            if (t == 6 && !isSix){
                res = res*10 + 9;
                isSix = true;
            } else{
                res = res*10 + t;
            }
        }
        return res;
    }

    vector<string> printVertically(string s) {
        vector<string> strs = split(s, " ");
        int maxLength = 0;
        int maxIndex = 0;
        for (int i = 0; i < strs.size(); i++) {
            if (maxLength <= strs[i].size()) {
                maxLength = strs[i].size();
            }
        }
        vector<string> res(maxLength, "");
        for (int i = 0; i < strs.size(); i++) {
            for (int j = 0; j < strs[i].size(); j++) {
                res[j].push_back(strs[i][j]);

            }
            for (int k = strs[i].size(); k < maxLength; k++) {
                res[k].push_back(' ');
            }
        }
        for (auto &s : res) {
            rtrim(s);
        }
        return res;
    }


    vector<string> split(const string &str, const string &delim) {
        vector<string> res;
        if ("" == str) return res;
        //先将要切割的字符串从string类型转换为char*类型
        char *strs = new char[str.length() + 1]; //不要忘了
        strcpy(strs, str.c_str());

        char *d = new char[delim.length() + 1];
        strcpy(d, delim.c_str());

        char *p = strtok(strs, d);
        while (p) {
            string s = p; //分割得到的字符串转换为string类型
            res.push_back(s); //存入结果数组
            p = strtok(NULL, d);
        }
        delete[] strs;
        delete[] d;

        return res;
    }


    inline string &ltrim(string &str) {
        string::iterator p = find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isspace)));
        str.erase(str.begin(), p);
        return str;
    }

    inline string &rtrim(string &str) {
        string::reverse_iterator p = find_if(str.rbegin(), str.rend(), not1(ptr_fun<int, int>(isspace)));
        str.erase(p.base(), str.end());
        return str;
    }

    inline string &trim(string &str) {
        ltrim(rtrim(str));
        return str;
    }


    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };


    TreeNode *removeLeafNodes(TreeNode *root, int target) {
        if (root == nullptr) return nullptr;
        root->left = removeLeafNodes(root->left, target);
        root->right = removeLeafNodes(root->right, target);
        return root->left == nullptr && root->right == nullptr && root->val == target ? nullptr : root;
    }


    int minTaps(int n, vector<int> &ranges) {
        vector<int> land(n);
        for (int i = 0; i < ranges.size(); i++) {
            int l = max(i - ranges[i], 0);
            int r = min(i + ranges[i], n);
            for (int j = l; j < r; j++) {
                land[j] = max(land[j], r);
            }
        }

        int cnt = 0;
        int cur = 0;
        while (cur < n) {
            if (land[cur] == 0) return -1;
            cur = land[cur];
            cnt++;
        }
        return cnt;
    }
};