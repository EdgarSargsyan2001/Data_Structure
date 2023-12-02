#include "Vector.h"
#include <iostream>
#include <vector>

int main()
{

  Vector<int> v{4, 7, 8, 9, 17};
  Vector<int> v2{1, 2, 3};

  Vector<int> v3(v + v2); // move ctr call
  // v3.insert(10, 2, 0);
  std::cout << '\n'
            << "size " << v3.size() << '\n'
            << "capacity " << v3.capacity() << '\n';

  // *v3.begin() = 444;
  // iterator
  for (int el : v3)
  {
    std::cout << el << " ";
  }

  // for (Vector<int>::const_iterator it = v3.cbegin(); it < v3.cend(); it++)
  // {
  //   std::cout << it[0] << " ";
  // }
}