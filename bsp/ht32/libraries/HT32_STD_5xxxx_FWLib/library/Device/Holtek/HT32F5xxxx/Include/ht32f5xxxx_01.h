/***************************************************************************//**
 * @file    ht32f5xxxx_01.h
 * @brief   CMSIS Cortex-M0+ Device Peripheral Access Layer Header File
 * @version $Rev:: 7319         $
 * @date    $Date:: 2023-10-28 #$
 *
 * @note
 * Copyright (C) Holtek Semiconductor Inc. All rights reserved.
 *
 * @par
 * Holtek supplies this software for Cortex-M processor-based
 * microcontrollers.  This file can be freely distributed within
 * development tools that are supporting such ARM-based processors.
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

// Supported Device
// ========================================
//   HT32F50020, HT32F50030
//   HT32F50220, HT32F50230
//   HT32F50231, HT32F50241
//   HT32F50343
//   HT32F50431, HT32F50441
//   HT32F50442, HT32F50452
//   HT32F52220, HT32F52230
//   HT32F52231, HT32F52241
//   HT32F52243, HT32F52253
//   HT32F52331, HT32F52341
//   HT32F52342, HT32F52352
//   HT32F52344, HT32F52354
//   HT32F52357, HT32F52367
//   HT32F53231, HT32F53241
//   HT32F53242, HT32F53252
//   HT32F54231, HT32F54241
//   HT32F54243, HT32F54253
//   HT32F57331, HT32F57341
//   HT32F57342, HT32F57352
//   HT32F5826,  HT32F5828
//   HT32F0006
//   HT32F0008
//   HT32F61141
//   HT32F61244, HT32F61245
//   HT32F65230, HT32F65240
//   HT32F65232
//   HT32F66242, HT32F66246
//   HT32F67041, HT32F67051
//   HT32F52234, HT32F52244

/** @addtogroup CMSIS
  * @{
  */

/** @addtogroup HT32F5xxxx HT32F5xxxx
  * @{
  */


#ifndef __HT32F5XXXX_01_H__
#define __HT32F5XXXX_01_H__

#include "ht32_config.h"

