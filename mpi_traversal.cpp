#include "mpi_traversal.h"
#include <iostream>

int get_process(int vertex, int size) {
    return vertex % size;
}

void visit(int vid, std::set<int>& visited, std::queue<int>& q, int rank, int size, Graph& graph) {
    // insert the current vertex to visited set
    // visited.insert(vid);
    // Find its neighbors
    std::cout << "Visit vertex " << vid << "." << std::endl;
    std::vector<int> neighbors = graph.get_neighbors(vid);
    for (int i : neighbors) {
        // If current neighbor has not been visited
        if (visited.count(i) == 0) {
            // Get where it belongs to
            int pid = get_process(i, size);
            // If it does not belong to the current process, send it to another process
            if (pid != rank) {
                MPI_Request req;
                MPI_Isend(&i, 1, MPI_INT, pid, 0, MPI_COMM_WORLD, &req);
                // Free the request to ensure send buffer could reuse
                MPI_Request_free(&req);
            } else {
                q.push(i);
                visited.insert(i);
            }
        }
    }
}

void start(int start_vertex, Graph& graph) {
    int size;
    int rank;
    std::cout << "Use " << size << " processes." << std::endl;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::queue<int> q;
    std::set<int> visited;

    // start vertex is 0 as always
    if (rank == 0) {
        visited.insert(start_vertex);
        visit(start_vertex, visited, q, rank, size, graph);
    }

    int i;
    MPI_Request recv_req;
    MPI_Status status;
    int flag = 0;

    // If the current proccess is not 0, it has no element in queue at beginning
    if (rank != 0) {
        MPI_Irecv(&i, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &recv_req);
    }
    

    while (true) {
        if (rank != 0) {
            // Check previous receive status
            MPI_Test(&recv_req, &flag, &status);
            // If previous recv is done
            if (flag) {
                visit(i, visited, q, rank, size, graph);
                MPI_Irecv(&i, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &recv_req);
            }
        }

        if (!q.empty()) {
            i = q.front();
            q.pop();
            visit(i, visited, q, rank, size, graph);
        }

        // Check whether all processes have no more vertices to visit and no more pending MPI_Irecv operations
        int local_done = q.empty() && !flag;
        int global_done;
        // Use logical and operation for reduce to check whether all local_done is true.
        MPI_Allreduce(&local_done, &global_done, 1, MPI_INT, MPI_LAND, MPI_COMM_WORLD);

        if (global_done) {
            break;
        }
    }
    
    if (rank != 0) {
        MPI_Cancel(&recv_req);
    }
}