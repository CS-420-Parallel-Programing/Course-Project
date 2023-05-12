#include <omp.h>
#include <ostream>
#include <queue>
#include <iostream>
#include "tools.h"

using namespace std;
std::vector<bool> bfs_omp1(const Graph& graph, int start_vertex){
    int n = graph.get_size();
    std::vector<bool> visited(n, false);
    std::queue<int> q;
    visited[start_vertex] = true;
    q.push(start_vertex);
    while(!q.empty()){
        int current = q.front();
        q.pop();
        #pragma omp parallel for schedule(dynamic, 1024)
        for(int i = 0; i < n; i ++){
            if(graph.check(current, i) != std::numeric_limits<int>::max() && !visited[i]){
                visited[i] = true;
                q.push(i);
            }
        }
    }
    return visited;
}

void visit(const Graph& graph, int start_vertex, std::vector<bool> &visited){
    if(visited[start_vertex]){
        return;
    }
    visited[start_vertex] = true;
    #pragma omp parallel for schedule(dynamic, 1024)
    for(int i = 0; i < graph.get_size(); i++){
        if(graph.check(start_vertex, i) != std::numeric_limits<int>::max() && !visited[i]){
                #pragma omp task
                visit(graph, i, visited);
            }
    }
}

std::vector<bool> bfs_omp2(const Graph& graph, int start_vertex){
    int n = graph.get_size();
    std::vector<bool> visited(n, false);
    #pragma omp parallel
    #pragma omp single
    visit(graph, start_vertex, visited);
    return visited;
}