#ifdef __cplusplus
 extern "C" {
#endif

#if !defined(USE_HT32F52220_30) && \
    !defined(USE_HT32F52231_41) && \
    !defined(USE_HT32F52331_41) && \
    !defined(USE_HT32F52342_52) && \
    !defined(USE_HT32F52243_53) && \
    !defined(USE_HT32F5826) && \
    !defined(USE_HT32F0008) && \
    !defined(USE_HT32F50220_30) && \
    !defined(USE_HT32F50231_41) && \
    !defined(USE_HT32F52344_54) && \
    !defined(USE_HT32F0006) && \
    !defined(USE_HT32F52357_67) && \
    !defined(USE_HT32F65230_40) && \
    !defined(USE_HT32F54231_41) && \
    !defined(USE_HT32F54243_53) && \
    !defined(USE_HT32F57331_41) && \
    !defined(USE_HT32F57342_52) && \
    !defined(USE_HT32F50343) && \
    !defined(USE_HT32F65232) && \
    !defined(USE_HT32F61141) && \
    !defined(USE_HT32F61244_45) && \
    !defined(USE_HT32F50020_30) && \
    !defined(USE_HT32F67041_51) && \
    !defined(USE_HT32F50431_41) && \
    !defined(USE_HT32F50442_52) && \
    !defined(USE_HT32F53231_41) && \
    !defined(USE_HT32F53242_52) && \
    !defined(USE_HT32F66242) && \
    !defined(USE_HT32F66246) && \
    !defined(USE_HT32F52234_44)

  //#define USE_HT32F52220_30
  //#define USE_HT32F52231_41
  //#define USE_HT32F52331_41
  //#define USE_HT32F52342_52
  //#define USE_HT32F52243_53
  //#define USE_HT32F5826
  //#define USE_HT32F0008
  //#define USE_HT32F50220_30
  //#define USE_HT32F50231_41
  //#define USE_HT32F52344_54
  //#define USE_HT32F0006
  //#define USE_HT32F52357_67
  //#define USE_HT32F65230_40
  //#define USE_HT32F54231_41
  //#define USE_HT32F54243_53
  //#define USE_HT32F57331_41
  //#define USE_HT32F57342_52
  //#define USE_HT32F50343
  //#define USE_HT32F65232
  //#define USE_HT32F61141
  //#define USE_HT32F61244_45
  //#define USE_HT32F50020_30
  //#define USE_HT32F67041_51
  //#define USE_HT32F50431_41
  //#define USE_HT32F50442_52
  //#define USE_HT32F53231_41
  //#define USE_HT32F53242_52
  //#define USE_HT32F66242
  //#define USE_HT32F66246
  //#define USE_HT32F52234_44

#endif

#if !defined(USE_NOCHIP) && \
    !defined(USE_HT32F52220_30) && \
    !defined(USE_HT32F52231_41) && \
    !defined(USE_HT32F52331_41) && \
    !defined(USE_HT32F52342_52) && \
    !defined(USE_HT32F52243_53) && \
    !defined(USE_HT32F5826) && \
    !defined(USE_HT32F0008) && \
    !defined(USE_HT32F50220_30) && \
    !defined(USE_HT32F50231_41) && \
    !defined(USE_HT32F52344_54) && \
    !defined(USE_HT32F0006) && \
    !defined(USE_HT32F52357_67) && \
    !defined(USE_HT32F65230_40) && \
    !defined(USE_HT32F54231_41) && \
    !defined(USE_HT32F54243_53) && \
    !defined(USE_HT32F57331_41) && \
    !defined(USE_HT32F57342_52) && \
    !defined(USE_HT32F50343) && \
    !defined(USE_HT32F65232) && \
    !defined(USE_HT32F61141) && \
    !defined(USE_HT32F61244_45) && \
    !defined(USE_HT32F50020_30) && \
    !defined(USE_HT32F67041_51) && \
    !defined(USE_HT32F50431_41) && \
    !defined(USE_HT32F50442_52) && \
    !defined(USE_HT32F53231_41) && \
    !defined(USE_HT32F53242_52) && \
    !defined(USE_HT32F66242) && \
    !defined(USE_HT32F66246) && \
    !defined(USE_HT32F52234_44)

  #error Please add "USE_HT32Fxxxxx_xx" define into C Preprocessor Symbols of the Project configuration.

#endif

/** @addtogroup Library_configuration_section
  * @{
  */
/**
 * @brief Value of the High Speed Internal oscillator in Hz
  */
#if defined(USE_HT32F50220_30) || defined(USE_HT32F50231_41)
  #define HSI_VALUE      20000000UL  /*!< Value of the Internal High Speed oscillator in Hz                 */
#elif defined(USE_HT32F50020_30)
  #define HSI_VALUE      16000000UL  /*!< Value of the Internal High Speed oscillator in Hz                 */
#else
  #define HSI_VALUE      8000000UL   /*!< Value of the High Speed Internal oscillator in Hz                 */
#endif

/**
 * @brief Value of the Low Speed Internal oscillator in Hz
  */
#define LSI_VALUE         32000UL     /*!< Value of the Low Speed Internal oscillator in Hz                 */

#if !defined(USE_HT32F52220_30) && !defined(USE_HT32F66242) && !defined(USE_HT32F66246)
/**
 * @brief Value of the Low Speed External oscillator in Hz
  */
#define LSE_VALUE         32768UL     /*!< Value of the Low Speed External oscillator in Hz                 */
#endif

/**
 * @brief Adjust the High Speed External oscillator (HSE) Startup Timeout value
   */
#define HSE_READY_TIME    ((uint16_t)0xFFFF)    /*!< Time out for HSE start up                              */
/**
  * @}
  */

/** @addtogroup Configuration_section_for_CMSIS
  * @{
  */
#define __MPU_PRESENT             0    /*!< MPU present or not                                              */
#define __VTOR_PRESENT            1    /*!< VTOR present or not                                             */
#define __NVIC_PRIO_BITS          2    /*!< Number of Bits used for Priority Levels                         */
#define __Vendor_SysTickConfig    0    /*!< Set to 1 if different SysTick Config is used                    */

/**
  * @}
  */


/** @addtogroup Configuration_for_Interrupt_Number
  * @{
  */
typedef enum IRQn
{
/****** Cortex-M0+ Processor Exceptions Numbers ********************************                            */
  NonMaskableInt_IRQn     = -14,    /*!< 2 Non Maskable Interrupt                                           */
  HardFault_IRQn          = -13,    /*!< 3 Cortex-M0+ Hard Fault Interrupt                                  */
  SVCall_IRQn             = -5,     /*!< 11 Cortex-M0+ SV Call Interrupt                                    */
  PendSV_IRQn             = -2,     /*!< 14 Cortex-M0+ Pend SV Interrupt                                    */
  SysTick_IRQn            = -1,     /*!< 15 Cortex-M0+ System Tick Interrupt                                */

/******  HT32 Specific Interrupt Numbers ***************************************                            */
  LVD_BOD_IRQn            = 0,      /*!< Low voltage & Brown-out detection interrupt                        */
  #if !defined(USE_HT32F52220_30)
  RTC_IRQn                = 1,      /*!< RTC Wake-up Interrupt                                              */
  #endif
  FLASH_IRQn              = 2,      /*!< FLASH global Interrupt                                             */
  EVWUP_IRQn              = 3,      /*!< EXTI Event Wake-up & WAKEUP pin Interrupt                          */
  EXTI0_1_IRQn            = 4,      /*!< EXTI0-1 Line detection Interrupt                                   */
  EXTI2_3_IRQn            = 5,      /*!< EXTI2-3 Line detection Interrupt                                   */
  #if defined(USE_HT32F65230_40) || defined(USE_HT32F65232)
  EXTI4_9_IRQn            = 6,      /*!< EXTI4-9 Line detection Interrupt                                   */
  #elif defined(USE_HT32F50020_30)
  EXTI4_7_IRQn            = 6,      /*!< EXTI4-7 Line detection Interrupt                                   */
  #else
  EXTI4_15_IRQn           = 6,      /*!< EXTI4-15 Line detection Interrupt                                  */
  #endif
  #if defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
  #if defined(USE_HT32F65230_40) || defined(USE_HT32F65232)
  EXTI10_15_IRQn          = 7,      /*!< EXTI10-15 Line detection Interrupt                                 */
  #elif defined(USE_HT32F66246)
  CAN0_IRQn               = 7,      /*!< CAN0 global Interrupt                                              */
  #endif
  ADC0_IRQn               = 8,      /*!< ADC0 Interrupt                                                     */
  #if defined(USE_HT32F65230_40)
  ADC1_IRQn               = 9,      /*!< ADC1 Interrupt                                                     */
  #elif defined(USE_HT32F66242)
  CORDIC_IRQn             = 9,      /*!< CORDIC global Interrupt                                            */
  #elif defined(USE_HT32F66246)
  CORDIC_IRQn             = 9,      /*!< CORDIC global Interrupt                                            */
  #endif
  MCTM0_BRK_IRQn          = 10,     /*!< MCTM BRK Interrupt                                                 */
  MCTM0_UP_IRQn           = 11,     /*!< MCTM UP Interrupt                                                  */
  MCTM0_TR_UP2_IRQn       = 12,     /*!< MCTM TR & UP2 Interrupt                                            */
  MCTM0_CC_IRQn           = 13,     /*!< MCTM CC Interrupt                                                  */
  GPTM0_G_IRQn            = 14,     /*!< GPTM G Interrupt                                                   */
  GPTM0_VCLK_IRQn         = 15,     /*!< GPTM VCLK Interrupt                                                */
  BFTM0_IRQn              = 16,     /*!< Basic Function Timer0 Interrupt                                    */
  BFTM1_IRQn              = 17,     /*!< Basic Function Timer1 Interrupt                                    */
  CMP0_IRQn               = 18,     /*!< Comparator0 Interrupt                                              */
  CMP1_IRQn               = 19,     /*!< Comparator1 Interrupt                                              */
  #if defined(USE_HT32F65230_40)
  CMP2_IRQn               = 20,     /*!< Comparator2 Interrupt                                              */
  #elif defined(USE_HT32F66242)
  PID_IRQn                = 20,     /*!< PID global Interrupt                                               */
  #elif defined(USE_HT32F66246)
  PID_IRQn                = 20,     /*!< PID global Interrupt                                               */
  #endif
  I2C0_IRQn               = 21,     /*!< I2C global Interrupt                                               */
  SPI0_IRQn               = 22,     /*!< SPI global Interrupt                                               */
  USART0_IRQn             = 23,     /*!< USART global Interrupt                                             */
  UART0_IRQn              = 24,     /*!< UART global Interrupt                                              */
  PDMACH0_1_IRQn          = 25,     /*!< PDMA channel 0-1 Interrupt                                         */
  PDMACH2_3_IRQn          = 26,     /*!< PDMA channel 2-3 Interrupt                                         */
  PDMACH4_5_IRQn          = 27,     /*!< PDMA channel 4-5 Interrupt                                         */
  SCTM0_IRQn              = 28,     /*!< Single Channel Timer0 Interrupt                                    */
  SCTM1_IRQn              = 29,     /*!< Single Channel Timer1 Interrupt                                    */
  SCTM2_IRQn              = 30,     /*!< Single Channel Timer2 Interrupt                                    */
  SCTM3_IRQn              = 31,     /*!< Single Channel Timer3 Interrupt                                    */
  #else
  #if defined(USE_HT32F52342_52) || defined(USE_HT32F5826) || defined(USE_HT32F52344_54) || defined(USE_HT32F54243_53) || defined(USE_HT32F53242_52) || defined(USE_HT32F50442_52)
  COMP_IRQn               = 7,      /*!< Comparator global Interrupt                                        */
  #endif
  #if defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52)
  COMP_DAC_IRQn           = 7,      /*!< Comparator & DAC global Interrupt                                  */
  #endif
  #if defined(USE_HT32F52234_44)
  DAC0_1_IRQn             = 7,      /*!< DAC0 & DAC1 global Interrupt                                       */
  #endif
  #if !defined(USE_HT32F0008)
  ADC0_IRQn               = 8,      /*!< ADC Interrupt                                                      */
  #endif
  #if defined(USE_HT32F52243_53) || defined(USE_HT32F54243_53) || defined(USE_HT32F52234_44)
  I2C2_IRQn               = 9,      /*!< I2C2 global Interrupt                                              */
  #endif
  #if defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F67041_51)
  AES_IRQn                = 9,      /*!< AES global Interrupt                                               */
  #endif
  #if !defined(USE_HT32F52220_30) && !defined(USE_HT32F0008) && !defined(USE_HT32F50220_30) && !defined(USE_HT32F0006) && !defined(USE_HT32F57342_52) && !defined(USE_HT32F57331_41) && !defined(USE_HT32F50343) && !defined(USE_HT32F61244_45) && !defined(USE_HT32F50020_30) && !defined(USE_HT32F67041_51) && !defined(USE_HT32F52234_44)
  MCTM0_IRQn              = 10,     /*!< Motor Control Timer0 interrupt                                     */
  #endif
  #if defined(USE_HT32F50343)
  PWM2_IRQn               = 10,     /*!< PWM Timer2 interrupt                                               */
  #endif
  #if defined(USE_HT32F52342_52) || defined(USE_HT32F5826)
  GPTM1_IRQn              = 11,     /*!< General-Purpose Timer1 Interrupt                                   */
  #endif
  #if defined(USE_HT32F52357_67)
  QSPI_IRQn               = 11,     /*!< QSPI global Interrupt                                              */
  #endif
  #if defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41)
  LCD_IRQn                = 11,     /*!< LCD global Interrupt                                               */
  #endif
  #if defined(USE_HT32F54231_41) || defined(USE_HT32F54243_53)
  TKEY_IRQn               = 11,     /*!< Touch-Key global Interrupt                                         */
  #endif
  #if defined(USE_HT32F67041_51)
  RF_IRQn                 = 11,     /*!< 2.4G RF global Interrupt                                           */
  #endif
  #if !defined(USE_HT32F50020_30) && !defined(USE_HT32F52234_44)
  GPTM0_IRQn              = 12,     /*!< General-Purpose Timer0 Interrupt                                   */
  #endif
  #if !defined(USE_HT32F0008) && !defined(USE_HT32F50220_30) && !defined(USE_HT32F50231_41) && !defined(USE_HT32F57331_41) && !defined(USE_HT32F53231_41) && !defined(USE_HT32F53242_52) && !defined(USE_HT32F50431_41) && !defined(USE_HT32F50442_52)
  SCTM0_IRQn              = 13,     /*!< Single Channel Timer0 Interrupt                                    */
  SCTM1_IRQn              = 14,     /*!< Single Channel Timer1 Interrupt                                    */
  #endif
  #if defined(USE_HT32F52231_41) || defined(USE_HT32F52331_41) || defined(USE_HT32F52243_53) || defined(USE_HT32F0006) || defined(USE_HT32F54243_53) || defined(USE_HT32F50020_30) || defined(USE_HT32F67041_51)
  SCTM2_IRQn              = 15,     /*!< Single Channel Timer2 Interrupt                                    */
  #endif
  #if defined(USE_HT32F52231_41) || defined(USE_HT32F52331_41) || defined(USE_HT32F52243_53) || defined(USE_HT32F0006) || defined(USE_HT32F54243_53) || defined(USE_HT32F67041_51)
  SCTM3_IRQn              = 16,     /*!< Single Channel Timer3 Interrupt                                    */
  #endif
  #if defined(USE_HT32F0008) || defined(USE_HT32F50220_30) || defined(USE_HT32F50231_41) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41) || defined(USE_HT32F50343) || defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52) || defined(USE_HT32F50431_41) || defined(USE_HT32F50442_52) || defined(USE_HT32F52234_44)
  PWM0_IRQn               = 15,     /*!< PWM Timer0 Interrupt                                               */
  #endif
  #if defined(USE_HT32F0008) || defined(USE_HT32F50220_30) || defined(USE_HT32F50231_41) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41) || defined(USE_HT32F50343) || defined(USE_HT32F53242_52) || defined(USE_HT32F50442_52)
  PWM1_IRQn               = 16,     /*!< PWM Timer1 Interrupt                                               */
  #endif
  BFTM0_IRQn              = 17,     /*!< Basic Function Timer0 Interrupt                                    */
  #if !defined(USE_HT32F52220_30) && !defined(USE_HT32F50220_30) && !defined(USE_HT32F50020_30)
  BFTM1_IRQn              = 18,     /*!< Basic Function Timer1 Interrupt                                    */
  #endif
  I2C0_IRQn               = 19,     /*!< I2C0 global Interrupt                                              */
  #if !defined(USE_HT32F52220_30) && !defined(USE_HT32F0008) && !defined(USE_HT32F50220_30) && !defined(USE_HT32F52344_54) && !defined(USE_HT32F0006) && !defined(USE_HT32F61244_45) && !defined(USE_HT32F50020_30)
  I2C1_IRQn               = 20,     /*!< I2C1 global Interrupt                                              */
  #endif
  SPI0_IRQn               = 21,     /*!< SPI0 global Interrupt                                              */
  #if !defined(USE_HT32F52220_30) && !defined(USE_HT32F0008) && !defined(USE_HT32F0006) && !defined(USE_HT32F50020_30) && !defined(USE_HT32F61244_45) && !defined(USE_HT32F52234_44)
  SPI1_IRQn               = 22,     /*!< SPI1 global Interrupt                                              */
  #endif
  #if defined(USE_HT32F0006) || defined(USE_HT32F61244_45)
  QSPI_IRQn               = 22,     /*!< QSPI global Interrupt                                              */
  #endif
  #if !defined(USE_HT32F50220_30) && !defined(USE_HT32F52344_54) && !defined(USE_HT32F50343) && !defined(USE_HT32F61244_45) && !defined(USE_HT32F50020_30) && !defined(USE_HT32F67041_51)
  USART0_IRQn             = 23,     /*!< USART0 global Interrupt                                            */
  #endif
  #if defined(USE_HT32F52342_52) || defined(USE_HT32F52243_53) || defined(USE_HT32F5826) || defined(USE_HT32F52357_67) || defined(USE_HT32F54243_53) || defined(USE_HT32F53242_52) || defined(USE_HT32F50442_52)
  USART1_IRQn             = 24,     /*!< USART1 global Interrupt                                            */
  #endif
  UART0_IRQn              = 25,     /*!< UART0 global Interrupt                                             */
  #if !defined(USE_HT32F52220_30) && !defined(USE_HT32F0008) && !defined(USE_HT32F0006) && !defined(USE_HT32F61244_45) && !defined(USE_HT32F52234_44)
  UART1_IRQn              = 26,     /*!< UART1 global Interrupt                                             */
  #endif
  #if defined(USE_HT32F52357_67)
  UART0_UART2_IRQn        = 25,     /*!< UART0 & UART2 global Interrupt                                     */
  UART1_UART3_IRQn        = 26,     /*!< UART1 & UART3 global Interrupt                                     */
  #endif
  #if defined(USE_HT32F52331_41) || defined(USE_HT32F52342_52) || defined(USE_HT32F5826) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41) || defined(USE_HT32F61141)
  SCI_IRQn                = 27,     /*!< Smart Card Interface Interrupt                                     */
  #endif
  #if defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52)
  CAN0_IRQn               = 27,     /*!< CAN0 global Interrupt                                              */
  #endif
  #if defined(USE_HT32F0006) || defined(USE_HT32F61244_45)
  MIDI_IRQn               = 27,     /*!< MIDI global Interrupt                                              */
  #endif
  #if defined(USE_HT32F52342_52) || defined(USE_HT32F5826) || defined(USE_HT32F0006) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52)
  I2S_IRQn                = 28,     /*!< I2S global Interrupt                                               */
  #endif
  #if defined(USE_HT32F52243_53) || defined(USE_HT32F54243_53)
  UART2_IRQn              = 27,     /*!< UART2 global Interrupt                                             */
  UART3_IRQn              = 28,     /*!< UART3 global Interrupt                                             */
  #endif
  #if defined(USE_HT32F0008)
  AES_IRQn                = 28,     /*!< AES global Interrupt                                               */
  #endif
  #if defined(USE_HT32F50343)
  SLED0_IRQn              = 27,     /*!< SLED0 global Interrupt                                             */
  SLED1_IRQn              = 28,     /*!< SLED1 global Interrupt                                             */
  #endif
  #if defined(USE_HT32F52331_41) || defined(USE_HT32F52342_52) || defined(USE_HT32F5826) || defined(USE_HT32F0008) || defined(USE_HT32F52344_54) || defined(USE_HT32F0006) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41) || defined(USE_HT32F50343) || defined(USE_HT32F61141)
  USB_IRQn                = 29,     /*!< USB interrupt                                                      */
  #endif
  #if defined(USE_HT32F54231_41) || defined(USE_HT32F54243_53) || defined(USE_HT32F50020_30) || defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52) || defined(USE_HT32F50431_41) || defined(USE_HT32F50442_52)
  LEDC_IRQn               = 29,     /*!< LEDC global Interrupt                                              */
  #endif
  #if defined(USE_HT32F52342_52) || defined(USE_HT32F52243_53) || defined(USE_HT32F5826) || defined(USE_HT32F0008) || defined(USE_HT32F52344_54) || defined(USE_HT32F0006) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F50343) || defined(USE_HT32F54243_53) || defined(USE_HT32F61244_45) || defined(USE_HT32F67041_51) || defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52) || defined(USE_HT32F50431_41) || defined(USE_HT32F50442_52) || defined(USE_HT32F52234_44)
  PDMACH0_1_IRQn          = 30,     /*!< PDMA channel 0-1 interrupt                                         */
  PDMACH2_5_IRQn          = 31,     /*!< PDMA channel 2-5 interrupt                                         */
  #endif
  #endif
} IRQn_Type;

#define EXTI0_IRQn EXTI0_1_IRQn
#define EXTI1_IRQn EXTI0_1_IRQn
#define EXTI2_IRQn EXTI2_3_IRQn
#define EXTI3_IRQn EXTI2_3_IRQn
#if defined(USE_HT32F65230_40) || defined(USE_HT32F65232)
#define EXTI4_IRQn EXTI4_9_IRQn
#define EXTI5_IRQn EXTI4_9_IRQn
#define EXTI6_IRQn EXTI4_9_IRQn
#define EXTI7_IRQn EXTI4_9_IRQn
#define EXTI8_IRQn EXTI4_9_IRQn
#define EXTI9_IRQn EXTI4_9_IRQn
#define EXTI10_IRQn EXTI10_15_IRQn
#define EXTI11_IRQn EXTI10_15_IRQn
#define EXTI12_IRQn EXTI10_15_IRQn
#define EXTI13_IRQn EXTI10_15_IRQn
#define EXTI14_IRQn EXTI10_15_IRQn
#define EXTI15_IRQn EXTI10_15_IRQn
#elif defined(USE_HT32F50020_30)
#define EXTI4_IRQn EXTI4_7_IRQn
#define EXTI5_IRQn EXTI4_7_IRQn
#define EXTI6_IRQn EXTI4_7_IRQn
#define EXTI7_IRQn EXTI4_7_IRQn
#else
#define EXTI4_IRQn EXTI4_15_IRQn
#define EXTI5_IRQn EXTI4_15_IRQn
#define EXTI6_IRQn EXTI4_15_IRQn
#define EXTI7_IRQn EXTI4_15_IRQn
#define EXTI8_IRQn EXTI4_15_IRQn
#define EXTI9_IRQn EXTI4_15_IRQn
#define EXTI10_IRQn EXTI4_15_IRQn
#define EXTI11_IRQn EXTI4_15_IRQn
#define EXTI12_IRQn EXTI4_15_IRQn
#define EXTI13_IRQn EXTI4_15_IRQn
#define EXTI14_IRQn EXTI4_15_IRQn
#define EXTI15_IRQn EXTI4_15_IRQn
#endif

#define PDMACH0_IRQn PDMACH0_1_IRQn
#define PDMACH1_IRQn PDMACH0_1_IRQn
#if defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
#define PDMACH2_IRQn PDMACH2_3_IRQn
#define PDMACH3_IRQn PDMACH2_3_IRQn
#define PDMACH4_IRQn PDMACH4_5_IRQn
#define PDMACH5_IRQn PDMACH4_5_IRQn
#else
#define PDMACH2_IRQn PDMACH2_5_IRQn
#define PDMACH3_IRQn PDMACH2_5_IRQn
#define PDMACH4_IRQn PDMACH2_5_IRQn
#define PDMACH5_IRQn PDMACH2_5_IRQn
#endif


/**
  * @}
  */

#include "core_cm0plus.h"              /* Cortex-M0+ processor and core peripherals                         */
#include "system_ht32f5xxxx_01.h"      /* HT32 system                                                       */


/** @addtogroup Exported_Types
  * @{
  */

typedef signed long long s64;
typedef signed int     s32;
typedef signed short   s16;
typedef signed char    s8;

typedef const s64      sc64;          /*!< Read Only                                                        */
typedef const s32      sc32;          /*!< Read Only                                                        */
typedef const s16      sc16;          /*!< Read Only                                                        */
typedef const s8       sc8;           /*!< Read Only                                                        */

typedef __IO s64       vs64;
typedef __IO s32       vs32;
typedef __IO s16       vs16;
typedef __IO s8        vs8;

typedef __I s64        vsc64;         /*!< Read Only                                                        */
typedef __I s32        vsc32;         /*!< Read Only                                                        */
typedef __I s16        vsc16;         /*!< Read Only                                                        */
typedef __I s8         vsc8;          /*!< Read Only                                                        */

typedef unsigned long long u64;
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef const u64      uc64;          /*!< Read Only                                                        */
typedef const u32      uc32;          /*!< Read Only                                                        */
typedef const u16      uc16;          /*!< Read Only                                                        */
typedef const u8       uc8;           /*!< Read Only                                                        */

typedef __IO u64       vu64;
typedef __IO u32       vu32;
typedef __IO u16       vu16;
typedef __IO u8        vu8;

typedef __I u64        vuc64;         /*!< Read Only                                                        */
typedef __I u32        vuc32;         /*!< Read Only                                                        */
typedef __I u16        vuc16;         /*!< Read Only                                                        */
typedef __I u8         vuc8;          /*!< Read Only                                                        */


typedef enum {DISABLE = 0, ENABLE = !DISABLE} EventStatus, ControlStatus;

#if !defined(bool) && !defined(__cplusplus) // user may already included <stdbool.h> or CPP
typedef enum {FALSE = 0, TRUE = !FALSE} bool;
#define false FALSE
#define true  TRUE
#else
#define FALSE 0
#define TRUE  1
#endif

typedef enum {RESET = 0, SET = !RESET} FlagStatus;

typedef enum {ERROR = 0, SUCCESS = !ERROR} ErrStatus;

/**
  * @}
  */

#if defined (__CC_ARM)
  #define __ALIGN4 __align(4)
#elif defined (__ICCARM__)
  #define __ALIGN4 _Pragma("data_alignment = 4")
#elif defined (__GNUC__)
  #define __ALIGN4  __attribute__((aligned(4)))
#endif

#if defined (__GNUC__)
  #define __PACKED_H
  #define __PACKED_F __attribute__ ((packed))
#elif defined (__ICCARM__) || (__CC_ARM)
  #define __PACKED_H __packed
  #define __PACKED_F
#endif

#if defined (__CC_ARM)
#pragma anon_unions
#endif


#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)


/**
 * @brief Exported constants and macro
 */
#define IS_CONTROL_STATUS(STATUS) ((STATUS == DISABLE) || (STATUS == ENABLE))

#define wb(addr, value)     (*((u8  volatile *) (addr)) = value)
#define rb(addr)            (*((u8  volatile *) (addr)))
#define whw(addr, value)    (*((u16 volatile *) (addr)) = value)
#define rhw(addr)           (*((u16 volatile *) (addr)))
#define ww(addr, value)     (*((u32 volatile *) (addr)) = value)
#define rw(addr)            (*((u32 volatile *) (addr)))


#define ResetBit_BB(Addr, BitNumber)        (rw(Addr) &= ~(1UL << BitNumber))
#define SetBit_BB(Addr, BitNumber)          (rw(Addr) |= (1UL << BitNumber))
#define GetBit_BB(Addr, BitNumber)          ((rw(Addr) >> BitNumber) & 1UL)
#define WriteBit_BB(Addr, BitNumber, Value) (Addr = ((Addr & ~((u32)1 << BitNumber)) | ((u32)Value << BitNumber)))

#define STRCAT2_(a, b)       a##b
#define STRCAT2(a, b)        STRCAT2_(a, b)
#define STRCAT3_(a, b, c)    a##b##c
#define STRCAT3(a, b, c)     STRCAT3_(a, b, c)

#define IPN_NULL                        (0)
#define IPN_MCTM0                       (0x4002C000)
#define IPN_MCTM1                       (0x4002D000)
#define IPN_GPTM0                       (0x4006E000)
#define IPN_GPTM1                       (0x4006F000)
#define IPN_SCTM0                       (0x40034000)
#define IPN_SCTM1                       (0x40074000)
#define IPN_SCTM2                       (0x40035000)
#define IPN_SCTM3                       (0x40075000)
#define IPN_PWM0                        (0x40031000)
#define IPN_PWM1                        (0x40071000)
#define IPN_PWM2                        (0x40031000)
#define IPN_BFTM0                       (0x40076000)
#define IPN_BFTM1                       (0x40077000)
#define IPN_CHECK(IP)                   STRCAT2(IPN_, IP)
#define IS_IPN_BFTM(IP)                 (IPN_CHECK(IP) == IPN_BFTM0) || (IPN_CHECK(IP) == IPN_BFTM1)
#define IS_IPN_MCTM(IP)                 (IPN_CHECK(IP) == IPN_MCTM0) || (IPN_CHECK(IP) == IPN_MCTM1)
#define IS_IPN_GPTM(IP)                 (IPN_CHECK(IP) == IPN_GPTM0) || (IPN_CHECK(IP) == IPN_GPTM1)
#define IS_IPN_SCTM(IP)                 (IPN_CHECK(IP) == IPN_SCTM0) || (IPN_CHECK(IP) == IPN_SCTM1) || (IPN_CHECK(IP) == IPN_SCTM2) || (IPN_CHECK(IP) == IPN_SCTM3)
#define IS_IPN_PWM(IP)                  (IPN_CHECK(IP) == IPN_PWM0) || (IPN_CHECK(IP) == IPN_PWM1) || (IPN_CHECK(IP) == IPN_PWM2)
#define IS_IPN_TM(IP)                   (IS_IPN_MCTM(IP) || IS_IPN_GPTM(IP) || IS_IPN_SCTM(IP) || IS_IPN_PWM(IP))


/** @addtogroup Peripheral_Registers_Structures
  * @{
  */


/**
 * @brief Universal Synchronous Asynchronous Receiver Transmitter
 */
typedef struct
{
                                 /* USART0: 0x40000000                                                      */
                                 /* USART1: 0x40040000                                                      */
                                 /* UART0:  0x40001000                                                      */
                                 /* UART2:  0x40002000                                                      */
                                 /* UART1:  0x40041000                                                      */
                                 /* UART3:  0x40042000                                                      */
  __IO uint32_t DR;              /*!< 0x000         Data Register                                           */
  __IO uint32_t CR;              /*!< 0x004         Control Register                                        */
  __IO uint32_t FCR;             /*!< 0x008         FIFO Control Register                                   */
  __IO uint32_t IER;             /*!< 0x00C         Interrupt Enable Register                               */
  __IO uint32_t SR;              /*!< 0x010         Status Register                                         */
  __IO uint32_t TPR;             /*!< 0x014         Timing Parameter Register                               */
  __IO uint32_t ICR;             /*!< 0x018         IrDA COntrol Register                                   */
  __IO uint32_t RCR;             /*!< 0x01C         RS485 Control Register                                  */
  __IO uint32_t SCR;             /*!< 0x020         Synchronous Control Register                            */
  __IO uint32_t DLR;             /*!< 0x024         Divisor Latch Register                                  */
  __IO uint32_t DTR;             /*!< 0x028         Debug/Test Register                                     */
} HT_USART_TypeDef;


/**
 * @brief SPI
 */
typedef struct
{
                                 /* SPI0: 0x40004000                                                        */
                                 /* SPI1: 0x40044000                                                        */
  __IO uint32_t CR0;             /*!< 0x000         Control Register 0                                      */
  __IO uint32_t CR1;             /*!< 0x004         Control Register 1                                      */
  __IO uint32_t IER;             /*!< 0x008         Interrupt Enable Register                               */
  __IO uint32_t CPR;             /*!< 0x00C         Clock Prescaler Register                                */
  __IO uint32_t DR;              /*!< 0x010         Data Register                                           */
  __IO uint32_t SR;              /*!< 0x014         Status Register                                         */
  __IO uint32_t FCR;             /*!< 0x018         FIFO Control Register                                   */
  __IO uint32_t FSR;             /*!< 0x01C         FIFO Status Register                                    */
  __IO uint32_t FTOCR;           /*!< 0x020         FIFO Time Out Counter Register                          */
#if defined(USE_HT32F0006) || defined(USE_HT32F61244_45)
  __IO uint32_t MIDICR0;         /*!< 0x040         MIDI Control Register 0                                 */
  __IO uint32_t MIDICR1;         /*!< 0x044         MIDI Control Register 1                                 */
#endif
} HT_SPI_TypeDef;


#if defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
/**
 * @brief Analog to Digital Converter
 */
typedef struct
{
                                 /* ADC0: 0x40010000                                                        */
                                 /* ADC1: 0x40050000                                                        */
  __IO uint32_t CFGR;            /*!< 0x000         ADC Configuration Register (ADC1 only)                  */
  __IO uint32_t RST;             /*!< 0x004         ADC Reset Register                                      */
  __IO uint32_t CONV;            /*!< 0x008         ADC Regular Conversion Mode Register                    */
  __IO uint32_t HCONV;           /*!< 0x00C         ADC High-priority Conversion Mode Register              */
  __IO uint32_t LST[2];          /*!< 0x010 - 0x014 ADC Conversion List Register                            */
       uint32_t RESERVE0[2];     /*!< 0x018 - 0x01C Reserved                                                */
  __IO uint32_t HLST;            /*!< 0x020         ADC High-priority Conversion List Register              */
       uint32_t RESERVE1[3];     /*!< 0x024 - 0x02C Reserved                                                */
  #if defined(USE_HT32F65230_40)
  __IO uint32_t OFR[12];         /*!< 0x030 - 0x05C ADC Input Offset Register 0-11                          */
       uint32_t RESERVE2[4];     /*!< 0x060 - 0x06C Reserved                                                */
  __IO uint32_t STR[12];         /*!< 0x070 - 0x08C ADC Input Sampling Time Register 0-11                   */
       uint32_t RESERVE3[4];     /*!< 0x090 - 0x0AC Reserved                                                */
  #endif
  #if defined(USE_HT32F65232)
  __IO uint32_t OFR[15];         /*!< 0x030 - 0x068 ADC Input Offset Register 0-14                          */
       uint32_t RESERVE2[1];     /*!< 0x06C         Reserved                                                */
  __IO uint32_t STR[15];         /*!< 0x070 - 0x0A8 ADC Input Sampling Time Register 0-14                   */
       uint32_t RESERVE3[1];     /*!< 0x0AC         Reserved                                                */
  #endif
  #if defined(USE_HT32F66242)
       uint32_t RESERVE2[16];    /*!< 0x030 - 0x06C Reserved                                                */
  __IO uint32_t STR[16];         /*!< 0x070 - 0x0AC ADC Input Sampling Time Register 0-15                   */
  #endif
  #if defined(USE_HT32F66246)
       uint32_t RESERVE2[16];    /*!< 0x030 - 0x06C Reserved                                                */
  __IO uint32_t STR[16];         /*!< 0x070 - 0x0AC ADC Input Sampling Time Register 0-15                   */
  #endif
  __IO uint32_t DR[8];           /*!< 0x0B0 - 0x0CC ADC Regular Conversion Data Register 0-7                */
       uint32_t RESERVE4[8];     /*!< 0x0D0 - 0x0EC Reserved                                                */
  __IO uint32_t HDR[4];          /*!< 0x0F0 - 0x0FC ADC High-priority Conversion Data Register 0-3          */
  __IO uint32_t TCR;             /*!< 0x100         ADC Trigger Control Register                            */
  __IO uint32_t TSR;             /*!< 0x104         ADC Trigger Source Register                             */
       uint32_t RESERVE5[2];     /*!< 0x108 - 0x10C Reserved                                                */
  __IO uint32_t HTCR;            /*!< 0x110         ADC High-priority Trigger Control Register              */
  __IO uint32_t HTSR;            /*!< 0x114         ADC High-priority Trigger Source Register               */
       uint32_t RESERVE6[2];     /*!< 0x118 - 0x11C Reserved                                                */
  __IO uint32_t WCR;             /*!< 0x120         ADC Watchdog Control Register                           */
  __IO uint32_t LTR;             /*!< 0x124         ADC Watchdog Threshold Register                         */
  __IO uint32_t UTR;             /*!< 0x128         ADC Watchdog Threshold Register                         */
       uint32_t RESERVE7[1];     /*!< 0x12C         Reserved                                                */
  __IO uint32_t IER;             /*!< 0x130         ADC Interrupt Enable Register                           */
  __IO uint32_t IRAW;            /*!< 0x134         ADC Interrupt Raw Status Register                       */
  __IO uint32_t ISR;             /*!< 0x138         ADC Interrupt Status Register                           */
  __IO uint32_t ICLR;            /*!< 0x13C         ADC Interrupt Clear Register                            */
  __IO uint32_t PDMAR;           /*!< 0x140         ADC PDMA Request Register                               */
  #if defined(USE_HT32F65230_40)
       uint32_t RESERVE8[3];     /*!< 0x144 - 0x14C Reserved                                                */
  __IO uint32_t DIESR;           /*!< 0x150         Dual ADC Interrupt Enable/Status Register (ADC1 only)   */
  __IO uint32_t DPDMAR;          /*!< 0x154         Dual ADC PDMA Request Register (ADC1 only)              */
  #endif
  #if defined(USE_HT32F66242)
       uint32_t RESERVE8[3];     /*!< 0x144 - 0x14C Reserved                                                */
  __IO uint32_t VREFCR;          /*!< 0x150         ADC Reference Voltage Control Register                  */
       uint32_t RESERVE9[3];     /*!< 0x154 - 0x15C Reserved                                                */
  __IO uint32_t HDR4[8];         /*!< 0x160 - 0x17C ADC High-priority Conversion Data Register 4-11         */
       uint32_t RESERVE10[4];    /*!< 0x180 - 0x18C Reserved                                                */
  __IO uint32_t STR16[2];        /*!< 0x190 - 0x194 ADC Input Sampling Time Register 16-17                  */
  #endif
  #if defined(USE_HT32F66246)
       uint32_t RESERVE8[3];     /*!< 0x144 - 0x14C Reserved                                                */
  __IO uint32_t VREFCR;          /*!< 0x150         ADC Reference Voltage Control Register                  */
       uint32_t RESERVE9[3];     /*!< 0x154 - 0x15C Reserved                                                */
  __IO uint32_t HDR4[8];         /*!< 0x160 - 0x17C ADC High-priority Conversion Data Register 4-11         */
       uint32_t RESERVE10[4];    /*!< 0x180 - 0x18C Reserved                                                */
  __IO uint32_t STR16[2];        /*!< 0x190 - 0x194 ADC Input Sampling Time Register 16-17                  */
  #endif
} HT_ADC_TypeDef;
#else
/**
 * @brief Analog to Digital Converter
 */
typedef struct
{
                                 /* ADC: 0x40010000                                                         */
  __IO uint32_t CR;              /*!< 0x000         ADC Conversion Control Register                         */
  #if defined(USE_HT32F50020_30)
  __IO uint32_t LST[1];          /*!< 0x004         ADC Conversion List Register 0                          */
       uint32_t RESERVE0[6];     /*!< 0x008 - 0x01C Reserved                                                */
  #else
  __IO uint32_t LST[2];          /*!< 0x004 - 0x008 ADC Conversion List Register 0-1                        */
       uint32_t RESERVE0[5];     /*!< 0x00C - 0x01C Reserved                                                */
  #endif
  __IO uint32_t STR;             /*!< 0x020         ADC Input Sampling Time Register                        */
       uint32_t RESERVE1[3];     /*!< 0x024 - 0x02C Reserved                                                */
  #if defined(USE_HT32F50020_30)
  __IO uint32_t DR[4];           /*!< 0x030 - 0x03C ADC Conversion Data Register 0-3                        */
       uint32_t RESERVE2[13];    /*!< 0x040 - 0x070 Reserved                                                */
  #else
  __IO uint32_t DR[8];           /*!< 0x030 - 0x04C ADC Conversion Data Register 0-7                        */
       uint32_t RESERVE2[8];     /*!< 0x050 - 0x06C Reserved                                                */
  __IO uint32_t TCR;             /*!< 0x070         ADC Trigger Control Register                            */
  #endif
  __IO uint32_t TSR;             /*!< 0x074         ADC Trigger Source Register                             */
  #if defined(USE_HT32F50020_30)
  __IO uint32_t RESERVE3[2];     /*!< 0x078 - 0x07C Reserved                                                */
  #else
  __IO uint32_t WCR;             /*!< 0x078         ADC Watchdog Control Register                           */
  __IO uint32_t WTR;             /*!< 0x07C         ADC Watchdog Threshold Register                         */
  #endif
  __IO uint32_t IER;             /*!< 0x080         ADC Interrupt Enable Register                           */
  __IO uint32_t IRAW;            /*!< 0x084         ADC Interrupt Raw Status Register                       */
  __IO uint32_t ISR;             /*!< 0x088         ADC Interrupt Status Register                           */
  __IO uint32_t ICLR;            /*!< 0x08C         ADC Interrupt Clear Register                            */
  #if defined(USE_HT32F52342_52) || defined(USE_HT32F52243_53) || defined(USE_HT32F5826) || defined(USE_HT32F52344_54) || defined(USE_HT32F0006) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F50343) || defined(USE_HT32F54243_53) || defined(USE_HT32F61244_45) || defined(USE_HT32F67041_51) || defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52) || defined(USE_HT32F50431_41) || defined(USE_HT32F50442_52) || defined(USE_HT32F52234_44)
  __IO uint32_t PDMAR;           /*!< 0x090         ADC PDMA Request Register                               */
  #else
       uint32_t RESERVE4;        /*!< 0x090         Reserved                                                */
  #endif
  #if defined(USE_HT32F52344_54) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41) || defined(USE_HT32F50343) || defined(USE_HT32F54231_41) || defined(USE_HT32F54243_53) || defined(USE_HT32F67041_51) || defined(USE_HT32F50020_30) || defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52) || defined(USE_HT32F50431_41) || defined(USE_HT32F50442_52) || defined(USE_HT32F52234_44)
       uint32_t RESERVE5[3];     /*!< 0x094 - 0x09C Reserved                                                */
  __IO uint32_t VREFCR;          /*!< 0x0A0         ADC Reference Voltage Control Register                  */
  __IO uint32_t VREFVALR;        /*!< 0x0A4         ADC Reference Voltage Value Register                    */
  #endif
} HT_ADC_TypeDef;
#endif


/**
 * @brief Digital to Analog Converter
 */
typedef struct
{
                                 /* DACDUAL16: 0x40054000                                                   */
  __IO uint32_t CR;              /*!< 0x000         D/A Converter Control Register                          */
  __IO uint32_t RH;              /*!< 0x004         D/A R-channel data register                             */
  __IO uint32_t LH;              /*!< 0x008         D/A L-channel data register                             */
  __IO uint32_t TG;              /*!< 0x00c         D/A data trigger Register                               */
} HT_DAC_DUAL16_TypeDef;

/**
 * @brief Digital to Analog Converter Channel
 */
typedef struct
{
  __IO uint32_t CR;              /*!< 0x000         DAC Channel Control Register                            */
       uint32_t RESERVE0[2];     /*!< 0x004 - 0x008 Reserved                                                */
  __IO uint32_t DHR;             /*!< 0x00C         DAC Channel Data Holding Register                       */
  __IO uint32_t DOR;             /*!< 0x010         DAC Channel Data Output Register                        */
       uint32_t RESERVE1[3];     /*!< 0x014 - 0x01C Reserved                                                */
} HT_DACCH_TypeDef;

/**
 * @brief Digital to Analog Converter
 */
typedef struct
{
                                 /* DAC1: 0x40014000                                                        */
                                 /* DAC0: 0x40054000                                                        */
  __IO uint32_t CFGR;            /*!< 0x000         DAC Configuration Register                              */
       uint32_t RESERVE0[3];     /*!< 0x004 - 0x00C Reserved                                                */
  HT_DACCH_TypeDef DACCH0;       /*!< 0x010         DAC channel 0 registers                                 */
  HT_DACCH_TypeDef DACCH1;       /*!< 0x030         DAC channel 1 registers                                 */
} HT_DAC_TypeDef;

/**
 * @brief Comparator
 */
typedef struct
{
                                 /* CMP0: 0x40058000                                                        */
                                 /* CMP1: 0x40058100                                                        */
                                 /* CMP2: 0x40058200                                                        */
  __IO uint32_t CR;              /*!< 0x000          Comparator Control Register                            */
  __IO uint32_t VALR;            /*!< 0x004          Comparator Voltage Reference Value Register            */
  __IO uint32_t IER;             /*!< 0x008          Comparator Interrupt Enable Register                   */
  __IO uint32_t TFR;             /*!< 0x00C          Comparator Transition Flag Register                    */
  #if defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
  __IO uint32_t CI;              /*!< 0x010          Comparator Input Control Register                      */
  #endif
  #if defined(USE_HT32F65232) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
  __IO uint32_t CO;              /*!< 0x014          Comparator Output Control Register                     */
  #endif
} HT_CMP_TypeDef;


/**
 * @brief Operational Amplifier
 */
typedef struct
{
                                 /* OPA0: 0x40018000                                                        */
                                 /* OPA1: 0x40018100                                                        */
  __IO uint32_t CR;              /*!< 0x000         Operational Amplifier Control Register                  */
  #if defined(USE_HT32F65232)
  __IO uint32_t VOS;             /*!< 0x004         Operational Amplifier Input Offset Register             */
  __IO uint32_t DAC;             /*!< 0x008         Operational Amplifier Voltage Reference Value Register  */
  #endif
} HT_OPA_TypeDef;

/**
 * @brief Programmable Gain Amplifier 0~X
 */
typedef struct
{
                                 /* PGA0: 0x40018000                                                        */
                                 /* PGA1: 0x40018008                                                        */
                                 /* PGA2: 0x40018010                                                        */
                                 /* PGA3: 0x40018018                                                        */
  __IO uint32_t CR;              /*!< 0x000         Programmable Gain Amplifier Control Register            */
  __IO uint32_t VOS;             /*!< 0x004         Programmable Gain Amplifier Offset Control Register     */
} HT_PGA0_X_TypeDef;

/**
 * @brief Programmable Gain Amplifier
 */
typedef struct
{
                                 /* PGA: 0x40018000                                                         */
  __IO uint32_t VR;              /*!< 0x020         PGA Voltage Follower Control Register                   */
} HT_PGA_TypeDef;

/**
 * @brief General Purpose I/O
 */
typedef struct
{
                                 /* GPIOA: 0x400B0000                                                       */
                                 /* GPIOB: 0x400B2000                                                       */
                                 /* GPIOC: 0x400B4000                                                       */
                                 /* GPIOD: 0x400B6000                                                       */
                                 /* GPIOE: 0x400B8000                                                       */
                                 /* GPIOF: 0x400BA000                                                       */
  __IO uint32_t DIRCR;           /*!< 0x000         Data Direction Control Register                         */
  __IO uint32_t INER;            /*!< 0x004         Input function enable register                          */
  __IO uint32_t PUR;             /*!< 0x008         Pull-Up Selection Register                              */
  __IO uint32_t PDR;             /*!< 0x00C         Pull-Down Selection Register                            */
  __IO uint32_t ODR;             /*!< 0x010         Open Drain Selection Register                           */
  __IO uint32_t DRVR;            /*!< 0x014         Drive Current Selection Register                        */
  __IO uint32_t LOCKR;           /*!< 0x018         Lock Register                                           */
  __IO uint32_t DINR;            /*!< 0x01c         Data Input Register                                     */
  __IO uint32_t DOUTR;           /*!< 0x020         Data Output Register                                    */
  __IO uint32_t SRR;             /*!< 0x024         Output Set and Reset Control Register                   */
  __IO uint32_t RR;              /*!< 0x028         Output Reset Control Register                           */
  #if defined(USE_HT32F50220_30) || defined(USE_HT32F50231_41) || defined(USE_HT32F54231_41) || defined(USE_HT32F54243_53) || defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52) || defined(USE_HT32F50431_41) || defined(USE_HT32F50442_52)
  __IO uint32_t SCER;            /*!< 0x02C         Sink Current Enhanced Selection Register                */
  #endif
} HT_GPIO_TypeDef;


/**
 * @brief AFIO
 */
typedef struct
{
                                 /* AFIO: 0x40022000                                                        */
  #if defined(USE_HT32F50020_30)
  __IO uint32_t ESSR[1];         /*!< 0x000         EXTI Source Selection Register 0                        */
       uint32_t RESERVE0[7];     /*!< 0x004 - 0x01C Reserved                                                */
  #else
  __IO uint32_t ESSR[2];         /*!< 0x000         EXTI Source Selection Register 0 ~ 1                    */
       uint32_t RESERVE0[6];     /*!< 0x008 - 0x01C Reserved                                                */
  #endif
  __IO uint32_t GPACFGR[2];      /*!< 0x020         GPIO Port A Configuration Register 0 ~ 1                */
  __IO uint32_t GPBCFGR[2];      /*!< 0x028         GPIO Port B Configuration Register 0 ~ 1                */
  #if !defined(USE_HT32F52220_30)
  __IO uint32_t GPCCFGR[2];      /*!< 0x030         GPIO Port C Configuration Register 0 ~ 1                */
  #endif
  #if defined(USE_HT32F52342_52) || defined(USE_HT32F52243_53) || defined(USE_HT32F5826) || defined(USE_HT32F52344_54) || defined(USE_HT32F0006) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41) || defined(USE_HT32F54243_53) || defined(USE_HT32F61244_45) || defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52) || defined(USE_HT32F50431_41) || defined(USE_HT32F50442_52)
  __IO uint32_t GPDCFGR[2];      /*!< 0x038         GPIO Port D Configuration Register 0 ~ 1                */
  #endif
  #if defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41)
  __IO uint32_t GPECFGR[2];      /*!< 0x040         GPIO Port E Configuration Register 0 ~ 1                */
  #endif
  #if defined(USE_HT32F0008) || defined(USE_HT32F50020_30)
       uint32_t RESERVE1[4];     /*!< 0x038 - 0x044 Reserved                                                */
  __IO uint32_t GPFCFGR[2];      /*!< 0x048         GPIO Port F Configuration Register 0 ~ 1                */
  #endif
} HT_AFIO_TypeDef;


/**
 * @brief External Interrupt/Event Controller
 */
typedef struct
{
                                 /* EXTI: 0x40024000                                                        */
  __IO uint32_t CFGR0;           /*!< 0x000         EXTI Interrupt 0 Configuration Register                 */
  __IO uint32_t CFGR1;           /*!< 0x004         EXTI Interrupt 1 Configuration Register                 */
  __IO uint32_t CFGR2;           /*!< 0x008         EXTI Interrupt 2 Configuration Register                 */
  __IO uint32_t CFGR3;           /*!< 0x00C         EXTI Interrupt 3 Configuration Register                 */
  __IO uint32_t CFGR4;           /*!< 0x010         EXTI Interrupt 4 Configuration Register                 */
  __IO uint32_t CFGR5;           /*!< 0x014         EXTI Interrupt 5 Configuration Register                 */
  __IO uint32_t CFGR6;           /*!< 0x018         EXTI Interrupt 6 Configuration Register                 */
  __IO uint32_t CFGR7;           /*!< 0x01C         EXTI Interrupt 7 Configuration Register                 */
  #if defined(USE_HT32F50020_30)
  __IO uint32_t RESERVE0[8];     /*!< 0x020 - 0x3C  Reserved                                                */
  #else
  __IO uint32_t CFGR8;           /*!< 0x020         EXTI Interrupt 8 Configuration Register                 */
  __IO uint32_t CFGR9;           /*!< 0x024         EXTI Interrupt 9 Configuration Register                 */
  __IO uint32_t CFGR10;          /*!< 0x028         EXTI Interrupt 10 Configuration Register                */
  __IO uint32_t CFGR11;          /*!< 0x02C         EXTI Interrupt 11 Configuration Register                */
  __IO uint32_t CFGR12;          /*!< 0x030         EXTI Interrupt 12 Configuration Register                */
  __IO uint32_t CFGR13;          /*!< 0x034         EXTI Interrupt 13 Configuration Register                */
  __IO uint32_t CFGR14;          /*!< 0x038         EXTI Interrupt 14 Configuration Register                */
  __IO uint32_t CFGR15;          /*!< 0x03C         EXTI Interrupt 15 Configuration Register                */
  #endif
  __IO uint32_t CR;              /*!< 0x040         EXTI Interrupt Control Register                         */
  __IO uint32_t EDGEFLGR;        /*!< 0x044         EXTI Interrupt Edge Flag Register                       */
  __IO uint32_t EDGESR;          /*!< 0x048         EXTI Interrupt Edge Status Register                     */
  __IO uint32_t SSCR;            /*!< 0x04C         EXTI Interrupt Software Set Command Register            */
  __IO uint32_t WAKUPCR;         /*!< 0x050         EXTI Interrupt Wakeup Control Register                  */
  __IO uint32_t WAKUPPOLR;       /*!< 0x054         EXTI Interrupt Wakeup Polarity Register                 */
  __IO uint32_t WAKUPFLG;        /*!< 0x058         EXTI Interrupt Wakeup Flag Register                     */
} HT_EXTI_TypeDef;


/**
 * @brief Inter-integrated Circuit Interface
 */
typedef struct
{
                                 /* I2C2: 0x40008000                                                        */
                                 /* I2C0: 0x40048000                                                        */
                                 /* I2C1: 0x40049000                                                        */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t IER;             /*!< 0x004         Interrupt Enable Register                               */
  __IO uint32_t ADDR;            /*!< 0x008         Address Register                                        */
  __IO uint32_t SR;              /*!< 0x00C         Status Register                                         */
  __IO uint32_t SHPGR;           /*!< 0x010         SCL High Period Generation Register                     */
  __IO uint32_t SLPGR;           /*!< 0x014         SCL Low Period Generation Register                      */
  __IO uint32_t DR;              /*!< 0x018         Data Register                                           */
  __IO uint32_t TAR;             /*!< 0x01C         Target Register                                         */
  __IO uint32_t ADDMR;           /*!< 0x020         Address Mask Register                                   */
  __IO uint32_t ADDSR;           /*!< 0x024         Address Snoop Register                                  */
  __IO uint32_t TOUT;            /*!< 0x028         Timeout Register                                        */
} HT_I2C_TypeDef;


/**
 * @brief WATCHDOG
 */
typedef struct
{
                                 /* WDT: 0x40068000                                                         */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t MR0;             /*!< 0x004         Mode 0 Register                                         */
  __IO uint32_t MR1;             /*!< 0x008         Mode 1 Register                                         */
  __IO uint32_t SR;              /*!< 0x00C         Status Register                                         */
  __IO uint32_t PR;              /*!< 0x010         Write Protect Register                                  */
       uint32_t RESERVED0[1];    /*!< 0x014         Reserved                                                */
  __IO uint32_t CSR;             /*!< 0x018         Clock Selection Register                                */
} HT_WDT_TypeDef;


/**
 * @brief Real-Time Clock
 */
typedef struct
{
                                 /* RTC: 0x4006A000                                                         */
  __IO uint32_t CNT;             /*!< 0x000         RTC Counter Register                                    */
  __IO uint32_t CMP;             /*!< 0x004         RTC Compare Register                                    */
  __IO uint32_t CR;              /*!< 0x008         RTC Control Register                                    */
  __IO uint32_t SR;              /*!< 0x00C         RTC Status Register                                     */
  __IO uint32_t IWEN;            /*!< 0x010         RTC Interrupt/Wake-up Enable Register                   */
} HT_RTC_TypeDef;


/**
 * @brief Power Control Unit
 */
typedef struct
{
                                 /* PWRCU: 0x4006A100                                                       */
  __IO uint32_t SR;              /*!< 0x000         Status Register                                         */
  __IO uint32_t CR;              /*!< 0x004         Control Register                                        */
  #if !defined(USE_HT32F50220_30) && !defined(USE_HT32F50231_41)  && !defined(USE_HT32F65230_40) && !defined(USE_HT32F50343) && !defined(USE_HT32F54231_41) && !defined(USE_HT32F54243_53) && !defined(USE_HT32F50020_30) && !defined(USE_HT32F53231_41) && !defined(USE_HT32F53242_52) && !defined(USE_HT32F50431_41) && !defined(USE_HT32F50442_52) && !defined(USE_HT32F66242) && !defined(USE_HT32F66246)
  __IO uint32_t TEST;            /*!< 0x008         Test Register                                           */
  #else
  uint32_t RESERVE0[1];          /*!< 0x008         Reserved                                                */
  #endif
  #if defined(USE_HT32F52342_52) || defined(USE_HT32F5826) || defined(USE_HT32F52357_67)
  __IO uint32_t HSIRCR;          /*!< 0x00C         HSI Ready Counter Control Register                      */
  #else
       uint32_t RESERVE1[1];     /*!< 0x00C         Reserved                                                */
  #endif
  __IO uint32_t LVDCSR;          /*!< 0x010         Low Voltage/Brown Out Detect Control and Status Register*/
  #if defined(USE_HT32F57342_52)
       uint32_t RESERVE2[2];     /*!< 0x014 ~ 0x18  Reserved                                                */
  __IO uint32_t LDOSR   ;        /*!< 0x01C         Power Control LDO Status Register                       */
  #endif
  #if defined(USE_HT32F52342_52) || defined(USE_HT32F5826) || defined(USE_HT32F52357_67)
       uint32_t RESERVE3[59];    /*!< 0x014 ~ 0x0FC Reserved                                                */
  __IO uint32_t BAKREG[10];      /*!< 0x100 ~ 0x124 Backup Register 0 ~ 9                                   */
  #endif
} HT_PWRCU_TypeDef;


/**
 * @brief General-Purpose Timer
 */
typedef struct
{
                                 /* GPTM0: 0x4006E000                                                       */
                                 /* GPTM1: 0x4006F000                                                       */
  __IO uint32_t CNTCFR;          /*!< 0x000          Counter Configuration Register                         */
  __IO uint32_t MDCFR;           /*!< 0x004          Mode Configuration Register                            */
  __IO uint32_t TRCFR;           /*!< 0x008          Trigger Configuration Register                         */
       uint32_t RESERVED0[1];    /*!< 0x00C          Reserved                                               */
  __IO uint32_t CTR;             /*!< 0x010          Control Register                                       */
       uint32_t RESERVED1[3];    /*!< 0x014 - 0x01C  Reserved                                               */
  __IO uint32_t CH0ICFR;         /*!< 0x020          Channel-0 Input Configuration Register                 */
  __IO uint32_t CH1ICFR;         /*!< 0x024          Channel-1 Input Configuration Register                 */
  __IO uint32_t CH2ICFR;         /*!< 0x028          Channel-2 Input Configuration Register                 */
  __IO uint32_t CH3ICFR;         /*!< 0x02C          Channel-3 Input Configuration Register                 */
       uint32_t RESERVED2[4];    /*!< 0x030 - 0x03C  Reserved                                               */
  __IO uint32_t CH0OCFR;         /*!< 0x040          Channel-0 Output Configuration Register                */
  __IO uint32_t CH1OCFR;         /*!< 0x044          Channel-1 Output Configuration Register                */
  __IO uint32_t CH2OCFR;         /*!< 0x048          Channel-2 Output Configuration Register                */
  __IO uint32_t CH3OCFR;         /*!< 0x04C          Channel-3 Output Configuration Register                */
  __IO uint32_t CHCTR;           /*!< 0x050          Channel Control Register                               */
  __IO uint32_t CHPOLR;          /*!< 0x054          Channel Polarity Configuration Register                */
       uint32_t RESERVED3[7];    /*!< 0x058 - 0x070  Reserved                                               */
  __IO uint32_t DICTR;           /*!< 0x074          DMA / Interrupt Control Register                       */
  __IO uint32_t EVGR;            /*!< 0x078          Event Generator Register                               */
  __IO uint32_t INTSR;           /*!< 0x07C          Interrupt Status Register                              */
  __IO uint32_t CNTR;            /*!< 0x080          Counter Register                                       */
  __IO uint32_t PSCR;            /*!< 0x084          Prescaler Register                                     */
  __IO uint32_t CRR;             /*!< 0x088          Counter Reload Register                                */
       uint32_t RESERVED4[1];    /*!< 0x08C          Reserved                                               */
  __IO uint32_t CH0CCR;          /*!< 0x090          Channel 0 Capture/Compare Register                     */
  __IO uint32_t CH1CCR;          /*!< 0x094          Channel 1 Capture/Compare Register                     */
  __IO uint32_t CH2CCR;          /*!< 0x098          Channel 2 Capture/Compare Register                     */
  __IO uint32_t CH3CCR;          /*!< 0x09C          Channel 3 Capture/Compare Register                     */
  __IO uint32_t CH0ACR;          /*!< 0x0A0          Channel 0 Asymmetric Compare Register                  */
  __IO uint32_t CH1ACR;          /*!< 0x0A4          Channel 1 Asymmetric Compare Register                  */
  __IO uint32_t CH2ACR;          /*!< 0x0A8          Channel 2 Asymmetric Compare Register                  */
  __IO uint32_t CH3ACR;          /*!< 0x0AC          Channel 3 Asymmetric Compare Register                  */
} HT_GPTM_TypeDef;


/**
 * @brief Flash Memory Controller
 */
typedef struct
{
                                 /* FLASH: 0x40080000                                                       */
  __IO uint32_t TADR;            /*!< 0x000         Flash Target Address Register                           */
  __IO uint32_t WRDR;            /*!< 0x004         Flash Write Data Register                               */
       uint32_t RESERVED0[1];    /*!< 0x008         Reserved                                                */
  __IO uint32_t OCMR;            /*!< 0x00C         Flash Operation Command Register                        */
  __IO uint32_t OPCR;            /*!< 0x010         Flash Operation Control Register                        */
  __IO uint32_t OIER;            /*!< 0x014         Flash Operation Interrupt Enable Register               */
  __IO uint32_t OISR;            /*!< 0x018         Flash Operation Interrupt and Status Register           */
       uint32_t RESERVED1[1];    /*!< 0x01C         Reserved                                                */
  __IO uint32_t PPSR[4];         /*!< 0x020 ~ 0x02C Flash Page Erase/Program Protection Status Register     */
  __IO uint32_t CPSR;            /*!< 0x030         Flash Security Protection Status Register               */
       uint32_t RESERVED2[51];   /*!< 0x034 ~ 0x0FC Reserved                                                */
  __IO uint32_t VMCR;            /*!< 0x100         Flash Vector Mapping Control Register                   */
       uint32_t RESERVED3[31];   /*!< 0x104 ~ 0x17C Reserved                                                */
  __IO uint32_t MDID;            /*!< 0x180         Manufacturer and Device ID Register                     */
  __IO uint32_t PNSR;            /*!< 0x184         Flash Page Number Status Register                       */
  __IO uint32_t PSSR;            /*!< 0x188         Flash Page Size Status Register                         */
  __IO uint32_t DID;             /*!< 0x18C         Device ID Register                                      */
       uint32_t RESERVED4[28];   /*!< 0x190 ~ 0x1FC Reserved                                                */
  #if defined(USE_HT32F50220_30) || defined(USE_HT32F50231_41)
       uint32_t RESERVED5[1];    /*!< 0x200         Reserved                                                */
  #else
  __IO uint32_t CFCR;            /*!< 0x200         Flash Cache and Pre-fetch Control Register              */
  #endif
       uint32_t RESERVED6[67];   /*!< 0x204 ~ 0x30C Reserved                                                */
  __IO uint32_t CID[4];          /*!< 0x310 ~ 0x31C Custom ID Register                                      */
} HT_FLASH_TypeDef;


/**
 * @brief Clock Control Unit
 */
typedef struct
{
                                 /* CKCU: 0x40088000                                                        */
  __IO uint32_t GCFGR;           /*!< 0x000         Global Clock Configuration Register                     */
  __IO uint32_t GCCR;            /*!< 0x004         Global Clock Control Register                           */
  __IO uint32_t GCSR;            /*!< 0x008         Global Clock Status Register                            */
  __IO uint32_t GCIR;            /*!< 0x00C         Global Clock Interrupt Register                         */
       uint32_t RESERVED0[2];    /*!< 0x010 ~ 0x14  Reserved                                                */
  #if !defined(USE_HT32F50220_30) && !defined(USE_HT32F50231_41)
  __IO uint32_t PLLCFGR;         /*!< 0x018         PLL Configuration Register                              */
  __IO uint32_t PLLCR;           /*!< 0x01C         PLL Control Register                                    */
  #else
  uint32_t RESERVED1[2];         /*!< 0x018 ~ 0x1C  Reserved                                                */
  #endif
  __IO uint32_t AHBCFGR;         /*!< 0x020         AHB Configuration Register                              */
  __IO uint32_t AHBCCR;          /*!< 0x024         AHB Clock Control Register                              */
  #if defined(USE_HT32F0008)
       uint32_t RESERVED1[1];    /*!< 0x028         Reserved                                                */
  #else
  __IO uint32_t APBCFGR;         /*!< 0x028         APB Configuration Register                              */
  #endif
  __IO uint32_t APBCCR0;         /*!< 0x02C         APB Clock Control Register 0                            */
  __IO uint32_t APBCCR1;         /*!< 0x030         APB Clock Control Register 1                            */
  __IO uint32_t CKST;            /*!< 0x034         Clock source status Register                            */
  #if !defined(USE_HT32F50020_30)
  __IO uint32_t APBPCSR0;        /*!< 0x038         APB Peripheral Clock Selection Register 0               */
  __IO uint32_t APBPCSR1;        /*!< 0x03C         APB Peripheral Clock Selection Register 1               */
  #else
       uint32_t RESERVED2[2];     /*!< 0x038 ~ 0x3C Reserved                                                */
  #endif
  #if !defined(USE_HT32F50020_30)
  __IO uint32_t HSICR;           /*!< 0x040         HSI Control Register                                    */
  __IO uint32_t HSIATCR;         /*!< 0x044         HSI Auto Trimming Counter Register                      */
  #else
       uint32_t RESERVED3[2];  /*!< 0x040 ~ 0x44 Reserved                                                */
  #endif
  #if defined(USE_HT32F0008) || defined(USE_HT32F50220_30) || defined(USE_HT32F50231_41) || defined(USE_HT32F0006) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41) || defined(USE_HT32F50343) || defined(USE_HT32F54231_41) || defined(USE_HT32F54243_53) || defined(USE_HT32F61244_45) || defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52) || defined(USE_HT32F50431_41) || defined(USE_HT32F50442_52)
  __IO uint32_t APBPCSR2;        /*!< 0x048         APB Peripheral Clock Selection Register 2               */
       uint32_t RESERVED4[173];  /*!< 0x04C ~ 0x2FC Reserved                                                */
  #elif defined(USE_HT32F52234_44)
  __IO uint32_t APBPCSR2;        /*!< 0x048         APB Peripheral Clock Selection Register 2               */
  __IO uint32_t HSIRDYCR;        /*!< 0x04C         HSI Ready Counter Register                              */
       uint32_t RESERVED4[172];  /*!< 0x050 ~ 0x2FC Reserved                                                */
  #else
       uint32_t RESERVED4[174];  /*!< 0x048 ~ 0x2FC Reserved                                                */
  #endif
  #if !defined(USE_HT32F50020_30)
  __IO uint32_t LPCR;            /*!< 0x300         Low Power Control Register                              */
  #else
       uint32_t RESERVED5;       /*!< 0x300         Reserved                                                */
  #endif
  __IO uint32_t MCUDBGCR;        /*!< 0x304         MCU Debug Control Register                              */
} HT_CKCU_TypeDef;


/**
 * @brief Reset Control Unit
 */
typedef struct
{
                                 /* RSTCU: 0x40088100                                                       */
  __IO uint32_t GRSR;            /*!< 0x000         Global Reset Status Register                            */
  __IO uint32_t AHBPRST;         /*!< 0x004         AHB Peripheral Reset Register                           */
  __IO uint32_t APBPRST0;        /*!< 0x008         APB Peripheral Reset Register 0                         */
  __IO uint32_t APBPRST1;        /*!< 0x00C         APB Peripheral Reset Register 1                         */
} HT_RSTCU_TypeDef;


/**
 * @brief Smart Card Interface
 */
typedef struct
{
                                 /* SCI0: 0x40043000                                                        */
                                 /* SCI1: 0x4003A000                                                        */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t SR;              /*!< 0x004         Status Register                                         */
  __IO uint32_t CCR;             /*!< 0x008         Contact Control Register                                */
  __IO uint32_t ETU;             /*!< 0x00C         Elementary Time Unit Register                           */
  __IO uint32_t GT;              /*!< 0x010         Guardtime Register                                      */
  __IO uint32_t WT;              /*!< 0x014         Waiting Time Register                                   */
  __IO uint32_t IER;             /*!< 0x018         Interrupt Enable Register                               */
  __IO uint32_t IPR;             /*!< 0x01C         Interrupt Pending Register                              */
  __IO uint32_t TXB;             /*!< 0x020         Transmit Buffer Register                                */
  __IO uint32_t RXB;             /*!< 0x024         Receive Buffer Register                                 */
  __IO uint32_t PSC;             /*!< 0x028         Prescaler Register                                      */
} HT_SCI_TypeDef;


/**
 * @brief Basic Function Timer
 */
typedef struct
{
                                 /* BFTM0: 0x40076000                                                       */
                                 /* BFTM1: 0x40077000                                                       */
  __IO uint32_t CR;              /*!< 0x000          Control Register                                       */
  __IO uint32_t SR;              /*!< 0x004          Status Register                                        */
  __IO uint32_t CNTR;            /*!< 0x008          Counter Value Register                                 */
  __IO uint32_t CMP;             /*!< 0x00C          Compare Value Register                                 */
} HT_BFTM_TypeDef;


#if 0
/**
 * @brief Motor Control Timer
 */
typedef struct
{
                                 /* MCTM0: 0x4002C000                                                       */
  __IO uint32_t CNTCFR;          /*!< 0x000          Counter Configuration Register                         */
  __IO uint32_t MDCFR;           /*!< 0x004          Mode Configuration Register                            */
  __IO uint32_t TRCFR;           /*!< 0x008          Trigger Configuration Register                         */
       uint32_t RESERVED0[1];    /*!< 0x00C          Reserved                                               */
  __IO uint32_t CTR;             /*!< 0x010          Control Register                                       */
       uint32_t RESERVED1[3];    /*!< 0x014 - 0x01C  Reserved                                               */
  __IO uint32_t CH0ICFR;         /*!< 0x020          Channel-0 Input Configuration Register                 */
  __IO uint32_t CH1ICFR;         /*!< 0x024          Channel-1 Input Configuration Register                 */
  __IO uint32_t CH2ICFR;         /*!< 0x028          Channel-2 Input Configuration Register                 */
  __IO uint32_t CH3ICFR;         /*!< 0x02C          Channel-3 Input Configuration Register                 */
       uint32_t RESERVED2[4];    /*!< 0x030 - 0x03C  Reserved                                               */
  __IO uint32_t CH0OCFR;         /*!< 0x040          Channel-0 Output Configuration Register                */
  __IO uint32_t CH1OCFR;         /*!< 0x044          Channel-1 Output Configuration Register                */
  __IO uint32_t CH2OCFR;         /*!< 0x048          Channel-2 Output Configuration Register                */
  __IO uint32_t CH3OCFR;         /*!< 0x04C          Channel-3 Output Configuration Register                */
  __IO uint32_t CHCTR;           /*!< 0x050          Channel Control Register                               */
  __IO uint32_t CHPOLR;          /*!< 0x054          Channel Polarity Configuration Register                */
       uint32_t RESERVED3[5];    /*!< 0x058 - 0x068  Reserved                                               */
  __IO uint32_t CHBRKCFR;        /*!< 0x06C          Channel Break Configuration Register                   */
  __IO uint32_t CHBRKCTR;        /*!< 0x070          Channel Break Control Register                         */
  __IO uint32_t DICTR;           /*!< 0x074          DMA / Interrupt Control Register                       */
  __IO uint32_t EVGR;            /*!< 0x078          Event Generator Register                               */
  __IO uint32_t INTSR;           /*!< 0x07C          Interrupt Status Register                              */
  __IO uint32_t CNTR;            /*!< 0x080          Counter Register                                       */
  __IO uint32_t PSCR;            /*!< 0x084          Prescaler Register                                     */
  __IO uint32_t CRR;             /*!< 0x088          Counter Reload Register                                */
  __IO uint32_t REPR;            /*!< 0x08C          Repetition Register                                    */
  __IO uint32_t CH0CCR;          /*!< 0x090          Channel 0 Capture/Compare Register                     */
  __IO uint32_t CH1CCR;          /*!< 0x094          Channel 1 Capture/Compare Register                     */
  __IO uint32_t CH2CCR;          /*!< 0x098          Channel 2 Capture/Compare Register                     */
  __IO uint32_t CH3CCR;          /*!< 0x09C          Channel 3 Capture/Compare Register                     */
  __IO uint32_t CH0ACR;          /*!< 0x0A0          Channel 0 Asymmetric Compare Register                  */
  __IO uint32_t CH1ACR;          /*!< 0x0A4          Channel 1 Asymmetric Compare Register                  */
  __IO uint32_t CH2ACR;          /*!< 0x0A8          Channel 2 Asymmetric Compare Register                  */
  __IO uint32_t CH3ACR;          /*!< 0x0AC          Channel 3 Asymmetric Compare Register                  */
} HT_MCTM_TypeDef;
#endif


/**
 * @brief Timer
 */
typedef struct
{
  __IO uint32_t CNTCFR;          /*!< 0x000          Counter Configuration Register                         */
  __IO uint32_t MDCFR;           /*!< 0x004          Mode Configuration Register                            */
  __IO uint32_t TRCFR;           /*!< 0x008          Trigger Configuration Register                         */
       uint32_t RESERVED0[1];    /*!< 0x00C          Reserved                                               */
  __IO uint32_t CTR;             /*!< 0x010          Control Register                                       */
       uint32_t RESERVED1[3];    /*!< 0x014 - 0x01C  Reserved                                               */
  __IO uint32_t CH0ICFR;         /*!< 0x020          Channel-0 Input Configuration Register                 */
  __IO uint32_t CH1ICFR;         /*!< 0x024          Channel-1 Input Configuration Register                 */
  __IO uint32_t CH2ICFR;         /*!< 0x028          Channel-2 Input Configuration Register                 */
  __IO uint32_t CH3ICFR;         /*!< 0x02C          Channel-3 Input Configuration Register                 */
       uint32_t RESERVED2[4];    /*!< 0x030 - 0x03C  Reserved                                               */
  __IO uint32_t CH0OCFR;         /*!< 0x040          Channel-0 Output Configuration Register                */
  __IO uint32_t CH1OCFR;         /*!< 0x044          Channel-1 Output Configuration Register                */
  __IO uint32_t CH2OCFR;         /*!< 0x048          Channel-2 Output Configuration Register                */
  __IO uint32_t CH3OCFR;         /*!< 0x04C          Channel-3 Output Configuration Register                */
  __IO uint32_t CHCTR;           /*!< 0x050          Channel Control Register                               */
  __IO uint32_t CHPOLR;          /*!< 0x054          Channel Polarity Configuration Register                */
       uint32_t RESERVED3[5];    /*!< 0x058 - 0x068  Reserved                                               */
  __IO uint32_t CHBRKCFR;        /*!< 0x06C          Channel Break Configuration Register                   */
  __IO uint32_t CHBRKCTR;        /*!< 0x070          Channel Break Control Register                         */
  __IO uint32_t DICTR;           /*!< 0x074          DMA / Interrupt Control Register                       */
  __IO uint32_t EVGR;            /*!< 0x078          Event Generator Register                               */
  __IO uint32_t INTSR;           /*!< 0x07C          Interrupt Status Register                              */
  __IO uint32_t CNTR;            /*!< 0x080          Counter Register                                       */
  __IO uint32_t PSCR;            /*!< 0x084          Prescaler Register                                     */
  __IO uint32_t CRR;             /*!< 0x088          Counter Reload Register                                */
  __IO uint32_t REPR;            /*!< 0x08C          Repetition Register                                    */
  __IO uint32_t CH0CCR;          /*!< 0x090          Channel 0 Capture/Compare Register                     */
  __IO uint32_t CH1CCR;          /*!< 0x094          Channel 1 Capture/Compare Register                     */
  __IO uint32_t CH2CCR;          /*!< 0x098          Channel 2 Capture/Compare Register                     */
  __IO uint32_t CH3CCR;          /*!< 0x09C          Channel 3 Capture/Compare Register                     */
  __IO uint32_t CH0ACR;          /*!< 0x0A0          Channel 0 Asymmetric Compare Register                  */
  __IO uint32_t CH1ACR;          /*!< 0x0A4          Channel 1 Asymmetric Compare Register                  */
  __IO uint32_t CH2ACR;          /*!< 0x0A8          Channel 2 Asymmetric Compare Register                  */
  __IO uint32_t CH3ACR;          /*!< 0x0AC          Channel 3 Asymmetric Compare Register                  */
  #if defined(USE_HT32F50343)
       uint32_t RESERVED4[20];   /*!< 0x0B0 - 0x0FC  Reserved                                               */
  __IO uint32_t CH4OCFR;         /*!< 0x100          Channel-4 Output Configuration Register                */
  __IO uint32_t CH5OCFR;         /*!< 0x104          Channel-5 Output Configuration Register                */
  __IO uint32_t CH6OCFR;         /*!< 0x108          Channel-6 Output Configuration Register                */
  __IO uint32_t CH7OCFR;         /*!< 0x10C          Channel-7 Output Configuration Register                */
  __IO uint32_t CH4CR;           /*!< 0x110          Channel 4 Compare Register                             */
  __IO uint32_t CH5CR;           /*!< 0x114          Channel 5 Compare Register                             */
  __IO uint32_t CH6CR;           /*!< 0x118          Channel 6 Compare Register                             */
  __IO uint32_t CH7CR;           /*!< 0x11C          Channel 7 Compare Register                             */
  #endif
} HT_TM_TypeDef;


/**
 * @brief Peripheral Direct Memory Access Channel
 */
typedef struct
{
  __IO uint32_t CR;              /*!< 0x000    PDMA Channel Control Register                                */
  __IO uint32_t SADR;            /*!< 0x004    PDMA Channel Source Address Register                         */
  __IO uint32_t DADR;            /*!< 0x008    PDMA Channel Destination Address Register                    */
       uint32_t RESERVED0[1];    /*!< 0x00C    Reserved                                                     */
  __IO uint32_t TSR;             /*!< 0x010    PDMA Channel Transfer Size Register                          */
  __IO uint32_t CTSR;            /*!< 0x014    PDMA Channel Current Transfer Size Register                  */
} HT_PDMACH_TypeDef;


/**
 * @brief Peripheral Direct Memory Access Global
 */
typedef struct
{
                                  /* PDMA: 0x40090000                                                       */
  HT_PDMACH_TypeDef PDMACH0;      /*!< 0x000          PDMA channel  0 registers                             */
  HT_PDMACH_TypeDef PDMACH1;      /*!< 0x018          PDMA channel  1 registers                             */
  HT_PDMACH_TypeDef PDMACH2;      /*!< 0x030          PDMA channel  2 registers                             */
  HT_PDMACH_TypeDef PDMACH3;      /*!< 0x048          PDMA channel  3 registers                             */
  HT_PDMACH_TypeDef PDMACH4;      /*!< 0x060          PDMA channel  4 registers                             */
  HT_PDMACH_TypeDef PDMACH5;      /*!< 0x078          PDMA channel  5 registers                             */
       uint32_t     RESERVED0[36];/*!< 0x090 - 0x11C  Reserved                                              */
  __IO uint32_t     ISR;          /*!< 0x120          PDMA Interrupt Status Register                        */
       uint32_t     RESERVED1[1]; /*!< 0x124          Reserved                                              */
  __IO uint32_t     ISCR;         /*!< 0x128          PDMA Interrupt Status Clear Register                  */
       uint32_t     RESERVED2[1]; /*!< 0x12C          Reserved                                              */
  __IO uint32_t     IER;          /*!< 0x130          PDMA Interrupt Enable Register                        */
} HT_PDMA_TypeDef;


/**
 * @brief Universal Serial Bus Global
 */
typedef struct
{
                                 /* USB: 0x400A8000                                                         */
  __IO uint32_t CSR;             /*!< 0x000 USB Control and Status Register                                 */
  __IO uint32_t IER;             /*!< 0x004 USB Interrupt Enable Register                                   */
  __IO uint32_t ISR;             /*!< 0x008 USB Interrupt Status Register                                   */
  __IO uint32_t FCR;             /*!< 0x00C USB Frame Count Register                                        */
  __IO uint32_t DEVAR;           /*!< 0x010 USB Device Address Register                                     */
  __IO uint32_t EP0CSR;          /*!< 0x014 USB Endpoint 0 Control and Status Register                      */
  __IO uint32_t EP0IER;          /*!< 0x018 USB Endpoint 0 Interrupt Enable Register                        */
  __IO uint32_t EP0ISR;          /*!< 0x01C USB Endpoint 0 Interrupt Status Register                        */
  __IO uint32_t EP0TCR;          /*!< 0x020 USB Endpoint 0 Transfer Count Register                          */
  __IO uint32_t EP0CFGR;         /*!< 0x024 USB Endpoint 0 Configuration Register                           */
  __IO uint32_t EP1CSR;          /*!< 0x028 USB Endpoint 1 Control and Status Register                      */
  __IO uint32_t EP1IER;          /*!< 0x02C USB Endpoint 1 Interrupt Enable Register                        */
  __IO uint32_t EP1ISR;          /*!< 0x030 USB Endpoint 1 Interrupt Status Register                        */
  __IO uint32_t EP1TCR;          /*!< 0x034 USB Endpoint 1 Transfer Count Register                          */
  __IO uint32_t EP1CFGR;         /*!< 0x038 USB Endpoint 1 Configuration Register                           */
  __IO uint32_t EP2CSR;          /*!< 0x03C USB Endpoint 2 Control and Status Register                      */
  __IO uint32_t EP2IER;          /*!< 0x040 USB Endpoint 2 Interrupt Enable Register                        */
  __IO uint32_t EP2ISR;          /*!< 0x044 USB Endpoint 2 Interrupt Status Register                        */
  __IO uint32_t EP2TCR;          /*!< 0x048 USB Endpoint 2 Transfer Count Register                          */
  __IO uint32_t EP2CFGR;         /*!< 0x04C USB Endpoint 2 Configuration Register                           */
  __IO uint32_t EP3CSR;          /*!< 0x050 USB Endpoint 3 Control and Status Register                      */
  __IO uint32_t EP3IER;          /*!< 0x054 USB Endpoint 3 Interrupt Enable Register                        */
  __IO uint32_t EP3ISR;          /*!< 0x058 USB Endpoint 3 Interrupt Status Register                        */
  __IO uint32_t EP3TCR;          /*!< 0x05C USB Endpoint 3 Transfer Count Register                          */
  __IO uint32_t EP3CFGR;         /*!< 0x060 USB Endpoint 3 Configuration Register                           */
  __IO uint32_t EP4CSR;          /*!< 0x064 USB Endpoint 4 Control and Status Register                      */
  __IO uint32_t EP4IER;          /*!< 0x068 USB Endpoint 4 Interrupt Enable Register                        */
  __IO uint32_t EP4ISR;          /*!< 0x06C USB Endpoint 4 Interrupt Status Register                        */
  __IO uint32_t EP4TCR;          /*!< 0x070 USB Endpoint 4 Transfer Count Register                          */
  __IO uint32_t EP4CFGR;         /*!< 0x074 USB Endpoint 4 Configuration Register                           */
  __IO uint32_t EP5CSR;          /*!< 0x078 USB Endpoint 5 Control and Status Register                      */
  __IO uint32_t EP5IER;          /*!< 0x07C USB Endpoint 5 Interrupt Enable Register                        */
  __IO uint32_t EP5ISR;          /*!< 0x080 USB Endpoint 5 Interrupt Status Register                        */
  __IO uint32_t EP5TCR;          /*!< 0x084 USB Endpoint 5 Transfer Count Register                          */
  __IO uint32_t EP5CFGR;         /*!< 0x088 USB Endpoint 5 Configuration Register                           */
  __IO uint32_t EP6CSR;          /*!< 0x08C USB Endpoint 6 Control and Status Register                      */
  __IO uint32_t EP6IER;          /*!< 0x090 USB Endpoint 6 Interrupt Enable Register                        */
  __IO uint32_t EP6ISR;          /*!< 0x094 USB Endpoint 6 Interrupt Status Register                        */
  __IO uint32_t EP6TCR;          /*!< 0x098 USB Endpoint 6 Transfer Count Register                          */
  __IO uint32_t EP6CFGR;         /*!< 0x09C USB Endpoint 6 Configuration Register                           */
  __IO uint32_t EP7CSR;          /*!< 0x0A0 USB Endpoint 7 Control and Status Register                      */
  __IO uint32_t EP7IER;          /*!< 0x0A4 USB Endpoint 7 Interrupt Enable Register                        */
  __IO uint32_t EP7ISR;          /*!< 0x0A8 USB Endpoint 7 Interrupt Status Register                        */
  __IO uint32_t EP7TCR;          /*!< 0x0AC USB Endpoint 7 Transfer Count Register                          */
  __IO uint32_t EP7CFGR;         /*!< 0x0B0 USB Endpoint 7 Configuration Register                           */
  #if defined(USE_HT32F61141)
  __IO uint32_t EP8CSR;          /*!< 0x0B4 USB Endpoint 8 Control and Status Register                      */
  __IO uint32_t EP8IER;          /*!< 0x0B8 USB Endpoint 8 Interrupt Enable Register                        */
  __IO uint32_t EP8ISR;          /*!< 0x0BC USB Endpoint 8 Interrupt Status Register                        */
  __IO uint32_t EP8TCR;          /*!< 0x0C0 USB Endpoint 8 Transfer Count Register                          */
  __IO uint32_t EP8CFGR;         /*!< 0x0C4 USB Endpoint 8 Configuration Register                           */
  __IO uint32_t EP9CSR;          /*!< 0x0C8 USB Endpoint 9 Control and Status Register                      */
  __IO uint32_t EP9IER;          /*!< 0x0CC USB Endpoint 9 Interrupt Enable Register                        */
  __IO uint32_t EP9ISR;          /*!< 0x0D0 USB Endpoint 9 Interrupt Status Register                        */
  __IO uint32_t EP9TCR;          /*!< 0x0D4 USB Endpoint 9 Transfer Count Register                          */
  __IO uint32_t EP9CFGR;         /*!< 0x0D8 USB Endpoint 9 Configuration Register                           */
  #endif
} HT_USB_TypeDef;


/**
 * @brief Universal Serial Bus Endpoint
 */
typedef struct
{
                                 /* USB Endpoint0: 0x400A8014                                               */
                                 /* USB Endpoint1: 0x400A8028                                               */
                                 /* USB Endpoint2: 0x400A803C                                               */
                                 /* USB Endpoint3: 0x400A8050                                               */
                                 /* USB Endpoint4: 0x400A8064                                               */
                                 /* USB Endpoint5: 0x400A8078                                               */
                                 /* USB Endpoint6: 0x400A808C                                               */
                                 /* USB Endpoint7: 0x400A80A0                                               */
                                 /* USB Endpoint8: 0x400A80B4                                               */
                                 /* USB Endpoint9: 0x400A80C8                                               */
  __IO uint32_t CSR;             /*!< 0x000 USB Endpoint n Control and Status Register                      */
  __IO uint32_t IER;             /*!< 0x004 USB Endpoint n Interrupt Enable Register                        */
  __IO uint32_t ISR;             /*!< 0x008 USB Endpoint n Interrupt Status Register                        */
  __IO uint32_t TCR;             /*!< 0x00C USB Endpoint n Transfer Count Register                          */
  __IO uint32_t CFGR;            /*!< 0x010 USB Endpoint n Configuration Register                           */
} HT_USBEP_TypeDef;


/**
 * @brief External Bus Interface
 */
typedef struct
{
                                 /* EBI: 0x40098000                                                         */
  __IO uint32_t CR;              /*!< 0x000    EBI Control Register                                         */
       uint32_t RESERVED0[1];    /*!< 0x004    Reserved                                                     */
  __IO uint32_t SR;              /*!< 0x008    EBI Status Register                                          */
       uint32_t RESERVED1[1];    /*!< 0x00C    Reserved                                                     */
  __IO uint32_t ATR;             /*!< 0x010    EBI Address Timing Register                                  */
  __IO uint32_t RTR;             /*!< 0x014    EBI Read Timing Register                                     */
  __IO uint32_t WTR;             /*!< 0x018    EBI Write Timing Register                                    */
  __IO uint32_t PR;              /*!< 0x01C    EBI Parity Register                                          */
} HT_EBI_TypeDef;


/**
 * @brief Cyclic Redundancy Check
 */
typedef struct
{
                                 /* CRC: 0x4008A000                                                         */
  __IO uint32_t CR;              /*!< 0x000 CRC Control Register                                            */
  __IO uint32_t SDR;             /*!< 0x004 CRC Seed Register                                               */
  __IO uint32_t CSR;             /*!< 0x008 CRC Checksum Register                                           */
  __IO uint32_t DR;              /*!< 0x00C CRC Data Register                                               */
} HT_CRC_TypeDef;


/**
 * @brief Integrated Interchip Sound
 */
typedef struct
{
                                 /* I2S: 0x40026000                                                         */
  __IO uint32_t CR;              /*!< 0x000 I2S Control Register                                            */
  __IO uint32_t IER;             /*!< 0x004 I2S Interrupt Enable Register                                   */
  __IO uint32_t CDR;             /*!< 0x008 I2S Clock Divider Register                                      */
  __IO uint32_t TXDR;            /*!< 0x00C I2S TX Data Register                                            */
  __IO uint32_t RXDR;            /*!< 0x010 I2S RX Data Register                                            */
  __IO uint32_t FCR;             /*!< 0x014 I2S FIFO Control Register                                       */
  __IO uint32_t SR;              /*!< 0x018 I2S Status Register                                             */
  __IO uint32_t RCNTR;           /*!< 0x01C I2S Rate Counter Register                                       */
} HT_I2S_TypeDef;


/**
 * @brief PWM Timer
 */
typedef struct
{
                                 /* PWM0: 0x40031000                                                        */
                                 /* PWM2: 0x40032000                                                        */
                                 /* PWM1: 0x40071000                                                        */
  __IO uint32_t CNTCFR;          /*!< 0x000          Counter Configuration Register                         */
  __IO uint32_t MDCFR;           /*!< 0x004          Mode Configuration Register                            */
  __IO uint32_t TRCFR;           /*!< 0x008          Trigger Configuration Register                         */
       uint32_t RESERVED0[1];    /*!< 0x00C          Reserved                                               */
  __IO uint32_t CTR;             /*!< 0x010          Control Register                                       */
       uint32_t RESERVED1[11];   /*!< 0x014 - 0x03C  Reserved                                               */
  __IO uint32_t CH0OCFR;         /*!< 0x040          Channel-0 Output Configuration Register                */
  __IO uint32_t CH1OCFR;         /*!< 0x044          Channel-1 Output Configuration Register                */
  __IO uint32_t CH2OCFR;         /*!< 0x048          Channel-2 Output Configuration Register                */
  __IO uint32_t CH3OCFR;         /*!< 0x04C          Channel-3 Output Configuration Register                */
  __IO uint32_t CHCTR;           /*!< 0x050          Channel Control Register                               */
  __IO uint32_t CHPOLR;          /*!< 0x054          Channel Polarity Configuration Register                */
       uint32_t RESERVED2[7];    /*!< 0x058 - 0x070  Reserved                                               */
  __IO uint32_t DICTR;           /*!< 0x074          DMA / Interrupt Control Register                       */
  __IO uint32_t EVGR;            /*!< 0x078          Event Generator Register                               */
  __IO uint32_t INTSR;           /*!< 0x07C          Interrupt Status Register                              */
  __IO uint32_t CNTR;            /*!< 0x080          Counter Register                                       */
  __IO uint32_t PSCR;            /*!< 0x084          Prescaler Register                                     */
  __IO uint32_t CRR;             /*!< 0x088          Counter Reload Register                                */
       uint32_t RESERVED3[1];    /*!< 0x08C          Reserved                                               */
  __IO uint32_t CH0CR;           /*!< 0x090          Channel 0 Compare Register                             */
  __IO uint32_t CH1CR;           /*!< 0x094          Channel 1 Compare Register                             */
  __IO uint32_t CH2CR;           /*!< 0x098          Channel 2 Compare Register                             */
  __IO uint32_t CH3CR;           /*!< 0x09C          Channel 3 Compare Register                             */
  __IO uint32_t CH0ACR;          /*!< 0x0A0          Channel 0 Asymmetric Compare Register                  */
  __IO uint32_t CH1ACR;          /*!< 0x0A4          Channel 1 Asymmetric Compare Register                  */
  __IO uint32_t CH2ACR;          /*!< 0x0A8          Channel 2 Asymmetric Compare Register                  */
  __IO uint32_t CH3ACR;          /*!< 0x0AC          Channel 3 Asymmetric Compare Register                  */
  #if defined(USE_HT32F50343)
       uint32_t RESERVED4[20];   /*!< 0x0B0 - 0x0FC  Reserved                                               */
  __IO uint32_t CH4OCFR;         /*!< 0x100          Channel-4 Output Configuration Register                */
  __IO uint32_t CH5OCFR;         /*!< 0x104          Channel-5 Output Configuration Register                */
  __IO uint32_t CH6OCFR;         /*!< 0x108          Channel-6 Output Configuration Register                */
  __IO uint32_t CH7OCFR;         /*!< 0x10C          Channel-7 Output Configuration Register                */
  __IO uint32_t CH4CR;           /*!< 0x110          Channel 4 Compare Register                             */
  __IO uint32_t CH5CR;           /*!< 0x114          Channel 5 Compare Register                             */
  __IO uint32_t CH6CR;           /*!< 0x118          Channel 6 Compare Register                             */
  __IO uint32_t CH7CR;           /*!< 0x11C          Channel 7 Compare Register                             */
  #endif
} HT_PWM_TypeDef;


/**
 * @brief Single Channel Timer
 */
typedef struct
{
                                 /* SCTM0: 0x40034000                                                       */
                                 /* SCTM1: 0x40074000                                                       */
                                 /* SCTM2: 0x40035000                                                       */
                                 /* SCTM3: 0x40075000                                                       */
  __IO uint32_t CNTCFR;          /*!< 0x000          Counter Configuration Register                         */
  __IO uint32_t MDCFR;           /*!< 0x004          Mode Configuration Register                            */
  __IO uint32_t TRCFR;           /*!< 0x008          Trigger Configuration Register                         */
       uint32_t RESERVED0[1];    /*!< 0x00C          Reserved                                               */
  __IO uint32_t CTR;             /*!< 0x010          Control Register                                       */
       uint32_t RESERVED1[3];    /*!< 0x014 - 0x01C  Reserved                                               */
  __IO uint32_t CH0ICFR;         /*!< 0x020          Channel 0 Input Configuration Register                 */
  #if defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
  __IO uint32_t CH1ICFR;         /*!< 0x024          Channel 1 Input Configuration Register                 */
       uint32_t RESERVED2[6];    /*!< 0x028 - 0x03C  Reserved                                               */
  #else
       uint32_t RESERVED2[7];    /*!< 0x024 - 0x03C  Reserved                                               */
  #endif
  __IO uint32_t CHOCFR;          /*!< 0x040          Channel Output Configuration Register                  */
  #if defined(USE_HT32F50020_30)
  __IO uint32_t CH1OCFR;         /*!< 0x044          Channel 1 Output Configuration Register                */
       uint32_t RESERVED3[2];    /*!< 0x048 - 0x04C  Reserved                                               */
  #else
       uint32_t RESERVED3[3];    /*!< 0x044 - 0x04C  Reserved                                               */
  #endif
  __IO uint32_t CHCTR;           /*!< 0x050          Channel Control Register                               */
  __IO uint32_t CHPOLR;          /*!< 0x054          Channel Polarity Configuration Register                */
       uint32_t RESERVED4[7];    /*!< 0x058 - 0x070  Reserved                                               */
  __IO uint32_t DICTR;           /*!< 0x074          Interrupt Control Register                             */
  __IO uint32_t EVGR;            /*!< 0x078          Event Generator Register                               */
  __IO uint32_t INTSR;           /*!< 0x07C          Interrupt Status Register                              */
  __IO uint32_t CNTR;            /*!< 0x080          Counter Register                                       */
  __IO uint32_t PSCR;            /*!< 0x084          Prescaler Register                                     */
  __IO uint32_t CRR;             /*!< 0x088          Counter Reload Register                                */
       uint32_t RESERVED5[1];    /*!< 0x08C          Reserved                                               */
  __IO uint32_t CH0CCR;          /*!< 0x090          Channel 0 Capture/Compare Register                     */
  #if defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F50020_30) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
  __IO uint32_t CH1CCR;          /*!< 0x094          Channel 1 Capture Register                             */
  #endif
} HT_SCTM_TypeDef;


/**
 * @brief Divider
 */
typedef struct
{
                                 /* DIV: 0x400CA000                                                         */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t DDR;             /*!< 0x004         Dividend register                                       */
  __IO uint32_t DSR;             /*!< 0x008         Divisor Register                                        */
  __IO uint32_t QTR;             /*!< 0x00C         Quotient Register                                       */
  __IO uint32_t RMR;             /*!< 0x010         Remainder Register                                      */
} HT_DIV_TypeDef;


/**
 * @brief Advanced Encryption Standard
 */
typedef struct
{
                                 /* AES: 0x400C8000                                                         */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t SR;              /*!< 0x004         Status Register                                         */
  __IO uint32_t PDMAR;           /*!< 0x008         PDMA Register                                           */
  __IO uint32_t ISR;             /*!< 0x00C         Interrupt Status Register                               */
  __IO uint32_t IER;             /*!< 0x010         Interrupt Enable Register                               */
  __IO uint32_t DINR;            /*!< 0x014         Data Input Register                                     */
  __IO uint32_t DOUTR;           /*!< 0x018         Data Output Register                                    */
  #if defined(USE_HT32F52357_67)
  __IO uint32_t KEYR[8];         /*!< 0x01C - 0x038 Key Register 0~7                                        */
  #else
  __IO uint32_t KEYR[4];         /*!< 0x01C - 0x028 Key Register 0~3                                        */
       uint32_t RESERVED0[4];    /*!< 0x02C - 0x038 Reserved                                                */
  #endif
  __IO uint32_t IVR[4];          /*!< 0x03C - 0x048 Initial Vector Register 0~3                             */
} HT_AES_TypeDef;


/**
 * @brief MIDI
 */
typedef struct
{
                                 /* MIDI: 0x40060000                                                        */
  __IO uint32_t CHAN;            /*!< 0x000         MIDI Channel Number Select                              */
  __IO uint32_t FREQ;            /*!< 0x004         MIDI Frequency Number                                   */
  __IO uint32_t VOL;             /*!< 0x008         MIDI Volume Control                                     */
  __IO uint32_t ST_ADDR;         /*!< 0x00C         MIDI Start Address                                      */
  __IO uint32_t RE_NUM;          /*!< 0x010         MIDI Repeat Number                                      */
  __IO uint32_t END_ADDR;        /*!< 0x014         MIDI End Address                                        */
  __IO uint32_t IER;             /*!< 0x018         MIDI Interrupt/DMA Enable Register                      */
  __IO uint32_t SR;              /*!< 0x01C         MIDI Status Register                                    */
  __IO uint32_t MCU_CH0;         /*!< 0x020         MIDI MCU Channel 0 data                                 */
  __IO uint32_t MCU_CH1;         /*!< 0x024         MIDI MCU Channel 1 data                                 */
  __IO uint32_t MCU_CH2;         /*!< 0x028         MIDI MCU Channel 2 data                                 */
  __IO uint32_t MCU_CH3;         /*!< 0x02C         MIDI MCU Channel 3 data                                 */
  __IO uint32_t MIDIL;           /*!< 0x030         MIDI Engine Waveform of Left Channel                    */
  __IO uint32_t MIDIR;           /*!< 0x034         MIDI Engine Waveform of Right Channel                   */
  __IO uint32_t SPI_DATA;        /*!< 0x038         MIDI SPI Flash data read                                */
  __IO uint32_t SPI_ADDR;        /*!< 0x03C         MIDI SPI Flash address read                             */
  __IO uint32_t CTRL;            /*!< 0x040         MIDI Control Register                                   */
} HT_MIDI_TypeDef;


/**
 * @brief LCD
 */
typedef struct
{
                                 /* LCD: 0x4001A000                                                         */
  __IO uint32_t CR;              /*!< 0x000         Control Register                                        */
  __IO uint32_t FCR;             /*!< 0x004         Frame Control Register                                  */
  __IO uint32_t IER;             /*!< 0x008         Interrupt Enable Register                               */
  __IO uint32_t SR;              /*!< 0x00C         Status Register                                         */
  __IO uint32_t CLR;             /*!< 0x010         Clear Register                                          */
       uint32_t RESERVED[3];     /*!< 0x014 - 0x020 Reserved                                                */
  __IO uint32_t RAM[16];         /*!< 0x020 - 0x05C Display Memory                                          */
} HT_LCD_TypeDef;


/**
 * @brief Serial SLED Interface
 */
typedef struct
{
                                 /* SLED0: 0x4000E000                                                       */
                                 /* SLED1: 0x4004E000                                                       */
  __IO uint32_t CR;              /*!< 0x000  Control Register                                               */
  __IO uint32_t SR;              /*!< 0x004  Status Register                                                */
  __IO uint32_t CDR;             /*!< 0x008  Clock Divider Register                                         */
  __IO uint32_t TCR;             /*!< 0x00C  Timne Code Register                                            */
  union {
  __IO uint8_t  DR_8BIT;         /*!< 0x010  Data Register, 8-bit access, duplicate 4 times into 32-bit     */
  __IO uint16_t DR_16BIT;        /*!< 0x010  Data Register, 16-bit access, duplicate 2 times into 32-bit    */
  __IO uint32_t DR_32BIT;        /*!< 0x010  Data Register                                                  */
  };
  __IO uint32_t FCR;             /*!< 0x014  FIFO Control Register                                          */
} HT_SLED_TypeDef;


/**
 * @brief Touch Key Module
 */
typedef struct
{
  __IO uint32_t CR;              /*!< 0x000          Touch Key Module Control Register                      */
  __IO uint32_t KCFGR;           /*!< 0x004          Touch Key Module Key Configuration Register            */
  __IO uint32_t SR;              /*!< 0x008          Touch Key Module Status Register                       */
  __IO uint32_t ROCPR;           /*!< 0x00C          Touch Key Module Reference OSC Capacitor Register      */
  __IO uint32_t K3CPR;           /*!< 0x010          Touch Key Module Key 3 Capacitor Register              */
  __IO uint32_t K2CPR;           /*!< 0x014          Touch Key Module Key 2 Capacitor Register              */
  __IO uint32_t K1CPR;           /*!< 0x018          Touch Key Module Key 1 Capacitor Register              */
  __IO uint32_t K0CPR;           /*!< 0x01C          Touch Key Module Key 0 Capacitor Register              */
  __IO uint32_t CFCNTR;          /*!< 0x020          Touch Key Module C/F Counter Register                  */
  __IO uint32_t K3CNTR;          /*!< 0x024          Touch Key Module Key 3 Counter Register                */
  __IO uint32_t K2CNTR;          /*!< 0x028          Touch Key Module Key 2 Counter Register                */
  __IO uint32_t K1CNTR;          /*!< 0x02C          Touch Key Module Key 1 Counter Register                */
  __IO uint32_t K0CNTR;          /*!< 0x030          Touch Key Module Key 0 Counter Register                */
  __IO uint32_t K3THR;           /*!< 0x034          Touch Key Module Key 3 Threshold Register              */
  __IO uint32_t K2THR;           /*!< 0x038          Touch Key Module Key 2 Threshold Register              */
  __IO uint32_t K1THR;           /*!< 0x03C          Touch Key Module Key 1 Threshold Register              */
  __IO uint32_t K0THR;           /*!< 0x040          Touch Key Module Key 0 Threshold Register              */
       uint32_t RESERVED0[47];   /*!< 0x044 - 0x0FC  Reserved                                               */
} HT_TKM_TypeDef;


/**
 * @brief Touch Key
 */
typedef struct
{
                                 /* TKEY: 0x4001A000                                                        */
  __IO uint32_t  TKCR;           /*!< 0x000          Touch Key Control Register                             */
  __IO uint32_t  TKCNTR;         /*!< 0x004          Touch Key Counter Register                             */
  __IO uint32_t  TKTSCRR;        /*!< 0x008          Touch Key Time Slot Counter Reload Register            */
  __IO uint32_t  TKIER;          /*!< 0x00C          Touch Key Interrupt Enable Register                    */
  __IO uint32_t  TKSR;           /*!< 0x010          Touch Key Status Register                              */
       uint32_t  RESERVED0[59];  /*!< 0x014 - 0x0FC  Reserved                                               */
  HT_TKM_TypeDef TKM0;           /*!< 0x100          Touch Key Module 0 registers                           */
  HT_TKM_TypeDef TKM1;           /*!< 0x200          Touch Key Module 1 registers                           */
  HT_TKM_TypeDef TKM2;           /*!< 0x300          Touch Key Module 2 registers                           */
  HT_TKM_TypeDef TKM3;           /*!< 0x400          Touch Key Module 3 registers                           */
  HT_TKM_TypeDef TKM4;           /*!< 0x500          Touch Key Module 4 registers                           */
  HT_TKM_TypeDef TKM5;           /*!< 0x600          Touch Key Module 5 registers                           */
} HT_TKEY_TypeDef;


/**
 * @brief LED Controller
 */
typedef struct
{
                                 /* LEDC: 0x4005A000                                                        */
  __IO uint32_t CR;              /*!< 0x000         LED Control Register                                    */
  __IO uint32_t CER;             /*!< 0x004         LED COM Enable Register                                 */
  __IO uint32_t PCR;             /*!< 0x008         LED Polarity Control Register                           */
  __IO uint32_t IER;             /*!< 0x00C         LED Interrupt Enable Register                           */
  __IO uint32_t SR;              /*!< 0x010         LED Status Register                                     */
  __IO uint32_t DTCR;            /*!< 0x014         LED Dead Time Control Register                          */
  #if defined(USE_HT32F54231_41) || defined(USE_HT32F50020_30) || defined(USE_HT32F53231_41) || defined(USE_HT32F53242_52) || defined(USE_HT32F50431_41) || defined(USE_HT32F50442_52)
  __IO uint32_t DR[8];           /*!< 0x018 - 0x034 LED Data Register                                       */
  #endif
  #if defined(USE_HT32F54243_53)
  __IO uint32_t DR[12];          /*!< 0x018 - 0x044 LED Data Register                                       */
  #endif
} HT_LEDC_TypeDef;


/**
 * @brief Controller Area Network Interface
 */
typedef struct
{
  __IO uint32_t CREQ;            /*!< 0x000         CAN Interface Command Request Register                  */
  __IO uint32_t CMASK;           /*!< 0x004         CAN Interface Command Mask Register                     */
  __IO uint32_t MASK0;           /*!< 0x008         CAN Interface Mask Register 0                           */
  __IO uint32_t MASK1;           /*!< 0x00C         CAN Interface Mask Register 1                           */
  __IO uint32_t ARB0;            /*!< 0x010         CAN Interface Arbitration Register 0                    */
  __IO uint32_t ARB1;            /*!< 0x014         CAN Interface Arbitration Register 1                    */
  __IO uint32_t MCR;             /*!< 0x018         CAN Interface Message Control Register                  */
  __IO uint32_t DA0R;            /*!< 0x01C         CAN Interface Data A 0 Register                         */
  __IO uint32_t DA1R;            /*!< 0x020         CAN Interface Data A 1 Register                         */
  __IO uint32_t DB0R;            /*!< 0x024         CAN Interface Data B 0 Register                         */
  __IO uint32_t DB1R;            /*!< 0x028         CAN Interface Data B 1 Register                         */
} HT_CANIF_TypeDef;

/**
 * @brief Controller Area Network Global
 */
typedef struct
{
                                 /* CAN: 0x4000C000                                                         */
  __IO uint32_t    CR;           /*!< 0x000         Control Register                                        */
  __IO uint32_t    SR;           /*!< 0x004         Status Register                                         */
  __IO uint32_t    ECR;          /*!< 0x008         Error Counter Register                                  */
  __IO uint32_t    BTR;          /*!< 0x00C         Bit Timing Register                                     */
  __IO uint32_t    IR;           /*!< 0x010         Interrupt Register                                      */
  __IO uint32_t    TR;           /*!< 0x014         Test Register                                           */
  __IO uint32_t    BRPER;        /*!< 0x018         BRP Extension Register                                  */
       uint32_t    RESERVED0[1]; /*!< 0x01C         Reserved                                                */
  HT_CANIF_TypeDef IF0;          /*!< 0x020 - 0x048 CAN Interface 0 registers                               */
       uint32_t    RESERVED1[13];/*!< 0x04C - 0x07C Reserved                                                */
  HT_CANIF_TypeDef IF1;          /*!< 0x080 - 0x0A8 CAN Interface 1 registers                               */
       uint32_t    RESERVED2[21];/*!< 0x0AC - 0x0FC Reserved                                                */
  __IO uint32_t    TRR0;         /*!< 0x100         Transmission Request Register 0                         */
  __IO uint32_t    TRR1;         /*!< 0x104         Transmission Request Register 1                         */
       uint32_t    RESERVED3[6]; /*!< 0x108 - 0x11C Reserved                                                */
  __IO uint32_t    NDR0;         /*!< 0x120         New Data Register 0                                     */
  __IO uint32_t    NDR1;         /*!< 0x124         New Data Register 1                                     */
       uint32_t    RESERVED4[6]; /*!< 0x128 - 0x13C Reserved                                                */
  __IO uint32_t    IPR0;         /*!< 0x140         Interrupt Pending Register 0                            */
  __IO uint32_t    IPR1;         /*!< 0x144         Interrupt Pending Register 1                            */
       uint32_t    RESERVED5[6]; /*!< 0x148 - 0x15C Reserved                                                */
  __IO uint32_t    MVR0;         /*!< 0x160         Message Valid Register 0                                */
  __IO uint32_t    MVR1;         /*!< 0x164         Message Valid Register 1                                */
} HT_CAN_TypeDef;

/**
 * @brief Coordinate Rotation Digital Computer
 */
typedef struct
{
                                 /* CORDIC: 0x400DC000                                                      */
  __IO uint32_t    CSR;          /*!< 0x000         Control/Satus Register                                  */
  __IO uint32_t    WDATA;        /*!< 0x004         Argument Register                                       */
  __IO uint32_t    RDATA;        /*!< 0x008         Result Register                                         */
} HT_CORDIC_TypeDef;

/**
 * @brief Proportional Integral Derivative controller
 */
typedef struct
{
                                 /* PID: 0x400EC000                                                         */
  __IO uint32_t CR0;             /*!< 0x000         Control Register 0                                      */
  __IO uint32_t UI_INPUT;        /*!< 0x004                                                                 */
  __IO uint32_t ERR_n;           /*!< 0x008                                                                 */
  __IO uint32_t PID_OUT;         /*!< 0x00C                                                                 */
  __IO uint32_t SPD1ERR1;        /*!< 0x010                                                                 */
  __IO uint32_t SPD1KP;          /*!< 0x014                                                                 */
  __IO uint32_t SPD1KI;          /*!< 0x018                                                                 */
  __IO uint32_t SPD1KD;          /*!< 0x01C                                                                 */
  __IO uint32_t SPD1UI1;         /*!< 0x020                                                                 */
  __IO uint32_t SPD1UI_MAX;      /*!< 0x024                                                                 */
  __IO uint32_t SPD1UI_MIN;      /*!< 0x028                                                                 */
  __IO uint32_t SPD1_PIDOUT_LIM; /*!< 0x02C                                                                 */
  __IO uint32_t IQ1ERR1;         /*!< 0x030                                                                 */
  __IO uint32_t IQ1KP;           /*!< 0x034                                                                 */
  __IO uint32_t IQ1KI;           /*!< 0x038                                                                 */
  __IO uint32_t IQ1KD;           /*!< 0x03C                                                                 */
  __IO uint32_t IQ1UI1;          /*!< 0x040                                                                 */
  __IO uint32_t IQ1UI_MAX;       /*!< 0x044                                                                 */
  __IO uint32_t IQ1UI_MIN;       /*!< 0x048                                                                 */
  __IO uint32_t IQ1_PIDOUT_LIM;  /*!< 0x04C                                                                 */
  __IO uint32_t ID1ERR1;         /*!< 0x050                                                                 */
  __IO uint32_t ID1KP;           /*!< 0x054                                                                 */
  __IO uint32_t ID1KI;           /*!< 0x058                                                                 */
  __IO uint32_t ID1KD;           /*!< 0x05C                                                                 */
  __IO uint32_t ID1UI1;          /*!< 0x060                                                                 */
  __IO uint32_t ID1UI_MAX;       /*!< 0x064                                                                 */
  __IO uint32_t ID1UI_MIN;       /*!< 0x068                                                                 */
  __IO uint32_t ID1_PIDOUT_LIM;  /*!< 0x06C                                                                 */
  __IO uint32_t FWNK1ERR1;       /*!< 0x070                                                                 */
  __IO uint32_t FWNK1KP;         /*!< 0x074                                                                 */
  __IO uint32_t FWNK1KI;         /*!< 0x078                                                                 */
  __IO uint32_t FWNK1KD;         /*!< 0x07C                                                                 */
  __IO uint32_t FWNK1UI1;        /*!< 0x080                                                                 */
  __IO uint32_t FWNK1UI_MAX;     /*!< 0x084                                                                 */
  __IO uint32_t FWNK1UI_MIN;     /*!< 0x088                                                                 */
  __IO uint32_t FWNK1_PIDOUT_LIM;/*!< 0x08C                                                                 */
  __IO uint32_t PLL1ERR1;        /*!< 0x090                                                                 */
  __IO uint32_t PLL1KP;          /*!< 0x094                                                                 */
  __IO uint32_t PLL1KI;          /*!< 0x098                                                                 */
  __IO uint32_t PLL1KD;          /*!< 0x09C                                                                 */
  __IO uint32_t PLL1UI1;         /*!< 0x0A0                                                                 */
  __IO uint32_t PLL1UI_MAX;      /*!< 0x0A4                                                                 */
  __IO uint32_t PLL1UI_MIN;      /*!< 0x0A8                                                                 */
  __IO uint32_t PLL1_PIDOUT_LIM; /*!< 0x0AC                                                                 */
  __IO uint32_t USR1ERR1;        /*!< 0x0B0                                                                 */
  __IO uint32_t USR1KP;          /*!< 0x0B4                                                                 */
  __IO uint32_t USR1KI;          /*!< 0x0B8                                                                 */
  __IO uint32_t USR1KD;          /*!< 0x0BC                                                                 */
  __IO uint32_t USR1UI1;         /*!< 0x0C0                                                                 */
  __IO uint32_t USR1UI_MAX;      /*!< 0x0C4                                                                 */
  __IO uint32_t USR1UI_MIN;      /*!< 0x0C8                                                                 */
  __IO uint32_t USR1_PIDOUT_LIM; /*!< 0x0CC                                                                 */
} HT_PID_TypeDef;
/**
  * @}
  */

/**
 * @brief RF
 */
typedef struct
{
                                 /* RF: 0x400D0000                                                          */
  __IO uint8_t TRXADR0;          /*!< 0x000         TX/RX ADDRESS 5BYTES(LSB)                               */
  __IO uint8_t TRXADR1;          /*!< 0x001         TX/RX ADDRESS 5BYTES                                    */
  __IO uint8_t TRXADR2;          /*!< 0x002         TX/RX ADDRESS 5BYTES                                    */
  __IO uint8_t TRXADR3;          /*!< 0x003         TX/RX ADDRESS 5BYTES                                    */
  __IO uint8_t TRXADR4;          /*!< 0x004         TX/RX ADDRESS 5BYTES(MSB)                               */
  __IO uint8_t RXP1ADR0;         /*!< 0x005         RX PIPE1 ADDRESS 5BYTES(LSB)                            */
  __IO uint8_t RXP1ADR1;         /*!< 0x006         RX PIPE1 ADDRESS 5BYTES                                 */
  __IO uint8_t RXP1ADR2;         /*!< 0x007         RX PIPE1 ADDRESS 5BYTES                                 */
  __IO uint8_t RXP1ADR3;         /*!< 0x008         RX PIPE1 ADDRESS 5BYTES                                 */
  __IO uint8_t RXP1ADR4;         /*!< 0x009         RX PIPE1 ADDRESS 5BYTES(MSB)                            */
  __IO uint8_t RXP2ADR0;         /*!< 0x00A         RX PIPE2 ADDRESS 5BYTES(LSB)                            */
  __IO uint8_t RXP3ADR0;         /*!< 0x00B         RX PIPE3 ADDRESS 5BYTES(LSB)                            */
  __IO uint8_t RXP4ADR0;         /*!< 0x00C         RX PIPE4 ADDRESS 5BYTES(LSB)                            */
  __IO uint8_t RXP5ADR0;         /*!< 0x00D         RX PIPE5 ADDRESS 5BYTES(LSB)                            */
       uint8_t RESERVED0[2];     /*!< 0x00E - 0x00F Reserved                                                */
  __IO uint8_t TXFIFO;           /*!< 0x010         TX FIFO WRITE ONLY                                      */
       uint8_t RESERVED1[3];     /*!< 0x011 - 0x013 Reserved                                                */
  __IO uint8_t RXFIFO;           /*!< 0x014         RX FIFO READ ONLY                                       */
       uint8_t RESERVED2[3];     /*!< 0x015 - 0x017 Reserved                                                */
  __IO uint8_t FWREND;           /*!< 0x018         FIFO Read/Write End                                     */
  __IO uint8_t FLUSHFF;          /*!< 0x019         FLUSH TX/RX FIFO                                        */
  __IO uint8_t TXFFSEL;          /*!< 0x01A         Write TX FIFO Select ACK Payload or NACK Payload        */
  __IO uint8_t PIPESEL;          /*!< 0x01B         Write TX FIFO for PIPE ACK Payload                      */
  __IO uint8_t RFC1;             /*!< 0x01C         RF Control Register 1                                   */
  __IO uint8_t RFC2;             /*!< 0x01D         RF Control Register 2                                   */
  __IO uint8_t RFC3;             /*!< 0x01E         RF Control Register 3                                   */
       uint8_t RESERVED3[1];     /*!< 0x01F         Reserved                                                */
  __IO uint8_t CFG1;             /*!< 0x020         Configuration Control Register 1                        */
  __IO uint8_t RC1;              /*!< 0x021         Reset/Clock Control Register 1                          */
  __IO uint8_t RC2;              /*!< 0x022         Reset/Clock Control Register 2                          */
  __IO uint8_t MASK;             /*!< 0x023         Mask Control Register                                   */
  __IO uint8_t IRQ1;             /*!< 0x024         Interrupt Control Register 1                            */
  __IO uint8_t STATUS;           /*!< 0x025         FIFO Status Control Register                            */
  __IO uint8_t IO1;              /*!< 0x026         IO Control Register 1                                   */
  __IO uint8_t IO2;              /*!< 0x027         IO Control Register 2                                   */
  __IO uint8_t IO3;              /*!< 0x028         IO Control Register 3                                   */
  __IO uint8_t PKT1;             /*!< 0x029         Packet Control Register 1                               */
  __IO uint8_t PKT2;             /*!< 0x02A         Packet Control Register 2                               */
  __IO uint8_t PKT3;             /*!< 0x02B         Packet Control Register 3                               */
  __IO uint8_t PKT4;             /*!< 0x02C         Packet Control Register 4                               */
  __IO uint8_t PKT5;             /*!< 0x02D         Packet Control Register 5                               */
  __IO uint8_t MOD1;             /*!< 0x02E         Modulator Control Register 1                            */
  __IO uint8_t MOD2;             /*!< 0x02F         Modulator Control Register 2                            */
  __IO uint8_t DM1;              /*!< 0x030         De-modulator Control Register 1                         */
  __IO uint8_t DM2;              /*!< 0x031         De-modulator Control Register 2                         */
  __IO uint8_t RT1;              /*!< 0x032         PTX Retransmission Control Register 1                   */
  __IO uint8_t RT2;              /*!< 0x033         PTX Retransmission Control Register 2                   */
  __IO uint8_t CE;               /*!< 0x034         Chip Enable Control Register                            */
  __IO uint8_t CP21;             /*!< 0x035         CP Control Register 21                                  */
  __IO uint8_t CP22;             /*!< 0x036         CP Control Register 22                                  */
  __IO uint8_t CP31;             /*!< 0x037         CP Control Register 31                                  */
  __IO uint8_t CP2R;             /*!< 0x038         CP Control Register 2 for Read                          */
  __IO uint8_t CP3R;             /*!< 0x039         CP Control Register 3 for Read                          */
  __IO uint8_t CP2RX;            /*!< 0x03A         CP Control Register 2 for RX                            */
  __IO uint8_t CP3RX;            /*!< 0x03B         CP Control Register 3 for RX                            */
  __IO uint8_t PDB;              /*!< 0x03C         RF Power Down Bar Enable Control Register               */
  __IO uint8_t RF1;              /*!< 0x03D         RF RX control Register 1                                */
       uint8_t RESERVED4[2];     /*!< 0x03E - 0x03F Reserved                                                */
  __IO uint8_t OM;               /*!< 0x040         Operation Mode Control Register                         */
  __IO uint8_t CFO1;             /*!< 0x041         Carrier Frequency Offset Control Register 1             */
  __IO uint8_t SX1;              /*!< 0x042         Fractional-N Synthesizer Control Register 1             */
  __IO uint8_t SX2;              /*!< 0x043         Fractional-N Synthesizer Control Register 2             */
  __IO uint8_t SX3;              /*!< 0x044         Fractional-N Synthesizer Control Register 3             */
  __IO uint8_t SX4;              /*!< 0x045         Fractional-N Synthesizer Control Register 4             */
  __IO uint8_t STA1;             /*!< 0x046         Status Control Register 1                               */
  __IO uint8_t RSSI1;            /*!< 0x047         RSSI Control Register 1                                 */
  __IO uint8_t RSSI2;            /*!< 0x048         RSSI Control Register 2                                 */
  __IO uint8_t RSSI3;            /*!< 0x049         RSSI Control Register 3                                 */
  __IO uint8_t DPL1;             /*!< 0x04A         Dynamic Payload Length Control Register 1               */
  __IO uint8_t DPL2;             /*!< 0x04B         Dynamic Payload Length Control Register 2               */
  __IO uint8_t RXPW0;            /*!< 0x04C         RX Payload Length Control Register 0                    */
  __IO uint8_t RXPW1;            /*!< 0x04D         RX Payload Length Control Register 1                    */
  __IO uint8_t RXPW2;            /*!< 0x04E         RX Payload Length Control Register 2                    */
  __IO uint8_t RXPW3;            /*!< 0x04F         RX Payload Length Control Register 3                    */
  __IO uint8_t RXPW4;            /*!< 0x050         RX Payload Length Control Register 4                    */
  __IO uint8_t RXPW5;            /*!< 0x051         RX Payload Length Control Register 5                    */
  __IO uint8_t ENAA;             /*!< 0x052         Enable Auto-ACK Control Register                        */
  __IO uint8_t PEN;              /*!< 0x053         Pipe Enable Control Register                            */
  __IO uint8_t XO1;              /*!< 0x054         XO Control Register 1                                   */
  __IO uint8_t XO2;              /*!< 0x055         XO Control Register 2                                   */
  __IO uint8_t TXP1;             /*!< 0x056         TX Power Control Register 1                             */
  __IO uint8_t DM3;              /*!< 0x057         De-modulator Control Register 3                         */
  __IO uint8_t AGC1;             /*!< 0x058         AGC Control Register 1                                  */
  __IO uint8_t AGC2;             /*!< 0x059         AGC Control Register 2                                  */
  __IO uint8_t AGC3;             /*!< 0x05A         AGC Control Register 3                                  */
  __IO uint8_t AGC4;             /*!< 0x05B         AGC Control Register 4                                  */
  __IO uint8_t FCF1;             /*!< 0x05C         Filter Coefficient Control Register 1                   */
  __IO uint8_t FCF2;             /*!< 0x05D         Filter Coefficient Control Register 2                   */
  __IO uint8_t FCF3;             /*!< 0x05E         Filter Coefficient Control Register 3                   */
  __IO uint8_t FCF4;             /*!< 0x05F         Filter Coefficient Control Register 4                   */
  __IO uint8_t RXG;              /*!< 0x060         RX Gain Control Register                                */
  __IO uint8_t CP1;              /*!< 0x061         CP Control Register 1                                   */
  __IO uint8_t CP2;              /*!< 0x062         CP Control Register 2                                   */
  __IO uint8_t CP3;              /*!< 0x063         CP Control Register 3                                   */
  __IO uint8_t OD1;              /*!< 0x064         MMD and OD Control Register 1                           */
  __IO uint8_t OD2;              /*!< 0x065         MMD and OD Control Register 2                           */
  __IO uint8_t VC1;              /*!< 0x066         VCO Control Register 1                                  */
  __IO uint8_t VC2;              /*!< 0x067         VCO Control Register 2                                  */
  __IO uint8_t VC3;              /*!< 0x068         VCO Control Register 3                                  */
  __IO uint8_t RX1;              /*!< 0x069         RX Control Register 1                                   */
  __IO uint8_t RX2;              /*!< 0x06A         RX Control Register 2                                   */
  __IO uint8_t RX3;              /*!< 0x06B         RX Control Register 3                                   */
  __IO uint8_t RX4;              /*!< 0x06C         RX Control Register 4                                   */
  __IO uint8_t RX5;              /*!< 0x06D         RX Control Register 5                                   */
  __IO uint8_t TX1;              /*!< 0x06E         TX Control Register 1                                   */
  __IO uint8_t TX2;              /*!< 0x06F         TX Control Register 2                                   */
  __IO uint8_t TX3;              /*!< 0x070         TX Control Register 3                                   */
  __IO uint8_t CA1;              /*!< 0x071         VCO DFC Calibration Control Register 1                  */
  __IO uint8_t CA2;              /*!< 0x072         VCO DFC Calibration Control Register 2                  */
  __IO uint8_t CA3;              /*!< 0x073         VCO DFC Calibration Control Register 3                  */
  __IO uint8_t LD1;              /*!< 0x074         LDO Control Register 1                                  */
  __IO uint8_t LD2;              /*!< 0x075         LDO Control Register 2                                  */
  __IO uint8_t LD3;              /*!< 0x076         LDO Control Register 3                                  */
  __IO uint8_t RTM1;             /*!< 0x077         RF Test Mode Control Register 1                         */
       uint8_t RESERVED5[8];     /*!< 0x078 - 0x07F Reserved                                                */
  __IO uint8_t TEST1;            /*!< 0x080         Test Control Register 1                                 */
  __IO uint8_t TEST2;            /*!< 0x081         Test Control Register 2                                 */
  __IO uint8_t TEST3;            /*!< 0x082         Test Control Register 3                                 */
  __IO uint8_t TEST4;            /*!< 0x083         Test Control Register 4                                 */
  __IO uint8_t TEST5;            /*!< 0x084         Test Control Register 5                                 */
  __IO uint8_t TEST6;            /*!< 0x085         Test Control Register 6                                 */
  __IO uint8_t TEST7;            /*!< 0x086         Test Control Register 7                                 */
} HT_RF_TypeDef;
/**
  * @}
  */

/** @addtogroup Peripheral_Memory_Map
  * @{
  */

#define HT_SRAM_BASE             (0x20000000UL)

#define HT_PERIPH_BASE           (0x40000000UL)

#define HT_APBPERIPH_BASE        (HT_PERIPH_BASE)                 /* 0x40000000                             */
#define HT_AHBPERIPH_BASE        (HT_PERIPH_BASE + 0x80000)       /* 0x40080000                             */

/* APB                                                                                                      */
#define HT_USART0_BASE           (HT_APBPERIPH_BASE + 0x0000)     /* 0x40000000                             */
#define HT_UART0_BASE            (HT_APBPERIPH_BASE + 0x1000)     /* 0x40001000                             */
#define HT_UART2_BASE            (HT_APBPERIPH_BASE + 0x2000)     /* 0x40002000                             */
#define HT_SPI0_BASE             (HT_APBPERIPH_BASE + 0x4000)     /* 0x40004000                             */
#define HT_I2C2_BASE             (HT_APBPERIPH_BASE + 0x8000)     /* 0x40008000                             */
#define HT_CAN0_BASE             (HT_APBPERIPH_BASE + 0xC000)     /* 0x4000C000                             */
#define HT_SLED0_BASE            (HT_APBPERIPH_BASE + 0xE000)     /* 0x4000E000                             */
#define HT_ADC0_BASE             (HT_APBPERIPH_BASE + 0x10000)    /* 0x40010000                             */
#define HT_DAC1_BASE             (HT_APBPERIPH_BASE + 0x14000)    /* 0x40014000                             */
#define HT_OPA0_BASE             (HT_APBPERIPH_BASE + 0x18000)    /* 0x40018000                             */
#define HT_PGA0_BASE             (HT_APBPERIPH_BASE + 0x18000)    /* 0x40018000                             */
#define HT_PGA1_BASE             (HT_APBPERIPH_BASE + 0x18008)    /* 0x40018008                             */
#define HT_PGA2_BASE             (HT_APBPERIPH_BASE + 0x18010)    /* 0x40018010                             */
#define HT_PGA3_BASE             (HT_APBPERIPH_BASE + 0x18018)    /* 0x40018018                             */
#define HT_PGA_BASE              (HT_APBPERIPH_BASE + 0x18020)    /* 0x40018020                             */
#define HT_OPA1_BASE             (HT_APBPERIPH_BASE + 0x18100)    /* 0x40018100                             */
#define HT_LCD_BASE              (HT_APBPERIPH_BASE + 0x1A000)    /* 0x4001A000                             */
#define HT_TKEY_BASE             (HT_APBPERIPH_BASE + 0x1A000)    /* 0x4001A000                             */
#define HT_AFIO_BASE             (HT_APBPERIPH_BASE + 0x22000)    /* 0x40022000                             */
#define HT_EXTI_BASE             (HT_APBPERIPH_BASE + 0x24000)    /* 0x40024000                             */
#define HT_I2S_BASE              (HT_APBPERIPH_BASE + 0x26000)    /* 0x40026000                             */
#define HT_MCTM0_BASE            (HT_APBPERIPH_BASE + 0x2C000)    /* 0x4002C000                             */
#define HT_PWM0_BASE             (HT_APBPERIPH_BASE + 0x31000)    /* 0x40031000                             */
#define HT_SCTM0_BASE            (HT_APBPERIPH_BASE + 0x34000)    /* 0x40034000                             */
#define HT_PWM2_BASE             (HT_APBPERIPH_BASE + 0x32000)    /* 0x40031000                             */
#define HT_SCTM2_BASE            (HT_APBPERIPH_BASE + 0x35000)    /* 0x40035000                             */
#define HT_SCI1_BASE             (HT_APBPERIPH_BASE + 0x3A000)    /* 0x4003A000                             */
#define HT_USART1_BASE           (HT_APBPERIPH_BASE + 0x40000)    /* 0x40040000                             */
#define HT_UART1_BASE            (HT_APBPERIPH_BASE + 0x41000)    /* 0x40041000                             */
#define HT_UART3_BASE            (HT_APBPERIPH_BASE + 0x42000)    /* 0x40042000                             */
#define HT_SCI0_BASE             (HT_APBPERIPH_BASE + 0x43000)    /* 0x40043000                             */
#define HT_SPI1_BASE             (HT_APBPERIPH_BASE + 0x44000)    /* 0x40044000                             */
#define HT_I2C0_BASE             (HT_APBPERIPH_BASE + 0x48000)    /* 0x40048000                             */
#define HT_I2C1_BASE             (HT_APBPERIPH_BASE + 0x49000)    /* 0x40049000                             */
#define HT_SLED1_BASE            (HT_APBPERIPH_BASE + 0x4E000)    /* 0x4004E000                             */
#define HT_ADC1_BASE             (HT_APBPERIPH_BASE + 0x50000)    /* 0x40050000                             */
#define HT_DACDUAL16_BASE        (HT_APBPERIPH_BASE + 0x54000)    /* 0x40054000                             */
#define HT_DAC0_BASE             (HT_APBPERIPH_BASE + 0x54000)    /* 0x40054000                             */
#define HT_CMP0_BASE             (HT_APBPERIPH_BASE + 0x58000)    /* 0x40058000                             */
#define HT_CMP1_BASE             (HT_APBPERIPH_BASE + 0x58100)    /* 0x40058100                             */
#define HT_CMP2_BASE             (HT_APBPERIPH_BASE + 0x58200)    /* 0x40058200                             */
#define HT_LEDC_BASE             (HT_APBPERIPH_BASE + 0x5A000)    /* 0x4005A000                             */
#define HT_MIDI_BASE             (HT_APBPERIPH_BASE + 0x60000)    /* 0x40060000                             */
#define HT_WDT_BASE              (HT_APBPERIPH_BASE + 0x68000)    /* 0x40068000                             */
#define HT_RTC_BASE              (HT_APBPERIPH_BASE + 0x6A000)    /* 0x4006A000                             */
#define HT_PWRCU_BASE            (HT_APBPERIPH_BASE + 0x6A100)    /* 0x4006A100                             */
#define HT_GPTM0_BASE            (HT_APBPERIPH_BASE + 0x6E000)    /* 0x4006E000                             */
#define HT_GPTM1_BASE            (HT_APBPERIPH_BASE + 0x6F000)    /* 0x4006F000                             */
#define HT_PWM1_BASE             (HT_APBPERIPH_BASE + 0x71000)    /* 0x40071000                             */
#define HT_SCTM1_BASE            (HT_APBPERIPH_BASE + 0x74000)    /* 0x40074000                             */
#define HT_SCTM3_BASE            (HT_APBPERIPH_BASE + 0x75000)    /* 0x40075000                             */
#define HT_BFTM0_BASE            (HT_APBPERIPH_BASE + 0x76000)    /* 0x40076000                             */
#define HT_BFTM1_BASE            (HT_APBPERIPH_BASE + 0x77000)    /* 0x40077000                             */

/* AHB                                                                                                      */
#define HT_FLASH_BASE            (HT_AHBPERIPH_BASE + 0x0000)     /* 0x40080000                             */
#define HT_CKCU_BASE             (HT_AHBPERIPH_BASE + 0x8000)     /* 0x40088000                             */
#define HT_RSTCU_BASE            (HT_AHBPERIPH_BASE + 0x8100)     /* 0x40088100                             */
#define HT_CRC_BASE              (HT_AHBPERIPH_BASE + 0xA000)     /* 0x4008A000                             */
#define HT_PDMA_BASE             (HT_AHBPERIPH_BASE + 0x10000)    /* 0x40090000                             */
#define HT_EBI_BASE              (HT_AHBPERIPH_BASE + 0x18000)    /* 0x40098000                             */
#define HT_USB_BASE              (HT_AHBPERIPH_BASE + 0x28000)    /* 0x400A8000                             */
#define HT_USB_EP0_BASE          (HT_USB_BASE       + 0x0014)     /* 0x400A8014                             */
#define HT_USB_EP1_BASE          (HT_USB_BASE       + 0x0028)     /* 0x400A8028                             */
#define HT_USB_EP2_BASE          (HT_USB_BASE       + 0x003C)     /* 0x400A803C                             */
#define HT_USB_EP3_BASE          (HT_USB_BASE       + 0x0050)     /* 0x400A8050                             */
#define HT_USB_EP4_BASE          (HT_USB_BASE       + 0x0064)     /* 0x400A8064                             */
#define HT_USB_EP5_BASE          (HT_USB_BASE       + 0x0078)     /* 0x400A8078                             */
#define HT_USB_EP6_BASE          (HT_USB_BASE       + 0x008C)     /* 0x400A808C                             */
#define HT_USB_EP7_BASE          (HT_USB_BASE       + 0x00A0)     /* 0x400A80A0                             */
#define HT_USB_EP8_BASE          (HT_USB_BASE       + 0x00B4)     /* 0x400A80B4                             */
#define HT_USB_EP9_BASE          (HT_USB_BASE       + 0x00C8)     /* 0x400A80C8                             */
#define HT_USB_SRAM_BASE         (HT_AHBPERIPH_BASE + 0x2A000)    /* 0x400AA000                             */
#define HT_GPIOA_BASE            (HT_AHBPERIPH_BASE + 0x30000)    /* 0x400B0000                             */
#define HT_GPIOB_BASE            (HT_AHBPERIPH_BASE + 0x32000)    /* 0x400B2000                             */
#define HT_GPIOC_BASE            (HT_AHBPERIPH_BASE + 0x34000)    /* 0x400B4000                             */
#define HT_GPIOD_BASE            (HT_AHBPERIPH_BASE + 0x36000)    /* 0x400B6000                             */
#define HT_GPIOE_BASE            (HT_AHBPERIPH_BASE + 0x38000)    /* 0x400B8000                             */
#define HT_GPIOF_BASE            (HT_AHBPERIPH_BASE + 0x3A000)    /* 0x400BA000                             */
#define HT_AES_BASE              (HT_AHBPERIPH_BASE + 0x48000)    /* 0x400C8000                             */
#define HT_DIV_BASE              (HT_AHBPERIPH_BASE + 0x4A000)    /* 0x400CA000                             */
#define HT_RF_BASE               (HT_AHBPERIPH_BASE + 0x50000)    /* 0x400D0000                             */
#define HT_CORDIC_BASE           (HT_AHBPERIPH_BASE + 0x5C000)    /* 0x400DC000                             */
#define HT_PID_BASE              (HT_AHBPERIPH_BASE + 0x5E000)    /* 0x400DE000                             */
#define HT_QSPI_BASE             (HT_AHBPERIPH_BASE + 0x60000)    /* 0x400E0000                             */

/**
  * @}
  */

/* Peripheral declaration                                                                                   */
#define HT_FLASH                 ((HT_FLASH_TypeDef *) HT_FLASH_BASE)
#define HT_CKCU                  ((HT_CKCU_TypeDef *) HT_CKCU_BASE)
#define HT_PWRCU                 ((HT_PWRCU_TypeDef *) HT_PWRCU_BASE)
#define HT_RSTCU                 ((HT_RSTCU_TypeDef *) HT_RSTCU_BASE)
#define HT_AFIO                  ((HT_AFIO_TypeDef *) HT_AFIO_BASE)
#define HT_EXTI                  ((HT_EXTI_TypeDef *) HT_EXTI_BASE)
#define HT_GPIOA                 ((HT_GPIO_TypeDef *) HT_GPIOA_BASE)
#define HT_GPIOB                 ((HT_GPIO_TypeDef *) HT_GPIOB_BASE)
#define HT_BFTM0                 ((HT_BFTM_TypeDef *) HT_BFTM0_BASE)
#define HT_WDT                   ((HT_WDT_TypeDef *) HT_WDT_BASE)
#define HT_UART0                 ((HT_USART_TypeDef *) HT_UART0_BASE)
#define HT_SPI0                  ((HT_SPI_TypeDef *) HT_SPI0_BASE)
#define HT_I2C0                  ((HT_I2C_TypeDef *) HT_I2C0_BASE)

#if !defined(USE_HT32F50020_30) && !defined(USE_HT32F52234_44)
#define HT_GPTM0                 ((HT_TM_TypeDef *) HT_GPTM0_BASE)
#endif

#if !defined(USE_HT32F0008) && !defined(USE_HT32F61141)
#define HT_ADC0                  ((HT_ADC_TypeDef *) HT_ADC0_BASE)
#endif

#if !defined(USE_HT32F0008) && !defined(USE_HT32F50220_30) && !defined(USE_HT32F50231_41) && !defined(USE_HT32F57331_41) && !defined(USE_HT32F53231_41) && !defined(USE_HT32F53242_52) && !defined(USE_HT32F50431_41) && !defined(USE_HT32F50442_52)
#define HT_SCTM0                 ((HT_TM_TypeDef *) HT_SCTM0_BASE)
#define HT_SCTM1                 ((HT_TM_TypeDef *) HT_SCTM1_BASE)
#endif

#if defined(USE_HT32F52231_41) || defined(USE_HT32F52331_41) || defined(USE_HT32F52243_53) || defined(USE_HT32F0006) || defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F54243_53) || defined(USE_HT32F50020_30) || defined(USE_HT32F67041_51) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
#define HT_SCTM2                 ((HT_TM_TypeDef *) HT_SCTM2_BASE)
#endif

#if defined(USE_HT32F52231_41) || defined(USE_HT32F52331_41) || defined(USE_HT32F52243_53) || defined(USE_HT32F0006) || defined(USE_HT32F65230_40) || defined(USE_HT32F65232) || defined(USE_HT32F54243_53) || defined(USE_HT32F67041_51) || defined(USE_HT32F66242) || defined(USE_HT32F66246)
#define HT_SCTM3                 ((HT_TM_TypeDef *) HT_SCTM3_BASE)
#endif

#if !defined(USE_HT32F50220_30) && !defined(USE_HT32F52344_54) && !defined(USE_HT32F50343) && !defined(USE_HT32F61141) && !defined(USE_HT32F61244_45) && !defined(USE_HT32F50020_30) && !defined(USE_HT32F67041_51)
#define HT_USART0                ((HT_USART_TypeDef *) HT_USART0_BASE)
#endif

#if defined(USE_HT32F52331_41) || defined(USE_HT32F52342_52) || defined(USE_HT32F5826) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41) || defined(USE_HT32F61141)
#define HT_SCI0                  ((HT_SCI_TypeDef *) HT_SCI0_BASE)
#endif

#if defined(USE_HT32F52331_41) || defined(USE_HT32F52342_52) || defined(USE_HT32F5826) || defined(USE_HT32F0008) || defined(USE_HT32F52344_54) || defined(USE_HT32F0006) || defined(USE_HT32F52357_67) || defined(USE_HT32F57342_52) || defined(USE_HT32F57331_41) || defined(USE_HT32F50343) || defined(USE_HT32F61141)
#define HT_USB                   ((HT_USB_TypeDef *) HT_USB_BASE)
#define HT_USBEP0                ((HT_USBEP_TypeDef *) HT_USB_EP0_BASE)
#define HT_USBEP1                ((HT_USBEP_TypeDef *) HT_USB_EP1_BASE)
#define HT_USBEP2                ((HT_USBEP_TypeDef *) HT_USB_EP2_BASE)
#define HT_USBEP3                ((HT_USBEP_TypeDef *) HT_USB_EP3_BASE)
#define HT_USBEP4                ((HT_USBEP_TypeDef *) HT_USB_EP4_BASE)
#define HT_USBEP5                ((HT_USBEP_TypeDef *) HT_USB_EP5_BASE)
#define HT_USBEP6                ((HT_USBEP_TypeDef *) HT_USB_EP6_BASE)
#define HT_USBEP7                ((HT_USBEP_TypeDef *) HT_USB_EP7_BASE)
#endif

#if defined(USE_HT32F52231_41) || defined(USE_HT32F52331_41)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#endif

#if defined(USE_HT32F52342_52) || defined(USE_HT32F5826)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_GPTM1                 ((HT_TM_TypeDef *) HT_GPTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_SCI1                  ((HT_SCI_TypeDef *) HT_SCI1_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#define HT_I2S                   ((HT_I2S_TypeDef *) HT_I2S_BASE)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#endif

#if defined(USE_HT32F52243_53)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_UART2                 ((HT_USART_TypeDef *) HT_UART2_BASE)
#define HT_UART3                 ((HT_USART_TypeDef *) HT_UART3_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_I2C2                  ((HT_I2C_TypeDef *) HT_I2C2_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#endif

#if defined(USE_HT32F0008)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_PWM1                  ((HT_TM_TypeDef *) HT_PWM1_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_AES                   ((HT_AES_TypeDef *) HT_AES_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOF                 ((HT_GPIO_TypeDef *) HT_GPIOF_BASE)
#endif

#if defined(USE_HT32F50220_30)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_PWM1                  ((HT_TM_TypeDef *) HT_PWM1_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#endif

#if defined(USE_HT32F50231_41)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_PWM1                  ((HT_TM_TypeDef *) HT_PWM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#endif

#if defined(USE_HT32F52344_54)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#endif

#if defined(USE_HT32F0006)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#define HT_QSPI                  ((HT_SPI_TypeDef *) HT_QSPI_BASE)
#define HT_I2S                   ((HT_I2S_TypeDef *) HT_I2S_BASE)
#define HT_DACDUAL16             ((HT_DAC_DUAL16_TypeDef *) HT_DACDUAL16_BASE)
#define HT_MIDI                  ((HT_MIDI_TypeDef *) HT_MIDI_BASE)
#endif

#if defined(USE_HT32F52357_67)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_DAC0                  ((HT_DAC_TypeDef *) HT_DAC0_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_PWM1                  ((HT_TM_TypeDef *) HT_PWM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_SCI1                  ((HT_SCI_TypeDef *) HT_SCI1_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#define HT_I2S                   ((HT_I2S_TypeDef *) HT_I2S_BASE)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_UART2                 ((HT_USART_TypeDef *) HT_UART2_BASE)
#define HT_UART3                 ((HT_USART_TypeDef *) HT_UART3_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_QSPI                  ((HT_SPI_TypeDef *) HT_QSPI_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_AES                   ((HT_AES_TypeDef *) HT_AES_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#define HT_GPIOE                 ((HT_GPIO_TypeDef *) HT_GPIOE_BASE)
#endif

#if defined(USE_HT32F57342_52)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_DAC0                  ((HT_DAC_TypeDef *) HT_DAC0_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_PWM1                  ((HT_TM_TypeDef *) HT_PWM1_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_SCI1                  ((HT_SCI_TypeDef *) HT_SCI1_BASE)
#define HT_I2S                   ((HT_I2S_TypeDef *) HT_I2S_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_AES                   ((HT_AES_TypeDef *) HT_AES_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#define HT_GPIOE                 ((HT_GPIO_TypeDef *) HT_GPIOE_BASE)
#define HT_LCD                   ((HT_LCD_TypeDef *) HT_LCD_BASE)
#endif

#if defined(USE_HT32F57331_41)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_PWM1                  ((HT_TM_TypeDef *) HT_PWM1_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#define HT_LCD                   ((HT_LCD_TypeDef *) HT_LCD_BASE)
#endif

#if defined(USE_HT32F65230_40)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_ADC1                  ((HT_ADC_TypeDef *) HT_ADC1_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_CMP2                  ((HT_CMP_TypeDef *) HT_CMP2_BASE)
#define HT_OPA0                  ((HT_OPA_TypeDef *) HT_OPA0_BASE)
#define HT_OPA1                  ((HT_OPA_TypeDef *) HT_OPA1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#endif

#if defined(USE_HT32F65232)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_OPA0                  ((HT_OPA_TypeDef *) HT_OPA0_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#endif

#if defined(USE_HT32F50343)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_PWM1                  ((HT_TM_TypeDef *) HT_PWM1_BASE)
#define HT_PWM2                  ((HT_TM_TypeDef *) HT_PWM2_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_SLED0                 ((HT_SLED_TypeDef *) HT_SLED0_BASE)
#define HT_SLED1                 ((HT_SLED_TypeDef *) HT_SLED1_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#endif

#if defined(USE_HT32F54231_41)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_TKEY                  ((HT_TKEY_TypeDef *) HT_TKEY_BASE)
#define HT_LEDC                  ((HT_LEDC_TypeDef *) HT_LEDC_BASE)
#endif

#if defined(USE_HT32F54243_53)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_UART2                 ((HT_USART_TypeDef *) HT_UART2_BASE)
#define HT_UART3                 ((HT_USART_TypeDef *) HT_UART3_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_I2C2                  ((HT_I2C_TypeDef *) HT_I2C2_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#define HT_TKEY                  ((HT_TKEY_TypeDef *) HT_TKEY_BASE)
#define HT_LEDC                  ((HT_LEDC_TypeDef *) HT_LEDC_BASE)
#endif

#if defined(USE_HT32F61141)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SCI1                  ((HT_SCI_TypeDef *) HT_SCI1_BASE)
#define HT_USBEP8                ((HT_USBEP_TypeDef *) HT_USB_EP8_BASE)
#define HT_USBEP9                ((HT_USBEP_TypeDef *) HT_USB_EP9_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#endif

#if defined(USE_HT32F61244_45)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_LSTM0                 ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#define HT_QSPI                  ((HT_SPI_TypeDef *) HT_QSPI_BASE)
#define HT_DACDUAL16             ((HT_DAC_DUAL16_TypeDef *) HT_DACDUAL16_BASE)
#define HT_MIDI                  ((HT_MIDI_TypeDef *) HT_MIDI_BASE)

#define HT_RTC HT_LSTM0
#endif

#if defined(USE_HT32F50020_30)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOF                 ((HT_GPIO_TypeDef *) HT_GPIOF_BASE)
#define HT_LEDC                  ((HT_LEDC_TypeDef *) HT_LEDC_BASE)
#endif

#if defined(USE_HT32F67041_51)
#define HT_AES                   ((HT_AES_TypeDef *) HT_AES_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_RF                    ((HT_RF_TypeDef *) HT_RF_BASE)
#endif

#if defined(USE_HT32F50442_52)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_PWM1                  ((HT_TM_TypeDef *) HT_PWM1_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_LEDC                  ((HT_LEDC_TypeDef *) HT_LEDC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#endif

#if defined(USE_HT32F50431_41)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_LEDC                  ((HT_LEDC_TypeDef *) HT_LEDC_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#endif

#if defined(USE_HT32F53242_52)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_PWM1                  ((HT_TM_TypeDef *) HT_PWM1_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_EBI                   ((HT_EBI_TypeDef *) HT_EBI_BASE)
#define HT_USART1                ((HT_USART_TypeDef *) HT_USART1_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_LEDC                  ((HT_LEDC_TypeDef *) HT_LEDC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_CAN0                  ((HT_CAN_TypeDef *) HT_CAN0_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#endif

#if defined(USE_HT32F53231_41)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_UART1                 ((HT_USART_TypeDef *) HT_UART1_BASE)
#define HT_SPI1                  ((HT_SPI_TypeDef *) HT_SPI1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_LEDC                  ((HT_LEDC_TypeDef *) HT_LEDC_BASE)
#define HT_CAN0                  ((HT_CAN_TypeDef *) HT_CAN0_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_GPIOD                 ((HT_GPIO_TypeDef *) HT_GPIOD_BASE)
#endif

#if defined(USE_HT32F66242)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_PGA0                  ((HT_PGA0_X_TypeDef *) HT_PGA0_BASE)
#define HT_PGA1                  ((HT_PGA0_X_TypeDef *) HT_PGA1_BASE)
#define HT_PGA2                  ((HT_PGA0_X_TypeDef *) HT_PGA2_BASE)
#define HT_PGA3                  ((HT_PGA0_X_TypeDef *) HT_PGA3_BASE)
#define HT_PGA                   ((HT_PGA_TypeDef *) HT_PGA_BASE)
#define HT_PID                   ((HT_LCD_TypeDef *) HT_LCD_BASE)
#define HT_CORDIC                ((HT_CORDIC_TypeDef *) HT_CORDIC_BASE)
#define HT_LSTM0                 ((HT_RTC_TypeDef *) HT_RTC_BASE)

#define HT_RTC HT_LSTM0
#endif

#if defined(USE_HT32F66246)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_CMP0                  ((HT_CMP_TypeDef *) HT_CMP0_BASE)
#define HT_CMP1                  ((HT_CMP_TypeDef *) HT_CMP1_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_MCTM0                 ((HT_TM_TypeDef *) HT_MCTM0_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#define HT_CAN0                  ((HT_CAN_TypeDef *) HT_CAN0_BASE)
#define HT_PGA0                  ((HT_PGA0_X_TypeDef *) HT_PGA0_BASE)
#define HT_PGA1                  ((HT_PGA0_X_TypeDef *) HT_PGA1_BASE)
#define HT_PGA2                  ((HT_PGA0_X_TypeDef *) HT_PGA2_BASE)
#define HT_PGA3                  ((HT_PGA0_X_TypeDef *) HT_PGA3_BASE)
#define HT_PGA                   ((HT_PGA_TypeDef *) HT_PGA_BASE)
#define HT_PID                   ((HT_LCD_TypeDef *) HT_LCD_BASE)
#define HT_CORDIC                ((HT_CORDIC_TypeDef *) HT_CORDIC_BASE)
#define HT_LSTM0                 ((HT_RTC_TypeDef *) HT_RTC_BASE)

#define HT_RTC HT_LSTM0
#endif

#if defined(USE_HT32F52234_44)
#define HT_PDMA                  ((HT_PDMA_TypeDef *) HT_PDMA_BASE)
#define HT_BFTM1                 ((HT_BFTM_TypeDef *) HT_BFTM1_BASE)
#define HT_PWM0                  ((HT_TM_TypeDef *) HT_PWM0_BASE)
#define HT_DAC0                  ((HT_DAC_TypeDef *) HT_DAC0_BASE)
#define HT_DAC1                  ((HT_DAC_TypeDef *) HT_DAC1_BASE)
#define HT_I2C1                  ((HT_I2C_TypeDef *) HT_I2C1_BASE)
#define HT_I2C2                  ((HT_I2C_TypeDef *) HT_I2C2_BASE)
#define HT_RTC                   ((HT_RTC_TypeDef *) HT_RTC_BASE)
#define HT_CRC                   ((HT_CRC_TypeDef *) HT_CRC_BASE)
#define HT_DIV                   ((HT_DIV_TypeDef *) HT_DIV_BASE)
#define HT_GPIOC                 ((HT_GPIO_TypeDef *) HT_GPIOC_BASE)
#endif

#if defined USE_HT32_DRIVER
  #include "ht32f5xxxx_lib.h"
#endif

/**
 * @brief Adjust the value of High Speed External oscillator (HSE)
          Tip: To avoid from modifying every time for different HSE, please define
          the "HSE_VALUE=n000000" ("n" represents n MHz) in your own toolchain compiler preprocessor,
          or edit the "HSE_VALUE" in the "ht32f5xxxx_conf.h" file.
  */
#if !defined  HSE_VALUE
  #if defined(USE_HT32F50220_30) || defined(USE_HT32F50231_41)
    /* Available HSE_VALUE: 4 MHz ~ 20 MHz                                                                  */
    #define HSE_VALUE       20000000UL /*!< Value of the External oscillator in Hz                          */
  #elif defined(USE_HT32F50020_30)
    /* Available HSE_VALUE: 4 MHz ~ 16 MHz                                                                  */
    #define HSE_VALUE       16000000UL  /*!< Value of the External oscillator in Hz                         */
  #elif defined(USE_HT32F0006)
    /* Available HSE_VALUE: 4 MHz ~ 16 MHz                                                                  */
    #define HSE_VALUE       12000000UL  /*!< Value of the External oscillator in Hz                         */
  #elif defined(USE_HT32F61244_45)
    /* Available HSE_VALUE: 4 MHz ~ 16 MHz                                                                  */
    #define HSE_VALUE       12000000UL  /*!< Value of the External oscillator in Hz                         */
  #elif defined(USE_HT32F67041_51)
    /* Available HSE_VALUE: 16 MHz                                                                          */
    #define HSE_VALUE       16000000UL  /*!< Value of the External oscillator in Hz                         */
  #else
    /* Available HSE_VALUE: 4 MHz ~ 16 MHz                                                                  */
    #define HSE_VALUE       8000000UL  /*!< Value of the External oscillator in Hz                          */
  #endif
#endif

/**
 * @brief Define for backward compatibility
 */
#define HT_ADC                   HT_ADC0
#define ADC                      ADC0
#define ADC_IRQn                 ADC0_IRQn

#define HT_DAC                   HT_DAC0
#define AFIO_FUN_DAC             AFIO_FUN_DAC0
#define CKCU_PCLK_DAC            CKCU_PCLK_DAC0

#if defined(USE_HT32F52357_67)
  #define UART0_IRQn             UART0_UART2_IRQn
  #define UART2_IRQn             UART0_UART2_IRQn
  #define UART1_IRQn             UART1_UART3_IRQn
  #define UART3_IRQn             UART1_UART3_IRQn
#endif

#if defined(USE_HT32F65230_40) || defined(USE_HT32F65232)
  // Alias
  #define GPTM0_IRQn             GPTM0_G_IRQn
  #define GPTM0_IRQHandler       GPTM0_G_IRQHandler
  #define MCTM0_IRQn             MCTM0_UP_IRQn
  #define MCTM0_IRQHandler       MCTM0_G_IRQHandler
  #define MCTM1_IRQn             MCTM1_UP_IRQn
  #define MCTM1_IRQHandler       MCTM1_G_IRQHandler
#endif

#define AFIO_ESS_Enum            u32

#if 0 // Set as 1 for backward compatibility
#if defined(USE_HT32F50020_30)
#define EXTI8_IRQn               EXTI0_1_IRQn
#define EXTI9_IRQn               EXTI0_1_IRQn
#define EXTI10_IRQn              EXTI2_3_IRQn
#define EXTI11_IRQn              EXTI2_3_IRQn
#define EXTI12_IRQn              EXTI4_7_IRQn
#define EXTI13_IRQn              EXTI4_7_IRQn
#define EXTI14_IRQn              EXTI4_7_IRQn
#define EXTI15_IRQn              EXTI4_7_IRQn

#define EXTI_CHANNEL_8           EXTI_CHANNEL_0
#define EXTI_CHANNEL_9           EXTI_CHANNEL_1
#define EXTI_CHANNEL_10          EXTI_CHANNEL_2
#define EXTI_CHANNEL_11          EXTI_CHANNEL_3
#define EXTI_CHANNEL_12          EXTI_CHANNEL_4
#define EXTI_CHANNEL_13          EXTI_CHANNEL_5
#define EXTI_CHANNEL_14          EXTI_CHANNEL_6
#define EXTI_CHANNEL_15          EXTI_CHANNEL_7
#endif
#endif

#if (LIBCFG_SPI_NO_MULTI_MASTER)
#define SPI_SELOutputCmd(...)
#endif

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif


/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT Holtek Semiconductor Inc. *****END OF FILE***                            */
