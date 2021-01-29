/**
  ******************************************************************************
  * @file    stm32wlxx_ll_system.h
  * @author  MCD Application Team
  * @brief   Header file of SYSTEM LL module.
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL SYSTEM driver contains a set of generic APIs that can be
    used by user:
      (+) Some of the FLASH features need to be handled in the SYSTEM file.
      (+) Access to DBGCMU registers
      (+) Access to SYSCFG registers
      (+) Access to VREFBUF registers

  @endverbatim
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                       opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WLxx_LL_SYSTEM_H
#define STM32WLxx_LL_SYSTEM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx.h"

/** @addtogroup STM32WLxx_LL_Driver
  * @{
  */

#if defined (FLASH) || defined (SYSCFG) || defined (DBGMCU) || defined (VREFBUF)

/** @defgroup SYSTEM_LL SYSTEM
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Private_Constants SYSTEM Private Constants
  * @{
  */
#define LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT     16U   /*!< Define used to shift pin position in EXTICR register */

/**
 * @brief VREFBUF VREF_SC0 & VREF_SC1 calibration values 
 */
#define VREFBUF_SC0_CAL_ADDR   ((uint8_t*) (0x1FFF75F0UL)) /*!<  Address of VREFBUF trimming value for VRS=0,
                                                                 VREF_SC0 in STM32WL datasheet */
