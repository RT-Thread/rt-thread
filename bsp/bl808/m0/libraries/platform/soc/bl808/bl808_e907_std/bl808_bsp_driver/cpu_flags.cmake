include(${CMAKE_SOURCE_DIR}/drivers/${CHIP}_driver/startup/${CPU_ID}/cpu_flags.cmake)

SET(BOOT2_LINKER_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/blsp_boot2_iap_flash.ld)