cmake_minimum_required(VERSION 3.24)

project(GraphicalRendering)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DGRAPHICALRENDERING_EXPORT)

find_package(OpenGL REQUIRED)


#SPDLOG
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/ spdlog_path)


# VTK
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/VTK/ vtk_path)
find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
    message(FATAL_ERROR "GraphicalRendering: Unable to find the VTK build folder.")
endif ()

find_package(VTK COMPONENTS
    CommonColor
    CommonCore
    FiltersSources
    InteractionStyle
    RenderingContextOpenGL2
    RenderingCore
    RenderingFreeType
    RenderingGL2PSOpenGL2
    RenderingOpenGL2
    )


include_directories(
    headers
    ..//implot//
    ..//imgui//
    ..//imgui//imgui//
    ..//imgui//imgui//examples//
    ..//imgui//third_party/glfw/include
    ..//imgui//third_party/gl3w/
    ..//imgui//third_party/glm-0.9.9.6/
    ${VTK_INCLUDES_DIR}
)

add_library(${PROJECT_NAME} SHARED
    headers/cube.hpp
    src/cube.cpp
    headers/VtkViewer.h
    src/VtkViewer.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui
    ${OPENGL_LIBRARIES}
    ${VTK_LIBRARIES}
    )

add_dependencies(${PROJECT_NAME}
    imgui
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${VTK_LIBRARIES}
    )

# vtk_module_autoinit is needed
vtk_module_autoinit(
    TARGETS GraphicalRendering
    MODULES ${VTK_LIBRARIES}
)