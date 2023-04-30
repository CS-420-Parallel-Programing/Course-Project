#pragma once
#include <vector>
#include "graph.h"

/**
 * @brief non-parallel breath first search algorithm
 * 
 * @param graph 
 * @param start_vertex 
 * @return return a vector recording the distance from the starting vertex to all other vertices respectively.
 */
std::vector<int> bfs(const Graph& graph, int start_vertex);