/**
 *******************************************************************************
 * @file  hc32_ll_fcg.h
 * @brief This file contains all the functions prototypes of the FCG driver
 *        library.
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
#define FCG0_PERIPH_SRAM0               (PWC_FCG0_SRAM0)
#define FCG0_PERIPH_SRAMB               (PWC_FCG0_SRAMB)
#define FCG0_PERIPH_KEY                 (PWC_FCG0_KEY)
#define FCG0_PERIPH_DMA1                (PWC_FCG0_DMA1)
#define FCG0_PERIPH_DMA2                (PWC_FCG0_DMA2)
#define FCG0_PERIPH_FCM                 (PWC_FCG0_FCM)
#define FCG0_PERIPH_AOS                 (PWC_FCG0_AOS)
#define FCG0_PERIPH_CTC                 (PWC_FCG0_CTC)
#define FCG0_PERIPH_AES                 (PWC_FCG0_AES)
#define FCG0_PERIPH_HASH                (PWC_FCG0_HASH)
#define FCG0_PERIPH_TRNG                (PWC_FCG0_TRNG)
#define FCG0_PERIPH_CRC                 (PWC_FCG0_CRC)
#define FCG0_PERIPH_DCU1                (PWC_FCG0_DCU1)
#define FCG0_PERIPH_DCU2                (PWC_FCG0_DCU2)
#define FCG0_PERIPH_DCU3                (PWC_FCG0_DCU3)
#define FCG0_PERIPH_DCU4                (PWC_FCG0_DCU4)
/**
 * @}
 */

/**
 * @defgroup FCG_FCG1_Peripheral FCG FCG1 peripheral
 * @{
 */
#define FCG1_PERIPH_MCAN1               (PWC_FCG1_MCAN1)
#define FCG1_PERIPH_MCAN2               (PWC_FCG1_MCAN2)
#define FCG1_PERIPH_QSPI                (PWC_FCG1_QSPI)
#define FCG1_PERIPH_I2C1                (PWC_FCG1_I2C1)
#define FCG1_PERIPH_I2C2                (PWC_FCG1_I2C2)
#define FCG1_PERIPH_SPI1                (PWC_FCG1_SPI1)
#define FCG1_PERIPH_SPI2                (PWC_FCG1_SPI2)
#define FCG1_PERIPH_SPI3                (PWC_FCG1_SPI3)
/**
 * @}
 */

/**
 * @defgroup FCG_FCG2_Peripheral FCG FCG2 peripheral
 * @{
 */
#define FCG2_PERIPH_TMR6_1              (PWC_FCG2_TMR6_1)
#define FCG2_PERIPH_TMR6_2              (PWC_FCG2_TMR6_2)
#define FCG2_PERIPH_TMR4_1              (PWC_FCG2_TMR4_1)
#define FCG2_PERIPH_TMR4_2              (PWC_FCG2_TMR4_2)
#define FCG2_PERIPH_TMR4_3              (PWC_FCG2_TMR4_3)
#define FCG2_PERIPH_TMR0_1              (PWC_FCG2_TMR0_1)
#define FCG2_PERIPH_TMR0_2              (PWC_FCG2_TMR0_2)
#define FCG2_PERIPH_EMB                 (PWC_FCG2_EMB)
#define FCG2_PERIPH_TMRA_1              (PWC_FCG2_TMRA_1)
#define FCG2_PERIPH_TMRA_2              (PWC_FCG2_TMRA_2)
#define FCG2_PERIPH_TMRA_3              (PWC_FCG2_TMRA_3)
#define FCG2_PERIPH_TMRA_4              (PWC_FCG2_TMRA_4)
#define FCG2_PERIPH_TMRA_5              (PWC_FCG2_TMRA_5)
/**
 * @}
 */

/**
 * @defgroup FCG_FCG3_Peripheral FCG FCG3 peripheral
 * @{
 */
#define FCG3_PERIPH_ADC1                (PWC_FCG3_ADC1)
#define FCG3_PERIPH_ADC2                (PWC_FCG3_ADC2)
#define FCG3_PERIPH_ADC3                (PWC_FCG3_ADC3)
#define FCG3_PERIPH_DAC                 (PWC_FCG3_DAC)
#define FCG3_PERIPH_CMP1_2              (PWC_FCG3_CMP12)
#define FCG3_PERIPH_CMP3_4              (PWC_FCG3_CMP34)
#define FCG3_PERIPH_SMC                 (PWC_FCG3_SMC)
#define FCG3_PERIPH_USART1              (PWC_FCG3_USART1)
#define FCG3_PERIPH_USART2              (PWC_FCG3_USART2)
#define FCG3_PERIPH_USART3              (PWC_FCG3_USART3)
#define FCG3_PERIPH_USART4              (PWC_FCG3_USART4)
#define FCG3_PERIPH_USART5              (PWC_FCG3_USART5)
#define FCG3_PERIPH_USART6              (PWC_FCG3_USART6)
/**
 * @}
 */

/**
 * @defgroup FCG_FCGx_Peripheral_Mask FCG FCGx Peripheral Mask
 * @{
 */
#define FCG_FCG0_PERIPH_MASK            (0x0FF7E411UL)
#define FCG_FCG1_PERIPH_MASK            (0x0007003BUL)
#define FCG_FCG2_PERIPH_MASK            (0x01F0BE03UL)
#define FCG_FCG3_PERIPH_MASK            (0x03F10317UL)
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
