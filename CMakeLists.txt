cmake_minimum_required(VERSION 3.10)
project(PrivacyVCS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenSSL
find_package(OpenSSL REQUIRED)
if (OPENSSL_FOUND)
    message(STATUS "Found OpenSSL: ${OPENSSL_VERSION}")
else()
    message(FATAL_ERROR "OpenSSL not found")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include ${OPENSSL_INCLUDE_DIR})

# Explicitly list source files
set(VCS_SOURCES
    ${CMAKE_SOURCE_DIR}/src/vcs_core/vcs_core.cpp
    ${CMAKE_SOURCE_DIR}/src/vcs_core/dag.cpp
    ${CMAKE_SOURCE_DIR}/src/vcs_core/trie.cpp
    ${CMAKE_SOURCE_DIR}/src/vcs_core/sha256.cpp
)
set(DB_SOURCES
    ${CMAKE_SOURCE_DIR}/src/db_core/db_core.cpp
)
set(SCHEDULER_SOURCES
    ${CMAKE_SOURCE_DIR}/src/scheduler/scheduler.cpp
)
set(SERVER_SOURCES
    ${CMAKE_SOURCE_DIR}/src/server/server.cpp
)

# Main executable
add_executable(privacy-vcs
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${VCS_SOURCES}
    ${DB_SOURCES}
    ${SCHEDULER_SOURCES}
    ${SERVER_SOURCES}
)
target_link_libraries(privacy-vcs OpenSSL::SSL OpenSSL::Crypto)

# Testing
enable_testing()
set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/tests/test_main.cpp
    ${CMAKE_SOURCE_DIR}/tests/test_vcs_core.cpp
)
add_executable(tests
    ${TEST_SOURCES}
    ${VCS_SOURCES}
    ${DB_SOURCES}
    ${SCHEDULER_SOURCES}
    ${SERVER_SOURCES}
)
target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/lib/catch2)
target_link_libraries(tests OpenSSL::SSL OpenSSL::Crypto)
add_test(NAME UnitTests COMMAND tests)