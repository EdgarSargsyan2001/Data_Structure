#include <iostream>
#include "bitset.h"

int main()
{
    Bitset<8> f;
    f.set(0);
    f.set(1);
    f.set(2);
    
    f.print();
}
