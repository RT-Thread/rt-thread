add_library(pico_binary_info_headers INTERFACE)

target_include_directories(pico_binary_info_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

add_library(pico_binary_info INTERFACE)

target_link_libraries(pico_binary_info INTERFACE pico_binary_info_headers)

function(pico_set_program_name TARGET name)
    # PICO_BUILD_DEFINE: PICO_PROGRAM_NAME, value passed to pico_set_program_name, type=string, default=none, group=pico_binary_info
    target_compile_definitions(${TARGET} PRIVATE -DPICO_PROGRAM_NAME="${name}")
endfunction()

function(pico_set_program_description TARGET description)
    # since this is the command line, we will remove newlines
    string(REPLACE "\n" " " description ${description})
    string(REPLACE "\"" "\\\"" description ${description})
    # PICO_BUILD_DEFINE: PICO_PROGRAM_DESCRIPTION, value passed to pico_set_program_description, type=string, default=none, group=pico_binary_info
    target_compile_definitions(${TARGET} PRIVATE -DPICO_PROGRAM_DESCRIPTION="${description}")
endfunction()

function(pico_set_program_url TARGET url)
    # PICO_BUILD_DEFINE: PICO_PROGRAM_URL, value passed to pico_set_program_url, type=string, default=none, group=pico_binary_info
    target_compile_definitions(${TARGET} PRIVATE -DPICO_PROGRAM_URL="${url}")
endfunction()

function(pico_set_program_version TARGET version)
    # PICO_BUILD_DEFINE: PICO_PROGRAM_VERSION_STRING, value passed to pico_set_program_version, type=string, default=none, group=pico_binary_info
    target_compile_definitions(${TARGET} PRIVATE -DPICO_PROGRAM_VERSION_STRING="${version}")
endfunction()
