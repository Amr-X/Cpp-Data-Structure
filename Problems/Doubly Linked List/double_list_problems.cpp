#include <iostream>
using namespace std;

class DoublyLinkedList {
    struct Node {
        int value;
        Node* next;
        Node* prev;
        Node(int value = 0, Node* next = nullptr, Node* prev = nullptr)
            : value(value), next(next), prev(prev) {}
    };
private:
    Node* head;
    Node* tail;
    int size;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = tail = nullptr;
        size = 0;
    }
    bool empty() { return head == nullptr; }
    void insert_front(int value) {
        Node* new_node = new Node(value, head, nullptr);
        if (empty()) {
            head = tail = new_node;
        } else {
            head->prev = new_node;
            head = new_node;
        }
        size++;
    }
    void insert_back(int value) {
        Node* new_node = new Node(value, nullptr, tail);
        if (empty()) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
        size++;
    }
    void delete_front() {
        if (empty()) return;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        size--;
    }
    void delete_back() {
        if (empty()) return;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        size--;
    }
    void print() {
        Node* curr = head;
        while (curr) {
            cout << curr->value << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    // Look at the simplicity of O(1) Operation - This is what I like to see
    Node* delete_node(Node* to_delete){
        if(empty() || !to_delete)return nullptr;

        if(to_delete == head){
            delete_front();
            return head->next;
        }
        if(to_delete == tail){
            delete_back();
            return nullptr;
        }
        Node* prev = to_delete->prev;
        Node* next = to_delete->next;
        prev->next = next;
        next->prev = prev;
        if(to_delete == tail) tail = prev;
        delete to_delete;
        size--;
        return next;
    }
    ////////////////////
    // Easy - Medium 
    ///////////////////
    void delete_all_nodes_with_key(int value){
        if(empty()) return;
        Node* curr = head;
        while(curr){
            if(curr->value == value){
                curr = delete_node(curr);
            }else{
                curr = curr->next;
            }
        }
    }

    void delete_even_positions(){
        if(size <= 1) return;
        Node* curr = head;
        while(curr){
            // This is what I wasn't doing for some reason - Doing the same logic over and over and over
            // Now, I get DRY
            curr = delete_node(curr->next);
        }
    }

    void delete_odd_positions(){
        if(empty()) return;
        delete_front();
        // Same logic
        delete_even_positions();
    }
    // crazy how I will someday forget about this code even thought I did it myself
    bool is_palindrome(){
        // Don't want to use size here
        if(empty()) return false;

        Node* curr1 = head;
        Node* curr2 = tail;

        // odd -> meets at middle both are equal
        // even -> their both next will be equal
        while (curr1 != curr2 && (curr1->next != curr2 ))
        {
            if(curr1->value != curr2->value){ return false; }
            curr1 = curr1->next;
            curr2 = curr2->prev;
        }
        // Will go here if it's even
        if(curr1->value != curr2->value){ return false; }

        // If odd Here cuz if odd then curr1 and curr2 are the same with the same values
        return true; 
    }
    ////////////////
    // Medium - Hard
    ////////////////

    // No size, No iteration more than once

    // DLL 
    pair<int,int> find_middle1(){
        // I find it to works perfectly fine
        if(empty()) return {-1,-1};
        // Renaming
        Node* right = head;
        Node* left = tail;

        // odd -> meets at middle both are equal
        // even -> their both next will be equal
        while (right !=  left && (right->next != left ))
        {
            right = right->next;
            left = left->prev;
        }
        // Will go here if it's even
        if(right != left){ return {right->value,left->value}; }

        // If odd Here cuz if odd then curr1 and  left are the same with the same values
        return {right->value,-1}; 

    }
    // SLL -> No Prev
    pair<int,int> find_middle2(){
        if(empty()) return {-1,-1};
        // Why dummy? I want slow to be at first middle part of the two so that i can return slow->next->value easily
        Node* dummy = new Node(0,head);
        Node* slow = dummy; Node* fast = dummy;

        while(fast && fast->next){
            slow = slow->next;
            fast = fast->next->next;
        }
        delete dummy;

        // We have to cases to stop the loop - fast is null or fast->next is null
        // That means that fast is at tail or it's null

        // even? 
        // if fast is valid (that it's tail) means it's even
        if(fast){ return {slow->value,slow->next->value};}
        // Odd? 
        // if fast is nullptr
        return {slow->value,-1};
    }
    // This doesn't work with adjecent nodes
    // And to be honest i don't why it doesn't.
    void swap_nodes(Node* first, Node* second){
        // Any nullptr
        if(!first || !second) return;
        // Same thing
        if(first == second) return;

        // Prev and next of each should also be updated
        if (first->prev) first->prev->next = second;
        if (first->next) first->next->prev = second;
        if (second->prev) second->prev->next = first;
        if (second->next) second->next->prev = first;
        // Just swapping here
        swap(first->next,second->next);
        swap(first->prev,second->prev);

        // One is head?
        if(first == head){ head = second; }
        else if(second == head){ head = first; }
        // One is tail?
        if(first == tail){ tail = second; }
        else if(second == tail){ tail = first; }
    }
    void swap_forward_with_backword(int k){
        if(empty() || tail == head || k > size){return;}
        // Just noticed my naming here, I meant the direction of the node
        Node* right = head;
        Node* left = tail;
        // -1 here
        for (int i = 0; i < k-1; i++) {
            if(right)
                right = right->next;
            if(left)
                left = left->prev; 
        }
        swap_nodes(right,left);

    }
    void reverse(){
        if(empty() || head == tail){return;}
        Node* curr = head;
        while(curr){
            swap(curr->next,curr->prev);
            // Remember? we swapped
            curr = curr->prev;
        }
        swap(head,tail);
    } 
    void merge_lists(DoublyLinkedList& other){
        if(other.empty()) return;
        if(empty()){
            // Move
            head = other.head; other.head = nullptr;
            tail = other.tail; other.tail = nullptr;
            size = other.size; other.size = 0;
            return;
        }
        Node* dummy = new Node(0);
        Node* curr = dummy;
        Node* curr1 = head;
        Node* curr2 = other.head;

        // The operation
        while(curr1 && curr2){
            if(curr1->value <= curr2->value){
                if(curr->next != curr1){
                    curr->next = curr1;
                    curr1->prev = curr;
                }
                curr1 = curr1->next;
            }else{
                if(curr->next != curr2){
                    curr->next = curr2;
                    curr2->prev = curr;
                }
                curr2 = curr2->next;
            }

            curr = curr->next;
        }
        // The head
        head = dummy->next;
        // Last - Points the remaining valid one
        curr->next = (curr1)?curr1:curr2;

        // The size
        size += other.size;

        // The tail
        tail = (curr1) ? tail : other.tail;

        delete dummy;
        // Invalidating the other
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
};

// I reapeat: THIS IS AI GENERATED TEST NOT MINE I DIN'T TOUCH THIS 
// JUST REVIEWED IT ONLY
void test_basic() {
    cout << "=== Basic Operations ===\n";
    DoublyLinkedList dll;
    dll.insert_front(3);
    dll.insert_back(4);
    dll.insert_front(2);
    dll.insert_back(5);
    dll.insert_front(1);
    cout << "Initial list: "; dll.print();
    dll.delete_front();
    dll.delete_back();
    cout << "After delete_front and delete_back: "; dll.print();
}

void test_key_and_position_deletes() {
    cout << "=== Key and Position Deletes ===\n";
    DoublyLinkedList dll;
    dll.insert_back(2);
    dll.insert_back(4);
    dll.insert_back(2);
    dll.insert_back(4);
    dll.insert_back(2);
    cout << "Before delete_all_nodes_with_key(2): "; dll.print();
    dll.delete_all_nodes_with_key(2);
    cout << "After delete_all_nodes_with_key(2): "; dll.print();

    dll.insert_front(1);
    dll.insert_back(5);
    dll.insert_back(6);
    cout << "Before delete_even_positions: "; dll.print();
    dll.delete_even_positions();
    cout << "After delete_even_positions: "; dll.print();

    dll.insert_back(7);
    dll.insert_back(8);
    cout << "Before delete_odd_positions: "; dll.print();
    dll.delete_odd_positions();
    cout << "After delete_odd_positions: "; dll.print();
}

void test_palindrome() {
    cout << "=== Palindrome Test ===\n";
    DoublyLinkedList pal;
    pal.insert_back(1);
    pal.insert_back(2);
    pal.insert_back(3);
    pal.insert_back(2);
    pal.insert_back(1);
    cout << "Palindrome list: "; pal.print();
    cout << "Is palindrome? " << (pal.is_palindrome() ? "Yes" : "No") << endl;

    DoublyLinkedList not_pal;
    not_pal.insert_back(1);
    not_pal.insert_back(2);
    not_pal.insert_back(3);
    cout << "Not palindrome list: "; not_pal.print();
    cout << "Is palindrome? " << (not_pal.is_palindrome() ? "Yes" : "No") << endl;
}

void test_advanced() {
    cout << "=== Advanced Features ===\n";
    DoublyLinkedList midlist;
    for (int i = 1; i <= 7; ++i) midlist.insert_back(i);
    cout << "Midlist: "; midlist.print();
    auto m1 = midlist.find_middle1();
    auto m2 = midlist.find_middle2();
    cout << "find_middle1: " << m1.first << " " << m1.second << endl;
    cout << "find_middle2: " << m2.first << " " << m2.second << endl;

    // Reverse multi-element list
    DoublyLinkedList revlist;
    for (int i = 1; i <= 5; ++i) revlist.insert_back(i); // 1 2 3 4 5
    cout << "Before reverse (multi-element): "; revlist.print();
    revlist.reverse();
    cout << "After reverse (multi-element): "; revlist.print(); // 5 4 3 2 1
    revlist.reverse();
    cout << "After reverse again (should restore): "; revlist.print(); // 1 2 3 4 5

    // Reverse two-element list
    DoublyLinkedList two;
    two.insert_back(10);
    two.insert_back(20);
    cout << "Before reverse (two elements): "; two.print();
    two.reverse();
    cout << "After reverse (two elements): "; two.print();

    // Reverse single-element list
    DoublyLinkedList single;
    single.insert_back(42);
    cout << "Single element list before reverse: "; single.print();
    single.reverse();
    cout << "Single element list after reverse: "; single.print();

    // Reverse empty list
    DoublyLinkedList empty;
    cout << "Empty list before reverse: "; empty.print();
    empty.reverse();
    cout << "Empty list after reverse: "; empty.print();

    // Swap forward/backward
    midlist.reverse(); // restore order
    cout << "Before swap_forward_with_backword(2): "; midlist.print();
    midlist.swap_forward_with_backword(2);
    cout << "After swap_forward_with_backword(2): "; midlist.print();

    DoublyLinkedList l1, l2;
    l1.insert_back(1); l1.insert_back(3); l1.insert_back(5);
    l2.insert_back(2); l2.insert_back(4); l2.insert_back(6);
    cout << "List 1: "; l1.print();
    cout << "List 2: "; l2.print();
    l1.merge_lists(l2);
    cout << "After merge_lists: "; l1.print();

    DoublyLinkedList l3;
    l1.merge_lists(l3);
    cout << "After merging with empty list: "; l1.print();

    DoublyLinkedList evenpal;
    evenpal.insert_back(1);
    evenpal.insert_back(2);
    evenpal.insert_back(2);
    evenpal.insert_back(1);
    cout << "Even palindrome list: "; evenpal.print();
    cout << "Is palindrome? " << (evenpal.is_palindrome() ? "Yes" : "No") << endl;
}

int main() {
    test_basic();
    test_key_and_position_deletes();
    test_palindrome();
    test_advanced();
    cout << "NO RTE\n";
}