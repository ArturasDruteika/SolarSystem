cmake_minimum_required(VERSION 3.24)

project(SolarSystemRendering)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSOLARSYSTEMRENDERING_EXPORT)

find_package(OpenGL REQUIRED)

# spdlog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

# stb_image
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/stb_image/ stb_image_path)
set(stb_image_includes ${stb_image_path})

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

# VTK
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/VTK/ vtk_path)
find_package(VTK REQUIRED)
if (NOT VTK_FOUND)
    message(FATAL_ERROR "SolarSystemRendering: Unable to find the VTK build folder.")
endif ()

# VTK
find_package(VTK QUIET)
if (NOT VTK_FOUND)
    message(FATAL_ERROR "VTK not found!")
    return()
endif ()


add_library(${PROJECT_NAME} SHARED
    headers/ObjectCreationWindow.hpp
    src/ObjectCreationWindow.cpp
    headers/ContextWindow.hpp
    src/ContextWindow.cpp
    headers/GraphicalRunner.hpp
    src/GraphicalRunner.cpp
    headers/GraphicalRunnerImpl.hpp
    src/GraphicalRunnerImpl.cpp
	headers/VTKWindow.hpp
	src/VTKWindow.cpp
	headers/ObjectsInfoWindow.hpp
	src/ObjectsInfoWindow.cpp
	headers/GraphicalWindow.hpp
	src/GraphicalWindow.cpp
    headers/SolarSystemVTKInteractor.hpp
    src/SolarSystemVTKInteractor.cpp
    )

include_directories(
    headers
    ../GraphicalObjects/headers/
    ../CelestialPhysics/headers/
    ..//imgui//implot//
    ..//imgui//
    ..//imgui//imgui//
    ..//imgui//imgui//examples//
    ..//imgui//imgui//backends//
    ..//imgui//third_party/glfw/include
    ..//imgui//third_party/gl3w/
    ..//imgui//third_party/glm-0.9.9.6/
    ..//imgui/imgui_vtk/
    ..//Utils//headers//
    ${stb_image_path}
    ${VTK_INCLUDES_DIR}
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui
    spdlog::spdlog
    GraphicalObjects
    CelestialPhysics
    Utils
    ${Boost_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${VTK_LIBRARIES}
    )

add_dependencies(${PROJECT_NAME}
    imgui
    GraphicalObjects
    CelestialPhysics
    Utils
    )

# vtk_module_autoinit is needed
vtk_module_autoinit(
    TARGETS SolarSystemRendering
    MODULES ${VTK_LIBRARIES}
)