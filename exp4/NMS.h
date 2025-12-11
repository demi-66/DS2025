#ifndef NMS_H
#define NMS_H

#include "BoundingBox.h"
#include "SortingAlgorithms.h"
#include <vector>
#include <algorithm>

class NMS {
private:
    float iouThreshold;
    
public:
    NMS(float threshold = 0.5f) : iouThreshold(threshold) {}
    
    // 基础NMS算法
    std::vector<BoundingBox> basicNMS(std::vector<BoundingBox>& boxes) {
        std::vector<BoundingBox> result;
        
        if (boxes.empty()) return result;
        
        // 按置信度降序排序
        std::vector<BoundingBox> sortedBoxes = boxes;
        SortingAlgorithms::stdSort(sortedBoxes);
        
        while (!sortedBoxes.empty()) {
            // 取出置信度最高的边界框
            BoundingBox current = sortedBoxes[0];
            result.push_back(current);
            sortedBoxes.erase(sortedBoxes.begin());
            
            // 移除与当前框IoU大于阈值的框
            std::vector<BoundingBox> remaining;
            for (size_t i = 0; i < sortedBoxes.size(); i++) {
                if (current.iou(sortedBoxes[i]) <= iouThreshold) {
                    remaining.push_back(sortedBoxes[i]);
                }
            }
            sortedBoxes = remaining;
        }
        
        return result;
    }
    
    // 使用指定排序算法的NMS
    std::vector<BoundingBox> nmsWithSort(std::vector<BoundingBox>& boxes, void (*sortFunc)(std::vector<BoundingBox>&)) {
        std::vector<BoundingBox> result;
        
        if (boxes.empty()) return result;
        
        std::vector<BoundingBox> sortedBoxes = boxes;
        
        // 使用指定的排序算法
        sortFunc(sortedBoxes);
        
        while (!sortedBoxes.empty()) {
            BoundingBox current = sortedBoxes[0];
            result.push_back(current);
            sortedBoxes.erase(sortedBoxes.begin());
            
            std::vector<BoundingBox> remaining;
            for (size_t i = 0; i < sortedBoxes.size(); i++) {
                if (current.iou(sortedBoxes[i]) <= iouThreshold) {
                    remaining.push_back(sortedBoxes[i]);
                }
            }
            sortedBoxes = remaining;
        }
        
        return result;
    }
    
    // 获取NMS后的边界框数量
    int getNMSResultCount(const std::vector<BoundingBox>& boxes) {
        std::vector<BoundingBox> nmsResult = basicNMS(const_cast<std::vector<BoundingBox>&>(boxes));
        return static_cast<int>(nmsResult.size());
    }
};

#endif
