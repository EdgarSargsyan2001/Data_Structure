#include <iostream>
#include "RBTree.h"

int main()
{
    RBTree<int> t = {8, 3, 44, 88, 16, 20, 15};

    t.inorder();
    t.print2D();
    std::cout << "\nok\n";
}
