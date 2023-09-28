pico_add_impl_library(pico_divider)

target_sources(pico_divider INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/divider.c)

pico_mirrored_target_link_libraries(pico_divider INTERFACE hardware_divider)

macro(pico_set_divider_implementation TARGET IMPL)
endmacro()