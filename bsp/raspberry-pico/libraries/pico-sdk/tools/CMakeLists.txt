function(_pico_init_pioasm)
    if (NOT Pioasm_FOUND)
        # Assemble the version string from components instead of using PICO_SDK_VERSION_STRING, because the version string
        # potentially has a PRE_RELEASE_ID suffix, which will trip up the find_package call.
        find_package(pico-sdk-tools "${PICO_SDK_VERSION_MAJOR}.${PICO_SDK_VERSION_MINOR}.${PICO_SDK_VERSION_REVISION}" QUIET CONFIG CMAKE_FIND_ROOT_PATH_BOTH)

        if (NOT Pioasm_FOUND)
            set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PICO_SDK_PATH}/tools)
            # todo CMAKE_CURRENT_FUNCTION_LIST_DIR ... what version?
            find_package(Pioasm REQUIRED)
        endif()
    endif()
endfunction()

# PICO_CMAKE_CONFIG: PICO_DEFAULT_PIOASM_OUTPUT_FORMAT, default output format used by pioasm when using pico_generate_pio_header, default=c-sdk, group=build
function(pico_generate_pio_header TARGET PIO)
    _pico_init_pioasm()
    cmake_parse_arguments(pico_generate_pio_header "" "OUTPUT_FORMAT;OUTPUT_DIR" "" ${ARGN} )

    if (pico_generate_pio_header_OUTPUT_FORMAT)
        set(OUTPUT_FORMAT "${pico_generate_pio_header_OUTPUT_FORMAT}")
    elseif(DEFINED PICO_DEFAULT_PIOASM_OUTPUT_FORMAT)
        set(OUTPUT_FORMAT "${PICO_DEFAULT_PIOASM_OUTPUT_FORMAT}")
    else()
        set(OUTPUT_FORMAT "c-sdk")
    endif()

    if (pico_generate_pio_header_OUTPUT_DIR)
        get_filename_component(HEADER_DIR ${pico_generate_pio_header_OUTPUT_DIR} ABSOLUTE)
    else()
        set(HEADER_DIR "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
    get_filename_component(PIO_NAME ${PIO} NAME)
    set(HEADER "${HEADER_DIR}/${PIO_NAME}.h")
    #message("Will generate ${HEADER}")
    get_filename_component(HEADER_GEN_TARGET ${PIO} NAME_WE)
    set(HEADER_GEN_TARGET "${TARGET}_${HEADER_GEN_TARGET}_pio_h")

    add_custom_target(${HEADER_GEN_TARGET} DEPENDS ${HEADER})

    add_custom_command(OUTPUT ${HEADER}
            DEPENDS ${PIO}
            COMMAND Pioasm -o ${OUTPUT_FORMAT} ${PIO} ${HEADER}
            VERBATIM)
    add_dependencies(${TARGET} ${HEADER_GEN_TARGET})
    get_target_property(target_type ${TARGET} TYPE)
    if ("INTERFACE_LIBRARY" STREQUAL "${target_type}")
        target_include_directories(${TARGET} INTERFACE ${HEADER_DIR})
    else()
        target_include_directories(${TARGET} PUBLIC ${HEADER_DIR})
    endif()
endfunction()

function(pico_add_uf2_output TARGET)
    get_target_property(${TARGET}_archive_directory ${TARGET} ARCHIVE_OUTPUT_DIRECTORY)
    if (${TARGET}_archive_directory)
        get_filename_component(output_path "${${TARGET}_archive_directory}"
                REALPATH BASE_DIR "${CMAKE_CURRENT_BINARY_DIR}")
        file(MAKE_DIRECTORY "${output_path}")
        set(output_path "${output_path}/")
    else()
        set(output_path "")
    endif()
    if (NOT ELF2UF2_FOUND)
        find_package(pico-sdk-tools "${PICO_SDK_VERSION_MAJOR}.${PICO_SDK_VERSION_MINOR}.${PICO_SDK_VERSION_REVISION}" QUIET CONFIG CMAKE_FIND_ROOT_PATH_BOTH)
        if (NOT ELF2UF2_FOUND)
            set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PICO_SDK_PATH}/tools)
            find_package(ELF2UF2)
        endif()
    endif()
    if (ELF2UF2_FOUND)
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ELF2UF2 $<TARGET_FILE:${TARGET}> ${output_path}$<IF:$<BOOL:$<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>>,$<TARGET_PROPERTY:${TARGET},OUTPUT_NAME>,$<TARGET_PROPERTY:${TARGET},NAME>>.uf2
            VERBATIM)
    endif()
endfunction()
