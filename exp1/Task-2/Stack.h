#ifndef STACK_H
#define STACK_H

#include <vector>
#include <stdexcept>

template<typename T>
class Stack {
private:
    std::vector<T> data;

public:
    void push(const T& value) {
        data.push_back(value);
    }
    
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack underflow");
        }
        T value = data.back();
        data.pop_back();
        return value;
    }
    
    T& top() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return data.back();
    }
    
    bool isEmpty() const {
        return data.empty();
    }
    
    size_t size() const {
        return data.size();
    }
};

#endif
