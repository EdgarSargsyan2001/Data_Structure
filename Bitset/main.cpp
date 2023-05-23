#include <iostream>
#include "bitset.h"

int main()
{
    Bitset<8> set1;
    set1.set(7);
    set1.set(1);
    set1.set(4);
    std::cout << "set1 :        " << set1 << "\n";

    Bitset<8> set2;
    set2.set(2);
    set2.set(0);
    set2.set();
    std::cout << "set2 :        " << set2 << "\n";

    std::cout << "set1 & set2 : " << (set1 & set2) << "\n";
    std::cout << "set1 | set2 : " << (set1 | set2) << "\n";
    std::cout << "set1 ^ set2 : " << (set1 ^ set2) << "\n";

    // =========
    // std::cout << "set1 & set2 : " << (set1.operator&(set2)) << "\n";
    // std::cout << "set1 & set2 : " << (set2.operator&(set1)) << "\n";
}
