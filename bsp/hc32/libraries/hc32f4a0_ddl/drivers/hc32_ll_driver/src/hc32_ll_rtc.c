/**
 *******************************************************************************
 * @file  hc32_ll_rtc.c
 * @brief This file provides firmware functions to manage the Real-Time
 *        Clock(RTC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2022-03-31       CDT             First version
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by XHSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32_ll_rtc.h"
#include "hc32_ll_utility.h"

/**
 * @addtogroup LL_Driver
 * @{
 */

/**
 * @defgroup LL_RTC RTC
 * @brief Real-Time Clock Driver Library
 * @{
 */

#if (LL_RTC_ENABLE == DDL_ON)

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/**
 * @defgroup RTC_Local_Macros RTC Local Macros
 * @{
 */

/* RTC TPCR register Mask */
#define RTC_TPCR_CLR_MASK                   (RTC_TPCR0_TPCT0   | RTC_TPCR0_TPNF0 | \
                                             RTC_TPCR0_TPRSTE0 | RTC_TPCR0_TSTPE0)
/* Get the specified register address of the RTC Intrusion Control */
#define RTC_TPCRx(__CH__)                   ((uint32_t)(&(CM_RTC->TPCR0)) + (uint32_t)(__CH__))

/* RTC software reset timeout(ms) */
#define RTC_SW_RST_TIMEOUT                  (100UL)
/* RTC mode switch timeout(ms) */
#define RTC_MD_SWITCH_TIMEOUT               (100UL)

/**
 * @defgroup RTC_Check_Parameters_Validity RTC Check Parameters Validity
 * @{
 */
#define IS_RTC_DATA_FMT(x)                                                     \
(   ((x) == RTC_DATA_FMT_DEC)                       ||                         \
    ((x) == RTC_DATA_FMT_BCD))

#define IS_RTC_CLK_SRC(x)                                                      \
(   ((x) == RTC_CLK_SRC_XTAL32)                     ||                         \
    ((x) == RTC_CLK_SRC_LRC))

#define IS_RTC_HOUR_FMT(x)                                                     \
(   ((x) == RTC_HOUR_FMT_12H)                       ||                         \
    ((x) == RTC_HOUR_FMT_24H))

#define IS_RTC_INT_PERIOD(x)                                                   \
(   ((x) == RTC_INT_PERIOD_INVD)                    ||                         \
    ((x) == RTC_INT_PERIOD_PER_HALF_SEC)            ||                         \
    ((x) == RTC_INT_PERIOD_PER_SEC)                 ||                         \
    ((x) == RTC_INT_PERIOD_PER_MINUTE)              ||                         \
    ((x) == RTC_INT_PERIOD_PER_HOUR)                ||                         \
    ((x) == RTC_INT_PERIOD_PER_DAY)                 ||                         \
    ((x) == RTC_INT_PERIOD_PER_MONTH))

#define IS_RTC_CLK_COMPEN(x)                                                   \
(   ((x) == RTC_CLK_COMPEN_DISABLE)                 ||                         \
    ((x) == RTC_CLK_COMPEN_ENABLE))

#define IS_RTC_CLK_COMPEN_MD(x)                                                \
(   ((x) == RTC_CLK_COMPEN_MD_DISTRIBUTED)          ||                         \
    ((x) == RTC_CLK_COMPEN_MD_UNIFORM))

#define IS_RTC_HOUR_12H_AM_PM(x)                                               \
(   ((x) == RTC_HOUR_12H_AM)                        ||                         \
    ((x) == RTC_HOUR_12H_PM))

#define IS_RTC_INTRU_CH(x)                                                     \
(   ((x) == RTC_INTRU_CH0)                          ||                         \
    ((x) == RTC_INTRU_CH1))

#define IS_RTC_INTRU_TIMESTAMP(x)                                              \
(   ((x) == RTC_INTRU_TS_DISABLE)                   ||                         \
    ((x) == RTC_INTRU_TS_ENABLE))

#define IS_RTC_INTRU_RST_BACKUP_REG(x)                                         \
(   ((x) == RTC_INTRU_RST_BACKUP_REG_DISABLE)       ||                         \
    ((x) == RTC_INTRU_RST_BACKUP_REG_ENABLE))

#define IS_RTC_INTRU_FILTER(x)                                                 \
(   ((x) == RTC_INTRU_FILTER_INVD)                  ||                         \
    ((x) == RTC_INTRU_FILTER_THREE_TIME)            ||                         \
    ((x) == RTC_INTRU_FILTER_THREE_TIME_CLK_DIV32))

#define IS_RTC_INTRU_TRIG_EDGE(x)                                              \
(   ((x) == RTC_INTRU_TRIG_EDGE_NONE)               ||                         \
    ((x) == RTC_INTRU_TRIG_EDGE_RISING)             ||                         \
    ((x) == RTC_INTRU_TRIG_EDGE_FALLING)            ||                         \
    ((x) == RTC_INTRU_TRIG_EDGE_RISING_FALLING))

#define IS_RTC_GET_FLAG(x)                                                     \
(   ((x) != 0U)                                     &&                         \
    (((x) | RTC_FLAG_ALL) == RTC_FLAG_ALL))

#define IS_RTC_CLR_FLAG(x)                                                     \
(   ((x) != 0U)                                     &&                         \
    (((x) | RTC_FLAG_CLR_ALL) == RTC_FLAG_CLR_ALL))

#define IS_RTC_INT(x)                                                          \
(   ((x) != 0U)                                     &&                         \
    (((x) | RTC_INT_ALL) == RTC_INT_ALL))

