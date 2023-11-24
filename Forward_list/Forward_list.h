#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H
#include <iostream>

template <class T>
struct Node
{
  Node(T d, Node<T> *p = nullptr) : info(d), next(p) {}
  T info;
  Node<T> *next;
};

template <class T>
class Forward_list
{
public:
  Forward_list();                              // default ctor
  Forward_list(std::initializer_list<T> list); // initializer_list ctor
  Forward_list(const Forward_list &);          // copy ctor
  Forward_list(Forward_list &&);               // move ctor
  ~Forward_list();                             // dtor

  // insert
  void insert_after(Node<T> *p, const T &val);         // O(1)
  void insert_at(int pos, const T &val);               // O(n)
  void insert(int pos, std::initializer_list<T> list); // O(n + m)
  void insert(int pos, const T *arr, int N);           // O(n + m)
  void insert(int pos, const Forward_list &);          // O(n + m)

  // push / pop
  void push_front(const T &val); // O(1)
  void pop_front();              // O(1)

  // delete
  void delete_after(Node<T> *p); // O(1)
  void delete_at(int n);         // O(n)
  void remove(const T &val);     // O(n)

  // methods
  bool empty() const;                       // O(1)
  void clear();                             // O(n)
  T &front();                               // O(1)
  void resize(int count, const T &val = 0); // O(n^2)
  Node<T> *search(const T &val);            // O(n)
  void reverse();                           // O(n)
  bool has_cyrcl();                         //
  void marge_to_sorted_list(Node<T> *);     // O( n + m)

  // operators
  Forward_list<T> &operator=(const Forward_list<T> &); // copy assignment
  Forward_list<T> &operator=(Forward_list<T> &&);      // move assignment

  // getters
  Node<T> *head() const;
  Node<T> *tail() const;
  Node<T> *get_middle_node() const; // O(n / 2)

  int size() const; // O(n)

private:
  void copy(const Forward_list<T> &);                 // O(n)
  void insert(int pos, Node<T> *start, Node<T> *end); // O(m)

private:
  Node<T> *_head = nullptr;
};

template <class T>
Forward_list<T>::Forward_list() {}

template <class T>
Forward_list<T>::Forward_list(std::initializer_list<T> list)
{
  _head = new Node<T>(*list.begin());
  Node<T> *curr = _head;
  for (auto it = list.begin() + 1; it != list.end(); it++)
  {
    curr->next = new Node<T>(*it);
    curr = curr->next;
  }
}

template <class T>
Forward_list<T>::Forward_list(const Forward_list &rhs)
{
  copy(rhs);
}

template <class T>
Forward_list<T>::Forward_list(Forward_list &&rhs)
{
  _head = rhs._head;
  rhs._head = nullptr;
}

template <class T>
Forward_list<T>::~Forward_list()
{
  while (_head != nullptr)
  {
    Node<T> *tmp = _head;
    _head = _head->next;
    delete tmp;
  }
}

// methos
template <class T>
bool Forward_list<T>::empty() const { return _head == nullptr; }

template <class T>
void Forward_list<T>::clear()
{
  while (_head != nullptr)
  {

    Node<T> *tmp = _head;
    _head = _head->next;
    delete tmp;
  }
  _head = nullptr;
}

template <class T>
T &Forward_list<T>::front()
{
  return _head->info;
}

template <class T>
void Forward_list<T>::resize(int count, const T &val)
{
  int N = size();
  int interval = count - N;

  if (interval > 0)
  {

    Node<T> *first = new Node<T>(val);
    Node<T> *curr = first;
    for (int i = 1; i < interval; ++i)
    {
      curr->next = new Node<T>(val);
      curr = curr->next;
    }

    tail()->next = first;
  }
  else
  {
    while (interval++)
    {
      delete_at(count);
    }
  }
}

template <class T>
Node<T> *Forward_list<T>::search(const T &val)
{
  Node<T> *ptr = _head;
  while (ptr != nullptr)
  {
    if (ptr->info == val)
    {
      return ptr;
    }
    ptr = ptr->next;
  }
  return nullptr;
}

template <class T>
void Forward_list<T>::reverse()
{
  if (_head)
  {
    Node<T> *prev = nullptr;
    Node<T> *curr = _head;
    Node<T> *next = _head->next;

    while (next)
    {
      curr->next = prev;
      prev = curr;
      curr = next;
      next = next->next;
    }
    curr->next = prev;

    _head = curr;
  }
}

template <class T>
bool Forward_list<T>::has_cyrcl()
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

template <class T>
void Forward_list<T>::marge_to_sorted_list(Node<T> *head2)
{
  if (_head)
  {
    Node<T> *ptr = _head;
    while (ptr->info >= head2->info)
    {
      push_front(head2->info);
      head2 = head2->next;
      ptr = _head;
    }

    while (ptr && ptr->next && head2)
    {
      T val = head2->info;
      if (ptr->info < val && ptr->next->info > val)
      {
        insert_after(ptr, val);
        head2 = head2->next;
      }
      ptr = ptr->next;
    }

    while (head2)
    {
      insert_after(ptr, head2->info);
      head2 = head2->next;
      ptr = ptr->next;
    }
  }
}

