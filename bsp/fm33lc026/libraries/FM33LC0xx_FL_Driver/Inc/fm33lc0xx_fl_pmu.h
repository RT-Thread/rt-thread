/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_pmu.h
  * @author  FMSH Application Team
  * @brief   Head file of PMU FL Module
  *******************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  *******************************************************************************************************
  */


/* Define to prevent recursive inclusion---------------------------------------------------------------*/
#ifndef __FM33LC0XX_FL_PMU_H
#define __FM33LC0XX_FL_PMU_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lc0xx_fl_def.h"
/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @defgroup PMU PMU
  * @brief PMU FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup PMU_FL_ES_INIT PMU Exported Init structures
  * @{
  */

/**
  * @brief PMU Init Sturcture definition
  */
typedef struct
{

    /*! 低功耗模式下内核电压降低与否 */
    FL_FunState coreVoltageScaling;
    /*! 睡眠模式配置 */
    uint32_t deepSleep;
    /*! 唤醒后的系统频率，仅对RCHF */
    uint32_t wakeupFrequency;
    /*! 芯片LDO是否进入低功耗 */
    uint32_t LDOLowPowerMode;
    /*! 额外唤醒延迟 */
    uint32_t wakeupDelay;
} FL_PMU_SleepInitTypeDef;
/**
  * @}
  */

/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup PMU_FL_Exported_Constants PMU Exported Constants
  * @{
  */

#define    PMU_CR_LDO_LPM_Pos                                     (18U)
#define    PMU_CR_LDO_LPM_Msk                                     (0x3U << PMU_CR_LDO_LPM_Pos)
#define    PMU_CR_LDO_LPM                                         PMU_CR_LDO_LPM_Msk

#define    PMU_CR_LDO15EN_Pos                                     (17U)
#define    PMU_CR_LDO15EN_Msk                                     (0x1U << PMU_CR_LDO15EN_Pos)
#define    PMU_CR_LDO15EN                                         PMU_CR_LDO15EN_Msk

#define    PMU_CR_LDO15EN_B_Pos                                   (16U)
#define    PMU_CR_LDO15EN_B_Msk                                   (0x1U << PMU_CR_LDO15EN_B_Pos)
#define    PMU_CR_LDO15EN_B                                       PMU_CR_LDO15EN_B_Msk

#define    PMU_CR_WKFSEL_Pos                                      (10U)
#define    PMU_CR_WKFSEL_Msk                                      (0x3U << PMU_CR_WKFSEL_Pos)
#define    PMU_CR_WKFSEL                                          PMU_CR_WKFSEL_Msk

#define    PMU_CR_SLPDP_Pos                                       (9U)
#define    PMU_CR_SLPDP_Msk                                       (0x1U << PMU_CR_SLPDP_Pos)
#define    PMU_CR_SLPDP                                           PMU_CR_SLPDP_Msk

#define    PMU_CR_CVS_Pos                                         (8U)
#define    PMU_CR_CVS_Msk                                         (0x1U << PMU_CR_CVS_Pos)
#define    PMU_CR_CVS                                             PMU_CR_CVS_Msk

#define    PMU_CR_PMOD_Pos                                        (0U)
#define    PMU_CR_PMOD_Msk                                        (0x3U << PMU_CR_PMOD_Pos)
#define    PMU_CR_PMOD                                            PMU_CR_PMOD_Msk

#define    PMU_WKTR_STPCLR_Pos                                    (2U)
#define    PMU_WKTR_STPCLR_Msk                                    (0x1U << PMU_WKTR_STPCLR_Pos)
#define    PMU_WKTR_STPCLR                                        PMU_WKTR_STPCLR_Msk

#define    PMU_WKTR_T1A_Pos                                       (0U)
#define    PMU_WKTR_T1A_Msk                                       (0x3U << PMU_WKTR_T1A_Pos)
#define    PMU_WKTR_T1A                                           PMU_WKTR_T1A_Msk

#define    PMU_WKFR_ADCWKF_Pos                                    (31U)
#define    PMU_WKFR_ADCWKF_Msk                                    (0x1U << PMU_WKFR_ADCWKF_Pos)
#define    PMU_WKFR_ADCWKF                                        PMU_WKFR_ADCWKF_Msk

#define    PMU_WKFR_RTCWKF_Pos                                    (28U)
#define    PMU_WKFR_RTCWKF_Msk                                    (0x1U << PMU_WKFR_RTCWKF_Pos)
#define    PMU_WKFR_RTCWKF                                        PMU_WKFR_RTCWKF_Msk

#define    PMU_WKFR_SVDWKF_Pos                                    (27U)
#define    PMU_WKFR_SVDWKF_Msk                                    (0x1U << PMU_WKFR_SVDWKF_Pos)
#define    PMU_WKFR_SVDWKF                                        PMU_WKFR_SVDWKF_Msk

#define    PMU_WKFR_LFDETWKF_Pos                                  (26U)
#define    PMU_WKFR_LFDETWKF_Msk                                  (0x1U << PMU_WKFR_LFDETWKF_Pos)
#define    PMU_WKFR_LFDETWKF                                      PMU_WKFR_LFDETWKF_Msk

#define    PMU_WKFR_VREFWKF_Pos                                   (25U)
#define    PMU_WKFR_VREFWKF_Msk                                   (0x1U << PMU_WKFR_VREFWKF_Pos)
#define    PMU_WKFR_VREFWKF                                       PMU_WKFR_VREFWKF_Msk

#define    PMU_WKFR_IOWKF_Pos                                     (24U)
#define    PMU_WKFR_IOWKF_Msk                                     (0x1U << PMU_WKFR_IOWKF_Pos)
#define    PMU_WKFR_IOWKF                                         PMU_WKFR_IOWKF_Msk

#define    PMU_WKFR_IICWKF_Pos                                    (23U)
#define    PMU_WKFR_IICWKF_Msk                                    (0x1U << PMU_WKFR_IICWKF_Pos)
#define    PMU_WKFR_IICWKF                                        PMU_WKFR_IICWKF_Msk

#define    PMU_WKFR_LPU1WKF_Pos                                   (21U)
#define    PMU_WKFR_LPU1WKF_Msk                                   (0x1U << PMU_WKFR_LPU1WKF_Pos)
#define    PMU_WKFR_LPU1WKF                                       PMU_WKFR_LPU1WKF_Msk

#define    PMU_WKFR_LPU0WKF_Pos                                   (20U)
#define    PMU_WKFR_LPU0WKF_Msk                                   (0x1U << PMU_WKFR_LPU0WKF_Pos)
#define    PMU_WKFR_LPU0WKF                                       PMU_WKFR_LPU0WKF_Msk

#define    PMU_WKFR_UART1WKF_Pos                                  (19U)
#define    PMU_WKFR_UART1WKF_Msk                                  (0x1U << PMU_WKFR_UART1WKF_Pos)
#define    PMU_WKFR_UART1WKF                                      PMU_WKFR_UART1WKF_Msk

#define    PMU_WKFR_UART0WKF_Pos                                  (18U)
#define    PMU_WKFR_UART0WKF_Msk                                  (0x1U << PMU_WKFR_UART0WKF_Pos)
#define    PMU_WKFR_UART0WKF                                      PMU_WKFR_UART0WKF_Msk

#define    PMU_WKFR_OPA2WKF_Pos                                   (17U)
#define    PMU_WKFR_OPA2WKF_Msk                                   (0x1U << PMU_WKFR_OPA2WKF_Pos)
#define    PMU_WKFR_OPA2WKF                                       PMU_WKFR_OPA2WKF_Msk

#define    PMU_WKFR_OPA1WKF_Pos                                   (16U)
#define    PMU_WKFR_OPA1WKF_Msk                                   (0x1U << PMU_WKFR_OPA1WKF_Pos)
#define    PMU_WKFR_OPA1WKF                                       PMU_WKFR_OPA1WKF_Msk

#define    PMU_WKFR_LPTWKF_Pos                                    (10U)
#define    PMU_WKFR_LPTWKF_Msk                                    (0x1U << PMU_WKFR_LPTWKF_Pos)
#define    PMU_WKFR_LPTWKF                                        PMU_WKFR_LPTWKF_Msk

#define    PMU_WKFR_BSTWKF_Pos                                    (9U)
#define    PMU_WKFR_BSTWKF_Msk                                    (0x1U << PMU_WKFR_BSTWKF_Pos)
#define    PMU_WKFR_BSTWKF                                        PMU_WKFR_BSTWKF_Msk

#define    PMU_WKFR_DBGWKF_Pos                                    (8U)
#define    PMU_WKFR_DBGWKF_Msk                                    (0x1U << PMU_WKFR_DBGWKF_Pos)
#define    PMU_WKFR_DBGWKF                                        PMU_WKFR_DBGWKF_Msk

#define    PMU_WKFR_WKPXF_Pos                                     (0U)
#define    PMU_WKFR_WKPXF_Msk                                     (0xffU << PMU_WKFR_WKPXF_Pos)
#define    PMU_WKFR_WKPXF                                         PMU_WKFR_WKPXF_Msk

#define    PMU_IER_LPRUNEIE_Pos                                   (3U)
#define    PMU_IER_LPRUNEIE_Msk                                   (0x1U << PMU_IER_LPRUNEIE_Pos)
#define    PMU_IER_LPRUNEIE                                       PMU_IER_LPRUNEIE_Msk

#define    PMU_IER_LPACTEIE_Pos                                   (2U)
#define    PMU_IER_LPACTEIE_Msk                                   (0x1U << PMU_IER_LPACTEIE_Pos)
#define    PMU_IER_LPACTEIE                                       PMU_IER_LPACTEIE_Msk

#define    PMU_IER_SLPEIE_Pos                                     (1U)
#define    PMU_IER_SLPEIE_Msk                                     (0x1U << PMU_IER_SLPEIE_Pos)
#define    PMU_IER_SLPEIE                                         PMU_IER_SLPEIE_Msk

#define    PMU_IER_RTCEIE_Pos                                     (0U)
#define    PMU_IER_RTCEIE_Msk                                     (0x1U << PMU_IER_RTCEIE_Pos)
#define    PMU_IER_RTCEIE                                         PMU_IER_RTCEIE_Msk

#define    PMU_ISR_SLPUNEIE_Pos                                   (3U)
#define    PMU_ISR_SLPUNEIE_Msk                                   (0x1U << PMU_ISR_SLPUNEIE_Pos)
#define    PMU_ISR_SLPUNEIE                                       PMU_ISR_SLPUNEIE_Msk

#define    PMU_ISR_LPACTEIF_Pos                                   (2U)
#define    PMU_ISR_LPACTEIF_Msk                                   (0x1U << PMU_ISR_LPACTEIF_Pos)
#define    PMU_ISR_LPACTEIF                                       PMU_ISR_LPACTEIF_Msk

#define    PMU_ISR_SLPEIF_Pos                                     (1U)
#define    PMU_ISR_SLPEIF_Msk                                     (0x1U << PMU_ISR_SLPEIF_Pos)
#define    PMU_ISR_SLPEIF                                         PMU_ISR_SLPEIF_Msk

#define    PMU_ISR_RTCEIF_Pos                                     (0U)
#define    PMU_ISR_RTCEIF_Msk                                     (0x1U << PMU_ISR_RTCEIF_Pos)
#define    PMU_ISR_RTCEIF                                         PMU_ISR_RTCEIF_Msk



#define    FL_PMU_WKUP0PIN                                        (0x1U << 0U)
#define    FL_PMU_WKUP1PIN                                        (0x1U << 1U)
#define    FL_PMU_WKUP2PIN                                        (0x1U << 2U)
#define    FL_PMU_WKUP3PIN                                        (0x1U << 3U)
#define    FL_PMU_WKUP4PIN                                        (0x1U << 4U)
#define    FL_PMU_WKUP5PIN                                        (0x1U << 5U)
#define    FL_PMU_WKUP6PIN                                        (0x1U << 6U)
#define    FL_PMU_WKUP7PIN                                        (0x1U << 7U)



#define    FL_PMU_LDO_LPM_DISABLE                                 (0x0U << PMU_CR_LDO_LPM_Pos)
#define    FL_PMU_LDO_LPM_ENABLE                                  (0x2U << PMU_CR_LDO_LPM_Pos)


#define    FL_PMU_RCHF_WAKEUP_FREQ_8MHZ                           (0x0U << PMU_CR_WKFSEL_Pos)
#define    FL_PMU_RCHF_WAKEUP_FREQ_16MHZ                          (0x1U << PMU_CR_WKFSEL_Pos)
#define    FL_PMU_RCHF_WAKEUP_FREQ_24MHZ                          (0x2U << PMU_CR_WKFSEL_Pos)


#define    FL_PMU_SLEEP_MODE_DEEP                                 (0x1U << PMU_CR_SLPDP_Pos)
#define    FL_PMU_SLEEP_MODE_NORMAL                               (0x0U << PMU_CR_SLPDP_Pos)


#define    FL_PMU_POWER_MODE_ACTIVE_OR_LPACTIVE                   (0x0U << PMU_CR_PMOD_Pos)
#define    FL_PMU_POWER_MODE_LPRUN_ONLY                           (0x1U << PMU_CR_PMOD_Pos)
#define    FL_PMU_POWER_MODE_SLEEP_OR_DEEPSLEEP                   (0x2U << PMU_CR_PMOD_Pos)

#define    FL_PMU_FLASH_STOP_CLEAR_MODE_ASYNCHRONOUS              (0x0U << PMU_WKTR_STPCLR_Pos)
#define    FL_PMU_FLASH_STOP_CLEAR_MODE_SYNCHRONOUS               (0x1U << PMU_WKTR_STPCLR_Pos)


#define    FL_PMU_WAKEUP_DELAY_0US                                (0x0U << PMU_WKTR_T1A_Pos)
#define    FL_PMU_WAKEUP_DELAY_2US                                (0x1U << PMU_WKTR_T1A_Pos)
#define    FL_PMU_WAKEUP_DELAY_4US                                (0x2U << PMU_WKTR_T1A_Pos)
#define    FL_PMU_WAKEUP_DELAY_8US                                (0x3U << PMU_WKTR_T1A_Pos)


/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup PMU_FL_Exported_Functions PMU Exported Functions
  * @{
  */

/**
  * @brief    Set LDO Low Power Mode
  * @rmtoll   CR    LDO_LPM    FL_PMU_SetLDOLowPowerMode
  * @param    PMUx PMU instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_PMU_LDO_LPM_DISABLE
  *           @arg @ref FL_PMU_LDO_LPM_ENABLE
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_SetLDOLowPowerMode(PMU_Type *PMUx, uint32_t mode)
{
    MODIFY_REG(PMUx->CR, PMU_CR_LDO_LPM_Msk, mode);
}

/**
  * @brief    Get LDO Low Power Mode Setting
  * @rmtoll   CR    LDO_LPM    FL_PMU_GetLDOLowPowerMode
  * @param    PMUx PMU instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_PMU_LDO_LPM_DISABLE
  *           @arg @ref FL_PMU_LDO_LPM_ENABLE
  */
__STATIC_INLINE uint32_t FL_PMU_GetLDOLowPowerMode(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->CR, PMU_CR_LDO_LPM_Msk));
}

/**
  * @brief    Get LDO15 Enable Status
  * @rmtoll   CR    LDO15EN    FL_PMU_GetLDO15Status
  * @param    PMUx PMU instance
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_PMU_GetLDO15Status(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->CR, PMU_CR_LDO15EN_Msk));
}

/**
  * @brief    Get LDO15 Inverse check bit
  * @rmtoll   CR    LDO15EN_B    FL_PMU_GetLDO15StatusInvert
  * @param    PMUx PMU instance
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_PMU_GetLDO15StatusInvert(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->CR, PMU_CR_LDO15EN_B_Msk));
}

/**
  * @brief    Set RCHF Frequency After Wakeup
  * @rmtoll   CR    WKFSEL    FL_PMU_SetRCHFWakeupFrequency
  * @param    PMUx PMU instance
  * @param    freq This parameter can be one of the following values:
  *           @arg @ref FL_PMU_RCHF_WAKEUP_FREQ_8MHZ
  *           @arg @ref FL_PMU_RCHF_WAKEUP_FREQ_16MHZ
  *           @arg @ref FL_PMU_RCHF_WAKEUP_FREQ_24MHZ
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_SetRCHFWakeupFrequency(PMU_Type *PMUx, uint32_t freq)
{
    MODIFY_REG(PMUx->CR, PMU_CR_WKFSEL_Msk, freq);
}

/**
  * @brief    Get RCHF Frequency After Wakeup Setting
  * @rmtoll   CR    WKFSEL    FL_PMU_GetRCHFWakeupFrequency
  * @param    PMUx PMU instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_PMU_RCHF_WAKEUP_FREQ_8MHZ
  *           @arg @ref FL_PMU_RCHF_WAKEUP_FREQ_16MHZ
  *           @arg @ref FL_PMU_RCHF_WAKEUP_FREQ_24MHZ
  */
__STATIC_INLINE uint32_t FL_PMU_GetRCHFWakeupFrequency(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->CR, PMU_CR_WKFSEL_Msk));
}

