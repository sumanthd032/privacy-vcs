cmake_minimum_required(VERSION 3.15)
project(PrivacyVCS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# External libraries (Crow and Catch2 to be added later)
# For now, set up source files
file(GLOB_RECURSIVE VCS_SOURCES "${CMAKE_SOURCE_DIR}/src/vcs_core/*.cpp")
file(GLOB_RECURSIVE DB_SOURCES "${CMAKE_SOURCE_DIR}/src/db_core/*.cpp")
file(GLOB_RECURSIVE SCHEDULER_SOURCES "${CMAKE_SOURCE_DIR}/src/scheduler/*.cpp")
file(GLOB_RECURSIVE SERVER_SOURCES "${CMAKE_SOURCE_DIR}/src/server/*.cpp")

# Main executable
add_executable(privacy-vcs
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${VCS_SOURCES}
    ${DB_SOURCES}
    ${SCHEDULER_SOURCES}
    ${SERVER_SOURCES}
)

# Testing
enable_testing()
file(GLOB_RECURSIVE TEST_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
add_executable(tests ${TEST_SOURCES})
add_test(NAME UnitTests COMMAND tests)