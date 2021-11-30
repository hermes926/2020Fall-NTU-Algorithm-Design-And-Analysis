#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#include <tuple>
#define MAXN 510
#define ll long long int

using namespace std;

ll calculator(ll &k, ll &n, ll &m, ll &c, ll map[MAXN][MAXN], ll sweety[11][MAXN][MAXN], ll largest[11][3]){
    if(k == 0){
        if(n == 0 && m == 0)
            return map[n][m];
        else if(n == 0)
            return map[n][m] + sweety[k][n][m - 1];
        else if(m == 0)
            return map[n][m] + sweety[k][n - 1][m];
        else
            return map[n][m] + max<ll>(sweety[k][n][m - 1], sweety[k][n - 1][m]);
    }else{
        if(n == 0 && m == 0)
            return map[n][m] - c * k + largest[k - 1][0];
        else if(n == 0)
            return map[n][m] - c * k + max<ll>(sweety[k][n][m - 1], largest[k - 1][0]);
        else if(m == 0)
            return map[n][m] - c * k + max<ll>(sweety[k][n - 1][m], largest[k - 1][0]);
        else
            return map[n][m] - c * k + max<ll>({sweety[k][n][m - 1], sweety[k][n - 1][m], largest[k - 1][0]});
    }
}

int main(){
    ll sweety[11][MAXN][MAXN];
    ll map[MAXN][MAXN];
    ll largest[11][3];
    //bool ifcount[11][MAXN][MAXN];
    ll n, m, c, k;
    cin >> n >> m >> k >> c;
    for(ll i = 0; i < n; i ++){
        for(ll j = 0; j < m; j++){
            cin >> map[i][j];
        }
    }
    for(ll i = 0; i <= k; i++){
        largest[i][0] = LLONG_MIN;
        for(ll j = 0; j < n; j++){
            for(ll l = 0; l < m; l ++){
                sweety[i][j][l] = calculator(i, j, l, c, map, sweety, largest);
                //cout << sweety[i][j][l] << endl;
                if(sweety[i][j][l] > largest[i][0]){
                    largest[i][0] = sweety[i][j][l];
                    largest[i][1] = j;
                    largest[i][2] = l;
                }
            }
        }
        
    }
    ll ans = sweety[0][n - 1][m - 1];
    int max_num = 0;
    for(int i = 1; i <= k; i++){
        //cout << sweety[i][n - 1][m - 1] << endl;
        if(sweety[i][n - 1][m - 1] > ans){
            ans = sweety[i][n - 1][m - 1];
            max_num = i;
        }
    }
    int rcount = 0, x = n - 1, y = m - 1;
    vector<tuple<int, int, int>> route;
    while(max_num != -1){
        tuple<int, int ,int>temp(max_num, x, y);
        route.push_back(temp);
        rcount ++;
        //cout << max_num << " " << x << " " << y << endl;
        if(max_num == 0){
            if(x == 0 && y == 0){
                break;
            }else if(x == 0){
                y--;
            }else if(y == 0){
                x--;
            }else{
                if(sweety[max_num][x - 1][y] > sweety[max_num][x][y - 1])
                    x--;
                else
                    y--;
            }
        }
        else{
            if(x == 0 && y == 0){
                max_num --;
                x = largest[max_num][1];
                y = largest[max_num][2];
            }else if(x == 0){
                if(sweety[max_num][x][y - 1] < largest[max_num - 1][0]){
                    max_num --;
                    x = largest[max_num][1];
                    y = largest[max_num][2];   
                }else
                    y--;
            }else if(y == 0){
                if(sweety[max_num][x - 1][y] < largest[max_num - 1][0]){
                    max_num --;
                    x = largest[max_num][1];
                    y = largest[max_num][2];   
                }else
                    x--;
            }else{
                if(sweety[max_num][x - 1][y] <= largest[max_num - 1][0] && sweety[max_num][x][y - 1] <= largest[max_num - 1][0]){
                    max_num --;
                    x = largest[max_num][1];
                    y = largest[max_num][2];   
                }else if(sweety[max_num][x - 1][y] >= largest[max_num - 1][0] && sweety[max_num][x - 1][y] >= sweety[max_num][x][y - 1])
                    x--;
                else
                    y --;
            }
        }
    }
    cout << ans << "\n" << rcount - 1 << "\n";
    for(int i = route.size() - 2; i >= 0; i--){
        if(i == route.size() - 1 || get<0>(route[i]) == get<0>(route[i + 1])){
            cout << "Move ";
        }else
            cout << "Jump ";
        cout << get<1>(route[i]) << " " << get<2>(route[i]) << "\n";
    }
    


    return 0;
}