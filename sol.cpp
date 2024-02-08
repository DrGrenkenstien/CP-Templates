#include <bits/stdc++.h>

using namespace std;

int findDthElement(const std::set<int>& mySet, int d) {
    auto it = mySet.begin();
    int count = 1;
    
    while(count < d && it != mySet.end()){
        count++;
        it++;
    }

    return *it; // Return the value at the dth position
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

    int t;
    cin>>t;
    while (t--)
    {
        int n, m, k;
        cin>>n>>m>>k;

        vector<int>  a(n), b(m);

        set<int> ar, br;
        vector<int> new_a(k + 1), new_b(k + 1);

        for(auto &e : a){
            cin>>e;
            if(e >= 1 && e <= k)ar.insert(e);
        }

        for(auto &e : b){
            cin>>e;
            if(e >= 1 && e <= k)br.insert(e);
        }
        
        if(ar.size() < k/2 || br.size() < k/2){
            cout<<"NO\n";
            continue;
        }
        
        vector<int> new_a(k + 1), new_b(k + 1);
        
        for(auto itr = ar.begin(); itr != ar.end(); itr++){
            new_a[*itr] = 1;
        }
        for(auto itr = br.begin(); itr != br.end(); itr++){
            new_b[*itr] = 1;
        }
        
        int cnt_a = 0, cnt_b = 0;

        vector<bool> vis(k + 1, false);

        for(int i = 1; i <= k; i++){
            if(new_a[i] && !new_b[i]){
                vis[i] = true;
                cnt_a++;
            }
        }

        for(int i = 1; i <= k; i++){
            if(!new_a[i] && new_b[i]){
                vis[i] = true;
                cnt_b++;
            }
        }
        
        if(cnt_a + cnt_b == k){
            cout<<"YES\n";
            continue;
        }

        int index = 1;
        while(cnt_a < k/2 && index <= k){
            if(!vis[index]){
                cnt_a++;
                vis[index] = true;
            }
            index++;
        }

        if(cnt_a < k/2){
            cout<<"NO\n";
            continue;
        } 

        index = 1;
        while(cnt_b < k/2 && index <= k){
            if(!vis[index]){
                cnt_b++;
                vis[index] = true;
            }
            index++;
        }

        if(cnt_b < k/2){
            cout<<"NO\n";
            continue;
        }

        if(cnt_a + cnt_b == k){
            cout<<"YES\n";
            continue;
        }
        else{
            cout<<"NO\n";
        }
    }
    

	return 0;
}