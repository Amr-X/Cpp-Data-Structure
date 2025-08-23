/*
    - Binary Tree Implementation Using Linked List
*/
#pragma once
#include <stdexcept>
#include "Queue\List\Queue.h"
#include "Stack\List\List_Stack.h"
// Iterative
template<typename Type>
class BinaryTree{
private:
    // Node Struct
    struct Node
    {

        Type m_data{};
        Node* m_parent{}; // Better
        Node* m_left{};
        Node* m_right{};

        Node(const Type& data = Type{},Node* parent = nullptr,Node* left = nullptr,Node* right = nullptr)
        :m_data{data},m_parent{parent},m_left{left},m_right{right}{}
    };
    // I Like It
    class Position{
        friend class BinaryTree;
    private:
        Node* m_pos{};
        Position(Node* pos)
        :m_pos{pos}{}
    public:
        Position left() const{
            return {m_pos->m_left};
        }
        Position right() const{
            return {m_pos->m_right};
        }
        Position parent() const{
            return {m_pos->m_parent};
        }
        bool isParent() const{
            return m_pos->m_parent == nullptr;
        }
        bool isExternal() const{
            return (!m_pos->right && !m_pos->m_left);
        }
        operator bool() const{ // First Time
            return m_pos != nullptr;
        }
        const Type& operator*() const{
           return m_pos->m_data; 
        }
        Type& operator*(){
           return m_pos->m_data; 
        }
    };
public:
    BinaryTree()
    :m_root{nullptr},m_last_nodes{}{}
    ~BinaryTree(){
        clear();
    }
    // Later Copy 
    // Doesn't Work..
    // BinaryTree& BinaryTree(BinaryTree&& rhs)
    // :m_root{rhs.m_root},m_last_nodes{std::move(rhs.m_last_nodes)}{
    //     rhs.m_root = nullptr;
    // }
    BinaryTree& operator=(BinaryTree&& rhs){
        clear();
        m_root = rhs.m_root;
        m_last_nodes = std::move(rhs.m_last_nodes);
        rhs.m_root = nullptr;
    }

    bool empty() const{
        return m_root == nullptr;
    }
    void insert(const Type& to_insert){
        // LevelByLevel Insertion
        if(empty()){
            m_root = new Node(to_insert);
            m_last_nodes.enqueue(m_root);
            return;
        }

        Node* parent = m_last_nodes.front();
        Node* new_node = new Node(to_insert,parent);
        if(!parent->m_left){
            parent->m_left = new_node;
        }else{
            parent->m_right = new_node; 
            m_last_nodes.dequeue();
        }
        m_last_nodes.enqueue(new_node);
    }
    void insert(const Type& to_insert,const Position& pos){ // Note: On left ,If not on right
        Node* par = pos.m_pos;
        if(!par){ return; }

        if(par->m_left == nullptr){
            par->m_left = new Node(to_insert,par);
        }else if (par->m_right == nullptr){
            par->m_right = new Node(to_insert,par);
        }
        ; // Completed Node
    }
    void remove(const Type& to_remove){
        if(empty()) return;
        Node* curr = m_root;
        // Challenging

    }
    void remove(const Position& pos){

    }
    bool contain(const Type& to_find) const{
        // Clever
        bool found{};
        Preorder([&found,&to_find](const Type& data){ // To See to_find and found
            if(data == to_find){
                found = true;
            }
        });
        return found;
    }
    void clear(){
        // Only recursive here
        clear(m_root);
        m_root = nullptr;
    }

    // Traversing - Want it with Function Pointer or Lambda 
    template<typename Function>
    void Preorder(Function func) const{
        
        Stack<Node*> stack;
        Node* curr = m_root;

        while(curr || !stack.empty()){
            if(curr){
                func(curr->m_data);
                stack.push(curr);
                curr = curr->m_left;
            }else{
                curr = stack.top(); stack.pop();
                curr = curr->m_right;
            }
        }
    }
    template<typename Function>
    void Inorder(Function func) const{
        Stack<Node*> stack;
        Node* curr = m_root;

        while(curr || !stack.empty()){
            if(curr){
                stack.push(curr); // First
                curr = curr->m_left;
            }else{
                curr = stack.top();
                stack.pop();
                func(curr->m_data);
                curr = curr->m_right;
            }
        }
    }
    // template<typename Function>
    // void Postorder(Function func) const{
    //     Stack<int> stack; // Node* 
    //     Node* curr = m_root;

    //     while(curr || !stack.empty()){
    //         if(curr){
    //             curr = curr->m_left;
    //             stack.push((int)curr);
    //         }else{
    //             // We are now on right, But we didn't print parent
    //             // So, we need to store it again to get back to, We use negative address to distinguish between 
    //             // Whether we are back to go right, or, to print parent
    //             int temp = stack.top();stack.pop();
    //             if(temp >= 0){
    //                 curr = (Node*)temp; // Go right
    //                 stack.push(-1 * (int)curr); // We need to get back here
    //                 curr = curr->m_right; 
    //             }else{
    //                 temp *= -1;
    //                 curr = (Node*) temp; // Print parent
    //                 func(curr->m_data);
    //             }
    //         }
    //     }
    // }



private:
    Node* m_root{};
    Queue<Node*> m_last_nodes{}; // Facilitate O(1) Insertion
    //
    void clear(Node* root){
        if(!root)return;
        clear(root->m_left);
        clear(root->m_right);
        delete root;
    }
};
