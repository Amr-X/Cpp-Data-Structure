#include <bits/stdc++.h>
using namespace std;

void right_rotation(vector<int>& vec,int steps = 1){
    if(vec.empty()) return;
    // It's 0,1,2,3,..,size()-1 only 
    steps = steps % vec.size();

    // Could do while(steps--){//Code Here}

    vector<int> last;
    last.reserve(steps);
    
    // Save Last ones
    for (int i = steps; i < (int)vec.size(); i++) {
        last.push_back(vec[i]);
    }
    // Do it here for the rest
    for (int i = (int)vec.size() - (steps) - 1; i >= 0; i--)
    {
        vec[i+steps] = vec[i];
    }
    // Push last again to be at the start
    for (int i = 0; i < (int)last.size(); i++) {
        vec[i] = last[i]; 
    }
}

// Left rotation is same
// right rotation with one step will work with this 
// Delete Position Done at vector implementation
// Improved Search -> is easy Consider the case for not swapping if found at index 0 - Other way is to what you find swap it with the first index at 0

int main() {

    vector<int> v{1,2,3,4,5,6};
    right_rotation(v,3);
    for (auto &item : v)
    {
        cout << item << " ";
    }
        

    return 0;
}