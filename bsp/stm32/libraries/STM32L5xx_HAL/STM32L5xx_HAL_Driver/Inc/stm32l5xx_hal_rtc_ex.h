/**
  ******************************************************************************
  * @file    stm32l5xx_hal_rtc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RTC HAL Extended module.
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
#ifndef STM32L5xx_HAL_RTC_EX_H
#define STM32L5xx_HAL_RTC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l5xx_hal_def.h"

/** @addtogroup STM32L5xx_HAL_Driver
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

  uint32_t Interrupt;                    /*!< Specifies the interrupt mode
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
                                             This parameter can be a value of @ref RTCEx_ActiveTamper_Async_prescaler */

  uint32_t TimeStampOnTamperDetection;  /*!< Specifies the timeStamp on tamper detection.
                                             This parameter can be a value of @ref RTCEx_Tamper_TimeStampOnTamperDetection */

  uint32_t ActiveOutputChangePeriod;    /*!< Specifies the Active Tamper output change period.
                                             This parameter can be a value from 0 to 7. */

  uint32_t Seed[RTC_ATAMP_SEED_NB_UINT32];
  /*!< Specifies the RNG Seed value.
       This parameter is an array of value from 0 to 0xFFFFFFFF. */

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
                                             This parameter can be a value of @ref RTCEx_Tamper_TimeStampOnTamperDetection */

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
  uint32_t rtcSecureFull;               /*!< Specifies If the RTC is fully secure or not
                                             This parameter can be a value of @ref RTCEx_RTC_Secure_Full */
  uint32_t rtcNonSecureFeatures;        /*!< Specifies the non-secure features.
                                             This parameter is only relevant if RTC is not fully secure (rtcSecureFull == RTC_SECURE_FULL_NO).
                                             This parameter can be a combination of @ref RTCEx_RTC_NonSecure_Features. */

  uint32_t tampSecureFull;              /*!< Specifies If the TAMP is fully secure or not
                                             This parameter can be a value of @ref RTCEx_TAMP_Secure_Full */

  uint32_t backupRegisterStartZone2;    /*!< Specifies the backup register start zone 2
                                             Zone 1 : read secure write secure.
                                             Zone 2 : read non-secure  write secure.
                                             This parameter can be RTC_BKP_DRx where x can be from 0 to 31 to specify the register.
                                             Warning : this parameter is shared with RTC_PrivilegeStateTypeDef. */

  uint32_t backupRegisterStartZone3;    /*!< Specifies the backup register start zone 3
                                             Zone 3 : read non-secure  write non-secure
                                             This parameter can be RTC_BKP_DRx where x can be from 0 to 31 to specify the register.
                                             Warning : this parameter is shared with RTC_PrivilegeStateTypeDef. */

} RTC_SecureStateTypeDef ;
/**
  * @}
  */

/** @defgroup RTCEx_Privilege_State_structure_definition RTCEx Privilege structure definition
  * @{
  */
