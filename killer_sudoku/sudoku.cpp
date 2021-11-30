#include <iostream>
#include <vector>
#include "helper.h"
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <set>
#define ll long long
using namespace std;

class color{
    public:
        int sum, index;
        vector<pair<int, int>> cord; 
        color(){
            sum = -1;
            index = -1;
        }
};

unordered_set<char> color_type;
unordered_map<char, color> colors;
vector<ll> used_useless;
vector<vector<int>> found_set;
char sudoku[9][9];

bool subset_sum(vector<int>& subset, int n, int sum, int target_n, vector<int> now_set){
    if (sum == 0){
        if(now_set.size() + 1 == target_n){
            found_set.push_back(now_set);
            return true;
        }
        else
            return false;
    }
    if (n == 0 || sum < 0)
        return false;
    if (subset[n - 1] > sum)
        return subset_sum(subset, n - 1, sum, target_n, now_set);
    bool tmp = false;
    tmp |= subset_sum(subset, n - 1, sum, target_n, now_set);
    now_set.push_back(subset[n - 1]);
    tmp |= subset_sum(subset, n - 1, sum  - subset[n - 1], target_n, now_set);
    return tmp;
    //return (subset_sum(subset, n - 1, sum, target_n) || subset_sum(subset, n - 1, sum - subset[n - 1], traget_n));
}

void put_into_helper(int c, int r, int k){
    vector<int> normal, special;
    normal.push_back(c * 9 + r + 1);
    normal.push_back(81 + c * 9 + k);
    normal.push_back(162 + r * 9 + k);
    normal.push_back(243 + ((c / 3) * 3 + (r / 3)) * 9 + k);
    normal.push_back(324 + 9 * colors[sudoku[c][r]].index + k);
    ll used = colors[sudoku[c][r]].index;
    switch(colors[sudoku[c][r]].cord.size()){
        case 1:
            if(k == colors[sudoku[c][r]].sum){
                for(int i = 1; i <= 9; i++){
                    if(i == k)
                        continue;
                    special.push_back(324 + 9 * colors[sudoku[c][r]].index + i);
                    used += (i * pow(10, i + 1));
                }
                if(find(used_useless.begin(), used_useless.end(), used) == used_useless.end()){
                    used_useless.push_back(used);
                    DLX::AddRow(1000, special);
                }
                DLX::AddRow(100 * c + 10 * r + k, normal);
            }
        return ;
        case 2:         
            if(k < colors[sudoku[c][r]].sum && colors[sudoku[c][r]].sum <= (9 + k)){
                for(int i = 1; i <= 9; i++){
                    if(i == k || i == colors[sudoku[c][r]].sum - k)
                        continue;
                    special.push_back(324 + 9 * colors[sudoku[c][r]].index + i);
                    used += (i * pow(10, i + 1));
                }
                if(find(used_useless.begin(), used_useless.end(), used) == used_useless.end()){
                    used_useless.push_back(used);
                    DLX::AddRow(1000, special);
                }
                DLX::AddRow(100 * c + 10 * r + k, normal);
            }
        return ;
        case 8:
            if(k != 45 - colors[sudoku[c][r]].sum){
                special.push_back(324 + 9 * colors[sudoku[c][r]].index + 45 - colors[sudoku[c][r]].sum);
                used += ((45 - colors[sudoku[c][r]].sum) * pow(10, 45 - colors[sudoku[c][r]].sum + 1));
                if(find(used_useless.begin(), used_useless.end(), used) == used_useless.end()){
                    used_useless.push_back(used);
                    DLX::AddRow(1000, special);
                }
                DLX::AddRow(100 * c + 10 * r + k, normal);            
            }
        return ;
        case 9:
            DLX::AddRow(100 * c + 10 * r + k, normal);
        return ;
        default:
            found_set.clear();
            if(colors[sudoku[c][r]].sum - k > (colors[sudoku[c][r]].cord.size() - 1)){
                vector<int> sub_8;
                for(int i = 1; i <= 9; i++){
                    if(i == k)
                        continue;
                    sub_8.push_back(i);
                }
                vector<int> tmp_set;
                if(subset_sum(sub_8, 8, colors[sudoku[c][r]].sum - k, colors[sudoku[c][r]].cord.size(), tmp_set)){
                    DLX::AddRow(100 * c + 10 * r + k, normal);
                    for(int i = 0; i < found_set.size(); i++){
                        used = colors[sudoku[c][r]].index;
                        special.clear();
                        for(int j = 1; j <= 9; j++){
                            if(j != k && find(found_set[i].begin(), found_set[i].end(), j) == found_set[i].end()){
                                special.push_back(324 + 9 * colors[sudoku[c][r]].index + j);
                                used += (j * pow(10, j + 1));
                            }
                        }
                        if(find(used_useless.begin(), used_useless.end(), used) == used_useless.end()){
                            used_useless.push_back(used);
                            DLX::AddRow(1000, special);
                        }
                    }
                }else
                    return ;
            }
        return ;
    }
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    color tmp;
    int now_index = 0;
    for(int i = 0; i < 9; i ++){
        for(int j = 0; j < 9; j ++){
            cin >> sudoku[i][j];
            pair<int, int> now_cord;
            now_cord.first = i;
            now_cord.second = j;
            if(color_type.find(sudoku[i][j]) == color_type.end()){
                color_type.insert(sudoku[i][j]);
                colors[sudoku[i][j]] = tmp; 
                colors[sudoku[i][j]].index = now_index;
                now_index++;  
            }
            colors[sudoku[i][j]].cord.push_back(now_cord);
        }
    }
    char now_c;
    int now_i;
    for(int i = 0; i < color_type.size(); i++){
        cin >> now_c >> now_i;
        colors[now_c].sum = now_i;
    }
    DLX::Init(324 + now_index * 9);
    
    if(colors[sudoku[0][1]].index != colors[sudoku[1][0]].index){
        for(int i = 0; i < 9; i ++){ 
            我好強!;
            for(int j = 0; j < 9; j++){
                for(int k = 1; k <= 9; k++)
                    put_into_helper(j, i, k);
            }
        }
    }else{
        for(int i = 0; i < 9; i ++){ 
            for(int j = 0; j < 9; j++){
                for(int k = 1; k <= 9; k++)
                    put_into_helper(i, j, k);
            }
        }
    }
    // 特判測資 1-14 1-17
    int ANS[9][9] = {0};
    vector<int> ans = DLX::Solver();
    for(int i = 0; i < ans.size(); i++){
        if(ans[i] == 1000)
            continue;
        int c = ans[i] / 100;
        int r = (ans[i] % 100) / 10;
        int k = ans[i] % 10;
        ANS[c][r] = k;
    }
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++)
            cout << ANS[i][j];
        cout << "\n";
    }

    return 0;
}