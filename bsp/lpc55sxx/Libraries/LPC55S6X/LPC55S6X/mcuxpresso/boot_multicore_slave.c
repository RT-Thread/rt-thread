//*****************************************************************************
// boot_multicore_slave.c
//
// Provides simple functions to boot slave core in LPC55xx multicore system
//
// Version : 181106
//
//*****************************************************************************
//
// Copyright 2016-2019 NXP
// All rights reserved.
//
// SPDX-License-Identifier: BSD-3-Clause
//*****************************************************************************

#if defined(__MULTICORE_MASTER)

#include <stdint.h>

//#define SYSCON_BASE       ((uint32_t) 0x40000000)
#define SYSCON_BASE ((uint32_t)0x50000000)

#define CPBOOT (((volatile uint32_t *)(SYSCON_BASE + 0x804)))
#define CPUCTRL (((volatile uint32_t *)(SYSCON_BASE + 0x800)))
#define CPUCFG (((volatile uint32_t *)(SYSCON_BASE + 0xFD4)))

#define CPUCTRL_KEY ((uint32_t)(0x0000C0C4 << 16))
#define CORE1_CLK_ENA (1 << 3)
#define CORE1_RESET_ENA (1 << 5)
#define CORE1_ENABLE (1 << 2)

extern uint8_t __core_m33slave_START__;

void boot_multicore_slave(void)
{
    volatile uint32_t *u32REG, u32Val;

    unsigned int *slavevectortable_ptr = (unsigned int *)&__core_m33slave_START__;

    // Enable CPU1 in SYSCON->CPUCFG
    *CPUCFG |= CORE1_ENABLE;

    // Set CPU1 boot address in SYSCON->CPBoot
    *CPBOOT = (uint32_t)slavevectortable_ptr;

    // Read SYSCON->CPUCTRL and set key value in bits 31:16
    u32REG = (uint32_t *)CPUCTRL;
    u32Val = *u32REG | CPUCTRL_KEY;

    // Enable slave clock and reset in SYSCON->CPUCTRL
    *u32REG = u32Val | CORE1_CLK_ENA | CORE1_RESET_ENA;

    // Clear slave reset in SYSCON->CPUCTRL
    *u32REG = (u32Val | CORE1_CLK_ENA) & (~CORE1_RESET_ENA);
}
#endif // defined (__MULTICORE_MASTER)
