#Description: CMSIS Include For Cortex-A; user_visible: True
include_guard(GLOBAL)
message("CMSIS_Include_core_ca component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../Source/cache_armv8a.c
    ${CMAKE_CURRENT_LIST_DIR}/../Source/mmu_armv8a.c
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/.
)