typedef struct
{
  uint32_t rtcPrivilegeFull;            /*!< Specifies If the RTC is fully privileged or not.
                                             This parameter can be a value of @ref RTCEx_RTC_Privilege_Full. */

  uint32_t rtcPrivilegeFeatures;        /*!< Specifies the privileged features.
                                             This parameter is only relevant if RTC is not fully privileged (rtcPrivilegeFull == RTC_PRIVILEGE_FULL_NO).
                                             This parameter can be a combination of @ref RTCEx_RTC_Privilege_Features. */

  uint32_t tampPrivilegeFull;           /*!< Specifies If the TAMP is fully privileged or not.
                                             This parameter can be a value of @ref RTCEx_TAMP_Privilege_Full. */

  uint32_t backupRegisterPrivZone;      /*!< Specifies backup register zone to be privileged.
                                             This parameter can be a combination of @ref RTCEx_Backup_Reg_Privilege_zone.
                                             Warning : this parameter is writable in secure mode or if trustzone is disabled. */


  uint32_t backupRegisterStartZone2;    /*!< Specifies the backup register start zone 2.
                                             Zone 1 : read secure write secure.
                                             Zone 2 : read non-secure  write secure.
                                             This parameter can be RTC_BKP_DRx where x can be from 0 to 31 to specify the register .
                                             Warning : this parameter is writable in secure mode or if trustzone is disabled.
                                             Warning : this parameter is shared with RTC_SecureStateTypeDef */

  uint32_t backupRegisterStartZone3;    /*!< Specifies the backup register start zone 3.
                                             Zone 3 : read non-secure  write non-secure.
                                             This parameter can be RTC_BKP_DRx where x can be from 0 to 31 to specify the register.
                                             Warning : this parameter is writable in secure mode or if trustzone is disabled.
                                             Warning : this parameter is shared with RTC_SecureStateTypeDef. */

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

/** @defgroup RTCEx_Time_Stamp_Edges_definitions RTCEx Time Stamp Edges definition
  * @{
  */
#define RTC_TIMESTAMPEDGE_RISING        0x00000000u
#define RTC_TIMESTAMPEDGE_FALLING       RTC_CR_TSEDGE
/**
  * @}
  */

/** @defgroup RTCEx_TimeStamp_Pin_Selections RTCEx TimeStamp Pin Selection
  * @{
  */
#define RTC_TIMESTAMPPIN_DEFAULT              0x00000000u
/**
  * @}
  */

/** @defgroup RTCEx_Wakeup_Timer_Definitions RTCEx Wakeup Timer Definitions
  * @{
  */
#define RTC_WAKEUPCLOCK_RTCCLK_DIV16        0x00000000u
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
#define RTC_SMOOTHCALIB_PERIOD_32SEC   0x00000000u              /*!< If RTCCLK = 32768 Hz, Smooth calibration
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
#define RTC_SMOOTHCALIB_PLUSPULSES_RESET  0x00000000u           /*!< The number of RTCCLK pulses subbstited
                                                                     during a 32-second window = CALM[8:0] */
/**
  * @}
  */

/** @defgroup RTCEx_Smooth_calib_low_power_Definitions RTCEx Smooth calib Low Power Definitions
  * @{
  */
#define RTC_LPCAL_SET                     RTC_CALR_LPCAL        /*!< Calibration window is 220 ck_apre,
                                                                     which is the required configuration for
                                                                     ultra-low consumption mode. */
#define RTC_LPCAL_RESET                   0x00000000u           /*!< Calibration window is 220 RTCCLK,
                                                                     which is a high-consumption mode.
                                                                     This mode should be set only when less
                                                                     than 32s calibration window is required. */
/**
  * @}
  */

/** @defgroup RTCEx_Calib_Output_selection_Definitions RTCEx Calib Output selection Definitions
 * @{
 */
#define RTC_CALIBOUTPUT_512HZ            0x00000000u
#define RTC_CALIBOUTPUT_1HZ              RTC_CR_COSEL

/**
  * @}
  */


/** @defgroup RTCEx_Add_1_Second_Parameter_Definition RTCEx Add 1 Second Parameter Definitions
  * @{
  */
#define RTC_SHIFTADD1S_RESET      0x00000000u
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
#define RTC_TAMPER_3                         TAMP_CR1_TAMP3E
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
#define RTC_INT_TAMPER_1                    TAMP_CR1_ITAMP1E
#define RTC_INT_TAMPER_2                    TAMP_CR1_ITAMP2E
#define RTC_INT_TAMPER_3                    TAMP_CR1_ITAMP3E
#define RTC_INT_TAMPER_5                    TAMP_CR1_ITAMP5E
#define RTC_INT_TAMPER_8                    TAMP_CR1_ITAMP8E
#define RTC_INT_TAMPER_ALL                  (RTC_INT_TAMPER_1 | RTC_INT_TAMPER_2 |\
                                             RTC_INT_TAMPER_3 | RTC_INT_TAMPER_5 |\
                                             RTC_INT_TAMPER_8)
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_Trigger  RTCEx Tamper Trigger
  * @{
  */
#define RTC_TAMPERTRIGGER_RISINGEDGE        0x00u  /*!< Warning : Filter must be RTC_TAMPERFILTER_DISABLE */
#define RTC_TAMPERTRIGGER_FALLINGEDGE       0x01u  /*!< Warning : Filter must be RTC_TAMPERFILTER_DISABLE */
#define RTC_TAMPERTRIGGER_LOWLEVEL          0x02u  /*!< Warning : Filter must not be RTC_TAMPERFILTER_DISABLE */
#define RTC_TAMPERTRIGGER_HIGHLEVEL         0x03u  /*!< Warning : Filter must not be RTC_TAMPERFILTER_DISABLE */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_MaskFlag  RTCEx Tamper MaskFlag
  * @{
  */
#define RTC_TAMPERMASK_FLAG_DISABLE         0x00u
#define RTC_TAMPERMASK_FLAG_ENABLE          0x01u
/**
  * @}
  */


/** @defgroup RTCEx_Tamper_Maskable_nb  RTCEx Tampers maskable number
  * @{
  */
#define RTC_TAMPER_MASKABLE_NB              3u

/**
  * @}
  */

/** @defgroup RTCEx_Tamper_EraseBackUp  RTCEx Tamper EraseBackUp
* @{
*/
#define RTC_TAMPER_ERASE_BACKUP_ENABLE      0x00u
#define RTC_TAMPER_ERASE_BACKUP_DISABLE     0x01u
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
#define RTC_TAMPER_PULLUP_ENABLE           0x00000000u           /*!< Tamper pins are pre-charged before sampling */
#define RTC_TAMPER_PULLUP_DISABLE          TAMP_FLTCR_TAMPPUDIS  /*!< Tamper pins pre-charge is disabled          */
/**
  * @}
  */

/** @defgroup RTCEx_Tamper_TimeStampOnTamperDetection RTCEx Tamper TimeStamp On Tamper Detection Definitions
  * @{
  */
#define RTC_TIMESTAMPONTAMPERDETECTION_DISABLE  0x00000000u    /*!< TimeStamp on Tamper Detection event is not saved */
#define RTC_TIMESTAMPONTAMPERDETECTION_ENABLE   RTC_CR_TAMPTS  /*!< TimeStamp on Tamper Detection event saved        */
/**
  * @}
  */

/** @defgroup RTCEx_Internal_Tamper_Interrupt  RTCEx Internal Tamper Interrupt
  * @{
  */
#define RTC_IT_TAMP_1                      TAMP_IER_TAMP1IE     /*!< Tamper 1 Interrupt */
#define RTC_IT_TAMP_2                      TAMP_IER_TAMP2IE     /*!< Tamper 2 Interrupt */
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

#define RTC_IT_INT_TAMP_1                   TAMP_IER_ITAMP1IE    /*!< Tamper 1 internal Interrupt */
#define RTC_IT_INT_TAMP_2                   TAMP_IER_ITAMP2IE    /*!< Tamper 2 internal Interrupt */
#define RTC_IT_INT_TAMP_3                   TAMP_IER_ITAMP3IE    /*!< Tamper 3 internal Interrupt */
#define RTC_IT_INT_TAMP_5                   TAMP_IER_ITAMP5IE    /*!< Tamper 5 internal Interrupt */
#define RTC_IT_INT_TAMP_8                   TAMP_IER_ITAMP8IE    /*!< Tamper 8 internal Interrupt */

#define RTC_IT_INT_TAMP_ALL                (RTC_IT_INT_TAMP_1 | RTC_IT_INT_TAMP_2 |\
                                            RTC_IT_INT_TAMP_3 | RTC_IT_INT_TAMP_5 |\
                                            RTC_IT_INT_TAMP_8 )
/**
  * @}
  */

/** @defgroup RTCEx_Flags  RTCEx Flags
  * @{
  */
#define RTC_FLAG_TAMP_1                    TAMP_SR_TAMP1F
#define RTC_FLAG_TAMP_2                    TAMP_SR_TAMP2F
#define RTC_FLAG_TAMP_3                    TAMP_SR_TAMP3F
#define RTC_FLAG_TAMP_4                    TAMP_SR_TAMP4F
#define RTC_FLAG_TAMP_5                    TAMP_SR_TAMP5F
#define RTC_FLAG_TAMP_6                    TAMP_SR_TAMP6F
#define RTC_FLAG_TAMP_7                    TAMP_SR_TAMP7F
#define RTC_FLAG_TAMP_8                    TAMP_SR_TAMP8F
#define RTC_FLAG_TAMP_ALL                 (RTC_FLAG_TAMP_1 | RTC_FLAG_TAMP_2 | RTC_FLAG_TAMP_3 |\
                                           RTC_FLAG_TAMP_4 | RTC_FLAG_TAMP_5 | RTC_FLAG_TAMP_6 |\
                                           RTC_FLAG_TAMP_7 | RTC_FLAG_TAMP_8)


