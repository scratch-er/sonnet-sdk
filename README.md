# Sonnet SDK

Sonnet SDK is a minimal SDK for embedded devices. The main objective of this SDK is demonstrating how an embedded program is built in practical applications.

## Components

Similar with many vendor SKDs, this SDK consists of the components listed below. Like most embedded software running on a microcontroller unit (MCU), this SDK is written in C, and it is designed for applications written in C, since C has become the de facto "cross-platform ABI and low level software description language", although it has been possible to do serious embedded developing in Zig and Rust. Python and Lua have been ported to microcontrollers, but they are mostly for hobbyists and are usually not that useful in practical MCU projects. JavaScript and WASM can also run on microcontrollers, but their application in the embedded world are mostly limited with Internet of things (IoT).

### Low Level Libraries for Hardware

Modern microcontrollers use memory mapped IO to talk with peripherals. This means that they are accessing the peripherals with exactly the same instructions used to access memory, as if the data read from and transmitted to the peripherals is just data stored in the memory. Each entry of data, which can be read or written to manipulate the peripheral, is called a register. For example, this is the memory mapping of a UART peripheral:

| Register  | Address      | Description           |
|-----------|--------------|-----------------------|
| `clk_div` | `0x03000010` | Clock divider.        |
| `data`    | `0x03000014` | Send or receive data. |

To transmit or receive data, you can just write:

```c
// Transmit a frame of data
*((volatile uint32_t*)0x03000014) = data_to_send;

// Receive a frame of data
received_data = *((volatile uint32_t*)0x03000014);
```

But this is way too messy. Since input and output are memory mapped, the mapping (offset and word length) of the registers (often placed in continuous memory addresses) can be described by a C structure. And since different device from a same vendor usually have peripherals with the same mappings but different base addresses (the lowest address among the registers), the definitions of the structures can be reused. For the UART above, you can alternatively write:

```c
// In the header for the peripheral
typedef struct {
    volatile uint32_t clkdiv __attribute__((__aligned__(4)));
    volatile uint32_t data __attribute__((__aligned__(4)));
} __attribute__((__packed__)) retrosoc_sysuart_map_t;

// In the header for the SoC
#define SYSUART ((retrosoc_sysuart_map_t*) 0x03000010)

// In your application code
SYSUART->data = data_to_send;
received_data = SYSUART->data;
```

This is what most vendor SDKs do for a specific model of peripheral and a specific family of devices. In this SDK, headers describing the register mapping of peripherals are under `include/periph`. And headers containing the base addresses of peripherals, and some other constants related with a specific SoC are under `include/soc`. It is cleaner than directly operating on the addresses. Still, it will be not intuitive if the peripheral grows more complicated. In this example, it is a very simple UART with only two registers, and each of the registers has very intuitive meaning. But in practical cases, a peripheral may come with decades of registers, and each register can consist of many bit fields indicating different status (those are too complicated for an example here). So we can define some peripheral specific functions to do the job:

```c
uint32_t retrosoc_sysuart_read(retrosoc_sysuart_map_t *uart_periph) {
    return uart_periph->data;
}

void retrosoc_sysuart_write(retrosoc_sysuart_map_t *uart_periph, uint32_t data) {
    uart_periph->data = data;
}

void retrosoc_sysuart_config_baudrate(retrosoc_sysuart_map_t *uart_periph, uint32_t baudrate_hz, uint32_t periph_freq) {
    uart_periph->clkdiv = periph_freq / baudrate_hz;
}
```

Headers under `include/periph` also contain declarations of these functions. And the actual definition of them are under `src/periph`. Still, these functions only work for a single model of peripheral. It is the hardware abstraction layer that provides an interface that works across different models of the same type of peripheral.

### Hardware Abstraction Layer

The hardware abstraction layer (HAL) is a sightly higher level and more unified interface (practically, functions and types) for hardware operations. It lets the developer handle peripheral operations easier, makes the code cleaner and a little bit more portable across devices. Although "write once, run anywhere" is still hardly practical in embedded developing.

In vendor SDKs, the HAL is usually designed to provide a unified interface across different families of devices from that vendor. Different families of devices from the same vendor usually share the IP cores of the peripherals. This means that the register mappings of the same type of peripherals are usually the same or very similar. However, different devices have different peripherals available, and the clock tree, bus layout and interrupts can vary a lot. The HAL is usually designed to abstract away these differences, and provide some advanced functionalities like IO buffering, interrupt handling and DMA management. So the developers can make use of all the advanced features of the hardware while not being messed up with too many details in the hardware configuration.

