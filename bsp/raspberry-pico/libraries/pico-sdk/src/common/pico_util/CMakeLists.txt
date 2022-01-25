if (NOT TARGET pico_util_headers)
    add_library(pico_util_headers INTERFACE)
    target_include_directories(pico_util_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
    target_link_libraries(pico_util_headers INTERFACE pico_base_headers hardware_sync)
endif()

if (NOT TARGET pico_util)
    add_library(pico_util INTERFACE)
    target_sources(pico_util INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/datetime.c
            ${CMAKE_CURRENT_LIST_DIR}/pheap.c
            ${CMAKE_CURRENT_LIST_DIR}/queue.c
    )
    target_link_libraries(pico_util INTERFACE pico_util_headers)
endif()
