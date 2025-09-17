#include <bits/stdc++.h>
using namespace std;

// Note: That the < or <= is changeable Here like less<> or greater<> to say if
// you want min or max heap
class BinaryHeap {
 private:
  vector<int> array{};

 private:
  // Useful
  int right(int idx) {
    int right = 2 * idx + 2;
    return (right >= array.size()) ? -1 : right;
  }
  int left(int idx) {
    int left = 2 * idx + 1;
    return (left >= array.size()) ? -1 : left;
  }
  // No parent for 0
  int parent(int idx) {
    if (idx == 0) return -1;
    int parent = (idx - 1) / 2;
    return (parent < 0) ? -1 : parent;
  }
  // I like the recursive way
  void heapify_up(int idx) {
    int par = parent(idx);
    if (idx == 0 || array[par] <= array[idx]) return;  // It's min heap
    swap(array[idx], array[par]);
    heapify_up(par);
  }
  void heapify_down(int idx) {
    int r = right(idx);
    int l = left(idx);
    int to_swap = idx;
    if (l != -1 && array[l] < array[to_swap]) to_swap = l;
    if (r != -1 && array[r] < array[to_swap]) to_swap = r;
    if (to_swap == idx) return;
    swap(array[idx], array[to_swap]);
    heapify_down(to_swap);
  }
  bool is_heap(int pos = 0) {
    if (pos == -1) return true;
    if (array[pos] > array[left(pos)] || array[pos] > array[right(pos)])
      return false;
    return is_heap(left(pos)) && right(pos);
  }

 public:
  BinaryHeap() : array{} {};

  void push(int value) {
    array.push_back(value);
    heapify_up((int)array.size() - 1);
  }
  void pop() {
    if (array.empty()) return;
    swap(array.front(), array.back());
    array.pop_back();
    heapify_down(0);
  }
  int top() {
    if (array.empty()) return -1;
    return array.front();
  }
  // We are can take it and insert one by one -> O(n log n)

  // I didn't explain it that well

  // Or, think of it as as tree and heapify down one by one from end to start ->
  // O(n) Floyd’s build-heap Optimal, It takes subtrees from smallest to the
  // biggest and make sure it's a heap Starting at leaf nodes and telling it to
  // bubble down is gonna move it anywhere if you sure that both subtrees you
  // heapifed are heap, add a root it both of it, (if root is veryy big value
  // like 1M let's say) Then root would have to go all the way to the end which
  // is O(log n) time but remember (n) is the tree that isn't full yet, we have
  // a small subtree It's analysis aren't straight forward but get the sense of
  // it

  // So, why not one by one heapify up (the opposite of floyd) -> It's like
  // inserting it one by one

  // Heapify-up: every node starts at the bottom, climbs toward the root → lots
  // of long climbs. Heapify-down: every node starts at the top of its own
  // subtree, so most can only go down 1–2 steps → much less work overall.

  // Finally, in Heapify-down the added node to both subtrees will do the work
  // that pushs the smaller element to the surface one step Just Think for
  // yourself and find out

  BinaryHeap(vector<int>& to_heapify) : array(to_heapify) {  // Deep Copy
    for (int i = to_heapify.size() - 1; i >= 0; i--) {
      // Can skip leafnodes - half of it is leaf-nodes
      heapify_down(i);
    }
  }

  // Note: Search o(n)
  // Note: Swapping right with left subtrees (if null) makes it non complete
  // binary tree Printing in sorted order -> O(n log n) , BST -> O(n)

  ///////////////////////
  // Easy - Mid
  ///////////////////////

  // MaxHeap -> No Need same exact thing

  void print_less_than(int value, int pos = 0) {
    if (pos != -1 && array[pos] < value) {
      cout << array[pos];
      print_less_than(value, left(pos));
      print_less_than(value, right(pos));
    }
    return;
  }

  // Done by taking the data members as copy and returning them back
  // Umm, Okay is this something to do always?

  bool is_heap(vector<int>& vec) {
    // Uses is_heap
    vector<int> temp = move(array);
    array = move(vec);

    bool result = is_heap();

    array = move(temp);
    return result;
  }
};

// Interesting
class MaxHeap {
 private:
  BinaryHeap min_heap;

 public:
  MaxHeap() : min_heap{} {}

  void push(int value) {
    min_heap.push(-value);  // HERE
  }
  int top() { return -min_heap.top(); }
  void pop() { min_heap.pop(); }
};

////////////////////////
// STL PQ - Mid - Hard
////////////////////////

// Just skip for now - Very basic

// Note: It uses less<int> by default -> MaxHeap - less(5,7) -> true 5 < 7 -> So
// 7, on top

int main() { return 0; }