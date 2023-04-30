#include <iostream>
#include <vector>
#include "graph.h"
#include "bfs.h"

int main() {
    // Test with a graph with 6 vertices
    Graph graph(6);

    // Add edges with distances
    graph.add_edge(0, 1, 7);
    // std::cout << "Distance between vertex 0 and 1: " << graph.check(0, 1) << std::endl;
    graph.add_edge(0, 2, 9);
    graph.add_edge(1, 3, 15);
    graph.add_edge(1, 4, 5);
    graph.add_edge(2, 5, 2);

    int start_vertex = 0;

    std::vector<int> distances = bfs(graph, start_vertex);
    for (int i = 0; i < graph.get_size(); i++) {
        std::cout << "Vertex " << i << ": ";
        if (distances[i] == -1) {
            std::cout << "Not connected\n";
        } else {
            std::cout << distances[i] << '\n';
        }
    }

    return 0;
}