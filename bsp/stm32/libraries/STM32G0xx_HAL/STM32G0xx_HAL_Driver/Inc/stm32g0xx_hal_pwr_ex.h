/**
  ******************************************************************************
  * @file    stm32g0xx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
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
#ifndef STM32G0xx_HAL_PWR_EX_H
#define STM32G0xx_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal_def.h"

/** @addtogroup STM32G0xx_HAL_Driver
  * @{
  */

/** @defgroup PWREx PWREx
  * @brief PWR Extended HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PWREx_Exported_Types PWR Extended Exported Types
  * @{
  */

#if defined(PWR_PVM_SUPPORT)
/**
  * @brief  PWR PVM configuration structure definition
  */
typedef struct
{
  uint32_t PVMType;   /*!< PVMType: Specifies which voltage is monitored and against which threshold.
                           This parameter can be a value of @ref PWREx_PVM_Type.
                           @arg @ref PWR_PVM_USB Peripheral Voltage Monitoring USB enable */

  uint32_t Mode;      /*!< Mode: Specifies the operating mode for the selected pins.
                           This parameter can be a value of @ref PWREx_PVM_Mode. */
} PWR_PVMTypeDef;
#endif /* PWR_PVM_SUPPORT */

#if defined(PWR_PVD_SUPPORT)
/**
  * @brief  PWR PVD configuration structure definition
  */
typedef struct
{
  uint32_t PVDLevel;    /*!< PVDLevel: Specifies the PVD detection level.
                              This parameter can be a value or a combination of
                              @ref PWR_PVD_detection_level. */

  uint32_t Mode;        /*!< Mode: Specifies the operating mode for the selected pins.
                              This parameter can be a value of @ref PWR_PVD_Mode. */
} PWR_PVDTypeDef;
#endif /* PWR_PVD_SUPPORT */

/**
  * @}
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Constants  PWR Extended Exported Constants
  * @{
  */
#if defined(PWR_PVD_SUPPORT)
/** @defgroup PWR_PVD_detection_level  Programmable Voltage Detection levels
  * @note   see datasheet for selection voltage value
  * @{
  */
