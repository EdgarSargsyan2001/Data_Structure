#include <iostream>
#include "Bitset.h"

template<ull bit_count>
std::ostream &operator<<(std::ostream &os, const Bitset<bit_count> &b)
    {
        for (int i = bit_count - 1; i >= 0; --i)
        {
            os << b[i];
        }
        return os;
    }

int main()
{
    // ========= when bitset's bit count is equal ========
    // Bitset<8> set1;
    // set1.set(4);
    // set1.set(5);
    // set1.set(7);
    // std::cout << "set1 :        " << set1 << "\n";

    // Bitset<8> set2;
    // set2.set(4);
    // set2.set(5);
    // set2.set(7);
    // std::cout << "set2 :        " << set2 << "\n";

    // std::cout << "set1 & set2 : " << (set1 & set2) << "\n";
    // std::cout << "set1 | set2 : " << (set1 | set2) << "\n";
    // std::cout << "set1 ^ set2 : " << (set1 ^ set2) << "\n";

    // ========= when bitset's bit count is not equal ========

    Bitset<4> a;
    a.set();
    std::cout << "a :           " << a << "\n";
    Bitset<10> b;
    b.set(3);
    b.set(6);
    b.set(8);
    b.flip();
    std::cout << "b :     " << b << "\n";

    std::cout << "a & b : " << (a & b) << "\n";
    std::cout << "b | a : " << (b | a) << "\n";
    std::cout << "a ^ b : " << (a ^ b) << "\n";
    std::cout << "b -> count: " << b.count() << "\n";
}
