#include "List.h"
#include <iostream>

int main() {
  try {
    int n = 4;
    List<int> l1;
    int a[n];
    for (int i = 0; i < n; i++) {
      std::cin >> a[i];
      l1.InsertAt(i, a[i]);
    }

    Node<int> *p = l1.GetFirst();
    for (int i = 0; i < l1.GetLength(); i++) {
      std::cout << l1.GetData(p) << ' ';
      p = p->link;
    }
    std::cout <<"\n"<< l1.GetData(p) <<" ";

  } catch (char *a) {
    std::cout << a;
  }
}