#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>
#include <iostream>

namespace AVL
{
    struct Node
    {
        std::string word;
        Node* left;
        Node* right;
        unsigned int count;
        int height;
        Node(const std::string& word)
            : word(word), left(nullptr), right(nullptr), count(1), height(0)
        {}
    };

    class AVLTree
    {
    private:

    protected:
        //fields
        Node * root;

        //helpers
        Node*& search(Node*& root, const std::string& word);
        void insert(Node*& root, const std::string& word);
        void sort(Node* root, std::vector<std::string>& v);
        void range(Node* root, const std::string& word1, const std::string& word2);
        void deleteWord(Node*& root, const std::string& word);
        int height(Node* root);
        void updateHeight(Node* root);
        int max(int a, int b);
        void balanceTree(Node*& root);
        void rotateLeft(Node*& root);
        void rotateRight(Node*& root);
        void deleteNode(Node*& root);
        int checkBalance(Node*& root);
    public:
        //ctor
        AVLTree();

        //dtor
        ~AVLTree();

        //methods
        bool search(const std::string& word);
        void insert(const std::string& word);
        void deleteWord(const std::string& word);
        std::vector<std::string> sort();
        void range(const std::string& word1, const std::string& word2);
    };
}
#endif