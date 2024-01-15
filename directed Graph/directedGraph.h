#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H
#include <vector>
#include <queue>
#include <stack>
#include <iostream>

class DirectedGraph // directed graph
{
public:
    DirectedGraph(const int N);
    ~DirectedGraph();

    void add_edge(int u, int v);

    void BFS(); // O(V + E)
    void DFS(); // O(V + E)
    bool detect_circle();
    std::vector<std::vector<int>> find_all_path(int src, int dst);
    void topological_sort();

    void print();

private:
    void find_path(int u, int dst, std::vector<bool> &visited, std::vector<int> &v, std::vector<std::vector<int>> &ans);
    bool is_cyclic_util(int v, std::vector<bool> &visited, std::vector<bool> &onStack);
    void topological_sort_util(int v, std::vector<bool> &visited, std::stack<int> &Stack);

private:
    std::vector<int> *_graph;
    const size_t _size; // Vertex size
};

DirectedGraph::DirectedGraph(const int N) : _size(N)
{
    _graph = new std::vector<int>[N];
}

DirectedGraph::~DirectedGraph()
{
    delete[] _graph;
}

void DirectedGraph::add_edge(int u, int v)
{
    if (u >= _size || v >= _size)
    {
        throw std::out_of_range("error:: out of range");
    }

    // directed graph
    _graph[u].push_back(v);
}

std::vector<std::vector<int>> DirectedGraph::find_all_path(int src, int dst)
{
    std::vector<std::vector<int>> ans;
    std::vector<int> v;
    std::vector<bool> visited(_size, false);

    find_path(src, dst, visited, v, ans);

    return ans;
}

void DirectedGraph::find_path(int u, int dst, std::vector<bool> &visited, std::vector<int> &v, std::vector<std::vector<int>> &ans)
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

void DirectedGraph::topological_sort()
{
    std::stack<int> stack;
    std::vector<bool> visited(_size, false);

    for (int i = 0; i < _size; ++i)
    {
        if (!visited[i])
        {
            topological_sort_util(i, visited, stack);
        }
    }
    while (!stack.empty())
    {
        std::cout << stack.top() << " ";
        stack.pop();
    }
}

void DirectedGraph::topological_sort_util(int v, std::vector<bool> &visited, std::stack<int> &stack)
{
    visited[v] = true;

    for (int neighbor : _graph[v])
    {
        if (!visited[neighbor])
        {
            topological_sort_util(neighbor, visited, stack);
        }
    }

    stack.push(v);
}

void DirectedGraph::BFS()
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

void DirectedGraph::DFS()
{
    std::vector<bool> visited(_size, false);
    for (int i = 0; i < _size; ++i) // if have componetns
    {
        if (!visited[i])
        {
            std::stack<int> s;
            s.push(i);
            visited[i] = true;

            while (!s.empty())
            {
                int x = s.top();
                std::cout << x << " ";
                s.pop();

                for (auto el : _graph[x])
                {
                    if (!visited[el])
                    {
                        visited[el] = true;
                        s.push(el);
                    }
                }
            }
        }
    }
}

bool DirectedGraph::detect_circle()
{
    std::vector<bool> visited(_size, false);
    std::vector<bool> onStack(_size, false);

    for (int i = 0; i < _size; ++i) // if have componetns
    {
        if (!visited[i])
        {
            if (is_cyclic_util(i, visited, onStack))
            {
                return true;
            }
        }
    }
    return false;
}

bool DirectedGraph::is_cyclic_util(int v, std::vector<bool> &visited, std::vector<bool> &onStack)
{
    visited[v] = true;
    onStack[v] = true;

    for (int neighbor : _graph[v])
    {
        if (!visited[neighbor])
        {
            if (is_cyclic_util(neighbor, visited, onStack)) // dfs
            {
                return true;
            }
        }
        else if (onStack[neighbor])
        {
            return true;
        }
    }

    onStack[v] = false;
    return false;
}

void DirectedGraph::print()
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

#endif // DIRECTEDGRAPH_H