/**
  * @brief    Set Sleep Mode
  * @rmtoll   CR    SLPDP    FL_PMU_SetSleepMode
  * @param    PMUx PMU instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_PMU_SLEEP_MODE_DEEP
  *           @arg @ref FL_PMU_SLEEP_MODE_NORMAL
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_SetSleepMode(PMU_Type *PMUx, uint32_t mode)
{
    MODIFY_REG(PMUx->CR, PMU_CR_SLPDP_Msk, mode);
}

/**
  * @brief    Get Sleep Mode Setting
  * @rmtoll   CR    SLPDP    FL_PMU_GetSleepMode
  * @param    PMUx PMU instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_PMU_SLEEP_MODE_DEEP
  *           @arg @ref FL_PMU_SLEEP_MODE_NORMAL
  */
__STATIC_INLINE uint32_t FL_PMU_GetSleepMode(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->CR, PMU_CR_SLPDP_Msk));
}

/**
  * @brief    Enable Core Voltage Scaling Under Low Power Mode
  * @rmtoll   CR    CVS    FL_PMU_EnableCoreVoltageScaling
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_EnableCoreVoltageScaling(PMU_Type *PMUx)
{
    SET_BIT(PMUx->CR, PMU_CR_CVS_Msk);
}

/**
  * @brief    Get Core Voltage Scaling Under Low Power Mode Enable Status
  * @rmtoll   CR    CVS    FL_PMU_IsEnabledCoreVoltageScaling
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsEnabledCoreVoltageScaling(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->CR, PMU_CR_CVS_Msk) == PMU_CR_CVS_Msk);
}

/**
  * @brief    Disable Core Voltage Scaling Under Low Power Mode
  * @rmtoll   CR    CVS    FL_PMU_DisableCoreVoltageScaling
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_DisableCoreVoltageScaling(PMU_Type *PMUx)
{
    CLEAR_BIT(PMUx->CR, PMU_CR_CVS_Msk);
}

/**
  * @brief    Set Low Power Mode
  * @rmtoll   CR    PMOD    FL_PMU_SetLowPowerMode
  * @param    PMUx PMU instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_PMU_POWER_MODE_ACTIVE_OR_LPACTIVE
  *           @arg @ref FL_PMU_POWER_MODE_LPRUN_ONLY
  *           @arg @ref FL_PMU_POWER_MODE_SLEEP_OR_DEEPSLEEP
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_SetLowPowerMode(PMU_Type *PMUx, uint32_t mode)
{
    MODIFY_REG(PMUx->CR, PMU_CR_PMOD_Msk, mode);
}

/**
  * @brief    Get Low Power Mode Setting
  * @rmtoll   CR    PMOD    FL_PMU_GetLowPowerMode
  * @param    PMUx PMU instance
  * @retval   Returned value can be one of the following values:
  */
