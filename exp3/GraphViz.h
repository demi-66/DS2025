#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include "Graph.h"
#include <fstream>
#include <string>

class GraphViz {
public:
    static void generateGraphVizFile(const Graph& graph, const std::string& filename, const std::string& title = "Graph") {
        std::ofstream file(filename.c_str());
        file << "/* " << title << " */" << std::endl;
        file << "graph G {" << std::endl;
        file << "  label=\"" << title << "\";" << std::endl;
        file << "  labelloc=t;" << std::endl;
        file << "  fontsize=20;" << std::endl;
        file << "  layout=neato;" << std::endl;
        file << "  node [shape=circle, style=filled, color=lightblue, fontsize=14];" << std::endl;
        file << "  edge [fontsize=12];" << std::endl;
        
        int vertexCount = graph.getVertexCount();
        
        for (int i = 0; i < vertexCount; i++) {
            for (int j = i + 1; j < vertexCount; j++) {
                int weight = graph.getWeight(i, j);
                if (weight != 0) {
                    file << "  " << graph.getVertexLabel(i) 
                         << " -- " << graph.getVertexLabel(j)
                         << " [label=\"" << weight << "\", len=2.0];" 
                         << std::endl;
                }
            }
        }
        
        file << "}" << std::endl;
        file.close();
        std::cout << "已生成可视化文件: " << filename << std::endl;
    }
};

#endif
