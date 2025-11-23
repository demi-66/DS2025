#include "Huffman.h"
#include <iostream>
#include <string>
#include <map>
#include <cctype>

std::map<char, int> countFrequency(const std::string& text) {
    std::map<char, int> freq;
    for (size_t i = 0; i < text.length(); i++) {
        char c = tolower(text[i]);
        if (isalpha(c)) {
            freq[c]++;
        }
    }
    return freq;
}

int main() {
    std::string speech = 
        "I have a dream that one day this nation will rise up and live out the true meaning of its creed "
        "We hold these truths to be self evident that all men are created equal";
    
    std::cout << "=== Huffman编码实验 ===" << std::endl;
    
    // 统计频率
    std::map<char, int> freqMap = countFrequency(speech);
    std::cout << "字符频率统计:" << std::endl;
    std::map<char, int>::iterator it;
    for (it = freqMap.begin(); it != freqMap.end(); ++it) {
        std::cout << "'" << it->first << "': " << it->second << "次" << std::endl;
    }
    
    // 构建Huffman树
    HuffTree huffTree;
    huffTree.build(freqMap);
    
    // 显示编码
    huffTree.displayCodes();
    
    // 测试编码
    std::vector<std::string> testWords;
    testWords.push_back("dream");
    testWords.push_back("freedom");
    testWords.push_back("justice");
    testWords.push_back("equal");
    
    std::cout << "\n单词编码结果:" << std::endl;
    for (size_t i = 0; i < testWords.size(); i++) {
        std::string encoded = huffTree.encode(testWords[i]);
        std::cout << testWords[i] << " -> " << encoded << std::endl;
    }
    
    return 0;
}
