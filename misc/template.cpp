#include<vector>
#include<iostream>
using namespace std;
// Main Point to Take: When Templating You Are Making Assumption About The Type
// Type has operator< or that is has default constructor with no args (Type{})
template<typename Type>
class Object{
public:
    Object(Type& value = Type{ }) 
    :m_value{value}{ }
    
    const Type& read() const {return m_value;} 
    Type& read() {return m_value;} 
    void write(Type& value) { m_value = value;}
private:
    Type m_value{}; // if Type() is not provided , Won't Work 
};

////////////////////////////////////////////////
class Square{ // Rectangle Would have been a better example - Sorry
public:
    Square(int side):m_side{side}{}
    int getSize()const {return m_side*m_side;}
    bool operator< (const Square& rhs){
        // So how a square is less than a square? -> Let's agree on m_side < m_side
        return m_side < rhs.m_side; 
    }
    friend ostream& operator<< (ostream& os,const Square& sqr) {
        os << "Square Side:" << sqr.m_side << "\tSquare Size: " << sqr.getSize();
        return os;
    }
private:
    int m_side{};
};

// This is what im talking about - Just a function
struct SquareComparator{ // Think of it as a function

    bool is_greater (const Square& lhs,const Square& rhs){
        return lhs.getSize() > rhs.getSize();
    }
    bool is_less (const Square& lhs,const Square& rhs){
        return lhs.getSize() < rhs.getSize();
    }
    // This is More Convenient To Use - But What if i want this to be is_greater? Use Template or Store State of What To Return Enum or something
    bool operator() (const Square& lhs,const Square& rhs){
        return is_less(lhs,rhs); // if(something) return isless else return isgreater
    }
};
/////////////////////////////////////////////////
// Let's Say We Want A Function To Get Max For Object Type
template <typename Type>
const Type& find_max(const vector<Type>& vec){
    Type max = vec[0];
    for (size_t i = 1; i < vec.size(); i++)
    {
        if(vec[i] < max){max = vec[i];}; // Not Every Type has < operator
        
    }
    return max;
}
// Solution Give find_max the function that tell it Use this object(function) to know - Which i implement based on what I Want
template <typename Type,typename Comparator> // Comparator Here is Used as Function - Whether that is "Functor", "Function Pointer", "Lambda"
const Type& find_max(const vector<Type>& vec,Comparator is_less){ // Will Take a function that I will use to know - Has to provided with what you want
    size_t max{0};
    for (size_t i = 0; i < vec.size(); i++)
    {
        if(is_less(vec[max],vec[i])){max = i;}; // Let's Say it Does, What if I Want To Change how to compare between 2 of the same types
        
    }
    return vec[max];
}


// Will Pass as Function Pointer
bool square_is_less_than(const Square& lhs,const Square& rhs){
    return lhs.getSize() < rhs.getSize();
}

int main(){
    vector<Square> squares{5,11,9,2,4,10,4,5,6}; // Will Convert - Makes a Copy Know That 5 -> Square(5)
    cout << find_max(squares,SquareComparator{}) << '\n'; // Use? is_less() <- Object name
    cout << find_max(squares,square_is_less_than) << '\n';// Use? is_less() <- Other name for a function pointer
    cout << find_max(squares,[](const Square& lhs,const Square& rhs){return lhs.getSize() < rhs.getSize();}) << '\n'; // Lambda
}