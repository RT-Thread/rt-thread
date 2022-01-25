/**
  ******************************************************************************
  * @file    stm32l5xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32L5xx_HAL_PWR_EX_H
#define STM32L5xx_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal_def.h"

/** @addtogroup STM32L5xx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */


/* Exported types ------------------------------------------------------------*/

/** @defgroup PWREx_Exported_Types PWR Extended Exported Types
  * @{
  */


/**
  * @brief  PWR PVM configuration structure definition
  */
typedef struct
{
  uint32_t PVMType;   /*!< PVMType: Specifies which voltage is monitored and against which threshold.
                           This parameter can be a value of @ref PWREx_PVM_Type.
                           @arg @ref PWR_PVM_1 Peripheral Voltage Monitoring 1 enable: VDDUSB versus 1.2 V (applicable when USB feature is supported).
                           @arg @ref PWR_PVM_2 Peripheral Voltage Monitoring 2 enable: VDDIO2 versus 0.9 V (applicable when VDDIO2 is present on device).
                           @arg @ref PWR_PVM_3 Peripheral Voltage Monitoring 3 enable: VDDA versus 1.62 V.
                           @arg @ref PWR_PVM_4 Peripheral Voltage Monitoring 4 enable: VDDA versus 1.8 V. */

  uint32_t Mode;      /*!< Mode: Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref PWREx_PVM_Mode. */
} PWR_PVMTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants  PWR Extended Exported Constants
  * @{
  */

/** @defgroup PWREx_WUP_Polarity Shift to apply to retrieve polarity information from PWR_WAKEUP_PINy_xxx constants
  * @{
  */
#define PWR_WUP_POLARITY_SHIFT                  0x05   /*!< Internal constant used to retrieve wakeup pin polariry */
/**
  * @}
  */


/** @defgroup PWREx_WakeUp_Pins  PWR wake-up pins
  * @{
  */
#define PWR_WAKEUP_PIN1                 PWR_CR3_EWUP1  /*!< Wakeup pin 1 (with high level polarity) */
#define PWR_WAKEUP_PIN2                 PWR_CR3_EWUP2  /*!< Wakeup pin 2 (with high level polarity) */
#define PWR_WAKEUP_PIN3                 PWR_CR3_EWUP3  /*!< Wakeup pin 3 (with high level polarity) */
#define PWR_WAKEUP_PIN4                 PWR_CR3_EWUP4  /*!< Wakeup pin 4 (with high level polarity) */
#define PWR_WAKEUP_PIN5                 PWR_CR3_EWUP5  /*!< Wakeup pin 5 (with high level polarity) */
#define PWR_WAKEUP_PIN1_HIGH            PWR_CR3_EWUP1  /*!< Wakeup pin 1 (with high level polarity) */
#define PWR_WAKEUP_PIN2_HIGH            PWR_CR3_EWUP2  /*!< Wakeup pin 2 (with high level polarity) */
#define PWR_WAKEUP_PIN3_HIGH            PWR_CR3_EWUP3  /*!< Wakeup pin 3 (with high level polarity) */
#define PWR_WAKEUP_PIN4_HIGH            PWR_CR3_EWUP4  /*!< Wakeup pin 4 (with high level polarity) */
#define PWR_WAKEUP_PIN5_HIGH            PWR_CR3_EWUP5  /*!< Wakeup pin 5 (with high level polarity) */
#define PWR_WAKEUP_PIN1_LOW             (uint32_t)((PWR_CR4_WUPP1<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP1) /*!< Wakeup pin 1 (with low level polarity) */
#define PWR_WAKEUP_PIN2_LOW             (uint32_t)((PWR_CR4_WUPP2<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP2) /*!< Wakeup pin 2 (with low level polarity) */
#define PWR_WAKEUP_PIN3_LOW             (uint32_t)((PWR_CR4_WUPP3<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP3) /*!< Wakeup pin 3 (with low level polarity) */
#define PWR_WAKEUP_PIN4_LOW             (uint32_t)((PWR_CR4_WUPP4<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP4) /*!< Wakeup pin 4 (with low level polarity) */
#define PWR_WAKEUP_PIN5_LOW             (uint32_t)((PWR_CR4_WUPP5<<PWR_WUP_POLARITY_SHIFT) | PWR_CR3_EWUP5) /*!< Wakeup pin 5 (with low level polarity) */
/**
  * @}
  */

/** @defgroup PWREx_PVM_Type Peripheral Voltage Monitoring type
  * @{
  */
#define PWR_PVM_1                  PWR_CR2_PVME1  /*!< Peripheral Voltage Monitoring 1 enable: VDDUSB versus 1.2 V (applicable when USB feature is supported) */
#define PWR_PVM_2                  PWR_CR2_PVME2  /*!< Peripheral Voltage Monitoring 2 enable: VDDIO2 versus 0.9 V */
#define PWR_PVM_3                  PWR_CR2_PVME3  /*!< Peripheral Voltage Monitoring 3 enable: VDDA versus 1.62 V */
#define PWR_PVM_4                  PWR_CR2_PVME4  /*!< Peripheral Voltage Monitoring 4 enable: VDDA versus 1.8 V  */
/**
  * @}
  */

/** @defgroup PWREx_PVM_Mode  PWR PVM interrupt and event mode
  * @{
  */
#define PWR_PVM_MODE_NORMAL                 ((uint32_t)0x00000000)   /*!< basic mode is used */
#define PWR_PVM_MODE_IT_RISING              ((uint32_t)0x00010001)   /*!< External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVM_MODE_IT_FALLING             ((uint32_t)0x00010002)   /*!< External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVM_MODE_IT_RISING_FALLING      ((uint32_t)0x00010003)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVM_MODE_EVENT_RISING           ((uint32_t)0x00020001)   /*!< Event Mode with Rising edge trigger detection */
#define PWR_PVM_MODE_EVENT_FALLING          ((uint32_t)0x00020002)   /*!< Event Mode with Falling edge trigger detection */
#define PWR_PVM_MODE_EVENT_RISING_FALLING   ((uint32_t)0x00020003)   /*!< Event Mode with Rising/Falling edge trigger detection */
/**
  * @}
  */



/** @defgroup PWREx_Regulator_Voltage_Scale  PWR Regulator voltage scale
  * @{
  */
#define PWR_REGULATOR_VOLTAGE_SCALE0       0U                /*!< Voltage scaling range 0 */
#define PWR_REGULATOR_VOLTAGE_SCALE1       PWR_CR1_VOS_0     /*!< Voltage scaling range 1 */
#define PWR_REGULATOR_VOLTAGE_SCALE2       PWR_CR1_VOS_1     /*!< Voltage scaling range 2 */
/**
  * @}
  */


/** @defgroup PWREx_SMPS_Mode  PWR SMPS step down converter mode
  * @{
  */
#define PWR_SMPS_HIGH_POWER                0U                 /*!< SMPS step down converter in high-power mode (default) */
#define PWR_SMPS_LOW_POWER                 PWR_CR4_SMPSLPEN   /*!< SMPS step down converter in low-power mode */
#define PWR_SMPS_BYPASS                    PWR_CR4_SMPSBYP    /*!< SMPS step down converter in bypass mode */
/**
  * @}
  */

/** @defgroup PWREx_EXT_SMPS_MAIN_REG_READY PWR SMPS main regulator ready for external SMPS
  * @{
  */
#define PWR_MAINREG_READY_FOR_EXTSMPS       PWR_SR1_EXTSMPSRDY  /*!< Main Regulator ready for use with external SMPS */
#define PWR_MAINREG_NOT_READY_FOR_EXTSMPS   0U                  /*!< Main Regulator not ready for use with external SMPS */
/**
  * @}
  */

/** @defgroup PWREx_VBAT_Battery_Charging_Selection PWR battery charging resistor selection
  * @{
  */
#define PWR_BATTERY_CHARGING_RESISTOR_5          ((uint32_t)0x00000000) /*!< VBAT charging through a 5 kOhms resistor   */
#define PWR_BATTERY_CHARGING_RESISTOR_1_5         PWR_CR4_VBRS          /*!< VBAT charging through a 1.5 kOhms resistor */
/**
  * @}
  */

/** @defgroup PWREx_VBAT_Battery_Charging PWR battery charging
  * @{
  */
#define PWR_BATTERY_CHARGING_DISABLE        ((uint32_t)0x00000000)
#define PWR_BATTERY_CHARGING_ENABLE         PWR_CR4_VBE
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Bit_Number GPIO bit number for I/O setting in standby/shutdown mode
  * @{
  */
#define PWR_GPIO_BIT_0   PWR_PUCRA_PU0    /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1   PWR_PUCRA_PU1    /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2   PWR_PUCRA_PU2    /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3   PWR_PUCRA_PU3    /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4   PWR_PUCRA_PU4    /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5   PWR_PUCRA_PU5    /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6   PWR_PUCRA_PU6    /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7   PWR_PUCRA_PU7    /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8   PWR_PUCRA_PU8    /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9   PWR_PUCRA_PU9    /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10  PWR_PUCRA_PU10   /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11  PWR_PUCRA_PU11   /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12  PWR_PUCRA_PU12   /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13  PWR_PUCRA_PU13   /*!< GPIO port I/O pin 13 */
#define PWR_GPIO_BIT_14  PWR_PUCRA_PU14   /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15  PWR_PUCRA_PU15   /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWREx_GPIO GPIO port
  * @{
  */
#define PWR_GPIO_A   0x00000000U      /*!< GPIO port A */
#define PWR_GPIO_B   0x00000001U      /*!< GPIO port B */
#define PWR_GPIO_C   0x00000002U      /*!< GPIO port C */
#define PWR_GPIO_D   0x00000003U      /*!< GPIO port D */
#define PWR_GPIO_E   0x00000004U      /*!< GPIO port E */
#define PWR_GPIO_F   0x00000005U      /*!< GPIO port F */
#define PWR_GPIO_G   0x00000006U      /*!< GPIO port G */
#define PWR_GPIO_H   0x00000007U      /*!< GPIO port H */
/**
  * @}
  */

/** @defgroup PWREx_PVM_EXTI_LINE PWR PVM external interrupts lines
  * @{
  */
#define PWR_EXTI_LINE_PVM1  ((uint32_t)0x00000008)  /*!< External interrupt line 35 Connected to the PVM1 EXTI Line   */
#define PWR_EXTI_LINE_PVM2  ((uint32_t)0x00000010)  /*!< External interrupt line 36 Connected to the PVM2 EXTI Line   */
#define PWR_EXTI_LINE_PVM3  ((uint32_t)0x00000020)  /*!< External interrupt line 37 Connected to the PVM3 EXTI Line   */
#define PWR_EXTI_LINE_PVM4  ((uint32_t)0x00000040)  /*!< External interrupt line 38 Connected to the PVM4 EXTI Line   */
/**
  * @}
  */

/** @defgroup PWREx_PVM_EVENT_LINE PWR PVM event lines
  * @{
  */
#define PWR_EVENT_LINE_PVM1 ((uint32_t)0x00000008)  /*!< Event line 35 Connected to the PVM1 EXTI Line */
#define PWR_EVENT_LINE_PVM2 ((uint32_t)0x00000010)  /*!< Event line 36 Connected to the PVM2 EXTI Line */
#define PWR_EVENT_LINE_PVM3 ((uint32_t)0x00000020)  /*!< Event line 37 Connected to the PVM3 EXTI Line */
#define PWR_EVENT_LINE_PVM4 ((uint32_t)0x00000040)  /*!< Event line 38 Connected to the PVM4 EXTI Line */
/**
  * @}
  */

/** @defgroup PWREx_Flag  PWR Status Flags
  *        Elements values convention: 0000 0000 0XXY YYYYb
  *           - Y YYYY  : Flag position in the XX register (5 bits)
  *           - XX  : Status register (2 bits)
  *                 - 01: SR1 register
  *                 - 10: SR2 register
  *        The only exception is PWR_FLAG_WU, encompassing all
  *        wake-up flags and set to PWR_SR1_WUF.
  * @{
  */
#define PWR_FLAG_WUF1                      ((uint32_t)0x0020)   /*!< Wakeup event on wakeup pin 1 */
#define PWR_FLAG_WUF2                      ((uint32_t)0x0021)   /*!< Wakeup event on wakeup pin 2 */
#define PWR_FLAG_WUF3                      ((uint32_t)0x0022)   /*!< Wakeup event on wakeup pin 3 */
#define PWR_FLAG_WUF4                      ((uint32_t)0x0023)   /*!< Wakeup event on wakeup pin 4 */
#define PWR_FLAG_WUF5                      ((uint32_t)0x0024)   /*!< Wakeup event on wakeup pin 5 */
#define PWR_FLAG_WU                        PWR_SR1_WUF          /*!< Encompass wakeup event on all wakeup pins */
#define PWR_FLAG_SB                        ((uint32_t)0x0028)   /*!< Standby flag */
#define PWR_FLAG_SMPS_BYPASS_RDY           ((uint32_t)0x002C)   /*!< SMPS bypass mode ready */
#define PWR_FLAG_EXT_SMPS_RDY              ((uint32_t)0x002D)   /*!< External SMPS mode ready */
#define PWR_FLAG_SMPS_HP_RDY               ((uint32_t)0x002E)   /*!< SMPS high-power mode ready */
#define PWR_FLAG_REGLPS                    ((uint32_t)0x0048)   /*!< Low-power regulator start flag */
#define PWR_FLAG_REGLPF                    ((uint32_t)0x0049)   /*!< Low-power regulator flag */
#define PWR_FLAG_VOSF                      ((uint32_t)0x004A)   /*!< Voltage scaling flag */
#define PWR_FLAG_PVDO                      ((uint32_t)0x004B)   /*!< Power Voltage Detector output flag */
#define PWR_FLAG_PVMO1                     ((uint32_t)0x004C)   /*!< Power Voltage Monitoring 1 output flag */
#define PWR_FLAG_PVMO2                     ((uint32_t)0x004D)   /*!< Power Voltage Monitoring 2 output flag */
#define PWR_FLAG_PVMO3                     ((uint32_t)0x004E)   /*!< Power Voltage Monitoring 3 output flag */
#define PWR_FLAG_PVMO4                     ((uint32_t)0x004F)   /*!< Power Voltage Monitoring 4 output flag */
/**
  * @}
  */

/** @defgroup PWREx_SecureMode PWREx Secure Mode
  * @note Only available when system implements security (TZEN=1)
  * @{
  */
#define PWR_SECURE_NONE                    0U                    /*!< No security on PWR resources (default) */
#define PWR_SECURE_ALL                     0x0F1FU               /*!< Security on all PWR resources          */

#define PWR_SECURE_WUP                     PWR_SECCFGR_WUPSEC    /*!< All Wakeup pins secure configuration */
#define PWR_SECURE_WUP1                    PWR_SECCFGR_WUP1SEC   /*!< Wakeup pin 1 secure configuration */
#define PWR_SECURE_WUP2                    PWR_SECCFGR_WUP2SEC   /*!< Wakeup pin 2 secure configuration */
#define PWR_SECURE_WUP3                    PWR_SECCFGR_WUP3SEC   /*!< Wakeup pin 3 secure configuration */
#define PWR_SECURE_WUP4                    PWR_SECCFGR_WUP4SEC   /*!< Wakeup pin 4 secure configuration */
#define PWR_SECURE_WUP5                    PWR_SECCFGR_WUP5SEC   /*!< Wakeup pin 5 secure configuration */
#define PWR_SECURE_LPM                     PWR_SECCFGR_LPMSEC    /*!< Low-power mode secure configuration */
#define PWR_SECURE_VDM                     PWR_SECCFGR_VDMSEC    /*!< Voltage Detection and Monitoring secure configuration */
#define PWR_SECURE_VB                      PWR_SECCFGR_VBSEC     /*!< VBAT mode secure configuration */
#define PWR_SECURE_APC                     PWR_SECCFGR_APCSEC    /*!< Pull-up/down Control secure configuration */
/**
  * @}
  */

/** @defgroup PWREx_SRAM2_Contents_Retention  PWR SRAM2 Content Retention
  * @{
  */
#define PWR_NO_SRAM2_RETENTION             0U                      /*!< SRAM2 is powered off in Standby mode (SRAM2 content is lost)*/
#define PWR_FULL_SRAM2_RETENTION           PWR_CR3_RRS_0           /*!< : Full SRAM2 is powered by the low-power regulator in Standby mode (SRAM2 content is kept) */
#define PWR_4KBYTES_SRAM2_RETENTION        PWR_CR3_RRS_1           /*!< Only 4kB of SRAM2 is powered by the low-power regulator in Standby mode (4kB of SRAM2 content is kept) */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup PWREx_Exported_Macros PWR Extended Exported Macros
 * @{
 */

/**
  * @brief Enable the PVM1 Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Disable the PVM1 Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Enable the PVM1 Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM1)

/**
  * @brief Disable the PVM1 Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM1)

/**
  * @brief Enable the PVM1 Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Disable the PVM1 Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Enable the PVM1 Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM1)


/**
  * @brief Disable the PVM1 Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM1)


/**
  * @brief  PVM1 EXTI line configuration: set rising & falling edge trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVM1_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVM1_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the PVM1 Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                     \
    __HAL_PWR_PVM1_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM1_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM1)

/**
  * @brief Check whether the specified PVM1 EXTI interrupt flag is set or not.
  * @retval EXTI PVM1 Line Status.
  */
#define __HAL_PWR_PVM1_EXTI_GET_FLAG()  ((EXTI->RPR2 | EXTI->FPR2) & PWR_EXTI_LINE_PVM1)

/**
  * @brief Clear the PVM1 EXTI flag.
  * @retval None
  */
#define __HAL_PWR_PVM1_EXTI_CLEAR_FLAG()                   \
    do {                                                   \
       WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM1);          \
       WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM1);          \
  } while(0)


/**
  * @brief Enable the PVM2 Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Disable the PVM2 Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Enable the PVM2 Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM2)

/**
  * @brief Disable the PVM2 Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM2)

/**
  * @brief Enable the PVM2 Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Disable the PVM2 Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Enable the PVM2 Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM2)


/**
  * @brief Disable the PVM2 Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM2)


/**
  * @brief  PVM2 EXTI line configuration: set rising & falling edge trigger.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVM2_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVM2_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the PVM2 Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                     \
    __HAL_PWR_PVM2_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM2_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM2)

/**
  * @brief Check whether the specified PVM2 EXTI interrupt flag is set or not.
  * @retval EXTI PVM2 Line Status.
  */
#define __HAL_PWR_PVM2_EXTI_GET_FLAG()  ((EXTI->RPR2 | EXTI->FPR2) & PWR_EXTI_LINE_PVM2)

/**
  * @brief Clear the PVM2 EXTI flag.
  * @retval None
  */
#define __HAL_PWR_PVM2_EXTI_CLEAR_FLAG()                   \
    do {                                                   \
       WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM2);          \
       WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM2);          \
  } while(0)


