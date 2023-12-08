#include <iostream>
#include "Priority_queue.h"

int main()
{
    Priority_queue<int> q = {45, 31, 14, 13, 20, 7, 11, 12, 7};

    // q.increase_key(0);
    // q.pop();
    // q.pop();
    // q.pop();
    // q.pop();

    while (!q.empty())
    {
        std::cout << q.top() << " ";
        q.pop();
    }
}