/**************************************************************************//**
 * @file     rng.c
 * @version  V3.00
 * @brief    Show how to get true random number.
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <stdio.h>
#include "NuMicro.h"

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup RNG_Driver RNG Driver
  @{
*/


/** @addtogroup RNG_EXPORTED_FUNCTIONS RNG Exported Functions
  @{
*/

typedef enum _RNG_KEY_SIZE
{
    KEY_128 = 0,
    KEY_192 = 2,
    KEY_224 = 3,
    KEY_233 = 4,
    KEY_255 = 5,
    KEY_256 = 6,
    KEY_283 = 7,
    KEY_384 = 8,
    KEY_409 = 9,
    KEY_512 = 10,
    KEY_521 = 11,
    KEY_571 = 12

} eRNG_SZ;


/**
 *  @brief      Open random number generator
 *
 *  @return      0  Successful
 *              -1  Failed
 *
 *  @details    The function is used to disable rng interrupt.
 */
int32_t RNG_Open(void)
{
    int32_t i;
    int32_t timeout = 0x1000000;

    /* Basic Configuration */
    CLK->AHBCLK  |= CLK_AHBCLK_CRPTCKEN_Msk;
    CLK->APBCLK1 |= CLK_APBCLK1_TRNGCKEN_Msk;
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;

    RTC->LXTCTL |= (RTC_LXTCTL_C32KSEL_Msk | RTC_LXTCTL_LIRC32KEN_Msk); //To use LIRC32K

    TRNG->ACT |= TRNG_ACT_ACT_Msk;
    /* Waiting for ready */
    i = 0;
    while((TRNG->CTL & TRNG_CTL_READY_Msk) == 0)
    {
        if(i++ > timeout)
        {
            /* TRNG ready timeout */
            return -1;
        }
    }

    TRNG->CTL = (0 << TRNG_CTL_CLKPSC_Pos);


    /* Enable SEEDGEN */
    TRNG->CTL |= (1 << 8);

    /* Waiting for seed ready */
    i = 0;
    while((TRNG->CTL & (1 << 9)) == 0)
    {
        if(i++ > timeout)
        {
            /* seed ready timeout */
            return -1;
        }
    }

    // Waiting for PRNG busy
    i = 0;
    while(CRPT->PRNG_CTL & (1 << 8))
    {
        if(i++ > timeout)
        {
            /* PRNG busy timeout */
            return -1;
        }
    }

    /* Set seed select to TRNG */
    CRPT->PRNG_CTL = CRPT_PRNG_CTL_SEEDSEL_Msk;

    /* Waiting for seed src ok */
    i = 0;
    while((CRPT->PRNG_CTL & CRPT_PRNG_CTL_SEEDSRC_Msk) == 0)
    {
        if(i++ > timeout)
        {
            /* PRNG src timeout */
            return -1; // Timeout
        }
    }

    /* Reload seed only at first time */
    CRPT->PRNG_CTL |= (PRNG_KEY_SIZE_256 << CRPT_PRNG_CTL_KEYSZ_Pos) | CRPT_PRNG_CTL_START_Msk | CRPT_PRNG_CTL_SEEDRLD_Msk;

    i = 0;
    while(CRPT->PRNG_CTL & CRPT_PRNG_CTL_BUSY_Msk)
    {
        if(i++ > timeout)
        {
            /* busy timeout */
            return -1;
        }
    }

    return 0;
}


/**
 *  @brief      Get random words
 *
 *  @param[in]  pu32Buf Buffer pointer to store the random number
 *
 *  @param[in]  nWords  Buffer size in word count. nWords must <= 8
 *
 *  @return     Word count of random number in buffer
 *
 *  @details    The function is used to generate random numbers
 */
int32_t RNG_Random(uint32_t *pu32Buf, int32_t nWords)
{
    int32_t i;
    int32_t timeout = 0x10000;

    /* Waiting for Busy */
    while(CRPT->PRNG_CTL & CRPT_PRNG_CTL_BUSY_Msk) {}

    if(nWords > 8)
        nWords = 8;

    /* Trig to generate seed 256 bits random number */
    CRPT->PRNG_CTL = (6 << CRPT_PRNG_CTL_KEYSZ_Pos) | CRPT_PRNG_CTL_START_Msk;

    while(CRPT->PRNG_CTL & CRPT_PRNG_CTL_BUSY_Msk)
    {
        if(timeout-- < 0)
            return 0;
    }

    for(i = 0; i < nWords; i++)
    {
        pu32Buf[i] = CRPT->PRNG_KEY[i];
    }

    return nWords;
}



