if (NOT TARGET pico_multicore)
    add_library(pico_multicore INTERFACE)

    target_sources(pico_multicore INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/multicore.c)

    target_include_directories(pico_multicore INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    target_compile_definitions(pico_multicore INTERFACE
        PICO_MULTICORE=1
    )

    target_link_libraries(pico_multicore INTERFACE pico_sync)
endif()



