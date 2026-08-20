/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_vrefp.h
  * @author  FMSH Application Team
  * @brief   Head file of VREFP FL Module
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
#ifndef __FM33LG0XX_FL_VREFP_H
#define __FM33LG0XX_FL_VREFP_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes -------------------------------------------------------------------------------------------*/
#include "fm33lg0xx_fl_def.h"
/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @defgroup VREFP VREFP
  * @brief VREFP FL driver
  * @{
  */

/* Exported types -------------------------------------------------------------------------------------*/
/** @defgroup VREFP_FL_ES_INIT VREFP Exported Init structures
  * @{
  */

/**
  * @brief FL VREFP Init Sturcture definition
  */
typedef  struct
{
    /* 输出电压的TRIM值 */
    uint32_t voltageTrim;
    /* 输出电压值 */
    uint32_t outputVoltage;
    /* VREFP输出模式 */
    uint32_t mode;
    /* 间歇模式下单次驱动时间 */
    uint32_t timeOfDriving;
    /* 间歇模式下使能周期 */
    uint32_t timeOfPeriod;

} FL_VREFP_InitTypeDef;
/**
  * @}
  */
/* Exported constants ---------------------------------------------------------------------------------*/
/** @defgroup VREFP_FL_Exported_Constants VREFP Exported Constants
  * @{
  */

#define    VREFP_CR_DENDIE_Pos                                    (2U)
#define    VREFP_CR_DENDIE_Msk                                    (0x1U << VREFP_CR_DENDIE_Pos)
#define    VREFP_CR_DENDIE                                        VREFP_CR_DENDIE_Msk

#define    VREFP_CR_POVIE_Pos                                     (1U)
#define    VREFP_CR_POVIE_Msk                                     (0x1U << VREFP_CR_POVIE_Pos)
#define    VREFP_CR_POVIE                                         VREFP_CR_POVIE_Msk

#define    VREFP_CR_EN_Pos                                        (0U)
#define    VREFP_CR_EN_Msk                                        (0x1U << VREFP_CR_EN_Pos)
#define    VREFP_CR_EN                                            VREFP_CR_EN_Msk

#define    VREFP_CFGR_VRS_Pos                                     (8U)
#define    VREFP_CFGR_VRS_Msk                                     (0x7U << VREFP_CFGR_VRS_Pos)
#define    VREFP_CFGR_VRS                                         VREFP_CFGR_VRS_Msk

#define    VREFP_CFGR_TPERIOD_Pos                                 (5U)
#define    VREFP_CFGR_TPERIOD_Msk                                 (0x7U << VREFP_CFGR_TPERIOD_Pos)
#define    VREFP_CFGR_TPERIOD                                     VREFP_CFGR_TPERIOD_Msk

#define    VREFP_CFGR_TDRV_Pos                                    (2U)
#define    VREFP_CFGR_TDRV_Msk                                    (0x7U << VREFP_CFGR_TDRV_Pos)
#define    VREFP_CFGR_TDRV                                        VREFP_CFGR_TDRV_Msk

#define    VREFP_CFGR_LPM_Pos                                     (1U)
#define    VREFP_CFGR_LPM_Msk                                     (0x1U << VREFP_CFGR_LPM_Pos)
#define    VREFP_CFGR_LPM                                         VREFP_CFGR_LPM_Msk

#define    VREFP_ISR_BUSY_Pos                                     (2U)
#define    VREFP_ISR_BUSY_Msk                                     (0x1U << VREFP_ISR_BUSY_Pos)
#define    VREFP_ISR_BUSY                                         VREFP_ISR_BUSY_Msk

#define    VREFP_ISR_DEND_Pos                                     (1U)
#define    VREFP_ISR_DEND_Msk                                     (0x1U << VREFP_ISR_DEND_Pos)
#define    VREFP_ISR_DEND                                         VREFP_ISR_DEND_Msk

#define    VREFP_ISR_POV_Pos                                      (0U)
#define    VREFP_ISR_POV_Msk                                      (0x1U << VREFP_ISR_POV_Pos)
#define    VREFP_ISR_POV                                          VREFP_ISR_POV_Msk






#define    FL_VREFP_OUTPUT_VOLTAGE_2P0V                           (0x0U << VREFP_CFGR_VRS_Pos)
#define    FL_VREFP_OUTPUT_VOLTAGE_2P5V                           (0x1U << VREFP_CFGR_VRS_Pos)
#define    FL_VREFP_OUTPUT_VOLTAGE_3P0V                           (0x2U << VREFP_CFGR_VRS_Pos)
#define    FL_VREFP_OUTPUT_VOLTAGE_4P5V                           (0x3U << VREFP_CFGR_VRS_Pos)
#define    FL_VREFP_OUTPUT_VOLTAGE_1P5V                           (0x4U << VREFP_CFGR_VRS_Pos)


#define    FL_VREFP_ENABLE_PERIOD_1MS                             (0x0U << VREFP_CFGR_TPERIOD_Pos)
#define    FL_VREFP_ENABLE_PERIOD_4MS                             (0x1U << VREFP_CFGR_TPERIOD_Pos)
#define    FL_VREFP_ENABLE_PERIOD_16MS                            (0x2U << VREFP_CFGR_TPERIOD_Pos)
#define    FL_VREFP_ENABLE_PERIOD_32MS                            (0x3U << VREFP_CFGR_TPERIOD_Pos)
#define    FL_VREFP_ENABLE_PERIOD_64MS                            (0x4U << VREFP_CFGR_TPERIOD_Pos)
#define    FL_VREFP_ENABLE_PERIOD_256MS                           (0x5U << VREFP_CFGR_TPERIOD_Pos)
#define    FL_VREFP_ENABLE_PERIOD_1000MS                          (0x6U << VREFP_CFGR_TPERIOD_Pos)
#define    FL_VREFP_ENABLE_PERIOD_4000MS                          (0x7U << VREFP_CFGR_TPERIOD_Pos)


#define    FL_VREFP_DRIVING_TIME_4LSCLK                           (0x0U << VREFP_CFGR_TDRV_Pos)
#define    FL_VREFP_DRIVING_TIME_8LSCLK                           (0x1U << VREFP_CFGR_TDRV_Pos)
#define    FL_VREFP_DRIVING_TIME_16LSCLK                          (0x2U << VREFP_CFGR_TDRV_Pos)
#define    FL_VREFP_DRIVING_TIME_32LSCLK                          (0x3U << VREFP_CFGR_TDRV_Pos)
#define    FL_VREFP_DRIVING_TIME_64LSCLK                          (0x4U << VREFP_CFGR_TDRV_Pos)
#define    FL_VREFP_DRIVING_TIME_128LSCLK                         (0x5U << VREFP_CFGR_TDRV_Pos)
#define    FL_VREFP_DRIVING_TIME_256LSCLK                         (0x6U << VREFP_CFGR_TDRV_Pos)
#define    FL_VREFP_DRIVING_TIME_512LSCLK                         (0x7U << VREFP_CFGR_TDRV_Pos)


#define    FL_VREFP_WORK_MODE_CONTINUOUS                          (0x0U << VREFP_CFGR_LPM_Pos)
#define    FL_VREFP_WORK_MODE_PERIODIC                            (0x1U << VREFP_CFGR_LPM_Pos)


#define    FL_VREFP_OUTPUT_VOLTAGE_2P0V_TRIM                      (*(uint32_t*)0x1FFFFA90)
#define    FL_VREFP_OUTPUT_VOLTAGE_2P5V_TRIM                      (*(uint32_t*)0x1FFFFA8C)
#define    FL_VREFP_OUTPUT_VOLTAGE_3P0V_TRIM                      (*(uint32_t*)0x1FFFFA88)
#define    FL_VREFP_OUTPUT_VOLTAGE_4P5V_TRIM                      (*(uint32_t*)0x1FFFFA84)
#define    FL_VREFP_OUTPUT_VOLTAGE_1P5V_TRIM                      (*(uint32_t*)0x1FFFFA94)
/**
  * @}
  */
/* Exported functions ---------------------------------------------------------------------------------*/
/** @defgroup VREFP_FL_Exported_Functions VREFP Exported Functions
  * @{
  */

/**
  * @brief    Driving end interrupt enable
  * @rmtoll   CR    DENDIE    FL_VREFP_EnableIT_DrivingEnd
  * @param    VREFPx VREFP instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_EnableIT_DrivingEnd(VREFP_Type *VREFPx)
{
    SET_BIT(VREFPx->CR, VREFP_CR_DENDIE_Msk);
}

/**
  * @brief    Get Driving end interrupt enable status
  * @rmtoll   CR    DENDIE    FL_VREFP_IsEnabledIT_DrivingEnd
  * @param    VREFPx VREFP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREFP_IsEnabledIT_DrivingEnd(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->CR, VREFP_CR_DENDIE_Msk) == VREFP_CR_DENDIE_Msk);
}

/**
  * @brief    Driving end interrupt disable
  * @rmtoll   CR    DENDIE    FL_VREFP_DisableIT_DrivingEnd
  * @param    VREFPx VREFP instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_DisableIT_DrivingEnd(VREFP_Type *VREFPx)
{
    CLEAR_BIT(VREFPx->CR, VREFP_CR_DENDIE_Msk);
}

/**
  * @brief    Periodic overflow interrupt enable
  * @rmtoll   CR    POVIE    FL_VREFP_EnableIT_EndOfPeriod
  * @param    VREFPx VREFP instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_EnableIT_EndOfPeriod(VREFP_Type *VREFPx)
{
    SET_BIT(VREFPx->CR, VREFP_CR_POVIE_Msk);
}

/**
  * @brief    Get Periodic overflow interrupt enable status
  * @rmtoll   CR    POVIE    FL_VREFP_IsEnabledIT_EndOfPeriod
  * @param    VREFPx VREFP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREFP_IsEnabledIT_EndOfPeriod(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->CR, VREFP_CR_POVIE_Msk) == VREFP_CR_POVIE_Msk);
}

/**
  * @brief    Periodic overflow interrupt disable
  * @rmtoll   CR    POVIE    FL_VREFP_DisableIT_EndOfPeriod
  * @param    VREFPx VREFP instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_DisableIT_EndOfPeriod(VREFP_Type *VREFPx)
{
    CLEAR_BIT(VREFPx->CR, VREFP_CR_POVIE_Msk);
}

/**
  * @brief    VREFP_VREG enable
  * @rmtoll   CR    EN    FL_VREFP_Enable
  * @param    VREFPx VREFP instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_Enable(VREFP_Type *VREFPx)
{
    SET_BIT(VREFPx->CR, VREFP_CR_EN_Msk);
}

/**
  * @brief    Get VREFP_VREG enable status
  * @rmtoll   CR    EN    FL_VREFP_IsEnabled
  * @param    VREFPx VREFP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREFP_IsEnabled(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->CR, VREFP_CR_EN_Msk) == VREFP_CR_EN_Msk);
}

/**
  * @brief    VREFP_VREG disable
  * @rmtoll   CR    EN    FL_VREFP_Disable
  * @param    VREFPx VREFP instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_Disable(VREFP_Type *VREFPx)
{
    CLEAR_BIT(VREFPx->CR, VREFP_CR_EN_Msk);
}

/**
  * @brief    Set output voltage
  * @rmtoll   CFGR    VRS    FL_VREFP_SetOutputVoltage
  * @param    VREFPx VREFP instance
  * @param    voltage This parameter can be one of the following values:
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_2P0V
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_2P5V
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_3P0V
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_4P5V
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_1P5V
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_SetOutputVoltage(VREFP_Type *VREFPx, uint32_t voltage)
{
    MODIFY_REG(VREFPx->CFGR, VREFP_CFGR_VRS_Msk, voltage);
}

/**
  * @brief    Get output voltage
  * @rmtoll   CFGR    VRS    FL_VREFP_GetOutputVoltage
  * @param    VREFPx VREFP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_2P0V
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_2P5V
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_3P0V
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_4P5V
  *           @arg @ref FL_VREFP_OUTPUT_VOLTAGE_1P5V
  */
__STATIC_INLINE uint32_t FL_VREFP_GetOutputVoltage(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->CFGR, VREFP_CFGR_VRS_Msk));
}

