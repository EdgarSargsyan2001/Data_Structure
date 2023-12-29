#include <iostream>
#include "RBTree.h"

int main()
{
    RBTree<int> t = {8, 3, 44, 88, 16, 20, 15,5,6,1,7};

    // t.inorder();
    // t.remove(8);
    t.remove(16);
    t.remove(8);
    t.remove(7);
    t.remove(6);
    t.remove(5);

    t.print2D();
    std::cout << "\nok\n";
}
