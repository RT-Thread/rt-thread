if (NOT TARGET pico_base_headers)
    pico_add_library(pico_base NOFLAG)
    target_include_directories(pico_base_headers INTERFACE include ${CMAKE_BINARY_DIR}/generated/pico_base)

    # PICO_BUILD_DEFINE: PICO_BOARD, Name of board, type=string, default=CMake PICO_BOARD variable, group=pico_base
    target_compile_definitions(pico_base_headers INTERFACE
            PICO_BOARD="${PICO_BOARD}")

    target_link_libraries(pico_base_headers INTERFACE pico_platform_headers)

    list(APPEND PICO_SDK_POST_LIST_FILES ${CMAKE_CURRENT_LIST_DIR}/generate_config_header.cmake)
    pico_promote_common_scope_vars()
endif()