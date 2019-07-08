#include "CArcGraph.hpp"

#include <assert.h>
#include <iostream>
#include <vector>

CArcGraph::CArcGraph(size_t vertices_count)
        : vertices_count_(vertices_count),
          edges_() {}

CArcGraph::CArcGraph(const IGraph& graph):
        vertices_count_(graph.VerticesCount()) {
    for (int i = 0; i < vertices_count_; i++) {
        std::vector<int> vertices;
        graph.GetNextVertices(i, vertices);
        for(int j : vertices)
            AddEdge(i, j);
    }
}

void CArcGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < VerticesCount());
    assert(to >= 0 && to < VerticesCount());

    Edge new_edge(from, to);
    edges_.push_back(new_edge);
}

void CArcGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < VerticesCount());

    for (const Edge &i : edges_) {
        if ( i.from == vertex )
            vertices.push_back(i.to);
    }
}

void CArcGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < VerticesCount());

    for (const Edge &i  : edges_) {
        if ( i.to == vertex )
            vertices.push_back(i.from);
    }
}

void CArcGraph::Print(std::ostream& out) {
    for (const Edge &i  : edges_) {
        out << i.from << " " << i.to << std::endl;
    }
}

CArcGraph::Edge::Edge(int from, int to):
        from(from),
        to(to) {}

void CArcGraph::BFS(int from) {
    std::queue<int> q;
    q.push(from);
    std::vector<int> d(VerticesCount(), 50000), p(VerticesCount(), -1);
    d[from] = 0;
    while ( !q.empty() ) {
        int v = q.front();
        q.pop();

        std::vector<int> vertices;
        GetNextVertices(v, vertices);
        for (int to : vertices) {
            if (d[to] == 50000) {
                q.push(to);
                d[to] = d[v] + 1;
                p[to] = v;
            }
        }
    }

    std::cout << "BFS: ";
    for (int i = 0; i < VerticesCount(); i++) {
        for (int u = 0; u < VerticesCount(); u++)
            if (d[u] == i)
                std::cout << u << " ";
    }
    std::cout << std::endl;
}
