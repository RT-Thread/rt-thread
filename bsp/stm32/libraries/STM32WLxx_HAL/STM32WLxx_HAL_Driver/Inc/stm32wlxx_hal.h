/**
  ******************************************************************************
  * @file    stm32wlxx_hal.h
  * @author  MCD Application Team
  * @brief   This file contains all the functions prototypes for the HAL
  *          module driver.
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
#ifndef __STM32WLxx_HAL_H
#define __STM32WLxx_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal_conf.h"
#include "stm32wlxx_ll_system.h"

/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @defgroup HAL HAL
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup HAL_Exported_Structures HAL Exported Structures
  * @{
  */

/** @defgroup HAL_TICK_FREQ Tick Frequency
  * @{
  */
typedef enum
{
  HAL_TICK_FREQ_10HZ         = 100U,
  HAL_TICK_FREQ_100HZ        = 10U,
  HAL_TICK_FREQ_1KHZ         = 1U,
  HAL_TICK_FREQ_DEFAULT      = HAL_TICK_FREQ_1KHZ
} HAL_TickFreqTypeDef;
/**
  * @}
  */

#if defined(DUAL_CORE)
/** @defgroup HAL_SYSCFG_IM HAL SYSCFG Interrupt Mask
  * @{
  */
/**
  * @brief SYSCFG Interrupt Mask structure definition
  */
typedef struct
{
  uint32_t InterruptMask1;      /*!< The SYSCFG Interrupt Mask to be configured.
                                     This parameter can be a combination of @ref SYSCFG_IM_GRP1 */
  uint32_t InterruptMask2;      /*!< The SYSCFG Interrupt Mask to be configured.
                                     This parameter can be a combination of @ref SYSCFG_IM_GRP2 */
} SYSCFG_InterruptTypeDef;
/**
  * @}
  */
#endif

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/
/** @defgroup HAL_Exported_Constants HAL Exported Constants
  * @{
  */

/** @defgroup SYSCFG_Exported_Constants SYSCFG Exported Constants
  * @{
  */

/** @defgroup SYSCFG_BootMode BOOT Mode
  * @{
  */
#define SYSCFG_BOOT_MAINFLASH           LL_SYSCFG_REMAP_FLASH           /*!< Main Flash memory mapped at 0x00000000   */
#define SYSCFG_BOOT_SYSTEMFLASH         LL_SYSCFG_REMAP_SYSTEMFLASH     /*!< System Flash memory mapped at 0x00000000 */
#define SYSCFG_BOOT_SRAM                LL_SYSCFG_REMAP_SRAM            /*!< SRAM1 mapped at 0x00000000               */
/**
  * @}
  */

/** @defgroup SYSCFG_SRAM2WRP SRAM2 Page Write protection (0 to 31)
  * @{
  */
#define SYSCFG_SRAM2WRP_PAGE0           LL_SYSCFG_SRAM2WRP_PAGE0        /*!< SRAM2 Write protection page 0  */
#define SYSCFG_SRAM2WRP_PAGE1           LL_SYSCFG_SRAM2WRP_PAGE1        /*!< SRAM2 Write protection page 1  */
#define SYSCFG_SRAM2WRP_PAGE2           LL_SYSCFG_SRAM2WRP_PAGE2        /*!< SRAM2 Write protection page 2  */
#define SYSCFG_SRAM2WRP_PAGE3           LL_SYSCFG_SRAM2WRP_PAGE3        /*!< SRAM2 Write protection page 3  */
#define SYSCFG_SRAM2WRP_PAGE4           LL_SYSCFG_SRAM2WRP_PAGE4        /*!< SRAM2 Write protection page 4  */
#define SYSCFG_SRAM2WRP_PAGE5           LL_SYSCFG_SRAM2WRP_PAGE5        /*!< SRAM2 Write protection page 5  */
#define SYSCFG_SRAM2WRP_PAGE6           LL_SYSCFG_SRAM2WRP_PAGE6        /*!< SRAM2 Write protection page 6  */
#define SYSCFG_SRAM2WRP_PAGE7           LL_SYSCFG_SRAM2WRP_PAGE7        /*!< SRAM2 Write protection page 7  */
#define SYSCFG_SRAM2WRP_PAGE8           LL_SYSCFG_SRAM2WRP_PAGE8        /*!< SRAM2 Write protection page 8  */
#define SYSCFG_SRAM2WRP_PAGE9           LL_SYSCFG_SRAM2WRP_PAGE9        /*!< SRAM2 Write protection page 9  */
#define SYSCFG_SRAM2WRP_PAGE10          LL_SYSCFG_SRAM2WRP_PAGE10       /*!< SRAM2 Write protection page 10 */
#define SYSCFG_SRAM2WRP_PAGE11          LL_SYSCFG_SRAM2WRP_PAGE11       /*!< SRAM2 Write protection page 11 */
#define SYSCFG_SRAM2WRP_PAGE12          LL_SYSCFG_SRAM2WRP_PAGE12       /*!< SRAM2 Write protection page 12 */
#define SYSCFG_SRAM2WRP_PAGE13          LL_SYSCFG_SRAM2WRP_PAGE13       /*!< SRAM2 Write protection page 13 */
#define SYSCFG_SRAM2WRP_PAGE14          LL_SYSCFG_SRAM2WRP_PAGE14       /*!< SRAM2 Write protection page 14 */
#define SYSCFG_SRAM2WRP_PAGE15          LL_SYSCFG_SRAM2WRP_PAGE15       /*!< SRAM2 Write protection page 15 */
#define SYSCFG_SRAM2WRP_PAGE16          LL_SYSCFG_SRAM2WRP_PAGE16       /*!< SRAM2 Write protection page 16 */
#define SYSCFG_SRAM2WRP_PAGE17          LL_SYSCFG_SRAM2WRP_PAGE17       /*!< SRAM2 Write protection page 17 */
#define SYSCFG_SRAM2WRP_PAGE18          LL_SYSCFG_SRAM2WRP_PAGE18       /*!< SRAM2 Write protection page 18 */
#define SYSCFG_SRAM2WRP_PAGE19          LL_SYSCFG_SRAM2WRP_PAGE19       /*!< SRAM2 Write protection page 19 */
#define SYSCFG_SRAM2WRP_PAGE20          LL_SYSCFG_SRAM2WRP_PAGE20       /*!< SRAM2 Write protection page 20 */
#define SYSCFG_SRAM2WRP_PAGE21          LL_SYSCFG_SRAM2WRP_PAGE21       /*!< SRAM2 Write protection page 21 */
#define SYSCFG_SRAM2WRP_PAGE22          LL_SYSCFG_SRAM2WRP_PAGE22       /*!< SRAM2 Write protection page 22 */
#define SYSCFG_SRAM2WRP_PAGE23          LL_SYSCFG_SRAM2WRP_PAGE23       /*!< SRAM2 Write protection page 23 */
#define SYSCFG_SRAM2WRP_PAGE24          LL_SYSCFG_SRAM2WRP_PAGE24       /*!< SRAM2 Write protection page 24 */
#define SYSCFG_SRAM2WRP_PAGE25          LL_SYSCFG_SRAM2WRP_PAGE25       /*!< SRAM2 Write protection page 25 */
#define SYSCFG_SRAM2WRP_PAGE26          LL_SYSCFG_SRAM2WRP_PAGE26       /*!< SRAM2 Write protection page 26 */
#define SYSCFG_SRAM2WRP_PAGE27          LL_SYSCFG_SRAM2WRP_PAGE27       /*!< SRAM2 Write protection page 27 */
#define SYSCFG_SRAM2WRP_PAGE28          LL_SYSCFG_SRAM2WRP_PAGE28       /*!< SRAM2 Write protection page 28 */
#define SYSCFG_SRAM2WRP_PAGE29          LL_SYSCFG_SRAM2WRP_PAGE29       /*!< SRAM2 Write protection page 29 */
#define SYSCFG_SRAM2WRP_PAGE30          LL_SYSCFG_SRAM2WRP_PAGE30       /*!< SRAM2 Write protection page 30 */
#define SYSCFG_SRAM2WRP_PAGE31          LL_SYSCFG_SRAM2WRP_PAGE31       /*!< SRAM2 Write protection page 31 */

