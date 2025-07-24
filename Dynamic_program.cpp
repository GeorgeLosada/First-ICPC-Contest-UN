#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;

//
// 1. Fibonacci con memoización
//
vector<ll> fib;
ll fibonacci(int n) {
    if (n <= 1) return n;
    if (fib[n] != -1) return fib[n];
    return fib[n] = (fibonacci(n - 1) + fibonacci(n - 2)) % MOD;
}

//
// 2. Subconjunto suma (Subset Sum) clásico con DP 1D
// ¿Se puede obtener suma S con algunos elementos?
//
bool subset_sum(const vector<int>& a, int S) {
    vector<bool> dp(S + 1, false);
    dp[0] = true;
    for (int x : a) {
        for (int s = S; s >= x; --s)
            dp[s] = dp[s] || dp[s - x];
    }
    return dp[S];
}

//
// 3. Mochila 0/1 (Knapsack) clásica con DP 2D
// Dado N elementos con peso y valor, ¿máximo valor que cabe en W?
//
int knapsack(int W, const vector<int>& peso, const vector<int>& valor) {
    int n = peso.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            dp[i][w] = dp[i - 1][w];
            if (w >= peso[i - 1])
                dp[i][w] = max(dp[i][w], dp[i - 1][w - peso[i - 1]] + valor[i - 1]);
        }
    }
    return dp[n][W];
}

//
// 4. DP con Bitmasks (Traveling Salesman Problem - versión simple)
// TSP de tamaño pequeño, mínimo costo de visitar todos los nodos y volver
//
const int MAXN = 16;
int tsp_dp[1 << MAXN][MAXN]; // dp[mask][u] = mínimo costo para llegar a u habiendo visitado mask
int tsp(const vector<vector<int>>& dist, int n) {
    const int INF = 1e9;
    for (int mask = 0; mask < (1 << n); ++mask)
        for (int i = 0; i < n; ++i)
            tsp_dp[mask][i] = INF;
    tsp_dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int u = 0; u < n; ++u) {
            if (mask & (1 << u)) {
                for (int v = 0; v < n; ++v) {
                    if (!(mask & (1 << v)))
                        tsp_dp[mask | (1 << v)][v] = min(
                            tsp_dp[mask | (1 << v)][v],
                            tsp_dp[mask][u] + dist[u][v]
                        );
                }
            }
        }
    }
    int res = 1e9;
    for (int u = 0; u < n; ++u)
        res = min(res, tsp_dp[(1 << n) - 1][u] + dist[u][0]);
    return res;
}