/**
  * @brief    Set period time on low power mode
  * @rmtoll   CFGR    TPERIOD    FL_VREFP_SetEnablePeriod
  * @param    VREFPx VREFP instance
  * @param    period This parameter can be one of the following values:
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_1MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_4MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_16MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_32MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_64MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_256MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_1000MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_4000MS
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_SetEnablePeriod(VREFP_Type *VREFPx, uint32_t period)
{
    MODIFY_REG(VREFPx->CFGR, VREFP_CFGR_TPERIOD_Msk, period);
}

/**
  * @brief    Get period time on low power mode
  * @rmtoll   CFGR    TPERIOD    FL_VREFP_GetEnablePeriod
  * @param    VREFPx VREFP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_1MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_4MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_16MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_32MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_64MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_256MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_1000MS
  *           @arg @ref FL_VREFP_ENABLE_PERIOD_4000MS
  */
__STATIC_INLINE uint32_t FL_VREFP_GetEnablePeriod(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->CFGR, VREFP_CFGR_TPERIOD_Msk));
}

/**
  * @brief    Set driving time on low power mode
  * @rmtoll   CFGR    TDRV    FL_VREFP_SetDrivingTime
  * @param    VREFPx VREFP instance
  * @param    time This parameter can be one of the following values:
  *           @arg @ref FL_VREFP_DRIVING_TIME_4LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_8LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_16LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_32LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_64LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_128LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_256LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_512LSCLK
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_SetDrivingTime(VREFP_Type *VREFPx, uint32_t time)
{
    MODIFY_REG(VREFPx->CFGR, VREFP_CFGR_TDRV_Msk, time);
}

/**
  * @brief    Get driving time on low power mode
  * @rmtoll   CFGR    TDRV    FL_VREFP_GetDrivingTime
  * @param    VREFPx VREFP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_VREFP_DRIVING_TIME_4LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_8LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_16LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_32LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_64LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_128LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_256LSCLK
  *           @arg @ref FL_VREFP_DRIVING_TIME_512LSCLK
  */
