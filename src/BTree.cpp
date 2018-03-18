#include "BTree.h"

BNode * BTree::search(BNode * root, const std::string & word)
{
    if (root == nullptr)
        return root;

    int i = 0;
    for (; i < root->size_; ++i)
    {
        if (word <= root->data_[i]->word_)
            break;
    }

    if (i < root->size_ && root->data_[i]->word_ == word)
        return root;
    else
        return search(root->children_[i], word);
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
        int i = 0;
        for (; i < root->size_; ++i)
        {
            if (word <= root->data_[i]->word_)
                break;
        }

        if (i < root->size_ && root->data_[i]->word_ == word)
        {
            root->data_[i]->count_ += 1;
            return;
        }
        else
        {
            insert(root->children_[i], word);
        }
    }
}

void BTree::insertHere(BNode * root, const std::string& word)
{
    //could put this loop in a findPivot func
    int i = 0;
    for (; i < root->size_; ++i)
    {
        if (word <= root->data_[i]->word_)
            break;
    }

    if (i < root->size_ && root->data_[i]->word_ == word)
    {
        root->data_[i]->count_ += 1;
        return;
    }
    else
    {
        //insert into i
        shiftContentsRight(root, i, i);
        root->data_[i] = new Data(word); //insertion
        root->size_ += 1;
    }
}

void BTree::split(BNode * unsplit_node)
{
    const int median = order_ / 2;
    BNode*& parent = unsplit_node->parent_;
    const auto& word = unsplit_node->data_[median]->word_;

    //check if we are splitting the tree's root
    if (parent == nullptr)
    {
        parent = new BNode(this->order_, false, nullptr);
        this->root_ = parent;
    }

    int i;
    for (i = 0; i < parent->size_; ++i)
        if (word < parent->data_[i]->word_)
            break;

    int separator = i;
    int left = separator;
    int right = separator + 1;

    BNode* left_child = unsplit_node;
    BNode* right_child = new BNode(order_, true, parent);

    //make room to promote median
    shiftContentsRight(parent, separator, right);

    //promote the median
    parent->data_[separator] = left_child->data_[median];
    parent->size_ += 1;
    left_child->data_[median] = nullptr;
    left_child->size_ -= 1;

    //assign parent children
    parent->children_[left] = left_child;
    parent->children_[right] = right_child;

    //copy elements to the right of the unsplit node's median into right child
    for (int j = 0; j < median; ++j)
    {
        //copy pointers into right_child
        right_child->data_[j] = left_child->data_[j + median + 1];
        right_child->children_[j + 1] = left_child->children_[j + median + 2];

        //erase stuff from unsplit node
        left_child->data_[j + median + 1] = nullptr;
        left_child->children_[j + median + 2] = nullptr;

        //update node sizes
        right_child->size_ += 1;
        left_child->size_ -= 1;
    }

    //copy the remaining child from left_child to right_child
    right_child->children_[0] = left_child->children_[median + 1];
    left_child->children_[median + 1] = nullptr;

    //set right_child's leaf status
    right_child->is_leaf_ = left_child->is_leaf_;

    //update all of right_child's children to recognize right_child as their parent (only if right_child is an internal node and actually has children)
    if (!right_child->is_leaf_)
        for (int j = 0; j <= right_child->size_; ++j)
            right_child->children_[j]->parent_ = right_child;

    //check for parent overflow
    if (checkOverflow(parent->size_))
        split(parent);
}

bool BTree::checkUnderflow(int size)
{
    return (size < ((this->order_ / 2) - 1));
}

bool BTree::checkOverflow(int size)
{
    return (size >= this->order_);
}

