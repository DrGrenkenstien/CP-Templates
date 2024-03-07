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
    vector<int> ans;
    vector<Query> query;

    public:

        Mo(int n, vector<Query> &queries){
            query = queries;
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
            
        };
        void add(int idx) {
           
        };

        void process_queries(){
            
            for (int i = 0; i < q; i++) {
                int left = query[i].l;
                int right = query[i].r;

                while (mo_left < left) { remove(mo_left++); }
                while (mo_left > left) { add(--mo_left); }
                while (mo_right < right) { add(++mo_right); }
                while (mo_right > right) { remove(mo_right--); }

                ans[query[i].idx] = different_values;
            }

        }

        vector<int> get_answered_queries(){
            return ans;
        }

};

int main(){



}