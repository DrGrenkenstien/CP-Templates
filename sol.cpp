#include <bits/stdc++.h>

using namespace std;

struct Query {
	int l, r, idx;
};

class Mo{

    int block_size;
    int different_values = 0, q;
    int mo_left = -1;
	int mo_right = -1;
    vector<int> ans, arr;
    vector<Query> query;
    multiset<int> val;

    public:

        Mo(int n, vector<Query> &queries, vector<int> &a){
            query = queries;
            arr = a;
            q = queries.size();
            block_size = (int)sqrt(n);
            sort(queries.begin(), queries.end(), mo_cmp);
            ans.resize(queries.size());
        }

        bool mo_cmp(Query a, Query b) {
            int block_a = a.l / block_size;
            int block_b = b.l / block_size;
            if (block_a == block_b) { return a.r < b.r; }
            return block_a < block_b;
        };

        void remove(int idx) {
            val.erase(val.find(arr[idx]));
        };
        void add(int idx) {
           val.insert(arr[idx]);
        };

        void process_queries(){
            
            for (int i = 0; i < q; i++) {
                int left = query[i].l;
                int right = query[i].r;

                while (mo_left < left) { remove(mo_left++); }
                while (mo_left > left) { add(--mo_left); }
                while (mo_right < right) { add(++mo_right); }
                while (mo_right > right) { remove(mo_right--); }

                ans[query[i].idx] = val.size();
            }

        }

        vector<int> get_answered_queries(){
            return ans;
        }

};

int main(){

    int n, q;
    cin>>n;
    
    vector<int> a(n);

    for(auto &e : a)cin>>e;

    cin>>q;

    vector<Query> que(q);

    for(int i = 0; i < q; i++){
        int x, y;
		cin >> x >> y;
		que.push_back({--x, --y, i});
    }


    Mo solver = Mo(n, que, a);

    solver.process_queries();

    auto ans = solver.get_answered_queries();

    for(auto e : ans)cout<<e<<"\n";

}