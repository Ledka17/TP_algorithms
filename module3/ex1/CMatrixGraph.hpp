#pragma once

#include <ostream>
#include <vector>

#include "graph.hpp"

class CMatrixGraph : public IGraph {
public:
    explicit CMatrixGraph(size_t vertices_count);
    CMatrixGraph(const IGraph& graph);

    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override { return vertices_count_; }

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

    void Print(std::ostream& out);
    void BFS(int from);

private:
    size_t vertices_count_;
    std::vector<std::vector<bool> > edges_;
};