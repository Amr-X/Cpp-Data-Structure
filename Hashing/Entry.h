#pragma once

// Insted Of Pair - We Define Our Own
template<typename Key, typename Value>
class Entry{
public:
    Entry(const Key& key,const Value& value)
        :m_key{key},m_value{value}{}
    // Getters 
    const Key& getKey() const {
        return m_key;
    }
    Value& getValue() {
        return m_value;
    }
    const Value& getValue() const {
        return m_value;
    }
    // Setters
    void setKey(const Key& key){
        m_key = key;
    }
    void setValue(const Value& value){
        m_value = value;
    }
private:
    Key m_key;
    Value m_value;

};