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
 * @file     ck_rsa.h
 * @brief    header file for rsa driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#ifndef _CK_RSA_H_
#define _CK_RSA_H_

#include <stdio.h>
#include "drv_rsa.h"
#include "soc.h"

#define RSA_KEY_LEN     1024
#define RSA_KEY_BYTE    (RSA_KEY_LEN >> 3)
#define RSA_KEY_WORD    (RSA_KEY_LEN >> 5)

#define BN_MAX_BITS     ((RSA_KEY_LEN << 1) + 32)
#define BN_MAX_BYTES    ((BN_MAX_BITS + 7) >> 3)
#define BN_MAX_WORDS    ((BN_MAX_BYTES + 3) >> 2)

#define MAX_RSA_LP_CNT  10000

#define UINT32_TO_UINT64(data)     ((uint64_t)(((uint64_t)(data)) & 0x00000000ffffffffU))
#define UINT64L_TO_UINT32(data)    ((uint32_t)(((uint64_t)(data)) & 0x00000000ffffffffU))
#define UINT64H_TO_UINT32(data)    ((uint32_t)((((uint64_t)(data)) >> 32) & 0x00000000ffffffffU))

#define PKCS1_PADDING   0x01
#define NO_PADDING      0x02

#define MD5_PADDING     0x00
#define SHA1_PADDING    0x01

#define MD5_HASH_SZ   16
#define SHA1_HASH_SZ  20

#define RAS_CALCULATE_Q     0x6
#define RSA_ENABLE_MODULE   0x3
#define RSA_ENDIAN_MODE     0x8
#define RSA_RESET           0x1
#define RSA_CAL_Q_DONE_OFFSET   0x5

typedef struct bignum {
    uint32_t pdata[BN_MAX_WORDS];
    uint32_t words;
} bignum_t;

typedef struct {
    __IOM uint32_t rsa_mwid;          /* Offset: 0x000 (R/W)  Width of M register */
    __IOM uint32_t rsa_ckid;          /* Offset: 0x004 (R/W)  Width of D register */
    __IOM uint32_t rsa_bwid;          /* Offset: 0x008 (R/W)  Width of B register */
    __IOM uint32_t rsa_ctrl;          /* Offset: 0x00c (R/W)  RSA control register */
    __OM  uint32_t rsa_rst;           /* Offset: 0x010 (W)    RSA reset register */
    __IM  uint32_t rsa_lp_cnt;        /* Offset: 0x014 (R)    Loop counter for inquiry register*/
    __IM  uint32_t rsa_q0;            /* Offset: 0x018 (R)    High-radix MM algorithm assistant register,part 1*/
    __IM  uint32_t rsa_q1;            /* Offset: 0x01c (R)    High-radix MM algorithm assistant register,part 2*/
    __IOM uint32_t rsa_isr;           /* Offset: 0x020 (W/R)  Interrupt raw status register */
    __IOM uint32_t rsa_imr;           /* Offset: 0x024 (W/R)  Interrupt mask register */
    __IOM uint32_t rev1[54];          /* Reserve regiser */
    __IOM uint32_t rsa_rfm;           /* Offset: 0x100 (W/R)  Register file for modulus M */
    __IOM uint32_t rev2[63];          /* Reserve regiser */
    __IOM uint32_t rsa_rfd;           /* Offset: 0x200 (W/R)  Register file for exponent D */
    __IOM uint32_t rev3[63];          /* Reserve regiser */
    __IOM uint32_t rsa_rfc;           /* Offset: 0x300 (W/R)  Register file for hard C */
    __IOM uint32_t rev4[63];          /* Reserve regiser */
    __IOM uint32_t rsa_rfb;           /* Offset: 0x400 (W/R)  Register file for data B */
    __IOM uint32_t rev5[63];          /* Reserve regiser */
    __IM  uint32_t rsa_rfr;           /* Offset: 0x500 (R)    Register file for storing the result */
} ck_rsa_reg_t;

#endif
