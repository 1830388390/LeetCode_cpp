//
// Created by Administrator on 2020/2/10 0010.
//
/** 22.18**/
/** 23.48**/
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <map>
#include <queue>

using namespace std;

class Solution {
public:
    bool checkIfExist(vector<int> &arr) {
        unordered_set<int> nums;
        for (int &n : arr) {
            if (nums.find(n * 2) != nums.end() ||
                n % 2 == 0 && nums.find(n >> 1) != nums.end()) {
                return true;
            }
            nums.insert(n);
        }
        return false;
    }

    int minSteps(string s, string t) {
        int ch[26]{0};
        for (char &c : s) {
            ch[c - 'a']++;
        }
        for (char &c : t) {
            ch[c - 'a']--;
        }
        int res = 0;
        for (int n : ch) {
            res += abs(n);
        }
        return res >> 1;
    }


    class TweetCounts {
    public:
        TweetCounts() {}

        void recordTweet(string tweetName, int time) {
            record[tweetName][time]++;
        }

        vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
            int f = 1;
            f *= (freq == "minute") ? 60 : 1;
            f *= (freq == "hour") ? 60 * 60 : 1;
            f *= (freq == "day") ? 60 * 60 * 24 : 1;

            vector<int> ans;
            int t = startTime;
            while (t <= endTime) {
                auto bg = record[tweetName].lower_bound(t);
                auto ed = record[tweetName].upper_bound(min(t + f - 1, endTime));
                int cnt = 0;
                for (auto it = bg; it != ed; it++) {
                    cnt += it->second;
                }
                ans.push_back(cnt);
                t += f;
            }
            return ans;
        }

    private:
        unordered_map<string, map<int, int>> record;
    };

    int maxStu = 0;

    int maxStudents(vector<vector<char>> &seats) {
        /** 坏座位#,有人坐!,暂时空置. **/
        DFS(seats, 0, 0, 0);
        return maxStu;
    }

    void DFS(vector<vector<char>> &seats, int y, int x, int stu) {
        if (y >= seats.size() || x >= seats[0].size()) {
            return;
        }
        if (y == seats.size() - 1 && x == seats[0].size() - 1) {
            if (isAccord(seats, y, x)) {
                stu++;
            }
            maxStu = max(maxStu, stu);
            return;
        }
        if (isAccord(seats, y, x)) {
            seats[y][x] = '!';
            DFS(seats, y + 1, x, stu + 1);
            seats[y][x] = '.';
            DFS(seats, y, x + 1, stu);
        } else {
            DFS(seats, y + 1, x, stu);
            DFS(seats, y, x + 1, stu);
        }
    }

    bool isAccord(vector<vector<char >> &seats, int y, int x) {
        if (y >= seats.size() || x < 0 || seats[y][x] != '.') {
            return false;
        }
        int wide = seats[0].size();
        int hight = seats.size();
        if (x + 1 <= wide - 1 && seats[y][x + 1] == '!') {
            return false;
        }
        if (x - 1 >= 0 && seats[y][x - 1] == '!') {
            return false;
        }
        if (x - 1 >= 0 && y + 1 <= hight - 1 && seats[y + 1][x - 1] == '!') {
            return false;
        }
        if (x + 1 <= wide - 1 && y + 1 <= hight - 1 && seats[y + 1][x + 1] == '!') {
            return false;
        }
        return true;
    }
};
