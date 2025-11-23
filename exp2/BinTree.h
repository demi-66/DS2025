#ifndef BINTREE_H
#define BINTREE_H

struct HuffNode {
    char data;
    int weight;
    HuffNode* parent;
    HuffNode* lc;
    HuffNode* rc;
    
    HuffNode(char d, int w) {
        data = d;
        weight = w;
        parent = 0;
        lc = 0;
        rc = 0;
    }
    
    bool isLeaf() {
        return lc == 0 && rc == 0;
    }
};

class BinTree {
public:
    HuffNode* root;
    int size;
    
    BinTree() {
        root = 0;
        size = 0;
    }
    
    HuffNode* insertAsRoot(char data, int weight) {
        root = new HuffNode(data, weight);
        size = 1;
        return root;
    }
    
    HuffNode* insertAsLC(HuffNode* parent, char data, int weight) {
        if (parent == 0) return 0;
        parent->lc = new HuffNode(data, weight);
        parent->lc->parent = parent;
        size++;
        return parent->lc;
    }
    
    HuffNode* insertAsRC(HuffNode* parent, char data, int weight) {
        if (parent == 0) return 0;
        parent->rc = new HuffNode(data, weight);
        parent->rc->parent = parent;
        size++;
        return parent->rc;
    }
};

#endif
