/**
  ******************************************************************************
  * @file    stm32h5xx_hal_rtc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RTC HAL Extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H5xx_HAL_RTC_EX_H
#define STM32H5xx_HAL_RTC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h5xx_hal_def.h"

/** @addtogroup STM32H5xx_HAL_Driver
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
                                             This parameter can be a value of
                                             @ref RTCEx_Tamper_Sampling_Frequencies */

  uint32_t PrechargeDuration;           /*!< Specifies the Precharge Duration.
                                             This parameter can be a value of
                                             @ref RTCEx_Tamper_Pin_Precharge_Duration */

  uint32_t TamperPullUp;                /*!< Specifies the Tamper PullUp.
                                             This parameter can be a value of @ref RTCEx_Tamper_Pull_UP */

  uint32_t TimeStampOnTamperDetection;  /*!< Specifies the TimeStampOnTamperDetection.
                                             This parameter can be a value of
                                              @ref RTCEx_Tamper_TimeStampOnTamperDetection */
} RTC_TamperTypeDef;
/**
  * @}
  */


/** @defgroup RTCEx_Active_Seed_Size Seed size Definitions
  * @{
  */
#define RTC_ATAMP_SEED_NB_UINT32        4U
/**
  * @}
  */


/** @defgroup RTCEx_ActiveTamper_structures_definition RTCEx Active Tamper structures definitions
  * @{
  */
typedef struct
{
  uint32_t Enable;                      /*!< Specifies the Tamper input is active.
                                             This parameter can be a value of @ref RTCEx_ActiveTamper_Enable */

  uint32_t Interrupt;                    /*!< Specifies the interrupt mode.
                                             This parameter can be a value of @ref RTCEx_ActiveTamper_Interrupt */

  uint32_t Output;                      /*!< Specifies the TAMP output to be compared with.
                                             The same output can be used for several tamper inputs.
                                             This parameter can be a value of @ref RTCEx_ActiveTamper_Sel */

  uint32_t NoErase;                     /*!< Specifies the Tamper no erase mode.
                                             This parameter can be a value of @ref RTCEx_Tamper_EraseBackUp */

  uint32_t MaskFlag;                    /*!< Specifies the Tamper Flag masking.
                                             This parameter can be a value of @ref RTCEx_Tamper_MaskFlag */

} RTC_ATampInputTypeDef;


typedef struct
{
  uint32_t ActiveFilter;                /*!< Specifies the Active tamper filter enable.
                                             This parameter can be a value of @ref RTCEx_ActiveTamper_Filter */

  uint32_t ActiveAsyncPrescaler;        /*!< Specifies the Active Tamper asynchronous Prescaler clock.
                                             This parameter can be a value of
                                             @ref RTCEx_ActiveTamper_Async_prescaler */

  uint32_t TimeStampOnTamperDetection;  /*!< Specifies the timeStamp on tamper detection.
                                             This parameter can be a value of
                                             @ref RTCEx_Tamper_TimeStampOnTamperDetection */

  uint32_t ActiveOutputChangePeriod;    /*!< Specifies the Active Tamper output change period.
                                             This parameter can be a value from 0 to 7 */

  uint32_t Seed[RTC_ATAMP_SEED_NB_UINT32];
  /*!< Specifies the RNG Seed value.
       This parameter is an array of value from 0 to 0xFFFFFFFF */

  RTC_ATampInputTypeDef TampInput[RTC_TAMP_NB];
  /*!< Specifies configuration of all active tampers.
       The index of TampInput[RTC_TAMP_NB] can be a value of RTCEx_ActiveTamper_Sel */
} RTC_ActiveTampersTypeDef;
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
                                             This parameter can be a value of
                                             @ref RTCEx_Tamper_TimeStampOnTamperDetection */

  uint32_t NoErase;                     /*!< Specifies the internal Tamper no erase mode.
                                             This parameter can be a value of @ref RTCEx_Tamper_EraseBackUp */

} RTC_InternalTamperTypeDef;
/**
  * @}
  */

/** @defgroup RTCEx_Secure_State_structure_definition RTCEx Secure structure definition
  * @{
  */
typedef struct
{
  uint32_t rtcSecureFull;               /*!< Specifies If the RTC is fully secure or not.
                                             This parameter can be a value of @ref RTCEx_RTC_Secure_Full */

  uint32_t rtcNonSecureFeatures;        /*!< Specifies the non-secure features.
                                             This parameter is only relevant if RTC is not fully secure
                                             (rtcSecureFull == RTC_SECURE_FULL_NO).
                                             This parameter can be a combination of
                                             @ref RTCEx_RTC_NonSecure_Features */

  uint32_t tampSecureFull;              /*!< Specifies If the TAMP is fully secure or not execpt monotonic counters
                                             and BackUp registers.
                                             This parameter can be a value of @ref RTCEx_TAMP_Secure_Full */

  uint32_t backupRegisterStartZone2;    /*!< Specifies the backup register start zone 2.
                                             Zone 1 : read secure write secure.
                                             Zone 2 : read non-secure  write secure.
                                             This parameter can be RTC_BKP_DRx where x can be from 0 to 31 to specify
                                             the register.
                                             Warning : this parameter is shared with RTC_PrivilegeStateTypeDef */

  uint32_t backupRegisterStartZone3;    /*!< Specifies the backup register start zone 3.
                                             Zone 3 : read non-secure  write non-secure.
                                             This parameter can be RTC_BKP_DRx where x can be from 0 to 31 to
                                             specify the register.
                                             Warning : this parameter is shared with RTC_PrivilegeStateTypeDef */

  uint32_t MonotonicCounterSecure;      /*!< Specifies If the monotonic counter is secure or not.
                                             This parameter can be a value of
                                             @ref RTCEx_TAMP_Monotonic_Counter_Secure */
} RTC_SecureStateTypeDef;
/**
  * @}
  */

/** @defgroup RTCEx_Privilege_State_structure_definition RTCEx Privilege structure definition
  * @{
  */
typedef struct
{
  uint32_t rtcPrivilegeFull;            /*!< Specifies If the RTC is fully privileged or not.
                                             This parameter can be a value of @ref RTCEx_RTC_Privilege_Full */

  uint32_t rtcPrivilegeFeatures;        /*!< Specifies the privileged features.
                                             This parameter is only relevant if RTC is not fully privileged
                                             (rtcPrivilegeFull == RTC_PRIVILEGE_FULL_NO).
                                             This parameter can be a combination of
                                             @ref RTCEx_RTC_Privilege_Features */

  uint32_t tampPrivilegeFull;           /*!< Specifies If the TAMP is fully privileged or not execpt monotonic
                                             counters and BackUp registers.
                                             This parameter can be a value of @ref RTCEx_TAMP_Privilege_Full */

  uint32_t backupRegisterPrivZone;      /*!< Specifies backup register zone to be privileged.
                                             This parameter can be a combination of
                                             @ref RTCEx_Backup_Reg_Privilege_zone.
                                             Warning : this parameter is writable in secure mode or if trustzone is
                                             disabled */

  uint32_t backupRegisterStartZone2;    /*!< Specifies the backup register start zone 2.
                                             Zone 1 : read secure write secure.
                                             Zone 2 : read non-secure  write secure.
                                             This parameter can be RTC_BKP_DRx where x can be from 0 to 31 to specify
                                             the register .
                                             Warning : this parameter is writable in secure mode or if trustzone is
                                             disabled.
                                             Warning : this parameter is shared with RTC_SecureStateTypeDef */

  uint32_t backupRegisterStartZone3;    /*!< Specifies the backup register start zone 3.
                                             Zone 3 : read non-secure  write non-secure.
                                             This parameter can be RTC_BKP_DRx where x can be from 0 to 31 to specify
                                             the register.
                                             Warning : this parameter is writable in secure mode or if trustzone is
                                             disabled.
                                             Warning : this parameter is shared with RTC_SecureStateTypeDef */

  uint32_t MonotonicCounterPrivilege;   /*!< Specifies If the monotonic counter is privileged or not.
                                             This parameter can be a value of
                                             @ref RTCEx_TAMP_Monotonic_Counter_Privilege */
} RTC_PrivilegeStateTypeDef;
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

#if defined(RTC_CR_TSEDGE)
/** @defgroup RTCEx_Time_Stamp_Edges_definitions RTCEx Time Stamp Edges definition
  * @{
  */
#define RTC_TIMESTAMPEDGE_RISING           0U
#define RTC_TIMESTAMPEDGE_FALLING          RTC_CR_TSEDGE
/**
  * @}
  */
#endif /* RTC_CR_TSEDGE */

/** @defgroup RTCEx_TimeStamp_Pin_Selections RTCEx TimeStamp Pin Selection
  * @{
  */
#define RTC_TIMESTAMPPIN_DEFAULT           0U
/**
  * @}
  */

/** @defgroup RTCEx_Wakeup_Timer_Definitions RTCEx Wakeup Timer Definitions
  * @{
  */
