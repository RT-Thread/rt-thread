if (NOT TARGET pico_double)
    # library to be depended on - we make this depend on particular implementations using per target generator expressions
    pico_add_library(pico_double)

    # no custom implementation; falls thru to compiler
    pico_add_library(pico_double_compiler)

    target_include_directories(pico_double_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    # add alias "default" which is just pico.
    add_library(pico_double_default INTERFACE)
    target_link_libraries(pico_double_default INTERFACE pico_double_pico)

    set(PICO_DEFAULT_DOUBLE_IMPL pico_double_default)

    target_link_libraries(pico_double INTERFACE
            $<IF:$<BOOL:$<TARGET_PROPERTY:PICO_TARGET_DOUBLE_IMPL>>,$<TARGET_PROPERTY:PICO_TARGET_DOUBLE_IMPL>,${PICO_DEFAULT_DOUBLE_IMPL}>)

    pico_add_library(pico_double_pico)
    target_sources(pico_double_pico INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/double_aeabi.S
            ${CMAKE_CURRENT_LIST_DIR}/double_init_rom.c
            ${CMAKE_CURRENT_LIST_DIR}/double_math.c
            ${CMAKE_CURRENT_LIST_DIR}/double_v1_rom_shim.S
    )

    target_link_libraries(pico_double_pico INTERFACE pico_bootrom pico_double_headers hardware_divider)

    pico_add_library(pico_double_none)
    target_sources(pico_double_none INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/double_none.S
            )

    target_link_libraries(pico_double_none INTERFACE pico_double_headers)

    target_compile_definitions(pico_double_none_headers INTERFACE
            PICO_PRINTF_SUPPORT_FLOAT=0 # printing floats/doubles won't work, so we can save space by removing it
    )

    function(wrap_double_functions TARGET)
        pico_wrap_function(${TARGET} __aeabi_dadd)
        pico_wrap_function(${TARGET} __aeabi_ddiv)
        pico_wrap_function(${TARGET} __aeabi_dmul)
        pico_wrap_function(${TARGET} __aeabi_drsub)
        pico_wrap_function(${TARGET} __aeabi_dsub)
        pico_wrap_function(${TARGET} __aeabi_cdcmpeq)
        pico_wrap_function(${TARGET} __aeabi_cdrcmple)
        pico_wrap_function(${TARGET} __aeabi_cdcmple)
        pico_wrap_function(${TARGET} __aeabi_dcmpeq)
        pico_wrap_function(${TARGET} __aeabi_dcmplt)
        pico_wrap_function(${TARGET} __aeabi_dcmple)
        pico_wrap_function(${TARGET} __aeabi_dcmpge)
        pico_wrap_function(${TARGET} __aeabi_dcmpgt)
        pico_wrap_function(${TARGET} __aeabi_dcmpun)
        pico_wrap_function(${TARGET} __aeabi_i2d)
        pico_wrap_function(${TARGET} __aeabi_l2d)
        pico_wrap_function(${TARGET} __aeabi_ui2d)
        pico_wrap_function(${TARGET} __aeabi_ul2d)
        pico_wrap_function(${TARGET} __aeabi_d2iz)
        pico_wrap_function(${TARGET} __aeabi_d2lz)
        pico_wrap_function(${TARGET} __aeabi_d2uiz)
        pico_wrap_function(${TARGET} __aeabi_d2ulz)
        pico_wrap_function(${TARGET} __aeabi_d2f)
        pico_wrap_function(${TARGET} sqrt)
        pico_wrap_function(${TARGET} cos)
        pico_wrap_function(${TARGET} sin)
        pico_wrap_function(${TARGET} tan)
        pico_wrap_function(${TARGET} atan2)
        pico_wrap_function(${TARGET} exp)
        pico_wrap_function(${TARGET} log)

        pico_wrap_function(${TARGET} ldexp)
        pico_wrap_function(${TARGET} copysign)
        pico_wrap_function(${TARGET} trunc)
        pico_wrap_function(${TARGET} floor)
        pico_wrap_function(${TARGET} ceil)
        pico_wrap_function(${TARGET} round)
        pico_wrap_function(${TARGET} sincos) # gnu
        pico_wrap_function(${TARGET} asin)
        pico_wrap_function(${TARGET} acos)
        pico_wrap_function(${TARGET} atan)
        pico_wrap_function(${TARGET} sinh)
        pico_wrap_function(${TARGET} cosh)
        pico_wrap_function(${TARGET} tanh)
        pico_wrap_function(${TARGET} asinh)
        pico_wrap_function(${TARGET} acosh)
        pico_wrap_function(${TARGET} atanh)
        pico_wrap_function(${TARGET} exp2)
        pico_wrap_function(${TARGET} log2)
        pico_wrap_function(${TARGET} exp10)
        pico_wrap_function(${TARGET} log10)
        pico_wrap_function(${TARGET} pow)
        pico_wrap_function(${TARGET} powint) #gnu
        pico_wrap_function(${TARGET} hypot)
        pico_wrap_function(${TARGET} cbrt)
        pico_wrap_function(${TARGET} fmod)
        pico_wrap_function(${TARGET} drem)
        pico_wrap_function(${TARGET} remainder)
        pico_wrap_function(${TARGET} remquo)
        pico_wrap_function(${TARGET} expm1)
        pico_wrap_function(${TARGET} log1p)
        pico_wrap_function(${TARGET} fma)
    endfunction()

    wrap_double_functions(pico_double_pico)
    wrap_double_functions(pico_double_none)

    macro(pico_set_double_implementation TARGET IMPL)
        get_target_property(target_type ${TARGET} TYPE)
        if ("EXECUTABLE" STREQUAL "${target_type}")
            set_target_properties(${TARGET} PROPERTIES PICO_TARGET_DOUBLE_IMPL "pico_double_${IMPL}")
        else()
            message(FATAL_ERROR "double implementation must be set on executable not library")
        endif()
    endmacro()
endif()
