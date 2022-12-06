include_guard()
message("driver_cmsis_enet component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fsl_enet_cmsis.c
    ${CMAKE_CURRENT_LIST_DIR}/fsl_enet_phy_cmsis.c
)


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)


include(driver_enet_MIMXRT1062)

include(CMSIS_Driver_Include_Ethernet_MAC_MIMXRT1062)

include(CMSIS_Driver_Include_Ethernet_PHY_MIMXRT1062)

include(CMSIS_Driver_Include_Ethernet_MIMXRT1062)

include(driver_phy-common_MIMXRT1062)

