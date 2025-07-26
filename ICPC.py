from collections import deque, defaultdict
import heapq
import sys
import math
import bisect

sys.setrecursionlimit(10**6)
input = sys.stdin.readline

# -------------------------- ESTRUCTURAS DE DATOS --------------------------
class DisjointSet:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
        
    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]
    
    def union(self, x, y):
        px, py = self.find(x), self.find(y)
        if px == py: return False
        if self.rank[px] < self.rank[py]:
            px, py = py, px
        self.parent[py] = px
        self.rank[px] += (self.rank[px] == self.rank[py])
        return True

class FenwickTree:
    def __init__(self, size):
        self.n = size
        self.tree = [0] * (self.n + 1)
    
    def update(self, index, delta):
        while index <= self.n:
            self.tree[index] += delta
            index += index & -index
    
    def query(self, index):
        s = 0
        while index:
            s += self.tree[index]
            index -= index & -index
        return s

# -------------------------- ALGORITMOS DE GRAFOS --------------------------
def bfs(graph, start, n):
    dist = [-1] * n
    queue = deque([start])
    dist[start] = 0
    while queue:
        u = queue.popleft()
        for v in graph[u]:
            if dist[v] == -1:
                dist[v] = dist[u] + 1
                queue.append(v)
    return dist

def dijkstra(graph, start, n):
    dist = [10**18] * n
    heap = [(0, start)]
    dist[start] = 0
    while heap:
        d, u = heapq.heappop(heap)
        if d != dist[u]: continue
        for v, w in graph[u]:
            nd = d + w
            if nd < dist[v]:
                dist[v] = nd
                heapq.heappush(heap, (nd, v))
    return dist

def topological_sort(graph, n):
    indegree = [0] * n
    for u in range(n):
        for v in graph[u]:
            indegree[v] += 1
    queue = deque(i for i in range(n) if indegree[i] == 0)
    order = []
    while queue:
        u = queue.popleft()
        order.append(u)
        for v in graph[u]:
            indegree[v] -= 1
            if indegree[v] == 0:
                queue.append(v)
    return order if len(order) == n else None

# -------------------------- TÉCNICAS AVANZADAS --------------------------
def knapsack(values, weights, capacity):
    n = len(values)
    dp = [0] * (capacity + 1)
    for i in range(n):
        for w in range(capacity, weights[i] - 1, -1):
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i])
    return dp[capacity]

def binary_search_answer(low, high, condition):
    while low < high:
        mid = (low + high) // 2
        if condition(mid):
            high = mid
        else:
            low = mid + 1
    return low

def two_pointers(arr, target):
    n = len(arr)
    left = curr_sum = 0
    for right in range(n):
        curr_sum += arr[right]
        while curr_sum > target:
            curr_sum -= arr[left]
            left += 1
        if curr_sum == target:
            return (left, right)
    return (-1, -1)

# -------------------------- MATEMÁTICAS --------------------------
def sieve(n):
    is_prime = [True] * (n + 1)
    is_prime[0] = is_prime[1] = False
    for i in range(2, int(math.sqrt(n)) + 1):
        if is_prime[i]:
            for j in range(i * i, n + 1, i):
                is_prime[j] = False
    return [i for i in range(n + 1) if is_prime[i]]

def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    gcd, x1, y1 = extended_gcd(b, a % b)
    x = y1
    y = x1 - (a // b) * y1
    return gcd, x, y

# -------------------------- EJEMPLOS DE USO --------------------------
def main():
    # Leer entrada rápida
    n, m = map(int, input().split())
    
    # Ejemplo de BFS
    graph = [[] for _ in range(n)]
    for _ in range(m):
        u, v = map(int, input().split())
        graph[u].append(v)
        graph[v].append(u)
        
    dist = bfs(graph, 0, n)
    print("Distancias BFS:", dist)
    
    # Ejemplo de DSU
    dsu = DisjointSet(n)
    dsu.union(0, 1)
    dsu.union(2, 3)
    print("Conectividad DSU:", dsu.find(0) == dsu.find(1))
    
    # Ejemplo de Dijkstra
    weighted_graph = [[] for _ in range(n)]
    for _ in range(m):
        u, v, w = map(int, input().split())
        weighted_graph[u].append((v, w))
        weighted_graph[v].append((u, w))
        
    dist_dijkstra = dijkstra(weighted_graph, 0, n)
    print("Distancias Dijkstra:", dist_dijkstra)

if __name__ == "__main__":
    main()
