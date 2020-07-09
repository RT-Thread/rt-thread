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
 * @file     ck_rtc.h
 * @brief    header file for rtc driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef __CK_RTC_H
#define __CK_RTC_H

#include <stdio.h>
#include "soc.h"

#define SEC_PER_MIN  ((time_t)60)
#define SEC_PER_HOUR ((time_t)60 * SEC_PER_MIN)
#define SEC_PER_DAY  ((time_t)24 * SEC_PER_HOUR)

typedef struct {
    __IM  uint32_t    RTC_CCVR;         /* Offset: 0x000 (R/ )  current count value register */
    __IOM uint32_t    RTC_CMR;          /* Offset: 0x004 (R/W)  count match register */
    __IOM uint32_t    RTC_CLR;          /* Offset: 0x008 (R/W)  count load register */
    __IOM uint32_t    RTC_CCR;          /* Offset: 0x00c (R/W)  count control register */
    __IM  uint32_t    RTC_STAT;         /* Offset: 0x010 (R/ )  interrupt status register */
    __IM  uint32_t    RTC_RSTAT;        /* Offset: 0x014 (R/ )  interrupt raw status register */
    __IM  uint32_t    RTC_EOI;          /* Offset: 0x018 (R/ )  end of interrupt register */
    __IM  uint32_t    RTC_COMP_VERSION; /* Offset: 0x01c (R/ )  component version register */
} ck_rtc_reg_t;

#endif /* __CK_RTC_H */

