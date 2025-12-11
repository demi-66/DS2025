#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <iostream>
#include <cmath>

class BoundingBox {
public:
    int id;
    float x1, y1, x2, y2;  // 左上角和右下角坐标
    float confidence;      // 置信度
    float area;           // 面积
    
    BoundingBox(int id = 0, float x1 = 0, float y1 = 0, 
                float x2 = 0, float y2 = 0, float confidence = 0)
        : id(id), x1(x1), y1(y1), x2(x2), y2(y2), confidence(confidence) {
        area = calculateArea();
    }
    
    // 计算面积
    float calculateArea() const {
        return std::max(0.0f, (x2 - x1) * (y2 - y1));
    }
    
    // 计算与另一个边界框的IoU
    float iou(const BoundingBox& other) const {
        float interX1 = std::max(x1, other.x1);
        float interY1 = std::max(y1, other.y1);
        float interX2 = std::min(x2, other.x2);
        float interY2 = std::min(y2, other.y2);
        
        float interWidth = std::max(0.0f, interX2 - interX1);
        float interHeight = std::max(0.0f, interY2 - interY1);
        float interArea = interWidth * interHeight;
        
        float unionArea = area + other.area - interArea;
        
        if (unionArea == 0) return 0;
        return interArea / unionArea;
    }
    
    // 重载运算符用于比较
    bool operator<(const BoundingBox& other) const {
        return confidence < other.confidence;
    }
    
    bool operator>(const BoundingBox& other) const {
        return confidence > other.confidence;
    }
    
    // 显示边界框信息
    void display() const {
        std::cout << "Box " << id << ": (" << x1 << ", " << y1 << ") - (" 
                  << x2 << ", " << y2 << "), conf: " << confidence 
                  << ", area: " << area << std::endl;
    }
};

#endif
