#include <bits/stdc++.h>
using namespace std;
// Copy Pasted -> New Recursion Way of representing a BinaryTree
class BinaryTree {
 private:
  int data{};
  BinaryTree *left{};
  BinaryTree *right{};

 public:
  BinaryTree(int data) : data(data) {}
  ~BinaryTree() { clear(); }

  void print_inorder() {
    if (left) left->print_inorder();
    cout << data << " ";
    if (right) right->print_inorder();
  }

  void add(vector<int> values, vector<char> direction) {
    assert(values.size() == direction.size());
    BinaryTree *current = this;
    // iterate on the path, create all necessary nodes
    for (int i = 0; i < (int)values.size(); ++i) {
      if (direction[i] == 'L') {
        if (!current->left)
          current->left = new BinaryTree(values[i]);
        else
          assert(current->left->data == values[i]);
        current = current->left;
      } else {
        if (!current->right)
          current->right = new BinaryTree(values[i]);
        else
          assert(current->right->data == values[i]);
        current = current->right;
      }
    }
  }
  ////////////////
  // Easy
  ////////////////
  // ALl Done before -> But first time dealing with this recursive
  // representation
  int max() {
    int left_max = (left) ? left->max() : INT_MIN;
    int right_max = (right) ? right->max() : INT_MIN;
    return std::max({left_max, right_max, data});
    // return std::max({left_max,right_max,data}); // Initializer_list
  }
  int height() {
    if (!left && !right) return 0;
    int left_height = (left) ? left->height() : 0;  // No Height for nullptr
    int right_height = (right) ? right->height() : 0;
    return (left_height >= right_height) ? left_height + 1 : right_height + 1;
  }

  // this is why it's weird -> What if no nodes at all?
  // How it should look like?
  // I think you can't to create the first binray tree you need a value
  // if done then you have 1 node -> In 0 nodes cases that means the tree isn't
  // even created that is so different than what i used to do
  int total_nodes() {
    return ((left) ? left->total_nodes() : 0) +
           ((right) ? right->total_nodes() : 0) + 1;
  }

  int count_leaf_nodes() {
    if (!left && !right) {
      return 1;
    }
    int res = 0;
    if (left) res += left->count_leaf_nodes();
    if (right) res += right->count_leaf_nodes();
    return res;
  }

  bool search(int &value) {
    if (data == value) return true;
    if (left && left->search(value)) return true;
    if (right && right->search(value)) return true;
    return false;
  }

  // Base Cases here are weird

  // Don't why struggled with this
  bool is_perfect() {
    // Could combine both height O(n) and is_perfect O(n) in one function

    // If both subtrees are perfect AND their height match
    if (!right && !left)  // One Node is perfect
      return true;
    // One could be null -> We can't call on a nullptr->is_perfect() ->
    // Dereferencing Nullptr
    if (!right || !left)  // Node with one nullptr child
      return false;

    return left->is_perfect() && right->is_perfect() &&
           left->height() == right->height();
  }

  bool is_perfect_formula() {
    return total_nodes() == std::pow(2, height() + 1) - 1;
  }
  ///////////////////
  // Mid - Hard
  ///////////////////

  // I don't care about the time complexity here -> The logic is the main
  // concern

  void clear() {
    // This works since left is a binary tree and it will call ~binaryTree()
    // recursively
    delete left;
    delete right;
    // Root still around with it's both left and right
    left = nullptr;
    right = nullptr;
  }
  // What about root as a stack object?

  // Done before A lot
  // void inorder_iterative(){}

  void traverse_left_boundary() {
    // isn't it just go left side
    // if no left then go right?
    // until you hit a nullptr?
    BinaryTree *curr = this;
    while (curr) {
      cout << curr->data << " ";
      if (curr->left)
        curr = curr->left;
      else
        curr = curr->right;
    }
  }

  // I Can't know where will be that diameter?
  // On right? on Left? -> I have to brute force my way?
  // These are new to me
  int binary_tree_diameter() {
    // Getting number of nodes between deepest left and deepest right
    int through_root = 1;
    if (left) through_root += (left->height());
    if (right) through_root += (right->height());

    // We need it from the right tree
    int right_di = (right) ? right->binary_tree_diameter() : 0;
    // We need it from the left tree
    int left_di = (left) ? left->binary_tree_diameter() : 0;

    return std::max({through_root, right_di, left_di});
  }
  //////////////////////////////
  // Problems (2) Level By Level - Mid - Hard
  //////////////////////////////

