#include <iostream>
#include "BSTree.h"

int main()
{

    BSTree<int> bs = {50, 40, 55, 45, 30, 52, 999,53};

    // std::cout << bs.get_height();

    // bs.remove(50);
    bs.print2D();
}