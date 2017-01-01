cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-W -Wall -Wextra -Werror -std=c++11")

include_directories(../../server/inc ../../common/inc)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_BINARY_DIR build)

file(GLOB_RECURSE sources ../../server/src/*.cpp)
list(REMOVE_ITEM sources ${CMAKE_CURRENT_SOURCE_DIR}/../../server/src/main.cpp)
file(GLOB_RECURSE common_sources ../../common/src/*.cpp)

add_executable(level ${sources} ${common_sources} src/main.cpp)

target_link_libraries(level pthread)
