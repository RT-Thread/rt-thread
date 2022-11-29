include_guard()
message("driver_inputmux_connections component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

include(driver_common_LPC55S28)

