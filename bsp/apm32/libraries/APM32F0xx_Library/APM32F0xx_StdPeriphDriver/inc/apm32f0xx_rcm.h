/*!
 * @file        apm32f0xx_rcm.h
 *
 * @brief       This file contains all the functions prototypes for the RCM firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-02-21
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#ifndef __APM32F0XX_RCM_H
#define __APM32F0XX_RCM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "apm32f0xx.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup RCM_Driver RCM Driver
  @{
*/

/** @defgroup RCM_Macros Macros
  @{
*/

/**@} end of group RCM_Macros*/

/** @defgroup RCM_Enumerations Enumerations
  @{
*/

/**
 * @brief   HSE enum
 */
typedef enum
{
    RCM_HSE_CLOSE = 0x00, /*!< turn OFF the HSE oscillator */
    RCM_HSE_OPEN  = 0x01, /*!< turn ON the HSE oscillator */
    RCM_HSE_BYPASS = 0x05, /*!< HSE oscillator bypassed with external clock */
} RCM_HSE_T;

/**
 * @brief   LSE enum
 */
typedef enum
{
    RCM_LSE_CLOSE = 0x00, /*!< turn OFF the LSE oscillator */
    RCM_LSE_OPEN  = 0x01, /*!< turn ON the LSE oscillator */
    RCM_LSE_BYPASS = 0x05, /*!< LSE oscillator bypassed with external clock */
} RCM_LSE_T;

/**
 * @brief   LSE_Drive enum
 */
typedef enum
{
    RCM_LSE_DRIVE_Low = 0x00, /*!< LSE oscillator low drive capability */
    RCM_LSE_DRIVE_MediumLow,  /*!< LSE oscillator medium low drive capability */
    RCM_LSE_DRIVE_MediumHigh, /*!< LSE oscillator medium high drive capability */
    RCM_LSE_DRIVE_High,       /*!< LSE oscillator high drive capability */
} RCM_LSE_DRIVE_T;

/**
 * @brief   System clock select
 */
typedef enum
{
    RCM_PLL_SEL_HSI_DIV2, /*!< HSI clock divided by 2 selected as PLL clock source */
    RCM_PLL_SEL_HSI,      /*!< HSI clock selected as PLL clock entry, only for APM32F072 and APM32F091 devices */
    RCM_PLL_SEL_HSE,      /*!< HSE/CLKDIV1 selected as PLL clock entry */
    RCM_PLL_SEL_HSI48     /*!< HSI48 oscillator clock selected as PLL clock source, only for APM32F072 and APM32F091 devices */
} RCM_PLL_SEL_T;

/**
 * @brief   PLL multiplication factor
 */
typedef enum
{
    RCM_PLLMF_2,  /*!< specifies the PLLMULCFG clock multiple factor as 2 */
    RCM_PLLMF_3,  /*!< specifies the PLLMULCFG clock multiple factor as 3 */
    RCM_PLLMF_4,  /*!< specifies the PLLMULCFG clock multiple factor as 4 */
    RCM_PLLMF_5,  /*!< specifies the PLLMULCFG clock multiple factor as 5 */
    RCM_PLLMF_6,  /*!< specifies the PLLMULCFG clock multiple factor as 6 */
    RCM_PLLMF_7,  /*!< specifies the PLLMULCFG clock multiple factor as 7 */
    RCM_PLLMF_8,  /*!< specifies the PLLMULCFG clock multiple factor as 8 */
    RCM_PLLMF_9,  /*!< specifies the PLLMULCFG clock multiple factor as 9 */
    RCM_PLLMF_10, /*!< specifies the PLLMULCFG clock multiple factor as 10 */
    RCM_PLLMF_11, /*!< specifies the PLLMULCFG clock multiple factor as 11 */
    RCM_PLLMF_12, /*!< specifies the PLLMULCFG clock multiple factor as 12 */
    RCM_PLLMF_13, /*!< specifies the PLLMULCFG clock multiple factor as 13 */
    RCM_PLLMF_14, /*!< specifies the PLLMULCFG clock multiple factor as 14 */
    RCM_PLLMF_15, /*!< specifies the PLLMULCFG clock multiple factor as 15 */
    RCM_PLLMF_16, /*!< specifies the PLLMULCFG clock multiple factor as 16 */
} RCM_PLLMF_T;

/**
 * @brief   RCM clock division
 */
