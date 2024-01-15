#include <iostream>
#include "directedGraph.h"

int main()
{
    DirectedGraph g(6);
    g.add_edge(0, 1);
    g.add_edge(0, 2);
    g.add_edge(1, 3);
    g.add_edge(2, 4);
    g.add_edge(3, 5);

    // g.DFS();
    // std::cout << "\n";
    // g.BFS();

    // g.print();
    // std::cout << std::boolalpha << g.detect_circle() << '\n';

    g.topological_sort();

    std::cout << "ok";
}