#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "helper.h"
#define ll long long int

using namespace std;

typedef struct inc{
    bool type, l_r;
    int time, r, l, level, damage;
};

void merge(vector<inc> &all_inc, map<int, ll> &ans, int l, int m, int r){
    int t1 = m - l + 1, t2 = r - m; 
    vector<inc> left(all_inc.begin() + l, all_inc.begin() + m + 1);
    vector<inc> right(all_inc.begin() + m + 1, all_inc.begin() + r + 1);  
    int l_c = 0, r_c = 0;  
    int count = l;       
    while (l_c < t1 && r_c < t2){ 
        if (left[l_c].level <= right[r_c].level){ 
            all_inc[count] = left[l_c];
            all_inc[count].l_r = true; 
            l_c++; 
        } 
        else{ 
            all_inc[count] = right[r_c];
            all_inc[count].l_r = false; 
            r_c++; 
        } 
        count++; 
    } 
    while (l_c < t1){ 
        all_inc[count] = left[l_c]; 
        all_inc[count].l_r = true; 
        l_c++; 
        count++; 
    }
    while (r_c < t2){ 
        all_inc[count] = right[r_c];
        all_inc[count].l_r = false;  
        r_c++; 
        count++; 
    }
    for(int i = r; i >= l; i--){
        if(all_inc[i].type && (!all_inc[i].l_r))
            Memory::add(all_inc[i].l, all_inc[i].r, all_inc[i].damage);
        else if((!all_inc[i].type) && all_inc[i].l_r)
            ans[all_inc[i].time] += (Memory::get(all_inc[i].l));
    } 
    for(int i = r; i >= l; i--){
        if(all_inc[i].type && (!all_inc[i].l_r))
            Memory::add(all_inc[i].l, all_inc[i].r, -all_inc[i].damage);
    }
    //Memory::reset();
}

void merge_sort(vector<inc> &all_inc, map<int, ll> &ans, int l, int r){
    if(l < r){
        int m = (l + r) / 2; 
        merge_sort(all_inc, ans, l, m); 
        merge_sort(all_inc, ans, m + 1, r); 
        merge(all_inc, ans, l, m, r); 
    }
    return ;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    vector<inc> all_inc;
    map<int, ll> ans;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        char c;
        inc temp;
        temp.time = i;
        cin >> c;
        if(c == 'A'){
            temp.type = true;
            cin >> temp.l >> temp.r >> temp.level >> temp.damage;
        }else{
            temp.type = false;
            cin >> temp.l >> temp.level;
            ans[i] = 0;
        }
        all_inc.push_back(temp);
    }
    merge_sort(all_inc, ans, 0, m - 1);
    for(auto i : ans)
        cout << i.second << "\n";
    return 0;
}