#include "list.h"
#include <iostream>

int main()
{
  List<int> l2 = {10, 18, 55,102,150};
  List<int> l1 = {15, 50, 100};

  l1.marge_to_sorted_list(l2.head());
  l1.print_reverse();
  // int arr[2] = {11, 22};
  // l1.insert(0, arr, 2);
  // l1.insert(6, {77, 88, 99});
  // l1.push_back(6);
  // l1.push_back(8);
  // l1.push_back(9);
  // l1.pop_front();

  // l1.resize(8);
  // l1.pop_back();
  // l1.pop_back();

  // l1.delete_at(1);
  // l1.remove(4);

  // l1.insert_at(6, 88);


  Node<int> *ptr = l1.head();
  while (ptr)
  {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << "\n";
  std::cout << "size " << l1.size() << "\n";

  std::cout << "\nok ";
}