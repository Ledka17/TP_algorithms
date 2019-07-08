#include "CListGraph.hpp"

#include <assert.h>
#include <iostream>
#include <vector>
#include <queue>

CListGraph::CListGraph(size_t vertices_count)
        : out_edges_(vertices_count),
          in_edges_(vertices_count) {}

CListGraph::CListGraph(const IGraph& graph)
        : in_edges_(graph.VerticesCount()),
        out_edges_(graph.VerticesCount())
{
    for(int i = 0; i < VerticesCount(); i++){
        std::vector<int> vertices;
        graph.GetNextVertices(i, vertices);
        for(int j : vertices)
            AddEdge(i, j);
    }
}

void CListGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < VerticesCount());
    assert(to >= 0 && to < VerticesCount());

    out_edges_[from].push_back(to);
    in_edges_[to].push_back(from);
}

void CListGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < VerticesCount());
    vertices = out_edges_[vertex];
}

void CListGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < VerticesCount());
    vertices = in_edges_[vertex];
}

void CListGraph::Print(std::ostream& out) {
    out << "Out_edges" << std::endl;
    for (int i = 0; i < out_edges_.size(); ++i) {
        out << i << ": ";
        for (int out_target : out_edges_[i]) {
            out << out_target << " ";
        }
        out << std::endl;
    }
}

void CListGraph::BFS(int from) {
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