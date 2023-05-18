#include "MyVector.h"
#include <iostream>

int main()
{

  MyVector<int> v{4, 7, 8, 9, 17};
  MyVector<int> v2{1, 2, 3};

  MyVector<int> v3(v + v2); // move ctr call

  // iterator
  for (auto i = v3.begin(); i < v3.end(); ++i)
  {
    std::cout << *(i) << " ";
  }
}