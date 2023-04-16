cmake_minimum_required(VERSION 3.24)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
project(Utils C CXX)
set(CMAKE_BUILD_PARALLEL_LEVEL)

include_directories(
    stb_image
)

#add_library(${PROJECT_NAME})