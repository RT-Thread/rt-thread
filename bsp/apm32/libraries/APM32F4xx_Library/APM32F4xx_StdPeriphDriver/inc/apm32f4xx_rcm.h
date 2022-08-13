/*!
 * @file        apm32f4xx_rcm.h
 *
 * @brief       This file contains all the functions prototypes for the RCM firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F4XX_RCM_H
#define __APM32F4XX_RCM_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup RCM_Driver
  @{
*/

/** @defgroup RCM_Enumerations
  @{
*/

/**
 * @brief HSE state
 */
typedef enum
{
    RCM_HSE_CLOSE,    /*!< Turn off the HSE oscillator */
    RCM_HSE_OPEN,     /*!< Turn on the HSE oscillator */
    RCM_HSE_BYPASS    /*!< HSE oscillator bypassed with external clock */
} RCM_HSE_T;

/**
 * @brief LSE State
 */
typedef enum
{
    RCM_LSE_CLOSE,  /*!< Close the LSE */
    RCM_LSE_OPEN,   /*!< Open the LSE */
    RCM_LSE_BYPASS  /*!< LSE bypass */
} RCM_LSE_T;

/**
 * @brief RCM PLL source select
 */
typedef enum
{
    RCM_PLLSEL_HSI, /*!< HSI oscillator clock selected as PLL clock entry */
    RCM_PLLSEL_HSE  /*!< HSE oscillator clock selected as PLL clock entry */
} RCM_PLLSEL_T;

/**
 * @brief RCM PLL System Division
 */
typedef enum
{
    RCM_PLL_SYS_DIV_2,  /*!< System clock Division factor is 2 */
    RCM_PLL_SYS_DIV_4,  /*!< System clock Division factor is 4 */
    RCM_PLL_SYS_DIV_6,  /*!< System clock Division factor is 6 */
    RCM_PLL_SYS_DIV_8   /*!< System clock Division factor is 8 */
} RCM_PLL_SYS_DIV_T;

/**
 * @brief RCM MCO1 Source Selece
 */
typedef enum
{
    RCM_MCO1_SEL_HSICLK,    /*!< HSI clock selected as MCO1 source */
    RCM_MCO1_SEL_LSECLK,    /*!< LSE clock selected as MCO1 source */
    RCM_MCO1_SEL_HSECLK,    /*!< HSE clock selected as MCO1 source */
    RCM_MCO1_SEL_PLLCLK     /*!< Main PLL clock selected as MCO1 source */
} RCM_MCO1_SEL_T;

/**
 * @brief RCM MCO1 Div
 */
typedef enum
{
    RCM_MCO1_DIV_1,     /*!< No division applied to MCO1 clock */
    RCM_MCO1_DIV_2 = 4, /*!< Division by 2 applied to MCO1 clock */
    RCM_MCO1_DIV_3,     /*!< Division by 3 applied to MCO1 clock */
    RCM_MCO1_DIV_4,     /*!< Division by 4 applied to MCO1 clock */
    RCM_MCO1_DIV_5      /*!< Division by 5 applied to MCO1 clock */
} RCM_MCO1_DIV_T;

/**
 * @brief RCM MCO2 Source Selece
 */
typedef enum
{
    RCM_MCO2_SEL_SYSCLK,    /*!< SYS clock selected as MCO2 source */
    RCM_MCO2_SEL_PLL2CLK,   /*!< PLL2 clock selected as MCO2 source */
    RCM_MCO2_SEL_HSECLK,    /*!< HSE clock selected as MCO2 source */
    RCM_MCO2_SEL_PLLCLK     /*!< PLL clock selected as MCO2 source */
} RCM_MCO2_SEL_T;

/**
 * @brief RCM MCO2 Division
 */
typedef enum
{
    RCM_MCO2_DIV_1,         /*!< No division applied to MCO2 clock */
    RCM_MCO2_DIV_2 = 4,     /*!< Division by 2 applied to MCO2 clock */
    RCM_MCO2_DIV_3,         /*!< Division by 3 applied to MCO2 clock */
    RCM_MCO2_DIV_4,         /*!< Division by 4 applied to MCO2 clock */
    RCM_MCO2_DIV_5          /*!< Division by 5 applied to MCO2 clock */
} RCM_MCO2_DIV_T;

/**
 * @brief System clock select
 */
