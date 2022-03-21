#ifndef BECK_AVL
#define BECK_AVL
#include <cassert>
#include <iostream>

/**
 * @brief This is an AVL tree class
 * NOT guaranteed to work with duplicate elements
 * @author Originally by Jon Beck
 * @author Hengyi Li
 * @copyright 2022, Hengyi Li, Jon Beck. All rights reserved. :)
 * @version 0.0.1 Alpha
 */
template <typename Comparable> class AVLTree
{
private:
  /**
   * @brief This is the AVL tree structure
   */
  struct AVL_node
  {
    Comparable data;
    unsigned height;
    AVL_node *left;
    AVL_node *right;
    AVL_node(const Comparable &data_p, AVL_node *left_p, AVL_node *right_p,
      unsigned height_p = 0) : data(data_p), height(height_p), left(left_p), right(right_p)
    {}
  };
  // Initial a root node as null
  AVL_node *root;

  /**
   * Insert an element into a subtree
   * @param data is the item to insert.
   * @param root_node_subtree the root node of the subtree.
   */
  void insert(const Comparable &data, AVL_node *&root_node_subtree)
  {
    // When the tree is empty, create a new node.
    if (root_node_subtree == nullptr)
    {
      root_node_subtree = new AVL_node(data, nullptr, nullptr);
    }
    // If insert data is less than the current node data.
    else if (data < root_node_subtree->data)
    {
      // 
      insert(data, root_node_subtree->left);
      if (height(root_node_subtree->left) -
              height(root_node_subtree->right) == 2)
      {
        if (data < root_node_subtree->left->data)
        {
          rotateLL(root_node_subtree);
        }
        else
        {
          rotateLR(root_node_subtree);
        }
      }
    }
    else if (root_node_subtree->data < data)
    {
      insert(data, root_node_subtree->right);
      if (height(root_node_subtree->right) -
              height(root_node_subtree->left) ==
          2)
      {
        if (root_node_subtree->right->data < data)
        {
          rotateRR(root_node_subtree);
        }
        else
        {
          rotateRL(root_node_subtree);
        }
      }
    }
    // else duplicate; do nothing
    root_node_subtree->height = std::max(height(root_node_subtree->left),
                                         height(root_node_subtree->right)) +
                                1;
  }
  /**
  * Does an element with this data occur in this subtree?
  * @param data the key to search for
  * @param t the root of the subtree to search
  * @return whether or not the data is found
  */
  bool find(const Comparable &data, AVL_node *t) const
  {
  if (t == nullptr)
  {
  return false;
  }
  if (t->data == data)
  {
  return true;
  }
  if (t->data < data)
  {
  return find(data, t->right);
  }
  return find(data, t->left);
  }

  /**
  * Accessor to report on the height of the subtree
  * @param t the root of the subtree
  * @return 0 = an empty tree, 1 = a one-node tree, 2 = a tree
  * with two or three nodes, etc.
  */
  unsigned height(AVL_node *t) const { return t == nullptr ? 0 : t->height; }

  /**
  * Print a subtree, at level depth, sideways
  * Uses spaces per level to indicate the depth "graphically"
  * @param t the subtree to print
  * @param depth the depth of this node
  */
  void print_tree(AVL_node *t, unsigned int depth) const
  {
  const std::string LEVEL_SPACE = "     ";
  if (t != nullptr)
  {
  print_tree(t->right, depth + 1);
  for (unsigned i = 0; i < depth; i++)
  {
  std::cout << "   ";
  }
  std::cout << LEVEL_SPACE << t->data << std::endl;
  print_tree(t->left, depth + 1);
  }
  }

  /**
  * Zero out and re-initialize a subtree
  * @param t the root of the subtree
  */
  void make_empty(AVL_node *&t)
  {
  if (t != nullptr)
  {
  make_empty(t->left);
  make_empty(t->right);
  delete t;
  t = nullptr;
  }
  }

  /**
  * Make a deep copy of a subtree
  * @param t the subtree to clone
  * @return a pointer to the cloned subtree
  */
  AVL_node *clone(AVL_node *t) const
  {
  if (t == nullptr)
  {
  return nullptr;
  }
  return new AVL_node(t->data, clone(t->left), clone(t->right), t->height);
  }

  /**
  * Perform an RR rotation on a node
  * @param p the node on which to rotate
  */
  void rotateRR(AVL_node *&p)
  {
  AVL_node *orig_right = p->right;
  p->right = orig_right->left;
  orig_right->left = p;
  p->height = std::max(height(p->right), height(p->left)) + 1;
  orig_right->height = std::max(height(orig_right->right), p->height) + 1;
  p = orig_right;
  }

  /**
  * This function is to perform the left-left rotation
  * @param p is the node on which to rotate
  */
  void rotateLL(AVL_node *&p)
  {
  AVL_node *orig_left = p->left;
  p->left = orig_left->right;
  orig_left->right = p;
  p->height = std::max(height(p->left), height(p->right)) + 1;
  orig_left->height = std::max(height(orig_left->left), p->height) + 1;
  p = orig_left;
  }

  /**
  * This function is to perform the Left-Right rotation
  * @param p is the node on which to rotate
  */
  void rotateLR(AVL_node *&p)
  {
  AVL_node *parent = p->left;
  AVL_node *right_child = p->left->right;
  rotateLL(right_child);
  rotateRR(parent);
  }

  /**
  * This function is to perform the right-left rotation
  * @param p is the node on which to rotate
  */
  void rotateRL(AVL_node *&p) {}

public:
  /**
   * @brief Construct a new AVLTree object for a empty tree
   */
  AVLTree() : root(nullptr) {}

  /**
   * @brief This is a copy of constructor for the AVL tree
   * @param rhs is the right hand side of the tree to be copied.
   */
  AVLTree(const AVLTree &rhs) : root(rhs.clone(rhs.root)) {}

  /**
   * @brief Destroy the AVLTree object
   * And deallocates the memory
   */
  ~AVLTree()
  {
    make_empty();
  }

  /**
   * @brief This is the standard = operator
   * @param rhs is the right hand side of the tree to be copied
   * @return a clone of the parameter tree
   */
  const AVLTree &operator=(const AVLTree &rhs)
  {
    if (this != &rhs)
    {
      make_empty();
      root = rhs.clone(rhs.root);
    }
    return *this;
  }

  /**
   * @brief This function is to find the data
   * whether occur in the tree or not.
   * @param data is the key to search for
   * @return true when data is found
   * @return false when data is not found.
   */
  bool find(const Comparable &data) const
  {
     return find(data, root);
  }

  /**
   * @brief This function is to find whether the tree is empty
   * @return true when tree is empty
   * @return false when it's not empty
   */
  bool is_empty() const
  {
    return root == nullptr;
  }

  /**
   * @brief This function is to print the tree sideways
   */
  void print_tree() const
  {
    print_tree(root, 0);
  }

  /**
   * @brief This function is to get the height of the tree
   * @return 0 if the tree is empty
   * @return 1 if the tree only has one node
   * @return 2 if the tree has two ot three nodes
   */
  unsigned height() const
  {
    return height(root);
  }

  /**
   * @brief This function is to re-initialize the tree
   */
  void make_empty()
  {
    make_empty(root);
  }

  /**
   * @brief This function is to insert the new element into the current tree
   * @param data is the data that to be inserted
   */
  void insert(const Comparable &data)
  {
    insert(data, root);
  }
};
#endif
