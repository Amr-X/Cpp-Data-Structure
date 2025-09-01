#include <bits/stdc++.h>
using namespace std;

// Circular Queue - Using array
// Done this again - Cuz it was confusing at first - But now I get it
class Queue{
public:
    Queue(int size)
    :array{new int[size+1]},size{size+1}{} // VERY IMPORTANT _ I FORGOT THIS SOMEHOW -> To meet the user expectations

    ~Queue(){delete[] array;}
    bool is_empty(){
        // The same
        return rear == front;
    }
    // If you don't want to use the added_elements variable
    // But, You will lose one slot this way to distinguish between full and empty
    bool is_full(){
        // rear -> next of it front?
        return (rear+1) % size == front;
    }

    void enqueue(int value){
        if(is_full()) return;
        array[rear] = value;
        rear = (rear+1) % size;
    }
    int dequeue(){
        if(is_empty()) return -1;
        int value = array[front];
        front = (front+1) % size;
        return value;
    }
    // Drain the term used
    void drain_display(){
        // You need the added_elements to know how much front should go
        // Do this, But removes the queue content
        while(!is_empty()){
            cout << dequeue() << " ";
        }
    }
    void display(){
        for (int i = front; i != rear; i = (i+1)%size){
            cout << array[i] << " "; 
        }
    }

private:
    // Just follow this convention - Rear is like normal (size) - Front at 0
    // First at front - Last at rear-1 -> Use the %

    int* array{};
    int rear{0};
    int front{0};
    int size{};
    // Added_elements -> Makes it easier -> For empty and full and to know how to iterate on the queue Which i think isn't that important
};

////////////////////////
// Easy - Mid
////////////////////////
class Dequeue{
public:
    Dequeue(int size)
    :array{new int[size+1]},size{size+1}{} // Here too

    ~Dequeue(){delete[] array;}
    bool is_empty(){
        return rear == front;
    }
    bool is_full(){
        return (rear+1) % size == front;
    }

    void enqueue_rear(int value){
        if(is_full()) return;
        array[rear] = value;
        rear = (rear+1) % size;
    }
    int dequeue_front(){
        if(is_empty()) return -1;
        int value = array[front];
        front = (front+1) % size;
        return value;
    }

    void enqueue_front(int value){
        if(is_full()){
            return;
        }
        front--;
        if(front <= -1){ front = size - 1; }
        array[front] = value;
    }
    int dequeue_rear(){
        if(is_empty())return -1;
        rear--;
        if(rear <= -1){ rear = size -1; }
        // I wonder if i could do that?
        return array[rear];
    }


private:
    int* array{};
    int rear{0};
    int front{0};
    int size{};
};

// Stack using Queue
class Stack{
public:
    Stack(int size)
    :q{size}{}


    // Or use the added_elements
    bool is_empty(){
        return q.is_empty();
    }
    bool is_full(){
        return q.is_full();
    }

    void push(int value){
        if(is_full()){
            return;
        }
        // make the last the first by moving all the front except the last to the end of the queue
        // We need added_elements here (count)
        q.enqueue(value);
        added_elements++;

        // O(n)
        int i = added_elements;
        while(i > 1){
            q.enqueue(q.dequeue());
            i--;
        }
        // now it's at front
    }
    // Same as deque
    int pop(){
        if(is_empty()){return -1;}
        int value = q.dequeue();
        added_elements--;
        return value;
    }
    // q.front()
    // int top(){}
private:    
    Queue q;
    int added_elements{};
};

// Queue using 2 Stacks
class Queue_stack{
public:
    Queue_stack()
    :st1{},st2{}{}

    bool is_empty(){
        return st1.empty() && st2.empty();
    }
    // st1 for pushing 
    void enqueue(int value){
        st1.push(value);
    }
    // This is Interesting to get bigO
    // It's O(n) if stack is empty
    // Then it becomes o(1) the next n times I dequeue
    // It's amortized O(1)
    int dequeue(){
        if(is_empty()){return -1;}

        // Ask yourself where is the one that need to be dequeued?
        // It's the last deepest item in st1
        // How to get it? -> pop everything from the st1 to st2 -> Now it's at top
        // Where is the one after it? -> Right down to it

        if(st2.empty()){
            while(!st1.empty()){
                st2.push(st1.top()); st1.pop();
            }
        }
        int value = st2.top(); st2.pop();
        return value;
    }

