/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
 
#ifndef FH_GPIO_H_
#define FH_GPIO_H_


#define     REG_GPIO_SWPORTA_DR         (0x0000)
#define     REG_GPIO_SWPORTA_DDR        (0x0004)
#define     REG_GPIO_PORTA_CTL          (0x0008)
#define     REG_GPIO_INTEN              (0x0030)
#define     REG_GPIO_INTMASK            (0x0034)
#define     REG_GPIO_INTTYPE_LEVEL      (0x0038)
#define     REG_GPIO_INT_POLARITY       (0x003C)
#define     REG_GPIO_INTSTATUS          (0x0040)
#define     REG_GPIO_RAWINTSTATUS       (0x0044)
#define     REG_GPIO_DEBOUNCE           (0x0048)
#define     REG_GPIO_PORTA_EOI          (0x004C)
#define     REG_GPIO_EXT_PORTA          (0x0050)

#define NUM_OF_GPIO         (64)

struct fh_gpio_obj
{
    unsigned int              id;
    unsigned int              irq;
};



#endif /* FH_GPIO_H_ */
