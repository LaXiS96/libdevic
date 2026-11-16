add_library(libdevic INTERFACE)
target_include_directories(libdevic
    INTERFACE include)

add_library(libdevic_ina226 STATIC
    src/device/ina226.c)
target_link_libraries(libdevic_ina226
    PUBLIC libdevic)