/**
  * @brief Enable the PVM3 Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Disable the PVM3 Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Enable the PVM3 Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM3)

/**
  * @brief Disable the PVM3 Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM3)

/**
  * @brief Enable the PVM3 Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Disable the PVM3 Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Enable the PVM3 Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM3)


/**
  * @brief Disable the PVM3 Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM3)


/**
  * @brief  PVM3 EXTI line configuration: set rising & falling edge trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVM3_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVM3_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the PVM3 Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                     \
    __HAL_PWR_PVM3_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM3_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM3)

/**
  * @brief Check whether the specified PVM3 EXTI interrupt flag is set or not.
  * @retval EXTI PVM3 Line Status.
  */
#define __HAL_PWR_PVM3_EXTI_GET_FLAG()  ((EXTI->RPR2 | EXTI->FPR2) & PWR_EXTI_LINE_PVM3)

/**
  * @brief Clear the PVM3 EXTI flag.
  * @retval None
  */
#define __HAL_PWR_PVM3_EXTI_CLEAR_FLAG()                   \
    do {                                                   \
       WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM3);          \
       WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM3);          \
  } while(0)



/**
  * @brief Enable the PVM4 Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_IT()   SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Disable the PVM4 Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_IT()  CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Enable the PVM4 Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_EVENT()   SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM4)

/**
  * @brief Disable the PVM4 Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_EVENT()  CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM4)

/**
  * @brief Enable the PVM4 Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Disable the PVM4 Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Enable the PVM4 Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_FALLING_EDGE()   SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM4)


/**
  * @brief Disable the PVM4 Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_FALLING_EDGE()  CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM4)


/**
  * @brief  PVM4 EXTI line configuration: set rising & falling edge trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVM4_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVM4_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the PVM4 Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                     \
    __HAL_PWR_PVM4_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM4_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM4)

/**
  * @brief Check whether or not the specified PVM4 EXTI interrupt flag is set.
  * @retval EXTI PVM4 Line Status.
  */
