#include <iostream>
#include <vector>
#include <queue>
#include <list>

class CSetGraph {
public:
    explicit CSetGraph(size_t vertices_count);

    void AddEdge(int from, int to);

    size_t VerticesCount() { return vertices_count_; }
    int KMinPath(int from, int to);

    void GetNextVertices(int vertex, std::vector<int> &vertices);

    void Print(std::ostream &out);

private:
    size_t vertices_count_;
    std::vector <std::list<int> > out_;
};

CSetGraph::CSetGraph(size_t vertices_count)
        : vertices_count_(vertices_count),
          out_(vertices_count_) {}

void CSetGraph::AddEdge(int from, int to) {
    for (int i : out_[from]) // проверка, если ребро уже есть
        if (i == to)
            return;

    out_[from].push_back(to);
    out_[to].push_back(from);
}

void CSetGraph::GetNextVertices(int vertex, std::vector<int>& vertices) {
    for (int i : out_[vertex]) {
        vertices.push_back(i);
    }
}

void CSetGraph::Print(std::ostream& out) {
    out << "In edges" << std::endl;
    for (int i = 0; i < VerticesCount(); ++i) {
        for (int j : out_[i]) {
            out << j << " ";
        }
        out << std::endl;
    }
}

int CSetGraph::KMinPath(int from, int to) {
    std::vector<int> d(vertices_count_, 0); // инициализируем массив расстояний очень большими числами
    // инициализируем массив родителей -1
    std::vector<int> k_min(vertices_count_, 0); // инициализируем массив количества мин путей 0

    k_min[from] = 1; // помечаем в массиве расстояний from 0
    std::queue<int> q; // инициализируем очередь
    q.push(from); // кладем в очередь текущую вершину

    while ( !q.empty() ) { // пока очередь не пуста делаем
        int u = q.front();
        q.pop(); // достаем из очереди вершину

        std::vector<int> vertices;
        GetNextVertices(u, vertices);
        for (int v : vertices) { // для всех следующих после этой вершин
            if (k_min[v] == 0) { // если лежащее расстояние большое
                d[v] = d[u] + 1; // то присваиваем расстоянию расстояние отца + 1
                // то в массив родителей заполняем родителя этой вершины
                k_min[v] = k_min[u]; // то в массив минимальных путей записываем мин путь родителя
                q.push(v); // помещаем вершину в очередь
            }
            else if (d[v] == d[u] + 1) // если лежащее расстояние = расстояние родителя + 1
                k_min[v] += k_min[u]; // то в массив минимальных путей добавляем мин расстояние родителя
        }
    }

    return k_min[to]; // возвращаем из массива количества мин путей to
}


int main() {
    int V = 0, E = 0;
    std::cin >> V >> E;
    CSetGraph graph(V);

    for (int i = 0; i < E; i++) {
        int from = 0, to = 0;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }

    int u = 0, w = 0;
    std::cin >> u >> w;
    std::cout << graph.KMinPath(u, w) << std::endl;
    //graph.Print(std::cout);
    return 0;
}