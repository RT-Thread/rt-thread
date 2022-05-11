include_guard(GLOBAL)
message("CMSIS_Driver_Include_Ethernet_MAC component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/.
)

include(CMSIS_Driver_Include_Ethernet_MIMXRT1176_cm4)

