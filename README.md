Privacy-First Distributed Version Control System
A next-generation Git-like DVCS with privacy-first design, smart scheduling, and dependency graphs.
Features

Local-first version control with optional P2P sync
Graph-based commit history with advanced conflict detection
OS-inspired scheduling for collaborative merges
Lightweight transactional DBMS for metadata
Visual dashboard with D3.js for commit graphs and diffs

Setup

Install CMake, a C++17 compiler, and Git.
Clone the repository: git clone <repo-url>
Create a build directory: mkdir build && cd build
Run CMake: cmake ..
Build: cmake --build .
Run tests: ctest

Project Structure

src/: Backend C++ code (VCS, DBMS, scheduler, server)
web/: Frontend HTML/CSS/JS
tests/: Unit tests
include/: Header files
