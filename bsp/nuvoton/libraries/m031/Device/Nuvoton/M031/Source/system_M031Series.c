/**************************************************************************//**
 * @file     system_M031Series.c
 * @version  V2.00
 * $Revision: 5 $
 * $Date: 18/07/19 1:44p $
 * @brief    M031 Series System Setting Source File
 *
 * @note
 * SPDX-License-Identifier: Apache-2.0
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include "NuMicro.h"



/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock  = __HSI;              /*!< System Clock Frequency (Core Clock) */
uint32_t CyclesPerUs      = (__HSI / 1000000);  /*!< Cycles per micro second             */
uint32_t PllClock         = __HSI;              /*!< PLL Output Clock Frequency          */
const uint32_t gau32ClkSrcTbl[] = {__HXT, __LXT, __HSI, __LIRC, __HIRC, 0UL, 0UL, __HIRC};


/**
 * @brief    Update the Variable SystemCoreClock
 *
 * @param    None
 *
 * @return   None
 *
 * @details  This function is used to update the variable SystemCoreClock
 *           and must be called whenever the core clock is changed.
 */
void SystemCoreClockUpdate(void)
{
    uint32_t u32Freq, u32ClkSrc;
    uint32_t u32HclkDiv;

    u32ClkSrc = CLK->CLKSEL0 & CLK_CLKSEL0_HCLKSEL_Msk;

    /* Update PLL Clock */
    PllClock = CLK_GetPLLClockFreq();

    if(u32ClkSrc != CLK_CLKSEL0_HCLKSEL_PLL)
    {
        /* Use the clock sources directly */
        u32Freq = gau32ClkSrcTbl[u32ClkSrc];
    }
    else
    {
        /* Use PLL clock */
        u32Freq = PllClock;
    }

    u32HclkDiv = (CLK->CLKDIV0 & CLK_CLKDIV0_HCLKDIV_Msk) + 1;

    /* Update System Core Clock */
    SystemCoreClock = u32Freq / u32HclkDiv;

    CyclesPerUs = (SystemCoreClock + 500000) / 1000000;
}


/**
 * @brief    System Initialization
 *
 * @param    None
 *
 * @return   None
 *
 * @details  The necessary initialization of system. Global variables are forbidden here.
 */
void SystemInit(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set HXTGain Level dependend on HXT Frequency */
    CLK->PWRCTL = CLK->PWRCTL & ~CLK_PWRCTL_HXTGAIN_Msk;
    if ((__HXT >= FREQ_4MHZ) && (__HXT < FREQ_8MHZ))
    {
        CLK->PWRCTL |= (1 << CLK_PWRCTL_HXTGAIN_Pos);
    }
    else if ((__HXT >= FREQ_8MHZ) && (__HXT < FREQ_12MHZ))
    {
        CLK->PWRCTL |= (2 << CLK_PWRCTL_HXTGAIN_Pos);
    }
    else if ((__HXT >= FREQ_12MHZ) && (__HXT < FREQ_16MHZ))
    {
        CLK->PWRCTL |= (3 << CLK_PWRCTL_HXTGAIN_Pos);
    }
    else if ((__HXT >= FREQ_16MHZ) && (__HXT < FREQ_24MHZ))
    {
        CLK->PWRCTL |= (4 << CLK_PWRCTL_HXTGAIN_Pos);
    }
    else
    {
        CLK->PWRCTL |= (7 << CLK_PWRCTL_HXTGAIN_Pos);
    }

    /* Lock protected registers */
    SYS_LockReg();
}

#if USE_ASSERT

/**
 * @brief      Assert Error Message
 *
 * @param[in]  file  the source file name
 * @param[in]  line  line number
 *
 * @return     None
 *
 * @details    The function prints the source file name and line number where
 *             the ASSERT_PARAM() error occurs, and then stops in an infinite loop.
 */
void AssertError(uint8_t * file, uint32_t line)
{

    printf("[%s] line %d : wrong parameters.\r\n", file, line);

    /* Infinite loop */
    while(1) ;
}
#endif
