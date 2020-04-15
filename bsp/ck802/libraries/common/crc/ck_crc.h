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
 * @file     ck_crc.h
 * @brief    header file for crc driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CK_CRC_H_
#define _CK_CRC_H_

#include "stdint.h"
#include "soc.h"

typedef struct {
    __IOM uint32_t CRC_DATA;                     /* Offset: 0x000 (W/R)  data register */
    __IOM uint32_t CRC_SEL;                      /* Offset: 0x004 (W/R)  mode select register for CRC */
    __OM  uint32_t CRC_INIT;                     /* Offset: 0x008 (W)    initial value register */

} ck_crc_reg_t;
#endif
