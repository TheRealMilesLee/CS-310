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
   * @brief This function is to insert an element into a subtree
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
      // Put the new data in the left side of the nodes.
      insert(data, root_node_subtree->left);
      // Keep the tree balance.
      if (height(root_node_subtree->left) - height(root_node_subtree->right) == 2)
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
    // If insert data is greater than the current node data.
    else if (root_node_subtree->data < data)
    {
      // Put the new data in the right side of the nodes.
      insert(data, root_node_subtree->right);
      // Keep the tree balance.
      if (height(root_node_subtree->right) - height(root_node_subtree->left) == 2)
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
                                         height(root_node_subtree->right)) + 1;
  }

  /**
   * @brief This function is to find the node is in the tree or node
   * @param data is the key that we looking for
   * @param search_node is the root of the subtree to search
   * @return true if the data is found
   * @return false if the data is not found.
   */
  bool find(const Comparable &data, AVL_node *search_node) const
  {
    if (search_node == nullptr)
    {
      return false;
    }
    if (search_node->data == data)
    {
      return true;
    }
    if (search_node->data < data)
    {
      return find(data, search_node->right);
    }
    return find(data, search_node->left);
  }

  /**
   * @brief This function is to get the height of the subtree
   * @param root_of_subtree is the root of the subtree
   * @return 0 if the tree is empty
   * @return 1 if the tree only have one node
   * @return 2 if the tree has two or three nodes.
   */
  unsigned height(AVL_node *root_of_subtree) const
  {
    return root_of_subtree == nullptr ? 0 : root_of_subtree->height;
  }

  /**
   * @brief This function is to print a subtree, at level depth, sideways
   * @param subtree is the subtree to print
   * @param depth is the depth of the node
   */
  void print_tree(AVL_node *subtree, unsigned int depth) const
  {
    const std::string LEVEL_SPACE = "    ";
    if (subtree != nullptr)
    {
      print_tree(subtree->right, depth + 1);
      for (size_t index = 0; index < depth; index++)
      {
        std::cout << "   ";
      }
      std::cout << LEVEL_SPACE << subtree->data << std::endl;
      print_tree(subtree->left, depth + 1);
    }
  }

  /**
   * @brief This function is to zero out and re-initialize the subtree
   * @param root_subtree is the root of the subtree
   */
  void make_empty(AVL_node *&root_subtree)
  {
    if (root_subtree != nullptr)
    {
      make_empty(root_subtree->left);
      make_empty(root_subtree->right);
      delete root_subtree;
      root_subtree = nullptr;
    }
  }

  /**
   * @brief This function is to make a deep copy of a subtree
   * @param subtree_clone is the subtree to clone
   * @return AVL_node* is a pointer to the cloned subtree
   */
  AVL_node *clone(AVL_node *subtree_clone) const
  {
    if (subtree_clone == nullptr)
    {
    return nullptr;
    }
    return new AVL_node(subtree_clone->data, clone(subtree_clone->left),
                        clone(subtree_clone->right), subtree_clone->height);
  }

  /**
   * @brief This function is to perform the RR rotation on a node
   * @param rotate_node is the node on which to rotate
   */
  void rotateRR(AVL_node *&rotate_node)
  {
    AVL_node *orig_right = rotate_node->right;
    rotate_node->right = orig_right->left;
    orig_right->left = rotate_node;
    rotate_node->height
      = std::max(height(rotate_node->right), height(rotate_node->left)) + 1;
    orig_right->height
      = std::max(height(orig_right->right), rotate_node->height) + 1;
    rotate_node = orig_right;
  }

  /**
   * @brief This function is to perform the LL rotation
   * @param rotate_node is the node on which to rotate
   */
  void rotateLL(AVL_node *&rotate_node)
  {
    AVL_node *orig_left = rotate_node->left;
    rotate_node->left = orig_left->right;
    orig_left->right = rotate_node;
    rotate_node->height
      = std::max(height(rotate_node->left), height(rotate_node->right)) + 1;
    orig_left->height
      = std::max(height(orig_left->left), rotate_node->height) + 1;
    rotate_node = orig_left;
  }

/**
 * @brief This function is to perform the LR operation
 * @param rotate_node is the node on which to rotate
 */
  void rotateLR(AVL_node *&rotate_node)
  {
    AVL_node *left_sub_node = rotate_node->left;
    AVL_node *orig_node = rotate_node;
    rotateRR(left_sub_node);
    rotateLL(orig_node);
  }

  /**
   * @brief This function is to perform the LR operation
   * @param rotate_node is the node on which to rotate
   */
  void rotateRL(AVL_node *&rotate_node)
  {
    AVL_node *right_sub_node = rotate_node->right;
    AVL_node *orig_node = rotate_node;
    rotateLL(right_sub_node);
    rotateRR(orig_node);
  }

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
