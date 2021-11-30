#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 100010
#define MAXK 401
#define ll long long

using namespace std;

ll dp_table[MAXN][2];
ll max_d[MAXK] = {0};
ll value[MAXN];

int main(){
    int n, k, a, b;
    cin >> n >> k >> a >> b;
    ll temp;
    vector<ll> value;
    for(int i = 0; i < n; i++){
        cin >> temp;
        value.push_back(temp);
    }
    sort(value.begin(), value.end());
    ll x = 1, ans = 0;
    while(value[value.size() - x] > 0 && x <= k){
        ans += value[value.size() - x];
        x++;
    }
    cout << ans << endl;


    return 0;
}