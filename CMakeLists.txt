# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("fractional")

# Include sub-projects.
set (BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "")
set (BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "")

add_subdirectory ("benchmark")
add_subdirectory ("catch2")

add_subdirectory ("fractional")
