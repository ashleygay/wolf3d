cmake_minimum_required(VERSION 3.10)

# set the project name
project(wolf3d)

# Set CPP std to C++20
set(CMAKE_CXX_STANDARD 20)

set(SHADERS_DIRECTORY, /home/ferryk/projects/wolf3d/shaders)
set(SCRIPTS_DIRECTORY, ${CMAKE_CURRENT_SOURCE_DIR}/scripts)

add_custom_command (OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/shader_manager/shader_manager.hpp
	            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/scripts/patch_shader_manager.py 
		    ${CMAKE_CURRENT_SOURCE_DIR}/shaders
		    ${CMAKE_CURRENT_SOURCE_DIR}/src/shader_manager/shader_manager.topatch
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)

add_custom_target(
  BuildDocs ALL
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/shader_manager/shader_manager.hpp
)

# Add standard switches
add_compile_options("-Wall")
add_compile_options("-Wextra")

# Set the macro that points to the shader directory.
add_definitions(-D__SHADERS_DIRECTORY=$(SHADERS_DIRECTORY))

# Link against necessary libraries
add_link_options("-lGL")
add_link_options("-lglfw")

# Add include directory
include_directories("include")
include_directories("src/shader_manager")

add_custom_target(run "./wolf3d")

set(WOLF3D_SRCS
${PROJECT_SOURCE_DIR}/src/main.cpp 
${PROJECT_SOURCE_DIR}/src/shader_manager/src/shader_manager.cpp
)
# add the executable
add_executable(wolf3d "${WOLF3D_SRCS}")
