#include <iostream>
#include "Unordered_map.h"

int main()
{
    Unordered_map<int, std::string> unordered_map = {
        {3, "RED"},
        {1, "GREEN"},
        {4, "GREEN"},
    };

    // unordered_map.clear();
    unordered_map.print();
    std::cout << "\nok";
}