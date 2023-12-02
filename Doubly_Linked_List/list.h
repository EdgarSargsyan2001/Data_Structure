#ifndef LIST_H
#define LIST_H
#include <iostream>

template <typename T>
struct Node
{
  Node(const T &val, Node<T> *n = nullptr, Node<T> *p = nullptr)
      : data(val), next(n), prev(p) {}

  Node<T> *next, *prev;
  T data;
};

template <typename T>
class List
{
public:
  class iterator;
  class const_iterator;

public:
  List();                            // default ctor
  List(std::initializer_list<T> li); // initializer_list ctor
  List(const List<T> &);             // copy ctor
  List(List<T> &&);                  // move ctor
  ~List();                           // dtor

  // insert
  void insert_after(Node<T> *p, const T &val);       // O(1)
  void insert_at(int pos, const T &val);             // O(n)
  void insert(int pos, std::initializer_list<T> li); // O(n + m)
  void insert(int pos, const T *arr, int N);         // O(n + m)
  void insert(int pos, const List &li);              // O(n + m)

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
  void print_reverse() const;               // O(n)
  bool empty() const;                       // O(1)
  void clear();                             // O(n)
  T &front();                               // O(1)
  T &back();                                // O(1)
  void resize(int count, const T &val = 0); // O(n^2)
  iterator search(const T &val);            // O(n)
  bool has_cyrcl();                         // O(n)
  void marge_to_sorted_list(Node<T> *);     // O(n + m)

  // operators
  List<T> &operator=(const List<T> &); // copy assignment
  List<T> &operator=(List<T> &&);      // move assignment

  // getters
  iterator begin();                 // O(1)
  iterator end();                   // O(1)
  const_iterator cbegin();          // O(1)
  const_iterator cend();            // O(1)
  Node<T> *head() const;            // O(1)
  Node<T> *tail() const;            // O(1)
  iterator get_middle_node() const; // O(n / 2)
  int size() const;                 // O(1)

private:
  void copy(const List<T> &);                         // O(n)
  void insert(int pos, Node<T> *start, Node<T> *end); // O(m)

private:
  Node<T> *_head = nullptr;
  Node<T> *_tail = nullptr;
  int _size = 0;

public:
  class iterator
  {
  public:
    iterator() = default; // default ctor
    iterator(Node<T> *);  // ctor

    // operators
    T &operator*();
    T *operator->();
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);

    bool operator!=(const iterator &other) const;
    bool operator==(const iterator &other) const;

  private:
    Node<T> *_ptr = nullptr;
  };

  class const_iterator
  {
  public:
    const_iterator() = default;
    const_iterator(Node<T> *ptr);

    // operators
    const T &operator*() const;
    const T *operator->() const;
    const_iterator &operator++();
    const_iterator operator++(int);
    const_iterator &operator--();
    const_iterator operator--(int);

    bool operator!=(const const_iterator &other) const;
    bool operator==(const const_iterator &other) const;

  private:
    Node<T> *_ptr = nullptr;
  };
};

template <typename T>
List<T>::List() {}

template <typename T>
List<T>::List(std::initializer_list<T> li)
{
  _head = _tail = new Node<T>(*li.begin());
  _size = li.size();
  Node<T> *curr = _head;

  for (auto it = li.begin() + 1; it != li.end(); it++)
  {
    curr->next = new Node<T>(*it);
    curr->next->prev = curr;
    curr = curr->next;
  }
  _tail = curr;
}

template <typename T>
List<T>::List(const List &rhs)
{
  copy(rhs);
}

template <typename T>
List<T>::List(List &&rhs)
{
  _head = rhs._head;
  _tail = rhs._tail;
  _size = rhs._size;
  rhs._head = nullptr;
  rhs._tail = nullptr;
  rhs._size = 0;
}

template <typename T>
List<T>::~List()
{
  while (_head != nullptr)
  {
    Node<T> *tmp = _head;
    _head = _head->next;
    delete tmp;
  }
}

// insert
template <typename T>
void List<T>::insert_after(Node<T> *p, const T &val)
{
  if (p && p->next)
  {
    Node<T> *tmp = new Node<T>(val, p->next, p);
    p->next->prev = tmp;
    p->next = tmp;
    _size++;
  }
}
template <typename T>
void List<T>::insert_at(int pos, const T &val)
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

