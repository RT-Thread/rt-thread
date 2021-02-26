if (NOT TARGET pico_float)
    # library to be depended on - we make this depend on particular implementations using per target generator expressions
    add_library(pico_float INTERFACE)

    # no custom implementation; falls thru to compiler
    add_library(pico_float_compiler INTERFACE)
    # PICO_BUILD_DEFINE: PICO_FLOAT_COMPILER, whether compiler provided float support is being used, type=bool, default=0, but dependent on CMake options, group=pico_float
    target_compile_definitions(pico_float_compiler INTERFACE
            PICO_FLOAT_COMPILER=1
    )

    add_library(pico_float_headers INTERFACE)
    target_include_directories(pico_float_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

    # add alias "default" which is just rom.
    add_library(pico_float_default INTERFACE)
    target_link_libraries(pico_float_default INTERFACE pico_float_pico)

    set(PICO_DEFAULT_FLOAT_IMPL pico_float_default)

    target_link_libraries(pico_float INTERFACE
            $<IF:$<BOOL:$<TARGET_PROPERTY:PICO_TARGET_FLOAT_IMPL>>,$<TARGET_PROPERTY:PICO_TARGET_FLOAT_IMPL>,${PICO_DEFAULT_FLOAT_IMPL}>)

    add_library(pico_float_pico INTERFACE)
    target_sources(pico_float_pico INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/float_aeabi.S
            ${CMAKE_CURRENT_LIST_DIR}/float_init_rom.c
            ${CMAKE_CURRENT_LIST_DIR}/float_math.c
            ${CMAKE_CURRENT_LIST_DIR}/float_v1_rom_shim.S
    )
    # PICO_BUILD_DEFINE: PICO_FLOAT_PICO, whether optimized pico/bootrom provided float support is being used, type=bool, default=1, but dependent on CMake options, group=pico_float
    target_compile_definitions(pico_float_pico INTERFACE
            PICO_FLOAT_PICO=1
            )

    target_link_libraries(pico_float_pico INTERFACE pico_bootrom pico_float_headers)

    add_library(pico_float_none INTERFACE)
    target_sources(pico_float_none INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/float_none.S
            )

    target_link_libraries(pico_float_none INTERFACE pico_float_headers)

    # PICO_BUILD_DEFINE: PICO_FLOAT_NONE, whether float support is disabled and functions will panic, type=bool, default=0, but dependent on CMake options, group=pico_float
    target_compile_definitions(pico_float_none INTERFACE
            PICO_FLOAT_NONE=1
    )

    function(wrap_float_functions TARGET)
        pico_wrap_function(${TARGET} __aeabi_fadd)
        pico_wrap_function(${TARGET} __aeabi_fdiv)
        pico_wrap_function(${TARGET} __aeabi_fmul)
        pico_wrap_function(${TARGET} __aeabi_frsub)
        pico_wrap_function(${TARGET} __aeabi_fsub)
        pico_wrap_function(${TARGET} __aeabi_cfcmpeq)
        pico_wrap_function(${TARGET} __aeabi_cfrcmple)
        pico_wrap_function(${TARGET} __aeabi_cfcmple)
        pico_wrap_function(${TARGET} __aeabi_fcmpeq)
        pico_wrap_function(${TARGET} __aeabi_fcmplt)
        pico_wrap_function(${TARGET} __aeabi_fcmple)
        pico_wrap_function(${TARGET} __aeabi_fcmpge)
        pico_wrap_function(${TARGET} __aeabi_fcmpgt)
        pico_wrap_function(${TARGET} __aeabi_fcmpun)
        pico_wrap_function(${TARGET} __aeabi_i2f)
        pico_wrap_function(${TARGET} __aeabi_l2f)
        pico_wrap_function(${TARGET} __aeabi_ui2f)
        pico_wrap_function(${TARGET} __aeabi_ul2f)
        pico_wrap_function(${TARGET} __aeabi_f2iz)
        pico_wrap_function(${TARGET} __aeabi_f2lz)
        pico_wrap_function(${TARGET} __aeabi_f2uiz)
        pico_wrap_function(${TARGET} __aeabi_f2ulz)
        pico_wrap_function(${TARGET} __aeabi_f2d)
        pico_wrap_function(${TARGET} sqrtf)
        pico_wrap_function(${TARGET} cosf)
        pico_wrap_function(${TARGET} sinf)
        pico_wrap_function(${TARGET} tanf)
        pico_wrap_function(${TARGET} atan2f)
        pico_wrap_function(${TARGET} expf)
        pico_wrap_function(${TARGET} logf)

        pico_wrap_function(${TARGET} ldexpf)
        pico_wrap_function(${TARGET} copysignf)
        pico_wrap_function(${TARGET} truncf)
        pico_wrap_function(${TARGET} floorf)
        pico_wrap_function(${TARGET} ceilf)
        pico_wrap_function(${TARGET} roundf)
        pico_wrap_function(${TARGET} sincosf) # gnu
        pico_wrap_function(${TARGET} asinf)
        pico_wrap_function(${TARGET} acosf)
        pico_wrap_function(${TARGET} atanf)
        pico_wrap_function(${TARGET} sinhf)
        pico_wrap_function(${TARGET} coshf)
        pico_wrap_function(${TARGET} tanhf)
        pico_wrap_function(${TARGET} asinhf)
        pico_wrap_function(${TARGET} acoshf)
        pico_wrap_function(${TARGET} atanhf)
        pico_wrap_function(${TARGET} exp2f)
        pico_wrap_function(${TARGET} log2f)
        pico_wrap_function(${TARGET} exp10f)
        pico_wrap_function(${TARGET} log10f)
        pico_wrap_function(${TARGET} powf)
        pico_wrap_function(${TARGET} powintf) #gnu
        pico_wrap_function(${TARGET} hypotf)
        pico_wrap_function(${TARGET} cbrtf)
        pico_wrap_function(${TARGET} fmodf)
        pico_wrap_function(${TARGET} dremf)
        pico_wrap_function(${TARGET} remainderf)
        pico_wrap_function(${TARGET} remquof)
        pico_wrap_function(${TARGET} expm1f)
        pico_wrap_function(${TARGET} log1pf)
        pico_wrap_function(${TARGET} fmaf)
    endfunction()

    wrap_float_functions(pico_float_pico)
    wrap_float_functions(pico_float_none)

    macro(pico_set_float_implementation TARGET IMPL)
        get_target_property(target_type ${TARGET} TYPE)
        if ("EXECUTABLE" STREQUAL "${target_type}")
            set_target_properties(${TARGET} PROPERTIES PICO_TARGET_FLOAT_IMPL "pico_float_${IMPL}")
        else()
            message(FATAL_ERROR "float implementation must be set on executable not library")
        endif()
    endmacro()
endif()
