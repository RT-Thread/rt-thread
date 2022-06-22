add_library(pico_stdio_uart INTERFACE)

target_sources(pico_stdio_uart INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/stdio_uart.c
)

target_include_directories(pico_stdio_uart INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_compile_definitions(pico_stdio_uart INTERFACE
        PICO_STDIO_UART=1
)

target_link_libraries(pico_stdio_uart INTERFACE pico_stdio)