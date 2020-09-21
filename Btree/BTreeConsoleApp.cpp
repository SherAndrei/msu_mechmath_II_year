#include <iostream>
#include <string>
#include <strstream>
#include "BTree.h"

using namespace std;

int main()
{
    using Node = RootLinker<string, string>::TNode;
    using Elem = Node::TElem;

    RootLinker<string, string> b_tree;

    /*Node* rootNode = */b_tree.createRoot();
    const int totalElemsCount = 100;
    int sum = 0;
    for (int i = 0; i < totalElemsCount; ++i)
    {
        string key     = ""  + std::to_string(i);
        string payload = "p" + std::to_string(i);
        Elem el{ key, payload };
        if (!b_tree.root()->treeInsert(el))
            break;

        sum += key.length() + 2;

        cout << key << "  ";
    }

    cout << endl << "main(): sum = " << sum << endl;

    Node* root = b_tree.root();

    int currentHeight = 0;
    root->treeHeight(currentHeight);
    cout << "The root height is " << currentHeight << endl;
    
    
    int fullWidth = 0;
    root->calcFullPrintWidth(fullWidth);
    cout << "The full width is " << fullWidth << endl;

    
    Node* leftLeaf = root->findLeftLeaf();
    if (leftLeaf)
    {
        int start = 0;
        leftLeaf->printFamily(start);
    }



    // [...]

    //Node* lastNode = rootNode;
    //Elem desired;
    //for (int i = 0; i < totalElemsCount; ++i)
    //{
    //    desired.set(std::to_string(i), "p" +std::to_string(i));
    //    Elem founded = rootNode->search(desired, lastNode);
    //    cout << endl;
    //    founded.print();
    //    cout << endl;
    //}

    std::cout << "Hello World!\n";

    std::cin.get();
    return 0;
}


/*
#include <iostream>
#include <string>
#include <strstream>
#include "BTree.h"

using namespace std;

int main()
{
    using Node = RootLinker<string, string>::TNode;
    using Elem = Node::TElem;

    RootLinker<string, string> b_tree;

    Node* node = b_tree.createRoot();
    strstream stm;
    string key;
    string payload;

    for (int i = 0; i < 1000000; ++i)
    {
        stm.clear();
        stm << i;
        stm >> key;
        stm << " p";
        stm >> payload;

        node->treeInsert(Elem{ key,payload });
    }

    std::cout << "Hello World!\n";
    return 0;
}
*/
