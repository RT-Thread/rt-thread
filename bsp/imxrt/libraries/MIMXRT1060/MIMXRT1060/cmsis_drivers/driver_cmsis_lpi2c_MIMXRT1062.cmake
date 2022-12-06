include_guard()
message("driver_cmsis_lpi2c component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_lpi2c_cmsis.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_lpi2c_edma_MIMXRT1062)

include(driver_lpi2c_MIMXRT1062)

include(CMSIS_Driver_Include_I2C_MIMXRT1062)