// operators
template <class T>
Forward_list<T> &Forward_list<T>::operator=(const Forward_list<T> &rhs)
{
  if (this != &rhs)
  {
    clear();
    copy(rhs);
  }

  return *this;
}

template <class T>
Forward_list<T> &Forward_list<T>::operator=(Forward_list<T> &&rhs)
{
  if (this != &rhs)
  {
    _head = rhs._head;
    rhs._head = nullptr;
  }
  return *this;
}

template <class T>
Node<T> *Forward_list<T>::head() const { return _head; }

template <class T>
Node<T> *Forward_list<T>::tail() const
{
  Node<T> *curr = _head;
  while (curr->next)
  {
    curr = curr->next;
  }
  return curr;
}

template <class T>
Node<T> *Forward_list<T>::get_middle_node() const
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
int Forward_list<T>::size() const
{
  int i = 0;
  Node<T> *ptr = _head;
  while (ptr)
  {
    i++;
    ptr = ptr->next;
  }
  return i;
}

template <class T>
void Forward_list<T>::insert_after(Node<T> *p, const T &val)
{
  p->next = new Node<T>(val, p->next);
}

template <class T>
void Forward_list<T>::insert_at(int pos, const T &val)
{
  if (pos == 0)
  {
    push_front(val);
    return;
  }
  Node<T> *ptr = _head;
  while (--pos && ptr->next != nullptr)
  {
    ptr = ptr->next;
  }
  insert_after(ptr, val);
}

template <class T>
void Forward_list<T>::insert(int pos, std::initializer_list<T> list)
{
  if (list.size() > 0)
  {
    Node<T> *start = new Node<T>(*list.begin());
    Node<T> *end = start;
    for (auto it = list.begin() + 1; it != list.end(); it++)
    {
      end->next = new Node<T>(*it);
      end = end->next;
    }

    insert(pos, start, end);
  }
}

template <class T>
void Forward_list<T>::insert(int pos, const T *arr, int N)
{
  if (N > 0)
  {
    Node<T> *start = new Node<T>(arr[0]);
    Node<T> *end = start;
    for (int i = 1; i < N; ++i)
    {
      end->next = new Node<T>(arr[i]);
      end = end->next;
    }
    insert(pos, start, end);
  }
}

template <class T>
void Forward_list<T>::insert(int pos, const Forward_list &li)
{
  if (li._head != nullptr)
  {
    Node<T> *start = new Node<T>(li._head->info);
    Node<T> *end = start;

    Node<T> *h = li.head()->next;
    while (h != nullptr)
    {
      end->next = new Node<T>(h->info);
      end = end->next;
      h = h->next;
    }
    insert(pos, start, end);
  }
}

template <class T>
void Forward_list<T>::push_front(const T &val)
{
  _head = new Node<T>(val, _head);
}

template <class T>
void Forward_list<T>::pop_front()
{
  if (_head)
  {
    Node<T> *tmp = _head;
    _head = _head->next;
    delete tmp;
  }
}

template <class T>
void Forward_list<T>::delete_after(Node<T> *p)
{
  Node<T> *tmp = p->next;
  if (tmp)
  {
    p->next = tmp->next;
    delete tmp;
  }
}

template <class T>
void Forward_list<T>::delete_at(int pos)
{
  if (pos == 0)
  {
    pop_front();
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
void Forward_list<T>::remove(const T &val)
{
  if (_head && _head->info == val)
  {
    pop_front();
    return;
  }

  Node<T> *ptr = _head;
  while (ptr->next != nullptr && ptr->next->info != val)
  {
    ptr = ptr->next;
  }
  delete_after(ptr);
}

template <class T>
void Forward_list<T>::copy(const Forward_list<T> &rhs)
{
  Node<T> *curr = rhs._head;
  if (!curr)
  {
    return;
  }
  Node<T> *ptr = nullptr;
  if (_head == nullptr)
  {
    ptr = new Node<T>(curr->info);
    _head = ptr;
    curr = curr->next;
  }
  while (curr != nullptr)
  {
    ptr->next = new Node<T>(curr->info);
    ptr = ptr->next;
    curr = curr->next;
  }
}

template <class T>
void Forward_list<T>::insert(int pos, Node<T> *start, Node<T> *end)
{
  if (pos == 0)
  {
    end->next = _head;
    _head = start;
    return;
  }

  Node<T> *ptr = _head;
  while (--pos && ptr->next != nullptr)
  {
    ptr = ptr->next;
  }
  end->next = ptr->next;
  ptr->next = start;
}

#endif // FORWARD_LIST_H