template <typename T>
void List<T>::insert(int pos, std::initializer_list<T> li)
{
  if (li.size() > 0)
  {
    Node<T> *start = new Node<T>(*li.begin());
    Node<T> *end = start;

    for (auto it = li.begin() + 1; it != li.end(); it++)
    {
      end->next = new Node<T>(*it);
      end->next->prev = end;
      end = end->next;
    }

    insert(pos, start, end);
    _size += li.size();
  }
}

template <typename T>
void List<T>::insert(int pos, const T *arr, int N)
{
  if (N > 0)
  {
    Node<T> *start = new Node<T>(arr[0]);
    Node<T> *end = start;

    for (int i = 1; i < N; ++i)
    {
      end->next = new Node<T>(arr[i]);
      end->next->prev = end;
      end = end->next;
    }

    insert(pos, start, end);
    _size += N;
  }
}

template <typename T>
void List<T>::insert(int pos, const List<T> &li)
{
  if (li._head != nullptr)
  {
    Node<T> *start = new Node<T>(li._head->data);
    Node<T> *end = start;

    Node<T> *h = li.head()->next;
    while (h != nullptr)
    {
      end->next = new Node<T>(h->data);
      end->next->prev = end;
      end = end->next;
      h = h->next;
    }
    insert(pos, start, end);
    _size += li._size;
  }
}

// push / pop
template <typename T>
void List<T>::push_front(const T &val)
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
  _size++;
}

template <typename T>
void List<T>::push_back(const T &val)
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
  _size++;
}

template <typename T>
void List<T>::pop_front()
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
    delete tmp;
  }
}

template <typename T>
void List<T>::pop_back()
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
    delete tmp;
  }
}

// delete
template <typename T>
void List<T>::delete_after(Node<T> *p)
{
  if (p)
  {
    Node<T> *tmp = p->next;
    if (tmp)
    {
      p->next = p->next->next;
      tmp->next->prev = p;
      _size--;
      delete tmp;
    }
  }
}

template <typename T>
void List<T>::delete_at(int pos)
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

template <typename T>
void List<T>::remove(const T &val)
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
template <typename T>
void List<T>::print_reverse() const
{
  Node<T> *ptr = _tail;
  while (ptr)
  {
    std::cout << ptr->data << " ";
    ptr = ptr->prev;
  }
  std::cout << "\n";
}

template <typename T>
bool List<T>::empty() const
{
  return _size == 0;
}

template <typename T>
void List<T>::clear()
{
  while (_head != nullptr)
  {
    Node<T> *tmp = _head;
    _head = _head->next;
    delete tmp;
  }
  _head = nullptr;
}

template <typename T>
T &List<T>::front()
{
  return _head->data;
}
template <typename T>
T &List<T>::back()
{
  return _tail->data;
}

template <typename T>
void List<T>::resize(int count, const T &val)
{
  int interval = count - _size;
  if (interval > 0)
  {

    Node<T> *first = new Node<T>(val);
    Node<T> *curr = first;
    for (int i = 1; i < interval; ++i)
    {
      curr->next = new Node<T>(val);
      curr->next->prev = curr;
      curr = curr->next;
    }

    _tail->next = first;
    first->prev = _tail;
    _tail = curr;
  }
  else
  {
    while (interval++)
    {
      delete_at(count);
    }
  }
}
template <typename T>
typename List<T>::iterator List<T>::search(const T &val)
{
  Node<T> *ptr = _head;
  while (ptr != nullptr)
  {
    if (ptr->data == val)
    {
      return iterator{ptr};
    }
    ptr = ptr->next;
  }
  return end();
}

template <typename T>
bool List<T>::has_cyrcl()
{
  if (_head == nullptr)
  {
    return false;
  }
  Node<T> *slow = _head;
  Node<T> *fast = _head->next;
  while (fast && fast->next)
  {
    if (fast == slow)
    {
      return true;
    }
    slow = slow->next;
    fast = (fast->next)->next;
  }
  return false;
}

template <typename T>
void List<T>::marge_to_sorted_list(Node<T> *h2)
{
  if (_head)
  {
    Node<T> *ptr = _head;
    while (h2 && ptr->data >= h2->data)
    {
      Node<T> *tmp = ptr->prev;
      Node<T> *node = new Node<T>(h2->data, ptr, tmp);
      ptr->prev = node;

      if (tmp)
      {
        tmp->next = ptr->prev;
      }
      else
      {
        _head = node;
      }
      _size++;
      h2 = h2->next;
    }

    while (ptr && ptr->next && h2)
    {
      T val = h2->data;
      if (ptr->data < val && ptr->next->data > val)
      {
        insert_after(ptr, val);
        h2 = h2->next;
      }
      ptr = ptr->next;
    }
    while (h2)
    {
      push_back(h2->data);
      h2 = h2->next;
    }
  }
}

