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
import os
from typing import List

"""
FUNCTIONS
"""
def get_formatted_declaration(name: str, code: str) -> str:
    return "std::string %s = \"%s\";\n" % (name, escape(code))

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

def get_shader_decl_from_file(f: str) -> str:
    return get_formatted_declaration(os.path.basename(f).split(".", 1)[0],\
                                     escape(get_shader_code(f)))

def get_shaders(shaders_directory: str) -> str:
    text = ""
    indent = ""
    for root, dirs, files in os.walk(shaders_directory):
        namespace = os.path.basename(root).capitalize()
        text = text + ("%snamespace %s {\n" % (indent, namespace))
        indent = indent + '\t'
        for f in files:
            text = text + ("%s" % indent)
            text = text + get_shader_decl_from_file(os.path.join(root, f))
    while indent != "":
        text = text + ("%s};\n" % indent)
        indent = indent[:-1]
    return text

"""
CODE
"""
shaders_directory = sys.argv[1]
shader_files = get_shaders(shaders_directory)

file_to_patch_name = sys.argv[2]
patched_file_name = file_to_patch_name.replace("topatch", "hpp")

shaders = get_shaders(shaders_directory)

with open(file_to_patch_name, 'r') as file_to_patch,\
     open(patched_file_name, 'w') as patched_file:
         line = file_to_patch.readline()
         while line :
            line = line.replace('@@SHADERS@@', shaders)
            patched_file.write(line)
            line = file_to_patch.readline()

