/* 
    - AI Generated Test For Circular_Queue
*/
#include <iostream>
#include "Circular_Queue.h"

int main() {
    CircularQueue<int> queue(5);
    
    // Test basic enqueue
    std::cout << "=== Enqueue Test ===" << std::endl;
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    
    std::cout << "Size: " << queue.size() << std::endl;
    std::cout << "Front: " << queue.front() << std::endl;
    std::cout << "Back: " << queue.back() << std::endl;
    
    // Fill to capacity
    std::cout << "\n=== Fill to Capacity ===" << std::endl;
    queue.enqueue(40);
    queue.enqueue(50);
    std::cout << "Full: " << (queue.full() ? "Yes" : "No") << std::endl;
    
    // Test circular behavior
    std::cout << "\n=== Circular Behavior ===" << std::endl;
    std::cout << "Before dequeue - Front: " << queue.front() << std::endl;
    queue.dequeue();
    std::cout << "After dequeue - Front: " << queue.front() << std::endl;
    
    queue.enqueue(60);  // Should wrap around
    std::cout << "After enqueue(60) - Back: " << queue.back() << std::endl;
    
    // Show all items by dequeuing
    std::cout << "\n=== Queue Contents (FIFO order): ";
    while (!queue.empty()) {
        std::cout << queue.front() << " ";
        queue.dequeue();
    }
    std::cout << std::endl;
    
    std::cout << "Final size: " << queue.size() << std::endl;
    
    return 0;
}