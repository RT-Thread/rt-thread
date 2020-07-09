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
 * @file     ck_trng.h
 * @brief    header file for trng driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CK_TRNG_H_
#define _CK_TRNG_H_

#include "drv_trng.h"
#include "soc.h"

/*
 *  define the bits for TCR
 */
#define TRNG_EN              (1UL << 1)
#define TRNG_LOWPER_MODE     (1UL << 2)
#define TRNG_DATA_READY      1

typedef struct {
    __IOM uint32_t TCR;                     /* Offset: 0x000 (W/R)  TRNG control register */
    __IM  uint32_t TDR;                     /* Offset: 0x004 (R)    TRNG Data register */

} ck_trng_reg_t;
#endif
