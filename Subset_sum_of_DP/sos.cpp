#include <bits/stdc++.h>

using namespace std;

typedef long long li;

class SOS{

    const li MLOG = 20;
    const li MAXN = (1<<MLOG); 
    vector<li> dp;

    public:

        SOS(){
            dp.resize(MAXN + 1);
        }

        void forward1(){	// adding element to all its super set
            for(int bit = 0; bit < MLOG; bit++){
                for(int i = 0; i < MAXN; i++){
                    if(i&(1<<bit))dp[i]+=dp[i^(1<<bit)];
                }
            }
        }

        void backward1(){	
            for(int bit = 0; bit < MLOG; bit++){
                for(int i = MAXN - 1; i >= 0; i--){
                    if(i&(1<<bit))dp[i]-=dp[i^(1<<bit)];
                }
            }
        }

         void forward2(){	// add elements to its subsets
            for(int bit = 0; bit < MLOG; bit++){
                for(int i = MAXN - 1; i >= 0; i--){
                    if(i&(1<<bit))dp[i^(1<<bit)]+=dp[i];
                }
            }
        }

        void backward2(){	
            for(int bit = 0; bit < MLOG; bit++){
                for(int i = 0; i < MAXN; i++){
                    if(i&(1<<bit))dp[i^(1<<bit)]-=dp[i];
                }
            }
        }

};

int main(){



}