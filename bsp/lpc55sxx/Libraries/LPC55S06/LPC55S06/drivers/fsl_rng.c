/*
 * Copyright 2017, 2019, 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_rng.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.rng_1"
#endif

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Prototypes
 *******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
static void rng_accumulateEntropy(RNG_Type *base)
{
    uint32_t minChiSq;
    uint32_t maxChiSq;

    /* Steps to accumulate entropy, more info can be found in LPC55SXX UM*/

    /* Select fourth clock on which to compute CHI SQUARE statistics*/
    base->COUNTER_CFG = (base->COUNTER_CFG & ~RNG_COUNTER_CFG_CLOCK_SEL_MASK) | RNG_COUNTER_CFG_CLOCK_SEL(4U);

    /* Activate CHI computing */
    base->ONLINE_TEST_CFG = RNG_ONLINE_TEST_CFG_ACTIVATE(1U);

    /* Read min chi squared value, on power on should be higher than max chi squared value */
    minChiSq = ((base->ONLINE_TEST_VAL & RNG_ONLINE_TEST_VAL_MIN_CHI_SQUARED_MASK) >>
                RNG_ONLINE_TEST_VAL_MIN_CHI_SQUARED_SHIFT);

    /* Read max chi squared value */
    maxChiSq = ((base->ONLINE_TEST_VAL & RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_MASK) >>
                RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_SHIFT);

    /* Wait until minChiSq decreases and become smaller than maxChiSq*/
    while (minChiSq > (maxChiSq - 1U))
    {
        maxChiSq = ((base->ONLINE_TEST_VAL & RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_MASK) >>
                    RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_SHIFT);
        minChiSq = ((base->ONLINE_TEST_VAL & RNG_ONLINE_TEST_VAL_MIN_CHI_SQUARED_MASK) >>
                    RNG_ONLINE_TEST_VAL_MIN_CHI_SQUARED_SHIFT);
    }
}

/*!
 * @brief Gets a entry data from the RNG.
 *
 * This function gets an entropy data from RNG.
 */
static uint32_t rng_readEntropy(RNG_Type *base)
{
    uint32_t data;
    uint32_t refreshCnt, maxChiSq, tmpShift4x;

    /* Activate CHI computing */
    base->ONLINE_TEST_CFG = RNG_ONLINE_TEST_CFG_ACTIVATE(1);

    /* Wait for refresh count become 31 to refill fresh entropy since last read of random number*/
    do
    {
        refreshCnt = ((base->COUNTER_VAL & RNG_COUNTER_VAL_REFRESH_CNT_MASK) >> RNG_COUNTER_VAL_REFRESH_CNT_SHIFT);
    } while (refreshCnt < 31U);

    /* reading RANDOM_NUMBER register will reset refCnt to 0 */
    data = base->RANDOM_NUMBER;

    /* Perform CHI computing by checking max chi squared value */
    /* Wait until maxChiSq become smaller or equal than 4, then next random number can be read*/
    maxChiSq = ((base->ONLINE_TEST_VAL & RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_MASK) >>
                RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_SHIFT);

    while (maxChiSq > 4U)
    {
        /* Deactivate CHI computing to reset*/
        base->ONLINE_TEST_CFG = RNG_ONLINE_TEST_CFG_ACTIVATE(0);

        /* read Shift4x register, if is less than 7 increment it and then start accumulating entropy again */
        tmpShift4x = ((base->COUNTER_CFG & RNG_COUNTER_CFG_SHIFT4X_MASK) >> RNG_COUNTER_CFG_SHIFT4X_SHIFT);
        if (tmpShift4x < 7U)
        {
            tmpShift4x++;
            base->COUNTER_CFG =
                (base->COUNTER_CFG & ~RNG_COUNTER_CFG_SHIFT4X_MASK) | RNG_COUNTER_CFG_SHIFT4X(tmpShift4x);
        }
        rng_accumulateEntropy(base);

        maxChiSq = ((base->ONLINE_TEST_VAL & RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_MASK) >>
                    RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_SHIFT);
    }

    return data;
}