/**
  * @}
  */

#if defined(VREFBUF)
/** @defgroup SYSCFG_VREFBUF_VoltageScale VREFBUF Voltage Scale
  * @{
  */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE0   LL_VREFBUF_VOLTAGE_SCALE0       /*!< Voltage reference scale 0 (VREF_OUT1) */
#define SYSCFG_VREFBUF_VOLTAGE_SCALE1   LL_VREFBUF_VOLTAGE_SCALE1       /*!< Voltage reference scale 1 (VREF_OUT2) */

/**
  * @}
  */

/** @defgroup SYSCFG_VREFBUF_HighImpedance VREFBUF High Impedance
  * @{
  */
#define SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE   0x00000000U             /*!< VREF_plus pin is internally connected to Voltage reference buffer output */
#define SYSCFG_VREFBUF_HIGH_IMPEDANCE_ENABLE    VREFBUF_CSR_HIZ         /*!< VREF_plus pin is high impedance */

/**
  * @}
  */
#endif /* VREFBUF */

/** @defgroup SYSCFG_SRAM_flags_definition SRAM Flags
  * @{
  */

#define SYSCFG_FLAG_SRAM2_PE            SYSCFG_CFGR2_SPF                /*!< SRAM2 parity error */
#define SYSCFG_FLAG_SRAM_BUSY           SYSCFG_SCSR_SRAMBSY             /*!< SRAM1 or SRAM2 erase operation is ongoing */
#define SYSCFG_FLAG_PKASRAM_BUSY        SYSCFG_SCSR_PKASRAMBSY          /*!< PKA SRAM busy by erase operation */
/**
  * @}
  */

/** @defgroup SYSCFG_FastModePlus_GPIO Fast-mode Plus on GPIO
  * @{
  */

/** @brief  Fast-mode Plus driving capability on a specific GPIO
  */
#define SYSCFG_FASTMODEPLUS_PB6         SYSCFG_CFGR1_I2C_PB6_FMP        /*!< Enable Fast-mode Plus on PB6 */
#define SYSCFG_FASTMODEPLUS_PB7         SYSCFG_CFGR1_I2C_PB7_FMP        /*!< Enable Fast-mode Plus on PB7 */
#define SYSCFG_FASTMODEPLUS_PB8         SYSCFG_CFGR1_I2C_PB8_FMP        /*!< Enable Fast-mode Plus on PB8 */
#define SYSCFG_FASTMODEPLUS_PB9         SYSCFG_CFGR1_I2C_PB9_FMP        /*!< Enable Fast-mode Plus on PB9 */

/**
 * @}
 */

#if defined(DUAL_CORE)
/** @defgroup SYSCFG_IM_GRP1 SYSCFG INTERRUPT MASK GROUP1
  * @{
  */

#define HAL_SYSCFG_GRP1_RESERVED                0x00U                              /*!< Define user to differentiate Group1 to Group 2                */

#if defined(CORE_CM0PLUS)
/** @brief  Interrupt mask related to CPU2 NVIC
  */
#define HAL_SYSCFG_GRP1_RTCSTAMP_RTCTAMP_LSECSS  (LL_C2_SYSCFG_GRP1_RTCSTAMP_RTCTAMP_LSECSS | HAL_SYSCFG_GRP1_RESERVED)  /*!< Enabling of interrupt from RTC TimeStamp, RTC Tampers
                                                                                                                              and LSE Clock Security System to CPU2               */
