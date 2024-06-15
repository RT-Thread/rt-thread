/******************************************************************************
*
* Copyright (C) 2017 Texas Instruments Incorporated - http://www.ti.com/
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
*  Redistributions of source code must retain the above copyright
*  notice, this list of conditions and the following disclaimer.
*
*  Redistributions in binary form must reproduce the above copyright
*  notice, this list of conditions and the following disclaimer in the
*  documentation and/or other materials provided with the
*  distribution.
*
*  Neither the name of Texas Instruments Incorporated nor the names of
*  its contributors may be used to endorse or promote products derived
*  from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include <stdint.h>
#include <msp.h>

/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define __SYSTEM_CLOCK    (16000000ul)

/* Update frequency to match the crystal frequency on your board */
#define XTAL_FREQ         (25000000ul)

/*----------------------------------------------------------------------------
  Clock Variable definitions
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = __SYSTEM_CLOCK; /*!< System Clock Frequency (Core Clock)*/


/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/
void SystemCoreClockUpdate(void)             /* Get Core Clock Frequency      */
{
    uint32_t getClockDivider;
    uint32_t getPLLMIntValue;
    uint32_t getPLLNValue;
    uint32_t getPLLQValue;

    /* Update the default System Clock value for MSP432E4x devices */
    SystemCoreClock = __SYSTEM_CLOCK;

    if ((SYSCTL->RSCLKCFG & SYSCTL_RSCLKCFG_USEPLL) == SYSCTL_RSCLKCFG_USEPLL)
    {
        getClockDivider = (SYSCTL->RSCLKCFG & SYSCTL_RSCLKCFG_PSYSDIV_M) >> SYSCTL_RSCLKCFG_PSYSDIV_S;

        getPLLMIntValue = (SYSCTL->PLLFREQ0 & SYSCTL_PLLFREQ0_MINT_M) >> SYSCTL_PLLFREQ0_MINT_S;
        getPLLNValue = (SYSCTL->PLLFREQ1 & SYSCTL_PLLFREQ1_N_M) >> SYSCTL_PLLFREQ1_N_S;
        getPLLQValue = (SYSCTL->PLLFREQ1 & SYSCTL_PLLFREQ1_Q_M) >> SYSCTL_PLLFREQ1_Q_S;

        if ((SYSCTL->RSCLKCFG & SYSCTL_RSCLKCFG_PLLSRC_M) == SYSCTL_RSCLKCFG_PLLSRC_PIOSC)
        {
            SystemCoreClock = (__SYSTEM_CLOCK * (getPLLMIntValue)) / ((getPLLNValue + 1) * (getPLLQValue + 1));
            SystemCoreClock = SystemCoreClock / (getClockDivider + 1);
        }
        else if ((SYSCTL->RSCLKCFG & SYSCTL_RSCLKCFG_PLLSRC_M) == SYSCTL_RSCLKCFG_PLLSRC_MOSC)
        {
            SystemCoreClock = (XTAL_FREQ * (getPLLMIntValue)) / ((getPLLNValue + 1) * (getPLLQValue + 1));
            SystemCoreClock = SystemCoreClock / (getClockDivider + 1);
        }
    }
    else
    {
        getClockDivider = (SYSCTL->RSCLKCFG & SYSCTL_RSCLKCFG_OSYSDIV_M) >> SYSCTL_RSCLKCFG_OSYSDIV_S;

        if ((SYSCTL->RSCLKCFG & SYSCTL_RSCLKCFG_OSCSRC_M) == SYSCTL_RSCLKCFG_OSCSRC_PIOSC)
        {
            SystemCoreClock = __SYSTEM_CLOCK / (getClockDivider + 1);
        }
        else if ((SYSCTL->RSCLKCFG & SYSCTL_RSCLKCFG_OSCSRC_M) == SYSCTL_RSCLKCFG_OSCSRC_MOSC)
        {
            SystemCoreClock = XTAL_FREQ / (getClockDivider + 1);
        }
    }
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit(void)
{
#if (__FPU_USED == 1)
    SCB->CPACR |= ((3UL << 10 * 2) |               /* set CP10 Full Access */
                   (3UL << 11 * 2));               /* set CP11 Full Access */
#endif

#ifdef UNALIGNED_SUPPORT_DISABLE
    SCB->CCR |= SCB_CCR_UNALIGN_TRP_Msk;
#endif

    SystemCoreClock = __SYSTEM_CLOCK;

}
