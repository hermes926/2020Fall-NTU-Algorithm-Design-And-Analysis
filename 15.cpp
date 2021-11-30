#include <iostream>
#include <map>
#include <vector>
#include <deque>
#include <string>
#define MAXN 200010
#define ll long long

typedef struct Group{
    ll type, people, time;
};

using namespace std;

deque <Group> people;
ll ans[MAXN] = {0};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll n, q;
    cin >> n >> q;
    for(ll i = 0; i < q; i++){
        string op;
        ll p;
        Group tmp3;
        cin >> op >> tmp3.people >> tmp3.type >> p;
        ll left = p;
        tmp3.people += p;
        tmp3.time = i;
        if(op[0] == 'f'){
            while(left > 0){
                Group tmp = people.front();
                people.pop_front();
                //cout << tmp.type << " " << tmp.time << " " << tmp.people << endl;
                if(left >= tmp.people){
                    ans[tmp.type] += ((i - tmp.time) * tmp.people);
                    left -= tmp.people;
                }else{
                    ans[tmp.type] += ((i - tmp.time) * tmp.people);
                    Group tmp2;
                    tmp2.time = i;
                    tmp2.type = tmp.type;
                    tmp2.people = tmp.people - left;
                    people.push_front(tmp2);
                    left = 0;
                    break;
                }
            }
            people.push_front(tmp3);
        }else{
            while(left > 0){
                Group tmp = people.back();
                people.pop_back();
                //cout << tmp.type << " " << tmp.time << " " << tmp.people << endl;
                if(left >= tmp.people){
                    ans[tmp.type] += ((i - tmp.time) * tmp.people);
                    left -= tmp.people;
                }else{
                    ans[tmp.type] += ((i - tmp.time) * tmp.people);
                    Group tmp2;
                    tmp2.time = i;
                    tmp2.type = tmp.type;
                    tmp2.people = tmp.people - left;
                    people.push_back(tmp2);
                    left = 0;
                    break;
                }
            }
            people.push_back(tmp3);
        }
    }
    /*for(int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";*/

    while(!people.empty()){
        Group tmp = people.back();
        ans[tmp.type] += ((q - tmp.time) * tmp.people);
        people.pop_back();
    }

    for(int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
    cout << "\n";


    return 0;
}