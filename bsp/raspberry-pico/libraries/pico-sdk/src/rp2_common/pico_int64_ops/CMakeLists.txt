if (NOT TARGET pico_int64_ops)

    #shims for ROM functions for -lgcc functions  (listed below)
    pico_add_library(pico_int64_ops)

    # no custom implementation; falls thru to compiler
    pico_add_library(pico_int64_ops_compiler)

    # add alias "default" which is just pico.
    add_library(pico_int64_ops_default INTERFACE)
    target_link_libraries(pico_int64_ops_default INTERFACE pico_int64_ops_pico)

    set(PICO_DEFAULT_INT64_OPS_IMPL pico_int64_ops_default)

    target_link_libraries(pico_int64_ops INTERFACE
            $<IF:$<BOOL:$<TARGET_PROPERTY:PICO_TARGET_INT64_OPS_IMPL>>,$<TARGET_PROPERTY:PICO_TARGET_INT64_OPS_IMPL>,${PICO_DEFAULT_INT64_OPS_IMPL}>)

    pico_add_library(pico_int64_ops_pico)
    target_include_directories(pico_int64_ops_pico INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
    pico_mirrored_target_link_libraries(pico_int64_ops_pico INTERFACE pico_base)

    target_sources(pico_int64_ops_pico INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/pico_int64_ops_aeabi.S
    )

    pico_wrap_function(pico_int64_ops_pico __aeabi_lmul)

    macro(pico_set_int64_ops_implementation TARGET IMPL)
        get_target_property(target_type ${TARGET} TYPE)
        if ("EXECUTABLE" STREQUAL "${target_type}")
            set_target_properties(${TARGET} PROPERTIES PICO_TARGET_INT64_OPS_IMPL "pico_int64_ops_${IMPL}")
        else()
            message(FATAL_ERROR "int64_ops implementation must be set on executable not library")
        endif()
    endmacro()
endif()