#include <iostream>
#include "directedGraph.h"

int main()
{
    DirectedGraph g(8);
    g.add_edge(0, 1);
    g.add_edge(1, 2);
    g.add_edge(2, 0);
    g.add_edge(5, 6);
    g.add_edge(6, 4);
    g.add_edge(4, 5);
    g.add_edge(3, 4);
    g.add_edge(3, 7);
    g.add_edge(7, 5);
    g.add_edge(7, 3);

    // g.add_edge(3, 0);

    // g.DFS();
    // std::cout << "\n";
    // g.BFS();

    // g.print();
    // std::cout << std::boolalpha << g.detect_circle() << '\n';

    // g.topological_sort();
    // g.kohns_algorithm();

    for (auto v : g.tarjan_algorithm()) // find Strongly Connected Components
    {
        for (int i : v)
        {
            std::cout << i << " ";
        }
        std::cout << '\n';
    }

    std::cout << "ok";
}