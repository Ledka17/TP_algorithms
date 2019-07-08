#pragma once

#include <ostream>

#include "graph.hpp"

class CListGraph : public IGraph {
public:
    explicit CListGraph(size_t vertices_count);
    CListGraph(const IGraph& graph);

    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override { return out_edges_.size(); }

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

    void Print(std::ostream& out);

    void BFS(int from);

private:
    std::vector<std::vector<int> > out_edges_;
    std::vector<std::vector<int> > in_edges_;
};