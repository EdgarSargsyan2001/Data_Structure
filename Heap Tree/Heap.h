#ifndef HEAP_H
#define HEAP_H
#include <iostream>
#include <queue>

template <typename T>
struct Node
{
    Node(T v, Node<T> *p = nullptr, Node<T> *l = nullptr, Node<T> *r = nullptr) : val(v), parent(p), left(l), right(r) {}
    T val;
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;
};

template <typename T>
class Heap
{
public:
    Heap() = default;
    Heap(std::initializer_list<T> li);
    ~Heap();

    // insert
    void push(T val);

    // delete
    void pop();

    // methods
    bool empty();

    // getters
    T top() const;
    size_t size() const;

private:
    void heapify_up(Node<T> *);
    void heapify_down(Node<T> *);
    void delete_all(Node<T> *r);
    Node<T> *last_node();

private:
    Node<T> *_root = nullptr;
    size_t _size = 0;
};

template <typename T>
Heap<T>::Heap(std::initializer_list<T> li)
{
    for (T el : li)
    {
        push(el);
    }
}
template <typename T>
Heap<T>::~Heap()
{
    delete_all(_root);
    _root = nullptr;
}

template <typename T>
bool Heap<T>::empty()
{
    return _root == nullptr;
}

template <typename T>
T Heap<T>::top() const
{
    return _root->val;
}

template <typename T>
size_t Heap<T>::size() const
{
    return _size;
}

template <typename T>
void Heap<T>::push(T val)
{
    if (_root == nullptr)
    {
        _root = new Node<T>(val);
    }
    else
    {
        Node<T> *node = nullptr;
        std::queue<Node<T> *> q;
        q.push(_root);
        while (!q.empty())
        {
            Node<T> *curr = q.front();
            if (!curr->left)
            {
                node = new Node<T>(val, curr);
                curr->left = node;
                break;
            }
            else if (!curr->right)
            {
                node = new Node<T>(val, curr);
                curr->right = node;
                break;
            }
            else
            {
                q.push(curr->left);
                q.push(curr->right);
            }
            q.pop();
        }

        heapify_up(node);
    }
    _size++;
}

template <typename T>
void Heap<T>::pop()
{
    if (_size == 1)
    {
        delete _root;
        _root = nullptr;
    }
    else
    {
        Node<T> *lastNode = last_node();

        std::swap(lastNode->val, _root->val);
        if (lastNode->parent->left == lastNode)
        {
            lastNode->parent->left = nullptr;
        }
        else
        {
            lastNode->parent->right = nullptr;
        }

        delete lastNode;
        heapify_down(_root);
    }
    _size--;
}

template <typename T>
void Heap<T>::heapify_up(Node<T> *node)
{
    if (node->parent != nullptr && node->parent->val < node->val)
    {
        std::swap(node->parent->val, node->val);
        heapify_up(node->parent);
    }
}

template <typename T>
void Heap<T>::heapify_down(Node<T> *node)
{
    Node<T> *maxNode = node;
    if (node->left && node->left->val > maxNode->val)
    {
        maxNode = node->left;
    }
    if (node->right && node->right->val > maxNode->val)
    {
        maxNode = node->right;
    }
    if (maxNode != node)
    {
        std::swap(maxNode->val, node->val);
        heapify_down(maxNode);
    }
}
template <typename T>
Node<T> *Heap<T>::last_node()
{
    std::queue<Node<T> *> q;
    q.push(_root);
    while (!q.empty())
    {
        Node<T> *curr = q.front();
        q.pop();
        if (!curr->left && !curr->right && q.empty())
        {
            return curr;
        }
        else
        {
            if (curr->left)
                q.push(curr->left);

            if (curr->right)
                q.push(curr->right);
        }
    }
    return nullptr;
}

template <typename T>
void Heap<T>::delete_all(Node<T> *t)
{
    if (t == nullptr)
    {
        return;
    }
    delete_all(t->left);
    delete_all(t->right);
    delete t;
}

#endif // HEAP_H