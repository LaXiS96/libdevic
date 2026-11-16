add_library(libdevic_port_testing STATIC)

target_include_directories(libdevic_port_testing
    PUBLIC include)

target_sources(libdevic_port_testing
    PRIVATE src/gpio.c)

target_link_libraries(libdevic_port_testing
    PUBLIC libdevic)
