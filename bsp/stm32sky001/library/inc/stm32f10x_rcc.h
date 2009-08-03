/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : stm32f10x_rcc.h
* Author             : MCD Application Team
* Version            : V2.0.3
* Date               : 09/22/2008
* Description        : This file contains all the functions prototypes for the
*                      RCC firmware library.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10x_RCC_H
#define __STM32F10x_RCC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_map.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  u32 SYSCLK_Frequency;
  u32 HCLK_Frequency;
  u32 PCLK1_Frequency;
  u32 PCLK2_Frequency;
  u32 ADCCLK_Frequency;
}RCC_ClocksTypeDef;

/* Exported constants --------------------------------------------------------*/
/* HSE configuration */
#define RCC_HSE_OFF                      ((u32)0x00000000)
#define RCC_HSE_ON                       ((u32)0x00010000)
#define RCC_HSE_Bypass                   ((u32)0x00040000)

#define IS_RCC_HSE(HSE) (((HSE) == RCC_HSE_OFF) || ((HSE) == RCC_HSE_ON) || \
                         ((HSE) == RCC_HSE_Bypass))

/* PLL entry clock source */
#define RCC_PLLSource_HSI_Div2           ((u32)0x00000000)
#define RCC_PLLSource_HSE_Div1           ((u32)0x00010000)
#define RCC_PLLSource_HSE_Div2           ((u32)0x00030000)

#define IS_RCC_PLL_SOURCE(SOURCE) (((SOURCE) == RCC_PLLSource_HSI_Div2) || \
                                   ((SOURCE) == RCC_PLLSource_HSE_Div1) || \
                                   ((SOURCE) == RCC_PLLSource_HSE_Div2))

/* PLL multiplication factor */
#define RCC_PLLMul_2                     ((u32)0x00000000)
#define RCC_PLLMul_3                     ((u32)0x00040000)
#define RCC_PLLMul_4                     ((u32)0x00080000)
#define RCC_PLLMul_5                     ((u32)0x000C0000)
#define RCC_PLLMul_6                     ((u32)0x00100000)
#define RCC_PLLMul_7                     ((u32)0x00140000)
#define RCC_PLLMul_8                     ((u32)0x00180000)
#define RCC_PLLMul_9                     ((u32)0x001C0000)
#define RCC_PLLMul_10                    ((u32)0x00200000)
#define RCC_PLLMul_11                    ((u32)0x00240000)
#define RCC_PLLMul_12                    ((u32)0x00280000)
#define RCC_PLLMul_13                    ((u32)0x002C0000)
#define RCC_PLLMul_14                    ((u32)0x00300000)
#define RCC_PLLMul_15                    ((u32)0x00340000)
#define RCC_PLLMul_16                    ((u32)0x00380000)

#define IS_RCC_PLL_MUL(MUL) (((MUL) == RCC_PLLMul_2) || ((MUL) == RCC_PLLMul_3)   || \
                             ((MUL) == RCC_PLLMul_4) || ((MUL) == RCC_PLLMul_5)   || \
                             ((MUL) == RCC_PLLMul_6) || ((MUL) == RCC_PLLMul_7)   || \
                             ((MUL) == RCC_PLLMul_8) || ((MUL) == RCC_PLLMul_9)   || \
                             ((MUL) == RCC_PLLMul_10) || ((MUL) == RCC_PLLMul_11) || \
                             ((MUL) == RCC_PLLMul_12) || ((MUL) == RCC_PLLMul_13) || \
                             ((MUL) == RCC_PLLMul_14) || ((MUL) == RCC_PLLMul_15) || \
                             ((MUL) == RCC_PLLMul_16))

/* System clock source */
#define RCC_SYSCLKSource_HSI             ((u32)0x00000000)
#define RCC_SYSCLKSource_HSE             ((u32)0x00000001)
#define RCC_SYSCLKSource_PLLCLK          ((u32)0x00000002)

#define IS_RCC_SYSCLK_SOURCE(SOURCE) (((SOURCE) == RCC_SYSCLKSource_HSI) || \
                                      ((SOURCE) == RCC_SYSCLKSource_HSE) || \
                                      ((SOURCE) == RCC_SYSCLKSource_PLLCLK))

