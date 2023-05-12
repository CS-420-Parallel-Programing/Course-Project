#ifndef MPI_TRAVERSL_H
#define MPI_TRAVERSL_H


#include "graph.h"
#include <set>
#include <queue>
#include <mpi.h>


bool* start(int start_vertex, Graph& graph);
void visit(int vid, bool visited[], std::queue<int>& q, int rank, int size, Graph& graph);
int get_process(int vertex, int size);




#endif