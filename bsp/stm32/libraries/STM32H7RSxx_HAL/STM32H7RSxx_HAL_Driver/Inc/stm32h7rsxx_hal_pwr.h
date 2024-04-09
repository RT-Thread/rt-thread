/**
  ******************************************************************************
  * @file    stm32h7rsxx_hal_pwr.h
  * @author  MCD Application Team
  * @brief   Header file of PWR HAL module.
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
#ifndef STM32H7RSxx_HAL_PWR_H
#define STM32H7RSxx_HAL_PWR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7rsxx_hal_def.h"

/** @addtogroup STM32H7RSxx_HAL_Driver
  * @{
  */

/** @addtogroup PWR
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
  uint32_t PVDLevel; /*!< Specifies the PVD detection level.
                          This parameter can be a value of
                          @ref PWR_PVD_Detection_Level.                       */

  uint32_t Mode;     /*!< Specifies the operating mode for the selected pins.
                          This parameter can be a value of @ref PWR_PVD_Mode. */
} PWR_PVDTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_WakeUp_Pins PWR Wake-Up Pins
  * @{
  */
/* High level and No pull (default configuration) */
#define PWR_WAKEUP_PIN4                PWR_WKUPEPR_WKUPEN4                     /*!< Wakeup pin 4 (with high level polarity) */
#define PWR_WAKEUP_PIN3                PWR_WKUPEPR_WKUPEN3                     /*!< Wakeup pin 3 (with high level polarity) */
#define PWR_WAKEUP_PIN2                PWR_WKUPEPR_WKUPEN2                     /*!< Wakeup pin 2 (with high level polarity) */
#define PWR_WAKEUP_PIN1                PWR_WKUPEPR_WKUPEN1                     /*!< Wakeup pin 1 (with high level polarity) */

/* High level and No pull */
#define PWR_WAKEUP_PIN4_HIGH           PWR_WKUPEPR_WKUPEN4                     /*!< Wakeup pin 4 (with high level polarity) */
#define PWR_WAKEUP_PIN3_HIGH           PWR_WKUPEPR_WKUPEN3                     /*!< Wakeup pin 3 (with high level polarity) */
#define PWR_WAKEUP_PIN2_HIGH           PWR_WKUPEPR_WKUPEN2                     /*!< Wakeup pin 2 (with high level polarity) */
#define PWR_WAKEUP_PIN1_HIGH           PWR_WKUPEPR_WKUPEN1                     /*!< Wakeup pin 1 (with high level polarity) */

/* Low level and No pull */
#define PWR_WAKEUP_PIN4_LOW            (PWR_WKUPEPR_WKUPP4 | PWR_WKUPEPR_WKUPEN4)  /*!< Wakeup pin 4 (with low level polarity) */
#define PWR_WAKEUP_PIN3_LOW            (PWR_WKUPEPR_WKUPP3 | PWR_WKUPEPR_WKUPEN3)  /*!< Wakeup pin 3 (with low level polarity) */
#define PWR_WAKEUP_PIN2_LOW            (PWR_WKUPEPR_WKUPP2 | PWR_WKUPEPR_WKUPEN2)  /*!< Wakeup pin 2 (with low level polarity) */
#define PWR_WAKEUP_PIN1_LOW            (PWR_WKUPEPR_WKUPP1 | PWR_WKUPEPR_WKUPEN1)  /*!< Wakeup pin 1 (with low level polarity) */
/**
  * @}
  */

/** @defgroup PWR_PVD_Detection_Level PWR PVD detection level
  * @{
  */
#define PWR_PVDLEVEL_1                 (0x00000000U)                                   /*!< Programmable voltage detector level 1 selection : 1V95     */
#define PWR_PVDLEVEL_2                 PWR_CR1_PLS_0                                   /*!< Programmable voltage detector level 2 selection : 2V1      */
#define PWR_PVDLEVEL_3                 PWR_CR1_PLS_1                                   /*!< Programmable voltage detector level 3 selection : 2V25     */
#define PWR_PVDLEVEL_4                 (PWR_CR1_PLS_1 | PWR_CR1_PLS_0)                 /*!< Programmable voltage detector level 4 selection : 2V4      */
#define PWR_PVDLEVEL_5                 PWR_CR1_PLS_2                                   /*!< Programmable voltage detector level 5 selection : 2V55     */
#define PWR_PVDLEVEL_6                 (PWR_CR1_PLS_2 | PWR_CR1_PLS_0)                 /*!< Programmable voltage detector level 6 selection : 2V7      */
#define PWR_PVDLEVEL_7                 (PWR_CR1_PLS_2 | PWR_CR1_PLS_1)                 /*!< Programmable voltage detector level 7 selection : 2V85     */
#define PWR_PVDLEVEL_EXT_VOL           (PWR_CR1_PLS_2 | PWR_CR1_PLS_1 | PWR_CR1_PLS_0) /*!< External input analog voltage (Compare internally to VREF) */
/**
  * @}
  */

/** @defgroup PWR_PVD_Mode PWR PVD Mode
  * @{
  */
#define PWR_PVD_MODE_NORMAL                (0x00000000U)                       /*!< Basic mode is used                                        */
#define PWR_PVD_MODE_IT_RISING             (0x00010001U)                       /*!< Interrupt Mode with Rising edge trigger detection         */
#define PWR_PVD_MODE_IT_FALLING            (0x00010002U)                       /*!< Interrupt Mode with Falling edge trigger detection        */
#define PWR_PVD_MODE_IT_RISING_FALLING     (0x00010003U)                       /*!< Interrupt Mode with Rising/Falling edge trigger detection */
#define PWR_PVD_MODE_EVENT_RISING          (0x00020001U)                       /*!< Event Mode with Rising edge trigger detection             */
#define PWR_PVD_MODE_EVENT_FALLING         (0x00020002U)                       /*!< Event Mode with Falling edge trigger detection            */
#define PWR_PVD_MODE_EVENT_RISING_FALLING  (0x00020003U)                       /*!< Event Mode with Rising/Falling edge trigger detection     */
/**
  * @}
  */

/** @defgroup PWR_Regulator_state_in_LP_mode PWR Regulator state in SLEEP/STOP mode
  * @{
  */
/* define for interface compatibility purpose */
#define PWR_MAINREGULATOR_ON           (0x0U)

/**
  * @}
  */

/** @defgroup PWR_SLEEP_mode_entry PWR SLEEP mode entry
  * @{
  */
#define PWR_SLEEPENTRY_WFI              (0x01U)
#define PWR_SLEEPENTRY_WFE              (0x02U)
#define PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR (0x03U)
/**
  * @}
  */

/** @defgroup PWR_STOP_mode_entry PWR STOP mode entry
  * @{
  */
#define PWR_STOPENTRY_WFI              (0x01U)
#define PWR_STOPENTRY_WFE              (0x02U)
#define PWR_STOPENTRY_WFE_NO_EVT_CLEAR (0x03U)
/**
  * @}
  */

/** @defgroup PWR_Regulator_Voltage_Scale PWR Regulator Voltage Scale
  * @{
  */
#define PWR_REGULATOR_VOLTAGE_SCALE0   PWR_CSR4_VOS                            /*!< Voltage scaling range 0 (highest frequency) */
#define PWR_REGULATOR_VOLTAGE_SCALE1   (0U)                                    /*!< Voltage scaling range 1 (lowest power)      */

/**
  * @}
  */

/** @defgroup PWR_Flag PWR Status Flags
  *        Elements values convention: 0000 0XXX XXXY YYYYb
  *           -   Y YYYY  : Flag position in the XXX register (5 bits)
  *           - XXX XXX   : Status register (6 bits)
  *                 - 000001: SR1    register
  *                 - 000010: CSR1   register
  *                 - 000100: CSR2   register
  *                 - 001000: CSR3   register
  *                 - 010000: CSR4   register
  *                 - 100000: WKUPCR register
  *        The only exception is PWR_FLAG_WU, encompassing all
  *        wake-up flags and set to PWR_SR1_WUF.
  * @{
  */
/* SR1 */
#define PWR_FLAG_AVDO                  (0x002DU)                               /*!< Analog voltage detector output on VDDA                           */
#define PWR_FLAG_PVDO                  (0x0024U)                               /*!< Programmable voltage detect output                               */
#define PWR_FLAG_ACTVOSRDY             (0x0021U)                               /*!< Voltage levels ready bit for currently used ACTVOS and SDHILEVEL */
#define PWR_FLAG_ACTVOS                (0x0020U)                               /*!< Programmable voltage detect output                               */

/* CSR1 */
#define PWR_FLAG_TEMPH                 (0x0057U)                               /*!< Temperature level monitoring versus high threshold */
#define PWR_FLAG_TEMPL                 (0x0056U)                               /*!< Temperature level monitoring versus low threshold  */
#define PWR_FLAG_VBATH                 (0x0055U)                               /*!< VBAT level monitoring versus high threshold        */
#define PWR_FLAG_VBATL                 (0x0054U)                               /*!< VBAT level monitoring versus low threshold         */
#define PWR_FLAG_BRRDY                 (0x0050U)                               /*!< Backup regulator ready                             */

/* CSR2 */
#define PWR_FLAG_USB33RDY              (0x009AU)                               /*!< USB supply ready                               */
#define PWR_FLAG_SDEXTRDY              (0x0090U)                               /*!< SMPS step-down converter external supply ready */

/* CSR3 */
#define PWR_FLAG_SBF                   (0x0109U)                               /*!< System Standby flag */
#define PWR_FLAG_STOPF                 (0x0108U)                               /*!< System Stop flag    */

/* CSR4 */
#define PWR_FLAG_VOSRDY                (0x0201U)                               /*!< VOS Ready bit for VCORE voltage scaling output selection */

/* WKUPCR & WKUPFR */
#define PWR_FLAG_WUF1                  (0x0400U)                               /*!< Wakeup event on wakeup pin 1 */
#define PWR_FLAG_WUF2                  (0x0401U)                               /*!< Wakeup event on wakeup pin 2 */
#define PWR_FLAG_WUF3                  (0x0402U)                               /*!< Wakeup event on wakeup pin 3 */
#define PWR_FLAG_WUF4                  (0x0403U)                               /*!< Wakeup event on wakeup pin 4 */
#define PWR_FLAG_WUF_ALL               (0x0404U)                               /*!< Wakeup flag all              */
/**
  * @}
  */

/** @defgroup PWR_ENABLE_WUP_Mask PWR Enable WUP Mask
  * @{
  */
#define  PWR_EWUP_MASK                 (0x00FF0F0FU)
/**
  * @}
  */

/** @defgroup PWR_Flag_WUP PWR Flag WakeUp
  * @{
  */
#define PWR_FLAG_WKUP1                 PWR_WKUPCR_WKUPC1
#define PWR_FLAG_WKUP2                 PWR_WKUPCR_WKUPC2
#define PWR_FLAG_WKUP3                 PWR_WKUPCR_WKUPC3
#define PWR_FLAG_WKUP4                 PWR_WKUPCR_WKUPC4
#define PWR_FLAG_WKUP                  PWR_WKUPCR_WKUPC
/**
  * @}
  */

/**
  * @}
  */
/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWR_Exported_Macro PWR Exported Macro
  * @{
  */

/** @brief  Check whether or not a specific PWR flag is set.
  * @param  __FLAG__ specifies the flag to check.
  *           This parameter can be one of the following values:
  *          @arg PWR_FLAG_ACTVOS:    This flag indicates that the regulator voltage
  *                                   scaling output selection is ready.
  *          @arg PWR_FLAG_ACTVOSRDY: This flag indicates that the regulator voltage
  *                                   scaling output selection is ready.
  *          @arg PWR_FLAG_PVDO:      PVD Output. This flag is valid only if PVD
  *                                   is enabled by the HAL_PWR_EnablePVD()function.
  *                                   The PVD is stopped by STANDBY mode. For this reason,
  *                                   this bit is equal to 0 after STANDBY or reset until the
  *                                   PVDE bit is set.
  *          @arg PWR_FLAG_AVDO:      AVD Output. This flag is valid only if AVD is enabled
  *                 by the HAL_PWREx_EnableAVD() function. The AVD is stopped by Standby mode.
  *                 For this reason, this bit is equal to 0 after Standby or reset
  *                 until the AVDE bit is set.
  *          @arg PWR_FLAG_BRRDY :   Backup regulator ready flag. This bit is not reset
  *                 when the device wakes up from Standby mode or by a system reset
  *                 or power reset.
  *          @arg PWR_FLAG_VBATL:    This flag indicates if the VBAT level is above
  *                                  the low monitoring threshold.
  *          @arg PWR_FLAG_VBATH:    This flag indicates if the VBAT level is above
  *                                  the high monitoring threshold.
  *          @arg PWR_FLAG_TEMPL     This flag indicates if the temperature level is above
  *                                  the low monitoring threshold.
  *          @arg PWR_FLAG_TEMPH:    This flag indicates if the temperature level is above
  *                                  the high monitoring threshold.
  *          @arg PWR_FLAG_SDEXTRDY: This flag indicates if the external supply
  *                                  from the SMPS step-down converter is ready.
  *          @arg PWR_FLAG_USB33RDY: This flag indicates if the USB supply is ready.
  *          @arg PWR_FLAG_STOPF:    STOP mode flag
  *          @arg PWR_FLAG_SBF:      Standby mode flag
  *          @arg PWR_FLAG_VOSRDY    When an internal regulator is used, this bit indicates
  *                                  that all the features allowed by the selected VOS can be used.
  *          @arg PWR_FLAG_WUF1:     This flag indicates a wakeup event was
  *                                  received from WKUP1 pin.
  *          @arg PWR_FLAG_WUF2:     This flag indicates a wakeup event was
  *                                  received from WKUP2 pin.
  *          @arg PWR_FLAG_WUF3:     This flag indicates a wakeup event was
  *                                  received from WKUP3 pin.
  *          @arg PWR_FLAG_WUF4:     This flag indicates a wakeup event was
  *                                  received from WKUP4 pin.
  * @retval The (__FLAG__) state (TRUE or FALSE).
  */
#define __HAL_PWR_GET_FLAG(__FLAG__) ( \
                      ((__FLAG__) == PWR_FLAG_ACTVOS)   ? ((PWR->SR1 & PWR_SR1_ACTVOS)       == PWR_SR1_ACTVOS)    : \
                      ((__FLAG__) == PWR_FLAG_ACTVOSRDY)? ((PWR->SR1 & PWR_SR1_ACTVOSRDY)    == PWR_SR1_ACTVOSRDY) : \
                      ((__FLAG__) == PWR_FLAG_PVDO)     ? ((PWR->SR1 & PWR_SR1_PVDO)         == PWR_SR1_PVDO)      : \
                      ((__FLAG__) == PWR_FLAG_AVDO)     ? ((PWR->SR1 & PWR_SR1_AVDO)         == PWR_SR1_AVDO)      : \
                      ((__FLAG__) == PWR_FLAG_BRRDY)    ? ((PWR->CSR1 & PWR_CSR1_BRRDY)      == PWR_CSR1_BRRDY)    : \
                      ((__FLAG__) == PWR_FLAG_VBATL)    ? ((PWR->CSR1 & PWR_CSR1_VBATL)      == PWR_CSR1_VBATL)    : \
                      ((__FLAG__) == PWR_FLAG_VBATH)    ? ((PWR->CSR1 & PWR_CSR1_VBATH)      == PWR_CSR1_VBATH)    : \
                      ((__FLAG__) == PWR_FLAG_TEMPL)    ? ((PWR->CSR1 & PWR_CSR1_TEMPL)      == PWR_CSR1_TEMPL)    : \
                      ((__FLAG__) == PWR_FLAG_TEMPH)    ? ((PWR->CSR1 & PWR_CSR1_TEMPH)      == PWR_CSR1_TEMPH)    : \
                      ((__FLAG__) == PWR_FLAG_SDEXTRDY) ? ((PWR->CSR2 & PWR_CSR2_SDEXTRDY)   == PWR_CSR2_SDEXTRDY) : \
                      ((__FLAG__) == PWR_FLAG_USB33RDY) ? ((PWR->CSR2 & PWR_CSR2_USB33RDY)   == PWR_CSR2_USB33RDY) : \
                      ((__FLAG__) == PWR_FLAG_STOPF)    ? ((PWR->CSR3 & PWR_CSR3_STOPF)      == PWR_CSR3_STOPF)    : \
                      ((__FLAG__) == PWR_FLAG_SBF)      ? ((PWR->CSR3 & PWR_CSR3_SBF)        == PWR_CSR3_SBF)      : \
                      ((__FLAG__) == PWR_FLAG_VOSRDY)   ? ((PWR->CSR4 & PWR_CSR4_VOSRDY)     == PWR_CSR4_VOSRDY)   : \
                      ((__FLAG__) == PWR_FLAG_WUF1)     ? ((PWR->WKUPFR & PWR_WKUPFR_WKUPF1) == PWR_WKUPFR_WKUPF1) : \
                      ((__FLAG__) == PWR_FLAG_WUF2)     ? ((PWR->WKUPFR & PWR_WKUPFR_WKUPF2) == PWR_WKUPFR_WKUPF2) : \
                      ((__FLAG__) == PWR_FLAG_WUF3)     ? ((PWR->WKUPFR & PWR_WKUPFR_WKUPF3) == PWR_WKUPFR_WKUPF3) : \
                      ((PWR->WKUPFR & PWR_WKUPFR_WKUPF4) == PWR_WKUPFR_WKUPF4))

/** @brief  Clear PWR flags.
  * @param  __FLAG__: specifies the flag to clear.
  *         This parameter can be one of the following values:
  *           @arg PWR_FLAG_STOPF  : Stop flag.
  *                                  Indicates that the device was resumed from Stop mode.
  *           @arg PWR_FLAG_SBF    : Standby flag.
  *                                  Indicates that the device was resumed from Standby mode.
  *           @arg PWR_FLAG_WUF1   : Wakeup flag 1.
  *                                  Indicates that a wakeup event was received from the WKUP line 1.
  *           @arg PWR_FLAG_WUF2   : Wakeup flag 2.
  *                                  Indicates that a wakeup event was received from the WKUP line 2.
  *           @arg PWR_FLAG_WUF3   : Wakeup flag 3.
  *                                  Indicates that a wakeup event was received from the WKUP line 3.
  *           @arg PWR_FLAG_WUF4   : Wakeup flag 4.
  *                                  Indicates that a wakeup event was received from the WKUP line 4.
  *           @arg PWR_FLAG_WUF_ALL: All Wakeup flags.
  * @retval None.
  */
#define __HAL_PWR_CLEAR_FLAG(__FLAG__) ( \
                                        ((__FLAG__) == PWR_FLAG_STOPF)   ? (SET_BIT(PWR->CSR3,   PWR_CSR3_CSSF))     : \
                                        ((__FLAG__) == PWR_FLAG_SBF)     ? (SET_BIT(PWR->CSR3,   PWR_CSR3_CSSF))     : \
                                        ((__FLAG__) == PWR_FLAG_WUF1)    ? (SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC1)) : \
                                        ((__FLAG__) == PWR_FLAG_WUF2)    ? (SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC2)) : \
                                        ((__FLAG__) == PWR_FLAG_WUF3)    ? (SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC3)) : \
                                        ((__FLAG__) == PWR_FLAG_WUF4)    ? (SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC4)) : \
                                        (SET_BIT(PWR->WKUPCR, PWR_WKUPCR_WKUPC)))

