#include<iostream>
#include "List.h"

int main(){
    List<int> l1;
    l1.insert(2);
    l1.insert(3);
    l1.insert(8);
    for (auto &&element : l1)
    {
        std::cout << element << " ";
    }
    return 0;
}

