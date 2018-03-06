#include <string>
#include <cassert>

class BNode
{
public:
    int number_of_words_;
    bool is_leaf_;
    std::string* words_;
    BNode** children_;
    BNode(int degree, bool is_leaf);
};