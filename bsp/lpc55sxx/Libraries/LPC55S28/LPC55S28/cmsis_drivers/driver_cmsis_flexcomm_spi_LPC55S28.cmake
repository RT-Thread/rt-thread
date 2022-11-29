include_guard()
message("driver_cmsis_flexcomm_spi component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_spi_cmsis.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_flexcomm_spi_dma_LPC55S28)

include(CMSIS_Driver_Include_SPI_LPC55S28)

