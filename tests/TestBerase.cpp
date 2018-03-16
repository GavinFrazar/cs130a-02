#include "BTree.h"

#include <vector>
#include <string>
#include <iostream>

int main()
{
    BTree tree;
    std::vector<std::string> words1;
    words1.push_back("c");
    words1.push_back("d");
    words1.push_back("e");
    words1.push_back("f");
    words1.push_back("g");
    words1.push_back("j");
    words1.push_back("k");
    words1.push_back("l");
    words1.push_back("o");
    words1.push_back("p");
    words1.push_back("q");
    words1.push_back("t");
    words1.push_back("u");
    words1.push_back("v");
    words1.push_back("a");
    words1.push_back("b");
    words1.push_back("h");
    words1.push_back("i");
    words1.push_back("m");
    words1.push_back("n");
    words1.push_back("r");
    words1.push_back("s");
    words1.push_back("w");
    words1.push_back("x");
    words1.push_back("A");

    for (auto& word : words1)
        tree.insert(word);

    for (auto& word : words1)
        tree.erase(word);

    for (auto& word : words1)
        assert(tree.search(word) != true);
    return 0;
}