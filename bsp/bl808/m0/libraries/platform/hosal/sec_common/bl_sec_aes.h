/*
 * Copyright (c) 2016-2022 Bouffalolab.
 *
 * This file is part of
 *     *** Bouffalolab Software Dev Kit ***
 *      (see www.bouffalolab.com).
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of Bouffalo Lab nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#pragma once


// copied struct from 616. Should be compatible with all chips
typedef struct
{
    uint32_t              : 3;  /*!< [2:0]Reserved */
    uint32_t aesMode      : 2;  /*!< [4:3]128-bit/256-bit/192-bit/128-bit-double key mode select */
    uint32_t aesDecEn     : 1;  /*!< [5]Encode or decode */
    uint32_t aesDecKeySel : 1;  /*!< [6]Use new key or use same key as last one */
    uint32_t aesHwKeyEn   : 1;  /*!< [7]Enable or disable using hardware hey */
    uint32_t              : 1;  /*!< [8]Reserved */
    uint32_t aesIntClr    : 1;  /*!< [9]Clear interrupt */
    uint32_t aesIntSet    : 1;  /*!< [10]Set interrupt */
    uint32_t              : 1;  /*!< [11]Reserved */
    uint32_t aesBlockMode : 2;  /*!< [13:12]ECB/CTR/CBC mode select */
    uint32_t aesIVSel     : 1;  /*!< [14]Use new iv or use same iv as last one */
    uint32_t aesXTS       : 1;  /*!< [15]XTS mode select */
    uint32_t aesMsgLen    : 16; /*!< [31:16]Number of 128-bit block */
    uint32_t aesSrcAddr;        /*!< Message source address */
    uint32_t aesDstAddr;        /*!< Message destination address */
    uint32_t aesIV0;            /*!< Big endian initial vector(MSB) */
    uint32_t aesIV1;            /*!< Big endian initial vector */
    uint32_t aesIV2;            /*!< Big endian initial vector */
    uint32_t aesIV3;            /*!< Big endian initial vector(LSB)(CTR mode:counter initial value) */
    uint32_t aesKey0;           /*!< Big endian aes key(aes-128/256 key MSB) */
    uint32_t aesKey1;           /*!< Big endian aes key */
    uint32_t aesKey2;           /*!< Big endian aes key */
    uint32_t aesKey3;           /*!< Big endian aes key(aes-128 key LSB) */
    uint32_t aesKey4;           /*!< Big endian aes key */
    uint32_t aesKey5;           /*!< Big endian aes key */
    uint32_t aesKey6;           /*!< Big endian aes key */
    uint32_t aesKey7;           /*!< Big endian aes key(aes-256 key LSB) */
} __attribute__((aligned(4))) bl_SEC_Eng_AES_Link_Config_Type;

typedef enum {
    BL_AES_ENCRYPT,
    BL_AES_DECRYPT,
} bl_sec_aes_op_t;

typedef struct {
    bl_SEC_Eng_AES_Link_Config_Type link_cfg;
} bl_sec_aes_t;

int bl_sec_aes_init();
int bl_aes_acquire_hw();
int bl_aes_release_hw();
int bl_aes_init(bl_sec_aes_t *aes);
int bl_aes_set_key(bl_sec_aes_t *aes, bl_sec_aes_op_t op, const uint8_t *key, size_t key_len);
int bl_aes_transform(bl_sec_aes_t *aes, bl_sec_aes_op_t op, const uint8_t *input, uint8_t *output);
