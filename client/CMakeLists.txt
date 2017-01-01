cmake_minimum_required (VERSION 3.0)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-W -Wall -Wextra -std=c++11")

include_directories(inc ../common/inc)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})
set(CMAKE_BINARY_DIR build)

file(GLOB_RECURSE sources src/*.cpp ../common/src/*.cpp)
file(GLOB_RECURSE libs lib/*.so libGLEW.so.1.13)
file(GLOB_RECURSE assets assets/*)

add_executable(client ${sources})

SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
SET(CMAKE_INSTALL_RPATH "lib/")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

target_link_libraries(client ${libs})