#define RTC_FLAG_INT_TAMP_1                 TAMP_SR_ITAMP1F
#define RTC_FLAG_INT_TAMP_2                 TAMP_SR_ITAMP2F
#define RTC_FLAG_INT_TAMP_3                 TAMP_SR_ITAMP3F
#define RTC_FLAG_INT_TAMP_5                 TAMP_SR_ITAMP5F
#define RTC_FLAG_INT_TAMP_8                 TAMP_SR_ITAMP8F
#define RTC_FLAG_INT_TAMP_ALL               (RTC_FLAG_INT_TAMP_1 | RTC_FLAG_INT_TAMP2 |\
                                             RTC_FLAG_INT_TAMP_3 | RTC_FLAG_INT_TAMP5 |\
                                             RTC_FLAG_INT_TAMP_8)
/**
  * @}
  */


/** @defgroup RTCEx_ActiveTamper_Enable RTCEx_ActiveTamper_Enable Definitions
  * @{
  */
#define RTC_ATAMP_ENABLE                   1u
#define RTC_ATAMP_DISABLE                  0u
/**
  * @}
  */

/** @defgroup RTCEx_ActiveTamper_Interrupt RTCEx_ActiveTamper_Interrupt Definitions
  * @{
  */
#define RTC_ATAMP_INTERRUPT_ENABLE        1u
#define RTC_ATAMP_INTERRUPT_DISABLE       0u
/**
  * @}
  */

