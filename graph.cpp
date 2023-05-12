#include "graph.h"
#include <random>

Graph::Graph(int n, bool isdirected) {
    size = n;
    hasDirection = isdirected;
    // Initialize with all vertices non-connected
    adj_matrix.resize(n);
    for (int i = 0; i < n; i++) {
        adj_matrix[i].resize(n, std::numeric_limits<int>::max());
        // bug_fixed: the diagonal terms should be zero to avoid mistacks calculating distances.
        adj_matrix[i][i] = 0;
    }
}


// The function allows to update the distance between two vertices.
bool Graph::add_edge(int i, int j, int distance) {
    if (distance < 0) {
        return false;
    }

    adj_matrix[i][j] = distance;
    if(!hasDirection){
        adj_matrix[j][i] = distance;
    }
    return true;
}

int Graph::get_size() const{
    return size;
}

int Graph::check(int i, int j) const{
    return adj_matrix[i][j];
}

std::vector<int> Graph::get_neighbors(int vid) const {
    std::vector<int> neighbors;

    for (int i = 0; i < size; i++) {
        if (i != vid && adj_matrix[vid][i] != std::numeric_limits<int>::max()) {
            neighbors.push_back(i);
        }
    }

    return neighbors;
}

