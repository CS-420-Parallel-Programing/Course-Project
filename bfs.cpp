#include "bfs.h"
#include <queue>
#include <iostream>

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
                queue_.push(i);
                // std::cout << "Add vertex" << i << "into the queue" << std::endl;
                visited[i] = true;
            }

            /**
             * Update the starting vertex's distance to current vertex and its neighbors. This should be separated from the search.
             * Because even though all vertices has been added to the queue, we still need to update distances later then they are poped
             * from the queue.
             * 
             * The condition to update is that starting vertex is connected to the current vertex and the current vertex is connected
             * to the vertex that is being checked.
             */
            if (distances[curr_vertex] != -1 && graph.check(curr_vertex, i) != -1) {
                // The new distance is start-current + current+neighbor = start-neighbor
                int new_distance = distances[curr_vertex] + graph.check(curr_vertex, i);
            
                if (distances[i] != -1) {
                    distances[i] = std::min(new_distance, distances[i]);
                } else { // If there is no previous records of the distance, directly update the record
                    distances[i] = new_distance;
                }    
            }
        }
    }

    return distances;
    
}