#define VREFBUF_SC1_CAL_ADDR   ((uint8_t*) (0x1FFF7530UL)) /*!<  Address of VREFBUF trimming value for VRS=1,
                                                                 VREF_SC1 in STM32WL datasheet */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Constants SYSTEM Exported Constants
  * @{
  */

/** @defgroup SYSTEM_LL_EC_REMAP SYSCFG REMAP
* @{
*/
#define LL_SYSCFG_REMAP_FLASH                   0x00000000U                                           /*!< Main Flash memory mapped at 0x00000000   */
#define LL_SYSCFG_REMAP_SYSTEMFLASH             SYSCFG_MEMRMP_MEM_MODE_0                              /*!< System Flash memory mapped at 0x00000000 */
#define LL_SYSCFG_REMAP_SRAM                    (SYSCFG_MEMRMP_MEM_MODE_1 | SYSCFG_MEMRMP_MEM_MODE_0) /*!< SRAM1 mapped at 0x00000000               */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_I2C_FASTMODEPLUS SYSCFG I2C FASTMODEPLUS
  * @{
  */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB6          SYSCFG_CFGR1_I2C_PB6_FMP /*!< Enable Fast Mode Plus on PB6       */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB7          SYSCFG_CFGR1_I2C_PB7_FMP /*!< Enable Fast Mode Plus on PB7       */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB8          SYSCFG_CFGR1_I2C_PB8_FMP /*!< Enable Fast Mode Plus on PB8       */
#define LL_SYSCFG_I2C_FASTMODEPLUS_PB9          SYSCFG_CFGR1_I2C_PB9_FMP /*!< Enable Fast Mode Plus on PB9       */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C1         SYSCFG_CFGR1_I2C1_FMP    /*!< Enable Fast Mode Plus on I2C1 pins */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C2         SYSCFG_CFGR1_I2C2_FMP    /*!< Enable Fast Mode Plus on I2C2 pins */
#define LL_SYSCFG_I2C_FASTMODEPLUS_I2C3         SYSCFG_CFGR1_I2C3_FMP    /*!< Enable Fast Mode Plus on I2C3 pins */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_EXTI_PORT SYSCFG EXTI PORT
  * @{
  */
#define LL_SYSCFG_EXTI_PORTA                    0U /*!< EXTI PORT A */
#define LL_SYSCFG_EXTI_PORTB                    1U /*!< EXTI PORT B */
#define LL_SYSCFG_EXTI_PORTC                    2U /*!< EXTI PORT C */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_EXTI_LINE SYSCFG EXTI LINE
  * @{
  */
#if defined(CORE_CM0PLUS)
#define LL_SYSCFG_EXTI_LINE0                    (uint32_t)((0U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 0U)  /*!< EXTI_POSITION_0  | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE1                    (uint32_t)((4U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 0U)  /*!< EXTI_POSITION_4  | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE2                    (uint32_t)((8U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 0U)  /*!< EXTI_POSITION_8  | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE3                    (uint32_t)((12U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 0U)  /*!< EXTI_POSITION_12 | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE4                    (uint32_t)((0U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 1U)  /*!< EXTI_POSITION_0  | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE5                    (uint32_t)((4U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 1U)  /*!< EXTI_POSITION_4  | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE6                    (uint32_t)((8U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 1U)  /*!< EXTI_POSITION_8  | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE7                    (uint32_t)((12U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 1U)  /*!< EXTI_POSITION_12 | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE8                    (uint32_t)((0U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 2U)  /*!< EXTI_POSITION_0  | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE9                    (uint32_t)((4U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 2U)  /*!< EXTI_POSITION_4  | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE10                   (uint32_t)((8U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 2U)  /*!< EXTI_POSITION_8  | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE11                   (uint32_t)((12U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 2U)  /*!< EXTI_POSITION_12 | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE12                   (uint32_t)((0U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 3U)  /*!< EXTI_POSITION_0  | EXTICR[3] */
#define LL_SYSCFG_EXTI_LINE13                   (uint32_t)((4U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 3U)  /*!< EXTI_POSITION_4  | EXTICR[3] */
#define LL_SYSCFG_EXTI_LINE14                   (uint32_t)((8U  << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 3U)  /*!< EXTI_POSITION_8  | EXTICR[3] */
#define LL_SYSCFG_EXTI_LINE15                   (uint32_t)((12U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 3U)  /*!< EXTI_POSITION_12 | EXTICR[3] */
#else
#define LL_SYSCFG_EXTI_LINE0                    (uint32_t)((0x000FU << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 0U) /*!< EXTI_POSITION_0  | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE1                    (uint32_t)((0x00F0U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 0U) /*!< EXTI_POSITION_4  | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE2                    (uint32_t)((0x0F00U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 0U) /*!< EXTI_POSITION_8  | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE3                    (uint32_t)((0xF000U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 0U) /*!< EXTI_POSITION_12 | EXTICR[0] */
#define LL_SYSCFG_EXTI_LINE4                    (uint32_t)((0x000FU << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 1U) /*!< EXTI_POSITION_0  | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE5                    (uint32_t)((0x00F0U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 1U) /*!< EXTI_POSITION_4  | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE6                    (uint32_t)((0x0F00U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 1U) /*!< EXTI_POSITION_8  | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE7                    (uint32_t)((0xF000U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 1U) /*!< EXTI_POSITION_12 | EXTICR[1] */
#define LL_SYSCFG_EXTI_LINE8                    (uint32_t)((0x000FU << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 2U) /*!< EXTI_POSITION_0  | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE9                    (uint32_t)((0x00F0U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 2U) /*!< EXTI_POSITION_4  | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE10                   (uint32_t)((0x0F00U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 2U) /*!< EXTI_POSITION_8  | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE11                   (uint32_t)((0xF000U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 2U) /*!< EXTI_POSITION_12 | EXTICR[2] */
#define LL_SYSCFG_EXTI_LINE12                   (uint32_t)((0x000FU << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 3U) /*!< EXTI_POSITION_0  | EXTICR[3] */
#define LL_SYSCFG_EXTI_LINE13                   (uint32_t)((0x00F0U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 3U) /*!< EXTI_POSITION_4  | EXTICR[3] */
#define LL_SYSCFG_EXTI_LINE14                   (uint32_t)((0x0F00U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 3U) /*!< EXTI_POSITION_8  | EXTICR[3] */
#define LL_SYSCFG_EXTI_LINE15                   (uint32_t)((0xF000U << LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) | 3U) /*!< EXTI_POSITION_12 | EXTICR[3] */
#endif
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_TIMBREAK SYSCFG TIMER BREAK
  * @{
  */
#define LL_SYSCFG_TIMBREAK_ECC                  SYSCFG_CFGR2_ECCL       /*!< Enables and locks the ECC error signal
                                                                              with Break Input of TIM1/16/17                                */
#define LL_SYSCFG_TIMBREAK_PVD                  SYSCFG_CFGR2_PVDL       /*!< Enables and locks the PVD connection
                                                                              with TIM1/16/17 Break Input
                                                                              and also the PVDE and PLS bits of the Power Control Interface */
#define LL_SYSCFG_TIMBREAK_SRAM2_PARITY         SYSCFG_CFGR2_SPL        /*!< Enables and locks the SRAM2_PARITY error signal
                                                                              with Break Input of TIM1/16/17                                */
#define LL_SYSCFG_TIMBREAK_LOCKUP               SYSCFG_CFGR2_CLL        /*!< Enables and locks the LOCKUP output of CortexM4
                                                                              with Break Input of TIM1/16/17                                */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_SRAM2WRP SYSCFG SRAM2 WRITE PROTECTION
  * @{
  */
#define LL_SYSCFG_SRAM2WRP_PAGE0                SYSCFG_SWPR_PAGE0       /*!< SRAM2 Write protection page 0  */
#define LL_SYSCFG_SRAM2WRP_PAGE1                SYSCFG_SWPR_PAGE1       /*!< SRAM2 Write protection page 1  */
#define LL_SYSCFG_SRAM2WRP_PAGE2                SYSCFG_SWPR_PAGE2       /*!< SRAM2 Write protection page 2  */
#define LL_SYSCFG_SRAM2WRP_PAGE3                SYSCFG_SWPR_PAGE3       /*!< SRAM2 Write protection page 3  */
#define LL_SYSCFG_SRAM2WRP_PAGE4                SYSCFG_SWPR_PAGE4       /*!< SRAM2 Write protection page 4  */
#define LL_SYSCFG_SRAM2WRP_PAGE5                SYSCFG_SWPR_PAGE5       /*!< SRAM2 Write protection page 5  */
#define LL_SYSCFG_SRAM2WRP_PAGE6                SYSCFG_SWPR_PAGE6       /*!< SRAM2 Write protection page 6  */
#define LL_SYSCFG_SRAM2WRP_PAGE7                SYSCFG_SWPR_PAGE7       /*!< SRAM2 Write protection page 7  */
#define LL_SYSCFG_SRAM2WRP_PAGE8                SYSCFG_SWPR_PAGE8       /*!< SRAM2 Write protection page 8  */
#define LL_SYSCFG_SRAM2WRP_PAGE9                SYSCFG_SWPR_PAGE9       /*!< SRAM2 Write protection page 9  */
#define LL_SYSCFG_SRAM2WRP_PAGE10               SYSCFG_SWPR_PAGE10      /*!< SRAM2 Write protection page 10 */
#define LL_SYSCFG_SRAM2WRP_PAGE11               SYSCFG_SWPR_PAGE11      /*!< SRAM2 Write protection page 11 */
#define LL_SYSCFG_SRAM2WRP_PAGE12               SYSCFG_SWPR_PAGE12      /*!< SRAM2 Write protection page 12 */
#define LL_SYSCFG_SRAM2WRP_PAGE13               SYSCFG_SWPR_PAGE13      /*!< SRAM2 Write protection page 13 */
#define LL_SYSCFG_SRAM2WRP_PAGE14               SYSCFG_SWPR_PAGE14      /*!< SRAM2 Write protection page 14 */
#define LL_SYSCFG_SRAM2WRP_PAGE15               SYSCFG_SWPR_PAGE15      /*!< SRAM2 Write protection page 15 */
#define LL_SYSCFG_SRAM2WRP_PAGE16               SYSCFG_SWPR_PAGE16      /*!< SRAM2 Write protection page 16 */
#define LL_SYSCFG_SRAM2WRP_PAGE17               SYSCFG_SWPR_PAGE17      /*!< SRAM2 Write protection page 17 */
#define LL_SYSCFG_SRAM2WRP_PAGE18               SYSCFG_SWPR_PAGE18      /*!< SRAM2 Write protection page 18 */
#define LL_SYSCFG_SRAM2WRP_PAGE19               SYSCFG_SWPR_PAGE19      /*!< SRAM2 Write protection page 19 */
#define LL_SYSCFG_SRAM2WRP_PAGE20               SYSCFG_SWPR_PAGE20      /*!< SRAM2 Write protection page 20 */
#define LL_SYSCFG_SRAM2WRP_PAGE21               SYSCFG_SWPR_PAGE21      /*!< SRAM2 Write protection page 21 */
#define LL_SYSCFG_SRAM2WRP_PAGE22               SYSCFG_SWPR_PAGE22      /*!< SRAM2 Write protection page 22 */
#define LL_SYSCFG_SRAM2WRP_PAGE23               SYSCFG_SWPR_PAGE23      /*!< SRAM2 Write protection page 23 */
#define LL_SYSCFG_SRAM2WRP_PAGE24               SYSCFG_SWPR_PAGE24      /*!< SRAM2 Write protection page 24 */
#define LL_SYSCFG_SRAM2WRP_PAGE25               SYSCFG_SWPR_PAGE25      /*!< SRAM2 Write protection page 25 */
#define LL_SYSCFG_SRAM2WRP_PAGE26               SYSCFG_SWPR_PAGE26      /*!< SRAM2 Write protection page 26 */
#define LL_SYSCFG_SRAM2WRP_PAGE27               SYSCFG_SWPR_PAGE27      /*!< SRAM2 Write protection page 27 */
#define LL_SYSCFG_SRAM2WRP_PAGE28               SYSCFG_SWPR_PAGE28      /*!< SRAM2 Write protection page 28 */
#define LL_SYSCFG_SRAM2WRP_PAGE29               SYSCFG_SWPR_PAGE29      /*!< SRAM2 Write protection page 29 */
#define LL_SYSCFG_SRAM2WRP_PAGE30               SYSCFG_SWPR_PAGE30      /*!< SRAM2 Write protection page 30 */
#define LL_SYSCFG_SRAM2WRP_PAGE31               SYSCFG_SWPR_PAGE31      /*!< SRAM2 Write protection page 31 */
/**
  * @}
  */

#if defined(DUAL_CORE)
/** @defgroup SYSTEM_LL_EC_IM SYSCFG CPU1 INTERRUPT MASK
  * @{
  */
#define LL_SYSCFG_GRP1_RTCSTAMPTAMPLSECSS       SYSCFG_IMR1_RTCSTAMPTAMPLSECSSIM /*!< Enabling of interrupt from RTCSTAMPTAMPLSECSS to CPU1  */
#define LL_SYSCFG_GRP1_RTCSSRU                  SYSCFG_IMR1_RTCSSRUIM  /*!< Enabling of interrupt from RTC SSRU to CPU1                   */
#define LL_SYSCFG_GRP1_EXTI5                    SYSCFG_IMR1_EXTI5IM    /*!< Enabling of interrupt from External Interrupt Line 5 to CPU1  */
#define LL_SYSCFG_GRP1_EXTI6                    SYSCFG_IMR1_EXTI6IM    /*!< Enabling of interrupt from External Interrupt Line 6 to CPU1  */
#define LL_SYSCFG_GRP1_EXTI7                    SYSCFG_IMR1_EXTI7IM    /*!< Enabling of interrupt from External Interrupt Line 7 to CPU1  */
#define LL_SYSCFG_GRP1_EXTI8                    SYSCFG_IMR1_EXTI8IM    /*!< Enabling of interrupt from External Interrupt Line 8 to CPU1  */
#define LL_SYSCFG_GRP1_EXTI9                    SYSCFG_IMR1_EXTI9IM    /*!< Enabling of interrupt from External Interrupt Line 9 to CPU1  */
#define LL_SYSCFG_GRP1_EXTI10                   SYSCFG_IMR1_EXTI10IM   /*!< Enabling of interrupt from External Interrupt Line 10 to CPU1 */
#define LL_SYSCFG_GRP1_EXTI11                   SYSCFG_IMR1_EXTI11IM   /*!< Enabling of interrupt from External Interrupt Line 11 to CPU1 */
#define LL_SYSCFG_GRP1_EXTI12                   SYSCFG_IMR1_EXTI12IM   /*!< Enabling of interrupt from External Interrupt Line 12 to CPU1 */
#define LL_SYSCFG_GRP1_EXTI13                   SYSCFG_IMR1_EXTI13IM   /*!< Enabling of interrupt from External Interrupt Line 13 to CPU1 */
#define LL_SYSCFG_GRP1_EXTI14                   SYSCFG_IMR1_EXTI14IM   /*!< Enabling of interrupt from External Interrupt Line 14 to CPU1 */
#define LL_SYSCFG_GRP1_EXTI15                   SYSCFG_IMR1_EXTI15IM   /*!< Enabling of interrupt from External Interrupt Line 15 to CPU1 */

#define LL_SYSCFG_GRP2_PVM3                     SYSCFG_IMR2_PVM3IM     /*!< Enabling of interrupt from Power Voltage Monitoring 3 to CPU1 */
#define LL_SYSCFG_GRP2_PVD                      SYSCFG_IMR2_PVDIM      /*!< Enabling of interrupt from Power Voltage Detector to CPU1     */
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EC_C2_IM SYSCFG CPU2 INTERRUPT MASK
  * @{
  */
#define LL_C2_SYSCFG_GRP1_RTCSTAMP_RTCTAMP_LSECSS  SYSCFG_C2IMR1_RTCSTAMPTAMPLSECSSIM /*!< Enabling of interrupt from RTC TimeStamp, RTC Tampers
                                                                                           and LSE Clock Security System to CPU2                */
#define LL_C2_SYSCFG_GRP1_RTCALARM              SYSCFG_C2IMR1_RTCALARMIM /*!< Enabling of interrupt from RTC Alarms to CPU2                     */
#define LL_C2_SYSCFG_GRP1_RTCSSRU               SYSCFG_C2IMR1_RTCSSRUIM  /*!< Enabling of interrupt from RTC SSRU to CPU2                       */
#define LL_C2_SYSCFG_GRP1_RTCWKUP               SYSCFG_C2IMR1_RTCWKUPIM  /*!< Enabling of interrupt from RTC Wakeup to CPU2                     */
#define LL_C2_SYSCFG_GRP1_RCC                   SYSCFG_C2IMR1_RCCIM      /*!< Enabling of interrupt from RCC to CPU2                            */
#define LL_C2_SYSCFG_GRP1_FLASH                 SYSCFG_C2IMR1_FLASHIM    /*!< Enabling of interrupt from FLASH to CPU2                          */
#define LL_C2_SYSCFG_GRP1_PKA                   SYSCFG_C2IMR1_PKAIM      /*!< Enabling of interrupt from PKA to CPU2                            */
#define LL_C2_SYSCFG_GRP1_AES                   SYSCFG_C2IMR1_AESIM      /*!< Enabling of interrupt from AES to CPU2                            */
#define LL_C2_SYSCFG_GRP1_COMP                  SYSCFG_C2IMR1_COMPIM     /*!< Enabling of interrupt from Comparator to CPU2                     */
#define LL_C2_SYSCFG_GRP1_ADC                   SYSCFG_C2IMR1_ADCIM      /*!< Enabling of interrupt from Analog Digital Converter to CPU2       */
#define LL_C2_SYSCFG_GRP1_DAC                   SYSCFG_C2IMR1_DACIM      /*!< Enabling of interrupt from Digital Analog Converter to CPU2       */

#define LL_C2_SYSCFG_GRP1_EXTI0                 SYSCFG_C2IMR1_EXTI0IM    /*!< Enabling of interrupt from External Interrupt Line 0 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI1                 SYSCFG_C2IMR1_EXTI1IM    /*!< Enabling of interrupt from External Interrupt Line 1 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI2                 SYSCFG_C2IMR1_EXTI2IM    /*!< Enabling of interrupt from External Interrupt Line 2 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI3                 SYSCFG_C2IMR1_EXTI3IM    /*!< Enabling of interrupt from External Interrupt Line 3 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI4                 SYSCFG_C2IMR1_EXTI4IM    /*!< Enabling of interrupt from External Interrupt Line 4 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI5                 SYSCFG_C2IMR1_EXTI5IM    /*!< Enabling of interrupt from External Interrupt Line 5 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI6                 SYSCFG_C2IMR1_EXTI6IM    /*!< Enabling of interrupt from External Interrupt Line 6 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI7                 SYSCFG_C2IMR1_EXTI7IM    /*!< Enabling of interrupt from External Interrupt Line 7 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI8                 SYSCFG_C2IMR1_EXTI8IM    /*!< Enabling of interrupt from External Interrupt Line 8 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI9                 SYSCFG_C2IMR1_EXTI9IM    /*!< Enabling of interrupt from External Interrupt Line 9 to CPU2      */
#define LL_C2_SYSCFG_GRP1_EXTI10                SYSCFG_C2IMR1_EXTI10IM   /*!< Enabling of interrupt from External Interrupt Line 10 to CPU2     */
#define LL_C2_SYSCFG_GRP1_EXTI11                SYSCFG_C2IMR1_EXTI11IM   /*!< Enabling of interrupt from External Interrupt Line 11 to CPU2     */
#define LL_C2_SYSCFG_GRP1_EXTI12                SYSCFG_C2IMR1_EXTI12IM   /*!< Enabling of interrupt from External Interrupt Line 12 to CPU2     */
#define LL_C2_SYSCFG_GRP1_EXTI13                SYSCFG_C2IMR1_EXTI13IM   /*!< Enabling of interrupt from External Interrupt Line 13 to CPU2     */
#define LL_C2_SYSCFG_GRP1_EXTI14                SYSCFG_C2IMR1_EXTI14IM   /*!< Enabling of interrupt from External Interrupt Line 14 to CPU2     */
#define LL_C2_SYSCFG_GRP1_EXTI15                SYSCFG_C2IMR1_EXTI15IM   /*!< Enabling of interrupt from External Interrupt Line 15 to CPU2     */

#define LL_C2_SYSCFG_GRP2_DMA1CH1               SYSCFG_C2IMR2_DMA1CH1IM  /*!< Enabling of interrupt from DMA1 Channel 1 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA1CH2               SYSCFG_C2IMR2_DMA1CH2IM  /*!< Enabling of interrupt from DMA1 Channel 2 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA1CH3               SYSCFG_C2IMR2_DMA1CH3IM  /*!< Enabling of interrupt from DMA1 Channel 3 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA1CH4               SYSCFG_C2IMR2_DMA1CH4IM  /*!< Enabling of interrupt from DMA1 Channel 4 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA1CH5               SYSCFG_C2IMR2_DMA1CH5IM  /*!< Enabling of interrupt from DMA1 Channel 5 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA1CH6               SYSCFG_C2IMR2_DMA1CH6IM  /*!< Enabling of interrupt from DMA1 Channel 6 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA1CH7               SYSCFG_C2IMR2_DMA1CH7IM  /*!< Enabling of interrupt from DMA1 Channel 7 to CPU2                 */

#define LL_C2_SYSCFG_GRP2_DMA2CH1               SYSCFG_C2IMR2_DMA2CH1IM  /*!< Enabling of interrupt from DMA2 Channel 1 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA2CH2               SYSCFG_C2IMR2_DMA2CH2IM  /*!< Enabling of interrupt from DMA2 Channel 2 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA2CH3               SYSCFG_C2IMR2_DMA2CH3IM  /*!< Enabling of interrupt from DMA2 Channel 3 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA2CH4               SYSCFG_C2IMR2_DMA2CH4IM  /*!< Enabling of interrupt from DMA2 Channel 4 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA2CH5               SYSCFG_C2IMR2_DMA2CH5IM  /*!< Enabling of interrupt from DMA2 Channel 5 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA2CH6               SYSCFG_C2IMR2_DMA2CH6IM  /*!< Enabling of interrupt from DMA2 Channel 6 to CPU2                 */
#define LL_C2_SYSCFG_GRP2_DMA2CH7               SYSCFG_C2IMR2_DMA2CH7IM  /*!< Enabling of interrupt from DMA2 Channel 7 to CPU2                 */

#define LL_C2_SYSCFG_GRP2_DMAMUX1               SYSCFG_C2IMR2_DMAMUX1IM  /*!< Enabling of interrupt from DMAMUX1 to CPU2                        */

#define LL_C2_SYSCFG_GRP2_PVM3                  SYSCFG_C2IMR2_PVM3IM     /*!< Enabling of interrupt from Power Voltage Monitoring 3 to CPU2     */
#define LL_C2_SYSCFG_GRP2_PVD                   SYSCFG_C2IMR2_PVDIM      /*!< Enabling of interrupt from Power Voltage Detector to CPU2         */
/**
  * @}
  */
#endif

/** @defgroup SYSTEM_LL_EC_RF_TEST_BUS_TYPE SYSCFG RF TEST BUS TYPE
  * @{
  */
#define LL_SYSCFG_ANALOG_TEST_BUS               SYSCFG_RFDCR_RFTBSEL    /*!< Analog test bus selected on RF_ADTB[3:0]   */
#define LL_SYSCFG_DIGITAL_TEST_BUS              0x00000000U             /*!< Digital test bus selected on RF_ADTB[3:0]  */
/**
  * @}
  */


#if defined(CORE_CM0PLUS)
#else
/** @defgroup SYSTEM_LL_EC_APB1_GRP1_STOP_IP DBGMCU CPU1 APB1 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB1_GRP1_TIM2_STOP      DBGMCU_APB1FZR1_DBG_TIM2_STOP   /*!< The counter clock of TIM2 is stopped when the core is halted              */
#define LL_DBGMCU_APB1_GRP1_RTC_STOP       DBGMCU_APB1FZR1_DBG_RTC_STOP    /*!< The clock of the RTC counter is stopped when the core is halted           */
#define LL_DBGMCU_APB1_GRP1_WWDG_STOP      DBGMCU_APB1FZR1_DBG_WWDG_STOP   /*!< The watchdog counter clock is stopped when the core is halted */
#define LL_DBGMCU_APB1_GRP1_IWDG_STOP      DBGMCU_APB1FZR1_DBG_IWDG_STOP   /*!< The independent watchdog counter clock is stopped when the core is halted */
#define LL_DBGMCU_APB1_GRP1_I2C1_STOP      DBGMCU_APB1FZR1_DBG_I2C1_STOP   /*!< The I2C1 SMBus timeout is frozen                                          */
#define LL_DBGMCU_APB1_GRP1_I2C2_STOP      DBGMCU_APB1FZR1_DBG_I2C2_STOP   /*!< The I2C2 SMBus timeout is frozen                                          */
#define LL_DBGMCU_APB1_GRP1_I2C3_STOP      DBGMCU_APB1FZR1_DBG_I2C3_STOP   /*!< The I2C3 SMBus timeout is frozen                                          */
#define LL_DBGMCU_APB1_GRP1_LPTIM1_STOP    DBGMCU_APB1FZR1_DBG_LPTIM1_STOP /*!< The counter clock of LPTIM1 is stopped when the core is halted            */
/**
  * @}
  */

#if defined(DUAL_CORE)
/** @defgroup SYSTEM_LL_EC_C2_APB1_GRP1_STOP_IP DBGMCU CPU2 APB1 GRP1 STOP IP
  * @{
  */
#define LL_C2_DBGMCU_APB1_GRP1_TIM2_STOP   DBGMCU_C2APB1FZR1_DBG_TIM2_STOP   /*!< The counter clock of TIM2 is stopped when the core is halted              */
#define LL_C2_DBGMCU_APB1_GRP1_RTC_STOP    DBGMCU_C2APB1FZR1_DBG_RTC_STOP    /*!< The clock of the RTC counter is stopped when the core is halted           */
#define LL_C2_DBGMCU_APB1_GRP1_IWDG_STOP   DBGMCU_C2APB1FZR1_DBG_IWDG_STOP   /*!< The independent watchdog counter clock is stopped when the core is halted */
#define LL_C2_DBGMCU_APB1_GRP1_I2C1_STOP   DBGMCU_C2APB1FZR1_DBG_I2C1_STOP   /*!< The I2C1 SMBus timeout is frozen                                          */
#define LL_C2_DBGMCU_APB1_GRP1_I2C2_STOP   DBGMCU_C2APB1FZR1_DBG_I2C2_STOP   /*!< The I2C2 SMBus timeout is frozen                                          */
#define LL_C2_DBGMCU_APB1_GRP1_I2C3_STOP   DBGMCU_C2APB1FZR1_DBG_I2C3_STOP   /*!< The I2C3 SMBus timeout is frozen                                          */
#define LL_C2_DBGMCU_APB1_GRP1_LPTIM1_STOP DBGMCU_C2APB1FZR1_DBG_LPTIM1_STOP /*!< The counter clock of LPTIM1 is stopped when the core is halted            */
/**
  * @}
  */
#endif /* DUAL_CORE */

/** @defgroup SYSTEM_LL_EC_APB1_GRP2_STOP_IP DBGMCU CPU1 APB1 GRP2 STOP IP
  * @{
  */
#define LL_DBGMCU_APB1_GRP2_LPTIM2_STOP    DBGMCU_APB1FZR2_DBG_LPTIM2_STOP /*!< The counter clock of LPTIM2 is stopped when the core is halted            */
#define LL_DBGMCU_APB1_GRP2_LPTIM3_STOP    DBGMCU_APB1FZR2_DBG_LPTIM3_STOP /*!< The counter clock of LPTIM3 is stopped when the core is halted            */
/**
  * @}
  */

#if defined(DUAL_CORE)
/** @defgroup SYSTEM_LL_EC_C2_APB1_GRP2_STOP_IP DBGMCU CPU2 APB1 GRP2 STOP IP
  * @{
  */
#define LL_C2_DBGMCU_APB1_GRP2_LPTIM2_STOP DBGMCU_C2APB1FZR2_DBG_LPTIM2_STOP /*!< The counter clock of LPTIM2 is stopped when the core is halted            */
#define LL_C2_DBGMCU_APB1_GRP2_LPTIM3_STOP DBGMCU_C2APB1FZR2_DBG_LPTIM3_STOP /*!< The counter clock of LPTIM3 is stopped when the core is halted            */
/**
  * @}
  */
#endif /* DUAL_CORE */

/** @defgroup SYSTEM_LL_EC_APB2_GRP1_STOP_IP DBGMCU CPU1 APB2 GRP1 STOP IP
  * @{
  */
#define LL_DBGMCU_APB2_GRP1_TIM1_STOP      DBGMCU_APB2FZR_DBG_TIM1_STOP   /*!< The counter clock of TIM1 is stopped when the core is halted              */
#define LL_DBGMCU_APB2_GRP1_TIM16_STOP     DBGMCU_APB2FZR_DBG_TIM16_STOP  /*!< The counter clock of TIM16 is stopped when the core is halted             */
#define LL_DBGMCU_APB2_GRP1_TIM17_STOP     DBGMCU_APB2FZR_DBG_TIM17_STOP  /*!< The counter clock of TIM17 is stopped when the core is halted             */
/**
  * @}
  */

#if defined(DUAL_CORE)
/** @defgroup SYSTEM_LL_EC_C2_APB2_GRP1_STOP_IP DBGMCU CPU2 APB2 GRP1 STOP IP
  * @{
  */
#define LL_C2_DBGMCU_APB2_GRP1_TIM1_STOP   DBGMCU_C2APB2FZR_DBG_TIM1_STOP   /*!< The counter clock of TIM1 is stopped when the core is halted              */
#define LL_C2_DBGMCU_APB2_GRP1_TIM16_STOP  DBGMCU_C2APB2FZR_DBG_TIM16_STOP  /*!< The counter clock of TIM16 is stopped when the core is halted             */
#define LL_C2_DBGMCU_APB2_GRP1_TIM17_STOP  DBGMCU_C2APB2FZR_DBG_TIM17_STOP  /*!< The counter clock of TIM17 is stopped when the core is halted             */
/**
  * @}
  */
#endif /* DUAL_CORE */

#endif

#if defined(VREFBUF)
/** @defgroup SYSTEM_LL_EC_VOLTAGE VREFBUF VOLTAGE
  * @{
  */
#define LL_VREFBUF_VOLTAGE_SCALE0          0x00000000U     /*!< Voltage reference scale 0 (VREF_OUT1) */
#define LL_VREFBUF_VOLTAGE_SCALE1          VREFBUF_CSR_VRS /*!< Voltage reference scale 1 (VREF_OUT2) */
/**
  * @}
  */
#endif /* VREFBUF */

/** @defgroup SYSTEM_LL_EC_LATENCY FLASH LATENCY
  * @{
  */
#define LL_FLASH_LATENCY_0                 0x00000000U                          /*!< FLASH Zero wait state   */
#define LL_FLASH_LATENCY_1                 FLASH_ACR_LATENCY_0                  /*!< FLASH One wait state    */
#define LL_FLASH_LATENCY_2                 FLASH_ACR_LATENCY_1                  /*!< FLASH Two wait states   */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup SYSTEM_LL_Exported_Functions SYSTEM Exported Functions
  * @{
  */

/** @defgroup SYSTEM_LL_EF_SYSCFG SYSCFG
  * @{
  */

/**
  * @brief  Set memory mapping at address 0x00000000
  * @rmtoll SYSCFG_MEMRMP MEM_MODE      LL_SYSCFG_SetRemapMemory
  * @param  Memory This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetRemapMemory(uint32_t Memory)
{
  MODIFY_REG(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE, Memory);
}

/**
  * @brief  Get memory mapping at address 0x00000000
  * @rmtoll SYSCFG_MEMRMP MEM_MODE      LL_SYSCFG_GetRemapMemory
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_REMAP_FLASH
  *         @arg @ref LL_SYSCFG_REMAP_SYSTEMFLASH
  *         @arg @ref LL_SYSCFG_REMAP_SRAM
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetRemapMemory(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->MEMRMP, SYSCFG_MEMRMP_MEM_MODE));
}

/**
  * @brief  Enable I/O analog switch voltage booster.
  * @note   When voltage booster is enabled, I/O analog switches are supplied
  *         by a dedicated voltage booster, from VDD power domain. This is
  *         the recommended configuration with low VDDA voltage operation.
  * @note   The I/O analog switch voltage booster is relevant for peripherals
  *         using I/O in analog input: ADC and COMP.
  *         However, COMP inputs have a high impedance and
  *         voltage booster do not impact performance significantly.
  *         Therefore, the voltage booster is mainly intended for
  *         usage with ADC.
  * @rmtoll SYSCFG_CFGR1 BOOSTEN       LL_SYSCFG_EnableAnalogBooster
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableAnalogBooster(void)
{
  SET_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOSTEN);
}

/**
  * @brief  Disable I/O analog switch voltage booster.
  * @note   When voltage booster is enabled, I/O analog switches are supplied
  *         by a dedicated voltage booster, from VDD power domain. This is
  *         the recommended configuration with low VDDA voltage operation.
  * @note   The I/O analog switch voltage booster is relevant for peripherals
  *         using I/O in analog input: ADC and COMP.
  *         However, COMP inputs have a high impedance and
  *         voltage booster do not impact performance significantly.
  *         Therefore, the voltage booster is mainly intended for
  *         usage with ADC.
  * @rmtoll SYSCFG_CFGR1 BOOSTEN       LL_SYSCFG_DisableAnalogBooster
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableAnalogBooster(void)
{
  CLEAR_BIT(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOSTEN);
}

/**
  * @brief  Enable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_CFGR1 I2C_PBx_FMP   LL_SYSCFG_EnableFastModePlus\n
  *         SYSCFG_CFGR1 I2Cx_FMP      LL_SYSCFG_EnableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB8
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB9
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C2
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableFastModePlus(uint32_t ConfigFastModePlus)
{
  SET_BIT(SYSCFG->CFGR1, ConfigFastModePlus);
}

/**
  * @brief  Disable the I2C fast mode plus driving capability.
  * @rmtoll SYSCFG_CFGR1 I2C_PBx_FMP   LL_SYSCFG_DisableFastModePlus\n
  *         SYSCFG_CFGR1 I2Cx_FMP      LL_SYSCFG_DisableFastModePlus
  * @param  ConfigFastModePlus This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB6
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB7
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB8
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_PB9
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C1
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C2
  *         @arg @ref LL_SYSCFG_I2C_FASTMODEPLUS_I2C3
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_DisableFastModePlus(uint32_t ConfigFastModePlus)
{
  CLEAR_BIT(SYSCFG->CFGR1, ConfigFastModePlus);
}

/**
  * @brief  Configure source input for the EXTI external interrupt.
  * @rmtoll SYSCFG_EXTICR1 EXTIx         LL_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR2 EXTIx         LL_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR3 EXTIx         LL_SYSCFG_SetEXTISource\n
  *         SYSCFG_EXTICR4 EXTIx         LL_SYSCFG_SetEXTISource
  * @param  Port This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_EXTI_PORTA
  *         @arg @ref LL_SYSCFG_EXTI_PORTB
  *         @arg @ref LL_SYSCFG_EXTI_PORTC
  *
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_EXTI_LINE0
  *         @arg @ref LL_SYSCFG_EXTI_LINE1
  *         @arg @ref LL_SYSCFG_EXTI_LINE2
  *         @arg @ref LL_SYSCFG_EXTI_LINE3
  *         @arg @ref LL_SYSCFG_EXTI_LINE4
  *         @arg @ref LL_SYSCFG_EXTI_LINE5
  *         @arg @ref LL_SYSCFG_EXTI_LINE6
  *         @arg @ref LL_SYSCFG_EXTI_LINE7
  *         @arg @ref LL_SYSCFG_EXTI_LINE8
  *         @arg @ref LL_SYSCFG_EXTI_LINE9
  *         @arg @ref LL_SYSCFG_EXTI_LINE10
  *         @arg @ref LL_SYSCFG_EXTI_LINE11
  *         @arg @ref LL_SYSCFG_EXTI_LINE12
  *         @arg @ref LL_SYSCFG_EXTI_LINE13
  *         @arg @ref LL_SYSCFG_EXTI_LINE14
  *         @arg @ref LL_SYSCFG_EXTI_LINE15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetEXTISource(uint32_t Port, uint32_t Line)
{
#if defined(CORE_CM0PLUS)
  MODIFY_REG(SYSCFG->EXTICR[Line & 0x03U], SYSCFG_EXTICR1_EXTI0 << ((Line >> LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) & 12UL), (Port << ((Line >> LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) & 12UL)));
#else
  MODIFY_REG(SYSCFG->EXTICR[Line & 0x03U], (Line >> LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT), (Port << ((POSITION_VAL((Line >> LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT))) & 0x0000000FUL)));
#endif
}

/**
  * @brief  Get the configured defined for specific EXTI Line
  * @rmtoll SYSCFG_EXTICR1 EXTIx         LL_SYSCFG_GetEXTISource\n
  *         SYSCFG_EXTICR2 EXTIx         LL_SYSCFG_GetEXTISource\n
  *         SYSCFG_EXTICR3 EXTIx         LL_SYSCFG_GetEXTISource\n
  *         SYSCFG_EXTICR4 EXTIx         LL_SYSCFG_GetEXTISource
  * @param  Line This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_EXTI_LINE0
  *         @arg @ref LL_SYSCFG_EXTI_LINE1
  *         @arg @ref LL_SYSCFG_EXTI_LINE2
  *         @arg @ref LL_SYSCFG_EXTI_LINE3
  *         @arg @ref LL_SYSCFG_EXTI_LINE4
  *         @arg @ref LL_SYSCFG_EXTI_LINE5
  *         @arg @ref LL_SYSCFG_EXTI_LINE6
  *         @arg @ref LL_SYSCFG_EXTI_LINE7
  *         @arg @ref LL_SYSCFG_EXTI_LINE8
  *         @arg @ref LL_SYSCFG_EXTI_LINE9
  *         @arg @ref LL_SYSCFG_EXTI_LINE10
  *         @arg @ref LL_SYSCFG_EXTI_LINE11
  *         @arg @ref LL_SYSCFG_EXTI_LINE12
  *         @arg @ref LL_SYSCFG_EXTI_LINE13
  *         @arg @ref LL_SYSCFG_EXTI_LINE14
  *         @arg @ref LL_SYSCFG_EXTI_LINE15
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_EXTI_PORTA
  *         @arg @ref LL_SYSCFG_EXTI_PORTB
  *         @arg @ref LL_SYSCFG_EXTI_PORTC
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetEXTISource(uint32_t Line)
{
#if defined(CORE_CM0PLUS)
  return (uint32_t)(READ_BIT(SYSCFG->EXTICR[Line & 0x03U], (SYSCFG_EXTICR1_EXTI0 << ((Line >> LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) & 12UL))) >> ((Line >> LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT) & 12UL));
#else
  return (uint32_t)(READ_BIT(SYSCFG->EXTICR[Line & 0x03U], ((Line >> LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT)) >> ((POSITION_VAL(Line >> LL_SYSCFG_EXTI_REGISTER_PINPOS_SHFT)) & 0x0000000FUL)));
#endif
}

/**
  * @brief  Start a hardware SRAM2 erase operation.
  * @rmtoll SYSCFG_SCSR SRAM2ER   LL_SYSCFG_EnableSRAM2Erase\n
  * @note   This operation can be done only once SRAM2 page write protection unlocked
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_EnableSRAM2Erase(void)
{
  SET_BIT(SYSCFG->SCSR, SYSCFG_SCSR_SRAM2ER);
}

/**
  * @brief  Check if SRAM1 or SRAM2 is busy by erase operation
  * @rmtoll SYSCFG_SCSR SRAMBSY LL_SYSCFG_IsSRAMEraseOngoing
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsSRAMEraseOngoing(void)
{
  return ((READ_BIT(SYSCFG->SCSR, SYSCFG_SCSR_SRAMBSY) == (SYSCFG_SCSR_SRAMBSY)) ? 1UL : 0UL);
}

/**
  * @brief  Check if PKA SRAMis busy by erase operation
  * @rmtoll SYSCFG_SCSR PKASRAMBSY LL_SYSCFG_IsPKASRAMEraseOngoing
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsPKASRAMEraseOngoing(void)
{
  return ((READ_BIT(SYSCFG->SCSR, SYSCFG_SCSR_PKASRAMBSY) == (SYSCFG_SCSR_PKASRAMBSY)) ? 1UL : 0UL);
}

/**
  * @brief  Set connections to TIM1/16/17 Break inputs
  * @rmtoll SYSCFG_CFGR2 CLL           LL_SYSCFG_SetTIMBreakInputs\n
  *         SYSCFG_CFGR2 SPL           LL_SYSCFG_SetTIMBreakInputs\n
  *         SYSCFG_CFGR2 PVDL          LL_SYSCFG_SetTIMBreakInputs\n
  *         SYSCFG_CFGR2 ECCL          LL_SYSCFG_SetTIMBreakInputs
  * @param  Break This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_ECC
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD
  *         @arg @ref LL_SYSCFG_TIMBREAK_SRAM2_PARITY
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetTIMBreakInputs(uint32_t Break)
{
  MODIFY_REG(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL | SYSCFG_CFGR2_SPL | SYSCFG_CFGR2_PVDL | SYSCFG_CFGR2_ECCL, Break);
}

/**
  * @brief  Get connections to TIM1/16/17 Break inputs
  * @rmtoll SYSCFG_CFGR2 CLL           LL_SYSCFG_GetTIMBreakInputs\n
  *         SYSCFG_CFGR2 SPL           LL_SYSCFG_GetTIMBreakInputs\n
  *         SYSCFG_CFGR2 PVDL          LL_SYSCFG_GetTIMBreakInputs\n
  *         SYSCFG_CFGR2 ECCL          LL_SYSCFG_GetTIMBreakInputs
  * @retval Returned value can be can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_TIMBREAK_ECC
  *         @arg @ref LL_SYSCFG_TIMBREAK_PVD
  *         @arg @ref LL_SYSCFG_TIMBREAK_SRAM2_PARITY
  *         @arg @ref LL_SYSCFG_TIMBREAK_LOCKUP
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetTIMBreakInputs(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_CLL | SYSCFG_CFGR2_SPL | SYSCFG_CFGR2_PVDL | SYSCFG_CFGR2_ECCL));
}

/**
  * @brief  Check if SRAM2 parity error detected
  * @rmtoll SYSCFG_CFGR2 SPF           LL_SYSCFG_IsActiveFlag_SP
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_IsActiveFlag_SP(void)
{
  return ((READ_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPF) == (SYSCFG_CFGR2_SPF)) ? 1UL : 0UL);
}

/**
  * @brief  Clear SRAM2 parity error flag
  * @rmtoll SYSCFG_CFGR2 SPF           LL_SYSCFG_ClearFlag_SP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_ClearFlag_SP(void)
{
  SET_BIT(SYSCFG->CFGR2, SYSCFG_CFGR2_SPF);
}

/**
  * @brief  Enable SRAM2 page write protection for Pages in range 0 to 31
  * @note Write protection is cleared only by a system reset
  * @rmtoll SYSCFG_SWPR PxWP          LL_SYSCFG_EnableSRAM2PageWRP_0_31
  * @param  SRAM2WRP This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE0
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE1
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE2
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE3
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE4
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE5
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE6
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE7
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE8
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE9
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE10
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE11
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE12
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE13
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE14
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE15
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE16
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE17
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE18
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE19
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE20
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE21
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE22
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE23
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE24
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE25
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE26
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE27
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE28
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE29
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE30
  *         @arg @ref LL_SYSCFG_SRAM2WRP_PAGE31
  * @retval None
  */
/* Legacy define */
#define LL_SYSCFG_EnableSRAM2PageWRP    LL_SYSCFG_EnableSRAM2PageWRP_0_31
__STATIC_INLINE void LL_SYSCFG_EnableSRAM2PageWRP_0_31(uint32_t SRAM2WRP)
{
  SET_BIT(SYSCFG->SWPR, SRAM2WRP);
}


/**
  * @brief  SRAM2 page write protection lock prior to erase
  * @rmtoll SYSCFG_SKR   KEY           LL_SYSCFG_LockSRAM2WRP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_LockSRAM2WRP(void)
{
  /* Writing a wrong key reactivates the write protection */
  WRITE_REG(SYSCFG->SKR, 0x00U);
}

/**
  * @brief  SRAM2 page write protection unlock prior to erase
  * @rmtoll SYSCFG_SKR   KEY           LL_SYSCFG_UnlockSRAM2WRP
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_UnlockSRAM2WRP(void)
{
  /* unlock the write protection of the SRAM2ER bit */
  WRITE_REG(SYSCFG->SKR, 0xCAU);
  WRITE_REG(SYSCFG->SKR, 0x53U);
}

#if defined(DUAL_CORE)
/**
  * @brief  Enable CPU1 Interrupt Mask
  * @rmtoll SYSCFG_IMR1  RTCSTAMPTAMPLSECSS1IM   LL_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_IMR1  RTCSSRUIM               LL_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_IMR1  EXTIxIM                 LL_SYSCFG_GRP1_EnableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GRP1_RTCSTAMPTAMPLSECSS
  *         @arg @ref LL_SYSCFG_GRP1_RTCSSRU
  *         @arg @ref LL_SYSCFG_GRP1_EXTI5
  *         @arg @ref LL_SYSCFG_GRP1_EXTI6
  *         @arg @ref LL_SYSCFG_GRP1_EXTI7
  *         @arg @ref LL_SYSCFG_GRP1_EXTI8
  *         @arg @ref LL_SYSCFG_GRP1_EXTI9
  *         @arg @ref LL_SYSCFG_GRP1_EXTI10
  *         @arg @ref LL_SYSCFG_GRP1_EXTI11
  *         @arg @ref LL_SYSCFG_GRP1_EXTI12
  *         @arg @ref LL_SYSCFG_GRP1_EXTI13
  *         @arg @ref LL_SYSCFG_GRP1_EXTI14
  *         @arg @ref LL_SYSCFG_GRP1_EXTI15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_GRP1_EnableIT(uint32_t Interrupt)
{
  CLEAR_BIT(SYSCFG->IMR1, Interrupt);
}

/**
  * @brief  Enable CPU1 Interrupt Mask
  * @rmtoll SYSCFG_IMR1  PVM3IM      LL_SYSCFG_GRP2_EnableIT\n
  *         SYSCFG_IMR1  PVDIM       LL_SYSCFG_GRP2_EnableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GRP2_PVM3
  *         @arg @ref LL_SYSCFG_GRP2_PVD
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_GRP2_EnableIT(uint32_t Interrupt)
{
  CLEAR_BIT(SYSCFG->IMR2, Interrupt);
}

/**
  * @brief  Disable CPU1 Interrupt Mask
  * @rmtoll SYSCFG_IMR1  RTCSTAMPTAMPLSECSS1IM      LL_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_IMR1  RTCSSRUIM     LL_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_IMR1  EXTIxIM     LL_SYSCFG_GRP1_DisableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GRP1_RTCSTAMPTAMPLSECSS
  *         @arg @ref LL_SYSCFG_GRP1_RTCSSRU
  *         @arg @ref LL_SYSCFG_GRP1_EXTI5
  *         @arg @ref LL_SYSCFG_GRP1_EXTI6
  *         @arg @ref LL_SYSCFG_GRP1_EXTI7
  *         @arg @ref LL_SYSCFG_GRP1_EXTI8
  *         @arg @ref LL_SYSCFG_GRP1_EXTI9
  *         @arg @ref LL_SYSCFG_GRP1_EXTI10
  *         @arg @ref LL_SYSCFG_GRP1_EXTI11
  *         @arg @ref LL_SYSCFG_GRP1_EXTI12
  *         @arg @ref LL_SYSCFG_GRP1_EXTI13
  *         @arg @ref LL_SYSCFG_GRP1_EXTI14
  *         @arg @ref LL_SYSCFG_GRP1_EXTI15
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_GRP1_DisableIT(uint32_t Interrupt)
{
  SET_BIT(SYSCFG->IMR1, Interrupt);
}

/**
  * @brief  Disable CPU1 Interrupt Mask
  * @rmtoll SYSCFG_IMR2  PVM3IM      LL_SYSCFG_GRP2_DisableIT\n
  *         SYSCFG_IMR2  PVDIM       LL_SYSCFG_GRP2_DisableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_SYSCFG_GRP2_PVM3
  *         @arg @ref LL_SYSCFG_GRP2_PVD
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_GRP2_DisableIT(uint32_t Interrupt)
{
  SET_BIT(SYSCFG->IMR2, Interrupt);
}

/**
  * @brief  Indicate if CPU1 Interrupt Mask is enabled
  * @rmtoll SYSCFG_IMR1  RTCSTAMPTAMPLSECSS1IM   LL_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_IMR1  RTCSSRUIM               LL_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_IMR1  EXTIxIM                 LL_SYSCFG_GRP1_IsEnabledIT
  * @param  Interrupt This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_GRP1_RTCSTAMPTAMPLSECSS
  *         @arg @ref LL_SYSCFG_GRP1_RTCSSRU
  *         @arg @ref LL_SYSCFG_GRP1_EXTI5
  *         @arg @ref LL_SYSCFG_GRP1_EXTI6
  *         @arg @ref LL_SYSCFG_GRP1_EXTI7
  *         @arg @ref LL_SYSCFG_GRP1_EXTI8
  *         @arg @ref LL_SYSCFG_GRP1_EXTI9
  *         @arg @ref LL_SYSCFG_GRP1_EXTI10
  *         @arg @ref LL_SYSCFG_GRP1_EXTI11
  *         @arg @ref LL_SYSCFG_GRP1_EXTI12
  *         @arg @ref LL_SYSCFG_GRP1_EXTI13
  *         @arg @ref LL_SYSCFG_GRP1_EXTI14
  *         @arg @ref LL_SYSCFG_GRP1_EXTI15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GRP1_IsEnabledIT(uint32_t Interrupt)
{
  return ((READ_BIT(SYSCFG->IMR1, Interrupt) != (Interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if CPU1 Interrupt Mask is enabled
  * @rmtoll SYSCFG_IMR2  PVM3IM      LL_SYSCFG_GRP2_IsEnabledIT\n
  *         SYSCFG_IMR2  PVDIM       LL_SYSCFG_GRP2_IsEnabledIT
  * @param  Interrupt This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_GRP2_PVM3
  *         @arg @ref LL_SYSCFG_GRP2_PVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GRP2_IsEnabledIT(uint32_t Interrupt)
{
  return ((READ_BIT(SYSCFG->IMR2, Interrupt) != (Interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Enable CPU2 Interrupt Mask
  * @rmtoll SYSCFG_C2IMR1  RTCSTAMPTAMPLSECSSIM      LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  RTCALARMIM  LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  RTCSSRUIM   LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  RTCWKUPIM   LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  RCCIM       LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  FLASHIM     LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  PKAIM       LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  RNGIM       LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  AESIM       LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  COMPIM      LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  ADCIM       LL_C2_SYSCFG_GRP1_EnableIT\n
  *         SYSCFG_C2IMR1  EXTIxIM     LL_C2_SYSCFG_GRP1_EnableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCSTAMP_RTCTAMP_LSECSS
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCALARM
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCSSRU
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCWKUP
  *         @arg @ref LL_C2_SYSCFG_GRP1_RCC
  *         @arg @ref LL_C2_SYSCFG_GRP1_FLASH
  *         @arg @ref LL_C2_SYSCFG_GRP1_PKA
  *         @arg @ref LL_C2_SYSCFG_GRP1_AES
  *         @arg @ref LL_C2_SYSCFG_GRP1_COMP
  *         @arg @ref LL_C2_SYSCFG_GRP1_ADC
  *         @arg @ref LL_C2_SYSCFG_GRP1_DAC
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI0
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI1
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI2
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI3
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI4
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI5
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI6
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI7
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI8
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI9
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI10
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI11
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI12
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI13
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI14
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI15
  * @retval None
  */
__STATIC_INLINE void LL_C2_SYSCFG_GRP1_EnableIT(uint32_t Interrupt)
{
  CLEAR_BIT(SYSCFG->C2IMR1, Interrupt);
}

/**
  * @brief  Enable CPU2 Interrupt Mask
  * @rmtoll SYSCFG_C2IMR2  DMA1CHxIM   LL_C2_SYSCFG_GRP2_EnableIT\n
  *         SYSCFG_C2IMR2  DMA2CHxIM   LL_C2_SYSCFG_GRP2_EnableIT\n
  *         SYSCFG_C2IMR2  DMAMUX1IM   LL_C2_SYSCFG_GRP2_EnableIT\n
  *         SYSCFG_C2IMR2  PVM3IM      LL_C2_SYSCFG_GRP2_EnableIT\n
  *         SYSCFG_C2IMR2  PVDIM       LL_C2_SYSCFG_GRP2_EnableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH1
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH2
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH3
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH4
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH5
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH6
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH7
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH1
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH2
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH3
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH4
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH5
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH6
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH7
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMAMUX1
  *         @arg @ref LL_C2_SYSCFG_GRP2_PVM3
  *         @arg @ref LL_C2_SYSCFG_GRP2_PVD
  * @retval None
  */
__STATIC_INLINE void LL_C2_SYSCFG_GRP2_EnableIT(uint32_t Interrupt)
{
  CLEAR_BIT(SYSCFG->C2IMR2, Interrupt);
}

/**
  * @brief  Disable CPU2 Interrupt Mask
  * @rmtoll SYSCFG_C2IMR1  RTCSTAMPTAMPLSECSS      LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  RTCALARMIM  LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  RTCSSRUIM   LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  RTCWKUPIM   LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  RCCIM       LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  FLASHIM     LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  PKAIM       LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  RNGIM       LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  AESIM       LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  COMPIM      LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  ADCIM       LL_C2_SYSCFG_GRP1_DisableIT\n
  *         SYSCFG_C2IMR1  EXTIxIM     LL_C2_SYSCFG_GRP1_DisableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCSTAMP_RTCTAMP_LSECSS
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCALARM
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCSSRU
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCWKUP
  *         @arg @ref LL_C2_SYSCFG_GRP1_RCC
  *         @arg @ref LL_C2_SYSCFG_GRP1_FLASH
  *         @arg @ref LL_C2_SYSCFG_GRP1_AES
  *         @arg @ref LL_C2_SYSCFG_GRP1_COMP
  *         @arg @ref LL_C2_SYSCFG_GRP1_ADC
  *         @arg @ref LL_C2_SYSCFG_GRP1_DAC
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI0
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI1
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI2
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI3
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI4
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI5
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI6
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI7
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI8
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI9
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI10
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI11
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI12
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI13
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI14
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI15
  * @retval None
  */
__STATIC_INLINE void LL_C2_SYSCFG_GRP1_DisableIT(uint32_t Interrupt)
{
  SET_BIT(SYSCFG->C2IMR1, Interrupt);
}

/**
  * @brief  Disable CPU2 Interrupt Mask
  * @rmtoll SYSCFG_C2IMR2  DMA1CHxIM   LL_C2_SYSCFG_GRP2_DisableIT\n
  *         SYSCFG_C2IMR2  DMA2CHxIM   LL_C2_SYSCFG_GRP2_DisableIT\n
  *         SYSCFG_C2IMR2  DMAMUX1IM   LL_C2_SYSCFG_GRP2_DisableIT\n
  *         SYSCFG_C2IMR2  PVM3IM      LL_C2_SYSCFG_GRP2_DisableIT\n
  *         SYSCFG_C2IMR2  PVDIM       LL_C2_SYSCFG_GRP2_DisableIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH1
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH2
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH3
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH4
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH5
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH6
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH7
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH1
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH2
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH3
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH4
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH5
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH6
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH7
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMAMUX1
  *         @arg @ref LL_C2_SYSCFG_GRP2_PVM3
  *         @arg @ref LL_C2_SYSCFG_GRP2_PVD
  * @retval None
  */
__STATIC_INLINE void LL_C2_SYSCFG_GRP2_DisableIT(uint32_t Interrupt)
{
  SET_BIT(SYSCFG->C2IMR2, Interrupt);
}

/**
  * @brief  Indicate if CPU2 Interrupt Mask is enabled
  * @rmtoll SYSCFG_C2IMR1  RTCSTAMPTAMPLSECSS      LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  RTCALARMIM  LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  RTCSSRUIM   LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  RTCWKUPIM   LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  RCCIM       LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  FLASHIM     LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  PKAIM       LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  RNGIM       LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  AESIM       LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  COMPIM      LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  ADCIM       LL_C2_SYSCFG_GRP1_IsEnabledIT\n
  *         SYSCFG_C2IMR1  EXTIxIM     LL_C2_SYSCFG_GRP1_IsEnabledIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCSTAMP_RTCTAMP_LSECSS
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCALARM
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCSSRU
  *         @arg @ref LL_C2_SYSCFG_GRP1_RTCWKUP
  *         @arg @ref LL_C2_SYSCFG_GRP1_RCC
  *         @arg @ref LL_C2_SYSCFG_GRP1_FLASH
  *         @arg @ref LL_C2_SYSCFG_GRP1_PKA
  *         @arg @ref LL_C2_SYSCFG_GRP1_AES
  *         @arg @ref LL_C2_SYSCFG_GRP1_COMP
  *         @arg @ref LL_C2_SYSCFG_GRP1_ADC
  *         @arg @ref LL_C2_SYSCFG_GRP1_DAC
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI0
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI1
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI2
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI3
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI4
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI5
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI6
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI7
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI8
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI9
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI10
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI11
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI12
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI13
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI14
  *         @arg @ref LL_C2_SYSCFG_GRP1_EXTI15
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_SYSCFG_GRP1_IsEnabledIT(uint32_t Interrupt)
{
  return ((READ_BIT(SYSCFG->C2IMR1, Interrupt) != (Interrupt)) ? 1UL : 0UL);
}

/**
  * @brief  Indicate if CPU2 Interrupt Mask is enabled
  * @rmtoll SYSCFG_C2IMR2  DMA1CHxIM   LL_C2_SYSCFG_GRP2_IsEnabledIT\n
  *         SYSCFG_C2IMR2  DMA2CHxIM   LL_C2_SYSCFG_GRP2_IsEnabledIT\n
  *         SYSCFG_C2IMR2  DMAMUX1IM   LL_C2_SYSCFG_GRP2_IsEnabledIT\n
  *         SYSCFG_C2IMR2  PVM3IM      LL_C2_SYSCFG_GRP2_IsEnabledIT\n
  *         SYSCFG_C2IMR2  PVDIM       LL_C2_SYSCFG_GRP2_IsEnabledIT
  * @param  Interrupt This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH1
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH2
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH3
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH4
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH5
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH6
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA1CH7
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH1
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH2
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH3
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH4
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH5
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH6
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMA2CH7
  *         @arg @ref LL_C2_SYSCFG_GRP2_DMAMUX1
  *         @arg @ref LL_C2_SYSCFG_GRP2_PVM3
  *         @arg @ref LL_C2_SYSCFG_GRP2_PVD
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_C2_SYSCFG_GRP2_IsEnabledIT(uint32_t Interrupt)
{
  return ((READ_BIT(SYSCFG->C2IMR2, Interrupt) != (Interrupt)) ? 1UL : 0UL);
}
#endif /* DUAL_CORE */

/**
  * @brief  Set radio debug test bus type, analog or digital
  * @rmtoll SYSCFG_RFDR RFTBSEL      LL_SYSCFG_SetRadioDebugTestBus
  * @param  RadioDebugTestBus This parameter can be one of the following values:
  *         @arg @ref LL_SYSCFG_ANALOG_TEST_BUS
  *         @arg @ref LL_SYSCFG_DIGITAL_TEST_BUS
  * @retval None
  */
__STATIC_INLINE void LL_SYSCFG_SetRadioDebugTestBus(uint32_t RadioDebugTestBus)
{
  MODIFY_REG(SYSCFG->RFDCR, SYSCFG_RFDCR_RFTBSEL, RadioDebugTestBus);
}

/**
  * @brief  Get radio debug test bus type, analog or digital
  * @rmtoll SYSCFG_RFDR RFTBSEL      LL_SYSCFG_GetRadioDebugTestBus
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_SYSCFG_ANALOG_TEST_BUS
  *         @arg @ref LL_SYSCFG_DIGITAL_TEST_BUS
  */
__STATIC_INLINE uint32_t LL_SYSCFG_GetRadioDebugTestBus(void)
{
  return (uint32_t)(READ_BIT(SYSCFG->RFDCR, SYSCFG_RFDCR_RFTBSEL));
}
/**
  * @}
  */

/** @defgroup SYSTEM_LL_EF_DBGMCU DBGMCU
  * @note  DBGMCU is only accessible by Cortex M4
  *        To access on DBGMCU, Cortex M0+ need to request to the Cortex M4
  *        the action.
  * @{
  */

#if defined(CORE_CM0PLUS)
#else
/**
  * @brief  Return the device identifier
  * @note   For STM32WLxxxx devices, the device ID is 0x497
  * @rmtoll DBGMCU_IDCODE DEV_ID        LL_DBGMCU_GetDeviceID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFF (ex: device ID is 0x497)
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetDeviceID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_DEV_ID));
}

/**
  * @brief  Return the device revision identifier
  * @note   This field indicates the revision of the device.
  * @rmtoll DBGMCU_IDCODE REV_ID        LL_DBGMCU_GetRevisionID
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t LL_DBGMCU_GetRevisionID(void)
{
  return (uint32_t)(READ_BIT(DBGMCU->IDCODE, DBGMCU_IDCODE_REV_ID) >> DBGMCU_IDCODE_REV_ID_Pos);
}

/**
  * @brief  Enable the CPU1 Debug Module during SLEEP mode
  * @rmtoll DBGMCU_CR    DBG_SLEEP     LL_DBGMCU_EnableDBGSleepMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGSleepMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Disable the CPU1 Debug Module during SLEEP mode
  * @rmtoll DBGMCU_CR    DBG_SLEEP     LL_DBGMCU_DisableDBGSleepMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGSleepMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_SLEEP);
}

/**
  * @brief  Enable the Debug Module during STOP mode
  * @note  This bit does not influence CPU2 operation, CPU2 cannot be debugged
  *        in Stop mode even when this bit is enabled
  * @rmtoll DBGMCU_CR    DBG_STOP      LL_DBGMCU_EnableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStopMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Disable the Debug Module during STOP mode
  * @rmtoll DBGMCU_CR    DBG_STOP      LL_DBGMCU_DisableDBGStopMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStopMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STOP);
}

/**
  * @brief  Enable the Debug Module during STANDBY mode
  * @note  This bit does not influence CPU2 operation, CPU2 cannot be debugged
  *        in Standby mode even when this bit is enabled
  * @rmtoll DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_EnableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_EnableDBGStandbyMode(void)
{
  SET_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Disable the Debug Module during STANDBY mode
  * @rmtoll DBGMCU_CR    DBG_STANDBY   LL_DBGMCU_DisableDBGStandbyMode
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_DisableDBGStandbyMode(void)
{
  CLEAR_BIT(DBGMCU->CR, DBGMCU_CR_DBG_STANDBY);
}

/**
  * @brief  Freeze CPU1 APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZR1 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB1FZR1, Periphs);
}

#if defined(DUAL_CORE)
/**
  * @brief  Freeze CPU2 APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_C2APB1FZR1 DBG_xxxx_STOP  LL_C2_DBGMCU_APB1_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_I2C2_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_I2C3_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_C2_DBGMCU_APB1_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->C2APB1FZR1, Periphs);
}
#endif /* DUAL_CORE */

/**
  * @brief  Freeze CPU1 APB1 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_APB1FZR2 LL_DBGMCU_APB1_GRP2_LPTIM2_STOP  LL_DBGMCU_APB1_GRP2_FreezePeriph
  *         DBGMCU_APB1FZR2 LL_DBGMCU_APB1_GRP2_LPTIM3_STOP  LL_DBGMCU_APB1_GRP2_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_LPTIM3_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB1FZR2, Periphs);
}

#if defined(DUAL_CORE)
/**
  * @brief  Freeze CPU2 APB1 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_APB1FZR2 LL_C2_DBGMCU_APB1_GRP2_LPTIM2_STOP  LL_C2_DBGMCU_APB1_GRP2_FreezePeriph
  *         DBGMCU_APB1FZR2 LL_C2_DBGMCU_APB1_GRP2_LPTIM3_STOP  LL_C2_DBGMCU_APB1_GRP2_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP2_LPTIM2_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP2_LPTIM3_STOP
  * @retval None
  */
__STATIC_INLINE void LL_C2_DBGMCU_APB1_GRP2_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->C2APB1FZR2, Periphs);
}
#endif /* DUAL_CORE */

/**
  * @brief  Unfreeze CPU1 APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_APB1FZR1 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_WWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_I2C3_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB1FZR1, Periphs);
}

#if defined(DUAL_CORE)
/**
  * @brief  Unfreeze CPU2 APB1 peripherals (group1 peripherals)
  * @rmtoll DBGMCU_C2APB1FZR1 DBG_xxxx_STOP  LL_C2_DBGMCU_APB1_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_TIM2_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_RTC_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_IWDG_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_I2C1_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_I2C3_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP1_LPTIM1_STOP
  * @retval None
  */
__STATIC_INLINE void LL_C2_DBGMCU_APB1_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->C2APB1FZR1, Periphs);
}
#endif /* DUAL_CORE */

/**
  * @brief  Unfreeze CPU1 APB1 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_APB1FZR2 DBG_xxxx_STOP  LL_DBGMCU_APB1_GRP2_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB1_GRP2_LPTIM2_STOP
  *         @arg @ref LL_DBGMCU_APB1_GRP2_LPTIM3_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB1_GRP2_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB1FZR2, Periphs);
}

#if defined(DUAL_CORE)
/**
  * @brief  Unfreeze CPU2 APB1 peripherals (group2 peripherals)
  * @rmtoll DBGMCU_C2APB1FZR2 DBG_xxxx_STOP  LL_C2_DBGMCU_APB1_GRP2_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP2_LPTIM2_STOP
  *         @arg @ref LL_C2_DBGMCU_APB1_GRP2_LPTIM3_STOP
  * @retval None
  */
__STATIC_INLINE void LL_C2_DBGMCU_APB1_GRP2_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->C2APB1FZR2, Periphs);
}
#endif /* DUAL_CORE */

