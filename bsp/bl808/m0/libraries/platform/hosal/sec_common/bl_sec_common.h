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

#include <stdint.h>

typedef enum {
    BL_SHA1,
    BL_SHA224,
    BL_SHA256,
    BL_MD5,
    BL_SHA384,
    BL_SHA512,
} bl_sha_type_t;

/*
 * SHA1/SHA224/SHA256
 */
/* copied SEC_Eng_SHA256_Ctx from stddrv */
typedef struct {
    uint32_t total[2];
    uint32_t  *shaBuf;
    uint32_t  *shaPadding;
    uint32_t linkAddr;
} bl_SEC_Eng_SHA256_Link_Ctx;

// used for both SHA1/SHA224/SHA256 and SHA512
typedef struct {
    uint32_t shaCfgWord;
    uint32_t shaSrcAddr;                     /*!< Message source address */
    uint32_t result[16];                      /*!< Result of SHA */
} __attribute__ ((aligned(4))) bl_SEC_Eng_SHA_Link_Config_Type;

typedef struct bl_sha_ctx {
    bl_sha_type_t type;
    bl_SEC_Eng_SHA256_Link_Ctx ctx;
    bl_SEC_Eng_SHA_Link_Config_Type link_cfg;
    uint32_t tmp[16];
    uint32_t pad[16];
} bl_sha_ctx_t;


/*
 * SHA384/512
 */
// copied SEC_Eng_SHA512_Link_Ctx from stddrv */
typedef struct
{
    uint64_t total[2];    /*!< Number of bytes processed */
    uint64_t *shaBuf;     /*!< Data not processed but in this temp buffer */
    uint64_t *shaPadding; /*!< Padding data */
    uint32_t linkAddr;    /*!< Link configure address */
} bl_SEC_Eng_SHA512_Link_Ctx;

typedef struct bl_sha512_ctx {
    bl_sha_type_t type;
    bl_SEC_Eng_SHA512_Link_Ctx ctx;
    bl_SEC_Eng_SHA_Link_Config_Type link_cfg;
    uint64_t tmp[16];
    uint64_t pad[16];
} bl_sha512_ctx_t;
