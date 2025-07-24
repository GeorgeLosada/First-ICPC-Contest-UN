#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
const int INF = 1e9;
const int MAXN = 100005;

//
// 1. BFS – Caminos más cortos sin peso
//
vector<int> bfs(int start, vector<vector<int>>& adj, int n) {
    vector<int> dist(n, -1);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    return dist;
}

//
// 2. DFS – Recorrido del grafo
//
void dfs(int u, vector<vector<int>>& adj, vector<bool>& vis) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) dfs(v, adj, vis);
    }
}

//
// 3. Dijkstra – Caminos más cortos con pesos positivos
//
vector<int> dijkstra(int start, vector<vector<pii>>& adj, int n) {
    vector<int> dist(n, INF);
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

//
// 4. Floyd-Warshall – Caminos más cortos entre todos los pares
//
void floyd(vector<vector<int>>& dist, int n) {
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] < INF && dist[k][j] < INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
}

//
// 5. Union-Find / DSU – Componentes conexas, ciclos
//
int parent[MAXN], sz[MAXN];

void dsu_init(int n) {
    for (int i = 0; i < n; ++i) parent[i] = i, sz[i] = 1;
}

int find(int x) {
    return (x == parent[x]) ? x : parent[x] = find(parent[x]);
}

bool unite(int a, int b) {
    a = find(a); b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    parent[b] = a;
    sz[a] += sz[b];
    return true;
}

//
// 6. Topological Sort – Ordenamiento de DAG
//
vector<int> top_sort(vector<vector<int>>& adj, int n) {
    vector<int> in(n, 0), res;
    for (int u = 0; u < n; ++u)
        for (int v : adj[u]) in[v]++;
    queue<int> q;
    for (int i = 0; i < n; ++i)
        if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        res.push_back(u);
        for (int v : adj[u])
            if (--in[v] == 0) q.push(v);
    }
    return res;
}