typedef enum
{
    RCM_CLK_DIV_1,  /*!< specifies the PLLDIVCFG clock division factor as 1 */
    RCM_CLK_DIV_2,  /*!< specifies the PLLDIVCFG clock division factor as 2 */
    RCM_CLK_DIV_3,  /*!< specifies the PLLDIVCFG clock division factor as 3 */
    RCM_CLK_DIV_4,  /*!< specifies the PLLDIVCFG clock division factor as 4 */
    RCM_CLK_DIV_5,  /*!< specifies the PLLDIVCFG clock division factor as 5 */
    RCM_CLK_DIV_6,  /*!< specifies the PLLDIVCFG clock division factor as 6 */
    RCM_CLK_DIV_7,  /*!< specifies the PLLDIVCFG clock division factor as 7 */
    RCM_CLK_DIV_8,  /*!< specifies the PLLDIVCFG clock division factor as 8 */
    RCM_CLK_DIV_9,  /*!< specifies the PLLDIVCFG clock division factor as 9 */
    RCM_CLK_DIV_10, /*!< specifies the PLLDIVCFG clock division factor as 10 */
    RCM_CLK_DIV_11, /*!< specifies the PLLDIVCFG clock division factor as 11 */
    RCM_CLK_DIV_12, /*!< specifies the PLLDIVCFG clock division factor as 12 */
    RCM_CLK_DIV_13, /*!< specifies the PLLDIVCFG clock division factor as 13 */
    RCM_CLK_DIV_14, /*!< specifies the PLLDIVCFG clock division factor as 14 */
    RCM_CLK_DIV_15, /*!< specifies the PLLDIVCFG clock division factor as 15 */
    RCM_CLK_DIV_16, /*!< specifies the PLLDIVCFG clock division factor as 16 */
} RCM_CLK_DIV_T;

/**
 * @brief   Clock output control
 */
typedef enum
{
    RCM_COC_NO_CLOCK,     /*!< No clock selected */
    RCM_COC_HSI14,        /*!< HSI14 oscillator clock selected */
    RCM_COC_LSI,          /*!< LSI oscillator clock selected */
    RCM_COC_LSE,          /*!< LSE oscillator clock selected */
    RCM_COC_SYSCLK,       /*!< System clock selected */
    RCM_COC_HSI,          /*!< HSI oscillator clock selected */
    RCM_COC_HSE,          /*!< HSE oscillator clock selected */
    RCM_COC_PLLCLK_DIV_2, /*!< PLL clock divided by 2 selected */
    RCM_COC_HSI48,        /*!< HSI48 oscillator clock selected, only for APM32F072 and APM32F091 devices */
    RCM_COC_PLLCLK        /*!< PLL clock selected */
} RCM_COCCLK_T;

/**
 * @brief   Clock output division
 */
typedef enum
{
    RCM_COC_DIV_1,   /*!< MCOSEL clock is divided by 1 */
    RCM_COC_DIV_2,   /*!< MCOSEL clock is divided by 2 */
    RCM_COC_DIV_4,   /*!< MCOSEL clock is divided by 4 */
    RCM_COC_DIV_8,   /*!< MCOSEL clock is divided by 8 */
    RCM_COC_DIV_16,  /*!< MCOSEL clock is divided by 16 */
    RCM_COC_DIV_32,  /*!< MCOSEL clock is divided by 32 */
    RCM_COC_DIV_64,  /*!< MCOSEL clock is divided by 64 */
    RCM_COC_DIV_128, /*!< MCOSEL clock is divided by 128 */
} RCM_COCPRE_T;

/**
 * @brief   System clock select
 */
typedef enum
{
    RCM_SYSCLK_SEL_HSI,     /*!< HSI selected as system clock source */
    RCM_SYSCLK_SEL_HSE,     /*!< HSE selected as system clock source */
    RCM_SYSCLK_SEL_PLL,     /*!< PLL selected as system clock source */
    RCM_SYSCLK_SEL_HSI48,   /*!< HSI48 selected as system clock source, only for APM32F072 and APM32F091 devices */
} RCM_SYSCLK_SEL_T;

/**
 * @brief   AHB divider Number
 */
