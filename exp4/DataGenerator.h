#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include "BoundingBox.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <algorithm>

class DataGenerator {
private:
    static const int IMAGE_WIDTH = 1000;
    static const int IMAGE_HEIGHT = 1000;
    static const int MIN_BOX_SIZE = 20;
    static const int MAX_BOX_SIZE = 100;
    
public:
    // 1. 随机分布生成
    static std::vector<BoundingBox> generateRandomBoxes(int count) {
        std::vector<BoundingBox> boxes;
        std::srand(static_cast<unsigned int>(std::time(0)));
        
        for (int i = 0; i < count; i++) {
            float width = static_cast<float>(MIN_BOX_SIZE + std::rand() % (MAX_BOX_SIZE - MIN_BOX_SIZE + 1));
            float height = static_cast<float>(MIN_BOX_SIZE + std::rand() % (MAX_BOX_SIZE - MIN_BOX_SIZE + 1));
            float x = static_cast<float>(std::rand() % (IMAGE_WIDTH - static_cast<int>(width)));
            float y = static_cast<float>(std::rand() % (IMAGE_HEIGHT - static_cast<int>(height)));
            
            // 生成合理的置信度（0.3-0.99）
            float confidence = 0.3f + static_cast<float>(std::rand() % 70) / 100.0f;
            
            boxes.push_back(BoundingBox(i, x, y, x + width, y + height, confidence));
        }
        
        return boxes;
    }
    
    // 2. 聚集分布生成（模拟目标检测中的密集场景）
    static std::vector<BoundingBox> generateClusteredBoxes(int count) {
        std::vector<BoundingBox> boxes;
        std::srand(static_cast<unsigned int>(std::time(0)));
        
        // 生成一些聚集中心
        int numClusters = std::max(3, count / 50);
        std::vector<std::pair<float, float> > centers;  // 注意 > > 之间有空格
        
        for (int i = 0; i < numClusters; i++) {
            float centerX = static_cast<float>(100 + std::rand() % (IMAGE_WIDTH - 200));
            float centerY = static_cast<float>(100 + std::rand() % (IMAGE_HEIGHT - 200));
            centers.push_back(std::make_pair(centerX, centerY));
        }
        
        for (int i = 0; i < count; i++) {
            // 随机选择一个聚集中心
            int clusterIdx = std::rand() % static_cast<int>(centers.size());
            float centerX = centers[clusterIdx].first;
            float centerY = centers[clusterIdx].second;
            
            // 在中心周围生成边界框
            float offsetX = static_cast<float>((std::rand() % 200) - 100);  // ±100像素
            float offsetY = static_cast<float>((std::rand() % 200) - 100);
            
            float width = static_cast<float>(MIN_BOX_SIZE + std::rand() % (MAX_BOX_SIZE - MIN_BOX_SIZE + 1));
            float height = static_cast<float>(MIN_BOX_SIZE + std::rand() % (MAX_BOX_SIZE - MIN_BOX_SIZE + 1));
            
            float x = centerX + offsetX;
            float y = centerY + offsetY;
            
            // 确保边界框在图像内
            x = std::max(0.0f, std::min(x, static_cast<float>(IMAGE_WIDTH - width - 1)));
            y = std::max(0.0f, std::min(y, static_cast<float>(IMAGE_HEIGHT - height - 1)));
            
            // 聚集区域通常有更高的置信度变化
            float confidence = 0.4f + static_cast<float>(std::rand() % 60) / 100.0f;
            
            boxes.push_back(BoundingBox(i, x, y, x + width, y + height, confidence));
        }
        
        return boxes;
    }
    
    // 显示数据集信息
    static void printDatasetInfo(const std::vector<BoundingBox>& boxes, const std::string& type) {
        std::cout << "=== " << type << "数据集 ===" << std::endl;
        std::cout << "边界框数量: " << boxes.size() << std::endl;
        
        if (!boxes.empty()) {
            float avgConfidence = 0;
            float avgArea = 0;
            float minConfidence = 1.0f;
            float maxConfidence = 0;
            
            for (size_t i = 0; i < boxes.size(); i++) {
                avgConfidence += boxes[i].confidence;
                avgArea += boxes[i].area;
                if (boxes[i].confidence < minConfidence) minConfidence = boxes[i].confidence;
                if (boxes[i].confidence > maxConfidence) maxConfidence = boxes[i].confidence;
            }
            
            avgConfidence /= static_cast<float>(boxes.size());
            avgArea /= static_cast<float>(boxes.size());
            
            std::cout << "平均置信度: " << avgConfidence << std::endl;
            std::cout << "置信度范围: " << minConfidence << " ~ " << maxConfidence << std::endl;
            std::cout << "平均面积: " << avgArea << std::endl;
        }
        std::cout << std::endl;
    }
};

#endif
