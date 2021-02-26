if (NOT TARGET pico_standard_link)
    add_library(pico_standard_link INTERFACE)

    target_sources(pico_standard_link INTERFACE
        ${CMAKE_CURRENT_LIST_DIR}/crt0.S
        ${CMAKE_CURRENT_LIST_DIR}/new_delete.cpp
        ${CMAKE_CURRENT_LIST_DIR}/binary_info.c
    )

    pico_add_map_output(pico_standard_link)

    # todo revisit when we do Clang
    if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        target_link_options(pico_standard_link INTERFACE "LINKER:-nostdlib")
    endif ()

    target_link_libraries(pico_standard_link INTERFACE hardware_regs pico_bootrom pico_binary_info pico_cxx_options)

    function(pico_add_link_depend TARGET dependency)
        get_target_property(target_type ${TARGET} TYPE)
        if (${target_type} STREQUAL "INTERFACE_LIBRARY")
            set(PROP "INTERFACE_LINK_DEPENDS")
        else()
            set(PROP "LINK_DEPENDS")
        endif()
        get_target_property(_LINK_DEPENDS ${TARGET} ${PROP})
        if (NOT _LINK_DEPENDS)
            set(_LINK_DEPENDS ${dependency})
        else()
            list(APPEND _LINK_DEPENDS ${dependency})
        endif()
        set_target_properties(${TARGET} PROPERTIES ${PROP} "${_LINK_DEPENDS}")
    endfunction()

    # need this because cmake does not appear to have a way to override an INTERFACE variable
    function(pico_set_linker_script TARGET LDSCRIPT)
        set_target_properties(${TARGET} PROPERTIES PICO_TARGET_LINKER_SCRIPT ${LDSCRIPT})
        pico_add_link_depend(${TARGET} ${LDSCRIPT})
    endfunction()

    function(pico_set_binary_type TARGET TYPE)
        set_target_properties(${TARGET} PROPERTIES PICO_TARGET_BINARY_TYPE ${TYPE})
    endfunction()

    if (PICO_NO_FLASH)
        set(PICO_DEFAULT_BINARY_TYPE no_flash)
    elseif (PICO_USE_BLOCKED_RAM)
        set(PICO_DEFAULT_BINARY_TYPE blocked_ram)
    elseif (PICO_COPY_TO_RAM)
        set(PICO_DEFAULT_BINARY_TYPE copy_to_ram)
    else()
        set(PICO_DEFAULT_BINARY_TYPE default)
    endif()

    # LINKER script will be PICO_TARGET_LINKER_SCRIPT if set on target, or ${CMAKE_CURRENT_LIST_DIR}/memmap_foo.ld
    # if PICO_TARGET_BINARY_TYPE is set to foo on the target, otherwise ${CMAKE_CURRENT_LIST_DIR}/memmap_${PICO_DEFAULT_BINARY_TYPE).ld
    target_link_options(pico_standard_link INTERFACE
            "LINKER:--script=$<IF:$<BOOL:$<TARGET_PROPERTY:PICO_TARGET_LINKER_SCRIPT>>,$<TARGET_PROPERTY:PICO_TARGET_LINKER_SCRIPT>,${CMAKE_CURRENT_LIST_DIR}/memmap_$<IF:$<STREQUAL:$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>,>,${PICO_DEFAULT_BINARY_TYPE},$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>>.ld>"
    )

    # PICO_NO_FLASH will be set based on PICO_TARGET_BUILD_TYPE target property being equal to no_flash if set, otherwise to the value of the PICO_NO_FLASH cmake variable unless PICO_TARGET_TYPE is set to something else
    # PICO_BUILD_DEFINE: PICO_NO_FLASH, whether this is a 'no_flash' build, type=bool, default=0, but dependent on CMake options, group=pico_standard_link
    target_compile_definitions(pico_standard_link INTERFACE PICO_NO_FLASH=$<IF:$<STREQUAL:$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>,no_flash>,1,$<AND:$<BOOL:${PICO_NO_FLASH}>,$<STREQUAL:,$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>>>>)
    # PICO_USE_BLOCKED_RAM will be set based on PICO_TARGET_BUILD_TYPE target property being equal to use_blocked_ram if set, otherwise to the value of the PICO_USE_BLOCKED_RAM cmake variable unless PICO_TARGET_TYPE is set to something else
    # PICO_BUILD_DEFINE: PICO_USE_BLOCKS_RAM, whether this is a 'blocked_ram' build, type=bool, default=0, but dependent on CMake options, group=pico_standard_link
    target_compile_definitions(pico_standard_link INTERFACE PICO_USE_BLOCKED_RAM=$<IF:$<STREQUAL:$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>,use_blocked_ram>,1,$<AND:$<BOOL:${PICO_USE_BLOCKED_RAM}>,$<STREQUAL:,$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>>>>)
    # PICO_COPY_TO_RAM will be set based on PICO_TARGET_BUILD_TYPE target property being equal to copy_to_ram if set, otherwise to the value of the PICO_COPY_TO_RAM cmake variable unless PICO_TARGET_TYPE is set to something else
    # PICO_BUILD_DEFINE: PICO_COPY_TO_RAM, whether this is a 'copy_to_ram' build, type=bool, default=0, but dependent on CMake options, group=pico_standard_link
    target_compile_definitions(pico_standard_link INTERFACE PICO_COPY_TO_RAM=$<IF:$<STREQUAL:$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>,copy_to_ram>,1,$<AND:$<BOOL:${PICO_COPY_TO_RAM}>,$<STREQUAL:,$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>>>>)

    target_compile_definitions(pico_standard_link INTERFACE PICO_CMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}")
    if (PICO_DEOPTIMIZED_DEBUG AND "${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        target_compile_definitions(pico_standard_link INTERFACE PICO_DEOPTIMIZED_DEBUG=1)
    endif()

    # todo revisit/recall reasoning for why not -nostartfiles always?
    # -nostartfiles will be added if PICO_NO_FLASH would be defined to 1
    target_link_options(pico_standard_link INTERFACE $<$<IF:$<STREQUAL:$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>,no_flash>,1,$<AND:$<BOOL:${PICO_NO_FLASH}>,$<STREQUAL:,$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>>>>:-nostartfiles>)
    # boot_stage2 will be linked if PICO_NO_FLASH would be defined to 0
    target_link_libraries(pico_standard_link INTERFACE $<$<NOT:$<IF:$<STREQUAL:$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>,no_flash>,1,$<AND:$<BOOL:${PICO_NO_FLASH}>,$<STREQUAL:,$<TARGET_PROPERTY:PICO_TARGET_BINARY_TYPE>>>>>:$<IF:$<BOOL:$<TARGET_PROPERTY:PICO_TARGET_BOOT_STAGE2>>,$<TARGET_PROPERTY:PICO_TARGET_BOOT_STAGE2>,bs2_default>_library>)

    # done in compiler now
    #target_link_options(pico_standard_link INTERFACE "LINKER:--build-id=none")

    # this line occasionally useful for debugging ... todo maybe make a PICO_ var
#    target_compile_options(pico_standard_link INTERFACE --save-temps) #debugging only

    # PICO_CMAKE_CONFIG: PICO_NO_GC_SECTIONS, Disable -ffunction-sections -fdata-sections, and --gc-sections, type=bool, default=0, advanced=true, group=pico_standard_link
    if (NOT PICO_NO_GC_SECTIONS)
        target_compile_options(pico_standard_link INTERFACE -ffunction-sections -fdata-sections)
        target_link_options(pico_standard_link INTERFACE "LINKER:--gc-sections")
    endif()
endif()
