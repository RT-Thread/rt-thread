/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_pwr_ex.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL Extension module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7RSxx_HAL_PWR_EX_H
#define STM32H7RSxx_HAL_PWR_EX_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @addtogroup PWREx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PWREx_Exported_Types PWREx Exported Types
  * @{
  */
/**
  * @brief  PWREx AVD configuration structure definition
  */
typedef struct
{
  uint32_t AVDLevel; /*!< Specifies the AVD detection level.
                          This parameter can be a value of @ref PWREx_AVD_detection_level */

  uint32_t Mode;     /*!< Specifies the EXTI operating mode for the AVD event.
                          This parameter can be a value of @ref PWREx_AVD_Mode.           */
} PWREx_AVDTypeDef;

/**
  * @brief  PWREx Wakeup pin configuration structure definition
  */
typedef struct
{
  uint32_t WakeUpPin;   /*!< Specifies the Wake-Up pin to be enabled.
                             This parameter can be a value of @ref PWR_WakeUp_Pins  */

  uint32_t PinPolarity; /*!< Specifies the Wake-Up pin polarity.
                             This parameter can be a value of @ref PWREx_PIN_Polarity */

  uint32_t PinPull;     /*!< Specifies the Wake-Up pin pull.
                             This parameter can be a value of @ref PWREx_PIN_Pull     */
} PWREx_WakeupPinTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWREx_Exported_Constants PWREx Exported Constants
  * @{
  */

/** @defgroup PWREx_PIN_Polarity PWREx Pin Polarity configuration
  * @{
  */
#define PWR_PIN_POLARITY_HIGH          (0x0U)
#define PWR_PIN_POLARITY_LOW           (0x1U)
/**
  * @}
  */

/** @defgroup PWREx_PIN_Pull PWREx Pin Pull configuration
  * @{
  */
#define PWR_PIN_NO_PULL                (0x0U)
#define PWR_PIN_PULL_UP                (0x1U)
#define PWR_PIN_PULL_DOWN              (0x2U)
/**
  * @}
  */

/** @defgroup PWREx_Wakeup_Pins_Flags PWREx Wakeup Pins Flags.
  * @{
  */
#define PWR_WAKEUP_FLAG1               PWR_WKUPFR_WKUPF1                       /*!< Wakeup flag on PA0  */
#define PWR_WAKEUP_FLAG2               PWR_WKUPFR_WKUPF2                       /*!< Wakeup flag on PA2  */
#define PWR_WAKEUP_FLAG3               PWR_WKUPFR_WKUPF3                       /*!< Wakeup flag on PC13 */
#define PWR_WAKEUP_FLAG4               PWR_WKUPFR_WKUPF4                       /*!< Wakeup flag on PC1  */

#define PWR_WAKEUP_FLAG_ALL           (PWR_WKUPFR_WKUPF1 | PWR_WKUPFR_WKUPF2 |\
                                       PWR_WKUPFR_WKUPF3 | PWR_WKUPFR_WKUPF4)
/**
  * @}
  */

/** @defgroup PWREx_Supply_configuration PWREx Supply configuration
  * @{
  */
#define PWR_LDO_SUPPLY                       PWR_CSR2_LDOEN                                                              /*!< Core domains are supplied from the LDO                                                                     */
#define PWR_EXTERNAL_SOURCE_SUPPLY           PWR_CSR2_BYPASS                                                             /*!< The SMPS disabled and the LDO Bypass. The Core domains are supplied from an external source                */
#define PWR_DIRECT_SMPS_SUPPLY               PWR_CSR2_SDEN                                                               /*!< Core domains are supplied from the SMPS only                                                               */

#define PWR_SMPS_1V8_SUPPLIES_LDO            (PWR_CSR2_SDHILEVEL | PWR_CSR2_SDEN    | PWR_CSR2_LDOEN)                    /*!< The SMPS 1.8V output supplies the LDO which supplies the Core domains                                      */
#define PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO    (PWR_CSR2_SDHILEVEL | PWR_CSR2_SMPSEXTHP | PWR_CSR2_SDEN | PWR_CSR2_LDOEN)  /*!< The SMPS 1.8V output supplies external circuits and the LDO. The Core domains are supplied from the LDO    */
#define PWR_SMPS_1V8_SUPPLIES_EXT            (PWR_CSR2_SDHILEVEL | PWR_CSR2_SMPSEXTHP | PWR_CSR2_SDEN | PWR_CSR2_BYPASS) /*!< The SMPS 1.8V output supplies external source which supplies the Core domains                              */

#define PWR_SUPPLY_CONFIG_MASK               (PWR_CSR2_SDHILEVEL | PWR_CSR2_SMPSEXTHP | \
                                              PWR_CSR2_SDEN | PWR_CSR2_LDOEN | PWR_CSR2_BYPASS)

