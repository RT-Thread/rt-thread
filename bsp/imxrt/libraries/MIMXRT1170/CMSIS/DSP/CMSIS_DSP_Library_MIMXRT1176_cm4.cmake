include_guard(GLOBAL)
message("CMSIS_DSP_Library component is included.")


target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Include
)

