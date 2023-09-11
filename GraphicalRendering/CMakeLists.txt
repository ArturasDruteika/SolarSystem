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

# OpenGL Loader - GL3W
# This can be replaced with your own OpenGL Loader
# Either compile it as a static library like this example
# Or add it to the source files for the main executable + imgui + vtkviewer
set(gl3w_dir ${CMAKE_CURRENT_SOURCE_DIR}/../imgui/third_party/gl3w)
set(gl3w_inc ${gl3w_dir}/include)
set(gl3w_src ${gl3w_dir}/src/gl3w.c)

if (EXISTS ${gl3w_src})
    message(STATUS "Found gl3w source files")
else ()
    execute_process(COMMAND python3 gl3w_gen.py WORKING_DIRECTORY ${gl3w_dir}) # use python or python3
    if (NOT EXISTS ${gl3w_src})
        message(FATAL_ERROR "Could not generate gl3w source files")
    endif ()
endif ()

add_library(gl3w STATIC ${gl3w_src})
target_include_directories(gl3w PUBLIC ${gl3w_inc})
target_link_libraries(${EXEC_NAME} gl3w)


# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../imgui/third_party/glfw/)
#target_link_libraries(${EXEC_NAME} glfw)


#SPDLOG
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/ spdlog_path)


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
    headers/imgui_vtk_demo.h
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