/**
  ******************************************************************************
  * @file    stm32wlxx_hal_rtc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of RTC HAL Extended module.
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
#ifndef STM32WLxx_HAL_RTC_EX_H
#define STM32WLxx_HAL_RTC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal_def.h"

/** @addtogroup STM32WLxx_HAL_Driver
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

  uint32_t NoErase;                     /*!< Specifies the internal Tamper no erase mode.
                                             This parameter can be a value of @ref RTCEx_Tamper_EraseBackUp */
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
#define RTC_TAMPER_3                        TAMP_CR1_TAMP3E
#define RTC_TAMPER_ALL                      (TAMP_CR1_TAMP1E | TAMP_CR1_TAMP2E |  TAMP_CR1_TAMP3E)
/**
  * @}
  */

/** @defgroup RTCEx_Internal_Tamper_Pins  RTCEx Internal Tamper Pins Definition
  * @{
  */
#define RTC_INT_TAMPER_3                    TAMP_CR1_ITAMP3E
#define RTC_INT_TAMPER_5                    TAMP_CR1_ITAMP5E
#define RTC_INT_TAMPER_6                    TAMP_CR1_ITAMP6E
#define RTC_INT_TAMPER_8                    TAMP_CR1_ITAMP8E
#define RTC_INT_TAMPER_ALL                  (TAMP_CR1_ITAMP3E | TAMP_CR1_ITAMP5E | TAMP_CR1_ITAMP6E | TAMP_CR1_ITAMP8E)
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
#define RTC_IT_TAMP_ALL                   (TAMP_IER_TAMP1IE | TAMP_IER_TAMP2IE | TAMP_IER_TAMP3IE)

#define RTC_IT_INT_TAMP_3                  TAMP_IER_ITAMP3IE
#define RTC_IT_INT_TAMP_5                  TAMP_IER_ITAMP5IE
#define RTC_IT_INT_TAMP_6                  TAMP_IER_ITAMP6IE
#define RTC_IT_INT_TAMP_8                  TAMP_IER_ITAMP8IE
#define RTC_IT_INT_TAMP_ALL                (TAMP_IT_INT_TAMP3 | TAMP_IT_INT_TAMP5 | TAMP_IT_INT_TAMP6 | TAMP_IT_INT_TAMP8)
/**
  * @}
  */

/** @defgroup RTCEx_Flags  RTCEx Flags
  * @{
  */
#define RTC_FLAG_TAMP_1                    TAMP_SR_TAMP1F
#define RTC_FLAG_TAMP_2                    TAMP_SR_TAMP2F
#define RTC_FLAG_TAMP_3                    TAMP_SR_TAMP3F
#define RTC_FLAG_TAMP_ALL                 (RTC_FLAG_TAMP1 | RTC_FLAG_TAMP2 | RTC_FLAG_TAMP3 )


#define RTC_FLAG_INT_TAMP_3                 TAMP_SR_ITAMP3F
#define RTC_FLAG_INT_TAMP_5                 TAMP_SR_ITAMP5F
#define RTC_FLAG_INT_TAMP_6                 TAMP_SR_ITAMP6F
#define RTC_FLAG_INT_TAMP_8                 TAMP_SR_ITAMP8F
#define RTC_FLAG_INT_TAMP_ALL               (RTC_FLAG_INT_TAMP3 | RTC_FLAG_INT_TAMP5 | RTC_FLAG_INT_TAMP6 | RTC_FLAG_INT_TAMP8)
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
/**
  * @}
  */

/** @defgroup RTCEx_Binary_Mode RTC Binary Mode (32-bit free-running counter configuration).
  *           Warning : It Should not be confused with the Binary format @ref RTC_Input_parameter_format_definitions.
  * @{
  */
