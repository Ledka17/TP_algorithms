#pragma once

#include <ostream>
#include <vector>
#include <unordered_set>

#include "graph.hpp"

using std::unordered_set;

class CSetGraph : public IGraph {
public:
    explicit CSetGraph(size_t vertices_count);
    CSetGraph(const IGraph& graph);

    void AddEdge(int from, int to) override;

    size_t VerticesCount() const override { return vertices_count_; }

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;
    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

    void Print(std::ostream& out);
    void BFS(int from);

private:
    size_t vertices_count_;
    std::vector<std::unordered_set<int> >    out_;
    std::vector<std::unordered_set<int> >    in_;
};