#define PWR_PVDLEVEL_RISING_0               (0x00000000u)                                           /*!< PVD threshold level 0 for rising detection */
#define PWR_PVDLEVEL_RISING_1               (PWR_CR2_PVDRT_0)                                       /*!< PVD threshold level 1 for rising detection */
#define PWR_PVDLEVEL_RISING_2               (PWR_CR2_PVDRT_1)                                       /*!< PVD threshold level 2 for rising detection */
#define PWR_PVDLEVEL_RISING_3               (PWR_CR2_PVDRT_0 | PWR_CR2_PVDRT_1)                     /*!< PVD threshold level 3 for rising detection */
#define PWR_PVDLEVEL_RISING_4               (PWR_CR2_PVDRT_2)                                       /*!< PVD threshold level 4 for rising detection */
#define PWR_PVDLEVEL_RISING_5               (PWR_CR2_PVDRT_2 | PWR_CR2_PVDRT_0)                     /*!< PVD threshold level 5 for rising detection */
#define PWR_PVDLEVEL_RISING_6               (PWR_CR2_PVDRT_2 | PWR_CR2_PVDRT_1)                     /*!< PVD threshold level 6 for rising detection */
#define PWR_PVDLEVEL_FALLING_0              (0x00000000u)                                           /*!< PVD threshold level 0 for falling detection */
#define PWR_PVDLEVEL_FALLING_1              (PWR_CR2_PVDFT_0)                                       /*!< PVD threshold level 1 for falling detection */
#define PWR_PVDLEVEL_FALLING_2              (PWR_CR2_PVDFT_1)                                       /*!< PVD threshold level 2 for falling detection */
#define PWR_PVDLEVEL_FALLING_3              (PWR_CR2_PVDFT_0 | PWR_CR2_PVDFT_1)                     /*!< PVD threshold level 3 for falling detection */
#define PWR_PVDLEVEL_FALLING_4              (PWR_CR2_PVDFT_2)                                       /*!< PVD threshold level 4 for falling detection */
#define PWR_PVDLEVEL_FALLING_5              (PWR_CR2_PVDFT_2 | PWR_CR2_PVDFT_0)                     /*!< PVD threshold level 5 for falling detection */
#define PWR_PVDLEVEL_FALLING_6              (PWR_CR2_PVDFT_2 | PWR_CR2_PVDFT_1)                     /*!< PVD threshold level 6 for falling detection */
#define PWR_PVDLEVEL_0                      (PWR_PVDLEVEL_RISING_0 | PWR_PVDLEVEL_FALLING_0)        /*!< same PVD threshold level 0 on rising & falling */
#define PWR_PVDLEVEL_1                      (PWR_PVDLEVEL_RISING_1 | PWR_PVDLEVEL_FALLING_1)        /*!< same PVD threshold level 1 on rising & falling */
#define PWR_PVDLEVEL_2                      (PWR_PVDLEVEL_RISING_2 | PWR_PVDLEVEL_FALLING_2)        /*!< same PVD threshold level 2 on rising & falling */
#define PWR_PVDLEVEL_3                      (PWR_PVDLEVEL_RISING_3 | PWR_PVDLEVEL_FALLING_3)        /*!< same PVD threshold level 3 on rising & falling */
#define PWR_PVDLEVEL_4                      (PWR_PVDLEVEL_RISING_4 | PWR_PVDLEVEL_FALLING_4)        /*!< same PVD threshold level 4 on rising & falling */
#define PWR_PVDLEVEL_5                      (PWR_PVDLEVEL_RISING_5 | PWR_PVDLEVEL_FALLING_5)        /*!< same PVD threshold level 5 on rising & falling */
#define PWR_PVDLEVEL_6                      (PWR_PVDLEVEL_RISING_6 | PWR_PVDLEVEL_FALLING_6)        /*!< same PVD threshold level 6 on rising & falling */
#define PWR_PVDLEVEL_7                      (PWR_CR2_PVDRT_2 | PWR_CR2_PVDRT_1 | PWR_CR2_PVDRT_0)   /*!< External input analog voltage (compared internally to VREFINT) */
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode  PWR PVD interrupt and event mode
  * @{
  */
#define PWR_PVD_MODE_NORMAL                 (0x00000000u)  /*!< basic mode is used */
#define PWR_PVD_MODE_IT_RISING              (0x00010001u)  /*!< External Interrupt Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_IT_FALLING             (0x00010002u)  /*!< External Interrupt Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_IT_RISING_FALLING      (0x00010003u)  /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING           (0x00020001u)  /*!< Event Mode with Rising edge trigger detection */
#define PWR_PVD_MODE_EVENT_FALLING          (0x00020002u)  /*!< Event Mode with Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING_FALLING   (0x00020003u)  /*!< Event Mode with Rising/Falling edge trigger detection */
/**
  * @}
  */

/** @defgroup PWR_PVD_EXTI_LINE  PWR PVD external interrupt line
  * @{
  */
#define PWR_EXTI_LINE_PVD                   (EXTI_IMR1_IM16)  /*!< External interrupt line 16 connected to PVD */
/**
  * @}
  */

/** @defgroup PWR_PVD_EVENT_LINE  PWR PVD event line
  * @{
  */
#define PWR_EVENT_LINE_PVD                  (EXTI_EMR1_EM16)  /*!< Event line 16 connected to PVD */
/**
  * @}
  */
#endif /* PWR_PVD_SUPPORT */

#if defined(PWR_PVM_SUPPORT)
/** @defgroup PWREx_PVM_Type Peripheral Voltage Monitoring type
  * @{
  */
#define PWR_PVM_USB                  PWR_CR2_PVMEN_USB  /*!< Peripheral Voltage Monitoring enable for USB peripheral: Enable to keep the USB peripheral voltage monitoring under control (power domain Vddio2) */
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
/** @defgroup PWR_PVM_EXTI_LINE  PWR PVM external interrupt line
  * @{
  */
#define PWR_EXTI_LINE_PVM                   (EXTI_IMR2_IM34)  /*!< External interrupt line 34 connected to PVM */
/**
  * @}
  */

/** @defgroup PWR_PVM_EVENT_LINE  PWR PVM event line
  * @{
  */
#define PWR_EVENT_LINE_PVM                  (EXTI_EMR2_EM34)  /*!< Event line 34 connected to PVM */
/**
  * @}
  */
#endif /* PWR_PVM_SUPPORT */

/** @defgroup PWREx_VBAT_Battery_Charging_Selection  PWR battery charging resistor selection
  * @{
  */
#define PWR_BATTERY_CHARGING_RESISTOR_5     (0x00000000u)   /*!< VBAT charging through a 5 kOhms resistor   */
#define PWR_BATTERY_CHARGING_RESISTOR_1_5   PWR_CR4_VBRS    /*!< VBAT charging through a 1.5 kOhms resistor */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Bit_Number  GPIO bit position
  * @brief    for I/O pull up/down setting in standby/shutdown mode
  * @{
  */
#define PWR_GPIO_BIT_0                      PWR_PUCRB_PU0   /*!< GPIO port I/O pin 0  */
#define PWR_GPIO_BIT_1                      PWR_PUCRB_PU1   /*!< GPIO port I/O pin 1  */
#define PWR_GPIO_BIT_2                      PWR_PUCRB_PU2   /*!< GPIO port I/O pin 2  */
#define PWR_GPIO_BIT_3                      PWR_PUCRB_PU3   /*!< GPIO port I/O pin 3  */
#define PWR_GPIO_BIT_4                      PWR_PUCRB_PU4   /*!< GPIO port I/O pin 4  */
#define PWR_GPIO_BIT_5                      PWR_PUCRB_PU5   /*!< GPIO port I/O pin 5  */
#define PWR_GPIO_BIT_6                      PWR_PUCRB_PU6   /*!< GPIO port I/O pin 6  */
#define PWR_GPIO_BIT_7                      PWR_PUCRB_PU7   /*!< GPIO port I/O pin 7  */
#define PWR_GPIO_BIT_8                      PWR_PUCRB_PU8   /*!< GPIO port I/O pin 8  */
#define PWR_GPIO_BIT_9                      PWR_PUCRB_PU9   /*!< GPIO port I/O pin 9  */
#define PWR_GPIO_BIT_10                     PWR_PUCRB_PU10  /*!< GPIO port I/O pin 10 */
#define PWR_GPIO_BIT_11                     PWR_PUCRB_PU11  /*!< GPIO port I/O pin 11 */
#define PWR_GPIO_BIT_12                     PWR_PUCRB_PU12  /*!< GPIO port I/O pin 12 */
#define PWR_GPIO_BIT_13                     PWR_PUCRB_PU13  /*!< GPIO port I/O pin 13 */
#define PWR_GPIO_BIT_14                     PWR_PUCRB_PU14  /*!< GPIO port I/O pin 14 */
#define PWR_GPIO_BIT_15                     PWR_PUCRB_PU15  /*!< GPIO port I/O pin 15 */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_Port  GPIO Port
  * @{
  */
#define PWR_GPIO_A                          (0x00000000u)  /*!< GPIO port A */
#define PWR_GPIO_B                          (0x00000001u)  /*!< GPIO port B */
#define PWR_GPIO_C                          (0x00000002u)  /*!< GPIO port C */
#define PWR_GPIO_D                          (0x00000003u)  /*!< GPIO port D */
#if defined (GPIOE)
#define PWR_GPIO_E                          (0x00000004u)  /*!< GPIO port E */
#endif /* GPIOE */
#define PWR_GPIO_F                          (0x00000005u)  /*!< GPIO port F */
/**
  * @}
  */

/** @defgroup PWREx_Flash_PowerDown  Flash Power Down modes
  * @{
  */
#define PWR_FLASHPD_LPRUN                   PWR_CR1_FPD_LPRUN  /*!< Enable Flash power down in low power run mode */
#define PWR_FLASHPD_LPSLEEP                 PWR_CR1_FPD_LPSLP  /*!< Enable Flash power down in low power sleep mode */
#define PWR_FLASHPD_STOP                    PWR_CR1_FPD_STOP   /*!< Enable Flash power down in stop mode */
/**
  * @}
  */

/** @defgroup PWREx_Regulator_Voltage_Scale  PWR Regulator voltage scale
  * @{
  */
#define PWR_REGULATOR_VOLTAGE_SCALE1        PWR_CR1_VOS_0  /*!< Voltage scaling range 1 */
#define PWR_REGULATOR_VOLTAGE_SCALE2        PWR_CR1_VOS_1  /*!< Voltage scaling range 2 */
/**
  * @}
  */

/** @addtogroup PWR_Flag  PWR Status Flags
  * @brief  Elements values convention: 0000 00XX 000Y YYYYb
  *           - Y YYYY  : Flag position in the XX register (5 bits)
  *           - XX  : Status register (2 bits)
  *                 - 01: SR1 register
  *                 - 10: SR2 register
  *         The only exception is PWR_FLAG_WU, encompassing all
  *         wake-up flags and set to PWR_SR1_WUF.
  * @{
  */
#if defined(PWR_PVM_SUPPORT)
#define PWR_FLAG_PVMOUSB                    (0x00020000u | PWR_SR2_PVMO_USB)   /*!< USB Peripheral Voltage Monitoring output */
#endif /* PWR_PVM_SUPPORT */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @addtogroup PWREx_Exported_Macros  PWR Extended Exported Macros
  * @{
  */
#if defined(PWR_PVD_SUPPORT)
/**
  * @brief Enable the PVD Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_IT()            SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_IT()           CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Enable the PVD Event Line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_EVENT()         SET_BIT(EXTI->EMR1, PWR_EVENT_LINE_PVD)

/**
  * @brief Disable the PVD Event Line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_EVENT()        CLEAR_BIT(EXTI->EMR1, PWR_EVENT_LINE_PVD)

/**
  * @brief Enable the PVD Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Enable the PVD Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE()  SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                   \
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0U)

/**
  * @brief Disable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0U)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT()        SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVD)

/**
  * @brief Check whether or not the PVD EXTI interrupt Rising flag is set.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_RISING_FLAG()      (EXTI->RPR1 & PWR_EXTI_LINE_PVD)

/**
  * @brief Check whether or not the PVD EXTI interrupt Falling flag is set.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_FALLING_FLAG()     (EXTI->FPR1 & PWR_EXTI_LINE_PVD)

/**
  * @brief Clear the PVD EXTI interrupt Rising flag.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_RISING_FLAG()    WRITE_REG(EXTI->RPR1, PWR_EXTI_LINE_PVD)

/**
  * @brief Clear the PVD EXTI interrupt Falling flag.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_FALLING_FLAG()   WRITE_REG(EXTI->FPR1, PWR_EXTI_LINE_PVD)
#endif /* PWR_PVD_SUPPORT */

#if defined(PWR_PVM_SUPPORT)
/**
  * @brief Enable the PVM Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_IT()            SET_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Disable the PVM Extended Interrupt Line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_IT()           CLEAR_BIT(EXTI->IMR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Enable the PVM Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_EVENT()         SET_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM)

/**
  * @brief Disable the PVM Event Line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_EVENT()        CLEAR_BIT(EXTI->EMR2, PWR_EVENT_LINE_PVM)

/**
  * @brief Enable the PVM Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_RISING_EDGE()   SET_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Disable the PVM Extended Interrupt Rising Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_RISING_EDGE()  CLEAR_BIT(EXTI->RTSR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Enable the PVM Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_FALLING_EDGE()  SET_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Disable the PVM Extended Interrupt Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR2, PWR_EXTI_LINE_PVM)

/**
  * @brief  Enable the PVM Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                   \
    __HAL_PWR_PVM_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVM_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0U)

/**
  * @brief Disable the PVM Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVM_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVM_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0U)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_GENERATE_SWIT()        SET_BIT(EXTI->SWIER2, PWR_EXTI_LINE_PVM)

/**
  * @brief Check whether or not the PVM EXTI interrupt Rising flag is set.
  * @retval EXTI PVM Line Status.
  */
#define __HAL_PWR_PVM_EXTI_GET_RISING_FLAG()      (EXTI->RPR2 & PWR_EXTI_LINE_PVM)

/**
  * @brief Check whether or not the PVM EXTI interrupt Falling flag is set.
  * @retval EXTI PVM Line Status.
  */
#define __HAL_PWR_PVM_EXTI_GET_FALLING_FLAG()     (EXTI->FPR2 & PWR_EXTI_LINE_PVM)

/**
  * @brief Clear the PVM EXTI interrupt Rising flag.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_CLEAR_RISING_FLAG()    WRITE_REG(EXTI->RPR2, PWR_EXTI_LINE_PVM)

/**
  * @brief Clear the PVM EXTI interrupt Falling flag.
  * @retval None
  */
#define __HAL_PWR_PVM_EXTI_CLEAR_FALLING_FLAG()   WRITE_REG(EXTI->FPR2, PWR_EXTI_LINE_PVM)
#endif /* PWR_PVM_SUPPORT */
/**
  * @}
  */

/* Private define ------------------------------------------------------------*/
/** @defgroup PWR_Extended_Private_Defines PWR Extended Private Defines
  * @{
  */

/** @defgroup PWREx_PVM_Mode_Mask PWR PVM Mode Mask
  * @{
  */
#define PVM_MODE_IT               ((uint32_t)0x00010000)  /*!< Mask for interruption yielded by PVM threshold crossing */
#define PVM_MODE_EVT              ((uint32_t)0x00020000)  /*!< Mask for event yielded by PVM threshold crossing        */
#define PVM_RISING_EDGE           ((uint32_t)0x00000001)  /*!< Mask for rising edge set as PVM trigger                 */
#define PVM_FALLING_EDGE          ((uint32_t)0x00000002)  /*!< Mask for falling edge set as PVM trigger                */
/**
  * @}
  */

/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/** @addtogroup  PWREx_Private_Macros   PWR Extended Private Macros
  * @{
  */

#define IS_PWR_BATTERY_RESISTOR_SELECT(__RESISTOR__) (((__RESISTOR__) == PWR_BATTERY_CHARGING_RESISTOR_5) || \
                                                      ((__RESISTOR__) == PWR_BATTERY_CHARGING_RESISTOR_1_5))

#define IS_PWR_GPIO_BIT_NUMBER(__BIT_NUMBER__)  ((((__BIT_NUMBER__) & 0x0000FFFFu) != 0x00u) && \
                                                 (((__BIT_NUMBER__) & 0xFFFF0000u) == 0x00u))
#if defined (GPIOE)
#define IS_PWR_GPIO(__GPIO__)               (((__GPIO__) == PWR_GPIO_A) || \
                                             ((__GPIO__) == PWR_GPIO_B) || \
                                             ((__GPIO__) == PWR_GPIO_C) || \
                                             ((__GPIO__) == PWR_GPIO_D) || \
                                             ((__GPIO__) == PWR_GPIO_E) || \
                                             ((__GPIO__) == PWR_GPIO_F))
#else
#define IS_PWR_GPIO(__GPIO__)               (((__GPIO__) == PWR_GPIO_A) || \
                                             ((__GPIO__) == PWR_GPIO_B) || \
                                             ((__GPIO__) == PWR_GPIO_C) || \
                                             ((__GPIO__) == PWR_GPIO_D) || \
                                             ((__GPIO__) == PWR_GPIO_F))
