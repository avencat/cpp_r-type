cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-W -Wall -Wextra -std=c++11")

include_directories(inc ../common/inc)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_BINARY_DIR build)

file(GLOB_RECURSE sources src/*.cpp)
file(GLOB_RECURSE common_sources ../common/src/*.cpp)

add_executable(server ${sources} ${common_sources})

target_link_libraries(server pthread)