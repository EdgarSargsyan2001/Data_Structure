#ifndef UNORDERED_MAP_H
#define UNORDERED_MAP_H
#include <iostream>
#include <forward_list>

template <typename T, typename U>
class Unordered_map
{
public:
    Unordered_map(){};
    Unordered_map(const Unordered_map<T, U> &);
    Unordered_map(Unordered_map<T, U> &&);
    Unordered_map(std::initializer_list<std::pair<T, U>> list);
    ~Unordered_map();

    // insert
    bool insert(const std::pair<T, U> &p);

    // delete
    void remove(const T &key);

    // methods
    bool search(const T &key);
    U *find(const T &key);
    bool empty();
    void clear();
    void print();

    // getters
    size_t size();
    size_t capacity();

    // operators
    Unordered_map<T, U> &operator=(const Unordered_map<T, U> &);
    Unordered_map<T, U> &operator=(Unordered_map<T, U> &&);

private:
    void reserve(int count);

    size_t hash(T el);

    void copy(const Unordered_map<T, U> &);

private:
    std::forward_list<std::pair<T, U>> *_arr = nullptr;
    size_t _size = 0;
    size_t _cap = 0;
};

template <typename T, typename U>
Unordered_map<T, U>::Unordered_map(const Unordered_map<T, U> &rhs)
{
    copy(rhs);
}
template <typename T, typename U>
Unordered_map<T, U>::Unordered_map(Unordered_map<T, U> &&tmp)
{
    _size = tmp._size;
    _cap = tmp._cap;
    _arr = tmp._arr;
    tmp._size = 0;
    tmp._cap = 0;
    tmp._arr = nullptr;
}

template <typename T, typename U>
Unordered_map<T, U>::Unordered_map(std::initializer_list<std::pair<T, U>> list)
{
    for (auto el : list)
    {
        insert(el);
    }
}

template <typename T, typename U>
Unordered_map<T, U>::~Unordered_map()
{
    delete[] _arr;
}

// insert
template <typename T, typename U>
bool Unordered_map<T, U>::insert(const std::pair<T, U> &pi)
{

    // load_factor = (float)(_size / _cap) and load_factor >= 0.7;
    if (search(pi.first))
    {
        return false;
    }

    if (_cap == 0 || ((float)(_size + 1) / _cap) >= 0.7)
    {
        reserve(_cap ? _cap * 1.8 : 7);
    }

    size_t key = hash(pi.first) % _cap;
    _arr[key].push_front(pi);
    _size++;
    return true;
}

// delete
template <typename T, typename U>
void Unordered_map<T, U>::remove(const T &key)
{
    if (_arr)
    {
        std::forward_list<std::pair<T, U>> &li = _arr[hash(key) % _cap];
        for (std::pair<T, U> pi : li)
        {
            if (pi.first == key)
            {
                li.remove(pi);
                break;
            }
        }
    }
}

// methods
template <typename T, typename U>
bool Unordered_map<T, U>::search(const T &key)
{
    if (_arr)
    {
        std::forward_list<std::pair<T, U>> li = _arr[hash(key) % _cap];

        for (std::pair<T, U> pi : li)
        {
            if (pi.first == key)
            {
                return true;
            }
        }
    }
    return false;
}

template <typename T, typename U>
U *Unordered_map<T, U>::find(const T &key)
{
    if (_arr)
    {
        std::forward_list<std::pair<T, U>> &li = _arr[hash(key) % _cap];

        for (auto it = li.begin(); it != li.end(); ++it)
        {
            if (it->first == key)
            {
                return &it->second;
            }
        }
    }
    return nullptr;
}

template <typename T, typename U>
bool Unordered_map<T, U>::empty()
{
    return _size == 0;
}

template <typename T, typename U>
void Unordered_map<T, U>::clear()
{
    for (int i = 0; i < _cap; ++i)
    {
        _arr[i].clear();
    }
}

// getters
template <typename T, typename U>
size_t Unordered_map<T, U>::size()
{
    return _size;
}

template <typename T, typename U>
size_t Unordered_map<T, U>::capacity()
{
    return _cap;
}

template <typename T, typename U>
Unordered_map<T, U> &Unordered_map<T, U>::operator=(const Unordered_map<T, U> &rhs)
{
    if (this != &rhs)
    {
        delete[] _arr;
        copy(rhs);
    }

    return *this;
}

template <typename T, typename U>
Unordered_map<T, U> &Unordered_map<T, U>::operator=(Unordered_map<T, U> &&tmp)
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

template <typename T, typename U>
void Unordered_map<T, U>::reserve(int newCap)
{
    if (newCap > _cap)
    {
        std::forward_list<std::pair<T, U>> *tmpArr = new std::forward_list<std::pair<T, U>>[newCap];

        // rehash
        for (int i = 0; i < _cap; ++i)
        {
            for (std::pair<T, U> el : _arr[i])
            {
                size_t newKey = hash(el.first) % newCap;
                tmpArr[newKey].push_front(el);
            }
        }

        delete[] _arr;
        _cap = newCap;
        _arr = tmpArr;
    }
}

// template <>
template <typename T, typename U>
size_t Unordered_map<T, U>::hash(T s)
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
size_t Unordered_map<int, std::string>::hash(int key)
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

template <typename T, typename U>
void Unordered_map<T, U>::copy(const Unordered_map<T, U> &rhs)
{
    _cap = rhs._cap;
    _size = rhs._size;
    _arr = new std::forward_list<T>[_cap];

    for (int i = 0; i < rhs._cap; i++)
    {
        _arr[i] = rhs._arr[i];
    }
}

template <typename T, typename U>
void Unordered_map<T, U>::print()
{
    for (int i = 0; i < _cap; ++i)
    {
        std::cout << i << ": ";
        for (std::pair<T, U> el : _arr[i])
        {
            std::cout << "{" << el.first << " , " << el.second << "} -> ";
        }
        std::cout << " \n";
    }
}

#endif // UNORDERED_MAP_H