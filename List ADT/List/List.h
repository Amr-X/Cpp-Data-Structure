/*
    - Doubly Linked List Implementation With Iterator Pattern
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
        Iterator& operator--(){ 
            m_pos = m_pos->m_prev;
            return *this;
        } 
        Iterator operator-(size_t i) const{
            node* curr = m_pos;
            for (size_t j = 0; j < i; j++)
            {
               curr = curr->m_prev; 
            }
            return {curr};
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
        for (const Type &element : list) // I Don't Get This One - Am I Counting On How Compiler Do This - Or How The Standard Made it?
        {
            insert_back(element);
        }
    }
    List(List&& list)
    :m_first_node{list.m_first_node},m_last_node{list.m_last_node}{
        list.m_first_node = list.m_last_node = nullptr;
        m_size = list.m_size;
    }
    List& operator=(const List& list){
        // Interesting - Different Sizes - Can Just Delete and Do It All Over Again
        if(this == &list) return *this; // A MUST DON"T FORGET
        clear();

        for (const Type &element : list) 
        {
            insert(element);
        }
        return *this;
    }
    List& operator=(List&& list){
        //        ~List(); // Why UB? Aha, Data Members After That Are Gone
        if(this == &list) return *this; // A MUST DON"T FORGET
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
        m_size++;
        return {new_node};
    }
    Iterator insert_back(const Type& to_insert_value){
        return insert(end(),to_insert_value);
    }
    Iterator insert_front(const Type& to_insert_value){
        return insert(begin(),to_insert_value);
    }
    void erase(const Iterator& pos){ // Invalidate The Iterator
        if(empty()) return;
        node* current = pos.m_pos;
        node* next = current->m_next;
        node* prev = current->m_prev;
        next->m_prev = prev;
        prev->m_next = next;
        delete current; m_size--;
    }
    void erase(const Iterator& first_pos,const Iterator& second_pos){
        Iterator temp = first_pos;
        while(temp != second_pos){
            erase(temp);
        }
    }
    void erase_front(){
        erase(begin());
    }
    void erase_back(){
        erase(end()-1);
    }
    void clear(){ erase(begin(),end()); }
    // Misc
    void reverse(){
        std::swap(m_first_node,m_last_node);
        // What I Forgot - The Linking
        node* left = m_first_node;
        node* right = m_first_node->m_next;
        while(right){
            std::swap(left->m_next,right->m_prev);
            left = right;
            right = right->m_next;
        }
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