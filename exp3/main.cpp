#include "Graph.h"
#include "GraphViz.h"
#include <iostream>
#include <vector>

void printTextGraph1() {
    std::cout << "图1的文本表示:" << std::endl;
    std::cout << "    A" << std::endl;
    std::cout << "   / \\" << std::endl;
    std::cout << "  4   2" << std::endl;
    std::cout << " /     \\" << std::endl;
    std::cout << "B       D" << std::endl;
    std::cout << "| \\     | \\" << std::endl;
    std::cout << "12 9    13 11" << std::endl;
    std::cout << "|   \\   |   \\" << std::endl;
    std::cout << "C     E       G" << std::endl;
    std::cout << " \\   / \\     /" << std::endl;
    std::cout << "  10 5   14 8" << std::endl;
    std::cout << "     \\   /" << std::endl;
    std::cout << "      F" << std::endl;
    std::cout << std::endl;
}

void printTextGraph2() {
    std::cout << "图2的文本表示:" << std::endl;
    std::cout << "    A" << std::endl;
    std::cout << "   / \\" << std::endl;
    std::cout << "  6   2" << std::endl;
    std::cout << " /     \\" << std::endl;
    std::cout << "B       D" << std::endl;
    std::cout << "| \\     | \\" << std::endl;
    std::cout << "4  13   1  11" << std::endl;
    std::cout << "|   \\   |   \\" << std::endl;
    std::cout << "C     E       G" << std::endl;
    std::cout << " \\   / \\     /" << std::endl;
    std::cout << "  12 9   14 3" << std::endl;
    std::cout << "     \\   /" << std::endl;
    std::cout << "      F   H" << std::endl;
    std::cout << std::endl;
}

void testGraph1() {
    std::cout << "=== 图1测试 ===" << std::endl;
    printTextGraph1();
    
    Graph g1(7);
    
    g1.setVertexLabel(0, 'A');
    g1.setVertexLabel(1, 'B');
    g1.setVertexLabel(2, 'C');
    g1.setVertexLabel(3, 'D');
    g1.setVertexLabel(4, 'E');
    g1.setVertexLabel(5, 'F');
    g1.setVertexLabel(6, 'G');
    
    g1.addEdge('A', 'B', 4);
    g1.addEdge('A', 'D', 2);
    g1.addEdge('B', 'C', 12);
    g1.addEdge('B', 'E', 9);
    g1.addEdge('C', 'F', 10);
    g1.addEdge('D', 'E', 13);
    g1.addEdge('D', 'G', 11);
    g1.addEdge('E', 'F', 5);
    g1.addEdge('E', 'G', 14);
    g1.addEdge('F', 'G', 8);
    
    g1.printAdjacencyMatrix();
    std::cout << std::endl;
    g1.printAdjacencyList();
    std::cout << std::endl;
    
    g1.BFS('A');
    g1.DFS('A');
    std::cout << std::endl;
    
    g1.dijkstra('A');
    std::cout << std::endl;
    
    g1.primMST('A');
    std::cout << std::endl;
    
    GraphViz::generateGraphVizFile(g1, "graph1.dot", "Graph 1");
}

void testGraph2() {
    std::cout << "=== 图2测试 ===" << std::endl;
    printTextGraph2();
    
    Graph g2(8);
    
    g2.setVertexLabel(0, 'A');
    g2.setVertexLabel(1, 'B');
    g2.setVertexLabel(2, 'C');
    g2.setVertexLabel(3, 'D');
    g2.setVertexLabel(4, 'E');
    g2.setVertexLabel(5, 'F');
    g2.setVertexLabel(6, 'G');
    g2.setVertexLabel(7, 'H');
    
    g2.addEdge('A', 'B', 6);
    g2.addEdge('A', 'D', 2);
    g2.addEdge('B', 'C', 4);
    g2.addEdge('B', 'E', 13);
    g2.addEdge('C', 'F', 12);
    g2.addEdge('D', 'E', 1);
    g2.addEdge('D', 'G', 11);
    g2.addEdge('E', 'F', 9);
    g2.addEdge('E', 'H', 14);
    g2.addEdge('F', 'H', 5);
    g2.addEdge('G', 'H', 3);
    
    g2.printAdjacencyMatrix();
    std::cout << std::endl;
    g2.printAdjacencyList();
    std::cout << std::endl;
    
    std::cout << "从不同起点查找关节点:" << std::endl;
    g2.findArticulationPoints();
    
    std::cout << std::endl;
    std::cout << "说明: 关节点与起点选择无关，结果应该一致" << std::endl;
    
    GraphViz::generateGraphVizFile(g2, "graph2.dot", "Graph 2");
}




int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "          图算法实验" << std::endl;
    std::cout << "========================================" << std::endl;
    
    testGraph1();
    
    std::cout << "========================================" << std::endl;
    
    testGraph2();
    
    std::cout << "========================================" << std::endl;
    
   
    
    return 0;
}
