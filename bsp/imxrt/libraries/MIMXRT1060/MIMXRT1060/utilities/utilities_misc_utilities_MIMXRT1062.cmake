include_guard()
message("utilities_misc_utilities component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_sbrk.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_memcpy.S
)


