#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "BinTree.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

class HuffTree {
private:
    BinTree* tree;
    std::map<char, std::string> codeMap;
    
    void generateCodes(HuffNode* node, std::string code) {
        if (node == 0) return;
        
        if (node->isLeaf()) {
            codeMap[node->data] = code;
            return;
        }
        
        generateCodes(node->lc, code + "0");
        generateCodes(node->rc, code + "1");
    }

public:
    HuffTree() {
        tree = 0;
    }
    
    void build(const std::map<char, int>& freqMap) {
        std::vector<HuffNode*> forest;
        
        // 创建叶子节点
        std::map<char, int>::const_iterator it;
        for (it = freqMap.begin(); it != freqMap.end(); ++it) {
            BinTree* bt = new BinTree();
            bt->insertAsRoot(it->first, it->second);
            forest.push_back(bt->root);
        }
        
        // 构建Huffman树
        while (forest.size() > 1) {
            // 按权重排序
            for (size_t i = 0; i < forest.size() - 1; i++) {
                for (size_t j = 0; j < forest.size() - i - 1; j++) {
                    if (forest[j]->weight > forest[j + 1]->weight) {
                        HuffNode* temp = forest[j];
                        forest[j] = forest[j + 1];
                        forest[j + 1] = temp;
                    }
                }
            }
            
            // 合并两个最小权重的树
            HuffNode* node1 = forest[0];
            HuffNode* node2 = forest[1];
            forest.erase(forest.begin());
            forest.erase(forest.begin());
            
            BinTree* newTree = new BinTree();
            HuffNode* parent = newTree->insertAsRoot('^', node1->weight + node2->weight);
            parent->lc = node1;
            parent->rc = node2;
            node1->parent = parent;
            node2->parent = parent;
            
            forest.push_back(parent);
        }
        
        tree = new BinTree();
        tree->root = forest[0];
        
        // 生成编码
        generateCodes(tree->root, "");
    }
    
    std::string encode(const std::string& text) {
        std::string result;
        for (size_t i = 0; i < text.length(); i++) {
            char c = tolower(text[i]);
            if (codeMap.find(c) != codeMap.end()) {
                result += codeMap[c];
            }
        }
        return result;
    }
    
    void displayCodes() {
        std::cout << "Huffman Codes:" << std::endl;
        std::map<char, std::string>::iterator it;
        for (it = codeMap.begin(); it != codeMap.end(); ++it) {
            std::cout << "'" << it->first << "': " << it->second << std::endl;
        }
    }
};

#endif
