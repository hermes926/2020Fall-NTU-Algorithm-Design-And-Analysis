#include <iostream>
using namespace std;

typedef struct pos{
    int lmax, lmin, rmax, rmin;
};

void right(long long int sum[], int num[], pos data[], int n, int m, int l, int r, int &ans);

void bruteforce(long long int sum[], int num[], int l, int r, int m, int &ans){
    //cout << "l" << l << " r" << r << endl;
    for(int i = l + 2; i <= r; i++){
        for(int j = l; j < i - 1; j++){
            int t_max = num[j], t_min = num[j];
            for(int k = j + 1; k <= i; k++){
                t_max = (num[k] > t_max) ? num[k] : t_max;
                t_min = (num[k] < t_min) ? num[k] : t_min;
            }
            //cout << j <<" "<< i << " " <<(sum[i] - sum[j] + num[j] - t_max - t_min) << endl;
            
            if((sum[i] - sum[j] + num[j] - t_max - t_min) % m == 0){
                ans++;
                //cout << i << " " << j << endl;
            }
        }
    }
    return ;
}

void left(long long int sum[], int num[], pos data[], int n, int m, int l, int r, int &ans){
    //brute force
    if(r - l < 5)
        bruteforce(sum, num, l, r, m, ans); 
    else{
    //recursive
        
        right(sum, num, data, n, m, (l + r) / 2 + 1, r, ans);
        left(sum, num, data, n, m, l, ((l + r) / 2), ans);
        cout << l << " " << r << " ";
        for(int i = l; i <= ((l + r) / 2); i++){
            for(int j = r; j >= (l + r) / 2 + 1; j--){
                if(i == j - 1)
                    continue;
                long long int t_sum = sum[j] - sum[i] + num[i];
                t_sum -= (data[i].rmax > data[j].lmax) ? data[i].rmax : data[j].lmax;
                t_sum -= (data[i].rmin < data[j].lmin) ? data[i].rmin : data[j].lmin;
                ans += (t_sum % m == 0) ? 1 : 0;
                //if(t_sum % m == 0)
                //    cout << i << " " << j << endl;
            }
        }
        cout << ans << endl;
    }
    
    for(int i = r; i >= l; i--){
        if(i == r){
            data[i].rmax = num[i];
            data[i].rmin = num[i];
        }else{
            data[i].rmax = (data[i + 1].rmax > num[i]) ? data[i + 1].rmax : num[i];
            data[i].rmin = (data[i + 1].rmin < num[i]) ? data[i + 1].rmin : num[i];
        }
    }
    return ;
}

void right(long long int sum[], int num[], pos data[], int n, int m, int l, int r, int &ans){
    if(r - l < 5)
        bruteforce(sum, num, l, r, m, ans);
    else{
        right(sum, num, data, n, m, (l + r) / 2 + 1, r, ans);
        left(sum, num, data, n, m, l, ((l + r) / 2), ans);
        cout << l << " " << r << " ";
        for(int i = l; i <= ((l + r) / 2); i++){
            for(int j = r; j >= (l + r) / 2 + 1; j--){
                if(i == j - 1)
                    continue;
                long long int t_sum = sum[j] - sum[i] + num[i];
                t_sum -= (data[i].rmax > data[j].lmax) ? data[i].rmax : data[j].lmax;
                t_sum -= (data[i].rmin < data[j].lmin) ? data[i].rmin : data[j].lmin;
                ans += (t_sum % m == 0) ? 1 : 0;
               // if(t_sum % m == 0)
                //    cout << i << " " << j << endl;
            }
        }
        cout << ans << "\n";
    }
    for(int i = l; i <= r; i++){
        if(i == l){
            data[i].lmax = num[i];
            data[i].lmin = num[i];
        }else{
            data[i].lmax = (data[i - 1].lmax > num[i]) ? data[i - 1].lmax : num[i];
            data[i].lmin = (data[i - 1].lmin < num[i]) ? data[i - 1].lmin : num[i];
        }
    }
    return ;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int m, n;
    long long int now_sum = 0;
    cin >> n >> m;
    long long int sum[n]; 
    int num[n];
    pos data[n];
    for(int i = 0; i < n; i ++){
        cin >> num[i];
        sum[i] = now_sum + num[i];
        now_sum += num[i];
    }

    int ans = n - 1;
    left(sum, num, data, n, m, 0, n - 1, ans);
    cout << ans << endl;





    return 0;
}