/**
  ******************************************************************************
  * @file    stm32g4xx_hal_rtc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RTC HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2019 STMicroelectronics</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32G4xx_HAL_RTC_EX_H
#define STM32G4xx_HAL_RTC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g4xx_hal_def.h"

/** @addtogroup STM32G4xx_HAL_Driver
  * @{
  */

/** @defgroup RTCEx RTCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup RTCEx_Exported_Types RTCEx Exported Types
  * @{
  */

/** @defgroup RTCEx_Tamper_structure_definition RTCEx Tamper structure definition
  * @{
  */
typedef struct
{
  uint32_t Tamper;                      /*!< Specifies the Tamper Pin.
                                             This parameter can be a value of @ref RTCEx_Tamper_Pins */

  uint32_t Trigger;                     /*!< Specifies the Tamper Trigger.
                                             This parameter can be a value of @ref RTCEx_Tamper_Trigger */

  uint32_t NoErase;                     /*!< Specifies the Tamper no erase mode.
                                             This parameter can be a value of @ref RTCEx_Tamper_EraseBackUp */

  uint32_t MaskFlag;                    /*!< Specifies the Tamper Flag masking.
                                             This parameter can be a value of @ref RTCEx_Tamper_MaskFlag */

  uint32_t Filter;                      /*!< Specifies the TAMP Filter Tamper.
                                             This parameter can be a value of @ref RTCEx_Tamper_Filter */

  uint32_t SamplingFrequency;           /*!< Specifies the sampling frequency.
                                             This parameter can be a value of @ref RTCEx_Tamper_Sampling_Frequencies */

  uint32_t PrechargeDuration;           /*!< Specifies the Precharge Duration .
                                             This parameter can be a value of @ref RTCEx_Tamper_Pin_Precharge_Duration */

  uint32_t TamperPullUp;                /*!< Specifies the Tamper PullUp .
                                             This parameter can be a value of @ref RTCEx_Tamper_Pull_UP */

  uint32_t TimeStampOnTamperDetection;  /*!< Specifies the TimeStampOnTamperDetection.
                                             This parameter can be a value of @ref RTCEx_Tamper_TimeStampOnTamperDetection */
} RTC_TamperTypeDef;
/**
  * @}
  */


/** @defgroup RTCEx_Internal_Tamper_structure_definition RTCEx Internal Tamper structure definition
  * @{
  */
