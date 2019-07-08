#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
//#include <stack>
//#include <set>

class DSU {
public:
    DSU(size_t size)
    : parent(size), rank(size, 1), size(size)
    {
        for (int i = 0; i < size; i++)
            parent[i] = i;
    }

    size_t find_set(size_t u) {
        if (u == parent[u])
            return u;
        return parent[u] = find_set(parent[u]);
    }

    void union_set(size_t u, size_t v) {
        u = find_set(u);
        v = find_set(v);

        if (u != v) {
            if (rank[u] < rank[v])
                std::swap(u, v);
            parent[v] = u;
            rank[u] += rank[v];
        }
    }

    bool has_one_tree() {
        int par = parent[0];
        for (size_t i = 1; i < size; i++) {
            if (parent[i] != par)
                return false;
        }
        return true;
    }

    int Kruskal(std::deque<std::pair<int, std::pair<int, int> > > edges) {
        sort(edges.begin(), edges.end()); // сортируем ребра по весу
        // инициализируем лес деревьев
        int w = 0;
        while (not edges.empty()) { // пока в лесу не одно дерево
            int weight = edges.begin()->first;
            std::pair<int, int> edge = edges.begin()->second;
            edges.erase(edges.begin()); // последовательно рассматриваем все ребра графа

            int v1 = edge.first - 1, v2 = edge.second - 1;
            if (find_set(v1) != find_set(v2)) { // если ребро соединяет два разных дерева из леса
                union_set(v1, v2); // то объединяет это ребра в одно
                w += weight;
            }
        }
        return w;
    }
private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;
    int size;

    friend std::ostream& operator <<(std::ostream &out, DSU &dsu);
};

/*std::ostream& operator <<(std::ostream &out, DSU &dsu) {
    std::map<size_t, std::vector<size_t> > sets;
    for (auto i = 0; i < dsu.parent.size(); i++) {
        sets[dsu.find_set(i)].push_back(i);
    }

    for (auto &kv : sets) {
        out << kv.first << "; ";
        for (auto j = 0; j < kv.second.size(); j++) {
            out << kv.second[j];
            if (j != kv.second.size() - 1)
                out << ", ";
            else
                out << std::endl;
        }
    }
    return out;
}*/


int main() {
    std::ios::sync_with_stdio(false); // оптимизация ввода

    int V = 0, E = 0;
    std::cin >> V >> E;
    DSU dsu(V);

    std::deque<std::pair<int, std::pair<int, int> > > edges;
    for (int i = 0; i < E; i++) {
        int v1 = 0, v2 = 0, w = 0;
        std::cin >> v1 >> v2 >> w;
        std::pair<int, int> edge(v1, v2);
        edges.push_back(std::pair<int, std::pair<int, int> >(w, edge));
    }
    std::cout << dsu.Kruskal(edges) << std::endl;

    return 0;
}