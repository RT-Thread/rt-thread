add_library(hardware_flash INTERFACE)

target_sources(hardware_flash INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/flash.c
        )

target_include_directories(hardware_flash INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(hardware_flash INTERFACE pico_base_headers pico_bootrom)