On the other hand, a cross-vendor HAL, including Arduino, the device framework of RT-Thread, the HAL of Zephyr RTOS, and the HAL of this SDK, is attempting to provide a unified interface for the same type of peripheral across different vendors. This is a more challenging than designing the vendor HAL, as the same type of peripheral from different vendors can be fundamentally different. So a cross-vendor HAL either lacks advanced features, or is a lot of bloat.

The source code for the HAL of this SKD is under `src/hal`. Like most other hardware abstraction layers, each family of SoCs has their own HAL implementation in this SDK. See `docs/hal.md` for more detailed information about the HAL of this SDK.

### Board Support Packages

The HAL is not enough to abstract away all the thing on the hardware. After all, a chip does not work alone, it needs to be soldered on a board and connected to many other electronic stuff. On different boards, the same model of chip can be connected to different types of things. For example, different boards with the same chip can use different UART controller as the "default debug UART". Even if the same UART controller is used, which pins are attached to it can also be different across boards. A board support package (BSP) further provides some "basic system functionalities" based on the hardware configuration of a specific board. The interfaces provided by the BSP of this SDK is defined in headers under `include/bsp`. And the source code of each BSP is under `src/bsp`. Please refer to `docs/bsp.md` for the details.

## Building an Application

To build an application with this SDK, simply create a Makefile defining the following variables:

- `APP_SRCS`: A list of the source files in your application.
- `SONNET_SDK_PATH`: The path to the Sonnet SDK source tree.
- `BSP_PATH`: The path to the board support package.
- `TOOLCHAIN_FILE`: Path to a `.mk` file that defines the toolchain. See `docs/toochain-file.md` for details.
- `APP_BUILD_DIR`: The directory containing the final binaries and intermediate files of your application.

At the end of the Makefile, include the toolchain file and then include `scripts/application.mk` from this SDK. This is an example of a Makefile:

```makefile
APP_SRCS += main.c backend.c

SONNET_SDK_PATH := /path/to/sonnet-sdk
TOOLCHAIN_FILE := $(SONNET_SDK_PATH)/scripts/toolchains/rv32im-clang.mk
APP_BUILD_DIR := build

MODULES += $(SONNET_SDK_PATH)/modules/compiler-rt
MODULES += $(SONNET_SDK_PATH)/modules/lightio

include $(TOOLCHAIN_FILE)
include $(SONNET_SDK_PATH)/scripts/application.mk
```

`scripts/application.mk` provides these targets:

- `all`: This is the default target. It will build your application in ELF and binary format. The resulting files will be `$(APP_BUILD_DIR)/application.bin` and`$(APP_BUILD_DIR)/application.elf`.
- `clean`: Removes all build output.
- `compile_commands`: Generate `compile_commands.json` for linting and IDE support.

Please see example project under `examples/`, and read `scripts/application.mk` for more details.

## What are Embedded Devices

On your desktop computer, laptop and phone usually runs **operating systems**, such as Linux, Android, macOS and Windows.  Applications are isolated from each other and the real hardware by mechanisms including **virtual memory**, **privilege levels** and **memory protection**. They are living under an illusion (called the **user space**) created by the operating system. The applications do not need to know much about hardware details. The operating system has provided a hardware-agnostic and unified interface for the applications to operate on **peripherals**. The application talks to the operating system (by making a **system call**), and the operating system lets the corresponding **driver** operate on the peripherals. The operating system **schedules** tasks (**threads** and **processes**), so multiple tasks can run alternatively on a single **processor core**, and different tasks can be distributed to different processor cores. The operating system also provides "standard" features like **networking**, **environment variables** and **file system** that most applications rely on. Your computer and phone are high-performance and general-purposed devices that you do many things with it.

**Embedded devices** are little computers for a dedicated purpose, and built into some electronic "things", such as wireless earphones, keyboards, washing machines and drones. Some embedded devices also runs a general purpose operating system (mostly Linux). Their hardware and software are similar with your computer. And developing **user space applications** for them is just like developing applications for your computer. But those devices have smaller sizes, less power consumption, and lower performance. But this SDK is telling stories about another kind of embedded devices that are much simpler (and also cheaper), usually called **microcontrollers**.