#define HAL_SYSCFG_GRP1_RTCALARM                (LL_C2_SYSCFG_GRP1_RTCALARM        | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from RTC Alarms to CPU2                 */
#define HAL_SYSCFG_GRP1_RTCSSRU                 (LL_C2_SYSCFG_GRP1_RTCSSRU         | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from RTC SSRU to CPU2                   */
#define HAL_SYSCFG_GRP1_RTCWKUP                 (LL_C2_SYSCFG_GRP1_RTCWKUP         | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from RTC Wakeup to CPU2                 */
#define HAL_SYSCFG_GRP1_RCC                     (LL_C2_SYSCFG_GRP1_RCC             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from RCC to CPU2                        */
#define HAL_SYSCFG_GRP1_FLASH                   (LL_C2_SYSCFG_GRP1_FLASH           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from FLASH to CPU2                      */
#define HAL_SYSCFG_GRP1_PKA                     (LL_C2_SYSCFG_GRP1_PKA             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from PKA to CPU2                        */
#define HAL_SYSCFG_GRP1_AES                     (LL_C2_SYSCFG_GRP1_AES             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from AES to CPU2                        */
#define HAL_SYSCFG_GRP1_COMP                    (LL_C2_SYSCFG_GRP1_COMP            | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from Comparator to CPU2                 */
#define HAL_SYSCFG_GRP1_ADC                     (LL_C2_SYSCFG_GRP1_ADC             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from Analog Digital Converter to CPU2   */
#define HAL_SYSCFG_GRP1_DAC                     (LL_C2_SYSCFG_GRP1_DAC             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from Digital Analog Converter to CPU2   */

#define HAL_SYSCFG_GRP1_EXTI0                   (LL_C2_SYSCFG_GRP1_EXTI0           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 0 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI1                   (LL_C2_SYSCFG_GRP1_EXTI1           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 1 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI2                   (LL_C2_SYSCFG_GRP1_EXTI2           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 2 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI3                   (LL_C2_SYSCFG_GRP1_EXTI3           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 3 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI4                   (LL_C2_SYSCFG_GRP1_EXTI4           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 4 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI5                   (LL_C2_SYSCFG_GRP1_EXTI5           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 5 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI6                   (LL_C2_SYSCFG_GRP1_EXTI6           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 6 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI7                   (LL_C2_SYSCFG_GRP1_EXTI7           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 7 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI8                   (LL_C2_SYSCFG_GRP1_EXTI8           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 8 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI9                   (LL_C2_SYSCFG_GRP1_EXTI9           | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 9 to CPU2  */
#define HAL_SYSCFG_GRP1_EXTI10                  (LL_C2_SYSCFG_GRP1_EXTI10          | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 10 to CPU2 */
#define HAL_SYSCFG_GRP1_EXTI11                  (LL_C2_SYSCFG_GRP1_EXTI11          | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 11 to CPU2 */
#define HAL_SYSCFG_GRP1_EXTI12                  (LL_C2_SYSCFG_GRP1_EXTI12          | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 12 to CPU2 */
#define HAL_SYSCFG_GRP1_EXTI13                  (LL_C2_SYSCFG_GRP1_EXTI13          | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 13 to CPU2 */
#define HAL_SYSCFG_GRP1_EXTI14                  (LL_C2_SYSCFG_GRP1_EXTI14          | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 14 to CPU2 */
#define HAL_SYSCFG_GRP1_EXTI15                  (LL_C2_SYSCFG_GRP1_EXTI15          | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 15 to CPU2 */

#else

/** @brief  Interrupt mask related to CPU1 NVIC
  */
#define HAL_SYSCFG_GRP1_RTCSTAMPTAMPLSECSS      (LL_SYSCFG_GRP1_RTCSTAMPTAMPLSECSS | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from RTCSTAMPTAMPLSECSS to CPU1         */
#define HAL_SYSCFG_GRP1_RTCSSRU                 (LL_SYSCFG_GRP1_RTCSSRU            | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from RTC SSRU to CPU1                   */
#define HAL_SYSCFG_GRP1_EXTI5                   (LL_SYSCFG_GRP1_EXTI5              | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 5 to CPU1  */
#define HAL_SYSCFG_GRP1_EXTI6                   (LL_SYSCFG_GRP1_EXTI6              | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 6 to CPU1  */
#define HAL_SYSCFG_GRP1_EXTI7                   (LL_SYSCFG_GRP1_EXTI7              | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 7 to CPU1  */
#define HAL_SYSCFG_GRP1_EXTI8                   (LL_SYSCFG_GRP1_EXTI8              | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 8 to CPU1  */
#define HAL_SYSCFG_GRP1_EXTI9                   (LL_SYSCFG_GRP1_EXTI9              | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 9 to CPU1  */
#define HAL_SYSCFG_GRP1_EXTI10                  (LL_SYSCFG_GRP1_EXTI10             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 10 to CPU1 */
#define HAL_SYSCFG_GRP1_EXTI11                  (LL_SYSCFG_GRP1_EXTI11             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 11 to CPU1 */
#define HAL_SYSCFG_GRP1_EXTI12                  (LL_SYSCFG_GRP1_EXTI12             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 12 to CPU1 */
#define HAL_SYSCFG_GRP1_EXTI13                  (LL_SYSCFG_GRP1_EXTI13             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 13 to CPU1 */
#define HAL_SYSCFG_GRP1_EXTI14                  (LL_SYSCFG_GRP1_EXTI14             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 14 to CPU1 */
#define HAL_SYSCFG_GRP1_EXTI15                  (LL_SYSCFG_GRP1_EXTI15             | HAL_SYSCFG_GRP1_RESERVED) /*!< Enabling of interrupt from External Interrupt Line 15 to CPU1 */

#endif

/**
  * @}
  */

/** @defgroup SYSCFG_IM_GRP2 SYSCFG INTERRUPT MASK GROUP2
  * @{
  */

#define HAL_SYSCFG_GRP2_RESERVED                0x80U                              /*!< Define user to differentiate Group1 to Group 2                */

