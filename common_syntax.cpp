#include <vector>
#include<iostream>
#include <numeric>

using namespace std;

int main(){

    int n;
    
    // declaring and taking array as inputs
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin>>a[i];
    }

    // Calculate the sum using std::accumulate
    int sum = accumulate(a.begin(), a.end(), 0);

    

}