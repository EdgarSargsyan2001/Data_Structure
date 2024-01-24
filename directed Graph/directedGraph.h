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
    void topological_sort();
    std::vector<int> kohns_algorithm();
    std::vector<std::vector<int>> find_all_path(int src, int dst);

    // ===== find SCC =====

    // Kosaraju algorithm
    std::vector<std::vector<int>> kosaraju_algorithm(); // O(3 * (V + E))
    void fill_order(int v, std::vector<bool> &visited, std::stack<int> &Stack);
    void DFS_util(int v, std::vector<bool> &visited, std::vector<int> &component);

    // Tarjan algorithm
    std::vector<std::vector<int>> tarjan_algorithm(); // O (V + E)
    void tarjan_util(int v, std::vector<int> &disc, std::vector<int> &low, std::stack<int> &Stack, std::vector<bool> &onStack, std::vector<std::vector<int>> &scc);

    void print();

private:
    void find_path(int u, int dst, std::vector<bool> &visited, std::vector<int> &v, std::vector<std::vector<int>> &ans);
    bool is_cyclic_util(int v, std::vector<bool> &visited, std::vector<bool> &onStack);
    bool topological_sort_util(int v, std::vector<bool> &visited, std::vector<bool> &onStack, std::stack<int> &Stack);

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
    std::vector<bool> onStack(_size, false);

    for (int i = 0; i < _size; ++i)
    {
        if (!visited[i])
        {
            if (topological_sort_util(i, visited, onStack, stack))
            {
                std::cout << "has a circle: can't sort topological\n";
                return;
            }
        }
    }
    while (!stack.empty())
    {
        std::cout << stack.top() << " ";
        stack.pop();
    }
}

bool DirectedGraph::topological_sort_util(int v, std::vector<bool> &visited, std::vector<bool> &onStack, std::stack<int> &stack)
{
    visited[v] = true;
    onStack[v] = true;

    for (int neighbor : _graph[v])
    {
        if (!visited[neighbor])
        {
            if (topological_sort_util(neighbor, visited, onStack, stack))
            {
                return true;
            }
        }
        else if (onStack[neighbor])
        {
            return true; // has a circle
        }
    }

    onStack[v] = false;
    stack.push(v);
    return false;
}

std::vector<int> DirectedGraph::kohns_algorithm()
{
    int inDegree[_size] = {0};
    for (int i = 0; i < _size; ++i)
    {
        for (int vertex : _graph[i])
        {
            ++inDegree[vertex];
        }
    }

    std::queue<int> q;
    for (int i = 0; i < _size; ++i)
    {
        if (inDegree[i] == 0)
        {
            q.push(i);
        }
    }

    std::vector<int> ans;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        ans.push_back(v);

        for (int u : _graph[v])
        {
            --inDegree[u];
            if (inDegree[u] == 0)
            {
                q.push(u);
            }
        }
    }
    if (ans.size() != _size)
    {
        std::cout << "There exists a cycle in the graph\n";
        return {};
    }

    return ans;
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

// ===============  kosaraju_algorithm ================ // find Strongly Connected Components
std::vector<std::vector<int>> DirectedGraph::kosaraju_algorithm()
{
    // Step 1: Fill the stack by using DFS
    std::stack<int> Stack;
    std::vector<bool> visited(_size, false);
    for (int i = 0; i < _size; i++)
    {
        if (!visited[i])
        {
            fill_order(i, visited, Stack);
        }
    }

    // Step 2: Transpose the graph
    DirectedGraph transposed_graph(_size);
    for (int v = 0; v < _size; ++v)
    {
        for (int u : _graph[v])
        {
            transposed_graph.add_edge(u, v);
        }
    }

    // Step 3: Perform DFS on the transposed graph and store strongly connected components

    std::vector<std::vector<int>> SCC; // Strongly Connected Components
    visited.assign(_size, false);
    while (!Stack.empty())
    {
        int v = Stack.top();
        Stack.pop();
        if (!visited[v])
        {
            std::vector<int> component;
            transposed_graph.DFS_util(v, visited, component);
            SCC.push_back(component);
        }
    }
    return SCC;
}
void DirectedGraph::fill_order(int v, std::vector<bool> &visited, std::stack<int> &Stack)
{
    visited[v] = true;
    for (int u : _graph[v])
    {
        if (!visited[u])
        {
            fill_order(u, visited, Stack);
        }
    }
    Stack.push(v);
}
void DirectedGraph::DFS_util(int v, std::vector<bool> &visited, std::vector<int> &component)
{
    visited[v] = true;
    component.push_back(v);
    for (int u : _graph[v])
    {
        if (!visited[u])
        {
            DFS_util(u, visited, component);
        }
    }
}

// ====================== Tarjan algorithm ======================
std::vector<std::vector<int>> DirectedGraph::tarjan_algorithm()
{
    std::vector<int> disc(_size, -1); // Discovery time of vertices
    std::vector<int> low(_size, -1);  // Earliest visited vertex reachable from subtree rooted with the current vertex
    std::stack<int> Stack;
    std::vector<bool> onStack(_size, false); // To keep track of whether a vertex is on the stack
    std::vector<std::vector<int>> scc;

    for (int i = 0; i < _size; ++i)
    {
        if (disc[i] == -1)
        {
            tarjan_util(i, disc, low, Stack, onStack, scc);
        }
    }
    return scc;
}
void DirectedGraph::tarjan_util(int v, std::vector<int> &disc, std::vector<int> &low, std::stack<int> &Stack, std::vector<bool> &onStack, std::vector<std::vector<int>> &scc)
{
    static int time = 0;
    disc[v] = low[v] = time++;
    onStack[v] = true;
    Stack.push(v);

    for (int u : _graph[v])
    {
        if (disc[u] == -1)
        {
            tarjan_util(u, disc, low, Stack, onStack, scc);
            low[v] = std::min(low[v], low[u]);
        }
        else if (onStack[u])
        {
            low[v] = std::min(low[v], disc[u]);
        }
    }

    if (low[v] == disc[v])
    {
        std::vector<int> component;
        while (1)
        {
            int u = Stack.top();
            Stack.pop();
            onStack[u] = false;
            component.push_back(u);

            if (u == v)
                break;
        }
        scc.push_back(component);
    }
}

#endif // DIRECTEDGRAPH_H