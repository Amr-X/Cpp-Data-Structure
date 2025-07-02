#include <bitset>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// You Give Functors on Equality and Hashing
// Or, Operator==, std::hash<type>
 
struct Key // Custom Key - Wait! How it will hash it?
{
    std::string first;
    std::string second;

    // operator== Will Work too!
};
 
struct KeyHash // Aha! You Define The Hash Function For it - It's a functor - but think of it as just a function
{
    std::size_t operator()(const Key& k) const
    {
        return std::hash<std::string>()(k.first) ^
            (std::hash<std::string>()(k.second) << 1); // It Uses The std::hash ans std::string is knowing - 
            // So Implement you own - unique OfC - More on that
    }
};
 
struct KeyEqual // Need To Know How Key is Equal to a Key
{
    bool operator()(const Key& lhs, const Key& rhs) const
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

// Another Defined Type
struct Foo
{
    Foo(int val_) : val(val_) {}
    int val;
    bool operator==(const Foo &rhs) const { return val == rhs.val; }
};
 
// Okay This is new to me .. Note: Adding to The std namespace
// create std::hash<Foo> Okay, Use This Here
template<>
struct std::hash<Foo>
{
    std::size_t operator()(const Foo &f) const
    {
        return std::hash<int>{}(f.val);
    }
};
 
int main()
{
    // default constructor: empty map
    std::unordered_map<std::string, std::string> m1; // std::hash<std::string> Knows how to hash
 
    // list constructor
    std::unordered_map<int, std::string> m2 = // Same
    {
        {1, "foo"},
        {3, "bar"},
        {2, "baz"}
    };
 
    // copy constructor
    std::unordered_map<int, std::string> m3 = m2;
 
    // move constructor
    std::unordered_map<int, std::string> m4 = std::move(m2);
 
    // range constructor
    std::vector<std::pair<std::bitset<8>, int>> v = {{0x12, 1}, {0x01,-1}};
    std::unordered_map<std::bitset<8>, double> m5(v.begin(), v.end());
 
    // Option 1 for a constructor with a custom Key type
    // Define the KeyHash and KeyEqual structs and use them in the template
    std::unordered_map<Key, std::string, KeyHash, KeyEqual> m6 = // Give it Hash Functor - Equal Functor
    {
        {{"John", "Doe"}, "example"},
        {{"Mary", "Sue"}, "another"}
    };
 
    // Option 2 for a constructor with a custom Key type.
    // Define a const == operator for the class/struct and specialize std::hash
    // structure in the std namespace
    std::unordered_map<Foo, std::string> m7 = // Or (This is Better) - Operator== , std::hash<Foo>
    {
        {Foo(1), "One"}, {2, "Two"}, {3, "Three"}
    };
}

