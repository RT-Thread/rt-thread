if (NOT TARGET pico_stdlib_headers)
    add_library(pico_stdlib_headers INTERFACE)
    target_include_directories(pico_stdlib_headers INTERFACE include)
    target_link_libraries(pico_stdlib_headers INTERFACE
            hardware_gpio
            hardware_uart
            hardware_divider
            pico_time
            pico_util
    )
endif()