/* 
    - AI Generated Test For Doubly List
*/
#include<iostream>
#include "List.h"

int main(){
    List<int> list;
    
    // Test basic insertion
    list.insert_back(10);
    list.insert_back(20);
    list.insert_front(5);
    
    // Test iteration: should print "5 10 20"
    std::cout << "List contents: ";
    for(const auto& element : list) {
        std::cout << element << " ";
    }
    std::cout << "\nSize: " << list.size() << std::endl;
    
    // Test erase
    list.erase_front();
    std::cout << "After erase_front: ";
    for(const auto& element : list) {
        std::cout << element << " ";
    }
    std::cout << "\nSize: " << list.size() << std::endl;
    
    // Test copy constructor
    List<int> list2 = list;
    std::cout << "Copied list: ";
    for(const auto& element : list2) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
    return 0;
}

