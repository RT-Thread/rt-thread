/*!
 * @file       apm32e10x_rcm.h
 *
 * @brief      This file contains all the functions prototypes for the RCM firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-12-31
 *
 * @attention
 *
 *  Copyright (C) 2021-2023 Geehy Semiconductor
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

/* Define to prevent recursive inclusion */
#ifndef __APM32E10X_RCM_H
#define __APM32E10X_RCM_H

/* Includes */
#include "apm32e10x.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup APM32E10x_StdPeriphDriver
  @{
*/

/** @addtogroup RCM_Driver
  @{
*/

/** @defgroup RCM_Enumerations Enumerations
  @{
*/

/**
 * @brief   HSE state
 */
typedef enum
{
    RCM_HSE_CLOSE,    /*!< CLOSE HSE */
    RCM_HSE_OPEN,     /*!< OPEN HSE */
    RCM_HSE_BYPASS,   /*!< HSE BYPASS */
} RCM_HSE_T;

/**
 * @brief   PLL multiplication factor
 */
typedef enum
{
    RCM_PLLMF_2,
    RCM_PLLMF_3,
    RCM_PLLMF_4,
    RCM_PLLMF_5,
    RCM_PLLMF_6,
    RCM_PLLMF_7,
    RCM_PLLMF_8,
    RCM_PLLMF_9,
    RCM_PLLMF_10,
    RCM_PLLMF_11,
    RCM_PLLMF_12,
    RCM_PLLMF_13,
    RCM_PLLMF_14,
    RCM_PLLMF_15,
    RCM_PLLMF_16
} RCM_PLLMF_T;

/**
 * @brief   System clock select
 */
typedef enum
{
    RCM_SYSCLK_SEL_HSI,
    RCM_SYSCLK_SEL_HSE,
    RCM_SYSCLK_SEL_PLL
} RCM_SYSCLK_SEL_T;

/**
 * @brief   AHB divider Number
 */
typedef enum
{
    RCM_AHB_DIV_1 = 7,
    RCM_AHB_DIV_2,
    RCM_AHB_DIV_4,
    RCM_AHB_DIV_8,
    RCM_AHB_DIV_16,
    RCM_AHB_DIV_64,
    RCM_AHB_DIV_128,
    RCM_AHB_DIV_256,
    RCM_AHB_DIV_512
} RCM_AHB_DIV_T;

/**
 * @brief   APB divider Number
 */
typedef enum
{
    RCM_APB_DIV_1 = 3,
    RCM_APB_DIV_2,
    RCM_APB_DIV_4,
    RCM_APB_DIV_8,
    RCM_APB_DIV_16
} RCM_APB_DIV_T;

/**
 * @brief   USB divider Number
 */
typedef enum
{
    RCM_USB_DIV_1_5,
    RCM_USB_DIV_1,
    RCM_USB_DIV_2,
    RCM_USB_DIV_2_5
} RCM_USB_DIV_T;

/**
 * @brief   FPU divider Number
 */
typedef enum
{
    RCM_FPU_DIV_1,
    RCM_FPU_DIV_2
} RCM_FPU_DIV_T;

/**
 * @brief   ADC divider Number
 */
typedef enum
{
    RCM_PCLK2_DIV_2,
    RCM_PCLK2_DIV_4,
    RCM_PCLK2_DIV_6,
    RCM_PCLK2_DIV_8
} RCM_PCLK2_DIV_T;

/**
 * @brief   LSE State
 */
typedef enum
{
    RCM_LSE_CLOSE,
    RCM_LSE_OPEN,
    RCM_LSE_BYPASS
} RCM_LSE_T;

/**
 * @brief   RTC clock select
 */
typedef enum
{
    RCM_RTCCLK_LSE = 1,
    RCM_RTCCLK_LSI,
    RCM_RTCCLK_HSE_DIV_128
} RCM_RTCCLK_T;

/**
 * @brief   Clock output control
 */
typedef enum
{
    RCM_MCOCLK_NO_CLOCK = 3,
    RCM_MCOCLK_SYSCLK,
    RCM_MCOCLK_HSI,
    RCM_MCOCLK_HSE,
    RCM_MCOCLK_PLLCLK_DIV_2
} RCM_MCOCLK_T;

/**
 * @brief   PLL entry clock select
 */
typedef enum
{
    RCM_PLLSEL_HSI_DIV_2 = 0,
    RCM_PLLSEL_HSE       = 1,
    RCM_PLLSEL_HSE_DIV2  = 3,
} RCM_PLLSEL_T;

/**
 * @brief   RCM Interrupt Source
 */
typedef enum
{
    RCM_INT_LSIRDY  = BIT0,  /*!< LSI ready interrupt */
    RCM_INT_LSERDY  = BIT1,  /*!< LSE ready interrupt */
    RCM_INT_HSIRDY  = BIT2,  /*!< HSI ready interrupt */
    RCM_INT_HSERDY  = BIT3,  /*!< HSE ready interrupt */
    RCM_INT_PLLRDY  = BIT4,  /*!< PLL ready interrupt */
    RCM_INT_CSS     = BIT7   /*!< Clock security system interrupt */
} RCM_INT_T;

/**
 * @brief   AHB peripheral
 */
typedef enum
{
    RCM_AHB_PERIPH_DMA1 = BIT0,
    RCM_AHB_PERIPH_DMA2 = BIT1,
    RCM_AHB_PERIPH_SRAM = BIT2,
    RCM_AHB_PERIPH_FPU  = BIT3,
    RCM_AHB_PERIPH_FMC  = BIT4,
    RCM_AHB_PERIPH_QSPI = BIT5,
    RCM_AHB_PERIPH_CRC  = BIT6,
    RCM_AHB_PERIPH_SMC  = BIT8,
    RCM_AHB_PERIPH_SDIO = BIT10
} RCM_AHB_PERIPH_T;

/**
 * @brief   AHB2 peripheral
 */
typedef enum
{
    RCM_APB2_PERIPH_AFIO    = BIT0,
    RCM_APB2_PERIPH_GPIOA   = BIT2,
    RCM_APB2_PERIPH_GPIOB   = BIT3,
    RCM_APB2_PERIPH_GPIOC   = BIT4,
    RCM_APB2_PERIPH_GPIOD   = BIT5,
    RCM_APB2_PERIPH_GPIOE   = BIT6,
    RCM_APB2_PERIPH_GPIOF   = BIT7,
    RCM_APB2_PERIPH_GPIOG   = BIT8,
    RCM_APB2_PERIPH_ADC1    = BIT9,
    RCM_APB2_PERIPH_ADC2    = BIT10,
    RCM_APB2_PERIPH_TMR1    = BIT11,
    RCM_APB2_PERIPH_SPI1    = BIT12,
    RCM_APB2_PERIPH_TMR8    = BIT13,
    RCM_APB2_PERIPH_USART1  = BIT14,
    RCM_APB2_PERIPH_ADC3    = BIT15
} RCM_APB2_PERIPH_T;

/**
 * @brief   AHB1 peripheral
 */
typedef enum
{
    RCM_APB1_PERIPH_TMR2   = BIT0,
    RCM_APB1_PERIPH_TMR3   = BIT1,
    RCM_APB1_PERIPH_TMR4   = BIT2,
    RCM_APB1_PERIPH_TMR5   = BIT3,
    RCM_APB1_PERIPH_TMR6   = BIT4,
    RCM_APB1_PERIPH_TMR7   = BIT5,
    RCM_APB1_PERIPH_WWDT   = BIT11,
    RCM_APB1_PERIPH_SPI2   = BIT14,
    RCM_APB1_PERIPH_SPI3   = BIT15,
    RCM_APB1_PERIPH_USART2 = BIT17,
    RCM_APB1_PERIPH_USART3 = BIT18,
    RCM_APB1_PERIPH_UART4  = BIT19,
    RCM_APB1_PERIPH_UART5  = BIT20,
    RCM_APB1_PERIPH_I2C1   = BIT21,
    RCM_APB1_PERIPH_I2C2   = BIT22,
    RCM_APB1_PERIPH_USB    = BIT23,
    RCM_APB1_PERIPH_CAN1   = BIT25,
    RCM_APB1_PERIPH_CAN2   = BIT26,
    RCM_APB1_PERIPH_BAKR   = BIT27,
    RCM_APB1_PERIPH_PMU    = BIT28,
    RCM_APB1_PERIPH_DAC    = BIT29
} RCM_APB1_PERIPH_T;

/**
 * @brief   RCM FLAG define
 */
typedef enum
{
    RCM_FLAG_HSIRDY  = 0x001,   /*!< HSI Ready Flag */
    RCM_FLAG_HSERDY  = 0x011,   /*!< HSE Ready Flag */
    RCM_FLAG_PLLRDY  = 0x019,   /*!< PLL Ready Flag */
    RCM_FLAG_LSERDY  = 0x101,   /*!< LSE Ready Flag */
    RCM_FLAG_LSIRDY  = 0x201,   /*!< LSI Ready Flag */
    RCM_FLAG_PINRST  = 0x21A,   /*!< PIN reset flag */
    RCM_FLAG_PORRST  = 0x21B,   /*!< POR/PDR reset flag */
    RCM_FLAG_SWRST   = 0x21C,   /*!< Software reset flag */
    RCM_FLAG_IWDTRST = 0x21D,   /*!< Independent watchdog reset flag */
    RCM_FLAG_WWDTRST = 0x21E,   /*!< Window watchdog reset flag */
    RCM_FLAG_LPRRST  = 0x21F    /*!< Low-power reset flag */
} RCM_FLAG_T;

/**@} end of group RCM_Enumerations */


/** @defgroup RCM_Functions Functions
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
void RCM_ConfigPLL(RCM_PLLSEL_T pllSelect, RCM_PLLMF_T pllMf);
void RCM_EnablePLL(void);
void RCM_DisablePLL(void);

/* Clock Security System */
void RCM_EnableCSS(void);
void RCM_DisableCSS(void);

void RCM_ConfigMCO(RCM_MCOCLK_T mcoClock);
void RCM_ConfigSYSCLK(RCM_SYSCLK_SEL_T sysClkSelect);
RCM_SYSCLK_SEL_T RCM_ReadSYSCLKSource(void);

/* Config clock prescaler of AHB, APB1, APB2, USB and ADC */
void RCM_ConfigAHB(RCM_AHB_DIV_T AHBDiv);
void RCM_ConfigAPB1(RCM_APB_DIV_T APB1Div);
void RCM_ConfigAPB2(RCM_APB_DIV_T APB2Div);
void RCM_ConfigUSBCLK(RCM_USB_DIV_T USBDiv);
void RCM_ConfigFPUCLK(RCM_FPU_DIV_T FPUDiv);
void RCM_ConfigADCCLK(RCM_PCLK2_DIV_T ADCDiv);

/* RTC clock */
void RCM_ConfigRTCCLK(RCM_RTCCLK_T rtcClkSelect);
void RCM_EnableRTCCLK(void);
void RCM_DisableRTCCLK(void);

/* Reads the clock frequency */
uint32_t RCM_ReadSYSCLKFreq(void);
uint32_t RCM_ReadHCLKFreq(void);
void RCM_ReadPCLKFreq(uint32_t* PCLK1, uint32_t* PCLK2);
uint32_t RCM_ReadADCCLKFreq(void);

/* Enable or disable Periph Clock */
void RCM_EnableAHBPeriphClock(uint32_t AHBPeriph);
void RCM_DisableAHBPeriphClock(uint32_t AHBPeriph);
void RCM_EnableAPB2PeriphClock(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphClock(uint32_t APB2Periph);
void RCM_EnableAPB1PeriphClock(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphClock(uint32_t APB1Periph);

/* Enable or disable Periph Reset */
void RCM_EnableAPB2PeriphReset(uint32_t APB2Periph);
void RCM_DisableAPB2PeriphReset(uint32_t APB2Periph);
void RCM_EnableAPB1PeriphReset(uint32_t APB1Periph);
void RCM_DisableAPB1PeriphReset(uint32_t APB1Periph);

/* Backup domain reset */
void RCM_EnableBackupReset(void);
void RCM_DisableBackupReset(void);

/* Interrupts and flags */
void RCM_EnableInterrupt(uint32_t interrupt);
void RCM_DisableInterrupt(uint32_t interrupt);
uint8_t RCM_ReadStatusFlag(RCM_FLAG_T flag);
void RCM_ClearStatusFlag(void);
uint8_t RCM_ReadIntFlag(RCM_INT_T flag);
void RCM_ClearIntFlag(uint32_t flag);

/**@} end of group RCM_Functions */
/**@} end of group RCM_Driver */
/**@} end of group APM32E10x_StdPeriphDriver*/

#ifdef __cplusplus
}
#endif

#endif /* __APM32E10X_RCM_H */
