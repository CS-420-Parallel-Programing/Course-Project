#include <queue>
#include <iostream>
#include "tools.h"

std::vector<bool> bfs(const Graph& graph, int start_vertex) {
    int n = graph.get_size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    visited[start_vertex] = true;
    q.push(start_vertex);
    while(!q.empty()){
        int current = q.front();
        q.pop();
        for(int i = 0; i < n; i ++){
            if(graph.check(current, i) != std::numeric_limits<int>::max() && !visited[i]){
                visited[i] = true;
                q.push(i);
            }
        }
    }
    return visited;
}