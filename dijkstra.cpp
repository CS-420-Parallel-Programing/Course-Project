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

std::vector<int> dijkstra_mpi(int start_vertex) {
    int kRank, kNumPes;
    int size;
    int range[2];
    Graph graph = getGraph();
    MPI_Init(NULL, NULL);
    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &kRank);
    // Get the number of processes
    MPI_Comm_size(MPI_COMM_WORLD, &kNumPes);
    if(kRank == 0){
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
    return dijkstra_local(graph, 0, begin, end, kRank);
    
}

std::vector<int> dijkstra_local(const Graph& graph, int start_vertex, int begin, int end, int kRank) {
    int n = graph.get_size();
    int num = end - begin + 1;
    std::vector<int> local_distances(num, std::numeric_limits<int>::max());
    std::vector<bool> visited(num, false);
    std::vector<int> global_distances;
    if(kRank == 0){
        global_distances.resize(n, std::numeric_limits<int>::max());
    }

    // The distance to itself is 0.
    local_distances[start_vertex] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq_;
    pq_.push({0, start_vertex});
    visited[start_vertex] = true;
    int global_closest_vertex = start_vertex;
    while (!pq_.empty()) {
        int current_vertex = pq_.top().second, current_distance = local_distances[current_vertex];
        int local_closest_pair[2] = {local_distances[current_vertex], current_vertex + begin};
        int global_closest_pair[2] = {std::numeric_limits<int>::max(), -1};

        //find the global closest vertex
        MPI_Allreduce(local_closest_pair, global_closest_pair, 1, MPI_2INT, MPI_MINLOC, MPI_COMM_WORLD);
        int global_closest_vertex = global_closest_pair[1], global_closest_dis = global_closest_pair[0];
        if(current_vertex + begin == global_closest_vertex){
            pq_.pop();
        }else{
            current_vertex = global_closest_vertex;
        }
        //update final result
        if(kRank == 0){
            global_distances[global_closest_vertex] = global_closest_dis;
        }
        for (int i = 0; i < n; i++) {
            // If the i-th vertex is connected with the current vertex and it has not be visited yet, we push to the queue.
            int current_distance = graph.check(current_vertex, i);
            // Update distance first. The item be pushes is the updated one
            if (current_distance!= std::numeric_limits<int>::max()) {
                local_distances[i] = std::min(local_distances[i], global_closest_dis + current_distance);
            }

            if (graph.check(current_vertex, i) != std::numeric_limits<int>::max() && !visited[i]) {
                pq_.push({local_distances[i], i});
                visited[i] = true;
            }
        }
    }

    return global_distances;
}