#define __HAL_PWR_PVM4_EXTI_GET_FLAG()  ((EXTI->RPR2 | EXTI->FPR2) & PWR_EXTI_LINE_PVM4)

/**
  * @brief Clear the PVM4 EXTI flag.
  * @retval None
  */
#define __HAL_PWR_PVM4_EXTI_CLEAR_FLAG()                   \
    do {                                                   \
       WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM4);          \
       WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM4);          \
  } while(0)


/**
  * @brief Configure the main internal regulator output voltage.
  * @param  __REGULATOR__ specifies the regulator output voltage to achieve
  *         a tradeoff between performance and power consumption.
  *          This parameter can be one of the following values:
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE0  Regulator voltage output range 0 mode,
  *                                                typical output voltage at 1.28 V,
  *                                                system frequency up to 110 MHz.
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE1  Regulator voltage output range 1 mode,
  *                                                typical output voltage at 1.2 V,
  *                                                system frequency up to 80 MHz.
  *            @arg @ref PWR_REGULATOR_VOLTAGE_SCALE2  Regulator voltage output range 2 mode,
  *                                                typical output voltage at 1.0 V,
  *                                                system frequency up to 26 MHz.
  * @note  This macro is similar to HAL_PWREx_ControlVoltageScaling() API but doesn't check
  *        whether or not VOSF flag is cleared when moving from range 2 to range 1. User
  *        may resort to __HAL_PWR_GET_FLAG() macro to check VOSF bit resetting.
  * @retval None
  */
