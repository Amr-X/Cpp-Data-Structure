
## Question
For a periodic table application where users search elements by name, should I use:
- Vector with linear search O(n)
- Sorted vector with binary search O(log n) 
- Map O(log n)
- Hash map O(1)

Given only 118 elements, does the choice matter?

## Answer

**Recommendation: `std::unordered_map<string, Element>`**

### Implementation
```cpp
struct Element {
    int atomic_number;
    string name, symbol;
    double atomic_weight;
};

// Multi-index approach for flexible searching
class PeriodicTable {
    unordered_map<string, Element> by_name;        // "hydrogen" -> Element
    unordered_map<string, Element> by_symbol;      // "H" -> Element  
    unordered_map<int, Element> by_atomic_number;  // 1 -> Element
public:
    const Element* find_by_name(const string& name);
    const Element* find_by_symbol(const string& symbol);
    const Element* find_by_atomic_number(int num);
};
```

### Analysis

| Approach | Time Complexity | API Quality | Use Case |
|----------|----------------|-------------|-----------|
| **Vector + Linear Search** | O(n) | Poor | Never recommended |
| **Sorted Vector + Binary Search** | O(log n) | Complex | Memory-constrained systems |
| **Map (Red-Black Tree)** | O(log n) | Excellent | When ordering matters |
| **Hash Map** | O(1) avg | Excellent | **Best for search-heavy applications** |

### Key Insights

1. **Size doesn't matter**: Even with 118 elements, hash map provides cleaner API
2. **Binary search ≠ Data structure**: Binary search is an algorithm that operates on sorted containers
3. **Multiple indexes**: Real applications need search by name, symbol, and atomic number
4. **Performance**: Hash map wins for lookup-heavy workload

**Conclusion**: Choose data structures based on **API clarity and usage patterns**, not just theoretical performance for