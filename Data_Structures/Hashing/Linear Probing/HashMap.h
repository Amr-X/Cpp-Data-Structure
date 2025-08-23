#pragma once
#include <vector>
#include "../Entry.h"
// Still Working ON.....
template <typename Key, typename Value, typename Hasher = std::hash<Key>>
class HashMap{
    using Entry<Key,Value> = Entry; 

public:
    HashMap()
    :m_hashTable{},
     m_hasher{},
     m_size{0}
    {
        m_hashTable.resize(20); // Note: Use half of it only - lambda <= 0.5
    }
    
    size_t size() const{
        return m_hashTable.size();
    }
    bool isEmpty() const{
        return m_hashTable.empty();
    }
    
    Value& insert(const Key& key,const Value& value){
        return insert(key,value,hash(key));
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
        return m_hasher(key) % m_hashTable.capacity(); // 
    }
    Value& insert(const Key& key,const Value& value,int hashValue){
        m_hashTable[hashValue].emplace_back(key,value);
        m_size++;
        return m_hashTable[hashValue].back().getValue();
    }

    // Data Members
    std::vector<Entry> m_hashTable{};
};