#endif /* GPIOE */

#define IS_PWR_FLASH_POWERDOWN(__MODE__)    ((((__MODE__) & (PWR_FLASHPD_LPRUN | PWR_FLASHPD_LPSLEEP | PWR_FLASHPD_STOP)) != 0x00u) && \
                                             (((__MODE__) & ~(PWR_FLASHPD_LPRUN | PWR_FLASHPD_LPSLEEP | PWR_FLASHPD_STOP)) == 0x00u))

#define IS_PWR_VOLTAGE_SCALING_RANGE(RANGE) (((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE1) || \
                                             ((RANGE) == PWR_REGULATOR_VOLTAGE_SCALE2))

#if defined(PWR_PVD_SUPPORT)
#define IS_PWR_PVD_LEVEL(LEVEL)                   (((LEVEL) & ~(PWR_CR2_PVDRT | PWR_CR2_PVDFT)) == 0x00000000u)

#define IS_PWR_PVD_MODE(MODE)                     (((MODE) == PWR_PVD_MODE_NORMAL)              || \
                                                   ((MODE) == PWR_PVD_MODE_IT_RISING)           || \
                                                   ((MODE) == PWR_PVD_MODE_IT_FALLING)          || \
                                                   ((MODE) == PWR_PVD_MODE_IT_RISING_FALLING)   || \
                                                   ((MODE) == PWR_PVD_MODE_EVENT_RISING)        || \
                                                   ((MODE) == PWR_PVD_MODE_EVENT_FALLING)       || \
                                                   ((MODE) == PWR_PVD_MODE_EVENT_RISING_FALLING))
