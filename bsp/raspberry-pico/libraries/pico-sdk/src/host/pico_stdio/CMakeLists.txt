if (NOT TARGET pico_stdio)
    add_library(pico_stdio INTERFACE)

    target_include_directories(pico_stdio INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    target_sources(pico_stdio INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/stdio.c
            )
    add_library(pico_stdio_usb INTERFACE)
    add_library(pico_stdio_uart INTERFACE)
    add_library(pico_stdio_semihosting INTERFACE)
    
    function(pico_enable_stdio_uart)
    endfunction()
    function(pico_enable_stdio_usb)
    endfunction()
    function(pico_enable_stdio_semihosting)
    endfunction()
endif()

