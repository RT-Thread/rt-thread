/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_is62wv51216.h
 * @brief This file contains all the functions prototypes for is62wv51216 of the
 *        board EV_HC32F4A0_LQFP176.
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
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
#ifndef __EV_HC32F4A0_LQFP176_IS62WV51216_H__
#define __EV_HC32F4A0_LQFP176_IS62WV51216_H__

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
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176_IS62WV51216
 * @{
 */
#if ((BSP_IS62WV51216_ENABLE == DDL_ON) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_IS62WV51216_Global_Macros  EV_HC32F4A0_LQFP176 IS62WV51216 Global Macros
 * @{
 */

/**
 * @defgroup IS62WV51216_Map_SMC_Chip IS62WV51216 Map SMC Chip
 * @{
 */
#define BSP_IS62WV51216_CHIP            (EXMC_SMC_CHIP2)
/**
 * @}
 */

/**
 * @defgroup IS62WV51216_SMC_Address_Space IS62WV51216 SMC Address Space
 * @{
 */
#define BSP_IS62WV51216_MATCH_ADDR      (0x70UL)
#define BSP_IS62WV51216_MASK_ADDR       (EXMC_SMC_ADDR_MASK_16MB)
/**
 * @}
 */

/**
 * @defgroup IS62WV51216_Memory_Size IS62WV51216 Memory Size
 * @{
 */
#define BSP_IS62WV51216_SIZE            (1UL * 1024UL * 1024UL)     /* 1MBytes*/
/**
 * @}
 */

/**
 * @defgroup IS62WV51216_SRAM_Address_Space IS62WV51216 SRAM Address Space
 * @note SRAM address:[0x60000000, 0x600FFFFF] & SRAM size: 1M bytes
 * @{
 */
#define BSP_IS62WV51216_START_ADDR      (EXMC_SMC_GetChipStartAddr(BSP_IS62WV51216_CHIP))
#define BSP_IS62WV51216_END_ADDR        (BSP_IS62WV51216_START_ADDR + BSP_IS62WV51216_SIZE - 1UL)
/**
 * @}
 */

/**
 * @defgroup SMC_Interface_Pin EXMC_SMC Interface Pin
 * @{
 */
#define BSP_IS62WV51216_CS_PORT         (GPIO_PORT_G)   /* PG10 - EXMC_CE2 */
#define BSP_IS62WV51216_CS_PIN          (GPIO_PIN_10)

#define BSP_IS62WV51216_WE_PORT         (GPIO_PORT_C)   /* PC00 - EXMC_WE */
#define BSP_IS62WV51216_WE_PIN          (GPIO_PIN_00)

#define BSP_IS62WV51216_BLS0_PORT       (GPIO_PORT_E)   /* PE00 - EXMC_CE4 */
#define BSP_IS62WV51216_BLS0_PIN        (GPIO_PIN_00)
#define BSP_IS62WV51216_BLS1_PORT       (GPIO_PORT_E)   /* PE01 - EXMC_CE5 */
#define BSP_IS62WV51216_BLS1_PIN        (GPIO_PIN_01)

#define BSP_IS62WV51216_OE_PORT         (GPIO_PORT_F)   /* PF11 - EXMC_OE */
#define BSP_IS62WV51216_OE_PIN          (GPIO_PIN_11)

#define BSP_IS62WV51216_ADD0_PORT       (GPIO_PORT_F)   /* PF00 - EXMC_ADD0 */
#define BSP_IS62WV51216_ADD0_PIN        (GPIO_PIN_00)
#define BSP_IS62WV51216_ADD1_PORT       (GPIO_PORT_F)   /* PF01 - EXMC_ADD1 */
#define BSP_IS62WV51216_ADD1_PIN        (GPIO_PIN_01)
#define BSP_IS62WV51216_ADD2_PORT       (GPIO_PORT_F)   /* PF02 - EXMC_ADD2 */
#define BSP_IS62WV51216_ADD2_PIN        (GPIO_PIN_02)
#define BSP_IS62WV51216_ADD3_PORT       (GPIO_PORT_F)   /* PF03 - EXMC_ADD3 */
#define BSP_IS62WV51216_ADD3_PIN        (GPIO_PIN_03)
#define BSP_IS62WV51216_ADD4_PORT       (GPIO_PORT_F)   /* PF04 - EXMC_ADD4 */
#define BSP_IS62WV51216_ADD4_PIN        (GPIO_PIN_04)
#define BSP_IS62WV51216_ADD5_PORT       (GPIO_PORT_F)   /* PF05 - EXMC_ADD5 */
#define BSP_IS62WV51216_ADD5_PIN        (GPIO_PIN_05)
#define BSP_IS62WV51216_ADD6_PORT       (GPIO_PORT_F)   /* PF12 - EXMC_ADD6 */
#define BSP_IS62WV51216_ADD6_PIN        (GPIO_PIN_12)
#define BSP_IS62WV51216_ADD7_PORT       (GPIO_PORT_F)   /* PF13 - EXMC_ADD7 */
#define BSP_IS62WV51216_ADD7_PIN        (GPIO_PIN_13)
#define BSP_IS62WV51216_ADD8_PORT       (GPIO_PORT_F)   /* PF14 - EXMC_ADD8 */
#define BSP_IS62WV51216_ADD8_PIN        (GPIO_PIN_14)
#define BSP_IS62WV51216_ADD9_PORT       (GPIO_PORT_F)   /* PF15 - EXMC_ADD9 */
#define BSP_IS62WV51216_ADD9_PIN        (GPIO_PIN_15)
#define BSP_IS62WV51216_ADD10_PORT      (GPIO_PORT_G)   /* PG00 - EXMC_ADD10 */
#define BSP_IS62WV51216_ADD10_PIN       (GPIO_PIN_00)
#define BSP_IS62WV51216_ADD11_PORT      (GPIO_PORT_G)   /* PG01 - EXMC_ADD11 */
#define BSP_IS62WV51216_ADD11_PIN       (GPIO_PIN_01)
#define BSP_IS62WV51216_ADD12_PORT      (GPIO_PORT_G)   /* PG02 - EXMC_ADD12 */
#define BSP_IS62WV51216_ADD12_PIN       (GPIO_PIN_02)
#define BSP_IS62WV51216_ADD13_PORT      (GPIO_PORT_G)   /* PG03 - EXMC_ADD13 */
#define BSP_IS62WV51216_ADD13_PIN       (GPIO_PIN_03)
#define BSP_IS62WV51216_ADD14_PORT      (GPIO_PORT_G)   /* PG04 - EXMC_ADD14 */
#define BSP_IS62WV51216_ADD14_PIN       (GPIO_PIN_04)
#define BSP_IS62WV51216_ADD15_PORT      (GPIO_PORT_G)   /* PG05 - EXMC_ADD15 */
#define BSP_IS62WV51216_ADD15_PIN       (GPIO_PIN_05)
#define BSP_IS62WV51216_ADD16_PORT      (GPIO_PORT_D)   /* PD11 - EXMC_ADD16 */
#define BSP_IS62WV51216_ADD16_PIN       (GPIO_PIN_11)
#define BSP_IS62WV51216_ADD17_PORT      (GPIO_PORT_D)   /* PD12 - EXMC_ADD17 */
#define BSP_IS62WV51216_ADD17_PIN       (GPIO_PIN_12)
#define BSP_IS62WV51216_ADD18_PORT      (GPIO_PORT_D)   /* PD13 - EXMC_ADD18 */
#define BSP_IS62WV51216_ADD18_PIN       (GPIO_PIN_13)

#define BSP_IS62WV51216_DATA0_PORT      (GPIO_PORT_D)   /* PD14 - EXMC_DATA0 */
#define BSP_IS62WV51216_DATA0_PIN       (GPIO_PIN_14)
#define BSP_IS62WV51216_DATA1_PORT      (GPIO_PORT_D)   /* PD15 - EXMC_DATA1 */
#define BSP_IS62WV51216_DATA1_PIN       (GPIO_PIN_15)
#define BSP_IS62WV51216_DATA2_PORT      (GPIO_PORT_D)   /* PD00 - EXMC_DATA2 */
#define BSP_IS62WV51216_DATA2_PIN       (GPIO_PIN_00)
#define BSP_IS62WV51216_DATA3_PORT      (GPIO_PORT_D)   /* PD01 - EXMC_DATA3 */
#define BSP_IS62WV51216_DATA3_PIN       (GPIO_PIN_01)
#define BSP_IS62WV51216_DATA4_PORT      (GPIO_PORT_E)   /* PE07 - EXMC_DATA4 */
#define BSP_IS62WV51216_DATA4_PIN       (GPIO_PIN_07)
#define BSP_IS62WV51216_DATA5_PORT      (GPIO_PORT_E)   /* PE08 - EXMC_DATA5 */
#define BSP_IS62WV51216_DATA5_PIN       (GPIO_PIN_08)
#define BSP_IS62WV51216_DATA6_PORT      (GPIO_PORT_E)   /* PE09 - EXMC_DATA6 */
#define BSP_IS62WV51216_DATA6_PIN       (GPIO_PIN_09)
#define BSP_IS62WV51216_DATA7_PORT      (GPIO_PORT_E)   /* PE10 - EXMC_DATA7 */
#define BSP_IS62WV51216_DATA7_PIN       (GPIO_PIN_10)
#define BSP_IS62WV51216_DATA8_PORT      (GPIO_PORT_E)   /* PE11 - EXMC_DATA8 */
#define BSP_IS62WV51216_DATA8_PIN       (GPIO_PIN_11)
#define BSP_IS62WV51216_DATA9_PORT      (GPIO_PORT_E)   /* PE12 - EXMC_DATA9 */
#define BSP_IS62WV51216_DATA9_PIN       (GPIO_PIN_12)
#define BSP_IS62WV51216_DATA10_PORT     (GPIO_PORT_E)   /* PE13 - EXMC_DATA10 */
#define BSP_IS62WV51216_DATA10_PIN      (GPIO_PIN_13)
#define BSP_IS62WV51216_DATA11_PORT     (GPIO_PORT_E)   /* PE14 - EXMC_DATA11 */
#define BSP_IS62WV51216_DATA11_PIN      (GPIO_PIN_14)
#define BSP_IS62WV51216_DATA12_PORT     (GPIO_PORT_E)   /* PE15 - EXMC_DATA12 */
#define BSP_IS62WV51216_DATA12_PIN      (GPIO_PIN_15)
#define BSP_IS62WV51216_DATA13_PORT     (GPIO_PORT_D)   /* PD08 - EXMC_DATA13 */
#define BSP_IS62WV51216_DATA13_PIN      (GPIO_PIN_08)
#define BSP_IS62WV51216_DATA14_PORT     (GPIO_PORT_D)   /* PD09 - EXMC_DATA14 */
#define BSP_IS62WV51216_DATA14_PIN      (GPIO_PIN_09)
#define BSP_IS62WV51216_DATA15_PORT     (GPIO_PORT_D)   /* PD10 - EXMC_DATA15 */
#define BSP_IS62WV51216_DATA15_PIN      (GPIO_PIN_10)
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
 * @addtogroup EV_HC32F4A0_LQFP176_IS62WV51216_Global_Functions
 * @{
 */
int32_t BSP_IS62WV51216_Init(void);
void BSP_IS62WV51216_GetMemInfo(uint32_t *pu32MemoryStartAddr, uint32_t *pu32MemoryByteSize);
/**
 * @}
 */

#endif /* BSP_IS62WV51216_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

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

#endif /* __EV_HC32F4A0_LQFP176_IS62WV51216_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
