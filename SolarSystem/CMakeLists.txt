cmake_minimum_required(VERSION 3.24)

project(SolarSystem)
set(CMAKE_BUILD_PARALLEL_LEVEL)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/icon.rc")

#SPDLOG
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/ spdlog_root_path)
file(TO_CMAKE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdParty/spdlog-1.x/ spdlog_path)

add_executable(SolarSystem
    main.cpp
    icon.rc
    )

include_directories(
    ../SolarSystemCore/headers/
)

add_dependencies(${PROJECT_NAME}
    SolarSystemCore
    )

target_link_libraries(${PROJECT_NAME} PRIVATE
    SolarSystemCore
    )

### Post builds
# SPDLog
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_if_different
    ${spdlog_root_path}//bin//$<$<CONFIG:debug>:spdlogd.dll>$<$<CONFIG:release>:spdlog.dll>
    $<TARGET_FILE_DIR:${PROJECT_NAME}>)

#Resources
#Create directory and copy files
file(TO_CMAKE_PATH $<TARGET_FILE_DIR:${PROJECT_NAME}>//res// resource_path)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${resource_path})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory
    ${CMAKE_SOURCE_DIR}//res//
    ${resource_path})

#additional copy for visual studio near project
file(TO_CMAKE_PATH $<TARGET_FILE_DIR:${PROJECT_NAME}>//..//${PROJECT_NAME}//res// resource_vs_path)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${resource_vs_path})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} ARGS -E copy_directory
    ${CMAKE_SOURCE_DIR}//res//
    ${resource_vs_path})
