//
// Created by Administrator on 2020/1/9 0009.
//
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;
using PSI = pair<string, int>;

class C170 {
public:
    /**
     * 字符（'a' - 'i'）分别用（'1' - '9'）表示。
     * 字符（'j' - 'z'）分别用（'10#' - '26#'）表示。
     */
    //abc#
    static string freqAlphabets(string s) {
        string words = "#abcdefghijklmnopqrstuvwxyz";
        string res = "";
        int index = s.size() - 1;
        while (index >= 0) {
            if (s[index] == '#') {
                int a = stoi(s.substr(index - 2, index));
                res = words[a] + res;
                index -= 3;
                continue;
            }
            int a = s[index] - '0';
            res = words[a] + res;
            index--;
        }
        return res;
    }


    vector<int> xorQueries(vector<int> &arr, vector<vector<int>> &queries) {
        vector<int> prefix(arr.size() + 1);
        for (int i = 1; i <= arr.size(); i++) {
            prefix[i] = prefix[i - 1] ^ arr[i - 1];
        }
        vector<int> res;
        for (auto &q : queries) {
            res.push_back(prefix[q[0]] ^ prefix[q[1] + 1]);
        }
        return res;
    }


    vector<string>
    watchedVideosByFriends(vector<vector<string>> &watchedVideos, vector<vector<int>> &friends, int id, int level) {
        int n = friends.size();
        vector<bool> used(n);
        queue<int> q;
        q.push(id);
        used[id] = true;
        for (int _ = 1; _ <= level; ++_) {
            int span = q.size();
            for (int i = 0; i < span; ++i) {
                int u = q.front();
                q.pop();
                for (int v: friends[u]) {
                    if (!used[v]) {
                        q.push(v);
                        used[v] = true;
                    }
                }
            }
        }

        unordered_map<string, int> freq;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (const string &watched: watchedVideos[u]) {
                ++freq[watched];
            }
        }

        vector<PSI> videos(freq.begin(), freq.end());
        sort(videos.begin(), videos.end(), [](const PSI &p, const PSI &q) {
            return p.second < q.second || (p.second == q.second && p.first < q.first);
        });

        vector<string> ans;
        for (const PSI &video: videos) {
            ans.push_back(video.first);
        }
        return ans;
    }

    int minInsertions(string s) {
        vector<vector<int>> DP(s.size(), vector<int>(s.size())); // 创建DP数组
        for (int left = s.size()-1; left >= 0; left--) {
            DP[left][left] = 1; // 初始化单个字符回文长度为 1
            for (int right = left + 1; right < s.size(); right++) {
                if (s[left] == s[right]) {
                    /**
                     * 左右字符相等 , 则DP[left][right]为除了左右两个字符的最大回文长度加2
                     * 即 [aba] = 1 + [b] + 1
                     */
                    DP[left][right] = DP[left + 1][right - 1] + 2;
                } else {
                    /**
                     * 左右字符不相等 , 则DP[left][right]为"除了左字符的串"和"除了右字符的串"的最大回文长度
                     * 即[abc] = max( [bc] , [ab] )
                     */
                    DP[left][right] = max(DP[left + 1][right], DP[left][right - 1]);
                }
            }
        }
        return s.size() - DP[s.size()][s.size()];
    }


    //集合表示 dp[i][j] 对前i个字符进行操作,转换为目标的前j个字符的操作次数 属性->操作次数最小值

    //集合划分 dp[i][j]的来源  考虑对第i个字符进行的操作是什么
    //1 插入操作 从而相等 所以先让前i个字符变为j-1字符，然后在第i处插入j代表的字符 即dp[i][j-1]+1
    //2 删除操作 从而相等 所以先让前i-1个字符变为j字符，然后在第i处删除 即dp[i-1][j]+1
    //3 替换操作 从而相等 if(i处等于j处 不需要替换) 即dp[i-1][j-1]
    //                   else 需要替换 dp[i-1][j-1]+1
    //上述取个最小值即可
    int minDistance(string w1, string w2) {
        int n = w1.size(), m = w2.size();
        vector<vector<int>> dp(n+1,vector<int>(m+1));
        for(int i = 0; i <= n; i++) dp[i][0] = i;//i个字符转化为0个字符 只能一直删i次
        for(int j = 0; j <= m; j++) dp[0][j] = j;//0个字符转化为j个字符 只能一直插入j次
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                dp[i][j] = min(dp[i][j-1],dp[i-1][j])+1;//插入 删除 时
                dp[i][j] = min(dp[i][j],dp[i-1][j-1] + (w1[i-1]==w2[j-1] ? 0:1));//替换时
            }
        }
        return dp[n][m];
    }

};
