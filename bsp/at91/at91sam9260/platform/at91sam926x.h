/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 */

#ifndef AT91SAM9260_H
#define AT91SAM9260_H

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>
#include "at91_aic.h"
#include "at91_pit.h"
#include "at91_pmc.h"
#include "at91_rstc.h"
#include "at91_shdwc.h"
#include "at91sam9260_matrix.h"
#include "at91_pio.h"
#include "at91_serial.h"
#include "at91_tc.h"
#include "at91_pdc.h"
#include "io.h"
#include "irq.h"
#include "gpio.h"

/*
 * Peripheral identifiers/interrupts.
 */
#define AT91_ID_FIQ     0   /* Advanced Interrupt Controller (FIQ) */
#define AT91_ID_SYS     1   /* System Peripherals */
#define AT91SAM9260_ID_PIOA 2   /* Parallel IO Controller A */
#define AT91SAM9260_ID_PIOB 3   /* Parallel IO Controller B */
#define AT91SAM9260_ID_PIOC 4   /* Parallel IO Controller C */
#define AT91SAM9260_ID_ADC  5   /* Analog-to-Digital Converter */
#define AT91SAM9260_ID_US0  6   /* USART 0 */
#define AT91SAM9260_ID_US1  7   /* USART 1 */
#define AT91SAM9260_ID_US2  8   /* USART 2 */
#define AT91SAM9260_ID_MCI  9   /* Multimedia Card Interface */
#define AT91SAM9260_ID_UDP  10  /* USB Device Port */
#define AT91SAM9260_ID_TWI  11  /* Two-Wire Interface */
#define AT91SAM9260_ID_SPI0 12  /* Serial Peripheral Interface 0 */
#define AT91SAM9260_ID_SPI1 13  /* Serial Peripheral Interface 1 */
#define AT91SAM9260_ID_SSC  14  /* Serial Synchronous Controller */
#define AT91SAM9260_ID_TC0  17  /* Timer Counter 0 */
#define AT91SAM9260_ID_TC1  18  /* Timer Counter 1 */
#define AT91SAM9260_ID_TC2  19  /* Timer Counter 2 */
#define AT91SAM9260_ID_UHP  20  /* USB Host port */
#define AT91SAM9260_ID_EMAC 21  /* Ethernet */
#define AT91SAM9260_ID_ISI  22  /* Image Sensor Interface */
#define AT91SAM9260_ID_US3  23  /* USART 3 */
#define AT91SAM9260_ID_US4  24  /* USART 4 */
#define AT91SAM9260_ID_US5  25  /* USART 5 */
#define AT91SAM9260_ID_TC3  26  /* Timer Counter 3 */
#define AT91SAM9260_ID_TC4  27  /* Timer Counter 4 */
#define AT91SAM9260_ID_TC5  28  /* Timer Counter 5 */
#define AT91SAM9260_ID_IRQ0 29  /* Advanced Interrupt Controller (IRQ0) */
#define AT91SAM9260_ID_IRQ1 30  /* Advanced Interrupt Controller (IRQ1) */
#define AT91SAM9260_ID_IRQ2 31  /* Advanced Interrupt Controller (IRQ2) */


/*
 * User Peripheral physical base addresses.
 */
#define AT91SAM9260_BASE_TCB0       0xfffa0000
#define AT91SAM9260_BASE_TC0        0xfffa0000
#define AT91SAM9260_BASE_TC1        0xfffa0040
#define AT91SAM9260_BASE_TC2        0xfffa0080
#define AT91SAM9260_BASE_UDP        0xfffa4000
#define AT91SAM9260_BASE_MCI        0xfffa8000
#define AT91SAM9260_BASE_TWI        0xfffac000
#define AT91SAM9260_BASE_US0        0xfffb0000
#define AT91SAM9260_BASE_US1        0xfffb4000
#define AT91SAM9260_BASE_US2        0xfffb8000
#define AT91SAM9260_BASE_SSC        0xfffbc000
#define AT91SAM9260_BASE_ISI        0xfffc0000
#define AT91SAM9260_BASE_EMAC       0xfffc4000
#define AT91SAM9260_BASE_SPI0       0xfffc8000
#define AT91SAM9260_BASE_SPI1       0xfffcc000
#define AT91SAM9260_BASE_US3        0xfffd0000
#define AT91SAM9260_BASE_US4        0xfffd4000
#define AT91SAM9260_BASE_US5        0xfffd8000
#define AT91SAM9260_BASE_TCB1       0xfffdc000
#define AT91SAM9260_BASE_TC3        0xfffdc000
#define AT91SAM9260_BASE_TC4        0xfffdc040
#define AT91SAM9260_BASE_TC5        0xfffdc080
#define AT91SAM9260_BASE_ADC        0xfffe0000
#define AT91_BASE_SYS               0xffffe800
#define AT91SAM9260_BASE_DBGU       0xfffff200

/*
 * System Peripherals (offset from AT91_BASE_SYS)
 */
