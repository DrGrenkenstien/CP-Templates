
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef long long int li;

li mod = 1000000007;

li power(li x, li n){
    li res = 1;
    
    while(n){
        if(n & 1)
            res = (res * x) % mod;
        n >>= 1;
        x = (x * x) % mod;
    }
    return res;
}

int main() {
    
    string s;
    cin>>s;
    
    li p = 31;
    
    int n = s.length();
    
    vector<li> hash(n), primes(n);
    primes[0] = 1; //the culprit
    
    for(int i = 1; i < n ; i++){
        primes[i] = (primes[i - 1] * p) % mod;
    }
    
    for(int i = 0; i < n; i++){
        if(!i){
            hash[i] = (s[i] - 'a' + 1);
        }
        else{
            hash[i] = (hash[i - 1] + ((s[i] - 'a' + 1) * primes[i]) % mod) % mod;
        }
    }
    
    for(int len = 1; len < n; len++){
        for(int i = 0; i + len < n; i++){
            int start = i, end = i + len - 1;
            
            li h = hash[end];
            
            if(start > 0)
                h = (h - hash[start - 1] + mod) % mod;
            
            
            h = (h * primes[n - start - 1]) % mod; //correct equation,
            
            cout<<h<<" hash for "<<s.substr(i, len)<<" \n ";
        }
    }
    
	return 0;
}