#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#define ll long long
#define MAXN 500010

using namespace std;

typedef struct Edge{
    ll to, weight;
};

vector<ll> node_val;
ll new_node_val[MAXN] = {0};
ll node_dp[MAXN] = {0};
bool visit[MAXN] = {0};
vector<Edge> edges[MAXN];
vector<Edge> tran_edges[MAXN];
vector<Edge> new_edges[MAXN];
ll new_n = 0;
unordered_map<ll, ll> node_to_new; 


void dfs(ll n){
    visit[n] = true; 
    node_dp[n] += new_node_val[n];
    for(int i = 0; i < new_edges[n].size(); i++){ 
        if(!visit[new_edges[n][i].to]) 
            dfs(new_edges[n][i].to); 
        node_dp[n] = max(node_dp[n], new_node_val[n] + new_edges[n][i].weight + node_dp[new_edges[n][i].to]); 
    } 
}

void find_max_treasure(ll n, ll &ans){
    for(int i = 0; i < n; i++) 
        visit[i] = false;  
	for(int i = 0; i < n; i++){ 
        if(!visit[i]) 
            dfs(i); 
    }   
    for(int i = 0; i < n; i++)
		ans = max(ans, node_dp[i]);
    return ; 
}


void deal_cyc(ll n, vector<ll> &scc){ 
	visit[n] = true; 
	scc.push_back(n); 
	for(int i = 0; i < tran_edges[n].size(); ++i) 
		if (!visit[tran_edges[n][i].to]) 
			deal_cyc(tran_edges[n][i].to, scc); 
} 

void getTranspose(ll n){ 
	for(int v = 1; v <= n; v++){ 
		for(int i = 0; i < edges[v].size(); i++){ 
			tran_edges[edges[v][i].to].push_back(edges[v][i]);
			tran_edges[edges[v][i].to][tran_edges[edges[v][i].to].size() - 1].to = v;
		} 
	} 
	return ; 
} 

void fillOrder(int v, stack<ll> &Stack){
	visit[v] = true;  
	for(int i = 0; i < edges[v].size(); ++i) {
		if(!visit[edges[v][i].to]) 
			fillOrder(edges[v][i].to, Stack);
    } 
	Stack.push(v); 
} 

void del_SCCs(ll n){ 
	stack<ll> Stack; 
	for(int i = 1; i <= n; i++) 
		visit[i] = false; 
	for(int i = 1; i <= n; i++) 
		if(visit[i] == false) 
			fillOrder(i, Stack); 
	getTranspose(n); 
	for(int i = 1; i <= n; i++) 
		visit[i] = false; 

	vector<vector<ll>> sccs;
	while(!Stack.empty()){ 
		ll v = Stack.top(); 
		Stack.pop(); 
		if(visit[v] == false){ 
			vector<ll> tmp;
			deal_cyc(v, tmp); 
			sccs.push_back(tmp);
			//cout << endl; 
		} 
	}
	for(int i = 0; i < sccs.size(); i++){
		for(int j = 0; j < sccs[i].size(); j++){
			node_to_new[sccs[i][j]] = i;
			//cout << sccs[i][j] << " ";
		}
		//cout << "\n";
	}
	new_n = sccs.size(); 
	for(int i = 1; i <= n; i++){
		ll from = node_to_new[i];
		//cout << from << " " << node_val[i - 1] << " hi\n";
		new_node_val[from] += node_val[i - 1];
		for(int j = 0; j < edges[i].size(); j++){
			ll to = node_to_new[edges[i][j].to];
			if(from == to){
				new_node_val[from] += edges[i][j].weight;
			}else{
				Edge tmp;
				tmp.to = to;
				tmp.weight = edges[i][j].weight;
				new_edges[from].push_back(tmp);
			}
		}
	}
} 

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll n, m, t;
    cin >> n >> m;
    for(int i = 1; i <= n ; i++){
        cin >> t;
        node_val.push_back(t);
    }
    for(int i = 1; i <= m ; i++){    
        int from; 
        Edge tmp;
        cin >> from >> tmp.to >> tmp.weight;
        edges[from].push_back(tmp);
    }
    del_SCCs(n);
    ll ans = 0;
    find_max_treasure(new_n, ans);
    cout << ans << "\n";
    return 0;
}