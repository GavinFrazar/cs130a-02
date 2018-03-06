#include "AVLTree.h"

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

int main()
{
    AVLTree tree;
    int power = 10;
    int num = std::pow(2, 10);
    for (int i = 0; i < num; ++i)
    {
        std::vector<char> v;
        for (int j = 0; j < i; ++j)
            v.push_back('a');
        std::string word(v.begin(), v.end());
        tree.insert(word);
    }

    if (tree.height() != power)
    {
        std::cout << "Tree was not balanced correctly. Height was:\t" << tree.height() << ", expected:\t" << power << std::endl;
        return -1;
    }
    return 0;
}