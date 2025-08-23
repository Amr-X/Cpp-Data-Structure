/*
    - Vector Implementation Using C++ Array
    Note: The Concept Of Iterator (Position) Don't Quite Work Like List
        - Why? Updating Where The Elements Are In The Data Structure 
        - An Iterator Pointing At Some Data That Is Subject To Be Changed 
        - (Inserting <- Shifts Elements) (Deleting <- Also Shifts Elements)
*/
#pragma once
#include <cstddef>
#include <stdexcept>
template<typename Type>
class Vector
{
private:
    // Can't you notice how this is unnecessary class   

    // class Iterator
    // {
    //     friend class Vector;
    // private:
    //     Type* m_pos{};
    //     Iterator(Type* pos):m_pos{pos}{};
    // public:
    //     bool operator==(const Iterator& rhs){
    //         return m_pos == rhs.m_pos;
    //     }
    //     bool operator!=(const Iterator& rhs){
    //         return (*this) == rhs;
    //     }
    //     Iterator& operator++(const Iterator& rhs){
    //         ++m_pos // Works Fine Normal Pointer Arithmetic
    //         return *this;
    //     }
    //     Iterator& operator--(const Iterator& rhs){
    //         --m_pos;
    //         return *this;
    //     }
    //     // Const-ness is very important to understand
    //     Type& operator*(){
    //         return *m_pos;
    //     }
    //     const Type& operator*() const{
    //         return *m_pos;
    //     }
    // };
    
public:
    // See this
    typedef Type* Iterator ;
    typedef const Type* Const_Iterator ;

    // Big 5
    Vector(size_t initial_size = 0):m_data{new Type[initial_size]},m_size{initial_size},m_capacity{initial_size}{
        // At Full Logically - Full with Garbage
        for (size_t i = 0; i < initial_size; i++)
        {
            m_data[i] = Type{}; // Move Works?
        }
    };
    ~Vector(){ delete[] m_data; }
    Vector(const Vector& vec):m_data{new Type[vec.m_capacity]},m_size{vec.m_size},m_capacity{vec.m_capacity}{
        // Or, Before Filling anything ... I DON"T KNOW WHICH IS CORRECT
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = vec.m_data[i];
            // Or Added Here? m_size++; <- This One Maybe
        }
        // Should Size Be Modified Here After Filling Data?
    }
    Vector(Vector&& vec):m_data{vec.m_data},m_size{vec.m_size},m_capacity{vec.m_capacity}{ // Don't Fully Get noexcept
        vec.m_data = nullptr;
        vec.m_size = 0;
        vec.m_capacity = 0;
    }
    Vector& operator=(const Vector& vec){
        delete[] m_data;
        m_data = new Type[vec.m_capacity];
        m_capacity = vec.m_capacity;
        for (size_t i = 0; i < vec.size; i++)
        {
            m_data[i] = vec.m_data[i];
        }
        // Same As The Copy Constructor Question
        m_size = vec.m_size; 
        return *this;
    }
    Vector& operator=(Vector&& vec){
        delete[] m_data;
        m_data = vec.m_data; vec.m_data = nullptr;
        m_size = vec.m_size; vec.m_size = 0;
        m_capacity = vec.m_capacity; vec.m_capacity = 0;
        return *this;
    }
    // API
    size_t size() const {return m_size;}
    bool empty() const {return m_size == 0;}
    bool full() const {return m_capacity == m_size;}
    Type& operator[](size_t index){return m_data[index];}
    const Type& operator[](size_t index) const {return m_data[index];}

    Type& at(size_t index) /* throw(std::out_of_range) By Default Functions Throw*/{
        if(!in_range(index)) {
            throw std::out_of_range("Invalid Index.");
        }
        return m_data[index];
    }
    template<typename ...Args>
    void emplace_back(Args&&... args){
        if(full()){
            reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
        }
        
        new (&m_data[m_size]) Type(std::forward<Args>(args)...);
        ++m_size;
    }
    
    void insert(size_t index,const Type& to_insert){ // O(n)
        if(!in_range(index)) return;
        if(full()){reserve(2*m_capacity);}
        for (int i = m_size-1; i >= (int)index; i--)
        {
            m_data[i+1] = m_data[i];
        }
        m_data[index] = to_insert;
        m_size++;
    }
    void insert(const Iterator& it,const Type& to_insert){
        // Iterator doesn't have any info of how big the vector is
        // All it Knows Im Pointing at this location in Memory
        // So, I Can't Shift Elements - We Could Replace Though..
    }

    Type erase(size_t index){
        if(!in_range(index) || empty()){
            throw std::out_of_range("Invalid Index.");
        }
        // 
        Type to_erase = std::move(m_data[index]);
        for (size_t i = index;i < m_size-1; i++)
        {
            m_data[i] = std::move(m_data[i+1]);
        }
        m_size--;
        return to_erase;
    }
    void erase(const Iterator& it){
        // Same Here
    }

    void resize(size_t new_size){
        // Grow or Shrink
        if(new_size <= m_size){
            // Shrink
            m_size = new_size;
            return;
        }
        // Grow
        if(new_size > m_capacity){
            reserve(2*new_size); // Double What He Wants - Not What We have
        }
        for (size_t i = m_size; i < new_size; i++)
        {
            m_data[i] = Type{}; // Move Will Work here? Yes
        }
        m_size = new_size;
    }
    void reserve(size_t new_capacity){
        if(new_capacity <= m_capacity){return;}
        Type* new_data = new Type[new_capacity];
        for (size_t i = 0; i < m_size; i++)
        {
            new_data[i] = m_data[i];
        }
        delete[] m_data;
        m_capacity = new_capacity;
        // Same Size
    }
    void clear(){ 
        // Clear Means What?
        // reset m_size to 0 Where Space is Still in memory
        // Or, Delete Space Also?

        // Option 1
        m_size = 0;
    } 

    void push_back(const Type& to_push){
        insert(m_size,to_push);
    }
    void push_front(const Type& to_push){ // Don't Use It
        insert(0,to_push);
    }
    Type pop_back(){// Typically, You Would Separate pop_back and back
        return erase(m_size-1); // So, Now We Copy Type 2 Times? Yes, Or Make It Here Yourself
        // This is why STL Separate pop_back and back
    } 
    Type pop_front(){
        return erase((size_t)0);
    }

    // Const-ness is very important to understand
    const Type& front() const{return m_data[0];}
    Type& front(){return m_data[0];}

    const Type& back() const {return m_data[m_size-1];}
    Type& back(){return m_data[m_size-1];}


    // Iterator Support - This is Different From List
    Const_Iterator begin() const {return m_data;} 
    Iterator begin(){return m_data;} 

    // Notice: end pointer isn't null -> Meaning we could pass last elements to wrong data
    Const_Iterator end() const {return m_data + m_size;}
    Iterator end(){return m_data + m_size;}

private:
    inline bool in_range(size_t index){ // - big number will work in this case <- Problem
        return !(index > m_size);
    } 

    constexpr static size_t INITIAL_CAP = 10;

    Type* m_data{};
    size_t m_size{};
    size_t m_capacity{};
};