/* AHB clock source */
#define RCC_SYSCLK_Div1                  ((u32)0x00000000)
#define RCC_SYSCLK_Div2                  ((u32)0x00000080)
#define RCC_SYSCLK_Div4                  ((u32)0x00000090)
#define RCC_SYSCLK_Div8                  ((u32)0x000000A0)
#define RCC_SYSCLK_Div16                 ((u32)0x000000B0)
#define RCC_SYSCLK_Div64                 ((u32)0x000000C0)
#define RCC_SYSCLK_Div128                ((u32)0x000000D0)
#define RCC_SYSCLK_Div256                ((u32)0x000000E0)
#define RCC_SYSCLK_Div512                ((u32)0x000000F0)

#define IS_RCC_HCLK(HCLK) (((HCLK) == RCC_SYSCLK_Div1) || ((HCLK) == RCC_SYSCLK_Div2) || \
                           ((HCLK) == RCC_SYSCLK_Div4) || ((HCLK) == RCC_SYSCLK_Div8) || \
                           ((HCLK) == RCC_SYSCLK_Div16) || ((HCLK) == RCC_SYSCLK_Div64) || \
                           ((HCLK) == RCC_SYSCLK_Div128) || ((HCLK) == RCC_SYSCLK_Div256) || \
                           ((HCLK) == RCC_SYSCLK_Div512))

/* APB1/APB2 clock source */
#define RCC_HCLK_Div1                    ((u32)0x00000000)
#define RCC_HCLK_Div2                    ((u32)0x00000400)
#define RCC_HCLK_Div4                    ((u32)0x00000500)
#define RCC_HCLK_Div8                    ((u32)0x00000600)
#define RCC_HCLK_Div16                   ((u32)0x00000700)

#define IS_RCC_PCLK(PCLK) (((PCLK) == RCC_HCLK_Div1) || ((PCLK) == RCC_HCLK_Div2) || \
                           ((PCLK) == RCC_HCLK_Div4) || ((PCLK) == RCC_HCLK_Div8) || \
                           ((PCLK) == RCC_HCLK_Div16))

/* RCC Interrupt source */
#define RCC_IT_LSIRDY                    ((u8)0x01)
#define RCC_IT_LSERDY                    ((u8)0x02)
#define RCC_IT_HSIRDY                    ((u8)0x04)
#define RCC_IT_HSERDY                    ((u8)0x08)
#define RCC_IT_PLLRDY                    ((u8)0x10)
#define RCC_IT_CSS                       ((u8)0x80)

#define IS_RCC_IT(IT) ((((IT) & (u8)0xE0) == 0x00) && ((IT) != 0x00))
#define IS_RCC_GET_IT(IT) (((IT) == RCC_IT_LSIRDY) || ((IT) == RCC_IT_LSERDY) || \
                           ((IT) == RCC_IT_HSIRDY) || ((IT) == RCC_IT_HSERDY) || \
                           ((IT) == RCC_IT_PLLRDY) || ((IT) == RCC_IT_CSS))
#define IS_RCC_CLEAR_IT(IT) ((((IT) & (u8)0x60) == 0x00) && ((IT) != 0x00))

/* USB clock source */
#define RCC_USBCLKSource_PLLCLK_1Div5    ((u8)0x00)
#define RCC_USBCLKSource_PLLCLK_Div1     ((u8)0x01)

#define IS_RCC_USBCLK_SOURCE(SOURCE) (((SOURCE) == RCC_USBCLKSource_PLLCLK_1Div5) || \
                                      ((SOURCE) == RCC_USBCLKSource_PLLCLK_Div1))

/* ADC clock source */
#define RCC_PCLK2_Div2                   ((u32)0x00000000)
#define RCC_PCLK2_Div4                   ((u32)0x00004000)
#define RCC_PCLK2_Div6                   ((u32)0x00008000)
#define RCC_PCLK2_Div8                   ((u32)0x0000C000)

#define IS_RCC_ADCCLK(ADCCLK) (((ADCCLK) == RCC_PCLK2_Div2) || ((ADCCLK) == RCC_PCLK2_Div4) || \
                               ((ADCCLK) == RCC_PCLK2_Div6) || ((ADCCLK) == RCC_PCLK2_Div8))

/* LSE configuration */
#define RCC_LSE_OFF                      ((u8)0x00)
#define RCC_LSE_ON                       ((u8)0x01)
#define RCC_LSE_Bypass                   ((u8)0x04)

#define IS_RCC_LSE(LSE) (((LSE) == RCC_LSE_OFF) || ((LSE) == RCC_LSE_ON) || \
                         ((LSE) == RCC_LSE_Bypass))

/* RTC clock source */
#define RCC_RTCCLKSource_LSE             ((u32)0x00000100)
#define RCC_RTCCLKSource_LSI             ((u32)0x00000200)
#define RCC_RTCCLKSource_HSE_Div128      ((u32)0x00000300)

