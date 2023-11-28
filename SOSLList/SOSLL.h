#pragma one
#include <iostream>

template <class T>
struct Node
{
  Node(
      const T &val,
      Node<T> *n = nullptr,
      Node<T> *p = nullptr,
      Node<T> *a = nullptr,
      Node<T> *d = nullptr)
      : data(val), next(n), prev(p), asc(a), desc(d)
  {
  }
  void set_asc(Node<T> *a) { asc = a; }
  void set_desc(Node<T> *d) { desc = d; }

  Node<T> *next, *prev;
  Node<T> *asc, *desc;
  T data;
};

template <class T>
class SOSLL
{
public:
  SOSLL();                            // default ctor
  SOSLL(std::initializer_list<T> li); // initializer_SOSLL ctor O(n^2)
  SOSLL(const SOSLL<T> &);            // copy ctor O(n^2)
  SOSLL(SOSLL<T> &&);                 // move ctor O(1)
  ~SOSLL();                           // dtor O(n)

  // insert
  void insert_after(Node<T> *p, const T &val); // O(1)
  void insert_at(int pos, const T &val);       // O(n)

  // push / pop
  void push_front(const T &val); // O(1)
  void push_back(const T &val);  // O(1)
  void pop_front();              // O(1)
  void pop_back();               // O(1)

  // delete
  void delete_after(Node<T> *p); // O(1)
  void delete_at(int n);         // O(n)
  void remove(const T &val);     // O(n)

  // methods
  void print_reverse() const;    // O(n)
  bool empty() const;            // O(1)
  void clear();                  // O(n)
  T &front();                    // O(1)
  T &back();                     // O(1)
  Node<T> *search(const T &val); // O(n)

  // operators
  SOSLL<T> &operator=(const SOSLL<T> &); // copy assignment
  SOSLL<T> &operator=(SOSLL<T> &&);      // move assignment

  // getters
  Node<T> *head() const;
  Node<T> *tail() const;
  Node<T> *asc() const;
  Node<T> *desc() const;

  Node<T> *get_middle_node() const; // O(n / 2)
  int size() const;                 // O(1)

private:
  void copy(const SOSLL<T> &); // O(n)
  void put_in_sorted_order(Node<T> *node);
  void take_out_in_sorted_order(Node<T> *node);

private:
  Node<T> *_head = nullptr;
  Node<T> *_tail = nullptr;
  Node<T> *_asc = nullptr;
  Node<T> *_desc = nullptr;
  int _size = 0;
};

template <class T>
SOSLL<T>::SOSLL() {}

template <class T>
SOSLL<T>::SOSLL(std::initializer_list<T> li)
{
  _head = _tail = new Node<T>(*li.begin());
  put_in_sorted_order(_head);

  _size = li.size();
  Node<T> *curr = _head;

  for (auto it = li.begin() + 1; it != li.end(); it++)
  {
    Node<T> *node = new Node<T>(*it);
    curr->next = node;
    curr->next->prev = curr;
    curr = curr->next;
    put_in_sorted_order(node);
  }
  _tail = curr;
}

template <class T>
SOSLL<T>::SOSLL(const SOSLL &rhs)
{
  copy(rhs);
}

template <class T>
SOSLL<T>::SOSLL(SOSLL &&rhs)
{
  _head = rhs._head;
  _tail = rhs._tail;
  _size = rhs._size;
  _asc = rhs._asc;
  _desc = rhs._desc;
  rhs._head = nullptr;
  rhs._tail = nullptr;
  rhs._asc = nullptr;
  rhs._desc = nullptr;
  rhs._size = 0;
}

template <class T>
SOSLL<T>::~SOSLL()
{
  while (_head != nullptr)
  {
    Node<T> *tmp = _head;
    _head = _head->next;
    delete tmp;
  }
}

// insert
template <class T>
void SOSLL<T>::insert_after(Node<T> *p, const T &val)
{
  if (p && p->next)
  {
    Node<T> *tmp = new Node<T>(val, p->next, p);
    put_in_sorted_order(tmp);
    p->next->prev = tmp;
    p->next = tmp;
    _size++;
  }
}
template <class T>
void SOSLL<T>::insert_at(int pos, const T &val)
{
  if (pos == 0)
  {
    push_front(val);
    return;
  }
  else if (pos >= _size - 1)
  {
    push_back(val);
    return;
  }

  Node<T> *ptr = _head;
  while (--pos && ptr->next != nullptr)
  {
    ptr = ptr->next;
  }
  insert_after(ptr, val);
}

// push / pop
template <class T>
void SOSLL<T>::push_front(const T &val)
{
  Node<T> *node = new Node<T>(val, _head, nullptr);
  if (_head == nullptr)
  {
    _tail = _head = node;
  }
  else
  {
    _head->prev = node;
    _head = node;
  }
  put_in_sorted_order(node);
  _size++;
}

template <class T>
void SOSLL<T>::push_back(const T &val)
{
  Node<T> *node = new Node<T>(val, nullptr, _tail);
  if (_head == nullptr)
  {
    _tail = _head = node;
  }
  else
  {
    _tail->next = node;
    _tail = node;
  }
  put_in_sorted_order(node);
  _size++;
}

template <class T>
void SOSLL<T>::pop_front()
{
  if (_head)
  {
    Node<T> *tmp = _head;
    _head = _head->next;
    if (_head)
    {
      _head->prev = nullptr;
    }
    else
    {
      _tail = _head = nullptr;
    }
    _size--;
    take_out_in_sorted_order(tmp);
    delete tmp;
  }
}