typedef struct
{
  uint32_t IntTamper;                   /*!< Specifies the Internal Tamper Pin.
                                             This parameter can be a value of @ref RTCEx_Internal_Tamper_Pins */

  uint32_t TimeStampOnTamperDetection;  /*!< Specifies the TimeStampOnTamperDetection.
                                             This parameter can be a value of @ref RTCEx_Tamper_TimeStampOnTamperDetection */
} RTC_InternalTamperTypeDef;
/**
  * @}
  */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup RTCEx_Exported_Constants RTCEx Exported Constants
  * @{
  */

/** @defgroup RTCEx_Time_Stamp_Edges_definitions RTCEx Time Stamp Edges definition
  * @{
  */
#define RTC_TIMESTAMPEDGE_RISING        0x00000000U
#define RTC_TIMESTAMPEDGE_FALLING       RTC_CR_TSEDGE
/**
  * @}
  */

/** @defgroup RTCEx_TimeStamp_Pin_Selections RTCEx TimeStamp Pin Selection
  * @{
  */
#define RTC_TIMESTAMPPIN_DEFAULT            0x00000000U
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

/** @defgroup RTCEx_Smooth_calib_period_Definitions RTCEx Smooth calib period Definitions
  * @{
  */
#define RTC_SMOOTHCALIB_PERIOD_32SEC   0x00000000U              /*!< If RTCCLK = 32768 Hz, Smooth calibration
                                                                     period is 32s,  else 2exp20 RTCCLK pulses */
#define RTC_SMOOTHCALIB_PERIOD_16SEC   RTC_CALR_CALW16          /*!< If RTCCLK = 32768 Hz, Smooth calibration
                                                                     period is 16s, else 2exp19 RTCCLK pulses */
#define RTC_SMOOTHCALIB_PERIOD_8SEC    RTC_CALR_CALW8           /*!< If RTCCLK = 32768 Hz, Smooth calibration
                                                                     period is 8s, else 2exp18 RTCCLK pulses */
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_Plus_pulses_Definitions RTCEx Smooth calib Plus pulses Definitions
  * @{
  */
#define RTC_SMOOTHCALIB_PLUSPULSES_SET    RTC_CALR_CALP         /*!< The number of RTCCLK pulses added
                                                                     during a X -second window = Y - CALM[8:0]
                                                                     with Y = 512, 256, 128 when X = 32, 16, 8 */
#define RTC_SMOOTHCALIB_PLUSPULSES_RESET  0x00000000U           /*!< The number of RTCCLK pulses subbstited
                                                                     during a 32-second window = CALM[8:0] */

/**
  * @}
  */

/** @defgroup RTCEx_Calib_Output_selection_Definitions RTCEx Calib Output selection Definitions
  * @{
  */
#define RTC_CALIBOUTPUT_512HZ            0x00000000U
#define RTC_CALIBOUTPUT_1HZ              RTC_CR_COSEL

/**
  * @}
  */


/** @defgroup RTCEx_Add_1_Second_Parameter_Definition RTCEx Add 1 Second Parameter Definitions
  * @{
  */
#define RTC_SHIFTADD1S_RESET      0x00000000U
#define RTC_SHIFTADD1S_SET        RTC_SHIFTR_ADD1S
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pins  RTCEx Tamper Pins Definition
  * @{
  */
#define RTC_TAMPER_1                        TAMP_CR1_TAMP1E
#define RTC_TAMPER_2                        TAMP_CR1_TAMP2E
#if (RTC_TAMP_NB == 3)
#define RTC_TAMPER_3                        TAMP_CR1_TAMP3E
#define RTC_TAMPER_ALL                      (RTC_TAMPER_1 | RTC_TAMPER_2 | RTC_TAMPER_3 )
#elif (RTC_TAMP_NB == 8)
#define RTC_TAMPER_3                        TAMP_CR1_TAMP3E
#define RTC_TAMPER_4                        TAMP_CR1_TAMP4E
#define RTC_TAMPER_5                        TAMP_CR1_TAMP5E
#define RTC_TAMPER_6                        TAMP_CR1_TAMP6E
#define RTC_TAMPER_7                        TAMP_CR1_TAMP7E
#define RTC_TAMPER_8                        TAMP_CR1_TAMP8E
#define RTC_TAMPER_ALL                      (RTC_TAMPER_1 | RTC_TAMPER_2 |\
                                             RTC_TAMPER_3 | RTC_TAMPER_4 |\
                                             RTC_TAMPER_5 | RTC_TAMPER_6 |\
                                             RTC_TAMPER_7 | RTC_TAMPER_8 )
#else
#define RTC_TAMPER_ALL                      (RTC_TAMPER_1 | RTC_TAMPER_2)
#endif /* RTC_TAMP_NB */
/**
  * @}
  */

/** @defgroup RTCEx_Internal_Tamper_Pins  RTCEx Internal Tamper Pins Definition
  * @{
  */
#if defined  (RTC_TAMP_INT_1_SUPPORT)
#define RTC_INT_TAMPER_1                    TAMP_CR1_ITAMP1E
#else
#define RTC_INT_TAMPER_1                    0U
#endif /* RTC_TAMP_INT_1_SUPPORT */
#if defined (RTC_TAMP_INT_2_SUPPORT)
#define RTC_INT_TAMPER_2                    TAMP_CR1_ITAMP2E
#else
#define RTC_INT_TAMPER_2                    0U
#endif /* RTC_TAMP_INT_2_SUPPORT */
#define RTC_INT_TAMPER_3                    TAMP_CR1_ITAMP3E
#define RTC_INT_TAMPER_4                    TAMP_CR1_ITAMP4E
#define RTC_INT_TAMPER_5                    TAMP_CR1_ITAMP5E
#if defined (RTC_TAMP_INT_6_SUPPORT)
#define RTC_INT_TAMPER_6                    TAMP_CR1_ITAMP6E
#else
#define RTC_INT_TAMPER_6                    0U
#endif /* RTC_TAMP_INT_6_SUPPORT */
#if defined (RTC_TAMP_INT_7_SUPPORT)
#define RTC_INT_TAMPER_7                    TAMP_CR1_ITAMP7E
#else
#define RTC_INT_TAMPER_7                    0U
#endif /* RTC_TAMP_INT_7_SUPPORT */
#if defined (RTC_TAMP_INT_8_SUPPORT)
#define RTC_INT_TAMPER_8                    TAMP_CR1_ITAMP8E
#else
#define RTC_INT_TAMPER_8                    0U
#endif /* RTC_TAMP_INT_8_SUPPORT */

#define RTC_INT_TAMPER_ALL              ( RTC_INT_TAMPER_1 | RTC_INT_TAMPER_2 |\
                                          RTC_INT_TAMPER_3 | RTC_INT_TAMPER_4 |\
                                          RTC_INT_TAMPER_5 | RTC_INT_TAMPER_6 |\
                                          RTC_INT_TAMPER_7 | RTC_INT_TAMPER_8 )
/**
  * @}
 */

/** @defgroup RTCEx_Tamper_Trigger  RTCEx Tamper Trigger
  * @{
  */
#define RTC_TAMPERTRIGGER_RISINGEDGE        0x00U  /*!< Warning : Filter must be RTC_TAMPERFILTER_DISABLE */
#define RTC_TAMPERTRIGGER_FALLINGEDGE       0x01U  /*!< Warning : Filter must be RTC_TAMPERFILTER_DISABLE */
#define RTC_TAMPERTRIGGER_LOWLEVEL          0x02U  /*!< Warning : Filter must not be RTC_TAMPERFILTER_DISABLE */
#define RTC_TAMPERTRIGGER_HIGHLEVEL         0x03U  /*!< Warning : Filter must not be RTC_TAMPERFILTER_DISABLE */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_MaskFlag  RTCEx Tamper MaskFlag
  * @{
  */
#define RTC_TAMPERMASK_FLAG_DISABLE         0x00U
#define RTC_TAMPERMASK_FLAG_ENABLE          0x01U
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_EraseBackUp  RTCEx Tamper EraseBackUp
  * @{
  */
#define RTC_TAMPER_ERASE_BACKUP_ENABLE      0x00U
#define RTC_TAMPER_ERASE_BACKUP_DISABLE     0x01U
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Filter  RTCEx Tamper Filter
  * @{
  */
#define RTC_TAMPERFILTER_DISABLE           0x00000000U             /*!< Tamper filter is disabled */
#define RTC_TAMPERFILTER_2SAMPLE           TAMP_FLTCR_TAMPFLT_0    /*!< Tamper is activated after 2
                                                                         consecutive samples at the active level */
#define RTC_TAMPERFILTER_4SAMPLE           TAMP_FLTCR_TAMPFLT_1    /*!< Tamper is activated after 4
                                                                         consecutive samples at the active level */
#define RTC_TAMPERFILTER_8SAMPLE           TAMP_FLTCR_TAMPFLT      /*!< Tamper is activated after 8
                                                                         consecutive samples at the active level */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Sampling_Frequencies  RTCEx Tamper Sampling Frequencies
  * @{
  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768  0x00000000U                                     /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 32768 */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV16384  TAMP_FLTCR_TAMPFREQ_0                           /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 16384 */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV8192   TAMP_FLTCR_TAMPFREQ_1                           /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 8192  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV4096   (TAMP_FLTCR_TAMPFREQ_0 | TAMP_FLTCR_TAMPFREQ_1) /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 4096  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV2048   TAMP_FLTCR_TAMPFREQ_2                           /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 2048  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV1024   (TAMP_FLTCR_TAMPFREQ_0 | TAMP_FLTCR_TAMPFREQ_2) /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 1024  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV512    (TAMP_FLTCR_TAMPFREQ_1 | TAMP_FLTCR_TAMPFREQ_2) /*!< Each of the tamper inputs are sampled
                                                                                                      with a frequency =  RTCCLK / 512   */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV256    (TAMP_FLTCR_TAMPFREQ_0 | TAMP_FLTCR_TAMPFREQ_1 | \
                                                 TAMP_FLTCR_TAMPFREQ_2)                         /*!< Each of the tamper inputs are sampled
with a frequency =  RTCCLK / 256   */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pin_Precharge_Duration  RTCEx Tamper Pin Precharge Duration
  * @{
  */
#define RTC_TAMPERPRECHARGEDURATION_1RTCCLK     0x00000000U                                       /*!< Tamper pins are pre-charged before
                                                                                                        sampling during 1 RTCCLK cycle  */
#define RTC_TAMPERPRECHARGEDURATION_2RTCCLK     TAMP_FLTCR_TAMPPRCH_0                             /*!< Tamper pins are pre-charged before
                                                                                                        sampling during 2 RTCCLK cycles */
#define RTC_TAMPERPRECHARGEDURATION_4RTCCLK     TAMP_FLTCR_TAMPPRCH_1                             /*!< Tamper pins are pre-charged before
                                                                                                        sampling during 4 RTCCLK cycles */
#define RTC_TAMPERPRECHARGEDURATION_8RTCCLK     (TAMP_FLTCR_TAMPPRCH_0 | TAMP_FLTCR_TAMPPRCH_1)   /*!< Tamper pins are pre-charged before
                                                                                                        sampling during 8 RTCCLK cycles */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pull_UP  RTCEx Tamper Pull UP
  * @{
  */
#define RTC_TAMPER_PULLUP_ENABLE           0x00000000U           /*!< Tamper pins are pre-charged before sampling */
#define RTC_TAMPER_PULLUP_DISABLE          TAMP_FLTCR_TAMPPUDIS  /*!< Tamper pins pre-charge is disabled          */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_TimeStampOnTamperDetection RTCEx Tamper TimeStamp On Tamper Detection
  * @{
  */
#define RTC_TIMESTAMPONTAMPERDETECTION_DISABLE  0x00000000U    /*!< TimeStamp on Tamper Detection event is not saved */
#define RTC_TIMESTAMPONTAMPERDETECTION_ENABLE   RTC_CR_TAMPTS  /*!< TimeStamp on Tamper Detection event saved        */
/**
  * @}
  */

/** @defgroup RTCEx_Internal_Tamper_Interrupt  RTCEx Internal Tamper Interrupt
  * @{
  */
#define RTC_IT_TAMP_1                      TAMP_IER_TAMP1IE     /*!< Tamper 1 Interrupt */
#define RTC_IT_TAMP_2                      TAMP_IER_TAMP2IE     /*!< Tamper 2 Interrupt */
#if (RTC_TAMP_NB == 3)
#define RTC_IT_TAMP_3                      TAMP_IER_TAMP3IE     /*!< Tamper 3 Interrupt */
#define RTC_IT_TAMP_ALL                   (RTC_IT_TAMP_1 | RTC_IT_TAMP_2 | RTC_IT_TAMP_3 )
#elif (RTC_TAMP_NB == 8)
#define RTC_IT_TAMP_3                      TAMP_IER_TAMP3IE     /*!< Tamper 3 Interrupt */
#define RTC_IT_TAMP_4                      TAMP_IER_TAMP4IE     /*!< Tamper 4 Interrupt */
#define RTC_IT_TAMP_5                      TAMP_IER_TAMP5IE     /*!< Tamper 5 Interrupt */
#define RTC_IT_TAMP_6                      TAMP_IER_TAMP6IE     /*!< Tamper 6 Interrupt */
#define RTC_IT_TAMP_7                      TAMP_IER_TAMP7IE     /*!< Tamper 7 Interrupt */
#define RTC_IT_TAMP_8                      TAMP_IER_TAMP8IE     /*!< Tamper 8 Interrupt */
#define RTC_IT_TAMP_ALL                   (RTC_IT_TAMP_1 | RTC_IT_TAMP_2 |\
                                           RTC_IT_TAMP_3 | RTC_IT_TAMP_4 |\
                                           RTC_IT_TAMP_5 | RTC_IT_TAMP_6 |\
                                           RTC_IT_TAMP_7 | RTC_IT_TAMP_8 )
#else
#define RTC_IT_TAMP_ALL                   (RTC_IT_TAMP_1 | RTC_IT_TAMP_2)
#endif /* RTC_TAMP_NB */

#if defined (RTC_TAMP_INT_1_SUPPORT)
#define RTC_IT_INT_TAMP_1                   TAMP_IER_ITAMP1IE    /*!< Tamper 1 internal Interrupt */
#else
#define RTC_IT_INT_TAMP_1                   0U
#endif /* RTC_TAMP_INT_1_SUPPORT */
#if defined (RTC_TAMP_INT_2_SUPPORT)
#define RTC_IT_INT_TAMP_2                   TAMP_IER_ITAMP2IE    /*!< Tamper 2 internal Interrupt */
#else
#define RTC_IT_INT_TAMP_2                   0U
#endif /* RTC_TAMP_INT_2_SUPPORT */
#define RTC_IT_INT_TAMP_3                   TAMP_IER_ITAMP3IE    /*!< Tamper 3 internal Interrupt */
#define RTC_IT_INT_TAMP_4                   TAMP_IER_ITAMP4IE    /*!< Tamper 4 internal Interrupt */
#define RTC_IT_INT_TAMP_5                   TAMP_IER_ITAMP5IE    /*!< Tamper 5 internal Interrupt */
#if defined (RTC_TAMP_INT_6_SUPPORT)
#define RTC_IT_INT_TAMP_6                   TAMP_IER_ITAMP6IE    /*!< Tamper 6 internal Interrupt */
#else
#define RTC_IT_INT_TAMP_6                   0U
#endif /* RTC_TAMP_INT_6_SUPPORT */
#if defined (RTC_TAMP_INT_7_SUPPORT)
#define RTC_IT_INT_TAMP_7                   TAMP_IER_ITAMP7IE    /*!< Tamper 7 internal Interrupt */
#else
#define RTC_IT_INT_TAMP_7                   0U
#endif /* RTC_TAMP_INT_7_SUPPORT */
#if defined (RTC_TAMP_INT_8_SUPPORT)
#define RTC_IT_INT_TAMP_8                   TAMP_IER_ITAMP8IE    /*!< Tamper 8 internal Interrupt */
#else
#define RTC_IT_INT_TAMP_8                   0U
#endif /* RTC_TAMP_INT_8_SUPPORT */

#define RTC_IT_INT_TAMP_ALL                 (RTC_IT_INT_TAMP_1 | RTC_IT_INT_TAMP_2 |\
                                             RTC_IT_INT_TAMP_3 | RTC_IT_INT_TAMP_4 |\
                                             RTC_IT_INT_TAMP_5 | RTC_IT_INT_TAMP_6 |\
                                             RTC_IT_INT_TAMP_7 | RTC_IT_INT_TAMP_8 )
/**
  * @}
  */

/** @defgroup RTCEx_Flags  RTCEx Flags
  * @{
  */

#define RTC_FLAG_TAMP_1                     TAMP_SR_TAMP1F
#define RTC_FLAG_TAMP_2                     TAMP_SR_TAMP2F
#if (RTC_TAMP_NB == 3)
#define RTC_FLAG_TAMP_3                     TAMP_SR_TAMP3F
#define RTC_FLAG_TAMP_ALL                   (RTC_FLAG_TAMP_1 | RTC_FLAG_TAMP_2 | RTC_FLAG_TAMP_3)
#elif (RTC_TAMP_NB == 8)
#define RTC_FLAG_TAMP_3                     TAMP_SR_TAMP3F
#define RTC_FLAG_TAMP_4                     TAMP_SR_TAMP4F
#define RTC_FLAG_TAMP_5                     TAMP_SR_TAMP5F
#define RTC_FLAG_TAMP_6                     TAMP_SR_TAMP6F
#define RTC_FLAG_TAMP_7                     TAMP_SR_TAMP7F
#define RTC_FLAG_TAMP_8                     TAMP_SR_TAMP8F
#define RTC_FLAG_TAMP_ALL                   (RTC_FLAG_TAMP_1 | RTC_FLAG_TAMP_2 | RTC_FLAG_TAMP_3 |\
                                             RTC_FLAG_TAMP_4 | RTC_FLAG_TAMP_5 |\
                                             RTC_FLAG_TAMP_6 | RTC_FLAG_TAMP_7 | RTC_FLAG_TAMP_8)

#else
#define RTC_FLAG_TAMP_ALL                   (RTC_FLAG_TAMP_1 | RTC_FLAG_TAMP_2)
#endif /* RTC_TAMP_NB */

#if defined (RTC_TAMP_INT_1_SUPPORT)
#define RTC_FLAG_INT_TAMP_1                 TAMP_SR_ITAMP1F      /*!< Tamper 1 Interrupt flag */
#else
#define RTC_FLAG_INT_TAMP_1                 0U
#endif /* RTC_TAMP_INT_1_SUPPORT */
#if defined (RTC_TAMP_INT_2_SUPPORT)
#define RTC_FLAG_INT_TAMP_2                 TAMP_SR_ITAMP2F      /*!< Tamper 2 Interrupt flag */
#else
#define RTC_FLAG_INT_TAMP_2                 0U
#endif /* RTC_TAMP_INT_2_SUPPORT */
#define RTC_FLAG_INT_TAMP_3                 TAMP_SR_ITAMP3F      /*!< Tamper 3 Interrupt flag */
#define RTC_FLAG_INT_TAMP_4                 TAMP_SR_ITAMP4F      /*!< Tamper 4 Interrupt flag */
#define RTC_FLAG_INT_TAMP_5                 TAMP_SR_ITAMP5F      /*!< Tamper 5 Interrupt flag */
#if defined (RTC_TAMP_INT_6_SUPPORT)
#define RTC_FLAG_INT_TAMP_6                 TAMP_SR_ITAMP6F      /*!< Tamper 6 Interrupt flag */
#else
#define RTC_FLAG_INT_TAMP_6                 0U
#endif /* RTC_TAMP_INT_6_SUPPORT */
#if defined (RTC_TAMP_INT_7_SUPPORT)
#define RTC_FLAG_INT_TAMP_7                 TAMP_SR_ITAMP7F      /*!< Tamper 7 Interrupt flag */
#else
#define RTC_FLAG_INT_TAMP_7                 0U
#endif /* RTC_TAMP_INT_7_SUPPORT */
#if defined (RTC_TAMP_INT_8_SUPPORT)
#define RTC_FLAG_INT_TAMP_8                 TAMP_SR_ITAMP8F      /*!< Tamper 8 Interrupt flag */
#else
#define RTC_FLAG_INT_TAMP_8                 0U
#endif /* RTC_TAMP_INT_8_SUPPORT */
#define RTC_FLAG_INT_TAMP_ALL               (RTC_FLAG_INT_TAMP_1 | RTC_FLAG_INT_TAMP_2 |\
                                             RTC_FLAG_INT_TAMP_3 | RTC_FLAG_INT_TAMP_4 |\
                                             RTC_FLAG_INT_TAMP_5 | RTC_FLAG_INT_TAMP_6 |\
                                             RTC_FLAG_INT_TAMP_7 | RTC_FLAG_INT_TAMP_8)
/**
  * @}
  */


/** @defgroup RTCEx_Backup_Registers  RTCEx Backup Registers Definition
  * @{
  */
#define RTC_BKP_NUMBER                    RTC_BACKUP_NB
#if (RTC_BACKUP_NB == 5)
#define RTC_BKP_DR0                       0x00000000U
#define RTC_BKP_DR1                       0x00000001U
#define RTC_BKP_DR2                       0x00000002U
#define RTC_BKP_DR3                       0x00000003U
#define RTC_BKP_DR4                       0x00000004U
#elif  (RTC_BACKUP_NB == 16)
#define RTC_BKP_DR0                       0x00U
#define RTC_BKP_DR1                       0x01U
#define RTC_BKP_DR2                       0x02U
#define RTC_BKP_DR3                       0x03U
#define RTC_BKP_DR4                       0x04U
#define RTC_BKP_DR5                       0x05U
#define RTC_BKP_DR6                       0x06U
#define RTC_BKP_DR7                       0x07U
#define RTC_BKP_DR8                       0x08U
#define RTC_BKP_DR9                       0x09U
#define RTC_BKP_DR10                      0x0AU
#define RTC_BKP_DR11                      0x0BU
#define RTC_BKP_DR12                      0x0CU
#define RTC_BKP_DR13                      0x0DU
#define RTC_BKP_DR14                      0x0EU
#define RTC_BKP_DR15                      0x0FU
#elif  (RTC_BACKUP_NB == 32)
#define RTC_BKP_DR0                       0x00U
#define RTC_BKP_DR1                       0x01U
#define RTC_BKP_DR2                       0x02U
#define RTC_BKP_DR3                       0x03U
#define RTC_BKP_DR4                       0x04U
#define RTC_BKP_DR5                       0x05U
#define RTC_BKP_DR6                       0x06U
#define RTC_BKP_DR7                       0x07U
#define RTC_BKP_DR8                       0x08U
#define RTC_BKP_DR9                       0x09U
#define RTC_BKP_DR10                      0x0AU
#define RTC_BKP_DR11                      0x0BU
#define RTC_BKP_DR12                      0x0CU
#define RTC_BKP_DR13                      0x0DU
#define RTC_BKP_DR14                      0x0EU
#define RTC_BKP_DR15                      0x0FU
#define RTC_BKP_DR16                      0x10U
#define RTC_BKP_DR17                      0x11U
#define RTC_BKP_DR18                      0x12U
#define RTC_BKP_DR19                      0x13U
#define RTC_BKP_DR20                      0x14U
#define RTC_BKP_DR21                      0x15U
#define RTC_BKP_DR22                      0x16U
#define RTC_BKP_DR23                      0x17U
#define RTC_BKP_DR24                      0x18U
#define RTC_BKP_DR25                      0x19U
#define RTC_BKP_DR26                      0x1AU
#define RTC_BKP_DR27                      0x1BU
#define RTC_BKP_DR28                      0x1CU
#define RTC_BKP_DR29                      0x1DU
#define RTC_BKP_DR30                      0x1EU
#define RTC_BKP_DR31                      0x1FU
#else
#error "no RTC Backup Registers Definition"
#endif /* RTC_BKP_NUMBER */
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

/** @brief  Clear the specified RTC pending flag.
  * @param  __HANDLE__ specifies the RTC Handle.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg @ref RTC_CLEAR_ITSF               Clear Internal Time-stamp flag
  *            @arg @ref RTC_CLEAR_TSOVF              Clear Time-stamp overflow flag
  *            @arg @ref RTC_CLEAR_TSF                Clear Time-stamp flag
  *            @arg @ref RTC_CLEAR_WUTF               Clear Wakeup timer flag
  *            @arg @ref RTC_CLEAR_ALRBF              Clear Alarm B flag
  *            @arg @ref RTC_CLEAR_ALRAF              Clear Alarm A flag
  * @retval None
  */
#define __HAL_RTC_CLEAR_FLAG(__HANDLE__, __FLAG__)   (RTC->SCR = (__FLAG__))


/** @brief  Check whether the specified RTC flag is set or not.
  * @param  __HANDLE__ specifies the RTC Handle.
  * @param  __FLAG__ specifies the flag to check.
  *          This parameter can be any combination of the following values:
  *            @arg @ref RTC_FLAG_RECALPF             Recalibration pending Flag
  *            @arg @ref RTC_FLAG_INITF               Initialization flag
  *            @arg @ref RTC_FLAG_RSF                 Registers synchronization flag
  *            @arg @ref RTC_FLAG_INITS               Initialization status flag
  *            @arg @ref RTC_FLAG_SHPF                Shift operation pending flag
  *            @arg @ref RTC_FLAG_WUTWF               Wakeup timer write flag
  *            @arg @ref RTC_FLAG_ALRBWF              Alarm B write flag
  *            @arg @ref RTC_FLAG_ALRAWF              Alarm A write flag
  *            @arg @ref RTC_FLAG_ITSF                Internal Time-stamp flag
  *            @arg @ref RTC_FLAG_TSOVF               Time-stamp overflow flag
  *            @arg @ref RTC_FLAG_TSF                 Time-stamp flag
  *            @arg @ref RTC_FLAG_WUTF                Wakeup timer flag
  *            @arg @ref RTC_FLAG_ALRBF               Alarm B flag
  *            @arg @ref RTC_FLAG_ALRAF               Alarm A flag
  * @retval None
  */
#define __HAL_RTC_GET_FLAG(__HANDLE__, __FLAG__)    (((((__FLAG__)) >> 8U) == 1U) ? ((__HANDLE__)->Instance->ICSR & (1U << (((uint16_t)(__FLAG__)) & RTC_FLAG_MASK))) : \
                                                     ((__HANDLE__)->Instance->SR & (1U << (((uint16_t)(__FLAG__)) & RTC_FLAG_MASK))))

/* ---------------------------------WAKEUPTIMER---------------------------------*/
/** @defgroup RTCEx_WakeUp_Timer RTC WakeUp Timer
  * @{
  */
/**
  * @brief  Enable the RTC WakeUp Timer peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_ENABLE(__HANDLE__)                      (RTC->CR |= (RTC_CR_WUTE))

/**
  * @brief  Disable the RTC WakeUp Timer peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_DISABLE(__HANDLE__)                     (RTC->CR &= ~(RTC_CR_WUTE))

/**
  * @brief  Enable the RTC WakeUpTimer interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC WakeUpTimer interrupt sources to be enabled.
  *         This parameter can be:
  *            @arg @ref RTC_IT_WUT WakeUpTimer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_ENABLE_IT(__HANDLE__, __INTERRUPT__)    (RTC->CR |= (__INTERRUPT__))

/**
  * @brief  Disable the RTC WakeUpTimer interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC WakeUpTimer interrupt sources to be disabled.
  *         This parameter can be:
  *            @arg @ref RTC_IT_WUT WakeUpTimer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_DISABLE_IT(__HANDLE__, __INTERRUPT__)   (RTC->CR &= ~(__INTERRUPT__))


/**
  * @brief  Check whether the specified RTC WakeUpTimer interrupt has occurred or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC WakeUpTimer interrupt to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_WUT  WakeUpTimer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_IT(__HANDLE__, __INTERRUPT__)       ((((RTC->MISR)\
                                                                         & ((__INTERRUPT__)>> 12U)) != 0UL) ? 1UL : 0UL)
/**
  * @brief  Check whether the specified RTC Wake Up timer interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Wake Up timer interrupt sources to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_WUT  WakeUpTimer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)   ((((RTC->CR)\
                                                                            & (__INTERRUPT__)) != 0UL) ? 1UL : 0UL)

/**
  * @brief  Get the selected RTC WakeUpTimers flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC WakeUpTimer Flag is pending or not.
  *          This parameter can be:
  *             @arg @ref RTC_FLAG_WUTF
  *             @arg @ref RTC_FLAG_WUTWF
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_FLAG(__HANDLE__, __FLAG__)   (__HAL_RTC_GET_FLAG((__HANDLE__), (__FLAG__)))

/**
  * @brief  Clear the RTC Wake Up timers pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC WakeUpTimer Flag to clear.
  *         This parameter can be:
  *            @arg @ref RTC_FLAG_WUTF
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(__HANDLE__, __FLAG__)     (__HAL_RTC_CLEAR_FLAG((__HANDLE__), RTC_CLEAR_WUTF))

/* WAKE-UP TIMER EXTI */
/* ------------------ */
/**
  * @brief  Enable interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT()       (EXTI->IMR1 |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_IT()      (EXTI->IMR1 &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @brief  set the rising edge for interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_RISING_IT()       (EXTI->RTSR1 |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  set the falling edge for interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_FALLING_IT()       (EXTI->FTSR1 |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Clear the interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_IT()         (EXTI->PR1 = RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Clear the interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_CLEAR_FLAG()           (EXTI->PR1 = RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Enable event on the RTC WakeUp Timer associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_EVENT()    (EXTI->EMR1 |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable event on the RTC WakeUp Timer associated Exti line.
  * @retval None.
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_EVENT()   (EXTI->EMR1 &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))

/**
  * @}
  */

/* ---------------------------------TIMESTAMP---------------------------------*/
/** @defgroup RTCEx_Timestamp RTC Timestamp
  * @{
  */
/**
  * @brief  Enable the RTC TimeStamp peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_ENABLE(__HANDLE__)                       (RTC->CR |= (RTC_CR_TSE))

/**
  * @brief  Disable the RTC TimeStamp peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_DISABLE(__HANDLE__)                      (RTC->CR &= ~(RTC_CR_TSE))

/**
  * @brief  Enable the RTC TimeStamp interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC TimeStamp interrupt source to be enabled.
  *         This parameter can be:
  *            @arg @ref RTC_IT_TS TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_ENABLE_IT(__HANDLE__, __INTERRUPT__)     (RTC->CR |= (__INTERRUPT__))

/**
  * @brief  Disable the RTC TimeStamp interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC TimeStamp interrupt source to be disabled.
  *         This parameter can be:
  *            @arg @ref RTC_IT_TS TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_DISABLE_IT(__HANDLE__, __INTERRUPT__)    (RTC->CR &= ~(__INTERRUPT__))

/**
  * @brief  Check whether the specified RTC TimeStamp interrupt has occurred or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC TimeStamp interrupt to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_TS TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_IT(__HANDLE__, __INTERRUPT__)        ((((RTC->MISR)\
                                                                        & ((__INTERRUPT__)>> 12U)) != 0U) ? 1UL : 0UL)
/**
  * @brief  Check whether the specified RTC Time Stamp interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Time Stamp interrupt source to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_TS TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)     ((((RTC->CR)\
                                                                            & (__INTERRUPT__)) != 0U) ? 1UL : 0UL)

/**
  * @brief  Get the selected RTC TimeStamps flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC TimeStamp Flag is pending or not.
  *         This parameter can be:
  *            @arg @ref RTC_FLAG_TSF
  *            @arg @ref RTC_FLAG_TSOVF
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_FLAG(__HANDLE__, __FLAG__)     (__HAL_RTC_GET_FLAG((__HANDLE__),(__FLAG__)))

/**
  * @brief  Clear the RTC Time Stamps pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC TimeStamp Flag to clear.
  *          This parameter can be:
  *             @arg @ref RTC_FLAG_TSF
  *             @arg @ref RTC_FLAG_TSOVF
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_CLEAR_FLAG(__HANDLE__, __FLAG__)   (__HAL_RTC_CLEAR_FLAG((__HANDLE__), (__FLAG__)))

/* TIMESTAMP TIMER EXTI */
/* -------------------- */

/**
  * @brief  Enable interrupt on the RTC Timestamp associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_EXTI_ENABLE_IT()        (EXTI->IMR1 |= RTC_EXTI_LINE_TIMESTAMP_EVENT)

/**
  * @brief  Disable interrupt on the RTC Timestamp associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_EXTI_DISABLE_IT()       (EXTI->IMR1 &= ~(RTC_EXTI_LINE_TIMESTAMP_EVENT))

/**
  * @brief  set the rising edge for interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_EXTI_RISING_IT()       (EXTI->RTSR1 |= RTC_EXTI_LINE_TIMESTAMP_EVENT)

/**
  * @brief  set the falling edge for interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_EXTI_FALLING_IT()       (EXTI->FSTR1 |= RTC_EXTI_LINE_TIMESTAMP_EVENT)

/**
  * @brief  Clear the interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_EXTI_CLEAR_IT()         (EXTI->PR1 = RTC_EXTI_LINE_TIMESTAMP_EVENT)

/**
  * @brief  Clear the interrupt on the RTC Timestamp associated Exti line.
  * @retval None
 */
#define __HAL_RTC_TIMESTAMP_EXTI_CLEAR_FLAG()      (EXTI->PR1 = RTC_EXTI_LINE_TIMESTAMP_EVENT)

/**
  * @brief  Enable event on the RTC Timestamp associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_EXTI_ENABLE_EVENT()    (EXTI->EMR1 |= RTC_EXTI_LINE_TIMESTAMP_EVENT)

/**
  * @brief  Disable event on the RTC Timestamp associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_EXTI_DISABLE_EVENT()   (EXTI->EMR1 &= ~(RTC_EXTI_LINE_TIMESTAMP_EVENT))

/**
  * @brief  Enable the RTC internal TimeStamp peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_INTERNAL_TIMESTAMP_ENABLE(__HANDLE__)                (RTC->CR |= (RTC_CR_ITSE))

/**
  * @brief  Disable the RTC internal TimeStamp peripheral.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_INTERNAL_TIMESTAMP_DISABLE(__HANDLE__)               (RTC->CR &= ~(RTC_CR_ITSE))

/**
  * @brief  Get the selected RTC Internal Time Stamps flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Internal Time Stamp Flag is pending or not.
  *         This parameter can be:
  *            @arg @ref RTC_FLAG_ITSF
  * @retval None
  */
#define __HAL_RTC_INTERNAL_TIMESTAMP_GET_FLAG(__HANDLE__, __FLAG__)    (__HAL_RTC_GET_FLAG((__HANDLE__),(__FLAG__)))

/**
  * @brief  Clear the RTC Internal Time Stamps pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Internal Time Stamp Flag source to clear.
  * This parameter can be:
  *             @arg @ref RTC_FLAG_ITSF
  * @retval None
  */
#define __HAL_RTC_INTERNAL_TIMESTAMP_CLEAR_FLAG(__HANDLE__, __FLAG__)  (__HAL_RTC_CLEAR_FLAG((__HANDLE__), RTC_CLEAR_ITSF))

/**
  * @brief  Enable the RTC TimeStamp on Tamper detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TAMPTS_ENABLE(__HANDLE__)                       (RTC->CR |= (RTC_CR_TAMPTS))

/**
  * @brief  Disable the RTC TimeStamp on Tamper detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TAMPTS_DISABLE(__HANDLE__)                      (RTC->CR &= ~(RTC_CR_TAMPTS))

/**
  * @brief  Enable the RTC Tamper detection output.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TAMPOE_ENABLE(__HANDLE__)                       (RTC->CR |= (RTC_CR_TAMPOE))

/**
  * @brief  Disable the RTC Tamper detection output.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_TAMPOE_DISABLE(__HANDLE__)                      (RTC->CR &= ~(RTC_CR_TAMPOE))


/**
  * @}
  */


/* ------------------------------Calibration----------------------------------*/
/** @defgroup RTCEx_Calibration RTC Calibration
  * @{
  */

/**
  * @brief  Enable the RTC calibration output.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CALIBRATION_OUTPUT_ENABLE(__HANDLE__)               (RTC->CR |= (RTC_CR_COE))

/**
  * @brief  Disable the calibration output.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CALIBRATION_OUTPUT_DISABLE(__HANDLE__)              (RTC->CR &= ~(RTC_CR_COE))


/**
  * @brief  Enable the clock reference detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CLOCKREF_DETECTION_ENABLE(__HANDLE__)               (RTC->CR |= (RTC_CR_REFCKON))

/**
  * @brief  Disable the clock reference detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @retval None
  */
#define __HAL_RTC_CLOCKREF_DETECTION_DISABLE(__HANDLE__)              (RTC->CR &= ~(RTC_CR_REFCKON))


/**
  * @brief  Get the selected RTC shift operations flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC shift operation Flag is pending or not.
  *          This parameter can be:
  *             @arg @ref RTC_FLAG_SHPF
  * @retval None
  */
#define __HAL_RTC_SHIFT_GET_FLAG(__HANDLE__, __FLAG__)                (__HAL_RTC_GET_FLAG((__HANDLE__), (__FLAG__)))
/**
  * @}
  */


/* ------------------------------Tamper----------------------------------*/
/** @defgroup RTCEx_Tamper RTCEx tamper
  * @{
  */
/**
  * @brief  Enable the TAMP Tamper input detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __TAMPER__ specifies the RTC Tamper source to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg  RTC_TAMPER_ALL: All tampers
  *            @arg  RTC_TAMPER_1: Tamper1
  *            @arg  RTC_TAMPER_2: Tamper2
  * @retval None
  */
#define __HAL_RTC_TAMPER_ENABLE(__HANDLE__, __TAMPER__)            (TAMP->CR1 |= (__TAMPER__))

/**
  * @brief  Disable the TAMP Tamper input detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __TAMPER__ specifies the RTC Tamper sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg  RTC_TAMPER_ALL: All tampers
  *            @arg  RTC_TAMPER_1: Tamper1
  *            @arg  RTC_TAMPER_2: Tamper2
  */
#define __HAL_RTC_TAMPER_DISABLE(__HANDLE__, __TAMPER__)           (TAMP->CR1 &= ~(__TAMPER__))


/**************************************************************************************************/
/**
  * @brief  Enable the TAMP Tamper interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *             @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *             @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *             @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_ENABLE_IT(__HANDLE__, __INTERRUPT__)      (TAMP->IER |= (__INTERRUPT__))


/**
  * @brief  Disable the TAMP Tamper interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *            @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *            @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_DISABLE_IT(__HANDLE__, __INTERRUPT__)     (TAMP->IER &= ~(__INTERRUPT__))


/**************************************************************************************************/
/**
  * @brief  Check whether the specified TAMP Tamper interrupt has occurred or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt to check.
  *         This parameter can be:
  *            @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *            @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *            @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT(__HANDLE__, __INTERRUPT__)         ((((TAMP->MISR)\
                                                                      & (__INTERRUPT__)) != 0UL) ? 1UL : 0UL)


/**
  * @brief  Check whether the specified TAMP Tamper interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt source to check.
  *         This parameter can be:
  *            @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *            @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *            @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)  ((((TAMP->IER)\
                                                                      & (__INTERRUPT__)) != 0UL) ? 1UL : 0UL)


/**
  * @brief  Get the selected TAMP Tampers flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Tamper Flag is pending or not.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP_ALL: All tampers flag
  *             @arg RTC_FLAG_TAMP_1: Tamper1 flag
  *             @arg RTC_FLAG_TAMP_2: Tamper2 flag
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_FLAG(__HANDLE__, __FLAG__)            (((TAMP->SR) & (__FLAG__)) != 0UL)


/**
  * @brief  Clear the TAMP Tampers pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Tamper Flag to clear.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP_ALL: All tampers flag
  *             @arg RTC_FLAG_TAMP_1: Tamper1 flag
  *             @arg RTC_FLAG_TAMP_2: Tamper2 flag
  * @retval None
  */
#define __HAL_RTC_TAMPER_CLEAR_FLAG(__HANDLE__, __FLAG__)      ((TAMP->SCR) = (__FLAG__))


/**
  * @brief  Enable interrupt on the RTC Tamper associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_ENABLE_IT()        (EXTI->IMR1 |= RTC_EXTI_LINE_TAMPER_EVENT)


/**
  * @brief  Disable interrupt on the RTC Tamper associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_DISABLE_IT()       (EXTI->IMR1 &= ~(RTC_EXTI_LINE_TAMPER_EVENT))


/**
  * @brief  Enable interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_RISING_IT()        (EXTI->RTSR1 |= RTC_EXTI_LINE_TAMPER_EVENT)


/**
  * @brief  Enable interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_FALLING_IT()       (EXTI->FSTR1 |= RTC_EXTI_LINE_TAMPER_EVENT)


/**
  * @brief  Clear the interrupt on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_CLEAR_IT()         (EXTI->PR1 = RTC_EXTI_LINE_TAMPER_EVENT)


/**
  * @brief  Enable event on the RTC Tamper associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_ENABLE_EVENT()     (EXTI->EMR1 |= RTC_EXTI_LINE_TAMPER_EVENT)


/**
  * @brief  Disable event on the RTC Tamper associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_DISABLE_EVENT()    (EXTI->EMR1 &= ~(RTC_EXTI_LINE_TAMPER_EVENT))


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

/* RTC TimeStamp functions *****************************************/
/** @defgroup RTCEx_Exported_Functions_Group1 Extended RTC TimeStamp functions
  * @{
  */

HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp_IT(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateInternalTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_GetTimeStamp(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTimeStamp,
                                         RTC_DateTypeDef *sTimeStampDate, uint32_t Format);
void              HAL_RTCEx_TimeStampIRQHandler(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForTimeStampEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
void              HAL_RTCEx_TimeStampEventCallback(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */


/* RTC Wake-up functions ******************************************************/
/** @defgroup RTCEx_Exported_Functions_Group2 Extended RTC Wake-up functions
  * @{
  */

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

/* Extended Control functions ************************************************/
/** @defgroup RTCEx_Exported_Functions_Group3 Extended Peripheral Control functions
  * @{
  */

HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef *hrtc, uint32_t SmoothCalibPeriod,
                                           uint32_t SmoothCalibPlusPulses, uint32_t SmoothCalibMinusPulsesValue);
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

/* Extended RTC features functions *******************************************/
/** @defgroup RTCEx_Exported_Functions_Group4 Extended features functions
  * @{
  */

void              HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForAlarmBEvent(RTC_HandleTypeDef *hrtc, uint32_t Timeout);
/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group5 Extended RTC Tamper functions
  * @{
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef *sTamper);
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef *sTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(RTC_HandleTypeDef *hrtc, uint32_t Tamper);
HAL_StatusTypeDef HAL_RTCEx_PollForTamperEvent(RTC_HandleTypeDef *hrtc, uint32_t Tamper, uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper(RTC_HandleTypeDef *hrtc, RTC_InternalTamperTypeDef *sIntTamper);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper_IT(RTC_HandleTypeDef *hrtc, RTC_InternalTamperTypeDef *sIntTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateInternalTamper(RTC_HandleTypeDef *hrtc, uint32_t IntTamper);
HAL_StatusTypeDef HAL_RTCEx_PollForInternalTamperEvent(RTC_HandleTypeDef *hrtc, uint32_t IntTamper, uint32_t Timeout);
void              HAL_RTCEx_TamperIRQHandler(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper2EventCallback(RTC_HandleTypeDef *hrtc);
#if (RTC_TAMP_NB == 3)
void              HAL_RTCEx_Tamper3EventCallback(RTC_HandleTypeDef *hrtc);
#endif /* RTC_TAMP_NB */

#ifdef RTC_TAMP_INT_1_SUPPORT
void              HAL_RTCEx_InternalTamper1EventCallback(RTC_HandleTypeDef *hrtc);
#endif /* RTC_TAMP_INT_1_SUPPORT */
#ifdef RTC_TAMP_INT_2_SUPPORT
void              HAL_RTCEx_InternalTamper2EventCallback(RTC_HandleTypeDef *hrtc);
#endif /* RTC_TAMP_INT_2_SUPPORT */
void              HAL_RTCEx_InternalTamper3EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper4EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper5EventCallback(RTC_HandleTypeDef *hrtc);
#ifdef RTC_TAMP_INT_6_SUPPORT
void              HAL_RTCEx_InternalTamper6EventCallback(RTC_HandleTypeDef *hrtc);
#endif /* RTC_TAMP_INT_6_SUPPORT */
#ifdef RTC_TAMP_INT_7_SUPPORT
void              HAL_RTCEx_InternalTamper7EventCallback(RTC_HandleTypeDef *hrtc);
#endif /* RTC_TAMP_INT_7_SUPPORT */
/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group6 Extended RTC Backup register functions
  * @{
  */
void              HAL_RTCEx_BKUPWrite(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data);
uint32_t          HAL_RTCEx_BKUPRead(RTC_HandleTypeDef *hrtc, uint32_t BackupRegister);

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
#define RTC_EXTI_LINE_ALARM_EVENT             EXTI_IMR1_IM17 /*!< External interrupt line 17 Connected to the RTC Alarm event */
#define RTC_EXTI_LINE_TIMESTAMP_EVENT         EXTI_IMR1_IM19 /*!< External interrupt line 19 Connected to the RTC tamper/Time Stamp/CSS_LSE events */
#define RTC_EXTI_LINE_TAMPER_EVENT            EXTI_IMR1_IM19 /*!< External interrupt line 19 Connected to the RTC tamper/Time Stamp/CSS_LSE events */
#define RTC_EXTI_LINE_WAKEUPTIMER_EVENT       EXTI_IMR1_IM20 /*!< External interrupt line 20 Connected to the RTC Wakeup event */
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
#define IS_TIMESTAMP_EDGE(EDGE) (((EDGE) == RTC_TIMESTAMPEDGE_RISING) || \
                                 ((EDGE) == RTC_TIMESTAMPEDGE_FALLING))


#define IS_RTC_TIMESTAMP_PIN(PIN)  (((PIN) == RTC_TIMESTAMPPIN_DEFAULT))



#define IS_RTC_TIMESTAMPONTAMPER_DETECTION(DETECTION) (((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_ENABLE) || \
                                                       ((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_DISABLE))

#define IS_RTC_TAMPER_TAMPERDETECTIONOUTPUT(MODE)    (((MODE) == RTC_TAMPERDETECTIONOUTPUT_ENABLE) || \
                                                      ((MODE) == RTC_TAMPERDETECTIONOUTPUT_DISABLE))


#define IS_RTC_WAKEUP_CLOCK(CLOCK) (((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV16)   || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV8)    || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV4)    || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_RTCCLK_DIV2)    || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_CK_SPRE_16BITS) || \
                                    ((CLOCK) == RTC_WAKEUPCLOCK_CK_SPRE_17BITS))

#define IS_RTC_WAKEUP_COUNTER(COUNTER)  ((COUNTER) <= RTC_WUTR_WUT)

#define IS_RTC_SMOOTH_CALIB_PERIOD(PERIOD) (((PERIOD) == RTC_SMOOTHCALIB_PERIOD_32SEC) || \
                                            ((PERIOD) == RTC_SMOOTHCALIB_PERIOD_16SEC) || \
                                            ((PERIOD) == RTC_SMOOTHCALIB_PERIOD_8SEC))

#define IS_RTC_SMOOTH_CALIB_PLUS(PLUS) (((PLUS) == RTC_SMOOTHCALIB_PLUSPULSES_SET) || \
                                        ((PLUS) == RTC_SMOOTHCALIB_PLUSPULSES_RESET))

#define IS_RTC_SMOOTH_CALIB_MINUS(VALUE) ((VALUE) <= RTC_CALR_CALM)

#define IS_RTC_LOW_POWER_CALIB(LPCAL) (((LPCAL) == RTC_LPCAL_SET) || \
                                       ((LPCAL) == RTC_LPCAL_RESET))

#define IS_RTC_TAMPER(__TAMPER__)                ((((__TAMPER__) & RTC_TAMPER_ALL) != 0x00U) && \
                                                  (((__TAMPER__) & ~RTC_TAMPER_ALL) == 0x00U))

#define IS_RTC_INTERNAL_TAMPER(__INT_TAMPER__)   ((((__INT_TAMPER__) & RTC_INT_TAMPER_ALL) != 0x00U) && \
                                                  (((__INT_TAMPER__) & ~RTC_INT_TAMPER_ALL) == 0x00U))

#define IS_RTC_TAMPER_TRIGGER(__TRIGGER__)       (((__TRIGGER__) == RTC_TAMPERTRIGGER_RISINGEDGE)  || \
                                                  ((__TRIGGER__) == RTC_TAMPERTRIGGER_FALLINGEDGE) || \
                                                  ((__TRIGGER__) == RTC_TAMPERTRIGGER_LOWLEVEL)    || \
                                                  ((__TRIGGER__) == RTC_TAMPERTRIGGER_HIGHLEVEL))