#define __HAL_PWR_VOLTAGESCALING_CONFIG(__REGULATOR__) do {                                                     \
                                                            __IO uint32_t tmpreg;                               \
                                                            MODIFY_REG(PWR->CR1, PWR_CR1_VOS, (__REGULATOR__)); \
                                                            /* Delay after an RCC peripheral clock enabling */  \
                                                            tmpreg = READ_BIT(PWR->CR1, PWR_CR1_VOS);           \
                                                            UNUSED(tmpreg);                                     \
                                                          } while(0)

/**
  * @}
  */

/* Private macros --------------------------------------------------------*/
/** @addtogroup  PWREx_Private_Macros   PWR Extended Private Macros
  * @{
  */

#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1) || \
                                ((PIN) == PWR_WAKEUP_PIN2) || \
                                ((PIN) == PWR_WAKEUP_PIN3) || \
                                ((PIN) == PWR_WAKEUP_PIN4) || \
                                ((PIN) == PWR_WAKEUP_PIN5) || \
                                ((PIN) == PWR_WAKEUP_PIN1_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN2_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN3_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN4_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN5_HIGH) || \
                                ((PIN) == PWR_WAKEUP_PIN1_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN2_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN3_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN4_LOW) || \
                                ((PIN) == PWR_WAKEUP_PIN5_LOW))

