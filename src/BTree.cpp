#include "BTree.h"

BNode *& BTree::search(BNode *& root, const std::string & word)
{
    BNode* node;

    return node;
}

void BTree::insert(BNode *& root, BNode*& parent, const std::string & word)
{
    BNode* tmp = new BNode(3, true);
    if (root->is_leaf_)
    {
        //root is the node to insert into
        for (int i = root->number_of_words_ - 1; i >= 0; --i)
        {
            if (root->number_of_words_ == degree_ - 1) //node is full
            {

            }
            else //node is not full
            {
                if (root->words_[i] > word)
                {
                    //shift some words to the right
                }
            }
        }
    }
    else
    {
        //find a leaf to insert into
        for (int i = root->number_of_words_ - 1; i >= 0; --i)
        {
            if (word > root->words_[i])
            {
                insert(root->children_[i+1], root, word);
                break;
            }
        }
    }
}

void BTree::sort(BNode * root, std::vector<std::string>& v)
{
}

void BTree::range(BNode * root, const std::string & word1, const std::string & word2)
{
}

void BTree::deleteWord(BNode *& root, const std::string & word)
{
}

void BTree::split(BNode * parent, BNode * unsplit_node)
{
}

BTree::BTree()
{
    this->root_ = nullptr;
    this->degree_ = 5;
}

BTree::~BTree()
{
}

bool BTree::search(const std::string & word)
{
    return false;
}

void BTree::insert(const std::string & word)
{
    insert(this->root_, this->root_, word);
}

void BTree::deleteWord(const std::string & word)
{
}

std::vector<std::string> BTree::sort()
{
    return std::vector<std::string>();
}

void BTree::range(const std::string & word1, const std::string & word2)
{
}

int BTree::height()
{
    return 0;
}
