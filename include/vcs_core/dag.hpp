#ifndef DAG_HPP
#define DAG_HPP

#include <string>
#include <vector>
#include <unordered_map>

namespace vcs_core {

class DAG {
public:
    void add_commit(const std::string& commit_id, const std::string& parent_id);
    std::vector<std::string> get_parents(const std::string& commit_id) const;
private:
    std::unordered_map<std::string, std::vector<std::string>> graph_;
};

} // namespace vcs_core

#endif // DAG_HPP