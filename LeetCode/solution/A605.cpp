//
// Created by Administrator on 2021/1/2 0002.
//
#include <vector>
#include <functional>
#include <queue>
using namespace std;

class Solution {
public:
    bool canPlaceFlowers(vector<int> &flowerbed, int n) {
        for (int i = 0; i < flowerbed.size(); ++i) {
            if (flowerbed[i] == 1) {
                continue;
            }
            if (i > 0 && flowerbed[i - 1] == 1) {
                continue;
            }
            if (i < flowerbed.size() - 1 && flowerbed[i + 1] == 1) {
                continue;
            }
            flowerbed[i] = 1;
            n--;
        }
        return n >= 0;
    }

    int eatenApples(vector<int> &apples, vector<int> &days) {
        #define Apple pair<int, int>
        int ans = 0;
        int n = apples.size();
        priority_queue <Apple, vector<Apple >, greater<Apple>> q;
        //当i<n时边吃边长，i>=n时只吃不长，q空时吃完
        for (int i = 0; i < n || !q.empty(); i++) {
            //去掉腐烂的
            while (!q.empty() && q.top().first <= i)
                q.pop();
            //加入新长出来的
            if (i < n && apples[i] != 0)
                q.push(make_pair(i + days[i], apples[i]));
            //吃
            if (!q.empty()) {
                Apple temp = q.top();
                q.pop();
                //i<n时一个一个吃，i>=n时一口气吃掉当前能吃的所有这类苹果
                if (i < n) {
                    ans++;
                    temp.second--;
                    //没吃完放回去
                    if (temp.second > 0)
                        q.push(temp);
                } else {
                    ans += min(temp.first - i, temp.second);
                    i += min(temp.first - i, temp.second) - 1;
                }
            }
        }
        return ans;
    }

};