Microcontrollers are designed for low cost and real-time scenarios. They have very little RAM (usually a few decades of KiB), and the programs are usually stored in a **programmable ROM** (usually a few hundreds of KiB). They usually have no virtual memory, and very limited privilege level and memory protection mechanism. Hence, their hardware can hardly support any general-purposes operating systems. The applications for them are tailored for specific device, and have direct and detailed control over hardware. "Standard features" like user interfaces, networking and file systems are not necessarily available. Some applications run with no operating system at all (called **bare-metal** applications), some run on **real-time operating systems** (RTOS). They focus just on task scheduling, and guarantees that the tasks are **real-time** (for example, sensor data is sampled exactly every 0.02 second, and an emergency feedback control must be done within 0.1 seconds when overloading is detected).

Tips: you can search the web or ask AIs about the highlighted concepts, if you find yourself difficult to understand this.

## Limitations

The core limitation of this SDK comes from the fact that this SDK tries to be low-level while the actual hardware is different, or in another way, different vendors are solving the same problem in different ways. This means that many things **cannot be supported by the HAL**, notably clock configuration, GIPO multiplexing and timer input compare. Please refer to `docs/hal.md` for what is supported, what is not, and why it is hard to support something. After all, we need to accept the fact that, "writing once, running everywhere" is hardly possible for embedding development, where you want to exactly control what happens on the hardware. In the future, these hard-to-support features might be supported by generating vendor-specific code from a device tree.

This SDK is a good starting point of learning embedded development, and it has enough features to fully support the simplest devices, such as an FPGA soft processor core, or a testing chip produced by experimental tape out. Yet, it is not any all-in-one manual for embedded devices. It helps you to see through the seemingly magic of your vendor's development environment, or some tutorials and blogs that only tells you how to do, but not why it is like that. You still need to be familiar with a relatively complicated device from a specific vendor, or perhaps multiple families of devices from different vendors to be able to solve any practical embedded development problems. Because the real world is complicated.

## Other Advice for Leaners

If you have been clear about how this SDK works, congratulations, you have taken your hardest step towards mastering embedded development. Yet, there is still a long way to go.

**Read the datasheets and documentation from the chip vendor!** Never rely solely on materials from where you buy your board, blog tutorials, AI chatbots, or even textbooks. They are very helpful when you learn, but they usually tell only a small part of the real story. They can be outdated, limited, scratching just on the surface, or having personal bias. Also, the easiest way to start a practical embedded project is not what "your friends is already using", not what third party materials says, and of course, not using this SDK. It is usually what the chip vendor recommends. The vendors website usually provide SDKs, IDEs, and guides that perfectly works for their products. After all, it is the vendor that know their own hardware best.

**Be prepared to try something new!** Many embedded developers are getting too used to a single IDE or a single family of devices, even thinking that is the only "canonical" way of embedded development. When staring a new project, please do some research on the devices that you have not tried but may be more suitable. When your vendor releases a completely new SDK or IDE, be free to try them.

**Do a practical problem without copying and pasting code.** Practical work is not a designed puzzle. It often involves complexity, but not tricky shortcuts. You won’t need overly clever hacks or reliance on coincidental solutions. Instead, rely on general knowledge and experience to choose the most appropriate approach, along with an intuitive sense of what tools and methods can achieve. If you are only happy with designed problems, you can be helpless when you are facing the real world. If you just copy and paste code, you will only know that you have done it, but will not understand how you have done it.

## License

All the source code is licensed under Mulan PSL 2.0. All the documentations are licensed under Creative Commons 4.0 BY-NC-SA.

## Contributing

Contributions are welcomed! The preferred way to contribute is by submitting pull requests. You can also open issues to report bugs or suggest improvements. Pull requests are accepted on GitLink, Gitee, and GitHub, with GitLink being the preferred platform. Please note that pull requests submitted via GitHub may receive lower priority.

Currently, we are especially looking for contributions in the following areas:

- Adding support for more devices.
- Designing the HAL for more functionalities.
- Device tree support.
- Improvement in documentation.
- Translating the documentation into Chinese.

Contributors need to follow these guidelines:

- Be friendly, helpful and patient.
- Contributors have the copyright of their contributed content, and license the content under the same license of this repository.
- AI generated content can be accepted, but the quality needs to be guaranteed.
