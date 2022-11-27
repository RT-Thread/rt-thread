include_guard()
message("utility_debug_console_lite component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_debug_console.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(component_usart_adapter_LPC55S69_cm33_core1)

include(driver_common_LPC55S69_cm33_core1)

