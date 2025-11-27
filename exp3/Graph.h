#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <climits>

class Graph {
private:
    int vertexCount;
    std::vector<std::vector<int> > adjacencyMatrix;
    std::vector<std::vector<std::pair<int, int> > > adjacencyList;
    std::vector<char> vertexLabels;

public:
    Graph(int n) {
        vertexCount = n;
        adjacencyMatrix.resize(n, std::vector<int>(n, 0));
        adjacencyList.resize(n);
        vertexLabels.resize(n);
    }

    void setVertexLabel(int index, char label) {
        if (index >= 0 && index < vertexCount) {
            vertexLabels[index] = label;
        }
    }

    char getVertexLabel(int index) const {
        if (index >= 0 && index < vertexCount) {
            return vertexLabels[index];
        }
        return '?';
    }

    int getVertexCount() const {
        return vertexCount;
    }

    int getWeight(int u, int v) const {
        if (u >= 0 && u < vertexCount && v >= 0 && v < vertexCount) {
            return adjacencyMatrix[u][v];
        }
        return 0;
    }

    int getVertexIndex(char label) {
        for (int i = 0; i < vertexCount; i++) {
            if (vertexLabels[i] == label) {
                return i;
            }
        }
        return -1;
    }

    void addEdge(int u, int v, int weight) {
        if (u >= 0 && u < vertexCount && v >= 0 && v < vertexCount) {
            adjacencyMatrix[u][v] = weight;
            adjacencyMatrix[v][u] = weight;
            
            adjacencyList[u].push_back(std::make_pair(v, weight));
            adjacencyList[v].push_back(std::make_pair(u, weight));
        }
    }

    void addEdge(char u, char v, int weight) {
        int uIndex = getVertexIndex(u);
        int vIndex = getVertexIndex(v);
        if (uIndex != -1 && vIndex != -1) {
            addEdge(uIndex, vIndex, weight);
        }
    }

    void printAdjacencyMatrix() {
        std::cout << "邻接矩阵:" << std::endl;
        std::cout << "   ";
        for (int i = 0; i < vertexCount; i++) {
            std::cout << vertexLabels[i] << "  ";
        }
        std::cout << std::endl;
        
        for (int i = 0; i < vertexCount; i++) {
            std::cout << vertexLabels[i] << "  ";
            for (int j = 0; j < vertexCount; j++) {
                if (adjacencyMatrix[i][j] == 0) {
                    std::cout << "0  ";
                } else {
                    if (adjacencyMatrix[i][j] < 10) {
                        std::cout << adjacencyMatrix[i][j] << "  ";
                    } else {
                        std::cout << adjacencyMatrix[i][j] << " ";
                    }
                }
            }
            std::cout << std::endl;
        }
    }

    void printAdjacencyList() {
        std::cout << "邻接表:" << std::endl;
        for (int i = 0; i < vertexCount; i++) {
            std::cout << vertexLabels[i] << ": ";
            for (size_t j = 0; j < adjacencyList[i].size(); j++) {
                int neighbor = adjacencyList[i][j].first;
                int weight = adjacencyList[i][j].second;
                std::cout << vertexLabels[neighbor] << "(" << weight << ") ";
            }
            std::cout << std::endl;
        }
    }

