#include <iostream>

template <class T> struct Node {
  T info;
  Node<T> *link;
};

template <class T> class List {
public:
  List();
  List(const List &);
  ~List();
  bool IsEmpty() const;
  int GetLength() const;
  Node<T> *GetFirst() const;
  void InsertAfter(Node<T> *p, T item);
  void InsertAt(int n, T item);
  void DeleteAfter(Node<T> *p);
  void DeleteAt(int n);
  T &GetData(Node<T> *p);

private:
  Node<T> *first;
  int size;
};

template <class T> List<T>::List() : size(0), first(nullptr) {}

template <class T> List<T>::List(const List &aList) {
  Node<T> *p = new Node<T>;
  Node<T> *p1 = aList.first;
  GetData(p) = aList.GetData(p1);
  first = p;
  first->link = nullptr;
  for (int i = 0; i < aList.GetLength() - 1; i++) {
    p1 = p1->link;
    InsertAfter(p, aList.GetData(p1));
    p = p->link;
  }
  size = aList.size;
}

template <class T> List<T>::~List() {
  if (first) {
    while (size) {
      size--;
      // std::cout << "\n kk " << first->link << " ";
      DeleteAfter(first);
    }
    delete first;
    first = 0;
  }
  size = 0;
}

template <class T> bool List<T>::IsEmpty() const { return size == 0; }

template <class T> int List<T>::GetLength() const { return size; }

template <class T> Node<T> *List<T>::GetFirst() const { return first; }

template <class T> void List<T>::InsertAfter(Node<T> *p, T item) {
  Node<T> *q = new Node<T>;
  // std::cout << " . " << p << " . ";
  q->info = item;
  q->link = p->link;
  p->link = q;
  size++;
}

template <class T> void List<T>::InsertAt(int n, T item) {

  if (n < 0 || n > GetLength()) {
    throw "position is out of range";
  }
  if (n == 0) {
    Node<T> *q = new Node<T>;
    q->info = item;
    q->link = q;
    first = q;
    size++;
    return;
  }
  Node<T> *p = first;
  for (int i = 0; i < n - 1; i++) {
    p = p->link;
  }
  InsertAfter(p, item);
}

template <class T> void List<T>::DeleteAfter(Node<T> *p) {
  if (IsEmpty()) {
    throw "List is empty";
  }
  if (p->link == nullptr) {
    throw "No element to delete";
  }

  Node<T> *q = p->link;
  p->link = q->link;
  delete q;
  size--;
  return;
}

template <class T> void List<T>::DeleteAt(int n) {

  if (n < 0 || n > GetLength()) {
    throw "position is out of range";
  }
  if (n == 0 && GetLength() != 0) {
    Node<T> *q = first;
    first = first->link;
    delete q;
    size--;
    return;
  }
  Node<T> *p = first;
  for (int i = 0; i < n - 1; i++) {
    p = p->link;
    DeleteAfter(p);
  }
}

template <class T> T &List<T>::GetData(Node<T> *p) { return p->info; }
