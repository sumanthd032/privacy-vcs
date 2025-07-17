#include "vcs_core/trie.hpp"

namespace vcs_core {

Trie::Trie() : root_(new TrieNode()) {}

Trie::~Trie() {
    delete_node(root_);
}

void Trie::delete_node(TrieNode* node) {
    if (!node) return;
    for (auto& [ch, child] : node->children) {
        delete_node(child);
    }
    delete node;
}

void Trie::insert(const std::string& key, const std::string& value) {
    TrieNode* current = root_;
    for (char c : key) {
        if (!current->children[c]) {
            current->children[c] = new TrieNode();
        }
        current = current->children[c];
    }
    current->value = value;
}

std::string Trie::get(const std::string& key) const {
    TrieNode* current = root_;
    for (char c : key) {
        auto it = current->children.find(c);
        if (it == current->children.end()) {
            return "";
        }
        current = it->second;
    }
    return current->value;
}

} // namespace vcs_core