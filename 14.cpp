#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <climits>
#include <queue>
#define MAXN 300010
#define ll long long
using namespace std;

typedef struct Edge{
    ll from, to, weight;
};

typedef struct Node{
    ll parent, depth;
};

class Node_val{
    public:
        ll index, dis;
        bool operator()(Node_val a, Node_val b){
            return (a.dis > b.dis);
        } 
};

typedef struct Edge_list{
    ll to, weight;
};

vector<Edge> all_edges;
vector<Edge_list> msts[MAXN];

Node nodes[MAXN];
ll node_val[MAXN] = {0};
bool visit[MAXN] = {0};

bool wei_cmp(Edge a, Edge b){
    return (a.weight < b.weight);
}


ll find_parent(int x){
    if(nodes[x].parent != x)
        nodes[x].parent = find_parent(nodes[x].parent);
    return nodes[x].parent;
}

void make_union(ll x, ll y){
    ll x_root = find_parent(x);
    ll y_root = find_parent(y);
    if(nodes[x_root].depth > nodes[y_root].depth){
        nodes[y_root].parent = x_root;
    }else if(nodes[x_root].depth == nodes[y_root].depth){
        nodes[x_root].depth ++;
        nodes[y_root].parent = x_root;
    }else{
        nodes[x_root].parent = y_root;
    }
    return ; 
}

void find_mst(ll n, ll m){
    ll e = 0, e_index = 0;
    for(int i = 1; i <= n; i++){
        nodes[i].depth = 0;
        nodes[i].parent = i;
    }
    ll te_index = 0;
    while(e < n - 1 && e_index < m){
        //ll te_index = e_index;
        Edge now_edge;
        ll from, to;     
        if(te_index == 0 || e_index - te_index == 1){
            te_index += 1; 
            while(te_index < m - 1 && all_edges[te_index].weight == all_edges[te_index + 1].weight){
                now_edge = all_edges[te_index];
                from = find_parent(now_edge.from);
                to = find_parent(now_edge.to);
                if(from != to){
                    //make_union(from, to);
                    Edge_list tmp1, tmp2;
                    tmp1.to = now_edge.to; 
                    tmp2.to = now_edge.from;
                    tmp1.weight = now_edge.weight;
                    tmp2.weight = now_edge.weight;
                    msts[now_edge.from].push_back(tmp1);
                    msts[now_edge.to].push_back(tmp2);
                }
                te_index++;
            }
            now_edge = all_edges[te_index];
            from = find_parent(now_edge.from);
            to = find_parent(now_edge.to);
            if(from != to){
                //make_union(from, to);
                Edge_list tmp1, tmp2;
                tmp1.to = now_edge.to; 
                tmp2.to = now_edge.from;
                tmp1.weight = now_edge.weight;
                tmp2.weight = now_edge.weight;
                msts[now_edge.from].push_back(tmp1);
                msts[now_edge.to].push_back(tmp2);
            }
        }
        now_edge = all_edges[e_index];
        from = find_parent(now_edge.from);
        to = find_parent(now_edge.to); 
        e_index++;  
        if(from != to){
            make_union(from, to);
            if(e == 0){
                Edge_list tmp1, tmp2;
                tmp1.to = now_edge.to; 
                tmp2.to = now_edge.from;
                tmp1.weight = now_edge.weight;
                tmp2.weight = now_edge.weight;
                msts[now_edge.from].push_back(tmp1);
                msts[now_edge.to].push_back(tmp2);
            }
            e++;
        }
    }
    return ;
}


ll dijkstra(ll n, ll m, ll from, ll to){
    priority_queue<Node_val, vector<Node_val>, Node_val> havent_node;
    //cout << n << "\n";
    for(int i = 1; i <= n; i ++){
        visit[i] = false;
        Node_val tmp;
        tmp.index = i;
        if(i == from){
            node_val[i] = 0;
            tmp.dis = 0;
        }
        else{
            node_val[i] = LLONG_MAX / 10;
            tmp.dis = LLONG_MAX / 10;
        }
        havent_node.push(tmp);
    }

    while(!havent_node.empty()){
        Node_val min = havent_node.top();
        havent_node.pop();
        //cout << min.index << " " << min.dis << "\n";
        if(!visit[min.index] && min.dis <= node_val[min.index]){
            //cout << min.index << " " << min.dis << " " << node_val[min.index] << "\n";
            visit[min.index] = true;
            node_val[min.index] = min.dis;
            for(int i = 0; i < msts[min.index].size(); i++){
                if(min.dis + msts[min.index][i].weight < node_val[msts[min.index][i].to]){
                    node_val[msts[min.index][i].to] = min.dis + msts[min.index][i].weight;
                    Node_val tmp3;
                    tmp3.index = msts[min.index][i].to;
                    tmp3.dis = node_val[msts[min.index][i].to];
                    //cout << min.index << " " << tmp3.dis << " " << tmp3.index << "\n";
                    havent_node.push(tmp3);
                }
            }
        }
    }

    return node_val[to];
}

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    ll n, m, start, end;
    cin >> n >> m >> start >> end;
    for(int i = 0; i < m; i ++){
        Edge tmp;
        cin >> tmp.from >> tmp.to >> tmp.weight;
        all_edges.push_back(tmp);
    }
    sort(all_edges.begin(), all_edges.end(), wei_cmp);
    find_mst(n, m);
    cout << dijkstra(n, m, start, end) << "\n";
    return 0;
}