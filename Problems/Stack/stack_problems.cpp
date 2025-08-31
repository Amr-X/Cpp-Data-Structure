#include <bits/stdc++.h>
using namespace std;

////////////////
// Easy - Mid
////////////////

// O(n) for pop and push
// How we implement our DS is important regarding the time and space
// Any implementation will work, but the design of such is critical
class ReverseStack{
    int* array{};
    int size{};
    int added_elements{};
public:
    // Note: Can be on the stack not heap
    ReverseStack(int size)
    :array{new int[size]},size{size},added_elements{0}{}
    ~ReverseStack(){
        delete[] array;
    }
    bool is_empty(){
       return added_elements == 0; 
    }
    bool is_full(){
        return added_elements == size;
    }
    bool push(int value){
        if(is_full()){
            return false;
        }
        for (int i = added_elements - 1; i >= 0; i--)
        {
            array[i+1] = array[i];
        }
        array[0] = value;
        added_elements++;
        return true;
    }
    bool pop(){
        if(is_empty()){
            return false;
        }
        for (int i = 1; i < added_elements; i++) {
            array[i-1] = array[i];
        } 
        added_elements--;
        return true;
    }
    bool top(int& result){
        if(is_empty()){
            return false;
        }
        result = array[0];
        return true;
    }
};
string reverse_subwords(string line){
    // Done before
    // read the line with stringstream push each to stack then pop until empty printing each
    return "";
}

int reverse_num(int num){
    // Done before
    // Push to stack each digit %, Build number from the stack again
    return 0;
}
int valid_parentheses(string str){
    // Done before
    // Note: for getting the closed version of a character
    // Use hashtable (i.e. unordered_map)  - first time I made a fuction with multiple or's logic
    return 0;
}

string remove_duplicates(string s){
    // Done before
    // I don't remember if i did it without a stack 
    // But I did with stack - Use a stack to push character
    // pop anything that matched the current character -> aa <- push a left with [..] nothing
    return "";
}

// Two Stacks 
// Done before - Some deleted code way back
// top1 at 0, top2 at size - 1
// push top1++ , push top2--
// full top1+1 == top2
// empty top1 == 0 && top2 == size-1

////////////////
// Mid - Hard 
////////////////

// Done before -> Previous Course
// Use stack take one of them and hit the stack with it any lesss value pop it
// until a bigger one which then you marked as destoryed and don't push it
// if equal then stop and marked as destoryed also
// if empty push it
vector<int> astroid_collision(vector<int> astroids){return {};}

// Only Recursive
// O(N) time and space
void insert_at_bottom(stack<int>& stk,int value){
    if(stk.empty()){
        stk.push(value);
        return;
    }
    int top = stk.top(); stk.pop();
    insert_at_bottom(stk,value);
    stk.push(top);
}
// O(N^2) time 
void reverse(stack<int>& stk){
    if(stk.empty()) return; 
    int top = stk.top(); stk.pop();
    reverse(stk);
    insert_at_bottom(stk,top); // O(N)
}
// Factorial Simulation
struct Element{
    int argument{};
    int return_type{};
    Element(int argument,int return_type = -1)
    : argument(argument),return_type(return_type){}
};

int f(int n){
    if(n == 1){
        return 1;
    }
    return n * f(n-1);
}

// Simulating Factorial Function
int factorial(int n){
    stack<Element> st;
    st.push(Element{n}); // no return type yet
    Element curr{n}; // Used for the current operation

        while(n != 1){
            n--;
            st.push(Element{n});
        }
        // Base case
        st.top().return_type = 1;

        // or st.size > 1
        while(!st.empty()){
            curr = st.top(); st.pop();
            if(!st.empty())
                st.top().return_type = curr.argument * curr.return_type;
        }

    return curr.return_type;    
}
// Simulating Factorial Function
int factorial1(int n){
    stack<Element> st;
    st.push(Element{n}); // no return type yet
    Element curr{n}; // Used for the current operation
    while(!st.empty()){
        while(true){
            n = n-1;
            if(n == 1){
                st.push(Element{n,1});
                break;
            }
            st.push(Element{n,-1});
        }

        while(!st.empty()){
            curr = st.top(); st.pop();
            if(!st.empty())
                st.top().return_type = curr.argument * curr.return_type;
        }
    }

    return curr.return_type;    
}

