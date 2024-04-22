#include "Graph.hpp"
#include <iostream>
namespace ariel {

void Graph::loadGraph(const std::vector<std::vector<int>>& adjacencyMatrix) {
    // Assuming adjacencyMatrix is a square matrix
    int size = adjacencyMatrix.size();
    if (size != 0 && size == adjacencyMatrix[0].size()) {
        matrix = adjacencyMatrix;
        std::cout << "Graph loaded successfully." << std::endl;
    } else {
        throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
    }
}


void Graph::printGraph() const {
    size_t size = matrix.size();
    std::cout << "Graph with " << size << " vertices and ";
    size_t edges = 0;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = i; j < size; ++j) { // Start j from i to avoid double counting edges
            if (matrix[i][j] != 0) {
                ++edges;
            }
        }
    }
    std::cout << edges << " edges." << std::endl;
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < size; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// void Graph::printGraph() const {
//     int size = matrix.size();
//     std::cout << "Graph with " << size << " vertices and ";
//     int edges = 0;
//     for (int i = 0; i < size; ++i) {
//         for (int j = 0; j < size; ++j) {
//             if (matrix[i][j] != 0) {
//                 ++edges;
//             }
//         }
//     }
//     std::cout << edges / 2 << " edges." << std::endl;
//     for (int i = 0; i < size; ++i) {
//         for (int j = 0; j < size; ++j) {
//             std::cout << matrix[i][j] << " ";
//         }
//         std::cout << std::endl;
//     }
// }
}
