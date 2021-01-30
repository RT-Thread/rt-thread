pico_simple_hardware_headers_target(sync)

if (NOT TARGET hardware_sync)
    add_library(hardware_sync INTERFACE)

    target_sources(hardware_sync INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/sync_core0_only.c
    )

    target_link_libraries(hardware_sync INTERFACE hardware_sync_headers pico_platform)
endif()

