/* 
    - AI Generated Test For Vector
*/
#include <iostream>
#include "Vector.h"

int main(){
    try {
        Vector<int> vec;
        
        std::cout << "=== Testing Empty Vector ===" << std::endl;
        std::cout << "Size: " << vec.size() << std::endl;
        std::cout << "Empty: " << (vec.empty() ? "true" : "false") << std::endl;
        
        std::cout << "\n=== Testing Push Back ===" << std::endl;
        vec.push_back(10);
        vec.push_back(20);
        vec.push_back(30);
        
        std::cout << "Size after push_back: " << vec.size() << std::endl;
        std::cout << "Contents: ";
        for(size_t i = 0; i < vec.size(); ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
        
        std::cout << "\n=== Testing Front/Back Access ===" << std::endl;
        std::cout << "Front: " << vec.front() << std::endl;
        std::cout << "Back: " << vec.back() << std::endl;
        
        std::cout << "\n=== Testing Pop Operations ===" << std::endl;
        std::cout << "Popped back: " << vec.pop_back() << std::endl;
        std::cout << "Size after pop_back: " << vec.size() << std::endl;
        
        std::cout << "Popped front: " << vec.pop_front() << std::endl;
        std::cout << "Size after pop_front: " << vec.size() << std::endl;
        std::cout << "Remaining element: " << vec[0] << std::endl;
        
        std::cout << "\n=== Testing Range-Based For Loop ===" << std::endl;
        vec.push_back(40);
        vec.push_back(50);
        std::cout << "Final contents: ";
        for(const auto& element : vec) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        
        std::cout << "\n=== Testing Copy Constructor ===" << std::endl;
        Vector<int> vec2 = vec;
        std::cout << "Copied vector: ";
        for(const auto& element : vec2) {
            std::cout << element << " ";
        }
        std::cout << "\nOriginal size: " << vec.size() << ", Copy size: " << vec2.size() << std::endl;
        
    } catch(const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    
    return 0;
}