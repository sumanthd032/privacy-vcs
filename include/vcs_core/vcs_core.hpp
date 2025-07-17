#ifndef VCS_CORE_HPP
#define VCS_CORE_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "vcs_core/dag.hpp"
#include "vcs_core/trie.hpp"
#include "vcs_core/sha256.hpp"

namespace vcs_core {

class VCS {
public:
    VCS(const std::string& repo_path);
    ~VCS(); // Explicit destructor to ensure Trie cleanup
    bool init();
    bool add(const std::string& file_path);
    bool commit(const std::string& message);
private:
    std::string repo_path_;
    std::filesystem::path pvcs_dir_;
    DAG commit_graph_;
    Trie diff_trie_;
    std::unordered_map<std::string, std::string> staged_files_; // file_path -> hash
    std::string current_branch_;
    std::string head_commit_;
    bool save_commit(const std::string& commit_id, const std::string& content);
    bool save_object(const std::string& hash, const std::string& content);
    std::string compute_file_hash(const std::string& file_path);
};

} // namespace vcs_core

#endif // VCS_CORE_HPP