#CPU_ARCH := RISCV
#MCPU := e907
#E906 rv32imacxthead ilp32 e907
#E906F rv32imacfxthead ilp32f e907
#E906FD rv32imacfdxthead ilp32d e907

SET(CPU_ARCH "RISCV")
SET(MCPU "e907")

SET(MARCH "rv32imafcpzpsfoperand_xtheade")
SET(MABI "ilp32f")

list(APPEND GLOBAL_C_FLAGS -march=${MARCH} -mabi=${MABI} -mtune=${MCPU})
list(APPEND GLOBAL_LD_FLAGS -march=${MARCH} -mabi=${MABI} -mtune=${MCPU})

SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/m0/bl808_flash.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/m0/bl808_rom.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/m0/bl808_flash.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/m0/bl808_ram_dv.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/m0/bl808_flash_dv.ld)