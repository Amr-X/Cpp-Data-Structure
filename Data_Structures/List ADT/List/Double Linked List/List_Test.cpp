/* 
    - AI Generated Test For Doubly List
*/
#include<iostream>
#include "List.h"

int main(){
    List<int> list;

    // Test: Empty list
    std::cout << "Empty list: ";
    for (const auto& element : list) std::cout << element << " ";
    std::cout << "\nSize: " << list.size() << std::endl;

    // Test: Insert at back and front
    list.insert_back(10);
    list.insert_back(20);
    list.insert_front(5);
    std::cout << "After insertions: ";
    for (const auto& element : list) std::cout << element << " ";
    std::cout << "\nSize: " << list.size() << std::endl;

    // Test: Erase front
    list.erase_front();
    std::cout << "After erase_front: ";
    for (const auto& element : list) std::cout << element << " ";
    std::cout << "\nSize: " << list.size() << std::endl;

    // Test: Erase back
    list.erase_back();
    std::cout << "After erase_back: ";
    for (const auto& element : list) std::cout << element << " ";
    std::cout << "\nSize: " << list.size() << std::endl;

    // Test: Insert at middle (before end)
    list.insert(list.end(), 100);
    std::cout << "After insert at end: ";
    for (const auto& element : list) std::cout << element << " ";
    std::cout << "\nSize: " << list.size() << std::endl;

    // Test: Insert at begin
    list.insert(list.begin(), 1);
    std::cout << "After insert at begin: ";
    for (const auto& element : list) std::cout << element << " ";
    std::cout << "\nSize: " << list.size() << std::endl;

    // Test: Range erase (erase all except last)
    if (list.size() > 1) {
        list.erase(list.begin(), --list.end());
        std::cout << "After erase range (all except last): ";
        for (const auto& element : list) std::cout << element << " ";
        std::cout << "\nSize: " << list.size() << std::endl;
    }

    // Test: Front and back access
    if (!list.empty()) {
        std::cout << "Front: " << list.front() << ", Back: " << list.back() << std::endl;
    }

    // Test: Clear
    list.clear();
    std::cout << "After clear: ";
    for (const auto& element : list) std::cout << element << " ";
    std::cout << "\nSize: " << list.size() << std::endl;

    // Test: Insert after clear
    list.insert_back(42);
    list.insert_front(24);
    std::cout << "After insertions to cleared list: ";
    for (const auto& element : list) std::cout << element << " ";
    std::cout << "\nSize: " << list.size() << std::endl;

    // Test: Copy constructor
    List<int> copy(list);
    std::cout << "Copy constructed list: ";
    for (const auto& element : copy) std::cout << element << " ";
    std::cout << "\nSize: " << copy.size() << std::endl;

    // Test: Assignment operator
    List<int> assigned;
    assigned = list;
    std::cout << "Assigned list: ";
    for (const auto& element : assigned) std::cout << element << " ";
    std::cout << "\nSize: " << assigned.size() << std::endl;

    // Test: Move constructor
    List<int> moved(std::move(list));
    std::cout << "Moved list: ";
    for (const auto& element : moved) std::cout << element << " ";
    std::cout << "\nSize: " << moved.size() << std::endl;

    // Test: Move assignment
    List<int> move_assigned;
    move_assigned = std::move(copy);
    std::cout << "Move assigned list: ";
    for (const auto& element : move_assigned) std::cout << element << " ";
    std::cout << "\nSize: " << move_assigned.size() << std::endl;

	std::cout << "\n\nNO RTE\n";

    return 0;
}

