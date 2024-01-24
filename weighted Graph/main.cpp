#include <iostream>
#include "weightedGraph.h"

int main()
{
    WeightedGraph g(6);
    g.add_edge(0, 1, 5);
    g.add_edge(0, 2, 3);
    g.add_edge(1, 3, 6);
    g.add_edge(1, 2, 2);
    g.add_edge(2, 4, 4);
    g.add_edge(2, 5, 2);
    g.add_edge(2, 3, 7);
    g.add_edge(3, 4, 1);
    g.add_edge(4, 5, 2);

    // g.print();
    // g.shortestPath(0);
    g.dijkstra(0);
    std::cout << "ok";
}