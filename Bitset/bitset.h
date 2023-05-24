#ifndef BITSET_H
#define BITSET_H
#include <iostream>
typedef unsigned long long ull;

template <ull bit_count>
class Bitset
{
public:
    friend std::ostream &operator<<(std::ostream &os, const Bitset<bit_count> &b)
    {
        for (int i = bit_count - 1; i >= 0; --i)
        {
            os << b[i];
        }
        return os;
    }

public:
    Bitset();
    ~Bitset();
    // === Modifiers ===
    Bitset &set();
    Bitset &set(ull);
    Bitset &reset();
    Bitset &reset(ull);
    Bitset &flip();
    Bitset &flip(ull);

    //
    bool operator[](ull) const;
    // === bitwise operators ===
    Bitset<bit_count> operator&(Bitset<bit_count> &rhs);
    Bitset<bit_count> operator|(Bitset<bit_count> &rhs);
    Bitset<bit_count> operator^(Bitset<bit_count> &rhs);
    //
    // when bitset's bit count is not equal; it returns the largest bit count
    template <ull bit_count2>
    Bitset<((bit_count > bit_count2) ? bit_count : bit_count2)> operator&(Bitset<bit_count2> &rhs);
    template <ull bit_count2>
    Bitset<((bit_count > bit_count2) ? bit_count : bit_count2)> operator|(Bitset<bit_count2> &rhs);
    template <ull bit_count2>
    Bitset<((bit_count > bit_count2) ? bit_count : bit_count2)> operator^(Bitset<bit_count2> &rhs);

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
// ========  Modifiers  =======
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
Bitset<bit_count> &Bitset<bit_count>::flip()
{
    for (int i = 0; i < bit_count; ++i)
    {
        (this->operator[](i)) ? this->reset(i) : this->set(i);
    }
    return *this;
}
template <ull bit_count>
Bitset<bit_count> &Bitset<bit_count>::flip(ull n)
{
    if (n >= 0 && n < bit_count)
    {
        (this->operator[](n)) ? this->reset(n) : this->set(n);
        return *this;
    }
    throw std::out_of_range("invalid position\n");
}

// =========== $$$ ===============

template <ull bit_count>
bool Bitset<bit_count>::operator[](ull pos) const
{
    return (_arr[pos / (sizeof(char) * 8)] >> pos % (sizeof(char) * 8)) & 1;
}
template <ull bit_count>
Bitset<bit_count> Bitset<bit_count>::operator&(Bitset<bit_count> &rhs)
{
    Bitset<bit_count> ans;
    for (int i = 0; i < bit_count; ++i)
    {
        (this->operator[](i) == 1 && rhs[i] == 1)
            ? ans.set(i)
            : ans.reset(i);
    }
    return ans;
}

// =============   when bitset's bit count is not equal; it returns the largest bit count  ==================
template <ull bit_count>
template <ull bit_count2>
Bitset<((bit_count > bit_count2) ? bit_count : bit_count2)> Bitset<bit_count>::operator&(Bitset<bit_count2> &rhs)
{
    // find smoller of two
    Bitset<((bit_count > bit_count2) ? bit_count : bit_count2)> ans;
    for (int i = 0; i < ((bit_count > bit_count2) ? bit_count2 : bit_count); ++i)
    {
        if (this->operator[](i) == 1 && rhs[i] == 1)
            ans.set(i);
    }

    return ans;
}

template <ull bit_count>
template <ull bit_count2>
Bitset<((bit_count > bit_count2) ? bit_count : bit_count2)> Bitset<bit_count>::operator|(Bitset<bit_count2> &rhs)
{
    Bitset<((bit_count > bit_count2) ? bit_count : bit_count2)> ans;
    // find smoller of two
    if (bit_count > bit_count2)
    {
        int i = 0;
        while (i < bit_count2)
        {
            if (this->operator[](i) == 1 || rhs[i] == 1)
                ans.set(i);
            ++i;
        }
        while (i < bit_count)
        {
            if (this->operator[](i))
                ans.set(i);
            ++i;
        }
    }
    else
    {
        int i = 0;
        while (i < bit_count)
        {
            if (this->operator[](i) == 1 || rhs[i] == 1)
                ans.set(i);
            ++i;
        }
        while (i < bit_count2)
        {
            if (rhs[i])
                ans.set(i);
            ++i;
        }
    }

    return ans;
}
template <ull bit_count>
template <ull bit_count2>
Bitset<((bit_count > bit_count2) ? bit_count : bit_count2)> Bitset<bit_count>::operator^(Bitset<bit_count2> &rhs)
{
    Bitset<((bit_count > bit_count2) ? bit_count : bit_count2)> ans;
    if (bit_count > bit_count2)
    {
        int i = 0;
        while (i < bit_count2)
        {
            if (this->operator[](i) != rhs[i])
                ans.set(i);
            ++i;
        }
        while (i < bit_count)
        {
            if (this->operator[](i))
                ans.set(i);
            ++i;
        }
    }
    else
    {
        int i = 0;
        while (i < bit_count)
        {
            if (this->operator[](i) != rhs[i])
                ans.set(i);
            ++i;
        }
        while (i < bit_count2)
        {
            if (rhs[i])
                ans.set(i);
            ++i;
        }
    }

    return ans;
}

// ============   $$$ ==============

template <ull bit_count>
Bitset<bit_count> Bitset<bit_count>::operator|(Bitset<bit_count> &rhs)
{
    Bitset<bit_count> ans;
    for (int i = 0; i < bit_count; ++i)
    {
        (this->operator[](i) == 1 || rhs[i] == 1)
            ? ans.set(i)
            : ans.reset(i);
    }
    return ans;
}
template <ull bit_count>
Bitset<bit_count> Bitset<bit_count>::operator^(Bitset<bit_count> &rhs)
{
    Bitset<bit_count> ans;
    for (int i = 0; i < bit_count; ++i)
    {
        (this->operator[](i) != rhs[i])
            ? ans.set(i)
            : ans.reset(i);
    }
    return ans;
}

#endif