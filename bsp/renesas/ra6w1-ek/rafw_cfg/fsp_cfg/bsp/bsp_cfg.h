/* generated configuration header file - do not edit */
#ifndef BSP_CFG_H_
#define BSP_CFG_H_
#ifdef __cplusplus
            extern "C" {
            #endif

#include "bsp_clock_cfg.h"
#include "bsp_mcu_family_cfg.h"
#include "board_cfg.h"
#define FSP_NOT_DEFINED 0
#ifndef BSP_CFG_RTOS
#if (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)
              #define BSP_CFG_RTOS (2)
             #elif (FSP_NOT_DEFINED) != (FSP_NOT_DEFINED)
              #define BSP_CFG_RTOS (1)
             #else
#define BSP_CFG_RTOS (0)
#endif
#endif
#undef FSP_NOT_DEFINED
#ifndef BSP_CFG_RTC_USED
#define BSP_CFG_RTC_USED (FSP_NOT_DEFINED)
#endif
#undef RRQ_NOT_DEFINED
#if defined(_RRQ_BOOT_IMAGE)
             #define BSP_CFG_BOOT_IMAGE (1)
            #else
#define BSP_CFG_BOOT_IMAGE ((0))
#endif
#define BSP_CFG_STACK_MAIN_BYTES (0x400)
#define BSP_CFG_HEAP_BYTES (0)
#define BSP_CFG_NVM_SIZE_BYTES (0x180000)
#define BSP_CFG_PARAM_CHECKING_ENABLE (0)
#define BSP_CFG_ASSERT (0)
#define BSP_CFG_ERROR_LOG (0)
#define BSP_CFG_WAKEUP_RESET_HANDLER_ENABLE (0)

#define BSP_CFG_C_RUNTIME_INIT ((1))
#define BSP_CFG_EARLY_INIT     ((0))

#ifndef BSP_CLOCK_CFG_MAIN_OSC_POPULATED
#define BSP_CLOCK_CFG_MAIN_OSC_POPULATED (1)
#endif
#ifndef BSP_CLOCK_CFG_XTAL32M_STABILIZATION_USEC
#define BSP_CLOCK_CFG_XTAL32M_STABILIZATION_USEC    0
#endif
#ifndef BSP_CLOCK_CFG_SUBCLOCK_POPULATED
#define BSP_CLOCK_CFG_SUBCLOCK_POPULATED (1)
#endif
#ifndef BSP_CLOCK_CFG_SUBCLOCK_STABILIZATION_MS
#define BSP_CLOCK_CFG_SUBCLOCK_STABILIZATION_MS 600
#endif
#ifndef BSP_CFG_CLOCK_CALIBRATION_CYCLES
#define BSP_CFG_CLOCK_CALIBRATION_CYCLES 25
#endif

#ifndef BSP_CFG_IMAGE_HEADER_VERSION
#define BSP_CFG_IMAGE_HEADER_VERSION    0x00000000
#endif
#ifndef BSP_CFG_PRODUCTION_HEADER_CRC
#define BSP_CFG_PRODUCTION_HEADER_CRC   0xFDA8
#endif

#ifndef BSP_CFG_CMN_TIMING_DEBUG
/* TODO add a property for this */
#define BSP_CFG_CMN_TIMING_DEBUG                    (0U)
#endif

#define __PROGRAM_START

#ifdef __cplusplus
            }
            #endif
#endif /* BSP_CFG_H_ */
