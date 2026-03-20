#include "bits/stdc++.h"

using namespace std;

void dfs(int u, vector<vector<int > > &graph, int p){

    for(auto v : graph[u]){
        if(v == p){
            continue;
        }
        dfs(v, graph, u);
    }

}

void bfs(int u, vector<vector<int> > &graph){

    int n = graph.size();
    queue<int> q;
    vector<bool> vis(n + 1, false);

    vis[u] = true;
    q.push(u);

    while(!q.empty()){

        int v = q.front();
        q.pop();

        vis[v] = true;

        for(auto c : graph[v]){
            if(vis[c]) continue;
            q.push(c);
        }
    }

}

int main(){
    int n;
    cin>>n;

    vector<vector<int> > graph(n);

    for(int i = 0; i < n; i++){
        int u, v;
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }


}