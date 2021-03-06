#include "CMatrixGraph.hpp"

#include <assert.h>
#include <iostream>
#include <vector>

CMatrixGraph::CMatrixGraph(size_t vertices_count)
        : vertices_count_(vertices_count),
        edges_(vertices_count_) {
    for(std::vector<bool> &i : edges_)
        i.assign(vertices_count_, false);
}

CMatrixGraph::CMatrixGraph(const IGraph &graph)
        : vertices_count_(graph.VerticesCount()),
        edges_(vertices_count_) {
    for (std::vector<bool> &i : edges_)
        i.assign(vertices_count_, false);

    for (int i = 0; i < vertices_count_; i++) {
        std::vector<int> vertices;
        graph.GetNextVertices(i, vertices);
        for (int j : vertices)
            AddEdge(i, j);
    }
}

void CMatrixGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < VerticesCount());
    assert(to >= 0 && to < VerticesCount());

    edges_[from][to] = true;
}

void CMatrixGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < VerticesCount());

    for (int i = 0; i < vertices_count_; i++) {
        if ( edges_[vertex][i] )
            vertices.push_back(i);
    }
}

void CMatrixGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < VerticesCount());

    for (int i = 0; i < vertices_count_; i++) {
        if ( edges_[i][vertex] )
            vertices.push_back(i);
    }
}

void CMatrixGraph::Print(std::ostream& out) {
    for (int i = 0; i < VerticesCount(); ++i) {
        for (int j = 0; j < VerticesCount(); ++j) {
            out << edges_[i][j] << " ";
        }
        out << std::endl;
    }
}

void CMatrixGraph::BFS(int from) {
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