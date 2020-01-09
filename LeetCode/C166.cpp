#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

class Solution {
public:

    int step;
    int maxStep;

    int minFlips(vector <vector<int>> &mat) {

        int height = mat.size();
        int wide = mat[0].size();
        maxStep = pow(2,height*wide);
        step = maxStep + 1; // step = INT_MAX;
        vector <vector<bool>> isChanged ;
        isChanged.resize(height);
        for (int i = 0; i < height; i++) {
            isChanged[i].resize(wide);
        }
        DFS(mat,isChanged,0);
        return step == maxStep + 1 ? -1 : step;
    }

    void DFS(vector <vector<int>> &mat , vector <vector<bool>> &isChanged , int tmpStep){
        if (isAllZero(mat)){
            step = min(step,tmpStep);
            return;
        }

        for (int y = 0;y<mat.size();y++){
            for (int x = 0; x < mat[0].size(); x++) {
                if (!isChanged[y][x]){
                    reverseMat(mat,y,x);
                    isChanged[y][x] = true;
                    DFS(mat,isChanged,tmpStep + 1);
                    reverseMat(mat,y,x);
                    isChanged[y][x] = false;
                }
            }
        }
    }


    void reverseMat(vector <vector<int>> &mat , int y ,int x){
        mat[y][x] = mat[y][x] == 1 ? 0 : 1;
        if (y - 1>=0){
            mat[y - 1][x] = mat[y - 1][x] == 1 ? 0 : 1;
        }
        if (y + 1<mat.size()){
            mat[y + 1][x] = mat[y + 1][x] == 1 ? 0 : 1;
        }
        if (x - 1>=0){
            mat[y][x - 1] = mat[y][x - 1] == 1 ? 0 : 1;
        }
        if (x + 1<mat[0].size()){
            mat[y][x + 1] = mat[y][x + 1] == 1 ? 0 : 1;
        }
    }


    bool isAllZero(vector <vector<int>> &mat){
        for (int y = 0; y < mat.size(); y++) {
            for (int x = 0 ; x < mat[0].size();x++){
                if(mat[y][x] == 1){
                    return false;
                }

            }
        }
        return true;
    }


};

