//*****************************************************************************
// boot_multicore_slave.c
//
// Provides simple functions to boot slave core in LPC55xx multicore system
//
// Version : 181106
//
//*****************************************************************************
//
// Copyright 2018, NXP
// All rights reserved.
//
// Software that is described herein is for illustrative purposes only
// which provides customers with programming information regarding the
// LPC products.  This software is supplied "AS IS" without any warranties of
// any kind, and NXP Semiconductors and its licensor disclaim any and
// all warranties, express or implied, including all implied warranties of
// merchantability, fitness for a particular purpose and non-infringement of
// intellectual property rights.  NXP Semiconductors assumes no responsibility
// or liability for the use of the software, conveys no license or rights under any
// patent, copyright, mask work right, or any other intellectual property rights in
// or to any products. NXP Semiconductors reserves the right to make changes
// in the software without notification. NXP Semiconductors also makes no
// representation or warranty that such application will be suitable for the
// specified use without further testing or modification.
//
// Permission to use, copy, modify, and distribute this software and its
// documentation is hereby granted, under NXP Semiconductors' and its
// licensor's relevant copyrights in the software, without fee, provided that it
// is used in conjunction with NXP Semiconductors microcontrollers.  This
// copyright, permission, and disclaimer notice must appear in all copies of
// this code.
//*****************************************************************************

#if defined (__MULTICORE_MASTER)

#include <stdint.h>

//#define SYSCON_BASE       ((uint32_t) 0x40000000)
#define SYSCON_BASE         ((uint32_t) 0x50000000)

#define CPBOOT              (((volatile uint32_t *) (SYSCON_BASE + 0x804)))
#define CPUCTRL             (((volatile uint32_t *) (SYSCON_BASE + 0x800)))
#define CPUCFG              (((volatile uint32_t *) (SYSCON_BASE + 0xFD4)))

#define CPUCTRL_KEY         ((uint32_t)(0x0000C0C4 << 16))
#define CORE1_CLK_ENA       (1<<3)
#define CORE1_RESET_ENA     (1<<5)
#define CORE1_ENABLE         (1 <<2)


extern uint8_t __core_m33slave_START__;

void boot_multicore_slave(void) {

    volatile uint32_t *u32REG, u32Val;

    unsigned int *slavevectortable_ptr =
            (uint32_t *) &__core_m33slave_START__;

    // Enable CPU1 in SYSCON->CPUCFG
     *CPUCFG |= CORE1_ENABLE;

     // Set CPU1 boot address in SYSCON->CPBoot
     *CPBOOT = (uint32_t) slavevectortable_ptr;

     // Read SYSCON->CPUCTRL and set key value in bits 31:16
     u32REG = (uint32_t *) CPUCTRL;
     u32Val = *u32REG | CPUCTRL_KEY;

     // Enable slave clock and reset in SYSCON->CPUCTRL
     *u32REG = u32Val | CORE1_CLK_ENA | CORE1_RESET_ENA;

     // Clear slave reset in SYSCON->CPUCTRL
     *u32REG = (u32Val | CORE1_CLK_ENA) & (~CORE1_RESET_ENA);

}
#endif //defined (__MULTICORE_MASTER)
