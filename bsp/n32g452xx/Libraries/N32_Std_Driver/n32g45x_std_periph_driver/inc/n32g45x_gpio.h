/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32g45x_gpio.h
 * @author Nations
 * @version v1.0.1
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#ifndef __N32G45X_GPIO_H__
#define __N32G45X_GPIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32g45x.h"

/** @addtogroup N32G45X_StdPeriph_Driver
 * @{
 */

/** @addtogroup GPIO
 * @{
 */

/** @addtogroup GPIO_Exported_Types
 * @{
 */

#define IS_GPIO_ALL_PERIPH(PERIPH)                                                                                     \
    (((PERIPH) == GPIOA) || ((PERIPH) == GPIOB) || ((PERIPH) == GPIOC) || ((PERIPH) == GPIOD) || ((PERIPH) == GPIOE)   \
     || ((PERIPH) == GPIOF) || ((PERIPH) == GPIOG))

/**
 * @brief  Output Maximum frequency selection
 */

typedef enum
{
    GPIO_INPUT      = 0,
    GPIO_Speed_2MHz = 1,
    GPIO_Speed_10MHz,
    GPIO_Speed_50MHz
} GPIO_SpeedType;
#define IS_GPIO_SPEED(SPEED)                                                                                           \
    (((SPEED) == GPIO_INPUT) || ((SPEED) == GPIO_Speed_10MHz) || ((SPEED) == GPIO_Speed_2MHz)                          \
     || ((SPEED) == GPIO_Speed_50MHz))

/**
 * @brief  Configuration Mode enumeration
 */

typedef enum
{
    GPIO_Mode_AIN         = 0x0,
    GPIO_Mode_IN_FLOATING = 0x04,
    GPIO_Mode_IPD         = 0x28,
    GPIO_Mode_IPU         = 0x48,
    GPIO_Mode_Out_OD      = 0x14,
    GPIO_Mode_Out_PP      = 0x10,
    GPIO_Mode_AF_OD       = 0x1C,
    GPIO_Mode_AF_PP       = 0x18
} GPIO_ModeType;

#define IS_GPIO_MODE(MODE)                                                                                             \
    (((MODE) == GPIO_Mode_AIN) || ((MODE) == GPIO_Mode_IN_FLOATING) || ((MODE) == GPIO_Mode_IPD)                       \
     || ((MODE) == GPIO_Mode_IPU) || ((MODE) == GPIO_Mode_Out_OD) || ((MODE) == GPIO_Mode_Out_PP)                      \
     || ((MODE) == GPIO_Mode_AF_OD) || ((MODE) == GPIO_Mode_AF_PP))

/**
 * @brief  GPIO Init structure definition
 */

typedef struct
{
    uint16_t Pin; /*!< Specifies the GPIO pins to be configured.
                            This parameter can be any value of @ref GPIO_pins_define */

    GPIO_SpeedType GPIO_Speed; /*!< Specifies the speed for the selected pins.
                                       This parameter can be a value of @ref GPIO_SpeedType */

    GPIO_ModeType GPIO_Mode; /*!< Specifies the operating mode for the selected pins.
                                     This parameter can be a value of @ref GPIO_ModeType */
} GPIO_InitType;

/**
 * @brief  Bit_SET and Bit_RESET enumeration
 */

typedef enum
{
    Bit_RESET = 0,
    Bit_SET
} Bit_OperateType;

#define IS_GPIO_BIT_OPERATE(OPERATE) (((OPERATE) == Bit_RESET) || ((OPERATE) == Bit_SET))

/**
 * @}
 */

/** @addtogroup GPIO_Exported_Constants
 * @{
 */

/** @addtogroup GPIO_pins_define
 * @{
 */

#define GPIO_PIN_0   ((uint16_t)0x0001) /*!< Pin 0 selected */
#define GPIO_PIN_1   ((uint16_t)0x0002) /*!< Pin 1 selected */
#define GPIO_PIN_2   ((uint16_t)0x0004) /*!< Pin 2 selected */
#define GPIO_PIN_3   ((uint16_t)0x0008) /*!< Pin 3 selected */
#define GPIO_PIN_4   ((uint16_t)0x0010) /*!< Pin 4 selected */
#define GPIO_PIN_5   ((uint16_t)0x0020) /*!< Pin 5 selected */
#define GPIO_PIN_6   ((uint16_t)0x0040) /*!< Pin 6 selected */
#define GPIO_PIN_7   ((uint16_t)0x0080) /*!< Pin 7 selected */
#define GPIO_PIN_8   ((uint16_t)0x0100) /*!< Pin 8 selected */
#define GPIO_PIN_9   ((uint16_t)0x0200) /*!< Pin 9 selected */
#define GPIO_PIN_10  ((uint16_t)0x0400) /*!< Pin 10 selected */
#define GPIO_PIN_11  ((uint16_t)0x0800) /*!< Pin 11 selected */
#define GPIO_PIN_12  ((uint16_t)0x1000) /*!< Pin 12 selected */
#define GPIO_PIN_13  ((uint16_t)0x2000) /*!< Pin 13 selected */
#define GPIO_PIN_14  ((uint16_t)0x4000) /*!< Pin 14 selected */
#define GPIO_PIN_15  ((uint16_t)0x8000) /*!< Pin 15 selected */
#define GPIO_PIN_ALL ((uint16_t)0xFFFF) /*!< All pins selected */