// Done before - Previous Course
// Idea: stack of integers with sential value (like 0) to represent a frame
// to get value of it double what ever inside it like (0 2 3)  -> 2*(2 + 3) -> (10)
int score_of_parentheses(string s){return 0;}

// Done before - Previous Course
// But I think my logic of it wan't the one explained -> Traversing the array from end and maintaining a stack of candidates of a next greater one -> pop until found or empty
// To know: It's a monotonic stack
vector<int> next_greater_element(vector<int>& vec){
   return {}; 
}

//////////////////////////////
// Linked Based Stack
//////////////////////////////

// I see it as the best way to represent stack 
// I don't know why, But it's very Efficient -> o(1)
// Very dynamic Not tight to some size
// The only cons about it is that it's not cache friendly which could slow you a bit
// yeah, And also need to delete everything O(n)

// List
// Pros:
//  - Dynamic - No size 
//  - No wasted space
// Cons:
//  - Not cache friendly 
//  - Deleting the Nodes O(n) - I don't see this as an issue
////////////////
// Array
// Pros:
//  - Simple 
//  - Cache friendly
// Cons:
//  - Not Dynamic - Tight Space -> Has to be growable  - But could be better in some cases
//  - Could waste Space 

class list_stack{
    struct Node{
        int value{};
        Node* next{};
        Node(int value = 0, Node* next = nullptr)
        :value(value),next(next){};
    };
public:    
    list_stack()
    :head(nullptr){}
    ~list_stack(){
        while(head){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = nullptr;
    }
    // In linked list representation it's full if Ram is out
    // Should check new's exception
    void push(int value){
        head = new Node(value,head);
    }

    void pop(){
        if(is_empty()){return;}
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    int top(){
        if(is_empty()) return;
        return head->value;
    }
    bool is_empty(){
        return !head;
    }
private:
    Node* head{};
};

int precedence(char op) {
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}
string infixToPostfix(string infix) {
	list_stack operators;
	string postfix;

    // Copy pasting cuz of this tricks - Why I didn't think of it before?
	infix += '-';		// Whatever lowest priority: force stack got empty
	operators.push('#');// Remove IsEmpty

	for (int i = 0; i < (int) infix.size(); ++i) {
		if (isdigit(infix[i]))
			postfix += infix[i];
		else {
			while (precedence(operators.top()) >= precedence(infix[i]))
				postfix += operators.top(); operators.pop();
			operators.push(infix[i]);
		}
	}
	return postfix;
}
// To do it with () Only thing you need is to push '(' and do the logic as if hitting '(' was like an empty stack -> that is it
// when ')' is like poping everything from the stack until '('

////////////////
// Mid - Hard
////////////////

// ^/*+- -> (), we just need to care the r-l associative for the ^
// Skip Now  *********
string better_infix_postfix(string infix){return "";}

// Done before -> based on operator (binary,unary,otherwise) pop from the stack of digits(numbers) -> switch statement or something
double postfix_eval(string postfix){return 0.0;}

// void stack::delete_middle(){} in O(1)
// It can't be an array based -> shifting elements require o(n)
// So, the only valid thing is linked list. But Finding the middle -> O(n)
// So, how about we maintain a pointer to the middle? update it with every pop and push like head and tail
// if it's a single list -> Pointer at middle - 1 ( the one before middle ) -> o(1)
// if it's a double list -> Pointer at middle and do the deletion operation -> O(1)

// With every "(" we push the result as oppsite of the operator
// I mean if '(' -> then any '+' becomes '-' and any '-' becomes '+'
// Skip Now  *********
string remove_expression_bracket(string infix) {return "";}


int main(){
    // No test cases
    return 0;
}