#define RTC_BINARY_NONE                     0x00000000u      /*!< Free running BCD calendar mode (Binary mode disabled). */
#define RTC_BINARY_ONLY                     RTC_ICSR_BIN_0   /*!< Free running Binary mode (BCD mode disabled) */
#define RTC_BINARY_MIX                      RTC_ICSR_BIN_1   /*!< Free running BCD calendar and Binary mode */
/**
  * @}
  */

/** @defgroup RTCEx_Binary_mix_BCDU If Binary mode is RTC_BINARY_MIX, the BCD calendar second is incremented using the SSR Least Significant Bits.
  * @{
  */
#define RTC_BINARY_MIX_BCDU_0  0x00000000u                   /*!<  The 1s BCD calendar increment is generated each time SS[7:0] = 0 */
#define RTC_BINARY_MIX_BCDU_1  (0x1UL << RTC_ICSR_BCDU_Pos)  /*!<  The 1s BCD calendar increment is generated each time SS[8:0] = 0 */
#define RTC_BINARY_MIX_BCDU_2  (0x2UL << RTC_ICSR_BCDU_Pos)  /*!<  The 1s BCD calendar increment is generated each time SS[9:0] = 0 */
#define RTC_BINARY_MIX_BCDU_3  (0x3UL << RTC_ICSR_BCDU_Pos)  /*!<  The 1s BCD calendar increment is generated each time SS[10:0] = 0 */
#define RTC_BINARY_MIX_BCDU_4  (0x4UL << RTC_ICSR_BCDU_Pos)  /*!<  The 1s BCD calendar increment is generated each time SS[11:0] = 0 */
#define RTC_BINARY_MIX_BCDU_5  (0x5UL << RTC_ICSR_BCDU_Pos)  /*!<  The 1s BCD calendar increment is generated each time SS[12:0] = 0 */
#define RTC_BINARY_MIX_BCDU_6  (0x6UL << RTC_ICSR_BCDU_Pos)  /*!<  The 1s BCD calendar increment is generated each time SS[13:0] = 0 */
#define RTC_BINARY_MIX_BCDU_7  (0x7UL << RTC_ICSR_BCDU_Pos)  /*!<  The 1s BCD calendar increment is generated each time SS[14:0] = 0 */
/**
  * @}
  */

/** @defgroup RTCEx_Alarm_Sub_Seconds_binary_Masks_Definitions RTC Alarm Sub Seconds with binary mode Masks Definitions
  * @{
  */
#define RTC_ALARMSUBSECONDBINMASK_ALL           0x00000000u                                                             /*!< All Alarm SS fields are masked.
                                                                                                                          There is no comparison on sub seconds for Alarm */
#define RTC_ALARMSUBSECONDBINMASK_SS31_1        (1UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:1] are don't care in Alarm
                                                                                                                          comparison. Only SS[0] is compared.    */
