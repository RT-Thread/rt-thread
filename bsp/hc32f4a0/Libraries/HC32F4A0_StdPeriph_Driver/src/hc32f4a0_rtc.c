/**
 *******************************************************************************
 * @file  hc32f4a0_rtc.c
 * @brief This file provides firmware functions to manage the Real-Time
 *        Clock(RTC).
 @verbatim
   Change Logs:
   Date             Author          Notes
   2020-06-12       Yangjp          First version
   2020-09-04       Yangjp          Optimize timeout handling in functions
 @endverbatim
 *******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 *
 *******************************************************************************
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f4a0_rtc.h"
#include "hc32f4a0_utility.h"

/**
 * @addtogroup HC32F4A0_DDL_Driver
 * @{
 */

/**
 * @defgroup DDL_RTC RTC
 * @brief Real-Time Clock Driver Library
 * @{
 */

#if (DDL_RTC_ENABLE == DDL_ON)

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
#define RTC_TPCR_CLEAR_MASK                 (RTC_TPCR0_TPCT0   | RTC_TPCR0_TPNF0 | \
                                             RTC_TPCR0_TPRSTE0 | RTC_TPCR0_TSTPE0)

/* Get the specified register address of the RTC Intrusion Control */
#define RTC_TPCRx(__CH__)                   ((uint32_t)(&(M4_RTC->TPCR0)) + (uint32_t)(__CH__))

/* RTC software reset timeout(ms) */
#define RTC_SOFTWARE_RESET_TIMEOUT          (100UL)

/* RTC mode switch timeout(ms) */
#define RTC_MODE_SWITCH_TIMEOUT             (100UL)

/**
 * @defgroup RTC_Check_Parameters_Validity RTC Check Parameters Validity
 * @{
 */
#define IS_RTC_DATA_FORMAT(x)                                                  \
(   ((x) == RTC_DATA_FORMAT_DEC)                    ||                         \
    ((x) == RTC_DATA_FORMAT_BCD))

#define IS_RTC_CLOCK_SOURCE(x)                                                 \
(   ((x) == RTC_CLOCK_SOURCE_XTAL32)                ||                         \
    ((x) == RTC_CLOCK_SOURCE_RTCLRC))

#define IS_RTC_HOUR_FORMAT(x)                                                  \
(   ((x) == RTC_HOUR_FORMAT_12)                     ||                         \
    ((x) == RTC_HOUR_FORMAT_24))

#define IS_RTC_PERIOD_INTERRUPT(x)                                             \
(   ((x) == RTC_PERIOD_INT_INVALID)                 ||                         \
    ((x) == RTC_PERIOD_INT_HALF_SECOND)             ||                         \
    ((x) == RTC_PERIOD_INT_ONE_SECOND)              ||                         \
    ((x) == RTC_PERIOD_INT_ONE_MINUTE)              ||                         \
    ((x) == RTC_PERIOD_INT_ONE_HOUR)                ||                         \
    ((x) == RTC_PERIOD_INT_ONE_DAY)                 ||                         \
    ((x) == RTC_PERIOD_INT_ONE_MONTH))

#define IS_RTC_CLOCK_COMPEN(x)                                                 \
(   ((x) == RTC_CLOCK_COMPEN_DISABLE)               ||                         \
    ((x) == RTC_CLOCK_COMPEN_ENABLE))

#define IS_RTC_OUTPUT_COMPEN_MODE(x)                                           \
(   ((x) == RTC_OUTPUT_COMPEN_MODE_DISTRIBUTED)     ||                         \
    ((x) == RTC_OUTPUT_COMPEN_MODE_UNIFORM))

#define IS_RTC_HOUR12_AM_PM(x)                                                 \
(   ((x) == RTC_HOUR12_AM_HOUR24)                   ||                         \
    ((x) == RTC_HOUR12_PM))

#define IS_RTC_INTRUSION_CHANNEL(x)                                            \
(   ((x) == RTC_INTRU_CH0)                          ||                         \
    ((x) == RTC_INTRU_CH1))

#define IS_RTC_INTRUSION_TIMESTAMP(x)                                          \
(   ((x) == RTC_INTRU_TIMESTAMP_DISABLE)            ||                         \
    ((x) == RTC_INTRU_TIMESTAMP_ENABLE))

#define IS_RTC_RESET_BACKUP_REGISTER(x)                                        \
(   ((x) == RTC_RESET_BACKUP_REG_DISABLE)           ||                         \
    ((x) == RTC_RESET_BACKUP_REG_ENABLE))

#define IS_RTC_INTRUSION_FILTER(x)                                             \
(   ((x) == RTC_INTRU_FILTER_INVALID)               ||                         \
    ((x) == RTC_INTRU_FILTER_THREE_TIME)            ||                         \
    ((x) == RTC_INTRU_FILTER_THREE_TIME_CLK_DIV32))

#define IS_RTC_INTRUSION_DETECT_EDGE(x)                                        \
(   ((x) == RTC_DETECT_EDGE_NONE)                   ||                         \
    ((x) == RTC_DETECT_EDGE_RISING)                 ||                         \
    ((x) == RTC_DETECT_EDGE_FALLING)                ||                         \
    ((x) == RTC_DETECT_EDGE_RISING_FALLING))

