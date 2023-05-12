#pragma once
#include <vector>
#include "graph.h"

std::vector<bool> bfs_omp1(const Graph& graph, int start_vertex);
std::vector<bool> bfs_omp2(const Graph& graph, int start_vertex);
void visit();