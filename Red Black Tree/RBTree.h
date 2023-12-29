#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
#include <stack>

template <typename T>
struct Node
{
    Node(T v, Node<T> *p = nullptr, Node<T> *l = nullptr, Node<T> *r = nullptr, bool c = false)
        : data(v), parent(p), left(l), right(r), color(c) {}

    T data;
    Node<T> *parent;
    Node<T> *left;
    Node<T> *right;
    bool color; // false <=> BLACK  /  true <=> RED
};

template <typename T>
class RBTree
{
public:
    RBTree() = default;
    RBTree(const RBTree &other);
    RBTree(RBTree &&rhs);
    RBTree(std::initializer_list<T> l);
    ~RBTree();

    // insert
    void insert(const T &val);

    // search
    bool search(const T &val); // O(log(n))  : { h <= 2 * log(n+1) }

    // delete
    void remove(const T &val);

    // iterations
    void inorder();   // l, root, r
    void preorder();  // root, l, r
    void postorder(); // l, r, root
    void levelOrder();

    // operators
    RBTree<T> &operator=(const RBTree &other);
    RBTree<T> &operator=(RBTree &&rhs);

    // gettres
    Node<T> *root() { return _root; };
    size_t height();

    // print
    void print2D();
    void print2DUtil(Node<T> *, int);
    Node<T> *get_min(Node<T> *);
    Node<T> *get_max(Node<T> *);

private:
    void remove(Node<T> *);

    void delete_fix_up(Node<T> *x);
    void insert_fix_up(Node<T> *z);

    void inorder(Node<T> *);
    void preorder(Node<T> *);
    void postorder(Node<T> *);
    void levelOrder(Node<T> *root, int level);
    size_t height(Node<T> *);

    Node<T> *left_rotate(Node<T> *node);
    Node<T> *right_rotate(Node<T> *node);
    void transplant(Node<T> *node1, Node<T> *node2);

    void copy(const RBTree &other);
    void destroy_tree(Node<T> *);

private:
    Node<T> *NIL = new Node<T>(0);
    Node<T> *_root = NIL;
};

template <typename T>
RBTree<T>::RBTree(const RBTree &other)
{
    copy(other);
}

template <typename T>
RBTree<T>::RBTree(RBTree &&rhs)
{
    _root = rhs._root;
    NIL = rhs.NIL;
    rhs._root = nullptr;
    rhs.NIL = nullptr;
}

template <typename T>
RBTree<T>::RBTree(std::initializer_list<T> l)
{
    for (T el : l)
    {
        insert(el);
    }
}

template <typename T>
RBTree<T>::~RBTree()
{
    destroy_tree(_root);
    delete NIL;
}

template <typename T>
void RBTree<T>::insert(const T &val)
{
    Node<T> *parent = NIL;
    Node<T> *tmp = _root;

    while (tmp != NIL)
    {
        parent = tmp;
        if (val < tmp->data)
        {
            tmp = tmp->left;
        }
        else
        {
            tmp = tmp->right;
        }
    }

    // create new node that has RED color
    Node<T> *newNode = new Node<T>(val, parent, NIL, NIL, true);

    if (parent == NIL)
    {
        _root = newNode;
    }
    if (parent->data > newNode->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }
    insert_fix_up(newNode);
}