#define IS_RTC_GET_FLAG(x)                                                     \
(   (0UL != (x))                                    &&                         \
    (0UL == ((x) & ((uint32_t)(~(RTC_FLAG_PRDF      |                          \
                                RTC_FLAG_ALMF       |                          \
                                RTC_FLAG_RWEN       |                          \
                                RTC_FLAG_TPOVF      |                          \
                                RTC_FLAG_TPF0       |                          \
                                RTC_FLAG_TPF1))))))

#define IS_RTC_CLEAR_FLAG(x)                                                   \
(   (0UL != (x))                                    &&                         \
    (0UL == ((x) & ((uint32_t)(~(RTC_FLAG_PRDF      |                          \
                                 RTC_FLAG_ALMF      |                          \
                                 RTC_FLAG_TPOVF     |                          \
                                 RTC_FLAG_TPF0      |                          \
                                 RTC_FLAG_TPF1))))))

#define IS_RTC_INTERRUPT(x)                                                    \
(   (0UL != (x))                                    &&                         \
    (0UL == ((x) & ((uint32_t)(~(RTC_INT_PRDIE      |                          \
                                 RTC_INT_ALMIE      |                          \
                                 RTC_INT_TPIE0      |                          \
                                 RTC_INT_TPIE1))))))

#define IS_RTC_YEAR(x)                              ((x) <= 99U)

#define IS_RTC_MONTH(x)                             (((x) >= 1U) && ((x) <= 12U))

#define IS_RTC_DAY(x)                               (((x) >= 1U) && ((x) <= 31U))

#define IS_RTC_HOUR12(x)                            (((x) >= 1U) && ((x) <= 12U))

#define IS_RTC_HOUR24(x)                            ((x) <= 23U)

#define IS_RTC_MINUTE(x)                            ((x) <= 59U)

#define IS_RTC_SECOND(x)                            ((x) <= 59U)

#define IS_RTC_WEEKDAY(x)                           ((x) <= 6U)

#define IS_RTC_ALARM_WEEKDAY(x)                     (((x) >= 0x01U) && ((x) <= 0x7FU))

#define IS_RTC_COMPENSATION_VALUE(x)                ((x) <= 0x1FFU)
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
 * @retval An en_result_t enumeration value:
 *           - Ok: De-Initialize success
 *           - ErrorTimeout: De-Initialize timeout
 */
en_result_t RTC_DeInit(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    WRITE_REG32(bM4_RTC->CR0_b.RESET, Reset);
    /* Waiting for normal count status or end of RTC software reset */
    u32Count = RTC_SOFTWARE_RESET_TIMEOUT * (HCLK_VALUE / 20000UL);
    while (0UL != READ_REG32(bM4_RTC->CR0_b.RESET))
    {
        if (0UL == u32Count)
        {
            enRet = ErrorTimeout;
            break;
        }
        u32Count--;
    }

    if (Ok == enRet)
    {
        /* Reset all RTC registers */
        WRITE_REG32(bM4_RTC->CR0_b.RESET, Set);
        /* Waiting for RTC software reset to complete */
        u32Count = RTC_SOFTWARE_RESET_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (0UL != READ_REG32(bM4_RTC->CR0_b.RESET))
        {
            if (0UL == u32Count)
            {
                enRet = ErrorTimeout;
                break;
            }
            u32Count--;
        }
    }

    return enRet;
}

/**
 * @brief  Initialize RTC.
 * @param  [in] pstcRtcInit             Pointer to a @ref stc_rtc_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_Init(const stc_rtc_init_t *pstcRtcInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRtcInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_CLOCK_SOURCE(pstcRtcInit->u8ClockSource));
        DDL_ASSERT(IS_RTC_HOUR_FORMAT(pstcRtcInit->u8HourFormat));
        DDL_ASSERT(IS_RTC_PERIOD_INTERRUPT(pstcRtcInit->u8PeriodInterrupt));
        DDL_ASSERT(IS_RTC_CLOCK_COMPEN(pstcRtcInit->u8ClkCompenEn));
        DDL_ASSERT(IS_RTC_COMPENSATION_VALUE(pstcRtcInit->u16ClkCompenValue));
        DDL_ASSERT(IS_RTC_OUTPUT_COMPEN_MODE(pstcRtcInit->u8CompenMode));

        /* RTC CR3 Configuration */
        MODIFY_REG8(M4_RTC->CR3, (RTC_CR3_LRCEN | RTC_CR3_RCKSEL), pstcRtcInit->u8ClockSource);
        /* RTC CR1 Configuration */
        MODIFY_REG8(M4_RTC->CR1, (RTC_CR1_PRDS | RTC_CR1_AMPM | RTC_CR1_ONEHZSEL),
                    (pstcRtcInit->u8PeriodInterrupt | pstcRtcInit->u8HourFormat | pstcRtcInit->u8CompenMode));
        /* RTC Compensation Configuration */
        MODIFY_REG8(M4_RTC->ERRCRH, (RTC_ERRCRH_COMPEN | RTC_ERRCRH_COMP8),
                    (pstcRtcInit->u8ClkCompenEn | (uint8_t)((pstcRtcInit->u16ClkCompenValue >> 8U) & 0x01U)));
        WRITE_REG8(M4_RTC->ERRCRL, (uint8_t)(pstcRtcInit->u16ClkCompenValue & 0xFFU));
    }

    return enRet;
}

