#include <bits/stdc++.h>

using namespace std;

class SegmentTree{

    int tree_size;
    vector<int> segTree, arr;

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
                segTree[node] = segTree[2*node] + segTree[2*node+1];
            }
        }

        void update(int node, int start, int end, int idx, int val)
        {
            if(start == end)
            {
                // Leaf node
                arr[idx] += val;
                segTree[node] += val;
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
                segTree[node] = segTree[2*node] + segTree[2*node+1];
            }
        }

        int query(int node, int start, int end, int l, int r)
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
            int p1 = query(2*node, start, mid, l, r);
            int p2 = query(2*node+1, mid+1, end, l, r);
            return (p1 + p2);
        }

};

int main(){

    int n;
    cin>>n;

    vector<int> a(n);

    for(auto &e : a)cin>>e;

    SegmentTree St = SegmentTree(n, a);

}