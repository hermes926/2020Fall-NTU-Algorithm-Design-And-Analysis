#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define MAXN 500010
#define ll long long
using namespace std;

class Edge{
    public:
        ll to, weight;
        Edge(ll to, ll weight){
            this->to = to;
            this->weight = weight;
        }
};

ll ans[MAXN] = {0};
ll dis[MAXN] = {0};
ll dis_dfs[MAXN] = {0};
vector<Edge> edges[MAXN];
vector<ll> l;
bool visit[MAXN] = {0};

ll bfs(ll n, ll u){
	queue<ll> q;
	q.push(u);
	dis[u] = 0;
	while (!q.empty()){
		ll t = q.front();
        q.pop();        
        for (int i = 0; i < edges[t].size(); i++){
            if(!visit[edges[t][i].to]){
                q.push(edges[t][i].to);
                dis[edges[t][i].to] = dis[t] + edges[t][i].weight;
                visit[edges[t][i].to] = true;
            }
        }
        visit[t] = true;
	}
	ll max_index = 0, max_dis = 0;
	for (int i = 1; i <= n; i++){
		//cout << dis[i] << " ";
        if (dis[i] > max_dis){
			max_dis = dis[i];
			max_index = i;
		}
	}
    //cout << "\n";
	return max_index;
}

ll dfs_re(ll now, ll prev_length, ll prev){
    ll max = 0, tmax = 0;
    if(edges[now].size() == 1)
        return prev_length;
    for(int i = 0; i < edges[now].size(); i++){
        if(edges[now][i].to == prev)
            continue;
        tmax = dfs_re(edges[now][i].to, edges[now][i].weight, now);
        if(i == 0){
            max = tmax;
        }else if(max < tmax){
            l.push_back(max);
            max = tmax;                
        }else{
            l.push_back(tmax);
        }
    }
    return (prev_length + max);
}

bool cmp(ll a, ll b){
    return (a > b);
}

ll dfs(ll n, ll start){ 
    ll max = 0, tmax = 0;
    for(int i = 0; i < edges[start].size(); i++){
        tmax = dfs_re(edges[start][i].to, edges[start][i].weight, start);
        if(i == 0){
            max = tmax;
        }else if(max < tmax){
            l.push_back(max);
            max = tmax;                
        }else{
            l.push_back(tmax);
        }
    }
    sort(l.begin(), l.end(), cmp);
    return max;
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll n;
    cin >> n;
    for(int i = 0; i < n - 1; i++){
        ll from, to, weight;
        cin >> from >> to >> weight;
        Edge tmp1(from, weight);
        Edge tmp2(to, weight);
        edges[from].push_back(tmp2);
        edges[to].push_back(tmp1);
    }
    ll far = bfs(n, 1);
    ll mmax = dfs(n, far);
    
    int cnt = 1, lcnt = 0;
    while(cnt <= n){
        if(cnt == 1)
            cout << "0 ";
        else if(cnt == 2 || lcnt >= l.size())
            cout << mmax << " ";
        else{
            mmax += l[lcnt];
            cout << mmax << " ";
            lcnt++;
        }
        cnt++;
    }
    cout << "\n";
    return 0;
}