typedef enum
{
    RCM_SYSCLK_SEL_HSI, /*!< HSI is selected as system clock source */
    RCM_SYSCLK_SEL_HSE, /*!< HSE is selected as system clock source */
    RCM_SYSCLK_SEL_PLL  /*!< PLL is selected as system clock source */
} RCM_SYSCLK_SEL_T;

/**
 * @brief AHB divider Number
 */
typedef enum
{
    RCM_AHB_DIV_1 = 7,  /*!< HCLK = SYSCLK */
    RCM_AHB_DIV_2,      /*!< HCLK = SYSCLK / 2 */
    RCM_AHB_DIV_4,      /*!< HCLK = SYSCLK / 4 */
    RCM_AHB_DIV_8,      /*!< HCLK = SYSCLK / 8 */
    RCM_AHB_DIV_16,     /*!< HCLK = SYSCLK / 16 */
    RCM_AHB_DIV_64,     /*!< HCLK = SYSCLK / 64 */
    RCM_AHB_DIV_128,    /*!< HCLK = SYSCLK / 128 */
    RCM_AHB_DIV_256,    /*!< HCLK = SYSCLK / 256 */
    RCM_AHB_DIV_512     /*!< HCLK = SYSCLK / 512 */
} RCM_AHB_DIV_T;

/**
 * @brief APB divider Number
 */
typedef enum
{
    RCM_APB_DIV_1 = 3,  /*!< PCLK1 = HCLK */
    RCM_APB_DIV_2,      /*!< PCLK1 = HCLK / 2 */
    RCM_APB_DIV_4,      /*!< PCLK1 = HCLK / 4 */
    RCM_APB_DIV_8,      /*!< PCLK1 = HCLK / 8 */
    RCM_APB_DIV_16      /*!< PCLK1 = HCLK / 16 */
} RCM_APB_DIV_T;

/**
 * @brief SDRAM divider Number
 */
typedef enum
{
    RCM_SDRAM_DIV_1 = 0,    /*!< SDRAM clock = DMC clock */
    RCM_SDRAM_DIV_2 = 1,    /*!< SDRAM clock = DMC clock / 2 */
    RCM_SDRAM_DIV_4 = 2,    /*!< SDRAM clock = DMC clock / 4 */
} RCM_SDRAM_DIV_T;

/**
 * @brief RTC clock select
 */
typedef enum
{
    RCM_RTCCLK_LSE,         /*!< RTCCLK = LSE clock */
    RCM_RTCCLK_LSI,         /*!< RTCCLK = LSI clock */
    RCM_RTCCLK_HSE_DIV2,    /*!< RTCCLK = HSE / 2 */
    RCM_RTCCLK_HSE_DIV3,    /*!< RTCCLK = HSE / 3 */
    RCM_RTCCLK_HSE_DIV4,    /*!< RTCCLK = HSE / 4 */
    RCM_RTCCLK_HSE_DIV5,    /*!< RTCCLK = HSE / 5 */
    RCM_RTCCLK_HSE_DIV6,    /*!< RTCCLK = HSE / 6 */
    RCM_RTCCLK_HSE_DIV7,    /*!< RTCCLK = HSE / 7 */
    RCM_RTCCLK_HSE_DIV8,    /*!< RTCCLK = HSE / 8 */
    RCM_RTCCLK_HSE_DIV9,    /*!< RTCCLK = HSE / 9 */
    RCM_RTCCLK_HSE_DIV10,   /*!< RTCCLK = HSE / 10 */
    RCM_RTCCLK_HSE_DIV11,   /*!< RTCCLK = HSE / 11 */
    RCM_RTCCLK_HSE_DIV12,   /*!< RTCCLK = HSE / 12 */
    RCM_RTCCLK_HSE_DIV13,   /*!< RTCCLK = HSE / 13 */
    RCM_RTCCLK_HSE_DIV14,   /*!< RTCCLK = HSE / 14 */
    RCM_RTCCLK_HSE_DIV15,   /*!< RTCCLK = HSE / 15 */
    RCM_RTCCLK_HSE_DIV16,   /*!< RTCCLK = HSE / 16 */
    RCM_RTCCLK_HSE_DIV17,   /*!< RTCCLK = HSE / 17 */
    RCM_RTCCLK_HSE_DIV18,   /*!< RTCCLK = HSE / 18 */
    RCM_RTCCLK_HSE_DIV19,   /*!< RTCCLK = HSE / 19 */
    RCM_RTCCLK_HSE_DIV20,   /*!< RTCCLK = HSE / 20 */
    RCM_RTCCLK_HSE_DIV21,   /*!< RTCCLK = HSE / 21 */
    RCM_RTCCLK_HSE_DIV22,   /*!< RTCCLK = HSE / 22 */
    RCM_RTCCLK_HSE_DIV23,   /*!< RTCCLK = HSE / 23 */
    RCM_RTCCLK_HSE_DIV24,   /*!< RTCCLK = HSE / 24 */
    RCM_RTCCLK_HSE_DIV25,   /*!< RTCCLK = HSE / 25 */
    RCM_RTCCLK_HSE_DIV26,   /*!< RTCCLK = HSE / 26 */
    RCM_RTCCLK_HSE_DIV27,   /*!< RTCCLK = HSE / 27 */
    RCM_RTCCLK_HSE_DIV28,   /*!< RTCCLK = HSE / 28 */
    RCM_RTCCLK_HSE_DIV29,   /*!< RTCCLK = HSE / 29 */
    RCM_RTCCLK_HSE_DIV30,   /*!< RTCCLK = HSE / 30 */
    RCM_RTCCLK_HSE_DIV31    /*!< RTCCLK = HSE / 31 */
} RCM_RTCCLK_T;

