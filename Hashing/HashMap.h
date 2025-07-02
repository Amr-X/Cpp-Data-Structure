#pragma once
#include <vector>
#include <list>
#include "Entry.h"

// If We Will Take Any Kind of Key -> We Have To Know How To Hash It
template <typename Key, typename Value, typename Hasher = std::hash<Key>>
class HashMap{
    typedef Entry<Key,Value> Entry; // Making const Key Confuse Me

public:
    HashMap()
    :m_hashTable{},m_hasher{},m_size{0}{
        m_hashTable.resize(10);
    }
    
    size_t size() const{
        return m_size;
    }
    bool isEmpty() const{
        return m_size == 0;
    }
    
    Hasher& getHashFunction() const{
        return m_hasher;
    }

    Value& insert(const Key& key,const Value& value){
        size_t hashValue = hash(key);
        return insert(key,value,hashValue);
    }
    Value& operator[] (const Key& key){
        size_t hashValue = hash(key);
        for (Entry& entry : m_hashTable[hashValue])
        {
            // Searching The Current Bucket - That It Should be in
               if(key == entry.getKey())
                    return entry.getValue(); // Found!
        }
        // Unlucky, Insert it {-1,""} - We Are Not Given What to Store so, Default is Used
        return insert(key,Value{},hashValue); 
        
    }

private:
    // Compress Function - Division - Simple
    size_t hash(const Key& key){
        return m_hasher(key) % m_hashTable.size(); // 
    }
    Value& insert(const Key& key,const Value& value,int hashValue){
        m_hashTable[hashValue].emplace_back(key,value);
        m_size++;
        return m_hashTable[hashValue].back().getValue();
    }

    // Data Members
    std::vector<std::list<Entry>> m_hashTable{};
    Hasher m_hasher{}; // Functors give you the flexibility of functions + the ability to store state + work as template parameters
    size_t m_size{}; // Needed - It's not equal to vector.size()
};

