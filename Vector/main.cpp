#include "Vector.h"
#include <iostream>

int main()
{

  Vector<int> v{4, 7, 8, 9, 17};
  Vector<int> v2{1, 2, 3};

  Vector<int> v3(v + v2); // move ctr call
  // v3.insert(10, 2, 0);
  std::cout << '\n'
            << "size " << v3.size() << '\n'
            << "capacity " << v3.capacity() << '\n';

  // std::cout << v3.at(3) << '\n';
  
  // iterator
  for (int el : v3)
  {
    std::cout << el << " ";
  }
}