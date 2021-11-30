#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <climits>
#include <utility>

#define ll long long
#define MAXN 210

using namespace std;

ll a_i[MAXN], c_i[MAXN], s_i[MAXN]; 
ll dp_table[MAXN][MAXN][610];
int wow[MAXN][MAXN][601];

int main(){
    ll n, k, d;
    cin >> n >> k >> d;
    for(int i = 0; i < n; i ++)
        cin >> a_i[i];
    for(int i = 0; i < n; i ++)
        cin >> c_i[i];
    for(int i = 0; i < n; i ++)
        cin >> s_i[i];
    int max_val = n * 3;    

    for(int i = 0; i < n; i ++){
        for(int j = 0; j < n; j ++){
            for(int l = 0; l <= max_val; l ++){
                dp_table[j][i][l] = INT_MAX;
                dp_table[j][i][l] *= 1000;
                wow[j][i][l] = -1;
            }
        }
    }

    for(int i = 0; i < n; i ++){    
        for(int val = 0; val <= s_i[i]; val ++)
            dp_table[i][i][val] = 0;
    }
    //cout << dp_table[max_val][0][n - 1] << endl; 
    for(int dif = 1; dif < n; dif ++){
        for(int j = 0; j < n - dif; j++){
            if(dif == 1 && abs(a_i[j] - a_i[j + dif]) <= d){
                for(int val = 0; val <= s_i[j] + s_i[j + dif]; val ++){
                    wow[j][j + dif][val] = 2;
                    dp_table[j][j + dif][val] = 0;
                }
            }
            else if(abs(a_i[j] - a_i[j + dif]) <= d){
                for(int val = 0; val <= s_i[j] + s_i[j + dif]; val ++){
                    wow[j][j + dif][val] = 2;
                    dp_table[j][j + dif][val] = 0;
                }for(int val = s_i[j] + s_i[j + dif] + 1; val <= max_val; val++){
                    dp_table[j][j + dif][val] = min({dp_table[j + 1][j + dif - 1][val - s_i[j] - s_i[j + dif]], dp_table[j + 1][j + dif][val], dp_table[j][j + dif - 1][val]});
                    if(dp_table[j + 1][j + dif - 1][val - s_i[j] - s_i[j + dif]] <= dp_table[j + 1][j + dif][val] && dp_table[j + 1][j + dif - 1][val - s_i[j] - s_i[j + dif]] <= dp_table[j][j + dif - 1][val])
                        wow[j][j + dif][val] = 2;
                    else if(dp_table[j + 1][j + dif][val] <= dp_table[j][j + dif - 1][val])
                        wow[j][j + dif][val] = 0;
                    else
                        wow[j][j + dif][val] = 1;
                }
            }
            //    dp_table[cost][j][j + dif] = max({s_i[j] + s_i[j + dif] + dp_table[cost][j + 1][j + dif - 1], dp_table[cost][j + 1][j + dif], dp_table[cost][j][j + dif - 1]});
            else{
                //dp_table[0][j][j + dif] = 0;
                for(int val = 0; val <= s_i[j] + s_i[j + dif]; val++){
                    dp_table[j][j + dif][val] = min({c_i[j + dif], c_i[j], dp_table[j + 1][j + dif][val], dp_table[j][j + dif - 1][val]});
                    if(c_i[j + dif] <= c_i[j] && c_i[j + dif] <= dp_table[j + 1][j + dif][val] && c_i[j + dif] <= dp_table[j][j + dif - 1][val])
                        wow[j][j + dif][val] = 4;
                    else if(c_i[j] <= dp_table[j + 1][j + dif][val] && c_i[j] <= dp_table[j][j + dif - 1][val])
                        wow[j][j + dif][val] = 3;
                    else if(dp_table[j + 1][j + dif][val] <= dp_table[j][j + dif - 1][val])
                        wow[j][j + dif][val] = 0;
                    else
                        wow[j][j + dif][val] = 1;
                }
                for(int val = s_i[j] + s_i[j + dif] + 1; val <= max_val; val ++){
                    dp_table[j][j + dif][val] = min({dp_table[j + 1][j + dif - 1][val - s_i[j] - s_i[j + dif]] + min(c_i[j + dif], c_i[j]), dp_table[j + 1][j + dif][val], dp_table[j][j + dif - 1][val]});
                    if(c_i[j + dif] <= c_i[j] && dp_table[j + 1][j + dif - 1][val - s_i[j] - s_i[j + dif]] + c_i[j + dif] <= dp_table[j + 1][j + dif][val] && dp_table[j + 1][j + dif - 1][val - s_i[j] - s_i[j + dif]] + c_i[j + dif] <= dp_table[j][j + dif - 1][val])
                        wow[j][j + dif][val] = 4;
                    else if(c_i[j] + dp_table[j + 1][j + dif - 1][val - s_i[j] - s_i[j + dif]] <= dp_table[j + 1][j + dif][val] && dp_table[j + 1][j + dif - 1][val - s_i[j] - s_i[j + dif]] + c_i[j] <= dp_table[j][j + dif - 1][val])
                        wow[j][j + dif][val] = 3;
                    else if(dp_table[j + 1][j + dif][val] <= dp_table[j][j + dif - 1][val])
                        wow[j][j + dif][val] = 0;
                    else
                        wow[j][j + dif][val] = 1;
                }
            }
        }
    }
    
    int ans_val = 0, ans_t = 0;
    for(int i = 0; i <= max_val; i ++)
        ans_val = (dp_table[0][n - 1][i] <= k) ?  i : ans_val;
    //cout << dp_table[0][n - 1][600] << endl;
    //cout << ans_val << endl;
    ans_t = ans_val;  
    set<int> ans_seq;
    set<pair<int, ll>> mod_seq;
    pair<int, ll> tmp;
    int big = n - 1, small = 0;
    while(big - small > 0){
        if(wow[small][big][ans_t] == -1)
            break;
        //cout << wow[small][big][ans_t] << " " << small << " " << big << " " << ans_t << endl ;
        switch(wow[small][big][ans_t]){
            case 0:
                small++;
                break;
            case 1:
                big--;
                break;
            case 2:
                ans_seq.insert(big);
                ans_seq.insert(small);
                ans_t -= (s_i[big] + s_i[small]);
                small++;
                big--;
                break;
            case 3:
                tmp.first = small;
                tmp.second =  a_i[big];
                mod_seq.insert(tmp);
                ans_seq.insert(big);
                ans_seq.insert(small);
                ans_t -= (s_i[big] + s_i[small]);
                small++;
                big--;
                
                break;
            case 4:
                tmp.first = big;
                tmp.second =  a_i[small];                
                mod_seq.insert(tmp);
                ans_seq.insert(big);
                ans_seq.insert(small);
                ans_t -= (s_i[big] + s_i[small]);
                small++;
                big--;
                
                break;        
            default:
                cout << "error\n";
                break;      
        }
    }
    ans_seq.insert(big);

    cout << ans_val << "\n" << mod_seq.size() << "\n";
    for(auto i : mod_seq)
        cout << i.first + 1 << " " << i.second << "\n";
    cout << ans_seq.size() << "\n";
    for(auto i : ans_seq)
        cout << i + 1 << " ";
    cout << "\n";
    
    return 0;
}