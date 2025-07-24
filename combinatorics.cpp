#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int MAX = 1e5 + 5;

// Precomputación de factoriales y factoriales inversos
long long fact[MAX], invFact[MAX];

// Exponenciación rápida
long long binpow(long long a, long long b) {
    long long res = 1;
    a %= MOD;
    while (b) {
        if (b & 1) res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

// Inverso modular usando Fermat
long long modinv(long long x) {
    return binpow(x, MOD - 2);
}

// Precalcular factoriales e inversos
void precompute() {
    fact[0] = invFact[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        fact[i] = fact[i - 1] * i % MOD;
        invFact[i] = modinv(fact[i]);
    }
}

// C(n, k) = n! / (k!(n-k)!)
long long comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
}

// Coeficiente binomial con DP (útil si n y k son pequeños)
long long C[500][500];
void build_pascal() {
    for (int i = 0; i < 500; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++)
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
    }
}

// Función Phi de Euler para todos los números hasta n
int phi[MAX];
void compute_phi(int n) {
    for (int i = 1; i <= n; i++) phi[i] = i;
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
}

// Permutaciones: P(n, k) = n! / (n - k)!
long long perm(int n, int k) {
    if (k < 0 || k > n) return 0;
    return fact[n] * invFact[n - k] % MOD;
}

// Potencia con módulo para conteos: ej. contar strings de k letras con n posibles letras
long long power_count(int n, int k) {
    return binpow(n, k);
}

// TEST
int main() {
    precompute();
    build_pascal();
    compute_phi(100);

    cout << "C(5, 2) = " << comb(5, 2) << "\n";       // 10
    cout << "P(5, 2) = " << perm(5, 2) << "\n";       // 20
    cout << "phi(10) = " << phi[10] << "\n";          // 4
    cout << "5^3 mod MOD = " << power_count(5, 3) << "\n"; // 125
    cout << "C(10, 4) (Pascal) = " << C[10][4] << "\n";    // 210

    return 0;
}
