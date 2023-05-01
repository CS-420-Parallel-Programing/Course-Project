#include "graph.h"
#include <random>
#include <limits>

Graph::Graph(int n) {
    size = n;
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
    adj_matrix[j][i] = distance;
    return true;
}

int Graph::get_size() const{
    return size;
}

int Graph::check(int i, int j) const{
    return adj_matrix[i][j];
}