template <class T>
void SOSLL<T>::pop_back()
{
  if (_tail)
  {
    Node<T> *tmp = _tail;
    _tail = _tail->prev;
    if (_tail)
    {
      _tail->next = nullptr;
    }
    else
    {
      _tail = _head = nullptr;
    }
    _size--;
    take_out_in_sorted_order(tmp);
    delete tmp;
  }
}

// delete
template <class T>
void SOSLL<T>::delete_after(Node<T> *p)
{
  if (p)
  {
    Node<T> *tmp = p->next;
    if (tmp)
    {
      take_out_in_sorted_order(tmp);
      p->next = p->next->next;
      tmp->next->prev = p;
      _size--;
      delete tmp;
    }
  }
}

template <class T>
void SOSLL<T>::delete_at(int pos)
{
  if (pos == 0)
  {
    pop_front();
    return;
  }
  else if (pos >= _size - 1)
  {
    pop_back();
    return;
  }

  Node<T> *ptr = _head;
  while (--pos && ptr->next != nullptr)
  {
    ptr = ptr->next;
  }
  delete_after(ptr);
}

template <class T>
void SOSLL<T>::remove(const T &val)
{
  if (_head)
  {
    if (_head->data == val)
    {
      pop_front();
      return;
    }
    else if (_tail->data == val)
    {
      pop_back();
      return;
    }

    Node<T> *ptr = _head;
    while (ptr->next != nullptr && ptr->next->data != val)
    {
      ptr = ptr->next;
    }
    delete_after(ptr);
  }
}

// methods
template <class T>
void SOSLL<T>::print_reverse() const
{
  Node<T> *ptr = _tail;
  while (ptr)
  {
    std::cout << ptr->data << " ";
    ptr = ptr->prev;
  }
  std::cout << "\n";
}

template <class T>
bool SOSLL<T>::empty() const
{
  return _size == 0;
}

template <class T>
void SOSLL<T>::clear()
{
  while (_head != nullptr)
  {
    Node<T> *tmp = _head;
    _head = _head->next;
    delete tmp;
  }
  _tail = _head = nullptr;
  _asc = _desc = nullptr;
}

template <class T>
T &SOSLL<T>::front()
{
  return _head->data;
}
template <class T>
T &SOSLL<T>::back()
{
  return _tail->data;
}

template <class T>
Node<T> *SOSLL<T>::search(const T &val)
{
  Node<T> *ptr = _head;
  while (ptr != nullptr)
  {
    if (ptr->data == val)
    {
      return ptr;
    }
    ptr = ptr->next;
  }
  return nullptr;
}

// operators
template <class T>
SOSLL<T> &SOSLL<T>::operator=(const SOSLL<T> &rhs)
{
  if (this != &rhs)
  {
    clear();
    copy(rhs);
  }

  return *this;
}

template <class T>
SOSLL<T> &SOSLL<T>::operator=(SOSLL<T> &&rhs)
{
  if (this != &rhs)
  {
    _head = rhs._head;
    _tail = rhs._tail;
    _size = rhs._size;
    _asc = rhs._asc;
    _desc = rhs._desc;
    rhs._head = nullptr;
    rhs._tail = nullptr;
    rhs._asc = nullptr;
    rhs._desc = nullptr;
    rhs._size = 0;
  }
  return *this;
}

template <class T>
Node<T> *SOSLL<T>::head() const
{
  return _head;
}

template <class T>
Node<T> *SOSLL<T>::tail() const
{
  return _tail;
}

template <class T>
Node<T> *SOSLL<T>::asc() const
{
  return _asc;
}
template <class T>
Node<T> *SOSLL<T>::desc() const
{
  return _desc;
}

template <class T>
Node<T> *SOSLL<T>::get_middle_node() const
{
  Node<T> *fast = _head;
  Node<T> *slow = _head;
  while (fast && fast->next)
  {
    fast = fast->next->next;
    slow = slow->next;
  }
  return slow;
}

template <class T>
int SOSLL<T>::size() const
{
  return _size;
}

template <class T>
void SOSLL<T>::copy(const SOSLL<T> &rhs)
{
  Node<T> *curr = rhs._head;
  if (!curr)
  {
    return;
  }

  Node<T> *ptr = nullptr;
  if (_head == nullptr)
  {
    ptr = new Node<T>(curr->data);
    put_in_sorted_order(ptr);
    _head = _tail = ptr;
    curr = curr->next;
  }

  while (curr != nullptr)
  {
    ptr->next = new Node<T>(curr->data);
    put_in_sorted_order(ptr->next);
    ptr->next->prev = ptr;
    ptr = ptr->next;
    curr = curr->next;
  }
  _size = rhs._size;
  _tail = ptr;
}

template <class T>
void SOSLL<T>::put_in_sorted_order(Node<T> *node)
{
  if (_asc == nullptr)
  {
    _asc = _desc = node;
  }
  else if (node->data < _desc->data)
  {
    node->set_asc(_desc);
    _desc->desc = node;
    _desc = node;
  }
  else if (node->data > _asc->data)
  {
    node->set_desc(_asc);
    _asc->asc = node;
    _asc = node;
  }
  else
  {
    Node<T> *p = _desc;
    while (p && node->data > p->data)
    {
      p = p->asc;
    }
    node->set_asc(p);
    node->set_desc(p->desc);

    p->desc ? p->desc->asc = node : _desc = node;
    p->desc = node;
  }
}

template <class T>
void SOSLL<T>::take_out_in_sorted_order(Node<T> *node)
{
  if (!_head)
  {
    _asc = _desc = nullptr;
    return;
  }
  if (node == _asc)
  {
    _asc = node->desc;
    _asc->asc = nullptr;
  }
  else if (node == _desc)
  {
    _desc = node->asc;
    _desc->desc = nullptr;
  }
  else
  {
    node->desc->asc = node->asc;
    node->asc->desc = node->desc;
  }
}