typedef enum
{
    RCM_SYSCLK_DIV_1 = 7, /*!< AHB clock = SYSCLK */
    RCM_SYSCLK_DIV_2,     /*!< AHB clock = SYSCLK/2 */
    RCM_SYSCLK_DIV_4,     /*!< AHB clock = SYSCLK/4 */
    RCM_SYSCLK_DIV_8,     /*!< AHB clock = SYSCLK/8 */
    RCM_SYSCLK_DIV_16,    /*!< AHB clock = SYSCLK/16 */
    RCM_SYSCLK_DIV_64,    /*!< AHB clock = SYSCLK/64 */
    RCM_SYSCLK_DIV_128,   /*!< AHB clock = SYSCLK/128 */
    RCM_SYSCLK_DIV_256,   /*!< AHB clock = SYSCLK/256 */
    RCM_SYSCLK_DIV_512,   /*!< AHB clock = SYSCLK/512 */
} RCM_AHBDIV_T;

/**
 * @brief   APB divider Number
 */
typedef enum
{
    RCM_HCLK_DIV_1 = 3,  /*!< APB clock = HCLK */
    RCM_HCLK_DIV_2,      /*!< APB clock = HCLK/2 */
    RCM_HCLK_DIV_4,      /*!< APB clock = HCLK/4 */
    RCM_HCLK_DIV_8,      /*!< APB clock = HCLK/8 */
    RCM_HCLK_DIV_16      /*!< APB clock = HCLK/16 */
} RCM_APBDIV_T;

/**
 * @brief   CEC divider Number
 */
typedef enum
{
    RCM_CECCLK_HSI_DIV_224, /*!< CEC clock = HSI/244 (32768Hz) */
    RCM_CECCLK_LSI_DIV,     /*!< CEC clock = LSI */
} RCM_CECCLK_T;

/**
 * @brief   I2C clock source selectio
 */
typedef enum
{
    RCM_I2C1CLK_HSI,    /*!< I2C1 clock = HSI */
    RCM_I2C1CLK_SYSCLK, /*!< I2C1 clock = System Clock */
} RCM_I2CCLK_T;

/**
 * @brief   USART clock source selectio
 */
typedef enum
{
    RCM_USART1CLK_PCLK    = ((uint32_t)0x00010000),    /*!< USART1 clock = APB Clock (PCLK) */
    RCM_USART1CLK_SYSCLK  = ((uint32_t)0x00010001),    /*!< USART1 clock = System Clock */
    RCM_USART1CLK_LSE     = ((uint32_t)0x00010002),    /*!< USART1 clock = LSE Clock */
    RCM_USART1CLK_HSI     = ((uint32_t)0x00010003),    /*!< USART1 clock = HSI Clock */
    RCM_USART2CLK_PCLK    = ((uint32_t)0x00020000),    /*!< USART2 clock = APB Clock (PCLK), only for APM32F072 and APM32F091 devices */
    RCM_USART2CLK_SYSCLK  = ((uint32_t)0x00020001),    /*!< USART2 clock = System Clock, only for APM32F072 and APM32F091 devices */
    RCM_USART2CLK_LSE     = ((uint32_t)0x00020002),    /*!< USART2 clock = LSE Clock, only for APM32F072 and APM32F091 devices */
    RCM_USART2CLK_HSI     = ((uint32_t)0x00020003),    /*!< USART2 clock = HSI Clock, only for APM32F072 and APM32F091 devices */
    RCM_USART3CLK_PCLK    = ((uint32_t)0x00040000),    /*!< USART3 clock = APB Clock (PCLK), only for APM32F091 devices */
    RCM_USART3CLK_SYSCLK  = ((uint32_t)0x00040001),    /*!< USART3 clock = System Clock, only for APM32F091 devices */
    RCM_USART3CLK_LSE     = ((uint32_t)0x00040002),    /*!< USART3 clock = LSE Clock, only for APM32F091 devices */
    RCM_USART3CLK_HSI     = ((uint32_t)0x00040003),    /*!< USART3 clock = HSI Clock, only for APM32F091 devices */
} RCM_USARTCLK_T;

/**
 * @brief    USB clock source selection
 */
typedef enum
{
    RCM_USBCLK_HSI48,  /*!<hsi48 selected as USB clock, only for APM32F072 devices */
    RCM_USBCLK_PLLCLK,  /*!<PLL clock selected as USB clock, only for APM32F072 devices */
} RCM_USBCLK_T;

/**
 * @brief   RTC clock select
 */
