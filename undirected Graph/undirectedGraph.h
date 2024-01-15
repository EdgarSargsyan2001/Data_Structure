#ifndef UNDIRECTEDGRAPH_H
#define UNDIRECTEDGRAPH_H
#include <vector>
#include <queue>
#include <iostream>

class UndirectedGraph // undirected graph
{
public:
    UndirectedGraph(const int N);
    ~UndirectedGraph();

    void add_edge(int u, int v);

    void BFS(); // O(V + E)
    void DFS(); // O(V + E)
    bool detect_circle();
    std::vector<std::vector<int>> find_all_path(int src, int dst);

    void print();

private:
    void find_path(int u, int dst, std::vector<bool> &visited, std::vector<int> &v, std::vector<std::vector<int>> &ans);
    bool is_cyclic_util(int v, std::vector<bool> &visited, int parent);
    void DFS_util(int u, std::vector<bool> &visited);

private:
    std::vector<int> *_graph;
    const size_t _size; // Vertex size
};

UndirectedGraph::UndirectedGraph(const int N) : _size(N)
{
    _graph = new std::vector<int>[N];
}

UndirectedGraph::~UndirectedGraph()
{
    delete[] _graph;
}

void UndirectedGraph::add_edge(int u, int v)
{
    if (u >= _size || v >= _size)
    {
        throw std::out_of_range("error:: out of range");
    }

    // undirected graph
    _graph[u].push_back(v);
    _graph[v].push_back(u);
}

std::vector<std::vector<int>> UndirectedGraph::find_all_path(int src, int dst)
{
    std::vector<std::vector<int>> ans;
    std::vector<int> v;
    std::vector<bool> visited(_size, false);

    find_path(src, dst, visited, v, ans);

    return ans;
}

void UndirectedGraph::find_path(int u, int dst, std::vector<bool> &visited, std::vector<int> &v, std::vector<std::vector<int>> &ans)
{
    visited[u] = true;
    v.push_back(u);
    for (auto el : _graph[u])
    {
        if (!visited[el])
        {
            if (el == dst)
            {
                ans.push_back(v);
            }
            find_path(el, dst, visited, v, ans);
        }
    }
    v.pop_back();
    visited[u] = false;
}

void UndirectedGraph::BFS()
{
    std::vector<bool> visited(_size, false);

    for (int i = 0; i < _size; ++i) // if have componetns
    {
        if (!visited[i])
        {
            std::queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty())
            {
                int x = q.front();
                std::cout << x << " ";
                q.pop();

                for (auto el : _graph[x])
                {
                    if (!visited[el])
                    {
                        visited[el] = true;
                        q.push(el);
                    }
                }
            }
        }
    }
}

void UndirectedGraph::DFS()
{
    std::vector<bool> visited(_size, false);

    for (int i = 0; i < _size; ++i)
    {
        if (!visited[i])
        {
            DFS_util(i, visited);
        }
    }
}

void UndirectedGraph::DFS_util(int u, std::vector<bool> &visited)
{
    visited[u] = true;
    std::cout << u << " ";
    for (int neb : _graph[u])
    {
        if (!visited[neb])
        {
            DFS_util(neb, visited);
        }
    }
}

bool UndirectedGraph::detect_circle()
{
    std::vector<bool> visited(_size, false);
    for (int i = 0; i < _size; ++i) // if have componetns
    {
        if (!visited[i])
        {
            if (is_cyclic_util(i, visited, -1))
            {
                return true;
            }
        }
    }
    return false;
}

bool UndirectedGraph::is_cyclic_util(int v, std::vector<bool> &visited, int parent)
{
    visited[v] = true;

    for (int neighbor : _graph[v])
    {
        if (!visited[neighbor])
        {
            if (is_cyclic_util(neighbor, visited, v)) // dfs
            {
                return true;
            }
        }
        else if (neighbor != parent)
        {
            return true;
        }
    }

    return false;
}

void UndirectedGraph::print()
{
    for (int i = 0; i < _size; ++i)
    {
        std::cout << i << ": ";
        for (auto el : _graph[i])
        {
            std::cout << el << ", ";
        }
        std::cout << "\n";
    }
}

#endif // UNDIRECTEDGRAPH_H