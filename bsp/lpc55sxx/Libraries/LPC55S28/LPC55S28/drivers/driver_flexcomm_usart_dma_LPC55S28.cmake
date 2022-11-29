include_guard()
message("driver_flexcomm_usart_dma component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_usart_dma.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexcomm_LPC55S28)

include(driver_flexcomm_usart_LPC55S28)

include(driver_lpc_dma_LPC55S28)

