#include "AVL.h"

AVL::Node*& AVL::AVLTree::search(Node*& root, const std::string & word)
{
    if (root == nullptr)
        return root;

    if (root->word > word)
        return search(root->left, word);
    else if (root->word < word)
        return search(root->right, word);
    else //root->word == word
        return root;
}

int AVL::AVLTree::height(Node * root)
{
    if (root == nullptr)
        return 0;
    else
        return 1 + this->max(height(root->left), height(root->right));
}

int AVL::AVLTree::max(int a, int b)
{
    return (a > b ? a : b);
}

void AVL::AVLTree::balanceTree(Node * root)
{
    if (root == nullptr)
        return;

    int difference = height(root->left) - height(root->right);
    if (difference > 1) //left tree heavy
    {

    }
    else if (difference < -1) //right tree heavy
    {

    }
    else
    {
        //balanced already
    }
}

void AVL::AVLTree::rotateLeft(Node*& root)
{
    if (root == nullptr || root->right == nullptr)
        return;
    
    Node* old_root = root;
    Node* new_root = root->right;
    old_root->right = new_root->left;
    new_root->left = old_root;
    root = new_root;
}

void AVL::AVLTree::rotateRight(Node*& root)
{
    if (root == nullptr || root->left == nullptr)
        return;

    Node* old_root = root;
    Node* new_root = root->left;
    old_root->left = new_root->right;
    new_root->right = old_root;
    root = new_root;
}

AVL::AVLTree::AVLTree()
{
    this->root = nullptr;
}

AVL::AVLTree::~AVLTree()
{
}

bool AVL::AVLTree::search(const std::string & word)
{
    return (this->search(this->root, word) != nullptr);
}

void AVL::AVLTree::insert(const std::string & word)
{
    //find insertion point
    Node*& insert_location = this->search(this->root, word);
    if (insert_location == nullptr)
    {
        insert_location = new Node(word);
        //this->balanceTree(insert_location); TODO -- rebalance at location parent
    }
    else
        ++insert_location->count;
}

void AVL::AVLTree::deleteWord(const std::string & word)
{
}

std::vector<std::string> AVL::AVLTree::sort()
{
    return std::vector<std::string>();
}

std::vector<std::string> AVL::AVLTree::range(const std::string & word1, const std::string & word2)
{
    return std::vector<std::string>();
}
