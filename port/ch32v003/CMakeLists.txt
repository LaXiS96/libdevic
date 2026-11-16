add_library(libdevic_port_ch32v003 STATIC)

target_include_directories(libdevic_port_ch32v003
    PUBLIC include)

target_sources(libdevic_port_ch32v003
    PRIVATE src/gpio.c)

target_link_libraries(libdevic_port_ch32v003
    PUBLIC libdevic)