#if defined(CORE_CM0PLUS)
/** @brief  Interrupt mask related to CPU2 NVIC
  */
#define HAL_SYSCFG_GRP2_DMA1CH1                 (LL_C2_SYSCFG_GRP2_DMA1CH1         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA1 Channel 1 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA1CH2                 (LL_C2_SYSCFG_GRP2_DMA1CH2         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA1 Channel 2 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA1CH3                 (LL_C2_SYSCFG_GRP2_DMA1CH3         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA1 Channel 3 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA1CH4                 (LL_C2_SYSCFG_GRP2_DMA1CH4         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA1 Channel 4 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA1CH5                 (LL_C2_SYSCFG_GRP2_DMA1CH5         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA1 Channel 5 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA1CH6                 (LL_C2_SYSCFG_GRP2_DMA1CH6         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA1 Channel 6 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA1CH7                 (LL_C2_SYSCFG_GRP2_DMA1CH7         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA1 Channel 7 to CPU2             */

#define HAL_SYSCFG_GRP2_DMA2CH1                 (LL_C2_SYSCFG_GRP2_DMA2CH1         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA2 Channel 1 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA2CH2                 (LL_C2_SYSCFG_GRP2_DMA2CH2         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA2 Channel 2 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA2CH3                 (LL_C2_SYSCFG_GRP2_DMA2CH3         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA2 Channel 3 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA2CH4                 (LL_C2_SYSCFG_GRP2_DMA2CH4         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA2 Channel 4 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA2CH5                 (LL_C2_SYSCFG_GRP2_DMA2CH5         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA2 Channel 5 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA2CH6                 (LL_C2_SYSCFG_GRP2_DMA2CH6         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA2 Channel 6 to CPU2             */
#define HAL_SYSCFG_GRP2_DMA2CH7                 (LL_C2_SYSCFG_GRP2_DMA2CH7         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMA2 Channel 7 to CPU2             */

#define HAL_SYSCFG_GRP2_DMAMUX1                 (LL_C2_SYSCFG_GRP2_DMAMUX1         | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from DMAMUX1 to CPU2                    */

#define HAL_SYSCFG_GRP2_PVM3                    (LL_C2_SYSCFG_GRP2_PVM3            | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from Power Voltage Monitoring 3 to CPU2 */
#define HAL_SYSCFG_GRP2_PVD                     (LL_C2_SYSCFG_GRP2_PVD             | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from Power Voltage Detector to CPU2     */

#else

/** @brief  Interrupt mask related to CPU1 NVIC
  */
#define HAL_SYSCFG_GRP2_PVM3                    (LL_SYSCFG_GRP2_PVM3               | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from Power Voltage Monitoring 3 to CPU1 */
#define HAL_SYSCFG_GRP2_PVD                     (LL_SYSCFG_GRP2_PVD                | HAL_SYSCFG_GRP2_RESERVED) /*!< Enabling of interrupt from Power Voltage Detector to CPU1     */

#endif
/**
  * @}
  */
#endif /* DUAL_CORE */

