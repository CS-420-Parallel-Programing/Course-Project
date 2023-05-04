#include "dijkstra.h"
#include <queue>
#include <iostream>

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



std::vector<int> dijkstra_mpi(const Graph& graph, int start_vertex) {
    // Total number of processes
    int world_size;
    // The rank of the current process
    int world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int n = graph.get_size();
    int rows_per_process = n / world_size;
    int remaining_rows = n % world_size;

    // Count the number of rows sent and displacement
    std::vector<int> send_counts(world_size);
    std::vector<int> displacement(world_size);
    int offset = 0;

    for (int i = 0; i < world_size; i++) {
        // If the index of process is smaller than i, allocates one more row. Then, all remaining rows will be allocated.
        send_counts[i] = (rows_per_process + (i < remaining_rows ? 1: 0)) * n;
        displacement[i] = offset;
        offset += send_counts[i];
    }


    /**
     * @todo:
     * 1. Need to consider how to divide the big task to small tasks.
     * 2. Consider corner cases like, vertices are not connected within a subgraph that is allcoated to a process.
     */
}