if (NOT TARGET pico_printf)
    add_library(pico_printf INTERFACE)
    function(pico_set_printf_implementation)
    endfunction()
endif()

