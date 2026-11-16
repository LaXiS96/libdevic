# libdevic

An attempt at writing drivers for various devices (sensors, displays, ...) to be portable across architectures/frameworks (ESP-IDF, CH32, STM32, ...).

Uses CMake and targets C11.

The name was born because I mistyped `libdevice`.

## Directories

- `examples`: usage examples
- `lib`: `libdevic` sources, comprised of platform-independent abstractions and implementations
    - `include/libdevic/device`: device driver abstractions
    - `include/libdevic/hal`: platform abstractions for communication buses (e.g. I2C, SPI), peripherals (e.g. GPIO, ADC) and anything else device drivers need to work
    - `src/device`: device driver implementations
- `port`: platform-specific implementations of abstractions defined by `libdevic`, where "platform" can be a different architecture/framework/OS/...
