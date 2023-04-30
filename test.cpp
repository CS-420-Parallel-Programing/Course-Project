#include <iostream>
#include <vector>
#include <cassert>
#include "graph.h"
#include "bfs.h"


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
    

    // Duplicated adding is not allowed
    bool d_add0 = graph.add_edge(0, 1, 5);
    assert(d_add0 == false);

    // Examine disconnected graph
    assert(graph.check(1, 3) == -1);
    assert(graph.check(0, 3) == -1);


    std::cout<< "Graph initialization tests all passed!" << std::endl;
}

void test_nonparallel_bfs() {
    Graph graph(5);

    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 3, 10);
    graph.add_edge(0, 4, 1);
    graph.add_edge(1, 2, 5);
    graph.add_edge(2, 3, 3);
    graph.add_edge(3, 4, 5);

    // Test the distance with 0 as starting vertex
    std::vector<int> expected_distances = {0, 10, 13, 6, 1};
    std::vector<int> test_distances = bfs(graph, 0);

    assert(expected_distances == test_distances);
}


int main() {
    test_graph();
    test_nonparallel_bfs();

    return 0;
}