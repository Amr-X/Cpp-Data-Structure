#include <bits/stdc++.h>
using namespace std;

class BinarySearchTree {
 private:
  int data{};
  BinarySearchTree* left{};
  BinarySearchTree* right{};

 public:
  BinarySearchTree(int data) : data(data) {}

  void print_inorder() {
    if (left) left->print_inorder();
    cout << data << " ";
    if (right) right->print_inorder();
  }
  ////////////////////////////////////////////

  void insert(int target) {
    if (target < data) {
      if (!left)
        left = new BinarySearchTree(target);
      else
        left->insert(target);
    } else if (target > data) {
      if (!right)
        right = new BinarySearchTree(target);
      else
        right->insert(target);
    }  // else: exists already
  }

  ////////////////////
  // Easy
  ////////////////////

  bool search(int value) {
    BinarySearchTree* curr = this;
    while (curr) {
      if (curr->data == value) {
        return true;
      } else if (curr->data > value)
        curr = curr->right;
      else if (curr->data < value)
        curr = curr->left;
      else
        ;  // No else
    }
    return false;  // null curr
  }
  // Not the obvious recursive and iterative - Where you can check it's left and
  // right recursivly He means to use it's property -> if we inorder it we are
  // given small to big elements And, (min/max) range -> the root should be
  // between (intmax,intmin) the left side should be between (intmax,root) and
  // right side should be between (root,intmin)

  bool is_bst(int min, int max) {
    if (!(min < data && data < max)) return false;
    return (!left || left->is_bst(min, data)) &&
           (!right || right->is_bst(data, max));
  }
  bool is_bst() { return is_bst(INT_MIN, INT_MAX); }
  // The other is the inorder values should be lesss than the prev one - using
  // Serialization. I cba

  // Interesting One -> If you have imbalance tree, Get the the inorder and
  // build it using this one There is some algo that does that in place
  BinarySearchTree* build_sorted_bst(vector<int>& values, size_t i, size_t j) {
    // Based on Binary Search
    // The middle is the root
    if (i >= j) return nullptr;
    size_t m = (i + j) / 2;
    BinarySearchTree* node = new BinarySearchTree(values[m]);
    node->left = build_sorted_bst(values, i, m);
    node->right = build_sorted_bst(values, m + 1, j);
    return node;
  }
  // Could be cleaner
  int k_th_smaller(int& k, int& count) {
    if (left) {
      int value = left->k_th_smaller(k, count);
      if (value != -1234) return value;
    }
    if (k == count++) return data;

    if (right) {
      int value = right->k_th_smaller(k, count);
      if (value != -1234) return value;
    }
    return -1234;
  }

  int k_th_smaller(int k) {
    int count = 1;
    return k_th_smaller(k, count);
  }

  // Good, But what if i were given two pointers to some random nodes that exist
  // here? What is the solution? Oh, It's same logic cuz we are at BST i can
  // search and find out this way I meant if it were a normal binary tree? what
  // is the logic IT will be based on searching -> if the search of left found
  // first or second and search of right found (second) or first -> it means
  // this is the lCA
  int lowest_common_ancestor(const int& first, const int& second) {
    // if one is current node value -> it is it's own ancestor It's the root so
    // ofc it's the ancestor of any other given node Like you given adam (PBUH)
    // and some other guy and asking where their family tree meet? Lik what?
    if (first == data || second == data) return data;  // Can remove this.......

    if (left && first < data && second < data)  // Both are at left side
      return left->lowest_common_ancestor(first, second);

    if (right && first > data && second > data)
      return right->lowest_common_ancestor(first, second);

    return data;  // Two values now split -> one goes left and the other goes
                  // right   -> or oppsite
  }

  ///////////////////
  // Mid - Hard
  //////////////////
 private:
  BinarySearchTree* GetBinarySearchTree(deque<int>& inorder, auto start,
                                        auto end, deque<int>& preorder) {
    // inorder empty -> no range
    if (start == end) return nullptr;
    data = preorder.front();
    preorder.pop_front();

    auto location_in_inorder = end;
    for (auto it = inorder.begin(); it != inorder.end(); it++) {
      if (*it == data) {
        location_in_inorder = it;
        break;
      }
    }
    if (start != location_in_inorder)
      left = new BinaryTree(inorder, start, location_in_inorder, preorder);
    if (end != location_in_inorder)
      right = new BinaryTree(inorder, location_in_inorder + 1, end, preorder);
  }