#endif /* PWR_PVD_SUPPORT */

#if defined(PWR_PVM_SUPPORT)
#define IS_PWR_PVM_TYPE(TYPE) ((TYPE) == PWR_PVM_USB)

#define IS_PWR_PVM_MODE(MODE)  (((MODE) == PWR_PVM_MODE_NORMAL)              ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING)           ||\
                                ((MODE) == PWR_PVM_MODE_IT_FALLING)          ||\
                                ((MODE) == PWR_PVM_MODE_IT_RISING_FALLING)   ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING)        ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_FALLING)       ||\
                                ((MODE) == PWR_PVM_MODE_EVENT_RISING_FALLING))
#endif /* PWR_PVM_SUPPORT */
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWREx_Exported_Functions  PWR Extended Exported Functions
  * @{
  */

/** @defgroup PWREx_Exported_Functions_Group1  Extended Peripheral Control functions
  * @{
  */

/* Peripheral Control functions  **********************************************/
void              HAL_PWREx_EnableBatteryCharging(uint32_t ResistorSelection);
void              HAL_PWREx_DisableBatteryCharging(void);
#if defined(PWR_CR3_ENB_ULP)
void              HAL_PWREx_EnablePORMonitorSampling(void);
void              HAL_PWREx_DisablePORMonitorSampling(void);
#endif /* PWR_CR3_ENB_ULP */
void              HAL_PWREx_EnableInternalWakeUpLine(void);
void              HAL_PWREx_DisableInternalWakeUpLine(void);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO, uint32_t GPIONumber);
void              HAL_PWREx_EnablePullUpPullDownConfig(void);
void              HAL_PWREx_DisablePullUpPullDownConfig(void);
#if defined(PWR_CR3_RRS)
void              HAL_PWREx_EnableSRAMRetention(void);
void              HAL_PWREx_DisableSRAMRetention(void);
#endif /* PWR_CR3_RRS */
void              HAL_PWREx_EnableFlashPowerDown(uint32_t PowerMode);
void              HAL_PWREx_DisableFlashPowerDown(uint32_t PowerMode);
uint32_t          HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);
#if defined(PWR_PVD_SUPPORT)
/* Power voltage detection configuration functions ****************************/
HAL_StatusTypeDef HAL_PWREx_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void              HAL_PWREx_EnablePVD(void);
void              HAL_PWREx_DisablePVD(void);
#endif /* PWR_PVD_SUPPORT */
#if defined(PWR_PVM_SUPPORT)
/* Power voltage monitoring configuration functions ***************************/
void HAL_PWREx_EnableVddIO2(void);
void HAL_PWREx_DisableVddIO2(void);
void HAL_PWREx_EnableVddUSB(void);
void HAL_PWREx_DisableVddUSB(void);
void HAL_PWREx_EnablePVMUSB(void);
void HAL_PWREx_DisablePVMUSB(void);
HAL_StatusTypeDef HAL_PWREx_ConfigPVM(PWR_PVMTypeDef *sConfigPVM);
#endif /* PWR_PVM_SUPPORT */

/* Low Power modes configuration functions ************************************/
void              HAL_PWREx_EnableLowPowerRunMode(void);
HAL_StatusTypeDef HAL_PWREx_DisableLowPowerRunMode(void);
#if defined(PWR_SHDW_SUPPORT)
void              HAL_PWREx_EnterSHUTDOWNMode(void);
#endif /* PWR_SHDW_SUPPORT */

#if defined(PWR_PVD_SUPPORT) && defined(PWR_PVM_SUPPORT)
void              HAL_PWREx_PVD_PVM_IRQHandler(void);
void              HAL_PWREx_PVD_PVM_Rising_Callback(void);
void              HAL_PWREx_PVD_PVM_Falling_Callback(void);
#elif defined(PWR_PVD_SUPPORT)
void              HAL_PWREx_PVD_IRQHandler(void);
void              HAL_PWREx_PVD_Rising_Callback(void);
void              HAL_PWREx_PVD_Falling_Callback(void);
#endif /* PWR_PVD_SUPPORT && PWR_PVM_SUPPORT */

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


#endif /* STM32G0xx_HAL_PWR_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
