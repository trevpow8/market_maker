cmake_minimum_required(VERSION 3.15)
project(market_maker_sim)

set(CMAKE_CXX_STANDARD 17)

# Set CMAKE_PREFIX_PATH to help find packages
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")

# Find required packages
find_package(cpr REQUIRED)
find_package(nlohmann_json REQUIRED)

add_subdirectory(src)
enable_testing()
add_subdirectory(tests)