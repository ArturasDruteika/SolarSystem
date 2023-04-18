cmake_minimum_required(VERSION 3.24)

project(SolarSystem)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# spdlog
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/lib/cmake/spdlog/ spdlog_path)
set(spdlog_DIR ${spdlog_path})
find_package(spdlog REQUIRED)

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
    spdlog::spdlog
    )

add_dependencies(${PROJECT_NAME}
    imgui
    )

### Post builds
# SPDLog
add_custom_command(TARGET SolarSystem POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different
    ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
    $<TARGET_FILE_DIR:SolarSystem>)
