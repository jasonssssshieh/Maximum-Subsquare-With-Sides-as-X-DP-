//
//  main.cpp
//  Maximum Subsquare With Sides as X DP
//
//  Created by Zijian Xie on 2016/11/13.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//
// Space: O(m*n), Time: O(m*n*min(m,n));
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

class MaxSubX{
private:
    vector<vector<char>> mtx;
public:
    MaxSubX(vector<vector<char>>& mtx){
        this->mtx = mtx;
    }
    int DP(){
        if(mtx.empty()) return 0;
        int m = (int)mtx.size();
        int n = (int)mtx[0].size();
        vector<vector<pair<int,int>>> dp(m,vector<pair<int,int>>(n));
        if(mtx[0][0] == 'X'){
            dp[0][0] = {1,1};
        }else{
            dp[0][0] = {0,0};
        }
        //horizal vertical
        for(int i = 1; i < m; ++i){
            if(mtx[i][0] == 'X'){dp[i][0].first = dp[i-1][0].first + 1, dp[i][0].second = 1;}
            else{dp[i][0] = {0,0};}
        }
        for(int j = 1; j < n; ++j){
            if(mtx[0][j] == 'X'){dp[0][j].first = dp[0][j-1].second + 1, dp[0][j].first = 1;}
            else{dp[0][j] = {0,0};}
        }
        
        for(int i = 1; i < m; ++i){
            for(int j = 1; j < n; ++j){
                if(mtx[i][j] != 'X'){dp[i][j] = {0,0};}
                else{
                    dp[i][j].first = dp[i][j-1].first + 1;
                    dp[i][j].second = dp[i-1][j].second + 1;
                }
            }
        }
        int res = INT_MIN;
        int side_end = 1;//也就是控制循环结束，比如说我们现在最大的边长已经是5，那么对于在dp[5][5]以内的那些点，其实就不必考虑了
        for(int i = m - 1; i >= side_end - 1; --i){
            for(int j = n - 1; j >= side_end - 1; --j){
                if(!dp[i][j].first || !dp[i][j].second) continue;//只要有一个为0.那么肯定无法构成
                int side = min(dp[i][j].first, dp[i][j].second);
                while(side >= 1){
                    int i_tmp = i - side + 1, j_tmp = j - side + 1;
                    if(dp[i][j_tmp].second >= side && dp[i_tmp][j].first >= side){
                        res = max(res, side*side);
                        side_end = side;
                        break;
                    }
                    side--;
                }
            }
        }
        if(res == INT_MIN) res = 0;
        cout<<"The max square area is: "<<res<<". "<<endl;
        return res;
    }
};

int main(){
    vector<vector<char>> mtx = {{'O','O','O','O','X'},{'X','O','X','X','X'},{'X','O','X','O','X'},{'X','X','X','X','X'},{'O','O','X','X','X'}};
    MaxSubX* test = new MaxSubX(mtx);
    test->DP();
    return 0;
}
