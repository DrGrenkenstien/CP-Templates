#include <bits/stdc++.h>

using namespace std;

// Code for finding the number of Numbers upto N with digit sum a prime number

class DigitDP{
    
    private:
        string s;
        int sz;

    public:
        DigitDP(string n){
            s = n;
            sz = s.length();
        }

        bool isPrime(int n){
            if(n % 2 == 0)return false;
            return true;
        }

        int Calculate(){

            vector<vector<vector<int> > > dp(sz + 1, vector<vector<int> > (2, vector<int> (201, 0)));

            dp[sz][0][0] = 1;
            dp[sz][1][0] = 1;

            for(int i = sz-1; i >=0 ; i--) {
                for(int tight = 0; tight < 2 ; tight++) {
                    for(int sum = 0; sum < 200 ; sum++) {
                        if(tight) {
                            for(int d = 0; d <= s[i] - '0' ; d++) {

                                if(sum - d < 0) continue;

                                dp[i][1][sum] += (d == s[i]-'0') ? dp[i+1][1][sum-d] : dp[i+1][0][sum-d];
                            }
                        }
                        else {
                            for(int d = 0; d < 10 ; d++) {
                                if(sum - d < 0) continue;
                                dp[i][0][sum] += dp[i+1][0][sum-d];
                            }
                        }
                    }
                }
            }

            int ans = 0;
            for(int i = 0; i < 200; i++) {
                if(isPrime(i))
                ans += dp[0][1][i];
            }
            return ans;

        }

};


int main(){

    int n = 545;

    DigitDP Digit = DigitDP(to_string(n));

    cout<<Digit.Calculate()<<" ans ";

}