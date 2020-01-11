//
// Created by Administrator on 2019/12/27 0027.
//

#include <vector>
using namespace std;
class C168{
public:
    int findNumbers(vector<int>& nums) {
        int res = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0 ||isEven(nums[i])){
                res++;
            }
        }
        return  res;
    }

    bool isEven(int num){
        int n = 1;
        while (num != 0){
            num /= 10;
            n++;
        }
        return n%2 == 0;
    }

};