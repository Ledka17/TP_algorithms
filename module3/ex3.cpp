#include <iostream>
#include <vector>
#include <list>
#include <set>

typedef std::pair<unsigned, unsigned> pair_vw;
const unsigned INFINITY = 4247000000;

class CArcGraph {
public:
    explicit CArcGraph(size_t vertices_count);

    void AddEdge(unsigned from, unsigned to, unsigned weight);

    size_t VerticesCount() { return vertices_count_; }
    int Dijkstra(unsigned from, unsigned to);

    void GetNextVertices(unsigned vertex, std::vector<pair_vw> &vertices);

    void Print(std::ostream &out);

private:
    size_t vertices_count_;
    std::vector<std::list<pair_vw> > edges_;
};

CArcGraph::CArcGraph(size_t vertices_count)
        : vertices_count_(vertices_count),
          edges_(vertices_count, std::list<pair_vw>() ) {}

void CArcGraph::AddEdge(unsigned from, unsigned to, unsigned weight) {
    edges_[from].push_back(pair_vw(to, weight) );
    edges_[to].push_back(pair_vw(from, weight) );
}

void CArcGraph::GetNextVertices(unsigned vertex, std::vector<pair_vw>& vertices) {
    vertices.clear();
    for (pair_vw i : edges_[vertex]) {
        vertices.push_back(i);
    }
}

int CArcGraph::Dijkstra(unsigned from, unsigned to) {
    std::vector<int> d(vertices_count_, INFINITY); // инициализируем массив расстояний очень большими числами

    d[from] = 0; // помечаем в массиве расстояний from 0
    std::set<pair_vw> q; // инициализируем очередь с приоритетом <вес, вершина>
    q.insert(std::pair<unsigned, unsigned>(d[from], from)); // кладем в очередь текущее расстояние и вершину

    while ( !q.empty() ) { // пока очередь не пуста делаем
        unsigned u = ( q.begin() )->second;
        q.erase(q.begin()); // достаем из очереди вершину

        std::vector<pair_vw> vertices;
        GetNextVertices(u, vertices);
        for (pair_vw vertex : vertices) { // для всех следующих после этой вершин
            unsigned v = vertex.first, weight = vertex.second;
            if (d[v] > d[u] + weight) { // если лежащее расстояние > расстояние родителя + вес (сюда входит и очень большое)
                if (d[v] != INFINITY) // если лежащее расстояние не большое
                    q.erase(std::pair<unsigned, unsigned>(d[v], v)); // удаляем его из очереди (так как его изменят)
                d[v] = d[u] + weight;
                q.insert(std::pair<unsigned, unsigned>(d[v], v));
            }
        }
    }

    return d[to] != INFINITY ? d[to] : -1; // возвращаем из массива длину пути к to
}


int main() {
    std::ios::sync_with_stdio(false); // оптимизация ввода

    unsigned V = 0, E = 0;
    std::cin >> V >> E;
    CArcGraph graph(V);

    for (unsigned i = 0; i < E; i++) {
        unsigned from = 0, to = 0, weight = 0;
        std::cin >> from >> to >> weight;
        graph.AddEdge(from, to, weight);
    }

    unsigned u = 0, w = 0;
    std::cin >> u >> w;
    std::cout << graph.Dijkstra(u, w) << std::endl;
    return 0;
}