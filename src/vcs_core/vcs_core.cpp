#include "vcs_core/vcs_core.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace vcs_core {

VCS::VCS(const std::string& repo_path) : repo_path_(repo_path), pvcs_dir_(repo_path + "/.pvcs"), diff_trie_() {}

VCS::~VCS() = default;

bool VCS::init() {
    try {
        fs::create_directory(pvcs_dir_);
        fs::create_directory(pvcs_dir_ / "objects");
        fs::create_directory(pvcs_dir_ / "refs");
        fs::create_directory(pvcs_dir_ / "refs" / "heads");
        current_branch_ = "main";
        std::ofstream head_file(pvcs_dir_ / "HEAD");
        head_file << "ref: refs/heads/main";
        head_file.close();
        std::ofstream branch_file(pvcs_dir_ / "refs" / "heads" / "main");
        branch_file.close();
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Init failed: " << e.what() << std::endl;
        return false;
    }
}

bool VCS::add(const std::string& file_path) {
    if (!fs::exists(file_path)) {
        std::cerr << "File does not exist: " << file_path << std::endl;
        return false;
    }
    std::string hash = compute_file_hash(file_path);
    if (hash.empty()) {
        std::cerr << "Failed to compute hash for: " << file_path << std::endl;
        return false;
    }
    
    // Store file content as object
    std::ifstream file(file_path, std::ios::binary);
    std::stringstream buffer;
    buffer << file.rdbuf();
    if (!save_object(hash, buffer.str())) {
        std::cerr << "Failed to save object for: " << file_path << std::endl;
        return false;
    }
    
    // Add to trie and staging area
    diff_trie_.insert(file_path, buffer.str());
    staged_files_[file_path] = hash;
    return true;
}

bool VCS::commit(const std::string& message) {
    if (staged_files_.empty()) {
        std::cerr << "No files staged for commit" << std::endl;
        return false;
    }
    
    // Create commit object
    std::stringstream commit_data;
    commit_data << "parent " << head_commit_ << "\n";
    for (const auto& [file_path, hash] : staged_files_) {
        commit_data << "file " << file_path << " " << hash << "\n";
    }
    commit_data << "message " << message;
    
    std::string commit_id = sha256(commit_data.str());
    if (!save_commit(commit_id, commit_data.str())) {
        std::cerr << "Failed to save commit: " << commit_id << std::endl;
        return false;
    }
    
    // Update DAG and HEAD
    commit_graph_.add_commit(commit_id, head_commit_);
    head_commit_ = commit_id;
    
    // Update branch ref
    std::ofstream branch_file(pvcs_dir_ / "refs" / "heads" / current_branch_);
    branch_file << commit_id;
    branch_file.close();
    
    staged_files_.clear();
    return true;
}

bool VCS::save_commit(const std::string& commit_id, const std::string& content) {
    return save_object(commit_id, content);
}

bool VCS::save_object(const std::string& hash, const std::string& content) {
    try {
        fs::path object_path = pvcs_dir_ / "objects" / hash.substr(0, 2) / hash.substr(2);
        fs::create_directories(object_path.parent_path());
        std::ofstream file(object_path, std::ios::binary);
        file << content;
        file.close();
        return true;
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Save object failed: " << e.what() << std::endl;
        return false;
    }
}

std::string VCS::compute_file_hash(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file) return "";
    std::stringstream buffer;
    buffer << file.rdbuf();
    return sha256(buffer.str());
}

} // namespace vcs_core