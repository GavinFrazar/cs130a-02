#include "BTree.h"

#include <string>
#include <vector>
#include <cassert>

int main()
{
    using std::vector;
    using std::string;

    string word1 = "ant";
    string word2 = "car";

    BTree tree;
    vector<string> expected_output;
    //this loop generates random words, but there will never be any collisions
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

        if (word >= word1 && word <= word2)
            expected_output.push_back(word);
    }

    auto output = tree.range(word1, word2);

    assert(output.size() == expected_output.size()); // make sure it got everything -- if this fails then either the range function is wrong, or some kind of collision happened which shouldn't have happened.
    for (auto data : output)
        assert(data >= word1 && data <= word2); // ensure everything is actually within the range

    return 0;
}