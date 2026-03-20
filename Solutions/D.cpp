#include <bits/stdc++.h>

using namespace std;

vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
{

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    vector<int> distTo(V, INT_MAX);

    // Source initialised with dist=0.
    distTo[S] = 0;
    pq.push({0, S});

    while (!pq.empty())
    {
        int node = pq.top().second;
        int dis = pq.top().first;
        pq.pop();

        for (auto it : adj[node])
        {
            int v = it[0];
            int w = it[1];
            if (dis ^ w < distTo[v])
            {
                distTo[v] = dis ^ w;
                pq.push({dis ^ w, v});
            }
        }
    }

    return distTo;
}

int main(){
    int n, m;
    cin>>n>>m;

    vector<vector<pair<int, int> > > adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    auto ans = dijkstra(n + 1, adj, 1);

    cout<<ans[n];
}