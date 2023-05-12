#include "mpi_traversal.h"
#include <iostream>

int get_process(int vertex, int size) {
    return vertex % size;
}

void visit(int vid, bool visited[], std::queue<int>& q, int rank, int size, Graph& graph) {
    // insert the current vertex to visited set
    // visited.insert(vid);
    // Find its neighbors
    // std::cout << "Visit Vertex" << vid << std::endl;
    std::vector<int> neighbors = graph.get_neighbors(vid);
    for (int i : neighbors) {
        // If current neighbor has not been visited
        if (!visited[i]) {
            // Get where it belongs to
            int pid = get_process(i, size);
            // If it does not belong to the current process, send it to another process
            // visited.insert(i);
            visited[i] = true;
            if (pid != rank) {
                MPI_Request req;
                MPI_Status status;
                
                MPI_Send(&i, 1, MPI_INT, pid, 0, MPI_COMM_WORLD);
                // Free the request to ensure send buffer could reuse
                // MPI_Request_free(&req);
            } else {
                q.push(i);
            }
        }
    }
}

bool* start(int start_vertex, Graph& graph) {
    int size;
    int rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    std::cout << "Use " << size << " processes." << std::endl;

    std::queue<int> q;
    int n = graph.get_size();
    bool* visited = new bool[n]();
    bool* global_visited = new bool[n]();

    // start vertex is 0 as always
    if (rank == 0) {
        // visited.insert(start_vertex);
        // visited[start_vertex] = true;
        visit(start_vertex, visited, q, rank, size, graph);
        // q.push(start_vertex);
    }

    int i;
    MPI_Request recv_req;
    MPI_Status status;
    // int flag = 0;

    // If the current proccess is not 0, it has no element in queue at beginning
    // if (rank != 0) {
    //     MPI_Recv(&i, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
    // }
    

    while (true) {
        // if (rank != 0) {
            // Check previous receive status
            // MPI_Test(&recv_req, &flag, &status);
            // If previous recv is done
            MPI_Recv(&i, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
            visit(i, visited, q, rank, size, graph);           
        // }

        if (!q.empty()) {
            i = q.front();
            q.pop();
            // MPI_Wait(&recv_req, &status);
            // MPI_Test(&recv_req, &flag, &status);
            visit(i, visited, q, rank, size, graph);
        }

        // Check whether all processes have no more vertices to visit and no more pending MPI_Irecv operations
        // int local_done = q.empty() && !flag;
        int local_done = q.empty();
        int global_done;

        
        // Use logical and operation for reduce to check whether all local_done is true.
        MPI_Allreduce(&local_done, &global_done, 1, MPI_INT, MPI_LAND, MPI_COMM_WORLD);

        
        if (global_done) {
            break;
        }
    }

    MPI_Allreduce(visited, global_visited, n, MPI_CXX_BOOL, MPI_LOR, MPI_COMM_WORLD);
    delete[] visited;
    return global_visited;
}