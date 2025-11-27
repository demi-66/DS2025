#include "Calculator.h"
#include <iostream>
#include <vector>
#include <string>

void testCalculator() {
    Calculator calc;

    std::cout << "=== 字符串计算器测试 ===" << std::endl;

    // 兼容旧编译器的初始化方式
    std::vector<std::string> testCases;
    testCases.push_back("3 + 4 * 2");
    testCases.push_back("(3 + 4) * 2");
    testCases.push_back("10 / 2 - 1");
    testCases.push_back("2 ^ 3 + 1");
    testCases.push_back("1 + 2 * (3 - 1)");
    testCases.push_back("5 * (2 + 3) / 5");

    for (size_t i = 0; i < testCases.size(); ++i) {
        try {
            std::cout << "表达式: " << testCases[i] << std::endl;
            double result = calc.evaluate(testCases[i]);
            std::cout << "结果: " << result << std::endl;
            std::cout << "------------------------" << std::endl;
        } catch (const std::exception& e) {
            std::cout << "错误: " << e.what() << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
}

int main() {
    testCalculator();
    
    // 交互式计算
    Calculator calc;
    std::string input;
    std::cout << "\n=== 交互式计算 ===" << std::endl;
    std::cout << "输入表达式 (输入 'quit' 退出):" << std::endl;
    
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        
        if (input == "quit" || input == "exit") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }
        
        try {
            double result = calc.evaluate(input);
            std::cout << "结果: " << result << std::endl;
        } catch (const std::exception& e) {
            std::cout << "错误: " << e.what() << std::endl;
        }
    }
    
    return 0;
}
