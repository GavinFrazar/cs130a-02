#include "AVL.h"

#include <cassert>
#include <vector>
#include <string>

using namespace AVL;

class TestAVLTree : public AVLTree
{
    public:
        Node* getRoot() {return this->root;}
};

int main()
{
    TestAVLTree tree;
    for (int i = 0; i < 500; ++i)
    {
        std::vector<char> accumulator;
        for (int j = 0; j < i; ++j)
            accumulator.push_back('a');
        std::string word(accumulator.begin(), accumulator.end());
        tree.insert(word);
    }
    Node* root = tree.getRoot();
    //assert height is always balanced, at each node
    return 0;
}