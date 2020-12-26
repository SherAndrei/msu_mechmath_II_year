#include <iostream>
#include <string>
#include <sstream>
#include "BTree.h"

int main() {
    using Node = RootLinker<std::string, std::string>::TNode;
    using Elem = Node::TElem;

    RootLinker<std::string, std::string> b_tree;

    /*Node* rootNode = */b_tree.createRoot();
    const int totalElemsCount = 100;
    int sum = 0;
    for (int i = 0; i < totalElemsCount; ++i) {
        std::string key     = ""  + std::to_string(i);
        std::string payload = "p" + std::to_string(i);
        Elem el{ key, payload };
        if (!b_tree.root()->treeInsert(el))
            break;

        sum += key.length() + 2;

        std::cout << key << "  ";
    }

    std::cout << std::endl << "main(): sum = " << sum << std::endl;

    Node* root = b_tree.root();

    int currentHeight = 0;
    root->treeHeight(currentHeight);
    std::cout << "The root height is " << currentHeight << std::endl;


    int fullWidth = 0;
    root->calcFullPrintWidth(fullWidth);
    std::cout << "The full width is " << fullWidth << std::endl;

    Node* leftLeaf = root->findLeftLeaf();
    if (leftLeaf) {
        int start = 0;
        leftLeaf->printFamily(start);
    }

    std::cout << "Hello World!\n";

    std::cin.get();
    return 0;
}
