add_library(pico_divider INTERFACE)

target_sources(pico_divider INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/divider.c)

target_link_libraries(pico_divider INTERFACE pico_divider_headers)

macro(pico_set_divider_implementation TARGET IMPL)
endmacro()