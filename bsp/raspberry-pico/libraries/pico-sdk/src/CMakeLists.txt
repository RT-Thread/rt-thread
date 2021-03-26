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

include(${CMAKE_CURRENT_LIST_DIR}/board_setup.cmake)

# todo add option to disable skip flag
function(pico_add_subdirectory subdir)
    string(TOUPPER ${subdir} subdir_upper)
    set(replace_flag SKIP_${subdir_upper})
    if (NOT ${replace_flag})
        add_subdirectory(${subdir})
    else ()
        message("Not including ${subdir} because ${replace_flag} defined.")
    endif ()
endfunction()

function(pico_wrap_function TARGET FUNCNAME)
    target_link_options(${TARGET} INTERFACE "LINKER:--wrap=${FUNCNAME}")
endfunction()

function(pico_add_map_output TARGET)
    get_target_property(target_type ${TARGET} TYPE)
    if ("EXECUTABLE" STREQUAL "${target_type}")
        target_link_options(${TARGET} PRIVATE "LINKER:-Map=$<TARGET_PROPERTY:NAME>${CMAKE_EXECUTABLE_SUFFIX}.map")
    else ()
        target_link_options(${TARGET} INTERFACE "LINKER:-Map=$<TARGET_PROPERTY:NAME>${CMAKE_EXECUTABLE_SUFFIX}.map")
    endif ()
endfunction()

macro(pico_simple_hardware_target NAME)
    pico_simple_hardware_headers_target(${NAME})
    pico_simple_hardware_impl_target(${NAME})
endmacro()

macro(pico_simple_hardware_headers_target NAME)
    if (NOT TARGET hardware_${NAME}_headers)
        add_library(hardware_${NAME}_headers INTERFACE)

        target_include_directories(hardware_${NAME}_headers INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
        target_link_libraries(hardware_${NAME}_headers INTERFACE pico_base_headers)
        if (NOT PICO_NO_HARDWARE)
            target_link_libraries(hardware_${NAME}_headers INTERFACE hardware_structs hardware_claim)
        endif()
    endif()
endmacro()

macro(pico_simple_hardware_headers_only_target NAME)
    if (NOT TARGET hardware_${NAME})
        add_library(hardware_${NAME} INTERFACE)

        target_include_directories(hardware_${NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)
        target_link_libraries(hardware_${NAME} INTERFACE pico_base_headers)
        if (NOT PICO_NO_HARDWARE)
            target_link_libraries(hardware_${NAME} INTERFACE hardware_structs)
        endif()
    endif()
endmacro()

macro(pico_simple_hardware_impl_target NAME)
    if (NOT TARGET hardware_${NAME})
        add_library(hardware_${NAME} INTERFACE)

        target_sources(hardware_${NAME} INTERFACE
                ${CMAKE_CURRENT_LIST_DIR}/${NAME}.c
                )

        target_link_libraries(hardware_${NAME} INTERFACE hardware_${NAME}_headers pico_platform)
    endif()
endmacro()

function(pico_add_doxygen SOURCE_DIR)
    set(PICO_DOXYGEN_PATHS "${PICO_DOXYGEN_PATHS} ${SOURCE_DIR}" CACHE INTERNAL "")
endfunction()

function(pico_add_doxygen_exclude SOURCE_DIR)
    set(PICO_DOXYGEN_EXCLUDE_PATHS "${PICO_DOXYGEN_EXCLUDE_PATHS} ${SOURCE_DIR}" CACHE INTERNAL "")
endfunction()

include(${PICO_PLATFORM_CMAKE_FILE})