#define RTC_WAKEUPCLOCK_RTCCLK_DIV16       0U
#define RTC_WAKEUPCLOCK_RTCCLK_DIV8        RTC_CR_WUCKSEL_0
#define RTC_WAKEUPCLOCK_RTCCLK_DIV4        RTC_CR_WUCKSEL_1
#define RTC_WAKEUPCLOCK_RTCCLK_DIV2        (RTC_CR_WUCKSEL_0 | RTC_CR_WUCKSEL_1)
#define RTC_WAKEUPCLOCK_CK_SPRE_16BITS     RTC_CR_WUCKSEL_2
#define RTC_WAKEUPCLOCK_CK_SPRE_17BITS     (RTC_CR_WUCKSEL_1 | RTC_CR_WUCKSEL_2)
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_period_Definitions RTCEx Smooth calib period Definitions
  * @{
  */
#define RTC_SMOOTHCALIB_PERIOD_32SEC       0U                    /*!< If RTCCLK = 32768 Hz, Smooth calibration period
                                                                      is 32s, else 2exp20 RTCCLK pulses */
#define RTC_SMOOTHCALIB_PERIOD_16SEC       RTC_CALR_CALW16       /*!< If RTCCLK = 32768 Hz, Smooth calibration period
                                                                      is 16s, else 2exp19 RTCCLK pulses */
#define RTC_SMOOTHCALIB_PERIOD_8SEC        RTC_CALR_CALW8        /*!< If RTCCLK = 32768 Hz, Smooth calibration period
                                                                      is 8s, else 2exp18 RTCCLK pulses  */
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_Plus_pulses_Definitions RTCEx Smooth calib Plus pulses Definitions
  * @{
  */
#define RTC_SMOOTHCALIB_PLUSPULSES_SET     RTC_CALR_CALP         /*!< The number of RTCCLK pulses added
                                                                      during a X -second window = Y - CALM[8:0]
                                                                      with Y = 512, 256, 128 when X = 32, 16, 8 */
#define RTC_SMOOTHCALIB_PLUSPULSES_RESET   0U                    /*!< The number of RTCCLK pulses subbstited
                                                                      during a 32-second window = CALM[8:0]     */
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_low_power_Definitions RTCEx Smooth calib Low Power Definitions
  * @{
  */
#define RTC_LPCAL_SET                      RTC_CALR_LPCAL        /*!< Calibration window is 2exp20 ck_apre, which is the required configuration for ultra-low consumption mode. */
#define RTC_LPCAL_RESET                    0U                    /*!< Calibration window is 2exp20 RTCCLK, which is a high-consumption mode.
                                                                      This mode should be set only when less
                                                                      than 32s calibration window is required. */
/**
  * @}
  */

#if defined(RTC_CR_COSEL)
/** @defgroup RTCEx_Calib_Output_selection_Definitions RTCEx Calib Output selection Definitions
  * @{
  */
#define RTC_CALIBOUTPUT_512HZ              0U
#define RTC_CALIBOUTPUT_1HZ                RTC_CR_COSEL
/**
  * @}
  */
#endif /* RTC_CR_COSEL */

/** @defgroup RTCEx_Add_1_Second_Parameter_Definition RTCEx Add 1 Second Parameter Definitions
  * @{
  */
#define RTC_SHIFTADD1S_RESET               0U
#define RTC_SHIFTADD1S_SET                 RTC_SHIFTR_ADD1S
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pins  RTCEx Tamper Pins Definition
  * @{
  */
#define RTC_TAMPER_1                       TAMP_CR1_TAMP1E
#define RTC_TAMPER_2                       TAMP_CR1_TAMP2E
#if (RTC_TAMP_NB == 2U)
#define RTC_TAMPER_ALL                     (RTC_TAMPER_1 | RTC_TAMPER_2)
#else
#define RTC_TAMPER_3                       TAMP_CR1_TAMP3E
#define RTC_TAMPER_4                       TAMP_CR1_TAMP4E
#define RTC_TAMPER_5                       TAMP_CR1_TAMP5E
#define RTC_TAMPER_6                       TAMP_CR1_TAMP6E
#define RTC_TAMPER_7                       TAMP_CR1_TAMP7E
#define RTC_TAMPER_8                       TAMP_CR1_TAMP8E
#define RTC_TAMPER_ALL                     (RTC_TAMPER_1 | RTC_TAMPER_2 |\
                                            RTC_TAMPER_3 | RTC_TAMPER_4 |\
                                            RTC_TAMPER_5 | RTC_TAMPER_6 |\
                                            RTC_TAMPER_7 | RTC_TAMPER_8 )
#endif /* RTC_TAMP_NB */
/**
  * @}
  */

/** @defgroup RTCEx_Internal_Tamper_Pins  RTCEx Internal Tamper Pins Definition
  * @{
  */
#define RTC_INT_TAMPER_1                   TAMP_CR1_ITAMP1E
#define RTC_INT_TAMPER_2                   TAMP_CR1_ITAMP2E
#define RTC_INT_TAMPER_3                   TAMP_CR1_ITAMP3E
#define RTC_INT_TAMPER_4                   TAMP_CR1_ITAMP4E
#define RTC_INT_TAMPER_5                   TAMP_CR1_ITAMP5E
#define RTC_INT_TAMPER_6                   TAMP_CR1_ITAMP6E
#define RTC_INT_TAMPER_7                   TAMP_CR1_ITAMP7E
#define RTC_INT_TAMPER_8                   TAMP_CR1_ITAMP8E
#define RTC_INT_TAMPER_9                   TAMP_CR1_ITAMP9E
#define RTC_INT_TAMPER_11                  TAMP_CR1_ITAMP11E
#define RTC_INT_TAMPER_12                  TAMP_CR1_ITAMP12E
#define RTC_INT_TAMPER_13                  TAMP_CR1_ITAMP13E
#define RTC_INT_TAMPER_15                  TAMP_CR1_ITAMP15E
#define RTC_INT_TAMPER_ALL                 (RTC_INT_TAMPER_1 | RTC_INT_TAMPER_2 |\
                                            RTC_INT_TAMPER_3 | RTC_INT_TAMPER_4 |\
                                            RTC_INT_TAMPER_5 | RTC_INT_TAMPER_6 |\
                                            RTC_INT_TAMPER_7 | RTC_INT_TAMPER_8 |\
                                            RTC_INT_TAMPER_9 | RTC_INT_TAMPER_11 |\
                                            RTC_INT_TAMPER_12 | RTC_INT_TAMPER_13 |\
                                            RTC_INT_TAMPER_15)
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Trigger  RTCEx Tamper Trigger
  * @{
  */
#define RTC_TAMPERTRIGGER_RISINGEDGE       0U                    /*!< Warning : Filter must be RTC_TAMPERFILTER_DISABLE */
#define RTC_TAMPERTRIGGER_FALLINGEDGE      1U                    /*!< Warning : Filter must be RTC_TAMPERFILTER_DISABLE */
#define RTC_TAMPERTRIGGER_LOWLEVEL         2U                    /*!< Warning : Filter must not be RTC_TAMPERFILTER_DISABLE */
#define RTC_TAMPERTRIGGER_HIGHLEVEL        3U                    /*!< Warning : Filter must not be RTC_TAMPERFILTER_DISABLE */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_MaskFlag  RTCEx Tamper MaskFlag
  * @{
  */
#define RTC_TAMPERMASK_FLAG_DISABLE        0U
#define RTC_TAMPERMASK_FLAG_ENABLE         1U
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Maskable_nb  RTCEx Tampers maskable number
  * @{
  */
#if (RTC_TAMP_NB == 2U)
#define RTC_TAMPER_MASKABLE_NB             2U
#else
#define RTC_TAMPER_MASKABLE_NB             3U
#endif /* (RTC_TAMP_NB == 2U) */

/**
  * @}
  */

/** @defgroup RTCEx_Tamper_EraseBackUp  RTCEx Tamper EraseBackUp
  * @{
  */
#define RTC_TAMPER_ERASE_BACKUP_ENABLE     0U
#define RTC_TAMPER_ERASE_BACKUP_DISABLE    1U
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Filter  RTCEx Tamper Filter
  * @{
  */
#define RTC_TAMPERFILTER_DISABLE           0U                    /*!< Tamper filter is disabled */
#define RTC_TAMPERFILTER_2SAMPLE           TAMP_FLTCR_TAMPFLT_0  /*!< Tamper is activated after 2 consecutive samples at the active level */
#define RTC_TAMPERFILTER_4SAMPLE           TAMP_FLTCR_TAMPFLT_1  /*!< Tamper is activated after 4 consecutive samples at the active level */
#define RTC_TAMPERFILTER_8SAMPLE           TAMP_FLTCR_TAMPFLT    /*!< Tamper is activated after 8 consecutive samples at the active level */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Sampling_Frequencies  RTCEx Tamper Sampling Frequencies
  * @{
  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV32768  0U                                                  /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 32768 */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV16384  TAMP_FLTCR_TAMPFREQ_0                               /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 16384 */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV8192   TAMP_FLTCR_TAMPFREQ_1                               /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 8192  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV4096   (TAMP_FLTCR_TAMPFREQ_0 | TAMP_FLTCR_TAMPFREQ_1)     /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 4096  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV2048   TAMP_FLTCR_TAMPFREQ_2                               /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 2048  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV1024   (TAMP_FLTCR_TAMPFREQ_0 | TAMP_FLTCR_TAMPFREQ_2)     /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 1024  */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV512    (TAMP_FLTCR_TAMPFREQ_1 | TAMP_FLTCR_TAMPFREQ_2)     /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 512   */
#define RTC_TAMPERSAMPLINGFREQ_RTCCLK_DIV256    (TAMP_FLTCR_TAMPFREQ_0 | TAMP_FLTCR_TAMPFREQ_1 | \
                                                 TAMP_FLTCR_TAMPFREQ_2)                             /*!< Each of the tamper inputs are sampled with a frequency =  RTCCLK / 256   */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pin_Precharge_Duration  RTCEx Tamper Pin Precharge Duration
  * @{
  */
#define RTC_TAMPERPRECHARGEDURATION_1RTCCLK  0U                                              /*!< Tamper pins are pre-charged before sampling during 1 RTCCLK cycle  */
#define RTC_TAMPERPRECHARGEDURATION_2RTCCLK  TAMP_FLTCR_TAMPPRCH_0                           /*!< Tamper pins are pre-charged before sampling during 2 RTCCLK cycles */
#define RTC_TAMPERPRECHARGEDURATION_4RTCCLK  TAMP_FLTCR_TAMPPRCH_1                           /*!< Tamper pins are pre-charged before sampling during 4 RTCCLK cycles */
#define RTC_TAMPERPRECHARGEDURATION_8RTCCLK  (TAMP_FLTCR_TAMPPRCH_0 | TAMP_FLTCR_TAMPPRCH_1) /*!< Tamper pins are pre-charged before sampling during 8 RTCCLK cycles */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Pull_UP  RTCEx Tamper Pull UP
  * @{
  */
#define RTC_TAMPER_PULLUP_ENABLE           0U                    /*!< Tamper pins are pre-charged before sampling */
#define RTC_TAMPER_PULLUP_DISABLE          TAMP_FLTCR_TAMPPUDIS  /*!< Tamper pins pre-charge is disabled          */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_TimeStampOnTamperDetection RTCEx Tamper TimeStamp On Tamper Detection Definitions
  * @{
  */
#define RTC_TIMESTAMPONTAMPERDETECTION_DISABLE  0U               /*!< TimeStamp on Tamper Detection event is not saved */
#define RTC_TIMESTAMPONTAMPERDETECTION_ENABLE   RTC_CR_TAMPTS    /*!< TimeStamp on Tamper Detection event saved        */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Detection_Output RTCEx Tamper detection output Definitions
  * @{
  */
#if defined(RTC_CR_TAMPOE)
#define RTC_TAMPERDETECTIONOUTPUT_DISABLE  0U                    /*!< Tamper detection output disable on TAMPALRM */
#define RTC_TAMPERDETECTIONOUTPUT_ENABLE   RTC_CR_TAMPOE         /*!< Tamper detection output enable on TAMPALRM  */
#endif /* RTC_CR_TAMPOE */
/**
  * @}
  */


/** @defgroup RTCEx_Tamper_Interrupt  RTCEx Tamper Interrupt
  * @{
  */
#define RTC_IT_TAMP_1                      TAMP_IER_TAMP1IE      /*!< Tamper 1 Interrupt */
#define RTC_IT_TAMP_2                      TAMP_IER_TAMP2IE      /*!< Tamper 2 Interrupt */
#if (RTC_TAMP_NB == 2U)
#define RTC_IT_TAMP_ALL                    (RTC_IT_TAMP_1 | RTC_IT_TAMP_2)
#else
#define RTC_IT_TAMP_3                      TAMP_IER_TAMP3IE      /*!< Tamper 3 Interrupt */
#define RTC_IT_TAMP_4                      TAMP_IER_TAMP4IE      /*!< Tamper 4 Interrupt */
#define RTC_IT_TAMP_5                      TAMP_IER_TAMP5IE      /*!< Tamper 5 Interrupt */
#define RTC_IT_TAMP_6                      TAMP_IER_TAMP6IE      /*!< Tamper 6 Interrupt */
#define RTC_IT_TAMP_7                      TAMP_IER_TAMP7IE      /*!< Tamper 7 Interrupt */
#define RTC_IT_TAMP_8                      TAMP_IER_TAMP8IE      /*!< Tamper 8 Interrupt */
#define RTC_IT_TAMP_ALL                    (RTC_IT_TAMP_1 | RTC_IT_TAMP_2 |\
                                            RTC_IT_TAMP_3 | RTC_IT_TAMP_4 |\
                                            RTC_IT_TAMP_5 | RTC_IT_TAMP_6 |\
                                            RTC_IT_TAMP_7 | RTC_IT_TAMP_8 )
#endif /* RTC_TAMP_NB */
/**
  * @}
  */

/** @defgroup RTCEx_Internal_Tamper_Interrupt  RTCEx Internal Tamper Interrupt
  * @{
  */
#define RTC_IT_INT_TAMP_1                  TAMP_IER_ITAMP1IE     /*!< Tamper 1 internal Interrupt  */
#define RTC_IT_INT_TAMP_2                  TAMP_IER_ITAMP2IE     /*!< Tamper 2 internal Interrupt  */
#define RTC_IT_INT_TAMP_3                  TAMP_IER_ITAMP3IE     /*!< Tamper 3 internal Interrupt  */
#define RTC_IT_INT_TAMP_4                  TAMP_IER_ITAMP4IE     /*!< Tamper 4 internal Interrupt  */
#define RTC_IT_INT_TAMP_5                  TAMP_IER_ITAMP5IE     /*!< Tamper 5 internal Interrupt  */
#define RTC_IT_INT_TAMP_6                  TAMP_IER_ITAMP6IE     /*!< Tamper 6 internal Interrupt  */
#define RTC_IT_INT_TAMP_7                  TAMP_IER_ITAMP7IE     /*!< Tamper 7 internal Interrupt  */
#define RTC_IT_INT_TAMP_8                  TAMP_IER_ITAMP8IE     /*!< Tamper 8 internal Interrupt  */
#define RTC_IT_INT_TAMP_9                  TAMP_IER_ITAMP9IE     /*!< Tamper 9 internal Interrupt  */
#define RTC_IT_INT_TAMP_11                 TAMP_IER_ITAMP11IE    /*!< Tamper 11 internal Interrupt */
#define RTC_IT_INT_TAMP_12                 TAMP_IER_ITAMP12IE    /*!< Tamper 12 internal Interrupt */
#define RTC_IT_INT_TAMP_13                 TAMP_IER_ITAMP13IE    /*!< Tamper 13 internal Interrupt */
#define RTC_IT_INT_TAMP_15                 TAMP_IER_ITAMP15IE    /*!< Tamper 15 internal Interrupt */
#define RTC_IT_INT_TAMP_ALL                (RTC_IT_INT_TAMP_1 | RTC_IT_INT_TAMP_2 |\
                                            RTC_IT_INT_TAMP_3 | RTC_IT_INT_TAMP_4 |\
                                            RTC_IT_INT_TAMP_5 | RTC_IT_INT_TAMP_6 |\
                                            RTC_IT_INT_TAMP_7 | RTC_IT_INT_TAMP_8 |\
                                            RTC_IT_INT_TAMP_9 | RTC_IT_INT_TAMP_11 |\
                                            RTC_IT_INT_TAMP_12 |RTC_IT_INT_TAMP_13 |\
                                            RTC_IT_INT_TAMP_15)
/**
  * @}
  */

/** @defgroup RTCEx_Flags  RTCEx Flags
  * @{
  */
#define RTC_FLAG_TAMP_1                    TAMP_SR_TAMP1F
#define RTC_FLAG_TAMP_2                    TAMP_SR_TAMP2F
#if (RTC_TAMP_NB == 2U)
#define RTC_FLAG_TAMP_ALL                  (TAMP_SR_TAMP1F | TAMP_SR_TAMP2F)
#else
#define RTC_FLAG_TAMP_3                    TAMP_SR_TAMP3F
#define RTC_FLAG_TAMP_4                    TAMP_SR_TAMP4F
#define RTC_FLAG_TAMP_5                    TAMP_SR_TAMP5F
#define RTC_FLAG_TAMP_6                    TAMP_SR_TAMP6F
#define RTC_FLAG_TAMP_7                    TAMP_SR_TAMP7F
#define RTC_FLAG_TAMP_8                    TAMP_SR_TAMP8F
#define RTC_FLAG_TAMP_ALL                  (RTC_FLAG_TAMP_1 | RTC_FLAG_TAMP_2 | RTC_FLAG_TAMP_3 |\
                                            RTC_FLAG_TAMP_4 | RTC_FLAG_TAMP_5 | RTC_FLAG_TAMP_6 |\
                                            RTC_FLAG_TAMP_7 | RTC_FLAG_TAMP_8)
#endif /* RTC_TAMP_NB */

#define RTC_FLAG_INT_TAMP_1                TAMP_SR_ITAMP1F
#define RTC_FLAG_INT_TAMP_2                TAMP_SR_ITAMP2F
#define RTC_FLAG_INT_TAMP_3                TAMP_SR_ITAMP3F
#define RTC_FLAG_INT_TAMP_4                TAMP_SR_ITAMP4F
#define RTC_FLAG_INT_TAMP_5                TAMP_SR_ITAMP5F
#define RTC_FLAG_INT_TAMP_6                TAMP_SR_ITAMP6F
#define RTC_FLAG_INT_TAMP_7                TAMP_SR_ITAMP7F
#define RTC_FLAG_INT_TAMP_8                TAMP_SR_ITAMP8F
#define RTC_FLAG_INT_TAMP_9                TAMP_SR_ITAMP9F
#define RTC_FLAG_INT_TAMP_11               TAMP_SR_ITAMP11F
#define RTC_FLAG_INT_TAMP_12               TAMP_SR_ITAMP12F
#define RTC_FLAG_INT_TAMP_13               TAMP_SR_ITAMP13F
#define RTC_FLAG_INT_TAMP_15               TAMP_SR_ITAMP15F
#define RTC_FLAG_INT_TAMP_ALL              (RTC_FLAG_INT_TAMP_1  | RTC_FLAG_INT_TAMP_2  |\
                                            RTC_FLAG_INT_TAMP_3  | RTC_FLAG_INT_TAMP_4  |\
                                            RTC_FLAG_INT_TAMP_5  | RTC_FLAG_INT_TAMP_6  |\
                                            RTC_FLAG_INT_TAMP_7  | RTC_FLAG_INT_TAMP_8  |\
                                            RTC_FLAG_INT_TAMP_9  | RTC_FLAG_INT_TAMP_11 |\
                                            RTC_FLAG_INT_TAMP_12 | RTC_FLAG_INT_TAMP_13 |\
                                            RTC_FLAG_INT_TAMP_15)
/**
  * @}
  */


/** @defgroup RTCEx_ActiveTamper_Enable RTCEx_ActiveTamper_Enable Definitions
  * @{
  */
#define RTC_ATAMP_ENABLE                   1U
#define RTC_ATAMP_DISABLE                  0U
/**
  * @}
  */

/** @defgroup RTCEx_ActiveTamper_Interrupt RTCEx_ActiveTamper_Interrupt Definitions
  * @{
  */
#define RTC_ATAMP_INTERRUPT_ENABLE         1U
#define RTC_ATAMP_INTERRUPT_DISABLE        0U
/**
  * @}
  */

/** @defgroup RTCEx_ActiveTamper_Filter RTCEx_ActiveTamper_Filter Definitions
  * @{
  */
#define RTC_ATAMP_FILTER_ENABLE            TAMP_ATCR1_FLTEN
#define RTC_ATAMP_FILTER_DISABLE           0U
/**
  * @}
  */

/** @defgroup RTCEx_ActiveTamper_Async_prescaler RTCEx Active_Tamper_Asynchronous_Prescaler clock Definitions
  * @{
  */
#define RTC_ATAMP_ASYNCPRES_RTCCLK         0U                                                                   /*!< RTCCLK      */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_2       TAMP_ATCR1_ATCKSEL_0                                                 /*!< RTCCLK/2    */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_4       TAMP_ATCR1_ATCKSEL_1                                                 /*!< RTCCLK/4    */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_8       (TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0)                        /*!< RTCCLK/8    */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_16      TAMP_ATCR1_ATCKSEL_2                                                 /*!< RTCCLK/16   */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_32      (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_0)                        /*!< RTCCLK/32   */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_64      (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1)                        /*!< RTCCLK/64   */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_128     (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0) /*!< RTCCLK/128  */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_2048    (TAMP_ATCR1_ATCKSEL_3 | TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0) /*!< RTCCLK/2048 */
/**
  * @}
  */

/** @defgroup RTCEx_ActiveTamper_Sel  RTCEx Active Tamper selection Definition
  * @{
  */
#define RTC_ATAMP_1                        0U                    /*!< Tamper 1 */
#define RTC_ATAMP_2                        1U                    /*!< Tamper 2 */
#define RTC_ATAMP_3                        2U                    /*!< Tamper 3 */
#define RTC_ATAMP_4                        3U                    /*!< Tamper 4 */
#define RTC_ATAMP_5                        4U                    /*!< Tamper 5 */
#define RTC_ATAMP_6                        5U                    /*!< Tamper 6 */
#define RTC_ATAMP_7                        6U                    /*!< Tamper 7 */
#define RTC_ATAMP_8                        7U                    /*!< Tamper 8 */
/**
  * @}
  */

/** @defgroup RTCEx_MonotonicCounter_Instance  RTCEx Monotonic Counter Instance Definition
  * @{
  */
#define RTC_MONOTONIC_COUNTER_1            0U                    /*!< Monotonic counter 1 */
/**
  * @}
  */


/** @defgroup RTCEx_Backup_Registers  RTCEx Backup Registers Definition
  * @{
  */
#define RTC_BKP_NUMBER                     RTC_BKP_NB
#define RTC_BKP_DR0                        0x00U
#define RTC_BKP_DR1                        0x01U
#define RTC_BKP_DR2                        0x02U
#define RTC_BKP_DR3                        0x03U
#define RTC_BKP_DR4                        0x04U
#define RTC_BKP_DR5                        0x05U
#define RTC_BKP_DR6                        0x06U
#define RTC_BKP_DR7                        0x07U
#define RTC_BKP_DR8                        0x08U
#define RTC_BKP_DR9                        0x09U
#define RTC_BKP_DR10                       0x0AU
#define RTC_BKP_DR11                       0x0BU
#define RTC_BKP_DR12                       0x0CU
#define RTC_BKP_DR13                       0x0DU
#define RTC_BKP_DR14                       0x0EU
#define RTC_BKP_DR15                       0x0FU
#define RTC_BKP_DR16                       0x10U
#define RTC_BKP_DR17                       0x11U
#define RTC_BKP_DR18                       0x12U
#define RTC_BKP_DR19                       0x13U
#define RTC_BKP_DR20                       0x14U
#define RTC_BKP_DR21                       0x15U
#define RTC_BKP_DR22                       0x16U
#define RTC_BKP_DR23                       0x17U
#define RTC_BKP_DR24                       0x18U
#define RTC_BKP_DR25                       0x19U
#define RTC_BKP_DR26                       0x1AU
#define RTC_BKP_DR27                       0x1BU
#define RTC_BKP_DR28                       0x1CU
#define RTC_BKP_DR29                       0x1DU
#define RTC_BKP_DR30                       0x1EU
#define RTC_BKP_DR31                       0x1FU
/**
  * @}
  */

/** @defgroup RTCEx_Binary_Mode RTC Binary Mode (32-bit free-running counter configuration).
  *           Warning : It Should not be confused with the Binary format @ref RTC_Input_parameter_format_definitions.
  * @{
  */
#define RTC_BINARY_NONE                    0U                    /*!< Free running BCD calendar mode (Binary mode disabled) */
#define RTC_BINARY_ONLY                    RTC_ICSR_BIN_0        /*!< Free running Binary mode (BCD mode disabled)          */
#define RTC_BINARY_MIX                     RTC_ICSR_BIN_1        /*!< Free running BCD calendar and Binary modes            */
/**
  * @}
  */

/** @defgroup RTCEx_Binary_mix_BCDU If Binary mode is RTC_BINARY_MIX, the BCD calendar second is incremented
  *           using the SSR Least Significant Bits.
  * @{
  */
#define RTC_BINARY_MIX_BCDU_0              0U                           /*!<  The 1s BCD calendar increment is generated each time SS[7:0] = 0  */
#define RTC_BINARY_MIX_BCDU_1              (0x1UL << RTC_ICSR_BCDU_Pos) /*!<  The 1s BCD calendar increment is generated each time SS[8:0] = 0  */
#define RTC_BINARY_MIX_BCDU_2              (0x2UL << RTC_ICSR_BCDU_Pos) /*!<  The 1s BCD calendar increment is generated each time SS[9:0] = 0  */
#define RTC_BINARY_MIX_BCDU_3              (0x3UL << RTC_ICSR_BCDU_Pos) /*!<  The 1s BCD calendar increment is generated each time SS[10:0] = 0 */
#define RTC_BINARY_MIX_BCDU_4              (0x4UL << RTC_ICSR_BCDU_Pos) /*!<  The 1s BCD calendar increment is generated each time SS[11:0] = 0 */
#define RTC_BINARY_MIX_BCDU_5              (0x5UL << RTC_ICSR_BCDU_Pos) /*!<  The 1s BCD calendar increment is generated each time SS[12:0] = 0 */
#define RTC_BINARY_MIX_BCDU_6              (0x6UL << RTC_ICSR_BCDU_Pos) /*!<  The 1s BCD calendar increment is generated each time SS[13:0] = 0 */
#define RTC_BINARY_MIX_BCDU_7              (0x7UL << RTC_ICSR_BCDU_Pos) /*!<  The 1s BCD calendar increment is generated each time SS[14:0] = 0 */
/**
  * @}
  */

/** @defgroup RTCEx_Alarm_Sub_Seconds_binary_Masks_Definitions RTC Alarm Sub Seconds with binary or mix mode
  *           Masks Definitions.
  * @{
  */
#define RTC_ALARMSUBSECONDBINMASK_ALL      0U                                /*!< All Alarm SS fields are masked.There is no comparison on sub seconds for Alarm */
#define RTC_ALARMSUBSECONDBINMASK_SS31_1   (1UL << RTC_ALRMASSR_MASKSS_Pos)  /*!< SS[31:1] are don't care in Alarm comparison. Only SS[0] is compared            */
#define RTC_ALARMSUBSECONDBINMASK_SS31_2   (2UL << RTC_ALRMASSR_MASKSS_Pos)  /*!< SS[31:2] are don't care in Alarm comparison. Only SS[1:0] are compared         */
#define RTC_ALARMSUBSECONDBINMASK_SS31_3   (3UL << RTC_ALRMASSR_MASKSS_Pos)  /*!< SS[31:3] are don't care in Alarm comparison. Only SS[2:0] are compared         */
#define RTC_ALARMSUBSECONDBINMASK_SS31_4   (4UL << RTC_ALRMASSR_MASKSS_Pos)  /*!< SS[31:4] are don't care in Alarm comparison. Only SS[3:0] are compared         */
#define RTC_ALARMSUBSECONDBINMASK_SS31_5   (5UL << RTC_ALRMASSR_MASKSS_Pos)  /*!< SS[31:5] are don't care in Alarm comparison. Only SS[4:0] are compared         */
#define RTC_ALARMSUBSECONDBINMASK_SS31_6   (6UL << RTC_ALRMASSR_MASKSS_Pos)  /*!< SS[31:6] are don't care in Alarm comparison. Only SS[5:0] are compared         */
#define RTC_ALARMSUBSECONDBINMASK_SS31_7   (7UL << RTC_ALRMASSR_MASKSS_Pos)  /*!< SS[31:7] are don't care in Alarm comparison. Only SS[6:0] are compared         */
#define RTC_ALARMSUBSECONDBINMASK_SS31_8   (8UL << RTC_ALRMASSR_MASKSS_Pos)  /*!< SS[31:8] are don't care in Alarm comparison. Only SS[7:0] are compared         */
#define RTC_ALARMSUBSECONDBINMASK_SS31_9   (9UL << RTC_ALRMASSR_MASKSS_Pos)  /*!< SS[31:9] are don't care in Alarm comparison. Only SS[8:0] are compared         */
#define RTC_ALARMSUBSECONDBINMASK_SS31_10  (10UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:10] are don't care in Alarm comparison. Only SS[9:0] are compared        */
#define RTC_ALARMSUBSECONDBINMASK_SS31_11  (11UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:11] are don't care in Alarm comparison. Only SS[10:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_12  (12UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:12] are don't care in Alarm comparison.Only SS[11:0] are compared        */
#define RTC_ALARMSUBSECONDBINMASK_SS31_13  (13UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:13] are don't care in Alarm comparison. Only SS[12:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_14  (14UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:14] are don't care in Alarm comparison. Only SS[13:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_15  (15UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:15] are don't care in Alarm comparison. Only SS[14:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_16  (16UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:16] are don't care in Alarm comparison. Only SS[15:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_17  (17UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:17] are don't care in Alarm comparison. Only SS[16:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_18  (18UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:18] are don't care in Alarm comparison. Only SS[17:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_19  (19UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:19] are don't care in Alarm comparison. Only SS[18:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_20  (20UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:20] are don't care in Alarm comparison. Only SS[19:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_21  (21UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:21] are don't care in Alarm comparison. Only SS[20:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_22  (22UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:22] are don't care in Alarm comparison. Only SS[21:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_23  (23UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:23] are don't care in Alarm comparison. Only SS[22:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_24  (24UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:24] are don't care in Alarm comparison. Only SS[23:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_25  (25UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:25] are don't care in Alarm comparison. Only SS[24:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_26  (26UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:26] are don't care in Alarm comparison. Only SS[25:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_27  (27UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:27] are don't care in Alarm comparison. Only SS[26:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_28  (28UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:28] are don't care in Alarm comparison. Only SS[27:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_29  (29UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:29] are don't care in Alarm comparison. Only SS[28:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31_30  (30UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31:30] are don't care in Alarm comparison. Only SS[29:0] are compared       */
#define RTC_ALARMSUBSECONDBINMASK_SS31     (31UL << RTC_ALRMASSR_MASKSS_Pos) /*!< SS[31] is don't care in Alarm comparison. Only SS[30:0] are compared           */
#define RTC_ALARMSUBSECONDBINMASK_NONE     RTC_ALRMASSR_MASKSS               /*!< SS[31:0] are compared and must match to activate alarm                         */
/**
  * @}
  */

/** @defgroup RTCEx_Alarm_Sub_Seconds_binary_Clear_Definitions RTC Alarm Sub Seconds
  *           with binary mode auto clear Definitions
  * @{
  */
#define RTC_ALARMSUBSECONDBIN_AUTOCLR_NO   0UL                   /*!< The synchronous Binary counter(SS[31:0] in RTC_SSR) is free-running */
#define RTC_ALARMSUBSECONDBIN_AUTOCLR_YES  RTC_ALRMASSR_SSCLR
/*!< The synchronous Binary counter (SS[31:0] in RTC_SSR) is running from 0xFFFF FFFF to RTC_ALRMABINR -> SS[31:0]
     value and is automatically reloaded with 0xFFFF FFFF whenreaching RTC_ALRMABINR -> SS[31:0]. */
/**
  * @}
  */

#ifdef RTC_SECCFGR_SEC
/** @defgroup RTCEx_RTC_Secure_Full  RTCEx Secure Definition
  * @{
  */
#define RTC_SECURE_FULL_YES                RTC_SECCFGR_SEC       /*!< RTC full secure */
#define RTC_SECURE_FULL_NO                 0U                    /*!< RTC is not full secure, features can be unsecure. See RTCEx_RTC_NonSecure_Features */
/**
  * @}
  */

/** @defgroup RTCEx_RTC_NonSecure_Features  RTCEx Secure Features Definition
  * @{
  */
#define RTC_NONSECURE_FEATURE_NONE         0U
#define RTC_NONSECURE_FEATURE_INIT         RTC_SECCFGR_INITSEC   /*!< Initialization */
#define RTC_NONSECURE_FEATURE_CAL          RTC_SECCFGR_CALSEC    /*!< Calibration    */
#define RTC_NONSECURE_FEATURE_TS           RTC_SECCFGR_TSSEC     /*!< Time stamp     */
#define RTC_NONSECURE_FEATURE_WUT          RTC_SECCFGR_WUTSEC    /*!< Wake up timer  */
#define RTC_NONSECURE_FEATURE_ALRA         RTC_SECCFGR_ALRASEC   /*!< Alarm A        */
#define RTC_NONSECURE_FEATURE_ALRB         RTC_SECCFGR_ALRBSEC   /*!< Alarm B        */

#define RTC_NONSECURE_FEATURE_ALL          (RTC_SECCFGR_INITSEC |  RTC_SECCFGR_CALSEC | \
                                            RTC_SECCFGR_TSSEC | RTC_SECCFGR_WUTSEC | \
                                            RTC_SECCFGR_ALRASEC | RTC_SECCFGR_ALRBSEC)
/**
  * @}
  */
#endif /* RTC_SECCFGR_SEC */

#ifdef TAMP_SECCFGR_TAMPSEC
/** @defgroup RTCEx_TAMP_Secure_Full  RTCEx TAMP Secure Definition
  * @{
  */
#define TAMP_SECURE_FULL_YES               TAMP_SECCFGR_TAMPSEC  /*!< TAMPER full secure   */
#define TAMP_SECURE_FULL_NO                0U                    /*!< TAMPER is not secure */
/**
  * @}
  */
#endif /* TAMP_SECCFGR_TAMPSEC*/

#ifdef TAMP_SECCFGR_CNT1SEC
/** @defgroup RTCEx_TAMP_Monotonic_Counter_Secure  RTCEx TAMP Monotonic Counter Secure Definition
  * @{
  */
#define TAMP_MONOTONIC_CNT_SECURE_YES      TAMP_SECCFGR_CNT1SEC  /*!< TAMPER Monotonic Counter secure        */
#define TAMP_MONOTONIC_CNT_SECURE_NO       0U                    /*!< TAMPER Monotonic Counter is not secure */
/**
  * @}
  */
#endif /* TAMP_SECCFGR_CNT1SEC */

/** @defgroup RTCEx_RTC_Privilege_Full  RTCEx Privilege Full Definition
  * @{
  */
#define RTC_PRIVILEGE_FULL_YES             RTC_PRIVCFGR_PRIV
#define RTC_PRIVILEGE_FULL_NO              0U
/**
  * @}
  */

/** @defgroup RTCEx_RTC_Privilege_Features  RTCEx Privilege Features Definition
  * @{
  */
#define RTC_PRIVILEGE_FEATURE_NONE         0U
#define RTC_PRIVILEGE_FEATURE_INIT         RTC_PRIVCFGR_INITPRIV /*!< Initialization */
#define RTC_PRIVILEGE_FEATURE_CAL          RTC_PRIVCFGR_CALPRIV  /*!< Calibration    */
#define RTC_PRIVILEGE_FEATURE_TS           RTC_PRIVCFGR_TSPRIV   /*!< Time stamp     */
#define RTC_PRIVILEGE_FEATURE_WUT          RTC_PRIVCFGR_WUTPRIV  /*!< Wake up timer  */
#define RTC_PRIVILEGE_FEATURE_ALRA         RTC_PRIVCFGR_ALRAPRIV /*!< Alarm A        */
#define RTC_PRIVILEGE_FEATURE_ALRB         RTC_PRIVCFGR_ALRBPRIV /*!< Alarm B        */

#define RTC_PRIVILEGE_FEATURE_ALL          (RTC_PRIVCFGR_INITPRIV |  RTC_PRIVCFGR_CALPRIV | \
                                            RTC_PRIVCFGR_TSPRIV | RTC_PRIVCFGR_WUTPRIV | \
                                            RTC_PRIVCFGR_ALRAPRIV | RTC_PRIVCFGR_ALRBPRIV)
/**
  * @}
  */

/** @defgroup RTCEx_TAMP_Privilege_Full  RTCEx TAMP security Definition
  * @{
  */
#define TAMP_PRIVILEGE_FULL_YES            TAMP_PRIVCFGR_TAMPPRIV
#define TAMP_PRIVILEGE_FULL_NO             0U
/**
  * @}
  */

/** @defgroup RTCEx_TAMP_Device_Secrets_Erase_Conf  RTCEx TAMP Device Secrets Erase Configuration Definition
  * @{
  */
#define TAMP_DEVICESECRETS_ERASE_NONE      0U                    /*! < No Erase */
#define TAMP_DEVICESECRETS_ERASE_BKPSRAM   TAMP_ERCFGR_ERCFG0    /*!< Backup SRAM */
/**
  * @}
  */

/** @defgroup RTCEx_TAMP_Monotonic_Counter_Privilege  RTCEx TAMP Monotonic Counter Privilege Definition
  * @{
  */
#define TAMP_MONOTONIC_CNT_PRIVILEGE_YES   TAMP_PRIVCFGR_CNT1PRIV
#define TAMP_MONOTONIC_CNT_PRIVILEGE_NO    0U
/**
  * @}
  */

/** @defgroup RTCEx_Backup_Reg_Privilege_zone  RTCEx Privilege Backup register privilege zone Definition
  * @{
  */
#define RTC_PRIVILEGE_BKUP_ZONE_NONE       0U
#define RTC_PRIVILEGE_BKUP_ZONE_1          TAMP_PRIVCFGR_BKPRWPRIV
#define RTC_PRIVILEGE_BKUP_ZONE_2          TAMP_PRIVCFGR_BKPWPRIV
#define RTC_PRIVILEGE_BKUP_ZONE_ALL        (RTC_PRIVILEGE_BKUP_ZONE_1 | RTC_PRIVILEGE_BKUP_ZONE_2)
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
  *            @arg @ref RTC_FLAG_ITSF                Internal Time-stamp flag
  *            @arg @ref RTC_FLAG_TSOVF               Time-stamp overflow flag
  *            @arg @ref RTC_FLAG_TSF                 Time-stamp flag
  *            @arg @ref RTC_FLAG_WUTF                Wakeup timer flag
  *            @arg @ref RTC_FLAG_ALRBF               Alarm B flag
  *            @arg @ref RTC_FLAG_ALRAF               Alarm A flag
  * @retval None
  */
#define __HAL_RTC_GET_FLAG(__HANDLE__, __FLAG__)    (((((__FLAG__)) >> 8U) == 1U) ? \
                                                     (RTC->ICSR & (1U << (((uint16_t)(__FLAG__)) & RTC_FLAG_MASK))) : \
                                                     (RTC->SR & (1U << (((uint16_t)(__FLAG__)) & RTC_FLAG_MASK))))

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
#define __HAL_RTC_WAKEUPTIMER_GET_IT(__HANDLE__, __INTERRUPT__)       ((((RTC->MISR) & ((__INTERRUPT__)>> 12U)) !=\
                                                                        0UL) ? 1UL : 0UL)

/**
  * @brief  Check whether the specified RTC Wake Up timer interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Wake Up timer interrupt sources to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_WUT  WakeUpTimer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)   ((((RTC->CR) & (__INTERRUPT__)) != \
                                                                           0UL) ? 1UL : 0UL)

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
#define __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(__HANDLE__, __FLAG__)  (__HAL_RTC_CLEAR_FLAG((__HANDLE__), RTC_CLEAR_WUTF))
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
#define __HAL_RTC_TIMESTAMP_GET_IT(__HANDLE__, __INTERRUPT__)        ((((RTC->MISR) & ((__INTERRUPT__)>> 12U)) != \
                                                                       0U) ? 1UL : 0UL)

/**
  * @brief  Check whether the specified RTC Time Stamp interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Time Stamp interrupt source to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_TS TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)     ((((RTC->CR) & (__INTERRUPT__)) != 0U) ?\
                                                                          1UL : 0UL)

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
#define __HAL_RTC_INTERNAL_TIMESTAMP_GET_FLAG(__HANDLE__, __FLAG__)     (__HAL_RTC_GET_FLAG((__HANDLE__),\
                                                                         (__FLAG__)))

/**
  * @brief  Clear the RTC Internal Time Stamps pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Internal Time Stamp Flag source to clear.
  * This parameter can be:
  *             @arg @ref RTC_FLAG_ITSF
  * @retval None
  */
#define __HAL_RTC_INTERNAL_TIMESTAMP_CLEAR_FLAG(__HANDLE__, __FLAG__)     (__HAL_RTC_CLEAR_FLAG((__HANDLE__),\
                                                                           RTC_CLEAR_ITSF))

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