/** @defgroup RTCEx_ActiveTamper_Filter RTCEx_ActiveTamper_Filter Definitions
  * @{
  */
#define RTC_ATAMP_FILTER_ENABLE           TAMP_ATCR1_FLTEN
#define RTC_ATAMP_FILTER_DISABLE          0u
/**
  * @}
  */

/** @defgroup RTCEx_ActiveTamper_Async_prescaler RTCEx Active_Tamper_Asynchronous_Prescaler clock Definitions
  * @{
  */
#define RTC_ATAMP_ASYNCPRES_RTCCLK        0u                                                                      /*!< RTCCLK */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_2      TAMP_ATCR1_ATCKSEL_0                                                    /*!< RTCCLK/2 */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_4      TAMP_ATCR1_ATCKSEL_1                                                    /*!< RTCCLK/4 */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_8     (TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0)                            /*!< RTCCLK/8 */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_16     TAMP_ATCR1_ATCKSEL_2                                                    /*!< RTCCLK/16 */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_32    (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_0)                            /*!< RTCCLK/32 */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_64    (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1)                            /*!< RTCCLK/64 */
#define RTC_ATAMP_ASYNCPRES_RTCCLK_128   (TAMP_ATCR1_ATCKSEL_2 | TAMP_ATCR1_ATCKSEL_1 | TAMP_ATCR1_ATCKSEL_0)     /*!< RTCCLK/128 */
/**
  * @}
  */

/** @defgroup RTCEx_ActiveTamper_Sel  RTCEx Active Tamper selection Definition
  * @{
  */
#define RTC_ATAMP_1                       0u   /*!< Tamper 1 */
#define RTC_ATAMP_2                       1u   /*!< Tamper 2 */
#define RTC_ATAMP_3                       2u   /*!< Tamper 3 */
#define RTC_ATAMP_4                       3u   /*!< Tamper 4 */
#define RTC_ATAMP_5                       4u   /*!< Tamper 5 */
#define RTC_ATAMP_6                       5u   /*!< Tamper 6 */
#define RTC_ATAMP_7                       6u   /*!< Tamper 7 */
#define RTC_ATAMP_8                       7u   /*!< Tamper 8 */
/**
  * @}
  */


/** @defgroup RTCEx_MonotonicCounter_Instance  RTCEx Monotonic Counter Instance Definition
  * @{
  */
#define RTC_MONOTONIC_COUNTER_1           0u   /*!< Monotonic counter 1 */
/**
  * @}
  */


/** @defgroup RTCEx_Backup_Registers  RTCEx Backup Registers Definition
  * @{
  */