/**
  * @}
  */


/** @defgroup PWREx_AVD_detection_level PWREx AVD detection level
  * @{
  */
#define PWR_AVDLEVEL_1                 (0x0U)                                  /*!< Analog voltage detector level 1 : 1V7 */
#define PWR_AVDLEVEL_2                 PWR_CR1_ALS_0                           /*!< Analog voltage detector level 2 : 2V1 */
#define PWR_AVDLEVEL_3                 PWR_CR1_ALS_1                           /*!< Analog voltage detector level 3 : 2V5 */
#define PWR_AVDLEVEL_4                 (PWR_CR1_ALS_1 | PWR_CR1_ALS_0)         /*!< Analog voltage detector level 4 : 2V8 */

/**
  * @}
  */

/** @defgroup PWREx_AVD_Mode PWREx AVD Mode
  * @{
  */
#define PWR_AVD_MODE_NORMAL                  (0x00000000U)                     /*!< Basic mode is used                                                 */
#define PWR_AVD_MODE_IT_RISING               (0x00010001U)                     /*!< External Interrupt Mode with Rising edge trigger detection         */
#define PWR_AVD_MODE_IT_FALLING              (0x00010002U)                     /*!< External Interrupt Mode with Falling edge trigger detection        */
#define PWR_AVD_MODE_IT_RISING_FALLING       (0x00010003U)                     /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_AVD_MODE_EVENT_RISING            (0x00020001U)                     /*!< Event Mode with Rising edge trigger detection                      */
#define PWR_AVD_MODE_EVENT_FALLING           (0x00020002U)                     /*!< Event Mode with Falling edge trigger detection                     */
#define PWR_AVD_MODE_EVENT_RISING_FALLING    (0x00020003U)                     /*!< Event Mode with Rising/Falling edge trigger detection              */
/**
  * @}
  */

/** @defgroup PWREx_Regulator_Voltage_Scale PWREx Regulator Voltage Scale
  * @{
  */
#define PWR_REGULATOR_STOP_VOLTAGE_SCALE3    PWR_CR1_SVOS                      /*!< System Stop mode voltage scaling range 3 (highest frequency) */
#define PWR_REGULATOR_STOP_VOLTAGE_SCALE5    (0x0U)                            /*!< System Stop mode voltage scaling range 5 (lowest power)      */

/**
  * @}
  */

/** @defgroup PWREx_VBAT_Battery_Charging_Resistor PWR battery charging resistor selection
  * @{
  */
#define PWR_BATTERY_CHARGING_RESISTOR_5      (0x0U)                            /*!< VBAT charging through a 5 kOhms resistor   */
#define PWR_BATTERY_CHARGING_RESISTOR_1_5    PWR_CSR2_VBRS                     /*!< VBAT charging through a 1.5 kOhms resistor */
/**
  * @}
  */

/** @defgroup PWREx_VBAT_Thresholds PWREx VBAT Thresholds
  * @{
  */
