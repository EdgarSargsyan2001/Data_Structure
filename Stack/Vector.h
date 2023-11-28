#include <iostream>
#ifndef Vector_H
#define Vector_H

template <typename T>
class Vector
{
public:
  class Iterator;
  class ConstIterator;
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = Vector::Iterator;
  using const_iterator = Vector::ConstIterator;

public:
  Vector();                                  // default ctor
  Vector(std::initializer_list<value_type>); // initializer list ctor
  Vector(const Vector<value_type> &);        // copy ctor
  Vector(Vector<value_type> &&);             // move ctor
  ~Vector();                                 // dtor

public:
  // push_back
  void push_back(value_type);                 // ~O(1)
  void push_back(value_type, int);            // ~O(1)
  void push_back(pointer, int);               // ~O(1)
  void push_back(const Vector<value_type> &); // ~O(1)

  value_type pop_back(); // O(1)
  void shrink();         // O(n)

  // insert
  void insert(value_type, int);                        // O(n)
  void insert(std::initializer_list<value_type>, int); // O(n)
  void insert(pointer, int, int);                      // O(n)
  void insert(const Vector<value_type> &, int);        // O(n)
  void insert(value_type, int, int);                   // O(n)

  // delete
  void remove(int);      // O(n)
  void remove(int, int); // O(n)

  // methods
  int search(value_type);               // O(n)
  reference at(int);                    // O(1)
  bool empty();                         // O(1)
  void clear();                         // O(1)
  void reserve(int);                    // O(n)
  void resize(int, value_type val = 0); // O(n)

  // getters
  size_type size() const;     // O(1)
  size_type capacity() const; // O(1)

  iterator begin();                    // O(1)
  iterator end();                      // O(1)
  const const_iterator cbegin() const; // O(1)
  const const_iterator cend() const;   // O(1)

  // operators
  Vector<value_type> &operator=(const Vector<value_type> &); // copy assignment
  Vector<value_type> &operator=(Vector<value_type> &&);      // move assignment
  Vector<value_type> operator+(const Vector<value_type> &);
  reference operator[](int); // O(1)

private:
  void copy(const Vector<value_type> &); // O(n)

private:
  size_type m_capacity = 0;
  size_type m_size = 0;
  pointer m_arr = nullptr;

  // Iterator
public:
  class Iterator
  {
  public:
    Iterator() = default;  // default ctor
    Iterator(pointer ptr); // ctor

    // operators
    reference operator*();
    pointer operator->();
    iterator &operator++();
    iterator operator++(int);
    iterator &operator--();
    iterator operator--(int);
    T &operator[](int i);

    bool operator!=(const iterator &other) const;
    bool operator==(const iterator &other) const;
    bool operator<(const iterator &other) const;
    bool operator>(const iterator &other) const;

  private:
    pointer m_ptr = nullptr;
  };

  class ConstIterator
  {
    ConstIterator() = default;
    ConstIterator(const_pointer ptr);

    // operators
    const_reference operator*() const;
    const_pointer operator->() const;
    const_iterator &operator++() const;
    const_iterator operator++(int) const;
    const_iterator &operator--() const;
    const_iterator operator--(int) const;
    const_reference &operator[](int i) const;

    bool operator!=(const const_iterator &other) const;
    bool operator==(const const_iterator &other) const;
    bool operator<(const const_iterator &other) const;
    bool operator>(const const_iterator &other) const;

  private:
    const_pointer m_ptr = nullptr;
  };
};

// default ctr
template <typename T>
Vector<T>::Vector() {}

// copy ctr
template <typename T>
Vector<T>::Vector(const Vector &oth)
{
  std::cout << "call copy ctr\n";
  copy(oth);
}

// move ctr
template <typename T>
Vector<T>::Vector(Vector &&Rval)
{
  std::cout << "move ctr";
  m_capacity = Rval.m_capacity;
  m_size = Rval.m_size;
  m_arr = Rval.m_arr;
  Rval.m_arr = nullptr;
  Rval.m_size = 0;
  Rval.m_capacity = 0;
}

// Constructor with initializer_list as an argument
template <typename T>
Vector<T>::Vector(std::initializer_list<T> list)
{
  for (T el : list)
  {
    push_back(el);
  }
}

// Dctr
template <typename T>
Vector<T>::~Vector()
{
  delete[] m_arr;
}

template <typename T>
typename Vector<T>::size_type Vector<T>::size() const
{
  return m_size;
};

template <typename T>
typename Vector<T>::size_type Vector<T>::capacity() const
{
  return m_capacity;
}

//// ===== operators ===================