/** @brief  Check PWR wake up flags are set or not.
  * @param  __FLAG__: specifies the wake up flag to check.
  *           This parameter can be one of the following values:
  *            @arg PWR_FLAG_WKUP1 : This parameter gets Wake up line 1 flag.
  *            @arg PWR_FLAG_WKUP2 : This parameter gets Wake up line 2 flag.
  *            @arg PWR_FLAG_WKUP3 : This parameter gets Wake up line 3 flag.
  *            @arg PWR_FLAG_WKUP4 : This parameter gets Wake up line 4 flag.
  *            @arg PWR_FLAG_WKUP  : This parameter gets Wake up lines 1 to 4 flags.
  * @retval The (__FLAG__) state (TRUE or FALSE).
  */
#define __HAL_PWR_GET_WAKEUPFLAG(__FLAG__) ((PWR->WKUPFR & (__FLAG__)) ? 0 : 1)

/** @brief  Clear CPU PWR wake up flags.
  * @param  __FLAG__ : Specifies the wake up flag to be cleared.
  *           This parameter can be one of the following values :
  *            @arg PWR_FLAG_WKUP1 : This parameter clears Wake up line 1 flag.
  *            @arg PWR_FLAG_WKUP2 : This parameter clears Wake up line 2 flag.
  *            @arg PWR_FLAG_WKUP3 : This parameter clears Wake up line 3 flag.
  *            @arg PWR_FLAG_WKUP4 : This parameter clears Wake up line 4 flag.
  *            @arg PWR_FLAG_WKUP  : This parameter clears Wake up lines 1 to 4 flags.
  * @retval None.
  */