#define IS_PWR_PVM_TYPE(TYPE) (((TYPE) == PWR_PVM_1) ||\
                               ((TYPE) == PWR_PVM_2) ||\
                               ((TYPE) == PWR_PVM_3) ||\
                               ((TYPE) == PWR_PVM_4))

#define IS_PWR_PVM_MODE(MODE)  (((MODE) == PWR_PVM_MODE_NORMAL)              ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING)           ||\
                                ((MODE) == PWR_PVM_MODE_IT_FALLING)          ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING_FALLING)   ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING)        ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_FALLING)       ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING_FALLING))

#define IS_PWR_VOLTAGE_SCALING_RANGE(RANGE) (((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE0) || \
                                             ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE1) || \
                                             ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE2))

#define IS_PWR_BATTERY_RESISTOR_SELECT(RESISTOR) (((RESISTOR) == PWR_BATTERY_CHARGING_RESISTOR_5) ||\
                                                  ((RESISTOR) == PWR_BATTERY_CHARGING_RESISTOR_1_5))

#define IS_PWR_BATTERY_CHARGING(CHARGING) (((CHARGING) == PWR_BATTERY_CHARGING_DISABLE) ||\
                                           ((CHARGING) == PWR_BATTERY_CHARGING_ENABLE))

#define IS_PWR_GPIO_BIT_NUMBER(BIT_NUMBER) (((BIT_NUMBER) & GPIO_PIN_MASK) != (uint32_t)0x00)


