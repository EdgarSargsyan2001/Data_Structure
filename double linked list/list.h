#pragma one
#include <iostream>

template <class T> class Node {
public:
  Node(const T &_val) : val(_val), next(nullptr), prev(nullptr) {}

  Node<T> *next, *prev;
  T val;
};

template <class T> class List {
public:
  List();
  ~List();
  void Push_front(const Node<T> &);
  void Push_back(const Node<T> &);
  void Insert_after(Node<T> *, const Node<T> &);
  void Insert_after(const T &val, const Node<T> &);
  void Delete(Node<T> *);
  void Delete(const T &);
  void Print() const;
  Node<T> *get_val_Ptr(const T &val) const;
  bool isEmpty() const { return size == 0; }
  int get_size() const { return size; }
  // Node<T> *getHead() const { return head; }
  // Node<T> *getTail() const { return tail; }

private:
  Node<T> *head, *tail;
  int size;
};

template <class T> List<T>::List() : size(0), head(nullptr), tail(nullptr) {}

template <class T> List<T>::~List() {
  while (head != nullptr) {
    Node<T> *tmp = head;
    head = head->next;
    delete tmp;
  }
}

template <class T> void List<T>::Push_front(const Node<T> &val) {
  Node<T> *tmp = new Node<T>(val);

  tmp->next = head;

  if (head == nullptr)
    head = tail = tmp;
  else {
    head->prev = tmp;
  }

  head = tmp;
  size++;
}

template <class T> void List<T>::Push_back(const Node<T> &val) {
  Node<T> *tmp = new Node<T>(val);

  tmp->prev = tail;

  if (tail == nullptr)
    tail = head = tmp;
  else {
    tail->next = tmp;
  }

  tail = tmp;
  size++;
}

template <class T> void List<T>::Insert_after(Node<T> *l, const Node<T> &val) {
  if (l == nullptr)
    return;

  Node<T> *tmp = new Node<T>(val), *nxt = l->next;

  l->next = tmp;
  tmp->prev = l;
  tmp->next = nxt;

  if (nxt != nullptr) {
    nxt->prev = tmp;
  } else {
    tail = tmp;
  }
  size++;
}

template <class T>
void List<T>::Insert_after(const T &pos, const Node<T> &val) {
  Node<T> *l = head;
  while (l != nullptr) {
    if (l->val == pos) {
      break;
    }
    l = l->next;
  }
  Insert_after(l, val);
}
template <class T> void List<T>::Delete(Node<T> *node) {
  if (node == nullptr)
    return;

  Node<T> *tmp = node;

  if (--size == 0)
    head = tail = nullptr;
  else {
    if (node == head)
      head = head->next, head->prev = nullptr;
    else if (node == tail)
      tail = tail->prev, tail->next = nullptr;
    else {
      node->prev->next = node->next;
      node->next->prev = node->prev;
    }
  }

  delete tmp;
}

template <class T> void List<T>::Delete(const T &val) {

  Node<T> *l = head;
  while (l != nullptr) {
    if (l->val == val) {
      break;
    }
    l = l->next;
  }
  Delete(l);
}

template <class T> Node<T>* List<T>::get_val_Ptr(const T& val) const {
  Node<T> *l = head;
    while(l != nullptr){
      if(l->val == val){
        break;
      }
      l = l->next;
    }
    return l;
}

template <class T> void List<T>::Print() const {
  Node<T> *l = head;
  std::cout<<"head-> "<<head<<"\n\n";
  while (l != nullptr) {
    std::cout << l->val << " " << l << " == next-> " << l->next << "  prev-> "
              << l->prev << "\n";

    l = l->next;
  }
  std::cout << "\n";
  std::cout<<"tail-> "<<tail<<"\n\n";
}