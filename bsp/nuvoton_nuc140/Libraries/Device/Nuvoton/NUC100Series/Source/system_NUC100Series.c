/**************************************************************************//**
 * @file     system_NUC100Series.c
 * @version  V3.0
 * $Revision: 1 $
 * $Date: 14/12/08 11:47a $
 * @brief    NUC100 Series CMSIS System File
 *
 * @note
 * Copyright (C) 2014 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdint.h>
#include "NUC100Series.h"


/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock  = __HSI;             /*!< System Clock Frequency (Core Clock) */
uint32_t CyclesPerUs      = (__HSI / 1000000); /* Cycles per micro second */
uint32_t PllClock         = __HSI;             /*!< PLL Output Clock Frequency */
uint32_t gau32ClkSrcTbl[] = {__HXT, __LXT, __HSI, __LIRC, NULL, NULL, NULL, __HIRC};


/*----------------------------------------------------------------------------
  Clock functions
  This function is used to update the variable SystemCoreClock
  and must be called whenever the core clock is changed.
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate(void)             /* Get Core Clock Frequency      */
{
    uint32_t u32Freq, u32ClkSrc;
    uint32_t u32HclkDiv;

    /* Update PLL Clock */
    PllClock = CLK_GetPLLClockFreq();

    u32ClkSrc = CLK->CLKSEL0 & CLK_CLKSEL0_HCLK_S_Msk;

    if(u32ClkSrc != CLK_CLKSEL0_HCLK_S_PLL)
    {
        /* Use the clock sources directly */
        u32Freq = gau32ClkSrcTbl[u32ClkSrc];
    }
    else
    {
        /* Use PLL clock */
        u32Freq = PllClock;
    }

    u32HclkDiv = (CLK->CLKDIV & CLK_CLKDIV_HCLK_N_Msk) + 1;

    /* Update System Core Clock */
    SystemCoreClock = u32Freq / u32HclkDiv;

    CyclesPerUs = (SystemCoreClock + 500000) / 1000000;
}

/*---------------------------------------------------------------------------------------------------------*/
/* Function: SystemInit                                                                                    */
/*                                                                                                         */
/* Parameters:                                                                                             */
/*      None                                                                                               */
/*                                                                                                         */
/* Returns:                                                                                                */
/*      None                                                                                               */
/*                                                                                                         */
/* Description:                                                                                            */
/*      The necessary initialization of system.                                                           */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
void SystemInit(void)
{
}
