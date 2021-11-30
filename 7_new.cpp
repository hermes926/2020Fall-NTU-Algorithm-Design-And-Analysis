#include <iostream>
#include <deque>
#include <algorithm>
#include <cstring>

#define MAXN 100010
#define MAXK 401
#define ll long long

using namespace std;

ll dp_table[MAXN][2];
ll max_d[MAXK];
ll value[MAXN];
int mono[MAXN];

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
        memset(mono, 0, n * sizeof(int));
        int l = 0, r = 0; 
        if(i >= n)
            break;
        dp_table[i][i % 2] = dp_table[i - 1][(i - 1) % 2] + value[i] + a * (b - 1);
        //cout << dp_table[i][i % 2] << " ";
        max_d[i] = dp_table[i][i % 2];
        int mono_max = -1;
        if(dp_table[i - 1][(i - 1) % 2] < dp_table[i][(i - 1) % 2] + a){
            mono_max = i - 1;
            mono[r] = i;
            r++;
        }else{
            mono[r] = i - 1;
            r++;
            mono[r] = i;
            r++;
        }
        for(int j = i + 1; j < n; j ++){
            //cout << l << " " << r << endl;
            while(r - l > 0 && j - mono[l] >= b){
                if(mono_max == -1 || dp_table[mono_max][(i - 1) % 2] < dp_table[mono[l]][(i - 1) % 2])
                    mono_max = mono[l];
                //cout << l << endl;
                l++;
            }
            if(r - l == 0)
                dp_table[j][i % 2] = dp_table[mono_max][(i - 1) % 2] + value[j]; 
            else if(mono_max == -1)
                dp_table[j][i % 2] = dp_table[mono[l]][(i - 1) % 2] + a * (b - (j - mono[l])) + value[j];
            else
                dp_table[j][i % 2] = max(dp_table[mono[l]][(i - 1) % 2] + a *(b - (j - mono[l])), dp_table[mono_max][(i - 1) % 2]) + value[j];
            //cout << dp_table[j][(i - 1) % 2] << " " << dp_table[mono[r]][(i - 1) % 2] << " " << a * (j - mono[r]) << endl;
            while(r - l > 0 && dp_table[j][(i - 1) % 2] > dp_table[mono[r - 1]][(i - 1) % 2] - a * (j - mono[r - 1])){
                if(dp_table[mono[r - 1]][(i - 1) % 2] > dp_table[mono_max][(i - 1) % 2])
                    mono_max = mono[r - 1];
                //cout << r << endl;
                r--;
            }
            mono[r] = j;
            r++;
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