#ifndef BINARY_TREE
#define BINARY_TREE
#include <iostream>

class BinaryTree;

struct TreeNode {
    explicit TreeNode(int value);
    ~TreeNode();

    int value;
    TreeNode* left{nullptr};
    TreeNode* right{nullptr};
};

class BinaryTree {
 public:
    BinaryTree();
    ~BinaryTree();

    TreeNode* Insert(int);
    bool Empty() const;

    void Print() const;

    TreeNode* root();
 private:
    TreeNode* Insert(int value, TreeNode* root);
 private:
    TreeNode* root_{nullptr};
};

std::istream& operator>>(std::istream& is, BinaryTree& bt);
int SumNumbers(TreeNode* root);

#endif  // BINARY_TREE