#if defined(RTC_CR_TAMPOE)
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

#endif /* RTC_CR_TAMPOE */

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
  *            @arg  RTC_TAMPER_3: Tamper3
  *            @arg  RTC_TAMPER_4: Tamper4
  *            @arg  RTC_TAMPER_5: Tamper5
  *            @arg  RTC_TAMPER_6: Tamper6
  *            @arg  RTC_TAMPER_7: Tamper7
  *            @arg  RTC_TAMPER_8: Tamper8
  * @retval None
  */
#define __HAL_RTC_TAMPER_ENABLE(__HANDLE__, __TAMPER__)           (TAMP->CR1 |= (__TAMPER__))

/**
  * @brief  Disable the TAMP Tamper input detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __TAMPER__ specifies the RTC Tamper sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg  RTC_TAMPER_ALL: All tampers
  *            @arg  RTC_TAMPER_1: Tamper1
  *            @arg  RTC_TAMPER_2: Tamper2
  *            @arg  RTC_TAMPER_3: Tamper3
  *            @arg  RTC_TAMPER_4: Tamper4
  *            @arg  RTC_TAMPER_5: Tamper5
  *            @arg  RTC_TAMPER_6: Tamper6
  *            @arg  RTC_TAMPER_7: Tamper7
  *            @arg  RTC_TAMPER_8: Tamper8
  */
