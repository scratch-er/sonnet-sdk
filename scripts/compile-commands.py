#!/usr/bin/env python3
"""
Generates `compile_commands.json` for LSP support.
Usage: compile-commands.py compiler build_dir cflags ... -- files ...
"""
import json
import sys
import re
import os

# read the command line arguments
cc = sys.argv[1]
build_dir = sys.argv[2]
sep_index = sys.argv.index("--")
cflags = sys.argv[3:sep_index]
files = sys.argv[sep_index+1:]

# get the output file path from input file path for build type "application"
def get_output_file_app(build_dir: str, input_file: str) -> str:
    if input_file.endswith(".c"):
        return re.sub(r'^(.*)\.c$', fr'{build_dir}/objs/\1.o', input_file)
    elif input_file.endswith(".s"):
        return re.sub(r'^(.*)\.s$', fr'{build_dir}/objs/\1.o', input_file)
    else:
        return "/dev/null"

# get one entry in `compile_commands.json` for build type "application"
def get_compile_command_app(cc: str, build_dir: str, input_file: str) -> dict[str, str]:
    output_file = get_output_file_app(build_dir, input_file)
    command = [cc] + cflags + ["-c", "-o"] + [output_file, input_file]
    # quote each entry in the command with single quote
    command = list(map(lambda str: "'{}'".format(str), command))
    return {
        "directory": os.path.abspath(os.path.curdir),
        "command": " ".join(command),
        "file": input_file,
        "output": output_file
    }

compile_command = []
for input_file in files:
    compile_command.append(get_compile_command_app(cc, build_dir, input_file))
with open(os.path.join(build_dir, "compile_commands.json"), "wt") as f:
    json.dump(compile_command, f, indent=4)
