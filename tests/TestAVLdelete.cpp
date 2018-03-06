#include "AVLTree.h"

#include <vector>
#include <string>
#include <iostream>

int main()
{
    AVLTree tree;
    
    std::vector<std::string> words;
    for (int i = 0; i < 1000; ++i)
    {
        char random_char = rand() % 52 + 65;
        std::string word = "";
        word += random_char;
        tree.insert(word);
        words.push_back(word);
    }

    for (auto word : words)
    {
        std::cout << "\n\nDeleting:\t" << word << std::endl << std::endl;
        auto vec = tree.sort();
        std::cout << "Before:\t";
        for (auto w : vec)
            std::cout << w << ' ';
        tree.deleteWord(word);
        vec = tree.sort();
        std::cout << "\n\nAfter:\t";
        for (auto w : vec)
            std::cout << w << ' ';
    }
    
    for (auto word : words)
    {
        if (tree.search(word) == true)
        {
            std::cout << "Found deleted 'word': " << word << std::endl;
            return -1;
        }
    }

    if (tree.height() > -1)
    {
        std::cout << "Tree is not empty after deleting all data. height: " << tree.height() << std::endl;
        return -1;
    }

    return 0;
}