__STATIC_INLINE uint32_t FL_VREFP_GetDrivingTime(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->CFGR, VREFP_CFGR_TDRV_Msk));
}

/**
  * @brief    Low power mode enable
  * @rmtoll   CFGR    LPM    FL_VREFP_SetWorkMode
  * @param    VREFPx VREFP instance
  * @param    mode This parameter can be one of the following values:
  *           @arg @ref FL_VREFP_WORK_MODE_CONTINUOUS
  *           @arg @ref FL_VREFP_WORK_MODE_PERIODIC
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_SetWorkMode(VREFP_Type *VREFPx, uint32_t mode)
{
    MODIFY_REG(VREFPx->CFGR, VREFP_CFGR_LPM_Msk, mode);
}

/**
  * @brief    Get low power mode enablestatus
  * @rmtoll   CFGR    LPM    FL_VREFP_GetWorkMode
  * @param    VREFPx VREFP instance
  * @retval   Returned value can be one of the following values:
  *           @arg @ref FL_VREFP_WORK_MODE_CONTINUOUS
  *           @arg @ref FL_VREFP_WORK_MODE_PERIODIC
  */
__STATIC_INLINE uint32_t FL_VREFP_GetWorkMode(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->CFGR, VREFP_CFGR_LPM_Msk));
}

