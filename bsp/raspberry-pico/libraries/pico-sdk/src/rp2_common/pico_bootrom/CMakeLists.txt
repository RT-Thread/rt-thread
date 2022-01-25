add_library(pico_bootrom INTERFACE)

target_sources(pico_bootrom INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/bootrom.c
        )

target_include_directories(pico_bootrom INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
target_link_libraries(pico_bootrom INTERFACE pico_base_headers)
