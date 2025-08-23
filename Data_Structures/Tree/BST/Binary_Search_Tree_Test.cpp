/* 
    - AI Generated Test For BST
*/
#include <iostream>
#include "Binary_Search_Tree.h"

int main() {
    BinarySearchTree<int> bst;
    
    // Insert elements
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);
    
    // Test search
    std::cout << "Contains 30: " << bst.contains(30) << std::endl;
    std::cout << "Contains 99: " << bst.contains(99) << std::endl;
    
    // Test min/max
    std::cout << "Min: " << bst.findMin() << std::endl;
    std::cout << "Max: " << bst.findMax() << std::endl;
    
    // Test remove (need to fix your remove function first)
    bst.remove(30);
    std::cout << "After removing 30: " << bst.contains(30) << std::endl;
    
    // Test clear
    bst.clear();
    std::cout << "Empty after clear: " << bst.empty() << std::endl;
    
    // Test move semantics
    BinarySearchTree<int> bst2;
    bst2.insert(100);
    BinarySearchTree<int> bst3 = std::move(bst2);
    std::cout << "Moved tree contains 100: " << bst3.contains(100) << std::endl;
    std::cout << "Original tree empty: " << bst2.empty() << std::endl;
    
    return 0;
}