#define RTC_BKP_NUMBER                    RTC_BACKUP_NB
#define RTC_BKP_DR0                       0x00u
#define RTC_BKP_DR1                       0x01u
#define RTC_BKP_DR2                       0x02u
#define RTC_BKP_DR3                       0x03u
#define RTC_BKP_DR4                       0x04u
#define RTC_BKP_DR5                       0x05u
#define RTC_BKP_DR6                       0x06u
#define RTC_BKP_DR7                       0x07u
#define RTC_BKP_DR8                       0x08u
#define RTC_BKP_DR9                       0x09u
#define RTC_BKP_DR10                      0x0Au
#define RTC_BKP_DR11                      0x0Bu
#define RTC_BKP_DR12                      0x0Cu
#define RTC_BKP_DR13                      0x0Du
#define RTC_BKP_DR14                      0x0Eu
#define RTC_BKP_DR15                      0x0Fu
#define RTC_BKP_DR16                      0x10u
#define RTC_BKP_DR17                      0x11u
#define RTC_BKP_DR18                      0x12u
#define RTC_BKP_DR19                      0x13u
#define RTC_BKP_DR20                      0x14u
#define RTC_BKP_DR21                      0x15u
#define RTC_BKP_DR22                      0x16u
#define RTC_BKP_DR23                      0x17u
#define RTC_BKP_DR24                      0x18u
#define RTC_BKP_DR25                      0x19u
#define RTC_BKP_DR26                      0x1Au
#define RTC_BKP_DR27                      0x1Bu
#define RTC_BKP_DR28                      0x1Cu
#define RTC_BKP_DR29                      0x1Du
#define RTC_BKP_DR30                      0x1Eu
#define RTC_BKP_DR31                      0x1Fu
/**
  * @}
  */


/** @defgroup RTCEx_RTC_Secure_Full  RTCEx Secure Definition
  * @{
  */
#define RTC_SECURE_FULL_YES                  0u                  /*!< RTC full secure */
#define RTC_SECURE_FULL_NO                   RTC_SMCR_DECPROT    /*!< RTC is not full secure, features can be non-secure. See RTC_LL_EC_NONSECURE_RTC_FEATURE */
/**
  * @}
  */

/** @defgroup RTCEx_RTC_NonSecure_Features  RTCEx Secure Features Definition
  * @{
  */
#define RTC_NONSECURE_FEATURE_NONE            0u
#define RTC_NONSECURE_FEATURE_INIT            RTC_SMCR_INITDPROT  /*!< Initialization */
#define RTC_NONSECURE_FEATURE_CAL             RTC_SMCR_CALDPROT   /*!< Calibration */
#define RTC_NONSECURE_FEATURE_TS              RTC_SMCR_TSDPROT    /*!< Time stamp */
#define RTC_NONSECURE_FEATURE_WUT             RTC_SMCR_WUTDPROT   /*!< Wake up timer */
#define RTC_NONSECURE_FEATURE_ALRA            RTC_SMCR_ALRADPROT  /*!< Alarm A */
#define RTC_NONSECURE_FEATURE_ALRB            RTC_SMCR_ALRBDPROT  /*!< Alarm B */
#define RTC_NONSECURE_FEATURE_ALL             (RTC_SMCR_INITDPROT |  RTC_SMCR_CALDPROT | \
                                              RTC_SMCR_TSDPROT | RTC_SMCR_WUTDPROT | \
                                              RTC_SMCR_ALRADPROT | RTC_SMCR_ALRBDPROT)
/**
  * @}
  */

/** @defgroup RTCEx_TAMP_Secure_Full  RTCEx TAMP Secure
  * @{
  */
#define TAMP_SECURE_FULL_YES                 0u                  /*!< TAMPER full secure */
#define TAMP_SECURE_FULL_NO                  TAMP_SMCR_TAMPDPROT /*!< TAMPER is not secure */
/**
  * @}
  */


/** @defgroup RTCEx_RTC_Privilege_Full  RTCEx Privilege Features
  * @{
  */
#define RTC_PRIVILEGE_FULL_YES               RTC_PRIVCR_PRIV
#define RTC_PRIVILEGE_FULL_NO                0u
/**
  * @}
  */

/** @defgroup RTCEx_RTC_Privilege_Features  RTCEx Privilege Features Definition
  * @{
  */
#define RTC_PRIVILEGE_FEATURE_NONE           0u
#define RTC_PRIVILEGE_FEATURE_INIT           RTC_PRIVCR_INITPRIV  /*!< Initialization */
#define RTC_PRIVILEGE_FEATURE_CAL            RTC_PRIVCR_CALPRIV   /*!< Calibration */
#define RTC_PRIVILEGE_FEATURE_TS             RTC_PRIVCR_TSPRIV    /*!< Time stamp */
#define RTC_PRIVILEGE_FEATURE_WUT            RTC_PRIVCR_WUTPRIV   /*!< Wake up timer */
#define RTC_PRIVILEGE_FEATURE_ALRA           RTC_PRIVCR_ALRAPRIV  /*!< Alarm A */
#define RTC_PRIVILEGE_FEATURE_ALRB           RTC_PRIVCR_ALRBPRIV  /*!< Alarm B */
#define RTC_PRIVILEGE_FEATURE_ALL            (RTC_PRIVCR_INITPRIV |  RTC_PRIVCR_CALPRIV | \
                                             RTC_PRIVCR_TSPRIV | RTC_PRIVCR_WUTPRIV | \
                                             RTC_PRIVCR_ALRAPRIV | RTC_PRIVCR_ALRBPRIV)
