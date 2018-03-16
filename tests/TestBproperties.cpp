#include "BTree.h"

#include <iostream>
#include <cassert>
#include <vector>
#include <string>

class TestBTree : public BTree
{
public:
    void traverse(BNode* node)
    {
        if (node == nullptr)
            return;

        for (int i = 0; i < node->size_; ++i)
        {
            traverse(node->children_[i]);
        }
        traverse(node->children_[node->size_]);

        int count_data = 0;
        int count_children = 0;
        for (int i = 0; i < this->order_; ++i)
        {
            if (node->data_[i] != nullptr)
                ++count_data;
            if (node->children_[i] != nullptr)
                ++count_children;
        }
        if (node->children_[this->order_] != nullptr)
            ++count_children;

        assert(count_data == node->size_); //check that size is properly tracked
        if (!node->is_leaf_)
            assert(count_children == count_data + 1); //check that there is 1 more child than data members
        else
            assert(count_children == 0);  //check that leaf node has no children
        
        if (!node->is_leaf_ && node != this->root_)
            assert(checkUnderflow(node->size_) == false); //check for underflow in internal nodes

        assert(checkOverflow(node->size_) == false); //check for overflowed node
    }
    void test()
    {
        traverse(this->root_);
    }
};

int main()
{
    using std::string;
    using std::vector;

    TestBTree tree;
    for (int i = 0; i < 1000; ++i)
    {
        vector<char> acc;
        for (int j = 0; j <= i; ++j)
        {
            char rand_char = 'A' + rand() %26;
            acc.push_back(rand_char);
        }
        std::string word(acc.begin(), acc.end());
        tree.insert(word);
    }
    tree.test();
    return 0;
}