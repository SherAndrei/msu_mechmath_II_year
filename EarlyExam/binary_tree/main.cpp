#include <iostream>
#include "binary_tree.h"

int main() {
    BinaryTree bt;
    std::cin >> bt;
    bt.Print();
    std::cout << SumNumbers(bt.root()) << std::endl;
}
