cmake_minimum_required(VERSION 3.24)

project(SolarSystem)
set(CMAKE_BUILD_PARALLEL_LEVEL)

set(CMAKE_CXX_STANDARD 23)

add_executable(SolarSystem
    main.cpp

    headers/DisplayWindow.hpp
    src/DisplayWindow.cpp

    headers/ContextWindow.hpp
    src/ContextWindow.cpp)

include_directories(
    headers
    ..//implot//
    ..//imgui//
    ..//imgui//imgui//
    ..//imgui//imgui//examples//
    ..//imgui//third_party/glfw/include
    ..//imgui//third_party/gl3w/
    ..//imgui//third_party/glm-0.9.9.6/
    ..//Utils//
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui
    )

add_dependencies(${PROJECT_NAME}
    imgui
    )
