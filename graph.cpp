#include "graph.h"
#include <random>

Graph::Graph(int n) {
    size = n;
    // Initialize with all vertices non-connected
    adj_matrix.resize(n);
    for (int i = 0; i < n; i++) {
        adj_matrix[i].resize(n, -1);
    }
}


bool Graph::add_edge(int i, int j, int distance) {
    // return false if two vertices are already connected.
    if (adj_matrix[i][j] != 0) {
        return false;
    }
    adj_matrix[i][j] = distance;
    adj_matrix[j][i] = distance;
    return true;
}

int Graph::get_size() const{
    return size;
}

int Graph::check(int i, int j) const{
    return adj_matrix[i][j];
}

