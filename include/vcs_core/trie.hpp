#ifndef TRIE_HPP
#define TRIE_HPP

#include <string>
#include <unordered_map>

namespace vcs_core {

class Trie {
public:
    Trie();
    ~Trie();
    void insert(const std::string& key, const std::string& value);
    std::string get(const std::string& key) const;
private:
    struct TrieNode {
        std::unordered_map<char, TrieNode*> children;
        std::string value;
        TrieNode() = default;
        ~TrieNode() = default;
    };
    TrieNode* root_;
    void delete_node(TrieNode* node);
};

} // namespace vcs_core

#endif // TRIE_HPP