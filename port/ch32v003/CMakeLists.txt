add_library(libdevic_port_ch32v003 INTERFACE)

target_include_directories(libdevic_port_ch32v003 INTERFACE include)

target_sources(libdevic_port_ch32v003 INTERFACE
    src/gpio.c
    src/i2c.c
)

target_link_libraries(libdevic_port_ch32v003 INTERFACE
    libdevic
    ch32v003_sdk
)
