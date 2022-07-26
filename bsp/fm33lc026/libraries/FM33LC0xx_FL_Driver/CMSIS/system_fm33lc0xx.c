/**************************************************************************//**
 * @file     system_fm33lc0xx.c
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File for
 *           Device FM33LC0XX
 * @version  V2.0.0
 * @date     15. Mar 2021
 *
 * @note
 *
 ******************************************************************************/
/* Copyright (c) 2012 ARM LIMITED

   All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#include "system_fm33lc0xx.h"

/* Clock Variable definitions ------------------------------------------------*/
uint32_t XTLFClock = XTLF_DEFAULT_VALUE;        /*!< External Low-freq Osc Clock Frequency (XTLF) */
uint32_t XTHFClock = XTHF_DEFAULT_VALUE;        /*!< External High-freq Osc Clock Frequency (XTHF) */
uint32_t SystemCoreClock = HCLK_DEFAULT_VALUE;  /*!< System Clock Frequency (Core Clock) */

/* Clock functions -----------------------------------------------------------*/
/**
 *  @brief Retrieve the PLL clock frequency
 *
 *  @retval PLL clock frequency
 */
static uint32_t SystemPLLClockUpdate(void)
{
    uint32_t clock = 0;

    /* Acquire PLL clock source */
    switch ((RCC->PLLCR >> 1) & 0x1)
    {
        case 0:
            switch ((RCC->RCHFCR >> 16) & 0xFU)
            {
                case 1: /* 16MHz */
                    clock = 16000000;
                    break;

                case 2: /* 24MHz */
                    clock = 24000000;
                    break;

                case 0: /* 8MHz */
                default:
                    clock = 8000000;
                    break;
            }
            break;

        case 1:
            clock = XTHFClock;
            break;
    }

    /* Acquire PLL prescaler */
    switch ((RCC->PLLCR >> 0x4) & 0x7)
    {
        case 0: /* input divided by 1 */
            clock /= 1;
            break;

        case 1: /* input divided by 2 */
            clock /= 2;
            break;

        case 2: /* input divided by 4 */
            clock /= 4;
            break;

        case 3: /* input divided by 8 */
            clock /= 8;
            break;

        case 4: /* input divided by 12 */
            clock /= 12;
            break;

        case 5: /* input divided by 16 */
            clock /= 16;
            break;

        case 6: /* input divided by 24 */
            clock /= 24;
            break;

        case 7: /* input divided by 32 */
            clock /= 32;
            break;
    }

    /* Acquire PLL multiplier and calculate PLL frequency */
    clock = clock * (((RCC->PLLCR >> 16) & 0x7F) + 1);

    /* Acquire PLL output channel(PLLx1 or PLLx2) */
    if ((RCC->PLLCR >> 3) & 0x1)
    {
        clock *= 2;
    }

    return clock;
}

/**
 *  @brief Update the core clock frequency variable: SystemCoreClock
 *
 */
void SystemCoreClockUpdate(void)
{
    switch ((RCC->SYSCLKCR >> 0) & 0x7)
    {
        case 1: /* XTHF */
            SystemCoreClock = XTHFClock;
            break;

        case 2: /* PLL */
            SystemCoreClock = SystemPLLClockUpdate();
            break;

        case 4: /* RCMF */
            switch ((RCC->RCMFCR >> 16) & 0x3)
            {
                case 0: /* output divided by 1 */
                    SystemCoreClock = 4000000;
                    break;

                case 1: /* output divided by 4 */
                    SystemCoreClock = 1000000;
                    break;

                case 2: /* output divided by 8 */
                    SystemCoreClock = 500000;
                    break;

                case 3: /* output divided by 16 */
                    SystemCoreClock = 250000;
                    break;
            }
            break;

        case 5: /* LSCLK */
            #ifdef USE_LSCLK_CLOCK_SRC_LPOSC
                SystemCoreClock = 32000;
            #else
                SystemCoreClock = XTLFClock;
            #endif
            break;

        case 6: /* LPOSC */
            SystemCoreClock = 32000;
            break;

        case 7: /* USBBCK */
            switch ((RCC->SYSCLKCR >> 3) & 0x1)
            {
                case 0: /* USBBCK 48MHz */
                    SystemCoreClock = 48000000;
                    break;

                case 1: /* USBBCK 120MHz/2 */
                    SystemCoreClock = 60000000;
                    break;
            }
            break;

        default:
            switch ((RCC->RCHFCR >> 16) & 0xf)
            {
                case 1: /* 16MHz */
                    SystemCoreClock = 16000000;
                    break;

                case 2: /* 24MHz */
                    SystemCoreClock = 24000000;
                    break;

                case 0: /* 8MHz */
                default:
                    SystemCoreClock = 8000000;
                    break;
            }
            break;
    }
}

