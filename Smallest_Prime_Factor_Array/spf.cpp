#include <bits/stdc++.h> // header file includes every Standard library
using namespace std;

typedef long long int li;

int MAX = 1e6 + 1;

vector<bool> v(MAX, false);
int len;
vector<int> sp(MAX);

void Sieve(){
	for (int i = 2; i < MAX; i += 2)	sp[i] = 2;//even numbers have smallest prime factor 2
	for (li i = 3; i < MAX; i += 2){
        // cout<<"Processing "<<i<<"\n";
        // sp[i] = i;
		if (!v[i]){
			sp[i] = i;
			for (li j = i; (j*i) < MAX; j += 2){
				if (!v[j*i])	v[j*i] = true, sp[j*i] = i;
			}
		}
	}
}