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
 * @file     dw_wdt.h
 * @brief    header file for wdt driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef __DW_WDT_H
#define __DW_WDT_H

#include <stdio.h>
#include "soc.h"

#define DW_WDT_CRR_RESET    0x76
typedef struct {
    __IOM uint8_t WDT_CR:5;          /* Offset: 0x000 (R/W)  WDT control register        */
    uint8_t  RESERVED0[3];
    __IOM uint8_t WDT_TORR;          /* Offset: 0x004 (R/W)  WDT timeout range register  */
    uint8_t  RESERVED1[3];
    __IM  uint32_t WDT_CCVR;         /* Offset: 0x008 (R/ )  WDT current counter value register */
    __OM  uint8_t WDT_CRR:8;         /* Offset: 0x00C ( /W)  WDT count restart register */
    uint8_t  RESERVED2[3];
    __IM  uint8_t WDT_STAT:1;        /* Offset: 0x010 (R/ )  WDT interrupt status register */
    uint8_t  RESERVED3[3];
    __IM  uint8_t WDT_EOI:1;         /* Offset: 0x014 (R/ )  WDT interrupt clear register */
    uint8_t  RESERVED4[3];
} dw_wdt_reg_t;

#endif /* __DW_WDT_H */

