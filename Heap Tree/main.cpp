#include <iostream>
#include "Heap.h"

int main()
{
    Heap<int> h = {10, 50, 90, 11, 1, 0, 999, 22, 33, 44};

    // h.pop();
    // h.pop();
    // std::cout << h.top() << " ";
    // std::cout << h.top() << " ";
    while (!h.empty())
    {
        std::cout << h.top() << " ";
        h.pop();
    }

    std::cout << "\nok\n";
}