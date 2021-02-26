# Initialize the PICO SDK
# This file must be included prior to the project() call

if (_PICO_SDK_INIT)
    return()
endif ()
set(_PICO_SDK_INIT 1)

function(pico_is_top_level_project VAR)
    string(TOLOWER ${CMAKE_CURRENT_LIST_DIR} __list_dir)
    string(TOLOWER ${CMAKE_SOURCE_DIR} __source_dir)
    if (__source_dir STREQUAL __list_dir)
        set(${VAR} 1 PARENT_SCOPE)
    else()
        set(${VAR} 0 PARENT_SCOPE)
    endif()
endfunction()

if (NOT PICO_SDK_PATH)
    set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR})
endif ()

get_filename_component(PICO_SDK_PATH "${PICO_SDK_PATH}" REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")

set(PICO_SDK_PATH ${CMAKE_CURRENT_LIST_DIR} CACHE PATH "Path to the Pico SDK" FORCE)

list(APPEND CMAKE_MODULE_PATH ${PICO_SDK_PATH}/cmake)

include(${CMAKE_CURRENT_LIST_DIR}/pico_sdk_version.cmake)
include(pico_utils)

message("Pico SDK is located at ${CMAKE_CURRENT_LIST_DIR}")

include(pico_pre_load_platform)

# todo perhaps this should be included by the platform instead?
# We want to configure correct toolchain prior to project load
include(pico_pre_load_toolchain)

macro(pico_sdk_init)
    if (NOT CMAKE_PROJECT_NAME)
        message(WARNING "pico_sdk_init() should be called after the project is created (and languages added)")
    endif()
    add_subdirectory(${PICO_SDK_PATH} pico_sdk)
endmacro()

macro(add_sub_list_dirs var)
    foreach(LIST_DIR IN LISTS ${var})
        get_filename_component(SHORT_NAME "${LIST_DIR}" NAME)
        message("Including custom CMakeLists.txt ${SHORT_NAME}")
        add_subdirectory(${LIST_DIR} ${SHORT_NAME})
    endforeach()
endmacro()

