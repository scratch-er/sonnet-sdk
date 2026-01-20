# Modules

Sonnet SDK provides the modules mechanism to add and manage extra components to your project. A module is a directory containing source files and a `module.mk` providing the build system with information about this module. A module provides static libraries and include directories for a project. They can be pre-built, or built on the fly.

## Adding a Module to Your Project

To add a module into your project, in the Makefile of your project, set the Makefile variable `MODULES` containing a list of module directories, after setting `APP_BUILD_DIR` and `TOOLCHAIN_FILE`, and before including `toolchain.mk` and `application.mk`. The building of the module and include directories will be set up automatically. Please refer to the examples on how to use modules.

There is no limitation where you place the module directory. There is currently no mechanism to manage the dependencies and clashes between modules.

## Creating a Module

To create a module, apart from writing the source files, you need to add a `module.mk` that does the following:

- Append the module's inclusion directory to `MODULE_INCLUDE_DIRS`.
- Append the paths of the module's static libraries to `MODULE_LIBS`.
- Provide a recipe to build the module's static libraries, if the static libraries are built on the fly. All the intermediate and resulting files should reside in a subdirectory of `APP_BUILD_DIR` in this case.

Please refer to the built-in modules for writing a `module.mk`. Also refer to `scripts/application.mk` for how a module works.

## Built-in Modules

There are some built-in modules under the `modules/` directory:

- `compiler-rt`: Port of `compiler-rt` for embedded devices. It provides low-level arithmetic and helper functions that compilers typically need when generating code for operations that aren't directly supported by hardware, for example, integer division, floating point operations.
- `lightio`: An light-weight alternative of `stdio`. It provides integer and string input/output functions.
- `sonnet-libc`: A minimal libc implementation, with only most common features supported.

They are git submodules of this repository. To correctly initialize them, use `git clone --recursive` when cloning this repository, or run the following command in this repository after cloning:

```sh
git submodule update --init
``