/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup HAL_Exported_Macros HAL Exported Macros
  * @{
  */

/** @defgroup DBGMCU_Exported_Macros DBGMCU Exported Macros
  * @{
  */

/** @brief  Freeze and Unfreeze Peripherals in Debug mode
  */

/** @defgroup DBGMCU_APBx_GRPx_STOP_IP DBGMCU CPU1 APBx GRPx STOP IP
  * @{
  */
#if defined(LL_DBGMCU_APB1_GRP1_TIM2_STOP)
#define __HAL_DBGMCU_FREEZE_TIM2()              LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_TIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM2()            LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_TIM2_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP1_RTC_STOP)
#define __HAL_DBGMCU_FREEZE_RTC()               LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_RTC_STOP)
#define __HAL_DBGMCU_UNFREEZE_RTC()             LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_RTC_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP1_WWDG_STOP)
#define __HAL_DBGMCU_FREEZE_WWDG()              LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_WWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_WWDG()            LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_WWDG_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP1_IWDG_STOP)
#define __HAL_DBGMCU_FREEZE_IWDG()              LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_IWDG_STOP)
#define __HAL_DBGMCU_UNFREEZE_IWDG()            LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_IWDG_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP1_I2C1_STOP)
#define __HAL_DBGMCU_FREEZE_I2C1_TIMEOUT()      LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_I2C1_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C1_TIMEOUT()    LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_I2C1_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP1_I2C2_STOP)
#define __HAL_DBGMCU_FREEZE_I2C2_TIMEOUT()      LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_I2C2_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C2_TIMEOUT()    LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_I2C2_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP1_I2C3_STOP)
#define __HAL_DBGMCU_FREEZE_I2C3_TIMEOUT()      LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_I2C3_STOP)
#define __HAL_DBGMCU_UNFREEZE_I2C3_TIMEOUT()    LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_I2C3_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP1_LPTIM1_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM1()            LL_DBGMCU_APB1_GRP1_FreezePeriph(LL_DBGMCU_APB1_GRP1_LPTIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM1()          LL_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_DBGMCU_APB1_GRP1_LPTIM1_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP2_LPTIM2_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM2()            LL_DBGMCU_APB1_GRP2_FreezePeriph(LL_DBGMCU_APB1_GRP2_LPTIM2_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM2()          LL_DBGMCU_APB1_GRP2_UnFreezePeriph(LL_DBGMCU_APB1_GRP2_LPTIM2_STOP)
#endif

#if defined(LL_DBGMCU_APB1_GRP2_LPTIM3_STOP)
#define __HAL_DBGMCU_FREEZE_LPTIM3()            LL_DBGMCU_APB1_GRP2_FreezePeriph(LL_DBGMCU_APB1_GRP2_LPTIM3_STOP)
#define __HAL_DBGMCU_UNFREEZE_LPTIM3()          LL_DBGMCU_APB1_GRP2_UnFreezePeriph(LL_DBGMCU_APB1_GRP2_LPTIM3_STOP)
#endif

#if defined(LL_DBGMCU_APB2_GRP1_TIM1_STOP)
#define __HAL_DBGMCU_FREEZE_TIM1()              LL_DBGMCU_APB2_GRP1_FreezePeriph(LL_DBGMCU_APB2_GRP1_TIM1_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM1()            LL_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_DBGMCU_APB2_GRP1_TIM1_STOP)
#endif

#if defined(LL_DBGMCU_APB2_GRP1_TIM16_STOP)
#define __HAL_DBGMCU_FREEZE_TIM16()             LL_DBGMCU_APB2_GRP1_FreezePeriph(LL_DBGMCU_APB2_GRP1_TIM16_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM16()           LL_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_DBGMCU_APB2_GRP1_TIM16_STOP)
#endif

#if defined(LL_DBGMCU_APB2_GRP1_TIM17_STOP)
#define __HAL_DBGMCU_FREEZE_TIM17()             LL_DBGMCU_APB2_GRP1_FreezePeriph(LL_DBGMCU_APB2_GRP1_TIM17_STOP)
#define __HAL_DBGMCU_UNFREEZE_TIM17()           LL_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_DBGMCU_APB2_GRP1_TIM17_STOP)
#endif

/**
  * @}
  */

/** @defgroup DBGMCU_C2_APBx_GRPx_STOP_IP DBGMCU CPU2 APBx GRPx STOP IP
  * @{
  */
#if defined(LL_C2_DBGMCU_APB1_GRP1_TIM2_STOP)
#define __HAL_C2_DBGMCU_FREEZE_TIM2()           LL_C2_DBGMCU_APB1_GRP1_FreezePeriph(LL_C2_DBGMCU_APB1_GRP1_TIM2_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_TIM2()         LL_C2_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB1_GRP1_TIM2_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB1_GRP1_RTC_STOP)
#define __HAL_C2_DBGMCU_FREEZE_RTC()            LL_C2_DBGMCU_APB1_GRP1_FreezePeriph(LL_C2_DBGMCU_APB1_GRP1_RTC_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_RTC()          LL_C2_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB1_GRP1_RTC_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB1_GRP1_IWDG_STOP)
#define __HAL_C2_DBGMCU_FREEZE_IWDG()           LL_C2_DBGMCU_APB1_GRP1_FreezePeriph(LL_C2_DBGMCU_APB1_GRP1_IWDG_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_IWDG()         LL_C2_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB1_GRP1_IWDG_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB1_GRP1_I2C1_STOP)
#define __HAL_C2_DBGMCU_FREEZE_I2C1_TIMEOUT()   LL_C2_DBGMCU_APB1_GRP1_FreezePeriph(LL_C2_DBGMCU_APB1_GRP1_I2C1_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_I2C1_TIMEOUT() LL_C2_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB1_GRP1_I2C1_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB1_GRP1_I2C2_STOP)
#define __HAL_C2_DBGMCU_FREEZE_I2C2_TIMEOUT()   LL_C2_DBGMCU_APB1_GRP1_FreezePeriph(LL_C2_DBGMCU_APB1_GRP1_I2C2_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_I2C2_TIMEOUT() LL_C2_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB1_GRP1_I2C2_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB1_GRP1_I2C3_STOP)
#define __HAL_C2_DBGMCU_FREEZE_I2C3_TIMEOUT()   LL_C2_DBGMCU_APB1_GRP1_FreezePeriph(LL_C2_DBGMCU_APB1_GRP1_I2C3_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_I2C3_TIMEOUT() LL_C2_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB1_GRP1_I2C3_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB1_GRP1_LPTIM1_STOP)
#define __HAL_C2_DBGMCU_FREEZE_LPTIM1()         LL_C2_DBGMCU_APB1_GRP1_FreezePeriph(LL_C2_DBGMCU_APB1_GRP1_LPTIM1_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_LPTIM1()       LL_C2_DBGMCU_APB1_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB1_GRP1_LPTIM1_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB1_GRP2_LPTIM2_STOP)
#define __HAL_C2_DBGMCU_FREEZE_LPTIM2()         LL_C2_DBGMCU_APB1_GRP2_FreezePeriph(LL_C2_DBGMCU_APB1_GRP2_LPTIM2_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_LPTIM2()       LL_C2_DBGMCU_APB1_GRP2_UnFreezePeriph(LL_C2_DBGMCU_APB1_GRP2_LPTIM2_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB1_GRP2_LPTIM3_STOP)
#define __HAL_C2_DBGMCU_FREEZE_LPTIM3()         LL_C2_DBGMCU_APB1_GRP2_FreezePeriph(LL_C2_DBGMCU_APB1_GRP2_LPTIM3_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_LPTIM3()       LL_C2_DBGMCU_APB1_GRP2_UnFreezePeriph(LL_C2_DBGMCU_APB1_GRP2_LPTIM3_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB2_GRP1_TIM1_STOP)
#define __HAL_C2_DBGMCU_FREEZE_TIM1()           LL_C2_DBGMCU_APB2_GRP1_FreezePeriph(LL_C2_DBGMCU_APB2_GRP1_TIM1_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_TIM1()         LL_C2_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB2_GRP1_TIM1_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB2_GRP1_TIM16_STOP)
#define __HAL_C2_DBGMCU_FREEZE_TIM16()          LL_C2_DBGMCU_APB2_GRP1_FreezePeriph(LL_C2_DBGMCU_APB2_GRP1_TIM16_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_TIM16()        LL_C2_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB2_GRP1_TIM16_STOP)
#endif

#if defined(LL_C2_DBGMCU_APB2_GRP1_TIM17_STOP)
#define __HAL_C2_DBGMCU_FREEZE_TIM17()          LL_C2_DBGMCU_APB2_GRP1_FreezePeriph(LL_C2_DBGMCU_APB2_GRP1_TIM17_STOP)
#define __HAL_C2_DBGMCU_UNFREEZE_TIM17()        LL_C2_DBGMCU_APB2_GRP1_UnFreezePeriph(LL_C2_DBGMCU_APB2_GRP1_TIM17_STOP)
#endif

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup SYSCFG_Exported_Macros SYSCFG Exported Macros
  * @{
  */

/** @brief  Main Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_FLASH()        LL_SYSCFG_SetRemapMemory(LL_SYSCFG_REMAP_FLASH)

/** @brief  System Flash memory mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_SYSTEMFLASH()  LL_SYSCFG_SetRemapMemory(LL_SYSCFG_REMAP_SYSTEMFLASH)

/** @brief  Embedded SRAM mapped at 0x00000000
  */
#define __HAL_SYSCFG_REMAPMEMORY_SRAM()         LL_SYSCFG_SetRemapMemory(LL_SYSCFG_REMAP_SRAM)

/**
  * @brief  Return the boot mode as configured by user.
  * @retval The boot mode as configured by user. The returned value can be one
  *         of the following values:
  *           @arg @ref SYSCFG_BOOT_MAINFLASH
  *           @arg @ref SYSCFG_BOOT_SYSTEMFLASH
  *           @arg @ref SYSCFG_BOOT_SRAM
  */
#define __HAL_SYSCFG_GET_BOOT_MODE()            LL_SYSCFG_GetRemapMemory()

/** @brief  SRAM2 page 0 to 31 write protection enable macro
  * @param  __SRAM2WRP__  This parameter can be a combination of values of @ref SYSCFG_SRAM2WRP
  * @note   Write protection can only be disabled by a system reset
  */
/* Legacy define */
#define __HAL_SYSCFG_SRAM2_WRP_1_31_ENABLE      __HAL_SYSCFG_SRAM2_WRP_0_31_ENABLE
#define __HAL_SYSCFG_SRAM2_WRP_0_31_ENABLE(__SRAM2WRP__)    do {assert_param(IS_SYSCFG_SRAM2WRP_PAGE((__SRAM2WRP__)));\
                                                                LL_SYSCFG_EnableSRAM2PageWRP_0_31(__SRAM2WRP__);\
                                                            }while(0)

/** @brief  SRAM2 page write protection unlock prior to erase
  * @note   Writing a wrong key reactivates the write protection
  */
#define __HAL_SYSCFG_SRAM2_WRP_UNLOCK()         LL_SYSCFG_UnlockSRAM2WRP()

/** @brief  SRAM2 erase
  * @note   __SYSCFG_GET_FLAG(SYSCFG_FLAG_SRAM_BUSY) may be used to check end of erase
  */
#define __HAL_SYSCFG_SRAM2_ERASE()              LL_SYSCFG_EnableSRAM2Erase()

/** @brief  SYSCFG Break ECC lock.
  *         Enable and lock the connection of Flash ECC error connection to TIM1/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_ECC_LOCK()           LL_SYSCFG_SetTIMBreakInputs(LL_SYSCFG_TIMBREAK_ECC)

/** @brief  SYSCFG Break Cortex-M4 Lockup lock.
  *         Enable and lock the connection of Cortex-M4 LOCKUP (Hardfault) output to TIM1/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_LOCKUP_LOCK()        LL_SYSCFG_SetTIMBreakInputs(LL_SYSCFG_TIMBREAK_LOCKUP)

/** @brief  SYSCFG Break PVD lock.
  *         Enable and lock the PVD connection to Timer1/16/17 Break input, as well as the PVDE and PLS[2:0] in the PWR_CR2 register.
  * @note   The selected configuration is locked and can be unlocked only by system reset.
  */
#define __HAL_SYSCFG_BREAK_PVD_LOCK()           LL_SYSCFG_SetTIMBreakInputs(LL_SYSCFG_TIMBREAK_PVD)

/** @brief  SYSCFG Break SRAM2 parity lock.
  *         Enable and lock the SRAM2 parity error signal connection to TIM1/16/17 Break input.
  * @note   The selected configuration is locked and can be unlocked by system reset.
  */
#define __HAL_SYSCFG_BREAK_SRAM2PARITY_LOCK()   LL_SYSCFG_SetTIMBreakInputs(LL_SYSCFG_TIMBREAK_SRAM2_PARITY)

/** @brief  Check SYSCFG flag is set or not.
  * @param  __FLAG__  specifies the flag to check.
  *         This parameter can be one of the following values:
  *            @arg @ref SYSCFG_FLAG_SRAM2_PE      SRAM2 Parity Error Flag
  *            @arg @ref SYSCFG_FLAG_SRAM_BUSY     SRAM2 Erase Ongoing
  *            @arg @ref SYSCFG_FLAG_PKASRAM_BUSY  PKA SRAM Erase Ongoing
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_SYSCFG_GET_FLAG(__FLAG__)         ((((((__FLAG__) == SYSCFG_FLAG_SRAM2_PE)? SYSCFG->CFGR2 : SYSCFG->SCSR) & (__FLAG__))!= 0) ? 1 : 0)

/** @brief  Set the SPF bit to clear the SRAM Parity Error Flag.
  */
#define __HAL_SYSCFG_CLEAR_FLAG()               LL_SYSCFG_ClearFlag_SP()

/** @brief  Fast mode Plus driving capability enable/disable macros
  * @param __FASTMODEPLUS__ This parameter can be a value of @ref SYSCFG_FastModePlus_GPIO
  */
#define __HAL_SYSCFG_FASTMODEPLUS_ENABLE(__FASTMODEPLUS__)  do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__))); \
                                                                LL_SYSCFG_EnableFastModePlus(__FASTMODEPLUS__);           \
                                                               }while(0)