/**
  * @brief  Freeze CPU1 APB2 peripherals
  * @rmtoll DBGMCU_APB2FZR DBG_TIMx_STOP  LL_DBGMCU_APB2_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->APB2FZR, Periphs);
}

#if defined(DUAL_CORE)
/**
  * @brief  Freeze CPU2 APB2 peripherals
  * @rmtoll DBGMCU_C2APB2FZR DBG_TIMx_STOP  LL_C2_DBGMCU_APB2_GRP1_FreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_C2_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_C2_DBGMCU_APB2_GRP1_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_C2_DBGMCU_APB2_GRP1_FreezePeriph(uint32_t Periphs)
{
  SET_BIT(DBGMCU->C2APB2FZR, Periphs);
}
#endif /* DUAL_CORE */

/**
  * @brief  Unfreeze CPU1 APB2 peripherals
  * @rmtoll DBGMCU_APB2FZR DBG_TIMx_STOP  LL_DBGMCU_APB2_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_DBGMCU_APB2_GRP1_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_DBGMCU_APB2_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->APB2FZR, Periphs);
}

#if defined(DUAL_CORE)
/**
  * @brief  Unfreeze CPU2 APB2 peripherals
  * @rmtoll DBGMCU_C2APB2FZR DBG_TIMx_STOP  LL_C2_DBGMCU_APB2_GRP1_UnFreezePeriph
  * @param  Periphs This parameter can be a combination of the following values:
  *         @arg @ref LL_C2_DBGMCU_APB2_GRP1_TIM1_STOP
  *         @arg @ref LL_C2_DBGMCU_APB2_GRP1_TIM16_STOP
  *         @arg @ref LL_C2_DBGMCU_APB2_GRP1_TIM17_STOP
  * @retval None
  */
