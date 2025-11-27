#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}
    
    double getReal() const { return real; }
    double getImag() const { return imag; }
    double getMod() const { return std::sqrt(real * real + imag * imag); }
    
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
    
    bool operator<(const Complex& other) const {
        double mod1 = getMod();
        double mod2 = other.getMod();
        if (mod1 != mod2) return mod1 < mod2;
        return real < other.real;
    }
    
    bool operator>(const Complex& other) const {
        return other < *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << " + " << c.imag << "i)";
    return os;
}

// 生成随机复数向量
std::vector<Complex> generateRandomComplexVector(int size, double minVal = -10.0, double maxVal = 10.0) {
    std::vector<Complex> vec;
    std::srand(std::time(0));
    
    for (int i = 0; i < size; ++i) {
        double r = minVal + (maxVal - minVal) * (std::rand() / (RAND_MAX + 1.0));
        double i_val = minVal + (maxVal - minVal) * (std::rand() / (RAND_MAX + 1.0));
        vec.push_back(Complex(r, i_val));
    }
    return vec;
}

// 置乱向量
template<typename T>
void shuffleVector(std::vector<T>& vec) {
    for (size_t i = vec.size() - 1; i > 0; --i) {
        size_t j = std::rand() % (i + 1);
        std::swap(vec[i], vec[j]);
    }
}

// 查找元素
template<typename T>
int findElement(const std::vector<T>& vec, const T& target) {
    for (size_t i = 0; i < vec.size(); ++i) {
        if (vec[i] == target) return i;
    }
    return -1;
}

// 唯一化
template<typename T>
void uniquifyVector(std::vector<T>& vec) {
    // 先排序
    for (size_t i = 0; i < vec.size(); ++i) {
        for (size_t j = i + 1; j < vec.size(); ++j) {
            if (vec[j] < vec[i]) {
                std::swap(vec[i], vec[j]);
            }
        }
    }
    
    // 再去重
    size_t write_index = 0;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i == 0 || !(vec[i] == vec[i - 1])) {
            vec[write_index++] = vec[i];
        }
    }
    vec.resize(write_index);
}

// 起泡排序
template<typename T>
void bubbleSort(std::vector<T>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (vec[j] > vec[j + 1]) {
                std::swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// 归并排序辅助函数
template<typename T>
void merge(std::vector<T>& vec, int left, int mid, int right) {
    std::vector<T> temp;
    int i = left, j = mid + 1;
    
    while (i <= mid && j <= right) {
        if (vec[i] < vec[j]) {
            temp.push_back(vec[i++]);
        } else {
            temp.push_back(vec[j++]);
        }
    }
    
    while (i <= mid) temp.push_back(vec[i++]);
    while (j <= right) temp.push_back(vec[j++]);
    
    for (size_t k = 0; k < temp.size(); ++k) {
        vec[left + k] = temp[k];
    }
}

// 归并排序
template<typename T>
void mergeSort(std::vector<T>& vec, int left, int right) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    mergeSort(vec, left, mid);
    mergeSort(vec, mid + 1, right);
    merge(vec, left, mid, right);
}

template<typename T>
void mergeSort(std::vector<T>& vec) {
    if (!vec.empty()) {
        mergeSort(vec, 0, vec.size() - 1);
    }
}

// 区间查找
std::vector<Complex> rangeSearch(const std::vector<Complex>& vec, double m1, double m2) {
    std::vector<Complex> result;
    for (size_t i = 0; i < vec.size(); ++i) {
        double mod = vec[i].getMod();
        if (mod >= m1 && mod <= m2) {
            result.push_back(vec[i]);
        }
    }
    return result;
}

#endif