#define IS_RTC_TAMPER_ERASE_MODE(__MODE__)       (((__MODE__) == RTC_TAMPER_ERASE_BACKUP_ENABLE) || \
                                                  ((__MODE__) == RTC_TAMPER_ERASE_BACKUP_DISABLE))

#define IS_RTC_TAMPER_MASKFLAG_STATE(__STATE__)  (((__STATE__) == RTC_TAMPERMASK_FLAG_ENABLE) || \
                                                  ((__STATE__) == RTC_TAMPERMASK_FLAG_DISABLE))

#define IS_RTC_TAMPER_FILTER(__FILTER__)         (((__FILTER__) == RTC_TAMPERFILTER_DISABLE)  || \
                                                  ((__FILTER__) == RTC_TAMPERFILTER_2SAMPLE) || \
                                                  ((__FILTER__) == RTC_TAMPERFILTER_4SAMPLE) || \
                                                  ((__FILTER__) == RTC_TAMPERFILTER_8SAMPLE))

#define IS_RTC_TAMPER_SAMPLING_FREQ(__FREQ__)    (((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768)|| \
                                                  ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV16384)|| \
                                                  ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV8192) || \
                                                  ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV4096) || \
                                                  ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV2048) || \
                                                  ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV1024) || \
                                                  ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV512)  || \
                                                  ((__FREQ__) == RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV256))

#define IS_RTC_TAMPER_PRECHARGE_DURATION(__DURATION__)   (((__DURATION__) == RTC_TAMPERPRECHARGEDURATION_1RTCCLK) || \
                                                          ((__DURATION__) == RTC_TAMPERPRECHARGEDURATION_2RTCCLK) || \
                                                          ((__DURATION__) == RTC_TAMPERPRECHARGEDURATION_4RTCCLK) || \
                                                          ((__DURATION__) == RTC_TAMPERPRECHARGEDURATION_8RTCCLK))

#define IS_RTC_TAMPER_PULLUP_STATE(__STATE__)    (((__STATE__) == RTC_TAMPER_PULLUP_ENABLE) || \
                                                  ((__STATE__) == RTC_TAMPER_PULLUP_DISABLE))

#define IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(DETECTION) (((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_ENABLE) || \
                                                              ((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_DISABLE))

#define IS_RTC_BKP(__BKP__)   ((__BKP__) < RTC_BKP_NUMBER)

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

#endif /* STM32G4xx_HAL_RTC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
