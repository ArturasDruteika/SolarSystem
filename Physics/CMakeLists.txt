cmake_minimum_required(VERSION 3.24)

project(Physics)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DPHYSICS_EXPORT)

find_package(OpenGL REQUIRED)

# spdlog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

add_library(${PROJECT_NAME} SHARED
	headers/OrbitalMechanics.hpp
	src/OrbitalMechanics.cpp
	headers/OrbitalPoint.hpp
	headers/PhysicalConstants.hpp
	headers/Geometry.hpp
	src/Geometry.cpp
)

include_directories(
    headers
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog::spdlog
)