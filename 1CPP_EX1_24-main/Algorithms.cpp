#include "Algorithms.hpp"
#include <queue>
#include <vector>
#include <unordered_set>
#include <stack>
#include <climits>
#include <algorithm>

namespace ariel {


bool Algorithms::isConnected(const Graph& graph) {
    // Perform DFS from every vertex
    for (size_t i = 0; i < graph.matrix.size(); ++i) {
        std::vector<bool> visited(graph.matrix.size(), false);
        std::stack<size_t> stack;
        stack.push(i);
        visited[i] = true;

        while (!stack.empty()) {
            size_t current = stack.top();
            stack.pop();

            for (size_t j = 0; j < graph.matrix.size(); ++j) {
                if (graph.matrix[current][j] != 0 && !visited[j]) {
                    stack.push(j);
                    visited[j] = true;
                }
            }
        }

        // If any vertex is unreachable, return false
        for (size_t j = 0; j < graph.matrix.size(); ++j) {
            if (!visited[j]) {
                return false;
            }
        }
    }

    return true;
}

// bool Algorithms::isConnected(const Graph& graph) {
//     // BFS traversal to check connectivity
//     std::vector<bool> visited(graph.matrix.size(), false);
//     size_t count = 0;

//     for (size_t start = 0; start < graph.matrix.size(); ++start) {
//         if (!visited[start]) {
//             std::queue<size_t> q;
//             q.push(start);
//             visited[start] = true;
//             ++count;

//             while (!q.empty()) {
//                 size_t current = q.front();
//                 q.pop();

//                 for (size_t i = 0; i < graph.matrix.size(); ++i) {
//                     if (graph.matrix[current][i] != 0 && !visited[i]) {
//                         q.push(i);
//                         visited[i] = true;
//                     }
//                 }
//             }
//         }
//     }

//     return count == 1;
// }


// bool Algorithms::isConnected(const Graph& graph) {
//     // BFS traversal to check connectivity
//     std::vector<bool> visited(graph.matrix.size(), false);
//     std::queue<size_t> q;
//     q.push(0);
//     visited[0] = true;
//     size_t count = 1;

//     while (!q.empty()) {
//         size_t current = q.front();
//         q.pop();

//         for (size_t i = 0; i < graph.matrix.size(); ++i) {
//             if (graph.matrix[current][i] != 0 && !visited[i]) {
//                 q.push(i);
//                 visited[i] = true;
//                 ++count;
//             }
//         }
//     }

//     return count == graph.matrix.size();
// }

std::string Algorithms::shortestPath(const Graph& graph, int start, int end) {
    // Dijkstra's algorithm to find the shortest path
    size_t size = graph.matrix.size();
    std::vector<int> dist(size, INT_MAX);
    std::vector<int> prev(size, -1);
    dist[(size_t)start] = 0;
    //dist[start] = 0;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, start));

    while (!pq.empty()) {
        size_t u = (size_t)pq.top().second;
        pq.pop();

        for (size_t v = 0; v < size; ++v) {
            if (graph.matrix[u][v] != 0) {
                int alt = dist[u] + graph.matrix[u][v];
                if (alt < dist[v]) {
                    dist[v] = alt;
                    prev[v] = u;
                    pq.push(std::make_pair(dist[v], v));
                }
            }
        }
    }

    // Construct the path as a string
    std::string path;
     if (prev[(size_t)end] != -1) {
    for (int at = end; at != -1; at = prev[(size_t)at]) {
        if (!path.empty()) {
            path = std::to_string(at) + "->" + path;
        } else {
            path = std::to_string(at);
        }
    }
     } else {
        path = "-1"; // No path exists
     }
    return path;
}


// std::vector<int> Algorithms::shortestPath(const Graph& graph, int start, int end) {
//     // Dijkstra's algorithm to find the shortest path
//     int size = graph.matrix.size();
//     std::vector<int> dist(size, INT_MAX);
//     std::vector<int> prev(size, -1);
//     dist[start] = 0;

//     std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
//     pq.push(std::make_pair(0, start));

//     while (!pq.empty()) {
//         int u = pq.top().second;
//         pq.pop();

//         for (int v = 0; v < size; ++v) {
//             if (graph.matrix[u][v] != 0) {
//                 int alt = dist[u] + graph.matrix[u][v];
//                 if (alt < dist[v]) {
//                     dist[v] = alt;
//                     prev[v] = u;
//                     pq.push(std::make_pair(dist[v], v));
//                 }
//             }
//         }
//     }

//     std::vector<int> path;
//     for (int at = end; at != -1; at = prev[at])
//         path.push_back(at);

//     std::reverse(path.begin(), path.end());
//     return path;
// }

bool Algorithms::isContainsCycle(const Graph& graph) {
    // DFS traversal to check for cycles
    size_t size = graph.matrix.size();
    std::vector<bool> visited(size, false);
    std::stack<int> stack;

    for (size_t i = 0; i < size; ++i) {
        if (!visited[i]) {
            stack.push(i);
            while (!stack.empty()) {
                size_t current = (size_t)stack.top();
                stack.pop();
                if (visited[current])
                    return true;
                visited[current] = true;
                for (size_t j = 0; j < size; ++j) {
                    if (graph.matrix[current][j] != 0 && !visited[j]) {
                        stack.push(j);
                    }
                }
            }
        }
    }

    return false;
}

std::string Algorithms::isBipartite(const Graph& graph) {
    size_t size = graph.matrix.size();
    std::vector<int> color(size, -1);
    std::queue<int> q;

    for (size_t i = 0; i < size; ++i) {
        if (color[i] == -1) {
            q.push(i);
            color[i] = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (size_t v = 0; v < size; ++v) {
                    if (graph.matrix[(size_t)u][v] != 0) {
                        if (color[v] == -1) {
                            color[v] = 1 - color[(size_t)u];
                            q.push(v);
                        } else if (color[v] == color[(size_t)u]) {
                            return "0"; // Not bipartite
                        }
                    }
                }
            }
        }
    }

