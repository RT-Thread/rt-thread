/**
 *******************************************************************************
 * @file  ev_hc32f448_lqfp80_is61lv6416.h
 * @brief This file contains all the functions prototypes for is61lv6416 of the
 *        board EV_HC32F448_LQFP80.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2023-05-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022-2023, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */
#ifndef __EV_HC32F448_LQFP80_IS61LV6416_H__
#define __EV_HC32F448_LQFP80_IS61LV6416_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_gpio.h"
#include "hc32_ll_smc.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F448_LQFP80
 * @{
 */

/**
 * @addtogroup EV_HC32F448_LQFP80_IS61LV6416
 * @{
 */
#if ((BSP_IS61LV6416_ENABLE == DDL_ON) && (BSP_EV_HC32F448_LQFP80 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F448_LQFP80_IS61LV6416_Global_Macros  EV_HC32F448_LQFP80 IS61LV6416 Global Macros
 * @{
 */

/**
 * @defgroup IS61LV6416_Map_SMC_Chip IS61LV6416 Map SMC Chip
 * @{
 */
#define BSP_IS61LV6416_CHIP            (EXMC_SMC_CHIP0)
/**
 * @}
 */

/**
 * @defgroup IS61LV6416_SMC_Address_Space IS61LV6416 SMC Address Space
 * @{
 */
#define BSP_IS61LV6416_MATCH_ADDR      (0x60UL)
#define BSP_IS61LV6416_MASK_ADDR       (EXMC_SMC_ADDR_MASK_16MB)
/**
 * @}
 */

/**
 * @defgroup IS61LV6416_Memory_Size IS61LV6416 Memory Size
 * @{
 */
#define BSP_IS61LV6416_SIZE            (1UL * 128UL * 1024UL)     /* 128KBytes */
/**
 * @}
 */

/**
 * @defgroup IS61LV6416_SRAM_Address_Space IS61LV6416 SRAM Address Space
 * @note SRAM address:[0x60000000, 0x600FFFFF] & SRAM size: 1M bytes
 * @{
 */
#define BSP_IS61LV6416_START_ADDR      (EXMC_SMC_GetChipStartAddr(BSP_IS61LV6416_CHIP))
#define BSP_IS61LV6416_END_ADDR        (BSP_IS61LV6416_START_ADDR + BSP_IS61LV6416_SIZE - 1UL)
/**
 * @}
 */

/**
 * @defgroup SMC_Interface_Pin EXMC_SMC Interface Pin
 * @{
 */
#define BSP_IS61LV6416_CS_PORT         (GPIO_PORT_A)   /* PA04 - EXMC_CE0 */
#define BSP_IS61LV6416_CS_PIN          (GPIO_PIN_04)

#define BSP_IS61LV6416_WE_PORT         (GPIO_PORT_B)   /* PB08 - EXMC_WE */
#define BSP_IS61LV6416_WE_PIN          (GPIO_PIN_08)

#define BSP_IS61LV6416_BLS0_PORT       (GPIO_PORT_C)   /* PC02 - EXMC_CE4 */
#define BSP_IS61LV6416_BLS0_PIN        (GPIO_PIN_02)
#define BSP_IS61LV6416_BLS1_PORT       (GPIO_PORT_C)   /* PC03 - EXMC_CE5 */
#define BSP_IS61LV6416_BLS1_PIN        (GPIO_PIN_03)

#define BSP_IS61LV6416_OE_PORT         (GPIO_PORT_B)   /* PB09 - EXMC_OE */
#define BSP_IS61LV6416_OE_PIN          (GPIO_PIN_09)

#define BSP_IS61LV6416_ADV_PORT        (GPIO_PORT_B)   /* PB07 - EXMC_ADV */
#define BSP_IS61LV6416_ADV_PIN         (GPIO_PIN_07)

#define BSP_IS61LV6416_DATA0_PORT      (GPIO_PORT_A)   /* PA06 - EXMC_DATA0 */
#define BSP_IS61LV6416_DATA0_PIN       (GPIO_PIN_06)
#define BSP_IS61LV6416_DATA1_PORT      (GPIO_PORT_A)   /* PA07 - EXMC_DATA1 */
#define BSP_IS61LV6416_DATA1_PIN       (GPIO_PIN_07)
#define BSP_IS61LV6416_DATA2_PORT      (GPIO_PORT_B)   /* PB00 - EXMC_DATA2 */
#define BSP_IS61LV6416_DATA2_PIN       (GPIO_PIN_00)
#define BSP_IS61LV6416_DATA3_PORT      (GPIO_PORT_B)   /* PB01 - EXMC_DATA3 */
#define BSP_IS61LV6416_DATA3_PIN       (GPIO_PIN_01)
#define BSP_IS61LV6416_DATA4_PORT      (GPIO_PORT_B)   /* PB10 - EXMC_DATA4 */
#define BSP_IS61LV6416_DATA4_PIN       (GPIO_PIN_10)
#define BSP_IS61LV6416_DATA5_PORT      (GPIO_PORT_B)   /* PB12 - EXMC_DATA5 */
#define BSP_IS61LV6416_DATA5_PIN       (GPIO_PIN_12)
#define BSP_IS61LV6416_DATA6_PORT      (GPIO_PORT_A)   /* PA12 - EXMC_DATA6 */
#define BSP_IS61LV6416_DATA6_PIN       (GPIO_PIN_12)
#define BSP_IS61LV6416_DATA7_PORT      (GPIO_PORT_A)   /* PA05 - EXMC_DATA7 */
#define BSP_IS61LV6416_DATA7_PIN       (GPIO_PIN_05)
#define BSP_IS61LV6416_DATA8_PORT      (GPIO_PORT_C)   /* PC04 - EXMC_DATA8 */
#define BSP_IS61LV6416_DATA8_PIN       (GPIO_PIN_04)
#define BSP_IS61LV6416_DATA9_PORT      (GPIO_PORT_C)   /* PC05 - EXMC_DATA9 */
#define BSP_IS61LV6416_DATA9_PIN       (GPIO_PIN_05)
#define BSP_IS61LV6416_DATA10_PORT     (GPIO_PORT_E)   /* PE12 - EXMC_DATA10 */
#define BSP_IS61LV6416_DATA10_PIN      (GPIO_PIN_12)
#define BSP_IS61LV6416_DATA11_PORT     (GPIO_PORT_E)   /* PE13 - EXMC_DATA11 */
#define BSP_IS61LV6416_DATA11_PIN      (GPIO_PIN_13)
#define BSP_IS61LV6416_DATA12_PORT     (GPIO_PORT_E)   /* PE14 - EXMC_DATA12 */
#define BSP_IS61LV6416_DATA12_PIN      (GPIO_PIN_14)
#define BSP_IS61LV6416_DATA13_PORT     (GPIO_PORT_E)   /* PE15 - EXMC_DATA13 */
#define BSP_IS61LV6416_DATA13_PIN      (GPIO_PIN_15)
#define BSP_IS61LV6416_DATA14_PORT     (GPIO_PORT_C)   /* PC08 - EXMC_DATA14 */
#define BSP_IS61LV6416_DATA14_PIN      (GPIO_PIN_08)
#define BSP_IS61LV6416_DATA15_PORT     (GPIO_PORT_C)   /* PC09 - EXMC_DATA15 */
#define BSP_IS61LV6416_DATA15_PIN      (GPIO_PIN_09)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/*******************************************************************************
  Global function prototypes (definition in C source)
 ******************************************************************************/
/**
 * @addtogroup EV_HC32F448_LQFP80_IS61LV6416_Global_Functions
 * @{
 */
int32_t BSP_IS61LV6416_Init(void);
void BSP_IS61LV6416_GetMemInfo(uint32_t *pu32MemoryStartAddr, uint32_t *pu32MemoryByteSize);
/**
 * @}
 */

#endif /* BSP_IS61LV6416_ENABLE && BSP_EV_HC32F448_LQFP80 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __EV_HC32F448_LQFP80_IS61LV6416_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
