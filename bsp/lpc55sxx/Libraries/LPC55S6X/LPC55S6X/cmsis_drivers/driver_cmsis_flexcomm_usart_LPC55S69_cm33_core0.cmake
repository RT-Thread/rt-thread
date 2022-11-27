include_guard()
message("driver_cmsis_flexcomm_usart component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_usart_cmsis.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexcomm_usart_dma_LPC55S69_cm33_core0)

include(CMSIS_Driver_Include_USART_LPC55S69_cm33_core0)

