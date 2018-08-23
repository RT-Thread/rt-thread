/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     dw_gpio.h
 * @brief    header file for GPIO Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _DW_GPIO_H_
#define _DW_GPIO_H_

#include "drv_gpio.h"
#include "soc.h"


typedef struct {
    __IOM uint32_t SWPORT_DR;                     /* Offset: 0x000 (W/R)  PortA data register */
    __IOM uint32_t SWPORT_DDR;                    /* Offset: 0x004 (W/R)  PortA data direction register */
    __IOM uint32_t PORT_CTL;                      /* Offset: 0x008 (W/R)  PortA source register */

} dw_gpio_reg_t;

typedef struct {
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

#endif