__STATIC_INLINE uint32_t FL_PMU_GetLowPowerMode(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->CR, PMU_CR_PMOD_Msk));
}

/**
  * @brief    Set Flash Stop Signal Clear Way
  * @rmtoll   WKTR    STPCLR    FL_PMU_SetFlashStopSignalClearMode
  * @param    PMUx PMU instance
  * @param    config This parameter can be one of the following values:
  *           @arg @ref FL_PMU_FLASH_STOP_CLEAR_MODE_ASYNCHRONOUS
  *           @arg @ref FL_PMU_FLASH_STOP_CLEAR_MODE_SYNCHRONOUS
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_SetFlashStopSignalClearMode(PMU_Type *PMUx, uint32_t config)
{
    MODIFY_REG(PMUx->WKTR, PMU_WKTR_STPCLR_Msk, config);
}

/**
  * @brief    Get Flash Stop Signal Clear Way Setting
  * @rmtoll   WKTR    STPCLR    FL_PMU_GetFlashStopSignalClearMode
  * @param    PMUx PMU instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_PMU_FLASH_STOP_CLEAR_MODE_ASYNCHRONOUS
  *           @arg @ref FL_PMU_FLASH_STOP_CLEAR_MODE_SYNCHRONOUS
  */
__STATIC_INLINE uint32_t FL_PMU_GetFlashStopSignalClearMode(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKTR, PMU_WKTR_STPCLR_Msk));
}

