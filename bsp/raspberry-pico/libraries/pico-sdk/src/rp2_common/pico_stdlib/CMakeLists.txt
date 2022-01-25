# PICO_CMAKE_CONFIG: PICO_STDIO_UART, OPTION: Globally enable stdio UART, default=1, group=pico_stdlib
option(PICO_STDIO_UART "Globablly enable stdio UART" 1)
# PICO_CMAKE_CONFIG: PICO_STDIO_USB, OPTION: Globally enable stdio USB, default=0, group=pico_stdlib
option(PICO_STDIO_USB "Globablly enable stdio USB" 0)
# PICO_CMAKE_CONFIG: PICO_STDIO_USB, OPTIONS: Globally enable stdio semihosting, default=0, group=pico_stdlib
option(PICO_STDIO_USB "Globablly enable stdio semihosting " 0)

if (NOT TARGET pico_stdlib)
    add_library(pico_stdlib INTERFACE)
    target_sources(pico_stdlib INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/stdlib.c
    )
    target_link_libraries(pico_stdlib INTERFACE
        pico_stdlib_headers
        pico_platform
        pico_runtime
        pico_stdio
        pico_time
    )

    function(pico_enable_stdio_uart TARGET ENABLED)
        set_target_properties(${TARGET} PROPERTIES PICO_TARGET_STDIO_UART ${ENABLED})
    endfunction()

    function(pico_enable_stdio_usb TARGET ENABLED)
        set_target_properties(${TARGET} PROPERTIES PICO_TARGET_STDIO_USB ${ENABLED})
    endfunction()

    function(pico_enable_stdio_semihosting TARGET ENABLED)
        set_target_properties(${TARGET} PROPERTIES PICO_TARGET_STDIO_SEMIHOSTING ${ENABLED})
    endfunction()

    if (TARGET pico_stdio_uart)
        target_link_libraries(pico_stdlib INTERFACE $<IF:$<BOOL:$<IF:$<STREQUAL:$<TARGET_PROPERTY:PICO_TARGET_STDIO_UART>,>,${PICO_STDIO_UART},$<TARGET_PROPERTY:PICO_TARGET_STDIO_UART>>>,pico_stdio_uart,>)
    endif()

    if (TARGET pico_stdio_usb)
        target_link_libraries(pico_stdlib INTERFACE $<IF:$<BOOL:$<IF:$<STREQUAL:$<TARGET_PROPERTY:PICO_TARGET_STDIO_USB>,>,${PICO_STDIO_USB},$<TARGET_PROPERTY:PICO_TARGET_STDIO_USB>>>,pico_stdio_usb,>)
    endif()

    if (TARGET pico_stdio_semihosting)
        target_link_libraries(pico_stdlib INTERFACE $<IF:$<BOOL:$<IF:$<STREQUAL:$<TARGET_PROPERTY:PICO_TARGET_STDIO_SEMIHOSTING>,>,${PICO_STDIO_SEMIHOSTING},$<TARGET_PROPERTY:PICO_TARGET_STDIO_SEMIHOSTING>>>,pico_stdio_semihosting,>)
    endif()

endif()