#define __HAL_PWR_CLEAR_WAKEUPFLAG(__FLAG__) SET_BIT(PWR->WKUPCR, (__FLAG__))

/**
  * @brief  Enable the PVD Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_IT() SET_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Extended Interrupt Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_IT() CLEAR_BIT(EXTI->IMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_EVENT() SET_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Event Line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_EVENT() CLEAR_BIT(EXTI->EMR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE() SET_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Extended Interrupt Rising Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE() CLEAR_BIT(EXTI->RTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE() SET_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Disable the PVD Extended Interrupt Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE() CLEAR_BIT(EXTI->FTSR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Enable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_ENABLE_RISING_FALLING_EDGE() \
  do                                                    \
  {                                                     \
    __HAL_PWR_PVD_EXTI_ENABLE_RISING_EDGE();            \
    __HAL_PWR_PVD_EXTI_ENABLE_FALLING_EDGE();           \
  } while(0);

/**
  * @brief  Disable the PVD Extended Interrupt Rising & Falling Trigger.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_DISABLE_RISING_FALLING_EDGE() \
  do                                                     \
  {                                                      \
    __HAL_PWR_PVD_EXTI_DISABLE_RISING_EDGE();            \
    __HAL_PWR_PVD_EXTI_DISABLE_FALLING_EDGE();           \
  } while(0);

/**
  * @brief Check whether the specified PVD EXTI interrupt flag is set or not.
  * @retval EXTI PVD Line Status.
  */
