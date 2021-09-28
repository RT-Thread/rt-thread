/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_wdt.c
 **
 ** A detailed description is available at
 ** @link WdtGroup Watchdog Counter description @endlink
 **
 **   - 2018-10-18  CDT  First version for Device Driver Library of WDT.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_wdt.h"
#include "hc32f460_utility.h"

#if (DDL_WDT_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup WdtGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*!< Parameter validity check for count cycle */
#define IS_VALID_COUNT_CYCLE(x)                                                \
(   (WdtCountCycle256 == (x))                   ||                             \
    (WdtCountCycle4096 == (x))                  ||                             \
    (WdtCountCycle16384 == (x))                 ||                             \
    (WdtCountCycle65536 == (x)))

/*!< Parameter validity check for clock division */
#define IS_VALID_CLOCK_DIV(x)                                                  \
(   (WdtPclk3Div4 == (x))                       ||                             \
    (WdtPclk3Div64 == (x))                      ||                             \
    (WdtPclk3Div128 == (x))                     ||                             \
    (WdtPclk3Div256 == (x))                     ||                             \
    (WdtPclk3Div512 == (x))                     ||                             \
    (WdtPclk3Div1024 == (x))                    ||                             \
    (WdtPclk3Div2048 == (x))                    ||                             \
    (WdtPclk3Div8192 == (x)))

/*!< Parameter validity check for allow refresh percent range */
#define IS_VALID_ALLOW_REFRESH_RANGE(x)                                        \
(   (WdtRefresh100Pct == (x))                   ||                             \
    (WdtRefresh0To25Pct == (x))                 ||                             \
    (WdtRefresh25To50Pct == (x))                ||                             \
    (WdtRefresh0To50Pct == (x))                 ||                             \
    (WdtRefresh50To75Pct == (x))                ||                             \
    (WdtRefresh0To25PctAnd50To75Pct == (x))     ||                             \
    (WdtRefresh25To75Pct == (x))                ||                             \
    (WdtRefresh0To75Pct == (x))                 ||                             \
    (WdtRefresh75To100Pct == (x))               ||                             \
    (WdtRefresh0To25PctAnd75To100Pct == (x))    ||                             \
    (WdtRefresh25To50PctAnd75To100Pct == (x))   ||                             \
    (WdtRefresh0To50PctAnd75To100Pct == (x))    ||                             \
    (WdtRefresh50To100Pct == (x))               ||                             \
    (WdtRefresh0To25PctAnd50To100Pct == (x))    ||                             \
    (WdtRefresh25To100Pct == (x))               ||                             \
    (WdtRefresh0To100Pct == (x)))

/*!< Parameter validity check for event request type */
#define IS_VALID_EVENT_REQUEST_TYPE(x)                                         \
(   (WdtTriggerInterruptRequest == (x))         ||                             \
    (WdtTriggerResetRequest == (x)))

/*!< Parameter validity check for flag type */
#define IS_VALID_FLAG_TYPE(x)                                                  \
(   (WdtFlagCountUnderflow == (x))              ||                             \
    (WdtFlagRefreshError == (x)))

/*!< WDT_RR register refresh key */
#define WDT_REFRESH_START_KEY                   ((uint16_t)0x0123)
#define WDT_REFRESH_END_KEY                     ((uint16_t)0x3210)

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
 *******************************************************************************
 ** \brief Initialize WDT function
 **
 ** \param [in] pstcWdtInit             Pointer to WDT init configuration
 ** \arg See the struct #stc_wdt_init_t
 **
 ** \retval Ok                          Process successfully done
 ** \retval Error                       Parameter error
 **
 ******************************************************************************/
en_result_t WDT_Init(const stc_wdt_init_t *pstcWdtInit)
{
    en_result_t enRet = Ok;
    uint32_t regTemp;

    if (NULL == pstcWdtInit)
    {
        enRet = Error;
    }
    else
    {
        /* Check parameters */
        DDL_ASSERT(IS_VALID_COUNT_CYCLE(pstcWdtInit->enCountCycle));
        DDL_ASSERT(IS_VALID_CLOCK_DIV(pstcWdtInit->enClkDiv));
        DDL_ASSERT(IS_VALID_ALLOW_REFRESH_RANGE(pstcWdtInit->enRefreshRange));
        DDL_ASSERT(IS_FUNCTIONAL_STATE(pstcWdtInit->enSleepModeCountEn));
        DDL_ASSERT(IS_VALID_EVENT_REQUEST_TYPE(pstcWdtInit->enRequestType));

        /* software start mode */
        regTemp = ((((uint32_t)pstcWdtInit->enRequestType) << 31)            | \
                (((uint32_t)(bool)(!pstcWdtInit->enSleepModeCountEn)) << 16) | \
                (((uint32_t)pstcWdtInit->enRefreshRange) << 8)               | \
                (((uint32_t)pstcWdtInit->enClkDiv) << 4)                     | \
                ((uint32_t)pstcWdtInit->enCountCycle));
        /* store the new value */
        M4_WDT->CR = regTemp;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief WDT refresh counter(First refresh start count when software start)
 **
 ** \param [in] None
 **
 ** \retval Ok                          Process successfully done
 **
 ******************************************************************************/
en_result_t WDT_RefreshCounter(void)
{
    en_result_t enRet = Ok;

    M4_WDT->RR = WDT_REFRESH_START_KEY;
    M4_WDT->RR = WDT_REFRESH_END_KEY;

    return enRet;
}

/**
 *******************************************************************************
 ** \brief Get WDT counter current count value
 **
 ** \param [in] None
 **
 ** \retval uint16_t                    WDT counter current count value
 **
 ******************************************************************************/
uint16_t WDT_GetCountValue(void)
{
    return ((uint16_t)M4_WDT->SR_f.CNT);
}

/**
 *******************************************************************************
 ** \brief Get WDT flag status
 **
 ** \param [in] enFlag                  WDT flag type
 ** \arg WdtFlagCountUnderflow          Count underflow flag
 ** \arg WdtFlagRefreshError            Refresh error flag
 **
 ** \retval Set                         Flag is set
 ** \retval Reset                       Flag is reset
 **
 ******************************************************************************/
en_flag_status_t WDT_GetFlag(en_wdt_flag_type_t enFlag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_FLAG_TYPE(enFlag));

    switch (enFlag)
    {
        case WdtFlagCountUnderflow:
            enFlagSta = (en_flag_status_t)M4_WDT->SR_f.UDF;
            break;
        case WdtFlagRefreshError:
            enFlagSta = (en_flag_status_t)M4_WDT->SR_f.REF;
            break;
        default:
            break;
    }

    return enFlagSta;
}

/**
 *******************************************************************************
 ** \brief Clear WDT flag status
 **
 ** \param [in] enFlag                  WDT flag type
 ** \arg WdtFlagCountUnderflow          Count underflow flag
 ** \arg WdtFlagRefreshError            Refresh error flag
 **
 ** \retval Ok                          Process successfully done
 **
 ******************************************************************************/
en_result_t WDT_ClearFlag(en_wdt_flag_type_t enFlag)
{
    en_result_t enRet = Ok;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_FLAG_TYPE(enFlag));

    switch (enFlag)
    {
        case  WdtFlagCountUnderflow:
            M4_WDT->SR_f.UDF = 0u;
            break;
        case WdtFlagRefreshError:
            M4_WDT->SR_f.REF = 0u;
            break;
        default:
            break;
    }

    return enRet;
}

//@} // WdtGroup

#endif /* DDL_WDT_ENABLE */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
