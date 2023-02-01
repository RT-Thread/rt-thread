# CPU_ARCH := RISCV
# MCPU := c906
# MARCH := rv64gcvxtheadc
# MABI := lp64d

SET(CPU_ARCH "RISCV")
SET(MCPU "c906")

SET(MARCH "rv64imafdcv0p7_zfh_xtheadc")
SET(MABI "lp64d")

list(APPEND GLOBAL_C_FLAGS -march=${MARCH} -mabi=${MABI} -mtune=${MCPU} -mcmodel=medany)
list(APPEND GLOBAL_LD_FLAGS -march=${MARCH} -mabi=${MABI} -mtune=${MCPU} -mcmodel=medany)

SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/d0/bl808_flash.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/d0/bl808_fpga.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/d0/bl808_ram.ld)
#SET(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/drivers/bl808_driver/startup/d0/bl808_ram_dv.ld)