/**
 *  @brief      To generate a key to KS SRAM for ECDSA.
 *
 *  @param[in]  u32KeySize  It could be PRNG_KEY_SIZE_128 ~ PRNG_KEY_SIZE_571
 *
 *  @param[in]  au32ECC_N   The N value of specified ECC curve.
 *
 *  @return     -1      Failed
 *              Others  The key number in KS SRAM
 *
 *  @details    The function is used to generate a key to KS SRAM for ECDSA.
 *              This key is necessary for ECDSA+Key Store function of ECC.
 */
int32_t RNG_ECDSA_Init(uint32_t u32KeySize, uint32_t au32ECC_N[18])
{
    int32_t i;
    int32_t timeout = 0x1000000;

    /* Basic Configuration */
    CLK->AHBCLK  |= CLK_AHBCLK_CRPTCKEN_Msk;
    CLK->APBCLK1 |= CLK_APBCLK1_TRNGCKEN_Msk;
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;

    RTC->LXTCTL |= (RTC_LXTCTL_C32KSEL_Msk | RTC_LXTCTL_LIRC32KEN_Msk); //To use LIRC32K

    TRNG->ACT |= TRNG_ACT_ACT_Msk;
    /* Waiting for ready */
    i = 0;
    while((TRNG->CTL & TRNG_CTL_READY_Msk) == 0)
    {
        if(i++ > timeout)
        {
            return -1; // Timeout
        }
    }

    TRNG->CTL = (0 << TRNG_CTL_CLKPSC_Pos);

    /* Reset seed select of PRNG */
    CRPT->PRNG_CTL = 0;


    /* Enable SEEDGEN */
    TRNG->CTL |= TRNG_CTL_SEEDGEN_Msk;

    /* Waiting for seed ready */
    i = 0;
    while((TRNG->CTL & TRNG_CTL_SEEDRDY_Msk) == 0)
    {
        if(i++ > timeout)
        {
            return -1; // Timeout
        }
    }

    // Waiting for PRNG busy
    i = 0;
    while(CRPT->PRNG_CTL & CRPT_PRNG_CTL_BUSY_Msk)
    {
        if(i++ > timeout)
        {
            return -1; // Timeout
        }
    }


    // Set seed select to TRNG
    CRPT->PRNG_CTL = 1 << CRPT_PRNG_CTL_SEEDSEL_Pos;

    // Waiting for seed src ok
    i = 0;
    while((CRPT->PRNG_CTL & CRPT_PRNG_CTL_SEEDSRC_Msk) == 0)
    {
        if(i++ > timeout)
        {
            return -1; // Timeout
        }
    }

    /* It is necessary to set ECC_N for ECDSA */
    for(i = 0; i < 18; i++)
        CRPT->ECC_N[i] = au32ECC_N[i];

    CRPT->PRNG_KSCTL = 0;

    /* Reload seed only at first time */
    CRPT->PRNG_CTL |= (u32KeySize << CRPT_PRNG_CTL_KEYSZ_Pos) |
                      CRPT_PRNG_CTL_START_Msk | CRPT_PRNG_CTL_SEEDRLD_Msk;


    i = 0;
    while(CRPT->PRNG_CTL & CRPT_PRNG_CTL_BUSY_Msk)
    {
        if(i++ > timeout)
        {
            return -1; // Timeout
        }
    }


    CRPT->PRNG_KSCTL = (KS_OWNER_ECC << CRPT_PRNG_KSCTL_OWNER_Pos) |
                       CRPT_PRNG_KSCTL_ECDSA_Msk |
                       (CRPT_PRNG_KSCTL_WDST_Msk) |
                       (KS_SRAM << CRPT_PRNG_KSCTL_WSDST_Pos);

    return 0;
}


/**
 *  @brief      To generate a key to KS SRAM for ECDSA.
 *
 *  @return     -1      Failed
 *              Others  The key number in KS SRAM
 *
 *  @details    The function is used to generate a key to KS SRAM for ECDSA.
 *              This key is necessary for ECDSA+Key Store function of ECC.
 */
int32_t RNG_ECDSA(uint32_t u32KeySize)
{
    int32_t timeout;
    int32_t i;

    /* Reload seed only at first time */
    CRPT->PRNG_CTL = (u32KeySize << CRPT_PRNG_CTL_KEYSZ_Pos) |
                     0xc0 |
                     CRPT_PRNG_CTL_START_Msk;

    timeout = 0x10000;
    i = 0;
    while(CRPT->PRNG_CTL & CRPT_PRNG_CTL_BUSY_Msk)
    {
        if(i++ > timeout)
        {
            //printf("busy timeout\n");
            return -1; // Timeout
        }
    }

    if(CRPT->PRNG_KSSTS & CRPT_PRNG_KSSTS_KCTLERR_Msk)
    {
        //printf("KCTLERR!\n");
        return -1;
    }

    return (CRPT->PRNG_KSSTS & CRPT_PRNG_KSCTL_NUM_Msk);
}



