#include "Forward_list.h"
#include <iostream>
#include <forward_list>

Node<int> *mergeTwoLists(Node<int> *h1, Node<int> *h2)
{
  if (!h1)
    return h2;

  if (!h2)
    return h1;

  if (h1->data < h2->data)
  {
    h1->next = mergeTwoLists(h1->next, h2);
    return h1;
  }
  else
  {
    h2->next = mergeTwoLists(h1, h2->next);
    return h2;
  }
}

int main()
{
  Forward_list<int> l2{3, 8, 16, 102, 1000};
  Forward_list<int> l1{10, 19, 20, 100};

  for (int el : l1)
  {
    std::cout << el << " ";
  }

  // std::forward_list<int> l = {1, 2, 3, 4};

  // const std::forward_list<int>::const_iterator p = l.cbegin()++;
  // p++;

  // l1.reverse_rec(l1.head());

  // l1.marge_to_sorted_list(l2.head());
  // mergeTwoLists(l1.head(), l2.head());

  // l1.resize(10);
  // l1.insert(0, {44, 55, 66});

  // int arr[] = {99, 99, 99};
  // int N = sizeof(arr) / sizeof(arr[0]);
  // l1.insert(0, arr, N);

  // std::cout << std::endl;

  // Forward_list<int> l2(l1);

  // l1.insert(8, l2);
  // l1.push_front(44);
  // l1.push_front(77);

  // l1.delete_at();
  // l1.remove(77);
  // l2.print();
  // l1.reverse();
  // std::cout << l1.has_cyrcl() << '\n';

  //     Node<int> *ptr = l1.head();
  // while (ptr)
  // {
  //   std::cout << ptr->data << " ";
  //   ptr = ptr->next;
  // }

  std::cout
      << "\nok\n";
}