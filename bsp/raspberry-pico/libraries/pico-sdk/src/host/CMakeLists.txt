pico_add_subdirectory(hardware_divider)
pico_add_subdirectory(hardware_gpio)
pico_add_subdirectory(hardware_sync)
pico_add_subdirectory(hardware_timer)
pico_add_subdirectory(hardware_uart)
pico_add_subdirectory(pico_bit_ops)
pico_add_subdirectory(pico_divider)
pico_add_subdirectory(pico_multicore)
pico_add_subdirectory(pico_platform)
pico_add_subdirectory(pico_printf)
pico_add_subdirectory(pico_stdio)
pico_add_subdirectory(pico_stdlib)

pico_add_doxygen(${CMAKE_CURRENT_LIST_DIR})

macro(pico_set_float_implementation TARGET IMPL)
endmacro()

macro(pico_set_double_implementation TARGET IMPL)
endmacro()

macro(pico_set_boot_stage2 TARGET IMPL)
endmacro()

set(PICO_HOST_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")
function(pico_define_boot_stage2 NAME)
    add_executable(${NAME} ${PICO_HOST_DIR}/boot_stage2.c)
endfunction()