/**
  * @brief    Get Driving busy flag
  * @rmtoll   ISR    BUSY    FL_VREFP_IsActiveFlag_DrivingBusy
  * @param    VREFPx VREFP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREFP_IsActiveFlag_DrivingBusy(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->ISR, VREFP_ISR_BUSY_Msk) == (VREFP_ISR_BUSY_Msk));
}

/**
  * @brief    Get Driving end flag
  * @rmtoll   ISR    DEND    FL_VREFP_IsActiveFlag_DrivingEnd
  * @param    VREFPx VREFP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREFP_IsActiveFlag_DrivingEnd(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->ISR, VREFP_ISR_DEND_Msk) == (VREFP_ISR_DEND_Msk));
}

/**
  * @brief    Clear Driving end flag
  * @rmtoll   ISR    DEND    FL_VREFP_ClearFlag_DrivingEnd
  * @param    VREFPx VREFP instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_ClearFlag_DrivingEnd(VREFP_Type *VREFPx)
{
    WRITE_REG(VREFPx->ISR, VREFP_ISR_DEND_Msk);
}

/**
  * @brief    Get periodic overflow flag
  * @rmtoll   ISR    POV    FL_VREFP_IsActiveFlag_EndOfPeriod
  * @param    VREFPx VREFP instance
  * @retval   State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t FL_VREFP_IsActiveFlag_EndOfPeriod(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->ISR, VREFP_ISR_POV_Msk) == (VREFP_ISR_POV_Msk));
}

/**
  * @brief    Clear periodic overflow flag
  * @rmtoll   ISR    POV    FL_VREFP_ClearFlag_EndOfPeriod
  * @param    VREFPx VREFP instance
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_ClearFlag_EndOfPeriod(VREFP_Type *VREFPx)
{
    WRITE_REG(VREFPx->ISR, VREFP_ISR_POV_Msk);
}

/**
  * @brief    Set VREFP output voltage
  * @rmtoll   TR        FL_VREFP_WriteOutputVoltageTrim
  * @param    VREFPx VREFP instance
  * @param    voltage
  * @retval   None
  */
__STATIC_INLINE void FL_VREFP_WriteOutputVoltageTrim(VREFP_Type *VREFPx, uint32_t voltage)
{
    MODIFY_REG(VREFPx->TR, (0xffU << 0U), (voltage << 0U));
}

/**
  * @brief    Get VREFP output voltage
  * @rmtoll   TR        FL_VREFP_ReadOutputVoltageTrim
  * @param    VREFPx VREFP instance
  * @retval
  */
__STATIC_INLINE uint32_t FL_VREFP_ReadOutputVoltageTrim(VREFP_Type *VREFPx)
{
    return (uint32_t)(READ_BIT(VREFPx->TR, (0xffU << 0U)) >> 0U);
}

/**
  * @}
  */

/** @defgroup VREFP_FL_EF_Init Initialization and de-initialization functions
  * @{
  */
FL_ErrorStatus FL_VREFP_Init(VREFP_Type *VREFPx, FL_VREFP_InitTypeDef *VREFP_InitStruct);
void FL_VREFP_StructInit(FL_VREFP_InitTypeDef *VREFP_InitStruct);
FL_ErrorStatus FL_VREFP_DeInit(VREFP_Type *VREFPx);

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

#endif /* __FM33LG0XX_FL_VREFP_H*/

/*************************Py_Code_Generator Version: 0.1-0.14-0.1 @ 2021-06-25*************************/
/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
