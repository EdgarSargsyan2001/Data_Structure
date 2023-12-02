#include <iostream>
#include "Unordered_set.h"

int main()
{
    Unordered_set<int> set = {1, 2, 4, 77, 99, 11, 22, 33, 44, 999, 14, 15, 16, 171};

    // std::cout << set.search(100);
    set.print();
    std::cout << "\nok";
}