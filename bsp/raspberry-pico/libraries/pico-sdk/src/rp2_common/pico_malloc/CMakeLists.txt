if (NOT TARGET pico_malloc)
    #shims for ROM functions for -lgcc functions  (listed below)
    add_library(pico_malloc INTERFACE)

    target_sources(pico_malloc INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/pico_malloc.c
            )

    pico_wrap_function(pico_malloc malloc)
    pico_wrap_function(pico_malloc calloc)
    pico_wrap_function(pico_malloc free)

    target_link_libraries(pico_malloc INTERFACE pico_sync)
endif()