/**
 * @brief I2S Clock Source
 */
typedef enum
{
    RCM_I2S_CLK_PLLI2S, /*!< PLLI2S is selected as I2S clock source */
    RCM_I2S_CLK_EXT     /*!< EXT is selected as I2S clock source */
} RCM_I2S_CLK_T;

/**
 * @brief RCM Interrupt Source
 */
typedef enum
{
    RCM_INT_LSIRDY   = BIT0, /*!< LSI ready interrupt */
    RCM_INT_LSERDY   = BIT1, /*!< LSE ready interrupt */
    RCM_INT_HSIRDY   = BIT2, /*!< HSI ready interrupt */
    RCM_INT_HSERDY   = BIT3, /*!< HSE ready interrupt */
    RCM_INT_PLL1RDY  = BIT4, /*!< PLL1 ready interrupt */
    RCM_INT_PLL2RDY  = BIT5, /*!< PLL2 ready interrupt */
    RCM_INT_CSS      = BIT7  /*!< Clock security system interrupt */
} RCM_INT_T;

/**
 * @brief AHB1 peripheral
 */
typedef enum
{
    RCM_AHB1_PERIPH_GPIOA        = BIT0,    /*!< Select GPIOA clock */
    RCM_AHB1_PERIPH_GPIOB        = BIT1,    /*!< Select GPIOB clock */
    RCM_AHB1_PERIPH_GPIOC        = BIT2,    /*!< Select GPIOC clock */
    RCM_AHB1_PERIPH_GPIOD        = BIT3,    /*!< Select GPIOD clock */
    RCM_AHB1_PERIPH_GPIOE        = BIT4,    /*!< Select GPIOE clock */
    RCM_AHB1_PERIPH_GPIOF        = BIT5,    /*!< Select GPIOF clock */
    RCM_AHB1_PERIPH_GPIOG        = BIT6,    /*!< Select GPIOG clock */
    RCM_AHB1_PERIPH_GPIOH        = BIT7,    /*!< Select GPIOH clock */
    RCM_AHB1_PERIPH_GPIOI        = BIT8,    /*!< Select GPIOI clock */
    RCM_AHB1_PERIPH_GPIOJ        = BIT9,    /*!< Select GPIOJ clock */
    RCM_AHB1_PERIPH_GPIOK        = BIT10,   /*!< Select GPIOK clock */
    RCM_AHB1_PERIPH_CRC          = BIT12,   /*!< Select CRC clock */
    RCM_AHB1_PERIPH_FLITF        = BIT15,   /*!< Select FLITF clock */
    RCM_AHB1_PERIPH_SRAM1        = BIT16,   /*!< Select SRAM1 clock */
    RCM_AHB1_PERIPH_SRAM2        = BIT17,   /*!< Select SRAM2 clock */
    RCM_AHB1_PERIPH_BKPSRAM      = BIT18,   /*!< Select BKPSRAM clock */
    RCM_AHB1_PERIPH_SRAM3        = BIT19,   /*!< Select SRAM3 clock */
    RCM_AHB1_PERIPH_CCMDATARAMEN = BIT20,   /*!< Select CCMDATARAMEN clock */
    RCM_AHB1_PERIPH_DMA1         = BIT21,   /*!< Select DMA1 clock */
    RCM_AHB1_PERIPH_DMA2         = BIT22,   /*!< Select DMA2 clock */
    RCM_AHB1_PERIPH_ETH_MAC      = BIT25,   /*!< Select ETH MAC clock */
    RCM_AHB1_PERIPH_ETH_MAC_Tx   = BIT26,   /*!< Select ETH MAC TX clock */
    RCM_AHB1_PERIPH_ETH_MAC_Rx   = BIT27,   /*!< Select ETH MAC RX clock */
    RCM_AHB1_PERIPH_ETH_MAC_PTP  = BIT28,   /*!< Select ETH MAC PTP clock */
    RCM_AHB1_PERIPH_OTG_HS       = BIT29,   /*!< Select OTG HS clock */
    RCM_AHB1_PERIPH_OTG_HS_ULPI  = BIT30    /*!< Select OTG HS ULPI clock */
} RCM_AHB1_PERIPH_T;