    // Construct the bipartition sets
    std::vector<int> setA, setB;
    for (size_t i = 0; i < size; ++i) {
        if (color[i] == 0) {
            setA.push_back(i);
        } else {
            setB.push_back(i);
        }
    }

    // Sort the sets
    std::sort(setA.begin(), setA.end());
    std::sort(setB.begin(), setB.end());

    // Construct the result string
    if (setA.empty() || setB.empty()) {
        return "0"; // Not bipartite
    }

    std::string result = "The graph is bipartite: A={";
    for (size_t i = 0; i < setA.size(); ++i) {
        result += std::to_string(setA[i]);
        if (i != setA.size() - 1) {
            result += ", ";
        }
    }
    result += "}, B={";
    for (size_t i = 0; i < setB.size(); ++i) {
        result += std::to_string(setB[i]);
        if (i != setB.size() - 1) {
            result += ", ";
        }
    }
    result += "}";

    return result;
}


// std::string Algorithms::isBipartite(const Graph& graph) {
//         size_t size = graph.matrix.size();
//         std::vector<int> color(size, -1);
//         std::queue<int> q;

//         for (size_t i = 0; i < size; ++i) {
//             if (color[i] == -1) {
//                 q.push(i);
//                 color[i] = 0;
//                 while (!q.empty()) {
//                     int u = q.front();
//                     q.pop();
//                     for (size_t v = 0; v < size; ++v) {
//                         if (graph.matrix[(size_t)u][v] != 0) {
//                             if (color[v] == -1) {
//                                 color[v] = 1 - color[(size_t)u];
//                                 q.push(v);
//                             } else if (color[v] == color[(size_t)u]) {
//                                 return "0"; // Not bipartite
//                             }
//                         }
//                     }
//                 }
//             }
//         }

