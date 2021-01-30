/**
  ******************************************************************************
  * @file    stm32wlxx_hal_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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
#ifndef STM32WLxx_HAL_PWR_H
#define STM32WLxx_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal_def.h"

/* Include low level driver */
#include "stm32wlxx_ll_pwr.h"

/** @addtogroup STM32WLxx_HAL_Driver
  * @{
  */

/** @defgroup PWR PWR
  * @brief PWR HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PWR_Exported_Types PWR Exported Types
  * @{
  */

/**
  * @brief  PWR PVD configuration structure definition
  */
typedef struct
{
  uint32_t PVDLevel;       /*!< PVDLevel: Specifies the PVD detection level.
                                This parameter can be a value of @ref PWR_PVD_detection_level. */

  uint32_t Mode;           /*!< Mode: Specifies the operating mode for the selected pins.
                                This parameter can be a value of @ref PWR_PVD_Mode. */
} PWR_PVDTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_PVD_detection_level  Power Voltage Detector Level selection
  * @note     Refer datasheet for selection voltage value
  * @{
  */
#define PWR_PVDLEVEL_0                      (0x00000000UL)                                   /*!< PVD threshold around 2.0 V */
#define PWR_PVDLEVEL_1                      (                                PWR_CR2_PLS_0)  /*!< PVD threshold around 2.2 V */
#define PWR_PVDLEVEL_2                      (                PWR_CR2_PLS_1                )  /*!< PVD threshold around 2.4 V */
#define PWR_PVDLEVEL_3                      (                PWR_CR2_PLS_1 | PWR_CR2_PLS_0)  /*!< PVD threshold around 2.5 V */
#define PWR_PVDLEVEL_4                      (PWR_CR2_PLS_2                                )  /*!< PVD threshold around 2.6 V */
#define PWR_PVDLEVEL_5                      (PWR_CR2_PLS_2                 | PWR_CR2_PLS_0)  /*!< PVD threshold around 2.8 V */
#define PWR_PVDLEVEL_6                      (PWR_CR2_PLS_2 | PWR_CR2_PLS_1                )  /*!< PVD threshold around 2.9 V */
#define PWR_PVDLEVEL_7                      (PWR_CR2_PLS_2 | PWR_CR2_PLS_1 | PWR_CR2_PLS_0)  /*!< External input analog voltage (compared internally to VREFINT) */
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode  PWR PVD interrupt and event mode
  * @{
  */
/* Note: On STM32WL series, power PVD event is not available on EXTI lines     */
/*       (only interruption is available through EXTI line 16).               */
#define PWR_PVD_MODE_NORMAL                 (0x00000000UL)                          /*!< PVD in polling mode (PVD flag update without interruption) */

#define PWR_PVD_MODE_IT_RISING              (PVD_MODE_IT | PVD_RISING_EDGE)         /*!< PVD in interrupt mode with rising edge trigger detection */
#define PWR_PVD_MODE_IT_FALLING             (PVD_MODE_IT | PVD_FALLING_EDGE)        /*!< PVD in interrupt mode with falling edge trigger detection */
#define PWR_PVD_MODE_IT_RISING_FALLING      (PVD_MODE_IT | PVD_RISING_FALLING_EDGE) /*!< PVD in interrupt mode with rising/falling edge trigger detection */
/**
  * @}
  */

/** @defgroup PWR_Low_Power_Mode_Selection  PWR Low Power Mode Selection
  * @{
  */
#ifdef CORE_CM0PLUS
#define PWR_LOWPOWERMODE_STOP0              (0x00000000UL)                        /*!< Stop 0: Stop mode with main regulator */
#define PWR_LOWPOWERMODE_STOP1              (PWR_C2CR1_LPMS_0)                    /*!< Stop 1: Stop mode with low power regulator */
#define PWR_LOWPOWERMODE_STOP2              (PWR_C2CR1_LPMS_1)                    /*!< Stop 2: Stop mode with low power regulator and VDD12I interruptible digital core domain supply OFF (less peripherals activated than low power mode stop 1 to reduce power consumption)*/
#define PWR_LOWPOWERMODE_STANDBY            (PWR_C2CR1_LPMS_0 | PWR_C2CR1_LPMS_1) /*!< Standby mode */
#define PWR_LOWPOWERMODE_SHUTDOWN           (PWR_C2CR1_LPMS_2 | PWR_C2CR1_LPMS_1 | PWR_C2CR1_LPMS_0) /*!< Shutdown mode */
#else
#define PWR_LOWPOWERMODE_STOP0              (0x00000000UL)                        /*!< Stop 0: Stop mode with main regulator */
#define PWR_LOWPOWERMODE_STOP1              (PWR_CR1_LPMS_0)                      /*!< Stop 1: Stop mode with low power regulator */
#define PWR_LOWPOWERMODE_STOP2              (PWR_CR1_LPMS_1)                      /*!< Stop 2: Stop mode with low power regulator and VDD12I interruptible digital core domain supply OFF (less peripherals activated than low power mode stop 1 to reduce power consumption)*/
#define PWR_LOWPOWERMODE_STANDBY            (PWR_CR1_LPMS_0 | PWR_CR1_LPMS_1)     /*!< Standby mode */
#define PWR_LOWPOWERMODE_SHUTDOWN           (PWR_CR1_LPMS_2 | PWR_CR1_LPMS_1 | PWR_CR1_LPMS_0) /*!< Shutdown mode */
#endif
/**
  * @}
  */

/** @defgroup PWR_Regulator_state_in_SLEEP_STOP_mode  PWR regulator mode
  * @{
  */
#define PWR_MAINREGULATOR_ON                (0x00000000UL)              /*!< Regulator in main mode      */
#define PWR_LOWPOWERREGULATOR_ON            (PWR_CR1_LPR)               /*!< Regulator in low-power mode */
/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry  PWR SLEEP mode entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI                  ((uint8_t)0x01)         /*!< Wait For Interruption instruction to enter Sleep mode */
#define PWR_SLEEPENTRY_WFE                  ((uint8_t)0x02)         /*!< Wait For Event instruction to enter Sleep mode        */
/**
  * @}
  */

/** @defgroup PWR_STOP_mode_entry  PWR STOP mode entry
  * @{
  */
#define PWR_STOPENTRY_WFI                   ((uint8_t)0x01)         /*!< Wait For Interruption instruction to enter Stop mode */
#define PWR_STOPENTRY_WFE                   ((uint8_t)0x02)         /*!< Wait For Event instruction to enter Stop mode        */
/**
  * @}
  */

/**
  * @}
  */

/* Private constants ---------------------------------------------------------*/
/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWR_PVD_EXTI_LINE  PWR PVD external interrupt line
  * @{
  */
#define PWR_EXTI_LINE_PVD                   (LL_EXTI_LINE_16)   /*!< External interrupt line 16 Connected to the PWR PVD */
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode_Mask PWR PVD Mode Mask
  * @{
  */
/* Note: On STM32WL series, power PVD event is not available on EXTI lines     */
/*       (only interruption is available through EXTI line 16).               */
#define PVD_MODE_IT                         (0x00010000UL)  /*!< Mask for interruption yielded by PVD threshold crossing */
#define PVD_RISING_EDGE                     (0x00000001UL)  /*!< Mask for rising edge set as PVD trigger                 */
#define PVD_FALLING_EDGE                    (0x00000002UL)  /*!< Mask for falling edge set as PVD trigger                */
#define PVD_RISING_FALLING_EDGE             (0x00000003UL)  /*!< Mask for rising and falling edges set as PVD trigger    */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/
/** @defgroup PWR_Exported_Macros  PWR Exported Macros
  * @{
  */
#if defined(DUAL_CORE)
/** @brief  Check whether or not a specific PWR flag is set.
  * @param __FLAG__ specifies the flag to check.
  *           This parameter can be one of the following values:
  *
  *            /--------------------------------SR1-------------------------------/
  *            @arg @ref PWR_FLAG_WUF1  Wake Up Flag 1. Indicates that a wakeup event
  *                                     was received from the WKUP pin 1.
  *            @arg @ref PWR_FLAG_WUF2  Wake Up Flag 2. Indicates that a wakeup event
  *                                     was received from the WKUP pin 2.
  *            @arg @ref PWR_FLAG_WUF3  Wake Up Flag 3. Indicates that a wakeup event
  *                                     was received from the WKUP pin 3.
  *
  *            @arg @ref PWR_FLAG_WPVD      Wakeup PVD flag
  *
  *            @arg @ref PWR_FLAG_HOLDC2I   CPU2 on-Hold Interrupt Flag
  *            @arg @ref PWR_FLAG_WUFI      Wake-Up Flag Internal. Set when a wakeup is detected on
  *                                         the internal wakeup line.
  *
  *            @arg @ref PWR_FLAG_WRFBUSY   Wake-up radio busy flag (triggered status: wake-up event or interruption occurred at least once. Can be cleared by software)
  *
  *            /--------------------------------SR2-------------------------------/
  *            @arg @ref PWR_FLAG_LDORDY   Main LDO ready flag
  *            @arg @ref PWR_FLAG_SMPSRDY  SMPS ready Flag
  *
  *            @arg @ref PWR_FLAG_REGLPS Low-power Regulator 1 started: Indicates whether the regulator
  *                                      is ready after a power-on reset or a Standby/Shutdown.
  *            @arg @ref PWR_FLAG_REGLPF Low-power Regulator 1 flag: Indicates whether the
  *                                      regulator 1 is in main mode or is in low-power mode.
  *
  *            @arg @ref PWR_FLAG_REGMRS Low-power regulator (main regulator or low-power regulator used) flag.
  *
  *            @arg @ref PWR_FLAG_FLASHRDY Flash ready flag
  *
  *            @arg @ref PWR_FLAG_VOSF   Voltage Scaling Flag. Indicates whether the regulator is ready
  *                                      in the selected voltage range or is still changing to the required voltage level.
  *            @arg @ref PWR_FLAG_PVDO   Power Voltage Detector Output. Indicates whether VDD voltage is below
  *                                      or above the selected PVD threshold.
  *
  *            @arg @ref PWR_FLAG_PVMO3 Peripheral Voltage Monitoring Output 3. Indicates whether VDDA voltage is
  *                                     is below or above PVM3 threshold.
  *
  *            @arg @ref PWR_FLAG_RFEOL Indicate whether supply voltage is below radio operating level (radio "end of life").
  *
  *            @arg @ref PWR_FLAG_RFBUSYS  Radio busy signal flag (current status).
  *            @arg @ref PWR_FLAG_RFBUSYMS Radio busy masked signal flag (current status).
  *
  *            @arg @ref PWR_FLAG_C2BOOTS  CPU2 boot request source information flag.
  *
  *            /----------------------------EXTSCR--------------------------/
  *            @arg @ref PWR_FLAG_STOP      System Stop 0 or Stop1 Flag for CPU1.
  *            @arg @ref PWR_FLAG_STOP2     System Stop 2 Flag for CPU1.
  *            @arg @ref PWR_FLAG_SB        System Standby Flag for CPU1.
  *
  *            @arg @ref PWR_FLAG_C2STOP    System Stop 0 or Stop1 Flag for CPU2.
  *            @arg @ref PWR_FLAG_C2STOP2   System Stop 2 Flag for CPU2.
  *            @arg @ref PWR_FLAG_C2SB      System Standby Flag for CPU2.
  *
  *            @arg @ref PWR_FLAG_C1DEEPSLEEP       CPU1 DeepSleep Flag.
  *            @arg @ref PWR_FLAG_C2DEEPSLEEP       CPU2 DeepSleep Flag.
  *
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#else
/** @brief  Check whether or not a specific PWR flag is set.
  * @param __FLAG__ specifies the flag to check.
  *           This parameter can be one of the following values:
  *
  *            /--------------------------------SR1-------------------------------/
  *            @arg @ref PWR_FLAG_WUF1  Wake Up Flag 1. Indicates that a wakeup event
  *                                     was received from the WKUP pin 1.
  *            @arg @ref PWR_FLAG_WUF2  Wake Up Flag 2. Indicates that a wakeup event
  *                                     was received from the WKUP pin 2.
  *            @arg @ref PWR_FLAG_WUF3  Wake Up Flag 3. Indicates that a wakeup event
  *                                     was received from the WKUP pin 3.
  *
  *            @arg @ref PWR_FLAG_WPVD      Wakeup PVD flag
  *
  *            @arg @ref PWR_FLAG_WUFI      Wake-Up Flag Internal. Set when a wakeup is detected on
  *                                         the internal wakeup line.
  *
  *            @arg @ref PWR_FLAG_WRFBUSY   Wake-up radio busy flag (triggered status: wake-up event or interruption occurred at least once. Can be cleared by software)
  *
  *            /--------------------------------SR2-------------------------------/
  *            @arg @ref PWR_FLAG_LDORDY   Main LDO ready flag
  *            @arg @ref PWR_FLAG_SMPSRDY  SMPS ready Flag
  *
  *            @arg @ref PWR_FLAG_REGLPS Low-power Regulator 1 started: Indicates whether the regulator
  *                                      is ready after a power-on reset or a Standby/Shutdown.
  *            @arg @ref PWR_FLAG_REGLPF Low-power Regulator 1 flag: Indicates whether the
  *                                      regulator 1 is in main mode or is in low-power mode.
  *
  *            @arg @ref PWR_FLAG_REGMRS Low-power regulator (main regulator or low-power regulator used) flag.
  *
  *            @arg @ref PWR_FLAG_FLASHRDY Flash ready flag
  *
  *            @arg @ref PWR_FLAG_VOSF   Voltage Scaling Flag. Indicates whether the regulator is ready
  *                                      in the selected voltage range or is still changing to the required voltage level.
  *            @arg @ref PWR_FLAG_PVDO   Power Voltage Detector Output. Indicates whether VDD voltage is below
  *                                      or above the selected PVD threshold.
  *
  *            @arg @ref PWR_FLAG_PVMO3 Peripheral Voltage Monitoring Output 3. Indicates whether VDDA voltage is
  *                                     is below or above PVM3 threshold.
  *
  *            @arg @ref PWR_FLAG_RFEOL Indicate whether supply voltage is below radio operating level (radio "end of life").
  *
  *            @arg @ref PWR_FLAG_RFBUSYS  Radio busy signal flag (current status).
  *            @arg @ref PWR_FLAG_RFBUSYMS Radio busy masked signal flag (current status).
  *
  *            /----------------------------EXTSCR--------------------------/
  *            @arg @ref PWR_FLAG_STOP      System Stop 0 or Stop1 Flag for CPU1.
  *            @arg @ref PWR_FLAG_STOP2     System Stop 2 Flag for CPU1.
  *            @arg @ref PWR_FLAG_SB        System Standby Flag for CPU1.
  *
  *            @arg @ref PWR_FLAG_C1DEEPSLEEP       CPU1 DeepSleep Flag.
  *
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#endif
#define __HAL_PWR_GET_FLAG(__FLAG__)  ((((__FLAG__) & PWR_FLAG_REG_MASK) == PWR_FLAG_REG_SR1) ?   \
                                       (                                                          \
                                        PWR->SR1 & (1UL << ((__FLAG__) & 31UL))                   \
                                       )                                                          \
                                       :                                                          \
                                       (                                                          \
                                        (((__FLAG__) & PWR_FLAG_REG_MASK) == PWR_FLAG_REG_SR2) ? \
                                        (                                                        \
                                         PWR->SR2 & (1UL << ((__FLAG__) & 31UL))                 \
                                        )                                                        \
                                        :                                                        \
                                        (                                                        \
                                         PWR->EXTSCR & (1UL << ((__FLAG__) & 31UL))              \
                                        )                                                        \
                                       )                                                          \
                                      )

#if defined(DUAL_CORE)
/** @brief  Clear a specific PWR flag.
  * @note   Clearing of flags {PWR_FLAG_STOP, PWR_FLAG_STOP2, PWR_FLAG_SB}
  *         and flags {PWR_FLAG_C2STOP, PWR_FLAG_C2SB} are grouped:
  *         clearing of one flag also clears the other ones.
  * @param __FLAG__ specifies the flag to clear.
  *          This parameter can be one of the following values:
  *
  *            /--------------------------------SCR (SRR)------------------------------/
  *            @arg @ref PWR_FLAG_WU    Wake Up Flag of all pins.
  *            @arg @ref PWR_FLAG_WUF1  Wake Up Flag 1. Indicates that a wakeup event
  *                                     was received from the WKUP pin 1.
  *            @arg @ref PWR_FLAG_WUF2  Wake Up Flag 2. Indicates that a wakeup event
  *                                     was received from the WKUP pin 2.
  *            @arg @ref PWR_FLAG_WUF3  Wake Up Flag 3. Indicates that a wakeup event
  *                                     was received from the WKUP pin 3.
  *
  *            @arg @ref PWR_FLAG_WPVD      Wakeup PVD flag
  *
  *            @arg @ref PWR_FLAG_HOLDC2I   CPU2 on-Hold Interrupt Flag
  *
  *            @arg @ref PWR_FLAG_WRFBUSY   Wake-up radio busy flag (triggered status: wake-up event or interruption occurred at least once. Can be cleared by software)
  *
  *            /----------------------------EXTSCR--------------------------/
  *            @arg @ref PWR_FLAG_LPMODES   System Standby Flag for CPU1.
  *            @arg @ref PWR_FLAG_C2LPMODES System Standby Flag for CPU2.
  *
  * @retval None
  */
#else
/** @brief  Clear a specific PWR flag.
  * @note   Clearing of flags {PWR_FLAG_STOP, PWR_FLAG_STOP2, PWR_FLAG_SB}
  *         are grouped:
  *         clearing of one flag also clears the other ones.
  * @param __FLAG__ specifies the flag to clear.
  *          This parameter can be one of the following values:
  *
  *            /--------------------------------SCR (SRR)------------------------------/
  *            @arg @ref PWR_FLAG_WU    Wake Up Flag of all pins.
  *            @arg @ref PWR_FLAG_WUF1  Wake Up Flag 1. Indicates that a wakeup event
  *                                     was received from the WKUP pin 1.
  *            @arg @ref PWR_FLAG_WUF2  Wake Up Flag 2. Indicates that a wakeup event
  *                                     was received from the WKUP pin 2.
  *            @arg @ref PWR_FLAG_WUF3  Wake Up Flag 3. Indicates that a wakeup event
  *                                     was received from the WKUP pin 3.
  *
  *            @arg @ref PWR_FLAG_WPVD      Wakeup PVD flag
  *
  *            @arg @ref PWR_FLAG_WRFBUSY   Wake-up radio busy flag (triggered status: wake-up event or interruption occurred at least once. Can be cleared by software)
  *
  *            /----------------------------EXTSCR--------------------------/
  *            @arg @ref PWR_FLAG_LPMODES   System Standby Flag for CPU1.
  *
  * @retval None
  */
#endif
#define __HAL_PWR_CLEAR_FLAG(__FLAG__)   ((((__FLAG__) & PWR_FLAG_REG_MASK) == PWR_FLAG_REG_EXTSCR) ?                                  \
                                          (                                                                                            \
                                           PWR->EXTSCR = (1UL << (((__FLAG__) & PWR_FLAG_EXTSCR_CLR_MASK) >> PWR_FLAG_EXTSCR_CLR_POS)) \
                                          )                                                                                            \
                                          :                                                                                            \
                                          (                                                                                            \
                                           (((__FLAG__)) == PWR_FLAG_WU) ?                                                             \
                                           (PWR->SCR = PWR_SCR_CWUF) :                                                                 \
                                           (PWR->SCR = (1UL << ((__FLAG__) & 31UL)))                                                   \
                                          )                                                                                            \
                                         )

/**
  * @brief Enable the PVD Extended Interrupt line.
  * @retval None
  */
#if defined(CORE_CM0PLUS)
#define __HAL_PWR_PVD_EXTI_ENABLE_IT()      LL_C2_EXTI_EnableIT_0_31(PWR_EXTI_LINE_PVD)
#else
#define __HAL_PWR_PVD_EXTI_ENABLE_IT()      LL_EXTI_EnableIT_0_31(PWR_EXTI_LINE_PVD)
#endif

/**
  * @brief Disable the PVD Extended Interrupt line.
  * @retval None
  */
#if defined(CORE_CM0PLUS)
#define __HAL_PWR_PVD_EXTI_DISABLE_IT()     LL_C2_EXTI_DisableIT_0_31(PWR_EXTI_LINE_PVD)
#else
#define __HAL_PWR_PVD_EXTI_DISABLE_IT()     LL_EXTI_DisableIT_0_31(PWR_EXTI_LINE_PVD)
#endif

/* Note: On STM32WL series, power PVD event is not available on EXTI lines     */
/*       (only interruption is available through EXTI line 16).               */

/**
  * @brief Enable the PVD Extended Interrupt Rising Trigger.
  * @note  PVD flag polarity is inverted compared to EXTI line, therefore
  *        EXTI rising and falling logic edges are inverted versus PVD voltage edges.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE()    LL_EXTI_EnableFallingTrig_0_31(PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Rising Trigger.
  * @note  PVD flag polarity is inverted compared to EXTI line, therefore
  *        EXTI rising and falling logic edges are inverted versus PVD voltage edges.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE()   LL_EXTI_DisableFallingTrig_0_31(PWR_EXTI_LINE_PVD)

/**
  * @brief Enable the PVD Extended Interrupt Falling Trigger.
  * @note  PVD flag polarity is inverted compared to EXTI line, therefore
  *        EXTI rising and falling logic edges are inverted versus PVD voltage edges.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE()   LL_EXTI_EnableRisingTrig_0_31(PWR_EXTI_LINE_PVD)

/**
  * @brief Disable the PVD Extended Interrupt Falling Trigger.
  * @note  PVD flag polarity is inverted compared to EXTI line, therefore
  *        EXTI rising and falling logic edges are inverted versus PVD voltage edges.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE()  LL_EXTI_DisableRisingTrig_0_31(PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE()  \
  do {                                                   \
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();             \
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief Disable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE()  \
  do {                                                    \
    __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();             \
    __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();            \
  } while(0)

/**
  * @brief  Generate a Software interrupt on selected EXTI line.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT()  LL_EXTI_GenerateSWI_0_31(PWR_EXTI_LINE_PVD)

/**
  * @brief Check whether or not the PVD EXTI interrupt flag is set.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_FLAG()       LL_EXTI_ReadFlag_0_31(PWR_EXTI_LINE_PVD)

/**
  * @brief Clear the PVD EXTI interrupt flag.
  * @retval None
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_FLAG()     LL_EXTI_ClearFlag_0_31(PWR_EXTI_LINE_PVD)

/**
  * @}
  */


/* Private macros --------------------------------------------------------*/
/** @defgroup PWR_Private_Macros  PWR Private Macros
  * @{
  */
#define IS_PWR_PVD_LEVEL(__LEVEL__) (((__LEVEL__) == PWR_PVDLEVEL_0) || ((__LEVEL__) == PWR_PVDLEVEL_1)|| \
                                     ((__LEVEL__) == PWR_PVDLEVEL_2) || ((__LEVEL__) == PWR_PVDLEVEL_3)|| \
                                     ((__LEVEL__) == PWR_PVDLEVEL_4) || ((__LEVEL__) == PWR_PVDLEVEL_5)|| \
                                     ((__LEVEL__) == PWR_PVDLEVEL_6) || ((__LEVEL__) == PWR_PVDLEVEL_7))

#define IS_PWR_PVD_MODE(__MODE__)  (((__MODE__) == PWR_PVD_MODE_NORMAL)              ||\
                                    ((__MODE__) == PWR_PVD_MODE_IT_RISING)           ||\
                                    ((__MODE__) == PWR_PVD_MODE_IT_FALLING)          ||\
                                    ((__MODE__) == PWR_PVD_MODE_IT_RISING_FALLING))

#define IS_PWR_REGULATOR(__REGULATOR__)           (((__REGULATOR__) == PWR_MAINREGULATOR_ON)    || \
                                                   ((__REGULATOR__) == PWR_LOWPOWERREGULATOR_ON))

