//
// Created by Administrator on 2020/3/23 0023.
//
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

class Solution {
public:
    vector<int> createTargetArray(vector<int> &nums, vector<int> &index) {
        vector<int> res(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            res.insert(res.begin() + index[i], nums[i]);
        }
        return res;
    }

    int sumFourDivisors(vector<int> &nums) {
        int sum = 0;
        for (auto &n:nums) {
            sum += fourSum(n);
        }
        return sum;
    }

    static int fourSum(int num) {
        int sum = num + 1;
        int k = 1;
        for (int i = 2; i < sqrt(num); i++) {
            if (num % i == 0) {
                if (k == 2) {
                    return 0;
                } else {
                    sum += i;
                    sum += num / i;
                    k++;
                }
            }
        }
        if (k == 2) {
            return sum;
        } else {
            return 0;
        }
    }


};

int main() {
    Solution::fourSum(21);
}