#include<bits/stdc++.h>

using namespace std;

// returns count of number between 0 and n with jth bit set
long long f(long long j,long long n){
  long long p2=(1ll<<j); // 2^j
  long long k=n/(2*p2);
  long long res=k*p2;
  long long l=n%(2*p2);
  if(l>=p2){
    res+=(l-p2+1);
  }
  return res;
}

int main(){
    return 0;
}