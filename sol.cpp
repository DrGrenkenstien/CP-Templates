#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef long long int li;

li maxi = (1 << 20) - 1;

class SOS{

    const li MLOG = 20;
    const li MAXN = (1<<MLOG); 
    vector<li> dp;

    public:

        SOS(){
            dp.resize(MAXN + 1);
        }
        
        void Set(int i, int val){
            dp[i] = val;
        }
        
        void Inc(int i, int val){
            dp[i] += val;
        }
        
        li get(int i){
            return dp[i];
        }
        
        void forward1(){	// adding element to all its super set
            for(int bit = 0; bit < MLOG; bit++){
                for(int i = 0; i < MAXN; i++){
                    if(i&(1<<bit))dp[i]+=dp[i^(1<<bit)];
                }
            }
        }

        void backward1(){	// adding element to all its super set
            for(int bit = 0; bit < MLOG; bit++){
                for(int i = MAXN - 1; i >= 0; i--){
                    if(i&(1<<bit))dp[i]-=dp[i^(1<<bit)];
                }
            }
        }

         void forward2(){	// adding element to all its super set
            for(int bit = 0; bit < MLOG; bit++){
                for(int i = MAXN - 1; i >= 0; i--){
                    if(i&(1<<bit))dp[i^(1<<bit)]+=dp[i];
                }
            }
        }

        void backward2(){	// adding element to all its super set
            for(int bit = 0; bit < MLOG; bit++){
                for(int i = 0; i < MAXN; i++){
                    if(i&(1<<bit))dp[i^(1<<bit)]-=dp[i];
                }
            }
        }

};

int main() {
	
    int n;
    cin>>n;
    
    vector<int> a(n);
    
    for(auto &e : a)cin>>e;
    
    SOS sos = SOS();
    
    for(auto e : a){
        sos.Inc(e, 1);
    }
    
    sos.forward1();
    
    vector<vector<li> > ans(n);
    
    for(int i = 0; i < n; i++){
        ans[i].push_back(sos.get(a[i]));
    }
    
    sos.backward1();
    
    sos.forward2();
    
    for(int i = 0; i < n; i++){
        ans[i].push_back(sos.get(a[i]));
    }
    
    sos.backward2();
    
    // for(auto e : a){
    //     sos.Set(e, 0);
    //     sos.Inc(((~e) & maxi), 1);
    // }
    
    sos.forward1();
    
    for(int i = 0; i < n; i++){
        ans[i].push_back(n - sos.get(((~a[i]) & maxi)));
    }
    
    for(auto v : ans){
        cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<"\n";
    }
	
	return 0;
}