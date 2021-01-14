#ifndef BINARY_TREE
#define BINARY_TREE
#include <iostream>

class BinaryTree;

struct TreeNode {
 public:
    explicit TreeNode(int value);
    ~TreeNode();

 private:
    TreeNode(const TreeNode& other) = delete;
    TreeNode& operator=(const TreeNode& other) = delete;

 public:
    int value;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
};

class BinaryTree {
 public:
    BinaryTree();
    ~BinaryTree();

 private:
    BinaryTree(BinaryTree& other) = delete;
    BinaryTree& operator=(BinaryTree& other) = delete;

 public:
    TreeNode* Insert(int);
    bool Empty() const;

    void Print() const;

 public:
    TreeNode* root();

 private:
    TreeNode* Insert(int value, TreeNode* root);
 private:
    TreeNode* root_{nullptr};
};

std::istream& operator>>(std::istream& is, BinaryTree& bt);
int SumNumbers(TreeNode* root);

#endif  // BINARY_TREE
