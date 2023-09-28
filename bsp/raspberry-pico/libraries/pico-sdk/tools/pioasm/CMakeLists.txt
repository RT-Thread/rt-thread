cmake_minimum_required(VERSION 3.4)
project(pioasm CXX)

set(CMAKE_CXX_STANDARD 11)

if (PIOASM_GENERATE_PARSER)
    find_package(BISON 3.4.2)
    find_package(FLEX 2.5.13) # no idea about the version

    FLEX_TARGET(pioasm_lexer lexer.ll ${CMAKE_CURRENT_SOURCE_DIR}/gen/lexer.cpp)
    BISON_TARGET(pioasm_parser parser.yy ${CMAKE_CURRENT_SOURCE_DIR}/gen/parser.cpp COMPILE_FLAGS "-Wcounterexamples")
    ADD_FLEX_BISON_DEPENDENCY(pioasm_lexer pioasm_parser)
endif()

add_executable(pioasm
        main.cpp
        pio_assembler.cpp
        pio_disassembler.cpp
        gen/lexer.cpp
        gen/parser.cpp
)

target_sources(pioasm PRIVATE c_sdk_output.cpp)
target_sources(pioasm PRIVATE python_output.cpp)
target_sources(pioasm PRIVATE hex_output.cpp)
target_sources(pioasm PRIVATE ada_output.cpp)
target_sources(pioasm PRIVATE ${PIOASM_EXTRA_SOURCE_FILES})

if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU") AND
    (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL "7") AND
    (CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9") AND
    (CMAKE_SYSTEM_PROCESSOR MATCHES "^arm.*$"))
    # disable GCC ARM info notice about ABI change
    target_compile_options(pioasm PRIVATE -Wno-psabi)
endif()

target_include_directories(pioasm PRIVATE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/gen)

if (MSVC OR
    (WIN32 AND NOT MINGW AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")))
    target_compile_definitions(pioasm PRIVATE YY_NO_UNISTD_H)
endif()
if (MSVC)
    target_compile_options(pioasm PRIVATE "/std:c++latest")
endif()