#define PWR_VBAT_BETWEEN_HIGH_LOW_THRESHOLD    (0x0U)
#define PWR_VBAT_BELOW_LOW_THRESHOLD           PWR_CSR1_VBATL
#define PWR_VBAT_ABOVE_HIGH_THRESHOLD          PWR_CSR1_VBATH
/**
  * @}
  */

/** @defgroup PWREx_TEMP_Thresholds PWREx Temperature Thresholds
  * @{
  */
#define PWR_TEMP_BETWEEN_HIGH_LOW_THRESHOLD  (0x00000000U)
#define PWR_TEMP_BELOW_LOW_THRESHOLD         PWR_CSR1_TEMPL
#define PWR_TEMP_ABOVE_HIGH_THRESHOLD        PWR_CSR1_TEMPH
/**
  * @}
  */

/** @defgroup PWREx_CAPACITOR_Port PWREx Capacitor Port
  * @{
  */
#define PWR_CAPACITOR_PORT1                 PWR_CSR2_XSPICAP1
#define PWR_CAPACITOR_PORT2                 PWR_CSR2_XSPICAP2
/**
  * @}
  */

/** @defgroup PWREx_CAPACITOR_Value PWREx Capacitor Value
  * @{
  */
#define PWR_CAPACITOR_OFF                      (0x0U)
#define PWR_CAPACITOR_ONE_THIRD_CAPACITANCE    PWR_CSR2_XSPICAP1_0
#define PWR_CAPACITOR_TWO_THIRD_CAPACITANCE    PWR_CSR2_XSPICAP1_1
#define PWR_CAPACITOR_FULL_CAPACITANCE         PWR_CSR2_XSPICAP1
/**
  * @}
  */

/** @defgroup PWREx_AVD_EXTI_Line PWREx AVD EXTI Line 16
  * @{
  */
