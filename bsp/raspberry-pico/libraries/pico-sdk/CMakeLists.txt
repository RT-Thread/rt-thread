cmake_minimum_required(VERSION 3.12)
if (NOT TARGET _pico_sdk_inclusion_marker)
    add_library(_pico_sdk_inclusion_marker INTERFACE)
    include(pico_sdk_init.cmake)

    project(pico_sdk C CXX ASM)

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

    add_subdirectory(tools)
    add_subdirectory(src)

    add_compile_options(-Winline)

    if (PICO_SDK_TOP_LEVEL_PROJECT AND NOT DEFINED PICO_SDK_TESTS_ENABLED)
        set(PICO_SDK_TESTS_ENABLED 1)
    endif()
    if (PICO_SDK_TESTS_ENABLED)
        add_subdirectory(test)
    endif ()
    set(PICO_SDK_TESTS_ENABLED "${PICO_SDK_TESTS_ENABLED}" CACHE INTERNAL "Enable build of SDK tests")

    # allow customization
    add_sub_list_dirs(PICO_SDK_POST_LIST_DIRS)

    # add docs at the end, as we gather documentation dirs as we go
    add_subdirectory(docs)
endif()

