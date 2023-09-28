cmake_policy(SET CMP0079 NEW) # allow inserting of dependencies into our INTERFACE libraries
set(PICO_PLATFORM_CMAKE_FILE "" CACHE INTERNAL "")
set(PICO_DOXYGEN_PATHS "" CACHE INTERNAL "") # generated each time

if (NOT PICO_PLATFORM_CMAKE_FILE)
    set(PICO_PLATFORM_CMAKE_FILE ${CMAKE_CURRENT_LIST_DIR}/${PICO_PLATFORM}.cmake CACHE INTERNAL "")
endif ()

if (NOT EXISTS "${PICO_PLATFORM_CMAKE_FILE}")
    message(FATAL_ERROR "${PICO_PLATFORM_CMAKE_FILE} does not exist. \
    Either specify a valid PICO_PLATFORM (or PICO_PLATFORM_CMAKE_FILE).")
endif ()

# Initialize board related build/compile settings
include(${CMAKE_CURRENT_LIST_DIR}/board_setup.cmake)

# call add_subdirectory(subdir) unless SKIP_SUBDIR evaluates to true
function(pico_add_subdirectory subdir)
    # todo add option to disable skip flag
    string(TOUPPER ${subdir} subdir_upper)
    set(replace_flag SKIP_${subdir_upper})
    if (NOT ${replace_flag})
        add_subdirectory(${subdir})
    else ()
        message("Not including ${subdir} because ${replace_flag} defined.")
    endif ()
    pico_promote_common_scope_vars()
endfunction()

# takes dependencies after the target
function(pico_mirrored_target_link_libraries TARGET SCOPE)
    if (${ARGC} LESS 3)
        message(FATAL_ERROR "expected a target, scope and at least one dependency")
    endif()
    if (NOT TARGET ${TARGET}_headers)
        message(FATAL_ERROR "${TARGET} does not have headers")
    endif()
    # library should depend on its own header
    target_link_libraries(${TARGET} ${SCOPE} ${TARGET}_headers)
    foreach(DEPENDENCY IN LISTS ARGN)
        if (DEPENDENCY MATCHES ".*_headers")
            message(FATAL_ERROR "should not use headers with pico_mirrored_target_link_libraries")
        endif()
        # note, it would be nice to only add the dependency if it exists, but we do
        # not necessarily add libraries in reverse dependency order, so we do this
        # unconditionally, so this function should only be passed dependencies that
        # have headers, or link will fail with a missing library -lfoo_headers
        target_link_libraries(${TARGET}_headers ${SCOPE} ${DEPENDENCY}_headers)
        target_link_libraries(${TARGET} ${SCOPE} ${DEPENDENCY})
    endforeach()
endfunction()

# add a link option to wrap the given function name; i.e. -Wl:wrap=FUNCNAME for gcc
function(pico_wrap_function TARGET FUNCNAME)
    target_link_options(${TARGET} INTERFACE "LINKER:--wrap=${FUNCNAME}")
endfunction()

# add map file generation for the given target
function(pico_add_map_output TARGET)
    get_target_property(target_type ${TARGET} TYPE)
    if ("EXECUTABLE" STREQUAL "${target_type}")
        target_link_options(${TARGET} PRIVATE "LINKER:-Map=$<IF:$<BOOL:$<TARGET_PROPERTY:OUTPUT_NAME>>,$<TARGET_PROPERTY:OUTPUT_NAME>,$<TARGET_PROPERTY:NAME>>${CMAKE_EXECUTABLE_SUFFIX}.map")
    else ()
        target_link_options(${TARGET} INTERFACE "LINKER:-Map=$<IF:$<BOOL:$<TARGET_PROPERTY:OUTPUT_NAME>>,$<TARGET_PROPERTY:OUTPUT_NAME>,$<TARGET_PROPERTY:NAME>>${CMAKE_EXECUTABLE_SUFFIX}.map")
    endif ()
endfunction()

# create a hardware_NAME_headers target (see pico_simple_hardware_headers_target)
# create a hardware_NAME target (see pico_simple_hardware_target)
macro(pico_simple_hardware_target NAME)
    pico_simple_hardware_headers_target(${NAME})
    pico_simple_hardware_impl_target(${NAME})
endmacro()

