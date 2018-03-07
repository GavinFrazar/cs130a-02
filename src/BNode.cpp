#include "BNode.h"

BNode::BNode(int degree, bool is_leaf)
{
    
    assert(degree > 1);
    words_ = new std::string[degree - 1](); //allocate space for degree -1 data members
    children_ = new BNode*[degree]();
}