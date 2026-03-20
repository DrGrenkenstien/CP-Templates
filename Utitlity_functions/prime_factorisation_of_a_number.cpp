vector<pair<long long, int>> getPrimeFactorization(long long n) {
    vector<pair<long long, int>> factors;

    // 1. Handle the even prime factor (2)
    int count2 = 0;
    while (n % 2 == 0) {
        count2++;
        n /= 2;
    }
    if (count2 > 0) {
        factors.push_back({2, count2});
    }

    // 2. Handle odd factors up to sqrt(n)
    for (long long i = 3; i * i <= n; i += 2) {
        int count = 0;
        while (n % i == 0) {
            count++;
            n /= i;
        }
        if (count > 0) {
            factors.push_back({i, count});
        }
    }

    // 3. Handle the case where n is a prime number greater than 2
    if (n > 2) {
        factors.push_back({n, 1});
    }

    return factors;
}//
// Created by shubham bhadoria on 01/03/26.
//