void RNG_Init(RNG_Type *base)
{
    uint32_t maxChiSq, tmpShift4x;

    /* Clear ring oscilator disable bit*/
    PMC->PDRUNCFGCLR0 = PMC_PDRUNCFG0_PDEN_RNG_MASK;
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_EnableClock(kCLOCK_Rng);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(kRNG_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

    /* Turn on CHI Squared test */
    /* Activate CHI computing and wait until min chi squared become smaller than max chi squared */
    rng_accumulateEntropy(base);

    maxChiSq = ((base->ONLINE_TEST_VAL & RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_MASK) >>
                RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_SHIFT);

    /* When maxChiSq is bigger than 4 its assumed there is not enough entropy and previous steps are repeated */
    /* When maxChiSq is 4 or less initialization is complete and random number can be read*/
    while (maxChiSq > 4U)
    {
        /* Deactivate CHI coputing to reset*/
        base->ONLINE_TEST_CFG = RNG_ONLINE_TEST_CFG_ACTIVATE(0);

        /* read Shift4x register, if is less than 7 increment it and then start accumulating entropy again */
        tmpShift4x = ((base->COUNTER_CFG & RNG_COUNTER_CFG_SHIFT4X_MASK) >> RNG_COUNTER_CFG_SHIFT4X_SHIFT);
        if (tmpShift4x < 7U)
        {
            tmpShift4x++;
            base->COUNTER_CFG =
                (base->COUNTER_CFG & ~RNG_COUNTER_CFG_SHIFT4X_MASK) | RNG_COUNTER_CFG_SHIFT4X(tmpShift4x);
        }
        rng_accumulateEntropy(base);

        maxChiSq = ((base->ONLINE_TEST_VAL & RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_MASK) >>
                    RNG_ONLINE_TEST_VAL_MAX_CHI_SQUARED_SHIFT);
    }
}

void RNG_Deinit(RNG_Type *base)
{
    /* Set ring oscilator disable bit*/
    PMC->PDRUNCFGSET0 = PMC_PDRUNCFG0_PDEN_RNG_MASK;

#if !(defined(FSL_SDK_DISABLE_DRIVER_RESET_CONTROL) && FSL_SDK_DISABLE_DRIVER_RESET_CONTROL)
    /* Reset the module. */
    RESET_PeripheralReset(kRNG_RST_SHIFT_RSTn);
#endif /* FSL_SDK_DISABLE_DRIVER_RESET_CONTROL */

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    CLOCK_DisableClock(kCLOCK_Rng);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

status_t RNG_GetRandomData(RNG_Type *base, void *data, size_t dataSize)
{
    status_t result = kStatus_Fail;
    uint32_t random32;
    uint32_t randomSize;
    uint8_t *pRandom;
    uint8_t *pData = (uint8_t *)data;
    uint32_t i;

    /* Check input parameters.*/
    if (!((base != NULL) && (data != NULL) && (dataSize != 0U)))
    {
        result = kStatus_InvalidArgument;
    }
    else
    {
        /* Check that ring oscilator is enabled */
        if (0U == (PMC->PDRUNCFG0 & PMC_PDRUNCFG0_PDEN_RNG_MASK))
        {
            do
            {
                /* Read Entropy.*/
                random32 = rng_readEntropy(base);
                pRandom  = (uint8_t *)&random32;

                if (dataSize < sizeof(random32))
                {
                    randomSize = dataSize;
                }
                else
                {
                    randomSize = sizeof(random32);
                }

                for (i = 0; i < randomSize; i++)
                {
                    *pData++ = *pRandom++;
                }

                dataSize -= randomSize;
            } while (dataSize > 0U);

            result = kStatus_Success;
        }
    }

    return result;
}