#define __HAL_SYSCFG_FASTMODEPLUS_DISABLE(__FASTMODEPLUS__) do {assert_param(IS_SYSCFG_FASTMODEPLUS((__FASTMODEPLUS__))); \
                                                                LL_SYSCFG_DisableFastModePlus(__FASTMODEPLUS__);          \
                                                               }while(0)

/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */

/** @defgroup SYSCFG_Private_Macros SYSCFG Private Macros
  * @{
  */

#define IS_SYSCFG_SRAM2WRP_PAGE(__PAGE__)               (((__PAGE__) > 0U) && ((__PAGE__) <= 0xFFFFFFFFU))

#define IS_SYSCFG_VREFBUF_VOLTAGE_SCALE(__SCALE__)      (((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE0) || \
                                                         ((__SCALE__) == SYSCFG_VREFBUF_VOLTAGE_SCALE1))

#define IS_SYSCFG_VREFBUF_HIGH_IMPEDANCE(__VALUE__)     (((__VALUE__) == SYSCFG_VREFBUF_HIGH_IMPEDANCE_DISABLE) || \
                                                         ((__VALUE__) == SYSCFG_VREFBUF_HIGH_IMPEDANCE_ENABLE))

#define IS_SYSCFG_VREFBUF_TRIMMING(__VALUE__)           (((__VALUE__) > 0U) && ((__VALUE__) <= VREFBUF_CCR_TRIM))