typedef enum
{
    RCM_RTCCLK_LSE = 0X01, /*!< LSE selected as RTC clock */
    RCM_RTCCLK_LSI,        /*!< LSI selected as RTC clock */
    RCM_RTCCLK_HSE_DIV_32  /*!< HSE divided by 32 selected as RTC clock */
} RCM_RTCCLK_T;

/**
 * @brief   AHB peripheral
 */
typedef enum
{
    RCM_AHB_PERIPH_DMA1     = BIT0,  /*!< DMA1 peripheral clock */
    RCM_AHB_PERIPH_DMA2     = BIT1,  /*!< DMA2 peripheral clock */
    RCM_AHB_PERIPH_SRAM     = BIT2,  /*!< SRAM peripheral clock */
    RCM_AHB_PERIPH_FPU      = BIT4,  /*!< FMC peripheral clock */
    RCM_AHB_PERIPH_CRC      = BIT6,  /*!< CRC peripheral clock */
    RCM_AHB_PERIPH_GPIOA    = BIT17, /*!< GPIOA peripheral clock */
    RCM_AHB_PERIPH_GPIOB    = BIT18, /*!< GPIOB peripheral clock */
    RCM_AHB_PERIPH_GPIOC    = BIT19, /*!< GPIOC peripheral clock */
    RCM_AHB_PERIPH_GPIOD    = BIT20, /*!< GPIOD peripheral clock */
    RCM_AHB_PERIPH_GPIOE    = BIT21, /*!< GPIOE peripheral clock, only for APM32F072 and APM32F091 devices */
    RCM_AHB_PERIPH_GPIOF    = BIT22, /*!< GPIOF peripheral clock */
    RCM_AHB_PERIPH_TSC      = BIT24, /*!< TSC peripheral clock */
} RCM_AHB_PERIPH_T;

/**
 * @brief   AHB2 peripheral
 */
typedef enum
{
    RCM_APB2_PERIPH_SYSCFG  = BIT0,  /*!< SYSCFG peripheral clock */
    RCM_APB2_PERIPH_USART6  = BIT5,  /*!< USART6 peripheral clock */
    RCM_APB2_PERIPH_USART7  = BIT6,  /*!< USART7 peripheral clock */
    RCM_APB2_PERIPH_USART8  = BIT7,  /*!< USART8 peripheral clock */
    RCM_APB2_PERIPH_ADC1    = BIT9,  /*!< ADC1 peripheral clock */
    RCM_APB2_PERIPH_TMR1    = BIT11, /*!< TMR1 peripheral clock */
    RCM_APB2_PERIPH_SPI1    = BIT12, /*!< SPI1 peripheral clock */
    RCM_APB2_PERIPH_USART1  = BIT14, /*!< USART1 peripheral clock */
    RCM_APB2_PERIPH_TMR15   = BIT16, /*!< TMR15 peripheral clock */
    RCM_APB2_PERIPH_TMR16   = BIT17, /*!< TMR16 peripheral clock */
    RCM_APB2_PERIPH_TMR17   = BIT18, /*!< TMR17 peripheral clock */
    RCM_APB2_PERIPH_DBGMCU  = BIT22, /*!< DBGMCU peripheral clock */
} RCM_APB2_PERIPH_T;

/**
 * @brief   AHB1 peripheral
 */
