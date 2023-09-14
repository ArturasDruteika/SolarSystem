cmake_minimum_required(VERSION 3.17.0)

project(imgui)
set(CMAKE_BUILD_PARALLEL_LEVEL)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
set(gl3w_dir ${CMAKE_CURRENT_SOURCE_DIR}/third_party/gl3w)
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

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../imgui/third_party/glfw/)
#target_link_libraries(${EXEC_NAME} glfw)

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
	imgui/
	imgui/examples/
	third_party/glfw/include
	third_party/gl3w/
	third_party/glm-0.9.9.6/
	imgui_vtk/
	${OPENGL_INCLUDE_DIRS}
	${VTK_INCLUDES_DIR}
 )

add_library(
	# ImGui
	imgui 
	imgui/imconfig.h
	imgui/imgui.cpp
	imgui/imgui.h
	imgui/imgui_tables.cpp
	imgui/imgui_demo.cpp
	imgui/imgui_draw.cpp
	imgui/imgui_internal.h
	imgui/imgui_widgets.cpp
	imgui/imstb_rectpack.h
	imgui/imstb_textedit.h
	imgui/imstb_truetype.h
	imgui/backends/imgui_impl_opengl3.cpp
	imgui/backends/imgui_impl_opengl3.h
	imgui/backends/imgui_impl_glfw.cpp
	imgui/backends/imgui_impl_glfw.h

	# ImPlot
	implot/implot.h
	implot/implot.cpp
	implot/implot_internal.h
	implot/implot_items.cpp

	#compile gl3w into executable
	third_party/gl3w/GL/gl3w.c
	third_party/gl3w/GL/gl3w.h
	third_party/gl3w/GL/glcorearb.h

	# ImGuiVTK
	imgui_vtk/VtkViewer.h
	imgui_vtk/VtkViewer.cpp
	imgui_vtk/imgui_vtk_demo.h

	)

target_link_libraries(imgui PRIVATE
	glfw
	${OPENGL_LIBRARIES}
	${VTK_LIBRARIES}
)


