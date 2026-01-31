# Hardware Abstraction Layer (HAL)

In embedded development, HAL (Hardware Abstraction Layer) is a software layer that sits between the hardware-specific code and the application logic. Its primary purpose is to abstract away the low-level details of the microcontroller or hardware peripherals, provide a unified interface for different models for the same type of peripheral, making the application code more portable, maintainable, and hardware-independent.

## Design Goals and Principles

This is an "SDK as embedded tutorial", so it needs to be simple enough for a beginner to understand. The HAL is designed to only provide the most common functionalities to control the peripherals. For each type of peripheral, the HAL usually provide these types and functions:

- `xxxx_config_t`: a structure containing the configuration of that peripheral. It is used for peripheral initialization.
- `xxxx_config(void* periph, xxxx_config_t* config)`: Initialize and configure the peripheral. `periph` is a pointer to the peripheral, `config` is the desired configuration. If the actual configuration applied is not the same as specified, the data that `config` points to will be updated to match the actual configuration.
- Other functions to manipulate the peripheral.

The first argument that the peripheral initialization and manipulation function accepts is a `void*` pointing to "the peripheral to operate on". It can be the memory mapped IO address to that peripheral, a pointer to a "peripheral handle", or even an index or magic number. A "peripheral handle" is a structure containing data and function pointers needed by the HAL functions to manipulate that peripheral. Taking real-world examples, the STM32 HAL library, Raspberry Pi Pico SDK and the MSP432 SDK use peripheral handles, while the legacy STM32 SDK uses pointers to memory mapped IO addresses.

The source code of HAL functions is under `src/hal`. Each subdirectory contains the HAL source code for a family of SoCs. Although different families of SoCs can use the same model of peripheral, the layout of their hardware can differ. So it is not generally practical for different families of SoCs to share much HAL source code.

## GPIO

### Pin Multiplexing

Many modern SoCs support pin multiplexing, allowing a single GPIO pin to serve different functions. For example, a same GPIO pin can be configured as plain GPIO, UART TX or IIC SDA. This is implemented by on-chip multiplexers that route the signals between internal peripherals and package pins.

However, it is hardly possible to design an abstraction layer for GPIO pin multiplexing that is unified across vendors but is not bloat. Unlike peripherals for input and output, the hardware implementation for pin multiplexing is very different across vendors. Some chips does not support this, some tie multiplexing to pins, some tie multiplexing to peripherals, some even have a centralized multiplexer or matrix.

This is an "SDK as embedded tutorial", not an industrial "cross-vendor development convention". So currently, this SDK **simply does not offer any HAL** for pin multiplexing. But in future versions, if this SDK is actively contributed to, support of code generation based on device tree or markup languages, for peripheral initialization and pin multiplexing, might be added.
