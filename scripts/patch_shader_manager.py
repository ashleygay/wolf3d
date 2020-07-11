#!/usr/bin/env python3

"""
The steps are the following :
    - For each shader, generate the C equivalent with `xxd -i 'shader'.glsl > 'shader'.c`
    - Import those C arrays into the std::aray inside the shader_manager class
    - ????
    - Profit.
"""
import sys
import fileinput

shaders_directory = sys.argv[1]
file_to_patch_name = sys.argv[2]
patched_file_name = file_to_patch_name.replace("topatch", "hpp")

with open(file_to_patch_name, 'r') as file_to_patch,\
     open(patched_file_name, 'w') as patched_file:

         line = file_to_patch.readline()
         while line :
            line = line.replace('@@ARRAY_SIZE@@', '1')
            line = line.replace('@@SHADERS@@', '\"Hello there\"')
            patched_file.write(line)
            line = file_to_patch.readline()
