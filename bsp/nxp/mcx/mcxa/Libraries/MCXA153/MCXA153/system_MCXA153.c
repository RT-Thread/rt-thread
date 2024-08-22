/*
** ###################################################################
**     Processors:          MCXA153VFM
**                          MCXA153VFT
**                          MCXA153VLF
**                          MCXA153VLH
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    MCXA1 User manual
**     Version:             rev. 1.0, 2022-03-29
**     Build:               b240403
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2024 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2022-03-29)
**         Initial version based on v0.1UM
**
** ###################################################################
*/

/*!
 * @file MCXA153
 * @version 1.0
 * @date 2022-03-29
 * @brief Device specific configuration file for MCXA153 (implementation file)
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

__attribute__ ((weak)) void SystemInit (void) {

  SCB->CPACR |= ((3UL << 0*2) | (3UL << 1*2));    /* set CP0, CP1 Full Access in Secure mode (enable PowerQuad) */
#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)
  SCB_NS->CPACR |= ((3UL << 0*2) | (3UL << 1*2));    /* set CP0, CP1 Full Access in Normal mode (enable PowerQuad) */
#endif /* (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U) */

  SCB->NSACR |= ((3UL << 0) | (3UL << 10));   /* enable CP0, CP1, CP10, CP11 Non-secure Access */

#if defined(__MCUXPRESSO)
    extern void(*const g_pfnVectors[]) (void);
    SCB->VTOR = (uint32_t) &g_pfnVectors;
#else
    extern void *__Vectors;
    SCB->VTOR = (uint32_t) &__Vectors;
#endif
    /* Enable the LPCAC */
    SYSCON->LPCAC_CTRL |= SYSCON_LPCAC_CTRL_LPCAC_MEM_REQ_MASK;
    SYSCON->LPCAC_CTRL &= ~SYSCON_LPCAC_CTRL_DIS_LPCAC_MASK;

    /* Enable flash RWX when FLASH_ACL in IFR0 is invalid */
    if ((*((volatile const uint32_t *)(0x1000000)) == 0xFFFFFFFFU) ||
        ((*((volatile const uint32_t *)(0x1000000)) == 0x59630000U) &&
         (*((volatile const uint32_t *)(0x1000040)) == 0xFFFFFFFFU) &&
         (*((volatile const uint32_t *)(0x1000044)) == 0xFFFFFFFFU)))
    {
        /* Enable MBC register written with GLIKEY index15 */
        GLIKEY0->CTRL_0 = 0x00060000U;
        GLIKEY0->CTRL_0 = 0x0002000FU;
        GLIKEY0->CTRL_0 = 0x0001000FU;
        GLIKEY0->CTRL_1 = 0x00290000U;
        GLIKEY0->CTRL_0 = 0x0002000FU;
        GLIKEY0->CTRL_1 = 0x00280000U;
        GLIKEY0->CTRL_0 = 0x0000000FU;

        /* Enable RWX for GLBAC0 */
        MBC0->MBC_INDEX[0].MBC_MEMN_GLBAC[0] = 0x7700U;

        /* Use GLBAC0 for all flash block */
        for (uint8_t i = 0; i < 2U; i++)
        {
            MBC0->MBC_INDEX[0].MBC_DOM0_MEM0_BLK_CFG_W[i] = 0x00000000U;
        }

        /* Disable MBC register written */
        GLIKEY0->CTRL_0 = 0x0002000FU;
    }
  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
