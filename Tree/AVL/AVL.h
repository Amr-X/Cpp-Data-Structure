/* 
    - AI Generated Test For AVL
*/
#pragma once

// Balance Factor = Height L-Subtree - Height R-Subtree
template<typename Type>
class AVLTree{
    void insert(const Type& to_insert,Node*& root){ // The & Is Very Important
        if(!root){
            root = new Node(to_insert); // Notice root is nullptr
            return;
        }
        if(to_insert < root->m_data){
            insert(to_insert,root->m_left);
        }else if(to_insert > root->m_data){
            insert(to_insert,root->m_right);
        }
        // They are Equal.. Didn't Think of Duplicates
        // Ignore For now
    }
private:
    // Node Struct
    struct Node
    {
        Type m_data{};
        int m_height{}; // Height of Every Node
        Node* m_left{};
        Node* m_right{};

        Node(const Type& data = Type{},Node* left = nullptr,Node* right = nullptr)
        :m_data{data},m_left{left},m_right{right}{}

        // Could Move Here
    };
    Node* m_root{};

    bool contains(const Type& to_find,Node* root) const{
        // Again, Operator < and Operator == Is Assumed Here - Works With Primitive Types
        if(!root){
            return false;
        }else if(to_find < root->m_data){ // On Left Tree
            return contains(to_find,root->m_left);
        }else if(to_find > root->m_data){ // On right
            return contains(to_find,root->m_right);
        }
        // Equal!!
        return true;
    }
    void insert(const Type& to_insert,Node*& root){ // The & Is Very Important
        if(!root){
            root = new Node(to_insert); // Notice root is nullptr
            return;
        }
        if(to_insert < root->m_data){
            insert(to_insert,root->m_left);
        }else if(to_insert > root->m_data){
            insert(to_insert,root->m_right);
        }
        // They are Equal.. Didn't Think of Duplicates
        // Ignore For now
    }
    void remove(const Type& to_remove,Node*& root){
        // Challenging To Connect - if It's Deg(2)
        if(!root){
            return ;
        }else if(to_remove < root->m_data){ // On Left Tree
            return remove(to_remove,root->m_left);
        }else if(to_remove > root->m_data){ // On right
            return remove(to_remove,root->m_right);
        }

        // Very Important 
        // Found
        if(root->m_left && root->m_right){
            // Two Children - Idea is to get inorder pre/post successor instead and go delete that until we get to 1 child or none
            Node* next_to_delete = findMax(root->m_left);
            root->m_data = next_to_delete->m_data;
            remove(next_to_delete->m_data,root->m_left); // Traverse Same n Times again  like findMax (Has to be better)

        }else{
            // One Or Zero
            Node* temp = root; // Will Delete after modifying Where we Should Connect to
            root = (root->m_right)?root->m_right:root->m_left;
            delete temp;
        }
    }
    void clear(Node* root){
        if(!root) return;
        clear(root->m_left);
        clear(root->m_right);
        delete root;
    }
    // My Find Max Returns A Pointer Used in remove Function
    Node* findMax(Node* root) const { 
        if(!root) return nullptr;
  
        while(root->m_right){
            root = root->m_right;
        }
        return root;
    }

};