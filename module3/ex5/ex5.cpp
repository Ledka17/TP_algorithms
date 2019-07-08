#include <algorithm>
#include <iostream>
#include <vector>
#include <deque>
#include <map>
#include <stack>

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

    std::deque<std::pair<double, double> > Kruskal(std::deque<std::pair<double, std::pair<double, double> > > edges) {
        sort(edges.begin(), edges.end()); // сортируем ребра по весу
        // инициализируем лес деревьев
        std::deque<std::pair<double, double> > tree;
        double w = 0;
        while (not edges.empty()) { // пока в лесу не одно дерево
            int weight = edges.begin()->first;
            std::pair<double, double> edge = edges.begin()->second;
            edges.erase(edges.begin()); // последовательно рассматриваем все ребра графа

            int v1 = edge.first - 1, v2 = edge.second - 1;
            if (find_set(v1) != find_set(v2)) { // если ребро соединяет два разных дерева из леса
                union_set(v1, v2); // то объединяет это ребра в одно
                w += weight;
                tree.push_back(std::pair<double, double>(v1, v2));
            }
        }
        return tree;
    }

    int DFS(int start, std::vector<int> mark, std::deque<std::pair<int, int> > edges, std::vector<double> ran) {
        int ans = 0;
        std::stack<int> s;
        s.push(start);
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            for (int i = 0; i < edges[v].size(); ++i) {
                if (mark[edges[v][i]] == 0) {
                    s.push(edges[v][i]);
                    mark[edges[v][i]] = 1;
                    ans += ran[v] * ran[v] + ran[i] * ran[i];
                }
            }
        }
        return ans;
    }

    /*int Best(std::deque<std::pair<double, std::pair<int, int> > > edges, std::vector<double> ran) {
        std::vector<int> mark(size, 0);

    }*/

    int Optimal(std::deque<std::pair<double, std::pair<int, int> > > edges, std::vector<double> ran) {
        std::vector<int> mark(size, 0);
        return DFS(0, mark, edges, ran);
    }
private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;
    int size;

    friend std::ostream& operator <<(std::ostream &out, DSU &dsu);
};
