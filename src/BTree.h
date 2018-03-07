#ifndef BTREE_H
#define BTREE_H

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

struct Data
{
public:
    std::string word_;
    int count_;
    Data(const std::string& word)
    {
        word_ = word;
        count_ = 1;
    }
};

struct BNode
{
public:
    int size_;
    bool is_leaf_;
    Data** data_;
    BNode** children_;
    BNode* parent_;
    BNode(int order, bool is_leaf, BNode* parent)
    {
        assert(order > 0);
        data_ = new Data*[order](); //allocate space for order - 1 # of data members, and an overflow slot
        children_ = new BNode*[order+1](); //allocate space for order # of children, and an overflow child
        parent_ = parent;
        is_leaf_ = is_leaf;
        size_ = 0;
    }
};

class BTree
{
private:
protected:
    //fields
    BNode * root_;
    unsigned int order_; //degree of the tree

    //helpers
    BNode*& search(BNode*& root, const std::string& word);
    void insert(BNode* root, const std::string& word);
    void insertHere(BNode* root, const std::string& word, BNode* child);
    void sort(BNode* root, std::vector<std::string>& v);
    void range(BNode* root, const std::string& word1, const std::string& word2);
    void deleteWord(BNode*& root, const std::string& word);
    void split(BNode* unsplit_node);
public:
    //ctor
    BTree();

    //dtor
    ~BTree();

    bool search(const std::string& word);
    void insert(const std::string& word);
    void deleteWord(const std::string& word);
    std::vector<std::string> sort();
    void range(const std::string& word1, const std::string& word2);
    int height();
};
#endif