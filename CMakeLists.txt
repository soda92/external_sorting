cmake_minimum_required(VERSION 2.10)
project(practices)

add_executable(mergesort mergesort.cpp)
add_executable(generate_random generate_random.cpp)

find_package(absl CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
add_executable(hello_world hello_world.cc)

# Declare dependency on the absl::strings library
target_link_libraries(hello_world absl::strings fmt::fmt)
