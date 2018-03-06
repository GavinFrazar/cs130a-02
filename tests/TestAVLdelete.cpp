#include "AVL.h"

#include <vector>
#include <string>
#include <iostream>

int main()
{
    using AVL::AVLTree;
    AVLTree tree;
    
    std::vector<std::string> words;
    for (int i = 0; i < 1000; ++i)
    {
        char random_char = rand() % 26 + 65;
        std::string word = "";
        word += random_char;
        tree.insert(word);
        words.push_back(word);
    }

    for (auto word : words)
        tree.deleteWord(word);
    
    for (auto word : words)
    {
        if (tree.search(word) == true)
        {
            std::cout << "Found deleted 'word': " << word << std::endl;
            return -1;
        }
    }

    return 0;
}