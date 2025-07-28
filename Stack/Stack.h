/*
    - Stack Implementation Using C++ Array  
        - On Heap -> Dynamic -> Used With Vector
        - On Stack -> Fixed Size 
*/
#pragma once
#include <stdexcept>
#include <cstddef>
#include "../List ADT/Vector/Vector.h"

//
template<typename Type>
class Stack{
public:
    // Big 5 - No Need For Any Of These Vector Knows How Copy, Move, Construct
    Stack() = default;
    ~Stack() = default;
    Stack(const Stack&) = default;
    Stack(Stack&&) = default;
    Stack& operator=(const Stack&) = default;
    Stack& operator=(Stack&&) = default;
    // Api
    size_t size() const{return stack.size();} // Isn't it private? how?
    bool empty() const {return stack.empty();}

    void pop(){
        if(empty()) throw std::underflow_error("Empty Stack."); 
        stack.pop_back();
    }
    Type& top(){
        if(empty()) throw std::underflow_error("Empty Stack."); 
        return stack.back();
    }
    const Type& top() const {
        if(empty()) throw std::underflow_error("Empty Stack."); 
        return stack.back();
    }
    void push(const Type& to_push){
        // Can't Overflow - Dynamic
        stack.push_back(to_push);
    }
private:
    Vector<Type> stack{};
};
