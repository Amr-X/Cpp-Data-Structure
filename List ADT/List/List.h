/*
    - Doubly Linked List Implementation
*/
#pragma once

#include <cstddef>
template<typename Type>
class List{
private:
    // Classes Structs Needed
    struct node{
        node(const Type& data = Type{})
        :m_prev{nullptr},m_data{data},m_next{nullptr}{}
        node(node* prev, const Type& data, node* next)
            :m_prev{prev},m_data{data},m_next{next}{}

        node* m_prev{};
        Type m_data{};
        node* m_next{};
    };

    class Iterator
    {
        friend class List;
    private:
        node* m_pos;
        Iterator(node* pos):m_pos{pos}{}; // Only List Makes It
    public:
        bool operator==(const Iterator& rhs) const{
            return m_pos == rhs.m_pos; 
        }
        bool operator!=(const Iterator& rhs) const{
            return !(*this == rhs); // Uses operator==
        }
        Iterator& operator++(){ // No Post-Fix 
            m_pos = m_pos->m_next;
            return *this;
        } 
        Type& operator*(){
            return m_pos->m_data;
        }
        ~Iterator(){}; // It's Not Iterator Resource
    };
public:
    // The Five Rule
    List() // Dummy Nodes - Makes it easier
    :m_first_node{new node()}
    ,m_last_node{new node()}
    {
        // Connect
        m_first_node->m_next = m_last_node;
        m_last_node->m_prev = m_first_node;
    }; 
    ~List(){
        while(m_first_node){
            node* temp = m_first_node;
            m_first_node = m_first_node->m_next;
            delete temp;
        }
        // Remove This and Use Clear()
    }
    List(const List& list)
    :List(){
        for (auto &element : list) // I Don't Get This One - Am I Counting On How Compiler Do This - Or How The Standard Made it?
        {
            insert(element);
        }
    }
    List(List&& list)
    :m_first_node{list.m_first_node},m_last_node{list.m_last_node}{
        list.m_first_node = list.m_last_node = nullptr;
    }
    List& operator=(const List& list){
        // Interesting - Different Sizes - Can Just Delete and Do It All Over Again

    }
    List& operator=(List&& list){
        //        ~List(); // Why UB?
        if(*this == &list) return *this; // A MUST DON"T FORGET
        // Delete Me
        clear();
        // Yes! Give Me it all
        m_first_node = list.m_first_node;
        m_last_node = list.m_last_node;
        m_size = list.m_size;
        // You Get Nothing
        list.m_first_node = list.m_last_node = nullptr;
        list.m_size = 0;
        return *this; // Chaining
    }
    // API
    size_t size() const {return m_size;}
    bool empty() const {return m_size == 0;}

    Iterator insert(const Iterator& position,const Type& to_insert_value){
        // Can't Insert At Position Ofc, But Before => Like at .end() is before it
        // So, Question in My Mind For A lot of Time, I Use Iterator Here or node*?
        node* next = position.m_pos;
        node* prev = next->m_prev;
        node* new_node = new node(prev,to_insert_value,next);
        next->m_prev = new_node;
        prev->m_next = new_node;
        return {new_node};
    }
    Iterator insert(const Type& to_insert_value){
        return insert(end(),to_insert_value);
    }
    bool clear(){ // With Iterator
        return false;
    }
    // Iterator Support
    Iterator begin() const{
        return {m_first_node->m_next};
    }
    Iterator end() const{
        return {m_last_node}; 
    }

private:
  
    node* m_first_node{};
    node* m_last_node{};
    size_t m_size{};
};