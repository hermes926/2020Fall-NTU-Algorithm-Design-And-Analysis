#include <iostream>
#include <algorithm>
#include <vector>
#define MAXN 20

using namespace std;

typedef struct pos{
    long long int sweet, sweet_o, map;
    bool ifcount, ifcount_o;
};

long long int findsweet_o(int n, int m, int x, int y, pos dp_data[MAXN][MAXN]){
    long long int sweety_o = 0;
    if(dp_data[x][y].ifcount_o)
        return dp_data[x][y].sweet_o;
    dp_data[x][y].ifcount_o = true;
    if(x == 0 && y == 0)
        sweety_o = dp_data[x][y].map;
    else if(x == 0)
        sweety_o = dp_data[x][y].map + findsweet_o(n, m, x, y-1, dp_data);
    else if(y == 0)
        sweety_o = dp_data[x][y].map + findsweet_o(n, m, x - 1, y, dp_data);
    else{
        long long int tx = findsweet_o(n, m, x, y-1, dp_data);
        long long int ty = findsweet_o(n, m, x - 1, y, dp_data);
        sweety_o = dp_data[x][y].map + max<long long int>(tx, ty);
    }
    dp_data[x][y].sweet_o = sweety_o;
    return sweety_o;
}

long long int findsweet(int n, int m, int x, int y, pos dp_data[MAXN][MAXN]){
    long long int sweety = 0;
    //cout << x << " " << y << endl;
    if(dp_data[x][y].ifcount)
        return dp_data[x][y].sweet;
    dp_data[x][y].ifcount = true;
    sweety = dp_data[x][y].map;
    if(x == 0 && y == 0)
        sweety *= 1;
    else if(x == 0){
        long long int t = findsweet(n, m, x, y-1, dp_data);
        if(t > 0)
            sweety += t;
    }
    else if(y == 0){
        long long int t = findsweet(n, m, x - 1, y, dp_data);       
        if(t > 0)
            sweety += t;
    }
    else{
        long long int tx = findsweet(n, m, x, y-1, dp_data), ty = findsweet(n, m, x - 1, y, dp_data);
        if(ty >= tx && ty > 0)
            sweety += ty;
        else if(tx > ty && tx > 0)
            sweety += tx;
    }
    dp_data[x][y].sweet = sweety;
    return sweety;
}

int move_o(int x1, int x2, int y1, int y2, pos dp_data[MAXN][MAXN], vector<pair<int, int>> &route_o){
        //vector<pair<int, int>> route_o;
        int r = 0;
        while(x2 > x1 || y2 > y1){
            pair<int, int> temp(x2, y2);
            if(x2 == x1){    
                y2--;
            }else if(y2 == y1){
                x2--;
            }else{
                if(dp_data[x2 - 1][y2].sweet_o > dp_data[x2][y2 - 1].sweet_o)
                    x2--;
                else
                    y2--;
            }
            route_o.push_back(temp);
            r++;
        }
        return r;
}

int move(int x, int y, pos dp_data[MAXN][MAXN], vector<pair<int, int>> &route){
        int r = 0;
        while(x > 0 || y > 0){
            pair<int, int> temp(x, y);
            route.push_back(temp);
            r++;
            if(x == 0){    
                if(dp_data[x][y - 1].sweet <= 0)
                    break;
                y--;
            }else if(y == 0){
                if(dp_data[x - 1][y].sweet <= 0)
                    break;
                x--;
            }else{
                if(dp_data[x - 1][y].sweet <= 0 && dp_data[x][y - 1].sweet <= 0)
                    break;
                else if(dp_data[x - 1][y].sweet > dp_data[x][y - 1].sweet)
                    x--;
                else
                    y--;
            }
        }
        return r;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m, k, c;
    cin >> n >> m >> k >> c;
    pos dp_data[MAXN][MAXN];
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j++){
            cin >> dp_data[i][j].map;
            dp_data[i][j].ifcount = false;
            dp_data[i][j].ifcount_o = false;
        }
    }
    long long int ans_o = findsweet_o(n, m, n - 1, m-1, dp_data);
    int x = n - 1, y = m - 1;
    //k = 1;
    vector<pair<int, int>> route;
    if(k == 0){
        cout << dp_data[n - 1][m - 1].sweet_o << "\n" << n + m - 2 << "\n";
        move_o(0, n - 1, 0, m - 1, dp_data, route);
        for(int i = route.size() - 1; i >= 0; i--)
            cout << "Move " << route.at(i).first << " " << route.at(i).second << "\n";
    }else if(k == 1){
        long long int ans_1 = ans_o;
        int x1 = n - 1, y1 = m - 1; 
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                dp_data[i][j].map -= c;
                if(ans_1 <= dp_data[i][j].sweet_o){
                    x1 = i;
                    y1 = j;
                    ans_1 = dp_data[i][j].sweet_o;
                }
            }
        }
        long long int ans_2 = findsweet(n, m, n - 1, m - 1, dp_data);
        //cout << ans_o << " " << ans_1 << " " << ans_2 << "\n";
        if(ans_1 + ans_2 > ans_o){
            int r1 = move_o(0, x1, 0, y1, dp_data, route);
            int r2 = move(n - 1, m - 1, dp_data, route);
            cout << ans_1 + ans_2 << "\n" << r1 + r2 << "\n";
            //cout << r1 << " " << r2 << endl;
            for(int i = r1 - 1; i >= 0; i--)
                cout << "Move " << route.at(i).first << " " << route.at(i).second << "\n";
            for(int i = r2 + r1 - 1; i >= r1; i--){
                if(i == r2 + r1 - 1)
                    cout << "Jump ";
                else
                    cout << "Move ";
                cout << route.at(i).first << " " << route.at(i).second << "\n";
            }
        }else{
            cout << ans_o << "\n" << n + m - 1 << "\n";
            int ul = move_o(0, n - 1, 0, m - 1, dp_data, route);
            for(int i = route.size() - 1; i >= 0; i--)
                cout << "Move " << route.at(i).first << " " << route.at(i).second << "\n";
        }
    }else{

    }
    
    return 0;
}