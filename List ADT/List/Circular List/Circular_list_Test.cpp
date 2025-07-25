/* 
    - AI Generated Test For Circular List
*/
#include <iostream>
#include "Circular_list.h"

int main(){
    try {
        Circular_List<int> clist;
        
        std::cout << "=== Testing Empty List ===" << std::endl;
        std::cout << "Size: " << clist.size() << std::endl;
        std::cout << "Empty: " << (clist.empty() ? "true" : "false") << std::endl;
        
        // Test current() on empty list (should throw)
        try {
            std::cout << "Trying to get current on empty list: ";
            std::cout << clist.current() << std::endl;
        } catch(const std::exception& e) {
            std::cout << "Exception caught: " << e.what() << std::endl;
        }
        
        std::cout << "\n=== Testing Insertion ===" << std::endl;
        // Insert at sentinel (cursor starts at sentinel)
        clist.insert_at_cursor(10);
        std::cout << "Inserted 10, size: " << clist.size() << std::endl;
        
        clist.advance_cursor(); // Move to data node 10
        std::cout << "Advanced cursor, current: " << clist.current() << std::endl;
        
        clist.insert_at_cursor(20); // Insert 20 after 10
        std::cout << "Inserted 20, size: " << clist.size() << std::endl;
        
        clist.advance_cursor(); // Move to data node 20
        std::cout << "Advanced cursor, current: " << clist.current() << std::endl;
        
        clist.insert_at_cursor(30); // Insert 30 after 20
        std::cout << "Inserted 30, size: " << clist.size() << std::endl;
        
        std::cout << "\n=== Testing Range-Based For Loop ===" << std::endl;
        std::cout << "List contents: ";
        for(const auto& element : clist) {
            std::cout << element << " ";
        }
        std::cout << std::endl;
        
        std::cout << "\n=== Testing Cursor Navigation ===" << std::endl;
        // Reset cursor to first data node
        clist.reset_to_sentinel();
        std::cout << "Reset cursor to first data node: " << clist.current() << std::endl;
        
        clist.advance_cursor();
        std::cout << "Advanced: " << clist.current() << std::endl;
        
        clist.advance_cursor();
        std::cout << "Advanced: " << clist.current() << std::endl;
        
        clist.advance_cursor(); // Should go to sentinel
        try {
            std::cout << "Advanced to sentinel, trying current(): ";
            std::cout << clist.current() << std::endl;
        } catch(const std::exception& e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
        
        clist.advance_cursor(); // Should wrap around to first data node
        std::cout << "Wrapped around to: " << clist.current() << std::endl;
        
        std::cout << "\n=== Testing Full Circle Navigation ===" << std::endl;
        clist.reset_to_sentinel();
        for(int i = 0; i < 8; i++) {  // Go around more than twice
            try {
                std::cout << "Position " << i << ": " << clist.current() << std::endl;
            } catch(const std::exception& e) {
                std::cout << "Position " << i << ": [SENTINEL]" << std::endl;
            }
            clist.advance_cursor();
        }
        
        std::cout << "\n=== Testing Multiple Insertions ===" << std::endl;
        clist.reset_to_sentinel(); // Start at first data node (10)
        clist.insert_at_cursor(15); // Insert 15 after 10
        
        std::cout << "After inserting 15, list contents: ";
        for(const auto& element : clist) {
            std::cout << element << " ";
        }
        std::cout << "\nSize: " << clist.size() << std::endl;
        
    } catch(const std::exception& e) {
        std::cout << "Unexpected error: " << e.what() << std::endl;
    }
    
    return 0;
}