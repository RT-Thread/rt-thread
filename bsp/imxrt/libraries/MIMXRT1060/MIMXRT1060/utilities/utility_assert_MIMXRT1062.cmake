include_guard()
message("utility_assert component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_assert.c
)


include(utility_debug_console_MIMXRT1062)