__STATIC_INLINE void LL_C2_DBGMCU_APB2_GRP1_UnFreezePeriph(uint32_t Periphs)
{
  CLEAR_BIT(DBGMCU->C2APB2FZR, Periphs);
}
#endif /* DUAL_CORE */

#endif
/**
  * @}
  */

#if defined(VREFBUF)
/** @defgroup SYSTEM_LL_EF_VREFBUF VREFBUF
  * @{
  */

/**
  * @brief  Enable Internal voltage reference
  * @rmtoll VREFBUF_CSR  ENVR          LL_VREFBUF_Enable
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_Enable(void)
{
  SET_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);
}

/**
  * @brief  Disable Internal voltage reference
  * @rmtoll VREFBUF_CSR  ENVR          LL_VREFBUF_Disable
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_Disable(void)
{
  CLEAR_BIT(VREFBUF->CSR, VREFBUF_CSR_ENVR);
}

/**
  * @brief  Enable high impedance (VREF+pin is high impedance)
  * @rmtoll VREFBUF_CSR  HIZ           LL_VREFBUF_EnableHIZ
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_EnableHIZ(void)
{
  SET_BIT(VREFBUF->CSR, VREFBUF_CSR_HIZ);
}

/**
  * @brief  Disable high impedance (VREF+pin is internally connected to the voltage reference buffer output)
  * @rmtoll VREFBUF_CSR  HIZ           LL_VREFBUF_DisableHIZ
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_DisableHIZ(void)
{
  CLEAR_BIT(VREFBUF->CSR, VREFBUF_CSR_HIZ);
}

/**
  * @brief  Set the Voltage reference scale
  * @rmtoll VREFBUF_CSR  VRS           LL_VREFBUF_SetVoltageScaling
  * @param  Scale This parameter can be one of the following values:
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE0
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE1
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_SetVoltageScaling(uint32_t Scale)
{
  MODIFY_REG(VREFBUF->CSR, VREFBUF_CSR_VRS, Scale);
}

/**
  * @brief  Get the Voltage reference scale
  * @rmtoll VREFBUF_CSR  VRS           LL_VREFBUF_GetVoltageScaling
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE0
  *         @arg @ref LL_VREFBUF_VOLTAGE_SCALE1
  */
