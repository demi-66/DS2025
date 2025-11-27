#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "Stack.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cctype>
#include <sstream>
#include <map>

class Calculator {
private:
    std::map<char, int> priority;

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')';
    }

    double calculate(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if (b == 0) throw std::runtime_error("Division by zero");
                return a / b;
            case '^': return std::pow(a, b);
            default: throw std::runtime_error("Unknown operator");
        }
    }

    std::string infixToPostfix(const std::string& infix) {
        Stack<char> opStack;
        std::string postfix;
        
        for (size_t i = 0; i < infix.length(); ++i) {
            char c = infix[i];
            
            if (std::isspace(c)) continue;
            
            if (std::isdigit(c) || c == '.') {
                while (i < infix.length() && (std::isdigit(infix[i]) || infix[i] == '.')) {
                    postfix += infix[i++];
                }
                postfix += ' ';
                i--;
            }
            else if (c == '(') {
                opStack.push(c);
            }
            else if (c == ')') {
                while (!opStack.isEmpty() && opStack.top() != '(') {
                    postfix += opStack.pop();
                    postfix += ' ';
                }
                if (opStack.isEmpty()) {
                    throw std::runtime_error("Mismatched parentheses");
                }
                opStack.pop();
            }
            else if (isOperator(c)) {
                while (!opStack.isEmpty() && priority[opStack.top()] >= priority[c]) {
                    postfix += opStack.pop();
                    postfix += ' ';
                }
                opStack.push(c);
            }
            else {
                throw std::runtime_error("Invalid character in expression");
            }
        }
        
        while (!opStack.isEmpty()) {
            if (opStack.top() == '(') {
                throw std::runtime_error("Mismatched parentheses");
            }
            postfix += opStack.pop();
            postfix += ' ';
        }
        
        return postfix;
    }

    double evaluatePostfix(const std::string& postfix) {
        Stack<double> numStack;
        std::istringstream iss(postfix);
        std::string token;
        
        while (iss >> token) {
            if (token.length() == 1 && isOperator(token[0])) {
                if (numStack.size() < 2) {
                    throw std::runtime_error("Invalid expression");
                }
                double b = numStack.pop();
                double a = numStack.pop();
                double result = calculate(a, b, token[0]);
                numStack.push(result);
            } else {
                double num = atof(token.c_str());
                numStack.push(num);
            }
        }
        
        if (numStack.size() != 1) {
            throw std::runtime_error("Invalid expression");
        }
        
        return numStack.pop();
    }

public:
    Calculator() {
        priority['+'] = 1;
        priority['-'] = 1;
        priority['*'] = 2;
        priority['/'] = 2;
        priority['^'] = 3;
        priority['('] = 0;
    }

    double evaluate(const std::string& expression) {
        try {
            std::string postfix = infixToPostfix(expression);
            std::cout << "后缀表达式: " << postfix << std::endl;
            return evaluatePostfix(postfix);
        } catch (const std::exception& e) {
            throw std::runtime_error("计算错误: " + std::string(e.what()));
        }
    }
};

#endif
