#include <iostream>
#include <cassert>

#define MAXN 200010
#define ll long long

using namespace std;

ll segs[MAXN][3];

namespace Memory {
    constexpr int N = 200010; // Number of cells, change this if you need more cells

    long long arr[N + 1]; // Note: This is NOT the memory itself, please don't try to access
                          //       this array directly unless you know what you're doing

    /* Start of internal functions */
    void _ins(int x, int k) {
        while (x <= N) arr[x] += k, x += x & -x;
    }

    long long _qr(int x) {
        long long ret = 0;
        while (x) ret += arr[x], x -= x & -x;
        return ret;
    }
    /* End of internal functions */

    // Explicitly fill the whole memory with zero
    // Complexity: O(N)
    void reset() {
        for (int i = N; i >= 0; --i)
            arr[i] = 0;
    }
    
    // Add k to every cell in range [l, r]
    // Complexity: O(log(N))
    void add(int l, int r, int k) {
        assert(1 <= l && l <= r && r <= N && "add: the argument should satisfy 1 <= l <= r <= N");
        _ins(l, k);
        _ins(r + 1, -k);
    }

    // Get the value in cell x
    // Complexity: O(log(N))
    long long get(int x) {
        assert(1 <= x && x <= N && "get: x should be a positive integer in range [1, N]");
        return _qr(x);
    }
}



int main(){
    int n, m, k;
    cin >> n >> m >> k;
    for(int i = 0; i < n; i++)
        cin >> segs[i][0] >> segs[i][1] >> segs[i][2];
    if(k == n){
        Memory::reset();
        for(int i = 0; i < n; i++)
            Memory::add(segs[i][0] + 1, segs[i][1], 1);
        int max = n + 1;
        for(int i = 1; i <= m; i++){
            if(Memory::get(i) < max)
                max = Memory::get(i);
        }
        cout << max << "\n";
        for(int i = 0; i < n; i++)
            cout << "1 ";
        cout << "\n";
    }
    else if(k == 2){
        int z_pos = -1, z_right = 0, m_pos = -1, m_left = m, cnt = 0; 
        for(int i = 0; i < n; i++){
            if(segs[i][0] == 0 && segs[i][1] == m && cnt == 0){
                cnt++;
                z_pos = i;
            }else if(segs[i][0] == 0 && segs[i][1] == m && cnt == 1){
                cout << "2\n";
                for(int j = 0; j < n; j++){
                    if(j == z_pos || j == i)
                        cout << "1 ";
                    else
                        cout << "0 ";   
                }
                cout << "\n";
                return 0;
            }
        }
        if(cnt == 1){
            cout << "1\n";          
            for(int j = 0; j < n; j++){
                if(j == z_pos)
                    cout << "1 ";
                else
                    cout << "0 ";   
            }
            cout << "\n";
            return 0;
        }

        for(int i = 0; i < n; i++){
            if(segs[i][0] == 0 && segs[i][1] > z_right){
                z_pos = i;
                z_right = segs[i][1];
            }else if(segs[i][1] == m && segs[i][0] < m_left){
                m_pos = i;
                m_left = segs[i][0];
            }
        }
        if(m_left - z_right < 1){
            cout << "1\n";
            for(int i = 0; i < n; i ++){
                if(i == m_pos || i == z_pos)
                    cout << "1 ";
                else
                    cout << "0 ";
            }
            cout << "\n";
        }else{
            cout << "0\n";
            for(int i = 0; i < n; i ++)
                cout << "0 ";
            cout << "\n";
        }
    }


    return 0;
}