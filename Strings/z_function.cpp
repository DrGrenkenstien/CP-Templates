#include <bits/stdc++.h>

using namespace std;

class Z_Function{

    string s;
    vector<int> z;

    public:
        
        Z_Function(string local){

            s = local;
            z.resize(local.length());
        }

        vector<int> z_function() {
            int n = s.size();
            int l = 0, r = 0;
            for(int i = 1; i < n; i++) {
                if(i < r) {
                    z[i] = min(r - i, z[i - l]);
                }
                while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
                    z[i]++;
                }
                if(i + z[i] > r) {
                    l = i;
                    r = i + z[i];
                }
            }
            return z;
        }

};

int main(){


    
}