/**
  * @}
  */

/** @defgroup RTCEx_TAMP_Privilege_Full  RTCEx TAMP security Definition
  * @{
  */
#define TAMP_PRIVILEGE_FULL_YES              TAMP_PRIVCR_TAMPPRIV
#define TAMP_PRIVILEGE_FULL_NO               0u
/**
  * @}
  */

/** @defgroup RTCEx_Backup_Reg_Privilege_zone  RTCEx Privilege Backup register privilege zone Definition
  * @{
  */
#define RTC_PRIVILEGE_BKUP_ZONE_NONE         0u
#define RTC_PRIVILEGE_BKUP_ZONE_1            TAMP_PRIVCR_BKPRWPRIV
#define RTC_PRIVILEGE_BKUP_ZONE_2            TAMP_PRIVCR_BKPWPRIV
#define RTC_PRIVILEGE_BKUP_ZONE_ALL          (RTC_PRIVILEGE_BKUP_ZONE_1 |  RTC_PRIVILEGE_BKUP_ZONE_2)
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
#define __HAL_RTC_GET_FLAG(__HANDLE__, __FLAG__)    (((((__FLAG__)) >> 8U) == 1U) ? (RTC->ICSR & (1U << (((uint16_t)(__FLAG__)) & RTC_FLAG_MASK))) : \
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
#define __HAL_RTC_WAKEUPTIMER_GET_IT(__HANDLE__, __INTERRUPT__)       ((((RTC->MISR) & ((__INTERRUPT__)>> 12U)) != 0UL) ? 1UL : 0UL)
/**
  * @brief  Check whether the specified RTC Wake Up timer interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Wake Up timer interrupt sources to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_WUT  WakeUpTimer interrupt
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)   ((((RTC->CR) & (__INTERRUPT__)) != 0UL) ? 1UL : 0UL)

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
  * @brief  Enable event on the RTC WakeUp Timer associated Exti line.
  * @retval None
  */
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_EVENT()    (EXTI->EMR1 |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)

/**
  * @brief  Disable event on the RTC WakeUp Timer associated Exti line.
  * @retval None
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
#define __HAL_RTC_TIMESTAMP_GET_IT(__HANDLE__, __INTERRUPT__)        ((((RTC->MISR) & ((__INTERRUPT__)>> 12U)) != 0U) ? 1UL : 0UL)
/**
  * @brief  Check whether the specified RTC Time Stamp interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Time Stamp interrupt source to check.
  *         This parameter can be:
  *            @arg @ref RTC_IT_TS TimeStamp interrupt
  * @retval None
  */
#define __HAL_RTC_TIMESTAMP_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)     ((((RTC->CR) & (__INTERRUPT__)) != 0U) ? 1UL : 0UL)

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
#define __HAL_RTC_INTERNAL_TIMESTAMP_GET_FLAG(__HANDLE__, __FLAG__)     (__HAL_RTC_GET_FLAG((__HANDLE__),(__FLAG__)))

/**
  * @brief  Clear the RTC Internal Time Stamps pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Internal Time Stamp Flag source to clear.
  * This parameter can be:
  *             @arg @ref RTC_FLAG_ITSF
  * @retval None
  */
#define __HAL_RTC_INTERNAL_TIMESTAMP_CLEAR_FLAG(__HANDLE__, __FLAG__)     (__HAL_RTC_CLEAR_FLAG((__HANDLE__), RTC_CLEAR_ITSF))

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
  *            @arg  RTC_IT_INT_TAMP_5: Internal Tamper5 interrupt
  *            @arg  RTC_IT_INT_TAMP_8: Internal Tamper8 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT(__HANDLE__, __INTERRUPT__)     ((((TAMP->MISR) & (__INTERRUPT__)) != 0U) ? 1UL : 0UL)


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
  *            @arg  RTC_IT_INT_TAMP_5: Internal Tamper5 interrupt
  *            @arg  RTC_IT_INT_TAMP_8: Internal Tamper8 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)    ((((TAMP->IER) & (__INTERRUPT__)) != 0U) ? 1UL : 0UL)


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
  *             @arg RTC_FLAG_INT_TAMP_5: Internal Tamper5 flag
  *             @arg RTC_FLAG_INT_TAMP_8: Internal Tamper8 flag
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
  *             @arg RTC_FLAG_INT_TAMP_5: Internal Tamper5 flag
  *             @arg RTC_FLAG_INT_TAMP_8: Internal Tamper8 flag
  * @retval None
  */