 public:
  // Building from preorder - Used Same logic for (preorder-inorder)
  // Very bad O(n^2) The searching step
  BinarySearchTree(deque<int>& preorder) {
    deque<int> inorder(preorder.begin(), preorder.end());
    sort(inorder.begin(), inorder.end());
    BinarySearchTree* tree =
        GetBinarySearchTree(inorder, inorder.begin(), inorder.end(), preorder);
    data = tree->data;
    left = tree->left;
    right = tree->left;
    left = nullptr;
    right = nullptr;
    delete tree;
  }
  // TODO
  // That was ugly, Let's start simple
  BinarySearchTree(deque<int>& preorder) {}
  // Using nextgreater logic
  BinarySearchTree(deque<int>& preorder) {}

  // Levelbylevel
  BinarySearchTree(deque<int>& level_order) {}
  ////////////////////////
  // Deletion - Easy-Mid
  ////////////////////////

  // Note: We can't delete root tree in this structure -> On stack

  // Look Code at BST Implemented -> Takes root by & so that it could be changed
  // to point to other valid child That is for node with 1 or 0 children -> If
  // Both Children are there -> Swap with Predecessor and Deletes it by swapping
  // the values (Don't worry It has a predecessor cuz it has it's left subtree)
  // Could've been Done Better -> The swapping and the deleting logic

  // Iti's very interesting to see the same logic with totally different
  // implementations

  // Problem 1 Delete with Predecessor -> Done -> Look code

  // Problem 2 Delete without recursion (lol,this is what i was saying) -> All
  // needed is Modify the parent of the Predecessor

  // Problem 3 Rewriting It with Node Structure -> Same here

  // DONE
};
///////////////////
// Successor - Mid
//////////////////

// For Duplicate Values -> Use any value>=data or value<=data but stick to one
// -> Will be all on the left chain or the right chain Or, Use a variable to
// indicate how many there are of this key
class BSTParent {
 private:
  int data;
  BSTParent* left{};
  BSTParent* right{};
  BSTParent* parent{};

 public:
  BSTParent(int value, BSTParent* parent) : data(value), parent(parent) {}

  void insert(const int& value) {
    if (value < data) {
      if (!left) {
        left = new BSTParent(value, this);
        return;
      }
      left->insert(value);
    }
    if (value > data) {
      if (!right) {
        right = new BSTParent(value, this);
        return;
      }
      left->insert(value);
    } else
      ;  // No duplicates
  }
  int min() {
    BSTParent* curr = this;
    while (curr->left) {
      curr = curr->left;
    }
    return curr->data;
  }
  BSTParent* search(const int& value) {
    if (value == data) return this;
    if (left)
      if (value < data) return left->search(value);
    if (right)
      if (value > data) return right->search(value);
    return nullptr;
  }
  int successor(const int& value) {
    BSTParent* value_node = search(value);
    if (!value_node) return -1;

    // The next item after value
    // On right subtree if there is left
    if (right) {
      return right->min();
    }

    // No right? then its's the parent of the current chain
    // This is were it's redundant
    BSTParent* curr = this;
    while (curr->parent && curr->parent->right == curr) {
      curr = curr->parent;
    }
    // No parent of the current chain? it's the last item on the most right of
    // the tree where there iss no sucesssor
    return (curr->parent) ? curr->parent->data : -1;
  }

  vector<int> Queries_of_ancestors(deque<int> q) {
    // My mind isn't working right now -> TODO
    return {};
  }
};

// Check the range
bool is_degenerate(vector<int>& preorder) {
  if (preorder.size() <= 2)
    return true;  // First node and second node has to be degenerate the3rd one
                  // could be the other child of the root
  // TODO
}
int main() { return 0; }