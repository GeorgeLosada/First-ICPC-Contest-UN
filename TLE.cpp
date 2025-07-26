#include <bits/stdc++.h>
using namespace std;

// Optimizaciones anti-TLE
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("avx,avx2,fma")
#define FAST_IO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl '\n'

// Macros y tipos
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define mp make_pair

// Constantes
const int MOD = 1e9 + 7;
const ll INF = 1e18;

// ------------------------- ESTRUCTURAS ANTI-TLE -------------------------

// Disjoint Set Union (DSU) ultra compacto
struct DSU {
    vi parent, rank;
    DSU(int n) {
        parent.resize(n+1);
        rank.resize(n+1, 0);
        iota(all(parent), 0);
    }
    int find(int x) { 
        return parent[x] = (x == parent[x] ? x : find(parent[x])); 
    }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return false;
        if(rank[x] < rank[y]) swap(x, y);
        parent[y] = x;
        rank[x] += (rank[x] == rank[y]);
        return true;
    }
};

// Fenwick Tree (BIT) optimizado
struct Fenwick {
    vll tree;
    int n;
    Fenwick(int size) : n(size) { tree.assign(n+1, 0); }
    void update(int i, ll delta) { 
        for(; i <= n; i += i & -i) tree[i] += delta; 
    }
    ll query(int i) {
        ll sum = 0;
        for(; i > 0; i -= i & -i) sum += tree[i];
        return sum;
    }
    ll range(int l, int r) { 
        return query(r) - query(l-1); 
    }
};

// Dijkstra con prioridad
vector<ll> dijkstra(vector<vector<pll>>& g, int start) {
    vll dist(sz(g), INF);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    pq.push({0, start});
    dist[start] = 0;
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;
        for(auto [v, w] : g[u]) {
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// BFS compacto
vi bfs(vector<vi>& graph, int start) {
    vi dist(sz(graph), -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int v : graph[u]) {
            if(dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

// Binary Search sobre respuesta
ll binary_search(ll lo, ll hi, function<bool(ll)> f) {
    while(lo < hi) {
        ll mid = lo + (hi - lo)/2;
        f(mid) ? hi = mid : lo = mid + 1;
    }
    return lo;
}

// ------------------------- FUNCIONES RÁPIDAS -------------------------

// Exponenciación modular (para problemas con MOD)
ll mod_pow(ll base, ll exp, ll mod = MOD) {
    ll res = 1;
    base %= mod;
    while(exp > 0) {
        if(exp & 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return res;
}

// GCD y LCM
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

// ------------------------- MAIN -------------------------
int main() {
    FAST_IO;
    
    // Ejemplo de uso rápido (descomentar para test)
    /*
    int n = 5;
    DSU dsu(n);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    cout << "DSU: " << dsu.find(1) << " " << dsu.find(3) << endl;
    
    Fenwick fenw(10);
    fenw.update(2, 5);
    fenw.update(3, 7);
    cout << "Fenwick: " << fenw.range(2, 3) << endl;
    
    vector<vi> graph = {{1}, {0, 2}, {1}};
    vi dist = bfs(graph, 0);
    cout << "BFS: ";
    for(int d : dist) cout << d << " ";
    cout << endl;
    
    vector<vector<pll>> weighted = {{{1, 5}}, {{0, 5}, {2, 3}}, {{1, 3}}};
    vll d_dist = dijkstra(weighted, 0);
    cout << "Dijkstra: ";
    for(ll d : d_dist) cout << d << " ";
    cout << endl;
    */
    
    return 0;
}
