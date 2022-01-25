if (NOT TARGET pico_mem_ops)
    #shims for ROM functions for -lgcc functions  (listed below)
    add_library(pico_mem_ops INTERFACE)

    # no custom implementation; falls thru to compiler
    add_library(pico_mem_ops_compiler INTERFACE)
    # PICO_BUILD_DEFINE: PICO_MEM_OPS_COMPILER, whether compiler provided mem_ops memcpy etc. support is being used, type=bool, default=0, but dependent on CMake options, group=pico_mem_ops
    target_compile_definitions(pico_mem_ops_compiler INTERFACE
            PICO_MEM_OPS_COMPILER=1
            )

    # add alias "default" which is just pico.
    add_library(pico_mem_ops_default INTERFACE)
    target_link_libraries(pico_mem_ops_default INTERFACE pico_mem_ops_pico)

    set(PICO_DEFAULT_MEM_OPS_IMPL pico_mem_ops_default)

    add_library(pico_mem_ops_pico INTERFACE)
    target_link_libraries(pico_mem_ops INTERFACE
            $<IF:$<BOOL:$<TARGET_PROPERTY:PICO_TARGET_MEM_OPS_IMPL>>,$<TARGET_PROPERTY:PICO_TARGET_MEM_OPS_IMPL>,${PICO_DEFAULT_MEM_OPS_IMPL}>)

    # PICO_BUILD_DEFINE: PICO_MEM_OPS_PICO, whether optimized pico/bootrom provided mem_ops memcpy etc. support is being used, type=bool, default=1, but dependent on CMake options, group=pico_mem_ops
    target_compile_definitions(pico_mem_ops_pico INTERFACE
            PICO_MEM_OPS_PICO=1
            )


    target_sources(pico_mem_ops_pico INTERFACE
            ${CMAKE_CURRENT_LIST_DIR}/mem_ops_aeabi.S
            )


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
