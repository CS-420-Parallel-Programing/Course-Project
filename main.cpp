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

    
    MPI_Init(NULL, NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    ts = clock();
    std::vector<int> mpiResult = dijkstra_mpi(graph, 2, rank, size);
    te = clock();
    
    MPI_Finalize();
    cout << "Total time (dijkstra MPI):" << (double)(te-ts)/CLOCKS_PER_SEC << endl;


    cout << "OMP parallel results are " << (nonResult == ompResult ? "correct!" : "false!");
    cout << "MPI parallel results are " << (nonResult == mpiResult ? "correct!" : "false!");
    return 0;
}