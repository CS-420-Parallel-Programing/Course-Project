#include "bfs.h"
#include <queue>

std::vector<int> bfs(const Graph& graph, int start_vertex) {
    int n = graph.get_size();
    // Array to record the distances
    std::vector<int> distances(n, -1);
    // Array to record whether a vertex has been visited
    std::vector<int> visited(n, false);
    std::queue<int> queue_;

    queue_.push(start_vertex);
    visited[start_vertex] = true;
    distances[start_vertex] = 0;

    while (!queue_.empty()) {
        int curr_vertex = queue_.front();
        queue_.pop();

        for (int i = 0; i < n; i++) {
            // If current vertex and vertex i are connected and i is not visited 
            if (graph.check(curr_vertex, i) != -1 && !visited[i]) {
                int new_distance = distances[curr_vertex] + graph.check(curr_vertex, i);
                // Update distance if the new distance is smaller than recorded distance.
                // Or we don't have recorded distance
                if (new_distance < distances[i] || distances[i] == -1) {
                    distances[i] = new_distance;
                }
                queue_.push(i);
                visited[i] = true;
            }
        }
    }
    
}