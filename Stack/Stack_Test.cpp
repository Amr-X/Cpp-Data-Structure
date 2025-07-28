/* 
    - AI Generated Test For Stack
*/
#include <iostream>
#include "Stack.h"

int main(){
    try {
        Stack<int> stack;
        
        std::cout << "=== Testing Empty Stack ===" << std::endl;
        std::cout << "Empty: " << (stack.empty() ? "true" : "false") << std::endl;
        std::cout << "Size: " << stack.size() << std::endl;
        
        std::cout << "\n=== Testing Push Operations ===" << std::endl;
        stack.push(10);
        stack.push(20);
        stack.push(30);
        
        std::cout << "Size after pushes: " << stack.size() << std::endl;
        std::cout << "Empty: " << (stack.empty() ? "true" : "false") << std::endl;
        std::cout << "Top element: " << stack.top() << std::endl;
        
        std::cout << "\n=== Testing Pop Operations ===" << std::endl;
        std::cout << "Current top: " << stack.top() << std::endl;
        stack.pop();
        std::cout << "After pop, top: " << stack.top() << std::endl;
        std::cout << "Size after pop: " << stack.size() << std::endl;
        
        std::cout << "\n=== Testing LIFO Behavior ===" << std::endl;
        stack.push(40);
        stack.push(50);
        
        std::cout << "Stack contents (top to bottom): ";
        while (!stack.empty()) {
            std::cout << stack.top() << " ";
            stack.pop();
        }
        std::cout << std::endl;
        std::cout << "Final size: " << stack.size() << std::endl;
        
        std::cout << "\n=== Testing Exception Handling ===" << std::endl;
        std::cout << "Trying to pop from empty stack..." << std::endl;
        stack.pop();  // Should throw
        
    } catch (const std::underflow_error& e) {
        std::cout << "Caught underflow exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    return 0;
}