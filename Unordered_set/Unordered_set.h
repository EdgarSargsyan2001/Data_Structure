#ifndef UNORDERED_SET_H
#define UNORDERED_SET_H
#include <iostream>
#include <forward_list>

template <typename T>
class Unordered_set
{
public:
    Unordered_set(){};
    Unordered_set(const Unordered_set<T> &);
    Unordered_set(Unordered_set<T> &&);
    Unordered_set(std::initializer_list<T> list);
    ~Unordered_set();

    // insert
    bool insert(const T &key);

    // delete
    void remove(const T &key);

    // methods
    bool search(const T &key);
    bool empty();
    void clear();
    void print();

    // getters
    size_t size();
    size_t capacity();

    // operators
    Unordered_set<T> &operator=(const Unordered_set<T> &);
    Unordered_set<T> &operator=(Unordered_set<T> &&);

private:
    void reserve(int count);
    size_t hash(T el) = delete;
    void copy(const Unordered_set<T> &);

private:
    std::forward_list<T> *_arr = nullptr;
    size_t _size = 0;
    size_t _cap = 0;
};

template <typename T>
Unordered_set<T>::Unordered_set(const Unordered_set<T> &rhs)
{
    copy(rhs);
}
template <typename T>
Unordered_set<T>::Unordered_set(Unordered_set<T> &&tmp)
{
    _size = tmp._size;
    _cap = tmp._cap;
    _arr = tmp._arr;
    tmp._size = 0;
    tmp._cap = 0;
    tmp._arr = nullptr;
}

template <typename T>
Unordered_set<T>::Unordered_set(std::initializer_list<T> list)
{
    for (auto el : list)
    {
        insert(el);
    }
}

template <typename T>
Unordered_set<T>::~Unordered_set()
{
    delete[] _arr;
}

// insert
template <typename T>
bool Unordered_set<T>::insert(const T &el)
{
    if (search(el))
    {
        return false;
    }

    // load_factor = (float)(_size / _cap) and load_factor >= 0.7;
    if (_cap == 0 || ((float)(_size + 1) / _cap) >= 0.7)
    {
        reserve(_cap ? _cap * 1.8 : 7);
    }

    size_t key = hash(el) % _cap;
    _arr[key].push_front(el);
    _size++;
    return true;
}

// delete
template <typename T>
void Unordered_set<T>::remove(const T &el)
{
    std::forward_list<T> &li = _arr[hash(el) % _cap];
    li.remove(el);
}

// methods
template <typename T>
bool Unordered_set<T>::search(const T &Key)
{
    if (_arr)
    {
        std::forward_list<T> li = _arr[hash(Key) % _cap];

        for (T el : li)
        {
            if (el == Key)
            {
                return true;
            }
        }
    }
    return false;
}

template <typename T>
bool Unordered_set<T>::empty()
{
    return _size == 0;
}

template <typename T>
void Unordered_set<T>::clear()
{
    for (int i = 0; i < _cap; ++i)
    {
        _arr[i].clear();
    }
}

// getters
template <typename T>
size_t Unordered_set<T>::size()
{
    return _size;
}

template <typename T>
size_t Unordered_set<T>::capacity()
{
    return _cap;
}

template <typename T>
Unordered_set<T> &Unordered_set<T>::operator=(const Unordered_set<T> &rhs)
{
    if (this != &rhs)
    {
        delete[] _arr;
        copy(rhs);
    }

    return *this;
}

template <typename T>
Unordered_set<T> &Unordered_set<T>::operator=(Unordered_set<T> &&tmp)
{
    if (this != &tmp)
    {
        _size = tmp._size;
        _cap = tmp._cap;
        _arr = tmp._arr;
        tmp._size = 0;
        tmp._cap = 0;
        tmp._arr = nullptr;
    }

    return *this;
}

template <typename T>
void Unordered_set<T>::reserve(int newCap)
{
    if (newCap > _cap)
    {
        std::forward_list<T> *tmpArr = new std::forward_list<T>[newCap];

        // rehash
        for (int i = 0; i < _cap; ++i)
        {
            for (auto el : _arr[i])
            {
                size_t newKey = hash(el) % newCap;
                tmpArr[newKey].push_front(el);
            }
        }

        delete[] _arr;
        _cap = newCap;
        _arr = tmpArr;
    }
}

template <>
size_t Unordered_set<std::string>::hash(std::string s)
{
    int hash_value = 2166136231u;
    for (char c : s)
    {
        hash_value ^= c;
        hash_value *= 16777619;
    }
    return hash_value;
}
template <>
size_t Unordered_set<int>::hash(int key)
{
    key = (key ^ 61) ^ (key >> 16);
    key = ~key + (key << 15);
    key = key ^ (key >> 12);
    key = key + (key << 2);
    key = key ^ (key >> 4);
    key = key * 2057;
    key = key ^ (key >> 16);

    return key;
}

template <typename T>
void Unordered_set<T>::copy(const Unordered_set<T> &rhs)
{
    _cap = rhs._cap;
    _size = rhs._size;
    _arr = new std::forward_list<T>[_cap];

    for (int i = 0; i < rhs._cap; i++)
    {
        _arr[i] = rhs._arr[i];
    }
}

template <typename T>
void Unordered_set<T>::print()
{
    for (int i = 0; i < _cap; ++i)
    {
        std::cout << i << ": ";
        for (auto el : _arr[i])
        {
            std::cout << el << " -> ";
        }
        std::cout << " \n";
    }
}

#endif //  UNORDERED_SET_H