#include<bits/stdc++.h>
using namespace std;
// Copy Pasted -> New Recursion Way of representing a BinaryTree
class BinaryTree {
private:
	int data { };
	BinaryTree* left { };
	BinaryTree* right { };

public:
	BinaryTree(int data) :
			data(data) {
	}
    ~BinaryTree(){
        clear();
    }

	void print_inorder() {
		if(left)
			left->print_inorder();
		cout << data << " ";
		if(right)
			right->print_inorder();
	}

	void add(vector<int> values, vector<char> direction) {
		assert(values.size() == direction.size());
		BinaryTree* current = this;
		// iterate on the path, create all necessary nodes
		for (int i = 0; i < (int) values.size(); ++i) {
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
    // ALl Done before -> But first time dealing with this recursive representation
    int max(){
        int left_max = (left)? left->max(): INT_MIN;
        int right_max = (right)? right->max(): INT_MIN;
        return std::max({left_max,right_max,data});
        // return std::max({left_max,right_max,data}); // Initializer_list
    }
    int height(){
        if(!left && !right) return 0;
        int left_height = (left)? left->height(): 0; // No Height for nullptr
        int right_height = (right)? right->height(): 0;
        return (left_height>=right_height)?left_height+1:right_height+1;
    }


    // this is why it's weird -> What if no nodes at all?
    // How it should look like?
    // I think you can't to create the first binray tree you need a value
    // if done then you have 1 node -> In 0 nodes cases that means the tree isn't even created 
    // that is so different than what i used to do
    int total_nodes(){
        return ((left)?left->total_nodes():0) + ((right)?right->total_nodes():0) + 1;
    }

    
    int count_leaf_nodes(){
        
        if(!left && !right){
            return 1;
        }
        int res = 0;
        if(left)
            res += left->count_leaf_nodes();
        if(right)
            res += right->count_leaf_nodes();
        return res;
    }

    bool search(int& value){
        if (data == value) return true;
        if (left && left->search(value)) return true;
        if (right && right->search(value)) return true;
        return false;
    }

    // Base Cases here are weird

    // Don't why struggled with this
    bool is_perfect(){
        // Could combine both height O(n) and is_perfect O(n) in one function

        // If both subtrees are perfect AND their height match
        if(!right && !left) // One Node is perfect
            return true;
        // One could be null -> We can't call on a nullptr->is_perfect() -> Dereferencing Nullptr
        if(!right || !left) // Node with one nullptr child
            return false; 

        return left->is_perfect() && right->is_perfect() && left->height() == right->height();
    }

    bool is_perfect_formula(){
        return total_nodes() == std::pow(2,height()+1)-1;
    }
    ///////////////////
    // Mid - Hard
    ///////////////////

    // I don't care about the time complexity here -> The logic is the main concern

    void clear(){
        // This works since left is a binary tree and it will call ~binaryTree() recursively
        delete left;
        delete right;
        // Root still around with it's both left and right
        left = nullptr;
        right = nullptr;
    }
    // What about root as a stack object?

    // Done before A lot
    // void inorder_iterative(){}

    void traverse_left_boundary(){
        // isn't it just go left side
        // if no left then go right?
        // until you hit a nullptr? 
        BinaryTree* curr = this;
        while(curr){
            cout << curr->data << " ";
            if(curr->left)
                curr = curr->left;
            else
                curr = curr->right;
        }
    }

    // I Can't know where will be that diameter?
    // On right? on Left? -> I have to brute force my way?
    // These are new to me
    int binary_tree_diameter(){
        // Getting number of nodes between deepest left and deepest right
        int through_root = 1;
        if(left) through_root += (left->height());
        if(right) through_root += (right->height());
        
        // We need it from the right tree
        int right_di = (right)? right->binary_tree_diameter():0;
        // We need it from the left tree
        int left_di = (left)? left->binary_tree_diameter():0;

        return std::max({through_root,right_di,left_di});
    }
};

class ExpressionTree{
private:
	char data { };
	ExpressionTree* left { };
	ExpressionTree* right { };

public:
	ExpressionTree(char data) :
			data(data) {
	}
    ~ExpressionTree(){
        delete left;
        delete right;
        left = nullptr;
        right = nullptr;
    }

    ExpressionTree(string postfix){
        // -> (2+3) * 5 -> 23+5*
        // Let's keep it simple -> Think this -> 235*+6+3-
        // and just one digit number -> only +-*/ -> No ()
        // Can extend to more complex expressions
        stack<ExpressionTree*> st;
        for (char &ch : postfix)
        {
            ExpressionTree* curr = new ExpressionTree(ch);
            if(!isdigit(ch)){
                // Operator
                ExpressionTree* right = st.top(); st.pop();
                ExpressionTree* left = st.top(); st.pop();
                curr->left = left;
                curr->right = right;
            }
            st.push(curr);
        }
        ExpressionTree* result = st.top(); st.pop();

        data = result->data;
        left = result->left;
        right = result->right;
        // To delete result will call destructor which will delete left and right
        // so make sure it's nullptr
        result->left = nullptr;
        result->right = nullptr;
        delete result;
    }
	void print_inorder(ExpressionTree* root) {
		if(root->left)
			print_inorder(root->left);
		cout << root->data;
		if(root->right)
			print_inorder(root->right);
	}
    void print_inorder(){ print_inorder(this);}

    void inorder_parentheses(ExpressionTree* root){
        if(!root)return;
        cout << "("; root->print_inorder(); cout << ")";
    }

    // It's not recursive
    void print_inorder_expression(){
        // inorder will print 5 * 2 + 3 which doesn't tell us if it's
        // (5*2)+3 or 5*(2+3) -> It's represented in memory but we need to surround it with (expression tree) 
        // The Question now, is how to not over parentheses it ((5*2)+(3))
        // Not just if it's operator we do (subtree) - It's when you have + as a child of * that is a child where the parent is higher in precedence of it
        if(left){
            if(left->right || left->left) cout << '(';
            left->print_inorder();
            if(left->right || left->left) cout << ')';
        }
        cout << data;
        if(right){
            if(right->right || right->left) cout << '(';
            right->print_inorder();
            if(right->right || right->left) cout << ')';
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
    cout << "Inorder: "; tree.print_inorder(); cout << "\n";
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
    tree.add({2,4}, {'L','L'});
    tree.add({2,5}, {'L','R'});
    tree.add({3,6}, {'R','L'});
    tree.add({3,7}, {'R','R'});

    // Level 4
    tree.add({2,4,8}, {'L','L','L'});
    tree.add({2,4,9}, {'L','L','R'});
    tree.add({2,5,10}, {'L','R','L'});
    tree.add({2,5,11}, {'L','R','R'});
    tree.add({3,6,12}, {'R','L','L'});
    tree.add({3,6,13}, {'R','L','R'});
    tree.add({3,7,14}, {'R','R','L'});
    tree.add({3,7,15}, {'R','R','R'});

    cout << "Is perfect: " << tree.is_perfect() << "\n";
    cout << "Is perfect (formula): " << tree.is_perfect_formula() << "\n";
    cout << "Left boundary: "; tree.traverse_left_boundary(); cout << "\n";
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
    tree.print_inorder(); cout << "\n";
}

// ExpressionTree Tests
void test_expression_tree() {
    cout << "\n[ExpressionTree Tests]\n";
    string postfix = "23+5*"; // (2+3)*5
    ExpressionTree et(postfix);
    cout << "Inorder: "; et.print_inorder(); cout << "\n";
    cout << "Inorder with parentheses: "; et.print_inorder_expression(); cout << "\n";
}

int main() {
    test_binary_tree_easy();
    test_binary_tree_mid();
    test_binary_tree_hard();
    test_expression_tree();
    return 0;
}

