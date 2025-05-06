/**
 *******************************************************************************
 * @file  hc32_ll_fcg.h
 * @brief This file contains all the functions prototypes of the FCG driver
 *        library.
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
#ifndef __HC32_LL_FCG_H__
#define __HC32_LL_FCG_H__

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_def.h"

#include "hc32f4xx.h"
#include "hc32f4xx_conf.h"
/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @addtogroup LL_FCG
 * @{
 */

#if (LL_FCG_ENABLE == DDL_ON)
/*******************************************************************************
 * Global type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Global pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup FCG_Global_Macros FCG Global Macros
 * @{
 */
/**
 * @defgroup FCG_FCG0_Peripheral FCG FCG0 peripheral
 * @{
 */
#define FCG0_PERIPH_SRAMH               (PWC_FCG0_SRAMH)
#define FCG0_PERIPH_SRAM12              (PWC_FCG0_SRAM12)
#define FCG0_PERIPH_SRAM3               (PWC_FCG0_SRAM3)
#define FCG0_PERIPH_SRAMRET             (PWC_FCG0_SRAMRET)
#define FCG0_PERIPH_DMA1                (PWC_FCG0_DMA1)
#define FCG0_PERIPH_DMA2                (PWC_FCG0_DMA2)
#define FCG0_PERIPH_FCM                 (PWC_FCG0_FCM)
#define FCG0_PERIPH_AOS                 (PWC_FCG0_AOS)
#define FCG0_PERIPH_AES                 (PWC_FCG0_AES)
#define FCG0_PERIPH_HASH                (PWC_FCG0_HASH)
#define FCG0_PERIPH_TRNG                (PWC_FCG0_TRNG)
#define FCG0_PERIPH_CRC                 (PWC_FCG0_CRC)
#define FCG0_PERIPH_DCU1                (PWC_FCG0_DCU1)
#define FCG0_PERIPH_DCU2                (PWC_FCG0_DCU2)
#define FCG0_PERIPH_DCU3                (PWC_FCG0_DCU3)
#define FCG0_PERIPH_DCU4                (PWC_FCG0_DCU4)
#define FCG0_PERIPH_KEY                 (PWC_FCG0_KEY)
/**
 * @}
 */

/**
 * @defgroup FCG_FCG1_Peripheral FCG FCG1 peripheral
 * @{
 */
#define FCG1_PERIPH_CAN                 (PWC_FCG1_CAN)
#define FCG1_PERIPH_QSPI                (PWC_FCG1_QSPI)
#define FCG1_PERIPH_I2C1                (PWC_FCG1_I2C1)
#define FCG1_PERIPH_I2C2                (PWC_FCG1_I2C2)
#define FCG1_PERIPH_I2C3                (PWC_FCG1_I2C3)
#define FCG1_PERIPH_USBFS               (PWC_FCG1_USBFS)
#define FCG1_PERIPH_SDIOC1              (PWC_FCG1_SDIOC1)
#define FCG1_PERIPH_SDIOC2              (PWC_FCG1_SDIOC2)
#define FCG1_PERIPH_I2S1                (PWC_FCG1_I2S1)
#define FCG1_PERIPH_I2S2                (PWC_FCG1_I2S2)
#define FCG1_PERIPH_I2S3                (PWC_FCG1_I2S3)
#define FCG1_PERIPH_I2S4                (PWC_FCG1_I2S4)
#define FCG1_PERIPH_SPI1                (PWC_FCG1_SPI1)
#define FCG1_PERIPH_SPI2                (PWC_FCG1_SPI2)
#define FCG1_PERIPH_SPI3                (PWC_FCG1_SPI3)
#define FCG1_PERIPH_SPI4                (PWC_FCG1_SPI4)
#define FCG1_PERIPH_USART1              (PWC_FCG1_USART1)
#define FCG1_PERIPH_USART2              (PWC_FCG1_USART2)
#define FCG1_PERIPH_USART3              (PWC_FCG1_USART3)
#define FCG1_PERIPH_USART4              (PWC_FCG1_USART4)
/**
 * @}
 */

/**
 * @defgroup FCG_FCG2_Peripheral FCG FCG2 peripheral
 * @{
 */
#define FCG2_PERIPH_TMR0_1              (PWC_FCG2_TIMER0_1)
#define FCG2_PERIPH_TMR0_2              (PWC_FCG2_TIMER0_2)
#define FCG2_PERIPH_TMRA_1              (PWC_FCG2_TIMERA_1)
#define FCG2_PERIPH_TMRA_2              (PWC_FCG2_TIMERA_2)
#define FCG2_PERIPH_TMRA_3              (PWC_FCG2_TIMERA_3)
#define FCG2_PERIPH_TMRA_4              (PWC_FCG2_TIMERA_4)
#define FCG2_PERIPH_TMRA_5              (PWC_FCG2_TIMERA_5)
#define FCG2_PERIPH_TMRA_6              (PWC_FCG2_TIMERA_6)
#define FCG2_PERIPH_TMR4_1              (PWC_FCG2_TIMER4_1)
#define FCG2_PERIPH_TMR4_2              (PWC_FCG2_TIMER4_2)
#define FCG2_PERIPH_TMR4_3              (PWC_FCG2_TIMER4_3)
#define FCG2_PERIPH_EMB                 (PWC_FCG2_EMB)
#define FCG2_PERIPH_TMR6_1              (PWC_FCG2_TIMER6_1)
#define FCG2_PERIPH_TMR6_2              (PWC_FCG2_TIMER6_2)
#define FCG2_PERIPH_TMR6_3              (PWC_FCG2_TIMER6_3)
/**
 * @}
 */

/**
 * @defgroup FCG_FCG3_Peripheral FCG FCG3 peripheral
 * @{
 */
#define FCG3_PERIPH_ADC1                (PWC_FCG3_ADC1)
#define FCG3_PERIPH_ADC2                (PWC_FCG3_ADC2)
#define FCG3_PERIPH_CMP                 (PWC_FCG3_CMP)
#define FCG3_PERIPH_OTS                 (PWC_FCG3_OTS)
/**
 * @}
 */

/**
 * @defgroup FCG_FCGx_Peripheral_Mask FCG FCGx Peripheral Mask
 * @{
 */
#define FCG_FCG0_PERIPH_MASK            (0x8FF3C511UL)
#define FCG_FCG1_PERIPH_MASK            (0x0F0FFD79UL)
#define FCG_FCG2_PERIPH_MASK            (0x000787FFUL)
#define FCG_FCG3_PERIPH_MASK            (0x00001103UL)
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
 * @addtogroup FCG_Global_Functions
 * @{
 */

void FCG_Fcg0PeriphClockCmd(uint32_t u32Fcg0Periph, en_functional_state_t enNewState);

void FCG_Fcg1PeriphClockCmd(uint32_t u32Fcg1Periph, en_functional_state_t enNewState);
void FCG_Fcg2PeriphClockCmd(uint32_t u32Fcg2Periph, en_functional_state_t enNewState);
void FCG_Fcg3PeriphClockCmd(uint32_t u32Fcg3Periph, en_functional_state_t enNewState);

/**
 * @}
 */

#endif /* LL_FCG_ENABLE */

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* __HC32_LL_FCG_H__ */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