#define IS_GPIO_PIN(PIN) ((((PIN) & (uint16_t)0x00) == 0x00) && ((PIN) != (uint16_t)0x00))

#define IS_GET_GPIO_PIN(PIN)                                                                                           \
    (((PIN) == GPIO_PIN_0) || ((PIN) == GPIO_PIN_1) || ((PIN) == GPIO_PIN_2) || ((PIN) == GPIO_PIN_3)                  \
     || ((PIN) == GPIO_PIN_4) || ((PIN) == GPIO_PIN_5) || ((PIN) == GPIO_PIN_6) || ((PIN) == GPIO_PIN_7)               \
     || ((PIN) == GPIO_PIN_8) || ((PIN) == GPIO_PIN_9) || ((PIN) == GPIO_PIN_10) || ((PIN) == GPIO_PIN_11)             \
     || ((PIN) == GPIO_PIN_12) || ((PIN) == GPIO_PIN_13) || ((PIN) == GPIO_PIN_14) || ((PIN) == GPIO_PIN_15))

/**
 * @}
 */

/** @addtogroup GPIO_Remap_define
 * @{
 */

#define GPIO_RMP_SPI1              ((uint32_t)0x00000001) /*!< SPI1 Alternate Function mapping */
#define GPIO_RMP_I2C1              ((uint32_t)0x00000002) /*!< I2C1 Alternate Function mapping */
#define GPIO_RMP_USART1            ((uint32_t)0x00000004) /*!< USART1 Alternate Function mapping */
#define GPIO_RMP_USART2            ((uint32_t)0x00000008) /*!< USART2 Alternate Function mapping */
#define GPIO_PART_RMP_USART3       ((uint32_t)0x00140010) /*!< USART3 Partial Alternate Function mapping */
#define GPIO_ALL_RMP_USART3        ((uint32_t)0x00140030) /*!< USART3 Full Alternate Function mapping */
#define GPIO_PART1_RMP_TIM1        ((uint32_t)0x00160040) /*!< TIM1 Partial Alternate Function mapping */
#define GPIO_PART2_RMP_TIM1        ((uint32_t)0x00160080) /*!< TIM1 Partial Alternate Function mapping */
#define GPIO_ALL_RMP_TIM1          ((uint32_t)0x001600C0) /*!< TIM1 Full Alternate Function mapping */
#define GPIO_PartialRemap1_TIM2    ((uint32_t)0x00180100) /*!< TIM2 Partial1 Alternate Function mapping */
#define GPIO_PART2_RMP_TIM2        ((uint32_t)0x00180200) /*!< TIM2 Partial2 Alternate Function mapping */
#define GPIO_ALL_RMP_TIM2          ((uint32_t)0x00180300) /*!< TIM2 Full Alternate Function mapping */
#define GPIO_PART1_RMP_TIM3        ((uint32_t)0x001A0800) /*!< TIM3 Partial Alternate Function mapping */
#define GPIO_ALL_RMP_TIM3          ((uint32_t)0x001A0C00) /*!< TIM3 Full Alternate Function mapping */
#define GPIO_RMP_TIM4              ((uint32_t)0x00001000) /*!< TIM4 Alternate Function mapping */
#define GPIO_RMP1_CAN1             ((uint32_t)0x001D2000) /*!< CAN1 Alternate Function mapping */
#define GPIO_RMP2_CAN1             ((uint32_t)0x001D4000) /*!< CAN1 Alternate Function mapping */
#define GPIO_RMP3_CAN1             ((uint32_t)0x001D6000) /*!< CAN1 Alternate Function mapping */
#define GPIO_RMP_PD01              ((uint32_t)0x00008000) /*!< PD01 Alternate Function mapping */
#define GPIO_RMP_TIM5CH4           ((uint32_t)0x00200001) /*!< LSI connected to TIM5 Channel4 input capture for calibration */
#define GPIO_RMP_ADC1_ETRI         ((uint32_t)0x00200002) /*!< ADC1 External Trigger Injected Conversion remapping */
#define GPIO_RMP_ADC1_ETRR         ((uint32_t)0x00200004) /*!< ADC1 External Trigger Regular Conversion remapping */
#define GPIO_RMP_ADC2_ETRI         ((uint32_t)0x00200008) /*!< ADC2 External Trigger Injected Conversion remapping */
#define GPIO_RMP_ADC2_ETRR         ((uint32_t)0x00200010) /*!< ADC2 External Trigger Regular Conversion remapping */
#define GPIO_RMP_MII_RMII_SEL      ((uint32_t)0x00200080) /*!< MII_RMII_SEL remapping */
#define GPIO_RMP_SW_JTAG_NO_NJTRST ((uint32_t)0x00300100) /*!< Full SWJ Enabled (JTAG-DP + SW-DP) but without JTRST */
#define GPIO_RMP_SW_JTAG_SW_ENABLE ((uint32_t)0x00300200) /*!< JTAG-DP Disabled and SW-DP Enabled */
#define GPIO_RMP_SW_JTAG_DISABLE   ((uint32_t)0x00300400) /*!< Full SWJ Disabled (JTAG-DP + SW-DP) */

