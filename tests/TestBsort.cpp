#include "BTree.h"

#include <string>
#include <vector>
#include <cassert>

int main()
{
    using std::vector;
    using std::string;

    BTree tree;
    for (int i = 0; i < 1000; ++i)
    {
        vector<char> acc;
        for (int j = 0; j <= i; ++j)
        {
            char rand_char = 'A' + rand() % 26;
            acc.push_back(rand_char);
        }
        std::string word(acc.begin(), acc.end());
        tree.insert(word);
    }

    auto sorted_v = tree.sort();
    for (int i = 1; i < sorted_v.size(); ++i)
    {
        assert(sorted_v[i] > sorted_v[i - 1]);
    }
    return 0;
}