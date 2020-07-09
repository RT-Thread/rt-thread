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
 * @file     ck_sha.h
 * @brief    header file for sha driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CK_SHA_H_
#define _CK_SHA_H_

#include <stdio.h>
#include "drv_sha.h"
#include "soc.h"

#define SHA_INIT_OFFSET         3
#define SHA_INT_ENABLE_OFFSET   4
#define SHA_ENDIAN_OFFSET       5
#define SHA_CAL_OFFSET          6
typedef struct {
    __IOM uint32_t SHA_CON;                     /* Offset: 0x000 (R/W)  Control register */
    __IOM uint32_t SHA_INTSTATE;                /* Offset: 0x004 (R/W)  Instatus register */
    __IOM uint32_t SHA_H0L;                     /* Offset: 0x008 (R/W)  H0L register */
    __IOM uint32_t SHA_H1L;                     /* Offset: 0x00c (R/W)  H1L register */
    __IOM uint32_t SHA_H2L;                     /* Offset: 0x010 (R/W)  H2L register */
    __IOM uint32_t SHA_H3L;                     /* Offset: 0x014 (R/W)  H3L register */
    __IOM uint32_t SHA_H4L;                     /* Offset: 0x018 (R/W)  H4L register */
    __IOM uint32_t SHA_H5L;                     /* Offset: 0x01c (R/W)  H5L register */
    __IOM uint32_t SHA_H6L;                     /* Offset: 0x020 (R/W)  H6L register */
    __IOM uint32_t SHA_H7L;                     /* Offset: 0x024 (R/W)  H7L register */
    __IOM uint32_t SHA_H0H;                     /* Offset: 0x028 (R/W)  H0H register */
    __IOM uint32_t SHA_H1H;                     /* Offset: 0x02c (R/W)  H1H register */
    __IOM uint32_t SHA_H2H;                     /* Offset: 0x030 (R/W)  H2H register */
    __IOM uint32_t SHA_H3H;                     /* Offset: 0x034 (R/W)  H3H register */
    __IOM uint32_t SHA_H4H;                     /* Offset: 0x038 (R/W)  H4H register */
    __IOM uint32_t SHA_H5H;                     /* Offset: 0x03c (R/W)  H5H register */
    __IOM uint32_t SHA_H6H;                     /* Offset: 0x040 (R/W)  H6H register */
    __IOM uint32_t SHA_H7H;                     /* Offset: 0x044 (R/W)  H7H register */
    __IOM uint32_t SHA_DATA1;                   /* Offset: 0x048 (R/W)  DATA1 register */
    uint32_t REV[15];
    __IOM uint32_t SHA_DATA2;                   /* Offset: 0x088 (R/W)  DATA2 register */
} ck_sha_reg_t;
#endif

typedef enum {
    SHA_STATUS_START_END = 0,      /* the one time count mode */
    SHA_STATUS_START     = 1,      /* the first time of the cal */
    SHA_STATUS_CONTINUE  = 2,      /* the middle stage of the cal */
    SHA_STATUS_END       = 3       /* the last time of the cal*/
} enum_sha_status;
