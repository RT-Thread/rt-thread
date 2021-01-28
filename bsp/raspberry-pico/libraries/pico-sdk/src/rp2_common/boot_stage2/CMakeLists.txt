# PICO_CMAKE_CONFIG: PICO_DEFAULT_BOOT_STAGE2_FILE, Default stage2 file to use unless overridden by pico_set_boot_stage2 on the TARGET, type=bool, default=.../boot2_w25q080.S, group=build
if (NOT PICO_DEFAULT_BOOT_STAGE2_FILE)
    set(PICO_DEFAULT_BOOT_STAGE2_FILE "${CMAKE_CURRENT_LIST_DIR}/boot2_w25q080.S")
endif()

set(PICO_DEFAULT_BOOT_STAGE2_FILE "${PICO_DEFAULT_BOOT_STAGE2_FILE}" CACHE STRING "boot_stage2 source file" FORCE)

if (NOT EXISTS ${PICO_DEFAULT_BOOT_STAGE2_FILE})
    message(FATAL_ERROR "Specified boot_stage2 source '${PICO_BOOT_STAGE2_FILE}' does not exist.")
endif()

# needed by function below
set(PICO_BOOT_STAGE2_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")

function(pico_define_boot_stage2 NAME SOURCES)
    add_executable(${NAME}
            ${SOURCES}
    )
    
    # todo bit of an abstraction failure - revisit for Clang support anyway
    if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        target_link_options(${NAME} PRIVATE "-nostdlib")
    else ()
        target_link_options(${NAME} PRIVATE "--specs=nosys.specs")
        target_link_options(${NAME} PRIVATE "-nostartfiles")
    endif ()
    
    target_link_libraries(${NAME} hardware_regs)
    target_link_options(${NAME} PRIVATE "LINKER:--script=${PICO_BOOT_STAGE2_DIR}/boot_stage2.ld")
    set_target_properties(${NAME} PROPERTIES LINK_DEPENDS ${PICO_BOOT_STAGE2_DIR}/boot_stage2.ld)
    
    pico_add_dis_output(${NAME})
    pico_add_map_output(${NAME})
    
    set(ORIGINAL_BIN ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.bin)
    set(PADDED_CHECKSUMMED_ASM ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_padded_checksummed.S)
    
    add_custom_target(${NAME}_bin DEPENDS ${ORIGINAL_BIN})
    add_dependencies(${NAME}_bin ${NAME})
    
    add_custom_command(OUTPUT ${ORIGINAL_BIN} COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${NAME}> ${ORIGINAL_BIN})
    
    find_package (Python3 REQUIRED COMPONENTS Interpreter)
    add_custom_command(OUTPUT ${PADDED_CHECKSUMMED_ASM}
            COMMAND ${Python3_EXECUTABLE} ${PICO_BOOT_STAGE2_DIR}/pad_checksum -s 0xffffffff ${ORIGINAL_BIN} ${PADDED_CHECKSUMMED_ASM}
            )
    
    add_custom_target(${NAME}_padded_checksummed_asm DEPENDS ${PADDED_CHECKSUMMED_ASM})
    add_dependencies(${NAME}_padded_checksummed_asm ${NAME}_bin)
    
    add_library(${NAME}_library INTERFACE)
    add_dependencies(${NAME}_library ${NAME}_padded_checksummed_asm)
    # not strictly (or indeed actually) a link library, but this avoids dependency cycle
    target_link_libraries(${NAME}_library INTERFACE ${PADDED_CHECKSUMMED_ASM})
endfunction()

macro(pico_set_boot_stage2 TARGET NAME)
    get_target_property(target_type ${TARGET} TYPE)
    if ("EXECUTABLE" STREQUAL "${target_type}")
        set_target_properties(${TARGET} PROPERTIES PICO_TARGET_BOOT_STAGE2 "${NAME}")
    else()
        message(FATAL_ERROR "boot stage2 implementation must be set on executable not library")
    endif()
endmacro()

pico_define_boot_stage2(bs2_default ${PICO_DEFAULT_BOOT_STAGE2_FILE})

