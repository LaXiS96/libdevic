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

## Usage

Add this repository as a submodule in your CMake-based application. Then, add this to your `CMakeLists.txt`:
```cmake
# Import the core library
add_subdirectory(libdevic)
# Import the platform port
add_subdirectory(libdevic/port/ch32v003)
# Import the devices you are interested in
add_subdirectory(libdevic/device/blink)
# Gotta link'em all!
target_link_libraries(firmware PRIVATE
    libdevic_port_ch32v003
    libdevic_blink
)
```

You also need to provide any port-specific dependency, e.g. for the CH32V003 port, provide and link `ch32v003_sdk` into your executable:
```cmake
add_library(ch32v003_sdk INTERFACE)
target_include_directories(ch32v003_sdk INTERFACE ...)
target_sources(ch32v003_sdk INTERFACE ...)

target_link_libraries(firmware PRIVATE
    ch32v003_sdk
    libdevic_port_ch32v003
    ...
)
```

## TODOs
- include ch32v003 sdk (submodule?)
- bring in BME280/BME680 sensor APIs as submodules and their drivers
