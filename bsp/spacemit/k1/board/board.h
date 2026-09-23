/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-10-15     IronsideZhang     first version
 */

#ifndef BOARD_H__
#define BOARD_H__

#include "rtconfig.h"
#include "mem_layout.h"
#include "irq_num.h"

/* From DTS '/cpus' node: timebase-frequency = <24000000>; */
#define CPUTIME_TIMER_FREQ          (24000000)

/*
 * SpacemiT K1 Memory Map
 */

/* UART0 Controller*/
#define UART0_BASE_ADDR             (0xd4017000UL)
#define UART0_IO_SIZE               (0x100UL)

/* IOMUX/Pinctrl Controller*/
#define IOMUX_BASE_ADDR             (0xd401e000UL)
#define IOMUX_IO_SIZE               (0x1000UL)

/* Clock & Reset Management Unit*/
#define CMU_BASE_ADDR               (0xd4050000UL)
#define CMU_IO_SIZE                 (0x3000UL)
#define RMU_BASE_ADDR               (0xd4050000UL) // Reset is part of CMU
#define RMU_IO_SIZE                 (0x3000UL)

/* APB Clock Controller*/
#define APBC_BASE_ADDR              (0xd4015000UL)
#define APBC_IO_SIZE                (0x1000UL)

#endif // BOARD_H__