function(_pico_init_pioasm)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PICO_SDK_PATH}/tools)
    # todo CMAKE_CURRENT_FUNCTION_LIST_DIR ... what version?
    find_package(Pioasm REQUIRED)
endfunction()

function(pico_generate_pio_header TARGET PIO)
    _pico_init_pioasm()
    cmake_parse_arguments(pico_generate_pio_header "" "OUTPUT_DIR" "" ${ARGN} )

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

    add_custom_target(${HEADER_GEN_TARGET} DEPENDS ${HEADER} Pioasm)

    add_custom_command(OUTPUT ${HEADER}
            DEPENDS ${PIO}
            COMMAND Pioasm -o c-sdk ${PIO} ${HEADER}
            )
    add_dependencies(${TARGET} ${HEADER_GEN_TARGET})
    get_target_property(target_type ${TARGET} TYPE)
    if ("EXECUTABLE" STREQUAL "${target_type}")
        target_include_directories(${TARGET} PRIVATE ${HEADER_DIR})
    else()
        target_include_directories(${TARGET} INTERFACE ${HEADER_DIR})
    endif()
endfunction()

function(pico_add_uf2_output TARGET)
    if (NOT ELF2UF2_FOUND)
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PICO_SDK_PATH}/tools)
        find_package(ELF2UF2)
    endif()
    if (ELF2UF2_FOUND)
        add_custom_command(TARGET ${TARGET} POST_BUILD
                COMMAND ELF2UF2 ${TARGET}${CMAKE_EXECUTABLE_SUFFIX} ${TARGET}.uf2)
    endif()
endfunction()

if (NOT DEFINED PICO_BUILD_PICOFLASH)
    if (DEFINED ENV{PICO_BUILD_PICOFLASH})
        set(PICO_BUILD_PICOFLASH $ENV{PICO_BUILD_PICOFLASH})
    else()
        # for now
        set(PICO_BUILD_PICOFLASH 1)
    endif()
endif()

if (PICO_BUILD_PICOTOOL)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PICO_SDK_PATH}/tools)
    find_package(Picotool REQUIRED)
endif()
