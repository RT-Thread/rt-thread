if (NOT TARGET pico_stdio)
    pico_add_library(pico_stdio)

    target_include_directories(pico_stdio_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    target_sources(pico_stdio INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/stdio.c
            )
    pico_add_library(pico_stdio_usb)
    pico_add_library(pico_stdio_uart)
    pico_add_library(pico_stdio_semihosting)
    
    function(pico_enable_stdio_uart)
    endfunction()
    function(pico_enable_stdio_usb)
    endfunction()
    function(pico_enable_stdio_semihosting)
    endfunction()
endif()

