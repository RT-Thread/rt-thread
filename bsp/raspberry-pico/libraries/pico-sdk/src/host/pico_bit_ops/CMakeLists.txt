add_library(pico_bit_ops INTERFACE)

target_sources(pico_bit_ops INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/bit_ops.c)

target_link_libraries(pico_bit_ops INTERFACE pico_bit_ops_headers)

macro(pico_set_bit_ops_implementation TARGET IMPL)
endmacro()