// search
template <typename T>
bool RBTree<T>::search(const T &val)
{
    Node<T> *x = _root;
    while (x != NIL)
    {
        if (x->data == val)
        {
            return true;
        }
        if (x->data > val)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    return false;
}

template <typename T>
void RBTree<T>::remove(const T &val)
{
    Node<T> *tmp = _root;
    while (tmp)
    {
        if (tmp->data == val)
        {
            remove(tmp);
            break;
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
}

// iterations
template <typename T>
void RBTree<T>::inorder()
{
    inorder(_root);
}

template <typename T>
void RBTree<T>::inorder(Node<T> *node)
{
    if (node != NIL)
    {
        inorder(node->left);
        std::cout << node->data << " ";
        inorder(node->right);
    }
}

template <typename T>
void RBTree<T>::preorder()
{
    preorder(_root);
}
template <typename T>
void RBTree<T>::preorder(Node<T> *node)
{
    if (node != NIL)
    {
        std::cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

template <typename T>
void RBTree<T>::postorder()
{
    postorder(_root);
}
template <typename T>
void RBTree<T>::postorder(Node<T> *node)
{
    if (node != NIL)
    {
        postorder(node->left);
        postorder(node->right);
        std::cout << node->data << " ";
    }
}

template <typename T>
void RBTree<T>::levelOrder()
{
    int h = height();
    for (int i = 1; i <= h; ++i)
    {
        levelOrder(_root, i);
    }
}
template <typename T>
void RBTree<T>::levelOrder(Node<T> *root, int level)
{
    if (root == NIL)
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
RBTree<T> &RBTree<T>::operator=(const RBTree &other)
{
    if (&other != this)
    {
        destroy_tree(_root);
        copy(other);
    }

    return *this;
}

template <typename T>
RBTree<T> &RBTree<T>::operator=(RBTree &&rhs)
{
    if (&rhs != this)
    {
        _root = rhs._root;
        NIL = rhs.NIL;
        rhs._root = nullptr;
        rhs.NIL = nullptr;
    }

    return *this;
}

template <typename T>
void RBTree<T>::remove(Node<T> *node)
{
    // std::cout << "data  " << node->data;

    Node<T> *tmp = node;
    bool origColor = tmp->color;
    Node<T> *x = nullptr;

    if (node->left == NIL)
    {

        x = node->right;
        transplant(node, node->right);
        // std::cout << "data  " << tmp->data;
        // std::cout << "x color " << x->color;
    }
    else if (node->right == NIL)
    {
        x = node->left;
        transplant(node, node->left);
    }
    else
    {
        tmp = get_max(node->left);
        x = tmp->left;

        origColor = tmp->color;
        if (tmp->parent == node)
        {
            x->parent = tmp;
        }
        else
        {
            transplant(tmp, tmp->left);
            tmp->left = node->left;
            tmp->left->parent = tmp;
        }
        transplant(node, tmp);
        tmp->right = node->right;
        tmp->right->parent = tmp;
        tmp->color = node->color;
    }
    if (origColor == false) // origColor == BLACK
    {
        delete_fix_up(x);
        delete node;
    }
}

template <typename T>
void RBTree<T>::delete_fix_up(Node<T> *x)
{

    // std::cout << "data  " << x->data << '\n';
    // std::cout << "color  " << x->color << '\n';

    while (x != _root && x->color == false)
    {
        if (x == x->parent->left)
        {
            Node<T> *sibling = x->parent->right;
            if (sibling->color == true) // case 1
            {
                sibling->color = false;
                x->parent->color = true;
                left_rotate(x->parent);
                sibling = x->parent->right;
            }
            if (sibling->left->color == false && sibling->right->color == false)
            { // case 2
                sibling->color = true;
                x = x->parent;
            }
            else
            {
                if (sibling->right->color == false) // case 3
                {
                    sibling->left->color = false;
                    sibling->color = true;
                    right_rotate(sibling);
                    sibling = x->parent->right;
                }

                // case 4
                sibling->color = x->parent->color;
                x->parent->color = false;
                sibling->right->color = false;
                left_rotate(x->parent);
                x = _root;
            }
        }
        else
        {

            Node<T> *sibling = x->parent->left;
            if (sibling->color == true) // case 1
            {

                sibling->color = false;
                x->parent->color = true;
                right_rotate(x->parent);
                sibling = x->parent->left;
            }
            if (sibling->left->color == false && sibling->right->color == false)
            { // case 2
                sibling->color = true;
                x = x->parent;
            }
            else
            {

                if (sibling->left->color == false) // case 3
                {
                    sibling->right->color = false;
                    sibling->color = true;
                    left_rotate(sibling);
                    sibling = x->parent->left;
                }

                // case 4
                sibling->color = x->parent->color;
                x->parent->color = false;
                sibling->left->color = false;
                right_rotate(x->parent);
                x = _root;
            }
        }
    }

    x->color = false; // x or _root->color = BLACK
}

template <typename T>
void RBTree<T>::insert_fix_up(Node<T> *newNode)
{
    while (newNode->parent->color == true) // newNode->parent->color == RED
    {
        if (newNode->parent == newNode->parent->parent->left)
        {
            Node<T> *tmp = newNode->parent->parent->right;

            if (tmp->color == true) // tmp->color == RED : case 1
            {
                newNode->parent->color = false;
                tmp->color = false;

                newNode->parent->parent->color = true;
                newNode = newNode->parent->parent;
            }
            else
            {
                if (newNode == newNode->parent->right) // case 2
                {
                    newNode = newNode->parent;
                    left_rotate(newNode);
                }

                // case 3
                newNode->parent->color = false;
                newNode->parent->parent->color = true;
                right_rotate(newNode->parent->parent);
            }
        }
        else
        {
            Node<T> *tmp = newNode->parent->parent->left;
            if (tmp->color == true) // tmp->color == RED : case 1
            {
                newNode->parent->color = false;
                tmp->color = false;

                newNode->parent->parent->color = true;
                newNode = newNode->parent->parent;
            }
            else
            {
                if (newNode == newNode->parent->left) // case 2
                {
                    newNode = newNode->parent;
                    right_rotate(newNode);
                }

                // case 3
                newNode->parent->color = false;
                newNode->parent->parent->color = true;
                left_rotate(newNode->parent->parent);
            }
        }
    }
    _root->color = false; // the root is always black
}

template <typename T>
size_t RBTree<T>::height()
{
    return height(_root);
}

template <typename T>
size_t RBTree<T>::height(Node<T> *node)
{
    size_t h = 0;
    if (node != NIL)
    {
        size_t l_h = height(node->left);
        size_t r_h = height(node->right);
        size_t max_h = std::max(l_h, r_h);
        h = max_h + 1;
    }
    return h;
}

template <typename T>
Node<T> *RBTree<T>::left_rotate(Node<T> *node)
{
    Node<T> *tmp = node->right;
    node->right = tmp->left;
    if (tmp->left != NIL)
    {
        tmp->left->parent = node;
    }
    tmp->parent = node->parent;
    if (node->parent == NIL)
    {
        _root = tmp;
    }

    if (node == node->parent->left)
    {
        node->parent->left = tmp;
    }
    else
    {
        node->parent->right = tmp;
    }
    tmp->left = node;
    node->parent = tmp;
    return tmp;
}

template <typename T>
Node<T> *RBTree<T>::right_rotate(Node<T> *node)
{
    Node<T> *tmp = node->left;
    node->left = tmp->right;

    if (tmp->right != NIL)
    {
        tmp->right->parent = node;
    }

    tmp->parent = node->parent;

    if (node->parent == NIL)
    {
        _root = tmp;
    }

    if (node == node->parent->left)
    {
        node->parent->left = tmp;
    }
    else
    {
        node->parent->right = tmp;
    }

    tmp->right = node;
    node->parent = tmp;
    return tmp;
}

template <typename T>
void RBTree<T>::transplant(Node<T> *node1, Node<T> *node2)
{
    if (node1->parent == NIL)
    {
        _root = node2;
    }
    else if (node1 == node1->parent->left)
    {
        node1->parent->left = node2;
    }
    else
    {
        node1->parent->right = node2;
    }
    node2->parent = node1->parent;
}

template <typename T>
Node<T> *RBTree<T>::get_min(Node<T> *node)
{
    if (node == NIL || node == nullptr)
    {
        return NIL;
    }
    while (node->left != NIL)
    {
        node = node->left;
    }
    return node;
}

template <typename T>
Node<T> *RBTree<T>::get_max(Node<T> *node)
{
    if (node == NIL || node == nullptr)
    {
        return NIL;
    }
    while (node->right != NIL)
    {
        node = node->right;
    }
    return node;
}

template <typename T>
void RBTree<T>::copy(const RBTree &other)
{
    std::stack<Node<T> *> s;
    s.push(other._root);
    while (!s.empty())
    {
        Node<T> *curr = s.top();
        s.pop();

        insert(curr->data);

        if (curr->right != other.NIL)
            s.push(curr->right);
        if (curr->left != other.NIL)
            s.push(curr->left);
    }
}

template <typename T>
void RBTree<T>::destroy_tree(Node<T> *root)
{
    if (root != NIL)
    {
        destroy_tree(root->right);
        destroy_tree(root->left);
        delete root;
    }
}

template <typename T>
void RBTree<T>::print2DUtil(Node<T> *root, int space)
{
    int COUNT = 4;

    if (root == NIL)
        return;
    space += COUNT;
    print2DUtil(root->right, space);

    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << root->data << (root->color ? "R" : "B");
    print2DUtil(root->left, space);
}

template <typename T>
void RBTree<T>::print2D()
{
    print2DUtil(_root, 0);
}

#endif // RBTREE_H