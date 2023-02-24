/**
  ******************************************************************************
  * @file    stm32f4xx_hal_rtc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RTC HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32F4xx_HAL_RTC_EX_H
#define STM32F4xx_HAL_RTC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal_def.h"

/** @addtogroup STM32F4xx_HAL_Driver
  * @{
  */

/** @addtogroup RTCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup RTCEx_Exported_Types RTCEx Exported Types
  * @{
  */

/**
  * @brief  RTC Tamper structure definition
  */
typedef struct
{
  uint32_t Tamper;                      /*!< Specifies the Tamper Pin.
                                             This parameter can be a value of @ref RTCEx_Tamper_Pin_Definitions */

  uint32_t PinSelection;                /*!< Specifies the Tamper Pin.
                                             This parameter can be a value of @ref RTCEx_Tamper_Pin_Selection */

  uint32_t Trigger;                     /*!< Specifies the Tamper Trigger.
                                             This parameter can be a value of @ref RTCEx_Tamper_Trigger_Definitions */

  uint32_t Filter;                      /*!< Specifies the RTC Filter Tamper.
                                             This parameter can be a value of @ref RTCEx_Tamper_Filter_Definitions */

  uint32_t SamplingFrequency;           /*!< Specifies the sampling frequency.
                                             This parameter can be a value of @ref RTCEx_Tamper_Sampling_Frequencies_Definitions */

  uint32_t PrechargeDuration;           /*!< Specifies the Precharge Duration .
                                             This parameter can be a value of @ref RTCEx_Tamper_Pin_Precharge_Duration_Definitions */

  uint32_t TamperPullUp;                /*!< Specifies the Tamper PullUp .
                                             This parameter can be a value of @ref RTCEx_Tamper_Pull_Up_Definitions */

  uint32_t TimeStampOnTamperDetection;  /*!< Specifies the TimeStampOnTamperDetection.
                                             This parameter can be a value of @ref RTCEx_Tamper_TimeStampOnTamperDetection_Definitions */
} RTC_TamperTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup RTCEx_Exported_Constants RTCEx Exported Constants
  * @{
  */

/** @defgroup RTCEx_Backup_Registers_Definitions RTCEx Backup Registers Definitions
  * @{
  */
#define RTC_BKP_DR0                       0x00000000U
#define RTC_BKP_DR1                       0x00000001U
#define RTC_BKP_DR2                       0x00000002U
#define RTC_BKP_DR3                       0x00000003U
#define RTC_BKP_DR4                       0x00000004U
#define RTC_BKP_DR5                       0x00000005U
#define RTC_BKP_DR6                       0x00000006U
#define RTC_BKP_DR7                       0x00000007U
#define RTC_BKP_DR8                       0x00000008U
#define RTC_BKP_DR9                       0x00000009U
#define RTC_BKP_DR10                      0x0000000AU
#define RTC_BKP_DR11                      0x0000000BU
#define RTC_BKP_DR12                      0x0000000CU
#define RTC_BKP_DR13                      0x0000000DU
#define RTC_BKP_DR14                      0x0000000EU
#define RTC_BKP_DR15                      0x0000000FU
#define RTC_BKP_DR16                      0x00000010U
#define RTC_BKP_DR17                      0x00000011U
#define RTC_BKP_DR18                      0x00000012U
#define RTC_BKP_DR19                      0x00000013U
/**
  * @}
  */

/** @defgroup RTCEx_Timestamp_Edges_Definitions RTCEx Timestamp Edges Definitions
  * @{
  */
#define RTC_TIMESTAMPEDGE_RISING          0x00000000U
#define RTC_TIMESTAMPEDGE_FALLING         RTC_CR_TSEDGE
/**
  * @}
  */

/** @defgroup RTCEx_Timestamp_Pin_Selection RTC Timestamp Pin Selection
  * @{
  */
#define RTC_TIMESTAMPPIN_DEFAULT            0x00000000U
#if defined(RTC_AF2_SUPPORT)
#define RTC_TIMESTAMPPIN_POS1               RTC_TAFCR_TSINSEL
#endif /* RTC_AF2_SUPPORT */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pin_Definitions RTCEx Tamper Pins Definitions
  * @{
  */
#define RTC_TAMPER_1                    RTC_TAFCR_TAMP1E
#if defined(RTC_TAMPER2_SUPPORT)
#define RTC_TAMPER_2                    RTC_TAFCR_TAMP2E
#endif /* RTC_TAMPER2_SUPPORT */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pin_Selection RTC tamper Pins Selection
  * @{
  */
#define RTC_TAMPERPIN_DEFAULT               0x00000000U
#if defined(RTC_AF2_SUPPORT)
#define RTC_TAMPERPIN_POS1                  RTC_TAFCR_TAMP1INSEL
#endif /* RTC_AF2_SUPPORT */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Interrupt_Definitions RTCEx Tamper Interrupt Definitions
  * @{
  */
#define RTC_IT_TAMP                       RTC_TAFCR_TAMPIE   /*!< Enable global Tamper Interrupt           */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Trigger_Definitions RTCEx Tamper Triggers Definitions
  * @{
  */
#define RTC_TAMPERTRIGGER_RISINGEDGE       0x00000000U
#define RTC_TAMPERTRIGGER_FALLINGEDGE      RTC_TAFCR_TAMP1TRG
#define RTC_TAMPERTRIGGER_LOWLEVEL         RTC_TAMPERTRIGGER_RISINGEDGE
#define RTC_TAMPERTRIGGER_HIGHLEVEL        RTC_TAMPERTRIGGER_FALLINGEDGE
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Filter_Definitions RTCEx Tamper Filter Definitions
  * @{
  */
#define RTC_TAMPERFILTER_DISABLE   0x00000000U             /*!< Tamper filter is disabled */

#define RTC_TAMPERFILTER_2SAMPLE   RTC_TAFCR_TAMPFLT_0    /*!< Tamper is activated after 2
                                                                 consecutive samples at the active level */
#define RTC_TAMPERFILTER_4SAMPLE   RTC_TAFCR_TAMPFLT_1    /*!< Tamper is activated after 4
                                                                 consecutive samples at the active level */
#define RTC_TAMPERFILTER_8SAMPLE   RTC_TAFCR_TAMPFLT      /*!< Tamper is activated after 8
                                                                 consecutive samples at the active level */
#define RTC_TAMPERFILTER_MASK      RTC_TAFCR_TAMPFLT      /*!< Masking all bits except those of
                                                                 field TAMPFLT                           */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Sampling_Frequencies_Definitions RTCEx Tamper Sampling Frequencies Definitions
  * @{
  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768  0x00000000U                                     /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 32768 */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV16384  RTC_TAFCR_TAMPFREQ_0                           /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 16384 */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV8192   RTC_TAFCR_TAMPFREQ_1                           /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 8192  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV4096   (RTC_TAFCR_TAMPFREQ_0 | RTC_TAFCR_TAMPFREQ_1) /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 4096  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV2048   RTC_TAFCR_TAMPFREQ_2                           /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 2048  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV1024   (RTC_TAFCR_TAMPFREQ_0 | RTC_TAFCR_TAMPFREQ_2) /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 1024  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV512    (RTC_TAFCR_TAMPFREQ_1 | RTC_TAFCR_TAMPFREQ_2) /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 512   */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV256    RTC_TAFCR_TAMPFREQ                             /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 256   */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_MASK      RTC_TAFCR_TAMPFREQ                             /*!< Masking all bits except those of
                                                                                                      field TAMPFREQ                     */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pin_Precharge_Duration_Definitions RTCEx Tamper Pin Precharge Duration Definitions
  * @{
  */
#define RTC_TAMPERPRECHARGEDURATION_1RTCCLK     0x00000000U             /*!< Tamper pins are pre-charged before
                                                                              sampling during 1 RTCCLK cycle  */
#define RTC_TAMPERPRECHARGEDURATION_2RTCCLK     RTC_TAFCR_TAMPPRCH_0   /*!< Tamper pins are pre-charged before
                                                                              sampling during 2 RTCCLK cycles */
#define RTC_TAMPERPRECHARGEDURATION_4RTCCLK     RTC_TAFCR_TAMPPRCH_1   /*!< Tamper pins are pre-charged before
                                                                              sampling during 4 RTCCLK cycles */
#define RTC_TAMPERPRECHARGEDURATION_8RTCCLK     RTC_TAFCR_TAMPPRCH     /*!< Tamper pins are pre-charged before
                                                                              sampling during 8 RTCCLK cycles */
#define RTC_TAMPERPRECHARGEDURATION_MASK        RTC_TAFCR_TAMPPRCH     /*!< Masking all bits except those of
                                                                              field TAMPPRCH                  */
/**
  * @}
  */

/** @defgroup  RTCEx_Tamper_Pull_Up_Definitions RTCEx Tamper Pull Up Definitions
  * @{
  */
#define RTC_TAMPER_PULLUP_ENABLE  0x00000000U           /*!< Tamper pins are pre-charged before sampling     */
#define RTC_TAMPER_PULLUP_DISABLE RTC_TAFCR_TAMPPUDIS   /*!< Tamper pins are not pre-charged before sampling */
#define RTC_TAMPER_PULLUP_MASK    RTC_TAFCR_TAMPPUDIS   /*!< Masking all bits except bit TAMPPUDIS           */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_TimeStampOnTamperDetection_Definitions RTCEx Tamper TimeStamp On Tamper Detection Definitions
  * @{
  */
#define RTC_TIMESTAMPONTAMPERDETECTION_ENABLE  RTC_TAFCR_TAMPTS  /*!< TimeStamp on Tamper Detection event saved        */
#define RTC_TIMESTAMPONTAMPERDETECTION_DISABLE 0x00000000U       /*!< TimeStamp on Tamper Detection event is not saved */
#define RTC_TIMESTAMPONTAMPERDETECTION_MASK    RTC_TAFCR_TAMPTS  /*!< Masking all bits except bit TAMPTS               */
/**
  * @}
  */

/** @defgroup RTCEx_Wakeup_Timer_Definitions RTCEx Wakeup Timer Definitions
  * @{
  */
#define RTC_WAKEUPCLOCK_RTCCLK_DIV16        0x00000000U
#define RTC_WAKEUPCLOCK_RTCCLK_DIV8         RTC_CR_WUCKSEL_0
#define RTC_WAKEUPCLOCK_RTCCLK_DIV4         RTC_CR_WUCKSEL_1
#define RTC_WAKEUPCLOCK_RTCCLK_DIV2         (RTC_CR_WUCKSEL_0 | RTC_CR_WUCKSEL_1)
#define RTC_WAKEUPCLOCK_CK_SPRE_16BITS      RTC_CR_WUCKSEL_2
#define RTC_WAKEUPCLOCK_CK_SPRE_17BITS      (RTC_CR_WUCKSEL_1 | RTC_CR_WUCKSEL_2)
/**
  * @}
  */

/** @defgroup RTCEx_Coarse_Calibration_Definitions RTCEx Coarse Calib Definitions
  * @{
  */
#define RTC_CALIBSIGN_POSITIVE            0x00000000U
#define RTC_CALIBSIGN_NEGATIVE            RTC_CALIBR_DCS
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_period_Definitions RTCEx Smooth Calib Period Definitions
  * @{
  */
#define RTC_SMOOTHCALIB_PERIOD_32SEC   0x00000000U      /*!< If RTCCLK = 32768 Hz, smooth calibration
                                                              period is 32s, otherwise 2^20 RTCCLK pulses */
#define RTC_SMOOTHCALIB_PERIOD_16SEC   RTC_CALR_CALW16  /*!< If RTCCLK = 32768 Hz, smooth calibration
                                                              period is 16s, otherwise 2^19 RTCCLK pulses */
#define RTC_SMOOTHCALIB_PERIOD_8SEC    RTC_CALR_CALW8   /*!< If RTCCLK = 32768 Hz, smooth calibration
                                                              period is 8s, otherwise 2^18 RTCCLK pulses  */
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_Plus_pulses_Definitions RTCEx Smooth Calib Plus Pulses Definitions
  * @{
  */
#define RTC_SMOOTHCALIB_PLUSPULSES_SET    RTC_CALR_CALP           /*!< The number of RTCCLK pulses added
                                                                        during a X -second window = Y - CALM[8:0]
                                                                        with Y = 512, 256, 128 when X = 32, 16, 8 */
#define RTC_SMOOTHCALIB_PLUSPULSES_RESET  0x00000000U             /*!< The number of RTCCLK pulses subbstited
                                                                        during a 32-second window = CALM[8:0] */
/**
  * @}
  */

/** @defgroup RTCEx_Add_1_Second_Parameter_Definitions RTCEx Add 1 Second Parameter Definitions
  * @{
  */
#define RTC_SHIFTADD1S_RESET      0x00000000U
#define RTC_SHIFTADD1S_SET        RTC_SHIFTR_ADD1S
/**
  * @}
  */

/** @defgroup RTCEx_Calib_Output_selection_Definitions RTCEx Calib Output Selection Definitions
  * @{
  */
#define RTC_CALIBOUTPUT_512HZ            0x00000000U
#define RTC_CALIBOUTPUT_1HZ              RTC_CR_COSEL
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup RTCEx_Exported_Macros RTCEx Exported Macros
  * @{
  */

/* ---------------------------------WAKEUPTIMER-------------------------------*/

/** @defgroup RTCEx_WakeUp_Timer RTCEx WakeUp Timer
  * @{
  */

/**
  * @brief  Enable the RTC WakeUp Timer peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_ENABLE(__HANDLE__)                      ((__HANDLE__)->Instance->CR |= (RTC_CR_WUTE))

/**
  * @brief  Disable the RTC Wakeup Timer peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_DISABLE(__HANDLE__)                     ((__HANDLE__)->Instance->CR &= ~(RTC_CR_WUTE))

/**
  * @brief  Enable the RTC Wakeup Timer interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Wakeup Timer interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_WUT: Wakeup Timer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_ENABLE_IT(__HANDLE__, __INTERRUPT__)    ((__HANDLE__)->Instance->CR |= (__INTERRUPT__))

/**
  * @brief  Disable the RTC Wakeup Timer interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Wakeup Timer interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_WUT: Wakeup Timer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_DISABLE_IT(__HANDLE__, __INTERRUPT__)   ((__HANDLE__)->Instance->CR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC Wakeup Timer interrupt has occurred or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Wakeup Timer interrupt to check.
  *         This parameter can be:
  *            @arg RTC_IT_WUT: Wakeup Timer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_IT(__HANDLE__, __INTERRUPT__)          (((((__HANDLE__)->Instance->ISR) & ((__INTERRUPT__) >> 4U)) != 0U) ? 1U : 0U)

/**
  * @brief  Check whether the specified RTC Wakeup timer interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Wakeup timer interrupt sources to check.
  *         This parameter can be:
  *            @arg RTC_IT_WUT: WakeUpTimer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)   (((((__HANDLE__)->Instance->CR) & (__INTERRUPT__)) != 0U) ? 1U : 0U)

/**
  * @brief  Get the selected RTC Wakeup Timer's flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Wakeup Timer flag to check.
  *          This parameter can be:
  *             @arg RTC_FLAG_WUTF: Wakeup Timer interrupt flag
  *             @arg RTC_FLAG_WUTWF: Wakeup Timer 'write allowed' flag
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_FLAG(__HANDLE__, __FLAG__)          (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) != 0U)? 1U : 0U)

/**
  * @brief  Clear the RTC Wakeup timer's pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Wakeup Timer Flag to clear.
  *         This parameter can be:
  *             @arg RTC_FLAG_WUTF: Wakeup Timer interrupt Flag
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(__HANDLE__, __FLAG__)            ((__HANDLE__)->Instance->ISR) = (~((__FLAG__) | RTC_ISR_INIT)|((__HANDLE__)->Instance->ISR & RTC_ISR_INIT))

/**
  * @brief  Enable interrupt on the RTC Wakeup Timer associated EXTI line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT()       (EXTI->IMR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable interrupt on the RTC Wakeup Timer associated EXTI line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_IT()      (EXTI->IMR &= ~RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Enable event on the RTC Wakeup Timer associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_EVENT()    (EXTI->EMR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable event on the RTC Wakeup Timer associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_EVENT()   (EXTI->EMR &= ~RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Enable falling edge trigger on the RTC Wakeup Timer associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_FALLING_EDGE()   (EXTI->FTSR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable falling edge trigger on the RTC Wakeup Timer associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_FALLING_EDGE()  (EXTI->FTSR &= ~RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Enable rising edge trigger on the RTC Wakeup Timer associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE()    (EXTI->RTSR |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable rising edge trigger on the RTC Wakeup Timer associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_RISING_EDGE()   (EXTI->RTSR &= ~RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Enable rising & falling edge trigger on the RTC Wakeup Timer associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_FALLING_EDGE() do {                                                   \
                                                                     __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_RISING_EDGE();  \
                                                                     __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_FALLING_EDGE(); \
                                                                   } while(0U)

/**
  * @brief  Disable rising & falling edge trigger on the RTC Wakeup Timer associated EXTI line.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_RISING_FALLING_EDGE() do {                                                    \
                                                                      __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_RISING_EDGE();  \
                                                                      __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_FALLING_EDGE(); \
                                                                    } while(0U)

/**
  * @brief Check whether the RTC Wakeup Timer associated EXTI line interrupt flag is set or not.
  * @retval Line Status.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_GET_FLAG()              (EXTI->PR & RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief Clear the RTC Wakeup Timer associated EXTI line flag.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG()            (EXTI->PR = RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief Generate a Software interrupt on the RTC Wakeup Timer associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_GENERATE_SWIT()         (EXTI->SWIER |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @}
  */

/* ---------------------------------TIMESTAMP---------------------------------*/

/** @defgroup RTCEx_Timestamp RTCEx Timestamp
  * @{
  */

/**
  * @brief  Enable the RTC Timestamp peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_ENABLE(__HANDLE__)                        ((__HANDLE__)->Instance->CR |= (RTC_CR_TSE))

/**
  * @brief  Disable the RTC Timestamp peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_DISABLE(__HANDLE__)                       ((__HANDLE__)->Instance->CR &= ~(RTC_CR_TSE))

/**
  * @brief  Enable the RTC Timestamp interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Timestamp interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_TS: TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_ENABLE_IT(__HANDLE__, __INTERRUPT__)      ((__HANDLE__)->Instance->CR |= (__INTERRUPT__))

/**
  * @brief  Disable the RTC Timestamp interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Timestamp interrupt sources to be enabled or disabled.
  *         This parameter can be:
  *            @arg RTC_IT_TS: TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_DISABLE_IT(__HANDLE__, __INTERRUPT__)     ((__HANDLE__)->Instance->CR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC Timestamp interrupt has occurred or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Timestamp interrupt to check.
  *         This parameter can be:
  *            @arg RTC_IT_TS: TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_IT(__HANDLE__, __INTERRUPT__)         (((((__HANDLE__)->Instance->ISR) & ((__INTERRUPT__) >> 4U)) != 0U) ? 1U : 0U)

/**
  * @brief  Check whether the specified RTC Timestamp interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Timestamp interrupt source to check.
  *         This parameter can be:
  *            @arg RTC_IT_TS: TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)     (((((__HANDLE__)->Instance->CR) & (__INTERRUPT__)) != 0U) ? 1U : 0U)

/**
  * @brief  Get the selected RTC Timestamp's flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Timestamp flag to check.
  *         This parameter can be:
  *            @arg RTC_FLAG_TSF: Timestamp interrupt flag
  *            @arg RTC_FLAG_TSOVF: Timestamp overflow flag
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_FLAG(__HANDLE__, __FLAG__)            (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) != 0U)? 1U : 0U)

/**
  * @brief  Clear the RTC Timestamp's pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Timestamp flag to clear.
  *         This parameter can be:
  *            @arg RTC_FLAG_TSF: Timestamp interrupt flag
  *            @arg RTC_FLAG_TSOVF: Timestamp overflow flag
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_CLEAR_FLAG(__HANDLE__, __FLAG__)          ((__HANDLE__)->Instance->ISR) = (~((__FLAG__) | RTC_ISR_INIT)|((__HANDLE__)->Instance->ISR & RTC_ISR_INIT))

/**
  * @}
  */

/* ---------------------------------TAMPER------------------------------------*/

/** @defgroup RTCEx_Tamper RTCEx Tamper
  * @{
  */

/**
  * @brief  Enable the RTC Tamper1 input detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TAMPER1_ENABLE(__HANDLE__)                         ((__HANDLE__)->Instance->TAFCR |= (RTC_TAFCR_TAMP1E))

/**
  * @brief  Disable the RTC Tamper1 input detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TAMPER1_DISABLE(__HANDLE__)                        ((__HANDLE__)->Instance->TAFCR &= ~(RTC_TAFCR_TAMP1E))

#if defined(RTC_TAMPER2_SUPPORT)
/**
  * @brief  Enable the RTC Tamper2 input detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TAMPER2_ENABLE(__HANDLE__)                         ((__HANDLE__)->Instance->TAFCR |= (RTC_TAFCR_TAMP2E))

/**
  * @brief  Disable the RTC Tamper2 input detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TAMPER2_DISABLE(__HANDLE__)                        ((__HANDLE__)->Instance->TAFCR &= ~(RTC_TAFCR_TAMP2E))
#endif /* RTC_TAMPER2_SUPPORT */

/**
  * @brief  Enable the RTC Tamper interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *            @arg RTC_IT_TAMP: Tamper global interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_ENABLE_IT(__HANDLE__, __INTERRUPT__)        ((__HANDLE__)->Instance->TAFCR |= (__INTERRUPT__))

/**
  * @brief  Disable the RTC Tamper interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg RTC_IT_TAMP: Tamper global interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_DISABLE_IT(__HANDLE__, __INTERRUPT__)       ((__HANDLE__)->Instance->TAFCR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC Tamper interrupt has occurred or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt to check.
  *         This parameter can be:
  *            @arg RTC_IT_TAMP1: Tamper 1 interrupt
  *            @arg RTC_IT_TAMP2: Tamper 2 interrupt
  * @note   RTC_IT_TAMP2 is not applicable to all devices.
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT(__HANDLE__, __INTERRUPT__)       (((((__HANDLE__)->Instance->ISR) & ((__INTERRUPT__) >> 4U)) != 0U) ? 1U : 0U)

/**
  * @brief  Check whether the specified RTC Tamper interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt source to check.
  *         This parameter can be:
  *            @arg RTC_IT_TAMP: Tamper global interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)     (((((__HANDLE__)->Instance->TAFCR) & (__INTERRUPT__)) != 0U) ? 1U : 0U)

/**
  * @brief  Get the selected RTC Tamper's flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Tamper flag to be checked.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP1F: Tamper 1 interrupt flag
  *             @arg RTC_FLAG_TAMP2F: Tamper 2 interrupt flag
  * @note   RTC_FLAG_TAMP2F is not applicable to all devices.
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_FLAG(__HANDLE__, __FLAG__)               (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) != 0U)? 1U : 0U)

/**
  * @brief  Clear the RTC Tamper's pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Tamper Flag to clear.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP1F: Tamper 1 interrupt flag
  *             @arg RTC_FLAG_TAMP2F: Tamper 2 interrupt flag
  * @note   RTC_FLAG_TAMP2F is not applicable to all devices.
  * @retval None
  */
#define __HAL_RTC_TAMPER_CLEAR_FLAG(__HANDLE__, __FLAG__)         ((__HANDLE__)->Instance->ISR) = (~((__FLAG__) | RTC_ISR_INIT)|((__HANDLE__)->Instance->ISR & RTC_ISR_INIT))
/**
  * @}
  */

/* --------------------------TAMPER/TIMESTAMP---------------------------------*/
/** @defgroup RTCEx_Tamper_Timestamp EXTI RTC Tamper Timestamp EXTI
  * @{
  */

/**
  * @brief  Enable interrupt on the RTC Tamper and Timestamp associated EXTI line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_IT()        (EXTI->IMR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Disable interrupt on the RTC Tamper and Timestamp associated EXTI line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_IT()       (EXTI->IMR &= ~RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Enable event on the RTC Tamper and Timestamp associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_EVENT()    (EXTI->EMR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Disable event on the RTC Tamper and Timestamp associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_EVENT()   (EXTI->EMR &= ~RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Enable falling edge trigger on the RTC Tamper and Timestamp associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_FALLING_EDGE()   (EXTI->FTSR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Disable falling edge trigger on the RTC Tamper and Timestamp associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_FALLING_EDGE()  (EXTI->FTSR &= ~RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Enable rising edge trigger on the RTC Tamper and Timestamp associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_RISING_EDGE()    (EXTI->RTSR |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Disable rising edge trigger on the RTC Tamper and Timestamp associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_RISING_EDGE()   (EXTI->RTSR &= ~RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief  Enable rising & falling edge trigger on the RTC Tamper and Timestamp associated EXTI line.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_RISING_FALLING_EDGE() do {                                                        \
                                                                          __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_RISING_EDGE();  \
                                                                          __HAL_RTC_TAMPER_TIMESTAMP_EXTI_ENABLE_FALLING_EDGE(); \
                                                                        } while(0U)

/**
  * @brief  Disable rising & falling edge trigger on the RTC Tamper and Timestamp associated EXTI line.
  * This parameter can be:
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_RISING_FALLING_EDGE() do {                                                         \
                                                                           __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_RISING_EDGE();  \
                                                                           __HAL_RTC_TAMPER_TIMESTAMP_EXTI_DISABLE_FALLING_EDGE(); \
                                                                         } while(0U)

/**
  * @brief Check whether the RTC Tamper and Timestamp associated EXTI line interrupt flag is set or not.
  * @retval Line Status.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_GET_FLAG()         (EXTI->PR & RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief Clear the RTC Tamper and Timestamp associated EXTI line flag.
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_CLEAR_FLAG()       (EXTI->PR = RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)

/**
  * @brief Generate a Software interrupt on the RTC Tamper and Timestamp associated EXTI line
  * @retval None.
  */
#define __HAL_RTC_TAMPER_TIMESTAMP_EXTI_GENERATE_SWIT()    (EXTI->SWIER |= RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT)
/**
  * @}
  */

/* ------------------------------CALIBRATION----------------------------------*/

/** @defgroup RTCEx_Calibration RTCEx Calibration
  * @{
  */

/**
  * @brief  Enable the Coarse calibration process.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_COARSE_CALIB_ENABLE(__HANDLE__)                       ((__HANDLE__)->Instance->CR |= (RTC_CR_DCE))

/**
  * @brief  Disable the Coarse calibration process.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_COARSE_CALIB_DISABLE(__HANDLE__)                      ((__HANDLE__)->Instance->CR &= ~(RTC_CR_DCE))

/**
  * @brief  Enable the RTC calibration output.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CALIBRATION_OUTPUT_ENABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR |= (RTC_CR_COE))

/**
  * @brief  Disable the calibration output.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CALIBRATION_OUTPUT_DISABLE(__HANDLE__)                ((__HANDLE__)->Instance->CR &= ~(RTC_CR_COE))

/**
  * @brief  Enable the clock reference detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CLOCKREF_DETECTION_ENABLE(__HANDLE__)                 ((__HANDLE__)->Instance->CR |= (RTC_CR_REFCKON))

/**
  * @brief  Disable the clock reference detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CLOCKREF_DETECTION_DISABLE(__HANDLE__)                ((__HANDLE__)->Instance->CR &= ~(RTC_CR_REFCKON))

/**
  * @brief  Get the selected RTC shift operation's flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC shift operation Flag is pending or not.
  *          This parameter can be:
  *             @arg RTC_FLAG_SHPF: Shift pending flag
  * @retval None
  */
#define __HAL_RTC_SHIFT_GET_FLAG(__HANDLE__, __FLAG__)                (((((__HANDLE__)->Instance->ISR) & (__FLAG__)) != 0U)? 1U : 0U)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup RTCEx_Exported_Functions RTCEx Exported Functions
  * @{
  */

/** @addtogroup RTCEx_Exported_Functions_Group1
  * @{
  */
/* RTC Timestamp and Tamper functions *****************************************/
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp(RTC_HandleTypeDef *hrtc, uint32_t RTC_TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp_IT(RTC_HandleTypeDef *hrtc, uint32_t RTC_TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_GetTimeStamp(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTimeStamp, RTC_DateTypeDef *sTimeStampDate, uint32_t Format);

HAL_StatusTypeDef HAL_RTCEx_SetTamper(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef *sTamper);
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef *sTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(RTC_HandleTypeDef *hrtc, uint32_t Tamper);
void              HAL_RTCEx_TamperTimeStampIRQHandler(RTC_HandleTypeDef *hrtc);

void              HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc);
#if defined(RTC_TAMPER2_SUPPORT)
void              HAL_RTCEx_Tamper2EventCallback(RTC_HandleTypeDef *hrtc);
#endif /* RTC_TAMPER2_SUPPORT */
void              HAL_RTCEx_TimeStampEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForTimeStampEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_PollForTamper1Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
#if defined(RTC_TAMPER2_SUPPORT)
HAL_StatusTypeDef HAL_RTCEx_PollForTamper2Event(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
#endif /* RTC_TAMPER2_SUPPORT */
/**
  * @}
  */

/** @addtogroup RTCEx_Exported_Functions_Group2
  * @{
  */
/* RTC Wakeup functions ******************************************************/
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock);
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer_IT(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock);
HAL_StatusTypeDef HAL_RTCEx_DeactivateWakeUpTimer(RTC_HandleTypeDef *hrtc);
uint32_t          HAL_RTCEx_GetWakeUpTimer(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_WakeUpTimerIRQHandler(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForWakeUpTimerEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
/**
  * @}
  */

/** @addtogroup RTCEx_Exported_Functions_Group3
  * @{
  */
/* Extended Control functions ************************************************/
void              HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data);
uint32_t          HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister);

HAL_StatusTypeDef HAL_RTCEx_SetCoarseCalib(RTC_HandleTypeDef *hrtc, uint32_t CalibSign, uint32_t Value);
HAL_StatusTypeDef HAL_RTCEx_DeactivateCoarseCalib(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef *hrtc, uint32_t SmoothCalibPeriod, uint32_t SmoothCalibPlusPulses, uint32_t SmoothCalibMinusPulsesValue);
HAL_StatusTypeDef HAL_RTCEx_SetSynchroShift(RTC_HandleTypeDef *hrtc, uint32_t ShiftAdd1S, uint32_t ShiftSubFS);
HAL_StatusTypeDef HAL_RTCEx_SetCalibrationOutPut(RTC_HandleTypeDef *hrtc, uint32_t CalibOutput);
HAL_StatusTypeDef HAL_RTCEx_DeactivateCalibrationOutPut(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_SetRefClock(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateRefClock(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_EnableBypassShadow(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DisableBypassShadow(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */

/** @addtogroup RTCEx_Exported_Functions_Group4
  * @{
  */
/* Extended RTC features functions *******************************************/
void HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForAlarmBEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
/**
  * @}
  */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/

/** @defgroup RTCEx_Private_Constants RTCEx Private Constants
  * @{
  */
#define RTC_EXTI_LINE_TAMPER_TIMESTAMP_EVENT  EXTI_IMR_MR21  /*!< External interrupt line 21 Connected to the RTC Tamper and Timestamp event */
#define RTC_EXTI_LINE_WAKEUPTIMER_EVENT       EXTI_IMR_MR22  /*!< External interrupt line 22 Connected to the RTC Wakeup event */
/**
  * @}
  */

/** @defgroup RTCEx_Private_Constants RTCEx Private Constants
  * @{
  */
/* Masks Definition */
#if defined(RTC_TAMPER2_SUPPORT)
#define RTC_TAMPER_ENABLE_BITS_MASK         ((uint32_t) (RTC_TAMPER_1 | \
                                                         RTC_TAMPER_2))

#define RTC_TAMPER_FLAGS_MASK               ((uint32_t) (RTC_FLAG_TAMP1F | \
                                                         RTC_FLAG_TAMP2F))
#else /* RTC_TAMPER2_SUPPORT */
#define RTC_TAMPER_ENABLE_BITS_MASK                      RTC_TAMPER_1

#define RTC_TAMPER_FLAGS_MASK                            RTC_FLAG_TAMP1F
#endif /* RTC_TAMPER2_SUPPORT */
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup RTCEx_Private_Macros RTCEx Private Macros
  * @{
  */

/** @defgroup RTCEx_IS_RTC_Definitions Private macros to check input parameters
  * @{
  */
#define IS_RTC_BKP(BKP)     ((BKP) < (uint32_t) RTC_BKP_NUMBER)

#define IS_TIMESTAMP_EDGE(EDGE) (((EDGE) == RTC_TIMESTAMPEDGE_RISING) || \
                                 ((EDGE) == RTC_TIMESTAMPEDGE_FALLING))

#define IS_RTC_TAMPER(TAMPER) ((((TAMPER) & ((uint32_t)~RTC_TAMPER_ENABLE_BITS_MASK)) == 0x00U) && ((TAMPER) != 0U))

#if defined(RTC_AF2_SUPPORT)
#define IS_RTC_TAMPER_PIN(PIN) (((PIN) == RTC_TAMPERPIN_DEFAULT) || \
                                ((PIN) == RTC_TAMPERPIN_POS1))
#else /* RTC_AF2_SUPPORT */
#define IS_RTC_TAMPER_PIN(PIN) ((PIN) == RTC_TAMPERPIN_DEFAULT)
#endif /* RTC_AF2_SUPPORT */

#if defined(RTC_AF2_SUPPORT)
#define IS_RTC_TIMESTAMP_PIN(PIN) (((PIN) == RTC_TIMESTAMPPIN_DEFAULT) || \
                                   ((PIN) == RTC_TIMESTAMPPIN_POS1))
#else /* RTC_AF2_SUPPORT */
#define IS_RTC_TIMESTAMP_PIN(PIN) ((PIN) == RTC_TIMESTAMPPIN_DEFAULT)
#endif /* RTC_AF2_SUPPORT */

#define IS_RTC_TAMPER_TRIGGER(TRIGGER) (((TRIGGER) == RTC_TAMPERTRIGGER_RISINGEDGE)  || \
                                        ((TRIGGER) == RTC_TAMPERTRIGGER_FALLINGEDGE) || \
                                        ((TRIGGER) == RTC_TAMPERTRIGGER_LOWLEVEL)    || \
                                        ((TRIGGER) == RTC_TAMPERTRIGGER_HIGHLEVEL))

#define IS_RTC_TAMPER_FILTER(FILTER)  (((FILTER) == RTC_TAMPERFILTER_DISABLE) || \
                                       ((FILTER) == RTC_TAMPERFILTER_2SAMPLE) || \
                                       ((FILTER) == RTC_TAMPERFILTER_4SAMPLE) || \
                                       ((FILTER) == RTC_TAMPERFILTER_8SAMPLE))

#define IS_RTC_TAMPER_FILTER_CONFIG_CORRECT(FILTER, TRIGGER)                  \
                        (  (  ((FILTER) != RTC_TAMPERFILTER_DISABLE)          \
                           && (  ((TRIGGER) == RTC_TAMPERTRIGGER_LOWLEVEL)    \
                              || ((TRIGGER) == RTC_TAMPERTRIGGER_HIGHLEVEL))) \
                        || (  ((FILTER) == RTC_TAMPERFILTER_DISABLE)          \
                           && (  ((TRIGGER) == RTC_TAMPERTRIGGER_RISINGEDGE)  \
                              || ((TRIGGER) == RTC_TAMPERTRIGGER_FALLINGEDGE))))

#define IS_RTC_TAMPER_SAMPLING_FREQ(FREQ) (((FREQ) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768)|| \
                                           ((FREQ) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV16384)|| \
                                           ((FREQ) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV8192) || \
                                           ((FREQ) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV4096) || \
                                           ((FREQ) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV2048) || \
                                           ((FREQ) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV1024) || \
                                           ((FREQ) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV512)  || \
                                           ((FREQ) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV256))

#define IS_RTC_TAMPER_PRECHARGE_DURATION(DURATION) (((DURATION) == RTC_TAMPERPRECHARGEDURATION_1RTCCLK) || \
                                                    ((DURATION) == RTC_TAMPERPRECHARGEDURATION_2RTCCLK) || \
                                                    ((DURATION) == RTC_TAMPERPRECHARGEDURATION_4RTCCLK) || \
                                                    ((DURATION) == RTC_TAMPERPRECHARGEDURATION_8RTCCLK))

#define IS_RTC_TAMPER_PULLUP_STATE(STATE) (((STATE) == RTC_TAMPER_PULLUP_ENABLE) || \
                                           ((STATE) == RTC_TAMPER_PULLUP_DISABLE))

#define IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(DETECTION) (((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_ENABLE) || \
                                                              ((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_DISABLE))

#define IS_RTC_WAKEUP_CLOCK(CLOCK) (((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV16)   || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV8)    || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV4)    || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV2)    || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_CK_SPRE_16BITS) || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_CK_SPRE_17BITS))

#define IS_RTC_WAKEUP_COUNTER(COUNTER)  ((COUNTER) <= RTC_WUTR_WUT)

#define IS_RTC_CALIB_SIGN(SIGN) (((SIGN) == RTC_CALIBSIGN_POSITIVE) || \
                                 ((SIGN) == RTC_CALIBSIGN_NEGATIVE))

#define IS_RTC_CALIB_VALUE(VALUE) ((VALUE) < 0x20U)

#define IS_RTC_SMOOTH_CALIB_PERIOD(PERIOD) (((PERIOD) == RTC_SMOOTHCALIB_PERIOD_32SEC) || \
                                            ((PERIOD) == RTC_SMOOTHCALIB_PERIOD_16SEC) || \
                                            ((PERIOD) == RTC_SMOOTHCALIB_PERIOD_8SEC))

#define IS_RTC_SMOOTH_CALIB_PLUS(PLUS) (((PLUS) == RTC_SMOOTHCALIB_PLUSPULSES_SET) || \
                                        ((PLUS) == RTC_SMOOTHCALIB_PLUSPULSES_RESET))

#define  IS_RTC_SMOOTH_CALIB_MINUS(VALUE) ((VALUE) <= RTC_CALR_CALM)

#define IS_RTC_SHIFT_ADD1S(SEL) (((SEL) == RTC_SHIFTADD1S_RESET) || \
                                 ((SEL) == RTC_SHIFTADD1S_SET))

#define IS_RTC_SHIFT_SUBFS(FS) ((FS) <= RTC_SHIFTR_SUBFS)

#define IS_RTC_CALIB_OUTPUT(OUTPUT)  (((OUTPUT) == RTC_CALIBOUTPUT_512HZ) || \
                                      ((OUTPUT) == RTC_CALIBOUTPUT_1HZ))
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

#endif /* STM32F4xx_HAL_RTC_EX_H */
