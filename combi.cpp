#define MAX_N 200000
vector<long long> fact(MAX_N + 1), inv_fact(MAX_N + 1);

long long mod_inverse(long long x, long long mod) {
    long long result = 1;
    long long power = mod - 2;
    while (power) {
        if (power & 1) result = result * x % mod;
        x = x * x % mod;
        power >>= 1;
    }
    return result;
}

void precompute_factorials() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= MAX_N; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
    }
    inv_fact[MAX_N] = mod_inverse(fact[MAX_N], MOD);
    for (int i = MAX_N - 1; i >= 1; --i) {
        inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
    }
    inv_fact[0] = 1;
}

long long comb(int n, int k) {
    if (k > n || k < 0) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}
