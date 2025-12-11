#ifndef SORTINGALGORITHMS_H
#define SORTINGALGORITHMS_H

#include "BoundingBox.h"
#include <vector>
#include <algorithm>
#include <ctime>
#include <stack>
#include <iostream>

// 定义比较函数（用于std::sort）
struct CompareByConfidenceDesc {
    bool operator()(const BoundingBox& a, const BoundingBox& b) const {
        return a.confidence > b.confidence;  // 降序排序
    }
};

class SortingAlgorithms {
private:
    // 快速排序的辅助函数
    static int partition(std::vector<BoundingBox>& boxes, int low, int high) {
        BoundingBox pivot = boxes[high];
        int i = low - 1;
        
        for (int j = low; j <= high - 1; j++) {
            if (boxes[j].confidence > pivot.confidence) {  // 降序排序
                i++;
                std::swap(boxes[i], boxes[j]);
            }
        }
        std::swap(boxes[i + 1], boxes[high]);
        return i + 1;
    }
    
    // 归并排序的合并函数
    static void merge(std::vector<BoundingBox>& boxes, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        
        // 创建临时数组
        std::vector<BoundingBox> leftArr(n1);
        std::vector<BoundingBox> rightArr(n2);
        
        for (int i = 0; i < n1; i++)
            leftArr[i] = boxes[left + i];
        for (int j = 0; j < n2; j++)
            rightArr[j] = boxes[mid + 1 + j];
        
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (leftArr[i].confidence > rightArr[j].confidence) {  // 降序排序
                boxes[k] = leftArr[i];
                i++;
            } else {
                boxes[k] = rightArr[j];
                j++;
            }
            k++;
        }
        
        while (i < n1) {
            boxes[k] = leftArr[i];
            i++;
            k++;
        }
        
        while (j < n2) {
            boxes[k] = rightArr[j];
            j++;
            k++;
        }
    }
    
    // 堆排序的堆化函数
    static void heapify(std::vector<BoundingBox>& boxes, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        
        if (left < n && boxes[left].confidence > boxes[largest].confidence)
            largest = left;
        
        if (right < n && boxes[right].confidence > boxes[largest].confidence)
            largest = right;
        
        if (largest != i) {
            std::swap(boxes[i], boxes[largest]);
            heapify(boxes, n, largest);
        }
    }
    
public:
    // 1. 快速排序
    static void quickSort(std::vector<BoundingBox>& boxes) {
        if (boxes.empty()) return;
        
        // 使用栈实现非递归快速排序，避免递归深度问题
        std::stack<std::pair<int, int> > stk;
        int low = 0;
        int high = static_cast<int>(boxes.size()) - 1;
        stk.push(std::make_pair(low, high));
        
        while (!stk.empty()) {
            low = stk.top().first;
            high = stk.top().second;
            stk.pop();
            
            if (low < high) {
                int pi = partition(boxes, low, high);
                
                // 压入左右子数组
                if (pi - 1 > low) {
                    stk.push(std::make_pair(low, pi - 1));
                }
                if (pi + 1 < high) {
                    stk.push(std::make_pair(pi + 1, high));
                }
            }
        }
    }
    
    // 2. 归并排序
    static void mergeSort(std::vector<BoundingBox>& boxes) {
        if (boxes.empty()) return;
        
        mergeSortHelper(boxes, 0, static_cast<int>(boxes.size()) - 1);
    }
    
    static void mergeSortHelper(std::vector<BoundingBox>& boxes, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(boxes, left, mid);
            mergeSortHelper(boxes, mid + 1, right);
            merge(boxes, left, mid, right);
        }
    }
    
    // 3. 堆排序
    static void heapSort(std::vector<BoundingBox>& boxes) {
        if (boxes.empty()) return;
        
        int n = static_cast<int>(boxes.size());
        
        // 构建最大堆
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(boxes, n, i);
        
        // 逐个提取元素
        for (int i = n - 1; i > 0; i--) {
            std::swap(boxes[0], boxes[i]);
            heapify(boxes, i, 0);
        }
    }
    
    // 4. 插入排序
    static void insertionSort(std::vector<BoundingBox>& boxes) {
        if (boxes.empty()) return;
        
        int n = static_cast<int>(boxes.size());
        
        for (int i = 1; i < n; i++) {
            BoundingBox key = boxes[i];
            int j = i - 1;
            
            while (j >= 0 && boxes[j].confidence < key.confidence) {  // 降序排序
                boxes[j + 1] = boxes[j];
                j--;
            }
            boxes[j + 1] = key;
        }
    }
    
    // 5. 冒泡排序
    static void bubbleSort(std::vector<BoundingBox>& boxes) {
        if (boxes.empty()) return;
        
        int n = static_cast<int>(boxes.size());
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (boxes[j].confidence < boxes[j + 1].confidence) {  // 降序排序
                    std::swap(boxes[j], boxes[j + 1]);
                }
            }
        }
    }
    
    // 6. 标准库排序（使用函数对象，兼容C++98）
    static void stdSort(std::vector<BoundingBox>& boxes) {
        if (boxes.empty()) return;
        
        std::sort(boxes.begin(), boxes.end(), CompareByConfidenceDesc());
    }
    
    // 测试排序算法性能
    static double timeSort(void (*func)(std::vector<BoundingBox>&), const std::vector<BoundingBox>& boxes) {
        std::vector<BoundingBox> boxesCopy = boxes;
        clock_t start = clock();
        func(boxesCopy);
        clock_t end = clock();
        return double(end - start) / CLOCKS_PER_SEC * 1000.0;
    }
};

#endif
