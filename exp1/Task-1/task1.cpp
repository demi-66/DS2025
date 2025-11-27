#include "Complex.h"
#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>

void testComplexOperations() {
    std::cout << "=== 测试复数向量基本操作 ===" << std::endl;
    
    // 生成随机复数向量
    std::vector<Complex> vec = generateRandomComplexVector(8, -5, 5);
    std::cout << "原始向量: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    // 置乱
    shuffleVector(vec);
    std::cout << "置乱后: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    // 查找
    if (vec.size() > 3) {
        Complex target = vec[3];
        int index = findElement(vec, target);
        std::cout << "查找 " << target << " 在位置: " << index << std::endl;
    }
    
    // 插入
    Complex newComplex(7.5, 8.5);
    if (vec.size() > 2) {
        vec.insert(vec.begin() + 2, newComplex);
    }
    std::cout << "插入后: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    // 删除
    if (vec.size() > 2) {
        vec.erase(vec.begin() + 2);
    }
    std::cout << "删除后: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
    
    // 唯一化
    if (!vec.empty()) {
        vec.push_back(vec[0]); // 添加重复项
    }
    uniquifyVector(vec);
    std::cout << "唯一化后: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

void compareSortingEfficiency() {
    std::cout << "\n=== 比较排序效率 ===" << std::endl;
    
    const int SIZE = 500; // 减小规模以便更快看到结果
    
    // 顺序向量
    std::vector<Complex> sortedVec;
    for (int i = 0; i < SIZE; ++i) {
        sortedVec.push_back(Complex(i, i));
    }
    
    // 乱序向量
    std::vector<Complex> randomVec = generateRandomComplexVector(SIZE, 0, 100);
    
    // 逆序向量
    std::vector<Complex> reverseVec;
    for (int i = SIZE - 1; i >= 0; --i) {
        reverseVec.push_back(Complex(i, i));
    }
    
    // 测试函数
    clock_t start, end;
    
    std::cout << "顺序向量:" << std::endl;
    
    std::vector<Complex> temp = sortedVec;
    start = clock();
    bubbleSort(temp);
    end = clock();
    std::cout << "起泡排序: " << std::fixed << std::setprecision(2) 
              << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
    
    temp = sortedVec;
    start = clock();
    mergeSort(temp);
    end = clock();
    std::cout << "归并排序: " << std::fixed << std::setprecision(2) 
              << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
    
    std::cout << "乱序向量:" << std::endl;
    
    temp = randomVec;
    start = clock();
    bubbleSort(temp);
    end = clock();
    std::cout << "起泡排序: " << std::fixed << std::setprecision(2) 
              << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
    
    temp = randomVec;
    start = clock();
    mergeSort(temp);
    end = clock();
    std::cout << "归并排序: " << std::fixed << std::setprecision(2) 
              << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
    
    std::cout << "逆序向量:" << std::endl;
    
    temp = reverseVec;
    start = clock();
    bubbleSort(temp);
    end = clock();
    std::cout << "起泡排序: " << std::fixed << std::setprecision(2) 
              << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
    
    temp = reverseVec;
    start = clock();
    mergeSort(temp);
    end = clock();
    std::cout << "归并排序: " << std::fixed << std::setprecision(2) 
              << (double)(end - start) / CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
}

void testRangeSearch() {
    std::cout << "\n=== 测试区间查找 ===" << std::endl;
    
    // 创建有序向量
    std::vector<Complex> sortedVec;
    for (int i = 0; i < 15; ++i) {
        sortedVec.push_back(Complex(i, i));
    }
    
    std::cout << "有序向量模值: ";
    for (size_t i = 0; i < sortedVec.size(); ++i) {
        std::cout << sortedVec[i].getMod() << " ";
    }
    std::cout << std::endl;
    
    // 区间查找
    double m1 = 5.0, m2 = 10.0;
    std::vector<Complex> result = rangeSearch(sortedVec, m1, m2);
    
    std::cout << "模在 [" << m1 << ", " << m2 << "] 范围内的复数:" << std::endl;
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << " (模=" << result[i].getMod() << ")" << std::endl;
    }
}

int main() {
    std::srand(std::time(0)); // 初始化随机数种子
    
    testComplexOperations();
    compareSortingEfficiency();
    testRangeSearch();
    
    return 0;
}
