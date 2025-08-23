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
    Vector(size_t initial_size = 0);
    ~Vector();
    Vector(const Vector& vec);
    Vector(Vector&& vec);
    Vector& operator=(const Vector& vec);
    Vector& operator=(Vector&& vec);

    // Look at it now, It's an ADT -> The Operations that operate on the data but, We don't know how it's done

    // API
    size_t size() const;
    bool empty() const;
    bool full() const;
    Type& operator[](size_t index);
    const Type& operator[](size_t index) const;

    Type& at(size_t index) /* throw(std::out_of_range) By Default Functions Throw*/;

    template<typename ...Args>
    void emplace_back(Args&&... args);
    
    void insert(size_t index,const Type& to_insert); // O(n)
    void insert(const Iterator& it,const Type& to_insert);

    Type erase(size_t index);
    Iterator erase(const Iterator& it);

    void resize(size_t new_size,const Type& to_resize_with = Type{});
    void reserve(size_t new_capacity);
    void clear(); 

    void push_back(const Type& to_push);
    void push_front(const Type& to_push); // Don't Use It
    Type pop_back();// Typically, You Would Separate pop_back and back
    Type pop_front();

    // Const-ness is very important to understand
    const Type& front() const;
    Type& front();

    const Type& back() const;
    Type& back();

    // Iterator Support - This is Different From List
    Const_Iterator begin() const; 
    Iterator begin(); 

    // Notice: end pointer isn't null -> Meaning we could pass last elements to wrong data
    Const_Iterator end() const;
    Iterator end();

private:
    inline bool in_range(size_t index); // - big number will work in this case <- Problem

    constexpr static size_t INITIAL_CAP = 16;

    Type* m_data{};
    size_t m_size{};
    size_t m_capacity{};
};
// Didn't know something as .tpp - Now I know
#include "Vector.tpp"
