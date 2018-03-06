#ifndef BTREE_H
#define BTREE_H

#include <string>
#include <vector>
#include <iostream>
#include <cassert>

#include "BNode.h"

class BTree
{
private:
protected:
    //fields
    BNode * root_;
    unsigned int degree_; //degree of the tree

    //helpers
    BNode*& search(BNode*& root, const std::string& word);
    void insert(BNode*& root, BNode*& parent, const std::string& word);
    void sort(BNode* root, std::vector<std::string>& v);
    void range(BNode* root, const std::string& word1, const std::string& word2);
    void deleteWord(BNode*& root, const std::string& word);
    void split(BNode* parent, BNode* unsplit_node);
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