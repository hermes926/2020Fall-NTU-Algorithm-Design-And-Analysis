#include <iostream>
#include <cassert>
#include <queue>
#include <vector>
#include <algorithm>

#define MAXN 200010
#define ll long long
using namespace std;

ll n, m, k;
ll ans_arr[MAXN] = {0};

class Seg{
    public:
        ll l, r, q, pos;
        bool operator() (const Seg &lhs, const Seg &rhs) const{
            //cout << lhs.r << " " << rhs.r << endl;
            return (lhs.r < rhs.r);
        }
};

bool sortcmp(Seg a, Seg b){
    if(a.l < b.l)
        return true;
    else
        return false;
}

vector<Seg> segs;

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

bool check(ll num, bool print){
    Memory::reset();
    priority_queue<Seg, vector<Seg>, Seg> seq_que;
    int seg_ptr = 0;
    ll used = 0;
    for(int i = 0; i < m; i++){
        //int v_cnt = Memory::get(i + 1);
        while(segs[seg_ptr].l == i && seg_ptr < n){
            seq_que.push(segs[seg_ptr]);
            seg_ptr++;
        }
        //cout << seg_ptr << endl;
        while(seq_que.size() > 0 && seq_que.top().r >= i + 1){
            Memory::add(seq_que.top().l + 1, seq_que.top().r, seq_que.top().q);
            if(print)
                ans_arr[seq_que.top().pos] += seq_que.top().q;
            used += seq_que.top().q;
            //cout << i << " " << Memory::get(i + 1) << endl;
            if(Memory::get(i + 1) == num){
                seq_que.pop();
                if(used > k)
                    return false;
                break;
            }else if(Memory::get(i + 1) > num){
                ll minus = Memory::get(i + 1) - num;
                Memory::add(seq_que.top().l + 1, seq_que.top().r,  -minus);
                if(print)
                    ans_arr[seq_que.top().pos] -= minus;
                used -= minus;
                Seg tmp = seq_que.top();
                tmp.q = minus;
                seq_que.pop();
                seq_que.push(tmp);
                //cout << used << " u " << Memory::get(i + 1) << endl;
                //seq_que.top().q -= (Memory::get(i + 1) - k);
                if(used > k)
                    return false;
                break;
            }else 
                seq_que.pop();
            if(used > k)
                return false;
            
        }
        if(Memory::get(i + 1) < num)
            return false;
    }
    if(print){
        cout << num << "\n";
        for(int i = 0; i < n; i++)
            cout << ans_arr[i] << " ";
        cout << endl;
    }
    return true;
}


int main(){

    cin >> n >> m >> k;
    for(int i = 0; i < n; i++){
        Seg tmp;
        tmp.pos = i;
        cin >> tmp.l >> tmp.r >> tmp.q;
        segs.push_back(tmp);
    }
    sort(segs.begin(), segs.end(), sortcmp);
    /*for(int i = 0; i < n; i++){
        cout << segs[i].l << " " << segs[i].r << endl;
    }*/

    if(k == n){
        Memory::reset();
        for(int i = 0; i < n; i++)
            Memory::add(segs[i].l + 1, segs[i].r, 1);
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
            if(segs[i].l == 0 && segs[i].r == m && cnt == 0){
                cnt++;
                z_pos = segs[i].pos;
            }else if(segs[i].l == 0 && segs[i].r == m && cnt == 1){
                cout << "2\n";
                for(int j = 0; j < n; j++){
                    if(j == z_pos || j == segs[i].pos)
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
            if(segs[i].l == 0 && segs[i].r > z_right){
                z_pos = segs[i].pos;
                z_right = segs[i].r;
            }else if(segs[i].r == m && segs[i].l < m_left){
                m_pos = segs[i].pos;
                m_left = segs[i].l;
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
    }else{
        ll left = 0, right = k;
        while(right - left > 1){
            ll mid = (left + right) / 2;
            //cout << mid << "hi\n";
            if(check(mid, false))
                left = mid;
            else
                right = mid;
            //cout << mid << endl;
        }
        //cout << left << " " << right << endl;
        /*if(right == mid){
            check(left, true);
        }else{
            
        }*/
        if(check(left, true))
            return 0;


    }


    return 0;
}