#define IS_RCC_RTCCLK_SOURCE(SOURCE) (((SOURCE) == RCC_RTCCLKSource_LSE) || \
                                      ((SOURCE) == RCC_RTCCLKSource_LSI) || \
                                      ((SOURCE) == RCC_RTCCLKSource_HSE_Div128))

/* AHB peripheral */
#define RCC_AHBPeriph_DMA1               ((u32)0x00000001)
#define RCC_AHBPeriph_DMA2               ((u32)0x00000002)
#define RCC_AHBPeriph_SRAM               ((u32)0x00000004)
#define RCC_AHBPeriph_FLITF              ((u32)0x00000010)
#define RCC_AHBPeriph_CRC                ((u32)0x00000040)
#define RCC_AHBPeriph_FSMC               ((u32)0x00000100)
#define RCC_AHBPeriph_SDIO               ((u32)0x00000400)

#define IS_RCC_AHB_PERIPH(PERIPH) ((((PERIPH) & 0xFFFFFAA8) == 0x00) && ((PERIPH) != 0x00))

/* APB2 peripheral */
#define RCC_APB2Periph_AFIO              ((u32)0x00000001)
#define RCC_APB2Periph_GPIOA             ((u32)0x00000004)
#define RCC_APB2Periph_GPIOB             ((u32)0x00000008)
#define RCC_APB2Periph_GPIOC             ((u32)0x00000010)
#define RCC_APB2Periph_GPIOD             ((u32)0x00000020)
#define RCC_APB2Periph_GPIOE             ((u32)0x00000040)
#define RCC_APB2Periph_GPIOF             ((u32)0x00000080)
#define RCC_APB2Periph_GPIOG             ((u32)0x00000100)
#define RCC_APB2Periph_ADC1              ((u32)0x00000200)
#define RCC_APB2Periph_ADC2              ((u32)0x00000400)
#define RCC_APB2Periph_TIM1              ((u32)0x00000800)
#define RCC_APB2Periph_SPI1              ((u32)0x00001000)
#define RCC_APB2Periph_TIM8              ((u32)0x00002000)
#define RCC_APB2Periph_USART1            ((u32)0x00004000)
#define RCC_APB2Periph_ADC3              ((u32)0x00008000)
#define RCC_APB2Periph_ALL               ((u32)0x0000FFFD)

#define IS_RCC_APB2_PERIPH(PERIPH) ((((PERIPH) & 0xFFFF0002) == 0x00) && ((PERIPH) != 0x00))

/* APB1 peripheral */
#define RCC_APB1Periph_TIM2              ((u32)0x00000001)
#define RCC_APB1Periph_TIM3              ((u32)0x00000002)
#define RCC_APB1Periph_TIM4              ((u32)0x00000004)
#define RCC_APB1Periph_TIM5              ((u32)0x00000008)
#define RCC_APB1Periph_TIM6              ((u32)0x00000010)
#define RCC_APB1Periph_TIM7              ((u32)0x00000020)
#define RCC_APB1Periph_WWDG              ((u32)0x00000800)
#define RCC_APB1Periph_SPI2              ((u32)0x00004000)
#define RCC_APB1Periph_SPI3              ((u32)0x00008000)
#define RCC_APB1Periph_USART2            ((u32)0x00020000)
#define RCC_APB1Periph_USART3            ((u32)0x00040000)
#define RCC_APB1Periph_UART4             ((u32)0x00080000)
#define RCC_APB1Periph_UART5             ((u32)0x00100000)
#define RCC_APB1Periph_I2C1              ((u32)0x00200000)
#define RCC_APB1Periph_I2C2              ((u32)0x00400000)
#define RCC_APB1Periph_USB               ((u32)0x00800000)
#define RCC_APB1Periph_CAN               ((u32)0x02000000)
#define RCC_APB1Periph_BKP               ((u32)0x08000000)
#define RCC_APB1Periph_PWR               ((u32)0x10000000)
#define RCC_APB1Periph_DAC               ((u32)0x20000000)
#define RCC_APB1Periph_ALL               ((u32)0x3AFEC83F)

#define IS_RCC_APB1_PERIPH(PERIPH) ((((PERIPH) & 0xC50137C0) == 0x00) && ((PERIPH) != 0x00))

/* Clock source to output on MCO pin */
#define RCC_MCO_NoClock                  ((u8)0x00)
#define RCC_MCO_SYSCLK                   ((u8)0x04)
#define RCC_MCO_HSI                      ((u8)0x05)
#define RCC_MCO_HSE                      ((u8)0x06)
#define RCC_MCO_PLLCLK_Div2              ((u8)0x07)

