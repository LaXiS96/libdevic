add_library(libdevic INTERFACE)
target_include_directories(libdevic INTERFACE include)
target_precompile_headers(libdevic INTERFACE
    <stdint.h>
    <stddef.h>
    <stdbool.h>
)

add_library(libdevic_blink INTERFACE)
target_sources(libdevic_blink INTERFACE
    src/device/blink.c
)
target_link_libraries(libdevic_blink INTERFACE libdevic)

add_library(libdevic_ina226 INTERFACE)
target_sources(libdevic_ina226 INTERFACE
    src/device/ina226.c
)
target_link_libraries(libdevic_ina226 INTERFACE libdevic)
