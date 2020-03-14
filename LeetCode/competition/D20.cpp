//
// Created by Administrator on 2020/2/22 0022.
//
#include <vector>
#include <algorithm>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> sortByBits(vector<int> &arr) {
        using pio = pair<int, int>;
        vector<pio> nums;
        for (auto &i : arr) {
            nums.push_back(make_pair(i, NumberOf1(i)));
        }
        sort(nums.begin(), nums.end(), [](const pio &a, const pio &b) {
            return a.second < b.second || a.first < b.first;
        });
        vector<int> res;
        for (pio &i:nums) {
            res.push_back(i.first);
        }
        return res;
    }

    int NumberOf1(int n) {
        int count = 0;
        unsigned int flag = 1;
        while (flag) {
            if (n & flag) {
                count++;
            }
            flag = flag << 1;
        }
        return count;
    }

    class Cashier {
    public:
        unordered_map<int,int> pnum;
        int n;
        int discount;
        int i = 0;
        vector<int> prices;
        Cashier(int n, int discount, vector<int> &products, vector<int> &prices) {
            this->prices = prices;
            for(int i = 0;i<products.size();i++){
                pnum[products[i]] = i;
            }
            this->n = n;
            this->discount = discount;
        }

        double getBill(vector<int> product, vector<int> amount) {
            i++;
            double sum = 0;
            for (int i = 0; i < product.size(); i++) {
                int num = pnum[product[i]];
                sum += prices[num] * amount[i];
            }
            if (i % n == 0) {
                // x - (discount * x) / 100
                sum -= ((double) discount * sum) / 100;
            }
            return sum;
        }
    };

    int numberOfSubstrings(string s) {
        vector<int> c(3);
        int i = 0;
        int l = 0;
        int r = 0;
        int res = 0;
        while (l < s.size() && r < s.size()) {
            char cr = s[r];
            i |= 1 << (cr - 'a');
            c[cr - 'a']++;
            //将二进制的第n位变为0.
            //int ret = num & ~(1 << n);
            if (i == 7) {
                while (i == 7) {
                    res += s.size() - r - 1;
                    if (r == s.size() - 1){
                        res++;
                    }
                    char lr = s[l];
                    if (--c[lr - 'a'] == 0) {
                        int ret = i & ~(1 << (lr - 'a'));
                        break;
                    }
                    l++;
                }
            }
            r++;
        }
        return res;
    }
};