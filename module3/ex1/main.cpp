#include <iostream>

#include "CListGraph.cpp"
#include "CMatrixGraph.cpp"
#include "CSetGraph.cpp"
#include "CArcGraph.cpp"

int main() {
    CArcGraph graph(6);
    graph.AddEdge(0, 1);
    graph.AddEdge(2, 3);
    graph.AddEdge(1, 3);
    graph.AddEdge(3, 1);
    graph.AddEdge(4, 2);
    graph.AddEdge(5, 4);
    graph.AddEdge(2, 5);
    graph.AddEdge(3, 4);

    std::cout << "Vertices count = " << graph.VerticesCount() << std::endl;

    graph.Print(std::cout);
    std::cout << std::endl;
    graph.BFS(0);

    CSetGraph graph1(graph);
    graph1.BFS(0);
    return 0;
}