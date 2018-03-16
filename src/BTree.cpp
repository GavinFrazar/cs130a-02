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

    auto& pivot_word = root->data_[i]->word_;
    if (pivot_word > word)
        return search(root->children_[i], word);
    else if (pivot_word < word)
        return search(root->children_[i + 1], word);
    else //pivot_word == word
        return root;
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
        insertHere(root, word);

        //check for node overflow
        if (checkOverflow(root->size_))
            split(root);
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

void BTree::insertHere(BNode * root, const std::string& word)
{
    int i = root->size_;
    while (i >= 0)
    {
        if (root->data_[i] != nullptr)
            if (root->data_[i]->word_ > word)
            {
                //shift stuff right
                root->data_[i + 1] = root->data_[i];
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
}

void BTree::split(BNode * unsplit_node)
{
    int median = order_ / 2;
    BNode*& parent = unsplit_node->parent_;
    std::string word = unsplit_node->data_[median]->word_;

    //check if we are splitting the tree's root
    if (parent == nullptr)
    {
        parent = new BNode(this->order_, false, nullptr);
        this->root_ = parent;
    }

    insertHere(parent, word);
    BNode* left_child = unsplit_node;
    BNode* right_child = new BNode(order_, true, parent);

    //copy elements to the right of the unsplit node's median into a new node
    for (int j = 0; j < median; ++j)
    {
        //copy pointers into right_child
        right_child->data_[j] = left_child->data_[j + median + 1];
        right_child->children_[j + 1] = left_child->children_[j + median + 2];
        right_child->size_ += 1;

        //erase pointers from left_child
        left_child->data_[j + median + 1] = nullptr;
        left_child->children_[j + median + 2] = nullptr;
        left_child->size_ -= 1;
    }

    //copy the last child from left_child to right_child
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

    //find location of the word we just inserted into parent
    int i = parent->size_ - 1;
    while (i >= 0)
    {
        if (parent->data_[i]->word_ == word)
            break;
        --i;
    }
    parent->children_[i] = left_child;
    parent->children_[i + 1] = right_child;

    //check for parent overflow
    if (checkOverflow(parent->size_))
        split(parent);
}

bool BTree::checkUnderflow(int size)
{
    return size < (this->order_ / 2) - 1;
}

bool BTree::checkOverflow(int size)
{
    return size >= this->order_;
}

void BTree::merge(BNode* root)
{
    BNode* parent = root->parent_;
    int pivot;
    for (int i = 0; i <= parent->size_; ++i)
    {
        if (parent->children_[i] == root)
        {
            if (i != 0)
                pivot = i - 1;
            else
                pivot = i;
            break;
        }
    }

    BNode* into = parent->children_[pivot];
    BNode* from = parent->children_[pivot + 1];

    //insert separator into merge node
    into->data_[into->size_] = parent->data_[pivot];
    ++into->size_;

    //insert data into merge node
    for (int i = into->size_; i < into->size_ + from->size_; ++i)
        std::swap(into->data_[i], from->data_[i - into->size_]);

    //insert children into merge node
    for (int i = into->size_; i < into->size_ + from->size_; ++i)
        std::swap(into->children_[i + 1], from->children_[i - into->size_]);

    //update merge node size
    into->size_ += from->size_;

    //destroy empty node
    delete from;
    from = nullptr;

    //shift data left in parent
    for (int k = pivot; k < parent->size_ - 1; ++k)
        parent->data_[k] = parent->data_[k + 1];
    parent->data_[parent->size_ - 1] = nullptr;

    //shift children left in parent
    for (int k = pivot + 1; k <= parent->size_ - 1; ++k)
        parent->children_[k] = parent->children_[k + 1];
    parent->children_[parent->size_] = nullptr;

    //update parent size
    --parent->size_;

    if (checkUnderflow(parent->size_))
        rebalance(parent);
}

void BTree::rebalance(BNode * root)
{
    if (root == this->root_)
    {
        if (root->size_ == 0)
        {
            delete this->root_;
            this->root_ = nullptr;
        }
        return;
    }

    BNode* parent = root->parent_;
    int i;
    for (i = 0; i < parent->size_ + 1; ++i)
        if (parent->children_[i] == root)
            break;

    //check left sibling
    if (i > 0)
    {
        if (!checkUnderflow(parent->children_[i - 1]->size_ - 1))
        {
            rotateWithLeftNeighbor(root);
            return;
        }
    }

    //check right sibling
    if (i < root->size_)
    {
        if (!checkUnderflow(parent->children_[i + 1]->size_ - 1))
        {
            rotateWithRightNeighbor(root);
            return;
        }
    }

    //resort to a merge of siblings
    merge(root);
}

void BTree::rotateWithLeftNeighbor(BNode * deficient_node)
{
    BNode* parent = deficient_node->parent_;
    Data* separator;
    BNode* left_neighbor;
    int i;
    for (i = 1; i <= parent->size_; ++i)
        if (parent->children_[i] = deficient_node)
        {
            separator = parent->data_[i - 1];
            left_neighbor = parent->children_[i - 1];
            break;
        }

    parent->data_[i - 1] = nullptr;
    std::swap(parent->data_[i - 1], left_neighbor->data_[left_neighbor->size_ - 1]);

    shiftContentsRight(deficient_node, 0);
    deficient_node->data_[0] = separator;
    deficient_node->children_[0] = nullptr;
    std::swap(deficient_node->children_[0], left_neighbor->children_[left_neighbor->size_]);
    if (deficient_node->children_[0] != nullptr)
        deficient_node->children_[0]->parent_ = deficient_node;

    --left_neighbor->size_;
    ++deficient_node->size_;
}

void BTree::rotateWithRightNeighbor(BNode * deficient_node)
{
    BNode* parent = deficient_node->parent_;
    BNode* right_neighbor;
    Data* separator;
    int i;
    for (i = 0; i < parent->size_; ++i)
    {
        if (parent->children_[i] == deficient_node)
        {
            right_neighbor = parent->children_[i + 1];
            separator = parent->data_[i];
        }
    }
    
    parent->data_[i] = nullptr;
    std::swap(parent->data_[i], right_neighbor->data_[0]);
    
    int k = deficient_node->size_;
    deficient_node->data_[k] = separator;
    deficient_node->children_[k + 1] = right_neighbor->children_[0];
    if (deficient_node->children_[k + 1] != nullptr)
        deficient_node->children_[k + 1]->parent_ = deficient_node;

    shiftContentsLeft(right_neighbor, 0);
    --right_neighbor->size_;
    ++deficient_node->size_;
}

void BTree::shiftContentsLeft(BNode * root, int start)
{
    int size = root->size_;
    for (int i = start; i < size - 1; ++i)
        root->data_[i] = root->data_[i + 1];
    root->data_[size - 1] = nullptr;

    for (int i = start; i <= size - 1; ++i)
        root->children_[i] = root->children_[i + 1];
    root->children_[size] = nullptr;
}

void BTree::shiftContentsRight(BNode * root, int start)
{
    int size = root->size_;
    for (int i = start; i < size - 1; ++i)
        root->data_[i + 1] = root->data_[i];
    root->data_[start] = nullptr;

    for (int i = start; i <= size - 1; ++i)
        root->children_[i + 1] = root->children_[i];
    root->children_[start] = nullptr;
}

BNode* BTree::findMaxLeaf(BNode * root)
{
    if (root->is_leaf_)
        return root;
    else
        return findMaxLeaf(root->children_[root->size_]);
}

BNode* BTree::findMinLeaf(BNode * root)
{
    if (root->is_leaf_)
        return root;
    else
        return findMinLeaf(root->children_[0]);
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

void BTree::erase(const std::string & word)
{
    BNode* target_node = this->search(this->root_, word);
    if (target_node == nullptr) //not found -- nothing to delete
        return;

    int i = 0;
    for (; i < target_node->size_; ++i)
        if (target_node->data_[i]->word_ == word)
            break;

    Data*& target_data = target_node->data_[i];
    if (target_data == nullptr)
        return;
    if (target_data->count_ > 1)
    {
        --target_data->count_;
        return;
    }

    delete target_data;
    target_data = nullptr;
    if (target_node->is_leaf_)
    {
        shiftContentsLeft(target_node, i);
        --target_node->size_;

        //check for underflow
        if (checkUnderflow(target_node->size_))
            rebalance(target_node);
    }
    else
    {
        //TODO -- internal node deletion
        BNode* max_leaf = findMaxLeaf(target_node->children_[i]);
        std::swap(target_data, max_leaf->data_[max_leaf->size_ - 1]);
        --max_leaf->size_;

        if (checkUnderflow(max_leaf->size_))
            rebalance(max_leaf);
    }

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
