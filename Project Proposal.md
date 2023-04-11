# Introduction

This project will implement parallel BFS algorithm to compute the distances to all vertices starting with any random vertex. The implementation mainly utilizes MPI and OpenMP as toolkits. Generally, we will develop a non-parallel BFS method as our baseline. Then, we will develop three parallel BFS solutions with OpenMP, MPI and a hybrid version respectively. Finally, we will compare the performance and scaling poperties of different methods.

# Implementation of Non-Parallel Breadth First Search

## Data Structure and Representation

The graph data is represented by an adjacency matrix A, stored in a two-dimensional array. The value of $A_{ij}$ denotes the distance between vertex $i$ and vertex $j$. The diagonal terms represent the degree of each vertex. The BFS algorithm implementation makes use of a queue and an array to record the visigted vertices.

## Algorithm

1. Initialize an empty two-dimensional array, an empty queue, and a visited array with all values set to false.

2. Randomly select a vertex and push it into the queue.

3. While the queue is not empty, perform the following steps:

   a. Pop the first vertex from the queue and assign it as the current vertex.

   b. Record the distances between the current vertex and its neighbors using the adjacency matrix.

   c. Push the unvisited neighbors of the current vertex into the queue.

   d. Update the visited array values for the current vertex's neighbors to be true.

4. Repeat the step 3 untill the queue is empty.

# Parallel Implementation of Breadth First Search

For OpenMp, we plan to try two methods. One method is to use #pragma omp parallel for, it can parallelize the loop that visits all the neighbors of the current node. Another is to use #pragma omp task, whenever we discover a new node, it can spawn a task and assign the task to visit that new node.

For MPI, we plan to try “MPI_Scatter” and “MPI_Gather”. In each level of BFS, we scatter parts of neighbors to different processes and then gather new neighbors to root process.