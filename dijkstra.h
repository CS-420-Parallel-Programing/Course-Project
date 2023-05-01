#pragma once
#include <vector>
#include "graph.h"

/**
 * @brief non-parallel Dijkstra's method to find the shortest distance from the starting vertex to all other vertices.
 * 
 * @param graph 
 * @param start_vertex 
 * @return return a vector recording the distances.
 */
std::vector<int> dijkstra(const Graph& graph, int start_vertex);