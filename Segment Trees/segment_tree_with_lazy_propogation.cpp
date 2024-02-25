#include <bits/stdc++.h>

using namespace std;

class SegmentTree{

    int tree_size;
    vector<int> segTree, arr, lazy;

    public:
        SegmentTree(int n, vector<int> &a){

            tree_size = 4*n;
            segTree.resize(tree_size);
            lazy.resize(tree_size);
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

        void updateRange(int node, int start, int end, int l, int r, int val)
        {
            if(lazy[node] != 0)
            { 
                // This node needs to be updated
                segTree[node] += (end - start + 1) * lazy[node];    // Update it
                if(start != end)
                {
                    lazy[node*2] += lazy[node];                  // Mark child as lazy
                    lazy[node*2+1] += lazy[node];                // Mark child as lazy
                }
                lazy[node] = 0;                                  // Reset it
            }
            if(start > end or start > r or end < l)              // Current segment is not within range [l, r]
                return;
            if(start >= l and end <= r)
            {
                // Segment is fully within range
                segTree[node] += (end - start + 1) * val;
                if(start != end)
                {
                    // Not leaf node
                    lazy[node*2] += val;
                    lazy[node*2+1] += val;
                }
                return;
            }
            int mid = (start + end) / 2;
            updateRange(node*2, start, mid, l, r, val);        // Updating left child
            updateRange(node*2 + 1, mid + 1, end, l, r, val);   // Updating right child
            segTree[node] = segTree[node*2] + segTree[node*2+1];        // Updating root with max value 
        }

        int queryRange(int node, int start, int end, int l, int r)
        {
            if(start > end or start > r or end < l)
                return 0;         // Out of range
            if(lazy[node] != 0)
            {
                // This node needs to be updated
                segTree[node] += (end - start + 1) * lazy[node];            // Update it
                if(start != end)
                {
                    lazy[node*2] += lazy[node];         // Mark child as lazy
                    lazy[node*2+1] += lazy[node];    // Mark child as lazy
                }
                lazy[node] = 0;                 // Reset it
            }
            if(start >= l and end <= r)             // Current segment is totally within range [l, r]
                return segTree[node];
            int mid = (start + end) / 2;
            int p1 = queryRange(node*2, start, mid, l, r);         // Query left child
            int p2 = queryRange(node*2 + 1, mid + 1, end, l, r); // Query right child
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