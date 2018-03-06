#include "BTree.h"

#include <vector>
#include <string>
#include <iostream>

int main()
{
    BTree tree;
    std::vector<std::string> words;
    for (int i = 1; i < 500; ++i)
    {
        std::vector<char> accumulator;
        for (int j = 0; j < i; ++j)
            accumulator.push_back('a');
        std::string word(accumulator.begin(), accumulator.end());
        tree.insert(word);
        words.push_back(word);
    }
    auto v = tree.sort();
    if (v.size() != words.size())
    {
        std::cout << "tree insert failed. Expected tree size: " << words.size() << ", got: " << v.size() << std::endl;
        return -1;
    }


    return 0;
}