/**
 * @brief AHB2 peripheral
 */
typedef enum
{
    RCM_AHB2_PERIPH_DCI    = BIT0,  /*!< Select DCI clock */
    RCM_AHB2_PERIPH_FPU    = BIT1,  /*!< Select FPU clock */
    RCM_AHB2_PERIPH_BN     = BIT2,  /*!< Select BN clock */
    RCM_AHB2_PERIPH_SM     = BIT3,  /*!< Select SM clock */
    RCM_AHB2_PERIPH_CRYP   = BIT4,  /*!< Select CRYP clock */
    RCM_AHB2_PERIPH_HASH   = BIT5,  /*!< Select HASH clock */
    RCM_AHB2_PERIPH_RNG    = BIT6,  /*!< Select RNG clock */
    RCM_AHB2_PERIPH_OTG_FS = BIT7   /*!< Select OTG FS clock */
} RCM_AHB2_PERIPH_T;

/**
 * @brief APB1 peripheral
 */
typedef enum
{
    RCM_APB1_PERIPH_TMR2   = BIT0,              /*!< Select TMR2 clock */
    RCM_APB1_PERIPH_TMR3   = BIT1,              /*!< Select TMR3 clock */
    RCM_APB1_PERIPH_TMR4   = BIT2,              /*!< Select TMR4 clock */
    RCM_APB1_PERIPH_TMR5   = BIT3,              /*!< Select TMR5 clock */
    RCM_APB1_PERIPH_TMR6   = BIT4,              /*!< Select TMR6 clock */
    RCM_APB1_PERIPH_TMR7   = BIT5,              /*!< Select TMR7 clock */
    RCM_APB1_PERIPH_TMR12  = BIT6,              /*!< Select TMR12 clock */
    RCM_APB1_PERIPH_TMR13  = BIT7,              /*!< Select TMR13 clock */
    RCM_APB1_PERIPH_TMR14  = BIT8,              /*!< Select TMR14 clock */
    RCM_APB1_PERIPH_WWDT   = BIT11,             /*!< Select WWDT clock */
    RCM_APB1_PERIPH_SPI2   = BIT14,             /*!< Select SPI2 clock */
    RCM_APB1_PERIPH_SPI3   = BIT15,             /*!< Select SPI3 clock */
    RCM_APB1_PERIPH_USART2 = BIT17,             /*!< Select USART2 clock */
    RCM_APB1_PERIPH_USART3 = BIT18,             /*!< Select USART3 clock */
    RCM_APB1_PERIPH_UART4  = BIT19,             /*!< Select UART4 clock */
    RCM_APB1_PERIPH_UART5  = BIT20,             /*!< Select UART5 clock */
    RCM_APB1_PERIPH_I2C1   = BIT21,             /*!< Select I2C1 clock */
    RCM_APB1_PERIPH_I2C2   = BIT22,             /*!< Select I2C2 clock */
    RCM_APB1_PERIPH_I2C3   = BIT23,             /*!< Select I2C3 clock */
    RCM_APB1_PERIPH_CAN1   = BIT25,             /*!< Select CAN1 clock */
    RCM_APB1_PERIPH_CAN2   = BIT26,             /*!< Select CAN2 clock */
    RCM_APB1_PERIPH_PMU    = BIT28,             /*!< Select PMU clock */
    RCM_APB1_PERIPH_DAC    = BIT29,             /*!< Select DAC clock */
    RCM_APB1_PERIPH_UART7  = BIT30,             /*!< Select UART7 clock */
    RCM_APB1_PERIPH_UART8  = (int32_t)BIT31     /*!< Select UART8 clock */
} RCM_APB1_PERIPH_T;

