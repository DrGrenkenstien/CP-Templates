#include <bits/stdc++.h>

using namespace std;

typedef long long int li;

class EluerTour{

    vector<int> start, end, euler_tour, property, propval;
    vector<vector<int> > tree;
    int timer = 0;

    public:

        EluerTour(vector<vector<int> > &tree, int n, vector<int> &val){

            this->tree = tree;
            start.resize(n + 1);
            end.resize(n + 1);
            // property.resize(n + 1);
            // euler_tour.resize(n + 1);
            propval = val;
        }

        void Euler_tour(int at = 0, int prev = -1, int depth = 0) {
            start[at] = timer;
            property.push_back(depth);
            euler_tour.push_back(at);
            for (int n : tree[at]) {
                if (n != prev) { Euler_tour(n, at, depth + 1), euler_tour.push_back(at); }

            }
            end[at] = timer;
        }

        vector<int> getStart(){
            return start;
        }

        vector<int> getEnd(){
            return end;
        }

        vector<int> getPropArray(){
            return property;
        }

        vector<int> getEulerTour(){
            return euler_tour;
        }

};

class SegmentTree{

    int tree_size;
    vector<li> segTree;
    vector<int> arr;

    public:
        SegmentTree(int n, vector<int> &a){

            tree_size = 4*n;
            segTree.resize(tree_size);
            arr = a;
        }
        
        void build(int node, int start, int end)
        {
            if(start == end)
            {
                // Leaf node will have a single element
                segTree[node] = arr[start];
            }
            else
            {
                int mid = (start + end) / 2;
                // Recurse on the left child
                build(2*node, start, mid);
                // Recurse on the right child
                build(2*node+1, mid+1, end);
                // Internal node will have the sum of both of its children
                segTree[node] = min(segTree[2*node], segTree[2*node+1]);
            }
        }

        void update(int node, int start, int end, int idx, int val)
        {
            if(start == end)
            {
                // Leaf node
                arr[idx] = val;
                segTree[node] = val;
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
                segTree[node] = min(segTree[2*node], segTree[2*node+1]);
            }
        }

        li query(int node, int start, int end, int l, int r)
        {
            if(r < start or end < l)
            {
                // range represented by a node is completely outside the given range
                return 0;
            }
            if(l <= start and end <= r)
            {
                // range represented by a node is completely inside the given range
                return segTree[node];
            }
            // range represented by a node is partially inside and partially outside the given range
            int mid = (start + end) / 2;
            li p1 = query(2*node, start, mid, l, r);
            li p2 = query(2*node+1, mid+1, end, l, r);
            return min(p1, p2);
        }

};

int main(){

    int n, q;
    cin>>n>>q;

    vector<int> val(n + 1);

    for(int i = 1; i <= n; i++){
        cin>>val[i];
    }

    vector<vector<int> > graph(n + 1);

    for(int i = 0; i < n - 1; i++){
        int a, b;
        cin>>a>>b;

        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    EluerTour ET = EluerTour(graph, n, val);
    ET.Euler_tour(1);

    auto prop = ET.getPropArray();
    auto start = ET.getStart();
    auto end = ET.getEnd();
    
    // for(auto e : prop)cout<<e<<" prop ";

    int sz = prop.size();

    SegmentTree ST = SegmentTree(sz, prop);

    ST.build(1, 0, sz);

    while(q--){

        int a, b;
        cin>>a>>b;

       
        if (start[a] > start[b]) swap(a, b);
            // return query(tin[a], tin[b]);


        cout<<ST.query(1, 0, sz, start[a], start[b])<<"\n";

        // if(t == 1){
        //     int s, x;
        //     cin>>s>>x;

        //     ST.update(1, 0, n, start[s], x);
        //     // cout<<ST.query(1, 0, n, start[s], start[s])<<" querying updated index \n";
        // }
        // else{
        //     int s;
        //     cin>>s;

        //     cout<<ST.query(1, 0, n, start[s], end[s] - 1)<<"\n";
        // }

    }

}