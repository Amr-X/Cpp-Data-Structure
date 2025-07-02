#include <iostream>
#include "HashMap.h"
#include "Hashers.h"
#include "Person.h"

// Keys : What will be used to know where the value
// value: The Data itself - This Can Be pair<key,value>
// Hash Table : Where are of this will located
// Hashing:
    // - Hash Code : Turn Something to Integer (key)
        // - There is A lot - Different From Type To Type std::hash<type> Support a lot 
    // - Compress Function : Compress it to fit in hash table 
        // - Division Method: |k|%N 
        // - MAD Method: |aK+b|%N <- Better
// Map : The Whole Thing as ADT
// Open Addressing : More Space Other Than Hash Table - Like Bucket
// Load Factor : How Many Values / Table Size - Where Each Bucket Contain this Much (At Ideal Case Of Course)
// Closed Addressing : In Hash Table
// Composition Pattern : Object Composed Of More Objects - Pair Tuple



// NOT ME - IT'S AI GENERATED
void test_int_string_hashmap() {
    std::cout << "=== Testing HashMap<int,string> ===\n";
    HashMap<int, std::string, intHasher> map;
    
    // Test insert
    map.insert(1, "Alice");
    map.insert(2, "Bob");
    map.insert(-5, "Charlie");
    std::cout << "Inserted 3 items, size: " << map.size() << "\n";
    
    // Test operator[]
    std::cout << "map[1] = " << map[1] << "\n";
    std::cout << "map[2] = " << map[2] << "\n";
    std::cout << "map[-5] = " << map[-5] << "\n";
    
    // Test collision (1 and -1 both hash to same value with intHasher)
    map.insert(-1, "David");
    std::cout << "After inserting -1, size: " << map.size() << "\n";
    std::cout << "map[1] = " << map[1] << "\n";
    std::cout << "map[-1] = " << map[-1] << "\n";
    
    // Test accessing non-existing key (creates default)
    std::cout << "Accessing map[99] (new key): '" << map[99] << "'\n";
    std::cout << "Size after accessing new key: " << map.size() << "\n";
}

void test_string_person_hashmap() {
    std::cout << "\n=== Testing HashMap<string,Person> ===\n";
    HashMap<std::string, Person, stringHasher> people;
    
    // Test insert
    people.insert("john", {"John Doe", 25});
    people.insert("jane", {"Jane Smith", 30});
    people.insert("bob", {"Bob Johnson", 22});
    std::cout << "Inserted 3 people, size: " << people.size() << "\n";
    
    // Test access
    Person& p1 = people["john"];
    std::cout << "people['john'] = " << p1.name << ", age " << p1.age << "\n";
    
    Person& p2 = people["jane"];
    std::cout << "people['jane'] = " << p2.name << ", age " << p2.age << "\n";
    
    // Test modifying value
    p1.age = 26;
    std::cout << "After modifying john's age: " << people["john"].age << "\n";
    
    // Test accessing new key (creates default Person)
    Person& p3 = people["newbie"];
    std::cout << "New person created - name: '" << p3.name << "', age: " << p3.age << "\n";
    p3.name = "New Guy";
    p3.age = 18;
    std::cout << "After setting values: " << people["newbie"].name << ", age " << people["newbie"].age << "\n";
    
    std::cout << "Final size: " << people.size() << "\n";
}

int main() {
    test_int_string_hashmap();
    test_string_person_hashmap();
    return 0;
}