  // This is interseting -> It's not mine

  // So, this prints only if given level is right if not it will call both right
  // and left The result is printing a certain level only
  void print_nodes_level(int level) {
    if (level == 0)
      cout << data << " ";
    else if (level) {
      if (left) left->print_nodes_level(level - 1);
      if (right) right->print_nodes_level(level - 1);
    }
  }

  void level_order_traversal_recursive() {  // O(n^2)
    int h = height();

    for (int level = 0; level <= h; level++)
      // Now, we call it on every level from 0 -> h
      print_nodes_level(level);
  }

  // Done before -> Used a deque and the level to indicate if odd or even - That
  // is it 103.binary-tree-zigzag-level-order-traversal
  void print_spiral() {}

  bool is_complete() {
    // My idea is to use levelbylevel if you hit a nullptr you should only see
    // nullptr after that only

    queue<BinaryTree *> q;
    BinaryTree *curr{};
    q.push(curr);
    bool nullptr_pushed = false;
    while (!q.empty()) {
      curr = q.front();
      q.pop();
      // Potentially a nullptr pushed
      if (curr->left) {  // a valid pointer
        q.push(curr->left);
        if (nullptr_pushed) return false;  // and there was a nullptr before
      } else {
        nullptr_pushed = true;
        // Don't have to push it actually in the queue
      }

      if (curr->right) {
        q.push(curr->right);
        if (nullptr_pushed) return false;
      } else {
        nullptr_pushed = true;
      }
    }
    // Done traversing didn't return false, no node after a nullptr -> It's
    // complete
    return true;
  }
  //////////////////////////////
  // Problems (3) BinaryTree Generation - Mid
  //////////////////////////////
  // Don't call with empty -> i don't care about edge cases
 private:
  BinaryTree(deque<int> &inorder, auto start, auto end, deque<int> &preorder) {
    // inorder empty -> no range
    if (start == end) return;

    // So, Is this alway right? that preorder front has the right data for the
    // current tree? Should I trust the logic?
    data = preorder.front();
    preorder.pop_front();

    // Find in inorder
    auto location_in_inorder = end;  // Not found
    for (auto it = inorder.begin(); it != inorder.end(); it++) {
      if (*it == data) {
        location_in_inorder = it;
        break;
      }
    }

    // Splitting - Avoiding Empty deque
    if (start != location_in_inorder)  // Nothing on left side don't create
      left = new BinaryTree(inorder, start, location_in_inorder, preorder);
    if (end != location_in_inorder)  // Same
      right = new BinaryTree(inorder, location_in_inorder + 1, end, preorder);
  }

 public:
  BinaryTree(deque<int> &inorder, auto start, auto end, deque<int> &preorder)
      : BinaryTree(inorder, inorder.begin(), inorder.end(), preorder) {}
  // It's been 1.5 Hours only to realize that it's preorder and not inorder
  // ........... It's Easy to do
  BinaryTree(queue<pair<int, bool>> preorder) {
    auto [value, is_leaf] = preorder.front();
    preorder.pop();
    data = value;

    if (!is_leaf) {  // Base case -> Create it with 2 nullptr and don't create
                     // any more
      if (!preorder.empty()) left = new BinaryTree(preorder);
      // it will pop from the queue which why we should ask again if it's empty
      if (!preorder.empty()) right = new BinaryTree(preorder);
    }
  }
  //////////////////////////////
  // Problems (4) BinaryTree Serialization - Mid
  //////////////////////////////