__STATIC_INLINE uint32_t LL_VREFBUF_GetVoltageScaling(void)
{
  return (uint32_t)(READ_BIT(VREFBUF->CSR, VREFBUF_CSR_VRS));
}

/**
  * @brief  Get the VREFBUF trimming value for VRS=0 (VREF_SC0)
  * @retval Between 0 and 0x3F
  */
__STATIC_INLINE uint32_t LL_VREFBUF_SC0_GetCalibration(void)
{
  return (uint32_t)(*VREFBUF_SC0_CAL_ADDR);
}

/**
  * @brief  Get the VREFBUF trimming value for VRS=1 (VREF_SC1)
  * @retval Between 0 and 0x3F
  */
__STATIC_INLINE uint32_t LL_VREFBUF_SC1_GetCalibration(void)
{
  return (uint32_t)(*VREFBUF_SC1_CAL_ADDR);
}

/**
  * @brief  Check if Voltage reference buffer is ready
  * @rmtoll VREFBUF_CSR  VRR           LL_VREFBUF_IsVREFReady
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_VREFBUF_IsVREFReady(void)
{
  return ((READ_BIT(VREFBUF->CSR, VREFBUF_CSR_VRR) == (VREFBUF_CSR_VRR)) ? 1UL : 0UL);
}

/**
  * @brief  Get the trimming code for VREFBUF calibration
  * @rmtoll VREFBUF_CCR  TRIM          LL_VREFBUF_GetTrimming
  * @retval Between 0 and 0x3F
  */
