#include <iostream>
#include "BSTree.h"
#include <vector>
#include <stack>
#include <queue>

template <typename T>
std::vector<T> inorderTraversal(Node<T> *root);

template <typename T>
std::vector<T> preorderTraversal(Node<T> *root);

template <typename T>
std::vector<T> postorderTraversal(Node<T> *root);

template <typename T>
std::vector<T> levelTraversal(Node<T> *root);

int main()
{

    BSTree<int> bs = {50, 40, 55, 45, 30, 52, 999, 53, 20};
    // std::cout << bs.get_height();

    // bs.remove(50);
    bs.print2D();
    std::cout << '\n';
    for (auto el : levelTraversal(bs.root()))
    {
        std::cout << el << " ";
    }
    // std::cout << '\n';
    // bs.postorder();
}

template <typename T>
std::vector<T> inorderTraversal(Node<T> *root)
{
    std::stack<Node<T> *> s;
    std::vector<T> v;
    Node<T> *curr = root;

    while (curr || !s.empty())
    {
        while (curr)
        {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();
        v.push_back(curr->data);
        curr = curr->right;
    }
    return v;
}

template <typename T>
std::vector<T> preorderTraversal(Node<T> *root)
{
    std::stack<Node<T> *> s;
    std::vector<T> v;

    s.push(root);
    while (!s.empty())
    {
        Node<T> *curr = s.top();
        s.pop();
        std::cout << curr->data << " ";
        if (curr->right)
            s.push(curr->right);
        if (curr->left)
            s.push(curr->left);
    }

    return v;
}

template <typename T>
std::vector<T> postorderTraversal(Node<T> *root)
{
    std::stack<Node<T> *> s1;
    std::stack<Node<T> *> s2;

    s1.push(root);
    while (!s1.empty())
    {
        Node<T> *curr = s1.top();
        s1.pop();
        s2.push(curr);

        if (curr->left)
            s1.push(curr->left);

        if (curr->right)
            s1.push(curr->right);
    }

    std::vector<T> v;
    while (!s2.empty())
    {
        v.push_back(s2.top()->data);
        s2.pop();
    }

    return v;
}

template <typename T>
std::vector<T> levelTraversal(Node<T> *root)
{
    std::queue<Node<T> *> q;
    std::vector<T> v;
    q.push(root);

    while (!q.empty())
    {
        Node<T> *curr = q.front();
        q.pop();
        v.push_back(curr->data);
        if (curr->left)
            q.push(curr->left);

        if (curr->right)
            q.push(curr->right);
    }
    return v;
}