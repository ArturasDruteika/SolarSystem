cmake_minimum_required(VERSION 3.24)

project(SolarSystemCore)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSOLARSYSTEMCORE_EXPORT)
find_package(OpenGL REQUIRED)

# spdlog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# stb_image
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/stb_image/ stb_image_path)
set(stb_image_includes ${stb_image_path})

include_directories(
    headers
    #    ..//Utils//
    ..//implot//
    ..//imgui//
    ..//imgui//imgui//
    ..//imgui//imgui//examples//
    ..//imgui//third_party/glfw/include
    ..//imgui//third_party/gl3w/
    ..//imgui//third_party/glm-0.9.9.6/
    ${stb_image_path}
)

add_library(${PROJECT_NAME} SHARED
    headers/DisplayWindow.hpp
    src/DisplayWindow.cpp
    headers/ContextWindow.hpp
    src/ContextWindow.cpp
    headers/GraphicalRunner.hpp
    src/GraphicalRunner.cpp
    headers/GraphicalRunnerImpl.hpp
    src/GraphicalRunnerImpl.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui
    spdlog::spdlog
    ${OPENGL_LIBRARIES}
    )

add_dependencies(${PROJECT_NAME}
    imgui
    )