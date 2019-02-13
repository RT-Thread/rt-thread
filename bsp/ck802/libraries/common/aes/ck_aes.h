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
 * @file     ck_aes.h
 * @brief    header file for aes driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CK_AES_H_
#define _CK_AES_H_

#include <stdio.h>
#include "drv_aes.h"
#include "soc.h"

#define AES_LITTLE_ENDIAN   0x00000100

#define AES_MAX_KEY_LENGTH  32
#define AES_IT_DATAINT      0x4
#define AES_IT_KEYINT       0x2
#define AES_IT_BUSY         0x1
#define AES_IT_ALL          0x7
#define AES_CRYPTO_KEYEXP   0x2

#define AES_WORK_ENABLE_OFFSET  0
#define AES_INT_ENABLE_OFFSET   2
#define AES_MODE_OFFSET         3
#define AES_KEY_LEN_OFFSET      4
#define AES_OPCODE_OFFSET       6

typedef struct {
    __IOM uint32_t datain[4];                 /* Offset: 0x000 (R/W) Data input 0~127 */
    __IOM uint32_t key[8];                    /* Offset: 0x010 (R/W) Key 0~255 */
    __IOM uint32_t iv[4];                     /* Offset: 0x030 (R/W) Initial Vector: 0~127 */
    __IOM uint32_t ctrl;                      /* Offset: 0x040 (R/W) AES Control Register */
    __IOM uint32_t state;                     /* Offset: 0x044 (R/W) AES State Register */
    __IOM uint32_t dataout[4];                /* Offset: 0x048 (R/W) Data Output 0~31 */
} ck_aes_reg_t;

#endif