__STATIC_INLINE uint32_t LL_VREFBUF_GetTrimming(void)
{
  return (uint32_t)(READ_BIT(VREFBUF->CCR, VREFBUF_CCR_TRIM));
}

/**
  * @brief  Set the trimming code for VREFBUF calibration (Tune the internal reference buffer voltage)
  * @note   Each VrefBuf voltage scale is calibrated in production for each device,
  *         data stored in flash memory.
  *         Functions @ref LL_VREFBUF_SC0_GetCalibration and 
  *         @ref LL_VREFBUF_SC0_GetCalibration can be used to retrieve
  *         these calibration data.
  * @rmtoll VREFBUF_CCR  TRIM          LL_VREFBUF_SetTrimming
  * @param  Value Between 0 and 0x3F
  * @retval None
  */
__STATIC_INLINE void LL_VREFBUF_SetTrimming(uint32_t Value)
{
  WRITE_REG(VREFBUF->CCR, Value);
}

/**
  * @}
  */
#endif /* VREFBUF */

/** @defgroup SYSTEM_LL_EF_FLASH FLASH
  * @{
  */

/**
  * @brief  Set FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_SetLatency
  * @param  Latency This parameter can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_2
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetLatency(uint32_t Latency)
{
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, Latency);
}

/**
  * @brief  Get FLASH Latency
  * @rmtoll FLASH_ACR    LATENCY       LL_FLASH_GetLatency
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_FLASH_LATENCY_0
  *         @arg @ref LL_FLASH_LATENCY_1
  *         @arg @ref LL_FLASH_LATENCY_2
  */