void BTree::merge(BNode* root)
{
    BNode* parent = root->parent_;
    int pivot;
    for (int i = 0; i <= parent->size_; ++i)
    {
        if (parent->children_[i] == root)
        {
            if (i > 0)
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
    into->size_ += 1;

    //insert data into merge node
    for (int i = into->size_; i < into->size_ + from->size_; ++i)
    {
        into->data_[i] = from->data_[i - into->size_];
        from->data_[i - into->size_] = nullptr;
    }

    //insert children into merge node
    for (int i = into->size_; i <= into->size_ + from->size_; ++i)
    {
        into->children_[i] = from->children_[i - into->size_];
        from->children_[i - into->size_] = nullptr;
    }

    //update merge node size
    into->size_ += from->size_;

    //destroy empty node
    delete from;
    from = nullptr;

    //shift data left in parent
    shiftContentsLeft(parent, pivot, pivot+1);

    //update parent size
    parent->size_ -= 1;

    if (into->is_leaf_ == false)
    {
        for (int i = 0; i <= into->size_; ++i)
            into->children_[i]->parent_ = into;
    }
    if (checkUnderflow(parent->size_))
        rebalance(parent);
}

void BTree::rebalance(BNode * root)
{
    if (root == this->root_)
    {
        if (root->size_ == 0)
        {
            if (this->root_->children_[0] != nullptr)
            {
                this->root_ = this->root_->children_[0];
                this->root_->parent_ = nullptr;
            }
            else
            {
                this->root_ = nullptr;
            }
            delete root;
            root = nullptr;
        }
        return;
    }

    BNode* parent = root->parent_;
    int i;
    for (i = 0; i <= parent->size_; ++i)
        if (parent->children_[i] == root)
            break;

    //check left sibling
    if (i > 0)
    {
        
        if (checkUnderflow(parent->children_[i - 1]->size_ - 1) == false)
        {
            rotateWithLeftNeighbor(root);
            return;
        }
    }

    if (i < parent->size_)    //check right sibling
    {
        if (checkUnderflow(parent->children_[i + 1]->size_ - 1) == false)
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
    BNode* left_neighbor;
    int i;
    for (i = 0; i <= parent->size_; ++i)
    {
        if (parent->children_[i] == deficient_node)
        {
            left_neighbor = parent->children_[i - 1];
            break;
        }
    }

    //demote separator from parent into the deficient node
    shiftContentsRight(deficient_node, 0, 0);
    deficient_node->data_[0] = parent->data_[i - 1];
    deficient_node->size_ += 1;

    //promote max data element from left neighbor into parent
    parent->data_[i - 1] = left_neighbor->data_[left_neighbor->size_ - 1];
    left_neighbor->data_[left_neighbor->size_ - 1] = nullptr;

    //steal the right-most child from left neighbor
    deficient_node->children_[0] = left_neighbor->children_[left_neighbor->size_];
    left_neighbor->children_[left_neighbor->size_] = nullptr;
    left_neighbor->size_ -= 1;

    //if the stolen child was not null, update its parent pointer
    if (deficient_node->children_[0] != nullptr)
        deficient_node->children_[0]->parent_ = deficient_node;
}

void BTree::rotateWithRightNeighbor(BNode * deficient_node)
{
    BNode* parent = deficient_node->parent_;
    BNode* right_neighbor;
    int i;
    for (i = 0; i <= parent->size_; ++i)
    {
        if (parent->children_[i] == deficient_node)
        {
            right_neighbor = parent->children_[i + 1];
            break;
        }
    }

    //demote separator from parent into the deficient node
    deficient_node->data_[deficient_node->size_] = parent->data_[i];
    deficient_node->size_ += 1;

    //steal child from right neighbor
    deficient_node->children_[deficient_node->size_] = right_neighbor->children_[0];
    right_neighbor->children_[0] = nullptr;
    if (deficient_node->children_[deficient_node->size_] != nullptr)
        deficient_node->children_[deficient_node->size_]->parent_ = deficient_node;

    //promote least data element from right neighbor into parent
    parent->data_[i] = right_neighbor->data_[0];
    right_neighbor->data_[0] = nullptr;
    shiftContentsLeft(right_neighbor, 0, 0);
    right_neighbor->size_ -= 1;
}

void BTree::shiftContentsLeft(BNode * root, int data_start, int child_start)
{
    int size = root->size_;
    for (int i = data_start; i < size - 1; ++i)
        root->data_[i] = root->data_[i + 1];
    root->data_[size - 1] = nullptr;

    for (int i = child_start; i < size; ++i)
        root->children_[i] = root->children_[i + 1];
    root->children_[size] = nullptr;
}

void BTree::shiftContentsRight(BNode * root, int data_start, int child_start)
{
    int size = root->size_;

    for (int i = size; i > data_start; --i)
        root->data_[i] = root->data_[i - 1];
    root->data_[data_start] = nullptr;

    for (int i = size + 1; i > child_start; --i)
        root->children_[i] = root->children_[i - 1];
    root->children_[child_start] = nullptr;
}

BNode* BTree::findMaxLeaf(BNode * root)
{
    if (root->is_leaf_ == true)
    {
        return root;
    }
    else
    {
        return findMaxLeaf(root->children_[root->size_]);
    }
}

BNode* BTree::findMinLeaf(BNode * root)
{
    if (root->is_leaf_)
        return root;
    else
        return findMinLeaf(root->children_[0]);
}

void BTree::freeMem(BNode *& root)
{
    if (root == nullptr)
        return;

    for (int i = 0; i < root->size_; ++i)
        delete root->data_[i];

    for (int i = 0; i <= root->size_; ++i)
        freeMem(root->children_[i]);

    delete root;
    root = nullptr;
}

void BTree::deepCopy(BNode *& first, BNode * const & second, BNode* parent)
{
    if (second == nullptr)
        return;

    first = new BNode(order_, second->is_leaf_, parent);
    first->size_ = second->size_;
    for (int i = 0; i < second->size_; ++i)
    {
        first->data_[i] = new Data(second->data_[i]->word_);
        first->data_[i]->count_ = second->data_[i]->count_;
    }

    for (int i = 0; i <= second->size_; ++i)
        deepCopy(first->children_[i], second->children_[i], first);
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
        if (word1 < root->data_[i]->word_)
            range(root->children_[i], word1, word2, v);
        if (word1 <= root->data_[i]->word_ && word2 >= root->data_[i]->word_)
            v.push_back(root->data_[i]->word_);
    }
    if (word2 > root->data_[root->size_ - 1]->word_)
        range(root->children_[root->size_], word1, word2, v); //get the last child's data
}

BTree::BTree()
{
    this->root_ = nullptr;
    this->order_ = 5;
}

BTree::BTree(const BTree & other)
    : BTree()
{
    deepCopy(this->root_, other.root_, nullptr);
}

BTree::BTree(BTree && other)
{
    swap(*this, other);
}

BTree::~BTree()
{
    freeMem(this->root_);
}

BTree & BTree::operator=(BTree rhs)
{
    swap(*this, rhs);
    return *this;
}

bool BTree::search(const std::string & word)
{
    return (this->search(this->root_, word) != nullptr);
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
    if (target_data->count_ > 1)
    {
        target_data->count_ -= 1;
        return;
    }

    delete target_data;
    target_data = nullptr;
    if (target_node->is_leaf_)
    {
        shiftContentsLeft(target_node, i,i);
        target_node->size_ -= 1;

        //check for underflow
        if (checkUnderflow(target_node->size_))
            rebalance(target_node);
    }
    else
    {

        BNode* max_leaf = findMaxLeaf(target_node->children_[i]);
        target_data = max_leaf->data_[max_leaf->size_ - 1];
        max_leaf->data_[max_leaf->size_ - 1] = nullptr;
        max_leaf->size_ -= 1;

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

void swap(BTree & first, BTree & second)
{
    using std::swap;
    swap(first.root_, second.root_);
    swap(first.order_, second.order_);
}