#define IS_SYSCFG_FASTMODEPLUS(__PIN__)                 ((((__PIN__) & SYSCFG_FASTMODEPLUS_PB6)  == SYSCFG_FASTMODEPLUS_PB6)  || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB7)  == SYSCFG_FASTMODEPLUS_PB7)  || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB8)  == SYSCFG_FASTMODEPLUS_PB8)  || \
                                                         (((__PIN__) & SYSCFG_FASTMODEPLUS_PB9)  == SYSCFG_FASTMODEPLUS_PB9))


#if defined(DUAL_CORE)
#if defined(CORE_CM0PLUS)
#define IS_SYSCFG_IM_GRP1(__VALUE__)                    ((((__VALUE__) & 0x80U) == HAL_SYSCFG_GRP1_RESERVED)                                                     && \
                                                        ((((__VALUE__) & HAL_SYSCFG_GRP1_RTCSTAMP_RTCTAMP_LSECSS)  == HAL_SYSCFG_GRP1_RTCSTAMP_RTCTAMP_LSECSS)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_RTCALARM               )  == HAL_SYSCFG_GRP1_RTCALARM               )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_RTCSSRU                )  == HAL_SYSCFG_GRP1_RTCSSRU                )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_RTCWKUP                )  == HAL_SYSCFG_GRP1_RTCWKUP                )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_RCC                    )  == HAL_SYSCFG_GRP1_RCC                    )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_FLASH                  )  == HAL_SYSCFG_GRP1_FLASH                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_PKA                    )  == HAL_SYSCFG_GRP1_PKA                    )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_AES                    )  == HAL_SYSCFG_GRP1_AES                    )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_COMP                   )  == HAL_SYSCFG_GRP1_COMP                   )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_ADC                    )  == HAL_SYSCFG_GRP1_ADC                    )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_DAC                    )  == HAL_SYSCFG_GRP1_DAC                    )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI0                  )  == HAL_SYSCFG_GRP1_EXTI0                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI1                  )  == HAL_SYSCFG_GRP1_EXTI1                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI2                  )  == HAL_SYSCFG_GRP1_EXTI2                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI3                  )  == HAL_SYSCFG_GRP1_EXTI3                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI4                  )  == HAL_SYSCFG_GRP1_EXTI4                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI5                  )  == HAL_SYSCFG_GRP1_EXTI5                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI6                  )  == HAL_SYSCFG_GRP1_EXTI6                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI7                  )  == HAL_SYSCFG_GRP1_EXTI7                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI8                  )  == HAL_SYSCFG_GRP1_EXTI8                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI9                  )  == HAL_SYSCFG_GRP1_EXTI9                  )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI10                 )  == HAL_SYSCFG_GRP1_EXTI10                 )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI11                 )  == HAL_SYSCFG_GRP1_EXTI11                 )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI12                 )  == HAL_SYSCFG_GRP1_EXTI12                 )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI13                 )  == HAL_SYSCFG_GRP1_EXTI13                 )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI14                 )  == HAL_SYSCFG_GRP1_EXTI14                 )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI15                 )  == HAL_SYSCFG_GRP1_EXTI15                 )))

#define IS_SYSCFG_IM_GRP2(__VALUE__)                    ((((__VALUE__) & 0x80U) == HAL_SYSCFG_GRP2_RESERVED)                    && \
                                                        ((((__VALUE__) & HAL_SYSCFG_GRP2_DMA1CH1)  == HAL_SYSCFG_GRP2_DMA1CH1)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA1CH2)  == HAL_SYSCFG_GRP2_DMA1CH2)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA1CH3)  == HAL_SYSCFG_GRP2_DMA1CH3)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA1CH4)  == HAL_SYSCFG_GRP2_DMA1CH4)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA1CH5)  == HAL_SYSCFG_GRP2_DMA1CH5)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA1CH6)  == HAL_SYSCFG_GRP2_DMA1CH6)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA1CH7)  == HAL_SYSCFG_GRP2_DMA1CH7)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA2CH1)  == HAL_SYSCFG_GRP2_DMA2CH1)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA2CH2)  == HAL_SYSCFG_GRP2_DMA2CH2)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA2CH3)  == HAL_SYSCFG_GRP2_DMA2CH3)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA2CH4)  == HAL_SYSCFG_GRP2_DMA2CH4)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA2CH5)  == HAL_SYSCFG_GRP2_DMA2CH5)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA2CH6)  == HAL_SYSCFG_GRP2_DMA2CH6)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMA2CH7)  == HAL_SYSCFG_GRP2_DMA2CH7)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_DMAMUX1)  == HAL_SYSCFG_GRP2_DMAMUX1)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_PVM3   )  == HAL_SYSCFG_GRP2_PVM3   )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_PVD    )  == HAL_SYSCFG_GRP2_PVD    )))