#define IS_PWR_GPIO(GPIO) (((GPIO) == PWR_GPIO_A) ||\
                           ((GPIO) == PWR_GPIO_B) ||\
                           ((GPIO) == PWR_GPIO_C) ||\
                           ((GPIO) == PWR_GPIO_D) ||\
                           ((GPIO) == PWR_GPIO_E) ||\
                           ((GPIO) == PWR_GPIO_F) ||\
                           ((GPIO) == PWR_GPIO_G) ||\
                           ((GPIO) == PWR_GPIO_H))

#define IS_PWR_SRAM2CONTENT_RETENTION(CONTENT) (((CONTENT) == PWR_NO_SRAM2_RETENTION)   ||\
                                                ((CONTENT) == PWR_FULL_SRAM2_RETENTION) ||\
                                                ((CONTENT) == PWR_4KBYTES_SRAM2_RETENTION))

#define IS_PWR_SMPS_MODE(__MODE__) (((__MODE__) == PWR_SMPS_HIGH_POWER) || \
                                    ((__MODE__) == PWR_SMPS_LOW_POWER)  || \
                                    ((__MODE__) == PWR_SMPS_BYPASS))

#define IS_PWR_SECURE_CONFIG(__CONFIG__)   (((__CONFIG__) == PWR_SECURE_NONE) || \
                                            ((__CONFIG__) == PWR_SECURE_ALL)  || \
                                            (((__CONFIG__) & PWR_SECURE_WUP)  == PWR_SECURE_WUP) || \
                                            (((__CONFIG__) & PWR_SECURE_WUP1) == PWR_SECURE_WUP1) || \
                                            (((__CONFIG__) & PWR_SECURE_WUP2) == PWR_SECURE_WUP2) || \
                                            (((__CONFIG__) & PWR_SECURE_WUP3) == PWR_SECURE_WUP3) || \
                                            (((__CONFIG__) & PWR_SECURE_WUP4) == PWR_SECURE_WUP4) || \
                                            (((__CONFIG__) & PWR_SECURE_WUP5) == PWR_SECURE_WUP5) || \
                                            (((__CONFIG__) & PWR_SECURE_LPM)  == PWR_SECURE_LPM) || \
                                            (((__CONFIG__) & PWR_SECURE_VDM)  == PWR_SECURE_VDM) || \
                                            (((__CONFIG__) & PWR_SECURE_VB)   == PWR_SECURE_VB) || \
                                            (((__CONFIG__) & PWR_SECURE_APC)  == PWR_SECURE_APC))
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions PWR Extended Exported Functions
  * @{
  */

/** @addtogroup PWREx_Exported_Functions_Group1 Extended Peripheral Control functions
  * @{
  */


/* Peripheral Control functions  **********************************************/
uint32_t HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorSelection);
void HAL_PWREx_DisableBatteryCharging(void);
void HAL_PWREx_EnableVddUSB(void);
void HAL_PWREx_DisableVddUSB(void);
void HAL_PWREx_EnableVddIO2(void);
void HAL_PWREx_DisableVddIO2(void);
void HAL_PWREx_EnableInternalWakeUpLine(void);
void HAL_PWREx_DisableInternalWakeUpLine(void);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
void HAL_PWREx_EnablePullUpPullDownConfig(void);
void HAL_PWREx_DisablePullUpPullDownConfig(void);
void HAL_PWREx_EnablePVM1(void);
void HAL_PWREx_DisablePVM1(void);
void HAL_PWREx_EnablePVM2(void);
void HAL_PWREx_DisablePVM2(void);
void HAL_PWREx_EnablePVM3(void);
void HAL_PWREx_DisablePVM3(void);
void HAL_PWREx_EnablePVM4(void);
void HAL_PWREx_DisablePVM4(void);
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(PWR_PVMTypeDef *sConfigPVM);

