/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-14     ArdaFu      first version
 */

/* write register a=address, v=value */
#define write_reg(a,v)      (*(volatile unsigned int *)(a) = (v))
/* Processor Reset */
#define AT91C_RSTC_PROCRST   (1 << 0)
#define AT91C_RSTC_PERRST    (1 << 2)
#define AT91C_RSTC_KEY       (0xa5 << 24)
#define AT91C_MATRIX_BASE    (0XFFFFEE00)
/* Master Remap Control Register */
#define AT91C_MATRIX_MRCR    (AT91C_MATRIX_BASE + 0x100)
/* Remap Command for AHB Master 0 (ARM926EJ-S InSTRuction Master) */
#define AT91C_MATRIX_RCB0    (1 << 0)
/* Remap Command for AHB Master 1 (ARM926EJ-S Data Master) */
#define AT91C_MATRIX_RCB1    (1 << 1)

#define AT91C_AIC_BASE       (0XFFFFF000)
/* Interrupt DisaBLe Command Register */
#define AT91C_AIC_IDCR       (AT91C_AIC_BASE + 0x124)
/* Interrupt Clear Command Register */
#define AT91C_AIC_ICCR       (AT91C_AIC_BASE + 0x128)

#define AT91C_WDT_BASE       (0XFFFFFD40)
#define AT91C_WDT_CR         (AT91C_WDT_BASE + 0x00)
#define AT91C_WDT_CR_KEY     (0xA5000000)
#define AT91C_WDT_CR_WDRSTT  (0x00000001)
#define AT91C_WDT_MR         (AT91C_WDT_BASE + 0x04)
#define AT91C_WDT_MR_WDDIS   (0x00008000)

void rt_low_level_init(void)
{
    // Mask all IRQs by clearing all bits in the INTMRS
    write_reg(AT91C_AIC_IDCR, 0xFFFFFFFF);
    write_reg(AT91C_AIC_ICCR, 0xFFFFFFFF);
    // Remap internal ram to 0x00000000 Address
    write_reg(AT91C_MATRIX_MRCR, AT91C_MATRIX_RCB0 | AT91C_MATRIX_RCB1);
    // Disable the watchdog
    //write_reg(AT91C_WDT_CR, AT91C_WDT_CR_KEY|AT91C_WDT_CR_WDRSTT);
    //write_reg(AT91C_WDT_MR, AT91C_WDT_MR_WDDIS);
}

