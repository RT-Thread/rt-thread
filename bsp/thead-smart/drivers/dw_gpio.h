/*
 * Copyright (C) 2017-2019 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-20     zx.chen      header file for GPIO Driver
 */

#ifndef _DW_GPIO_H_
#define _DW_GPIO_H_

#include "drv_gpio.h"
#include "soc.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct 
{
    __IOM uint32_t SWPORT_DR;                     /* Offset: 0x000 (W/R)  PortA data register */
    __IOM uint32_t SWPORT_DDR;                    /* Offset: 0x004 (W/R)  PortA data direction register */
    __IOM uint32_t PORT_CTL;                      /* Offset: 0x008 (W/R)  PortA source register */

} dw_gpio_reg_t;

typedef struct
{
    __IOM uint32_t INTEN;                         /* Offset: 0x000 (W/R)  Interrupt enable register */
    __IOM uint32_t INTMASK;                       /* Offset: 0x004 (W/R)  Interrupt mask register */
    __IOM uint32_t INTTYPE_LEVEL;                 /* Offset: 0x008 (W/R)  Interrupt level register */
    __IOM uint32_t INT_POLARITY;                  /* Offset: 0x00c (W/R)  Interrupt polarity register */
    __IM  uint32_t INTSTATUS;                     /* Offset: 0x010 (R)    Interrupt status of Port */
    __IM  uint32_t RAWINTSTATUS;                  /* Offset: 0x014 (W/R)  Raw interrupt status of Port */
    __IOM uint32_t revreg1;                       /* Offset: 0x018 (W/R)  Reserve register */
    __OM  uint32_t PORTA_EOI;                     /* Offset: 0x01c (W/R)  Port clear interrupt register */
    __IM  uint32_t EXT_PORTA;                     /* Offset: 0x020 (W/R)  PortA external port register */
    __IM  uint32_t EXT_PORTB;                     /* Offset: 0x024 (W/R)  PortB external port register */
    __IOM uint32_t revreg2[2];                    /* Offset: 0x028 (W/R)  Reserve register */
    __IOM uint32_t LS_SYNC;                       /* Offset: 0x030 (W/R)  Level-sensitive synchronization enable register */

} dw_gpio_control_reg_t;

#ifdef __cplusplus
}
#endif

#endif

