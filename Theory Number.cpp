#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// GCD común (Euclides)
ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// LCM usando GCD
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

// Exponenciación rápida: a^b % m
ll binpow(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// Criba de Eratóstenes: primos hasta n
vector<bool> criba(int n) {
    vector<bool> es_primo(n + 1, true);
    es_primo[0] = es_primo[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (es_primo[i]) {
            for (int j = i * i; j <= n; j += i)
                es_primo[j] = false;
        }
    }
    return es_primo;
}

// Primos menores o iguales a n
vector<int> primos_hasta(int n) {
    vector<bool> es_primo = criba(n);
    vector<int> primos;
    for (int i = 2; i <= n; ++i)
        if (es_primo[i]) primos.push_back(i);
    return primos;
}

// Función totiente de Euler
int phi(int n) {
    int res = n;
    for (int i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

// Inverso modular: a^-1 mod m (cuando m es primo)
ll modinv(ll a, ll m) {
    return binpow(a, m - 2, m);  // Solo si m primo
}

// Factorización simple
vector<int> factores(int n) {
    vector<int> f;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            f.push_back(i);
            n /= i;
        }
    }
    if (n > 1) f.push_back(n);
    return f;
}

// GCD común (Euclides)
ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// LCM usando GCD
ll lcm(ll a, ll b) {
    return a / gcd(a, b) * b;
}

// Exponenciación rápida: a^b % m
ll binpow(ll a, ll b, ll m) {
    ll res = 1;
    a %= m;
    while (b) {
        if (b & 1) res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}

// Criba de Eratóstenes: primos hasta n
vector<bool> criba(int n) {
    vector<bool> es_primo(n + 1, true);
    es_primo[0] = es_primo[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (es_primo[i]) {
            for (int j = i * i; j <= n; j += i)
                es_primo[j] = false;
        }
    }
    return es_primo;
}

// Primos menores o iguales a n
vector<int> primos_hasta(int n) {
    vector<bool> es_primo = criba(n);
    vector<int> primos;
    for (int i = 2; i <= n; ++i)
        if (es_primo[i]) primos.push_back(i);
    return primos;
}

// Función totiente de Euler
int phi(int n) {
    int res = n;
    for (int i = 2; i*i <= n; ++i) {
        if (n % i == 0) {
            while (n % i == 0) n /= i;
            res -= res / i;
        }
    }
    if (n > 1) res -= res / n;
    return res;
}

// Inverso modular: a^-1 mod m (cuando m es primo)
ll modinv(ll a, ll m) {
    return binpow(a, m - 2, m);  // Solo si m primo
}

// Factorización simple
vector<int> factores(int n) {
    vector<int> f;
    for (int i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            f.push_back(i);
            n /= i;
        }
    }
    if (n > 1) f.push_back(n);
    return f;
}
