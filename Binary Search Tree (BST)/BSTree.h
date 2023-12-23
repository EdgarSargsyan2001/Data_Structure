#ifndef BSTREE_H
#define BSTREE_H
#include <iostream>
#include <stack>

template <typename T>
struct Node
{
    Node(T d, Node<T> *l = nullptr, Node<T> *r = nullptr) : data(d), left(l), right(r) {}
    T data;
    Node<T> *left;
    Node<T> *right;
};

template <typename T>
class BSTree
{
public:
    BSTree() = default;
    BSTree(const BSTree &other);
    BSTree(BSTree &&rhs);
    BSTree(std::initializer_list<T>);
    ~BSTree();

    // insert
    void insert(const T &val);

    // delete
    void remove(const T &val);

    // methods
    bool search(const T &val);

    // iterations
    void inorder();   // l, root, r
    void preorder();  // root, l, r
    void postorder(); // l, r, root
    void levelOrder();

    // operators
    BSTree<T> &operator=(const BSTree &other);
    BSTree<T> &operator=(BSTree &&rhs);

    // gettres
    size_t get_height();
    Node<T> *get_predecessor(Node<T> *);
    Node<T> *get_successor(Node<T> *);

    Node<T> *root() { return _root; };
    void print2D();
    void print2DUtil(Node<T> *, int);

private:
    size_t get_height(Node<T> *);
    void inorder(Node<T> *);
    void preorder(Node<T> *);
    void postorder(Node<T> *);
    void levelOrder(Node<T> *root, int level);

    Node<T> *remove(Node<T> *, const T &val);
    Node<T> *get_min(Node<T> *);
    Node<T> *get_max(Node<T> *);

    void copy(const BSTree &other);
    void destroy_tree(Node<T> *leaf);

private:
    Node<T> *_root = nullptr;
    size_t _size = 0;
};

template <typename T>
BSTree<T>::BSTree(const BSTree &other) : _size(other._size)
{
    copy(other);
}

template <typename T>
BSTree<T>::BSTree(BSTree &&rhs)
{
    _root = rhs._root;
    _size = rhs._size;
    rhs._root = nullptr;
    rhs._size = 0;
}

template <typename T>
BSTree<T>::BSTree(std::initializer_list<T> li)
{
    for (T el : li)
    {
        insert(el);
    }
}
template <typename T>
BSTree<T>::~BSTree()
{
    destroy_tree(_root);
}

// insert
template <typename T>
void BSTree<T>::insert(const T &val)
{
    Node<T> *newNode = new Node<T>(val);
    if (_root == nullptr)
    {
        _root = newNode;
    }
    else
    {
        Node<T> *tmp = _root;
        while (1)
        {
            if (tmp->data > val)
            {
                if (tmp->left)
                {
                    tmp = tmp->left;
                }
                else
                {
                    tmp->left = newNode;
                    break;
                }
            }
            else
            {
                if (tmp->right)
                {
                    tmp = tmp->right;
                }
                else
                {
                    tmp->right = newNode;
                    break;
                }
            }
        }
    }
    _size++;
}

// delete

template <typename T>
void BSTree<T>::remove(const T &val)
{
    remove(_root, val);
    _size--;
}

// methods
template <typename T>
bool BSTree<T>::search(const T &val)
{
    Node<T> *tmp = _root;
    while (tmp)
    {
        if (tmp->data == val)
        {
            return true;
        }
        if (tmp->data > val)
        {
            tmp = tmp->left;
        }
        else
        {
            tmp = tmp->right;
        }
    }
    return false;
}

// iterations
template <typename T>
void BSTree<T>::inorder()
{
    inorder(_root);
}

template <typename T>
void BSTree<T>::inorder(Node<T> *r) // l, root, r
{
    if (r != nullptr)
    {
        inorder(r->left);
        std::cout << r->data << " ";
        inorder(r->right);
    }
}

template <typename T>
void BSTree<T>::preorder()
{
    preorder(_root);
}
template <typename T>
void BSTree<T>::preorder(Node<T> *r) // root, l, r
{
    if (r != nullptr)
    {
        std::cout << r->data << " ";
        preorder(r->left);
        preorder(r->right);
    }
}

template <typename T>
void BSTree<T>::postorder()
{
    postorder(_root);
}

