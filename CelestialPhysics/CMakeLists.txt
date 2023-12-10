cmake_minimum_required(VERSION 3.24)

project(CelestialPhysics)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DCELESTIALPHYSICS_EXPORT)

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
    message(FATAL_ERROR "CelestialPhysics: Unable to find the VTK build folder.")
endif ()

# VTK
find_package(VTK QUIET)
if (NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found!")
    return()
endif ()

add_library(${PROJECT_NAME} SHARED
    headers/Planet.hpp
    src/Planet.cpp
	headers/Star.hpp
    src/Star.cpp
    headers/ObjectsComponents.hpp
	headers/SolarSystemModel.hpp
	src/SolarSystemModel.cpp
    headers/OrbitalMechanics.hpp
    src/OrbitalMechanics.cpp
)

include_directories(
    headers
    ../GraphicalObjects/headers/
    ${VTK_INCLUDES_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    GraphicalObjects
    spdlog::spdlog
    ${OPENGL_LIBRARIES}
    ${VTK_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}
    GraphicalObjects
)

# vtk_module_autoinit is needed
vtk_module_autoinit(
    TARGETS CelestialPhysics
    MODULES ${VTK_LIBRARIES}
)