// copy assignment operator
template <typename T>
Vector<typename Vector<T>::value_type> &Vector<T>::operator=(const Vector &rhs)
{
  // std::cout << "call copy ctr\n";
  if (this != &rhs)
  {
    if (rhs.m_capacity == m_capacity)
    {
      m_size = rhs.m_size;
      for (int i = 0; i < m_size; i++)
      {
        m_arr[i] = rhs.m_arr[i];
      }
    }
    else
    {
      delete[] m_arr;
      copy(rhs);
    }
  }

  return *this;
}

template <typename T>

Vector<typename Vector<T>::value_type> &Vector<T>::operator=(Vector &&rhs) // move assignment
{
  if (this != &rhs)
  {
    m_capacity = rhs.m_capacity;
    m_size = rhs.m_size;
    m_arr = rhs.m_arr;
    rhs.m_arr = nullptr;
    rhs.m_size = 0;
    rhs.m_capacity = 0;
  }
  return *this;
}

// Overloading [] operator
template <typename T>
T &Vector<T>::operator[](int i)
{
  return m_arr[i];
}

// Overloading + operator custom solution
template <typename T>
Vector<typename Vector<T>::value_type> Vector<T>::operator+(const Vector<value_type> &v)
{
  Vector<T> r;
  r.m_capacity = m_capacity + v.m_capacity;
  r.m_size = m_size + v.m_size;
  r.m_arr = new T[r.m_capacity];
  int i = 0;
  for (; i < m_size; i++)
  {
    r.m_arr[i] = m_arr[i];
  }
  for (int j = 0; j < v.m_size; j++, i++)
  {
    r.m_arr[i] = v.m_arr[j];
  }
  // std::cout << "Overloading + operator\n";
  return r;
}

// private mathids
template <typename T>
void Vector<T>::copy(const Vector<value_type> &rhs)
{
  m_capacity = rhs.m_capacity;
  m_size = rhs.m_size;
  m_arr = new T[m_capacity];
  for (int i = 0; i < m_size; i++)
  {
    m_arr[i] = rhs.m_arr[i];
  }
}

// other mathids
template <typename T>
void Vector<T>::push_back(value_type el)
{
  if (m_capacity == m_size)
  {
    reserve(m_capacity ? m_capacity * 2 : 1);
  }
  m_arr[m_size++] = el;
}

template <typename T>
void Vector<T>::push_back(value_type val, int count)
{
  for (int i = 0; i < count; ++i)
  {
    push_back(val);
  }
}

template <typename T>
void Vector<T>::push_back(pointer arr, int N)
{
  for (int i = 0; i < N; ++i)
  {
    push_back(arr[i]);
  }
}

template <typename T>
void Vector<T>::push_back(const Vector<value_type> &v)
{
  for (int i = 0; i < v.m_size; ++i)
  {
    push_back(v[i]);
  }
}

