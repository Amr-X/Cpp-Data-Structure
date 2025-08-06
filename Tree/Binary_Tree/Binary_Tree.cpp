/* 
    - AI Generated Test For Binary Tree
*/

#include "Binary_Tree.h"
#include <iostream>
#include <vector>

void testBinaryTree() {
    std::cout << "=== Binary Tree Test ===" << std::endl;
    
    BinaryTree<int> tree;
    
    // Test 1: Empty tree
    std::cout << "1. Testing empty tree..." << std::endl;
    std::cout << "   Empty: " << (tree.empty() ? "Yes" : "No") << std::endl;
    std::cout << "   Contains 5: " << (tree.contain(5) ? "Yes" : "No") << std::endl;
    
    // Test 2: Insert elements level by level
    std::cout << "\n2. Inserting elements: 1, 2, 3, 4, 5, 6, 7..." << std::endl;
    tree.insert(1);  // Root
    tree.insert(2);  // Left of 1
    tree.insert(3);  // Right of 1
    tree.insert(4);  // Left of 2
    tree.insert(5);  // Right of 2
    tree.insert(6);  // Left of 3
    tree.insert(7);  // Right of 3
    
    std::cout << "   Empty after insertion: " << (tree.empty() ? "Yes" : "No") << std::endl;
    
    // Test 3: Traversals
    std::cout << "\n3. Testing traversals:" << std::endl;
    
    std::cout << "   Preorder:  ";
    tree.Preorder([](const int& data) { 
        std::cout << data << " "; 
    });
    std::cout << std::endl;
    
    std::cout << "   Inorder:   ";
    tree.Inorder([](const int& data) { 
        std::cout << data << " "; 
    });
    std::cout << std::endl;
    
    std::cout << std::endl;
    
    // Test 4: Search functionality
    std::cout << "\n4. Testing search:" << std::endl;
    std::vector<int> searchValues = {1, 4, 7, 8, 10};
    for(int val : searchValues) {
        std::cout << "   Contains " << val << ": " << (tree.contain(val) ? "Yes" : "No") << std::endl;
    }
    
    // Test 5: Functional traversal (collect even numbers)
    std::cout << "\n5. Collecting even numbers using traversal:" << std::endl;
    std::vector<int> evenNumbers;
    tree.Preorder([&evenNumbers](const int& data) {
        if(data % 2 == 0) {
            evenNumbers.push_back(data);
        }
    });
    std::cout << "   Even numbers: ";
    for(int num : evenNumbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    
    // Test 6: Count nodes using lambda
    std::cout << "\n6. Counting total nodes:" << std::endl;
    int nodeCount = 0;
    tree.Inorder([&nodeCount](const int& data) {
        nodeCount++;
    });
    std::cout << "   Total nodes: " << nodeCount << std::endl;
    
    // Test 7: Find maximum value
    std::cout << "\n7. Finding maximum value:" << std::endl;
    int maxValue = INT_MIN;
    tree.Preorder([&maxValue](const int& data) {
        if(data > maxValue) {
            maxValue = data;
        }
    });
    std::cout << "   Maximum value: " << maxValue << std::endl;
    
    // Test 8: Clear tree
    std::cout << "\n8. Clearing tree..." << std::endl;
    tree.clear();
    std::cout << "   Empty after clear: " << (tree.empty() ? "Yes" : "No") << std::endl;
    std::cout << "   Contains 1 after clear: " << (tree.contain(1) ? "Yes" : "No") << std::endl;
    
    std::cout << "\n=== Test Complete ===" << std::endl;
}

int main() {
    testBinaryTree();
    return 0;
}

