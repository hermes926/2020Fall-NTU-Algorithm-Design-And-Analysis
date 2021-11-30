#include <iostream>
#include <deque>
#include <algorithm>

#define MAXN 100010
#define MAXK 401
#define ll long long

using namespace std;

ll dp_table[MAXN][2];
ll max_n, max_bonus, ans = 0;
ll value[MAXN];

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll n, k, a, b;
    cin >> n >> k >> a >> b;
    for(int i = 0; i < n; i++){
        cin >> value[i];
        if(i == 0 || value[i] > max_d[0])
            max_n = value[i];
        dp_table[i][0] = value[i];
    }
    for(int i = 1; i < k; i ++){
        dp_table[i][i % 2] = dp_table[i - 1][(i - 1) % 2] + value[i] + a * (b - 1);
        max_n = dp_table[i][i % 2];
        max_bonus = max_n;
        for(int j = i + 1; j < n; j ++){
            
            dp_table[j][i % 2] = max(max_bonus, max_n) + value[j];
            max_bonus = max(max_bonus - a, dp_table[j - 1][(i - 1) % 2] + a * (b - 1));
            ans = max(ans, max_bonus);
        }
    }
    cout << ans << endl; 
    return 0;
}