#define __HAL_RTC_TAMPER_CLEAR_FLAG(__HANDLE__, __FLAG__)      ((TAMP->SCR) = (__FLAG__))

/**
  * @brief  Enable interrupt on the RTC tamper associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_ENABLE_IT()        (EXTI->IMR1 |= RTC_EXTI_LINE_TAMPER_EVENT)

/**
  * @brief  Disable interrupt on the RTC tamper associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_DISABLE_IT()       (EXTI->IMR1 &= ~(RTC_EXTI_LINE_TAMPER_EVENT))

/**
  * @brief  Enable event on the RTC tamper associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_ENABLE_EVENT()    (EXTI->EMR1 |= RTC_EXTI_LINE_TAMPER_EVENT)

/**
  * @brief  Disable event on the RTC tamper associated Exti line.
  * @retval None
  */
#define __HAL_RTC_TAMPER_EXTI_DISABLE_EVENT()   (EXTI->EMR1 &= ~(RTC_EXTI_LINE_TAMPER_EVENT))

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
HAL_StatusTypeDef HAL_RTCEx_GetTimeStamp(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTimeStamp, RTC_DateTypeDef *sTimeStampDate, uint32_t Format);
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
HAL_StatusTypeDef HAL_RTCEx_SetWakeUpTimer_IT(RTC_HandleTypeDef *hrtc, uint32_t WakeUpCounter, uint32_t WakeUpClock, uint32_t WakeUpAutoClr);
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

