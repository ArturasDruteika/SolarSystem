cmake_minimum_required(VERSION 3.24)

project(GraphicalObjects)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DGRAPHICALOBJECTS_EXPORT)

# boost
file(TO_CMAKE_PATH ../../3rdParty/boost_1_79_0/ boost_path)
set(BOOST_DIR ${boost_path})
set(BOOST_ROOT ${boost_path})
set(BOOST_LIB ${boost_path}/lib/)
set(BOOST_INCLUDE_DIR ${boost_path}/include/)
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.79.0 COMPONENTS system filesystem serialization regex REQUIRED)
find_package(OpenMP REQUIRED)

find_package(OpenGL REQUIRED)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(${EXEC_NAME} OpenGL::GL)
if (APPLE)
    # Ignore macOS OpenGL deprecation warnings
    target_compile_definitions(${EXEC_NAME} PRIVATE GL_SILENCE_DEPRECATION)
endif ()

# spdlog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# VTK
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/VTK/ vtk_path)
find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
    message(FATAL_ERROR "GraphicalObjects: Unable to find the VTK build folder.")
endif ()

# VTK
find_package(VTK QUIET)
if (NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found!")
    return()
endif ()


include_directories(
    headers
    ${Boost_INCLUDE_DIR}
    ${VTK_INCLUDES_DIR}
)

add_library(${PROJECT_NAME} SHARED
    headers/Cube.hpp
    src/Cube.cpp
    headers/ObjectBase.hpp
    src/ObjectBase.cpp
    headers/Sphere.hpp
    src/Sphere.cpp
	headers/ColorsVTK.hpp
    # headers/XYZArrows.hpp
    # src/XYZArrows.cpp
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    spdlog::spdlog
    ${Boost_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${VTK_LIBRARIES}
    )

# vtk_module_autoinit is needed
vtk_module_autoinit(
    TARGETS GraphicalObjects
    MODULES ${VTK_LIBRARIES}
)