#define __HAL_RTC_TAMPER_DISABLE(__HANDLE__, __TAMPER__)           (TAMP->CR1 &= ~(__TAMPER__))


/**************************************************************************************************/
/**
  * @brief  Enable the TAMP Tamper interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt sources to be enabled.
  *          This parameter can be any combination of the following values:
  *            @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *            @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *            @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  *            @arg  RTC_IT_TAMP_3: Tamper3 interrupt
  *            @arg  RTC_IT_TAMP_4: Tamper4 interrupt
  *            @arg  RTC_IT_TAMP_5: Tamper5 interrupt
  *            @arg  RTC_IT_TAMP_6: Tamper6 interrupt
  *            @arg  RTC_IT_TAMP_7: Tamper7 interrupt
  *            @arg  RTC_IT_TAMP_8: Tamper8 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_ENABLE_IT(__HANDLE__, __INTERRUPT__)        (TAMP->IER |= (__INTERRUPT__))

/**
  * @brief  Disable the TAMP Tamper interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *            @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *            @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  *            @arg  RTC_IT_TAMP_3: Tamper3 interrupt
  *            @arg  RTC_IT_TAMP_4: Tamper4 interrupt
  *            @arg  RTC_IT_TAMP_5: Tamper5 interrupt
  *            @arg  RTC_IT_TAMP_6: Tamper6 interrupt
  *            @arg  RTC_IT_TAMP_7: Tamper7 interrupt
  *            @arg  RTC_IT_TAMP_8: Tamper8 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_DISABLE_IT(__HANDLE__, __INTERRUPT__)       (TAMP->IER &= ~(__INTERRUPT__))


/**************************************************************************************************/
/**
  * @brief  Check whether the specified RTC Tamper interrupt has occurred or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt to check.
  *         This parameter can be:
  *            @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *            @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *            @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  *            @arg  RTC_IT_TAMP_3: Tamper3 interrupt
  *            @arg  RTC_IT_TAMP_4: Tamper4 interrupt
  *            @arg  RTC_IT_TAMP_5: Tamper5 interrupt
  *            @arg  RTC_IT_TAMP_6: Tamper6 interrupt
  *            @arg  RTC_IT_TAMP_7: Tamper7 interrupt
  *            @arg  RTC_IT_TAMP_8: Tamper8 interrupt
  *            @arg  RTC_IT_INT_TAMP_ALL: All Internal Tamper interrupts
  *            @arg  RTC_IT_INT_TAMP_1: Internal Tamper1 interrupt
  *            @arg  RTC_IT_INT_TAMP_2: Internal Tamper2 interrupt
  *            @arg  RTC_IT_INT_TAMP_3: Internal Tamper3 interrupt
  *            @arg  RTC_IT_INT_TAMP_4: Internal Tamper4 interrupt
  *            @arg  RTC_IT_INT_TAMP_5: Internal Tamper5 interrupt
  *            @arg  RTC_IT_INT_TAMP_6: Internal Tamper6 interrupt
  *            @arg  RTC_IT_INT_TAMP_7: Internal Tamper7 interrupt
  *            @arg  RTC_IT_INT_TAMP_8: Internal Tamper8 interrupt
  *            @arg  RTC_IT_INT_TAMP_9: Internal Tamper9 interrupt
  *            @arg  RTC_IT_INT_TAMP_11: Internal Tamper11 interrupt
  *            @arg  RTC_IT_INT_TAMP_12: Internal Tamper12 interrupt
  *            @arg  RTC_IT_INT_TAMP_13: Internal Tamper13 interrupt
  *            @arg  RTC_IT_INT_TAMP_15: Internal Tamper15 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT(__HANDLE__, __INTERRUPT__)    ((((TAMP->MISR) & (__INTERRUPT__)) != 0U) ? 1UL : 0UL)

/**
  * @brief  Check whether the specified RTC Tamper interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt source to check.
  *         This parameter can be:
  *            @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *            @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *            @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  *            @arg  RTC_IT_TAMP_3: Tamper3 interrupt
  *            @arg  RTC_IT_TAMP_4: Tamper4 interrupt
  *            @arg  RTC_IT_TAMP_5: Tamper5 interrupt
  *            @arg  RTC_IT_TAMP_6: Tamper6 interrupt
  *            @arg  RTC_IT_TAMP_7: Tamper7 interrupt
  *            @arg  RTC_IT_TAMP_8: Tamper8 interrupt
  *            @arg  RTC_IT_INT_TAMP_ALL: All internal tampers interrupts
  *            @arg  RTC_IT_INT_TAMP_1: Internal Tamper1 interrupt
  *            @arg  RTC_IT_INT_TAMP_2: Internal Tamper2 interrupt
  *            @arg  RTC_IT_INT_TAMP_3: Internal Tamper3 interrupt
  *            @arg  RTC_IT_INT_TAMP_4: Internal Tamper4 interrupt
  *            @arg  RTC_IT_INT_TAMP_5: Internal Tamper5 interrupt
  *            @arg  RTC_IT_INT_TAMP_6: Internal Tamper6 interrupt
  *            @arg  RTC_IT_INT_TAMP_7: Internal Tamper7 interrupt
  *            @arg  RTC_IT_INT_TAMP_8: Internal Tamper8 interrupt
  *            @arg  RTC_IT_INT_TAMP_9: Internal Tamper9 interrupt
  *            @arg  RTC_IT_INT_TAMP_11: Internal Tamper11 interrupt
  *            @arg  RTC_IT_INT_TAMP_12: Internal Tamper12 interrupt
  *            @arg  RTC_IT_INT_TAMP_13: Internal Tamper13 interrupt
  *            @arg  RTC_IT_INT_TAMP_15: Internal Tamper15 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)   ((((TAMP->IER) & (__INTERRUPT__)) != \
                                                                      0U) ? 1UL : 0UL)

/**
  * @brief  Get the selected RTC Tampers flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Tamper Flag is pending or not.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP_ALL: All tampers flag
  *             @arg RTC_FLAG_TAMP_1: Tamper1 flag
  *             @arg RTC_FLAG_TAMP_2: Tamper2 flag
  *             @arg RTC_FLAG_TAMP_3: Tamper3 flag
  *             @arg RTC_FLAG_TAMP_4: Tamper4 flag
  *             @arg RTC_FLAG_TAMP_5: Tamper5 flag
  *             @arg RTC_FLAG_TAMP_6: Tamper6 flag
  *             @arg RTC_FLAG_TAMP_7: Tamper7 flag
  *             @arg RTC_FLAG_TAMP_8: Tamper8 flag
  *             @arg RTC_FLAG_INT_TAMP_1: Internal Tamper1 flag
  *             @arg RTC_FLAG_INT_TAMP_2: Internal Tamper2 flag
  *             @arg RTC_FLAG_INT_TAMP_3: Internal Tamper3 flag
  *             @arg RTC_FLAG_INT_TAMP_4: Internal Tamper4 flag
  *             @arg RTC_FLAG_INT_TAMP_5: Internal Tamper5 flag
  *             @arg RTC_FLAG_INT_TAMP_6: Internal Tamper6 flag
  *             @arg RTC_FLAG_INT_TAMP_7: Internal Tamper7 flag
  *             @arg RTC_FLAG_INT_TAMP_8: Internal Tamper8 flag
  *             @arg RTC_FLAG_INT_TAMP_9: Internal Tamper9 flag
  *             @arg RTC_FLAG_INT_TAMP_11: Internal Tamper11 flag
  *             @arg RTC_FLAG_INT_TAMP_12: Internal Tamper12 flag
  *             @arg RTC_FLAG_INT_TAMP_13: Internal Tamper13 flag
  *             @arg RTC_FLAG_INT_TAMP_15: Internal Tamper15 flag
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_FLAG(__HANDLE__, __FLAG__)        (((TAMP->SR) & (__FLAG__)) != 0U)

/**
  * @brief  Clear the RTC Tamper's pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Tamper Flag to clear.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP_ALL: All tampers flag
  *             @arg RTC_FLAG_TAMP_1: Tamper1 flag
  *             @arg RTC_FLAG_TAMP_2: Tamper2 flag
  *             @arg RTC_FLAG_TAMP_3: Tamper3 flag
  *             @arg RTC_FLAG_TAMP_4: Tamper4 flag
  *             @arg RTC_FLAG_TAMP_5: Tamper5 flag
  *             @arg RTC_FLAG_TAMP_6: Tamper6 flag
  *             @arg RTC_FLAG_TAMP_7: Tamper7 flag
  *             @arg RTC_FLAG_TAMP_8: Tamper8 flag
  *             @arg RTC_FLAG_INT_TAMP_ALL: All Internal Tamper flags
  *             @arg RTC_FLAG_INT_TAMP_1: Internal Tamper1 flag
  *             @arg RTC_FLAG_INT_TAMP_2: Internal Tamper2 flag
  *             @arg RTC_FLAG_INT_TAMP_3: Internal Tamper3 flag
  *             @arg RTC_FLAG_INT_TAMP_4: Internal Tamper4 flag
  *             @arg RTC_FLAG_INT_TAMP_5: Internal Tamper5 flag
  *             @arg RTC_FLAG_INT_TAMP_6: Internal Tamper6 flag
  *             @arg RTC_FLAG_INT_TAMP_7: Internal Tamper7 flag
  *             @arg RTC_FLAG_INT_TAMP_8: Internal Tamper8 flag
  *             @arg RTC_FLAG_INT_TAMP_9: Internal Tamper9 flag
  *             @arg RTC_FLAG_INT_TAMP_11: Internal Tamper11 flag
  *             @arg RTC_FLAG_INT_TAMP_12: Internal Tamper12 flag
  *             @arg RTC_FLAG_INT_TAMP_13: Internal Tamper13 flag
  *             @arg RTC_FLAG_INT_TAMP_15: Internal Tamper15 flag
  * @retval None
  */
