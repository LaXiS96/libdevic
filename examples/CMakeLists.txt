add_executable(libdevic_examples_testing_gpio
    testing_gpio.c
)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../port/testing
    ${CMAKE_CURRENT_BINARY_DIR}/port/testing
)

target_link_libraries(libdevic_examples_testing_gpio PRIVATE
    libdevic_port_testing
)
