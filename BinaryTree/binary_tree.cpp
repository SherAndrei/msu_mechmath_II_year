#include "binary_tree.h"
#include <iostream>
#include <string>
#include <cmath>

TreeNode::TreeNode(int val)
    : value(val), left(nullptr), right(nullptr) {}

TreeNode::~TreeNode() {
    delete left;
    delete right;
}

BinaryTree::BinaryTree()
    : root_{nullptr} {}

BinaryTree::~BinaryTree() {
    delete root_;
}

TreeNode* BinaryTree::Insert(int value) {
    if (Empty()) {
        root_ = new TreeNode{value};
        return root_;
    } else {
        return Insert(value, root_);
    }
}

TreeNode* BinaryTree::Insert(int value, TreeNode* root) {
    if (!root) {
        root = new TreeNode{value};
    } else {
        TreeNode* pos;
        if (value <= root->value) {
            pos = Insert(value, root->left);
            root->left = pos;
        } else {
            pos = Insert(value, root->right);
            root->right = pos;
        }
    }
    return root;
}

bool BinaryTree::Empty() const {
    return root_ == nullptr;
}

static void printTree(const std::string& prefix, const TreeNode* node, bool isLeft) {
    if (node != nullptr) {
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──");
        std::cout << node->value << std::endl;
        printTree(prefix + (isLeft ? "│   " : "    "), node->left, true);
        printTree(prefix + (isLeft ? "│   " : "    "), node->right, false);
    }
}

TreeNode* BinaryTree::root() {
    return root_;
}

void BinaryTree::Print() const {
    printTree("", root_, false);
}

namespace {

int globalSum = 0;

void sumNumbers(TreeNode* pos, int level, int last_result) {
    int result = pos->value * std::pow(10, level) + last_result;
    if (pos->left != nullptr) {
        sumNumbers(pos->left, level + 1, result);
    }
    if (pos->right != nullptr) {
        sumNumbers(pos->right, level + 1, result);
    }
    if (pos->left == nullptr && pos->right == nullptr) {
        globalSum += result;
    }
}

}  // namespace

int SumNumbers(TreeNode* root) {
    globalSum = 0;

    if (root->left != nullptr) {
        sumNumbers(root->left, 1, root->value);
    }
    if (root->right != nullptr) {
        sumNumbers(root->right, 1, root->value);
    }
    if (root->left == nullptr && root->right == nullptr) {
        globalSum += root->value;
    }

    return globalSum;
}


std::istream& operator>>(std::istream& is, BinaryTree& bt) {
    int cur;
    while (is >> cur) {
        bt.Insert(cur);
    }
    return is;
}
