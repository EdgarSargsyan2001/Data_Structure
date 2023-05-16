#include "Tree.h"
#include <iostream>

int main() {
  BSTree t;
  t.insert(15);
  t.insert(10);
  t.insert(21);
  t.insert(30);
  t.insert(12);
  t.insert(8);
  t.insert(18);
  t.insert(19);
  t.insert(16);
  t.insert(20);
  t.print2D(t.getRoot());

  // std::cout << t.calcHeight(t.getRoot());
  // t.remove(t.getRoot(), 21);
  std::cout << "\n-------------------------\n";
  t.print2D(t.getRoot());
}