#include "vcs_core/dag.hpp"

namespace vcs_core {

void DAG::add_commit(const std::string& commit_id, const std::string& parent_id) {
    graph_[commit_id].push_back(parent_id);
}

std::vector<std::string> DAG::get_parents(const std::string& commit_id) const {
    auto it = graph_.find(commit_id);
    if (it != graph_.end()) {
        return it->second;
    }
    return {};
}

} // namespace vcs_core