//         // Construct the bipartition sets
//         std::vector<int> setA, setB;
//         for (size_t i = 0; i < size; ++i) {
//             if (color[i] == 0) {
//                 setA.push_back(i);
//             } else {
//                 setB.push_back(i);
//             }
//         }

//         // Construct the result string
//         if (setA.empty() || setB.empty()) {
//             return "0"; // Not bipartite
//         }

//         std::string result = "The graph is bipartite: A={";
//         for (size_t i = 0; i < setA.size(); ++i) {
//             result += std::to_string(setA[i]);
//             if (i != setA.size() - 1) {
//                 result += ", ";
//             }
//         }
//         result += "}, B={";
//         for (size_t i = 0; i < setB.size(); ++i) {
//             result += std::to_string(setB[i]);
//             if (i != setB.size() - 1) {
//                 result += ", ";
//             }
//         }
//         result += "}";

//         return result;
//     }


// std::string Algorithms::isBipartite(const Graph& graph) {
//             size_t size = graph.matrix.size();
//             std::vector<int> color(size, -1);
//             std::queue<int> q;

//             for (size_t i = 0; i < size; ++i) {
//                 if (color[i] == -1) {
//                     q.push(i);
//                     color[i] = 0;
//                     while (!q.empty()) {
//                         int u = q.front();
//                         q.pop();
//                         for (size_t v = 0; v < size; ++v) {
//                             if (graph.matrix[(size_t)u][v] != 0) {
//                                 if (color[v] == -1) {
//                                     color[v] = 1 - color[(size_t)u];
//                                     q.push(v);
//                                 } else if (color[v] == color[(size_t)u]) {
//                                     return "0"; // Changed to "0" to match the existing test case
//                                 }
//                             }
//                         }
//                     }
//                 }
//             }

//             // Construct the bipartition sets
//             std::vector<int> setA, setB;
//             for (size_t i = 0; i < size; ++i) {
//                 if (color[i] == 0) {
//                     setA.push_back(i);
//                 } else {
//                     setB.push_back(i);
//                 }
//             }

//             // Construct the result string
//             if (setA.empty() || setB.empty()) {
//                 return "0"; // Changed to "0" to match the existing test case
//             }

// std::string result = "The graph is bipartite: A={";
// for (size_t i = 0; i < setA.size(); ++i) {
//     result += std::to_string(setA[i]);
//     if (i != setA.size() - 1) {
//         result += ", ";
//     }
// }
// result += ", ";

// for (size_t i = 0; i < setB.size(); ++i) {
//     result += std::to_string(setB[i]);
//     if (i != setB.size() - 1) {
//         result += ", ";
//     }
// }
// result += "}";

// return result;


//            // return result;
//         }


// std::string Algorithms::isBipartite(const Graph& graph) {
//     size_t size = graph.matrix.size();
//     std::vector<int> color(size, -1);
//     std::queue<int> q;

//     for (size_t i = 0; i < size; ++i) {
//         if (color[i] == -1) {
//             q.push(i);
//             color[i] = 0;
//             while (!q.empty()) {
//                 int u = q.front();
//                 q.pop();
//                 for (size_t v = 0; v < size; ++v) {
//                     if (graph.matrix[(size_t)u][v] != 0) {
//                         if (color[v] == -1) {
//                             color[v] = 1 - color[(size_t)u];
//                             q.push(v);
//                         } else if (color[v] == color[(size_t)u]) {
//                             return "The graph is not bipartite";
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     // Construct the bipartition sets
//     std::vector<int> setA, setB;
//     for (size_t i = 0; i < size; ++i) {
//         if (color[i] == 0) {
//             setA.push_back(i);
//         } else {
//             setB.push_back(i);
//         }
//     }

//     // Construct the result string
//     if (setA.empty() || setB.empty()) {
//         return "The graph is not bipartite";
//     }