template <typename T>
typename Vector<T>::value_type Vector<T>::pop_back()
{
  return m_arr[--m_size];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin()
{
  return Vector<T>::iterator{m_arr};
}
template <typename T>
typename Vector<T>::iterator Vector<T>::end()
{
  return Vector<T>::iterator{m_arr + m_size};
}
template <typename T>
const typename Vector<T>::const_iterator Vector<T>::cbegin() const
{
  // return ConstIterator();
}
template <typename T>
const typename Vector<T>::const_iterator Vector<T>::cend() const
{
}

template <typename T>
void Vector<T>::shrink()
{
  m_capacity = m_size + 1;
  T *newArr = new T[m_capacity];
  for (int i = 0; i < m_size; ++i)
  {
    newArr[i] = m_arr[i];
  }
  delete m_arr;
  m_arr = newArr;
}

template <typename T>
void Vector<T>::insert(value_type val, int index)
{
  if (index >= 0 && index <= m_size)
  {
    if (m_size++ == m_capacity)
    {
      reserve(m_capacity ? m_capacity * 1.3 : 1);
    }

    for (int i = m_size - 1; i >= index; --i)
    {
      m_arr[i] = m_arr[i - 1];
    }
    m_arr[index] = val;
  }
}

template <typename T>
void Vector<T>::insert(std::initializer_list<value_type> list, int index)
{
  for (T el : list)
  {
    insert(el, index++);
  }
}

template <typename T>
void Vector<T>::insert(pointer arr, int N, int index)
{
  for (int i = 0; i < N; ++i)
  {
    insert(arr[i], index++);
  }
}

template <typename T>
void Vector<T>::insert(const Vector<value_type> &v, int index)
{
  for (int el : v)
  {
    insert(el, index++);
  }
}

template <typename T>
void Vector<T>::insert(value_type val, int count, int index)
{
  for (int i = 0; i < count; ++i)
  {
    insert(val, index++);
  }
}

template <typename T>
void Vector<T>::remove(int i)
{
  while (i < m_size)
  {
    m_arr[i] = m_arr[i + 1];
    ++i;
  }
  --m_size;
}

template <typename T>
void Vector<T>::remove(int start, int end)
{
  int interval = end - start;
  if (interval > 0 && interval <= m_size)
  {
    while (start < m_size)
    {
      m_arr[start] = m_arr[start + interval];
      ++start;
    }
    m_size -= interval;
  }
}

template <typename T>
int Vector<T>::search(value_type val)
{
  for (int i = 0; i < m_size; ++i)
  {
    if (m_arr[i] == val)
    {
      return i;
    }
  }
  return -1;
}

template <typename T>

T &Vector<T>::at(int pos)
{
  if (pos >= m_size || pos < 0)
  {
    throw std::out_of_range("");
  }
  return m_arr[pos];
}

template <typename T>
bool Vector<T>::empty()
{
  return m_size == 0;
}

template <typename T>
void Vector<T>::clear()
{
  m_size = 0;
}

template <typename T>
void Vector<T>::reserve(int count)
{

  if (count > m_capacity)
  {
    m_capacity = count;
    T *newArr = new int[count];
    for (int i = 0; i < m_size; ++i)
    {
      newArr[i] = m_arr[i];
    }
    delete[] m_arr;
    m_arr = newArr;
  }
}
template <typename T>
void Vector<T>::resize(int count, value_type val)
{
  int interval = count - m_size;
  if (interval > 0)
  {
    for (int i = 0; i < interval; ++i)
    {
      push_back(val);
    }
  }
  else
  {
    m_size = count;
  }
}

// iterator implem.
template <typename T>
Vector<T>::Iterator::Iterator(pointer ptr)
    : m_ptr(ptr)
{
}

template <typename T>
T &Vector<T>::Iterator::operator*()
{
  return *m_ptr;
}

template <typename T>
typename Vector<T>::pointer Vector<T>::Iterator::operator->()
{
  return m_arr;
}

template <typename T>
typename Vector<T>::iterator &Vector<T>::Iterator::operator++()
{
  ++m_ptr;
  return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Iterator::operator++(int)
{
  Iterator p = *this;
  m_ptr++;
  return p;
}

template <typename T>
typename Vector<T>::iterator &Vector<T>::Iterator::operator--()
{
  --m_ptr;
  return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::Iterator::operator--(int)
{
  Iterator p = *this;
  m_ptr--;
  return p;
}

template <typename T>
T &Vector<T>::Iterator::operator[](int i)
{
  return m_ptr[i];
}

template <typename T>
bool Vector<T>::Iterator::operator!=(const iterator &other) const
{
  return m_ptr != other.m_ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator==(const iterator &other) const
{
  return m_ptr == other.m_ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator<(const iterator &other) const
{
  return m_ptr < other.m_ptr;
}

template <typename T>
bool Vector<T>::Iterator::operator>(const iterator &other) const
{
  return m_ptr > other.m_ptr;
}

// const iterator
template <typename T>
Vector<T>::ConstIterator::ConstIterator(const_pointer ptr)
    : m_ptr(ptr)
{
}

template <typename T>
typename Vector<T>::const_reference Vector<T>::ConstIterator::operator*() const
{
  return *m_ptr;
}

template <typename T>
typename Vector<T>::const_pointer Vector<T>::ConstIterator::operator->() const
{
  return m_ptr;
}

template <typename T>
typename Vector<T>::const_iterator &Vector<T>::ConstIterator::operator++() const
{
  m_ptr++;
  return *this;
}
template <typename T>
typename Vector<T>::const_iterator Vector<T>::ConstIterator::operator++(int) const
{
  const_iterator it = m_ptr;
  ++m_ptr;
  return it;
}
template <typename T>
typename Vector<T>::const_iterator &Vector<T>::ConstIterator::operator--() const
{
  m_ptr--;
  return *this;
}
template <typename T>
typename Vector<T>::const_iterator Vector<T>::ConstIterator::operator--(int) const
{
  const_iterator it = m_ptr;
  --m_ptr;
  return it;
}

template <typename T>
typename Vector<T>::const_reference &Vector<T>::ConstIterator::operator[](int i) const
{
  return m_ptr[i];
}

template <typename T>
bool Vector<T>::ConstIterator::operator!=(const const_iterator &other) const
{
  return m_ptr != other.m_ptr;
}
template <typename T>
bool Vector<T>::ConstIterator::operator==(const const_iterator &other) const
{
  return m_ptr == other.m_ptr;
}
template <typename T>
bool Vector<T>::ConstIterator::operator<(const const_iterator &other) const
{
  return m_ptr < other.m_ptr;
}
template <typename T>
bool Vector<T>::ConstIterator::operator>(const const_iterator &other) const
{
  return m_ptr > other.m_ptr;
}

#endif