# create an INTERFACE library named target, and define LIB_TARGET=1 (upper case) as a compile option
# and make it dependent on a pre-existing corresponding _headers library
# optional arg NOFLAG will skip the LIB_TARGET definition
function(pico_add_impl_library target)
    add_library(${target} INTERFACE)
    string(TOUPPER ${target} TARGET_UPPER)
    if (${ARGC} GREATER 1)
        if (NOT "${ARGV1}" STREQUAL "NOFLAG")
            message(FATAL_ERROR "Unknown parameter ${ARGV1}")
        endif()
    else()
        target_compile_definitions(${target} INTERFACE LIB_${TARGET_UPPER}=1)
    endif()
    target_link_libraries(${target} INTERFACE ${target}_headers)
endfunction()

# create an INTERFACE library named target along with associated header, and define LIB_TARGET=1 (upper case) as a compile option
# optional arg NOFLAG will skip the LIB_TARGET definition
function(pico_add_library target)
    add_library(${target}_headers INTERFACE)
    pico_add_impl_library(${target} ${ARGN})
endfunction()

# create an INTERFACE library named hardware_NAME_headers INTERFACE library if it doesn't already exist,
#        and add include/ relative to the calling directory to the includes.
#        and hardware_structs and hardware_claim as dependencies of the library
macro(pico_simple_hardware_headers_target NAME)
    if (NOT TARGET hardware_${NAME}_headers)
        add_library(hardware_${NAME}_headers INTERFACE)

        target_include_directories(hardware_${NAME}_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
        target_link_libraries(hardware_${NAME}_headers INTERFACE pico_base_headers)
        if (NOT PICO_NO_HARDWARE)
            target_link_libraries(hardware_${NAME}_headers INTERFACE hardware_structs hardware_claim_headers)
        endif()
    endif()
endmacro()

# create an INTERFACE library named hardware_NAME if it doesn't exist, along with a hardware_NAME_headers
#        INTERFACE library that it depends on. The hardware_NAME_headers library add include/ relative to
#        and pico_base_headers, and harddware_structs as a dependency of the library
macro(pico_simple_hardware_headers_only_target NAME)
    if (NOT TARGET hardware_${NAME})
        # Choosing not to add LIB_HARDWARE_ defines to avoid command line bloat pending a need (they aren't
        #   super interesting except to determine functionality as they are mostly passive accessors, however
        #   they could be useful to determine if the header is available.
        # pico_add_sdk_impl_library(hardware_${NAME})
        add_library(hardware_${NAME}_headers INTERFACE)

        # a headers only target should still have an explicit _headers library for consistency
        target_include_directories(hardware_${NAME}_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
        target_link_libraries(hardware_${NAME}_headers INTERFACE pico_base_headers)
        if (NOT PICO_NO_HARDWARE)
            target_link_libraries(hardware_${NAME}_headers INTERFACE hardware_structs)
        endif()

        add_library(hardware_${NAME} INTERFACE)
        target_link_libraries(hardware_${NAME} INTERFACE hardware_${NAME}_headers)
    endif()
endmacro()

# create an INTERFACE library named hardware_NAME if it doesn't exist, dependent on a pre-existing  hardware_NAME_headers
#        INTERFACE library and pico_platform. The file NAME.c relative to the caller is added to the C sources for the hardware_NAME
macro(pico_simple_hardware_impl_target NAME)
    if (NOT TARGET hardware_${NAME})
        # Choosing not to add LIB_HARDWARE_ defines to avoid command line bloat pending a need (they aren't
        #   super interesting except to determine functionality as they are mostly passive accessors, however
        #   they could be useful to determine if the header is available.
        # pico_add_sdk_impl_library(hardware_${NAME})
        add_library(hardware_${NAME} INTERFACE)

        target_sources(hardware_${NAME} INTERFACE
                ${CMAKE_CURRENT_LIST_DIR}/${NAME}.c
                )

        pico_mirrored_target_link_libraries(hardware_${NAME} INTERFACE pico_platform)
        if (NOT PICO_NO_HARDWARE)
            target_link_libraries(hardware_${NAME} INTERFACE hardware_claim)
        endif()
    endif()
endmacro()

function(pico_add_doxygen SOURCE_DIR)
    set(PICO_DOXYGEN_PATHS "${PICO_DOXYGEN_PATHS} ${SOURCE_DIR}" CACHE INTERNAL "")
endfunction()

function(pico_add_doxygen_exclude SOURCE_DIR)
    set(PICO_DOXYGEN_EXCLUDE_PATHS "${PICO_DOXYGEN_EXCLUDE_PATHS} ${SOURCE_DIR}" CACHE INTERNAL "")
endfunction()

include(${PICO_PLATFORM_CMAKE_FILE})

pico_promote_common_scope_vars()