/* AFIO_RMP_CFG2 */
#define GPIO_Remap_XFMC_NADV       ((uint32_t)0x80000400) /*!< XFMC_NADV Alternate Function mapping */

/* AFIO_RMP_CFG3 */
#define GPIO_RMP_SDIO   ((uint32_t)0x40000001) /*!< SDIO Alternate Function mapping */
#define GPIO_RMP1_CAN2  ((uint32_t)0x40110002) /*!< CAN2 Alternate Function mapping */
#define GPIO_RMP3_CAN2  ((uint32_t)0x40110006) /*!< CAN2 Alternate Function mapping */
#define GPIO_RMP1_QSPI  ((uint32_t)0x40140020) /*!< QSPI Alternate Function mapping */
#define GPIO_RMP3_QSPI  ((uint32_t)0x40140030) /*!< QSPI Alternate Function mapping */
#define GPIO_RMP1_I2C2  ((uint32_t)0x40160040) /*!< I2C2 Alternate Function mapping */
#define GPIO_RMP3_I2C2  ((uint32_t)0x401600C0) /*!< I2C2 Alternate Function mapping */
#define GPIO_RMP2_I2C3  ((uint32_t)0x40180200) /*!< I2C3 Alternate Function mapping */
#define GPIO_RMP3_I2C3  ((uint32_t)0x40180300) /*!< I2C3 Alternate Function mapping */
#define GPIO_RMP1_I2C4  ((uint32_t)0x401A0400) /*!< I2C4 Alternate Function mapping */
#define GPIO_RMP3_I2C4  ((uint32_t)0x401A0C00) /*!< I2C4 Alternate Function mapping */
#define GPIO_RMP1_SPI2  ((uint32_t)0x401C1000) /*!< SPI2 Alternate Function mapping */
#define GPIO_RMP2_SPI2  ((uint32_t)0x401C3000) /*!< SPI2 Alternate Function mapping */
#define GPIO_RMP1_SPI3  ((uint32_t)0x401E4000) /*!< SPI3 Alternate Function mapping */
#define GPIO_RMP2_SPI3  ((uint32_t)0x401E8000) /*!< SPI3 Alternate Function mapping */
#define GPIO_RMP3_SPI3  ((uint32_t)0x401EC000) /*!< SPI3 Alternate Function mapping */
#define GPIO_RMP1_ETH   ((uint32_t)0x40300001) /*!< ETH Alternate Function mapping */
#define GPIO_RMP2_ETH   ((uint32_t)0x40300002) /*!< ETH Alternate Function mapping */
#define GPIO_RMP3_ETH   ((uint32_t)0x40300003) /*!< ETH Alternate Function mapping */
#define GPIO_RMP1_SPI1  ((uint32_t)0x41200000) /*!< SPI1 Alternate Function mapping */
#define GPIO_RMP2_SPI1  ((uint32_t)0x41200004) /*!< SPI1 Alternate Function mapping */
#define GPIO_RMP3_SPI1  ((uint32_t)0x43200004) /*!< SPI1 Alternate Function mapping */
#define GPIO_RMP1_USART2 ((uint32_t)0x44200000) /*!< USART2 Alternate Function mapping */
#define GPIO_RMP2_USART2 ((uint32_t)0x44200008) /*!< USART2 Alternate Function mapping */
#define GPIO_RMP3_USART2 ((uint32_t)0x46200008) /*!< USART2 Alternate Function mapping */
#define GPIO_RMP1_UART4 ((uint32_t)0x40340010) /*!< UART4 Alternate Function mapping */
#define GPIO_RMP2_UART4 ((uint32_t)0x40340020) /*!< UART4 Alternate Function mapping */
#define GPIO_RMP3_UART4 ((uint32_t)0x40340030) /*!< UART4 Alternate Function mapping */
#define GPIO_RMP1_UART5 ((uint32_t)0x40360040) /*!< UART5 Alternate Function mapping */
#define GPIO_RMP2_UART5 ((uint32_t)0x40360080) /*!< UART5 Alternate Function mapping */
#define GPIO_RMP3_UART5 ((uint32_t)0x403600C0) /*!< UART5 Alternate Function mapping */
#define GPIO_RMP2_UART6 ((uint32_t)0x40380200) /*!< UART6 Alternate Function mapping */
#define GPIO_RMP3_UART6 ((uint32_t)0x40380300) /*!< UART6 Alternate Function mapping */
#define GPIO_RMP1_UART7 ((uint32_t)0x403A0400) /*!< UART7 Alternate Function mapping */
#define GPIO_RMP3_UART7 ((uint32_t)0x403A0C00) /*!< UART7 Alternate Function mapping */
#define GPIO_RMP1_XFMC  ((uint32_t)0x403C1000) /*!< XFMC Alternate Function mapping */
#define GPIO_RMP3_XFMC  ((uint32_t)0x403C3000) /*!< XFMC Alternate Function mapping */
#define GPIO_RMP1_TIM8  ((uint32_t)0x403E4000) /*!< TIM8 Alternate Function mapping */
#define GPIO_RMP3_TIM8  ((uint32_t)0x403EC000) /*!< TIM8 Alternate Function mapping */

