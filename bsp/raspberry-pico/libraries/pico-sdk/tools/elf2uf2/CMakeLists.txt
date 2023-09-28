cmake_minimum_required(VERSION 3.12)
project(elf2uf2)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(../../src/common/boot_uf2 boot_uf2_headers)

add_executable(elf2uf2 main.cpp)
if (WIN32 AND NOT MINGW AND (CMAKE_CXX_COMPILER_ID STREQUAL "Clang"))
    target_compile_definitions(elf2uf2 PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()
target_link_libraries(elf2uf2 boot_uf2_headers)