/**
 * @brief APB2 peripheral
 */
typedef enum
{
    RCM_APB2_PERIPH_TMR1   = BIT0,      /*!< Select TMR1 clock */
    RCM_APB2_PERIPH_TMR8   = BIT1,      /*!< Select TMR8 clock */
    RCM_APB2_PERIPH_USART1 = BIT4,      /*!< Select USART1 clock */
    RCM_APB2_PERIPH_USART6 = BIT5,      /*!< Select USART6 clock */
    RCM_APB2_PERIPH_ADC    = BIT8,      /*!< Select ADC clock */
    RCM_APB2_PERIPH_ADC1   = BIT8,      /*!< Select ADC1 clock */
    RCM_APB2_PERIPH_ADC2   = BIT9,      /*!< Select ADC2 clock */
    RCM_APB2_PERIPH_ADC3   = BIT10,     /*!< Select ADC3 clock */
    RCM_APB2_PERIPH_SDIO   = BIT11,     /*!< Select SDIO clock */
    RCM_APB2_PERIPH_SPI1   = BIT12,     /*!< Select SPI1 clock */
    RCM_APB2_PERIPH_SPI4   = BIT13,     /*!< Select SPI4 clock */
    RCM_APB2_PERIPH_SYSCFG = BIT14,     /*!< Select SYSCFG clock */
    RCM_APB2_PERIPH_EXTIT  = BIT15,     /*!< Select EXTIT clock */
    RCM_APB2_PERIPH_TMR9   = BIT16,     /*!< Select TMR9 clock */
    RCM_APB2_PERIPH_TMR10  = BIT17,     /*!< Select TMR10 clock */
    RCM_APB2_PERIPH_TMR11  = BIT18,     /*!< Select TMR11 clock */
    RCM_APB2_PERIPH_SPI5   = BIT20,     /*!< Select SPI5 clock */
    RCM_APB2_PERIPH_SPI6   = BIT21,     /*!< Select SPI6 clock */
    RCM_APB2_PERIPH_SAI1   = BIT22,     /*!< Select SAI1 clock */
    RCM_APB2_PERIPH_LTDC   = BIT26      /*!< Select LTDC clock */
} RCM_APB2_PERIPH_T;

/**
 * @brief RCM FLAG define
 */
typedef enum
{
    RCM_FLAG_HSIRDY  = 0x001,   /*!< HSI Ready Flag */
    RCM_FLAG_HSERDY  = 0x011,   /*!< HSE Ready Flag */
    RCM_FLAG_PLL1RDY = 0x019,   /*!< PLL1 Ready Flag */
    RCM_FLAG_PLL2RDY = 0x01B,   /*!< PLL2 Ready Flag */

    RCM_FLAG_LSERDY  = 0x101,   /*!< LSE Ready Flag */

    RCM_FLAG_LSIRDY  = 0x201,   /*!< LSI Ready Flag */
    RCM_FLAG_BORRST  = 0x219,   /*!< POR/PDR or BOR reset Flag */
    RCM_FLAG_PINRST  = 0x21A,   /*!< PIN reset flag */
    RCM_FLAG_PORRST  = 0x21B,   /*!< POR/PDR reset flag */
    RCM_FLAG_SWRST   = 0x21C,   /*!< Software reset flag */
    RCM_FLAG_IWDTRST = 0x21D,   /*!< Independent watchdog reset flag */
    RCM_FLAG_WWDTRST = 0x21E,   /*!< Window watchdog reset flag */
    RCM_FLAG_LPRRST  = 0x21F,   /*!< Low-power reset flag */
} RCM_FLAG_T;

/**@} end of group RCM_Enumerations*/

/** @defgroup RCM_Functions
  @{
*/

/* Function description */

/* RCM Reset */
void RCM_Reset(void);

/* HSE clock */
void RCM_ConfigHSE(RCM_HSE_T state);
uint8_t RCM_WaitHSEReady(void);

/* HSI clock */
void RCM_ConfigHSITrim(uint8_t HSITrim);
void RCM_EnableHSI(void);
void RCM_DisableHSI(void);

/* LSE and LSI clock */
void RCM_ConfigLSE(RCM_LSE_T state);
void RCM_EnableLSI(void);
void RCM_DisableLSI(void);

