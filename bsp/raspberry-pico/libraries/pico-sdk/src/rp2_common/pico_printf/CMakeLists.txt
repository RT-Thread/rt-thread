if (NOT TARGET pico_printf)
    # library to be depended on - we make this depend on particular implementations using per target generator expressions
    pico_add_library(pico_printf)

    # no custom implementation; falls thru to compiler
    pico_add_library(pico_printf_compiler)

    target_include_directories(pico_printf_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    # add alias "default" which is just pico.
    add_library(pico_printf_default INTERFACE)
    target_link_libraries(pico_printf_default INTERFACE pico_printf_pico)

    set(PICO_DEFAULT_PRINTF_IMPL pico_printf_default)

    target_link_libraries(pico_printf INTERFACE
            $<IF:$<BOOL:$<TARGET_PROPERTY:PICO_TARGET_PRINTF_IMPL>>,$<TARGET_PROPERTY:PICO_TARGET_PRINTF_IMPL>,${PICO_DEFAULT_PRINTF_IMPL}>)

    pico_add_library(pico_printf_pico)
    target_sources(pico_printf_pico INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/printf.c
    )
    target_link_libraries(pico_printf_pico INTERFACE pico_printf_headers)

    pico_add_library(pico_printf_none)
    target_sources(pico_printf_none INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/printf_none.S
    )
    target_link_libraries(pico_printf_none INTERFACE pico_printf_headers)

    function(wrap_printf_functions TARGET)
        # note that printf and vprintf are in pico_stdio so we can provide thread safety
        pico_wrap_function(${TARGET} sprintf)
        pico_wrap_function(${TARGET} snprintf)
        pico_wrap_function(${TARGET} vsnprintf)
    endfunction()

    wrap_printf_functions(pico_printf_pico)
    wrap_printf_functions(pico_printf_none)

    macro(pico_set_printf_implementation TARGET IMPL)
        get_target_property(target_type ${TARGET} TYPE)
        if ("EXECUTABLE" STREQUAL "${target_type}")
            set_target_properties(${TARGET} PROPERTIES PICO_TARGET_PRINTF_IMPL "pico_printf_${IMPL}")
        else()
            message(FATAL_ERROR "printf implementation must be set on executable not library")
        endif()
    endmacro()
endif()
