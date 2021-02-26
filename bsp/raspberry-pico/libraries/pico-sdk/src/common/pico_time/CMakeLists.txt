if (NOT TARGET pico_time_headers)
    add_library(pico_time_headers INTERFACE)

    target_include_directories(pico_time_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    target_link_libraries(pico_time_headers INTERFACE hardware_timer)
endif()

if (NOT TARGET pico_time)
    add_library(pico_time INTERFACE)

    target_sources(pico_time INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/time.c
            ${CMAKE_CURRENT_LIST_DIR}/timeout_helper.c)
    target_link_libraries(pico_time INTERFACE pico_time_headers pico_sync pico_util)
endif()