#define __HAL_RTC_TAMPER_CLEAR_FLAG(__HANDLE__, __FLAG__)      ((TAMP->SCR) = (__FLAG__))
/**
  * @}
  */

/* --------------------------------- SSR Underflow ---------------------------------*/
/** @defgroup RTCEx_SSR_Underflow RTC SSR Underflow
  * @{
  */

/**
  * @brief  Enable the RTC SSRU interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC SSRU interrupt sources to be enabled.
  *         This parameter can be:
  *            @arg @ref RTC_IT_SSRU SSRU interrupt
  * @retval None
  */
#define __HAL_RTC_SSRU_ENABLE_IT(__HANDLE__, __INTERRUPT__)    (RTC->CR |= (__INTERRUPT__))

/**
  * @brief  Disable the RTC SSRU interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC SSRU interrupt sources to be disabled.
  *         This parameter can be:
  *            @arg @ref RTC_IT_SSRU SSRU interrupt
  * @retval None
  */
#define __HAL_RTC_SSRU_DISABLE_IT(__HANDLE__, __INTERRUPT__)   (RTC->CR &= ~(__INTERRUPT__))


/**
  * @brief  Check whether the specified RTC SSRU interrupt has occurred or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC SSRU interrupt to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_SSRU  SSRU interrupt
  * @retval None
  */
