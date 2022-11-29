include_guard()
message("driver_lpc_iocon component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

include(driver_common_LPC55S28)

