/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_swdt.c
 **
 ** A detailed description is available at
 ** @link SwdtGroup Special Watchdog Counter description @endlink
 **
 **   - 2018-10-16  CDT  First version for Device Driver Library of SWDT.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_swdt.h"
#include "hc32f460_utility.h"

#if (DDL_SWDT_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup SwdtGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*!< Parameter valid check for flag type */
#define IS_VALID_FLAG_TYPE(x)                                                  \
(   (SwdtFlagCountUnderflow == (x))             ||                             \
    (SwdtFlagRefreshError == (x)))

/*!< SWDT_RR register refresh key */
#define SWDT_REFRESH_START_KEY                  ((uint16_t)0x0123)
#define SWDT_REFRESH_END_KEY_                   ((uint16_t)0x3210)

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
 ** \brief SWDT refresh counter
 **
 ** \param [in] None
 **
 ** \retval Ok                          Process successfully done
 **
 ******************************************************************************/
en_result_t SWDT_RefreshCounter(void)
{
    en_result_t enRet = Ok;

    M4_SWDT->RR = SWDT_REFRESH_START_KEY;
    M4_SWDT->RR = SWDT_REFRESH_END_KEY_;

    return enRet;
}

/**
 *******************************************************************************
 ** \brief Get SWDT counter current count value
 **
 ** \param [in] None
 **
 ** \retval uint16_t                    SWDT counter current count value
 **
 ******************************************************************************/
uint16_t SWDT_GetCountValue(void)
{
    return ((uint16_t)M4_SWDT->SR_f.CNT);
}

/**
 *******************************************************************************
 ** \brief Get SWDT flag status
 **
 ** \param [in] enFlag                  SWDT flag type
 ** \arg SwdtFlagCountUnderflow         Count underflow flag
 ** \arg SwdtFlagRefreshError           Refresh error flag
 **
 ** \retval Set                         Flag is set
 ** \retval Reset                       Flag is reset
 **
 ******************************************************************************/
en_flag_status_t SWDT_GetFlag(en_swdt_flag_type_t enFlag)
{
    en_flag_status_t enFlagSta = Reset;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_FLAG_TYPE(enFlag));

    switch (enFlag)
    {
        case SwdtFlagCountUnderflow:
            enFlagSta = (en_flag_status_t)M4_SWDT->SR_f.UDF;
            break;
        case SwdtFlagRefreshError:
            enFlagSta = (en_flag_status_t)M4_SWDT->SR_f.REF;
            break;
        default:
            break;
    }

    return enFlagSta;
}

/**
 *******************************************************************************
 ** \brief Clear SWDT flag status
 **
 ** \param [in] enFlag                  SWDT flag type
 ** \arg SwdtFlagCountUnderflow         Count underflow flag
 ** \arg SwdtFlagRefreshError           Refresh error flag
 **
 ** \retval Ok                          Process successfully done
 **
 ******************************************************************************/
en_result_t SWDT_ClearFlag(en_swdt_flag_type_t enFlag)
{
    en_result_t enRet = Ok;

    /* Check parameters */
    DDL_ASSERT(IS_VALID_FLAG_TYPE(enFlag));

    switch (enFlag)
    {
        case SwdtFlagCountUnderflow:
            M4_SWDT->SR_f.UDF = 0u;
            break;
        case SwdtFlagRefreshError:
            M4_SWDT->SR_f.REF = 0u;
            break;
        default:
            break;
    }

    return enRet;
}

//@} // SwdtGroup

#endif /* DDL_SWDT_ENABLE */

/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
