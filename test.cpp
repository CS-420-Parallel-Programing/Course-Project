#include <iostream>
#include <vector>
#include <cassert>
#include "graph.h"
#include "dijkstra.h"


void test_graph() {
    // Test a small graph
    Graph graph(4);
    // Test size of the graph
    assert(graph.get_size() == 4);

    // Test adding vertices
    bool add0 = graph.add_edge(0, 1, 10);
    bool add1 = graph.add_edge(1, 2, 5);
    bool add2 = graph.add_edge(2, 3, 7);

    assert(graph.check(0, 1) == 10 && add0 == true);
    assert(graph.check(1, 2) == 5 && add1 == true);
    assert(graph.check(2, 3) == 7 && add2 == true);
    

    // Adding negative distances is not allowed
    bool d_add0 = graph.add_edge(0, 1, -5);
    assert(d_add0 == false);

    // Examine disconnected graph
    assert(graph.check(1, 3) == std::numeric_limits<int>::max());
    assert(graph.check(0, 3) == std::numeric_limits<int>::max());


    std::cout<< "Graph initialization tests all passed!" << std::endl;
}

void test_nonparallel_dijkstra() {
    Graph graph(5);

    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 3, 10);
    graph.add_edge(0, 4, 1);
    graph.add_edge(1, 2, 5);
    graph.add_edge(2, 3, 3);
    graph.add_edge(3, 4, 5);

    // Test the distance with 0 as starting vertex
    std::vector<int> expected_distances = {0, 10, 9, 6, 1};
    std::vector<int> test_distances = dijkstra(graph, 0);

    assert(expected_distances == test_distances);

    std::cout<< "Dijksdra's method tests all passed!" << std::endl;
}


int main() {
    test_graph();
    test_nonparallel_dijkstra();

    return 0;
}