/**
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit(void)
{
    #if !defined(MFANG) && defined(USE_LSCLK_CLOCK_SRC_XTLF)
    uint32_t temp;
    #endif

    #if defined(USE_IWDT_ON_STARTUP)
    RCC->PCLKCR1 |= 0x20U;              /* Enable IWDT Operation Clock */
    IWDT->CR = IWDT_OVERFLOW_PERIOD;    /* Configure IWDT overflow period */
    IWDT->SERV = 0x12345A5AU;           /* Enable IWDT */
    #endif

    /* Reset PLL & SYSCLK selection */
    RCC->PLLCR = 0x00000000U;
    RCC->SYSCLKCR = 0x0A000000U;

    /* Enable PAD Operation Clock */
    RCC->PCLKCR1 |= (0x1U << 7);

    #ifndef MFANG   /* MFANG handles clock configurations by itself */
    #ifdef USE_LSCLK_CLOCK_SRC_XTLF

        /* XTLF IO configuration */
        GPIOD->FCR |= 0x003C0000U;

        /* Enable XTLF */
        RCC->XTLFCR = 0x00000000U;
        RCC->XTLFCR |= (uint32_t)(0x5U << 8);
        for(temp = 2000U; temp > 0U; temp--);

    #ifdef USE_LSCLK_AUTO_SWITCH

        /* Enable LSCLK auto switch */
        RCC->SYSCLKCR |= 0x8000000U;

        /* LSCLK from XTLF */
        RCC->LSCLKSEL = 0xAAU;

    #else

        /* Disable LSCLK auto switch */
        CMU->SYSCLKCR &= 0x7FFFFFFU;

        /* LSCLK from XTLF */
        CMU->LSCLKSEL = 0xAAU;

    #endif  /* USE_LSCLK_AUTO_SWITCH */
    #else

        /* Disable LSCLK auto switch */
        RCC->SYSCLKCR &= 0x7FFFFFFU;

        /* LSCLK from LPOSC */
        RCC->LSCLKSEL = 0x55U;

    #endif  /* USE_LSCLK_CLOCK_SRC_XTLF */
    #endif  /* MFANG */

    /* PDR & BOR Configuration */
    RMU->PDRCR = 0x1U;
    RMU->BORCR = 0xEU;

    /* Disable IWDT & WWDT, enable other peripherals(e.g. timers) under Debug Mode */
    DBG->CR = 0x3U;

    /* Load clock trim value */
    RCC->RCHFTR = RCHF8M_TRIM;
    RCC->RCMFTR = RCMF4M_TRIM;
    RCC->LPOSCTR = LPOSC_TRIM;

    /* Enable SWD port pull up */
    GPIOD->PUEN |= (0x3U << 7U);

    /* DMA Flash Channel: Flash->RAM */
    RCC->PCLKCR2 |= (0x1U << 4U);
    DMA->CH7CR |= (0x1U << 10U);
    RCC->PCLKCR2 &= ~(0x1U << 4U);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    #if defined(USE_IWDT_ON_STARTUP)
    IWDT->SERV = 0x12345A5AU; /* Feed IWDT */
    #endif
}



