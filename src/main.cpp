#include "vcs_core/vcs_core.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <command> [args...]" << std::endl;
        return 1;
    }

    vcs_core::VCS vcs(".");
    std::string command = argv[1];

    if (command == "init") {
        if (vcs.init()) {
            std::cout << "Initialized empty Privacy VCS repository in .pvcs" << std::endl;
        } else {
            std::cerr << "Failed to initialize repository" << std::endl;
            return 1;
        }
    } else if (command == "add" && argc == 3) {
        if (vcs.add(argv[2])) {
            std::cout << "Added " << argv[2] << " to staging" << std::endl;
        } else {
            std::cerr << "Failed to add " << argv[2] << std::endl;
            return 1;
        }
    } else if (command == "commit" && argc == 3) {
        if (vcs.commit(argv[2])) {
            std::cout << "Committed with message: " << argv[2] << std::endl;
        } else {
            std::cerr << "Failed to commit" << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Unknown command or invalid arguments" << std::endl;
        return 1;
    }

    return 0;
}