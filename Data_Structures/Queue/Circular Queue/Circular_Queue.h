/*
    - Circular Queue Implementation Using C++ Array  
*/
#pragma once
#include <stdexcept>
#include <cstddef>

// [1,2,3,4,5,-,-]
//  |       |    |
//  f       r    c

template<typename Type>
class CircularQueue{
private:
    // This is simpler than vector 
    Type* m_data;     
    size_t m_capacity; 
    size_t m_size{0};  
    // Wraps Around - No need to check state of rear and front to know empty or not
    size_t m_front{0}; 
    size_t m_rear{0};  

public:
    // Most of It Like Vector (No Dynamic Size Change)
    CircularQueue(size_t capacity) 
        : m_data{new Type[capacity]}, m_capacity{capacity} {}
    
    ~CircularQueue() { 
        delete[] m_data; 
    }
    // API 
    size_t size() const { return m_size;}
    bool empty() const { return m_size == 0;}
    bool full() const { return m_size >= m_capacity;}

    void enqueue(const Type& value) {
        if(m_size >= m_capacity) {
            throw std::overflow_error("Queue is full.");
        }
        // Much Like Normal Push 
        m_data[m_rear] = value;
        ++m_size;
        m_rear = (m_rear + 1) % m_capacity;  // Wrap around - Make sure we still the array range
    }
    
    void dequeue() {
        if(empty()) {
            throw std::underflow_error("Queue is empty.");
        }
       
        // Logical Deletion
        --m_size;
        m_front = (m_front + 1) % m_capacity;  // Same
    }

    Type& front() {
        if(empty()) {
            throw std::underflow_error("Queue is empty.");
        }
        return m_data[m_front];
    }
    const Type& front() const {
        if(empty()) {
            throw std::underflow_error("Queue is empty.");
        }
        return m_data[m_front];
    }

    Type& back() {
        if(empty()) {
            throw std::underflow_error("Queue is empty.");
        }
        // Exception if rear at 0 index
        size_t back_index = (m_rear == 0) ? m_capacity - 1 : m_rear - 1;
        return m_data[back_index];
    }
    const Type& back() const {
        if(empty()) {
            throw std::underflow_error("Queue is empty.");
        }
        // Same
        size_t back_index = (m_rear == 0) ? m_capacity - 1 : m_rear - 1;
        return m_data[back_index];
    }
};