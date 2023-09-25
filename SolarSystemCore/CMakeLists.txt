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
    message(FATAL_ERROR "SolarSystemCore: Unable to find the VTK build folder.")
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


add_library(${PROJECT_NAME} SHARED
    headers/DisplayWindow.hpp
    src/DisplayWindow.cpp
    headers/ContextWindow.hpp
    src/ContextWindow.cpp
    headers/GraphicalRunner.hpp
    src/GraphicalRunner.cpp
    headers/GraphicalRunnerImpl.hpp
    src/GraphicalRunnerImpl.cpp
	headers/VTKWindow.hpp
	src/VTKWindow.cpp
    )

include_directories(
    headers
    ..//imgui//implot//
    ..//imgui//
    ..//imgui//imgui//
    ..//imgui//imgui//examples//
    ..//imgui//imgui//backends//
    ..//imgui//third_party/glfw/include
    ..//imgui//third_party/gl3w/
    ..//imgui//third_party/glm-0.9.9.6/
    ../imgui/imgui_vtk/
    ${stb_image_path}
    ../GraphicalObjects/headers/
    ${VTK_INCLUDES_DIR}
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    imgui
    spdlog::spdlog
    ${OPENGL_LIBRARIES}
    ${VTK_LIBRARIES}
    GraphicalObjects
    ${Boost_LIBRARIES}
    )

add_dependencies(${PROJECT_NAME}
    imgui
    GraphicalObjects
    )