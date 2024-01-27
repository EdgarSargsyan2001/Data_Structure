#ifndef WEIGHTEDGRAPH_H
#define WEIGHTEDGRAPH_H
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <climits>

class WeightedGraph // directed graph
{

public:
    WeightedGraph(const int N);
    ~WeightedGraph();

    void add_edge(int u, int v, int weight);

    // find shortest paht using topological sort
    void shortestPath(int source);
    void topologicalSortUtil(int v, std::vector<bool> &visited, std::stack<int> &Stack);

    void dijkstra(int source); // O((V + E) * log(V))
    void bellman(int source);  // algorithm shortest path

    void print();

private:
    std::vector<std::pair<int, int>> *_graph;
    const size_t _size; // Vertex size
};

WeightedGraph::WeightedGraph(const int N) : _size(N)
{
    _graph = new std::vector<std::pair<int, int>>[N];
}

WeightedGraph::~WeightedGraph()
{
    delete[] _graph;
}

void WeightedGraph::add_edge(int u, int v, int weight)
{
    if (u >= _size || v >= _size)
    {
        throw std::out_of_range("error:: out of range");
    }

    // directed graph
    _graph[u].push_back({v, weight});
}

void WeightedGraph::shortestPath(int s)
{
    std::stack<int> Stack;
    std::vector<bool> visited(_size, false);

    for (int i = 0; i < _size; ++i)
    {
        if (!visited[i])
        {
            topologicalSortUtil(i, visited, Stack);
        }
    }

    std::vector<int> dist(_size, INT_MAX);
    dist[s] = 0;

    while (!Stack.empty())
    {
        int u = Stack.top();
        Stack.pop();

        if (dist[u] != INT_MAX)
        {
            for (auto pair : _graph[u])
            {
                if (dist[pair.first] > dist[u] + pair.second) // pari.first -> vertex , pair.second -> weight
                {
                    dist[pair.first] = dist[u] + pair.second;
                }
            }
        }
    }

    for (int i = 0; i < _size; i++)
    {
        (dist[i] == INT_MAX) ? std::cout << "INF " : std::cout << dist[i] << " ";
    }
}

void WeightedGraph::topologicalSortUtil(int v, std::vector<bool> &visited, std::stack<int> &Stack)
{
    visited[v] = true;

    for (auto pair : _graph[v])
    {
        if (!visited[pair.first])
        {
            topologicalSortUtil(pair.first, visited, Stack);
        }
    }

    Stack.push(v);
}

void WeightedGraph::dijkstra(int source)
{
    std::vector<int> distance(_size, INT_MAX);
    distance[source] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        for (auto pair : _graph[u])
        {
            int v = pair.first;
            int weight = pair.second;

            if (distance[v] > distance[u] + weight)
            {
                distance[v] = distance[u] + weight;
                pq.push({distance[v], v});
            }
        }
    }
    std::cout << "Shortest distances from source 'dijkstra'" << source << ":\n";
    for (int i = 0; i < _size; ++i)
    {
        std::cout << "Vertex " << i << ": " << distance[i] << '\n';
    }
}

void WeightedGraph::bellman(int source)
{
    std::vector<int> distance(_size, INT_MAX);
    distance[source] = 0;

    for (int u = 0; u < _size; ++u)
    {
        for (auto pair : _graph[u])
        {
            int v = pair.first;
            int weight = pair.second;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
            {
                distance[v] = distance[u] + weight;
            }
        }
    }

    for (int u = 0; u < _size; ++u)
    {
        for (auto pair : _graph[u])
        {
            int v = pair.first;
            int weight = pair.second;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v])
            {
                printf("Graph contains negative weight cycle");
                return; 
            }
        }
    }

    std::cout << "Shortest distances from source 'bellman'" << source << ":\n";
    for (int i = 0; i < _size; ++i)
    {
        std::cout << "Vertex " << i << ": " << distance[i] << '\n';
    }
}

void WeightedGraph::print()
{
    for (int i = 0; i < _size; ++i)
    {
        std::cout << i << " ";
        for (auto pair : _graph[i])
        {
            std::cout << pair.first << " weight " << pair.second << " : ";
        }
        std::cout << "\n";
    }
}

#endif // WEIGHTEDGRAPH_H