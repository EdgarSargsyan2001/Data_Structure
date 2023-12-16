#include <iostream>
#include "AVLTree.h"
#include <vector>

int main()
{

    AVLTree<int> bs = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // std::cout << bs.get_height();

    bs.remove(5);
    bs.remove(3);
    bs.remove(1);

    bs.print2D();
    std::cout << '\n';

    // bs.inorder();

    // std::cout << '\n';
    // bs.postorder();
}
