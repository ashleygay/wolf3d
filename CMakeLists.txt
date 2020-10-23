cmake_minimum_required(VERSION 3.10)

# set the project name
project(wolf3d)

# Set CPP std to C++20
set(CMAKE_CXX_STANDARD 20)

# Add standard switches
add_compile_options("-Wall")
add_compile_options("-Wextra")
add_compile_options("-Wunused-result")
add_compile_options("-Wpessimizing-move")
add_compile_options("-fconcepts")
add_compile_options("-g")


set(SHADERS_DIRECTORY /home/ferryk/projects/wolf3d/shaders)
set(SCRIPTS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/scripts)

set(SHADER_MANAGER_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/src/shader_manager/shader_manager.hpp)
set(STATIC_ANALYSIS_RESULTS ${CMAKE_CURRENT_SOURCE_DIR}/cppcheck_results.txt)

set(ADDITIONAL_CLEAN_FILES "${ADDITIONAL_CLEAN_FILES} ${SHADER_MANAGER_HEADER}")

add_link_options("-lGL")
add_link_options("-lglfw")
add_link_options("-lfmt")

include_directories("src/shader_manager")

add_custom_target(run "./wolf3d")

set(WOLF3D_SRCS
    ${PROJECT_SOURCE_DIR}/src/main.cpp 
)

# add the executable
add_executable(wolf3d "${WOLF3D_SRCS}" "${SHADER_MANAGER_HEADER}")

add_custom_command (OUTPUT "${SHADER_MANAGER_HEADER}"
	            COMMAND
		    ${CMAKE_CURRENT_SOURCE_DIR}/scripts/patch_shader_manager.py
		    ${SHADERS_DIRECTORY}
		    ${CMAKE_CURRENT_SOURCE_DIR}/src/shader_manager/shader_manager.hpp_to_patch
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)

add_custom_command (OUTPUT "${STATIC_ANALYSIS_RESULTS}"
	            COMMAND
		    cppcheck --std=c++20 --enable=all --verbose --project=${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json > ${CMAKE_CURRENT_SOURCE_DIR}/cppcheck_results.txt)

add_custom_target(
  patch_shader_manager
  ALL
  DEPENDS "${SHADER_MANAGER_HEADER}"
)

add_custom_target(
  static_analysis
  ALL
  DEPENDS "${STATIC_ANALYSIS_RESULTS}"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
