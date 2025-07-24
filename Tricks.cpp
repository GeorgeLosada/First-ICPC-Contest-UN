#include <bits/stdc++.h>
using namespace std;

// Ordenar con pares
void ordenar_pares() {
    vector<pair<int, int>> a = {{2, 3}, {1, 4}, {2, 1}, {1, 2}};
    sort(a.begin(), a.end()); // ordena por first, luego por second
    for (auto [x, y] : a)
        cout << "(" << x << "," << y << ") ";
    cout << "\n";
}

// Ordenar con lambda (ejemplo: ordenar por suma de par)
void ordenar_lambda() {
    vector<pair<int, int>> a = {{2, 3}, {1, 4}, {2, 1}, {1, 2}};
    sort(a.begin(), a.end(), [](pair<int, int> p1, pair<int, int> p2) {
        return p1.first + p1.second < p2.first + p2.second;
    });
    for (auto [x, y] : a)
        cout << "(" << x << "," << y << ") ";
    cout << "\n";
}

// Binary Search
void busqueda_binaria() {
    vector<int> a = {1, 3, 3, 3, 5, 7, 8};
    int x = 3;
    int lb = lower_bound(a.begin(), a.end(), x) - a.begin(); // primera posición ≥ x
    int ub = upper_bound(a.begin(), a.end(), x) - a.begin(); // primera posición > x
    cout << "lower_bound: " << lb << "\n"; // debe ser 1
    cout << "upper_bound: " << ub << "\n"; // debe ser 4
    cout << "Frecuencia: " << (ub - lb) << "\n";
}

// Fast IO
void fast_io() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    // Ya puedes usar cin y cout mucho más rápido
}

// Hashing básico (unordered_map)
void hashing() {
    unordered_map<string, int> freq;
    vector<string> words = {"apple", "banana", "apple", "apple", "banana", "pear"};
    for (auto& word : words) freq[word]++;
    for (auto& [word, count] : freq)
        cout << word << ": " << count << "\n";
}

// Sliding window: suma máxima en ventana de tamaño k
void sliding_window() {
    vector<int> a = {1, 3, 2, 5, 1, 1, 7};
    int k = 3, sum = 0, max_sum = 0;
    for (int i = 0; i < k; i++) sum += a[i];
    max_sum = sum;
    for (int i = k; i < a.size(); i++) {
        sum += a[i] - a[i - k];
        max_sum = max(max_sum, sum);
    }
    cout << "Max suma en ventana de tamaño " << k << ": " << max_sum << "\n";
}

int main() {
    cout << "--- Ordenar pares ---\n";
    ordenar_pares();

    cout << "--- Ordenar con lambda ---\n";
    ordenar_lambda();

    cout << "--- Búsqueda binaria ---\n";
    busqueda_binaria();

    cout << "--- Hashing básico ---\n";
    hashing();

    cout << "--- Sliding window ---\n";
    sliding_window();

    return 0;
}
