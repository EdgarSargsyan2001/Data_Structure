#include <algorithm>
#include <iostream>

class TreeNode {
public:
  int key; 
  TreeNode *left;
  TreeNode *right;
  TreeNode(int k, TreeNode *l = 0, TreeNode *r = 0)
      : key(k), left(l), right(r) {}
};

TreeNode *findMaximumKey(TreeNode *ptr) {
  while (ptr->right != nullptr) {
    ptr = ptr->right;
  }
  return ptr;
}

class BSTree {
public:
  BSTree() : root(0), count_nodes(0){};
  TreeNode *getRoot() { return root; };
  bool insert(int);
  bool remove(TreeNode *, int);
  bool find(int);
  int calcHeight(TreeNode *);
  void inorder(TreeNode *);
  void print2D(TreeNode *);
  void print2DUtil(TreeNode *, int);

private:
  TreeNode *root;
  int count_nodes;
};

bool BSTree::find(int x) {
  if (!root) {
    return false;
  }
  TreeNode *t = root;

  while (t) {
    if (t->key == x) {
      return true;
    }
    if (t->key < x) {
      t = t->right;
    } else {
      t = t->left;
    }
  }
  return false;
}

bool BSTree::insert(int x) {

  if (!root) {
    root = new TreeNode(x);
    return true;
  }
  TreeNode *t = root;

  while (1) {
    if (t->key == x)
      return false;

    if (t->key < x) {
      if (t->right) {
        t = t->right;
      } else {
        t->right = new TreeNode(x);
        break;
      }
    } else {
      if (t->left) {
        t = t->left;
      } else {
        t->left = new TreeNode(x);
        break;
      }
    }
  }
  return true;
}

void BSTree::inorder(TreeNode *s) {

  if (s) {
    inorder(s->left);
    std::cout << s->key << "\n";
    inorder(s->right);
  }
}

bool BSTree::remove(TreeNode *root, int x) {
  if (!find(x)) {
    return false;
  }
  TreeNode *rip;
  TreeNode *parent = nullptr;

  rip = root;
  while (rip->key != x) {
    parent = rip;
    if (rip->key < x) {
      rip = rip->right;
    } else {
      rip = rip->left;
    }
  }
  // Case 1: node to be deleted has no children, i.e., it is a leaf node
  if (!rip->right && !rip->left) {
    if (rip == root) {
      root = nullptr;
    } else {
      if (parent->right == rip) {
        parent->right = nullptr;
      } else {
        parent->left = nullptr;
      }
    }

    // Case 2: node to be deleted has two children
  } else if (rip->left && rip->right) {
    TreeNode *predecessor = findMaximumKey(rip->left);

    int val = predecessor->key;
    remove(root, val);
    rip->key = val;

    // Case 3: node to be deleted has only one child
  } else {
    TreeNode *child = (rip->left) ? rip->left : rip->right;

    if (rip != root) {
      if (rip == parent->left) {
        parent->left = child;
      } else {
        parent->right = child;
      }
    } else {
      root = child;
    }
  }
  return true;
}

int BSTree::calcHeight(TreeNode *ptr) {
  if (!ptr) {
    return -1;
  }
  int r = calcHeight(ptr->right);
  int l = calcHeight(ptr->left);
  return std::max(r, l) + 1;
}

void BSTree::print2DUtil(TreeNode *root, int space) {
  int COUNT = 5;

  if (root == NULL)
    return;
  space += COUNT;
  print2DUtil(root->right, space);

  std::cout << std::endl;
  for (int i = COUNT; i < space; i++)
    std::cout << " ";
  std::cout << root->key << "\n";
  print2DUtil(root->left, space);
}

void BSTree::print2D(TreeNode *root) { print2DUtil(root, 0); }
