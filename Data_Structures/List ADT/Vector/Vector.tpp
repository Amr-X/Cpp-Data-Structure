template<typename Type>
Vector<Type>::Vector(size_t initial_size)
    :m_data{new Type[initial_size]},m_size{initial_size},m_capacity{initial_size}{
        // At Full Logically - Full with Garbage
        for (size_t i = 0; i < initial_size; i++)
        {
            m_data[i] = Type{}; 
        }
        // new Type[initial_size] Defaults it for class/structs - so why it's here? for primitive types -> int-0,double0.0
}

template<typename Type>
Vector<Type>::~Vector(){ delete[] m_data; m_data = nullptr; }

template<typename Type>
Vector<Type>::Vector(const Vector& vec)
    :m_data{new Type[vec.m_capacity]},m_size{vec.m_size},m_capacity{vec.m_capacity}{
        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = vec.m_data[i];
        }
}

template<typename Type>
Vector<Type>::Vector(Vector&& vec)
    :m_data{vec.m_data},m_size{vec.m_size},m_capacity{vec.m_capacity}{ // Don't Fully Get noexcept
        // Leave it in empty state - So when it get's destroyed don't mess the original (now, vec data) data
        vec.m_data = nullptr;
        vec.m_size = 0;
        vec.m_capacity = 0;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator=(const Vector& vec){
        delete[] m_data;

        m_capacity = vec.m_capacity;
        m_size = vec.m_size; 
        m_data = new Type[m_capacity];

        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = vec.m_data[i];
        }
        return *this;
}

template<typename Type>
Vector<Type>& Vector<Type>::operator=(Vector&& vec){
        delete[] m_data;
        m_data = vec.m_data; vec.m_data = nullptr;
        m_size = vec.m_size; vec.m_size = 0;
        m_capacity = vec.m_capacity; vec.m_capacity = 0;
        return *this;
}

template<typename Type>
size_t Vector<Type>::size() const {return m_size;}

template<typename Type>
bool Vector<Type>::empty() const {return m_size == 0;}

template<typename Type>
bool Vector<Type>::full() const {return m_capacity == m_size;}

template<typename Type>
Type& Vector<Type>::operator[](size_t index){return m_data[index];}

template<typename Type>
const Type& Vector<Type>::operator[](size_t index) const {return m_data[index];}

template<typename Type>
Type& Vector<Type>::at(size_t index) /* throw(std::out_of_range) By Default Functions Throw*/{
        if(!in_range(index)) {
            throw std::out_of_range("Invalid Index.");
        }
        return m_data[index];
}

template<typename Type>
template<typename ...Args>
void Vector<Type>::emplace_back(Args&&... args){
        if(full()){
            reserve(m_capacity == 0 ? 1 : 2 * m_capacity);
        }
        
        new (&m_data[m_size]) Type(std::forward<Args>(args)...);
        ++m_size;
}

template<typename Type>
void Vector<Type>::insert(size_t index,const Type& to_insert){ // O(n)
        // For insertion, allow index == m_size (insert at end)
        if(index > m_size) return;
        if(full()){reserve(2*m_capacity);}
        // Did I mention Amortized Time Complexity? No? Okay It's O(n) Amortized.
        // What the hell that means -> Think of it this way 
        // What we have is O(1) insertion but occasionally It's O(n) The more we hit the O(n) The more less it happens
        // So we say that each insertion isn't o(1) but O(3) means that it take 3 steps to do
        // but hold on it doesn't. Yes, I know but it's Amortized It will pay for the step that we will move it in

        // When we insert, we pay:
        // 1 coin for the actual insertion,
        // 1 coin for shifting elements (if needed),
        // 1 coin for future moves when the array grows (amortized cost).

        for (int i = m_size-1; i >= (int)index; i--)
        {
            m_data[i+1] = m_data[i];
        }
        m_data[index] = to_insert;
        m_size++;
}


template<typename Type>
Type Vector<Type>::erase(size_t index){
        if(!in_range(index) || empty()){
            throw std::out_of_range("Invalid Index.");
        }
        // 
        Type to_erase = std::move(m_data[index]);
        for (size_t i = index;i < m_size-1; i++)
        {
            m_data[i] = std::move(m_data[i+1]);
        }
        m_size--;
        return to_erase;
}

template<typename Type>
typename Vector<Type>::Iterator Vector<Type>::erase(const Iterator& it) {
    // Assuming Valid Iterator
    size_t index = (size_t)(it - m_data); // Get index from iterator

    erase(index);

    // Next valid position
    // Don't forget if it's last it will be index is not valid, return end() if that happens
    return (index < m_size)?&m_data[index]:end();
}

template<typename Type>
void Vector<Type>::resize(size_t new_size,const Type& to_resize_with){
        // Grow or Shrink
        if(new_size <= m_size){
            // Shrink
            m_size = new_size;
            return;
        }
        // Grow

        // Want more than what we have?
        if(new_size > m_capacity){
            reserve(new_size); // What He Wants - Not What We have
        }
        // Assign new places to what user wants
        for (size_t i = m_size; i < new_size; i++)
        {
            m_data[i] = to_resize_with; 
        }
        m_size = new_size;
}

template<typename Type>
void Vector<Type>::reserve(size_t new_capacity){
        if(new_capacity <= m_capacity){return;}

        delete[] m_data;
        m_data = new Type[new_capacity];

        for (size_t i = 0; i < m_size; i++)
        {
            m_data[i] = m_data[i];
        }
        m_capacity = new_capacity;
        // Same Size
}

template<typename Type>
void Vector<Type>::clear(){ 
        // Clear Means What?
        // reset m_size to 0 Where Space is Still in memory
        // Or, Delete Space Also?

        // Option 1
        // This is what the user expects - We don't want to reallocate and start reversing again
        m_size = 0;
        // Option 2
        // Make a shrink_to_fit function 
} 

template<typename Type>
void Vector<Type>::push_back(const Type& to_push){
        insert(m_size,to_push);
}

template<typename Type>
void Vector<Type>::push_front(const Type& to_push){ // Don't Use It
        insert(0,to_push);
}

template<typename Type>
Type Vector<Type>::pop_back(){// Typically, You Would Separate pop_back and back
        return erase(m_size-1); // So, Now We Copy Type 2 Times? Yes, Or Make It Here Yourself
        // This is why STL Separate pop_back and back} 
}
template<typename Type>
Type Vector<Type>::pop_front(){
        return erase((size_t)0);
}


// Don't Always Check - User Should be careful with these operations if it's empty
template<typename Type>
const Type& Vector<Type>::front() const{return m_data[0];}

template<typename Type>
Type& Vector<Type>::front(){return m_data[0];}

template<typename Type>
const Type& Vector<Type>::back() const {return m_data[m_size-1];}

template<typename Type>
Type& Vector<Type>::back(){return m_data[m_size-1];}

template<typename Type>
typename Vector<Type>::Const_Iterator Vector<Type>::begin() const {return m_data;} 

template<typename Type>
typename Vector<Type>::Iterator Vector<Type>::begin(){return m_data;} 

template<typename Type>
typename Vector<Type>::Const_Iterator Vector<Type>::end() const {return m_data + m_size;}

template<typename Type>
typename Vector<Type>::Iterator Vector<Type>::end(){return m_data + m_size;}

template<typename Type>
inline bool Vector<Type>::in_range(size_t index){ // - big number will work in this case <- Problem
        return index < m_size;
} 
