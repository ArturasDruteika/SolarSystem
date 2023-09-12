cmake_minimum_required(VERSION 3.24)

project(GraphicalRendering)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DGRAPHICALRENDERING_EXPORT)

find_package(OpenGL REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

# VTK
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/VTK/ vtk_path)
find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
    message(FATAL_ERROR "GraphicalRendering: Unable to find the VTK build folder.")
endif ()

# VTK
find_package(VTK COMPONENTS
    CommonCore
    CommonColor
    CommonDataModel
    FiltersCore
    InteractionStyle
    RenderingCore
    RenderingFreeType
    RenderingGL2PSOpenGL2
    RenderingOpenGL2
    QUIET
    )
if (NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found!")
    return()
endif ()


include_directories(
    headers
    ${VTK_INCLUDES_DIR}
)

add_library(${PROJECT_NAME} SHARED
    headers/cube.hpp
    src/cube.cpp
    # headers/VtkViewer.h
    # src/VtkViewer.cpp
    # headers/imgui_vtk_demo.h
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${OPENGL_LIBRARIES}
    ${VTK_LIBRARIES}
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${VTK_LIBRARIES}
    )

# vtk_module_autoinit is needed
vtk_module_autoinit(
    TARGETS GraphicalRendering
    MODULES ${VTK_LIBRARIES}
)