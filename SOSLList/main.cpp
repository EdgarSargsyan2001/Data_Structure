#include "SOSLL.h"
#include <iostream>

int main()
{
  SOSLL<int> l1 = {3, 0, 99};

  Node<int> *ptr = l1.head();
  while (ptr)
  {
    std::cout << ptr->data << " ";
    ptr = ptr->next;
  }
  std::cout << "\n->:  ";
  Node<int> *p = l1.desc();
  while (p)
  {
    std::cout << p->data << " ";
    p = p->asc;
  }
  std::cout << "\n<-:  ";
  p = l1.asc();
  while (p)
  {
    std::cout << p->data << " ";
    p = p->desc;
  }
  std::cout << "\n";
  std::cout << "size " << l1.size() << "\n";
  std::cout << "ok ";
}