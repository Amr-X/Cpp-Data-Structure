/*
    - Queue Implementation With Adapter Pattern (List)
*/
#pragma once
#include <stdexcept>
#include <cstddef>
#include "../../List ADT/List/Double Linked List/List.h"

template<typename Type>
class Queue{
public:
    Queue() = default;
    //Api
    size_t size() const {return m_list.size();}
    bool empty() const {return m_list.empty();}

    void enqueue(const Type& to_enqueue){
        m_list.insert_back(to_enqueue);
    }
    // Forgot This - list.enqueue(String("string"))
    void enqueue(Type&& to_enqueue) {
        m_list.insert_back(std::move(to_enqueue));
    }   
    void dequeue(){
        // Encapsulation
        // if(empty())        // ✅ Queue asking "Am I empty?" --------> Better
        // if(m_list.empty()) // ❌ Queue asking "Is my internal list empty?"
        // Or, Changing The Logic Of How Queue Is Empty...

        // Forgot This
        if(empty()) throw std::underflow_error("Queue Empty.");
        m_list.erase_front();
    }

    Type& front() {
        return m_list.front();
    }
    const Type& front() const{
        return m_list.front();
    }
    Type& back() {
        return m_list.back();
    }
    const Type& back() const{
        return m_list.back();
    }
private:
    List<Type> m_list{};
};