// operators
template <typename T>
List<T> &List<T>::operator=(const List<T> &rhs)
{
  if (this != &rhs)
  {
    clear();
    copy(rhs);
  }

  return *this;
}

template <typename T>
List<T> &List<T>::operator=(List<T> &&rhs)
{
  if (this != &rhs)
  {
    _head = rhs._head;
    _tail = rhs._tail;
    _size = rhs._size;
    rhs._head = nullptr;
    rhs._tail = nullptr;
    rhs._size = 0;
  }
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::begin()
{
  return List<T>::iterator{_head};
}

template <typename T>
typename List<T>::iterator List<T>::end()
{
  return List<T>::iterator{_tail->next};
}

template <typename T>
typename List<T>::const_iterator List<T>::cbegin()
{
  return List<T>::const_iterator{_head};
}

template <typename T>
typename List<T>::const_iterator List<T>::cend()
{
  return List<T>::const_iterator{_tail->next};
}

template <typename T>
Node<T> *List<T>::head() const
{
  return _head;
}

template <typename T>
Node<T> *List<T>::tail() const
{
  return _tail;
}

template <typename T>
typename List<T>::iterator List<T>::get_middle_node() const
{
  Node<T> *fast = _head;
  Node<T> *slow = _head;
  while (fast && fast->next)
  {
    fast = fast->next->next;
    slow = slow->next;
  }
  return iterator{slow};
}

template <typename T>
int List<T>::size() const
{
  return _size;
}

template <typename T>
void List<T>::copy(const List<T> &rhs)
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
    _head = _tail = ptr;
    curr = curr->next;
  }

  while (curr != nullptr)
  {
    ptr->next = new Node<T>(curr->data);
    ptr->next->prev = ptr;
    ptr = ptr->next;
    curr = curr->next;
  }
  _size = rhs._size;
  _tail = ptr;
}

template <typename T>
void List<T>::insert(int pos, Node<T> *start, Node<T> *end)
{
  if (pos == 0)
  {

    end->next = _head;
    _head->prev = end;
    _head = start;
    return;
  }
  else if (pos > _size - 1)
  {
    start->prev = _tail;
    _tail->next = start;
    _tail = end;

    return;
  }
  Node<T> *ptr = _head;
  while (--pos && ptr->next != nullptr)
  {
    ptr = ptr->next;
  }
  ptr->next->prev = end;
  end->next = ptr->next;

  ptr->next = start;
  start->prev = ptr;
}

// iterator
template <typename T>
List<T>::iterator::iterator(Node<T> *p) : _ptr(p)
{
}

// operators
template <typename T>
T &List<T>::iterator::operator*()
{
  return _ptr->data;
}

template <typename T>
T *List<T>::iterator::operator->()
{
  return &_ptr->data;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator++()
{
  _ptr = _ptr->next;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)
{
  iterator p = *this;
  _ptr = _ptr->next;
  return p;
}

template <typename T>
typename List<T>::iterator &List<T>::iterator::operator--()
{
  _ptr = _ptr->prev;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)
{
  iterator p = *this;
  _ptr = _ptr->prev;
  return p;
}

template <typename T>
bool List<T>::iterator::operator!=(const iterator &other) const
{
  return other._ptr != _ptr;
}

template <typename T>
bool List<T>::iterator::operator==(const iterator &other) const
{
  return other._ptr == _ptr;
}

// const iterator
template <typename T>
List<T>::const_iterator::const_iterator(Node<T> *p) : _ptr(p)
{
}

// operators
template <typename T>
const T &List<T>::const_iterator::operator*() const
{
  return _ptr->data;
}

template <typename T>
const T *List<T>::const_iterator::operator->() const
{
  return &_ptr->data;
}

template <typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator++()
{
  _ptr = _ptr->next;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
{
  const_iterator p = *this;
  _ptr = _ptr->next;
  return p;
}

template <typename T>
typename List<T>::const_iterator &List<T>::const_iterator::operator--()
{
  _ptr = _ptr->prev;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
{
  const_iterator p = *this;
  _ptr = _ptr->prev;
  return p;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &other) const
{
  return other._ptr != _ptr;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &other) const
{
  return other._ptr == _ptr;
}

#endif // LIST_H