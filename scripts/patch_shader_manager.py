#!/usr/bin/env python3

"""
The steps are the following :
    - For each shader, generate the C equivalent with `xxd -i 'shader'.glsl > 'shader'.c`
    - Import those C arrays into the std::aray inside the shader_manager class
    - ????
    - Profit.
"""
"""
IMPORTS
"""
import sys
import fileinput
import glob
from typing import List

"""
FUNCTIONS
"""
def get_shaders(shaders_directory: str) -> List[str]:
    return (glob.glob(shaders_directory + "/*.glsl"))

def get_shader_code(shader_file: str) -> str:
    with open(shader_file, 'r') as file:
        return file.read()

def escape(s: str) -> str:
     return s.translate(str.maketrans({"-":  r"\-",\
                                          "]":  r"\]",\
                                          "\\": r"\\",\
                                          "\n": r"\\n",\
                                          "^":  r"\^",\
                                          "$":  r"\$",\
                                          "*":  r"\*"}))

def get_formatted_array(name: str, code: str) -> str:
    return "\tstd::string %s = \"%s\";" % (name, escape(code))

"""
CODE
"""
shaders_directory = sys.argv[1]
shader_files = get_shaders(shaders_directory)

file_to_patch_name = sys.argv[2]
patched_file_name = file_to_patch_name.replace("topatch", "hpp")

print(shader_files)

shaders = [\
            get_formatted_array(\
                name=shader_file.split("/")[-1].split(".", 1)[0],\
                code=get_shader_code(shader_file)\
                )\
           for shader_file in shader_files]

shaders = "\n".join(shaders)

with open(file_to_patch_name, 'r') as file_to_patch,\
     open(patched_file_name, 'w') as patched_file:

         line = file_to_patch.readline()
         while line :
            #line = line.replace('@@ARRAY_SIZE@@', str(len(shaders)))
            shader_arrays = []
            line = line.replace('@@SHADERS@@', shaders)
            patched_file.write(line)
            line = file_to_patch.readline()

