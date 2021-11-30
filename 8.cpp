#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define ll long long
#define MAXN 201

using namespace std;

ll a_i[MAXN], c_i[MAXN], s_i[MAXN]; 
ll dp_table[601][MAXN][MAXN];

int main(){
    ll n, k, d;
    cin >> n >> k >> d;
    for(int i = 0; i < n; i ++)
        cin >> a_i[i];
    for(int i = 0; i < n; i ++)
        cin >> c_i[i];
    for(int i = 0; i < n; i ++)
        cin >> s_i[i];
    for(int cost = 0; cost <= k; cost ++){    
        for(int i = 0; i < n; i ++)
            dp_table[cost][i][i] = s_i[i];
    }
    

    for(int cost = 0; cost <= k; cost++){
        if(cost == 0){
            for(int dif = 1; dif < n; dif ++){
                for(int j = 0; j < n - dif; j++){
                    if(dif == 1 && abs(a_i[j] - a_i[j + dif]) <= d)
                        dp_table[0][j][j + dif] = s_i[j] + s_i[j + dif];
                    else if(abs(a_i[j] - a_i[j + dif]) <= d)
                        dp_table[0][j][j + dif] = max({s_i[j] + s_i[j + dif] + dp_table[0][j + 1][j + dif - 1], dp_table[0][j + 1][j + dif], dp_table[0][j][j + dif - 1]});
                    else
                        dp_table[0][j][j + dif] = max(dp_table[0][j + 1][j + dif], dp_table[0][j][j + dif - 1]);
                }
            }
        }else{
            for(int dif = 1; dif < n; dif ++){
                for(int j = 0; j < n - dif; j++){
                    if(dif == 1 && abs(a_i[j] - a_i[j + dif]) <= d)
                        dp_table[cost][j][j + dif] = s_i[j] + s_i[j + dif];
                    else if(abs(a_i[j] - a_i[j + dif]) <= d)
                        dp_table[cost][j][j + dif] = max({s_i[j] + s_i[j + dif] + dp_table[cost][j + 1][j + dif - 1], dp_table[cost][j + 1][j + dif], dp_table[cost][j][j + dif - 1]});
                    else{
                        if(cost >= min(c_i[j], c_i[j + dif]))
                            dp_table[cost][j][j + dif] = max({dp_table[cost][j + 1][j + dif], dp_table[cost][j][j + dif - 1], dp_table[cost - min(c_i[j], c_i[j + dif])][j + 1][j + dif - 1] + s_i[j] + s_i[j + dif]});
                        else
                            dp_table[cost][j][j + dif] = max(dp_table[cost][j + 1][j + dif], dp_table[cost][j][j + dif - 1]);
                    }
                }
            }            
        }
    }
    
    
    
    
    set<int> ans_seq;
    int cost = k, big = n - 1, small = 0;
    while(big - small > 1){
        if(abs(a_i[big] - a_i[small]) <= d){
            if(dp_table[small + 1][big] > dp_table[small][big - 1] && dp_table[small + 1][big] > s_i[small] + s_i[big] + dp_table[small + 1][big - 1])
                small++;
            else if(dp_table[small][big - 1] > s_i[small] + s_i[big] + dp_table[small + 1][big - 1])
                big--;
            else{
                ans_seq.insert(small);
                ans_seq.insert(big);
                small++;
                big--;
            }
        }else{
            if(dp_table[small + 1][big] > dp_table[small][big - 1])
                small++;
            else
                big--;
        }
    }

    if(big - small == 1 && abs(a_i[big] - a_i[small]) <= d){
        ans_seq.insert(big);
        ans_seq.insert(small);
    }else if(big - small == 1 && s_i[big] > s_i[small])
        ans_seq.insert(big);
    else if(big - small == 1)
        ans_seq.insert(small);    
    else
        ans_seq.insert(big);

    cout << dp_table[0][n - 1] << "\n0\n" << ans_seq.size() << "\n";
    for(auto i : ans_seq)
        cout << i + 1 << " ";
    cout << "\n";


    return 0;
}