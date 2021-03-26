if (NOT TARGET pico_stdio)
    add_library(pico_stdio INTERFACE)

    target_include_directories(pico_stdio INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    target_sources(pico_stdio INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/stdio.c
    )

    pico_wrap_function(pico_stdio printf)
    pico_wrap_function(pico_stdio vprintf)
    pico_wrap_function(pico_stdio puts)
    pico_wrap_function(pico_stdio putchar)

    if (TARGET pico_printf)
        target_link_libraries(pico_stdio INTERFACE pico_printf)
    endif()
endif()