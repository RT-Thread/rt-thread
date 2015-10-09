INCLUDE(CMakeForceCompiler)

# CROSS COMPILER SETTING
SET(CMAKE_SYSTEM_NAME Generic)
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

# THE VERSION NUMBER
SET (Tutorial_VERSION_MAJOR 1)
SET (Tutorial_VERSION_MINOR 0)

# ENABLE ASM
ENABLE_LANGUAGE(ASM)

SET(CMAKE_STATIC_LIBRARY_PREFIX)
SET(CMAKE_STATIC_LIBRARY_SUFFIX)

SET(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
SET(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

 
# CURRENT DIRECTORY
SET(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})


SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -g")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mcpu=cortex-m0plus")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mthumb")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -Wall")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-common")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -mapcs")

SET(CMAKE_ASM_FLAGS_DEBUG "${CMAKE_ASM_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mcpu=cortex-m0plus")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mthumb")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -Wall")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-common")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -mapcs")

SET(CMAKE_ASM_FLAGS_RELEASE "${CMAKE_ASM_FLAGS_RELEASE} -std=gnu99")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DDEBUG")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCPU_MKW40Z160VHT4")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DFRDM_KW40Z")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DFREEDOM")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mcpu=cortex-m0plus")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mthumb")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MMD")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -MP")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-common")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffunction-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fdata-sections")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -ffreestanding")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-builtin")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -mapcs")

SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -std=gnu99")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DCPU_MKW40Z160VHT4")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DFRDM_KW40Z")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DFREEDOM")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Os")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mcpu=cortex-m0plus")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mthumb")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MMD")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -MP")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-common")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffunction-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fdata-sections")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -ffreestanding")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -fno-builtin")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -mapcs")

SET(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -std=gnu99")

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/osa/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/CMSIS/Include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKW40Z4/include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKW40Z4/startup)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/utilities/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/system/inc)

include_directories(${ProjDirPath}/../../../../components/drivers/include/drivers)

include_directories(${ProjDirPath}/../../../../components/drivers/include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/driver_wrapper/inc)

include_directories(${ProjDirPath}/../../../../components/finsh)

include_directories(${ProjDirPath}/../../../../include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/osa/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/CMSIS/Include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKW40Z4/include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/devices/MKW40Z4/startup)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/utilities/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc)

include_directories(${ProjDirPath}/../../../../bsp/freescale/platform/system/inc)

include_directories(${ProjDirPath}/../../../../components/drivers/include/drivers)

include_directories(${ProjDirPath}/../../../../components/drivers/include)

include_directories(${ProjDirPath}/../../../../bsp/freescale/driver_wrapper/inc)

include_directories(${ProjDirPath}/../../../../components/finsh)

include_directories(${ProjDirPath}/../../../../include)

add_library(libksdk_platform.a STATIC
"${ProjDirPath}/../../../../bsp/freescale/platform/osa/inc/fsl_os_abstraction.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/osa/inc/fsl_os_abstraction_bm.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/osa/src/fsl_os_abstraction_bm.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/clock/fsl_clock_manager.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/inc/fsl_clock_manager.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/clock/fsl_clock_manager_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/clock/MKW40Z4/fsl_clock_MKW40Z4.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/clock/MKW40Z4/fsl_clock_MKW40Z4.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/interrupt/fsl_interrupt_manager.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/inc/fsl_interrupt_manager.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/hwtimer/fsl_hwtimer.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/inc/fsl_hwtimer.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/hwtimer/fsl_hwtimer_pit.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/inc/fsl_hwtimer_pit.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/hwtimer/fsl_hwtimer_systick.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/inc/fsl_hwtimer_systick.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/power/fsl_power_manager.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/inc/fsl_power_manager.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/system/src/power/fsl_power_manager_common.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/adc16/fsl_adc16_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_adc16_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_adc16_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/adc16/fsl_adc16_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/adc16/fsl_adc16_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/cmp/fsl_cmp_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_cmp_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/cmp/fsl_cmp_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_cmp_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/cmp/fsl_cmp_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/cmt/fsl_cmt_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_cmt_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/cmt/fsl_cmt_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_cmt_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/cmt/fsl_cmt_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/cop/fsl_cop_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_cop_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/cop/fsl_cop_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_cop_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/cop/fsl_cop_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/dac/fsl_dac_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_dac_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dac/fsl_dac_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_dac_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dac/fsl_dac_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/dma/fsl_dma_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_dma_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dma/fsl_dma_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_dma_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_dma_request.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dma/fsl_dma_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/dmamux/fsl_dmamux_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_dmamux_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/dspi/fsl_dspi_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_dspi_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dspi/fsl_dspi_shared_function.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_dspi_shared_function.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dspi/fsl_dspi_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_dspi_master_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dspi/fsl_dspi_master_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_dspi_slave_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dspi/fsl_dspi_slave_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_dspi_dma_slave_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dspi/fsl_dspi_dma_slave_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_dspi_dma_master_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/dspi/fsl_dspi_dma_master_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/gpio/fsl_gpio_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_gpio_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/gpio/fsl_gpio_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/gpio/fsl_gpio_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_gpio_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/i2c/fsl_i2c_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_i2c_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/i2c/fsl_i2c_shared_function.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_i2c_shared_function.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/i2c/fsl_i2c_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/i2c/fsl_i2c_master_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_i2c_master_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/i2c/fsl_i2c_slave_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_i2c_slave_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/llwu/fsl_llwu_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_llwu_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/lptmr/fsl_lptmr_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_lptmr_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_lptmr_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/lptmr/fsl_lptmr_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/lptmr/fsl_lptmr_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/ltc/fsl_ltc_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_ltc_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_ltc_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_ltc_driver_aes.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_ltc_driver_hash.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_ltc_driver_prv.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/ltc/fsl_ltc_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/ltc/fsl_ltc_driver_aes.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/ltc/fsl_ltc_driver_aes_ccm.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/ltc/fsl_ltc_driver_hash.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/ltc/fsl_ltc_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/trng/fsl_trng_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_trng_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/trng/fsl_trng_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/trng/fsl_trng_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_trng_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/lpuart/fsl_lpuart_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_lpuart_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_lpuart_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/lpuart/fsl_lpuart_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/lpuart/fsl_lpuart_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/lpuart/fsl_lpuart_dma_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_lpuart_dma_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/mcg/fsl_mcg_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_mcg_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/mcg/fsl_mcg_hal_modes.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_mcg_hal_modes.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/pit/fsl_pit_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_pit_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/pit/fsl_pit_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_pit_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/pit/fsl_pit_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/port/fsl_port_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_port_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/rtc/fsl_rtc_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_rtc_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/rtc/fsl_rtc_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_rtc_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/rtc/fsl_rtc_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_sim_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/sim/MKW40Z4/fsl_sim_hal_MKW40Z4.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/sim/MKW40Z4/fsl_sim_hal_MKW40Z4.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/smc/fsl_smc_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_smc_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_pmc_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/rcm/fsl_rcm_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_rcm_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_tpm_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/tpm/fsl_tpm_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/tpm/fsl_tpm_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/tpm/fsl_tpm_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_tpm_driver.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/tsi/fsl_tsi_hal.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/src/tsi/fsl_tsi_v4_hal_specific.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_tsi_hal.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/hal/inc/fsl_tsi_v4_hal_specific.h"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/tsi/fsl_tsi_common.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/tsi/fsl_tsi_driver.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/src/tsi/fsl_tsi_v4_driver_specific.c"
"${ProjDirPath}/../../../../bsp/freescale/platform/drivers/inc/fsl_tsi_driver.h"
)