#define __HAL_RTC_SSRU_GET_IT(__HANDLE__, __INTERRUPT__)       (((RTC->MISR) & ((__INTERRUPT__) >> 1) != 0U) \
                                                                ? 1U : 0U)
/**
  * @brief  Check whether the specified RTC Wake Up timer interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Wake Up timer interrupt sources to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_SSRU  SSRU interrupt
  * @retval None
  */
#define __HAL_RTC_SSRU_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)   ((((RTC->CR) & (__INTERRUPT__)) != 0U) ? 1U : 0U)

/**
  * @brief  Get the selected RTC SSRU's flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC SSRU Flag is pending or not.
  *          This parameter can be:
  *             @arg @ref RTC_FLAG_SSRUF
  * @retval None
  */
#define __HAL_RTC_SSRU_GET_FLAG(__HANDLE__, __FLAG__)   (__HAL_RTC_GET_FLAG((__HANDLE__), (__FLAG__)))

/**
  * @brief  Clear the RTC Wake Up timer's pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC SSRU Flag to clear.
  *         This parameter can be:
  *            @arg @ref RTC_FLAG_SSRUF
  * @retval None
  */
#define __HAL_RTC_SSRU_CLEAR_FLAG(__HANDLE__, __FLAG__)     (__HAL_RTC_CLEAR_FLAG((__HANDLE__), RTC_CLEAR_SSRUF))
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