typedef enum
{
    RCM_APB1_PERIPH_TMR2    = BIT0,  /*!< TMR2 peripheral clock, only for APM32F072 and APM32F091 devices */
    RCM_APB1_PERIPH_TMR3    = BIT1,  /*!< TMR3 peripheral clock */
    RCM_APB1_PERIPH_TMR6    = BIT4,  /*!< TMR6 peripheral clock */
    RCM_APB1_PERIPH_TMR7    = BIT5,  /*!< TMR7 peripheral clock, only for APM32F072 and APM32F091 devices */
    RCM_APB1_PERIPH_TMR14   = BIT8,  /*!< TMR14 peripheral clock */
    RCM_APB1_PERIPH_WWDT    = BIT11, /*!< WWDT peripheral clock */
    RCM_APB1_PERIPH_SPI2    = BIT14, /*!< SPI2 peripheral clock */
    RCM_APB1_PERIPH_USART2  = BIT17, /*!< USART2 peripheral clock */
    RCM_APB1_PERIPH_USART3  = BIT18, /*!< USART3 peripheral clock, only for APM32F072 and APM32F091 devices */
    RCM_APB1_PERIPH_USART4  = BIT19, /*!< USART4 peripheral clock, only for APM32F072 and APM32F091 devices */
    RCM_APB1_PERIPH_USART5  = BIT20, /*!< USART5 peripheral clock, only for APM32F091 devices */
    RCM_APB1_PERIPH_I2C1    = BIT21, /*!< I2C1 peripheral clock */
    RCM_APB1_PERIPH_I2C2    = BIT22, /*!< I2C2 peripheral clock */
    RCM_APB1_PERIPH_USB     = BIT23, /*!< USB peripheral clock only for APM32F072 devices */
    RCM_APB1_PERIPH_CAN     = BIT25, /*!< CAN peripheral clock, only for APM32F072 and APM32F091 devices */
    RCM_APB1_PERIPH_CRS     = BIT27, /*!< CRS peripheral clock, only for APM32F072 and APM32F091 devices */
    RCM_APB1_PERIPH_PMU     = BIT28, /*!< PMU peripheral clock */
    RCM_APB1_PERIPH_DAC     = BIT29, /*!< DAC peripheral clock, only for APM32F072 and APM32F091 devices */
    RCM_APB1_PERIPH_CEC     = BIT30, /*!< CEC peripheral clock, only for APM32F072 and APM32F091 devices */
} RCM_APB1_PERIPH_T;

/**
 * @brief   RCM Interrupt Source
 */
typedef enum
{
    RCM_INT_LSIRDY      = BIT0,      /*!< LSI ready interrupt */
    RCM_INT_LSERDY      = BIT1,      /*!< LSE ready interrupt */
    RCM_INT_HSIRDY      = BIT2,      /*!< HSI ready interrupt */
    RCM_INT_HSERDY      = BIT3,      /*!< HSE ready interrupt */
    RCM_INT_PLLRDY      = BIT4,      /*!< PLL ready interrupt */
    RCM_INT_HSI14RDY    = BIT5,      /*!< HSI14 ready interrupt */
    RCM_INT_HSI48RDY    = BIT6,      /*!< HSI48 ready interrupt (Only for APM32F072 and APM32F091 devices) */
    RCM_INT_CSS         = BIT7       /*!< Clock security system interrupt */
} RCM_INT_T;

/**
 * @brief   RCM FLAG define
 */
typedef enum
{
    RCM_FLAG_HSIRDY     = 0x001,      /*!< HSI Ready Flag */
    RCM_FLAG_HSERDY     = 0x011,      /*!< HSE Ready Flag */
    RCM_FLAG_PLLRDY     = 0x019,      /*!< PLL Ready Flag */
    RCM_FLAG_LSERDY     = 0x101,      /*!< LSE Ready Flag */
    RCM_FLAG_LSIRDY     = 0x201,      /*!< LSI Ready Flag */
    RCM_FLAG_V18PRRST   = 0x217,      /*!< Software reset flag */
    RCM_FLAG_OBRST      = 0x219,      /*!< Option byte loader reset flag */
    RCM_FLAG_PINRST     = 0x21A,      /*!< PIN reset flag */
    RCM_FLAG_PWRRST     = 0x21B,      /*!< POR/PDR reset flag */
    RCM_FLAG_SWRST      = 0x21C,      /*!< Software reset flag */
    RCM_FLAG_IWDTRST    = 0x21D,      /*!< Independent watchdog reset flag */
    RCM_FLAG_WWDTRST    = 0x21E,      /*!< Window watchdog reset flag */
    RCM_FLAG_LPRRST     = 0x21F,      /*!< Low-power reset flag */
    RCM_FLAG_HSI14RDY   = 0x301,      /*!< HSI14 Ready Flag */
    RCM_FLAG_HSI48RDY   = 0x311,      /*!< HSI48 Ready Flag (Only for APM32F072 devices and APM32F091 devices) */
} RCM_FLAG_T;

/**@} end of group RCM_Enumerations*/

/** @defgroup RCM_Structures Structures
  @{
*/

/**@} end of group RCM_Structures*/

/** @defgroup RCM_Variables Variables
  @{
*/

/**@} end of group RCM_Variables*/

/** @defgroup RCM_Fuctions Fuctions
  @{
*/

/** Function description */

void RCM_Reset(void);

