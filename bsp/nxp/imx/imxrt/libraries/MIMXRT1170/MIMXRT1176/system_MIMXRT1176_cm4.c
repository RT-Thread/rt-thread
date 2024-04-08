/*
** ###################################################################
**     Processors:          MIMXRT1176AVM8A_cm4
**                          MIMXRT1176CVM8A_cm4
**                          MIMXRT1176DVMAA_cm4
**
**     Compilers:           Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    IMXRT1170RM, Rev 1, 02/2021
**     Version:             rev. 1.0, 2020-12-29
**     Build:               b210615
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**
** ###################################################################
*/

/*!
 * @file MIMXRT1176_cm4
 * @version 1.0
 * @date 2021-06-15
 * @brief Device specific configuration file for MIMXRT1176_cm4 (implementation
 *        file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"



/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {
#if ((__FPU_PRESENT == 1) && (__FPU_USED == 1))
  SCB->CPACR |= ((3UL << 10*2) | (3UL << 11*2));    /* set CP10, CP11 Full Access */
#endif /* ((__FPU_PRESENT == 1) && (__FPU_USED == 1)) */

#if defined(__MCUXPRESSO)
    extern uint32_t g_pfnVectors[];  // Vector table defined in startup code
    SCB->VTOR = (uint32_t)g_pfnVectors;
#endif

/* Watchdog disable */

#if (DISABLE_WDOG)
    if ((WDOG1->WCR & WDOG_WCR_WDE_MASK) != 0U)
    {
        WDOG1->WCR &= ~(uint16_t) WDOG_WCR_WDE_MASK;
    }
    if ((WDOG2->WCR & WDOG_WCR_WDE_MASK) != 0U)
    {
        WDOG2->WCR &= ~(uint16_t) WDOG_WCR_WDE_MASK;
    }
    if ((RTWDOG3->CS & RTWDOG_CS_CMD32EN_MASK) != 0U)
    {
        RTWDOG3->CNT = 0xD928C520U; /* 0xD928C520U is the update key */
    }
    else
    {
        RTWDOG3->CNT = 0xC520U;
        RTWDOG3->CNT = 0xD928U;
    }
    RTWDOG3->TOVAL = 0xFFFF;
    RTWDOG3->CS = (uint32_t) ((RTWDOG3->CS) & ~RTWDOG_CS_EN_MASK) | RTWDOG_CS_UPDATE_MASK;
    if ((RTWDOG4->CS & RTWDOG_CS_CMD32EN_MASK) != 0U)
    {
        RTWDOG4->CNT = 0xD928C520U; /* 0xD928C520U is the update key */
    }
    else
    {
        RTWDOG4->CNT = 0xC520U;
        RTWDOG4->CNT = 0xD928U;
    }
    RTWDOG4->TOVAL = 0xFFFF;
    RTWDOG4->CS = (uint32_t) ((RTWDOG4->CS) & ~RTWDOG_CS_EN_MASK) | RTWDOG_CS_UPDATE_MASK;
#endif /* (DISABLE_WDOG) */

    /* Disable Systick which might be enabled by bootrom */
    if ((SysTick->CTRL & SysTick_CTRL_ENABLE_Msk) != 0U)
    {
        SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    }

    /* Initialize Cache */
    /* Enable Code Bus Cache */
    if (0U == (LMEM->PCCCR & LMEM_PCCCR_ENCACHE_MASK))
    {
        /* set command to invalidate all ways, and write GO bit to initiate command */
        LMEM->PCCCR |= LMEM_PCCCR_INVW1_MASK | LMEM_PCCCR_INVW0_MASK | LMEM_PCCCR_GO_MASK;
        /* Wait until the command completes */
        while ((LMEM->PCCCR & LMEM_PCCCR_GO_MASK) != 0U) {
        }
        /* Enable cache, enable write buffer */
        LMEM->PCCCR |= (LMEM_PCCCR_ENWRBUF_MASK | LMEM_PCCCR_ENCACHE_MASK);
    }

    /* Enable System Bus Cache */
    if (0U == (LMEM->PSCCR & LMEM_PSCCR_ENCACHE_MASK))
    {
        /* set command to invalidate all ways, and write GO bit to initiate command */
        LMEM->PSCCR |= LMEM_PSCCR_INVW1_MASK | LMEM_PSCCR_INVW0_MASK | LMEM_PSCCR_GO_MASK;
        /* Wait until the command completes */
        while ((LMEM->PSCCR & LMEM_PSCCR_GO_MASK) != 0U) {
        }
        /* Enable cache, enable write buffer */
        LMEM->PSCCR |= (LMEM_PSCCR_ENWRBUF_MASK | LMEM_PSCCR_ENCACHE_MASK);
    }

    /* Clear bit 13 to its reset value since it might be set by ROM. */
    IOMUXC_GPR->GPR28 &= ~IOMUXC_GPR_GPR28_CACHE_USB_MASK;

#if defined(ROM_ECC_ENABLED)
    /* When ECC is enabled, SRC->SRSR need to be cleared since only correct SRSR value can trigger ROM ECC preload procedure.
       Save SRSR to SRC->GPR[11] so that application can still check SRSR value from SRC->GPR[11]. */
    SRC->GPR[11] = SRC->SRSR;
    /* clear SRSR */
    SRC->SRSR = 0xFFFFFFFFU;
#endif

    /* Enable entry to thread mode when divide by zero */
    SCB->CCR |= SCB_CCR_DIV_0_TRP_Msk;
    __DSB();
    __ISB();

  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

/* TBD */

}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