#define IS_PWR_SLEEP_ENTRY(__ENTRY__)             (((__ENTRY__) == PWR_SLEEPENTRY_WFI) || \
                                                   ((__ENTRY__) == PWR_SLEEPENTRY_WFE))

#define IS_PWR_STOP_ENTRY(__ENTRY__)              (((__ENTRY__) == PWR_STOPENTRY_WFI) || \
                                                   ((__ENTRY__) == PWR_STOPENTRY_WFE))
/**
  * @}
  */

/* Include PWR HAL Extended module */
#include "stm32wlxx_hal_pwr_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_Exported_Functions  PWR Exported Functions
  * @{
  */

/** @defgroup PWR_Exported_Functions_Group1  Initialization and de-initialization functions
  * @{
  */

/* Initialization and de-initialization functions *******************************/
void              HAL_PWR_DeInit(void);

void              HAL_PWR_EnableBkUpAccess(void);
void              HAL_PWR_DisableBkUpAccess(void);
/**
  * @}
  */

/** @defgroup PWR_Exported_Functions_Group2  Peripheral Control functions
  * @{
  */
/* Peripheral Control functions  ************************************************/
HAL_StatusTypeDef HAL_PWR_ConfigPVD(PWR_PVDTypeDef *sConfigPVD);
void              HAL_PWR_EnablePVD(void);
void              HAL_PWR_DisablePVD(void);

/* WakeUp pins configuration functions ****************************************/
void              HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinPolarity);
void              HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);

/* Low Power modes configuration functions ************************************/
void              HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void              HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void              HAL_PWR_EnterSTANDBYMode(void);

void              HAL_PWR_EnableSleepOnExit(void);
void              HAL_PWR_DisableSleepOnExit(void);

void              HAL_PWR_EnableSEVOnPend(void);
void              HAL_PWR_DisableSEVOnPend(void);

void              HAL_PWR_PVDCallback(void);

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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif


#endif /* STM32WLxx_HAL_PWR_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
