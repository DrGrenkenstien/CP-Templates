#include <bits/stdc++.h>

using namespace std;

class HLD{

    vector<int> parent, depth, heavy, head, pos;
    int cur_pos;

    public:
        HLD(vector<vector<int>> const& adj){

            int n = adj.size();
            parent = vector<int>(n + 1);
            depth = vector<int>(n + 1);
            heavy = vector<int>(n + 1, -1);
            head = vector<int>(n + 1);
            pos = vector<int>(n + 1);
            cur_pos = 0;

            dfs(1, adj);
            decompose(1, 1, adj);
        }

        int dfs(int v, vector<vector<int>> const& adj) {
            int size = 1;
            int max_c_size = 0;
            for (int c : adj[v]) {
                if (c != parent[v]) {
                    parent[c] = v, depth[c] = depth[v] + 1;
                    int c_size = dfs(c, adj);
                    size += c_size;
                    if (c_size > max_c_size)
                        max_c_size = c_size, heavy[v] = c;
                }
            }
            return size;
        }

        void decompose(int v, int h, vector<vector<int>> const& adj) {
            head[v] = h, pos[v] = cur_pos++;
            if (heavy[v] != -1)
                decompose(heavy[v], h, adj);
            for (int c : adj[v]) {
                if (c != parent[v] && c != heavy[v])
                    decompose(c, c, adj);
            }
        }

        int query(int a, int b) {
            int res = 0;
            for (; head[a] != head[b]; b = parent[head[b]]) {
                if (depth[head[a]] > depth[head[b]])
                    swap(a, b);
                int cur_heavy_path_max = segment_tree_query(pos[head[b]], pos[b]);
                res = max(res, cur_heavy_path_max);
            }
            if (depth[a] > depth[b])
                swap(a, b);
            int last_heavy_path_max = segment_tree_query(pos[a], pos[b]);
            res = max(res, last_heavy_path_max);
            return res;
        }

};

int main(){

    

}