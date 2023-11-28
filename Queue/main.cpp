#include <iostream>
#include "Queue.h"

int main()
{
    Queue<int> q(4);

    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.pop();
    q.push(88);

    Queue<int> q2(44);
    q2 = q;

    std::cout << "size " << q2.size() << "\n";
    while (!q2.empty())
    {
        std::cout << q2.top() << " ";
        q2.pop();
    }
}