//     std::string result = "The graph is bipartite: A={";
//     for (size_t i = 0; i < setA.size(); ++i) {
//         result += std::to_string(setA[i]);
//         if (i != setA.size() - 1) {
//             result += ", ";
//         }
//     }
//     result += "}, B={";
//     for (size_t i = 0; i < setB.size(); ++i) {
//         result += std::to_string(setB[i]);
//         if (i != setB.size() - 1) {
//             result += ", ";
//         }
//     }
//     result += "}";

//     return result;
// }



// std::string Algorithms::isBipartite(const Graph& graph) {
//     size_t size = graph.matrix.size();
//     std::vector<int> color(size, -1);
//     std::queue<int> q;

//     for (size_t i = 0; i < size; ++i) {
//         if (color[i] == -1) {
//             q.push(i);
//             color[i] = 0;
//             while (!q.empty()) {
//                 int u = q.front();
//                 q.pop();
//                 for (size_t v = 0; v < size; ++v) {
//                     if (graph.matrix[(size_t)u][v] != 0) {
//                         if (color[v] == -1) {
//                             color[v] = 1 - color[(size_t)u];
//                             q.push(v);
//                         } else if (color[v] == color[(size_t)u]) {
//                             return "The graph is not bipartite";
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     // Construct the bipartition sets
//     std::vector<int> setA, setB;
//     for (size_t i = 0; i < size; ++i) {
//         if (color[i] == 0) {
//             setA.push_back(i);
//         } else {
//             setB.push_back(i);
//         }
//     }

//     // Construct the result string
//     std::string result = "The graph is bipartite: A={";
//     for (size_t i = 0; i < setA.size(); ++i) {
//         result += std::to_string(setA[i]);
//         if (i != setA.size() - 1) {
//             result += ", ";
//         }
//     }
//     result += "}, B={";
//     for (size_t i = 0; i < setB.size(); ++i) {
//         result += std::to_string(setB[i]);
//         if (i != setB.size() - 1) {
//             result += ", ";
//         }
//     }
//     result += "}";

//     return result;
// }


    // std::string Algorithms::isBipartite(const Graph& graph) {
    //     size_t size = graph.matrix.size();
    //     std::vector<int> color(size, -1);
    //     std::queue<int> q;

    //     for (size_t i = 0; i < size; ++i) {
    //         if (color[i] == -1) {
    //             q.push(i);
    //             color[i] = 0;
    //             while (!q.empty()) {
    //                 int u = q.front();
    //                 q.pop();
    //                 for (size_t v = 0; v < size; ++v) {
    //                     if (graph.matrix[(size_t)u][v] != 0) {
    //                         if (color[v] == -1) {
    //                             color[v] = 1 - color[(size_t)u];
    //                             q.push(v);
    //                         } else if (color[v] == color[(size_t)u]) {
    //                             return "The graph is not bipartite";
    //                         }
    //                     }
    //                 }
    //             }
    //         }
    //     }

    //     return "The graph is bipartite";
    // }

// bool Algorithms::isBipartite(const Graph& graph) {
//     // BFS traversal to check if graph is bipartite
//     size_t size = graph.matrix.size();
//     std::vector<int> color(size, -1);
//     std::queue<int> q;

//     for (size_t i = 0; i < size; ++i) {
//         if (color[i] == -1) {
//             q.push(i);
//             color[i] = 0;
//             while (!q.empty()) {
//                 int u = q.front();
//                 q.pop();
//                 for (size_t v = 0; v < size; ++v) {
//                     if (graph.matrix[(size_t)u][v] != 0) {
//                         if (color[v] == -1) {
//                             color[v] = 1 - color[(size_t)u];
//                             q.push(v);
//                         } else if (color[v] == color[(size_t)u]) {
//                             return false;
//                         }
//                     }
//                 }
//             }
//         }
//     }

//     return true;
// }
} // namespace ariel
