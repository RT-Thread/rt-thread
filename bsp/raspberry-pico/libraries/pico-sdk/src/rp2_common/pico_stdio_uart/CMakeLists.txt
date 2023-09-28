pico_add_library(pico_stdio_uart)

target_sources(pico_stdio_uart INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/stdio_uart.c
)

target_include_directories(pico_stdio_uart_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

pico_mirrored_target_link_libraries(pico_stdio_uart INTERFACE pico_stdio)