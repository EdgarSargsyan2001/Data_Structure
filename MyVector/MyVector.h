#include <iostream>
#ifndef MyVector_H
#define MyVector_H

template <typename T>
class MyVector
{

public:
  class iterator
  {

  public:
    iterator() : m_vector(nullptr), m_nindex(-1){};
    iterator(const MyVector<T> *vector, int nindex);
    const T &operator*() const;
    iterator &operator++();
    iterator operator++(int);
    bool operator!=(const iterator &other) const;
    bool operator<(const iterator &other) const;

  private:
    const MyVector<T> *m_vector;
    int m_nindex = -1;
  };

public:
  MyVector();
  MyVector(MyVector &&); // move ctr
  MyVector(const MyVector &);
  MyVector(std::initializer_list<T>);
  ~MyVector();

public:
  void push_back(T);
  int size() { return m_size; };
  void print();
  void printPtr() { std::cout << "\n"
                              << m_arr << "\n"; };
  iterator begin() const;
  iterator end() const;

public:
  MyVector<T> &operator=(const MyVector &);
  MyVector<T> operator+(const MyVector &);
  T &operator[](int);

private:
  int m_capacity;
  int m_size;
  T *m_arr;

private:
  void copy(const MyVector &);
};

// default ctr
template <typename T>
MyVector<T>::MyVector() : m_size{0}, m_capacity{0}, m_arr{nullptr}
{
  std::cout << "default ctr\n";
}

// copy ctr
template <typename T>
MyVector<T>::MyVector(const MyVector &oth)
    : m_size{0}, m_capacity{0}, m_arr{nullptr}
{
  std::cout << "call copy ctr\n";
  copy(oth);
}

// move ctr
template <typename T>
MyVector<T>::MyVector(MyVector &&Rval)
    : m_size{0}, m_capacity{0}, m_arr{nullptr}
{
  std::cout << "move ctr";
  m_capacity = Rval.m_capacity;
  m_size = Rval.m_size;
  m_arr = Rval.m_arr;
  Rval.m_arr = nullptr;
}

// Constructor with initializer_list as an argument
template <typename T>
MyVector<T>::MyVector(std::initializer_list<T> list)
    : m_size{0}, m_capacity{0}, m_arr{nullptr}
{
  // std::cout << "initializer_list \n";
  typename std::initializer_list<T>::iterator el = list.begin();
  for (int i = 0; i < list.size(); i++)
  {
    push_back(*(el + i));
  }
}

// Dctr
template <typename T>
MyVector<T>::~MyVector()
{
  if (m_arr)
  {
    delete[] m_arr;
    m_arr = nullptr;
  }
}

//// ===== operators ===================

// copy assignment operator
template <typename T>
MyVector<T> &MyVector<T>::operator=(const MyVector &rhs)
{
  // std::cout << "call copy ctr\n";
  if (this == &rhs)
  {
    return *this;
  }
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
  return *this;
}

// Overloading [] operator
template <typename T>
T &MyVector<T>::operator[](int i)
{
  if (i < 0 || i >= m_size)
  {
    throw std::runtime_error("error");
  }
  else
  {
    return m_arr[i];
  }
}

// Overloading + operator
template <typename T>
MyVector<T> MyVector<T>::operator+(const MyVector &v)
{

  MyVector<T> r;
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
void MyVector<T>::copy(const MyVector &rhs)
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
void MyVector<T>::push_back(T el)
{
  if (m_capacity == m_size)
  {
    m_capacity = m_capacity ? m_capacity * 2 : 1;

    T *temp = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
    {
      temp[i] = m_arr[i];
    }
    delete[] m_arr;
    m_arr = temp;
  }
  m_arr[m_size++] = el;
}
template <typename T>
typename MyVector<T>::iterator MyVector<T>::begin() const
{
  return MyVector<T>::iterator{this, 0};
}
template <typename T>
typename MyVector<T>::iterator MyVector<T>::end() const
{
  return MyVector<T>::iterator{this, m_size};
}

template <typename T>
void MyVector<T>::print()
{
  for (int i = 0; i < m_size; i++)
  {
    std::cout << m_arr[i] << " ";
  }
  std::cout << "\n";
}

// iterator implem.
template <typename T>
MyVector<T>::iterator::iterator(const MyVector<T> *vector, int nindex) : m_vector(vector), m_nindex(nindex)
{
}

template <typename T>
const T &MyVector<T>::iterator::operator*() const
{
  if (m_vector == nullptr)
    throw std::invalid_argument(":)");
  return m_vector->m_arr[m_nindex];
}
template <typename T>
typename MyVector<T>::iterator &MyVector<T>::iterator::operator++()
{
  if (m_nindex == -1)
    throw std::invalid_argument(":))");

  ++m_nindex;
  return *this;
}

template <typename T>
typename MyVector<T>::iterator MyVector<T>::iterator::operator++(int)
{
  if (m_nindex == -1)
    throw std::invalid_argument(":))");

  iterator p = *this;
  m_nindex++;
  return p;
}

template <typename T>
bool MyVector<T>::iterator::operator!=(const iterator &other) const
{
  if (m_nindex == -1)
    throw std::invalid_argument(":)))");
  return m_nindex != other.m_nindex;
}

template <typename T>
bool MyVector<T>::iterator::operator<(const iterator &other) const
{
  if (m_nindex == -1)
    throw std::invalid_argument(":)))");
  return m_nindex < other.m_nindex;
}
#endif