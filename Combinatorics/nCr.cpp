#include <iostream>
#include <vector>

using namespace std;

typedef long long int li;

vector<li> fac, inv; // resize it next time

int mod = 1e7 + 9;

li nCr(li n, li r)
{
    if(n<0||r<0||r>n)
        return 0;
    return fac[n]*inv[r]*inv[n-r];
}

void pre(li n)
{
    fac[0]=1;
    for(int i=1;i<=n;++i)
        fac[i]=i*fac[i-1];
    inv[n]=fac[n]; // fix this
    for(int i=n;i>0;--i)
        inv[i-1]=i*inv[i];
    // assert(inv[0]==mint(1));
}

int main(){

}