template <typename T>
void BSTree<T>::postorder(Node<T> *r) // l, r, root
{
    if (r != nullptr)
    {
        postorder(r->left);
        postorder(r->right);
        std::cout << r->data << " ";
    }
}
template <typename T>
void BSTree<T>::levelOrder()
{
    int h = get_height();
    for (int i = 0; i <= h; ++i)
    {
        levelOrder(_root, i);
    }
}
template <typename T>
void BSTree<T>::levelOrder(Node<T> *root, int level)
{
    if (root == nullptr)
    {
        return;
    }
    if (level == 0)
    {
        std::cout << root->data << " ";
    }
    else if (level > 0)
    {
        levelOrder(root->left, level - 1);
        levelOrder(root->right, level - 1);
    }
}

template <typename T>
Node<T> *BSTree<T>::remove(Node<T> *node, const T &val)
{
    if (!node)
    {
        return nullptr;
    }

    if (node->data > val)
    {
        node->left = remove(node->left, val);
    }
    else if (node->data < val)
    {
        node->right = remove(node->right, val);
    }
    else
    {
        Node<T> *tmp;
        if (!node->left)
        {
            tmp = node->right;
            delete node;
            return tmp;
        }

        if (!node->right)
        {
            tmp = node->left;
            delete node;
            return tmp;
        }
        tmp = get_min(node->right);
        node->data = tmp->data;
        node->right = remove(node->right, tmp->data);
    }
    return node;
}

// operators
template <typename T>
BSTree<T> &BSTree<T>::operator=(const BSTree &other)
{
    if (&other != this)
    {
        destroy_tree(_root);
        copy(other);
        _size = other._size;
    }

    return *this;
}

template <typename T>
BSTree<T> &BSTree<T>::operator=(BSTree &&rhs)
{
    if (&rhs != this)
    {
        _root = rhs._root;
        _size = rhs._size;
        rhs._root = nullptr;
        rhs._size = 0;
    }

    return *this;
}

// gettres
template <typename T>
size_t BSTree<T>::get_height()
{
    return get_height(_root);
}

template <typename T>
Node<T> *BSTree<T>::get_predecessor(Node<T> *node)
{
    if (!node)
    {
        return nullptr;
    }
    if (node->left)
    {
        return get_max(node->left);
    }

    Node<T> *pred = nullptr;
    Node<T> *ancestor = _root;

    while (ancestor != node)
    {
        if (ancestor->data < node->data)
        {
            pred = ancestor;
            ancestor = ancestor->right;
        }
        else
        {
            ancestor = ancestor->left;
        }
    }

    return pred;
}

template <typename T>
Node<T> *BSTree<T>::get_successor(Node<T> *node)
{
    if (!node)
    {
        return nullptr;
    }
    if (node->right)
    {
        return get_min(node->right);
    }

    Node<T> *succ = nullptr;
    Node<T> *ancestor = _root;

    while (ancestor != node)
    {
        if (ancestor->data > node->data)
        {
            succ = ancestor;
            ancestor = ancestor->left;
        }
        else
        {
            ancestor = ancestor->right;
        }
    }

    return succ;
}

template <typename T>
size_t BSTree<T>::get_height(Node<T> *t)
{
    if (t == nullptr)
    {
        return -1;
    }
    else
    {
        return std::max(get_height(t->left) + 1, get_height(t->right) + 1);
    }
}

template <typename T>
Node<T> *BSTree<T>::get_min(Node<T> *node)
{
    if (!node)
    {
        return nullptr;
    }
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

template <typename T>
Node<T> *BSTree<T>::get_max(Node<T> *node)
{
    if (!node)
    {
        return 0;
    }
    while (node->right)
    {
        node = node->right;
    }
    return node;
}

template <typename T>
void BSTree<T>::copy(const BSTree &other)
{
    std::stack<Node<T> *> s;
    s.push(other._root);
    while (!s.empty())
    {
        Node<T> *curr = s.top();
        s.pop();

        insert(curr->data);

        if (curr->right)
            s.push(curr->right);
        if (curr->left)
            s.push(curr->left);
    }
}

template <typename T>
void BSTree<T>::destroy_tree(Node<T> *leaf)
{
    if (leaf != nullptr)
    {
        destroy_tree(leaf->right);
        destroy_tree(leaf->left);
        delete leaf;
    }
}

template <typename T>
void BSTree<T>::print2DUtil(Node<T> *root, int space)
{
    int COUNT = 4;

    if (root == NULL)
        return;
    space += COUNT;
    print2DUtil(root->right, space);

    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << root->data;
    print2DUtil(root->left, space);
}

template <typename T>
void BSTree<T>::print2D()
{
    print2DUtil(_root, 0);
}

#endif // BSTREE_H