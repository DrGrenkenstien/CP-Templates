#include <bits/stdc++.h>

using namespace std;

typedef long long int li;

li inf = 1e18;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

    int n;
	cin>>n;

	vector<int> a(n), b(n), x(n);

	for(int i = 0; i < n; i++){
		cin>>a[i]>>b[i]>>x[i];
	}

	vector<int> par(n + 1, -1);

	for(int i = 1; i < n; i++){
		par[x[i - 1]] = i;
	}

	vector<li> dp(n + 2, inf);

	dp[1] = 0;

	for(int i = 1; i < n; i++){
		dp[i] += a[i - 1];
		dp[i + 1] = dp[i];
	}


	cout<<min(dp[n][1], dp[n][0]);

	return 0;
}