#include <bits/stdc++.h>
using namespace std;

// Just for the basic Problems 
class LinkedList{
    struct Node{
        int value;
        Node* next;
        Node(int value = 0, Node* next = nullptr)
        :value(value),next(next){}
    };
private:
    Node* head{};
    // Only head
    // Assume They aren't here - Only in problems that require them 
    Node* tail{};
    int size{};


    // VERY, VERY, VERY, Helpful Helpers Here
    Node* create_node(int value, Node* next = nullptr) {
        return new Node(value, next);
    }

    void unlink_head() {
        Node* temp = head;
        head = head->next;
        delete temp;
        size--;
        // This is the thing about linked list - There is one million ways things go wrong
        if (size == 0) tail = nullptr;
    }

    void link_after(Node* prev, Node* node) {
        if (prev) {
            node->next = prev->next;
            prev->next = node;
            if (prev == tail) tail = node;
        } else {
            node->next = head;
            head = node;
            if (!tail) tail = node;
        }
        size++;
    }

    Node* delete_node(Node* node, Node* prev) {
        if (!node) return nullptr;
        Node* after = node->next;
        if (node == head) {
            unlink_head();
        } else {
            if (node == tail) tail = prev;
            prev->next = node->next;
            delete node;
            size--;
        }
        return after;
    }

public:
    LinkedList()
    :head(nullptr),tail(nullptr){}

