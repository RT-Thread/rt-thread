if (NOT TARGET pico_printf)
    pico_add_library(pico_printf)
    function(pico_set_printf_implementation)
    endfunction()
endif()

