#include "BTree.h"

#include <vector>
#include <string>
#include <iostream>

int main()
{
    B::Tree b_tree;
    std::vector<std::string> words;
    for (int i = 0; i < 1000; ++i)
    {
        std::vector<char> accumulator;
        for (int j = 0; j < i; ++j)
            accumulator.push_back('x');
        std::string word1(accumulator.begin(), accumulator.end());
        b_tree.insert(word1);
        words.push_back(word1);

        accumulator.clear();
        for (int k = 0; k < i; ++k)
            if (k % 2 == 0)
                accumulator.push_back('a');
            else
                accumulator.push_back('x');
        std::string word2(accumulator.begin(), accumulator.end());
        b_tree.insert(word2);
        words.push_back(word2);
    }

    for (auto word : words)
    {
        if (b_tree.search(word) != true)
        {
            std::cout << "Word: " << word << "\t not found" << std::endl;
            return -1;
        }
    }

    return 0;
}