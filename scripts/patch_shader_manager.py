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
file_to_patch = sys.argv[2]

with fileinput.FileInput(file_to_patch, inplace=True, backup='.bak') as file:
    for line in file:
        print(line.replace("@@SIZE@@", "1"), end='')
        print(line.replace("@@ARRAY@@", "\"Hello there\""), end='')
