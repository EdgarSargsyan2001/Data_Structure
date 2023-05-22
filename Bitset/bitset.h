#ifndef BITSET_H
#define BITSET_H
#include <iostream>
#include <cmath >
typedef unsigned long long ull;

template <ull bit_count>
class Bitset
{
    friend Bitset &operator&();

public:
    Bitset();
    ~Bitset();
    //
    Bitset &set();
    Bitset &set(ull);
    Bitset &reset();
    Bitset &reset(ull);

    //
    bool operator[](ull) const;

    //
    void print();

private:
    char *_arr;
    ull _size = 1;
};

template <ull bit_count>
Bitset<bit_count>::Bitset() : _arr(nullptr)
{
    if (bit_count > 8)
        _size = bit_count / (sizeof(char) * 8) + 1;

    _arr = {new char[_size]{0}};
}

template <ull bit_count>
Bitset<bit_count>::~Bitset()
{
    delete[] _arr;
}

template <ull bit_count>
Bitset<bit_count> &Bitset<bit_count>::set()
{

    for (int i = 0; i < _size; ++i)
        _arr[i] |= (1 << ((sizeof(char) * 8) + 1)) - 1;

    return *this;
}

template <ull bit_count>
Bitset<bit_count> &Bitset<bit_count>::set(ull n)
{
    if (n >= 0 && n < bit_count)
    {

        _arr[n / (sizeof(char) * 8)] |= (1 << n % (sizeof(char) * 8));
        return *this;
    }
    throw std::out_of_range("invalid position\n");
}

template <ull bit_count>
Bitset<bit_count> &Bitset<bit_count>::reset()
{

    for (int i = 0; i < _size; ++i)
        _arr[i] = 0;

    return *this;
}

template <ull bit_count>
Bitset<bit_count> &Bitset<bit_count>::reset(ull n)
{
    if (n >= 0 && n < bit_count)
    {
        _arr[n / (sizeof(char) * 8)] &= ~(1 << n % (sizeof(char) * 8));
        return *this;
    }
    throw std::out_of_range("invalid position\n");
}

template <ull bit_count>
bool Bitset<bit_count>::operator[](ull pos) const
{
    return (_arr[pos / (sizeof(char) * 8)] >> pos % (sizeof(char) * 8)) & 1;
}
// template <ull bit_count>
// Bitset &Bitset<bit_count>::operator&()
// {
// }

template <ull bit_count>
void Bitset<bit_count>::print()
{
    for (int i = _size - 1; i >= 0; --i)
    {
        for (int j = (sizeof(char) * 8) - 1; j >= 0; --j)
        {
            std::cout << ((_arr[i] >> j) & 1);
        }
    }
}

#endif