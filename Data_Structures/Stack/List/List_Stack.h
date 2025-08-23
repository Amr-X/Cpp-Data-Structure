/*
    - Stack Implementation Using Linked List
*/
#pragma once
#include "List ADT/List/Double Linked List/List.h"
#include <stdexcept>

template<typename Type>
class Stack{
public:
    // Api
    size_t size() const{return m_stack.size();} 
    bool empty() const {return m_stack.empty();}

    void pop(){
        if(empty()) throw std::underflow_error("Empty Stack."); 
        m_stack.erase_back();
    }
    Type& top(){
        if(empty()) throw std::underflow_error("Empty Stack."); 
        return m_stack.back();
    }
    const Type& top() const {
        if(empty()) throw std::underflow_error("Empty Stack."); 
        return m_stack.back();
    }
    void push(const Type& to_push){
        m_stack.insert_back(to_push);
    }
private:
    List<Type> m_stack{};
};