#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>
#include <math.h>
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
class AVLTree
{
public:
    AVLTree() = default;
    AVLTree(const AVLTree &other);
    AVLTree(AVLTree &&rhs);
    AVLTree(std::initializer_list<T>);
    ~AVLTree();

    // insert
    void insert(const T &val);

    // methods
    bool search(const T &val);

    // delete
    void remove(const T &val);

    // iterations
    void inorder();   // l, root, r
    void preorder();  // root, l, r
    void postorder(); // l, r, root
    void levelOrder();

    // operators
    AVLTree<T> &operator=(const AVLTree &other);
    AVLTree<T> &operator=(AVLTree &&rhs);

    // gettres
    Node<T> *root() { return _root; };
    size_t height();

    void print2D();
    void print2DUtil(Node<T> *, int);

private:
    Node<T> *insert(Node<T> *, const T &val);

    Node<T> *remove(Node<T> *, const T &val);

    void inorder(Node<T> *);
    void preorder(Node<T> *);
    void postorder(Node<T> *);
    void levelOrder(Node<T> *root, int level);
    size_t height(Node<T> *);

    Node<T> *rr_rot(Node<T> *);
    Node<T> *ll_rot(Node<T> *);
    Node<T> *lr_rot(Node<T> *);
    Node<T> *rl_rot(Node<T> *);
    Node<T> *balance(Node<T> *);
    int height_diff(Node<T> *);

    Node<T> *get_min(Node<T> *);
    Node<T> *get_max(Node<T> *);
    void copy(const AVLTree &other);
    void destroy_tree(Node<T> *);

private:
    Node<T> *_root = nullptr;
    size_t _size = 0;
};

template <typename T>
AVLTree<T>::AVLTree(const AVLTree &other)
{
    copy(other);
}

template <typename T>
AVLTree<T>::AVLTree(AVLTree &&rhs)
{
    _root = rhs._root;
    _size = rhs._size;
    rhs._root = nullptr;
    rhs._size = 0;
}

template <typename T>
AVLTree<T>::AVLTree(std::initializer_list<T> li)
{
    for (T el : li)
    {
        insert(el);
    }
}
template <typename T>
AVLTree<T>::~AVLTree()
{
    destroy_tree(_root);
}

// insert
template <typename T>
void AVLTree<T>::insert(const T &val)
{
    _root = insert(_root, val);
}
template <typename T>
Node<T> *AVLTree<T>::insert(Node<T> *root, const T &val)
{
    if (!root)
    {
        return new Node<T>(val);
    }
    if (root->data > val)
    {
        root->left = insert(root->left, val);
        root = balance(root);
    }
    else
    {
        root->right = insert(root->right, val);
        root = balance(root);
    }
    return root;
}

// delete
template <typename T>
void AVLTree<T>::remove(const T &val)
{
    _root = remove(_root, val);
    _size--;
}

// methods
template <typename T>
bool AVLTree<T>::search(const T &val)
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
void AVLTree<T>::inorder()
{
    inorder(_root);
}

template <typename T>
void AVLTree<T>::inorder(Node<T> *r) // l, root, r
{
    if (r != nullptr)
    {
        inorder(r->left);
        std::cout << r->data << " ";
        inorder(r->right);
    }
}

template <typename T>
void AVLTree<T>::preorder()
{
    preorder(_root);
}
template <typename T>
void AVLTree<T>::preorder(Node<T> *r) // root, l, r
{
    if (r != nullptr)
    {
        std::cout << r->data << " ";
        preorder(r->left);
        preorder(r->right);
    }
}

template <typename T>
void AVLTree<T>::postorder()
{
    postorder(_root);
}
template <typename T>
void AVLTree<T>::postorder(Node<T> *r) // l, r, root
{
    if (r != nullptr)
    {
        postorder(r->left);
        postorder(r->right);
        std::cout << r->data << " ";
    }
}

template <typename T>
void AVLTree<T>::levelOrder()
{
    int h = height();
    for (int i = 1; i <= h; ++i)
    {
        levelOrder(_root, i);
    }
}
template <typename T>
void AVLTree<T>::levelOrder(Node<T> *root, int level)
{
    if (root == nullptr)
    {
        return;
    }
    if (level == 1)
    {
        std::cout << root->data << " ";
    }
    else if (level > 1)
    {
        levelOrder(root->left, level - 1);
        levelOrder(root->right, level - 1);
    }
}

// operators
template <typename T>
AVLTree<T> &AVLTree<T>::operator=(const AVLTree &other)
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
AVLTree<T> &AVLTree<T>::operator=(AVLTree &&rhs)
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

template <typename T>
Node<T> *AVLTree<T>::remove(Node<T> *node, const T &val)
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
    if (node)
    {
        node = balance(node);
    }
    return node;
}

// gettres
template <typename T>
size_t AVLTree<T>::height()
{
    return height(_root);
}

template <typename T>
size_t AVLTree<T>::height(Node<T> *temp)
{
    size_t h = 0;
    if (temp != nullptr)
    {
        size_t l_height = height(temp->left);
        size_t r_height = height(temp->right);
        size_t max_height = std::max(l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

template <typename T>
Node<T> *AVLTree<T>::rr_rot(Node<T> *parent)
{
    Node<T> *tmp = parent->right;
    parent->right = tmp->left;
    tmp->left = parent;
    return tmp;
}

template <typename T>
Node<T> *AVLTree<T>::ll_rot(Node<T> *parent)
{
    Node<T> *tmp = parent->left;
    parent->left = tmp->right;
    tmp->right = parent;
    return tmp;
}

template <typename T>
Node<T> *AVLTree<T>::lr_rot(Node<T> *parent)
{
    Node<T> *tmp = parent->left;
    parent->left = rr_rot(tmp);
    return ll_rot(parent);
}

template <typename T>
Node<T> *AVLTree<T>::rl_rot(Node<T> *parent)
{
    Node<T> *tmp = parent->right;
    parent->right = ll_rot(tmp);
    return rr_rot(parent);
}

template <typename T>
Node<T> *AVLTree<T>::balance(Node<T> *tmp)
{
    int bal_fac = height_diff(tmp);
    if (bal_fac > 1)
    {
        if (height_diff(tmp->left) > 0)
        {
            tmp = ll_rot(tmp);
        }
        else
        {
            tmp = lr_rot(tmp);
        }
    }
    else if (bal_fac < -1)
    {
        if (height_diff(tmp->right) > 0)
        {
            tmp = rl_rot(tmp);
        }
        else
        {
            tmp = rr_rot(tmp);
        }
    }

    return tmp;
}

template <typename T>
int AVLTree<T>::height_diff(Node<T> *tmp)
{
    return height(tmp->left) - height(tmp->right);
}

template <typename T>
Node<T> *AVLTree<T>::get_min(Node<T> *node)
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
Node<T> *AVLTree<T>::get_max(Node<T> *node)
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
void AVLTree<T>::copy(const AVLTree &other)
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
void AVLTree<T>::destroy_tree(Node<T> *leaf)
{
    if (leaf != nullptr)
    {
        destroy_tree(leaf->right);
        destroy_tree(leaf->left);
        delete leaf;
    }
}

template <typename T>
void AVLTree<T>::print2DUtil(Node<T> *root, int space)
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
void AVLTree<T>::print2D()
{
    print2DUtil(_root, 0);
}

#endif // AVLTREE_H