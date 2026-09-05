# Sonnet SDK

Sonnet SDK is a minimal SDK for embedded devices. The main objective of this SDK is demonstrating how an embedded program is built in practical applications.

## Components

Similar with many vendor SKDs, this SDK consists of the components listed below. Like most embedded software running on a microcontroller unit (MCU), this SDK is written in C, and it is designed for applications written in C, since C has become the de facto "cross-platform ABI and low level software description language". This SDK has minimal support for C++, but most standard C++ features are not available.

### Low Level Libraries for Hardware

In this SDK, headers describing the register mapping of peripherals are under `include/periph`. And headers containing the base addresses of peripherals, and some other constants related with a specific SoC are under `include/soc`. Headers under `include/periph` also contain declarations of these functions. And the actual definition of them are under `src/periph`. These functions only work for a single model of peripheral. It is the hardware abstraction layer that provides an interface that works across different models of the same type of peripheral.

### Hardware Abstraction Layer

The hardware abstraction layer (HAL) is a sightly higher level and more unified interface (practically, functions and types) for hardware operations. The source code for the HAL of this SKD is under `src/hal`. Like most other hardware abstraction layers, each family of SoCs has their own HAL implementation in this SDK. See `docs/hal.md` for more detailed information about the HAL of this SDK.

### Board Support Packages

The HAL is not enough to abstract away all the thing on the hardware. After all, a chip does not work alone, it needs to be soldered on a board and connected to many other electronic stuff. On different boards, the same model of chip can be connected to different types of things. For example, different boards with the same chip can use different UART controller as the "default debug UART". Even if the same UART controller is used, which pins are attached to it can also be different across boards. A board support package (BSP) further provides some "basic system functionalities" based on the hardware configuration of a specific board. The interfaces provided by the BSP of this SDK is defined in headers under `include/bsp`. And the source code of each BSP is under `src/bsp`. Please refer to `docs/bsp.md` for the details.

## Building an Application

To build an application with this SDK, simply create a Makefile defining the following variables:

- `APP_SRCS`: A list of the source files in your application. C, C++ and assembly sources are supported.
- `APP_INCLUDE_DIRS`: A list of include directories of the application.
- `MODULES`: A list of directories, each of which contains a Sonnet SDK module. See `docs/module.md` for more details.
- `SONNET_SDK_PATH`: The path to the Sonnet SDK source tree.
- `BSP_PATH`: The path to the board support package.
- `TOOLCHAIN_FILE`: Path to a `.mk` file that defines the toolchain. See `docs/toochain-file.md` for details.
- `APP_BUILD_DIR`: The directory containing the final binaries and intermediate files of your application.

`scripts/application.mk` provides these targets:

- `all`: This is the default target. It will build your application in ELF and binary format. The resulting files will be `$(APP_BUILD_DIR)/application.bin` and`$(APP_BUILD_DIR)/application.elf`.
- `clean`: Removes all build output.
- `compile_commands`: Generate `compile_commands.json` for linting and IDE support.

At the end of the Makefile, include the toolchain file and then include `scripts/application.mk` from this SDK. Please see example project under `examples/`, and read `scripts/application.mk` for more details.

## Abstract Machine Compatible Layer

This SDK has a compatible layer for AM. Most code written for AM should compile and work against this SDK with no modification. You still need to write a `Makefile` according to this SDK's specifications. See the example `microbench`, which is copied from `am-kernels` without modifications, for how to build an AM program against this SDK. The following AM feartures are supported by this SDK:

- TRM: fully supported.
- IOE: only UART and timer are supported.
- CTE: fully supported.
- VME: not supported. Most microcontrollers have no MMU, so VME makes little sense.
- MPE: currently this SDK has no BSP for multicore microcontrollers. Only a dummy implementation of MPE is shipped.

To use the AM compatible layer, you need to add the `compiler-rt` module, and a module to provide a libc.

## Limitations

The core limitation of this SDK comes from the fact that this SDK tries to be low-level while the actual hardware is different, or in another way, different vendors are solving the same problem in different ways. This means that many things **cannot be supported by the HAL**, notably clock configuration, GIPO multiplexing and timer input compare. Please refer to `docs/hal.md` for what is supported, what is not, and why it is hard to support something. After all, we need to accept the fact that, "writing once, running everywhere" is hardly possible for embedding development, where you want to exactly control what happens on the hardware. In the future, these hard-to-support features might be supported by generating vendor-specific code from a markup file.

This SDK is a good starting point of learning embedded development, and it has enough features to fully support the simplest devices, such as an FPGA soft processor core, or a testing chip produced by experimental tape out. Yet, it is not any all-in-one manual for embedded devices. It helps you to see through the seemingly magic of your vendor's development environment, or some tutorials and blogs that only tells you how to do, but not why it is like that. You still need to be familiar with a relatively complicated device from a specific vendor, or perhaps multiple families of devices from different vendors to be able to solve any practical embedded development problems. Because the real world is complicated.

## License

All the source code is licensed under Mulan PSL 2.0, except for 3rd party code with its own license. All the documentations are licensed under Creative Commons 4.0 BY-NC-SA.

## Contributing

Contributions are welcomed! The preferred way to contribute is by submitting pull requests. You can also open issues to report bugs or suggest improvements. Pull requests are accepted on GitLink, Gitee, and GitHub, with GitLink being the preferred platform. Please note that pull requests submitted via GitHub may receive lower priority.

Currently, we are especially looking for contributions in the following areas:

- Adding support for more devices.
- Designing the HAL for more functionalities.
- Support for generating hardware initialization code from markup.
- Improvement in documentation.
- Translating the documentation into Chinese.

Contributors need to follow these guidelines:

- Be friendly, helpful and patient.
- Contributors have the copyright of their contributed content, and license the content under the same license of this repository.
- AI generated content can be accepted, but the quality needs to be guaranteed.