/* AFIO_RMP_CFG4 */
#define GPIO_RMP1_COMP1       ((uint32_t)0x20100001) /*!< COMP1 Alternate Function mapping */
#define GPIO_RMP2_COMP1       ((uint32_t)0x20100002) /*!< COMP1 Alternate Function mapping */
#define GPIO_RMP3_COMP1       ((uint32_t)0x20100003) /*!< COMP1 Alternate Function mapping */
#define GPIO_RMP1_COMP2       ((uint32_t)0x20120004) /*!< COMP2 Alternate Function mapping */
#define GPIO_RMP2_COMP2       ((uint32_t)0x20120008) /*!< COMP2 Alternate Function mapping */
#define GPIO_RMP3_COMP2       ((uint32_t)0x2012000C) /*!< COMP2 Alternate Function mapping */
#define GPIO_RMP1_COMP3       ((uint32_t)0x20140010) /*!< COMP3 Alternate Function mapping */
#define GPIO_RMP3_COMP3       ((uint32_t)0x20140030) /*!< COMP3 Alternate Function mapping */
#define GPIO_RMP1_COMP4       ((uint32_t)0x20160040) /*!< COMP4 Alternate Function mapping */
#define GPIO_RMP3_COMP4       ((uint32_t)0x201600C0) /*!< COMP4 Alternate Function mapping */
#define GPIO_RMP1_COMP5       ((uint32_t)0x20180100) /*!< COMP5 Alternate Function mapping */
#define GPIO_RMP2_COMP5       ((uint32_t)0x20180200) /*!< COMP5 Alternate Function mapping */
#define GPIO_RMP3_COMP5       ((uint32_t)0x20180300) /*!< COMP5 Alternate Function mapping */
#define GPIO_RMP1_COMP6       ((uint32_t)0x201A0400) /*!< COMP6 Alternate Function mapping */
#define GPIO_RMP3_COMP6       ((uint32_t)0x201A0C00) /*!< COMP6 Alternate Function mapping */
#define GPIO_RMP_COMP7        ((uint32_t)0x20001000) /*!< COMP7 Alternate Function mapping */
#define GPIO_RMP_ADC3_ETRI    ((uint32_t)0x20004000) /*!< ADC3_ETRGINJ Alternate Function mapping */
#define GPIO_RMP_ADC3_ETRR    ((uint32_t)0x20008000) /*!< ADC3_ETRGREG Alternate Function mapping */
#define GPIO_RMP_ADC4_ETRI    ((uint32_t)0x20200001) /*!< ADC4_ETRGINJ Alternate Function mapping */
#define GPIO_RMP_ADC4_ETRR    ((uint32_t)0x20200002) /*!< ADC4_ETRGREG Alternate Function mapping */
#define GPIO_RMP_TSC_OUT_CTRL ((uint32_t)0x20200004) /*!< TSC_OUT_CTRL Alternate Function mapping */
#define GPIO_RMP_QSPI_XIP_EN  ((uint32_t)0x20200008) /*!< QSPI_XIP_EN Alternate Function mapping */
#define GPIO_RMP1_DVP         ((uint32_t)0x20340010) /*!< DVP Alternate Function mapping */
#define GPIO_RMP3_DVP         ((uint32_t)0x20340030) /*!< DVP Alternate Function mapping */
#define GPIO_Remap_SPI1_NSS   ((uint32_t)0x20200040) /*!< SPI1 NSS Alternate Function mapping */
#define GPIO_Remap_SPI2_NSS   ((uint32_t)0x20200080) /*!< SPI2 NSS Alternate Function mapping */
#define GPIO_Remap_SPI3_NSS   ((uint32_t)0x20200100) /*!< SPI3 NSS Alternate Function mapping */
#define GPIO_Remap_QSPI_MISO  ((uint32_t)0x20200200) /*!< QSPI MISO Alternate Function mapping */

