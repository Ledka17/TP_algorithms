#include "CSetGraph.hpp"

#include <assert.h>
#include <iostream>
#include <vector>

CSetGraph::CSetGraph(size_t vertices_count)
        : vertices_count_(vertices_count),
          in_(vertices_count_),
          out_(vertices_count_) {}

CSetGraph::CSetGraph(const IGraph &graph)
    : vertices_count_(graph.VerticesCount()),
      in_(vertices_count_),
      out_(vertices_count_)
    {
        for (int i = 0; i < vertices_count_; i++) {
            std::vector<int> vertices;
            graph.GetNextVertices(i, vertices);
            for (int j : vertices)
                AddEdge(i, j);
        }
    }

void CSetGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < VerticesCount());
    assert(to >= 0 && to < VerticesCount());

    out_[from].insert(to);
    in_[to].insert(from);
}

void CSetGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < VerticesCount());

    for (int i : out_[vertex]) {
        vertices.push_back(i);
    }
}

void CSetGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < VerticesCount());

    for (int i : in_[vertex]) {
        vertices.push_back(i);
    }
}

void CSetGraph::Print(std::ostream& out) {
    out << "In edges" << std::endl;
    for (int i = 0; i < VerticesCount(); ++i) {
        for (int j : in_[i]) {
            out << j << " ";
        }
        out << std::endl;
    }
}

void CSetGraph::BFS(int from) {
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