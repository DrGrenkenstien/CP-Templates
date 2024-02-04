#include <bits/stdc++.h>

using namespace std;

vector<int> calculateZ(const std::string& s) {
    int n = s.length();
    std::vector<int> Z(n, 0);

    int left = 0, right = 0;
    for (int i = 1; i < n; ++i) {
        if (i <= right) {
            Z[i] = std::min(right - i + 1, Z[i - left]);
        }

        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]]) {
            ++Z[i];
        }

        if (i + Z[i] - 1 > right) {
            left = i;
            right = i + Z[i] - 1;
        }
    }

    return Z;
}

string findShortestRepeatingUnit(const std::string& s) {
    int n = s.length();

    // Calculate the Z array for the given string
    std::vector<int> Z = calculateZ(s);

    for (int i = 1; i < n; ++i) {
        if (i + Z[i] == n && n % i == 0) {
            // If Z[i] reaches the end of the string and i is a divisor of n
            // then s[0:i-1] is the shortest repeating unit
            return s.substr(0, i);
        }
    }

    // If no repeating unit is found, return the original string
    return s;
}