__STATIC_INLINE uint32_t LL_FLASH_GetLatency(void)
{
  return (uint32_t)(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY));
}

/**
  * @brief  Enable Prefetch
  * @rmtoll FLASH_ACR    PRFTEN        LL_FLASH_EnablePrefetch
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnablePrefetch(void)
{
#if defined(CORE_CM0PLUS)
  SET_BIT(FLASH->C2ACR, FLASH_C2ACR_PRFTEN);
#else
  SET_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
#endif
}

/**
  * @brief  Disable Prefetch
  * @rmtoll FLASH_ACR    PRFTEN        LL_FLASH_DisablePrefetch
  * @rmtoll FLASH_C2ACR  PRFTEN        LL_FLASH_DisablePrefetch
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisablePrefetch(void)
{
#if defined(CORE_CM0PLUS)
  CLEAR_BIT(FLASH->C2ACR, FLASH_C2ACR_PRFTEN);
#else
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_PRFTEN);
#endif
}

/**
  * @brief  Check if Prefetch buffer is enabled
  * @rmtoll FLASH_ACR    PRFTEN        LL_FLASH_IsPrefetchEnabled
  * @rmtoll FLASH_C2ACR  C2PRFTEN      LL_FLASH_IsPrefetchEnabled
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsPrefetchEnabled(void)
{
#if defined(CORE_CM0PLUS)
  return ((READ_BIT(FLASH->C2ACR, FLASH_C2ACR_PRFTEN) == (FLASH_C2ACR_PRFTEN)) ? 1UL : 0UL);
#else
  return ((READ_BIT(FLASH->ACR, FLASH_ACR_PRFTEN) == (FLASH_ACR_PRFTEN)) ? 1UL : 0UL);
#endif
}

/**
  * @brief  Enable Instruction cache
  * @rmtoll FLASH_ACR    ICEN          LL_FLASH_EnableInstCache
  * @rmtoll FLASH_C2ACR  ICEN          LL_FLASH_EnableInstCache
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableInstCache(void)
{
#if defined(CORE_CM0PLUS)
  SET_BIT(FLASH->C2ACR, FLASH_C2ACR_ICEN);
#else
  SET_BIT(FLASH->ACR, FLASH_ACR_ICEN);
#endif
}

/**
  * @brief  Disable Instruction cache
  * @rmtoll FLASH_ACR    ICEN          LL_FLASH_DisableInstCache
  * @rmtoll FLASH_C2ACR  ICEN          LL_FLASH_DisableInstCache
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableInstCache(void)
{
#if defined(CORE_CM0PLUS)
  CLEAR_BIT(FLASH->C2ACR, FLASH_C2ACR_ICEN);
#else
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_ICEN);
#endif
}

#if defined(CORE_CM0PLUS)
#else
/**
  * @brief  Enable Data cache
  * @rmtoll FLASH_ACR    DCEN          LL_FLASH_EnableDataCache
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableDataCache(void)
{
  SET_BIT(FLASH->ACR, FLASH_ACR_DCEN);
}

/**
  * @brief  Disable Data cache
  * @rmtoll FLASH_ACR    DCEN          LL_FLASH_DisableDataCache
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableDataCache(void)
{
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_DCEN);
}
#endif

/**
  * @brief  Enable Instruction cache reset
  * @note  bit can be written only when the instruction cache is disabled
  * @rmtoll FLASH_ACR    ICRST         LL_FLASH_EnableInstCacheReset
  * @rmtoll FLASH_C2ACR  ICRST         LL_FLASH_EnableInstCacheReset
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableInstCacheReset(void)
{
#if defined(CORE_CM0PLUS)
  SET_BIT(FLASH->C2ACR, FLASH_C2ACR_ICRST);
#else
  SET_BIT(FLASH->ACR, FLASH_ACR_ICRST);
#endif
}

/**
  * @brief  Disable Instruction cache reset
  * @rmtoll FLASH_ACR    ICRST         LL_FLASH_DisableInstCacheReset
  * @rmtoll FLASH_C2ACR  ICRST         LL_FLASH_DisableInstCacheReset
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableInstCacheReset(void)
{
#if defined(CORE_CM0PLUS)
  CLEAR_BIT(FLASH->C2ACR, FLASH_C2ACR_ICRST);
#else
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_ICRST);
#endif
}

#if defined(CORE_CM0PLUS)
#else
/**
  * @brief  Enable Data cache reset
  * @note bit can be written only when the data cache is disabled
  * @rmtoll FLASH_ACR    DCRST         LL_FLASH_EnableDataCacheReset
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_EnableDataCacheReset(void)
{
  SET_BIT(FLASH->ACR, FLASH_ACR_DCRST);
}

/**
  * @brief  Disable Data cache reset
  * @rmtoll FLASH_ACR    DCRST         LL_FLASH_DisableDataCacheReset
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_DisableDataCacheReset(void)
{
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_DCRST);
}
#endif

/**
  * @brief  Suspend new program or erase operation request
  * @note   Any new Flash program and erase operation on both CPU side will be suspended
  *         until this bit and the same bit in Flash CPU2 access control register (FLASH_C2ACR) are
  *         cleared. The PESD bit in both the Flash status register (FLASH_SR) and Flash
  *         CPU2 status register (FLASH_C2SR) register will be set when at least one PES
  *         bit in FLASH_ACR or FLASH_C2ACR is set.
  * @rmtoll FLASH_ACR    PES         LL_FLASH_SuspendOperation
  * @rmtoll FLASH_C2ACR  PES         LL_FLASH_SuspendOperation
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SuspendOperation(void)
{
#if defined(CORE_CM0PLUS)
  SET_BIT(FLASH->C2ACR, FLASH_C2ACR_PES);
#else
  SET_BIT(FLASH->ACR, FLASH_ACR_PES);
#endif
}

/**
  * @brief  Allow new program or erase operation request
  * @note   Any new Flash program and erase operation on both CPU side will be allowed
  *         until one of this bit or the same bit in Flash CPU2 access control register (FLASH_C2ACR) is
  *         set. The PESD bit in both the Flash status register (FLASH_SR) and Flash
  *         CPU2 status register (FLASH_C2SR) register will be clear when both PES
  *         bit in FLASH_ACR or FLASH_C2ACR is cleared.
  * @rmtoll FLASH_ACR    PES      LL_FLASH_AllowOperation
  * @rmtoll FLASH_C2ACR  PES      LL_FLASH_AllowOperation
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_AllowOperation(void)
{
#if defined(CORE_CM0PLUS)
  CLEAR_BIT(FLASH->C2ACR, FLASH_C2ACR_PES);
#else
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_PES);
#endif
}

/**
  * @brief  Check if new program or erase operation request from CPU2 is suspended
  * @rmtoll FLASH_ACR    PES         LL_FLASH_IsOperationSuspended
  * @rmtoll FLASH_C2ACR  PES         LL_FLASH_IsOperationSuspended
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsOperationSuspended(void)
{
#if defined(CORE_CM0PLUS)
  return ((READ_BIT(FLASH->C2ACR, FLASH_C2ACR_PES) == (FLASH_C2ACR_PES)) ? 1UL : 0UL);
#else
  return ((READ_BIT(FLASH->ACR, FLASH_ACR_PES) == (FLASH_ACR_PES)) ? 1UL : 0UL);
#endif
}

/**
  * @brief  Check if new program or erase operation request from CPU1 or CPU2 is suspended
  * @rmtoll FLASH_SR      PESD         LL_FLASH_IsActiveFlag_OperationSuspended
  * @rmtoll FLASH_C2SR    PESD         LL_FLASH_IsActiveFlag_OperationSuspended
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsActiveFlag_OperationSuspended(void)
{
#if defined(CORE_CM0PLUS)
  return ((READ_BIT(FLASH->C2SR, FLASH_C2SR_PESD) == (FLASH_C2SR_PESD)) ? 1UL : 0UL);
#else
  return ((READ_BIT(FLASH->SR, FLASH_SR_PESD) == (FLASH_SR_PESD)) ? 1UL : 0UL);
#endif
}

/**
  * @brief  Set EMPTY flag information as Flash User area empty
  * @rmtoll FLASH_ACR    EMPTY      LL_FLASH_SetEmptyFlag
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_SetEmptyFlag(void)
{
  SET_BIT(FLASH->ACR, FLASH_ACR_EMPTY);
}

/**
  * @brief  Clear EMPTY flag information as Flash User area programmed
  * @rmtoll FLASH_ACR    EMPTY      LL_FLASH_ClearEmptyFlag
  * @retval None
  */
