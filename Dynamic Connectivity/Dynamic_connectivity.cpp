#include <iostream>
#include <bits/stdc++.h>

using namespace std;

pair<int, int> eed;
vector<vector<int> > op_parent, op_size;
vector<int> query(300100, -1);

struct q{
    int u, v;
    bool con = false;
};

vector<vector<q> > tree(4001000);
vector<pair<int, int> > ans;

vector<int> parent, rank_;

int comp = 0;

void make_set(int u){
    parent[u] = u;
}

int find_set(int u){
    if(u == parent[u])return u;
    return find_set(parent[u]);
}

bool combine(int u, int v){
    
    u = find_set(u);
    v = find_set(v);
    
    if(u == v){
        return false;  
    }
    
    if(rank_[u] < rank_[v])swap(u, v);
    
    op_parent.push_back({v, parent[v]});
    op_size.push_back({u, rank_[u]});
    
    parent[v] = u;
    
    if(rank_[u] == rank_[v])rank_[u]++;
    comp--;
    return true;
}

void rollback(){
    parent[op_parent.back()[0]] = op_parent.back()[1];
    rank_[op_size.back()[0]] = op_size.back()[1];
    op_parent.pop_back();
    op_size.pop_back();
    comp++;
}

bool united(int a, int b){
    a = find_set(a);
    b = find_set(b);
    
    if(a == b) return true;
    return false;
}

void update(int node, int l, int r, int ql, int qr){
    
    if(ql > r || qr < l)return;
    
    if(ql <= l && r <= qr){
        // cout<<node<<" inserted here \n";
        tree[node].push_back({eed.first, eed.second, false});
        return;
    }
    
    int mid = (l + r)/2;
    
    update(node<<1, l, mid, ql, qr);
    update(node<<1|1, mid + 1, r, ql, qr);
}

void dfs(int node, int l, int r){
    
    // cout<<tree[node].size()<<" sz \n";
    // int prev = curuf.cur;
    for(auto &v : tree[node]){
            v.con = combine(v.u, v.v);
            // cout<<comp<<" after combining ";
    }
    
    if(l == r){
        if(query[l] != -1)
            ans.push_back({query[l], comp});
    }
    else{
        int mid = (l + r)/2;
    
        dfs(node<<1, l, mid);
        dfs(node<<1|1, mid + 1, r);   
    }
    for (auto v : tree[node]) {
            if(v.con){
                rollback();
                // cout<<comp<<" after rolling back ";
            }
    }
} 

map<pair<int, int>, int> edge;

int main() {
	
    #define NAME "connect"
    assert(freopen(NAME ".in", "r", stdin));
    assert(freopen(NAME ".out", "w", stdout));

	int n, k;
	cin>>n>>k;
	
	comp = n;
	
	parent.resize(n + 1);
	rank_.resize(n + 1);
	
	for(int i = 1; i <= n; i++){
	    parent[i] = i;
	}
	
// 	query.resize(k + 1);
	
// 	query.assign(k + 1, -1);
	
	for(int i = 0; i < k; i++){
	    
	    char c;
	    int u, v;
	    
	    cin>>c;
	    
	    if(c == '+'){
	        cin>>u>>v;
	        if(u > v)swap(u, v);
	        edge[{u, v}] = i;
	    }
	    else if(c == '-'){
	        cin>>u>>v;
	        if(u > v)swap(u, v);
	        eed = pair<int, int> (u, v);
	        int added = edge[eed];
	       // cout<<added<<" added "<<u<<" "<<v<<" nodes \n";
	        update(1, 0, k, added, i);
	        if(edge.find(eed) != edge.end())edge.erase(eed);
	    }
	    else{
	        query[i] = i;
	    }
	}
	
	for(auto v : edge){
	    eed = v.first;
	    update(1,0, k, v.second, k);
	}
	
	dfs(1, 0, k);
	sort(ans.begin(), ans.end());
	
	for(auto v : ans){
	    cout<<v.second<<"\n";
	}
	
	return 0;
}