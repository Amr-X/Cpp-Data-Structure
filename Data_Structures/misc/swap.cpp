#include<vector> // Heavy Object
#include<string>
using namespace std;

// r-value meaning: Object That is About To Be Destroyed Anyway - It's a Semantic Meaning To Move And Object

void old_swap(vector<string>& vec1,vector<string> vec2){
    // It's Right - But Why Copy When You Can Move
    vector<string> temp = vec1;
    vec1 = vec2;
    vec2 = temp;
}
void modern_swap(vector<string>& vec1,vector<string> vec2){
    // Or Change Type To r-value reference && - What Moves Do
    vector<string> temp = move(vec1);
    vec1 = move(vec2);
    vec2 = move(temp);
}

vector<int> returnrvalue(){return {1,2};} // Move Constructor   

vector<int> returnlvalue() {vector<int> v; return v;} // Copy Constructor

int main(){
    vector<string> vec1;
    vector<string> vec2;
    // Put Big Data
    // Swap
}