/**
 * @brief  Fills each stc_rtc_init_t member with default value.
 * @param  [out] pstcRtcInit            Pointer to a @ref stc_rtc_init_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: stc_rtc_init_t member initialize success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_StructInit(stc_rtc_init_t *pstcRtcInit)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRtcInit)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        pstcRtcInit->u8ClockSource      = RTC_CLOCK_SOURCE_RTCLRC;
        pstcRtcInit->u8HourFormat       = RTC_HOUR_FORMAT_24;
        pstcRtcInit->u8PeriodInterrupt  = RTC_PERIOD_INT_INVALID;
        pstcRtcInit->u8ClkCompenEn      = RTC_CLOCK_COMPEN_DISABLE;
        pstcRtcInit->u16ClkCompenValue  = 0U;
        pstcRtcInit->u8CompenMode       = RTC_OUTPUT_COMPEN_MODE_DISTRIBUTED;
    }

    return enRet;
}

/**
 * @brief  Enter RTC read/write mode.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Enter mode success
 *           - ErrorTimeout: Enter mode timeout
 */
en_result_t RTC_EnterRwMode(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    /* Mode switch when RTC is running */
    if (0UL != READ_REG32(bM4_RTC->CR1_b.START))
    {
        if (1UL != READ_REG32(bM4_RTC->CR2_b.RWEN))
        {
            WRITE_REG32(bM4_RTC->CR2_b.RWREQ, Set);
            /* Waiting for RWEN bit set */
            u32Count = RTC_MODE_SWITCH_TIMEOUT * (HCLK_VALUE / 20000UL);
            while (1UL != READ_REG32(bM4_RTC->CR2_b.RWEN))
            {
                if (0UL == u32Count)
                {
                    enRet = ErrorTimeout;
                    break;
                }
                u32Count--;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Exit RTC read/write mode.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Exit mode success
 *           - ErrorTimeout: Exit mode timeout
 */
en_result_t RTC_ExitRwMode(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    /* Mode switch when RTC is running */
    if (0UL != READ_REG32(bM4_RTC->CR1_b.START))
    {
        if (0UL != READ_REG32(bM4_RTC->CR2_b.RWEN))
        {
            WRITE_REG32(bM4_RTC->CR2_b.RWREQ, Reset);
            /* Waiting for RWEN bit reset */
            u32Count = RTC_MODE_SWITCH_TIMEOUT * (HCLK_VALUE / 20000UL);
            while (0UL != READ_REG32(bM4_RTC->CR2_b.RWEN))
            {
                if (0UL == u32Count)
                {
                    enRet = ErrorTimeout;
                    break;
                }
                u32Count--;
            }
        }
    }

    return enRet;
}

/**
 * @brief  RTC period interrupt config.
 * @param  [in] u8IntCond               Specifies the period interrupt type
 *         This parameter can be one of the following values:
 *           @arg RTC_PERIOD_INT_INVALID:       Period interrupt invalid
 *           @arg RTC_PERIOD_INT_HALF_SECOND:   0.5 second period interrupt
 *           @arg RTC_PERIOD_INT_ONE_SECOND:    1 second period interrupt
 *           @arg RTC_PERIOD_INT_ONE_MINUTE:    1 minute period interrupt
 *           @arg RTC_PERIOD_INT_ONE_HOUR:      1 hour period interrupt
 *           @arg RTC_PERIOD_INT_ONE_DAY:       1 day period interrupt
 *           @arg RTC_PERIOD_INT_ONE_MONTH:     1 month period interrupt
 * @retval None
 */
void RTC_PeriodIntConfig(uint8_t u8IntCond)
{
    uint32_t u32RtcSta;
    uint32_t u32IntSta;

    /* Check parameters */
    DDL_ASSERT(IS_RTC_PERIOD_INTERRUPT(u8IntCond));

    u32RtcSta = READ_REG32(bM4_RTC->CR1_b.START);
    u32IntSta = READ_REG32(bM4_RTC->CR2_b.PRDIE);
    /* Disable period interrupt when START=1 and clear period flag after write */
    if ((0UL != u32IntSta) && (0UL != u32RtcSta))
    {
        WRITE_REG32(bM4_RTC->CR2_b.PRDIE, Reset);
    }

    /* RTC CR1 Configuration */
    MODIFY_REG8(M4_RTC->CR1, RTC_CR1_PRDS, u8IntCond);
    WRITE_REG32(bM4_RTC->CR2_b.PRDF, Reset);

    if ((0UL != u32IntSta) && (0UL != u32RtcSta))
    {
        WRITE_REG32(bM4_RTC->CR2_b.PRDIE, Set);
    }
}

/**
 * @brief  RTC enter low power condition check.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Ok: Can enter low power mode
 *           - ErrorTimeout: Can't enter low power mode
 */
en_result_t RTC_LowPowerCheck(void)
{
    __IO uint32_t u32Count;
    en_result_t enRet = Ok;

    /* Check RTC work status */
    if (0UL != READ_REG32(bM4_RTC->CR1_b.START))
    {
        WRITE_REG32(bM4_RTC->CR2_b.RWREQ, Set);
        /* Waiting for RTC RWEN bit set */
        u32Count = RTC_MODE_SWITCH_TIMEOUT * (HCLK_VALUE / 20000UL);
        while (1UL != READ_REG32(bM4_RTC->CR2_b.RWEN))
        {
            if (0UL == u32Count)
            {
                enRet = ErrorTimeout;
                break;
            }
            u32Count--;
        }

        if (Ok == enRet)
        {
            WRITE_REG32(bM4_RTC->CR2_b.RWREQ, Reset);
            /* Waiting for RTC RWEN bit reset */
            u32Count = RTC_MODE_SWITCH_TIMEOUT * (HCLK_VALUE / 20000UL);
            while (0UL != READ_REG32(bM4_RTC->CR2_b.RWEN))
            {
                if (0UL == u32Count)
                {
                    enRet = ErrorTimeout;
                    break;
                }
                u32Count--;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Set RTC clock compensation value.
 * @param  [in] u16CompenVal            Specifies the clock compensation value of RTC.
 *           @arg This parameter can be a number between Min_Data = 0 and Max_Data = 0x1FF.
 * @retval None
 */
void RTC_SetClkCompenValue(uint16_t u16CompenVal)
{
    /* Check parameters */
    DDL_ASSERT(IS_RTC_COMPENSATION_VALUE(u16CompenVal));

    WRITE_REG32(bM4_RTC->ERRCRH_b.COMP8, ((uint32_t)u16CompenVal >> 8U) & 0x01U);
    WRITE_REG8(M4_RTC->ERRCRL, (uint8_t)(u16CompenVal & 0x00FFU));
}

/**
 * @brief  Enable or disable RTC count.
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void RTC_Cmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_RTC->CR1_b.START, enNewSta);
}

/**
 * @brief  Enable or disable RTC LRC function.
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void RTC_LrcCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_RTC->CR3_b.LRCEN, enNewSta);
}

/**
 * @brief  Get RTC counter status.
 * @param  None
 * @retval An en_result_t enumeration value:
 *           - Enable: RTC counter started
 *           - Disable: RTC counter stopped
 */
en_functional_state_t RTC_GetCounterState(void)
{
    en_functional_state_t enState;

    if (0UL != READ_REG32(bM4_RTC->CR1_b.START))
    {
        enState = Enable;
    }
    else
    {
        enState = Disable;
    }

    return enState;
}

/**
 * @brief  Enable or disable RTC 1HZ output.
 * @param  [in] enNewSta                 The function new state.
 *          @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void RTC_OneHzOutputCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_RTC->CR1_b.ONEHZOE, enNewSta);
}

/**
 * @brief  Enable or disable clock compensation.
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void RTC_ClkCompenCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_RTC->ERRCRH_b.COMPEN, enNewSta);
}

/**
 * @brief  Set RTC current date.
 * @param  [in] u8Format                Specifies the format of the entered parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FORMAT_DEC:  Decimal data format
 *           @arg RTC_DATA_FORMAT_BCD:  BCD data format
 * @param  [in] pstcRtcDate             Pointer to a @ref stc_rtc_date_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Set date success
 *           - Error: Set date failed
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_SetDate(uint8_t u8Format, stc_rtc_date_t *pstcRtcDate)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRtcDate)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FORMAT(u8Format));
        if (RTC_DATA_FORMAT_DEC != u8Format)
        {
            DDL_ASSERT(IS_RTC_YEAR(BCD2DEC(pstcRtcDate->u8Year)));
            DDL_ASSERT(IS_RTC_MONTH(BCD2DEC(pstcRtcDate->u8Month)));
            DDL_ASSERT(IS_RTC_DAY(BCD2DEC(pstcRtcDate->u8Day)));
        }
        else
        {
            DDL_ASSERT(IS_RTC_YEAR(pstcRtcDate->u8Year));
            DDL_ASSERT(IS_RTC_MONTH(pstcRtcDate->u8Month));
            DDL_ASSERT(IS_RTC_DAY(pstcRtcDate->u8Day));
        }
        DDL_ASSERT(IS_RTC_WEEKDAY(pstcRtcDate->u8Weekday));

        /* Enter read/write mode */
        if (Ok != RTC_EnterRwMode())
        {
            enRet = Error;
        }
        else
        {
            if (RTC_DATA_FORMAT_DEC == u8Format)
            {
                pstcRtcDate->u8Year  = DEC2BCD(pstcRtcDate->u8Year);
                pstcRtcDate->u8Month = DEC2BCD(pstcRtcDate->u8Month);
                pstcRtcDate->u8Day   = DEC2BCD(pstcRtcDate->u8Day);
            }

            WRITE_REG8(M4_RTC->YEAR, pstcRtcDate->u8Year);
            WRITE_REG8(M4_RTC->MON,  pstcRtcDate->u8Month);
            WRITE_REG8(M4_RTC->DAY,  pstcRtcDate->u8Day);
            WRITE_REG8(M4_RTC->WEEK, pstcRtcDate->u8Weekday);

            /* Exit read/write mode */
            if (Ok != RTC_ExitRwMode())
            {
                enRet = Error;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Get RTC current date.
 * @param  [in] u8Format                Specifies the format of the returned parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FORMAT_DEC:  Decimal data format
 *           @arg RTC_DATA_FORMAT_BCD:  BCD data format
 * @param  [out] pstcRtcDate            Pointer to a @ref stc_rtc_date_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Get date success
 *           - Error: Get date failed
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_GetDate(uint8_t u8Format, stc_rtc_date_t *pstcRtcDate)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRtcDate)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FORMAT(u8Format));
        /* Enter read/write mode */
        if (Ok != RTC_EnterRwMode())
        {
            enRet = Error;
        }
        else
        {
            /* Get RTC date registers */
            pstcRtcDate->u8Year    = READ_REG8(M4_RTC->YEAR);
            pstcRtcDate->u8Month   = READ_REG8(M4_RTC->MON);
            pstcRtcDate->u8Day     = READ_REG8(M4_RTC->DAY);
            pstcRtcDate->u8Weekday = READ_REG8(M4_RTC->WEEK);

            /* Check decimal format*/
            if (RTC_DATA_FORMAT_DEC == u8Format)
            {
                pstcRtcDate->u8Year  = BCD2DEC(pstcRtcDate->u8Year);
                pstcRtcDate->u8Month = BCD2DEC(pstcRtcDate->u8Month);
                pstcRtcDate->u8Day   = BCD2DEC(pstcRtcDate->u8Day);
            }

            /* exit read/write mode */
            if (Ok != RTC_ExitRwMode())
            {
                enRet = Error;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Set RTC current time.
 * @param  [in] u8Format                Specifies the format of the entered parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FORMAT_DEC:  Decimal data format
 *           @arg RTC_DATA_FORMAT_BCD:  BCD data format
 * @param  [in] pstcRtcTime             Pointer to a @ref stc_rtc_time_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Set time success
 *           - Error: Set time failed
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_SetTime(uint8_t u8Format, stc_rtc_time_t *pstcRtcTime)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRtcTime)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FORMAT(u8Format));
        if (RTC_DATA_FORMAT_DEC != u8Format)
        {
            if (RTC_HOUR_FORMAT_12 == READ_REG32(bM4_RTC->CR1_b.AMPM))
            {
                DDL_ASSERT(IS_RTC_HOUR12(BCD2DEC(pstcRtcTime->u8Hour)));
                DDL_ASSERT(IS_RTC_HOUR12_AM_PM(pstcRtcTime->u8AmPm));
            }
            else
            {
                DDL_ASSERT(IS_RTC_HOUR24(BCD2DEC(pstcRtcTime->u8Hour)));
            }
            DDL_ASSERT(IS_RTC_MINUTE(BCD2DEC(pstcRtcTime->u8Minute)));
            DDL_ASSERT(IS_RTC_SECOND(BCD2DEC(pstcRtcTime->u8Second)));
        }
        else
        {
            if (RTC_HOUR_FORMAT_12 == READ_REG32(bM4_RTC->CR1_b.AMPM))
            {
                DDL_ASSERT(IS_RTC_HOUR12(pstcRtcTime->u8Hour));
                DDL_ASSERT(IS_RTC_HOUR12_AM_PM(pstcRtcTime->u8AmPm));
            }
            else
            {
                DDL_ASSERT(IS_RTC_HOUR24(pstcRtcTime->u8Hour));
            }
            DDL_ASSERT(IS_RTC_MINUTE(pstcRtcTime->u8Minute));
            DDL_ASSERT(IS_RTC_SECOND(pstcRtcTime->u8Second));
        }

        /* Enter read/write mode */
        if (Ok != RTC_EnterRwMode())
        {
            enRet = Error;
        }
        else
        {
            if (RTC_DATA_FORMAT_DEC == u8Format)
            {
                pstcRtcTime->u8Hour   = DEC2BCD(pstcRtcTime->u8Hour);
                pstcRtcTime->u8Minute = DEC2BCD(pstcRtcTime->u8Minute);
                pstcRtcTime->u8Second = DEC2BCD(pstcRtcTime->u8Second);
            }
            if ((RTC_HOUR_FORMAT_12 == READ_REG32(bM4_RTC->CR1_b.AMPM)) &&
                (RTC_HOUR12_PM == pstcRtcTime->u8AmPm))
            {
                pstcRtcTime->u8Hour |= RTC_HOUR12_PM;
            }

            WRITE_REG8(M4_RTC->HOUR, pstcRtcTime->u8Hour);
            WRITE_REG8(M4_RTC->MIN,  pstcRtcTime->u8Minute);
            WRITE_REG8(M4_RTC->SEC,  pstcRtcTime->u8Second);

            /* Exit read/write mode */
            if (Ok != RTC_ExitRwMode())
            {
                enRet = Error;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Get RTC current time.
 * @param  [in] u8Format                Specifies the format of the returned parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FORMAT_DEC:  Decimal data format
 *           @arg RTC_DATA_FORMAT_BCD:  BCD data format
 * @param  [out] pstcRtcTime            Pointer to a @ref stc_rtc_time_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Get time success
 *           - Error: Get time failed
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_GetTime(uint8_t u8Format, stc_rtc_time_t *pstcRtcTime)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRtcTime)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FORMAT(u8Format));
        /* Enter read/write mode */
        if (Ok != RTC_EnterRwMode())
        {
            enRet = Error;
        }
        else
        {
            /* Get RTC time registers */
            pstcRtcTime->u8Hour   = READ_REG8(M4_RTC->HOUR);
            pstcRtcTime->u8Minute = READ_REG8(M4_RTC->MIN);
            pstcRtcTime->u8Second = READ_REG8(M4_RTC->SEC);

            if (RTC_HOUR_FORMAT_12 == READ_REG32(bM4_RTC->CR1_b.AMPM))
            {
                if (RTC_HOUR12_PM == (pstcRtcTime->u8Hour & RTC_HOUR12_PM))
                {
                    pstcRtcTime->u8Hour &= (uint8_t)(~RTC_HOUR12_PM);
                    pstcRtcTime->u8AmPm  = RTC_HOUR12_PM;
                }
                else
                {
                    pstcRtcTime->u8AmPm = RTC_HOUR12_AM_HOUR24;
                }
            }
            else
            {
                pstcRtcTime->u8AmPm = RTC_HOUR12_AM_HOUR24;
            }

            /* Check decimal format*/
            if (RTC_DATA_FORMAT_DEC == u8Format)
            {
                pstcRtcTime->u8Hour   = BCD2DEC(pstcRtcTime->u8Hour);
                pstcRtcTime->u8Minute = BCD2DEC(pstcRtcTime->u8Minute);
                pstcRtcTime->u8Second = BCD2DEC(pstcRtcTime->u8Second);
            }

            /* exit read/write mode */
            if (Ok != RTC_ExitRwMode())
            {
                enRet = Error;
            }
        }
    }

    return enRet;
}

/**
 * @brief  Set RTC alarm time.
 * @param  [in] u8Format                Specifies the format of the entered parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FORMAT_DEC:  Decimal data format
 *           @arg RTC_DATA_FORMAT_BCD:  BCD data format
 * @param  [in] pstcRtcAlarm            Pointer to a @ref stc_rtc_alarm_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Set RTC alarm time success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_SetAlarm(uint8_t u8Format, stc_rtc_alarm_t *pstcRtcAlarm)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRtcAlarm)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FORMAT(u8Format));
        if (RTC_DATA_FORMAT_DEC != u8Format)
        {
            if (RTC_HOUR_FORMAT_12 == READ_REG32(bM4_RTC->CR1_b.AMPM))
            {
                DDL_ASSERT(IS_RTC_HOUR12(BCD2DEC(pstcRtcAlarm->u8AlarmHour)));
                DDL_ASSERT(IS_RTC_HOUR12_AM_PM(pstcRtcAlarm->u8AlarmAmPm));
            }
            else
            {
                DDL_ASSERT(IS_RTC_HOUR24(BCD2DEC(pstcRtcAlarm->u8AlarmHour)));
            }
            DDL_ASSERT(IS_RTC_MINUTE(BCD2DEC(pstcRtcAlarm->u8AlarmMinute)));
        }
        else
        {
            if (RTC_HOUR_FORMAT_12 == READ_REG32(bM4_RTC->CR1_b.AMPM))
            {
                DDL_ASSERT(IS_RTC_HOUR12(pstcRtcAlarm->u8AlarmHour));
                DDL_ASSERT(IS_RTC_HOUR12_AM_PM(pstcRtcAlarm->u8AlarmAmPm));
            }
            else
            {
                DDL_ASSERT(IS_RTC_HOUR24(pstcRtcAlarm->u8AlarmHour));
            }
            DDL_ASSERT(IS_RTC_MINUTE(pstcRtcAlarm->u8AlarmMinute));
        }
        DDL_ASSERT(IS_RTC_ALARM_WEEKDAY(pstcRtcAlarm->u8AlarmWeekday));

        /* Configure alarm registers */
        if (RTC_DATA_FORMAT_DEC == u8Format)
        {
            pstcRtcAlarm->u8AlarmHour   = DEC2BCD(pstcRtcAlarm->u8AlarmHour);
            pstcRtcAlarm->u8AlarmMinute = DEC2BCD(pstcRtcAlarm->u8AlarmMinute);
        }
        if ((RTC_HOUR_FORMAT_12 == READ_REG32(bM4_RTC->CR1_b.AMPM)) &&
            (RTC_HOUR12_PM == pstcRtcAlarm->u8AlarmAmPm))
        {
            pstcRtcAlarm->u8AlarmHour |= RTC_HOUR12_PM;
        }

        WRITE_REG8(M4_RTC->ALMHOUR, pstcRtcAlarm->u8AlarmHour);
        WRITE_REG8(M4_RTC->ALMMIN,  pstcRtcAlarm->u8AlarmMinute);
        WRITE_REG8(M4_RTC->ALMWEEK, pstcRtcAlarm->u8AlarmWeekday);
    }

    return enRet;
}

/**
 * @brief  Get RTC alarm time.
 * @param  [in] u8Format                Specifies the format of the returned parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FORMAT_DEC:  Decimal data format
 *           @arg RTC_DATA_FORMAT_BCD:  BCD data format
 * @param  [out] pstcRtcAlarm           Pointer to a @ref stc_rtc_alarm_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Get RTC alarm time success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_GetAlarm(uint8_t u8Format, stc_rtc_alarm_t *pstcRtcAlarm)
{
    en_result_t enRet = Ok;

    if (NULL == pstcRtcAlarm)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FORMAT(u8Format));

        /* Get RTC date and time register */
        pstcRtcAlarm->u8AlarmWeekday = READ_REG8(M4_RTC->ALMWEEK);
        pstcRtcAlarm->u8AlarmMinute  = READ_REG8(M4_RTC->ALMMIN);
        pstcRtcAlarm->u8AlarmHour    = READ_REG8(M4_RTC->ALMHOUR);

        if (RTC_HOUR_FORMAT_12 == READ_REG32(bM4_RTC->CR1_b.AMPM))
        {
            if (RTC_HOUR12_PM == (pstcRtcAlarm->u8AlarmHour & RTC_HOUR12_PM))
            {
                pstcRtcAlarm->u8AlarmHour &= (uint8_t)(~RTC_HOUR12_PM);
                pstcRtcAlarm->u8AlarmAmPm = RTC_HOUR12_PM;
            }
            else
            {
                pstcRtcAlarm->u8AlarmAmPm = RTC_HOUR12_AM_HOUR24;
            }
        }

        /* Check decimal format*/
        if (RTC_DATA_FORMAT_DEC == u8Format)
        {
            pstcRtcAlarm->u8AlarmHour   = BCD2DEC(pstcRtcAlarm->u8AlarmHour);
            pstcRtcAlarm->u8AlarmMinute = BCD2DEC(pstcRtcAlarm->u8AlarmMinute);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable RTC alarm.
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void RTC_AlarmCmd(en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    WRITE_REG32(bM4_RTC->CR2_b.ALME, enNewSta);
}

/**
 * @brief  Configure RTC intrusion function.
 * @param  [in] u8Ch                    Specifies the RTC intrusion channel.
 *         This parameter can be one of the following values:
 *           @arg RTC_INTRU_CH0:    Intrusion channel 0
 *           @arg RTC_INTRU_CH1:    Intrusion channel 1
 * @param  [in] pstcIntru               Pointer to a @ref stc_rtc_intrusion_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Configure RTC intrusion function success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_IntrusionConfig(uint8_t u8Ch, const stc_rtc_intrusion_t *pstcIntru)
{
    en_result_t enRet = Ok;
    __IO uint8_t *TPCR;

    if (NULL == pstcIntru)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_INTRUSION_CHANNEL(u8Ch));
        DDL_ASSERT(IS_RTC_INTRUSION_TIMESTAMP(pstcIntru->u8TimeStampEn));
        DDL_ASSERT(IS_RTC_RESET_BACKUP_REGISTER(pstcIntru->u8ResetBackupRegEn));
        DDL_ASSERT(IS_RTC_INTRUSION_FILTER(pstcIntru->u8Filter));
        DDL_ASSERT(IS_RTC_INTRUSION_DETECT_EDGE(pstcIntru->u8TrigEdge));

        TPCR = (__IO uint8_t *)RTC_TPCRx(u8Ch);
        /* RTC Intrusion control Configuration */
        MODIFY_REG8(*TPCR, RTC_TPCR_CLEAR_MASK,
                    (pstcIntru->u8TimeStampEn | pstcIntru->u8ResetBackupRegEn |
                     pstcIntru->u8Filter      | pstcIntru->u8TrigEdge));
    }

    return enRet;
}

/**
 * @brief  Get RTC intrusion timestamp.
 * @param  [in] u8Format                Specifies the format of the returned parameters.
 *         This parameter can be one of the following values:
 *           @arg RTC_DATA_FORMAT_DEC:  Decimal data format
 *           @arg RTC_DATA_FORMAT_BCD:  BCD data format
 * @param  [out] pstcTimestamp          Pointer to a @ref stc_rtc_timestamp_t structure
 * @retval An en_result_t enumeration value:
 *           - Ok: Get RTC intrusion timestamp success
 *           - ErrorInvalidParameter: Invalid parameter
 */
en_result_t RTC_GetIntrusionTimestamp(uint8_t u8Format, stc_rtc_timestamp_t *pstcTimestamp)
{
    en_result_t enRet = Ok;

    if (NULL == pstcTimestamp)
    {
        enRet = ErrorInvalidParameter;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_RTC_DATA_FORMAT(u8Format));

        /* Get RTC Timestamp registers */
        pstcTimestamp->stcTSTime.u8Hour   = READ_REG8(M4_RTC->HOURTP);
        pstcTimestamp->stcTSTime.u8Minute = READ_REG8(M4_RTC->MINTP);
        pstcTimestamp->stcTSTime.u8Second = READ_REG8(M4_RTC->SECTP);
        pstcTimestamp->u8TSMonth          = READ_REG8(M4_RTC->MONTP);
        pstcTimestamp->u8TSDay            = READ_REG8(M4_RTC->DAYTP);

        if (RTC_HOUR_FORMAT_12 == READ_REG32(bM4_RTC->CR1_b.AMPM))
        {
            if (RTC_HOUR12_PM == (pstcTimestamp->stcTSTime.u8Hour & RTC_HOUR12_PM))
            {
                pstcTimestamp->stcTSTime.u8Hour &= (uint8_t)(~RTC_HOUR12_PM);
                pstcTimestamp->stcTSTime.u8AmPm  = RTC_HOUR12_PM;
            }
            else
            {
                pstcTimestamp->stcTSTime.u8AmPm = RTC_HOUR12_AM_HOUR24;
            }
        }
        else
        {
            pstcTimestamp->stcTSTime.u8AmPm = RTC_HOUR12_AM_HOUR24;
        }

        /* Check decimal format*/
        if (RTC_DATA_FORMAT_DEC == u8Format)
        {
            pstcTimestamp->stcTSTime.u8Hour   = BCD2DEC(pstcTimestamp->stcTSTime.u8Hour);
            pstcTimestamp->stcTSTime.u8Minute = BCD2DEC(pstcTimestamp->stcTSTime.u8Minute);
            pstcTimestamp->stcTSTime.u8Second = BCD2DEC(pstcTimestamp->stcTSTime.u8Second);
            pstcTimestamp->u8TSMonth          = BCD2DEC(pstcTimestamp->u8TSMonth);
            pstcTimestamp->u8TSDay            = BCD2DEC(pstcTimestamp->u8TSDay);
        }
    }

    return enRet;
}

/**
 * @brief  Enable or disable RTC intrusion.
 * @param  [in] u8Ch                    Specifies the RTC intrusion channel.
 *         This parameter can be one of the following values:
 *           @arg RTC_INTRU_CH0:    Intrusion channel 0
 *           @arg RTC_INTRU_CH1:    Intrusion channel 1
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void RTC_IntrusionCmd(uint8_t u8Ch, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_RTC_INTRUSION_CHANNEL(u8Ch));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (RTC_INTRU_CH0 != u8Ch)
    {
        WRITE_REG32(bM4_RTC->TPCR1_b.TPEN1, enNewSta);
    }
    else
    {
        WRITE_REG32(bM4_RTC->TPCR0_b.TPEN0, enNewSta);
    }
}

/**
 * @brief  Enable or disable specified RTC interrupt.
 * @param  [in] u32IntSrc               Specifies the RTC interrupt source.
 *         This parameter can be one or any combination of the following values:
 *           @arg RTC_INT_PRDIE:    Period interrupt
 *           @arg RTC_INT_ALMIE:    Alarm interrupt
 *           @arg RTC_INT_TPIE0:    RTCIC0 intrusion interrupt
 *           @arg RTC_INT_TPIE1:    RTCIC1 intrusion interrupt
 * @param  [in] enNewSta                The function new state.
 *           @arg This parameter can be: Enable or Disable.
 * @retval None
 */
void RTC_IntCmd(uint32_t u32IntSrc, en_functional_state_t enNewSta)
{
    /* Check parameters */
    DDL_ASSERT(IS_RTC_INTERRUPT(u32IntSrc));
    DDL_ASSERT(IS_FUNCTIONAL_STATE(enNewSta));

    if (0UL != (u32IntSrc & 0x0000FFUL))
    {
        if (Disable != enNewSta)
        {
            SET_REG8_BIT(M4_RTC->CR2, (u32IntSrc & 0x0000FFUL));
        }
        else
        {
            CLEAR_REG8_BIT(M4_RTC->CR2, (u32IntSrc & 0x0000FFUL));
        }
    }

    if (0UL != (u32IntSrc & 0x00FF00UL))
    {
        WRITE_REG32(bM4_RTC->TPCR0_b.TPIE0, enNewSta);
    }

    if (0UL != (u32IntSrc & 0xFF0000UL))
    {
        WRITE_REG32(bM4_RTC->TPCR1_b.TPIE1, enNewSta);
    }
}

/**
 * @brief  Get RTC flag status.
 * @param  [in] u32Flag                 Specifies the RTC flag type.
 *         This parameter can be one or any combination of the following values:
 *           @arg RTC_FLAG_PRDF:    Period flag
 *           @arg RTC_FLAG_ALMF:    Alarm flag
 *           @arg RTC_FLAG_RWEN:    Read and write permission flag
 *           @arg RTC_FLAG_TPOVF:   Intrusion overflow flag
 *           @arg RTC_FLAG_TPF0:    RTCIC0 intrusion flag
 *           @arg RTC_FLAG_TPF1:    RTCIC1 intrusion flag
 * @retval An en_flag_status_t enumeration value:
 *           - Set: Flag is set
 *           - Reset: Flag is reset
 */
en_flag_status_t RTC_GetStatus(uint32_t u32Flag)
{
    en_flag_status_t enFlagSta = Reset;
    uint8_t u8NormalFlag;
    uint8_t u8IntruFlag;

    /* Check parameters */
    DDL_ASSERT(IS_RTC_GET_FLAG(u32Flag));

    u8NormalFlag = (uint8_t)(u32Flag & 0xFFU);
    u8IntruFlag  = (uint8_t)((u32Flag >> 16U) & 0xFFU);
    if (0U != u8NormalFlag)
    {
        if (0U != (READ_REG8_BIT(M4_RTC->CR2, u8NormalFlag)))
        {
            enFlagSta = Set;
        }
    }
    if ((0U != u8IntruFlag) && (Set != enFlagSta))
    {
        if (0U != (READ_REG8_BIT(M4_RTC->TPSR, u8IntruFlag)))
        {
            enFlagSta = Set;
        }
    }

    return enFlagSta;
}

/**
 * @brief  Clear RTC flag.
 * @param  [in] u32Flag                 Specifies the RTC flag type.
 *         This parameter can be one or any combination of the following values:
 *           @arg RTC_FLAG_PRDF:    Period flag
 *           @arg RTC_FLAG_ALMF:    Alarm flag
 *           @arg RTC_FLAG_TPOVF:   Intrusion overflow flag
 *           @arg RTC_FLAG_TPF0:    RTCIC0 intrusion flag
 *           @arg RTC_FLAG_TPF1:    RTCIC1 intrusion flag
 * @retval None
 */
void RTC_ClearStatus(uint32_t u32Flag)
{
    uint8_t u8NormalFlag;
    uint8_t u8IntruFlag;

    /* Check parameters */
    DDL_ASSERT(IS_RTC_CLEAR_FLAG(u32Flag));

    u8NormalFlag = (uint8_t)(u32Flag & 0xFFU);
    u8IntruFlag  = (uint8_t)((u32Flag >> 16U) & 0xFFU);
    if (0U != u8NormalFlag)
    {
        CLEAR_REG8_BIT(M4_RTC->CR2, u8NormalFlag);
    }
    if (0U != u8IntruFlag)
    {
        CLEAR_REG8_BIT(M4_RTC->TPSR, u8IntruFlag);
    }
}

/**
 * @}
 */

#endif /* DDL_RTC_ENABLE */

/**
 * @}
 */

/**
* @}
*/

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