    void BFS(char startLabel) {
        int start = getVertexIndex(startLabel);
        if (start == -1) return;

        std::vector<bool> visited(vertexCount, false);
        std::queue<int> q;
        
        std::cout << "BFS遍历顺序 (" << startLabel << "出发): ";
        
        visited[start] = true;
        q.push(start);
        
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            std::cout << vertexLabels[current] << " ";
            
            for (int i = 0; i < vertexCount; i++) {
                if (adjacencyMatrix[current][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }
        std::cout << std::endl;
    }

    void DFSUtil(int v, std::vector<bool>& visited) {
        visited[v] = true;
        std::cout << vertexLabels[v] << " ";
        
        for (int i = 0; i < vertexCount; i++) {
            if (adjacencyMatrix[v][i] != 0 && !visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    void DFS(char startLabel) {
        int start = getVertexIndex(startLabel);
        if (start == -1) return;

        std::vector<bool> visited(vertexCount, false);
        std::cout << "DFS遍历顺序 (" << startLabel << "出发): ";
        DFSUtil(start, visited);
        std::cout << std::endl;
    }

    void dijkstra(char startLabel) {
        int start = getVertexIndex(startLabel);
        if (start == -1) return;

        std::vector<int> dist(vertexCount, INT_MAX);
        std::vector<bool> visited(vertexCount, false);
        std::vector<int> parent(vertexCount, -1);
        
        dist[start] = 0;
        
        for (int count = 0; count < vertexCount - 1; count++) {
            int minDist = INT_MAX, minIndex = -1;
            for (int v = 0; v < vertexCount; v++) {
                if (!visited[v] && dist[v] <= minDist) {
                    minDist = dist[v];
                    minIndex = v;
                }
            }
            
            if (minIndex == -1) break;
            
            int u = minIndex;
            visited[u] = true;
            
            for (int v = 0; v < vertexCount; v++) {
                if (!visited[v] && adjacencyMatrix[u][v] != 0 && 
                    dist[u] != INT_MAX && dist[u] + adjacencyMatrix[u][v] < dist[v]) {
                    dist[v] = dist[u] + adjacencyMatrix[u][v];
                    parent[v] = u;
                }
            }
        }
        
        std::cout << "从 " << startLabel << " 出发的最短路径 (Dijkstra):" << std::endl;
        for (int i = 0; i < vertexCount; i++) {
            if (i != start && dist[i] != INT_MAX) {
                std::cout << "到 " << vertexLabels[i] << ": 距离=" << dist[i] << ", 路径=";
                printPath(parent, i);
                std::cout << std::endl;
            }
        }
    }

    void printPath(const std::vector<int>& parent, int j) {
        if (parent[j] == -1) {
            std::cout << vertexLabels[j];
            return;
        }
        printPath(parent, parent[j]);
        std::cout << " -> " << vertexLabels[j];
    }

    void primMST(char startLabel) {
        int start = getVertexIndex(startLabel);
        if (start == -1) return;

        std::vector<int> parent(vertexCount, -1);
        std::vector<int> key(vertexCount, INT_MAX);
        std::vector<bool> inMST(vertexCount, false);
        
        key[start] = 0;
        
        for (int count = 0; count < vertexCount - 1; count++) {
            int minKey = INT_MAX, minIndex = -1;
            for (int v = 0; v < vertexCount; v++) {
                if (!inMST[v] && key[v] < minKey) {
                    minKey = key[v];
                    minIndex = v;
                }
            }
            
            if (minIndex == -1) break;
            
            int u = minIndex;
            inMST[u] = true;
            
            for (int v = 0; v < vertexCount; v++) {
                if (adjacencyMatrix[u][v] != 0 && !inMST[v] && adjacencyMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjacencyMatrix[u][v];
                }
            }
        }
        
        std::cout << "最小生成树 (Prim算法):" << std::endl;
        int totalWeight = 0;
        for (int i = 0; i < vertexCount; i++) {
            if (parent[i] != -1) {
                std::cout << vertexLabels[parent[i]] << " - " << vertexLabels[i] 
                          << " (权重: " << adjacencyMatrix[i][parent[i]] << ")" << std::endl;
                totalWeight += adjacencyMatrix[i][parent[i]];
            }
        }
        std::cout << "总权重: " << totalWeight << std::endl;
    }

    void findArticulationPoints() {
        std::vector<int> disc(vertexCount, -1);
        std::vector<int> low(vertexCount, -1);
        std::vector<int> parent(vertexCount, -1);
        std::vector<bool> articulation(vertexCount, false);
        
        int time = 0;
        
        for (int i = 0; i < vertexCount; i++) {
            if (disc[i] == -1) {
                articulationPointUtil(i, disc, low, parent, articulation, time);
            }
        }
        
        std::cout << "关节点: ";
        bool found = false;
        for (int i = 0; i < vertexCount; i++) {
            if (articulation[i]) {
                std::cout << vertexLabels[i] << " ";
                found = true;
            }
        }
        if (!found) {
            std::cout << "无";
        }
        std::cout << std::endl;
    }

private:
    void articulationPointUtil(int u, std::vector<int>& disc, std::vector<int>& low,
                              std::vector<int>& parent, std::vector<bool>& articulation, int& time) {
        int children = 0;
        disc[u] = low[u] = ++time;
        
        for (int v = 0; v < vertexCount; v++) {
            if (adjacencyMatrix[u][v] != 0) {
                if (disc[v] == -1) {
                    children++;
                    parent[v] = u;
                    articulationPointUtil(v, disc, low, parent, articulation, time);
                    
                    low[u] = std::min(low[u], low[v]);
                    
                    if (parent[u] == -1 && children > 1) {
                        articulation[u] = true;
                    }
                    
                    if (parent[u] != -1 && low[v] >= disc[u]) {
                        articulation[u] = true;
                    }
                } else if (v != parent[u]) {
                    low[u] = std::min(low[u], disc[v]);
                }
            }
        }
    }
};

#endif
