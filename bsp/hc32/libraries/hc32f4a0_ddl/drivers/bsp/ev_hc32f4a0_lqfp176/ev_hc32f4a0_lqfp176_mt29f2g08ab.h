/**
 *******************************************************************************
 * @file  ev_hc32f4a0_lqfp176_mt29f2g08ab.h
 * @brief This file contains all the functions prototypes for mt29f2g08ab of the
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
#ifndef __EV_HC32F4A0_LQFP176_MT29F2G08AB_H__
#define __EV_HC32F4A0_LQFP176_MT29F2G08AB_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_gpio.h"
#include "hc32_ll_nfc.h"

/**
 * @addtogroup BSP
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176
 * @{
 */

/**
 * @addtogroup EV_HC32F4A0_LQFP176_MT29F2G08AB
 * @{
 */

#if ((BSP_MT29F2G08AB_ENABLE == DDL_ON) && (BSP_EV_HC32F4A0_LQFP176 == BSP_EV_HC32F4XX))

/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup EV_HC32F4A0_LQFP176_MT29F2G08AB_Global_Macros EV_HC32F4A0_LQFP176 MT29F2G08AB Global Macros
 * @{
 */

/**
 * @defgroup MT29F2G08AB_Map_NFC_Chip MT29F2G08AB Map NFC Chip
 * @{
 */
#define BSP_MT29F2G08AB_BANK            (EXMC_NFC_BANK0)
/**
 * @}
 */

/**
 * @defgroup NFC_Interface_Pin NF Interface Pin
 * @{
 */
#define BSP_MT29F2G08AB_CE_PORT         (GPIO_PORT_C)   /* PC02 - EXMC_CE0 */
#define BSP_MT29F2G08AB_CE_PIN          (GPIO_PIN_02)

#define BSP_MT29F2G08AB_RE_PORT         (GPIO_PORT_F)   /* PF11 - EXMC_OE */
#define BSP_MT29F2G08AB_RE_PIN          (GPIO_PIN_11)

#define BSP_MT29F2G08AB_WE_PORT         (GPIO_PORT_C)   /* PC00 - EXMC_WE */
#define BSP_MT29F2G08AB_WE_PIN          (GPIO_PIN_00)

#define BSP_MT29F2G08AB_CLE_PORT        (GPIO_PORT_I)   /* PI12 - EXMC_CLE */
#define BSP_MT29F2G08AB_CLE_PIN         (GPIO_PIN_12)

#define BSP_MT29F2G08AB_ALE_PORT        (GPIO_PORT_C)   /* PC03 - EXMC_ALE */
#define BSP_MT29F2G08AB_ALE_PIN         (GPIO_PIN_03)

#define BSP_MT29F2G08AB_WP_PORT         (GPIO_PORT_G)   /* PG15 - EXMC_BAA */
#define BSP_MT29F2G08AB_WP_PIN          (GPIO_PIN_15)

#define BSP_MT29F2G08AB_RB_PORT         (GPIO_PORT_G)   /* PG06 - EXMC_RB0 */
#define BSP_MT29F2G08AB_RB_PIN          (GPIO_PIN_06)

#define BSP_MT29F2G08AB_DATA0_PORT      (GPIO_PORT_D)   /* PD14 - EXMC_DATA0 */
#define BSP_MT29F2G08AB_DATA0_PIN       (GPIO_PIN_14)
#define BSP_MT29F2G08AB_DATA1_PORT      (GPIO_PORT_D)   /* PD15 - EXMC_DATA1 */
#define BSP_MT29F2G08AB_DATA1_PIN       (GPIO_PIN_15)
#define BSP_MT29F2G08AB_DATA2_PORT      (GPIO_PORT_D)   /* PD0 - EXMC_DATA2 */
#define BSP_MT29F2G08AB_DATA2_PIN       (GPIO_PIN_00)
#define BSP_MT29F2G08AB_DATA3_PORT      (GPIO_PORT_D)   /* PD1 - EXMC_DATA3 */
#define BSP_MT29F2G08AB_DATA3_PIN       (GPIO_PIN_01)
#define BSP_MT29F2G08AB_DATA4_PORT      (GPIO_PORT_E)   /* PE7 - EXMC_DATA4 */
#define BSP_MT29F2G08AB_DATA4_PIN       (GPIO_PIN_07)
#define BSP_MT29F2G08AB_DATA5_PORT      (GPIO_PORT_E)   /* PE8 - EXMC_DATA5 */
#define BSP_MT29F2G08AB_DATA5_PIN       (GPIO_PIN_08)
#define BSP_MT29F2G08AB_DATA6_PORT      (GPIO_PORT_E)   /* PE9 - EXMC_DATA6 */
#define BSP_MT29F2G08AB_DATA6_PIN       (GPIO_PIN_09)
#define BSP_MT29F2G08AB_DATA7_PORT      (GPIO_PORT_E)   /* PE10 - EXMC_DATA7 */
#define BSP_MT29F2G08AB_DATA7_PIN       (GPIO_PIN_10)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_MT29F2G08AB_Device_Size MT29F2G08AB Device Size
 * @{
 */
#define BSP_MT29F2G08AB_PAGE_SIZE_WITHOUT_SPARE (2048UL)
#define BSP_MT29F2G08AB_SPARE_AREA_SIZE         (64UL)
#define BSP_MT29F2G08AB_PAGE_SIZE_WITH_SPARE    (BSP_MT29F2G08AB_PAGE_SIZE_WITHOUT_SPARE +  BSP_MT29F2G08AB_SPARE_AREA_SIZE)

#define BSP_MT29F2G08AB_PAGES_PER_BLOCK         (64UL)
#define BSP_MT29F2G08AB_BLOCKS_PER_PLANE        (1024UL)
#define BSP_MT29F2G08AB_PLANE_PER_DEVICE        (2UL)
#define BSP_MT29F2G08AB_DEVICE_PAGES            (BSP_MT29F2G08AB_PLANE_PER_DEVICE * BSP_MT29F2G08AB_BLOCKS_PER_PLANE * \
                                                 BSP_MT29F2G08AB_PAGES_PER_BLOCK)

#define BSP_MT29F2G08AB_PAGE_1BIT_ECC_VALUE_SIZE                                   \
(   (BSP_MT29F2G08AB_PAGE_SIZE_WITHOUT_SPARE / EXMC_NFC_ECC_CALCULATE_BLOCK_BYTE) * EXMC_NFC_1BIT_ECC_VALUE_BYTE)
/**
 * @}
 */

/**
 * @defgroup EV_HC32F4A0_LQFP176_MT29F2G08AB_ID_Information MT29F2G08AB ID Information
 * @{
 */
#define BSP_MT29F2G08ABAEA_MANUFACTURER_ID      (0x2CU)
#define BSP_MT29F2G08ABAEA_DEVICE_ID1           (0xDAU)
#define BSP_MT29F2G08ABAEA_DEVICE_ID2           (0x90U)
#define BSP_MT29F2G08ABAEA_DEVICE_ID3           (0x95U)
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
* @addtogroup EV_HC32F4A0_LQFP176_MT29F2G08AB_Global_Functions
* @{
*/
int32_t BSP_MT29F2G08AB_Init(void);
int32_t BSP_MT29F2G08AB_ReadId(uint32_t u32IdAddr, uint8_t au8DevId[], uint32_t u32NumBytes, uint32_t u32Timeout);
int32_t BSP_MT29F2G08AB_EraseBlock(uint32_t u32BlockRowAddr, uint32_t u32Timeout);
int32_t BSP_MT29F2G08AB_ReadPage(uint32_t u32Page, uint8_t *pu8Data,
                                 uint32_t u32NumBytes, uint32_t u32Timeout);
int32_t BSP_MT29F2G08AB_WritePage(uint32_t u32Page, const uint8_t *pu8Data,
                                  uint32_t u32NumBytes, uint32_t u32Timeout);
int32_t BSP_MT29F2G08AB_1BitEccReadPage(uint32_t u32Page, uint8_t *pu8Data,
                                        uint32_t u32NumBytes, uint32_t u32Timeout);
int32_t BSP_MT29F2G08AB_1BitEccWritePage(uint32_t u32Page, const uint8_t *pu8Data,
                                         uint32_t u32NumBytes, uint32_t u32Timeout);
int32_t BSP_MT29F2G08AB_4BitEccReadPage(uint32_t u32Page, uint8_t *pu8Data,
                                        uint32_t u32NumBytes, uint32_t u32Timeout);
int32_t BSP_MT29F2G08AB_4BitEccWritePage(uint32_t u32Page, const uint8_t *pu8Data,
                                         uint32_t u32NumBytes, uint32_t u32Timeout);
/**
 * @}
 */
#endif /* BSP_MT29F2G08AB_ENABLE && BSP_EV_HC32F4A0_LQFP176 */

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

#endif /* __EV_HC32F4A0_LQFP176_MT29F2G08AB_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
