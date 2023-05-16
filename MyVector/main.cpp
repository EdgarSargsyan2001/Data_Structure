#include "MyVector.h"
#include <iostream>

int main() {

  MyVector<int> v{4, 7, 8, 9, 7};
  MyVector<int> v2{1, 2, 3};
  
  MyVector<int> v3(v + v2);  // move ctr call
  v3.print();
}