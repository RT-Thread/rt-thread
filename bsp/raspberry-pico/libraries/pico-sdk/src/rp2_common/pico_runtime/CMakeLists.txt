pico_add_library(pico_runtime)

target_sources(pico_runtime INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/runtime.c
)

target_include_directories(pico_runtime_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

pico_mirrored_target_link_libraries(pico_runtime INTERFACE
        hardware_uart
        hardware_clocks
        hardware_irq
        pico_printf
        pico_sync
        )

if (TARGET pico_bit_ops)
    pico_mirrored_target_link_libraries(pico_runtime INTERFACE pico_bit_ops)
endif()
if (TARGET pico_divider)
    pico_mirrored_target_link_libraries(pico_runtime INTERFACE pico_divider)
endif()
if (TARGET pico_double)
    pico_mirrored_target_link_libraries(pico_runtime INTERFACE pico_double)
endif()
if (TARGET pico_int64_ops)
    pico_mirrored_target_link_libraries(pico_runtime INTERFACE pico_int64_ops)
endif()
if (TARGET pico_float)
    pico_mirrored_target_link_libraries(pico_runtime INTERFACE pico_float)
endif()
if (TARGET pico_malloc)
    pico_mirrored_target_link_libraries(pico_runtime INTERFACE pico_malloc)
endif()
if (TARGET pico_mem_ops)
    pico_mirrored_target_link_libraries(pico_runtime INTERFACE pico_mem_ops)
endif()
if (TARGET pico_standard_link)
    pico_mirrored_target_link_libraries(pico_runtime INTERFACE pico_standard_link)
endif()

# todo is this correct/needed?
if (PICO_C_COMPILER_IS_GNU)
    target_link_options(pico_runtime INTERFACE "--specs=nosys.specs")
elseif (PICO_C_COMPILER_IS_CLANG)
   # target_link_options(pico_runtime INTERFACE "-nostdlib")
endif()

