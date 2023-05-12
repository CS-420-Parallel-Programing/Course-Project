#include "dijkstra.h"
#include <omp.h>
#include <queue>
#include <iostream>
#include "tools.h"
#include <mpi.h>

std::vector<int> dijkstra(const Graph& graph, int start_vertex) {
    int n = graph.get_size();
    std::vector<int> distances(n, std::numeric_limits<int>::max());
    std::vector<bool> visited(n, false);


    // The distance to itself is 0.
    distances[start_vertex] = 0;

    /**
     * @brief Use a priority queue to keep track of the unvisited vertices, because dijkstra's method need
     * to select the vertice with the minimal distance.
     * 
     * @tparam T The priority queue stores pairs of integers. The first integer is the current shorest path from the 
     * vertex whose ID is the second integer to the starting vertex. The second integer is the vertex ID.
     * 
     * @tparam Container We use a vector to store pairs of integers.
     * @tparam Compare Small values have higher priority.
     */
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq_;
    pq_.push({0, start_vertex});
    visited[start_vertex] = true;

    while (!pq_.empty()) {
        int current_vertex = pq_.top().second;
        pq_.pop();

        for (int i = 0; i < n; i++) {
            // If the i-th vertex is connected with the current vertex and it has not be visited yet, we push to the queue.
            int current_distance = graph.check(current_vertex, i);
            // Update distance first. The item be pushes is the updated one
            if (current_distance!= std::numeric_limits<int>::max()) {
                distances[i] = std::min(distances[i], distances[current_vertex] + current_distance);
            }

            if (graph.check(current_vertex, i) != std::numeric_limits<int>::max() && !visited[i]) {
                pq_.push({distances[i], i});
                visited[i] = true;
            }
        }
    }

    return distances;
}

std::vector<int> dijkstra_omp(const Graph& graph, int start_vertex) {
    int n = graph.get_size();
    std::vector<int> distances(n, std::numeric_limits<int>::max());
    std::vector<bool> visited(n, false);


    // The distance to itself is 0.
    distances[start_vertex] = 0;

    /**
     * @brief Use a priority queue to keep track of the unvisited vertices, because dijkstra's method need
     * to select the vertice with the minimal distance.
     * 
     * @tparam T The priority queue stores pairs of integers. The first integer is the current shorest path from the 
     * vertex whose ID is the second integer to the starting vertex. The second integer is the vertex ID.
     * 
     * @tparam Container We use a vector to store pairs of integers.
     * @tparam Compare Small values have higher priority.
     */
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq_;
    pq_.push({0, start_vertex});
    visited[start_vertex] = true;

    while (!pq_.empty()) {
        int current_vertex = pq_.top().second;
        pq_.pop();

        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            // If the i-th vertex is connected with the current vertex and it has not be visited yet, we push to the queue.
            int current_distance = graph.check(current_vertex, i);
            // Update distance first. The item be pushes is the updated one
            if (current_distance!= std::numeric_limits<int>::max()) {
                distances[i] = std::min(distances[i], distances[current_vertex] + current_distance);
            }

            if (graph.check(current_vertex, i) != std::numeric_limits<int>::max() && !visited[i]) {
                pq_.push({distances[i], i});
                visited[i] = true;
            }


        }
    }

    return distances;
}

std::vector<int> dijkstra_mpi( int start_vertex) {
    int kRank, kNumPes;
    int size;
    int range[2];
    MPI_Init(NULL, NULL);
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &kRank);
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &kNumPes);
    if(kRank == 0){
        Graph graph = getGraph();
        size = graph.get_size();
        int displs[kRank][2];
        int mod = size % kNumPes, num = size / kNumPes + (mod == 0 ? 0 : 1);
        for(int i = 0; i < kNumPes; i++){
            if(i == 0){
                displs[i][0] = 0;
                displs[i][1] = num -1;
            }else{
                if(i < kNumPes - mod){
                    displs[i][0] = displs[i-1][0] + num;
                    displs[i][1] = displs[i][0] + num - 1;
                }else{
                    displs[i][0] = displs[i-1][0] + num - 1;
                    displs[i][0] = displs[i][0] + num - 2;
                }
            }
        }
        MPI_Scatter(displs, 2, MPI_INT, range, 2, MPI_INT, 0, MPI_COMM_WORLD);
    }
    int begin = range[0], end = range[1];
    int localdis[end - begin + 1];
}