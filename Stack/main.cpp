#include "Stack.h"
#include <iostream>

int main()
{
  Stack<int> s = {1, 2, 3, 4, 5};
  s.push(6);
  s.pop();

  while (!s.empty())
  {
    std::cout << s.top() << " ";
    s.pop();
  }
}