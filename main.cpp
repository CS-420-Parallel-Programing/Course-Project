#include <iostream>
#include <vector>
#include "graph.h"
#include "dijkstra.h"
#include <time.h>
#include "tools.h"
/**
 * @brief This function will compare the computation time of different implementations.
 */
using namespace std;

int main() {
    // Create a separate test file.
    clock_t ts, te;
    Graph graph = getGraph();

    ts = clock();
    std::vector<int> nonResult = dijkstra(graph, 2);
    te = clock();
    cout << "Total time (non parallel dijkstra):" << (double)(te-ts)/CLOCKS_PER_SEC << endl;

    ts = clock();
    std::vector<int> ompResult = dijkstra_omp(graph, 2);
    te = clock();
    cout << "Total time (dijkstra openMp):" << (double)(te-ts)/CLOCKS_PER_SEC << endl;

    cout << "Parallel results are " << (nonResult == ompResult ? "correct!" : "false!");
    return 0;
}