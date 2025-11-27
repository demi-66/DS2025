#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>

class Solution {
public:
    // 单调栈解法
    int largestRectangleArea(const std::vector<int>& heights) {
        int n = heights.size();
        if (n == 0) return 0;
        
        std::vector<int> left(n), right(n);
        std::stack<int> st;
        
        // 计算左边界
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                st.pop();
            }
            left[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
        
        // 清空栈
        while (!st.empty()) st.pop();
        
        // 计算右边界
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && heights[st.top()] >= heights[i]) {
                st.pop();
            }
            right[i] = st.empty() ? n : st.top();
            st.push(i);
        }
        
        // 计算最大面积
        int maxArea = 0;
        for (int i = 0; i < n; ++i) {
            int width = right[i] - left[i] - 1;
            maxArea = std::max(maxArea, heights[i] * width);
        }
        
        return maxArea;
    }
};

// 生成随机测试数据
std::vector<std::vector<int> > generateTestData(int numTests, int maxSize, int maxHeight) {
    std::vector<std::vector<int> > testData;
    std::srand(std::time(0));
    
    for (int i = 0; i < numTests; ++i) {
        int size = 1 + std::rand() % maxSize;
        std::vector<int> heights;
        for (int j = 0; j < size; ++j) {
            heights.push_back(std::rand() % (maxHeight + 1));
        }
        testData.push_back(heights);
    }
    
    return testData;
}

int main() {
    Solution sol;
    
    std::cout << "=== 柱状图最大矩形面积测试 ===" << std::endl;
    
    // 测试示例
    std::vector<int> test1;
    test1.push_back(2);
    test1.push_back(1);
    test1.push_back(5);
    test1.push_back(6);
    test1.push_back(2);
    test1.push_back(3);
    
    std::vector<int> test2;
    test2.push_back(2);
    test2.push_back(4);
    
    int result1 = sol.largestRectangleArea(test1);
    int result2 = sol.largestRectangleArea(test2);
    
    std::cout << "示例1 [2,1,5,6,2,3]: " << result1 << std::endl;
    std::cout << "示例2 [2,4]: " << result2 << std::endl;
    
    // 随机测试
    std::cout << "\n随机测试:" << std::endl;
    std::vector<std::vector<int> > randomTests = generateTestData(10, 1000, 100);
    
    for (int i = 0; i < randomTests.size(); ++i) {
        int result = sol.largestRectangleArea(randomTests[i]);
        std::cout << "测试 " << i + 1 << ": 大小=" << randomTests[i].size() 
                  << ", 最大面积=" << result << std::endl;
    }
    
    return 0;
}
