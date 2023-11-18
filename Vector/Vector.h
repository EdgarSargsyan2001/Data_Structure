#include <iostream>
#ifndef Vector_H
#define Vector_H

template <typename T>
class Vector
{

public:
  class iterator
  {

  public:
    iterator() : m_vector(nullptr), m_nindex(-1){};
    iterator(const Vector<T> *vector, int nindex);
    const T &operator*() const;
    iterator &operator++();
    iterator operator++(int);
    bool operator!=(const iterator &other) const;
    bool operator<(const iterator &other) const;

  private:
    const Vector<T> *m_vector;
    int m_nindex = -1;
  };

public:
  Vector();                         // default ctor
  Vector(std::initializer_list<T>); // initializer list ctor
  Vector(const Vector &);           // copy ctor
  Vector(Vector &&);                // move ctor
  ~Vector();                        // dtor

public:
  // push_back
  void push_back(T);                 // ~O(1)
  void push_back(T, int);            // ~O(1)
  void push_back(T *, int);          // ~O(1)
  void push_back(const Vector<T> &); // ~O(1)

  T pop_back();  // O(1)
  void shrink(); // O(n)

  // insert
  void insert(T, int);                        // O(n)
  void insert(std::initializer_list<T>, int); // O(n)
  void insert(T *, int, int);                 // O(n)
  void insert(const Vector<T> &, int);        // O(n)
  void insert(T, int, int);                   // O(n)

  // delete
  void remove(int);      // O(n)
  void remove(int, int); // O(n)

  // methods
  int search(T);               // O(n)
  T &at(int);                  // O(1)
  bool empty();                // O(1)
  void clear();                // O(1)
  void reserve(int);           // O(n)
  void resize(int, T val = 0); // O(n)

  // getters
  int size();             // O(1)
  int capacity();         // O(1)
  iterator begin() const; // O(1)
  iterator end() const;   // O(1)

  // operators
  Vector<T> &operator=(const Vector &); // copy assignment
  Vector<T> &operator=(Vector &&);      // move assignment
  Vector<T> operator+(const Vector &);
  T &operator[](int); // O(1)

private:
  void copy(const Vector &); // O(n)

private:
  int m_capacity = 0;
  int m_size = 0;
  T *m_arr = nullptr;
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
int Vector<T>::size()
{
  return m_size;
};

template <typename T>
int Vector<T>::capacity()
{
  return m_capacity;
}

//// ===== operators ===================

// copy assignment operator
template <typename T>
Vector<T> &Vector<T>::operator=(const Vector &rhs)
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

Vector<T> &Vector<T>::operator=(Vector &&rhs) // move assignment
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
Vector<T> Vector<T>::operator+(const Vector &v)
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
void Vector<T>::copy(const Vector &rhs)
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
void Vector<T>::push_back(T el)
{
  if (m_capacity == m_size)
  {
    reserve(m_capacity ? m_capacity * 2 : 1);
  }
  m_arr[m_size++] = el;
}

template <typename T>
void Vector<T>::push_back(T val, int count)
{
  for (int i = 0; i < count; ++i)
  {
    push_back(val);
  }
}

template <typename T>
void Vector<T>::push_back(T *arr, int N)
{
  for (int i = 0; i < N; ++i)
  {
    push_back(arr[i]);
  }
}

template <typename T>
void Vector<T>::push_back(const Vector<T> &v)
{
  for (int i = 0; i < v.m_size; ++i)
  {
    push_back(v[i]);
  }
}

template <typename T>
T Vector<T>::pop_back()
{
  return m_arr[--m_size];
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const
{
  return Vector<T>::iterator{this, 0};
}
template <typename T>
typename Vector<T>::iterator Vector<T>::end() const
{
  return Vector<T>::iterator{this, m_size};
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
void Vector<T>::insert(T val, int index)
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
void Vector<T>::insert(std::initializer_list<T> list, int index)
{
  for (T el : list)
  {
    insert(el, index++);
  }
}

template <typename T>
void Vector<T>::insert(T *arr, int N, int index)
{
  for (int i = 0; i < N; ++i)
  {
    insert(arr[i], index++);
  }
}

template <typename T>
void Vector<T>::insert(const Vector<T> &v, int index)
{
  for (int el : v)
  {
    insert(el, index++);
  }
}

template <typename T>
void Vector<T>::insert(T val, int count, int index)
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
int Vector<T>::search(T val)
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
void Vector<T>::resize(int count, T val)
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
Vector<T>::iterator::iterator(const Vector<T> *vector, int nindex)
    : m_vector(vector), m_nindex(nindex)
{
}

template <typename T>
const T &Vector<T>::iterator::operator*() const
{
  if (m_vector == nullptr)
    throw std::invalid_argument(":)");
  return m_vector->m_arr[m_nindex];
}

template <typename T>
typename Vector<T>::iterator &Vector<T>::iterator::operator++()
{
  if (m_nindex == -1)
    throw std::invalid_argument(":))");

  ++m_nindex;
  return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator++(int)
{
  if (m_nindex == -1)
    throw std::invalid_argument(":))");

  iterator p = *this;
  m_nindex++;
  return p;
}

template <typename T>
bool Vector<T>::iterator::operator!=(const iterator &other) const
{
  if (m_nindex == -1)
    throw std::invalid_argument(":)))");
  return m_nindex != other.m_nindex;
}

template <typename T>
bool Vector<T>::iterator::operator<(const iterator &other) const
{
  if (m_nindex == -1)
    throw std::invalid_argument(":)))");
  return m_nindex < other.m_nindex;
}
#endif