#define IS_RTC_YEAR(x)                              ((x) <= 99U)

#define IS_RTC_MONTH(x)                             (((x) >= 1U) && ((x) <= 12U))

#define IS_RTC_DAY(x)                               (((x) >= 1U) && ((x) <= 31U))

#define IS_RTC_HOUR_12H(x)                          (((x) >= 1U) && ((x) <= 12U))

#define IS_RTC_HOUR_24H(x)                          ((x) <= 23U)

#define IS_RTC_MINUTE(x)                            ((x) <= 59U)

#define IS_RTC_SEC(x)                               ((x) <= 59U)

#define IS_RTC_WEEKDAY(x)                           ((x) <= 6U)

#define IS_RTC_ALARM_WEEKDAY(x)                     (((x) >= 0x01U) && ((x) <= 0x7FU))

#define IS_RTC_COMPEN_VALUE(x)                      ((x) <= 0x1FFU)
/**
 * @}
 */

/**
 * @}
 */

/*******************************************************************************
 * Global variable definitions (declared in header file with 'extern')
 ******************************************************************************/

/*******************************************************************************
 * Local function prototypes ('static')
 ******************************************************************************/

/*******************************************************************************
 * Local variable definitions ('static')
 ******************************************************************************/

/*******************************************************************************
 * Function implementation - global ('extern') and local ('static')
 ******************************************************************************/
/**
 * @defgroup RTC_Global_Functions RTC Global Functions
 * @{
 */

/**
 * @brief  De-Initialize RTC.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: De-Initialize success
 *           - LL_ERR_TIMEOUT: De-Initialize timeout
 */
int32_t RTC_DeInit(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    WRITE_REG32(bCM_RTC->CR0_b.RESET, RESET);
    /* Waiting for normal count status or end of RTC software reset */
    u32Count = RTC_SW_RST_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bCM_RTC->CR0_b.RESET)) {
        if (0UL == u32Count) {
            i32Ret = LL_ERR_TIMEOUT;
            break;
        }
        u32Count--;
    }

    if (LL_OK == i32Ret) {
        /* Reset all RTC registers */
        WRITE_REG32(bCM_RTC->CR0_b.RESET, SET);
        /* Waiting for RTC software reset to complete */
        u32Count = RTC_SW_RST_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32(bCM_RTC->CR0_b.RESET)) {
            if (0UL == u32Count) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
            u32Count--;
        }
    }

    return i32Ret;
}

/**
 * @brief  Initialize RTC.
 * @param  [in] pstcRtcInit             Pointer to a @ref stc_rtc_init_t structure
 * @retval int32_t:
 *           - LL_OK: Initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_Init(const stc_rtc_init_t *pstcRtcInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRtcInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_CLK_SRC(pstcRtcInit->u8ClockSrc));
        DDL_ASSERT(IS_RTC_HOUR_FMT(pstcRtcInit->u8HourFormat));
        DDL_ASSERT(IS_RTC_INT_PERIOD(pstcRtcInit->u8IntPeriod));
        DDL_ASSERT(IS_RTC_CLK_COMPEN(pstcRtcInit->u8ClockCompen));
        DDL_ASSERT(IS_RTC_COMPEN_VALUE(pstcRtcInit->u16CompenValue));
        DDL_ASSERT(IS_RTC_CLK_COMPEN_MD(pstcRtcInit->u8CompenMode));

        /* RTC CR3 Configuration */
        MODIFY_REG8(CM_RTC->CR3, (RTC_CR3_LRCEN | RTC_CR3_RCKSEL), pstcRtcInit->u8ClockSrc);
        /* RTC CR1 Configuration */
        MODIFY_REG8(CM_RTC->CR1, (RTC_CR1_PRDS | RTC_CR1_AMPM | RTC_CR1_ONEHZSEL),
                    (pstcRtcInit->u8IntPeriod | pstcRtcInit->u8HourFormat | pstcRtcInit->u8CompenMode));
        /* RTC Compensation Configuration */
        MODIFY_REG8(CM_RTC->ERRCRH, (RTC_ERRCRH_COMPEN | RTC_ERRCRH_COMP8),
                    (pstcRtcInit->u8ClockCompen | (uint8_t)((pstcRtcInit->u16CompenValue >> 8U) & 0x01U)));
        WRITE_REG8(CM_RTC->ERRCRL, (uint8_t)(pstcRtcInit->u16CompenValue & 0xFFU));
    }

    return i32Ret;
}

/**
 * @brief  Fills each stc_rtc_init_t member with default value.
 * @param  [out] pstcRtcInit            Pointer to a @ref stc_rtc_init_t structure
 * @retval int32_t:
 *           - LL_OK: stc_rtc_init_t member initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_StructInit(stc_rtc_init_t *pstcRtcInit)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRtcInit) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcRtcInit->u8ClockSrc     = RTC_CLK_SRC_LRC;
        pstcRtcInit->u8HourFormat   = RTC_HOUR_FMT_24H;
        pstcRtcInit->u8IntPeriod    = RTC_INT_PERIOD_INVD;
        pstcRtcInit->u8ClockCompen  = RTC_CLK_COMPEN_DISABLE;
        pstcRtcInit->u8CompenMode   = RTC_CLK_COMPEN_MD_DISTRIBUTED;
        pstcRtcInit->u16CompenValue = 0U;
    }

    return i32Ret;
}

/**
 * @brief  Enter RTC read/write mode.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Enter mode success
 *           - LL_ERR_TIMEOUT: Enter mode timeout
 */
