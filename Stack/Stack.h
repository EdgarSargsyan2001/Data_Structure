#ifndef STACK_H
#define STACK_H
#include "Vector.h"

template <typename T>
class Stack
{
public:
  Stack() = default;
  Stack(std::initializer_list<T> li);
  ~Stack(){};

  // modifiers
  void push(T);
  void pop();

  // getters
  T top();
  bool empty() const;
  size_t size() const;

private:
  Vector<T> _vec;
};

template <typename T>
Stack<T>::Stack(std::initializer_list<T> list)
{
  for (T el : list)
  {
    _vec.push_back(el);
  }
}

// modifiers
template <typename T>
void Stack<T>::push(T el)
{
  _vec.push_back(el);
}

template <typename T>
void Stack<T>::pop()
{
  if (!empty())
  {
    _vec.pop_back();
  }
}

// getters
template <typename T>
bool Stack<T>::empty() const
{
  return _vec.size() == 0;
}

template <typename T>
T Stack<T>::top()
{
  if (!empty())
  {
    return _vec[_vec.size() - 1];
  }
  throw std::invalid_argument("top not found");
}

template <typename T>
size_t Stack<T>::size() const
{
  return _vec.size();
}

#endif // STACK_H