/* Low Power modes configuration functions ************************************/
void HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);
void HAL_PWREx_EnableUltraLowPowerMode(void);
void HAL_PWREx_DisableUltraLowPowerMode(void);
void HAL_PWREx_EnterSTOP0Mode(uint8_t STOPEntry);
void HAL_PWREx_EnterSTOP1Mode(uint8_t STOPEntry);
void HAL_PWREx_EnterSTOP2Mode(uint8_t STOPEntry);
void HAL_PWREx_EnterSHUTDOWNMode(void);

void HAL_PWREx_PVD_PVM_IRQHandler(void);
void HAL_PWREx_PVM1Callback(void);
void HAL_PWREx_PVM2Callback(void);
void HAL_PWREx_PVM3Callback(void);
void HAL_PWREx_PVM4Callback(void);

HAL_StatusTypeDef HAL_PWREx_ConfigSRAM2ContentRetention(uint32_t SRAM2ContentRetention);
void HAL_PWREx_EnableSRAM2ContentRetention(void);
void HAL_PWREx_DisableSRAM2ContentRetention(void);

void HAL_PWREx_EnableUCPDStandbyMode(void);
void HAL_PWREx_DisableUCPDStandbyMode(void);
void HAL_PWREx_EnableUCPDDeadBattery(void);
void HAL_PWREx_DisableUCPDDeadBattery(void);

/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group2
  * @{
  */

HAL_StatusTypeDef HAL_PWREx_SMPS_SetMode(uint32_t OperatingMode);
uint32_t HAL_PWREx_SMPS_GetEffectiveMode(void);
uint32_t HAL_PWREx_SMPS_GetMainRegulatorExtSMPSReadyStatus(void);
void HAL_PWREx_SMPS_EnableFastStart(void);
void HAL_PWREx_SMPS_DisableFastStart(void);

void HAL_PWREx_SMPS_EnableExternal(void);
void HAL_PWREx_SMPS_DisableExternal(void);
void HAL_PWREx_SMPS_DisableBypassMode(void);
void HAL_PWREx_SMPS_EnableBypassMode(void);

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


#endif /* STM32L5xx_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
