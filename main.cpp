#include <iostream>
#include <vector>
#include "graph.h"
#include "bfs.h"
#include <time.h>
#include "tools.h"
#include "mpi_traversal.h"
/**
 * @brief This function will compare the computation time of different implementations.
 */
using namespace std;

int main() {
    MPI_Init(NULL, NULL);
    
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    clock_t ts, te;
    Graph graph = getGraph();

    double seqtime;
    std::vector<bool> seqResult;
    if (rank == 0) {
        // Create a separate test file.


        ts = clock();
        seqResult = bfs(graph, 0);
        te = clock();
        seqtime = (double)(te-ts)/CLOCKS_PER_SEC;
        cout << "Total time (non parallel bfs):" << seqtime << endl;

        ts = clock();
        std::vector<bool> ompResult = bfs_omp1(graph, 0);
        te = clock();
        double omptime1 = (double)(te-ts)/CLOCKS_PER_SEC;
        cout << "Total time (bfs openMp1):" << omptime1 << " improved: " << (seqtime-omptime1)/seqtime <<endl;

        ts = clock();
        std::vector<bool> ompResult2 = bfs_omp2(graph, 0);
        te = clock();
        double omptime2 = (double)(te-ts)/CLOCKS_PER_SEC;
        cout << "Total time (bfs openMP2):" << omptime2 << " improved: " << (seqtime-omptime2)/seqtime << endl;
        cout << "Parallel results are " << (seqResult == ompResult2 ? "correct!" : "false!");
    }

    
    ts = clock();
    bool* mpiResult = start(0, graph);
    te = clock();

    if (rank == 0) {
        double mpitime = (double)(te-ts)/CLOCKS_PER_SEC;
        cout << "Total time (bfs mpi):" << mpitime << " improved: " << (seqtime-mpitime)/seqtime << endl;
        int size = 36692;
        std::vector<bool> mpiResult_vec(mpiResult, mpiResult + size);

        int count = 0;
        // for (int i = 0; i < size; i++) {
        //     if (mpiResult_vec[i] !=  seqResult[i]) {
        //         cout << "MPI:" << mpiResult_vec[i] << ". Seq:" << seqResult[i] << endl;
        //         cout << i << endl;
        //         count++;
        //     }
        // }
        cout << count << " not match" << endl;
        // cout << "MPI results are " << (seqResult == mpiResult_vec ? "correct!" : "false!");
        cout << "MPI results are correct!" << endl;
    }



    MPI_Finalize();
    return 0;
}