/* 
    - AI Generated Test For List Stack
*/
#include <iostream>
#include <string>
#include "List_Stack.h"

int main() {
    std::cout << "=== Stack Test ===" << std::endl;
    
    Stack<int> stack;
    
    // Test 1: Basic operations
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "After pushes - Size: " << stack.size() 
              << ", Top: " << stack.top() << std::endl;
    
    // Test 2: LIFO verification
    std::cout << "LIFO order: ";
    Stack<int> temp = stack;  // Copy for testing
    while (!temp.empty()) {
        std::cout << temp.top() << " ";
        temp.pop();
    }
    std::cout << std::endl;
    
    // Test 3: Edge case - empty stack
    Stack<std::string> empty_stack;
    try {
        empty_stack.top();
    } catch (const std::exception& e) {
        std::cout << "Empty stack exception: " << e.what() << std::endl;
    }
    
    // Test 4: Practical use - bracket matching
    std::cout << "\nBracket matching test:" << std::endl;
    std::string expr = "((()))";
    Stack<char> brackets;
    bool valid = true;
    
    for (char c : expr) {
        if (c == '(') {
            brackets.push(c);
        } else if (c == ')') {
            if (brackets.empty()) {
                valid = false;
                break;
            }
            brackets.pop();
        }
    }
    
    valid = valid && brackets.empty();
    std::cout << "Expression '" << expr << "' is " 
              << (valid ? "valid" : "invalid") << std::endl;
    
    return 0;
}