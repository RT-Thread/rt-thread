//*****************************************************************************
// boot_multicore_slave.c
//
// Provides functions to allow booting of secondary core in multicore system
//
//*****************************************************************************
//
// Copyright 2021 NXP
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
#if defined (__MULTICORE_MASTER_SLAVE_M4SLAVE) || \
    defined (__MULTICORE_MASTER_SLAVE_M7SLAVE)
#include "fsl_device_registers.h"

#if defined (__MULTICORE_MASTER_SLAVE_M4SLAVE)
extern uint8_t __core_m4slave_START__;
#else
extern uint8_t __core_m7slave_START__;
#endif

void boot_multicore_slave(void) {

    volatile uint32_t bootAddress;

    /* When kicking off the CM4 core from the CM7 core */
    #if defined(__MULTICORE_MASTER_SLAVE_M4SLAVE)
        bootAddress = (uint32_t)(char *)&__core_m4slave_START__;
        IOMUXC_LPSR_GPR->GPR0 = IOMUXC_LPSR_GPR_GPR0_CM4_INIT_VTOR_LOW(bootAddress >> 3u);
        IOMUXC_LPSR_GPR->GPR1 = IOMUXC_LPSR_GPR_GPR1_CM4_INIT_VTOR_HIGH(bootAddress >> 16u);

        SRC->CTRL_M4CORE = SRC_CTRL_M4CORE_SW_RESET_MASK;
        SRC->SCR |= SRC_SCR_BT_RELEASE_M4_MASK;
    #endif
    /* When kicking off the CM7 core from the CM4 core */
    #if defined(__MULTICORE_MASTER_SLAVE_M7SLAVE)
        bootAddress = (uint32_t)(char *)&__core_m7slave_START__;
        if (ANADIG_MISC->MISC_DIFPROG == 0x1170A0U)
        {
            /* Set hidden register at 0x400e404c address */
            *(uint32_t *)&IOMUXC_GPR->RESERVED_0[0] = bootAddress >> 7u;
        }
        else
        {
            IOMUXC_LPSR_GPR->GPR26 &= ~IOMUXC_LPSR_GPR_GPR26_CM7_INIT_VTOR_MASK;
            IOMUXC_LPSR_GPR->GPR26 |= IOMUXC_LPSR_GPR_GPR26_CM7_INIT_VTOR(bootAddress >> 7u);
        }

        SRC->CTRL_M7CORE = SRC_CTRL_M7CORE_SW_RESET_MASK;
        SRC->SCR |= SRC_SCR_BT_RELEASE_M7_MASK;
    #endif

}
#endif // defined (__MULTICORE_MASTER_SLAVE_M4SLAVE) ||
       //         (__MULTICORE_MASTER_SLAVE_M7SLAVE)