/**
 *  @brief      To generate a key to KS SRAM for ECDH.
 *
 *  @param[in]  u32KeySize  It could be PRNG_KEY_SIZE_128 ~ PRNG_KEY_SIZE_571
 *
 *  @param[in]  au32ECC_N   The N value of specified ECC curve.
 *
 *  @return     -1      Failed
 *              Others  The key number in KS SRAM
 *
 *  @details    The function is used to generate a key to KS SRAM for ECDH.
 *              This key is necessary for ECDH+Key Store function of ECC.
 */
int32_t RNG_ECDH_Init(uint32_t u32KeySize, uint32_t au32ECC_N[18])
{
    int32_t i;
    int32_t timeout = 0x1000000;

    /* Basic Configuration */
    CLK->AHBCLK  |= CLK_AHBCLK_CRPTCKEN_Msk;
    CLK->APBCLK1 |= CLK_APBCLK1_TRNGCKEN_Msk;
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;

    RTC->LXTCTL |= (RTC_LXTCTL_C32KSEL_Msk | RTC_LXTCTL_LIRC32KEN_Msk); //To use LIRC32K

    TRNG->ACT |= TRNG_ACT_ACT_Msk;
    /* Waiting for ready */
    i = 0;
    while((TRNG->CTL & TRNG_CTL_READY_Msk) == 0)
    {
        if(i++ > timeout)
        {
            /* TRNG ready timeout */
            return -1;
        }
    }

    TRNG->CTL = (0 << TRNG_CTL_CLKPSC_Pos);


    /* Enable SEEDGEN */
    TRNG->CTL |= TRNG_CTL_SEEDGEN_Msk;

    /* Waiting for seed ready */
    i = 0;
    while((TRNG->CTL & TRNG_CTL_SEEDRDY_Msk) == 0)
    {
        if(i++ > timeout)
        {
            /* seed ready timeout */
            return -1;
        }
    }

    /* Waiting for PRNG busy */
    i = 0;
    while(CRPT->PRNG_CTL & TRNG_CTL_SEEDGEN_Msk)
    {
        if(i++ > timeout)
        {
            /* PRNG busy timeout */
            return -1;
        }
    }



    /* Set seed select to TRNG */
    CRPT->PRNG_CTL = (1 << 6);

    // Waiting for seed src ok
    i = 0;
    while((CRPT->PRNG_CTL & (1 << 7)) == 0)
    {
        if(i++ > timeout)
        {
            /* PRNG src timeout */
            return -1;
        }
    }

    /* It is necessary to set ECC_N for ECDSA */
    for(i = 0; i < 18; i++)
        CRPT->ECC_N[i] = au32ECC_N[i];

    CRPT->PRNG_KSCTL = 0;

    /* Reload seed only at first time */
    CRPT->PRNG_CTL |= (u32KeySize << CRPT_PRNG_CTL_KEYSZ_Pos) |
                      CRPT_PRNG_CTL_START_Msk | CRPT_PRNG_CTL_SEEDRLD_Msk;


    i = 0;
    while(CRPT->PRNG_CTL & CRPT_PRNG_CTL_BUSY_Msk)
    {
        if(i++ > timeout)
        {
            /* busy timeout */
            return -1;
        }
    }

    CRPT->PRNG_KSCTL = (KS_OWNER_ECC << CRPT_PRNG_KSCTL_OWNER_Pos) |
                       (CRPT_PRNG_KSCTL_ECDH_Msk) |
                       (CRPT_PRNG_KSCTL_WDST_Msk) |
                       (KS_SRAM << CRPT_PRNG_KSCTL_WSDST_Pos);

    return 0;
}


/**
 *  @brief      To generate a key to KS SRAM for ECDH.
 *
 *  @return     -1      Failed
 *              Others  The key number in KS SRAM
 *
 *  @details    The function is used to generate a key to KS SRAM for ECDH.
 *              This key is necessary for ECDH+Key Store function of ECC.
 */
int32_t RNG_ECDH(uint32_t u32KeySize)
{
    int32_t timeout;
    int32_t i;

    /* Reload seed only at first time */
    CRPT->PRNG_CTL = (u32KeySize << CRPT_PRNG_CTL_KEYSZ_Pos) |
                     0xc0 |
                     CRPT_PRNG_CTL_START_Msk;

    timeout = 0x10000;
    i = 0;
    while(CRPT->PRNG_CTL & CRPT_PRNG_CTL_BUSY_Msk)
    {
        if(i++ > timeout)
            return -1;
    }

    if(CRPT->PRNG_KSSTS & CRPT_PRNG_KSSTS_KCTLERR_Msk)
        return -1;

    return (CRPT->PRNG_KSSTS & CRPT_PRNG_KSCTL_NUM_Msk);
}

/**@}*/ /* end of group RNG_EXPORTED_FUNCTIONS */

/**@}*/ /* end of group RNG_Driver */

/**@}*/ /* end of group Standard_Driver */