#ifdef RTC_CR_TSE
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_SetTimeStamp_IT(RTC_HandleTypeDef *hrtc, uint32_t TimeStampEdge, uint32_t RTC_TimeStampPin);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTimeStamp(RTC_HandleTypeDef *hrtc);
#endif /* RTC_CR_TSE */
HAL_StatusTypeDef HAL_RTCEx_SetInternalTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateInternalTimeStamp(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_GetTimeStamp(const RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTimeStamp,
                                         RTC_DateTypeDef *sTimeStampDate, uint32_t Format);
void              HAL_RTCEx_TimeStampIRQHandler(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForTimeStampEvent(const RTC_HandleTypeDef *hrtc, uint32_t Timeout);
void              HAL_RTCEx_TimeStampEventCallback(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */


/* RTC Wake-up functions ******************************************************/
/** @defgroup RTCEx_Exported_Functions_Group2 Extended RTC Wake-up functions
  * @{
  */

HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock);
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer_IT(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock,
                                              uint32_t WakeUpAutoClr);
HAL_StatusTypeDef HAL_RTCEx_DeactivateWakeUpTimer(RTC_HandleTypeDef *hrtc);
uint32_t          HAL_RTCEx_GetWakeUpTimer(const RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_WakeUpTimerIRQHandler(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForWakeUpTimerEvent(const RTC_HandleTypeDef *hrtc, uint32_t Timeout);
/**
  * @}
  */

/* Extended Control functions ************************************************/
/** @defgroup RTCEx_Exported_Functions_Group3 Extended Peripheral Control functions
  * @{
  */

HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef *hrtc, uint32_t SmoothCalibPeriod,
                                           uint32_t SmoothCalibPlusPulses, uint32_t SmoothCalibMinusPulsesValue);
HAL_StatusTypeDef HAL_RTCEx_SetLowPowerCalib(RTC_HandleTypeDef *hrtc, uint32_t LowPowerCalib);
HAL_StatusTypeDef HAL_RTCEx_SetSynchroShift(RTC_HandleTypeDef *hrtc, uint32_t ShiftAdd1S, uint32_t ShiftSubFS);
#if defined(RTC_CR_COSEL)
HAL_StatusTypeDef HAL_RTCEx_SetCalibrationOutPut(RTC_HandleTypeDef *hrtc, uint32_t CalibOutput);
HAL_StatusTypeDef HAL_RTCEx_DeactivateCalibrationOutPut(RTC_HandleTypeDef *hrtc);
#endif /* RTC_CR_COSEL */
#if defined(RTC_CR_REFCKON)
HAL_StatusTypeDef HAL_RTCEx_SetRefClock(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateRefClock(RTC_HandleTypeDef *hrtc);
#endif /* RTC_CR_REFCKON */
HAL_StatusTypeDef HAL_RTCEx_EnableBypassShadow(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DisableBypassShadow(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_MonotonicCounterIncrement(const RTC_HandleTypeDef *hrtc, uint32_t Instance);
HAL_StatusTypeDef HAL_RTCEx_MonotonicCounterGet(const RTC_HandleTypeDef *hrtc, uint32_t Instance, uint32_t *pValue);
HAL_StatusTypeDef HAL_RTCEx_SetSSRU_IT(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateSSRU(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_SSRUIRQHandler(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_SSRUEventCallback(RTC_HandleTypeDef *hrtc);

/**
  * @}
  */

/* Extended RTC features functions *******************************************/
/** @defgroup RTCEx_Exported_Functions_Group4 Extended features functions
  * @{
  */

void              HAL_RTCEx_AlarmBEventCallback(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForAlarmBEvent(const RTC_HandleTypeDef *hrtc, uint32_t Timeout);
/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group5 Extended RTC Tamper functions
  * @{
  */
HAL_StatusTypeDef HAL_RTCEx_SetTamper(const RTC_HandleTypeDef *hrtc, const RTC_TamperTypeDef *sTamper);
HAL_StatusTypeDef HAL_RTCEx_SetActiveTampers(RTC_HandleTypeDef *hrtc, const RTC_ActiveTampersTypeDef *sAllTamper);
HAL_StatusTypeDef HAL_RTCEx_SetActiveSeed(RTC_HandleTypeDef *hrtc, const uint32_t *pSeed);
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(const RTC_HandleTypeDef *hrtc, const RTC_TamperTypeDef *sTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(const RTC_HandleTypeDef *hrtc, uint32_t Tamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateActiveTampers(const RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForTamperEvent(const RTC_HandleTypeDef *hrtc, uint32_t Tamper, uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper(const RTC_HandleTypeDef *hrtc,
                                              const RTC_InternalTamperTypeDef *sIntTamper);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper_IT(const RTC_HandleTypeDef *hrtc,
                                                 const RTC_InternalTamperTypeDef *sIntTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateInternalTamper(const RTC_HandleTypeDef *hrtc, uint32_t IntTamper);
HAL_StatusTypeDef HAL_RTCEx_PollForInternalTamperEvent(const RTC_HandleTypeDef *hrtc, uint32_t IntTamper,
                                                       uint32_t Timeout);
#if defined(TAMP_SECCFGR_BHKLOCK)
HAL_StatusTypeDef HAL_RTCEx_LockBootHardwareKey(const RTC_HandleTypeDef *hrtc);
#endif /* TAMP_SECCFGR_BHKLOCK */
void              HAL_RTCEx_TamperIRQHandler(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper1EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper2EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper3EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper4EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper5EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper6EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper7EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_Tamper8EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper1EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper2EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper3EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper4EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper5EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper6EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper7EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper8EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper9EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper11EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper12EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper13EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper15EventCallback(RTC_HandleTypeDef *hrtc);
/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group6 Extended RTC Backup register functions
  * @{
  */
void              HAL_RTCEx_BKUPWrite(const RTC_HandleTypeDef *hrtc, uint32_t BackupRegister, uint32_t Data);
uint32_t          HAL_RTCEx_BKUPRead(const RTC_HandleTypeDef *hrtc, uint32_t BackupRegister);
void              HAL_RTCEx_BKUPErase(const RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_BKUPBlock(const RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_BKUPUnblock(const RTC_HandleTypeDef *hrtc);
#ifdef TAMP_ERCFGR_ERCFG0
void              HAL_RTCEx_ConfigEraseDeviceSecrets(const RTC_HandleTypeDef *hrtc, uint32_t DeviceSecretConf);
#endif /* TAMP_ERCFGR_ERCFG0 */
/**
  * @}
  */

#if defined(RTC_SECCFGR_SEC)
/** @defgroup RTCEx_Exported_Functions_Group7 Extended RTC secure functions
  * @{
  */
HAL_StatusTypeDef HAL_RTCEx_SecureModeGet(const RTC_HandleTypeDef *hrtc, RTC_SecureStateTypeDef  *secureState);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
HAL_StatusTypeDef HAL_RTCEx_SecureModeSet(const RTC_HandleTypeDef *hrtc, const RTC_SecureStateTypeDef  *secureState);
#endif /* #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
/**
  * @}
  */
#endif /* RTC_SECCFGR_SEC */

#if defined(TAMP_PRIVCFGR_TAMPPRIV)
/** @defgroup RTCEx_Exported_Functions_Group8 Extended RTC privilege functions
  * @{
  */
HAL_StatusTypeDef HAL_RTCEx_PrivilegeModeSet(const RTC_HandleTypeDef *hrtc,
                                             const RTC_PrivilegeStateTypeDef *privilegeState);
HAL_StatusTypeDef HAL_RTCEx_PrivilegeModeGet(const RTC_HandleTypeDef *hrtc, RTC_PrivilegeStateTypeDef *privilegeState);
/**
  * @}
  */
#endif /* TAMP_PRIVCFGR_TAMPPRIV */

/**
  * @}
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private constants ---------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/
/** @defgroup RTCEx_Private_Macros RTCEx Private Macros
  * @{
  */

/** @defgroup RTCEx_IS_RTC_Definitions Private macros to check input parameters
  * @{
  */
#if defined(RTC_CR_TSEDGE)
#define IS_TIMESTAMP_EDGE(EDGE) (((EDGE) == RTC_TIMESTAMPEDGE_RISING) || \
                                 ((EDGE) == RTC_TIMESTAMPEDGE_FALLING))
#endif /* RTC_CR_TSEDGE */

#define IS_RTC_TIMESTAMP_PIN(PIN)  (((PIN) == RTC_TIMESTAMPPIN_DEFAULT))

#define IS_RTC_TIMESTAMPONTAMPER_DETECTION(DETECTION) (((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_ENABLE) || \
                                                       ((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_DISABLE))

#if defined(RTC_CR_TAMPOE)
#define IS_RTC_TAMPER_TAMPERDETECTIONOUTPUT(MODE)    (((MODE) == RTC_TAMPERDETECTIONOUTPUT_ENABLE) || \
                                                      ((MODE) == RTC_TAMPERDETECTIONOUTPUT_DISABLE))
#endif /* RTC_CR_TAMPOE */

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


#define IS_RTC_TAMPER(__TAMPER__)                ((((__TAMPER__) & RTC_TAMPER_ALL) != 0U) && \
                                                  (((__TAMPER__) & ~RTC_TAMPER_ALL) == 0U))

#define IS_RTC_INTERNAL_TAMPER(__INT_TAMPER__)   ((((__INT_TAMPER__) & RTC_INT_TAMPER_ALL) != 0U) && \
                                                  (((__INT_TAMPER__) & ~RTC_INT_TAMPER_ALL) == 0U))

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

#define IS_RTC_TAMPER_TIMESTAMPONTAMPER_DETECTION(DETECTION)  \
  (((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_ENABLE) || \
   ((DETECTION) == RTC_TIMESTAMPONTAMPERDETECTION_DISABLE))

#define IS_RTC_ATAMPER_FILTER(__FILTER__)                    (((__FILTER__) == RTC_ATAMP_FILTER_ENABLE) || \
                                                              ((__FILTER__) == RTC_ATAMP_FILTER_DISABLE))

#define IS_RTC_ATAMPER_OUTPUT_CHANGE_PERIOD(__PERIOD__)      ((__PERIOD__) <= 7U)

#define IS_RTC_ATAMPER_ASYNCPRES_RTCCLK(__PRESCALER__)       (((__PRESCALER__) == RTC_ATAMP_ASYNCPRES_RTCCLK)       || \
                                                              ((__PRESCALER__) == RTC_ATAMP_ASYNCPRES_RTCCLK_2)     || \
                                                              ((__PRESCALER__) == RTC_ATAMP_ASYNCPRES_RTCCLK_4)     || \
                                                              ((__PRESCALER__) == RTC_ATAMP_ASYNCPRES_RTCCLK_8)     || \
                                                              ((__PRESCALER__) == RTC_ATAMP_ASYNCPRES_RTCCLK_16)    || \
                                                              ((__PRESCALER__) == RTC_ATAMP_ASYNCPRES_RTCCLK_32)    || \
                                                              ((__PRESCALER__) == RTC_ATAMP_ASYNCPRES_RTCCLK_64)    || \
                                                              ((__PRESCALER__) == RTC_ATAMP_ASYNCPRES_RTCCLK_128)   || \
                                                              ((__PRESCALER__) == RTC_ATAMP_ASYNCPRES_RTCCLK_2048))


#define IS_RTC_BKP(__BKP__)   ((__BKP__) < RTC_BKP_NUMBER)

#define IS_RTC_SHIFT_ADD1S(SEL) (((SEL) == RTC_SHIFTADD1S_RESET) || \
                                 ((SEL) == RTC_SHIFTADD1S_SET))

#define IS_RTC_SHIFT_SUBFS(FS) ((FS) <= RTC_SHIFTR_SUBFS)

#if defined(RTC_CR_COSEL)
#define IS_RTC_CALIB_OUTPUT(OUTPUT)  (((OUTPUT) == RTC_CALIBOUTPUT_512HZ) || \
                                      ((OUTPUT) == RTC_CALIBOUTPUT_1HZ))
#endif /* RTC_CR_COSEL */

#define IS_RTC_SECURE_FULL(__STATE__) (((__STATE__) == RTC_SECURE_FULL_YES) || \
                                       ((__STATE__) == RTC_SECURE_FULL_NO))

#define IS_RTC_NONSECURE_FEATURES(__FEATURES__) (((__FEATURES__) & ~RTC_NONSECURE_FEATURE_ALL) == 0U)

#define IS_TAMP_SECURE_FULL(__STATE__) (((__STATE__) == TAMP_SECURE_FULL_YES) || \
                                        ((__STATE__) == TAMP_SECURE_FULL_NO))

#define IS_TAMP_MONOTONIC_CNT_SECURE(__STATE__) (((__STATE__) == TAMP_MONOTONIC_CNT_SECURE_YES) || \
                                                 ((__STATE__) == TAMP_MONOTONIC_CNT_SECURE_NO))

#define IS_RTC_PRIVILEGE_FULL(__STATE__) (((__STATE__) == RTC_PRIVILEGE_FULL_YES) || \
                                          ((__STATE__) == RTC_PRIVILEGE_FULL_NO))

#define IS_RTC_PRIVILEGE_FEATURES(__FEATURES__) (((__FEATURES__) & ~RTC_PRIVILEGE_FEATURE_ALL) == 0U)

#define IS_TAMP_PRIVILEGE_FULL(__STATE__) (((__STATE__) == TAMP_PRIVILEGE_FULL_YES) || \
                                           ((__STATE__) == TAMP_PRIVILEGE_FULL_NO))

#define IS_TAMP_MONOTONIC_CNT_PRIVILEGE(__STATE__) (((__STATE__) == TAMP_MONOTONIC_CNT_PRIVILEGE_YES) || \
                                                    ((__STATE__) == TAMP_MONOTONIC_CNT_PRIVILEGE_NO))

#define IS_RTC_PRIVILEGE_BKUP_ZONE(__ZONES__) (((__ZONES__) & ~RTC_PRIVILEGE_BKUP_ZONE_ALL) == 0U)

#define IS_RTC_BINARY_MODE(MODE) (((MODE) == RTC_BINARY_NONE) || \
                                  ((MODE) == RTC_BINARY_ONLY) || \
                                  ((MODE) == RTC_BINARY_MIX ))

#define IS_RTC_BINARY_MIX_BCDU(BDCU) (((BDCU) == RTC_BINARY_MIX_BCDU_0) || \
                                      ((BDCU) == RTC_BINARY_MIX_BCDU_1) || \
                                      ((BDCU) == RTC_BINARY_MIX_BCDU_2) || \
                                      ((BDCU) == RTC_BINARY_MIX_BCDU_3) || \
                                      ((BDCU) == RTC_BINARY_MIX_BCDU_4) || \
                                      ((BDCU) == RTC_BINARY_MIX_BCDU_5) || \
                                      ((BDCU) == RTC_BINARY_MIX_BCDU_6) || \
                                      ((BDCU) == RTC_BINARY_MIX_BCDU_7))

#define IS_RTC_ALARM_SUB_SECOND_BINARY_MASK(MASK)   (((MASK) == 0U) || \
                                                     (((MASK) >= RTC_ALARMSUBSECONDBINMASK_SS31_1) &&\
                                                      ((MASK) <= RTC_ALARMSUBSECONDBINMASK_NONE)))

#define IS_RTC_ALARMSUBSECONDBIN_AUTOCLR(SEL) (((SEL) == RTC_ALARMSUBSECONDBIN_AUTOCLR_NO) || \
                                               ((SEL) == RTC_ALARMSUBSECONDBIN_AUTOCLR_YES))
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

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32H5xx_HAL_RTC_EX_H */