#define AT91_ECC    (0xffffe800 - AT91_BASE_SYS)
#define AT91_SDRAMC (0xffffea00 - AT91_BASE_SYS)
#define AT91_SMC    (0xffffec00 - AT91_BASE_SYS)
#define AT91_MATRIX (0xffffee00 - AT91_BASE_SYS)
#define AT91_CCFG   (0xffffef10 - AT91_BASE_SYS)
#define AT91_AIC    (0xfffff000 - AT91_BASE_SYS)
#define AT91_DBGU   (0xfffff200 - AT91_BASE_SYS)
#define AT91_PIOA   (0xfffff400 - AT91_BASE_SYS)
#define AT91_PIOB   (0xfffff600 - AT91_BASE_SYS)
#define AT91_PIOC   (0xfffff800 - AT91_BASE_SYS)
#define AT91_PMC    (0xfffffc00 - AT91_BASE_SYS)
#define AT91_RSTC   (0xfffffd00 - AT91_BASE_SYS)
#define AT91_SHDWC  (0xfffffd10 - AT91_BASE_SYS)
#define AT91_RTT    (0xfffffd20 - AT91_BASE_SYS)
#define AT91_PIT    (0xfffffd30 - AT91_BASE_SYS)
#define AT91_WDT    (0xfffffd40 - AT91_BASE_SYS)
#define AT91_GPBR   (0xfffffd50 - AT91_BASE_SYS)


/*
 * Internal Memory.
 */
#define AT91SAM9260_ROM_BASE    0x00100000  /* Internal ROM base address */
#define AT91SAM9260_ROM_SIZE    SZ_32K      /* Internal ROM size (32Kb) */

#define AT91SAM9260_SRAM0_BASE  0x00200000  /* Internal SRAM 0 base address */
#define AT91SAM9260_SRAM0_SIZE  SZ_4K       /* Internal SRAM 0 size (4Kb) */
#define AT91SAM9260_SRAM1_BASE  0x00300000  /* Internal SRAM 1 base address */
#define AT91SAM9260_SRAM1_SIZE  SZ_4K       /* Internal SRAM 1 size (4Kb) */

#define AT91SAM9260_UHP_BASE    0x00500000  /* USB Host controller */

#define AT91SAM9XE_FLASH_BASE   0x00200000  /* Internal FLASH base address */
#define AT91SAM9XE_SRAM_BASE    0x00300000  /* Internal SRAM base address */

#define AT91SAM9G20_ROM_BASE    0x00100000  /* Internal ROM base address */
#define AT91SAM9G20_ROM_SIZE    SZ_32K      /* Internal ROM size (32Kb) */

#define AT91SAM9G20_SRAM0_BASE  0x00200000  /* Internal SRAM 0 base address */
#define AT91SAM9G20_SRAM0_SIZE  SZ_16K      /* Internal SRAM 0 size (16Kb) */
#define AT91SAM9G20_SRAM1_BASE  0x00300000  /* Internal SRAM 1 base address */
#define AT91SAM9G20_SRAM1_SIZE  SZ_16K      /* Internal SRAM 1 size (16Kb) */

#define AT91SAM9G20_UHP_BASE    0x00500000  /* USB Host controller */



/* Serial ports */
#define ATMEL_MAX_UART      7       /* 6 USART3's and one DBGU port (SAM9260) */

/* External Memory Map */
#define AT91_CHIPSELECT_0   0x10000000
#define AT91_CHIPSELECT_1   0x20000000
#define AT91_CHIPSELECT_2   0x30000000
#define AT91_CHIPSELECT_3   0x40000000
#define AT91_CHIPSELECT_4   0x50000000
#define AT91_CHIPSELECT_5   0x60000000
#define AT91_CHIPSELECT_6   0x70000000
#define AT91_CHIPSELECT_7   0x80000000

/* SDRAM */
#define AT91_SDRAM_BASE     AT91_CHIPSELECT_1

/* Clocks */
#define AT91_SLOW_CLOCK     32768       /* slow clock */


/*****************************/
/* CPU Mode                  */
/*****************************/
#define USERMODE        0x10
#define FIQMODE         0x11
#define IRQMODE         0x12
#define SVCMODE         0x13
#define ABORTMODE       0x17
#define UNDEFMODE       0x1b
#define MODEMASK        0x1f
#define NOINT           0xc0

struct rt_hw_register
{
    rt_uint32_t r0;
    rt_uint32_t r1;
    rt_uint32_t r2;
    rt_uint32_t r3;
    rt_uint32_t r4;
    rt_uint32_t r5;
    rt_uint32_t r6;
    rt_uint32_t r7;
    rt_uint32_t r8;
    rt_uint32_t r9;
    rt_uint32_t r10;
    rt_uint32_t fp;
    rt_uint32_t ip;
    rt_uint32_t sp;
    rt_uint32_t lr;
    rt_uint32_t pc;
    rt_uint32_t cpsr;
    rt_uint32_t ORIG_r0;
};

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

extern struct clk *clk_get(const char *id);
extern rt_uint32_t clk_get_rate(struct clk *clk);
extern void rt_hw_clock_init(void);

#ifdef __cplusplus
}
#endif

#endif

