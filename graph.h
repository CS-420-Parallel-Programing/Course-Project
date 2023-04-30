#pragma once

#include <vector>

class Graph {
public:
    Graph(int n);

    /**
     * @brief function to add an edge between vertices
     * 
     * @param i index of start vertex
     * @param j index of end vertex
     * @return whether an edge is successfully added. We don't not allow adding redundant edges.
     */
    bool add_edge(int i, int j, int distance);

    /**
     * @brief Get the size of the graph
     * 
     * @return int 
     */
    int get_size() const;

    /**
     * @brief Check the length of the edge between two vertices
     * 
     * @param i 
     * @param j 
     * @return int. If two vertices are not connected return -1.
     */
    int check(int i, int j) const;

private:
    // 2-D array to represent a undirected graph. The diagonal terms are teh degree of the vertex.
    // Off diagonal terms A_{ij} are 0 or 1. 1 means connected and 0 means not connected.
    std::vector<std::vector<int>> adj_matrix;
    int size;
};