int32_t RTC_EnterRwMode(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    /* Mode switch when RTC is running */
    if (0UL != READ_REG32(bCM_RTC->CR1_b.START)) {
        if (1UL != READ_REG32(bCM_RTC->CR2_b.RWEN)) {
            WRITE_REG32(bCM_RTC->CR2_b.RWREQ, SET);
            /* Waiting for RWEN bit set */
            u32Count = RTC_MD_SWITCH_TIMEOUT * (HCLK_VALUE / 20000UL);
            while (1UL != READ_REG32(bCM_RTC->CR2_b.RWEN)) {
                if (0UL == u32Count) {
                    i32Ret = LL_ERR_TIMEOUT;
                    break;
                }
                u32Count--;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Exit RTC read/write mode.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Exit mode success
 *           - LL_ERR_TIMEOUT: Exit mode timeout
 */
int32_t RTC_ExitRwMode(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    /* Mode switch when RTC is running */
    if (0UL != READ_REG32(bCM_RTC->CR1_b.START)) {
        if (0UL != READ_REG32(bCM_RTC->CR2_b.RWEN)) {
            WRITE_REG32(bCM_RTC->CR2_b.RWREQ, RESET);
            /* Waiting for RWEN bit reset */
            u32Count = RTC_MD_SWITCH_TIMEOUT * (HCLK_VALUE / 20000UL);
            while (0UL != READ_REG32(bCM_RTC->CR2_b.RWEN)) {
                if (0UL == u32Count) {
                    i32Ret = LL_ERR_TIMEOUT;
                    break;
                }
                u32Count--;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Confirm the condition for RTC to enter low power mode.
 * @param  None
 * @retval int32_t:
 *           - LL_OK: Can enter low power mode
 *           - LL_ERR_TIMEOUT: Can't enter low power mode
 */
int32_t RTC_ConfirmLPMCond(void)
{
    __IO uint32_t u32Count;
    int32_t i32Ret = LL_OK;

    /* Check RTC work status */
    if (0UL != READ_REG32(bCM_RTC->CR1_b.START)) {
        WRITE_REG32(bCM_RTC->CR2_b.RWREQ, SET);
        /* Waiting for RTC RWEN bit set */
        u32Count = RTC_MD_SWITCH_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (1UL != READ_REG32(bCM_RTC->CR2_b.RWEN)) {
            if (0UL == u32Count) {
                i32Ret = LL_ERR_TIMEOUT;
                break;
            }
            u32Count--;
        }

        if (LL_OK == i32Ret) {
            WRITE_REG32(bCM_RTC->CR2_b.RWREQ, RESET);
            /* Waiting for RTC RWEN bit reset */
            u32Count = RTC_MD_SWITCH_TIMEOUT * (HCLK_VALUE / 20000UL);
            while (0UL != READ_REG32(bCM_RTC->CR2_b.RWEN)) {
                if (0UL == u32Count) {
                    i32Ret = LL_ERR_TIMEOUT;
                    break;
                }
                u32Count--;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Set the RTC interrupt period.
 * @param  [in] u8Period                Specifies the interrupt period.
 *         This parameter can be one of the following values:
 *           @arg RTC_INT_PERIOD_INVD:          Period interrupt invalid
 *           @arg RTC_INT_PERIOD_PER_HALF_SEC:  Interrupt per half second
 *           @arg RTC_INT_PERIOD_PER_SEC:       Interrupt per second
 *           @arg RTC_INT_PERIOD_PER_MINUTE:    Interrupt per minute
 *           @arg RTC_INT_PERIOD_PER_HOUR:      Interrupt per hour
 *           @arg RTC_INT_PERIOD_PER_DAY:       Interrupt per day
 *           @arg RTC_INT_PERIOD_PER_MONTH:     Interrupt per month
 * @retval None
 */
void RTC_SetIntPeriod(uint8_t u8Period)
{
    uint32_t u32RtcSta;
    uint32_t u32IntSta;

    /* Check parameters */
    DDL_ASSERT(IS_RTC_INT_PERIOD(u8Period));

    u32RtcSta = READ_REG32(bCM_RTC->CR1_b.START);
    u32IntSta = READ_REG32(bCM_RTC->CR2_b.PRDIE);
    /* Disable period interrupt when START=1 and clear period flag after write */
    if ((0UL != u32IntSta) && (0UL != u32RtcSta)) {
        WRITE_REG32(bCM_RTC->CR2_b.PRDIE, RESET);
    }

    /* RTC CR1 Configuration */
    MODIFY_REG8(CM_RTC->CR1, RTC_CR1_PRDS, u8Period);
    WRITE_REG32(bCM_RTC->CR2_b.PRDF, RESET);

    if ((0UL != u32IntSta) && (0UL != u32RtcSta)) {
        WRITE_REG32(bCM_RTC->CR2_b.PRDIE, SET);
    }
}

/**
 * @brief  Set the RTC clock source.
 * @param  [in] u8Src                   Specifies the clock source.
 *         This parameter can be one of the following values:
 *           @arg RTC_CLK_SRC_XTAL32:   XTAL32 Cloc
 *           @arg RTC_CLK_SRC_LRC:      LRC/RTCLRC Clock
 * @retval None
 */
void RTC_SetClockSrc(uint8_t u8Src)
{
    /* Check parameters */
    DDL_ASSERT(IS_RTC_CLK_SRC(u8Src));

    MODIFY_REG8(CM_RTC->CR3, (RTC_CR3_LRCEN | RTC_CR3_RCKSEL), u8Src);
}

/**
 * @brief  Set RTC clock compensation value.
 * @param  [in] u16Value                Specifies the clock compensation value of RTC.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 0x1FF.
 * @retval None
 */
void RTC_SetClockCompenValue(uint16_t u16Value)
{
    /* Check parameters */
    DDL_ASSERT(IS_RTC_COMPEN_VALUE(u16Value));

    WRITE_REG32(bCM_RTC->ERRCRH_b.COMP8, ((uint32_t)u16Value >> 8U) & 0x01U);
    WRITE_REG8(CM_RTC->ERRCRL, (uint8_t)(u16Value & 0x00FFU));
}

/**
 * @brief  Get RTC counter status.
 * @param  None
 * @retval An @ref en_functional_state_t enumeration value.
 *           - ENABLE: RTC counter started
 *           - DISABLE: RTC counter stopped
 */
en_functional_state_t RTC_GetCounterState(void)
{
    en_functional_state_t enState = DISABLE;

    if (0UL != READ_REG32(bCM_RTC->CR1_b.START)) {
        enState = ENABLE;
    }

    return enState;
}

/**
 * @brief  Enable or disable RTC count.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void RTC_Cmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_RTC->CR1_b.START, enNewState);
}

/**
 * @brief  Enable or disable RTC LRC function.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void RTC_LrcCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_RTC->CR3_b.LRCEN, enNewState);
}

/**
 * @brief  Enable or disable RTC 1HZ output.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void RTC_OneHzOutputCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_RTC->CR1_b.ONEHZOE, enNewState);
}

/**
 * @brief  Enable or disable clock compensation.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void RTC_ClockCompenCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_RTC->ERRCRH_b.COMPEN, enNewState);
}

/**
 * @brief  Set RTC current date.
 * @param  [in] u8Format                Specifies the format of the entered parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FMT_DEC:     Decimal data format
 *           @arg RTC_DATA_FMT_BCD:     BCD data format
 * @param  [in] pstcRtcDate             Pointer to a @ref stc_rtc_date_t structure
 * @retval int32_t:
 *           - LL_OK: Set date success
 *           - LL_ERR: Set date failed
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_SetDate(uint8_t u8Format, stc_rtc_date_t *pstcRtcDate)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRtcDate) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FMT(u8Format));
        if (RTC_DATA_FMT_DEC != u8Format) {
            DDL_ASSERT(IS_RTC_YEAR(RTC_BCD2DEC(pstcRtcDate->u8Year)));
            DDL_ASSERT(IS_RTC_MONTH(RTC_BCD2DEC(pstcRtcDate->u8Month)));
            DDL_ASSERT(IS_RTC_DAY(RTC_BCD2DEC(pstcRtcDate->u8Day)));
        } else {
            DDL_ASSERT(IS_RTC_YEAR(pstcRtcDate->u8Year));
            DDL_ASSERT(IS_RTC_MONTH(pstcRtcDate->u8Month));
            DDL_ASSERT(IS_RTC_DAY(pstcRtcDate->u8Day));
        }
        DDL_ASSERT(IS_RTC_WEEKDAY(pstcRtcDate->u8Weekday));

        /* Enter read/write mode */
        if (LL_OK != RTC_EnterRwMode()) {
            i32Ret = LL_ERR;
        } else {
            if (RTC_DATA_FMT_DEC == u8Format) {
                pstcRtcDate->u8Year  = RTC_DEC2BCD(pstcRtcDate->u8Year);
                pstcRtcDate->u8Month = RTC_DEC2BCD(pstcRtcDate->u8Month);
                pstcRtcDate->u8Day   = RTC_DEC2BCD(pstcRtcDate->u8Day);
            }

            WRITE_REG8(CM_RTC->YEAR, pstcRtcDate->u8Year);
            WRITE_REG8(CM_RTC->MON,  pstcRtcDate->u8Month);
            WRITE_REG8(CM_RTC->DAY,  pstcRtcDate->u8Day);
            WRITE_REG8(CM_RTC->WEEK, pstcRtcDate->u8Weekday);

            /* Exit read/write mode */
            if (LL_OK != RTC_ExitRwMode()) {
                i32Ret = LL_ERR;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Get RTC current date.
 * @param  [in] u8Format                Specifies the format of the returned parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FMT_DEC:     Decimal data format
 *           @arg RTC_DATA_FMT_BCD:     BCD data format
 * @param  [out] pstcRtcDate            Pointer to a @ref stc_rtc_date_t structure
 * @retval int32_t:
 *           - LL_OK: Get date success
 *           - LL_ERR: Get date failed
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_GetDate(uint8_t u8Format, stc_rtc_date_t *pstcRtcDate)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRtcDate) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FMT(u8Format));
        /* Enter read/write mode */
        if (LL_OK != RTC_EnterRwMode()) {
            i32Ret = LL_ERR;
        } else {
            /* Get RTC date registers */
            pstcRtcDate->u8Year    = READ_REG8(CM_RTC->YEAR);
            pstcRtcDate->u8Month   = READ_REG8(CM_RTC->MON);
            pstcRtcDate->u8Day     = READ_REG8(CM_RTC->DAY);
            pstcRtcDate->u8Weekday = READ_REG8(CM_RTC->WEEK);

            /* Check decimal format*/
            if (RTC_DATA_FMT_DEC == u8Format) {
                pstcRtcDate->u8Year  = RTC_BCD2DEC(pstcRtcDate->u8Year);
                pstcRtcDate->u8Month = RTC_BCD2DEC(pstcRtcDate->u8Month);
                pstcRtcDate->u8Day   = RTC_BCD2DEC(pstcRtcDate->u8Day);
            }

            /* exit read/write mode */
            if (LL_OK != RTC_ExitRwMode()) {
                i32Ret = LL_ERR;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Set RTC current time.
 * @param  [in] u8Format                Specifies the format of the entered parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FMT_DEC:     Decimal data format
 *           @arg RTC_DATA_FMT_BCD:     BCD data format
 * @param  [in] pstcRtcTime             Pointer to a @ref stc_rtc_time_t structure
 * @retval int32_t:
 *           - LL_OK: Set time success
 *           - LL_ERR: Set time failed
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_SetTime(uint8_t u8Format, stc_rtc_time_t *pstcRtcTime)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRtcTime) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FMT(u8Format));
        if (RTC_DATA_FMT_DEC != u8Format) {
            if (RTC_HOUR_FMT_12H == READ_REG32(bCM_RTC->CR1_b.AMPM)) {
                DDL_ASSERT(IS_RTC_HOUR_12H(RTC_BCD2DEC(pstcRtcTime->u8Hour)));
                DDL_ASSERT(IS_RTC_HOUR_12H_AM_PM(pstcRtcTime->u8AmPm));
            } else {
                DDL_ASSERT(IS_RTC_HOUR_24H(RTC_BCD2DEC(pstcRtcTime->u8Hour)));
            }
            DDL_ASSERT(IS_RTC_MINUTE(RTC_BCD2DEC(pstcRtcTime->u8Minute)));
            DDL_ASSERT(IS_RTC_SEC(RTC_BCD2DEC(pstcRtcTime->u8Second)));
        } else {
            if (RTC_HOUR_FMT_12H == READ_REG32(bCM_RTC->CR1_b.AMPM)) {
                DDL_ASSERT(IS_RTC_HOUR_12H(pstcRtcTime->u8Hour));
                DDL_ASSERT(IS_RTC_HOUR_12H_AM_PM(pstcRtcTime->u8AmPm));
            } else {
                DDL_ASSERT(IS_RTC_HOUR_24H(pstcRtcTime->u8Hour));
            }
            DDL_ASSERT(IS_RTC_MINUTE(pstcRtcTime->u8Minute));
            DDL_ASSERT(IS_RTC_SEC(pstcRtcTime->u8Second));
        }

        /* Enter read/write mode */
        if (LL_OK != RTC_EnterRwMode()) {
            i32Ret = LL_ERR;
        } else {
            if (RTC_DATA_FMT_DEC == u8Format) {
                pstcRtcTime->u8Hour   = RTC_DEC2BCD(pstcRtcTime->u8Hour);
                pstcRtcTime->u8Minute = RTC_DEC2BCD(pstcRtcTime->u8Minute);
                pstcRtcTime->u8Second = RTC_DEC2BCD(pstcRtcTime->u8Second);
            }
            if ((RTC_HOUR_FMT_12H == READ_REG32(bCM_RTC->CR1_b.AMPM)) &&
                    (RTC_HOUR_12H_PM == pstcRtcTime->u8AmPm)) {
                SET_REG8_BIT(pstcRtcTime->u8Hour, RTC_HOUR_12H_PM);
            }

            WRITE_REG8(CM_RTC->HOUR, pstcRtcTime->u8Hour);
            WRITE_REG8(CM_RTC->MIN,  pstcRtcTime->u8Minute);
            WRITE_REG8(CM_RTC->SEC,  pstcRtcTime->u8Second);

            /* Exit read/write mode */
            if (LL_OK != RTC_ExitRwMode()) {
                i32Ret = LL_ERR;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Get RTC current time.
 * @param  [in] u8Format                Specifies the format of the returned parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FMT_DEC:     Decimal data format
 *           @arg RTC_DATA_FMT_BCD:     BCD data format
 * @param  [out] pstcRtcTime            Pointer to a @ref stc_rtc_time_t structure
 * @retval int32_t:
 *           - LL_OK: Get time success
 *           - LL_ERR: Get time failed
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_GetTime(uint8_t u8Format, stc_rtc_time_t *pstcRtcTime)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRtcTime) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FMT(u8Format));
        /* Enter read/write mode */
        if (LL_OK != RTC_EnterRwMode()) {
            i32Ret = LL_ERR;
        } else {
            /* Get RTC time registers */
            pstcRtcTime->u8Hour   = READ_REG8(CM_RTC->HOUR);
            pstcRtcTime->u8Minute = READ_REG8(CM_RTC->MIN);
            pstcRtcTime->u8Second = READ_REG8(CM_RTC->SEC);

            if (RTC_HOUR_FMT_12H == READ_REG32(bCM_RTC->CR1_b.AMPM)) {
                if (RTC_HOUR_12H_PM == (pstcRtcTime->u8Hour & RTC_HOUR_12H_PM)) {
                    CLR_REG8_BIT(pstcRtcTime->u8Hour, RTC_HOUR_12H_PM);
                    pstcRtcTime->u8AmPm  = RTC_HOUR_12H_PM;
                } else {
                    pstcRtcTime->u8AmPm = RTC_HOUR_12H_AM;
                }
            } else {
                pstcRtcTime->u8AmPm = RTC_HOUR_24H;
            }

            /* Check decimal format*/
            if (RTC_DATA_FMT_DEC == u8Format) {
                pstcRtcTime->u8Hour   = RTC_BCD2DEC(pstcRtcTime->u8Hour);
                pstcRtcTime->u8Minute = RTC_BCD2DEC(pstcRtcTime->u8Minute);
                pstcRtcTime->u8Second = RTC_BCD2DEC(pstcRtcTime->u8Second);
            }

            /* exit read/write mode */
            if (LL_OK != RTC_ExitRwMode()) {
                i32Ret = LL_ERR;
            }
        }
    }

    return i32Ret;
}

/**
 * @brief  Set RTC alarm time.
 * @param  [in] u8Format                Specifies the format of the entered parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FMT_DEC:     Decimal data format
 *           @arg RTC_DATA_FMT_BCD:     BCD data format
 * @param  [in] pstcRtcAlarm            Pointer to a @ref stc_rtc_alarm_t structure
 * @retval int32_t:
 *           - LL_OK: Set RTC alarm time success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_SetAlarm(uint8_t u8Format, stc_rtc_alarm_t *pstcRtcAlarm)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRtcAlarm) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FMT(u8Format));
        if (RTC_DATA_FMT_DEC != u8Format) {
            if (RTC_HOUR_FMT_12H == READ_REG32(bCM_RTC->CR1_b.AMPM)) {
                DDL_ASSERT(IS_RTC_HOUR_12H(RTC_BCD2DEC(pstcRtcAlarm->u8AlarmHour)));
                DDL_ASSERT(IS_RTC_HOUR_12H_AM_PM(pstcRtcAlarm->u8AlarmAmPm));
            } else {
                DDL_ASSERT(IS_RTC_HOUR_24H(RTC_BCD2DEC(pstcRtcAlarm->u8AlarmHour)));
            }
            DDL_ASSERT(IS_RTC_MINUTE(RTC_BCD2DEC(pstcRtcAlarm->u8AlarmMinute)));
        } else {
            if (RTC_HOUR_FMT_12H == READ_REG32(bCM_RTC->CR1_b.AMPM)) {
                DDL_ASSERT(IS_RTC_HOUR_12H(pstcRtcAlarm->u8AlarmHour));
                DDL_ASSERT(IS_RTC_HOUR_12H_AM_PM(pstcRtcAlarm->u8AlarmAmPm));
            } else {
                DDL_ASSERT(IS_RTC_HOUR_24H(pstcRtcAlarm->u8AlarmHour));
            }
            DDL_ASSERT(IS_RTC_MINUTE(pstcRtcAlarm->u8AlarmMinute));
        }
        DDL_ASSERT(IS_RTC_ALARM_WEEKDAY(pstcRtcAlarm->u8AlarmWeekday));

        /* Configure alarm registers */
        if (RTC_DATA_FMT_DEC == u8Format) {
            pstcRtcAlarm->u8AlarmHour   = RTC_DEC2BCD(pstcRtcAlarm->u8AlarmHour);
            pstcRtcAlarm->u8AlarmMinute = RTC_DEC2BCD(pstcRtcAlarm->u8AlarmMinute);
        }
        if ((RTC_HOUR_FMT_12H == READ_REG32(bCM_RTC->CR1_b.AMPM)) &&
                (RTC_HOUR_12H_PM == pstcRtcAlarm->u8AlarmAmPm)) {
            SET_REG8_BIT(pstcRtcAlarm->u8AlarmHour, RTC_HOUR_12H_PM);
        }

        WRITE_REG8(CM_RTC->ALMHOUR, pstcRtcAlarm->u8AlarmHour);
        WRITE_REG8(CM_RTC->ALMMIN,  pstcRtcAlarm->u8AlarmMinute);
        WRITE_REG8(CM_RTC->ALMWEEK, pstcRtcAlarm->u8AlarmWeekday);
    }

    return i32Ret;
}

/**
 * @brief  Get RTC alarm time.
 * @param  [in] u8Format                Specifies the format of the returned parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FMT_DEC:     Decimal data format
 *           @arg RTC_DATA_FMT_BCD:     BCD data format
 * @param  [out] pstcRtcAlarm           Pointer to a @ref stc_rtc_alarm_t structure
 * @retval int32_t:
 *           - LL_OK: Get RTC alarm time success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_GetAlarm(uint8_t u8Format, stc_rtc_alarm_t *pstcRtcAlarm)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcRtcAlarm) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FMT(u8Format));

        /* Get RTC date and time register */
        pstcRtcAlarm->u8AlarmWeekday = READ_REG8(CM_RTC->ALMWEEK);
        pstcRtcAlarm->u8AlarmMinute  = READ_REG8(CM_RTC->ALMMIN);
        pstcRtcAlarm->u8AlarmHour    = READ_REG8(CM_RTC->ALMHOUR);

        if (RTC_HOUR_FMT_12H == READ_REG32(bCM_RTC->CR1_b.AMPM)) {
            if (RTC_HOUR_12H_PM == (pstcRtcAlarm->u8AlarmHour & RTC_HOUR_12H_PM)) {
                CLR_REG8_BIT(pstcRtcAlarm->u8AlarmHour, RTC_HOUR_12H_PM);
                pstcRtcAlarm->u8AlarmAmPm = RTC_HOUR_12H_PM;
            } else {
                pstcRtcAlarm->u8AlarmAmPm = RTC_HOUR_12H_AM;
            }
        } else {
            pstcRtcAlarm->u8AlarmAmPm = RTC_HOUR_24H;
        }

        /* Check decimal format*/
        if (RTC_DATA_FMT_DEC == u8Format) {
            pstcRtcAlarm->u8AlarmHour   = RTC_BCD2DEC(pstcRtcAlarm->u8AlarmHour);
            pstcRtcAlarm->u8AlarmMinute = RTC_BCD2DEC(pstcRtcAlarm->u8AlarmMinute);
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable RTC alarm.
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void RTC_AlarmCmd(en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    WRITE_REG32(bCM_RTC->CR2_b.ALME, enNewState);
}

/**
 * @brief  De-Initialize RTC intrusion function..
 * @param  [in] u8Ch                    Specifies the RTC intrusion channel.
 *         This parameter can be one of the following values:
 *           @arg RTC_INTRU_CH0:    Intrusion channel 0
 *           @arg RTC_INTRU_CH1:    Intrusion channel 1
 * @retval None
 */
void RTC_INTRU_DeInit(uint8_t u8Ch)
{
    __IO uint8_t *TPCR;

    /* Check parameters */
    DDL_ASSERT(IS_RTC_INTRU_CH(u8Ch));

    TPCR = (__IO uint8_t *)RTC_TPCRx(u8Ch);
    WRITE_REG8(*TPCR, 0U);
    WRITE_REG8(CM_RTC->TPSR, 0U);
}

/**
 * @brief  Initialize RTC intrusion function.
 * @param  [in] u8Ch                    Specifies the RTC intrusion channel.
 *         This parameter can be one of the following values:
 *           @arg RTC_INTRU_CH0:    Intrusion channel 0
 *           @arg RTC_INTRU_CH1:    Intrusion channel 1
 * @param  [in] pstcIntru               Pointer to a @ref stc_rtc_intrusion_t structure
 * @retval int32_t:
 *           - LL_OK: Configure RTC intrusion function success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_INTRU_Init(uint8_t u8Ch, const stc_rtc_intrusion_t *pstcIntru)
{
    int32_t i32Ret = LL_OK;
    __IO uint8_t *TPCR;

    if (NULL == pstcIntru) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_INTRU_CH(u8Ch));
        DDL_ASSERT(IS_RTC_INTRU_TIMESTAMP(pstcIntru->u8Timestamp));
        DDL_ASSERT(IS_RTC_INTRU_RST_BACKUP_REG(pstcIntru->u8ResetBackupReg));
        DDL_ASSERT(IS_RTC_INTRU_FILTER(pstcIntru->u8Filter));
        DDL_ASSERT(IS_RTC_INTRU_TRIG_EDGE(pstcIntru->u8TriggerEdge));

        TPCR = (__IO uint8_t *)RTC_TPCRx(u8Ch);
        /* RTC Intrusion control Configuration */
        MODIFY_REG8(*TPCR, RTC_TPCR_CLR_MASK,
                    (pstcIntru->u8Timestamp | pstcIntru->u8ResetBackupReg |
                     pstcIntru->u8Filter    | pstcIntru->u8TriggerEdge));
    }

    return i32Ret;
}

/**
 * @brief  Fills each stc_rtc_intrusion_t member with default value.
 * @param  [out] pstcIntru              Pointer to a @ref stc_rtc_intrusion_t structure
 * @retval int32_t:
 *           - LL_OK: stc_rtc_intrusion_t member initialize success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_INTRU_StructInit(stc_rtc_intrusion_t *pstcIntru)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcIntru) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        pstcIntru->u8Timestamp       = RTC_INTRU_TS_DISABLE;
        pstcIntru->u8ResetBackupReg  = RTC_INTRU_RST_BACKUP_REG_DISABLE;
        pstcIntru->u8Filter          = RTC_INTRU_FILTER_INVD;
        pstcIntru->u8TriggerEdge     = RTC_INTRU_TRIG_EDGE_NONE;
    }

    return i32Ret;
}

/**
 * @brief  Get RTC intrusion timestamp.
 * @param  [in] u8Format                Specifies the format of the returned parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FMT_DEC:     Decimal data format
 *           @arg RTC_DATA_FMT_BCD:     BCD data format
 * @param  [out] pstcTimestamp          Pointer to a @ref stc_rtc_timestamp_t structure
 * @retval int32_t:
 *           - LL_OK: Get RTC intrusion timestamp success
 *           - LL_ERR_INVD_PARAM: Invalid parameter
 */
int32_t RTC_INTRU_GetTimestamp(uint8_t u8Format, stc_rtc_timestamp_t *pstcTimestamp)
{
    int32_t i32Ret = LL_OK;

    if (NULL == pstcTimestamp) {
        i32Ret = LL_ERR_INVD_PARAM;
    } else {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FMT(u8Format));

        /* Get RTC Timestamp registers */
        pstcTimestamp->stcTime.u8Hour   = READ_REG8(CM_RTC->HOURTP);
        pstcTimestamp->stcTime.u8Minute = READ_REG8(CM_RTC->MINTP);
        pstcTimestamp->stcTime.u8Second = READ_REG8(CM_RTC->SECTP);
        pstcTimestamp->u8Month          = READ_REG8(CM_RTC->MONTP);
        pstcTimestamp->u8Day            = READ_REG8(CM_RTC->DAYTP);

        if (RTC_HOUR_FMT_12H == READ_REG32(bCM_RTC->CR1_b.AMPM)) {
            if (RTC_HOUR_12H_PM == (pstcTimestamp->stcTime.u8Hour & RTC_HOUR_12H_PM)) {
                CLR_REG8_BIT(pstcTimestamp->stcTime.u8Hour, RTC_HOUR_12H_PM);
                pstcTimestamp->stcTime.u8AmPm  = RTC_HOUR_12H_PM;
            } else {
                pstcTimestamp->stcTime.u8AmPm = RTC_HOUR_12H_AM;
            }
        } else {
            pstcTimestamp->stcTime.u8AmPm = RTC_HOUR_24H;
        }

        /* Check decimal format*/
        if (RTC_DATA_FMT_DEC == u8Format) {
            pstcTimestamp->stcTime.u8Hour   = RTC_BCD2DEC(pstcTimestamp->stcTime.u8Hour);
            pstcTimestamp->stcTime.u8Minute = RTC_BCD2DEC(pstcTimestamp->stcTime.u8Minute);
            pstcTimestamp->stcTime.u8Second = RTC_BCD2DEC(pstcTimestamp->stcTime.u8Second);
            pstcTimestamp->u8Month          = RTC_BCD2DEC(pstcTimestamp->u8Month);
            pstcTimestamp->u8Day            = RTC_BCD2DEC(pstcTimestamp->u8Day);
        }
    }

    return i32Ret;
}

/**
 * @brief  Enable or disable RTC intrusion.
 * @param  [in] u8Ch                    Specifies the RTC intrusion channel.
 *         This parameter can be one of the following values:
 *           @arg RTC_INTRU_CH0:        Intrusion channel 0
 *           @arg RTC_INTRU_CH1:        Intrusion channel 1
 * @param  [in] enNewState              An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void RTC_INTRU_Cmd(uint8_t u8Ch, en_functional_state_t enNewState)
{
    /* Check parameters */
    DDL_ASSERT(IS_RTC_INTRU_CH(u8Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    if (RTC_INTRU_CH0 != u8Ch) {
        WRITE_REG32(bCM_RTC->TPCR1_b.TPEN1, enNewState);
    } else {
        WRITE_REG32(bCM_RTC->TPCR0_b.TPEN0, enNewState);
    }
}

/**
 * @brief  Enable or disable specified RTC interrupt.
 * @param  [in] u32IntType              Specifies the RTC interrupt source.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref RTC_Interrupt
 * @param  [in] enNewState                An @ref en_functional_state_t enumeration value.
 * @retval None
 */
void RTC_IntCmd(uint32_t u32IntType, en_functional_state_t enNewState)
{
    uint32_t u32IntTemp;

    /* Check parameters */
    DDL_ASSERT(IS_RTC_INT(u32IntType));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewState));

    u32IntTemp = u32IntType & 0x0000FFUL;
    if (0UL != u32IntTemp) {
        if (DISABLE != enNewState) {
            SET_REG8_BIT(CM_RTC->CR2, u32IntTemp);
        } else {
            CLR_REG8_BIT(CM_RTC->CR2, u32IntTemp);
        }
    }

    /* Intrusion interrupt */
    if (0UL != (u32IntType & 0x00FF00UL)) {
        WRITE_REG32(bCM_RTC->TPCR0_b.TPIE0, enNewState);
    }
    if (0UL != (u32IntType & 0xFF0000UL)) {
        WRITE_REG32(bCM_RTC->TPCR1_b.TPIE1, enNewState);
    }
}

/**
 * @brief  Get RTC flag status.
 * @param  [in] u32Flag                 Specifies the RTC flag type.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref RTC_Flag
 *           @arg RTC_FLAG_ALL:         All of the above
 * @retval An @ref en_flag_status_t enumeration type value.
 */
en_flag_status_t RTC_GetStatus(uint32_t u32Flag)
{
    uint8_t u8FlagTemp;
    en_flag_status_t enFlagSta = RESET;

    /* Check parameters */
    DDL_ASSERT(IS_RTC_GET_FLAG(u32Flag));

    u8FlagTemp = (uint8_t)(u32Flag & 0xFFU);
    if (0U != u8FlagTemp) {
        if (0U != (READ_REG8_BIT(CM_RTC->CR2, u8FlagTemp))) {
            enFlagSta = SET;
        }
    }

    /* Intrusion interrupt flag */
    u8FlagTemp = (uint8_t)((u32Flag >> 16U) & 0xFFU);
    if ((0U != u8FlagTemp) && (SET != enFlagSta)) {
        if (0U != (READ_REG8_BIT(CM_RTC->TPSR, u8FlagTemp))) {
            enFlagSta = SET;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Clear RTC flag.
 * @param  [in] u32Flag                 Specifies the RTC flag type.
 *         This parameter can be one or any combination of the following values:
 *           @arg @ref RTC_Flag
 *           @arg RTC_FLAG_CLR_ALL:     All of the above
 * @retval None
 */
void RTC_ClearStatus(uint32_t u32Flag)
{
    uint8_t u8FlagTemp;

    /* Check parameters */
    DDL_ASSERT(IS_RTC_CLR_FLAG(u32Flag));

    u8FlagTemp = (uint8_t)(u32Flag & 0xFFU);
    if (0U != u8FlagTemp) {
        CLR_REG8_BIT(CM_RTC->CR2, u8FlagTemp);
    }

    u8FlagTemp  = (uint8_t)((u32Flag >> 16U) & 0xFFU);
    /* Intrusion interrupt flag */
    if (0U != u8FlagTemp) {
        CLR_REG8_BIT(CM_RTC->TPSR, u8FlagTemp);
    }
}

/**
 * @}
 */

#endif /* LL_RTC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
