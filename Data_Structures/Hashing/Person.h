#pragma once
#include <string>

// Some Defined Type
struct Person{
    std::string name{};
    size_t age{};
    bool operator==(const Person& other){
        return (name == other.name) && (age == other.age);
    }
};
