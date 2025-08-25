/*
    - Doubly Linked List Implementation With Iterator Pattern
*/
#pragma once

#include <cstddef>
#include <utility>
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
    class Reverse_Iterator
    {
        friend class List;
    private:
        node* m_pos;
        Reverse_Iterator(node* pos):m_pos{pos}{}; 
    public:
        bool operator==(const Iterator& rhs) const{
            return m_pos == rhs.m_pos; 
        }
        bool operator!=(const Iterator& rhs) const{
            return !(*this == rhs); 
        }
        Reverse_Iterator& operator++(){ 
            m_pos = m_pos->m_prev;
            return *this;
        } 
        Reverse_Iterator& operator--(){ 
            m_pos = m_pos->m_next;
            return *this;
        } 
        Reverse_Iterator operator-(size_t i) const{
            node* curr = m_pos;
            for (size_t j = 0; j < i; j++)
            {
               curr = curr->m_next; 
            }
            return {curr};
        }
        Type& operator*(){
            return m_pos->m_data;
        }
    };
public:
    // The Five Rule
    List() // Dummy Nodes - Makes it easier => Best Choice to do
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
        m_last_node = nullptr; m_size = 0;
    }

    List(const List& list)
    :List(){
        //  standard behavior defined by the C++ language - Once you Have the iterator pattern..
        for (const Type &element : list) 
        {
            insert_back(element);
        }
    }
    List(List&& list)
    :m_first_node{list.m_first_node},m_last_node{list.m_last_node},m_size{list.m_size}{
        list.m_first_node = list.m_last_node = nullptr;
    }
    List& operator=(const List& list){
        // Interesting - Different Sizes - Can Just Delete and Do It All Over Again
        if(this == &list) return *this; // A MUST DON"T FORGET

        clear();
        for (const Type &element : list) 
        {
            insert_back(element);
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
        
        /*
            - I saw this with std::swap() - It's same thing for *this object
            S
            - Both Works, Since rhs will be out of scope any way It doesn't matter if it got nothing or what we had
            - Point Taken: Leave rhs Object in a valid state but unspecified <- We Don't Know What it got after moving it
        */
    }
    // API
    size_t size() const {return m_size;}
    bool empty() const {return m_size == 0;}

    Iterator insert(const Iterator& position,const Type& to_insert_value){
        // Can't Insert At Position Ofc, But Before => Like at .end() is before it
        // So, Question in My Mind For A lot of Time, I Use Iterator Here or node*?
        // That is a design problem => Use node* for internal Implementation like here - Use Iterator For public API
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

    // Validate And Return Iterator To The Currently Valid Node (The one after it)
    Iterator erase(const Iterator& pos){ // Invalidate The Iterator
        if(empty()) return end();
        node* current = pos.m_pos;
        node* next = current->m_next;
        node* prev = current->m_prev;
        next->m_prev = prev;
        prev->m_next = next;
        delete current; m_size--;
        return next;
    }
    void erase(const Iterator& first_pos,const Iterator& second_pos){
        // Data Integrity?
        // What if I was passed erase(.begin()-1,..)? 
        // What now?
        // Passing an invalid iterator (like .begin()-1) to erase is undefined behavior.
        // The user is responsible for passing valid iterators.
        Iterator temp = first_pos;
        while(temp != second_pos){
            temp = erase(temp); // Used it here - Fixed
        }
    }
    void erase_front(){
        erase(begin());
    }
    void erase_back(){
        erase(end()-1);
    }
    Type& front() {
        return *begin();
    }
    const Type& front() const{
        return *begin();
    }
    Type& back() {
        return *(--end());
    }
    const Type& back() const{
        return *(--end());  
    }

    void clear(){ erase(begin(),end());}
    // Iterator Support
    Iterator begin() const{
        return m_first_node->m_next;
    }
    Iterator end() const{
        return m_last_node;
    }
    Iterator rbegin() const{
        return m_last_node->m_prev;
    }
    Iterator rend() const{
        return m_first_node; 
    }
private:
    node* m_first_node{};
    node* m_last_node{};
    size_t m_size{};
};