    // The solution in course is to flip the stack using the other one - It's that simple
    // And to push the item and then return them back -> think Stack of books it will make sense
    // Like pushing at the deepest of the stack O(N)
    // Or to pop the item at the end of the stack by also flipping it and then pop and then return it back O(N) also


    // But This is better one for sure
private:
    // Using std::stack
    stack<int> st1;
    stack<int> st2;
};


////////////////////////
// Mid - Hard
////////////////////////

// --1
// Priority Queue - Using Circular Queue
// I almost Forgot about it

// What I Should do here is 3 Different Queues -> 1[] 2[] 3[] -> O(1) For all operations
// And just push where you should and when you pop you pick the first array 1[]
// If empty? next if empty? next 

// It's very bad since it's tight to only 3 types of priorities. What if i want more like 5,6 100, 2000?
// Let's ignore this It's not good to make it as an array since will most likely waste space

// If it's in array --> Becomes O(n^2) -- Shifting

// Linked_list is a better choice
// If you want arbitrary priorities -> You enqueue normally o(1) when dequeue Search Linear O(n)
// Or, Reverse -> You enqueue (Keep them Sorted) O(n) - When dequeue Normally O(1)

// Advanced -> Heap (array-based) for both O(log n) O(log n)

// --2
// Circular Queue without added_elements -> Done -> Look up
// Note: One empty slot is needed to indicate whether it's full or empty


class last_k_stream{
public:
    // Don't use it as q(k+1) cuz the queue should do that by default (Edited above) -> Forgot about it somehow
    // The queue should behave in a predictable way 
    last_k_stream(int k)
    :q(k){}

    int next(int next_number){
        if(q.is_full()){
            current_result -= q.dequeue();

        }
        q.enqueue(next_number);
        current_result += next_number;

        return current_result;
    }

private:
    Queue q;
    int current_result{};
};

void last_k_stream_test(){
    last_k_stream stream(4);
    int n;
    while(cin >> n){
        cout << stream.next(n) << " ";
    }    
}


void test_queue() {
    cout << "\n--- Queue Test ---\n";
    Queue q(3);
    cout << "Enqueue 1,2,3: ";
    q.enqueue(1); q.enqueue(2); q.enqueue(3); q.display(); cout << "\n";
    cout << "Dequeue: " << q.dequeue() << "\n";
    cout << "Enqueue 4: "; q.enqueue(4); q.display(); cout << "\n";
    cout << "Drain: "; q.drain_display(); cout << "\n";
    cout << "Is empty: " << q.is_empty() << "\n";
}

void test_dequeue() {
    cout << "\n--- Dequeue Test ---\n";
    Dequeue dq(3);
    cout << "Enqueue rear 1,2: "; dq.enqueue_rear(1); dq.enqueue_rear(2);
    cout << "Is full: " << dq.is_full() << "\n";
    cout << "Enqueue front 0: "; dq.enqueue_front(0); cout << "\n";
    cout << "Dequeue front: " << dq.dequeue_front() << "\n";
    cout << "Dequeue rear: " << dq.dequeue_rear() << "\n";
    cout << "Is empty: " << dq.is_empty() << "\n";
}

void test_stack() {
    cout << "\n--- Stack (using Queue) Test ---\n";
    Stack s(3);
    cout << "Push 1,2,3\n";
    s.push(1); s.push(2); s.push(3);
    cout << "Pop: " << s.pop() << "\n";
    cout << "Pop: " << s.pop() << "\n";
    cout << "Pop: " << s.pop() << "\n";
    cout << "Is empty: " << s.is_empty() << "\n";
}

void test_queue_stack() {
    cout << "\n--- Queue_stack (using 2 stacks) Test ---\n";
    Queue_stack qs;
    cout << "Enqueue 1,2,3\n";
    qs.enqueue(1); qs.enqueue(2); qs.enqueue(3);
    cout << "Dequeue: " << qs.dequeue() << "\n";
    cout << "Dequeue: " << qs.dequeue() << "\n";
    cout << "Dequeue: " << qs.dequeue() << "\n";
    cout << "Is empty: " << qs.is_empty() << "\n";
}

void test_last_k_stream() {
    cout << "\n--- last_k_stream Test ---\n";
    last_k_stream stream(3);
    int arr[] = {1,2,3,4,5};
    cout << "Input: 1 2 3 4 5\nOutput: ";
    for(int n : arr) cout << stream.next(n) << " ";
    cout << "\n";
}

int main() {
    test_queue();
    test_dequeue();
    test_stack();
    test_queue_stack();
    test_last_k_stream();
    cout << "NO RTE\n";
    return 0;
}