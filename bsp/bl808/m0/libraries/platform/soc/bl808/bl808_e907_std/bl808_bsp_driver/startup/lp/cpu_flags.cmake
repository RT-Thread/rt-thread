#CPU_ARCH := RISCV
#MCPU := e902
#E902 rv32ecxthead ilp32e e902
#E902M rv32emcxthead ilp32e e902
#E902T rv32ecxthead ilp32e e902
#E902MT rv32emcxthead ilp32e e902
#MARCH := rv32emcxthead
#MARCH := rv32emc
#MABI := ilp32e

SET(CPU_ARCH "RISCV")
SET(MCPU "e902")

SET(MARCH "rv32emcxtheadse")
SET(MABI "ilp32e")

list(APPEND GLOBAL_C_FLAGS -march=${MARCH} -mabi=${MABI} -mtune=${MCPU})
list(APPEND GLOBAL_LD_FLAGS -march=${MARCH} -mabi=${MABI} -mtune=${MCPU})

SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/lp/bl808_flash.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/lp/bl808_ram.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/lp/bl808_ram_dv.ld)