/**
  * @brief    Set Extra Wakeup Delay Under Sleep/DeepSleep Mode
  * @rmtoll   WKTR    T1A    FL_PMU_SetWakeupDelay
  * @param    PMUx PMU instance
  * @param    time This parameter can be one of the following values:
  *           @arg @ref FL_PMU_WAKEUP_DELAY_0US
  *           @arg @ref FL_PMU_WAKEUP_DELAY_2US
  *           @arg @ref FL_PMU_WAKEUP_DELAY_4US
  *           @arg @ref FL_PMU_WAKEUP_DELAY_8US
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_SetWakeupDelay(PMU_Type *PMUx, uint32_t time)
{
    MODIFY_REG(PMUx->WKTR, PMU_WKTR_T1A_Msk, time);
}

/**
  * @brief    Get Extra Wakeup Delay Under Sleep/DeepSleep Mode Setting
  * @rmtoll   WKTR    T1A    FL_PMU_GetWakeupDelay
  * @param    PMUx PMU instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_PMU_WAKEUP_DELAY_0US
  *           @arg @ref FL_PMU_WAKEUP_DELAY_2US
  *           @arg @ref FL_PMU_WAKEUP_DELAY_4US
  *           @arg @ref FL_PMU_WAKEUP_DELAY_8US
  */