  // Some Talk
  /*
    - Serialization -> Data Structure to be represented
    - Canonicalization -> Converting Multiple representation to one simple
    representation
    - E.g (2/4) is (1/2) also (4/8) is (1/2), So (1/2) can be represented in
    more that one way
    - Canonicalization something is to unify that (2/4),(2/8) -> (1/2)

    // What that have to do with tree?
    // What if you want to know if a tree have the same values at same exact
    node location as the other trees?
    // You can make the O(n) logic simply traversing each at the same time
    // But, if i said you have 8 trees? They are equal?
    // To Ease this up -> Use Serialization to represent it -> Let's say like
    this Preorder:[12,4,-1,-1,5,-1,6,-1,-1] or ((12)(4)()()(5)()(6)()())
    // Now, Use Canonicalization to make the logic -> (int this case) Just see
    if tree_ser3 == tree_ser2
    // - A more complicated problem -> do they have same values (don't have to
    be at same node)
    // Use Serialization to represent it? -> Same
    // Use canonicalization -> Sort them and compare

  */
  bool is_mirror(BinaryTree *first, BinaryTree *second) {
    if (!first || !second) return (first == second);
    return (first->data == second->data) &&
           (is_mirror(first->left, second->right)) &&
           (is_mirror(first->right, second->left));
  }
  // O(n)
  bool is_symmetricR() {
    // root is symmetric by definition
    return is_mirror(right, left);
  }
  // Serialization-Canonicalization
  void serialize_canonicalize(vector<int> &res) {
    // Nullptr == -1
    // Inorder -> Easier, And I like it
    if (left)
      left->serialize_canonicalize(res);
    else
      res.push_back(-1);

    res.push_back(data);

    if (right)
      right->serialize_canonicalize(res);
    else
      res.push_back(-1);
  }
  // O(n) slightly worse, but it's a general purpose tool
  bool is_symmetric() {
    vector<int> right_ser;
    vector<int> left_ser;
    if (left) {
      left->serialize_canonicalize(left_ser);
    }
    if (right) {
      right->serialize_canonicalize(right_ser);
    }
    // I Don't have to do a thing here -> Left should equal to the right
    // But it depends on the logic

    // Even in empty case - Still holds
    return right_ser == left_ser;
  }

  // TODOs:
  bool is_flip_equivR(BinaryTree *other) {}
  bool is_flip_equiv(BinaryTree *other) {
    vector<int> right_ser;
    vector<int> left_ser;
    if (left) {
      left->serialize_canonicalize(left_ser);
    }
    if (right) {
      right->serialize_canonicalize(right_ser);
    }

    vector<int> other_right_ser;
    vector<int> other_left_ser;
    if (other->left) {
      other->left->serialize_canonicalize(left_ser);
    }
    if (other->right) {
      other->right->serialize_canonicalize(right_ser);
    }
    return right_ser == other_left_ser && left_ser == other_right_ser;
  }

  // This is where it peaks
  // It could be done without serialization. But, Why? Why make it complex?
  // Use set, Map go and look for same structure in tree and alot more to think
  // about Makes it almost impossible to do
  void print_all_duplicates() {
    // Just get the array representation of it
    // And deal with like any array problem
    // Even the structure of it is represented what do you want more?
    vector<int> rep;
    serialize_canonicalize(rep);
  }
};

class ExpressionTree {
 private:
  char data{};
  ExpressionTree *left{};
  ExpressionTree *right{};

 public:
  ExpressionTree(char data) : data(data) {}
  ~ExpressionTree() {
    delete left;
    delete right;
    left = nullptr;
    right = nullptr;
  }

  ExpressionTree(string postfix) {
    // -> (2+3) * 5 -> 23+5*
    // Let's keep it simple -> Think this -> 235*+6+3-
    // and just one digit number -> only +-*/ -> No ()
    // Can extend to more complex expressions
    stack<ExpressionTree *> st;
    for (char &ch : postfix) {
      ExpressionTree *curr = new ExpressionTree(ch);
      if (!isdigit(ch)) {
        // Operator
        ExpressionTree *right = st.top();
        st.pop();
        ExpressionTree *left = st.top();
        st.pop();
        curr->left = left;
        curr->right = right;
      }
      st.push(curr);
    }
    ExpressionTree *result = st.top();
    st.pop();

    data = result->data;
    left = result->left;
    right = result->right;
    // To delete result will call destructor which will delete left and right
    // so make sure it's nullptr
    result->left = nullptr;
    result->right = nullptr;
    delete result;
  }
  void print_inorder(ExpressionTree *root) {
    if (root->left) print_inorder(root->left);
    cout << root->data;
    if (root->right) print_inorder(root->right);
  }
  void print_inorder() { print_inorder(this); }

  void inorder_parentheses(ExpressionTree *root) {
    if (!root) return;
    cout << "(";
    root->print_inorder();
    cout << ")";
  }

