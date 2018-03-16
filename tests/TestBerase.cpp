#include "BTree.h"

#include <vector>
#include <string>
#include <iostream>

int main()
{
    BTree tree;
    tree.insert("x");
    tree.insert("a");
    tree.erase("x");
    if (tree.search("x"))
        return -1;
    return 0;
}