/* AFIO_RMP_CFG5 */
#define GPIO_Remap_DET_EN_EGB4    ((uint32_t)0x10200080) /*!< EGB4 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_EGB3    ((uint32_t)0x10200040) /*!< EGB4 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_EGB2    ((uint32_t)0x10200020) /*!< EGB4 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_EGB1    ((uint32_t)0x10200010) /*!< EGB4 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_EGBN4   ((uint32_t)0x10200008) /*!< EGBN4 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_EGBN3   ((uint32_t)0x10200004) /*!< EGBN3 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_EGBN2   ((uint32_t)0x10200002) /*!< EGBN2 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_EGBN1   ((uint32_t)0x10200001) /*!< EGBN1 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_ECLAMP4 ((uint32_t)0x10008000) /*!< ECLAMP4 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_ECLAMP3 ((uint32_t)0x10004000) /*!< ECLAMP3 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_ECLAMP2 ((uint32_t)0x10002000) /*!< ECLAMP2 Detect Alternate Function mapping*/
#define GPIO_Remap_DET_EN_ECLAMP1 ((uint32_t)0x10001000) /*!< ECLAMP1 Detect Alternate Function mapping*/
#define GPIO_Remap_RST_EN_EGB4    ((uint32_t)0x10000800) /*!< EGB4 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_EGB3    ((uint32_t)0x10000400) /*!< EGB3 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_EGB2    ((uint32_t)0x10000200) /*!< EGB2 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_EGB1    ((uint32_t)0x10000100) /*!< EGB1 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_EGBN4   ((uint32_t)0x10000080) /*!< EGBN4 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_EGBN3   ((uint32_t)0x10000040) /*!< EGBN3 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_EGBN2   ((uint32_t)0x10000020) /*!< EGBN2 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_EGBN1   ((uint32_t)0x10000010) /*!< EGBN1 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_ECLAMP4 ((uint32_t)0x10000008) /*!< ECLAMP4 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_ECLAMP3 ((uint32_t)0x10000004) /*!< ECLAMP3 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_ECLAMP2 ((uint32_t)0x10000002) /*!< ECLAMP2 Reset Alternate Function mapping*/
#define GPIO_Remap_RST_EN_ECLAMP1 ((uint32_t)0x10000001) /*!< ECLAMP1 Reset Alternate Function mapping*/

