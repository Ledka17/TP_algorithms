#pragma once

#include <ostream>
#include <vector>

#include "graph.hpp"

class CArcGraph : public IGraph {
public:
    explicit CArcGraph(size_t vertices_count);
    CArcGraph(const IGraph& graph);

    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override { return vertices_count_; }

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

    void Print(std::ostream& out);
    void BFS(int from);

private:
    struct Edge {
        Edge(int from, int to);
        int from;
        int to;
    };

    size_t vertices_count_;
    std::vector<Edge> edges_;
};