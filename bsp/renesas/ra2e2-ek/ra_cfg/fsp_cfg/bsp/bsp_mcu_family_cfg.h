/* generated configuration header file - do not edit */
#ifndef BSP_MCU_FAMILY_CFG_H_
#define BSP_MCU_FAMILY_CFG_H_
#ifdef __cplusplus
            extern "C" {
            #endif

            #include "bsp_mcu_device_pn_cfg.h"
            #include "bsp_mcu_device_cfg.h"
            #include "../../../ra/fsp/src/bsp/mcu/ra2e2/bsp_mcu_info.h"
            #include "bsp_clock_cfg.h"
            #define BSP_MCU_GROUP_RA2E2 (1)
            #define BSP_LOCO_HZ                 (32768)
            #define BSP_MOCO_HZ                 (8000000)
            #if   BSP_CFG_HOCO_FREQUENCY == 0
                #define BSP_HOCO_HZ             (24000000)
            #elif BSP_CFG_HOCO_FREQUENCY == 2
                #define BSP_HOCO_HZ             (32000000)
            #elif BSP_CFG_HOCO_FREQUENCY == 4
                #define BSP_HOCO_HZ             (48000000)
            #elif BSP_CFG_HOCO_FREQUENCY == 5
                #define BSP_HOCO_HZ             (64000000)
            #else
                #error "Invalid HOCO frequency chosen (BSP_CFG_HOCO_FREQUENCY) in bsp_clock_cfg.h"
            #endif

            #define BSP_CORTEX_VECTOR_TABLE_ENTRIES    (16U)
            #define BSP_VECTOR_TABLE_MAX_ENTRIES       (48U)
            #define BSP_CFG_INLINE_IRQ_FUNCTIONS       (0)

            /* Used to create IELS values for the interrupt initialization table g_interrupt_event_link_select. */
            #define BSP_PRV_IELS_ENUM(vector)    (ICU_ ## vector)

            #define BSP_CLOCK_CFG_MAIN_OSC_POPULATED (0)
            #define BSP_CLOCK_CFG_SUBCLOCK_POPULATED (0)
            #ifdef __cplusplus
            }
            #endif
#endif /* BSP_MCU_FAMILY_CFG_H_ */
