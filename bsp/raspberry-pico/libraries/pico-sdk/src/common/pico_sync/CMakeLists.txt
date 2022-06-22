if (NOT TARGET pico_sync_headers)
    add_library(pico_sync_headers INTERFACE)
    target_include_directories(pico_sync_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
    target_link_libraries(pico_sync_headers INTERFACE hardware_sync pico_time)
endif()

if (NOT TARGET pico_sync_core)
    add_library(pico_sync_core INTERFACE)
    target_sources(pico_sync_core INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/lock_core.c
    )
    target_link_libraries(pico_sync_core INTERFACE pico_sync_headers)
endif()

if (NOT TARGET pico_sync_sem)
    add_library(pico_sync_sem INTERFACE)
    target_sources(pico_sync_sem INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/sem.c
    )
    target_link_libraries(pico_sync_sem INTERFACE pico_sync_core pico_time)
endif()

if (NOT TARGET pico_sync_mutex)
    add_library(pico_sync_mutex INTERFACE)
    target_sources(pico_sync_mutex INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/mutex.c
            )
    target_link_libraries(pico_sync_mutex INTERFACE pico_sync_core pico_time)
endif()

if (NOT TARGET pico_sync_critical_section)
    add_library(pico_sync_critical_section INTERFACE)
    target_sources(pico_sync_critical_section INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/critical_section.c
            )
    target_link_libraries(pico_sync_critical_section INTERFACE pico_sync_core pico_time)
endif()

if (NOT TARGET pico_sync)
    add_library(pico_sync INTERFACE)
    target_link_libraries(pico_sync INTERFACE pico_sync_sem pico_sync_mutex pico_sync_critical_section pico_sync_core)
endif()