  // It's not recursive
  void print_inorder_expression() {
    // inorder will print 5 * 2 + 3 which doesn't tell us if it's
    // (5*2)+3 or 5*(2+3) -> It's represented in memory but we need to surround
    // it with (expression tree) The Question now, is how to not over
    // parentheses it ((5*2)+(3)) Not just if it's operator we do (subtree) -
    // It's when you have + as a child of * that is a child where the parent is
    // higher in precedence of it
    if (left) {
      if (left->right || left->left) cout << '(';
      left->print_inorder();
      if (left->right || left->left) cout << ')';
    }
    cout << data;
    if (right) {
      if (right->right || right->left) cout << '(';
      right->print_inorder();
      if (right->right || right->left) cout << ')';
    }
  }
};

// Easy Level Tests
void test_binary_tree_easy() {
  cout << "\n[Easy Level BinaryTree Tests]\n";
  BinaryTree tree(1);
  tree.add({2, 4, 7}, {'L', 'L', 'L'});
  tree.add({2, 4, 8}, {'L', 'L', 'R'});
  tree.add({2, 5, 9}, {'L', 'R', 'R'});
  tree.add({3, 6, 10}, {'R', 'R', 'L'});
  cout << "Inorder: ";
  tree.print_inorder();
  cout << "\n";
  cout << "Max value: " << tree.max() << "\n";
  cout << "Height: " << tree.height() << "\n";
  cout << "Total nodes: " << tree.total_nodes() << "\n";
  cout << "Leaf nodes: " << tree.count_leaf_nodes() << "\n";
  int search_val = 10;
  cout << "Search " << search_val << ": " << tree.search(search_val) << "\n";
}

// Mid Level Tests
void test_binary_tree_mid() {
  cout << "\n[Mid Level BinaryTree Tests]\n";
  BinaryTree tree(1);

  // Level 2
  tree.add({2}, {'L'});
  tree.add({3}, {'R'});

  // Level 3
  tree.add({2, 4}, {'L', 'L'});
  tree.add({2, 5}, {'L', 'R'});
  tree.add({3, 6}, {'R', 'L'});
  tree.add({3, 7}, {'R', 'R'});

  // Level 4
  tree.add({2, 4, 8}, {'L', 'L', 'L'});
  tree.add({2, 4, 9}, {'L', 'L', 'R'});
  tree.add({2, 5, 10}, {'L', 'R', 'L'});
  tree.add({2, 5, 11}, {'L', 'R', 'R'});
  tree.add({3, 6, 12}, {'R', 'L', 'L'});
  tree.add({3, 6, 13}, {'R', 'L', 'R'});
  tree.add({3, 7, 14}, {'R', 'R', 'L'});
  tree.add({3, 7, 15}, {'R', 'R', 'R'});

  cout << "Is perfect: " << tree.is_perfect() << "\n";
  cout << "Is perfect (formula): " << tree.is_perfect_formula() << "\n";
  cout << "Left boundary: ";
  tree.traverse_left_boundary();
  cout << "\n";
}

// Hard Level Tests
void test_binary_tree_hard() {
  cout << "\n[Hard Level BinaryTree Tests]\n";
  BinaryTree tree(1);
  tree.add({2, 4, 7}, {'L', 'L', 'L'});
  tree.add({2, 4, 8}, {'L', 'L', 'R'});
  tree.add({2, 5, 9}, {'L', 'R', 'R'});
  tree.add({3, 6, 10}, {'R', 'R', 'L'});
  cout << "Diameter: " << tree.binary_tree_diameter() << "\n";
  cout << "Clear tree and print inorder: ";
  tree.clear();
  tree.print_inorder();
  cout << "\n";
}

// ExpressionTree Tests
void test_expression_tree() {
  cout << "\n[ExpressionTree Tests]\n";
  string postfix = "23+5*";  // (2+3)*5
  ExpressionTree et(postfix);
  cout << "Inorder: ";
  et.print_inorder();
  cout << "\n";
  cout << "Inorder with parentheses: ";
  et.print_inorder_expression();
  cout << "\n";
}

int main() {
  test_binary_tree_easy();
  test_binary_tree_mid();
  test_binary_tree_hard();
  test_expression_tree();
  return 0;
}
