#include <iostream>
#include <cstring>
#define MAXM 500010
#define MAXN 1000010
#define ll long long 


using namespace std;

unsigned short int mod_l[MAXM] = {0};
unsigned short int mod_r[MAXM] = {0};
unsigned short int mod_rs[MAXM] = {0}, mod_ls[MAXM] = {0};
unsigned short int mod_rl[MAXM] = {0}, mod_ll[MAXM] = {0};
ll sum[MAXN]; 
ll num[MAXN];

void bruteforce(ll sum[], ll num[], ll l, ll r, ll m, ll &ans){
    //cout << "l" << l << " r" << r << endl;
    for(ll i = l + 1; i <= r; i++){
        for(ll j = l; j < i ; j++){
            ll t_max = num[j], t_min = num[j];
            for(ll k = j + 1; k <= i; k++){
                t_max = (num[k] > t_max) ? num[k] : t_max;
                t_min = (num[k] < t_min) ? num[k] : t_min;
            }          
            if((sum[i] - sum[j] + num[j] - t_max - t_min) % m == 0)
                ans++;
        }
    }
    return ;
}


void findans(ll sum[], ll num[], ll n, ll m, ll l, ll r, ll &ans){
    if(r - l < 5)
        bruteforce(sum, num, l, r, m, ans);
    else{
        findans(sum, num, n, m, (l + r) / 2 + 1, r, ans);
        findans(sum, num, n, m, l, ((l + r) / 2), ans);
        //cout << l << " " << r  << "\n";
        memset(mod_l, 0, m * sizeof(unsigned short int));
        memset(mod_r, 0, m * sizeof(unsigned short int));
        memset(mod_ls, 0, m * sizeof(unsigned short int));
        memset(mod_ll, 0, m * sizeof(unsigned short int));
        memset(mod_rs, 0, m * sizeof(unsigned short int));
        memset(mod_rl, 0, m * sizeof(unsigned short int));

        int max = num[(l + r) / 2 + 1], min = num[(l + r) / 2 + 1];
        int x = (l + r) / 2 + 1, y = (l + r) / 2;
        //cout << ans << "\n";
        while(x <= r){
            max = (num[x] > max) ? num[x] : max;
            min = (num[x] < min) ? num[x] : min;
            while(y >= l && num[y] <= max && num[y] >= min){
                mod_l[(sum[(l + r) / 2] - sum[y] + num[y]) % m] += 1;
                y--;
            }
            int inc = (sum[x] - sum[(l + r) / 2 + 1] + num[(l + r) / 2 + 1] - min - max) % m ;
            inc = (inc <= 0) ? inc + m : inc;
            ans += mod_l[m - inc];
            //cout << x << " " << y << " " << num[x] << " " << mod_l[m - inc] << endl;
            x++;
        }
        //cout << ans << "\n";
        max = num[(l + r) / 2], min = num[(l + r) / 2];
        x = (l + r) / 2 + 1, y = (l + r) / 2;
        while(y >= l){
            max = (num[y] > max) ? num[y] : max;
            min = (num[y] < min) ? num[y] : min;
            while(x <= r && num[x] < max && num[x] > min ){
                mod_r[(sum[x] - sum[(l + r) / 2 + 1] + num[(l + r) / 2 + 1]) % m] += 1;
                x++;
            }
            int inc = (sum[(l + r) / 2] - sum[y] + num[y] - min - max) % m ;
            inc = (inc <= 0) ? inc + m : inc;
            ans += mod_r[m - inc];
            //cout << x << " " << y << " " << num[x] << " " << mod_r[m - inc] << endl;
            y--;
        }
        //cout << ans << "\n";
        
        int ymax = num[(l + r) / 2], xmax = num[(l + r) / 2 + 1];
        int mmax = xmax, mmin = xmax;
        min = num[(l + r) / 2];
        x = (l + r) / 2 + 1;
        y = (l + r) / 2;
        bool temp = true;
        int mid = x;
        int l_y = y;
        while(y >= l){
            bool find = true;
            min = (num[y] < min) ? num[y] : min;
            ymax = (num[y] > ymax) ? num[y] : ymax;
            while(xmax < ymax && mid <= r){    
                if(l_y != y && mid != (l + r) / 2 + 1){
                    //cout << "hi ";
                    mod_rs[(sum[mid - 1] - sum[(l + r) / 2 + 1] + num[(l + r) / 2 + 1] - xmax) % m] += 1;
                }
                xmax = (num[mid] > xmax) ? num[mid] : xmax;
                if(ymax >= xmax)
                    mod_rs[(sum[mid] - sum[(l + r) / 2 + 1] + num[(l + r) / 2 + 1] - xmax) % m] += 1;
                mid++;  
                l_y = y;      
            }
            
            while((x <= r && num[x] > min) || x < mid){
                mmax = (num[x] > mmax) ? num[x] : mmax;
                mmin = (num[x] < mmin) ? num[x] : mmin;
                mod_rl[(sum[x] - sum[(l + r) / 2 + 1] + num[(l + r) / 2 + 1] - mmax) % m] += 1;
                x++;
            }
            if(mmin < min || (ymax > xmax && mid == r + 1))
                find = false;
            //cout << y << " " << mid << " " << x << " ";
            int inc = m;
            if(find){
                //cout << "hi ";
                inc = (sum[(l + r) / 2] - sum[y] + num[y] - min) % m ;
                inc = (inc <= 0) ? inc + m : inc; 
                ans += (mod_rl[m - inc] - mod_rs[m - inc]);
            }
            //ans += mod_r[m - inc];
            //cout << inc << " " << mod_rl[m - inc] << " " << mod_rs[m - inc] << endl;
            y--;
        }
        //cout << ans << "\n";
        

        int ymin = num[(l + r) / 2], xmin = num[(l + r) / 2 + 1];
        mmin = num[(l + r) / 2 + 1], mmax = mmin;
        max = num[(l + r) / 2];
        x = (l + r) / 2 + 1;
        y = (l + r) / 2;
        mid = x;
        l_y = y;
        
        while(y >= l){
            bool find = true;
            ymin = (num[y] < ymin) ? num[y] : ymin;
            max = (num[y] > max) ? num[y] : max;
            while(xmin >= ymin && mid <= r){
                if(l_y != y && mid != (l + r) / 2 + 1){
                    mod_ls[(sum[mid - 1] - sum[(l + r) / 2 + 1] + num[(l + r) / 2 + 1] - xmin) % m] += 1;
                    //cout << "hh ";
                }
                xmin = (num[mid] <= xmin) ? num[mid] : xmin;
                if(xmin >= ymin)
                    mod_ls[(sum[mid] - sum[(l + r) / 2 + 1] + num[(l + r) / 2 + 1] - xmin) % m] += 1;
                mid++;
                l_y = y;
            }
            
            while((x <= r && num[x] <= max) || x < mid ){
                mmin = (num[x] < mmin) ? num[x] : mmin;
                mmax = (num[x] > mmax) ? num[x] : mmax;
                mod_ll[(sum[x] - sum[(l + r) / 2 + 1] + num[(l + r) / 2 + 1] - mmin) % m] += 1;
                x++; 
            }
            if(mmax > max || (ymin <= xmin && mid == r + 1))
                find = false;
            //cout << y << " " << mid << " " << x << " ";
            int inc = m;
            if(find){
                //cout << "hi ";
                inc = (sum[(l + r) / 2] - sum[y] + num[y] - max) % m ;
                inc = (inc <= 0) ? inc + m : inc; 
                ans += (mod_ll[m - inc] - mod_ls[m - inc]);
            }
            //ans += mod_r[m - inc];
           //cout << inc << " " << mod_ll[m - inc] << " " << mod_ls[m - inc] << endl;

            y--;
        }
        
        //ans--;
        //cout << ans << endl;
    }
    return ;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll m, n;
    ll now_sum = 0;
    cin >> n >> m;

    for(ll i = 0; i < n; i ++){
        cin >> num[i];
        sum[i] = now_sum + num[i];
        now_sum += num[i];
    }
    ll ans = 0;
    if(m == 1)
        cout << (n - 1) * n / 2 << endl;
    else{
        findans(sum, num, n, m, 0, n - 1, ans);
        cout << ans << endl;
    }
    return 0;
}