#define IS_GPIO_REMAP(REMAP)                                                                                           \
    (((REMAP) == GPIO_RMP_SPI1) || ((REMAP) == GPIO_RMP_I2C1) || ((REMAP) == GPIO_RMP_USART1)                          \
     || ((REMAP) == GPIO_RMP_USART2) || ((REMAP) == GPIO_PART_RMP_USART3) || ((REMAP) == GPIO_ALL_RMP_USART3)          \
     || ((REMAP) == GPIO_PART1_RMP_TIM1) || ((REMAP) == GPIO_ALL_RMP_TIM1) || ((REMAP) == GPIO_PartialRemap1_TIM2)     \
     || ((REMAP) == GPIO_PART2_RMP_TIM2) || ((REMAP) == GPIO_ALL_RMP_TIM2) || ((REMAP) == GPIO_PART1_RMP_TIM3)         \
     || ((REMAP) == GPIO_ALL_RMP_TIM3) || ((REMAP) == GPIO_RMP_TIM4) || ((REMAP) == GPIO_RMP1_CAN1)                    \
     || ((REMAP) == GPIO_RMP2_CAN1) || ((REMAP) == GPIO_RMP3_CAN1) || ((REMAP) == GPIO_RMP_PD01) || ((REMAP) == GPIO_RMP_TIM5CH4) \
     || ((REMAP) == GPIO_RMP_ADC1_ETRI) || ((REMAP) == GPIO_RMP_ADC1_ETRR) || ((REMAP) == GPIO_RMP_ADC2_ETRI)          \
     || ((REMAP) == GPIO_RMP_ADC2_ETRR) || ((REMAP) == GPIO_RMP_SW_JTAG_NO_NJTRST)                                     \
     || ((REMAP) == GPIO_RMP_SW_JTAG_SW_ENABLE) || ((REMAP) == GPIO_RMP_SW_JTAG_DISABLE)                               \
     || ((REMAP) == GPIO_Remap_XFMC_NADV) || ((REMAP) == GPIO_RMP_SDIO) || ((REMAP) == GPIO_RMP1_CAN2)                 \
     || ((REMAP) == GPIO_RMP3_CAN2) || ((REMAP) == GPIO_RMP1_QSPI) || ((REMAP) == GPIO_RMP3_QSPI)                      \
     || ((REMAP) == GPIO_RMP1_I2C2) || ((REMAP) == GPIO_RMP3_I2C2) || ((REMAP) == GPIO_RMP2_I2C3)                      \
     || ((REMAP) == GPIO_RMP3_I2C3) || ((REMAP) == GPIO_RMP1_I2C4) || ((REMAP) == GPIO_RMP3_I2C4)                      \
     || ((REMAP) == GPIO_RMP1_SPI2) || ((REMAP) == GPIO_RMP2_SPI2) || ((REMAP) == GPIO_RMP1_SPI3)                      \
     || ((REMAP) == GPIO_RMP2_SPI3) || ((REMAP) == GPIO_RMP3_SPI3) || ((REMAP) == GPIO_RMP1_ETH)                       \
     || ((REMAP) == GPIO_RMP2_ETH) || ((REMAP) == GPIO_RMP3_ETH) || ((REMAP) == GPIO_RMP1_SPI1)                        \
     || ((REMAP) == GPIO_RMP2_SPI1) || ((REMAP) == GPIO_RMP3_SPI1) || ((REMAP) == GPIO_RMP1_USART2)                    \
     || ((REMAP) == GPIO_RMP2_USART2) || ((REMAP) == GPIO_RMP3_USART2) || ((REMAP) == GPIO_RMP1_UART4)                 \
     || ((REMAP) == GPIO_RMP2_UART4) || ((REMAP) == GPIO_RMP3_UART4) || ((REMAP) == GPIO_RMP1_UART5)                   \
     || ((REMAP) == GPIO_RMP2_UART5) || ((REMAP) == GPIO_RMP3_UART5) || ((REMAP) == GPIO_RMP2_UART6)                   \
     || ((REMAP) == GPIO_RMP3_UART6) || ((REMAP) == GPIO_RMP1_UART7) || ((REMAP) == GPIO_RMP3_UART7)                   \
     || ((REMAP) == GPIO_RMP1_XFMC) || ((REMAP) == GPIO_RMP3_XFMC) || ((REMAP) == GPIO_RMP1_TIM8)                      \
     || ((REMAP) == GPIO_RMP3_TIM8) || ((REMAP) == GPIO_RMP1_COMP1) || ((REMAP) == GPIO_RMP2_COMP1)                    \
     || ((REMAP) == GPIO_RMP3_COMP1) || ((REMAP) == GPIO_RMP1_COMP2) || ((REMAP) == GPIO_RMP2_COMP2)                   \
     || ((REMAP) == GPIO_RMP3_COMP2) || ((REMAP) == GPIO_RMP1_COMP3) || ((REMAP) == GPIO_RMP3_COMP3)                   \
     || ((REMAP) == GPIO_RMP1_COMP4) || ((REMAP) == GPIO_RMP3_COMP4) || ((REMAP) == GPIO_RMP1_COMP5)                   \
     || ((REMAP) == GPIO_RMP2_COMP5) || ((REMAP) == GPIO_RMP3_COMP5) || ((REMAP) == GPIO_RMP1_COMP6)                   \
     || ((REMAP) == GPIO_RMP3_COMP6) || ((REMAP) == GPIO_RMP_COMP7) || ((REMAP) == GPIO_RMP_ADC3_ETRI)                 \
     || ((REMAP) == GPIO_RMP_ADC3_ETRR) || ((REMAP) == GPIO_RMP_ADC4_ETRI) || ((REMAP) == GPIO_RMP_ADC4_ETRR)          \
     || ((REMAP) == GPIO_RMP_TSC_OUT_CTRL) || ((REMAP) == GPIO_RMP_QSPI_XIP_EN) || ((REMAP) == GPIO_RMP1_DVP)          \
     || ((REMAP) == GPIO_RMP3_DVP) || ((REMAP) == GPIO_Remap_SPI1_NSS) || ((REMAP) == GPIO_Remap_SPI2_NSS)             \
     || ((REMAP) == GPIO_Remap_SPI3_NSS) || ((REMAP) == GPIO_Remap_QSPI_MISO) || ((REMAP) == GPIO_RMP_MII_RMII_SEL)    \
     || ((REMAP) == GPIO_PART2_RMP_TIM1) || ((REMAP) == GPIO_Remap_DET_EN_EGB4) || ((REMAP) == GPIO_Remap_DET_EN_EGB3) \
     || ((REMAP) == GPIO_Remap_DET_EN_EGB2) || ((REMAP) == GPIO_Remap_DET_EN_EGB1)                                     \
     || ((REMAP) == GPIO_Remap_DET_EN_EGBN4) || ((REMAP) == GPIO_Remap_DET_EN_EGBN3)                                   \
     || ((REMAP) == GPIO_Remap_DET_EN_EGBN2) || ((REMAP) == GPIO_Remap_DET_EN_EGBN1)                                   \
     || ((REMAP) == GPIO_Remap_DET_EN_ECLAMP4) || ((REMAP) == GPIO_Remap_DET_EN_ECLAMP3)                               \
     || ((REMAP) == GPIO_Remap_DET_EN_ECLAMP2) || ((REMAP) == GPIO_Remap_DET_EN_ECLAMP1)                               \
     || ((REMAP) == GPIO_Remap_RST_EN_EGB4) || ((REMAP) == GPIO_Remap_RST_EN_EGB3)                                     \
     || ((REMAP) == GPIO_Remap_RST_EN_EGB2) || ((REMAP) == GPIO_Remap_RST_EN_EGB1)                                     \
     || ((REMAP) == GPIO_Remap_RST_EN_EGBN4) || ((REMAP) == GPIO_Remap_RST_EN_EGBN3)                                   \
     || ((REMAP) == GPIO_Remap_RST_EN_EGBN2) || ((REMAP) == GPIO_Remap_RST_EN_EGBN1)                                   \
     || ((REMAP) == GPIO_Remap_RST_EN_ECLAMP4) || ((REMAP) == GPIO_Remap_RST_EN_ECLAMP3)                               \
     || ((REMAP) == GPIO_Remap_RST_EN_ECLAMP2) || ((REMAP) == GPIO_Remap_RST_EN_ECLAMP1))

