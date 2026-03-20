#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

tuple<bool, int, int> exploreComponent(const vector<vector<int>>& adj, int startNode, vector<int>& colors) {
    queue<int> q;
    q.push(startNode);
    colors[startNode] = 0; // 0 and 1 are colors, -1 means unvisited

    bool hasOddCycle = false;
    int size0 = 0; // Tracks nodes colored 0
    int size1 = 0; // Tracks nodes colored 1

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // Increment the respective partition size based on the node's color
        if (colors[u] == 0) {
            size0++;
        } else {
            size1++;
        }

        for (int neighbor : adj[u]) {
            if (colors[neighbor] == -1) {
                // Unvisited: color with the opposite color and add to queue
                colors[neighbor] = 1 - colors[u];
                q.push(neighbor);
            } else if (colors[neighbor] == colors[u]) {
                // Visited and same color: an odd-length cycle exists!
                hasOddCycle = true;
            }
        }
    }

    return {hasOddCycle, size0, size1};
}

/**
 * Wrapper function to process an entire graph that might be disconnected.
 */
int checkEntireGraph(const vector<vector<int>>& adj) {
    int numVertices = adj.size();

    // Let's assume 'ans' is a flag checking if the whole graph is free of odd cycles.
    // 1 means no odd cycles (bipartite), 0 means it contains at least one odd cycle.
    int ans = 0;

    // Global colors array initialized to -1 (unvisited)
    vector<int> colors(numVertices, -1);

    // Loop through every node to ensure we hit all disconnected components
    for (int i = 0; i < numVertices; ++i) {
        if (colors[i] == -1) {
            // Found an unvisited component, let's explore it
            auto [hasOddCycle, size0, size1] = exploreComponent(adj, i, colors);
//            cout<<result.first<<" "<<result.second<<" result for "<<i<<"\n";
            // result.first is true if an odd cycle EXISTS.
            if(!hasOddCycle){
                ans += max(size0, size1); // The graph contains an odd cycle, update ans.
                // Depending on your problem, you might want to `break;` or `return 0;` here to save time.
            }

            // You also have access to the component size here if your problem needs it!
            // int sizeOfThisComponent = result.second;
        }
    }
    return ans;
}

int main(){
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("./input.txt", "r", stdin);
    freopen("./output.txt", "w", stdout);
#endif

    int t;
    if (cin >> t) { // Good practice to check if 't' was actually read
        while (t--){
            int n, m;
            cin >> n >> m;

            vector<vector<int>> adj(n);

            for(int i = 0; i < m; i++){
                int u, v;
                cin >> u >> v;
                u--; // 1-based to 0-based
                v--;

                adj[u].push_back(v);
                adj[v].push_back(u);
            }

            cout << checkEntireGraph(adj) << "\n";
        }
    }
    return 0;
}