#define __HAL_PWR_PVD_EXTI_GET_FLAG() ((READ_BIT(EXTI->PR1, PWR_EXTI_LINE_PVD) == PWR_EXTI_LINE_PVD) ? 1UL : 0UL)

/**
  * @brief Clear the PVD EXTI flag.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_CLEAR_FLAG() WRITE_REG(EXTI->PR1, PWR_EXTI_LINE_PVD)

/**
  * @brief  Generates a Software interrupt on PVD EXTI line.
  * @retval None.
  */
#define __HAL_PWR_PVD_EXTI_GENERATE_SWIT() SET_BIT(EXTI->SWIER1, PWR_EXTI_LINE_PVD)
/**
  * @}
  */

/* Include PWR HAL Extension module */
#include "stm32h7rsxx_hal_pwr_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup PWR_Exported_Functions PWR Exported Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group1 Initialization and De-Initialization Functions
  * @{
  */
/* Initialization and de-initialization functions *****************************/
void HAL_PWR_DeInit(void);
void HAL_PWR_EnableBkUpAccess(void);
void HAL_PWR_DisableBkUpAccess(void);
/**
  * @}
  */

/** @addtogroup PWR_Exported_Functions_Group2 Peripheral Control Functions
  * @{
  */
/* Peripheral Control Functions  **********************************************/
/* PVD configuration */
void HAL_PWR_ConfigPVD(const PWR_PVDTypeDef *sConfigPVD);
void HAL_PWR_EnablePVD(void);
void HAL_PWR_DisablePVD(void);

/* WakeUp pins configuration */
void HAL_PWR_EnableWakeUpPin(uint32_t WakeUpPinPolarity);
void HAL_PWR_DisableWakeUpPin(uint32_t WakeUpPinx);

/* Low Power modes entry */
void HAL_PWR_EnterSTOPMode(uint32_t Regulator, uint8_t STOPEntry);
void HAL_PWR_EnterSLEEPMode(uint32_t Regulator, uint8_t SLEEPEntry);
void HAL_PWR_EnterSTANDBYMode(void);

/* Cortex System Control functions  *******************************************/
void HAL_PWR_EnableSleepOnExit(void);
void HAL_PWR_DisableSleepOnExit(void);
void HAL_PWR_EnableSEVOnPend(void);
void HAL_PWR_DisableSEVOnPend(void);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/** @defgroup PWR_Private_Constants PWR Private Constants
  * @{
  */

/** @defgroup PWR_PVD_EXTI_Line PWR PVD EXTI Line
  * @{
  */
#define PWR_EXTI_LINE_PVD              EXTI_IMR1_IM16                          /*!< External interrupt line 16 connected to the PVD EXTI Line */
/**
  * @}
  */

/**
  * @}
  */
/* Private macros ------------------------------------------------------------*/
/** @defgroup PWR_Private_Macros PWR Private Macros
  * @{
  */

/** @defgroup PWR_IS_PWR_Definitions PWR Private macros to check input parameters
  * @{
  */
/* Check PVD level parameter */
#define IS_PWR_PVD_LEVEL(LEVEL) (((LEVEL) == PWR_PVDLEVEL_1) ||\
                                 ((LEVEL) == PWR_PVDLEVEL_2) ||\
                                 ((LEVEL) == PWR_PVDLEVEL_3) ||\
                                 ((LEVEL) == PWR_PVDLEVEL_4) ||\
                                 ((LEVEL) == PWR_PVDLEVEL_5) ||\
                                 ((LEVEL) == PWR_PVDLEVEL_6) ||\
                                 ((LEVEL) == PWR_PVDLEVEL_7) ||\
                                 ((LEVEL) == PWR_PVDLEVEL_EXT_VOL))

