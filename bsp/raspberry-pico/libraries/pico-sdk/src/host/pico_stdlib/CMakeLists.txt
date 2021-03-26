if (NOT TARGET pico_stdlib)
    add_library(pico_stdlib INTERFACE)

    target_sources(pico_stdlib INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/stdlib.c
    )

    target_link_libraries(pico_stdlib INTERFACE
            pico_stdlib_headers
            pico_platform
            pico_time
            pico_divider
            pico_binary_info
            pico_printf
            pico_stdio
            hardware_gpio
    )
endif()

