/*******************************************************************************
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd. All rights reserved.
 *
 * This software component is licensed by HDSC under BSD 3-Clause license
 * (the "License"); You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                    opensource.org/licenses/BSD-3-Clause
 */
/******************************************************************************/
/** \file hc32f460_trng.c
 **
 ** A detailed description is available at
 ** @link TrngGroup Trng description @endlink
 **
 **   - 2018-10-20  CDT First version for Device Driver Library of Trng.
 **
 ******************************************************************************/

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "hc32f460_trng.h"
#include "hc32f460_utility.h"

#if (DDL_TRNG_ENABLE == DDL_ON)

/**
 *******************************************************************************
 ** \addtogroup TrngGroup
 ******************************************************************************/
//@{

/*******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/*******************************************************************************
 * Local pre-processor symbols/macros ('#define')
 ******************************************************************************/
/*! Parameter validity check for TRNG load control. */
#define IS_TRNG_LOAD_CTRL(CTRL)                                                 \
(   ((CTRL) == TrngLoadNewInitValue_Enable)     ||                              \
    ((CTRL) == TrngLoadNewInitValue_Disable))

/*! Parameter validity check for TRNG shift count. */
#define IS_TRNG_SHIFT_COUNT(COUNT)                                              \
(   ((COUNT) == TrngShiftCount_32)              ||                              \
    ((COUNT) == TrngShiftCount_64)              ||                              \
    ((COUNT) == TrngShiftCount_128)             ||                              \
    ((COUNT) == TrngShiftCount_256))


#define RANDOM_NUM_LENGTH                       (2u)

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
 ** \brief Initializes the TRNG.
 **
 ** \param [in] pstcInit                Pointer to TRNG initialization structure.
 ** \arg enLoadCtrl
 ** \- TrngLoadNewInitValue_Enable      Data register load new initial value before
 **                                     random number is generated.
 ** \- TrngLoadNewInitValue_Disable     Data register do not load new initial value
 **                                     before random number is generated.
 **
 ** \arg enShiftCount                   Shift count control bit when capturing random noise.
 ** \- TrngShiftCount_32                Shift 32 times.
 ** \- TrngShiftCount_64                Shift 64 times.
 ** \- TrngShiftCount_128               Shift 128 times.
 ** \- TrngShiftCount_256               Shift 256 times.
 **
 ** \retval Ok                          No error occurred.
 ** \retval ErrorInvalidParameter       Parameter error.
 **
 ******************************************************************************/
en_result_t TRNG_Init(const stc_trng_init_t *pstcInit)
{
    en_result_t enRet = ErrorInvalidParameter;

    if (NULL != pstcInit)
    {
        /* Parameter validity check */
        DDL_ASSERT(IS_TRNG_LOAD_CTRL(pstcInit->enLoadCtrl));
        DDL_ASSERT(IS_TRNG_SHIFT_COUNT(pstcInit->enShiftCount));

        /* Stop TRNG generating*/
        bM4_TRNG_CR_RUN = 0u;

        /* Turn off TRNG circuit */
        bM4_TRNG_CR_EN = 0u;

        M4_TRNG->MR_f.LOAD = pstcInit->enLoadCtrl;
        M4_TRNG->MR_f.CNT  = pstcInit->enShiftCount;

        enRet = Ok;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief  Deinitializes the TRNG.
 **
 ** \param  None.
 **
 ** \retval None.
 **
 ******************************************************************************/
void TRNG_DeInit(void)
{
    /* Stop TRNG generating*/
    bM4_TRNG_CR_RUN = 0u;

    /* Turn off TRNG circuit */
    bM4_TRNG_CR_EN = 0u;

    /* Set the value of all registers to the reset value. */
    M4_TRNG->CR  = 0u;
    M4_TRNG->MR  = 0x12ul;
    M4_TRNG->DR0 = 0x08000000ul;
    M4_TRNG->DR0 = 0x08000200ul;
}

/**
 *******************************************************************************
 ** \brief Start TRNG and generate random number.
 **
 ** \param [out] pu32Random             The destination address where the random
 **                                     number will be stored.
 ** \param [in] u8Length                Random number length(in word).
 **                                     TRNG generates two random numbers(2 words) at one time.
 **                                     u8Length >= 2, both random numbers will be read.
 **                                     u8Length < 2, only one random number will be read.
 ** \param [in] u32Timeout              Timeout value.
 **
 ** \retval Ok                          No error occurred.
 ** \retval ErrorTimeout                TRNG works timeout.
 ** \retval ErrorInvalidParameter       Parameter error.
 **
 ******************************************************************************/
en_result_t TRNG_Generate(uint32_t *pu32Random, uint8_t u8Length, uint32_t u32Timeout)
{
    en_result_t   enRet = ErrorInvalidParameter;
    uint32_t      u32TrngTimeout;
    __IO uint32_t u32TimeCount;

    if ((NULL != pu32Random) && (0u != u32Timeout) && (0u != u8Length))
    {
        /* 10 is the number of required instructions cycles for the below loop statement. */
        u32TrngTimeout = u32Timeout * (SystemCoreClock / 10u / 1000u);

        /* Turn on TRNG circuit. */
        bM4_TRNG_CR_EN = 1u;

        /* Start TRNG to generate random number. */
        bM4_TRNG_CR_RUN = 1u;

        /* wait generation done and check if timeout. */
        u32TimeCount = 0u;
        enRet = ErrorTimeout;
        while (u32TimeCount < u32TrngTimeout)
        {
            if (bM4_TRNG_CR_RUN == 0u)
            {
                enRet = Ok;
                break;
            }
            u32TimeCount++;
        }

        if (Ok == enRet)
        {
            /* read the random number. */
            pu32Random[0u] = M4_TRNG->DR0;
            if (u8Length >= RANDOM_NUM_LENGTH)
            {
                pu32Random[1u] = M4_TRNG->DR1;
            }
        }

        /* Stop TRNG generating. */
        bM4_TRNG_CR_RUN = 0u;

        /* Turn off TRNG circuit. */
        bM4_TRNG_CR_EN = 0u;
    }

    return enRet;
}

/**
 *******************************************************************************
 ** \brief Start TRNG only.
 **
 ** \param  None.
 **
 ** \retval None.
 **
 ******************************************************************************/
void TRNG_StartIT(void)
{
    /* Turn on TRNG circuit. */
    bM4_TRNG_CR_EN = 1u;

    /* Start TRNG to generate random number. */
    bM4_TRNG_CR_RUN = 1u;
}

/**
 *******************************************************************************
 ** \brief  Get random number.
 **
 ** \param  [out] pu32Random            The destination address where the random
 **                                     number will be stored.
 ** \param [in] u8Length                Random number length(in word).
 **                                     TRNG generates two random numbers(2 words) at one time.
 **                                     u8Length >= 2, both random numbers will be read.
 **                                     u8Length < 2, only one random number will be read.
 **
 ** \retval None.
 **
 ******************************************************************************/
void TRNG_GetRandomNum(uint32_t *pu32Random, uint8_t u8Length)
{
    if ((NULL != pu32Random) && (0u != u8Length))
    {
        pu32Random[0u] = M4_TRNG->DR0;
        if (u8Length >= RANDOM_NUM_LENGTH)
        {
            pu32Random[1u] = M4_TRNG->DR1;
        }

        /* Stop TRNG generating */
        bM4_TRNG_CR_RUN = 0u;

        /* Turn off TRNG circuit */
        bM4_TRNG_CR_EN  = 0u;
    }
}

//@} // TrngGroup

#endif /* DDL_TRNG_ENABLE */

/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/
