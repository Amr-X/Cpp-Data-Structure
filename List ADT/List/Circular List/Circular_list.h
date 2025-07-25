#pragma once
#include <stdexcept>

template<typename Type>
class Circular_List {
private:
    struct node { // Points to itself
        node() : m_data{Type{}}, m_next{this}, m_prev{this} {}  // For sentinel
        node(const Type& data) : m_data{data}, m_next{nullptr}, m_prev{nullptr} {}
        
        Type m_data;
        node* m_next{};
        node* m_prev{};
    };

    class Iterator {
        friend class Circular_List;
        node* m_pos;
        
        Iterator(node* pos) : m_pos{pos} {}
    public:
        bool operator==(const Iterator& other) const { 
            return m_pos == other.m_pos;
        }
        bool operator!=(const Iterator& other) const { 
            return !(*this == other);
        }
        Iterator& operator++() { 
            m_pos = m_pos->m_next;
            return *this;
        }
        Type& operator*() const { return m_pos->m_data; }
    };

public:
    Circular_List() : m_sentinel{new node()},m_cursor{m_sentinel}, m_size{0} {
        
    }
    
    ~Circular_List() {
        
        while (m_sentinel->m_next != m_sentinel) {
            node* to_delete = m_sentinel->m_next;
            m_sentinel->m_next = to_delete->m_next;
            to_delete->m_next->m_prev = m_sentinel;
            delete to_delete;
        }
        delete m_sentinel;
    }
    
    void insert_at_cursor(const Type& value) { // After
        node* new_node = new node(value);
        node* next = m_cursor->m_next;
        
        // Insert between cursor and cursor->next
        new_node->m_next = next;
        new_node->m_prev = m_cursor;
        m_cursor->m_next = new_node;
        next->m_prev = new_node;
        
        ++m_size;
    }
    
    void advance_cursor() {
        m_cursor = m_cursor->m_next;
    }
    
    const Type& current() const {
        if (m_cursor == m_sentinel) { // Don't Dereference Sentinel
            throw std::runtime_error("Cursor at sentinel - no current element");
        }
        return m_cursor->m_data;
    }
    
    void reset_to_sentinel() { // Reset
        m_cursor = m_sentinel->m_next;
    }
    
    // For range-based for loop - iterate data nodes only
    Iterator begin() const {
        return {m_sentinel->m_next};  // First data node
    }
    
    Iterator end() const {
        return {m_sentinel};  // Sentinel marks end
    }
    
    size_t size() const { return m_size; }
    bool empty() const { return m_size == 0; }

private:
    node* m_sentinel{};  // Dummy node that marks beginning/end
    node* m_cursor{};    // Current position (can point to sentinel or data)
    size_t m_size{};
};