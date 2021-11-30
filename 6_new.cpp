#include <iostream>
#include <cstring>
#define MAXM 500010
#define MAXN 1000010
#define ll long long 


using namespace std;

ll p[MAXN]; 
ll num[MAXN];
ll maxr[MAXN], minr[MAXN], maxl[MAXN], minl[MAXN];
ll ans = 0;
int cnt[MAXM] = {0};

void bruteforce(int l, int r, int m){
    //cout << "l" << l << " r" << r << endl;
    for(int i = l + 1; i <= r; i++){
        for(int j = l; j < i; j++){
            ll t_max = num[j], t_min = num[j];
            for(int k = j + 1; k <= i; k++){
                t_max = (num[k] > t_max) ? num[k] : t_max;
                t_min = (num[k] < t_min) ? num[k] : t_min;
            }          
            if((p[i] - p[j] + num[j] - t_max - t_min) % m == 0)
                ans++;
        }
    }
    return ;
}


void findans(int N, int M, int L, int R){
    if(R - L < 50)
        bruteforce(L, R, M);
    else{
        findans(N, M, (L + R) / 2 + 1, R);
        findans(N, M, L, ((L + R) / 2));
        //cout << L << " " << R  << "\n";

        int mid = (L + R) / 2;
        maxl[mid] = minl[mid] = num[mid];
        for (int i = mid - 1; i >= L; --i) {
            maxl[i] = max(maxl[i + 1], num[i]);
            minl[i] = min(minl[i + 1], num[i]);
        }
        maxr[mid + 1] = minr[mid + 1] = num[mid + 1];
        for (int i = mid + 2; i <= R; ++i) {
            maxr[i] = max(maxr[i - 1], num[i]);
            minr[i] = min(minr[i - 1], num[i]);
        }


        //cout << ans << endl;
        int ptrl = mid, ptrr = mid;
        for (int i = mid; i >= L; --i) {
            while (ptrl + 1 <= R && minl[i] <= minr[ptrl + 1] && maxr[ptrl + 1] <= maxl[i]) {
                cnt[ p[ptrl + 1] % M ]++;
                ++ptrl;
            }
            if(i == 0)
                ans += cnt[ (minl[i] + maxl[i]) % M ];
            else
                ans += cnt[ (p[i - 1] + minl[i] + maxl[i]) % M ];
        }
        ptrl = mid;
        for (int i = mid; i >= L; --i) {
            while (ptrl + 1 <= R && minl[i] <= minr[ptrl + 1] && maxr[ptrl + 1] <= maxl[i]) {
                cnt[ p[ptrl + 1] % M ]--;
                ++ptrl;
            }
        }
        //cout << ans << endl;

        //memset(cnt, 0, M * sizeof(unsigned short));

        ptrl = mid + 1;
        for (int i = mid + 1; i <= R; ++i) {
            while (ptrl - 1 >= L && minr[i] < minl[ptrl - 1] && maxl[ptrl - 1] < maxr[i]) {
                if(ptrl - 1 == 0)
                    cnt[0] ++;
                else
                    cnt[ p[ptrl - 2] % M ]++;
                --ptrl;
            }
            ans += cnt[ (((p[i] - minr[i] - maxr[i]) % M) + M) % M ];
        }
        ptrl = mid + 1;

        for (int i = mid + 1; i <= R; ++i) {
            while (ptrl - 1 >= L && minr[i] < minl[ptrl - 1] && maxl[ptrl - 1] < maxr[i]) {
                if(ptrl - 1 == 0)
                    cnt[0] --;
                else
                    cnt[ p[ptrl - 2] % M ]--;
                --ptrl;
            }
        }

        //cout << ans << endl;
        int mn_ptr = mid, mx_ptr = mid + 1;
        for (int i = mid; i >= L; --i) {
            while (mx_ptr != R + 1 && maxl[i] >= maxr[mx_ptr]) {
                if (mx_ptr <= mn_ptr) {
                    --cnt[(p[mx_ptr] - maxr[mx_ptr]) % M];
                }
                ++mx_ptr;
            }
            while (mn_ptr != R && minr[mn_ptr + 1] >= minl[i]) {
                ++mn_ptr;
                if (mx_ptr <= mn_ptr) {
                    ++cnt[(p[mn_ptr] - maxr[mn_ptr]) % M];
                }
            }
            if(i > 0)
                ans += cnt[(p[i - 1] + minl[i]) % M];
            else
                ans += cnt[ minl[i] % M];
        }

        for(int i = mx_ptr; i <= mn_ptr; i++)
            --cnt[(p[i] - maxr[i]) % M];
        
        memset(cnt, 0, M * sizeof(unsigned short));
        //cout << ans << endl;
        mn_ptr = mid, mx_ptr = mid + 1;
        for (int i = mid; i >= L; --i) {
            while (mx_ptr != R + 1 && minl[i] <= minr[mx_ptr]) {
                if (mx_ptr <= mn_ptr) {
                    --cnt[(p[mx_ptr] - minr[mx_ptr]) % M];
                }
                ++mx_ptr;
            }
            while (mn_ptr != R && maxr[mn_ptr + 1] <= maxl[i]) {
                ++mn_ptr;
                if (mx_ptr <= mn_ptr) {
                    ++cnt[(p[mn_ptr] - minr[mn_ptr]) % M];
                }
            }
            if(i > 0)
                ans += cnt[(p[i - 1] + maxl[i]) % M];
            else
                ans += cnt[ maxl[i] % M];
        }
        for(int i = mx_ptr; i <= mn_ptr; i++)
            --cnt[(p[i] - minr[i]) % M];
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
        p[i] = now_sum + num[i];
        now_sum += num[i];
    }
    if(m == 1)
        cout << (n - 1) * n / 2 << endl;
    else{
        findans(n, m, 0, n - 1);
        cout << ans << endl;
    }
    return 0;
}