__STATIC_INLINE uint32_t FL_PMU_GetWakeupDelay(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKTR, PMU_WKTR_T1A_Msk));
}

/**
  * @brief    Get ADC interrupt wakeup flag
  * @rmtoll   WKFR    ADCWKF    FL_PMU_IsActiveFlag_WakeupADC
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupADC(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_ADCWKF_Msk) == (PMU_WKFR_ADCWKF_Msk));
}

/**
  * @brief    Get RTC interrupt wakeup flag
  * @rmtoll   WKFR    RTCWKF    FL_PMU_IsActiveFlag_WakeupRTC
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupRTC(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_RTCWKF_Msk) == (PMU_WKFR_RTCWKF_Msk));
}

/**
  * @brief    Get SVD interrupt wakeup flag
  * @rmtoll   WKFR    SVDWKF    FL_PMU_IsActiveFlag_WakeupSVD
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupSVD(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_SVDWKF_Msk) == (PMU_WKFR_SVDWKF_Msk));
}

/**
  * @brief    Get LFDET interrupt wakeup flag
  * @rmtoll   WKFR    LFDETWKF    FL_PMU_IsActiveFlag_WakeupLFDET
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupLFDET(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_LFDETWKF_Msk) == (PMU_WKFR_LFDETWKF_Msk));
}

/**
  * @brief    Get VREF interrupt wakeup flag
  * @rmtoll   WKFR    VREFWKF    FL_PMU_IsActiveFlag_WakeupVREF
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupVREF(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_VREFWKF_Msk) == (PMU_WKFR_VREFWKF_Msk));
}

/**
  * @brief    Get IO interrupt wakeup flag
  * @rmtoll   WKFR    IOWKF    FL_PMU_IsActiveFlag_WakeupEXTI
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupEXTI(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_IOWKF_Msk) == (PMU_WKFR_IOWKF_Msk));
}

/**
  * @brief    Get I2C interrupt wakeup flag
  * @rmtoll   WKFR    IICWKF    FL_PMU_IsActiveFlag_WakeupI2C
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupI2C(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_IICWKF_Msk) == (PMU_WKFR_IICWKF_Msk));
}

/**
  * @brief    Get LPUART1 interrupt wakeup flag
  * @rmtoll   WKFR    LPU1WKF    FL_PMU_IsActiveFlag_WakeupLPUART1
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupLPUART1(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_LPU1WKF_Msk) == (PMU_WKFR_LPU1WKF_Msk));
}

/**
  * @brief    Get LPUART0 interrupt wakeup flag
  * @rmtoll   WKFR    LPU0WKF    FL_PMU_IsActiveFlag_WakeupLPUART0
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupLPUART0(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_LPU0WKF_Msk) == (PMU_WKFR_LPU0WKF_Msk));
}

/**
  * @brief    Get UART1 interrupt wakeup flag
  * @rmtoll   WKFR    UART1WKF    FL_PMU_IsActiveFlag_WakeupUART1
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupUART1(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_UART1WKF_Msk) == (PMU_WKFR_UART1WKF_Msk));
}

/**
  * @brief    Get UART0 interrupt wakeup flag
  * @rmtoll   WKFR    UART0WKF    FL_PMU_IsActiveFlag_WakeupUART0
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupUART0(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_UART0WKF_Msk) == (PMU_WKFR_UART0WKF_Msk));
}

/**
  * @brief    Get COMP2 interrrupt wakeup flag
  * @rmtoll   WKFR    OPA2WKF    FL_PMU_IsActiveFlag_WakeupCOMP2
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupCOMP2(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_OPA2WKF_Msk) == (PMU_WKFR_OPA2WKF_Msk));
}

/**
  * @brief    Get COMP1 interrrupt wakeup flag
  * @rmtoll   WKFR    OPA1WKF    FL_PMU_IsActiveFlag_WakeupCOMP1
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupCOMP1(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_OPA1WKF_Msk) == (PMU_WKFR_OPA1WKF_Msk));
}

/**
  * @brief    Get LPTIM32 interrupt wakeup flag
  * @rmtoll   WKFR    LPTWKF    FL_PMU_IsActiveFlag_WakeupLPTIM32
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupLPTIM32(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_LPTWKF_Msk) == (PMU_WKFR_LPTWKF_Msk));
}

/**
  * @brief    Get BSTIM32 interrupt wakeup flag
  * @rmtoll   WKFR    BSTWKF    FL_PMU_IsActiveFlag_WakeupBSTIM32
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupBSTIM32(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_BSTWKF_Msk) == (PMU_WKFR_BSTWKF_Msk));
}

/**
  * @brief    Get CPU Debugger wakeup flag
  * @rmtoll   WKFR    DBGWKF    FL_PMU_IsActiveFlag_WakeupDBG
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupDBG(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, PMU_WKFR_DBGWKF_Msk) == (PMU_WKFR_DBGWKF_Msk));
}

/**
  * @brief    Clear CPU Debugger wakeup flag
  * @rmtoll   WKFR    DBGWKF    FL_PMU_ClearFlag_WakeupDBG
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_ClearFlag_WakeupDBG(PMU_Type *PMUx)
{
    WRITE_REG(PMUx->WKFR, PMU_WKFR_DBGWKF_Msk);
}

/**
  * @brief    Get pinx wakeup flag
  * @rmtoll   WKFR    WKPXF    FL_PMU_IsActiveFlag_WakeupPIN
  * @param    PMUx PMU instance
  * @param    Pin This parameter can be one of the following values:
  *           @arg @ref FL_PMU_WKUP0PIN
  *           @arg @ref FL_PMU_WKUP1PIN
  *           @arg @ref FL_PMU_WKUP2PIN
  *           @arg @ref FL_PMU_WKUP3PIN
  *           @arg @ref FL_PMU_WKUP4PIN
  *           @arg @ref FL_PMU_WKUP5PIN
  *           @arg @ref FL_PMU_WKUP6PIN
  *           @arg @ref FL_PMU_WKUP7PIN
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_WakeupPIN(PMU_Type *PMUx, uint32_t Pin)
{
    return (uint32_t)(READ_BIT(PMUx->WKFR, ((Pin & 0xff) << 0x0U)) == ((Pin & 0xff) << 0x0U));
}

/**
  * @brief    Clear pinx wakeup flag
  * @rmtoll   WKFR    WKPXF    FL_PMU_ClearFlag_WakeupPIN
  * @param    PMUx PMU instance
  * @param    Pin This parameter can be one of the following values:
  *           @arg @ref FL_PMU_WKUP0PIN
  *           @arg @ref FL_PMU_WKUP1PIN
  *           @arg @ref FL_PMU_WKUP2PIN
  *           @arg @ref FL_PMU_WKUP3PIN
  *           @arg @ref FL_PMU_WKUP4PIN
  *           @arg @ref FL_PMU_WKUP5PIN
  *           @arg @ref FL_PMU_WKUP6PIN
  *           @arg @ref FL_PMU_WKUP7PIN
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_ClearFlag_WakeupPIN(PMU_Type *PMUx, uint32_t Pin)
{
    WRITE_REG(PMUx->WKFR, ((Pin & 0xff) << 0x0U));
}

/**
  * @brief    LPREIE error interrupt enable
  * @rmtoll   IER    LPRUNEIE    FL_PMU_EnableIT_LPRunError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_EnableIT_LPRunError(PMU_Type *PMUx)
{
    SET_BIT(PMUx->IER, PMU_IER_LPRUNEIE_Msk);
}

/**
  * @brief    Get LPREIE error interrupt enable status
  * @rmtoll   IER    LPRUNEIE    FL_PMU_IsEnabledIT_LPRunError
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsEnabledIT_LPRunError(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->IER, PMU_IER_LPRUNEIE_Msk) == PMU_IER_LPRUNEIE_Msk);
}

/**
  * @brief    LPREIE error interrupt disable
  * @rmtoll   IER    LPRUNEIE    FL_PMU_DisableIT_LPRunError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_DisableIT_LPRunError(PMU_Type *PMUx)
{
    CLEAR_BIT(PMUx->IER, PMU_IER_LPRUNEIE_Msk);
}

/**
  * @brief    LPActive error interrupt enable
  * @rmtoll   IER    LPACTEIE    FL_PMU_EnableIT_LPActiveError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_EnableIT_LPActiveError(PMU_Type *PMUx)
{
    SET_BIT(PMUx->IER, PMU_IER_LPACTEIE_Msk);
}

/**
  * @brief    Get LPActive error interrupt enable status
  * @rmtoll   IER    LPACTEIE    FL_PMU_IsEnabledIT_LPActiveError
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsEnabledIT_LPActiveError(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->IER, PMU_IER_LPACTEIE_Msk) == PMU_IER_LPACTEIE_Msk);
}

/**
  * @brief    LPActive error interrupt disable
  * @rmtoll   IER    LPACTEIE    FL_PMU_DisableIT_LPActiveError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_DisableIT_LPActiveError(PMU_Type *PMUx)
{
    CLEAR_BIT(PMUx->IER, PMU_IER_LPACTEIE_Msk);
}

/**
  * @brief    Sleep error interrupt enable
  * @rmtoll   IER    SLPEIE    FL_PMU_EnableIT_SleepError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_EnableIT_SleepError(PMU_Type *PMUx)
{
    SET_BIT(PMUx->IER, PMU_IER_SLPEIE_Msk);
}

/**
  * @brief    Get sleep error interrupt enable status
  * @rmtoll   IER    SLPEIE    FL_PMU_IsEnabledIT_SleepError
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsEnabledIT_SleepError(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->IER, PMU_IER_SLPEIE_Msk) == PMU_IER_SLPEIE_Msk);
}

/**
  * @brief    sleep error interrupt disable
  * @rmtoll   IER    SLPEIE    FL_PMU_DisableIT_SleepError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_DisableIT_SleepError(PMU_Type *PMUx)
{
    CLEAR_BIT(PMUx->IER, PMU_IER_SLPEIE_Msk);
}

/**
  * @brief    RTCBKP error interrupt enable
  * @rmtoll   IER    RTCEIE    FL_PMU_EnableIT_RTCBKPError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_EnableIT_RTCBKPError(PMU_Type *PMUx)
{
    SET_BIT(PMUx->IER, PMU_IER_RTCEIE_Msk);
}

/**
  * @brief    Get RTCBKP error interrupt enable status
  * @rmtoll   IER    RTCEIE    FL_PMU_IsEnabledIT_RTCBKPError
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsEnabledIT_RTCBKPError(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->IER, PMU_IER_RTCEIE_Msk) == PMU_IER_RTCEIE_Msk);
}

/**
  * @brief    Sleep error interrupt disable
  * @rmtoll   IER    RTCEIE    FL_PMU_DisableIT_RTCBKPError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_DisableIT_RTCBKPError(PMU_Type *PMUx)
{
    CLEAR_BIT(PMUx->IER, PMU_IER_RTCEIE_Msk);
}

/**
  * @brief    Get LPRUN error interrupt flag
  * @rmtoll   ISR    SLPUNEIE    FL_PMU_IsActiveFlag_LPRunError
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_LPRunError(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->ISR, PMU_ISR_SLPUNEIE_Msk) == (PMU_ISR_SLPUNEIE_Msk));
}

/**
  * @brief    Clear LPRUN error interrupt flag
  * @rmtoll   ISR    SLPUNEIE    FL_PMU_ClearFlag_LPRunError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_ClearFlag_LPRunError(PMU_Type *PMUx)
{
    WRITE_REG(PMUx->ISR, PMU_ISR_SLPUNEIE_Msk);
}

/**
  * @brief    Get LPACTIF error interrupt flag
  * @rmtoll   ISR    LPACTEIF    FL_PMU_IsActiveFlag_LPActiveError
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_LPActiveError(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->ISR, PMU_ISR_LPACTEIF_Msk) == (PMU_ISR_LPACTEIF_Msk));
}

/**
  * @brief    Clear LPACTIF error interrupt flag
  * @rmtoll   ISR    LPACTEIF    FL_PMU_ClearFlag_LPActiveError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_ClearFlag_LPActiveError(PMU_Type *PMUx)
{
    WRITE_REG(PMUx->ISR, PMU_ISR_LPACTEIF_Msk);
}

/**
  * @brief    Get SLEEP error interrupt flag
  * @rmtoll   ISR    SLPEIF    FL_PMU_IsActiveFlag_SleepError
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_SleepError(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->ISR, PMU_ISR_SLPEIF_Msk) == (PMU_ISR_SLPEIF_Msk));
}

/**
  * @brief    Clear SLEEP error interrupt flag
  * @rmtoll   ISR    SLPEIF    FL_PMU_ClearFlag_SleepError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_ClearFlag_SleepError(PMU_Type *PMUx)
{
    WRITE_REG(PMUx->ISR, PMU_ISR_SLPEIF_Msk);
}

/**
  * @brief    Get RTCBKP error interrupt flag
  * @rmtoll   ISR    RTCEIF    FL_PMU_IsActiveFlag_RTCError
  * @param    PMUx PMU instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_PMU_IsActiveFlag_RTCError(PMU_Type *PMUx)
{
    return (uint32_t)(READ_BIT(PMUx->ISR, PMU_ISR_RTCEIF_Msk) == (PMU_ISR_RTCEIF_Msk));
}

/**
  * @brief    Clear RTCBKP error interrupt flag
  * @rmtoll   ISR    RTCEIF    FL_PMU_ClearFlag_RTCError
  * @param    PMUx PMU instance
  * @retval   None
  */
__STATIC_INLINE void FL_PMU_ClearFlag_RTCError(PMU_Type *PMUx)
{
    WRITE_REG(PMUx->ISR, PMU_ISR_RTCEIF_Msk);
}

/**
  * @}
  */

/** @defgroup PMU_FL_EF_Init Initialization and de-initialization functions
  * @{
  */

FL_ErrorStatus FL_PMU_Sleep_DeInit(PMU_Type *PMUx);
FL_ErrorStatus FL_PMU_Sleep_Init(PMU_Type *PMUx, FL_PMU_SleepInitTypeDef *LPM_InitStruct);
void FL_PMU_StructInit(FL_PMU_SleepInitTypeDef *LPM_InitStruct);

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

#endif /* __FM33LC0XX_FL_PMU_H*/

/*************************Py_Code_Generator Version: 0.1-0.11-0.2 @ 2020-09-23*************************/
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
