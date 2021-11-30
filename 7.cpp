#include <iostream>
#include <deque>
#include <algorithm>

#define MAXN 100010
#define MAXK 401
#define ll long long

using namespace std;

ll dp_table[MAXN][2];
ll max_d[MAXK];
ll value[MAXN];

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll n, k, a, b;
    cin >> n >> k >> a >> b;
    for(int i = 0; i < n; i++){
        cin >> value[i];
        if(i == 0 || value[i] > max_d[0])
            max_d[0] = value[i];
        dp_table[i][0] = value[i];
    }

    for(int i = 1; i < k; i ++){
        deque<int> mono; 
        if(i >= n)
            break;
        dp_table[i][i % 2] = dp_table[i - 1][(i - 1) % 2] + value[i] + a * (b - 1);
        //cout << dp_table[i][i % 2] << " ";
        max_d[i] = dp_table[i][i % 2];
        int mono_max = -1;
        if(dp_table[i - 1][(i - 1) % 2] < dp_table[i][(i - 1) % 2] + a){
            mono_max = i - 1;
            mono.push_back(i);
        }else{
            mono.push_back(i - 1);
            mono.push_back(i);
        }
        
        for(int j = i + 1; j < n; j ++){
            while(mono.size() > 0 && j - mono.front() >= b){
                if(mono_max == -1 || dp_table[mono_max][(i - 1) % 2] < dp_table[mono.front()][(i - 1) % 2])
                    mono_max = mono.front();
                mono.pop_front();
            }
            if(mono.size() == 0)
                dp_table[j][i % 2] = dp_table[mono_max][(i - 1) % 2] + value[j]; 
            else if(mono_max == -1)
                dp_table[j][i % 2] = dp_table[mono.front()][(i - 1) % 2] + a * (b - (j - mono.front())) + value[j];
            else
                dp_table[j][i % 2] = max(dp_table[mono.front()][(i - 1) % 2] + a *(b - (j - mono.front())), dp_table[mono_max][(i - 1) % 2]) + value[j];
            while(mono.size() > 0 && dp_table[j][(i - 1) % 2] > dp_table[mono.back()][(i - 1) % 2] - a * (j - mono.back())){
                if(dp_table[mono.back()][(i - 1) % 2] > dp_table[mono_max][(i - 1) % 2])
                    mono_max = mono.back();
                mono.pop_back();
            }
            mono.push_back(j);
            max_d[i] = (dp_table[j][i % 2] > max_d[i]) ? dp_table[j][i % 2] : max_d[i];
            //cout << dp_table[j][i % 2] << " ";
        }
        //cout << endl;
    }
    ll max_ans = max_d[0] > 0 ? max_d[0] : 0;
    for(int i = 1; i < min(k, n); i++){
        if(max_d[i] > max_ans)
            max_ans = max_d[i];
    }
    cout << max_ans << endl; 
    return 0;
}