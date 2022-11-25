# CMakeList.txt : CMake project for fractional, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (fract_benchmark "bench.cpp" "fractional.cpp" "fractional.h")
target_link_libraries (fract_benchmark benchmark benchmark_main)

add_executable (fract_test "test.cpp" "fractional.cpp" "fractional.h")
target_link_libraries (fract_test Catch2::Catch2WithMain)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET fract_benchmark PROPERTY CXX_STANDARD 14)
  set_property(TARGET fract_test PROPERTY CXX_STANDARD 14)
endif()

# TODO: Add tests and install targets if needed.