/**
 * @}
 */

/** @addtogroup GPIO_Port_Sources
 * @{
 */

#define GPIOA_PORT_SOURCE ((uint8_t)0x00)
#define GPIOB_PORT_SOURCE ((uint8_t)0x01)
#define GPIOC_PORT_SOURCE ((uint8_t)0x02)
#define GPIOD_PORT_SOURCE ((uint8_t)0x03)
#define GPIOE_PORT_SOURCE ((uint8_t)0x04)
#define GPIOF_PORT_SOURCE ((uint8_t)0x05)
#define GPIOG_PORT_SOURCE ((uint8_t)0x06)
#define IS_GPIO_EVENTOUT_PORT_SOURCE(PORTSOURCE)                                                                       \
    (((PORTSOURCE) == GPIOA_PORT_SOURCE) || ((PORTSOURCE) == GPIOB_PORT_SOURCE) || ((PORTSOURCE) == GPIOC_PORT_SOURCE) \
     || ((PORTSOURCE) == GPIOD_PORT_SOURCE) || ((PORTSOURCE) == GPIOE_PORT_SOURCE))

#define IS_GPIO_EXTI_PORT_SOURCE(PORTSOURCE)                                                                           \
    (((PORTSOURCE) == GPIOA_PORT_SOURCE) || ((PORTSOURCE) == GPIOB_PORT_SOURCE) || ((PORTSOURCE) == GPIOC_PORT_SOURCE) \
     || ((PORTSOURCE) == GPIOD_PORT_SOURCE) || ((PORTSOURCE) == GPIOE_PORT_SOURCE)                                     \
     || ((PORTSOURCE) == GPIOF_PORT_SOURCE) || ((PORTSOURCE) == GPIOG_PORT_SOURCE))

/**
 * @}
 */

/** @addtogroup GPIO_Pin_sources
 * @{
 */

