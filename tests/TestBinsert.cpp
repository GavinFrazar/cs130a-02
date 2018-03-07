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

    for (auto word : words1)
        tree.insert(word);

    auto v1 = tree.sort();
    if (v1.size() != words1.size())
    {
        std::cout << "Size of tree was: " << v1.size() << "\t Expected: " << words1.size() << std::endl;
        return -1;
    }

    std::vector<std::string> words2;
    for (int i = 0; i < 100; ++i)
    {
        std::vector<char> accumulator;
        for (int j = 0; j <= i; ++j)
            accumulator.push_back('z');
        std::string word(accumulator.begin(), accumulator.end());
        words2.push_back(word);
        tree.insert(word);
    }
    
    auto v2 = tree.sort();
    if (v2.size() != words1.size() + words2.size())
    {
        std::cout << "Size of tree was: " << v2.size() << "\t Expected: " << words1.size() + words2.size() << std::endl;
        return -1;
    }

    return 0;
}