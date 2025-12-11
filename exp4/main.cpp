#include "SortingAlgorithms.h"
#include "NMS.h"
#include "DataGenerator.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// 定义函数指针类型
typedef void (*SortFunction)(std::vector<BoundingBox>&);

void testSortingPerformance() {
    std::cout << "==========================================" << std::endl;
    std::cout << "        排序算法性能测试" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    // 测试不同规模的数据
    std::vector<int> testSizes;
    testSizes.push_back(100);
    testSizes.push_back(500);
    testSizes.push_back(1000);
    testSizes.push_back(5000);
    testSizes.push_back(10000);
    
    std::cout << std::fixed << std::setprecision(3);
    
    for (size_t sizeIdx = 0; sizeIdx < testSizes.size(); sizeIdx++) {
        int size = testSizes[sizeIdx];
        std::cout << "\n=== 数据规模: " << size << " 个边界框 ===" << std::endl;
        
        // 测试随机分布
        std::cout << "\n[随机分布]" << std::endl;
        std::vector<BoundingBox> randomBoxes = DataGenerator::generateRandomBoxes(size);
        DataGenerator::printDatasetInfo(randomBoxes, "随机分布");
        
        // 测试每种排序算法
        std::cout << "排序算法性能 (单位: 毫秒):" << std::endl;
        
        double time1 = SortingAlgorithms::timeSort(SortingAlgorithms::quickSort, randomBoxes);
        std::cout << "快速排序: " << time1 << " ms" << std::endl;
        
        double time2 = SortingAlgorithms::timeSort(SortingAlgorithms::mergeSort, randomBoxes);
        std::cout << "归并排序: " << time2 << " ms" << std::endl;
        
        double time3 = SortingAlgorithms::timeSort(SortingAlgorithms::heapSort, randomBoxes);
        std::cout << "堆排序:   " << time3 << " ms" << std::endl;
        
        double time4 = SortingAlgorithms::timeSort(SortingAlgorithms::insertionSort, randomBoxes);
        std::cout << "插入排序: " << time4 << " ms" << std::endl;
        
        double time5 = SortingAlgorithms::timeSort(SortingAlgorithms::stdSort, randomBoxes);
        std::cout << "标准库排序: " << time5 << " ms" << std::endl;
        
        if (size <= 2000) {  // 冒泡排序只在小数据量测试
            double time6 = SortingAlgorithms::timeSort(SortingAlgorithms::bubbleSort, randomBoxes);
            std::cout << "冒泡排序: " << time6 << " ms" << std::endl;
        }
        
        // 测试聚集分布
        std::cout << "\n[聚集分布]" << std::endl;
        std::vector<BoundingBox> clusteredBoxes = DataGenerator::generateClusteredBoxes(size);
        DataGenerator::printDatasetInfo(clusteredBoxes, "聚集分布");
        
        std::cout << "排序算法性能 (单位: 毫秒):" << std::endl;
        
        time1 = SortingAlgorithms::timeSort(SortingAlgorithms::quickSort, clusteredBoxes);
        std::cout << "快速排序: " << time1 << " ms" << std::endl;
        
        time2 = SortingAlgorithms::timeSort(SortingAlgorithms::mergeSort, clusteredBoxes);
        std::cout << "归并排序: " << time2 << " ms" << std::endl;
        
        time3 = SortingAlgorithms::timeSort(SortingAlgorithms::heapSort, clusteredBoxes);
        std::cout << "堆排序:   " << time3 << " ms" << std::endl;
        
        time4 = SortingAlgorithms::timeSort(SortingAlgorithms::insertionSort, clusteredBoxes);
        std::cout << "插入排序: " << time4 << " ms" << std::endl;
        
        time5 = SortingAlgorithms::timeSort(SortingAlgorithms::stdSort, clusteredBoxes);
        std::cout << "标准库排序: " << time5 << " ms" << std::endl;
        
        if (size <= 2000) {
            double time6 = SortingAlgorithms::timeSort(SortingAlgorithms::bubbleSort, clusteredBoxes);
            std::cout << "冒泡排序: " << time6 << " ms" << std::endl;
        }
    }
}

void testNMSPerformance() {
    std::cout << "\n==========================================" << std::endl;
    std::cout << "        NMS算法性能测试" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    NMS nmsProcessor(0.5f);
    
    // 测试不同排序算法在NMS中的性能
    std::vector<int> testSizes;
    testSizes.push_back(100);
    testSizes.push_back(500);
    testSizes.push_back(1000);
    testSizes.push_back(2000);
    
    for (size_t sizeIdx = 0; sizeIdx < testSizes.size(); sizeIdx++) {
        int size = testSizes[sizeIdx];
        std::cout << "\n=== 数据规模: " << size << " 个边界框 ===" << std::endl;
        
        // 生成测试数据
        std::vector<BoundingBox> boxes = DataGenerator::generateClusteredBoxes(size);
        
        // 测试不同排序算法在NMS中的性能
        std::cout << "NMS处理时间 (包含排序时间):" << std::endl;
        
        clock_t start, end;
        
        // 1. 基础NMS（使用std::sort）
        start = clock();
        std::vector<BoundingBox> result0 = nmsProcessor.basicNMS(boxes);
        end = clock();
        std::cout << "基础NMS(std::sort): " << double(end - start) / CLOCKS_PER_SEC * 1000.0 
                  << " ms, 保留: " << result0.size() << " 个框" << std::endl;
        
        // 2. 使用快速排序的NMS
        start = clock();
        std::vector<BoundingBox> result1 = nmsProcessor.nmsWithSort(boxes, SortingAlgorithms::quickSort);
        end = clock();
        std::cout << "快速排序+NMS: " << double(end - start) / CLOCKS_PER_SEC * 1000.0 
                  << " ms, 保留: " << result1.size() << " 个框" << std::endl;
        
        // 3. 使用归并排序的NMS
        start = clock();
        std::vector<BoundingBox> result2 = nmsProcessor.nmsWithSort(boxes, SortingAlgorithms::mergeSort);
        end = clock();
        std::cout << "归并排序+NMS: " << double(end - start) / CLOCKS_PER_SEC * 1000.0 
                  << " ms, 保留: " << result2.size() << " 个框" << std::endl;
        
        // 4. 使用堆排序的NMS
        start = clock();
        std::vector<BoundingBox> result3 = nmsProcessor.nmsWithSort(boxes, SortingAlgorithms::heapSort);
        end = clock();
        std::cout << "堆排序+NMS:   " << double(end - start) / CLOCKS_PER_SEC * 1000.0 
                  << " ms, 保留: " << result3.size() << " 个框" << std::endl;
        
        if (size <= 1000) {
            // 5. 使用插入排序的NMS（只在小数据量测试）
            start = clock();
            std::vector<BoundingBox> result4 = nmsProcessor.nmsWithSort(boxes, SortingAlgorithms::insertionSort);
            end = clock();
            std::cout << "插入排序+NMS: " << double(end - start) / CLOCKS_PER_SEC * 1000.0 
                      << " ms, 保留: " << result4.size() << " 个框" << std::endl;
        }
    }
}

int main() {
    // 设置随机种子
    std::srand(static_cast<unsigned int>(std::time(0)));
    
    
    // 1. 测试排序算法性能
    testSortingPerformance();
    
    // 2. 测试NMS算法性能
    testNMSPerformance();
    
    std::cout << "\n==========================================" << std::endl;
    std::cout << "            实验完成" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    return 0;
}
