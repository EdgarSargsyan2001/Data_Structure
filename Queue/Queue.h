#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>

template <typename T>
class Queue
{
public:
    Queue(size_t n);
    Queue(const Queue<T> &q);
    ~Queue();

    // setters
    void push(T val);

    // getters
    T top() const;
    void pop();
    size_t size() const;
    size_t capacity() const;

    // methods
    bool empty();

    // copy asignment
    Queue &operator=(const Queue<T> &q);

public:
    size_t _size = 0;
    size_t _capacity = 0;
    size_t _front_index = 0;
    size_t _rear_index = 0;
    T *_arr = nullptr;
};

template <typename T>
Queue<T>::Queue(size_t n) : _capacity(n)
{
    _arr = new T[_capacity];
}

template <typename T>
Queue<T>::Queue(const Queue &q)
    : _size(q._size),
      _capacity(q._capacity),
      _front_index(q._front_index),
      _rear_index(q._rear_index)
{
    _arr = new T[_capacity];
    for (int i = 0; i < _capacity; ++i)
    {
        _arr[i] = q._arr[i];
    }
}

template <typename T>
Queue<T>::~Queue()
{
    delete[] _arr;
}

template <typename T>
Queue<T> &Queue<T>::operator=(const Queue &q)
{
    if (this != &q)
    {
        _size = q._size;
        _capacity = q._capacity;
        _front_index = q._front_index;
        _rear_index = q._rear_index;

        delete[] _arr;
        _arr = new T[_capacity];

        for (int i = 0; i < _capacity; ++i)
        {
            _arr[i] = q._arr[i];
        }
    }

    return *this;
}

template <typename T>
bool Queue<T>::empty() { return _size == 0; }

template <typename T>
T Queue<T>::top() const { return _arr[_front_index]; }

template <typename T>
void Queue<T>::push(T val)
{
    if (_size != _capacity)
    {
        if (_rear_index == _capacity)
        {
            _rear_index = 0;
        }
        _arr[_rear_index++] = val;
        _size++;
    }
}

template <typename T>
void Queue<T>::pop()
{
    if (!empty())
    {
        _size--;
        ++_front_index;
        if (_front_index == _capacity)
        {
            _front_index = 0;
            _rear_index = 0;
        }
    }
}

template <typename T>
size_t Queue<T>::size() const
{
    return _size;
}

template <typename T>
size_t Queue<T>::capacity() const
{
    return _capacity;
}

#endif // QUEUE_H