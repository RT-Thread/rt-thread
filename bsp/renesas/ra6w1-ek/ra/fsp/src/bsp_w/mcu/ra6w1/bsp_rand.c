/*
* Copyright (c) 2020 - 2026 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "bsp_api.h"
#include "bsp_rand.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Functions
 **********************************************************************************************************************/

uint32_t prng_rand (void)
{
    uint32_t old_value, new_value;

    HW_ACC->PRNG_OP_EN_REG = 1U;
    old_value              = HW_ACC->PRNG_REG_CAL_VAL;

    do
    {
        HW_ACC->PRNG_REQ_CLR_REG = HW_ACC_PRNG_REQ_CLR_REG_PRNG_REQ_GET_Msk;
        new_value                = HW_ACC->PRNG_REG_CAL_VAL;

        if ((new_value == 0) && (old_value == 0))
        {
            /* Sometimes we hang indefinitely in this do-while loop (new_value is always zero, just as old_value).
             * It is reproducible without critical sections for a sequence like:
             *
             * srand(rand());
             * rand();
             *
             * It seems to be a HW design issue. This workaround solves it as far as I can test.
             * PRNG has not been revised, so it should behave in the same way for both AA and BA hardware revisions.
             * Note: adding busy-wait loops before/after rand()/srand() doesn't seem to help..
             * TODO:
             * - How can we confirm that previous PRNG operation is finished and we can issue next one?
             */
            HW_ACC->PRNG_REQ_CLR_REG = HW_ACC_PRNG_REQ_CLR_REG_PRNG_REQ_CLR_Msk;
        }
    } while (new_value == old_value);

    HW_ACC->PRNG_OP_EN_REG = 0;

    return new_value;
}

uint32_t trng_rand(void)
{
    uint32_t val = 0;

    if (!trng_init_regs())
    {
        return 0;
    }

    for (int tries = 0; tries < TRNG_RETRY_LIMIT; tries++)
    {
        if (trng_is_valid())
        {
            /* Clear up the interrupt status register */
            CC312->CC312_RNG_ICR_REG = ~0UL;
            val = CC312->CC312_EHR_DATA_0_REG;
            goto out;
        }

        /* Clear interrupt/status and try again */
        CC312->CC312_RNG_ICR_REG = ~0UL;
    }

out:

    /* Disable signal for the random source */
    CC312->CC312_RND_SOURCE_ENABLE_REG = 0;

    /* Disable the HW RNG clock */
    CC312->CC312_RNG_CLK_ENABLE_REG = 0;

    return val;
}

bool trng_init_regs (void)
{
    int poll_retry_limit = 0;

    /* Reset the RNG block */
    CC312->CC312_RNG_SW_RESET_REG = 0x1;

    do
    {
        /* enable the HW RNG clock */
        CC312->CC312_RNG_CLK_ENABLE_REG = 1;

        /* Set the number of rng_clk cycles between two consecutive samples.
         * If the Von-Neumann is bypassed, the minimum value for sample counter
         * must not be less than decimal seventeen - set to 20 dec
         */
        CC312->CC312_SAMPLE_CNT1_REG = TRNG_DEF_SAMPLES_CNT;

        if (++poll_retry_limit == TRNG_REG_POLL_RETRY_LIMIT)
        {
            return false;
        }

        /* Enable the HW RNG clock and set sample counter value until it is set correctly */
    } while (CC312->CC312_SAMPLE_CNT1_REG != TRNG_DEF_SAMPLES_CNT);

    /* Set the length of the oscillator ring to longest possible length - 3 */
    CC312->CC312_TRNG_CONFIG_REG_b.CC312_RND_SRC_SEL = 3;

    /* Bypass auto correlate, VNC and CRNGT are not bypassed and kept activated */
    CC312->CC312_TRNG_DEBUG_CONTROL_REG_b.CC312_VNC_BYPASS = 1;
    CC312->CC312_TRNG_DEBUG_CONTROL_REG_b.CC312_TRNG_CRNGT_BYPASS = 0;
    CC312->CC312_TRNG_DEBUG_CONTROL_REG_b.CC312_AUTO_CORRELATE_BYPASS = 1;

    /* Enable signal for the random source */
    CC312->CC312_RND_SOURCE_ENABLE_REG = 1;

    return true;
}

bool trng_is_valid (void)
{
    int poll_retry_limit = 0;

    while ((CC312->CC312_TRNG_VALID_REG != 1) &&
           (CC312->CC312_RNG_ISR_REG_b.CC312_RNG_ISR_EHR_VALID != 1))
    {
        if (++poll_retry_limit == TRNG_REG_POLL_RETRY_LIMIT)
        {
            return false;
        }
    }

    if (CC312->CC312_RNG_ISR_REG_b.CC312_RNG_ISR_AUTOCORR_ERR != 0)
    {
        return false;
    }

    poll_retry_limit = 0;

    while ((CC312->CC312_EHR_DATA_0_REG == 0x0) || (CC312->CC312_EHR_DATA_0_REG == 0x80000000))
    {
        if (++poll_retry_limit == TRNG_REG_POLL_RETRY_LIMIT)
        {
            return false;
        }
    }

    return true;
}

/*******************************************************************************************************************//**
 * Implementation of srand() function from standard C library.
 *
 * @param[in] seed    A seed value to use for a new sequence of pseudo-random integers to be returned by rand(). These
 *                    sequences are repeatable by calling srand() with the same seed value.
 *
 * @note RA6W1 PRNG is using polynomial calculation, which is similar to CRC. Providing the same seed to PRNG after POR
 *       boot (not SW reset), results in PRNG generating a deterministic sequence (the same pattern). However PRNG seed
 *       is designed to accumulate the current calculation without resetting the poly calculation. Hence to implement
 *       proper standard C library srand() semantics, need to use hardware CRC/SHA/AES instead of PRNG.
 **********************************************************************************************************************/
void srand (unsigned seed)
{
    uint32_t prng_seed = (uint32_t) seed & HW_ACC_PRNG_SEED_REG_PRNG_SEED_VAL_Msk;

    /* Seeding prng with a 0 not allowed because:
     * - causes constant 0 output from prng
     * - causes infinite loop in prng_rand() due to constant 0 output
     */
    if (prng_seed == 0U)
    {
        prng_seed = 1U;
    }

    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;
    HW_ACC->PRNG_OP_EN_REG    = 1U;
    HW_ACC->PRNG_PAR_TYPE_REG = PRNG_PAR_TYPE_32_BITS;
    HW_ACC->PRNG_SEED_REG = prng_seed;
    HW_ACC->PRNG_REQ_CLR_REG  = HW_ACC_PRNG_REQ_CLR_REG_PRNG_REQ_CLR_Msk;
    HW_ACC->PRNG_OP_EN_REG    = 0U;
    FSP_CRITICAL_SECTION_EXIT;
}

/*******************************************************************************************************************//**
 * Implementation of rand() function from standard C library.
 *
 * @retval a pseudo-random integer in the range 0 to RAND_MAX inclusive.
 * @note This function is not reentrant.
 **********************************************************************************************************************/
int rand (void)
{
    return (int) (prng_rand() % (((uint32_t) RAND_MAX) + 1U));
}
