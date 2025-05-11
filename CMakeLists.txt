cmake_minimum_required(VERSION 3.30) 

project(Red)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic") # Enable more warnings

include_directories(include)

set(SOURCE_DIRS
    src
)

file(GLOB_RECURSE SOURCE_FILES
    "${SOURCE_DIRS}/*.cc"
)

add_executable(red ${SOURCE_FILES})