#define GPIO_PIN_SOURCE0  ((uint8_t)0x00)
#define GPIO_PIN_SOURCE1  ((uint8_t)0x01)
#define GPIO_PIN_SOURCE2  ((uint8_t)0x02)
#define GPIO_PIN_SOURCE3  ((uint8_t)0x03)
#define GPIO_PIN_SOURCE4  ((uint8_t)0x04)
#define GPIO_PIN_SOURCE5  ((uint8_t)0x05)
#define GPIO_PIN_SOURCE6  ((uint8_t)0x06)
#define GPIO_PIN_SOURCE7  ((uint8_t)0x07)
#define GPIO_PIN_SOURCE8  ((uint8_t)0x08)
#define GPIO_PIN_SOURCE9  ((uint8_t)0x09)
#define GPIO_PIN_SOURCE10 ((uint8_t)0x0A)
#define GPIO_PIN_SOURCE11 ((uint8_t)0x0B)
#define GPIO_PIN_SOURCE12 ((uint8_t)0x0C)
#define GPIO_PIN_SOURCE13 ((uint8_t)0x0D)
#define GPIO_PIN_SOURCE14 ((uint8_t)0x0E)
#define GPIO_PIN_SOURCE15 ((uint8_t)0x0F)

#define IS_GPIO_PIN_SOURCE(PINSOURCE)                                                                                  \
    (((PINSOURCE) == GPIO_PIN_SOURCE0) || ((PINSOURCE) == GPIO_PIN_SOURCE1) || ((PINSOURCE) == GPIO_PIN_SOURCE2)       \
     || ((PINSOURCE) == GPIO_PIN_SOURCE3) || ((PINSOURCE) == GPIO_PIN_SOURCE4) || ((PINSOURCE) == GPIO_PIN_SOURCE5)    \
     || ((PINSOURCE) == GPIO_PIN_SOURCE6) || ((PINSOURCE) == GPIO_PIN_SOURCE7) || ((PINSOURCE) == GPIO_PIN_SOURCE8)    \
     || ((PINSOURCE) == GPIO_PIN_SOURCE9) || ((PINSOURCE) == GPIO_PIN_SOURCE10) || ((PINSOURCE) == GPIO_PIN_SOURCE11)  \
     || ((PINSOURCE) == GPIO_PIN_SOURCE12) || ((PINSOURCE) == GPIO_PIN_SOURCE13) || ((PINSOURCE) == GPIO_PIN_SOURCE14) \
     || ((PINSOURCE) == GPIO_PIN_SOURCE15))

/**
 * @}
 */

/** @addtogroup Ethernet_Media_Interface
 * @{
 */
#define GPIO_ETH_MII_CFG  ((uint32_t)0x00000000)
#define GPIO_ETH_RMII_CFG ((uint32_t)0x00800000)

#define IS_GPIO_ETH_MEDIA_INTERFACE(INTERFACE) (((INTERFACE) == GPIO_ETH_MII_CFG) || ((INTERFACE) == GPIO_ETH_RMII_CFG))

/**
 * @}
 */
/**
 * @}
 */

/** @addtogroup GPIO_Exported_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup GPIO_Exported_Functions
 * @{
 */

void GPIO_DeInit(GPIO_Module* GPIOx);
void GPIO_AFIOInitDefault(void);
void GPIO_InitPeripheral(GPIO_Module* GPIOx, GPIO_InitType* GPIO_InitStruct);
void GPIO_InitStruct(GPIO_InitType* GPIO_InitStruct);
uint8_t GPIO_ReadInputDataBit(GPIO_Module* GPIOx, uint16_t Pin);
uint16_t GPIO_ReadInputData(GPIO_Module* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_Module* GPIOx, uint16_t Pin);
uint16_t GPIO_ReadOutputData(GPIO_Module* GPIOx);
void GPIO_SetBits(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_ResetBits(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_WriteBit(GPIO_Module* GPIOx, uint16_t Pin, Bit_OperateType BitCmd);
void GPIO_Write(GPIO_Module* GPIOx, uint16_t PortVal);
void GPIO_ConfigPinLock(GPIO_Module* GPIOx, uint16_t Pin);
void GPIO_ConfigEventOutput(uint8_t PortSource, uint8_t PinSource);
void GPIO_CtrlEventOutput(FunctionalState Cmd);
void GPIO_ConfigPinRemap(uint32_t RmpPin, FunctionalState Cmd);
void GPIO_ConfigEXTILine(uint8_t PortSource, uint8_t PinSource);
void GPIO_ETH_ConfigMediaInterface(uint32_t ETH_ConfigSel);
void GPIO_SetBitsHigh16(GPIO_Module* GPIOx, uint32_t Pin);

#ifdef __cplusplus
}
#endif

#endif /* __N32G45X_GPIO_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
