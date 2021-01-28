if (NOT TARGET pico_bit_ops)
    #shims for ROM functions for -lgcc functions  (listed below)
    add_library(pico_bit_ops INTERFACE)

    # no custom implementation; falls thru to compiler
    add_library(pico_bit_ops_compiler INTERFACE)
    # PICO_BUILD_DEFINE: PICO_BIT_OPS_COMPILER, whether compiler provided bit_ops bit functions support is being used, type=bool, default=0, but dependent on CMake options, group=pico_bit_ops
    target_compile_definitions(pico_bit_ops_compiler INTERFACE
            PICO_BIT_OPS_COMPILER=1
            )

    # add alias "default" which is just pico.
    add_library(pico_bit_ops_default INTERFACE)
    target_link_libraries(pico_bit_ops_default INTERFACE pico_bit_ops_pico)

    set(PICO_DEFAULT_BIT_OPS_IMPL pico_bit_ops_default)

    add_library(pico_bit_ops_pico INTERFACE)
    target_link_libraries(pico_bit_ops INTERFACE
            $<IF:$<BOOL:$<TARGET_PROPERTY:PICO_TARGET_BIT_OPS_IMPL>>,$<TARGET_PROPERTY:PICO_TARGET_BIT_OPS_IMPL>,${PICO_DEFAULT_BIT_OPS_IMPL}>)

    # PICO_BUILD_DEFINE: PICO_BIT_OPS_PICO, whether optimized pico/bootrom provided bit_ops bit functions support is being used, type=bool, default=1, but dependent on CMake options, group=pico_bit_ops
    target_compile_definitions(pico_bit_ops_pico INTERFACE
            PICO_BIT_OPS_PICO=1
            )

    target_sources(pico_bit_ops_pico INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/bit_ops_aeabi.S
            )

    target_link_libraries(pico_bit_ops_pico INTERFACE pico_bootrom pico_bit_ops_headers)

    # gcc
    pico_wrap_function(pico_bit_ops_pico __clzsi2)
    pico_wrap_function(pico_bit_ops_pico __clzsi2)
    pico_wrap_function(pico_bit_ops_pico __clzdi2)
    pico_wrap_function(pico_bit_ops_pico __ctzsi2)
    pico_wrap_function(pico_bit_ops_pico __ctzdi2)
    pico_wrap_function(pico_bit_ops_pico __popcountsi2)
    pico_wrap_function(pico_bit_ops_pico __popcountdi2)

    # armclang
    pico_wrap_function(pico_bit_ops_pico __clz)
    pico_wrap_function(pico_bit_ops_pico __clzl)
    pico_wrap_function(pico_bit_ops_pico __clzsi2)
    pico_wrap_function(pico_bit_ops_pico __clzll)

    macro(pico_set_bit_ops_implementation TARGET IMPL)
        get_target_property(target_type ${TARGET} TYPE)
        if ("EXECUTABLE" STREQUAL "${target_type}")
            set_target_properties(${TARGET} PROPERTIES PICO_TARGET_BIT_OPS_IMPL "pico_bit_ops_${IMPL}")
        else()
            message(FATAL_ERROR "bit_ops implementation must be set on executable not library")
        endif()
    endmacro()
    
endif()
