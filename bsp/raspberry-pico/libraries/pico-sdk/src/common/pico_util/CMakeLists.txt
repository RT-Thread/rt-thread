if (NOT TARGET pico_util_headers)
    add_library(pico_util_headers INTERFACE)
    target_include_directories(pico_util_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
    target_link_libraries(pico_util_headers INTERFACE pico_base_headers hardware_sync_headers)
endif()

if (NOT TARGET pico_util)
    pico_add_impl_library(pico_util)
    target_sources(pico_util INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/datetime.c
            ${CMAKE_CURRENT_LIST_DIR}/pheap.c
            ${CMAKE_CURRENT_LIST_DIR}/queue.c
    )
    pico_mirrored_target_link_libraries(pico_util INTERFACE pico_sync)
endif()
