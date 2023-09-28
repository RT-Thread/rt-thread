cmake_minimum_required(VERSION 3.13)

# Note: this CMakeLists.txt can be used as a top-level CMakeLists.txt for the SDK itself. For all other uses
# it is included as a subdirectory via the pico_sdk_init() method provided by pico_sdk_init.cmake
if (NOT TARGET _pico_sdk_inclusion_marker)
    add_library(_pico_sdk_inclusion_marker INTERFACE)
    # This is a no-op unless we are the top-level CMakeLists.txt
    include(pico_sdk_init.cmake)

    project(pico_sdk C CXX ASM)

    string(REGEX MATCH "Clang" PICO_C_COMPILER_IS_CLANG "${CMAKE_C_COMPILER_ID}")
    string(REGEX MATCH "GNU" PICO_C_COMPILER_IS_GNU "${CMAKE_C_COMPILER_ID}")
    string(REGEX MATCH "IAR" PICO_C_COMPILER_IS_IAR "${CMAKE_C_COMPILER_ID}")
    pico_register_common_scope_var(PICO_C_COMPILER_IS_CLANG)
    pico_register_common_scope_var(PICO_C_COMPILER_IS_GNU)
    pico_register_common_scope_var(PICO_C_COMPILER_IS_IAR)

    message("Build type is ${CMAKE_BUILD_TYPE}")
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        if (PICO_DEOPTIMIZED_DEBUG)
            message("Using fully de-optimized debug build (set PICO_DEOPTIMIZED_DEBUG=0 to optimize)")
        else()
            message("Using regular optimized debug build (set PICO_DEOPTIMIZED_DEBUG=1 to de-optimize)")
        endif()
    endif()

    pico_is_top_level_project(PICO_SDK_TOP_LEVEL_PROJECT)

    set(CMAKE_C_STANDARD 11)
    set(CMAKE_CXX_STANDARD 11)

    if (NOT PICO_SDK_TOP_LEVEL_PROJECT)
        set(PICO_SDK 1 PARENT_SCOPE)
    endif()

    # allow customization
    add_sub_list_dirs(PICO_SDK_PRE_LIST_DIRS)
    add_sub_list_files(PICO_SDK_PRE_LIST_FILES)

    add_subdirectory(tools)
    add_subdirectory(src)

    # allow customization
    add_sub_list_dirs(PICO_SDK_POST_LIST_DIRS)
    add_sub_list_files(PICO_SDK_POST_LIST_FILES)

    if (PICO_SDK_TOP_LEVEL_PROJECT AND NOT DEFINED PICO_SDK_TESTS_ENABLED)
        set(PICO_SDK_TESTS_ENABLED 1)
    endif()
    if (PICO_SDK_TESTS_ENABLED)
        add_subdirectory(test)
    endif ()

    set(PICO_SDK_TESTS_ENABLED "${PICO_SDK_TESTS_ENABLED}" CACHE INTERNAL "Enable build of SDK tests")

    # add docs at the end, as we gather documentation dirs as we go
    add_subdirectory(docs)

    if (NOT PICO_SDK_TOP_LEVEL_PROJECT)
        pico_promote_common_scope_vars()
    endif()
endif()