    ~LinkedList(){
        while(head){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    bool empty(){
        return head == nullptr;
    }
    void insert_front(int value){
        Node* new_node = create_node(value, head);
        if(empty()){
            head = tail = new_node;
            return;
        }
        head = new_node;
        size++;
    }
    void delete_front(){
        if(empty()){
            return;
        }
        unlink_head();
    }
    Node* get_nth_from_back(int n){
        // same thing I need size here to be efficient

        // So what to do? two pointers
        // this algo has a name i don't know it 
        if(n <= 0 || empty()){return nullptr;}

        Node* ahead = head;
        for (int i = 0; i < n; i++) {
            if (!ahead) return nullptr; // list shorter than n
            ahead = ahead->next;
        }
        Node* curr = head;
        while(ahead){
            curr = curr->next;
            ahead = ahead->next;
        }
        return curr;
    }

    bool operator==(const LinkedList& l2){
        // No size remember
        Node* curr1 = head;
        Node* curr2 = l2.head;
        while(curr1 && curr2){
            if(curr1->value != curr2->value){
                return false;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
        return (!curr1 && !curr2);

    }

   void print() const {
        Node* curr = head;
        while (curr) {
            cout << curr->value << " ";
            curr = curr->next;
        }
        cout << endl;
    }
    // insert at front -> same thing to make it O(1)
    // void add_element(int value){
    // }
    // O(n) unless I have tail
    // Node* get_tail(){
    // }

    ////////////////////////////
    // Easy
    ////////////////////////////
    void delete_with_key(int value){
        Node* curr = head;
        Node* prev = nullptr;
        while(curr){
            if(curr->value == value){
                Node* to_delete = curr;
                curr = curr->next;
                delete_node(to_delete, prev);
            }
            else{
                prev = curr;
                curr = curr->next;
            }
        }
    }
    void swap_pairs(){
        // Remember doing this before, But I was forcing it, I don't think i come up with this simple solution back then
        Node* curr = head;
        while(curr && curr->next){
            swap(curr->value,curr->next->value);
            curr = curr->next->next;
        }

    }
    // void reverse(); Done before, even recursive

    // void delete_even_positions(); Simple, cnt = 1 check cnt if even delete
    void insert_sorted(int value){
        // [2,4,7,10,15,20] -> insert 8
        Node* new_node = create_node(value);
        if(empty()){
            head = tail = new_node;
            size++;
            return;
        }

        Node* curr = head;
        Node* prev = nullptr;
        while(curr && curr->value <= value){
            prev = curr;
            curr = curr->next;
        }
        // valid syntax? No!
        // (prev)?prev->next:head = new_node; 
        link_after(prev, new_node);
    }

    ////////////////////////////
    // Medium
    ////////////////////////////

    // Helpers
    void print_with_address(){
        Node* curr = head;
        while (curr)
        {
            cout << curr->value << "(address: " << curr << ")\t";
            curr = curr->next;
        }
        
    }
    
    Node* get_before(Node* node){
        // Getting before 
        if (empty() || node == head) return nullptr;
        Node* curr = head;
        while (curr && curr->next != node) {
            curr = curr->next;
        }
        return curr;
    }

    Node* delete_node_after(Node* prev){
        if(empty() || !prev || !prev->next) return nullptr;

        // How to delete head? It's own function - For now
        Node* after = prev->next;
        Node* next_node = after->next;
        if(after == tail){ tail = prev;}
        prev->next = after->next;
        delete after;
        size--;
        return next_node;
    }
    // It's own function
    void delete_head(){
        if(empty()) return;
        unlink_head();
    }

    void swap_head_and_tail(){
        // Head == Tail is like swapping anyways
        if(empty() || head == tail)return;

        Node* before_tail = get_before(tail); // O(n) -> We need double linked list

        tail->next = head->next;

        before_tail->next = head;

        head->next = nullptr;

        swap(head,tail);
    }
    void left_rotate(int k){
        // Got a crazy idea -> Circular the first I think would be okay
        if(empty()) return;

        // k is wrapping around 
        k %= size;
        if(k == 0) return; // => It's safe even if this is not here -> since the loop won't work, But we will link the list and then delink

        // Circular
        tail->next = head;
        
        // this could be a fuction like get_nth_node(k)
        for (int i = 0; i < k; i++) {
            head = head->next;
            tail = tail->next; 
        }
        // Cut the link
        tail->next = nullptr;
    }
    void remove_duplicates(){
        if(empty()) return;
        // No sets -> O(n^2) is the best we can do

        Node* curr = head;
        while(curr){
            // Very Critical To know -> It's a linked list
            // You don't need to make look at the start again(head) 
            // You need the next of yourself
            // Why it works? there will be no duplicates before it only after it (even unsorted)
            // We remove them when we go
            // Maybe it's Intuitive but I didn't get it at first
            Node* look = curr; // Look will be before what we are looking for
            // Using look->next here since we will need any way the one before the deleted one - Works just fine
            while(look->next){
                if(look->next->value == curr->value){
                    // Duplicate
                    delete_node_after(look); 
                }else{
                    // No found
                    look = look->next;
                }
            }
            //
            curr = curr->next;
        }
    }
    void remove_last_occurance(int key){
        if(empty()) return;
        Node* curr = head;
        Node* prev = nullptr;
        Node* marker = nullptr;
        Node* marker_prev = nullptr;

        while(curr){
            if(curr->value == key){
                marker = curr;
                marker_prev = prev;
            }
            prev = curr;
            curr = curr->next;
        }
        // Found
        if(marker){
            // I made a helper for - Checks if head or tail -> deals with edge cases
            delete_node(marker, marker_prev);
        }
        // Not found
    }
    // Returns after
    Node* move_node_back(Node* node){
        // You dumb?
        // Can't move nothing to end nor moving the last node to last 
        if(node == tail || !node){
            return nullptr;
        }
        if(empty()){
            head = tail = node;    
            return nullptr;
        }

        // Just adjust the head before doing the work
        Node* after = node->next;
        if(node == head){
            head = head->next;
        }
        tail->next = node;
        tail = node;
        tail->next = nullptr;
        return after;
    }
    // Took Quiet sometime tbh didn't feel the time flying -> 30 pure min
    void move_to_back(int value){
        // Note: Infinite Loop 
        if(empty())return;
        Node* old_tail = tail; // MUST Be Here - Unless you go with last you already moved and will be stuck in infinite loop
        Node* curr = head;
        Node* prev = nullptr;
        while(curr != old_tail){
            if(curr->value == value){
                if(prev) // Linking if head is the one -> there would be no prev
                    prev->next = curr->next; // No need to link if it's the first one
                curr = move_node_back(curr);
            }else{
                prev = curr;
                curr = curr->next;
            }
        }
        // Last one - Still have to do Even if there were no movement happening
        // It will do nothing if it's the (actual) tail
        if(curr->value == value){
            // Unlink last node before moving
            if(prev) {
                prev->next = curr->next;
                move_node_back(curr);
            } else {
                // If last node is head
                head = head->next;
                move_node_back(curr);
            }
        }

        // I could've moved size times - Overthinking........
    }
    int max(Node* node){
        if(!node){
            return INT_MIN;
        }
        int right = max(node->next);
        if(node->value >= right)
            return node->value;
        else   
            return right;
        // return std::max(node->value,max(node->next));

    }
    int max(){ return max(head); }

    // A Trick Never seen before
    int max_trick(Node* node = nullptr,bool is_first_call = true){
        if(is_first_call){
            return max_trick(head,false);
        }
        if(!node){
            return INT_MIN;
        }
        return std::max(node->value,max_trick(node->next,false));

    }
    ////////////////////////////
    // Hard 
    ////////////////////////////
    void arrange_odd_even(){
        if(size <= 2)return;
        Node* odd = head;    
        Node* first_even = head->next; // have to mark it to connect later

        while(odd->next && odd->next->next){ // There is even and next odd
            Node*& next_odd = odd->next->next;
            odd->next = next_odd;

            Node*& even = odd->next;
            even->next = even->next->next;

            odd = odd->next;
            // Dealing with tail can be with a pointer than knows where is the last even
            // or, better always updating the tail -> that if we are dealing with odd size linked list
            if(size%2){
                tail = even;
            }
        }
        odd->next = first_even;

    }

    // Done Before - Merge Sort is better with linked list (This Questions feels like merging)
    // void insert_alternating(const LinkedList& l2);

    // Done it before - LeetCode Question 
    // void add_numbers(const LinkedList& l2);

    void remove_all_repeated(){
        if(empty())return;

        Node* curr = head;
        Node* prev = nullptr;
        while(curr){
            bool found_duplicate = false;
            Node* s = curr;
            // Searching if it exist after it
            while(s->next){
                if(s->next->value == curr->value){
                    found_duplicate = true;
                    s = delete_node(s->next,s); 
                }
            }
            // if something was found we remove this also
            if(found_duplicate){
                curr = delete_node(curr,prev); // Very handy function
            }else{
                prev = curr;
                curr = curr->next;
            }
        }
    }
    // I think I did this before but within a smaller scale
    Node* reverse_sublist(Node* start,Node* end){
        // Shouldn't include end and should return the head of the new list
        return nullptr;
    }
    void reverse_chain(int k){
        // TODO:
        // Should link sublists with each other -> Don't forget head to move 
    }

};



void test_general() {
    cout << "=== General Linked List Stuff ===\n";
    LinkedList list;
    list.insert_sorted(5);
    list.insert_sorted(3);
    list.insert_sorted(7);
    list.insert_sorted(1);
    list.insert_sorted(5);
    list.insert_sorted(0);
    cout << "After insert_sorted: "; list.print();

    list.insert_front(10);
    cout << "After insert_front: "; list.print();

    list.delete_front();
    cout << "After delete_front: "; list.print();

    cout << "\n";
}

void test_easy() {
    cout << "=== Easy Problems ===\n";
    LinkedList list;
    list.insert_sorted(5);
    list.insert_sorted(3);
    list.insert_sorted(7);
    list.insert_sorted(1);
    list.insert_sorted(5);
    list.insert_sorted(0);

    list.swap_pairs();
    cout << "After swap_pairs: "; list.print();

    list.delete_with_key(5);
    cout << "After delete_with_key(5): "; list.print();

    cout << "\n";
}

void test_medium() {
    cout << "=== Medium Problems ===\n";
    LinkedList list;
    list.insert_sorted(3);
    list.insert_sorted(7);
    list.insert_sorted(1);
    list.insert_sorted(3);
    list.insert_sorted(7);
    list.insert_sorted(7);

    cout << "Before remove_duplicates: "; list.print();
    list.remove_duplicates();
    cout << "After remove_duplicates: "; list.print();

    // Test remove_last_occurance
    list.insert_sorted(7); // Add another 7 for last occurrence
    cout << "Before remove_last_occurance(7): "; list.print();
    list.remove_last_occurance(7);
    cout << "After remove_last_occurance(7): "; list.print();

    // Test swap_head_and_tail
    cout << "Before swap_head_and_tail: "; list.print();
    list.swap_head_and_tail();
    cout << "After swap_head_and_tail: "; list.print();

    // Test left_rotate
    cout << "Before left_rotate(2): "; list.print();
    list.left_rotate(2);
    cout << "After left_rotate(2): "; list.print();

    // Test move_to_back
    list.insert_front(3);
    list.insert_front(1);
    list.insert_front(7);
    cout << "Before move_to_back(3): "; list.print();
    list.move_to_back(3);
    cout << "After move_to_back(3): "; list.print();

    // Edge case: move_to_back for value not present
    cout << "Before move_to_back(99): "; list.print();
    list.move_to_back(99);
    cout << "After move_to_back(99): "; list.print();

    // Edge case: remove_last_occurance for value not present
    cout << "Before remove_last_occurance(99): "; list.print();
    list.remove_last_occurance(99);
    cout << "After remove_last_occurance(99): "; list.print();

    // Test max function
    cout << "Max value in list: " << list.max() << endl;
    cout << "\n";
}
void test_hard() {
    cout << "=== Hard Problems ===\n";
    LinkedList hard;
    // Test arrange_odd_even
    for(int i=1; i<=7; ++i) hard.insert_sorted(i); // 1 2 3 4 5 6 7
    cout << "Before arrange_odd_even: "; hard.print();
    hard.arrange_odd_even();
    cout << "After arrange_odd_even: "; hard.print(); // Should be odds then evens

    // Test remove_all_repeated
    LinkedList rep;
    int arr[] = {1,2,2,3,3,3,4,5,5,6,7,7,7,8};
    for(int v : arr) rep.insert_sorted(v);
    cout << "Before remove_all_repeated: "; rep.print();
    rep.remove_all_repeated();
    cout << "After remove_all_repeated: "; rep.print(); // Should have only unique values
}

int main() {
    // Now, I hate AI
    test_general();
    test_easy();
    test_medium();
    test_hard();
    cout << "NO RTE\n";
    return 0;

}