#define PWR_EXTI_LINE_AVD              EXTI_IMR1_IM16                          /*!< External interrupt line 16 connected to the AVD EXTI Line */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_PullUp_Port PWR Extended GPIO Pull-Up Port
  * @{
  */
#define PWR_GPIO_PULLUP_PORT_N         (0x00U)                                 /*!< GPIO port N */
#define PWR_GPIO_PULLUP_PORT_O         (0x01U)                                 /*!< GPIO port O */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_PullDown_Port PWR Extended GPIO Pull-Down Port
  * @{
  */
#define PWR_GPIO_PULLDOWN_PORT_N       (0x00U)                                 /*!< GPIO port N */
#define PWR_GPIO_PULLDOWN_PORT_O       (0x01U)                                 /*!< GPIO port O */
#define PWR_GPIO_PULLDOWN_PORT_P       (0x02U)                                 /*!< GPIO port P */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_PullUp_Pin_Mask PWR Extended GPIO Pull-Up Pin Mask
  * @{
  */
#define PWR_GPIO_N_PULLUP_PIN_1        (0x0002U)                               /*!< GPIO N pin 1  */
#define PWR_GPIO_N_PULLUP_PIN_6        (0x0040U)                               /*!< GPIO N pin 6  */
#define PWR_GPIO_N_PULLUP_PIN_12       (0x1000U)                               /*!< GPIO N pin 12 */

#define PWR_GPIO_O_PULLUP_PIN_0        (0x0001U)                               /*!< GPIO O pin 0 */
#define PWR_GPIO_O_PULLUP_PIN_1        (0x0002U)                               /*!< GPIO O pin 1 */
#define PWR_GPIO_O_PULLUP_PIN_4        (0x0010U)                               /*!< GPIO O pin 4 */
/**
  * @}
  */

/** @defgroup PWREx_GPIO_PullDown_Pin_Mask PWR Extended GPIO Pull-Down Pin Mask
  * @{
  */
#define PWR_GPIO_N_PULLDOWN_PIN_0      (0x0001U)                               /*!< GPIO N pin 0       */
#define PWR_GPIO_N_PULLDOWN_PIN_1      (0x0002U)                               /*!< GPIO N pin 1       */
#define PWR_GPIO_N_PULLDOWN_PIN_2_5    (0x0004U)                               /*!< GPIO N pin 2 to 5  */
#define PWR_GPIO_N_PULLDOWN_PIN_6      (0x0040U)                               /*!< GPIO N pin 6       */
#define PWR_GPIO_N_PULLDOWN_PIN_8_11   (0x0100U)                               /*!< GPIO N pin 8 to 11 */
#define PWR_GPIO_N_PULLDOWN_PIN_12     (0x1000U)                               /*!< GPIO N pin 12      */

#define PWR_GPIO_O_PULLDOWN_PIN_0      (0x0001U)                               /*!< GPIO O pin 0        */
#define PWR_GPIO_O_PULLDOWN_PIN_1      (0x0002U)                               /*!< GPIO O pin 1        */
#define PWR_GPIO_O_PULLDOWN_PIN_2      (0x0004U)                               /*!< GPIO O pin 2        */
#define PWR_GPIO_O_PULLDOWN_PIN_3      (0x0008U)                               /*!< GPIO O pin 3        */
#define PWR_GPIO_O_PULLDOWN_PIN_4      (0x0010U)                               /*!< GPIO O pin 4        */

#define PWR_GPIO_P_PULLDOWN_PIN_0_3    (0x0001U)                               /*!< GPIO P pin 0 to 3   */
#define PWR_GPIO_P_PULLDOWN_PIN_4_7    (0x0010U)                               /*!< GPIO P pin 4 to 7   */
#define PWR_GPIO_P_PULLDOWN_PIN_8_11   (0x0100U)                               /*!< GPIO P pin 8 to 11  */
#define PWR_GPIO_P_PULLDOWN_PIN_12_15  (0x1000U)                               /*!< GPIO P pin 12 to 15 */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/** @defgroup PWREx_Exported_Macro PWREx Exported Macro
  *  @{
  */

/**
  * @brief Enable the AVD EXTI Line 16.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_ENABLE_IT()    SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_AVD)

/**
  * @brief Disable the AVD EXTI Line 16
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_DISABLE_IT()    CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_AVD)

/**
  * @brief Enable event on AVD EXTI Line 16.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_ENABLE_EVENT()    SET_BIT(EXTI->EMR1, PWR_EXTI_LINE_AVD)

/**
  * @brief Disable event on AVD EXTI Line 16.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_DISABLE_EVENT()    CLEAR_BIT(EXTI->EMR1, PWR_EXTI_LINE_AVD)

/**
  * @brief Enable the AVD Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_ENABLE_RISING_EDGE()    SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_AVD)

/**
  * @brief Disable the AVD Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_DISABLE_RISING_EDGE()    CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_AVD)

/**
  * @brief Enable the AVD Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_ENABLE_FALLING_EDGE()    SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_AVD)

/**
  * @brief Disable the AVD Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_DISABLE_FALLING_EDGE()    CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_AVD)

/**
  * @brief Enable the AVD Extended Interrupt Rising and Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_ENABLE_RISING_FALLING_EDGE() \
do {                                                    \
     __HAL_PWR_AVD_EXTI_ENABLE_RISING_EDGE();           \
     __HAL_PWR_AVD_EXTI_ENABLE_FALLING_EDGE();          \
} while(0);

/**
  * @brief Disable the AVD Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_DISABLE_RISING_FALLING_EDGE() \
do {                                                     \
     __HAL_PWR_AVD_EXTI_DISABLE_RISING_EDGE();           \
     __HAL_PWR_AVD_EXTI_DISABLE_FALLING_EDGE();          \
} while(0);

/**
  * @brief Check whether the specified AVD EXTI interrupt flag is set or not.
  * @retval EXTI AVD Line Status.
  */
#define __HAL_PWR_AVD_EXTI_GET_FLAG()     ((READ_BIT(EXTI->PR1, PWR_EXTI_LINE_AVD) == PWR_EXTI_LINE_AVD) ? 1UL : 0UL)

/**
  * @brief  Clear the AVD EXTI flag.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_CLEAR_FLAG()    WRITE_REG(EXTI->PR1, PWR_EXTI_LINE_AVD)

/**
  * @brief  Generates a Software interrupt on AVD EXTI line.
  * @retval None.
  */
#define __HAL_PWR_AVD_EXTI_GENERATE_SWIT()    SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_AVD)
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @addtogroup PWREx_Exported_Functions PWREx Exported Functions
  * @{
  */

/** @addtogroup PWREx_Exported_Functions_Group1 Power Supply Control Functions
  * @{
  */
/* Power supply control functions */
HAL_StatusTypeDef HAL_PWREx_ConfigSupply(uint32_t SupplySource);
uint32_t          HAL_PWREx_GetSupplyConfig(void);

/* Power voltage scaling functions */
HAL_StatusTypeDef HAL_PWREx_ControlVoltageScaling(uint32_t VoltageScaling);
uint32_t          HAL_PWREx_GetVoltageRange(void);
HAL_StatusTypeDef HAL_PWREx_ControlStopModeVoltageScaling(uint32_t VoltageScaling);
uint32_t          HAL_PWREx_GetStopModeVoltageRange(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group2 Low Power Control Functions
  * @{
  */
/* Flash low power control functions */
void HAL_PWREx_EnableFlashPowerDown(void);
void HAL_PWREx_DisableFlashPowerDown(void);

/* Wakeup Pins control functions */
void              HAL_PWREx_EnableWakeUpPin(const PWREx_WakeupPinTypeDef *sPinParams);
void              HAL_PWREx_DisableWakeUpPin(uint32_t WakeUpPin);
uint32_t          HAL_PWREx_GetWakeupFlag(uint32_t WakeUpFlag);
HAL_StatusTypeDef HAL_PWREx_ClearWakeupFlag(uint32_t WakeUpFlag);

/* Power Wakeup PIN IRQ Handler */
void HAL_PWREx_WAKEUP_PIN_IRQHandler(void);
void HAL_PWREx_WKUP1_Callback(void);
void HAL_PWREx_WKUP2_Callback(void);
void HAL_PWREx_WKUP3_Callback(void);
void HAL_PWREx_WKUP4_Callback(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group3 Peripherals Control Functions
  * @{
  */
/* Backup regulator control functions */
HAL_StatusTypeDef HAL_PWREx_EnableBkUpReg(void);
HAL_StatusTypeDef HAL_PWREx_DisableBkUpReg(void);

/* USB regulator control functions */
void              HAL_PWREx_EnableUSBReg(void);
void              HAL_PWREx_DisableUSBReg(void);
HAL_StatusTypeDef HAL_PWREx_EnableUSBVoltageDetector(void);
HAL_StatusTypeDef HAL_PWREx_DisableUSBVoltageDetector(void);
void              HAL_PWREx_EnableUSBHSregulator(void);
void              HAL_PWREx_DisableUSBHSregulator(void);

/* USB regulator control functions */
void HAL_PWREx_EnableUCPDStandbyMode(void);
void HAL_PWREx_DisableUCPDStandbyMode(void);
void HAL_PWREx_EnableUCPDDeadBattery(void);
void HAL_PWREx_DisableUCPDDeadBattery(void);

/* Battery control functions */
void HAL_PWREx_EnableBatteryCharging(uint32_t ResistorValue);
void HAL_PWREx_DisableBatteryCharging(void);

/* Analog Booster functions */
void HAL_PWREx_EnableAnalogBooster(void);
void HAL_PWREx_DisableAnalogBooster(void);

/* XSPIM_P1 functions */
void HAL_PWREx_EnableXSPIM1(void);
void HAL_PWREx_DisableXSPIM1(void);

/* XSPIM_P2 functions */
void HAL_PWREx_EnableXSPIM2(void);
void HAL_PWREx_DisableXSPIM2(void);

/* PORT capacitor control functions */
void     HAL_PWREx_ConfigXSPIPortCap(uint32_t PortCapacitor, uint32_t PortCapacitorSetting);
uint32_t HAL_PWREx_GetConfigXSPIPortCap(uint32_t PortCapacitor);

/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group4 Power Monitoring functions
  * @{
  */
/* Power VBAT/Temperature monitoring functions */
void     HAL_PWREx_EnableMonitoring(void);
void     HAL_PWREx_DisableMonitoring(void);
uint32_t HAL_PWREx_GetTemperatureLevel(void);
uint32_t HAL_PWREx_GetVBATLevel(void);

/* Power AVD configuration functions */
void HAL_PWREx_ConfigAVD(const PWREx_AVDTypeDef *sConfigAVD);
void HAL_PWREx_EnableAVD(void);
void HAL_PWREx_DisableAVD(void);

/* Power PVD/AVD IRQ Handler */
void HAL_PWREx_PVD_AVD_IRQHandler(void);
void HAL_PWREx_PVD_AVD_Callback(void);
/**
  * @}
  */

/** @addtogroup PWREx_Exported_Functions_Group5 I/O Pull-Up Pull-Down Configuration Functions
  * @{
  */
/* GPIO Pull-up Pull-down configuration functions */
void HAL_PWREx_EnablePullUpPullDownConfig(void);
void HAL_PWREx_DisablePullUpPullDownConfig(void);

/* GPIO Pull control functions */
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullUp(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_EnableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin);
HAL_StatusTypeDef HAL_PWREx_DisableGPIOPullDown(uint32_t GPIO_Port, uint32_t GPIO_Pin);
/**
  * @}
  */

/**
  * @}
  */
/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup PWREx_Private_Macros PWREx Private Macros
  * @{
  */

/** @defgroup PWREx_IS_PWR_Definitions PWREx Private macros to check input parameters
  * @{
  */
/* Check PWR regulator configuration parameter */
#define IS_PWR_SUPPLY(PWR_SOURCE) (((PWR_SOURCE) == PWR_LDO_SUPPLY)                    ||\
                                   ((PWR_SOURCE) == PWR_DIRECT_SMPS_SUPPLY)            ||\
                                   ((PWR_SOURCE) == PWR_SMPS_1V8_SUPPLIES_LDO)         ||\
                                   ((PWR_SOURCE) == PWR_SMPS_1V8_SUPPLIES_EXT_AND_LDO) ||\
                                   ((PWR_SOURCE) == PWR_SMPS_1V8_SUPPLIES_EXT)         ||\
                                   ((PWR_SOURCE) == PWR_EXTERNAL_SOURCE_SUPPLY))

/* Check PWR regulator configuration in STOP mode parameter */
#define IS_PWR_STOP_MODE_REGULATOR_VOLTAGE(VOLTAGE) (((VOLTAGE) == PWR_REGULATOR_STOP_VOLTAGE_SCALE3)  ||\
                                                     ((VOLTAGE) == PWR_REGULATOR_STOP_VOLTAGE_SCALE5))

/* Check wake up pin polarity parameter */
#define IS_PWR_WAKEUP_PIN_POLARITY(POLARITY) (((POLARITY) == PWR_PIN_POLARITY_HIGH) ||\
                                              ((POLARITY) == PWR_PIN_POLARITY_LOW))

/* Check wake up pin pull configuration parameter */
#define IS_PWR_WAKEUP_PIN_PULL(PULL) (((PULL) == PWR_PIN_NO_PULL) ||\
                                      ((PULL) == PWR_PIN_PULL_UP) ||\
                                      ((PULL) == PWR_PIN_PULL_DOWN))

/* Check wake up flag parameter */
#define IS_PWR_WAKEUP_FLAG(FLAG) (((FLAG) == PWR_WAKEUP_FLAG1) ||\
                                  ((FLAG) == PWR_WAKEUP_FLAG2) ||\
                                  ((FLAG) == PWR_WAKEUP_FLAG3) ||\
                                  ((FLAG) == PWR_WAKEUP_FLAG4) ||\
                                  ((FLAG) == PWR_WAKEUP_FLAG_ALL))

/* Check wake up flag parameter */
#define IS_PWR_AVD_LEVEL(LEVEL) (((LEVEL) == PWR_AVDLEVEL_1) ||\
                                 ((LEVEL) == PWR_AVDLEVEL_2) ||\
                                 ((LEVEL) == PWR_AVDLEVEL_3) ||\
                                 ((LEVEL) == PWR_AVDLEVEL_4))

/* Check AVD mode parameter */
#define IS_PWR_AVD_MODE(MODE) (((MODE) == PWR_AVD_MODE_IT_RISING)         ||\
                               ((MODE) == PWR_AVD_MODE_IT_FALLING)        ||\
                               ((MODE) == PWR_AVD_MODE_IT_RISING_FALLING) ||\
                               ((MODE) == PWR_AVD_MODE_EVENT_RISING)      ||\
                               ((MODE) == PWR_AVD_MODE_EVENT_FALLING)     ||\
                               ((MODE) == PWR_AVD_MODE_NORMAL)            ||\
                               ((MODE) == PWR_AVD_MODE_EVENT_RISING_FALLING))

/* Check resistor battery parameter */
#define IS_PWR_BATTERY_RESISTOR_SELECT(RESISTOR) (((RESISTOR) == PWR_BATTERY_CHARGING_RESISTOR_5) ||\
                                                  ((RESISTOR) == PWR_BATTERY_CHARGING_RESISTOR_1_5))

/* Check the capacitor port parameter */
#define IS_PWR_CAPACITOR(PORT)  (((PORT) == PWR_CAPACITOR_PORT1) || \
                                 ((PORT) == PWR_CAPACITOR_PORT2))

/* Check the capacitor port setting parameter */
#define IS_PWR_CAPACITOR_SETTING(SETTING)  (((SETTING) == PWR_CAPACITOR_OFF) || \
                                            ((SETTING) == PWR_CAPACITOR_ONE_THIRD_CAPACITANCE) || \
                                            ((SETTING) == PWR_CAPACITOR_TWO_THIRD_CAPACITANCE) || \
                                            ((SETTING) == PWR_CAPACITOR_FULL_CAPACITANCE))

/* Check GPIO Pull-Up Port parameter */
#define IS_PWR_GPIO_PULLPUP_PORT(GPIO_PORT)  (((GPIO_PORT) == PWR_GPIO_PULLUP_PORT_N) ||\
                                              ((GPIO_PORT) == PWR_GPIO_PULLUP_PORT_O))

/* Check GPIO Pull-Down Port parameter */
#define IS_PWR_GPIO_PULLDOWN_PORT(GPIO_PORT)  (((GPIO_PORT) == PWR_GPIO_PULLDOWN_PORT_N) ||\
                                               ((GPIO_PORT) == PWR_GPIO_PULLDOWN_PORT_O) ||\
                                               ((GPIO_PORT) == PWR_GPIO_PULLDOWN_PORT_P))

/* GPIO pin mask check macro */
#define IS_PWR_GPIO_PIN_MASK(BIT_MASK)  ((((BIT_MASK) & GPIO_PIN_MASK) != 0U) && ((BIT_MASK) <= GPIO_PIN_MASK))
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
#endif /* __cplusplus */


#endif /* STM32H7RSxx_HAL_PWR_EX_H */