void RCM_ConfigHSE(RCM_HSE_T state);
uint8_t RCM_WaitHSEReady(void);
void RCM_SetHSITrim(uint8_t HSITrim);
void RCM_EnableHSI(void);
void RCM_DisableHSI(void);

void RCM_SetHSI14Trim(uint8_t HSI14Trim);
void RCM_EnableHSI14(void);
void RCM_DisableHSI14(void);
void RCM_EnableHSI14ADC(void);
void RCM_DisableHSI14ADC(void);

void RCM_ConfigLSE(RCM_LSE_T state);
void RCM_ConfigDriveLSE(RCM_LSE_DRIVE_T state);

void RCM_EnableLSI(void);
void RCM_DisableLSI(void);

void RCM_ConfigPLL(RCM_PLL_SEL_T pllSelect, RCM_PLLMF_T pllMf);
void RCM_EnablePLL(void);
void RCM_DisablePLL(void);

void RCM_EnableHSI48(void);   /*!< Only for APM32F072 and APM32F091 devices */
void RCM_DisableHSI48(void);  /*!< Only for APM32F072 and APM32F091 devices */
uint32_t RCM_ReadHSI48CalibrationValue(void);  /*!< Only for APM32F072 and APM32F091 devices */

void RCM_ConfigCLKDIV(RCM_CLK_DIV_T state);

void RCM_EnableCCS(void);
void RCM_DisableCCS(void);

#if defined (APM32F030) || defined (APM32F051)
void RCM_ConfigCOC(RCM_COCCLK_T cocClock);
#else
void RCM_ConfigCOC(RCM_COCCLK_T cocClock, RCM_COCPRE_T divided);
#endif

void RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_T sysClkSelect);
RCM_SYSCLK_SEL_T RCM_ReadSYSCLKSource(void);

void RCM_ConfigAHB(RCM_AHBDIV_T AHBDiv);
void RCM_ConfigAPB(RCM_APBDIV_T APBDiv);
void RCM_ConfigCECCLK(RCM_CECCLK_T CECClk);
void RCM_ConfigI2CCLK(RCM_I2CCLK_T I2CCLk);
void RCM_ConfigUSARTCLK(RCM_USARTCLK_T USARTClk);
void RCM_ConfigUSBCLK(RCM_USBCLK_T USBClk);  /*!< Only for APM32F072 devices */

uint32_t RCM_ReadSYSCLKFreq(void);
uint32_t RCM_ReadHCLKFreq(void);
uint32_t RCM_ReadPCLKFreq(void);
uint32_t RCM_ReadADCCLKFreq(void);
uint32_t RCM_ReadCECCLKFreq(void);
uint32_t RCM_ReadI2C1CLKFreq(void);
uint32_t RCM_ReadUSART1CLKFreq(void);
uint32_t RCM_ReadUSART2CLKFreq(void);
uint32_t RCM_ReadUSBCLKFreq(void);

void RCM_ConfigRTCCLK(RCM_RTCCLK_T RTCClk);
void RCM_EnableRTCCLK(void);
void RCM_DisableRTCCLK(void);

void RCM_EnableBackupReset(void);
void RCM_DisableBackupReset(void);

void RCM_EnableAHBPeriphClock(uint32_t AHBPeriph);
void RCM_DisableAHBPeriphClock(uint32_t AHBPeriph);
void RCM_EnableAPB2PeriphClock(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphClock(uint32_t APB2Periph);
void RCM_EnableAPB1PeriphClock(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphClock(uint32_t APB1Periph);

void RCM_EnableAHBPeriphReset(uint32_t AHBPeriph);
void RCM_DisableAHBPeriphReset(uint32_t AHBPeriph);
void RCM_EnableAPB1PeriphReset(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphReset(uint32_t APB1Periph);
void RCM_EnableAPB2PeriphReset(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphReset(uint32_t APB2Periph);

void RCM_EnableInterrupt(uint8_t interrupt);
void RCM_DisableInterrupt(uint8_t interrupt);
uint16_t RCM_ReadStatusFlag(RCM_FLAG_T flag);
void RCM_ClearStatusFlag(void);
uint8_t RCM_ReadIntFlag(RCM_INT_T flag);
void RCM_ClearIntFlag(uint8_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F0XX_RCM_H */

/**@} end of group RCM_Functions*/
/**@} end of group RCM_Driver*/
/**@} end of group APM32F0xx_StdPeriphDriver*/