__STATIC_INLINE void LL_FLASH_ClearEmptyFlag(void)
{
  CLEAR_BIT(FLASH->ACR, FLASH_ACR_EMPTY);
}

/**
  * @brief  Check if the EMPTY flag is set or reset
  * @rmtoll FLASH_ACR    EMPTY      LL_FLASH_IsEmptyFlag
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FLASH_IsEmptyFlag(void)
{
  return ((READ_BIT(FLASH->ACR, FLASH_ACR_EMPTY) == FLASH_ACR_EMPTY) ? 1UL : 0UL);
}

#if defined(DUAL_CORE)
/**
  * @brief  Get IPCC buffer base address
  * @rmtoll FLASH_IPCCBR    IPCCDBA       LL_FLASH_GetIPCCBufferAddr
  * @retval IPCC data buffer base address offset
  */
__STATIC_INLINE uint32_t LL_FLASH_GetIPCCBufferAddr(void)
{
  return (uint32_t)(READ_BIT(FLASH->IPCCBR, FLASH_IPCCBR_IPCCDBA));
}
#endif /* DUAL_CORE */

#if defined(DUAL_CORE)
/**
  * @brief  Get CPU2 boot reset vector
  * @rmtoll FLASH_SRRVR    SBRV       LL_FLASH_GetC2BootResetVect
  * @retval CPU2 boot reset vector
  */
__STATIC_INLINE uint32_t LL_FLASH_GetC2BootResetVect(void)
{
  return (uint32_t)(READ_BIT(FLASH->SRRVR, FLASH_SRRVR_SBRV));
}
#endif /* DUAL_CORE */

/**
  * @brief  Return the Unique Device Number
  * @retval Values between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t LL_FLASH_GetUDN(void)
{
  return (READ_REG(*((uint32_t *)UID64_BASE)));
}

/**
  * @brief  Return the Device ID
  *         For STM32WLxxxx devices, the device ID is 0x15
  * @retval Values between Min_Data=0x00 and Max_Data=0xFF (ex: Device ID is 0x15)
  */
__STATIC_INLINE uint32_t LL_FLASH_GetDeviceID(void)
{
  return ((READ_REG(*((uint32_t *)UID64_BASE + 1U))) & 0x000000FFU);
}

/**
  * @brief  Return the ST Company ID
  * @note   For STM32WLxxxx devices, the ST Company ID is 0x0080E1
  * @retval Values between Min_Data=0x00 and Max_Data=0xFFFFFF (ex: ST Company ID is 0x0080E1)
  */
__STATIC_INLINE uint32_t LL_FLASH_GetSTCompanyID(void)
{
  return (((READ_REG(*((uint32_t *)UID64_BASE + 1U))) >> 8U) & 0x00FFFFFFU);
}
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined (FLASH) || defined (SYSCFG) || defined (DBGMCU) || defined (VREFBUF) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WLxx_LL_SYSTEM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
