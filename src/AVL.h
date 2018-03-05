#ifndef AVLTREE_H
#define AVLTREE_H

#include <string>
#include <vector>
namespace AVL
{
    struct Node
    {
        std::string word;
        Node* left;
        Node* right;
        unsigned int count;
        Node(const std::string& word)
            : word(word), left(nullptr), right(nullptr), count(1)
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
        int height(Node* root);
        int max(int a, int b);
        void balanceTree(Node* root);
        void rotateLeft(Node*& root);
        void rotateRight(Node*& root);

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
        std::vector<std::string> range(const std::string& word1, const std::string& word2);
    };
}
#endif