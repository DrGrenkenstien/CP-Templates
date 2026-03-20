#include <bits/stdc++.h>

using namespace std;

int main(){
    #ifndef ONLINE_JUDGE
        freopen("./input.txt", "r", stdin);
        freopen("./output.txt", "w", stdout);
    #endif

    int t;
    cin>>t;

    while (t--){
        int n;
        cin>>n;

        vector<int> v(n);

        for(auto &e: v){
            cin>>e;
        }
//        for(auto e : v){
//            count[e]++;
//        }

        int curr_max = INT_MIN;
        int ans = 0;

        for(int e : v){
            if(e >= curr_max){
                curr_max = max(curr_max, e);
                ans++;
            }
        }
        cout<<ans<<"\n";
    }
}