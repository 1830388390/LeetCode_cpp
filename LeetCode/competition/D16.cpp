//
// Created by Administrator on 2020/1/4 0004.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>
#include <unordered_map>

using namespace std;

class D16 {
public:
    vector<int> replaceElements(vector<int> &arr) {
        int Max = -1;
        for (int index = arr.size() - 1; index >= 0; index--) {
            int tmp = Max;
            Max = max(arr[index], Max);
            arr[index] = tmp;
        }
        return arr;
    }

    int findBestValue(vector<int> &arr, int target) {

        sort(arr.begin(), arr.end()); //将数组排序,以便创造前缀和数组 查找对应index
        vector<int> prefixArray = vector<int>(arr.size()); // 前缀和数组
        prefixArray[0] = arr[0];

        int right = arr[0];//二分最大值
        int left = 0;//二分最小值

        for (int i = 1; i < arr.size(); i++) {
            right = max(right, arr[i]);
            prefixArray[i] = prefixArray[i - 1] + arr[i];
        }

        int sum = INT_MAX; //当前最接近target数组和
        int value = INT_MAX;
        while (right >= left) {
            int mid = (right + left) >> 1;
            int index = findIndex(arr, mid); // 查找坐标
            int tmpSum = 0;
            if (index == -1) {
                tmpSum = arr.size() * mid;
            } else {
                tmpSum = prefixArray[index] + (arr.size() - 1 - index) * mid;
            }

            // 若当前value与target差值更小, 更新sum和value
            if (abs(tmpSum - target) <= abs(sum - target)) {
                if (abs(tmpSum - target) == abs(sum - target)) {
                    value = min(mid, value);
                } else {
                    value = mid;
                }
                sum = tmpSum;
            }
            // 进行二分
            if (tmpSum - target > 0) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return value;
    }

    /**
     * 查找存在于数组的,
     * 当前恰好大于等于当前value的,
     * 前一个数字坐标.
     * 例如 [1,2,4] 3 => 1
     * 更新后数组和 = 前缀和[index] + ( 数组长度 - 1 - index ) * value
     * index == -1 时,数组和正好为 数组长度*value
     */
    int findIndex(vector<int> &arr, int t) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] >= t) {
                return i - 1;
            }
        }
        return 0;
    }

    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;

        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };

    int deepestLeavesSum(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }
        queue<TreeNode *> levelTraversal;
        levelTraversal.push(root);
        int sum = 0;
        while (!levelTraversal.empty()) {
            int size = levelTraversal.size();
            int tmpSum = 0;
            for (int i = 0; i < size; i++) {
                TreeNode *tmp = levelTraversal.front();
                levelTraversal.pop();
                tmpSum += tmp->val;
                if (tmp->left != nullptr) {
                    levelTraversal.push(tmp->left);
                }
                if (tmp->right != nullptr) {
                    levelTraversal.push(tmp->right);
                }
            }
            sum = tmpSum;
        }
        return sum;
    }

    vector<int> pathsWithMaxScore2(vector<string> &board) {
        unordered_map<int, int> res;
        queue<int *> BFS;
        int maxSum = -1;
        // new int[]{Y, X, SUM}
        BFS.push(new int[3]{1, 0, 0});
        BFS.push(new int[3]{1, 1, 0});
        BFS.push(new int[3]{0, 1, 0});
        int wide = board.size();
        while (!BFS.empty()) {
            int *tmp = BFS.front();
            BFS.pop();
            int Y = tmp[0];
            int X = tmp[1];
            int SUM = tmp[2];
            if (Y >= wide || X >= wide || board[Y][X] == 'X') {
                continue;
            }

            if (board[Y][X] == 'S') {
                if (res.find(SUM) != res.end()) {
                    maxSum = max(SUM, maxSum);
                    res[SUM] = res[SUM] + 1;
                } else {
                    maxSum = max(SUM, maxSum);
                    res[SUM] = 1;
                }
                cout << maxSum << endl;
                continue;
            }
            BFS.push(new int[3]{Y + 1, X, SUM + board[Y][X] - '0'});
            BFS.push(new int[3]{Y + 1, X + 1, SUM + board[Y][X] - '0'});
            BFS.push(new int[3]{Y, X + 1, SUM + board[Y][X] - '0'});
        }
        cout << maxSum << "     " << res[maxSum] << endl;
        return maxSum == -1 ? vector<int>{0, 0} : vector<int>{maxSum, res[maxSum]};
    }

    static vector<int> pathsWithMaxScore(vector<string> &board) {
        //创建DP数组
        int DP[board.size()][board.size()][2];
        //初始化DP的第一行和第一列
        DP[0][0][0] = 0;
        DP[0][0][1] = 0;
        if (board[0][1] == 'X') {
            DP[0][1][0] = 0;
            DP[0][1][1] = 0;
        } else {
            DP[0][1][0] = board[0][1] - '0';
            DP[0][1][1] = 1;
        }
        if (board[1][0] == 'X') {
            DP[1][0][0] = 0;
            DP[1][0][1] = 0;
        } else {
            DP[1][0][0] = board[1][0] - '0';
            DP[1][0][1] = 1;
        }
        for (int y = 2; y < board.size(); y++) {
            if (DP[y - 1][0][0] == 0 || board[y][0] == 'X') {
                DP[y][0][0] = 0;
                DP[y][0][1] = 0;
            } else {
                DP[y][0][0] = board[y][0] + DP[y - 1][0][0] - '0';
                DP[y][0][1] = 1;
            }
        }
        for (int x = 2; x < board.size(); x++) {
            if (DP[0][x - 1][0] == 0 || board[0][x] == 'X'){
                DP[0][x][0] = 0;
                DP[0][x][1] = 0;
            } else{
                DP[0][x][0] = DP[0][x - 1][0] + board[0][x] - '0';
                DP[0][x][1] = 1;
            }
        }
        //初试完毕,直接打表
        for (int y = 1; y < board.size(); y++) {
            for (int x = 1; x < board.size(); x++) {
                if (board[y][x] == 'X') {
                    DP[y][x][0] = 0;
                    DP[y][x][1] = 0;
                    continue;
                }
                int maxSum = max(DP[y - 1][x][0], max(DP[y][x - 1][0], DP[y - 1][x - 1][0]));
                int step = 0;
                if (maxSum != 0) {
                    if (DP[y - 1][x][0] == maxSum) step += DP[y - 1][x][1];
                    if (DP[y - 1][x - 1][0] == maxSum) step += DP[y - 1][x - 1][1];
                    if (DP[y][x - 1][0] == maxSum) step += DP[y][x - 1][1];
                    step %= 1000000007;
                    DP[y][x][0] = maxSum + board[y][x] - '0';
                    DP[y][x][1] = step;
                } else{
                    DP[y][x][0] = 0;
                    DP[y][x][1] = 0;
                }
                if (board[y][x] == 'S') {
                    if (board.size() == 2 && maxSum == 0){
                        return vector<int>{0, 1};
                    } else{
                        return vector<int>{maxSum, step};
                    }
                }
            }
        }
        return vector<int>{0, 0};
    }
};
