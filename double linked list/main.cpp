#include "list.h"
#include <iostream>

int main() {
  List<int> l1;
  l1.Push_front(2);
  l1.Push_front(1);
  l1.Push_back(3);
  l1.Push_back(4);
  l1.Push_back(5);

  l1.Insert_after(2, 11);
  l1.Insert_after(11, 22);
  l1.Print();

  //======== delete ================
  std::cout << "============== delete =============\n\n";

  l1.Delete(5);
  l1.Delete(11);

  l1.Print();
}