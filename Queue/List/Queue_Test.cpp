/* 
    - AI Generated Test For Queue
*/
#include <iostream>
#include "Queue.h"

int main(){
    try {
        Queue<int> queue;
        
        std::cout << "=== Testing Empty Queue ===" << std::endl;
        std::cout << "Empty: " << (queue.empty() ? "true" : "false") << std::endl;
        std::cout << "Size: " << queue.size() << std::endl;
        
        std::cout << "\n=== Testing Enqueue Operations ===" << std::endl;
        queue.enqueue(10);
        queue.enqueue(20);
        queue.enqueue(30);
        
        std::cout << "Size after enqueues: " << queue.size() << std::endl;
        std::cout << "Empty: " << (queue.empty() ? "true" : "false") << std::endl;
        std::cout << "Front element: " << queue.front() << std::endl;
        std::cout << "Back element: " << queue.back() << std::endl;
        
        std::cout << "\n=== Testing Dequeue Operations ===" << std::endl;
        std::cout << "Before dequeue - Front: " << queue.front() << std::endl;
        queue.dequeue();
        std::cout << "After dequeue - Front: " << queue.front() << std::endl;
        std::cout << "Size after dequeue: " << queue.size() << std::endl;
        
        std::cout << "\n=== Testing FIFO Behavior ===" << std::endl;
        queue.enqueue(40);
        queue.enqueue(50);
        
        std::cout << "Queue contents (front to back): ";
        while (!queue.empty()) {
            std::cout << queue.front() << " ";
            queue.dequeue();
        }
        std::cout << std::endl;
        std::cout << "Final size: " << queue.size() << std::endl;
        
        std::cout << "\n=== Testing Exception Handling ===" << std::endl;
        std::cout << "Trying to access front of empty queue..." << std::endl;
        std::cout << "Front: " << queue.front() << std::endl;  // Should throw
        
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what() << std::endl;
    }
    
    return 0;
}