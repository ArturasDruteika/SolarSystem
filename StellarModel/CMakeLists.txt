cmake_minimum_required(VERSION 3.24)

project(StellarModel)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DSTELLARMODEL_EXPORT)

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

add_library(${PROJECT_NAME} SHARED
    headers/Planet.hpp
    src/Planet.cpp
	headers/Star.hpp
    src/Star.cpp
    headers/ObjectsComponents.hpp
	headers/SolarSystemModel.hpp
	src/SolarSystemModel.cpp
    headers/CosmicBody.hpp
    src/CosmicBody.cpp
    headers/OrbitingBody.hpp
    src/OrbitingBody.cpp
)

include_directories(
    headers
    ..//Physics//headers//
    ${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Physics
    spdlog::spdlog
    ${OPENGL_LIBRARIES}
    ${Boost_LIBRARIES}
)

add_dependencies(${PROJECT_NAME}
    Physics
)