/* Check PVD mode parameter */
#define IS_PWR_PVD_MODE(MODE) (((MODE) == PWR_PVD_MODE_IT_RISING)            ||\
                               ((MODE) == PWR_PVD_MODE_IT_FALLING)           ||\
                               ((MODE) == PWR_PVD_MODE_IT_RISING_FALLING)    ||\
                               ((MODE) == PWR_PVD_MODE_EVENT_RISING)         ||\
                               ((MODE) == PWR_PVD_MODE_EVENT_FALLING)        ||\
                               ((MODE) == PWR_PVD_MODE_EVENT_RISING_FALLING) ||\
                               ((MODE) == PWR_PVD_MODE_NORMAL))

/* Check low power regulator parameter */
#define IS_PWR_REGULATOR(REGULATOR) ((REGULATOR) == PWR_MAINREGULATOR_ON)

/* Check low power mode entry parameter */
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == PWR_SLEEPENTRY_WFI) ||\
                                   ((ENTRY) == PWR_SLEEPENTRY_WFE) ||\
                                   ((ENTRY) == PWR_SLEEPENTRY_WFE_NO_EVT_CLEAR))

/* Check low power mode entry parameter */
#define IS_PWR_STOP_ENTRY(ENTRY) (((ENTRY) == PWR_STOPENTRY_WFI) ||\
                                  ((ENTRY) == PWR_STOPENTRY_WFE) ||\
                                  ((ENTRY) == PWR_STOPENTRY_WFE_NO_EVT_CLEAR))

