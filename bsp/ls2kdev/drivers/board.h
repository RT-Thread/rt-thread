/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-04-05     bigmagic     the first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include <stdint.h>
#include <rthw.h>
#include "ls2k1000.h"

extern unsigned char __bss_end;

#define CPU_HZ              (1000 * 1000 * 1000) //QEMU 200*1000*1000
#define RT_HW_HEAP_BEGIN    (void*)&__bss_end
#define RT_HW_HEAP_END      (void*)(RT_HW_HEAP_BEGIN + 64 * 1024 * 1024)

/*
 * General PM Configuration Register
 */
#define PMCON_BASE			(APB_BASE | (0x7 << 12))

/*
 * Power Management1 Configuration Registers
 */
#define PM1_BASE			(PMCON_BASE + 0x0C)
#define PM1_STS				HWREG32(PM1_BASE)
#define PM1_EN				HWREG32(PM1_BASE + 0x04)
#define PM1_CNT				HWREG32(PM1_BASE + 0x08)
	
/*
 * Watch Dog Configuration Registers
 */
#define WDT_BASE			(PMCON_BASE + 0x30)
#define WDT_EN				HWREG32(WDT_BASE)
#define WDT_SET				HWREG32(WDT_BASE + 0x04)
#define WDT_TIMER			HWREG32(WDT_BASE + 0x08)


void rt_hw_board_init(void);

#endif
