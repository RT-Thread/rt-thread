if (NOT TARGET pico_stdio)
    pico_add_library(pico_stdio)

    target_include_directories(pico_stdio_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    target_sources(pico_stdio INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/stdio.c
    )

    pico_wrap_function(pico_stdio printf)
    pico_wrap_function(pico_stdio vprintf)
    pico_wrap_function(pico_stdio puts)
    pico_wrap_function(pico_stdio putchar)
    pico_wrap_function(pico_stdio getchar)

    if (TARGET pico_printf)
        pico_mirrored_target_link_libraries(pico_stdio INTERFACE pico_printf)
    endif()
endif()