/* Check voltage scale level parameter */
#define IS_PWR_REGULATOR_VOLTAGE(VOLTAGE) (((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE0) || \
                                           ((VOLTAGE) == PWR_REGULATOR_VOLTAGE_SCALE1))


/* Check wake up pin parameter */
#define IS_PWR_WAKEUP_PIN(PIN) (((PIN) == PWR_WAKEUP_PIN1)      ||\
                                ((PIN) == PWR_WAKEUP_PIN2)      ||\
                                ((PIN) == PWR_WAKEUP_PIN3)      ||\
                                ((PIN) == PWR_WAKEUP_PIN4)      ||\
                                ((PIN) == PWR_WAKEUP_PIN1_HIGH) ||\
                                ((PIN) == PWR_WAKEUP_PIN2_HIGH) ||\
                                ((PIN) == PWR_WAKEUP_PIN3_HIGH) ||\
                                ((PIN) == PWR_WAKEUP_PIN4_HIGH) ||\
                                ((PIN) == PWR_WAKEUP_PIN1_LOW)  ||\
                                ((PIN) == PWR_WAKEUP_PIN2_LOW)  ||\
                                ((PIN) == PWR_WAKEUP_PIN3_LOW)  ||\
                                ((PIN) == PWR_WAKEUP_PIN4_LOW))

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

#endif /* STM32H7RSxx_HAL_PWR_H */

