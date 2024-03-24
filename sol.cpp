#include <bits/stdc++.h>

using namespace std;

int block_size;

void solve(int indx, vector<int> &cnt, vector<int> &next, vector<int> &p){

    int block = indx/block_size;
    cout<<block<<" for "<<indx<<"\n";
    int n = p.size();

    int l = block * block_size;
    int r = min((block + 1) * block_size - 1, n - 1);

    int steps = 0, curr = indx;

    for (int i = r; i >= l; i--){
        if (i+p[i] >= r){ cnt[i] = 1, next[i] = i; }
        else { cnt[i] = cnt[i+p[i]]+1, next[i] = next[i+p[i]]; }
    }
}

int get_ans(int indx, vector<int> &cnt, vector<int> &next){

    int ans = 0;

    int block = indx/block_size;
    int n = cnt.size();
    int r = min((block + 1) * block_size - 1, n - 1);

    while(next[indx] != -1){

        ans += cnt[indx];
        indx = next[indx];
    }
    return ans;
}

int main(){

    int n, m;
    cin>>n>>m;

    vector<int> p(n), cnt(n), next(n, -1);

    block_size = (int)sqrt(n);
    cout<<block_size<<"block size\n";

    for(auto &e : p)cin>>e, cout<<e<<" input ";
    
    for(int i = 0; i < n/block_size; i++)solve(i, cnt, next, p);
    
    while(m--){

        int t, a, b;
        cin>>t;
        
        if(!t){
            cin>>a>>b;
            a--;
            p[a] = b;
            solve(a, cnt, next, p);
        }
        else{
            cin>>a;
            a--;

            int index = a, ans = 0;
            cout<<a<<" initial a\n";
            while (a < n){
                cout<<a<<" current a ";
                ans += cnt[a];
                a = next[a];
                index = a;
                a += p[a];
            } 

            // int ans = get_ans(a, cnt, next);
            cout<<ans<<"\n";
        }

    }

}