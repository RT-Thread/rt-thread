# PICO_CMAKE_CONFIG: PICO_DEFAULT_BOOT_STAGE2_FILE, Default boot stage 2 file to use unless overridden by pico_set_boot_stage2 on the TARGET; this setting is useful when explicitly setting the default build from a per board CMake file, group=build
# PICO_CMAKE_CONFIG: PICO_DEFAULT_BOOT_STAGE2, Simpler alternative to specifying PICO_DEFAULT_BOOT_STAGE2_FILE where the file is src/rp2_common/boot_stage2/{PICO_DEFAULT_BOOT_STAGE2}.S, default=compile_time_choice, group=build

if (DEFINED ENV{PICO_DEFAULT_BOOT_STAGE2_FILE})
    set(PICO_DEFAULT_BOOT_STAGE2_FILE $ENV{PICO_DEFAULT_BOOT_STAGE2_FILE})
    message("Using PICO_DEFAULT_BOOT_STAGE2_FILE from environment ('${PICO_DEFAULT_BOOT_STAGE2_FILE}')")
elseif (PICO_DEFAULT_BOOT_STAGE2_FILE)
    # explicitly set, so cache it
    set(PICO_DEFAULT_BOOT_STAGE2_FILE "${PICO_DEFAULT_BOOT_STAGE2_FILE}" CACHE STRING "boot stage 2 source file" FORCE)
endif()

set(PICO_BOOT_STAGE2_COMPILE_TIME_CHOICE_NAME compile_time_choice) # local var
if (NOT PICO_DEFAULT_BOOT_STAGE2_FILE)
    if (DEFINED ENV{PICO_DEFAULT_BOOT_STAGE2})
        set(PICO_DEFAULT_BOOT_STAGE2 $ENV{PICO_DEFAULT_BOOT_STAGE2})
        message("Using PICO_DEFAULT_BOOT_STAGE2 from environment ('${PICO_DEFAULT_BOOT_STAGE2}')")
    endif()
    if (NOT DEFINED PICO_DEFAULT_BOOT_STAGE2)
        set(PICO_DEFAULT_BOOT_STAGE2 ${PICO_BOOT_STAGE2_COMPILE_TIME_CHOICE_NAME})
    endif()
    set(PICO_DEFAULT_BOOT_STAGE2 "${PICO_DEFAULT_BOOT_STAGE2}" CACHE STRING "boot stage 2 short name" FORCE)
    set(PICO_DEFAULT_BOOT_STAGE2_FILE "${CMAKE_CURRENT_LIST_DIR}/${PICO_DEFAULT_BOOT_STAGE2}.S")
endif()

if (NOT EXISTS ${PICO_DEFAULT_BOOT_STAGE2_FILE})
    message(FATAL_ERROR "Specified boot stage 2 source '${PICO_DEFAULT_BOOT_STAGE2_FILE}' does not exist.")
endif()
pico_register_common_scope_var(PICO_DEFAULT_BOOT_STAGE2_FILE)

# needed by function below
set(PICO_BOOT_STAGE2_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")

add_library(boot_stage2_headers INTERFACE)
target_include_directories(boot_stage2_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

# by convention the first source file name without extension is used for the binary info name
function(pico_define_boot_stage2 NAME SOURCES)
    add_executable(${NAME}
            ${SOURCES}
    )

    # todo bit of an abstraction failure - revisit for Clang support anyway
    if (PICO_C_COMPILER_IS_CLANG)
        target_link_options(${NAME} PRIVATE "-nostdlib")
    elseif (PICO_C_COMPILER_IS_GNU)
        target_link_options(${NAME} PRIVATE "--specs=nosys.specs")
        target_link_options(${NAME} PRIVATE "-nostartfiles")
    endif ()

    # boot2_helpers include dir
    target_include_directories(${NAME} PRIVATE ${PICO_BOOT_STAGE2_DIR}/asminclude)

    target_link_libraries(${NAME} hardware_regs boot_stage2_headers)
    target_link_options(${NAME} PRIVATE "LINKER:--script=${PICO_BOOT_STAGE2_DIR}/boot_stage2.ld")
    set_target_properties(${NAME} PROPERTIES LINK_DEPENDS ${PICO_BOOT_STAGE2_DIR}/boot_stage2.ld)

    pico_add_dis_output(${NAME})
    pico_add_map_output(${NAME})

    set(ORIGINAL_BIN ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.bin)
    set(PADDED_CHECKSUMMED_ASM ${CMAKE_CURRENT_BINARY_DIR}/${NAME}_padded_checksummed.S)

    find_package (Python3 REQUIRED COMPONENTS Interpreter)

    add_custom_target(${NAME}_bin DEPENDS ${ORIGINAL_BIN})
    add_custom_command(OUTPUT ${ORIGINAL_BIN} DEPENDS ${NAME} COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${NAME}> ${ORIGINAL_BIN}
        VERBATIM)

    add_custom_target(${NAME}_padded_checksummed_asm DEPENDS ${PADDED_CHECKSUMMED_ASM})
    add_custom_command(OUTPUT ${PADDED_CHECKSUMMED_ASM} DEPENDS ${ORIGINAL_BIN}
            COMMAND ${Python3_EXECUTABLE} ${PICO_BOOT_STAGE2_DIR}/pad_checksum -s 0xffffffff ${ORIGINAL_BIN} ${PADDED_CHECKSUMMED_ASM}
            VERBATIM)

    add_library(${NAME}_library INTERFACE)
    add_dependencies(${NAME}_library ${NAME}_padded_checksummed_asm)
    # not strictly (or indeed actually) a link library, but this avoids dependency cycle
    target_link_libraries(${NAME}_library INTERFACE ${PADDED_CHECKSUMMED_ASM})
    target_link_libraries(${NAME}_library INTERFACE boot_stage2_headers)

    list(GET SOURCES 0 FIRST_SOURCE)
    get_filename_component(BOOT_STAGE2_BI_NAME ${FIRST_SOURCE} NAME_WE)

    # we only set the PICO_BUILD_STAGE2_NAME if it isn't 'compile_time_choice'
    if (NOT BOOT_STAGE2_BI_NAME STREQUAL PICO_BOOT_STAGE2_COMPILE_TIME_CHOICE_NAME)
        target_compile_definitions(${NAME} INTERFACE
                -DPICO_BUILD_BOOT_STAGE2_NAME="${BOOT_STAGE2_BI_NAME}")
        target_compile_definitions(${NAME}_library INTERFACE
                -DPICO_BUILD_BOOT_STAGE2_NAME="${BOOT_STAGE2_BI_NAME}")
    endif()
endfunction()

macro(pico_set_boot_stage2 TARGET NAME)
    get_target_property(target_type ${TARGET} TYPE)
    if ("EXECUTABLE" STREQUAL "${target_type}")
        set_target_properties(${TARGET} PROPERTIES PICO_TARGET_BOOT_STAGE2 "${NAME}")
    else()
        message(FATAL_ERROR "boot stage 2 implementation must be set on executable not library")
    endif()
endmacro()

pico_define_boot_stage2(bs2_default ${PICO_DEFAULT_BOOT_STAGE2_FILE})

# Create a new boot stage 2 target using the default implementation for the current build (PICO_BOARD derived)
function(pico_clone_default_boot_stage2 NAME)
    pico_define_boot_stage2(${NAME} ${PICO_DEFAULT_BOOT_STAGE2_FILE})
endfunction()

pico_promote_common_scope_vars()