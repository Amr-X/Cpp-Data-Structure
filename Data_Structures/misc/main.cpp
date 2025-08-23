#include <vector> // Only What you call gets initiated
#include <iostream>

// Simple Class
class Int{
public:
    // Works with zero or one argument
    explicit Int(int value = 0)
    :m_value{value}{ }
    
    // Want To Return Reference
    const int& read() const {return m_value;} // User marked it with const
    int& read() {return m_value;} // User 

    void write(int value) { m_value = value;}
private:
    int m_value{}; // Imagine This Int m_value In Other - Think about The Construction
};

void test_some_Initialization(){
    Int obj; // Default 
    Int obj1{}; // Same with C++11
    Int obj2(1); // Normal Construction Call
    Int obj3{1}; // New Way <- Preferred
    // Int obj4(); // Ambagious with Function Declaration
    // double n = 3.2; Int obj5{n}; // double to int 3.2 to 3 Narrowing Convert But OK!
    obj1 = obj3; // Normal Assignment 
    //obj1 = 12; // Explicit Construction with Only Type int - Can't Convert 12 to 
    obj1 = Int(12); // Normal Assignment (Temp Obj)
    // Constness
    const Int OBJ; // Value is 0
    // OBJ.read() = 4; // The Const Version - Nope..
    //int value = OBJ.read(); // Same But No Changing Here - OK
    

}

void printVector(const std::vector<int>& vec){
    std::cout << "Elements in Vector<int>: "; std::cout << "[ ";
    for (auto &element : vec)
    {
       std::cout << element << " "; 
    }
    std::cout << "]\n";
    std::cout << "With Size: " << vec.size();
    std::cout << "\nWith Capacity: " << vec.capacity();
    std::cout << "\nWith Max Size: " << vec.max_size();
    std::cout << std::boolalpha;
    std::cout << "\nisEmpty: " << vec.empty();
     
}
void printVectorInt(const std::vector<Int>& vec){
    std::cout << "Elements in Vector<Int>: "; std::cout << "[ ";
    for (auto &element : vec)
    {
       std::cout << element.read() << " "; 
    }
    std::cout << "]\n";
    std::cout << "With Size: " << vec.size();
    std::cout << "\nWith Capacity: " << vec.capacity();
    std::cout << "\nWith Max Size: " << vec.max_size();
    std::cout << std::boolalpha;
    std::cout << "\nisEmpty: " << vec.empty();
        
}
void test_vector(){
    std::vector<int> very_complex_and_long_name_for_vector;
    std::vector<int>& vec = very_complex_and_long_name_for_vector;
    printVector(vec); 
    //
    std::cout << "\nTesting Vector<Int>\n";
    std::vector<Int> vecInt;
    printVectorInt(vecInt);
    vecInt.resize(20);
    vecInt.reserve(40);
    std::cout << "\nAfter Resize to 20 and Reserve 20\n";
    printVectorInt(vecInt); 

}

int main(){
    test_some_Initialization();
    test_vector();
}