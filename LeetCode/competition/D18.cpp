//
// Created by Administrator on 2020/1/27 0027.
//
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string breakPalindrome(string palindrome) {
        if (palindrome.size() <= 1) {
            return "";
        }
        for (int i = 0; i < palindrome.size(); i++) {
            if (palindrome[i] != 'a') {
                if (palindrome.size() % 2 == 1 && i == palindrome.size() / 2 + 1) {
                    continue;
                }
                palindrome[i] = 'a';
                return palindrome;
            }
        }
        palindrome[palindrome.size() - 1] = 'b';
        return palindrome;
    }

    vector<vector<int>> diagonalSort(vector<vector<int>> &mat) {
        priority_queue<int, vector<int>, greater<>> pq;
        for (auto &y:mat) {
            for (auto &x : y) {
                pq.push(x);
            }
        }
        int i = 0;
        vector<vector<int>> res(mat.size(), vector<int>(mat[0].size(), INT_MAX));
        int x = mat[0].size() - 1;
        int y = 0, tmpY = 0;
        int dis[2][2] = {{0, -1}, // 向左
                         {1, 0}}; // 向下
        int index = 0;
        while (y < mat.size()) {
            res[y][x] = pq.top();
            pq.pop();
            // 新位置
            int newY = y + dis[index][0];
            int newX = x + dis[index][1];
            // 新 X 小于零,或下个位置已经被占用,则改变方向,向下遍历
            if (newX < 0 || res[y][newX] != INT_MAX && index == 0) {
                index = 1;
                y++;
                continue;
            }
            // 新 Y 大于边长,改变方向,重置起始点
            if (newY >= mat.size()) {
                tmpY++;
                y = tmpY;
                index = 0;
                x = res[0].size() - 1;
                continue;
            }
            // 非特殊情况,直接改变坐标
            x = newX;
            y = newY;
        }
        return res;
    }

    int maxValueAfterReverse(vector<int> &nums) {
        vector<int> dif;
        int sum = 0;
        for (int i = 0; i < nums.size() - 1; i++) {
            int d = abs(nums[i + 1] - nums[i]);
            sum += d;
            dif.push_back(d);
        }
        int k = sum;
        for (int i = 0; i < nums.size() - 1; i++) {
            for (int j = i + 1; j < nums.size(); j++) {
                int newSum = k;
                if (i != 0) {
                    newSum += abs(nums[j] - nums[i - 1])-dif[i-1];
                }
                if (j != nums.size() - 1) {
                    newSum += abs(nums[i] - nums[j + 1])-dif[j];
                }
                sum = max(sum,newSum);
            }
        }
        return sum;
    }
};