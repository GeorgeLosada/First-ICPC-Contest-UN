#include <bits/stdc++.h>
using namespace std;

// Configuración rápida de I/O
#define FAST_IO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// Macros útiles
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i = 0; i < (n); i++)
#define forn(i, n) for(int i = 0; i < (n); i++)
#define forab(i, a, b) for(int i = (a); i < (b); i++)

// Tipos de datos
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

// ==================== ESTRUCTURAS DE DATOS ====================

// ---------- Disjoint Set Union (DSU) ----------
struct DSU {
    vector<int> parent, size;
    
    DSU(int n) {
        parent.resize(n+1);
        size.resize(n+1, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (size[x] < size[y]) swap(x, y);
        parent[y] = x;
        size[x] += size[y];
        return true;
    }
};

// ---------- Fenwick Tree (BIT) ----------
struct FenwickTree {
    vector<ll> bit;
    int n;

    FenwickTree(int size) {
        n = size;
        bit.assign(n+1, 0);
    }

    void update(int idx, ll delta) {
        for(; idx <= n; idx += idx & -idx)
            bit[idx] += delta;
    }

    ll query(int idx) {
        ll sum = 0;
        for(; idx > 0; idx -= idx & -idx)
            sum += bit[idx];
        return sum;
    }
    
    ll range_query(int l, int r) {
        return query(r) - query(l-1);
    }
};

// ---------- Segment Tree (Suma) ----------
struct SegmentTree {
    vector<ll> tree;
    int n;

    SegmentTree(const vector<ll>& arr) {
        n = arr.size();
        tree.resize(4*n);
        build(arr, 1, 0, n-1);
    }

    void build(const vector<ll>& arr, int node, int l, int r) {
        if(l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l+r)/2;
        build(arr, 2*node, l, mid);
        build(arr, 2*node+1, mid+1, r);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    void update(int node, int l, int r, int idx, ll val) {
        if(l == r) {
            tree[node] = val;
            return;
        }
        int mid = (l+r)/2;
        if(idx <= mid) update(2*node, l, mid, idx, val);
        else update(2*node+1, mid+1, r, idx, val);
        tree[node] = tree[2*node] + tree[2*node+1];
    }

    ll query(int node, int l, int r, int ql, int qr) {
        if(ql > r || qr < l) return 0;
        if(ql <= l && r <= qr) return tree[node];
        int mid = (l+r)/2;
        return query(2*node, l, mid, ql, qr) + 
               query(2*node+1, mid+1, r, ql, qr);
    }
};

// ==================== ALGORITMOS DE GRAFOS ====================

// ---------- BFS (Caminos mínimos en grafos no ponderados) ----------
vector<int> bfs(const vector<vi>& graph, int start) {
    int n = graph.size();
    vector<int> dist(n, -1);
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

// ---------- Dijkstra (Caminos mínimos con pesos) ----------
vector<ll> dijkstra(const vector<vector<pll>>& graph, int start) {
    int n = graph.size();
    vector<ll> dist(n, LLONG_MAX);
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while(!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if(d != dist[u]) continue;
        for(auto [v, w] : graph[u]) {
            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// ---------- Ordenamiento Topológico (DFS) ----------
vector<int> topologicalSort(const vector<vi>& graph) {
    int n = graph.size();
    vector<int> indegree(n, 0), order;
    for(int u = 0; u < n; u++)
        for(int v : graph[u]) indegree[v]++;
    queue<int> q;
    for(int u = 0; u < n; u++)
        if(indegree[u] == 0) q.push(u);
    while(!q.empty()) {
        int u = q.front(); q.pop();
        order.push_back(u);
        for(int v : graph[u]) {
            if(--indegree[v] == 0) 
                q.push(v);
        }
    }
    if(order.size() != n) return {}; // Hay ciclo
    return order;
}

// ==================== TÉCNICAS ADICIONALES ====================

// ---------- Binary Search (Sobre la respuesta) ----------
ll binary_search_answer(ll low, ll high, function<bool(ll)> check) {
    ll ans = -1;
    while(low <= high) {
        ll mid = low + (high - low)/2;
        if(check(mid)) {
            ans = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

// ---------- Two Pointers (Subarreglo con suma exacta) ----------
pii two_pointers(const vi& arr, int target) {
    int n = arr.size(), l = 0, r = 0, sum = 0;
    while(r < n) {
        sum += arr[r];
        while(sum > target) sum -= arr[l++];
        if(sum == target) return {l, r};
        r++;
    }
    return {-1, -1};
}

// ---------- Knapsack 0/1 (Versión básica) ----------
int knapsack(vi& values, vi& weights, int capacity) {
    int n = values.size();
    vector<vi> dp(n+1, vi(capacity+1, 0));
    for(int i = 1; i <= n; i++) {
        for(int w = 0; w <= capacity; w++) {
            if(weights[i-1] <= w)
                dp[i][w] = max(dp[i-1][w], values[i-1] + dp[i-1][w-weights[i-1]]);
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][capacity];
}

// ==================== FUNCIONES MATEMÁTICAS ====================

// ---------- Exponenciación Rápida ----------
ll fast_pow(ll base, ll exp) {
    ll result = 1;
    while(exp > 0) {
        if(exp & 1) result *= base;
        base *= base;
        exp >>= 1;
    }
    return result;
}

// ---------- Máximo Común Divisor (MCD) ----------
ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

// ---------- Mínimo Común Múltiplo (MCM) ----------
ll lcm(ll a, ll b) {
    return a * (b / gcd(a, b));
}

// ==================== MAIN (Ejemplo de uso) ====================
int main() {
    FAST_IO;
    
    // Ejemplo de uso rápido
    int n = 10;
    DSU dsu(n);
    dsu.unite(1, 2);
    dsu.unite(3, 4);
    cout << "DSU: " << dsu.find(1) << " " << dsu.find(3) << endl;

    FenwickTree fenw(n);
    fenw.update(1, 5);
    fenw.update(2, 3);
    cout << "Fenwick: " << fenw.range_query(1, 2) << endl;

    vector<ll> arr = {1, 3, 5, 7, 9};
    SegmentTree seg(arr);
    cout << "Segment Tree: " << seg.query(1, 0, 4, 1, 3) << endl;

    return 0;
}
