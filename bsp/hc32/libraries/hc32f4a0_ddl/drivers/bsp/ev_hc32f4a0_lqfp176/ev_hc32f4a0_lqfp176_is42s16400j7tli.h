/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_is42s16400j7tli.h
 * @brief This file contains all the functions prototypes for is42s16400j7tli of
 *        the board EV_HC32F4A0_LQFP176.
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
#ifndef __EV_HC32F4A0_LQFP176_IS42S16400J7TLI_H__
#define __EV_HC32F4A0_LQFP176_IS42S16400J7TLI_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_gpio.h"
#include "hc32_ll_dmc.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176_IS42S16400J7TLI
 * @{
 */

#if ((BSP_IS42S16400J7TLI_ENABLE == DDL_ON) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_IS42S16400J7TLI_Global_Macros EV_HC32F4A0_LQFP176 IS42S16400J7TLI Global Macros
 * @{
 */

/**
 * @defgroup IS42S16400J7TLI_Map_DMC_Chip IS42S16400J7TLI Map DMC Chip
 * @{
 */
#define BSP_IS42S16400J7TLI_CHIP            (EXMC_DMC_CHIP1)
#define BSP_IS42S16400J7TLI_BANK            (EXMC_DMC_BANK0)
/**
 * @}
 */

/**
 * @defgroup IS42S16400J7TLI_Map_Address_Space IS42S16400J7TLI Map Address Space
 * @{
 */
#define BSP_IS42S16400J7TLI_ADDR_MATCH      (0x80UL)
#define BSP_IS42S16400J7TLI_ADDR_MASK       (EXMC_DMC_ADDR_MASK_16MB)
/**
 * @}
 */

/**
 * @defgroup IS42S16400J7TLI_Memory_Size IS42S16400J7TLI Memory Size
 * @{
 */
#define BSP_IS42S16400J7TLI_SIZE            (8UL * 1024UL * 1024UL)     /* 8MBytes*/
/**
 * @}
 */

/**
 * @defgroup SDRAM_Address_Space SDRAM Address Space
 * @note SDRAM address:[0x80000000, 0x807FFFFF] and SDRAM size: 8M bytes
 * @{
 */
#define BSP_IS42S16400J7TLI_START_ADDR      (EXMC_DMC_GetChipStartAddr(BSP_IS42S16400J7TLI_CHIP))
#define BSP_IS42S16400J7TLI_END_ADDR        (BSP_IS42S16400J7TLI_START_ADDR + BSP_IS42S16400J7TLI_SIZE - 1UL)
/**
 * @}
 */

/**
 * @defgroup DMC_Interface_Pin DMC Interface Pin
 * @{
 */
#define BSP_IS42S16400J7TLI_CKE_PORT        (GPIO_PORT_C)   /* PC03 - EXMC_ALE */
#define BSP_IS42S16400J7TLI_CKE_PIN         (GPIO_PIN_03)

#define BSP_IS42S16400J7TLI_CLK_PORT        (GPIO_PORT_G)   /* PD03 - EXMC_CLK */
#define BSP_IS42S16400J7TLI_CLK_PIN         (GPIO_PIN_08)

#define BSP_IS42S16400J7TLI_DQM0_PORT       (GPIO_PORT_E)   /* PE00 - EXMC_CE4 */
#define BSP_IS42S16400J7TLI_DQM0_PIN        (GPIO_PIN_00)
#define BSP_IS42S16400J7TLI_DQM1_PORT       (GPIO_PORT_E)   /* PE01 - EXMC_CE5 */
#define BSP_IS42S16400J7TLI_DQM1_PIN        (GPIO_PIN_01)

#define BSP_IS42S16400J7TLI_BA0_PORT        (GPIO_PORT_D)   /* PD11 - EXMC_ADD16 */
#define BSP_IS42S16400J7TLI_BA0_PIN         (GPIO_PIN_11)
#define BSP_IS42S16400J7TLI_BA1_PORT        (GPIO_PORT_D)   /* PD12 - EXMC_ADD17 */
#define BSP_IS42S16400J7TLI_BA1_PIN         (GPIO_PIN_12)

#define BSP_IS42S16400J7TLI_CS1_PORT        (GPIO_PORT_G)   /* PG09 - EXMC_CE1 */
#define BSP_IS42S16400J7TLI_CS1_PIN         (GPIO_PIN_09)

#define BSP_IS42S16400J7TLI_RAS_PORT        (GPIO_PORT_F)   /* PF11 - EXMC_OE */
#define BSP_IS42S16400J7TLI_RAS_PIN         (GPIO_PIN_11)

#define BSP_IS42S16400J7TLI_CAS_PORT        (GPIO_PORT_G)   /* PG15 - EXMC_BAA */
#define BSP_IS42S16400J7TLI_CAS_PIN         (GPIO_PIN_15)

#define BSP_IS42S16400J7TLI_WE_PORT         (GPIO_PORT_C)   /* PC00 - EXMC_WE */
#define BSP_IS42S16400J7TLI_WE_PIN          (GPIO_PIN_00)

#define BSP_IS42S16400J7TLI_ADD0_PORT       (GPIO_PORT_F)   /* PF00 - EXMC_ADD0 */
#define BSP_IS42S16400J7TLI_ADD0_PIN        (GPIO_PIN_00)
#define BSP_IS42S16400J7TLI_ADD1_PORT       (GPIO_PORT_F)   /* PF01 - EXMC_ADD1 */
#define BSP_IS42S16400J7TLI_ADD1_PIN        (GPIO_PIN_01)
#define BSP_IS42S16400J7TLI_ADD2_PORT       (GPIO_PORT_F)   /* PF02 - EXMC_ADD2 */
#define BSP_IS42S16400J7TLI_ADD2_PIN        (GPIO_PIN_02)
#define BSP_IS42S16400J7TLI_ADD3_PORT       (GPIO_PORT_F)   /* PF03 - EXMC_ADD3 */
#define BSP_IS42S16400J7TLI_ADD3_PIN        (GPIO_PIN_03)
#define BSP_IS42S16400J7TLI_ADD4_PORT       (GPIO_PORT_F)   /* PF04 - EXMC_ADD4 */
#define BSP_IS42S16400J7TLI_ADD4_PIN        (GPIO_PIN_04)
#define BSP_IS42S16400J7TLI_ADD5_PORT       (GPIO_PORT_F)   /* PF05 - EXMC_ADD5 */
#define BSP_IS42S16400J7TLI_ADD5_PIN        (GPIO_PIN_05)
#define BSP_IS42S16400J7TLI_ADD6_PORT       (GPIO_PORT_F)   /* PF12 - EXMC_ADD6 */
#define BSP_IS42S16400J7TLI_ADD6_PIN        (GPIO_PIN_12)
#define BSP_IS42S16400J7TLI_ADD7_PORT       (GPIO_PORT_F)   /* PF13 - EXMC_ADD7 */
#define BSP_IS42S16400J7TLI_ADD7_PIN        (GPIO_PIN_13)
#define BSP_IS42S16400J7TLI_ADD8_PORT       (GPIO_PORT_F)   /* PF14 - EXMC_ADD8 */
#define BSP_IS42S16400J7TLI_ADD8_PIN        (GPIO_PIN_14)
#define BSP_IS42S16400J7TLI_ADD9_PORT       (GPIO_PORT_F)   /* PF15 - EXMC_ADD9 */
#define BSP_IS42S16400J7TLI_ADD9_PIN        (GPIO_PIN_15)
#define BSP_IS42S16400J7TLI_ADD10_PORT      (GPIO_PORT_G)   /* PG00 - EXMC_ADD10 */
#define BSP_IS42S16400J7TLI_ADD10_PIN       (GPIO_PIN_00)
#define BSP_IS42S16400J7TLI_ADD11_PORT      (GPIO_PORT_G)   /* PG01 - EXMC_ADD11 */
#define BSP_IS42S16400J7TLI_ADD11_PIN       (GPIO_PIN_01)

#define BSP_IS42S16400J7TLI_DATA0_PORT      (GPIO_PORT_D)   /* PD14 - EXMC_DATA0 */
#define BSP_IS42S16400J7TLI_DATA0_PIN       (GPIO_PIN_14)
#define BSP_IS42S16400J7TLI_DATA1_PORT      (GPIO_PORT_D)   /* PD15 - EXMC_DATA1 */
#define BSP_IS42S16400J7TLI_DATA1_PIN       (GPIO_PIN_15)
#define BSP_IS42S16400J7TLI_DATA2_PORT      (GPIO_PORT_D)   /* PD00 - EXMC_DATA2 */
#define BSP_IS42S16400J7TLI_DATA2_PIN       (GPIO_PIN_00)
#define BSP_IS42S16400J7TLI_DATA3_PORT      (GPIO_PORT_D)   /* PD01 - EXMC_DATA3 */
#define BSP_IS42S16400J7TLI_DATA3_PIN       (GPIO_PIN_01)
#define BSP_IS42S16400J7TLI_DATA4_PORT      (GPIO_PORT_E)   /* PE07 - EXMC_DATA4 */
#define BSP_IS42S16400J7TLI_DATA4_PIN       (GPIO_PIN_07)
#define BSP_IS42S16400J7TLI_DATA5_PORT      (GPIO_PORT_E)   /* PE08 - EXMC_DATA5 */
#define BSP_IS42S16400J7TLI_DATA5_PIN       (GPIO_PIN_08)
#define BSP_IS42S16400J7TLI_DATA6_PORT      (GPIO_PORT_E)   /* PE09 - EXMC_DATA6 */
#define BSP_IS42S16400J7TLI_DATA6_PIN       (GPIO_PIN_09)
#define BSP_IS42S16400J7TLI_DATA7_PORT      (GPIO_PORT_E)   /* PE10 - EXMC_DATA7 */
#define BSP_IS42S16400J7TLI_DATA7_PIN       (GPIO_PIN_10)
#define BSP_IS42S16400J7TLI_DATA8_PORT      (GPIO_PORT_E)   /* PE11 - EXMC_DATA8 */
#define BSP_IS42S16400J7TLI_DATA8_PIN       (GPIO_PIN_11)
#define BSP_IS42S16400J7TLI_DATA9_PORT      (GPIO_PORT_E)   /* PE12 - EXMC_DATA9 */
#define BSP_IS42S16400J7TLI_DATA9_PIN       (GPIO_PIN_12)
#define BSP_IS42S16400J7TLI_DATA10_PORT     (GPIO_PORT_E)   /* PE13 - EXMC_DATA10 */
#define BSP_IS42S16400J7TLI_DATA10_PIN      (GPIO_PIN_13)
#define BSP_IS42S16400J7TLI_DATA11_PORT     (GPIO_PORT_E)   /* PE14 - EXMC_DATA11 */
#define BSP_IS42S16400J7TLI_DATA11_PIN      (GPIO_PIN_14)
#define BSP_IS42S16400J7TLI_DATA12_PORT     (GPIO_PORT_E)   /* PE15 - EXMC_DATA12 */
#define BSP_IS42S16400J7TLI_DATA12_PIN      (GPIO_PIN_15)
#define BSP_IS42S16400J7TLI_DATA13_PORT     (GPIO_PORT_D)   /* PD08 - EXMC_DATA13 */
#define BSP_IS42S16400J7TLI_DATA13_PIN      (GPIO_PIN_08)
#define BSP_IS42S16400J7TLI_DATA14_PORT     (GPIO_PORT_D)   /* PD09 - EXMC_DATA14 */
#define BSP_IS42S16400J7TLI_DATA14_PIN      (GPIO_PIN_09)
#define BSP_IS42S16400J7TLI_DATA15_PORT     (GPIO_PORT_D)   /* PD10 - EXMC_DATA15 */
#define BSP_IS42S16400J7TLI_DATA15_PIN      (GPIO_PIN_10)
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
* @addtogroup EV_HC32F4A0_LQFP176_IS42S16400J7TLI_Global_Functions
* @{
*/
int32_t BSP_IS42S16400J7TLI_Init(void);
void BSP_IS42S16400J7TLI_GetMemInfo(uint32_t *pu32MemoryStartAddr, uint32_t *pu32MemoryByteSize);
/**
 * @}
 */

#endif /* BSP_IS42S16400J7TLI_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

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

#endif /* __EV_HC32F4A0_LQFP176_IS42S16400J7TLI_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
