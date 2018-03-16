#include "AVLTree.h"

Node*& AVLTree::search(Node*& root, const std::string & word)
{
    if (root == nullptr)
        return root;

    if (word > root->word)
        return search(root->right, word);
    else if (word < root->word)
        return search(root->left, word);
    else //root->word == word
        return root;
}

void AVLTree::insert(Node *& root, const std::string & word)
{
    if (root == nullptr)
        root = new Node(word);
    else if (word < root->word)
        insert(root->left, word);
    else if (word > root->word)
        insert(root->right, word);
    else
        ++root->count;

    updateHeight(root);
    this->balanceTree(root);
}

void AVLTree::sort(Node * root, std::vector<std::string>& v)
{
    if (root == nullptr)
        return;

    sort(root->left, v);
    v.push_back(root->word);
    sort(root->right, v);
}

void AVLTree::range(Node * root, const std::string & word1, const std::string & word2, std::vector<std::string>& v)
{
    if (root == nullptr)
        return;

    if (root->word < word1)
        range(root->right, word1, word2, v);
    else if (root->word > word2)
        range(root->left, word1, word2, v);
    else
    {
        range(root->left, word1, word2, v);
        v.push_back(root->word);
        range(root->right, word1, word2, v);
    }
}

void AVLTree::erase(Node *& root, const std::string & word)
{
    if (root == nullptr)
        return;
    if (word < root->word)
        erase(root->left, word);
    else if (word > root->word)
        erase(root->right, word);
    else
    {
        if (root->count > 1)
        {
            --root->count;
        }
        else
        {
            //two children
            if (root->left != nullptr && root->right != nullptr)
            {
                Node* min_from_right = root->right;
                while (min_from_right->left != nullptr)
                {
                    min_from_right = min_from_right->left;
                }
                //copy the minimum from root->right into root
                root->word = min_from_right->word;
                root->count = min_from_right->count;
                min_from_right->count = 0;
                erase(root->right, root->word);
            }
            else if (root->left != nullptr) //only a left child
            {
                Node* target = root;
                root = target->left;
                delete target;
            }
            else if (root->right != nullptr) //one right child
            {
                Node* target = root;
                root = target->right;
                delete target;
            }
            else
            {
                delete root;
                root = nullptr;
            }
        }
    }
    updateHeight(root);
    balanceTree(root);
}

int AVLTree::height(Node * root)
{
    if (root == nullptr)
        return -1;
    else
        return root->height;
}

void AVLTree::updateHeight(Node * root)
{
    if (root == nullptr)
        return;

    root->height = 1 + max(height(root->left), height(root->right));
}

int AVLTree::max(int a, int b)
{
    return (a > b ? a : b);
}

void AVLTree::balanceTree(Node*& root)
{
    int difference = checkBalance(root);
    if (difference > 1) //left tree heavy
    {
        //left-left case
        if (checkBalance(root->left) > 0)
        {
            rotateRight(root);
        }
        else //left-right case
        {
            rotateLeft(root->left);
            rotateRight(root);
        }
    }
    else if (difference < -1) //right tree heavy
    {
        if (checkBalance(root->right) < 0) //right-right case
        {
            rotateLeft(root);
        }
        else //right-left case
        {
            rotateRight(root->right);
            rotateLeft(root);
        }
    }
}

void AVLTree::rotateLeft(Node*& root)
{
    if (root == nullptr || root->right == nullptr)
        return;

    Node* old_root = root;
    Node* new_root = root->right;
    old_root->right = new_root->left;
    new_root->left = old_root;
    updateHeight(old_root);
    updateHeight(new_root);
    root = new_root;
}

void AVLTree::rotateRight(Node*& root)
{
    if (root == nullptr || root->left == nullptr)
        return;

    Node* old_root = root;
    Node* new_root = root->left;
    old_root->left = new_root->right;
    new_root->right = old_root;
    updateHeight(old_root);
    updateHeight(new_root);
    root = new_root;
}

void AVLTree::deleteNode(Node *& root)
{
    if (root == nullptr)
        return;

    delete root;
    root = nullptr;
}

int AVLTree::checkBalance(Node *& root)
{
    if (root == nullptr)
        return 0;

    return height(root->left) - height(root->right);
}


AVLTree::AVLTree()
{
    this->root = nullptr;
}

AVLTree::~AVLTree()
{
    Node* target = this->root;
    while (target != nullptr)
    {
        deleteNode(target->left);
        deleteNode(target->right);
        deleteNode(target);
    }
}

bool AVLTree::search(const std::string & word)
{
    return (this->search(this->root, word) != nullptr);
}

void AVLTree::insert(const std::string & word)
{
    this->insert(root, word);
}

void AVLTree::erase(const std::string & word)
{
    this->erase(this->root, word);
}

std::vector<std::string> AVLTree::sort()
{
    std::vector<std::string> v;
    sort(this->root, v);
    return v;
}

std::vector<std::string> AVLTree::range(const std::string & word1, const std::string & word2)
{
    std::vector<std::string> v;
    this->range(this->root, word1, word2, v);
    return v;
}

int AVLTree::height()
{
    return this->root == nullptr ? -1 : this->root->height;
}
