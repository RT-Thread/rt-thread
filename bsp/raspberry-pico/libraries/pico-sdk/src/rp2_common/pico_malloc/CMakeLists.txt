if (NOT TARGET pico_malloc)
    #shims for ROM functions for -lgcc functions  (listed below)
    pico_add_library(pico_malloc)

    target_sources(pico_malloc INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/pico_malloc.c
            )

    target_include_directories(pico_malloc_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    pico_wrap_function(pico_malloc malloc)
    pico_wrap_function(pico_malloc calloc)
    pico_wrap_function(pico_malloc realloc)
    pico_wrap_function(pico_malloc free)

    target_link_libraries(pico_malloc INTERFACE pico_sync)
endif()