HAL_StatusTypeDef HAL_RTCEx_SetSmoothCalib(RTC_HandleTypeDef *hrtc, uint32_t SmoothCalibPeriod, uint32_t SmoothCalibPlusPulses, uint32_t SmoothCalibMinusPulsesValue);
HAL_StatusTypeDef HAL_RTCEx_SetLowPowerCalib(RTC_HandleTypeDef *hrtc, uint32_t LowPowerCalib);
HAL_StatusTypeDef HAL_RTCEx_SetSynchroShift(RTC_HandleTypeDef *hrtc, uint32_t ShiftAdd1S, uint32_t ShiftSubFS);
HAL_StatusTypeDef HAL_RTCEx_SetCalibrationOutPut(RTC_HandleTypeDef *hrtc, uint32_t CalibOutput);
HAL_StatusTypeDef HAL_RTCEx_DeactivateCalibrationOutPut(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_SetRefClock(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DeactivateRefClock(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_EnableBypassShadow(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_DisableBypassShadow(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_MonotonicCounterIncrement(RTC_HandleTypeDef *hrtc, uint32_t Instance);
HAL_StatusTypeDef HAL_RTCEx_MonotonicCounterGet(RTC_HandleTypeDef *hrtc, uint32_t Instance, uint32_t *Value);
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
HAL_StatusTypeDef HAL_RTCEx_SetActiveTampers(RTC_HandleTypeDef *hrtc, RTC_ActiveTampersTypeDef *sAllTamper);
HAL_StatusTypeDef HAL_RTCEx_SetActiveSeed(RTC_HandleTypeDef *hrtc, uint32_t *pSeed);
HAL_StatusTypeDef HAL_RTCEx_SetTamper_IT(RTC_HandleTypeDef *hrtc, RTC_TamperTypeDef *sTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateTamper(RTC_HandleTypeDef *hrtc, uint32_t Tamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateActiveTampers(RTC_HandleTypeDef *hrtc);
HAL_StatusTypeDef HAL_RTCEx_PollForTamperEvent(RTC_HandleTypeDef *hrtc, uint32_t Tamper, uint32_t Timeout);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper(RTC_HandleTypeDef *hrtc, RTC_InternalTamperTypeDef *sIntTamper);
HAL_StatusTypeDef HAL_RTCEx_SetInternalTamper_IT(RTC_HandleTypeDef *hrtc, RTC_InternalTamperTypeDef *sIntTamper);
HAL_StatusTypeDef HAL_RTCEx_DeactivateInternalTamper(RTC_HandleTypeDef *hrtc, uint32_t IntTamper);
HAL_StatusTypeDef HAL_RTCEx_PollForInternalTamperEvent(RTC_HandleTypeDef *hrtc, uint32_t IntTamper, uint32_t Timeout);
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
void              HAL_RTCEx_InternalTamper5EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper8EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_EnableTemperatureMonitoring(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_DisableTemperatureMonitoring(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_EnableVoltageMonitoring(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_DisableVoltageMonitoring(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_EnableWUTMonitoring(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_DisableWUTMonitoring(RTC_HandleTypeDef *hrtc);
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

/** @defgroup RTCEx_Exported_Functions_Group7 Extended RTC secure functions
 * @{
 */
HAL_StatusTypeDef HAL_RTCEx_SecureModeGet(RTC_HandleTypeDef *hrtc, RTC_SecureStateTypeDef  *secureState);
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
HAL_StatusTypeDef HAL_RTCEx_SecureModeSet(RTC_HandleTypeDef *hrtc, RTC_SecureStateTypeDef  *secureState);
#endif /* #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
/**
  * @}
  */

/** @defgroup RTCEx_Exported_Functions_Group8 Extended RTC privilege functions
 * @{
 */
HAL_StatusTypeDef HAL_RTCEx_PrivilegeModeSet(RTC_HandleTypeDef *hrtc, RTC_PrivilegeStateTypeDef *privilegeState);
HAL_StatusTypeDef HAL_RTCEx_PrivilegeModeGet(RTC_HandleTypeDef *hrtc, RTC_PrivilegeStateTypeDef *privilegeState);
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
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
#define RTC_EXTI_LINE_ALARM_EVENT             EXTI_IMR1_IM18 /*!< External interrupt line 18 Connected to the RTC Alarm event */
#define RTC_EXTI_LINE_TIMESTAMP_EVENT         EXTI_IMR1_IM18 /*!< External interrupt line 18 Connected to the RTC Time Stamp events */
#define RTC_EXTI_LINE_WAKEUPTIMER_EVENT       EXTI_IMR1_IM18 /*!< External interrupt line 18 Connected to the RTC Wakeup event */
#define RTC_EXTI_LINE_TAMPER_EVENT            EXTI_IMR1_IM20 /*!< External interrupt line 20 Connected to the RTC tamper events */
#else /* #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
#define RTC_EXTI_LINE_ALARM_EVENT             EXTI_IMR1_IM17 /*!< External interrupt line 17 Connected to the RTC Alarm event */
#define RTC_EXTI_LINE_TIMESTAMP_EVENT         EXTI_IMR1_IM17 /*!< External interrupt line 17 Connected to the RTC Time Stamp events */
#define RTC_EXTI_LINE_WAKEUPTIMER_EVENT       EXTI_IMR1_IM17 /*!< External interrupt line 17 Connected to the RTC Wakeup event */
#define RTC_EXTI_LINE_TAMPER_EVENT            EXTI_IMR1_IM19 /*!< External interrupt line 19 Connected to the RTC tamper events */
#endif /* #if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */
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

#define IS_RTC_SECURE_FULL(__STATE__) (((__STATE__) == RTC_SECURE_FULL_YES) || \
                                       ((__STATE__) == RTC_SECURE_FULL_NO))

#define IS_RTC_NONSECURE_FEATURES(__FEATURES__) (((__FEATURES__) & ~RTC_NONSECURE_FEATURE_ALL) == 0u)

#define IS_TAMP_SECURE_FULL(__STATE__) (((__STATE__) == TAMP_SECURE_FULL_YES) || \
                                        ((__STATE__) == TAMP_SECURE_FULL_NO))

#define IS_RTC_PRIVILEGE_FULL(__STATE__) (((__STATE__) == RTC_PRIVILEGE_FULL_YES) || \
                                          ((__STATE__) == RTC_PRIVILEGE_FULL_NO))

#define IS_RTC_PRIVILEGE_FEATURES(__FEATURES__) (((__FEATURES__) & ~RTC_PRIVILEGE_FEATURE_ALL) == 0u)

#define IS_TAMP_PRIVILEGE_FULL(__STATE__) (((__STATE__) == TAMP_PRIVILEGE_FULL_YES) || \
                                           ((__STATE__) == TAMP_PRIVILEGE_FULL_NO))

#define IS_RTC_PRIVILEGE_BKUP_ZONE(__ZONES__) (((__ZONES__) & ~RTC_PRIVILEGE_BKUP_ZONE_ALL) == 0u)

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

#endif /* STM32L5xx_HAL_RTC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