#else /* !CORE_CM0PLUS */

#define IS_SYSCFG_IM_GRP1(__VALUE__)                    ((((__VALUE__) & 0x80U) == HAL_SYSCFG_GRP1_RESERVED)                                          && \
                                                        ((((__VALUE__) & HAL_SYSCFG_GRP1_RTCSTAMPTAMPLSECSS)  == HAL_SYSCFG_GRP1_RTCSTAMPTAMPLSECSS)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_RTCSSRU           )  == HAL_SYSCFG_GRP1_RTCSSRU           )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI5             )  == HAL_SYSCFG_GRP1_EXTI5             )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI6             )  == HAL_SYSCFG_GRP1_EXTI6             )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI7             )  == HAL_SYSCFG_GRP1_EXTI7             )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI8             )  == HAL_SYSCFG_GRP1_EXTI8             )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI9             )  == HAL_SYSCFG_GRP1_EXTI9             )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI10            )  == HAL_SYSCFG_GRP1_EXTI10            )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI11            )  == HAL_SYSCFG_GRP1_EXTI11            )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI12            )  == HAL_SYSCFG_GRP1_EXTI12            )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI13            )  == HAL_SYSCFG_GRP1_EXTI13            )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI14            )  == HAL_SYSCFG_GRP1_EXTI14            )  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP1_EXTI15            )  == HAL_SYSCFG_GRP1_EXTI15            )))

#define IS_SYSCFG_IM_GRP2(__VALUE__)                    ((((__VALUE__) & 0x80U) == HAL_SYSCFG_GRP2_RESERVED)              && \
                                                        ((((__VALUE__) & HAL_SYSCFG_GRP2_PVM3)  == HAL_SYSCFG_GRP2_PVM3)  || \
                                                         (((__VALUE__) & HAL_SYSCFG_GRP2_PVD )  == HAL_SYSCFG_GRP2_PVD )))

#endif /* CORE_CM0PLUS */
#endif /* DUAL_CORE */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup HAL_Private_Macros HAL Private Macros
  * @{
  */
#define IS_TICKFREQ(FREQ) (((FREQ) == HAL_TICK_FREQ_10HZ)  || \
                           ((FREQ) == HAL_TICK_FREQ_100HZ) || \
                           ((FREQ) == HAL_TICK_FREQ_1KHZ))
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/

/** @defgroup HAL_Exported_Functions HAL Exported Functions
  * @{
  */

/** @defgroup HAL_Exported_Functions_Group1 HAL Initialization and Configuration functions
  * @{
  */

/* Initialization and Configuration functions  ******************************/
HAL_StatusTypeDef HAL_Init(void);
HAL_StatusTypeDef HAL_DeInit(void);
void HAL_MspInit(void);
void HAL_MspDeInit(void);

HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority);

/**
  * @}
  */

/* Exported variables ---------------------------------------------------------*/
/** @addtogroup HAL_Exported_Variables
  * @{
  */
extern __IO uint32_t uwTick;
extern uint32_t uwTickPrio;
extern HAL_TickFreqTypeDef uwTickFreq;
/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group2 HAL Control functions
  * @{
  */

/* Peripheral Control functions  ************************************************/
void HAL_IncTick(void);
void HAL_Delay(uint32_t Delay);
uint32_t HAL_GetTick(void);
uint32_t HAL_GetTickPrio(void);
HAL_StatusTypeDef HAL_SetTickFreq(HAL_TickFreqTypeDef Freq);
HAL_TickFreqTypeDef HAL_GetTickFreq(void);
void HAL_SuspendTick(void);
void HAL_ResumeTick(void);
uint32_t HAL_GetHalVersion(void);
uint32_t HAL_GetREVID(void);
uint32_t HAL_GetDEVID(void);
uint32_t HAL_GetUIDw0(void);
uint32_t HAL_GetUIDw1(void);
uint32_t HAL_GetUIDw2(void);

/**
  * @}
  */

/** @defgroup HAL_Exported_Functions_Group3 HAL Debug functions
  * @{
  */

/* DBGMCU Peripheral Control functions  *****************************************/
void HAL_DBGMCU_EnableDBGSleepMode(void);
void HAL_DBGMCU_DisableDBGSleepMode(void);
void HAL_DBGMCU_EnableDBGStopMode(void);
void HAL_DBGMCU_DisableDBGStopMode(void);
void HAL_DBGMCU_EnableDBGStandbyMode(void);
void HAL_DBGMCU_DisableDBGStandbyMode(void);
/**
  * @}
  */

/** @addtogroup HAL_Exported_Functions_Group4 HAL System Configuration functions
  * @{
  */

/* SYSCFG Control functions  ****************************************************/
void HAL_SYSCFG_SRAM2Erase(void);

void HAL_SYSCFG_VREFBUF_VoltageScalingConfig(uint32_t VoltageScaling);
void HAL_SYSCFG_VREFBUF_HighImpedanceConfig(uint32_t Mode);
void HAL_SYSCFG_VREFBUF_TrimmingConfig(uint32_t TrimmingValue);
HAL_StatusTypeDef HAL_SYSCFG_EnableVREFBUF(void);
void HAL_SYSCFG_DisableVREFBUF(void);

void HAL_SYSCFG_EnableIOAnalogSwitchBooster(void);
void HAL_SYSCFG_DisableIOAnalogSwitchBooster(void);

#if defined(DUAL_CORE)
void HAL_SYSCFG_EnableIT(SYSCFG_InterruptTypeDef *Interrupt);
void HAL_SYSCFG_DisableIT(SYSCFG_InterruptTypeDef *Interrupt);
#endif
/**
  * @}
  */

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

#endif /* __STM32WLxx_HAL_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
