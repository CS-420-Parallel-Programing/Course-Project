#pragma once
#include <vector>
#include "graph.h"
#include <omp.h>
#include <mpi.h>

/**
 * @brief non-parallel Dijkstra's method to find the shortest distance from the starting vertex to all other vertices.
 * 
 * @param graph 
 * @param start_vertex 
 * @return return a vector recording the distances.
 */
std::vector<int> dijkstra(const Graph& graph, int start_vertex);
std::vector<int> dijkstra_omp(const Graph& graph, int start_vertex);