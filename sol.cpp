#include <bits/stdc++.h>

using namespace std;

class HLD{

    vector<int> parent, depth, heavy, head, pos;
    int cur_pos, N;
	int tree_size;
    vector<int> arr;
	vector<set<int> > segTree;

    public:
        HLD(vector<vector<int>> const& adj, int n, vector<int> &a){

			N = n;
            parent = vector<int>(n + 1);
            depth = vector<int>(n + 1);
            heavy = vector<int>(n + 1, -1);
            head = vector<int>(n + 1);
            pos = vector<int>(n + 1);
            cur_pos = 0;
			tree_size = 4*n;
            segTree.resize(tree_size);
			arr = a;

            dfs(1, adj);
            decompose(1, 1, adj);
            // cout<<"curr pos : "<<cur_pos<<"\n";
        }

		auto position(int node){
			return pos[node];
		}

		void build(int node, int start, int end)
        {
            if(start == end)
            {
                // Leaf node will have a single element
                segTree[node].insert(arr[start]);
            }
            else
            {
                int mid = (start + end) / 2;
                // Recurse on the left child
                build(2*node, start, mid);
                // Recurse on the right child
                build(2*node+1, mid+1, end);
                // Internal node will have the sum of both of its children

				auto left = segTree[2*node];
				auto right = segTree[2*node + 1];

				if(left.size() < right.size())swap(left, right);

				for(auto itr = right.begin(); itr != right.end(); itr++){
					left.insert(*itr);
				}

                segTree[node] = left;
            }
        }

		void update(int node, int start, int end, int idx, int val)
        {
            if(start == end)
            {
                // Leaf node will have a single element
                segTree[node].insert(val);
            }
            else
            {
                int mid = (start + end) / 2;
                if(start <= idx and idx <= mid)
                {
                    // If idx is in the left child, recurse on the left child
                    update(2*node, start, mid, idx, val);
                }
                else
                {
                    // if idx is in the right child, recurse on the right child
                    update(2*node+1, mid+1, end, idx, val);
                }
                // Internal node will have the sum of both of its children
				auto left = segTree[2*node];
				auto right = segTree[2*node + 1];

				if(segTree[node].size() < right.size())swap(segTree[node], right);

				for(auto itr = right.begin(); itr != right.end(); itr++){
					segTree[node].insert(*itr);
				}

                if(segTree[node].size() < left.size())swap(segTree[node], left);

                for(auto itr = left.begin(); itr != left.end(); itr++){
					segTree[node].insert(*itr);
				}
            }
        }

		bool query(int node, int start, int end, int l, int r, int val)
        {
            if(r < start or end < l)
            {
                // range represented by a node is completely outside the given range
                return 0;
            }
            if(l <= start and end <= r)
            {
                // range represented by a node is completely inside the given range
                if(segTree[node].find(val)!=segTree[node].end())return true;
                return false;
            }
            // range represented by a node is partially inside and partially outside the given range
            int mid = (start + end) / 2;
            bool p1 = query(2*node, start, mid, l, r, val);
            bool p2 = query(2*node+1, mid+1, end, l, r, val);
            return (p1 | p2);
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

        bool sol_query(int a, int b, int val) {
            bool res = false;
            for (; head[a] != head[b]; b = parent[head[b]]) {
                if (depth[head[a]] > depth[head[b]])
                    swap(a, b);
                bool cur_heavy_path_max = query(1, 0, cur_pos - 1, pos[head[b]], pos[b], val);
                res |= cur_heavy_path_max;
				if(res)return true;
            }
            if (depth[a] > depth[b])
                swap(a, b);
            bool last_heavy_path_max = query(1, 0, cur_pos - 1, pos[a], pos[b], val);
            res |= last_heavy_path_max;
            return res;
        }

};

int main(){
	

  
	// For getting input from input.txt file 
	freopen("milkvisits.in", "r", stdin); 

	// Printing the Output to output.txt file 
	freopen("milkvisits.out", "w", stdout); 
  


    int n, m;
	cin>>n>>m;

	vector<int> a(n);

	for(auto &e : a)cin>>e;

	vector<vector<int> > graph(n + 1);

	for(int i = 0; i < n - 1; i++){
		int u, v;
		cin>>u>>v;

		graph[u].push_back(v);
		graph[v].push_back(u);
	}

	HLD sol = HLD(graph, n, a);

	for(int i = 1; i <= n; i++){
		sol.update(1, 0, n - 1, sol.position(i), a[i - 1]);
	}

	while(m--){

		int u, v, c;
		cin>>u>>v>>c;

		cout<<sol.sol_query(u, v, c);

	}

}