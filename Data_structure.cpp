#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    // VECTOR
    vector<int> v = {5, 2, 9};
    v.push_back(4); // Añadir al final
    sort(v.begin(), v.end()); // Ordenar

    // STACK (LIFO)
    stack<int> st;
    st.push(10);
    st.push(20);
    st.pop(); // Quita el 20

    // QUEUE (FIFO)
    queue<int> q;
    q.push(1);
    q.push(2);
    q.pop(); // Quita el 1

    // DEQUE (doble cola)
    deque<int> d;
    d.push_back(5);
    d.push_front(3);
    d.pop_back(); // Quita el 5

    // PRIORITY QUEUE (máximos por defecto)
    priority_queue<int> pq;
    pq.push(4);
    pq.push(10);
    pq.pop(); // Quita el 10

    // PRIORITY QUEUE MIN-HEAP
    priority_queue<int, vector<int>, greater<int>> minpq;
    minpq.push(4);
    minpq.push(10);
    minpq.pop(); // Quita el 4

    // SET (conjunto ordenado, sin duplicados)
    set<int> s = {3, 1, 4};
    s.insert(2);
    s.erase(3); // Borra el 3

    // MULTISET (permite duplicados)
    multiset<int> ms;
    ms.insert(1);
    ms.insert(1);

    // MAP (clave-valor ordenado)
    map<string, int> m;
    m["peras"] = 3;
    m["manzanas"] = 5;

    // UNORDERED MAP (hash, sin orden)
    unordered_map<int, int> um;
    um[10] = 100;
    um[3] = 15;

    // BITSET (uso de bits como bools)
    bitset<8> b; // 00000000
    b[1] = 1;    // 00000010
    b.flip();    // 11111101

    // OUTPUT EJEMPLO
    cout << "Vector ordenado: ";
    for (int x : v) cout << x << " ";
    cout << "\nTop de stack: " << st.top();
    cout << "\nFrente de queue: " << q.front();
    cout << "\nMayor en priority_queue: " << pq.top();
    cout << "\nMenor en min-heap: " << minpq.top();
    cout << "\nContenido del set: ";
    for (int x : s) cout << x << " ";
    cout << "\nCantidad de 'peras': " << m["peras"];
    cout << "\nbitset actual: " << b << "\n";

    return 0;
}
