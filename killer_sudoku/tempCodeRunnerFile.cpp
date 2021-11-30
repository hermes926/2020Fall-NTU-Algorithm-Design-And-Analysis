#include <iostream>
#include <vector>
#include "helper.h"
#include <unordered_map>
#include <unordered_set>
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
char sudoku[9][9];

void put_into_helper(int c, int r, int k){
    vector<int> normal, special;
    normal.push_back(243 + ((c / 3) * 3 + (r / 3)) * 9 + k);
    normal.push_back(324 + 9 * colors[sudoku[c][r]].index + k);
    normal.push_back(c * 9 + r + 1);
    normal.push_back(81 + r * 9 + k);
    normal.push_back(162 + c * 9 + k);
    switch(colors[sudoku[c][r]].cord.size()){
        case 1:
            /*if(k == colors[sudoku[r][c]].sum){

            }*/
        return ;
        case 2:

        return ;
        case 8:

        return ;
        case 9:
            /*cout << "hi\n";
            for(int i = 0; i < normal.size(); i++)
                cout << normal[i] << " ";
            cout << "\n";*/
            DLX::AddRow(100 * c + 10 * r + k, normal);
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
    //cout << now_index << "\n";
    DLX::Init(405);
    
    
    for(int i = 0; i < 18; i += 2){ 
        for(int j = 0; j < 18; j+= 2){
            for(int k = 1; k <= 9; k++){
                put_into_helper(i % 9, j % 9, k);
            }
        }
    }
    int ANS[9][9] = {0};
    vector<int> ans = DLX::Solver();

    //cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        //cout << ans[i] << "\n";
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