/* PLL clock */
void RCM_ConfigPLL1(uint32_t pllSelect, uint32_t inputDiv, uint32_t vcoMul,
                   RCM_PLL_SYS_DIV_T sysDiv, uint32_t appDiv);
void RCM_EnablePLL1(void);
void RCM_DisablePLL1(void);
void RCM_ConfigPLL2(uint32_t i2sVcoMul, uint32_t i2sDiv);
void RCM_EnablePLL2(void);
void RCM_DisablePLL2(void);

/* Clock Security System */
void RCM_EnableCSS(void);
void RCM_DisableCSS(void);

void RCM_ConfigMCO1(RCM_MCO1_SEL_T mco1Select, RCM_MCO1_DIV_T mco1Div);
void RCM_ConfigMCO2(RCM_MCO2_SEL_T mco2Select, RCM_MCO2_DIV_T mco2Div);
void RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_T sysClkSelect);
RCM_SYSCLK_SEL_T RCM_ReadSYSCLKSource(void);

/* Config clock prescaler of AHB, APB1, APB2, SDRAM, USB and ADC */
void RCM_ConfigAHB(RCM_AHB_DIV_T AHBDiv);
void RCM_ConfigAPB1(RCM_APB_DIV_T APB1Div);
void RCM_ConfigAPB2(RCM_APB_DIV_T APB2Div);
void RCM_ConfigSDRAM(RCM_SDRAM_DIV_T SDRAMDiv);

/* Reads the clock frequency */
uint32_t RCM_ReadSYSCLKFreq(void);
uint32_t RCM_ReadHCLKFreq(void);
void RCM_ReadPCLKFreq(uint32_t* PCLK1, uint32_t* PCLK2);

/* RTC clock */
void RCM_ConfigRTCCLK(RCM_RTCCLK_T rtcClkSelect);
void RCM_EnableRTCCLK(void);
void RCM_DisableRTCCLK(void);

/* Backup domain reset */
void RCM_EnableBackupReset(void);
void RCM_DisableBackupReset(void);

void RCM_ConfigI2SCLK(RCM_I2S_CLK_T i2sClkSource);

/* Enable or disable Periph Clock */
void RCM_EnableAHB1PeriphClock(uint32_t AHB1Periph);
void RCM_DisableAHB1PeriphClock(uint32_t AHB1Periph);
void RCM_EnableAHB2PeriphClock(uint32_t AHB2Periph);
void RCM_DisableAHB2PeriphClock(uint32_t AHB2Periph);
void RCM_EnableAPB1PeriphClock(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphClock(uint32_t APB1Periph);
void RCM_EnableAPB2PeriphClock(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphClock(uint32_t APB2Periph);

/* Enable or disable Periph Reset */
void RCM_EnableAHB1PeriphReset(uint32_t AHB1Periph);
void RCM_DisableAHB1PeriphReset(uint32_t AHB1Periph);
void RCM_EnableAHB2PeriphReset(uint32_t AHB2Periph);
void RCM_DisableAHB2PeriphReset(uint32_t AHB2Periph);
void RCM_EnableAPB1PeriphReset(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphReset(uint32_t APB1Periph);
void RCM_EnableAPB2PeriphReset(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphReset(uint32_t APB2Periph);

/* Enable or disable Periph clock during Low Power (Sleep) mode */
void RCM_EnableAHB1PeriphClockLPMode(uint32_t AHB1Periph);
void RCM_DisableAHB1PeriphClockLPMode(uint32_t AHB1Periph);
void RCM_EnableAHB2PeriphClockLPMode(uint32_t AHB2Periph);
void RCM_DisableAHB2PeriphClockLPMode(uint32_t AHB2Periph);
void RCM_EnableAPB1PeriphClockLPMode(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphClockLPMode(uint32_t APB1Periph);
void RCM_EnableAPB2PeriphClockLPMode(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphClockLPMode(uint32_t APB2Periph);

/* Interrupts and flags */
void RCM_EnableInterrupt(uint32_t interrupt);
void RCM_DisableInterrupt(uint32_t interrupt);
uint8_t RCM_ReadStatusFlag(RCM_FLAG_T flag);
void RCM_ClearStatusFlag(void);
uint8_t RCM_ReadIntFlag(RCM_INT_T flag);
void RCM_ClearIntFlag(uint32_t flag);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_RCM_H */

/**@} end of group RCM_Enumerations */
/**@} end of group RCM_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
