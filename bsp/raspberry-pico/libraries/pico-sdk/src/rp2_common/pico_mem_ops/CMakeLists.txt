if (NOT TARGET pico_mem_ops)
    #shims for ROM functions for -lgcc functions  (listed below)
    pico_add_library(pico_mem_ops)

    # no custom implementation; falls thru to compiler
    pico_add_library(pico_mem_ops_compiler)

    # add alias "default" which is just pico.
    add_library(pico_mem_ops_default INTERFACE)
    target_link_libraries(pico_mem_ops_default INTERFACE pico_mem_ops_pico)

    set(PICO_DEFAULT_MEM_OPS_IMPL pico_mem_ops_default)

    pico_add_library(pico_mem_ops_pico)
    target_link_libraries(pico_mem_ops INTERFACE
            $<IF:$<BOOL:$<TARGET_PROPERTY:PICO_TARGET_MEM_OPS_IMPL>>,$<TARGET_PROPERTY:PICO_TARGET_MEM_OPS_IMPL>,${PICO_DEFAULT_MEM_OPS_IMPL}>)

    target_sources(pico_mem_ops_pico INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/mem_ops_aeabi.S
            )
    target_include_directories(pico_mem_ops_pico_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
    pico_mirrored_target_link_libraries(pico_mem_ops_pico INTERFACE pico_base)

    target_link_libraries(pico_mem_ops INTERFACE pico_bootrom)

    pico_wrap_function(pico_mem_ops_pico memcpy)
    pico_wrap_function(pico_mem_ops_pico memset)
    pico_wrap_function(pico_mem_ops_pico __aeabi_memcpy)
    pico_wrap_function(pico_mem_ops_pico __aeabi_memset)
    pico_wrap_function(pico_mem_ops_pico __aeabi_memcpy4)
    pico_wrap_function(pico_mem_ops_pico __aeabi_memset4)
    pico_wrap_function(pico_mem_ops_pico __aeabi_memcpy8)
    pico_wrap_function(pico_mem_ops_pico __aeabi_memset8)

    macro(pico_set_mem_ops_implementation TARGET IMPL)
        get_target_property(target_type ${TARGET} TYPE)
        if ("EXECUTABLE" STREQUAL "${target_type}")
            set_target_properties(${TARGET} PROPERTIES PICO_TARGET_MEM_OPS_IMPL "pico_mem_ops_${IMPL}")
        else()
            message(FATAL_ERROR "mem_ops implementation must be set on executable not library")
        endif()
    endmacro()
endif()
