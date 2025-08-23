#pragma once
#include <string>
#include <cmath>
#include "Person.h"

// Making it Simple here
struct intHasher{

    size_t operator()(const int& num) const{
        return std::abs(num); // 1 and -1 Collision!
    } 
    // And This also
    //size_t hash = key * 2654435761u;  // Knuth's multiplicative hash
};

struct stringHasher{

    size_t operator()(const std::string& str) const{
        // I copy pasted this - I will check it later
        size_t hash = 0;
        for (char c : str) {
            hash = hash * 31 + c;
        }
        return hash;
    }
};



struct personHasher{
    // Also Will have a look later
    size_t operator()(const Person& person) const{
        size_t hash = stringHasher{}(person.name) ^
                      intHasher{}((int)person.age);
        return hash;
    }
};

// Or Push tell std::hash 
template<>
struct std::hash<Person>
{
    size_t operator()(const Person& person) const{
        size_t hash = stringHasher{}(person.name) ^
                      intHasher{}((int)person.age);
        return hash;
    }
};