#define IS_RCC_MCO(MCO) (((MCO) == RCC_MCO_NoClock) || ((MCO) == RCC_MCO_HSI) || \
                         ((MCO) == RCC_MCO_SYSCLK)  || ((MCO) == RCC_MCO_HSE) || \
                         ((MCO) == RCC_MCO_PLLCLK_Div2))

/* RCC Flag */
#define RCC_FLAG_HSIRDY                  ((u8)0x21)
#define RCC_FLAG_HSERDY                  ((u8)0x31)
#define RCC_FLAG_PLLRDY                  ((u8)0x39)
#define RCC_FLAG_LSERDY                  ((u8)0x41)
#define RCC_FLAG_LSIRDY                  ((u8)0x61)
#define RCC_FLAG_PINRST                  ((u8)0x7A)
#define RCC_FLAG_PORRST                  ((u8)0x7B)
#define RCC_FLAG_SFTRST                  ((u8)0x7C)
#define RCC_FLAG_IWDGRST                 ((u8)0x7D)
#define RCC_FLAG_WWDGRST                 ((u8)0x7E)
#define RCC_FLAG_LPWRRST                 ((u8)0x7F)

#define IS_RCC_FLAG(FLAG) (((FLAG) == RCC_FLAG_HSIRDY) || ((FLAG) == RCC_FLAG_HSERDY) || \
                           ((FLAG) == RCC_FLAG_PLLRDY) || ((FLAG) == RCC_FLAG_LSERDY) || \
                           ((FLAG) == RCC_FLAG_LSIRDY) || ((FLAG) == RCC_FLAG_PINRST) || \
                           ((FLAG) == RCC_FLAG_PORRST) || ((FLAG) == RCC_FLAG_SFTRST) || \
                           ((FLAG) == RCC_FLAG_IWDGRST)|| ((FLAG) == RCC_FLAG_WWDGRST)|| \
                           ((FLAG) == RCC_FLAG_LPWRRST))

#define IS_RCC_CALIBRATION_VALUE(VALUE) ((VALUE) <= 0x1F)

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void RCC_DeInit(void);
void RCC_HSEConfig(u32 RCC_HSE);
ErrorStatus RCC_WaitForHSEStartUp(void);
void RCC_AdjustHSICalibrationValue(u8 HSICalibrationValue);
void RCC_HSICmd(FunctionalState NewState);
void RCC_PLLConfig(u32 RCC_PLLSource, u32 RCC_PLLMul);
void RCC_PLLCmd(FunctionalState NewState);
void RCC_SYSCLKConfig(u32 RCC_SYSCLKSource);
u8 RCC_GetSYSCLKSource(void);
void RCC_HCLKConfig(u32 RCC_SYSCLK);
void RCC_PCLK1Config(u32 RCC_HCLK);
void RCC_PCLK2Config(u32 RCC_HCLK);
void RCC_ITConfig(u8 RCC_IT, FunctionalState NewState);
void RCC_USBCLKConfig(u32 RCC_USBCLKSource);
void RCC_ADCCLKConfig(u32 RCC_PCLK2);
void RCC_LSEConfig(u8 RCC_LSE);
void RCC_LSICmd(FunctionalState NewState);
void RCC_RTCCLKConfig(u32 RCC_RTCCLKSource);
void RCC_RTCCLKCmd(FunctionalState NewState);
void RCC_GetClocksFreq(RCC_ClocksTypeDef* RCC_Clocks);
void RCC_AHBPeriphClockCmd(u32 RCC_AHBPeriph, FunctionalState NewState);
void RCC_APB2PeriphClockCmd(u32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphClockCmd(u32 RCC_APB1Periph, FunctionalState NewState);
void RCC_APB2PeriphResetCmd(u32 RCC_APB2Periph, FunctionalState NewState);
void RCC_APB1PeriphResetCmd(u32 RCC_APB1Periph, FunctionalState NewState);
void RCC_BackupResetCmd(FunctionalState NewState);
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);
void RCC_MCOConfig(u8 RCC_MCO);
FlagStatus RCC_GetFlagStatus(u8 RCC_FLAG);
void RCC_ClearFlag(void);
ITStatus RCC_GetITStatus(u8 RCC_IT);
void RCC_ClearITPendingBit(u8 RCC_IT);

#endif /* __STM32F10x_RCC_H */

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/
