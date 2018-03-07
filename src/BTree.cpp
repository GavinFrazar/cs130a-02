#include "BTree.h"

BNode *& BTree::search(BNode *& root, const std::string & word)
{
    if (root == nullptr)
        return root;
    int i = 0;
    for (; i < root->size_ - 1; ++i)
    {
        if (root->data_[i + 1]->word_ > word)
            break;
    }
    if (root->data_[i]->word_ == word)
        return root;
    else
        search(root->children_[i + 1], word);
}

void BTree::insert(BNode * root, const std::string & word)
{
    if (this->root_ == nullptr)
    {
        this->root_ = new BNode(this->order_, true, nullptr);
        this->root_->data_[0] = new Data(word);
        this->root_->size_ += 1;
        return;
    }
    else if (root->is_leaf_)
    {
        //root is the leaf node to insert into
        insertHere(root, word, nullptr);
    }
    else
    {
        //find a leaf node to insert into
        int i = root->size_ - 1;
        while (i >= 0 && root->data_[i]->word_ >= word)
        {
            if (root->data_[i]->word_ == word)
            {
                root->data_[i]->count_ += 1;
                return;
            }
            --i;
        }
        insert(root->children_[i + 1], word);
    }
}

void BTree::insertHere(BNode * root, const std::string& word, BNode* left_child)
{
    int i = root->size_;
    while (i >= 0)
    {
        if (root->data_[i] != nullptr)
            if (root->data_[i]->word_ > word)
            {
                root->data_[i + 1] = root->data_[i]; //shift stuff right
                root->children_[i + 2] = root->children_[i + 1];
            }
            else if (root->data_[i]->word_ == word)
            {
                root->data_[i]->count_ += 1;
                return;
            }
            else //found spot to insert
                break;
        --i;
    }
    root->data_[i + 1] = new Data(word); //insert
    root->size_ += 1;

    //left child is (or should be) in slot i+1, right child will be in slot i+2
    root->children_[i + 1] = left_child;

    //this insert must be the result of a split
    if (left_child != nullptr)
    {
        BNode* right_child = new BNode(order_, true, root);
        int median = order_ / 2;
        //copy elements to the right of old_child median into new_child
        for (int j = 0; j < median; ++j)
        {
            right_child->data_[j] = left_child->data_[j + median + 1];
            right_child->children_[j + 1] = left_child->children_[j + median + 2];
            //erase duplicate pointers from left_child
            left_child->data_[j + median + 1] = nullptr;
            left_child->children_[j + median + 2] = nullptr;
            left_child->size_ -= 1;
            right_child->size_ += 1;
        }

        //copy and then erase median's right child from left_child
        right_child->children_[0] = left_child->children_[median + 1];
        left_child->children_[median + 1] = nullptr;

        //erase median pointer from left_child
        delete left_child->data_[median];
        left_child->data_[median] = nullptr;
        left_child->size_ -= 1;

        //set right_child's leaf status
        right_child->is_leaf_ = left_child->is_leaf_;

        //update all of right_child's children to recognize right_child as their parent (only if right_child is an internal node and actually has children)
        if (!right_child->is_leaf_)
            for (int i = 0; i < right_child->size_ + 1; ++i)
                right_child->children_[i]->parent_ = right_child;
        root->children_[i + 2] = right_child;
    }

    if (root->size_ == order_) //we overflowed the node
        split(root);
}

void BTree::split(BNode * unsplit_node)
{
    int median = order_ / 2;
    if (unsplit_node->parent_ == nullptr) //insert into the root
    {
        this->root_ = new BNode(this->order_, false, nullptr);
        unsplit_node->parent_ = this->root_;
        insertHere(this->root_, unsplit_node->data_[median]->word_, unsplit_node);
    }
    else
    {
        insertHere(unsplit_node->parent_, unsplit_node->data_[median]->word_, unsplit_node);
    }
}

void BTree::sort(BNode * root, std::vector<std::string>& v)
{
    if (root == nullptr)
        return;
    for (int i = 0; i < root->size_; ++i)
    {
        sort(root->children_[i], v);
        v.push_back(root->data_[i]->word_);
    }
    sort(root->children_[root->size_], v); //get the last child's data
}

void BTree::range(BNode * root, const std::string & word1, const std::string & word2, std::vector<std::string>& v)
{
    if (root == nullptr)
        return;
    for (int i = 0; i < root->size_; ++i)
    {
        if (root->data_[i]->word_ > word1)
            range(root->children_[i], word1, word2, v);
        if (root->data_[i]->word_ >= word1 && root->data_[i]->word_ <= word2)
            v.push_back(root->data_[i]->word_);
    }
    if (root->data_[root->size_ - 1]->word_ < word2)
        range(root->children_[root->size_], word1, word2, v); //get the last child's data
}

void BTree::deleteWord(BNode *& root, const std::string & word)
{
}

BTree::BTree()
{
    this->root_ = nullptr;
    this->order_ = 5;
}

BTree::~BTree()
{
}

bool BTree::search(const std::string & word)
{
    return this->search(this->root_, word) != nullptr;
}

void BTree::insert(const std::string & word)
{
    insert(this->root_, word);
}

void BTree::deleteWord(const std::string & word)
{
}

std::vector<std::string> BTree::sort()
{
    std::vector<std::string> sorted_v;
    this->sort(this->root_, sorted_v);
    return sorted_v;
}

std::vector<std::string> BTree::range(const std::string & word1, const std::string & word2)
{
    std::vector<std::string> sorted_v;
    this->range(this->root_, word1, word2, sorted_v);
    return sorted_v;
}