#define RTC_ALARMSUBSECONDBINMASK_SS31_2        (2UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:2] are don't care in Alarm
                                                                                                                          comparison. Only SS[1:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_3        (3UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:3] are don't care in Alarm
                                                                                                                          comparison. Only SS[2:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_4        (4UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:4] are don't care in Alarm
                                                                                                                          comparison. Only SS[3:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_5        (5UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:5] are don't care in Alarm
                                                                                                                          comparison. Only SS[4:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_6        (6UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:6] are don't care in Alarm
                                                                                                                          comparison. Only SS[5:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_7        (7UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:7] are don't care in Alarm
                                                                                                                          comparison. Only SS[6:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_8        (8UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:8] are don't care in Alarm
                                                                                                                          comparison. Only SS[7:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_9        (9UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:9] are don't care in Alarm
                                                                                                                          comparison. Only SS[8:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_10      (10UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:10] are don't care in Alarm
                                                                                                                          comparison. Only SS[9:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_11      (11UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:11] are don't care in Alarm
                                                                                                                          comparison. Only SS[10:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_12      (12UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:12] are don't care in Alarm
                                                                                                                          comparison.Only SS[11:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_SS31_13      (13UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:13] are don't care in Alarm
                                                                                                                          comparison. Only SS[12:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_14      (14UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:14] are don't care in Alarm
                                                                                                                          comparison. Only SS[13:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_15      (15UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:15] are don't care in Alarm
                                                                                                                          comparison. Only SS[14:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_16      (16UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:16] are don't care in Alarm
                                                                                                                          comparison. Only SS[15:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_17      (17UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:17] are don't care in Alarm
                                                                                                                          comparison. Only SS[16:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_18      (18UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:18] are don't care in Alarm
                                                                                                                          comparison. Only SS[17:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_19      (19UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:19] are don't care in Alarm
                                                                                                                          comparison. Only SS[18:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_20      (20UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:20] are don't care in Alarm
                                                                                                                          comparison. Only SS[19:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_21      (21UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:21] are don't care in Alarm
                                                                                                                          comparison. Only SS[20:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_22      (22UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:22] are don't care in Alarm
                                                                                                                          comparison. Only SS[21:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_23      (23UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:23] are don't care in Alarm
                                                                                                                          comparison. Only SS[22:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_24      (24UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:24] are don't care in Alarm
                                                                                                                          comparison. Only SS[23:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_25      (25UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:25] are don't care in Alarm
                                                                                                                          comparison. Only SS[24:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_26      (26UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:26] are don't care in Alarm
                                                                                                                          comparison. Only SS[25:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_27      (27UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:27] are don't care in Alarm
                                                                                                                          comparison. Only SS[26:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_28      (28UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:28] are don't care in Alarm
                                                                                                                          comparison. Only SS[27:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_29      (29UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:29] are don't care in Alarm
                                                                                                                          comparison. Only SS[28:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31_30      (30UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:30] are don't care in Alarm
                                                                                                                          comparison. Only SS[29:0] are compared */
#define RTC_ALARMSUBSECONDBINMASK_SS31         (31UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31] is don't care in Alarm
                                                                                                                          comparison. Only SS[30:0] are compared  */
#define RTC_ALARMSUBSECONDBINMASK_NONE         (32UL << RTC_ALRMASSR_MASKSS_Pos)                                        /*!< SS[31:0] are compared and must match to activate alarm. */
/**
  * @}
  */

/** @defgroup RTCEx_Alarm_Sub_Seconds_binary_Clear_Definitions RTC Alarm Sub Seconds with binary mode auto clear Definitions
  * @{
  */
#define RTC_ALARMSUBSECONDBIN_AUTOCLR_NO    0UL                  /*!<  The synchronous Binary counter (SS[31:0] in RTC_SSR) is free-running. */
#define RTC_ALARMSUBSECONDBIN_AUTOCLR_YES   RTC_ALRMASSR_SSCLR   /*!<  The synchronous Binary counter (SS[31:0] in RTC_SSR) is running from 0xFFFF FFFF to
                                                                          RTC_ALRMABINR -> SS[31:0] value and is automatically reloaded with 0xFFFF FFFF
                                                                          whenreaching RTC_ALRMABINR -> SS[31:0]. */
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
#if defined(CORE_CM0PLUS)
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT()       (EXTI->C2IMR1 |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_IT()      (EXTI->C2IMR1 &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_EVENT()    (EXTI->C2EMR1 |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_EVENT()   (EXTI->C2EMR1 &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))
#else
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_IT()       (EXTI->IMR1 |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_IT()      (EXTI->IMR1 &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))
#define __HAL_RTC_WAKEUPTIMER_EXTI_ENABLE_EVENT()    (EXTI->EMR1 |= RTC_EXTI_LINE_WAKEUPTIMER_EVENT)
#define __HAL_RTC_WAKEUPTIMER_EXTI_DISABLE_EVENT()   (EXTI->EMR1 &= ~(RTC_EXTI_LINE_WAKEUPTIMER_EVENT))
#endif

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

/* TIMESTAMP EXTI */
/* -------------- */
#if defined(CORE_CM0PLUS)
#define __HAL_RTC_TIMESTAMP_EXTI_ENABLE_IT()        (EXTI->C2IMR1 |= RTC_EXTI_LINE_TIMESTAMP_EVENT)
#define __HAL_RTC_TIMESTAMP_EXTI_DISABLE_IT()       (EXTI->C2IMR1 &= ~(RTC_EXTI_LINE_TIMESTAMP_EVENT))
#define __HAL_RTC_TIMESTAMP_EXTI_ENABLE_EVENT()    (EXTI->C2EMR1 |= RTC_EXTI_LINE_TIMESTAMP_EVENT)
#define __HAL_RTC_TIMESTAMP_EXTI_DISABLE_EVENT()   (EXTI->C2EMR1 &= ~(RTC_EXTI_LINE_TIMESTAMP_EVENT))
#else
#define __HAL_RTC_TIMESTAMP_EXTI_ENABLE_IT()        (EXTI->IMR1 |= RTC_EXTI_LINE_TIMESTAMP_EVENT)
#define __HAL_RTC_TIMESTAMP_EXTI_DISABLE_IT()       (EXTI->IMR1 &= ~(RTC_EXTI_LINE_TIMESTAMP_EVENT))
#define __HAL_RTC_TIMESTAMP_EXTI_ENABLE_EVENT()    (EXTI->EMR1 |= RTC_EXTI_LINE_TIMESTAMP_EVENT)
#define __HAL_RTC_TIMESTAMP_EXTI_DISABLE_EVENT()   (EXTI->EMR1 &= ~(RTC_EXTI_LINE_TIMESTAMP_EVENT))
#endif

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
  * @retval None
  */
#define __HAL_RTC_TAMPER_ENABLE(__HANDLE__, __TAMPER__)           ((TAMP->CR1 |= (__TAMPER__))

/**
  * @brief  Disable the TAMP Tamper input detection.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __TAMPER__ specifies the RTC Tamper sources to be enabled.
  *         This parameter can be any combination of the following values:
  *            @arg  RTC_TAMPER_ALL: All tampers
  *            @arg  RTC_TAMPER_1: Tamper1
  *            @arg  RTC_TAMPER_2: Tamper2
  *            @arg  RTC_TAMPER_3: Tamper3
  */
#define __HAL_RTC_TAMPER_DISABLE(__HANDLE__, __TAMPER__)           ((TAMP->CR1 &= ~(__TAMPER__))


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
  * @retval None
  */
#define __HAL_RTC_TAMPER_ENABLE_IT(__HANDLE__, __INTERRUPT__)        ((TAMP->IER |= (__INTERRUPT__))

/**
  * @brief  Disable the TAMP Tamper interrupt.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt sources to be disabled.
  *         This parameter can be any combination of the following values:
  *            @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *            @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *            @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  *            @arg  RTC_IT_TAMP_3: Tamper3 interrupt

  * @retval None
  */
#define __HAL_RTC_TAMPER_DISABLE_IT(__HANDLE__, __INTERRUPT__)       ((TAMP->IER &= ~(__INTERRUPT__))


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
  *            @arg  RTC_IT_INT_TAMP_ALL: All Internal Tamper interrupts
  *            @arg  RTC_IT_INT_TAMP_3: Internal Tamper3 interrupt
  *            @arg  RTC_IT_INT_TAMP_5: Internal Tamper5 interrupt
  *            @arg  RTC_IT_INT_TAMP_6: Internal Tamper6 interrupt
  *            @arg  RTC_IT_INT_TAMP_8: Internal Tamper8 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT(__HANDLE__, __INTERRUPT__)     (((((TAMP->MISR) & (__INTERRUPT__)) != 0U) ? 1UL : 0UL)


/**
  * @brief  Check whether the specified RTC Tamper interrupt has been enabled or not.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __INTERRUPT__ specifies the RTC Tamper interrupt source to check.
  *         This parameter can be:
  *            @arg  RTC_IT_TAMP_ALL: All tampers interrupts
  *            @arg  RTC_IT_TAMP_1: Tamper1 interrupt
  *            @arg  RTC_IT_TAMP_2: Tamper2 interrupt
  *            @arg  RTC_IT_TAMP_3: Tamper3 interrupt
  *            @arg  RTC_IT_INT_TAMP_ALL: All internal tampers interrupts
  *            @arg  RTC_IT_INT_TAMP_3: Internal Tamper3 interrupt
  *            @arg  RTC_IT_INT_TAMP_5: Internal Tamper5 interrupt
  *            @arg  RTC_IT_INT_TAMP_6: Internal Tamper6 interrupt
  *            @arg  RTC_IT_INT_TAMP_8: Internal Tamper8 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)    (((((TAMP->IER) & (__INTERRUPT__)) != 0U) ? 1UL : 0UL)


/**
  * @brief  Get the selected RTC Tampers flag status.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Tamper Flag is pending or not.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP_1: Tamper1 flag
  *             @arg RTC_FLAG_TAMP_2: Tamper2 flag
  *             @arg RTC_FLAG_TAMP_3: Tamper3 flag
  *             @arg RTC_FLAG_INT_TAMP_3: Internal Tamper3 interrupt
  *             @arg RTC_FLAG_INT_TAMP_5: Internal Tamper5 interrupt
  *             @arg RTC_FLAG_INT_TAMP_6: Internal Tamper6 interrupt
  *             @arg RTC_FLAG_INT_TAMP_8: Internal Tamper8 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_GET_FLAG(__HANDLE__, __FLAG__)        ((((TAMP->SR) & (__FLAG__)) != 0U) ? 1UL : 0UL)

/**
  * @brief  Clear the RTC Tamper's pending flags.
  * @param  __HANDLE__ specifies the RTC handle.
  * @param  __FLAG__ specifies the RTC Tamper Flag to clear.
  *          This parameter can be:
  *             @arg RTC_FLAG_TAMP_ALL: All tampers flag
  *             @arg RTC_FLAG_TAMP_1: Tamper1 flag
  *             @arg RTC_FLAG_TAMP_2: Tamper2 flag
  *             @arg RTC_FLAG_TAMP_3: Tamper3 flag
  *             @arg RTC_FLAG_INT_TAMP_ALL: All Internal Tamper flags
  *             @arg RTC_FLAG_INT_TAMP_3: Internal Tamper3 interrupt
  *             @arg RTC_FLAG_INT_TAMP_5: Internal Tamper5 interrupt
  *             @arg RTC_FLAG_INT_TAMP_6: Internal Tamper6 interrupt
  *             @arg RTC_FLAG_INT_TAMP_8: Internal Tamper8 interrupt
  * @retval None
  */
#define __HAL_RTC_TAMPER_CLEAR_FLAG(__HANDLE__, __FLAG__)      (((TAMP->SCR) = (__FLAG__)))

/* TAMPER EXTI */
/* ----------- */
#if defined(CORE_CM0PLUS)
#define __HAL_RTC_TAMPER_EXTI_ENABLE_IT()        (EXTI->C2IMR1 |= RTC_EXTI_LINE_TAMPER_EVENT)
#define __HAL_RTC_TAMPER_EXTI_DISABLE_IT()       (EXTI->C2IMR1 &= ~(RTC_EXTI_LINE_TAMPER_EVENT))
#define __HAL_RTC_TAMPER_EXTI_ENABLE_EVENT()    (EXTI->C2EMR1 |= RTC_EXTI_LINE_TAMPER_EVENT)
#define __HAL_RTC_TAMPER_EXTI_DISABLE_EVENT()   (EXTI->C2EMR1 &= ~(RTC_EXTI_LINE_TAMPER_EVENT))
#else
#define __HAL_RTC_TAMPER_EXTI_ENABLE_IT()        (EXTI->IMR1 |= RTC_EXTI_LINE_TAMPER_EVENT)
#define __HAL_RTC_TAMPER_EXTI_DISABLE_IT()       (EXTI->IMR1 &= ~(RTC_EXTI_LINE_TAMPER_EVENT))
#define __HAL_RTC_TAMPER_EXTI_ENABLE_EVENT()    (EXTI->EMR1 |= RTC_EXTI_LINE_TAMPER_EVENT)
#define __HAL_RTC_TAMPER_EXTI_DISABLE_EVENT()   (EXTI->EMR1 &= ~(RTC_EXTI_LINE_TAMPER_EVENT))
#endif

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
#define __HAL_RTC_SSRU_GET_IT(__HANDLE__, __INTERRUPT__)       ((((RTC->MISR) & ((__INTERRUPT__) >> 1) != 0U) ? 1U : 0U)
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

/* SSR Underflow EXTI */
/* ------------------ */
#if defined(CORE_CM0PLUS)
#define __HAL_RTC_SSRU_EXTI_ENABLE_IT()       (EXTI->C2IMR1 |= RTC_EXTI_LINE_SSRU_EVENT)
#define __HAL_RTC_SSRU_EXTI_DISABLE_IT()      (EXTI->C2IMR1 &= ~(RTC_EXTI_LINE_SSRU_EVENT))
#define __HAL_RTC_SSRU_EXTI_ENABLE_EVENT()    (EXTI->C2EMR1 |= RTC_EXTI_LINE_SSRU_EVENT)
#define __HAL_RTC_SSRU_EXTI_DISABLE_EVENT()   (EXTI->C2EMR1 &= ~(RTC_EXTI_LINE_SSRU_EVENT))
#else
#define __HAL_RTC_SSRU_EXTI_ENABLE_IT()       (EXTI->IMR1 |= RTC_EXTI_LINE_SSRU_EVENT)
#define __HAL_RTC_SSRU_EXTI_DISABLE_IT()      (EXTI->IMR1 &= ~(RTC_EXTI_LINE_SSRU_EVENT))
#define __HAL_RTC_SSRU_EXTI_ENABLE_EVENT()    (EXTI->EMR1 |= RTC_EXTI_LINE_SSRU_EVENT)
#define __HAL_RTC_SSRU_EXTI_DISABLE_EVENT()   (EXTI->EMR1 &= ~(RTC_EXTI_LINE_SSRU_EVENT))
#endif

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
void              HAL_RTCEx_Tamper3EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper3EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper5EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper6EventCallback(RTC_HandleTypeDef *hrtc);
void              HAL_RTCEx_InternalTamper8EventCallback(RTC_HandleTypeDef *hrtc);
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
/*#define RTC_EXTI_LINE_ALARM_EVENT           EXTI_IMR1_IM17 */ /*!< External interrupt line 17 Connected to the RTC Alarm event (defined in rtc.h) */
#define RTC_EXTI_LINE_SSRU_EVENT              EXTI_IMR1_IM18 /*!< External interrupt line 18 Connected to the RTC SSR Underflow event  */
#define RTC_EXTI_LINE_TIMESTAMP_EVENT         EXTI_IMR1_IM19 /*!< External interrupt line 19 Connected to the RTC Time Stamp events */
#define RTC_EXTI_LINE_WAKEUPTIMER_EVENT       EXTI_IMR1_IM20 /*!< External interrupt line 20 Connected to the RTC Wakeup event */
#define RTC_EXTI_LINE_TAMPER_EVENT            EXTI_IMR1_IM19 /*!< External interrupt line 19 Connected to the RTC tamper events */
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

#define IS_RTC_ALARM_SUB_SECOND_BINARY_MASK(MASK)   (((MASK) == 0u) || \
                                                    (((MASK) >= RTC_ALARMSUBSECONDBINMASK_SS31_1) && ((MASK) <= RTC_ALARMSUBSECONDBINMASK_NONE)))

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

#ifdef __cplusplus
}
#endif

#endif /* STM32WLxx_HAL_RTC_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
