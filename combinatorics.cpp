const int MOD = 1e9 + 7;
const int N = 1e6 + 5;

long long fact[N], inv_fact[N];

// Función para exponenciación binaria
long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// Precomputar factoriales e inversos
void precompute_factorials() {
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        inv_fact[i] = binpow(fact[i], MOD - 2); // Inverso modular
    }
}

// nCk = n! / (k!(n-k)!) % MOD
long long nCk(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
}
