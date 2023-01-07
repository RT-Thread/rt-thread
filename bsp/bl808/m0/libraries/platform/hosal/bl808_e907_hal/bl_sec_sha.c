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
#include <stdio.h>

#include <bl606p_sec_eng.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include "bl_irq.h"
#include "bl_sec.h"

#include <blog.h>

typedef struct sha256_link_item {
    SEC_Eng_SHA256_Link_Ctx ctx;
    SEC_Eng_SHA_Link_Config_Type linkCfg;
    uint32_t tmp[16];
    uint32_t pad[16];
} sha256_link_item_t;

#define BL_SHA_ID SEC_ENG_SHA_ID0 // this is the only valid value

int bl_sha_mutex_take()
{
    if (pdPASS != xSemaphoreTake(g_bl_sec_sha_mutex, portMAX_DELAY)) {
        blog_error("sha semphr take failed\r\n");
        return -1;
    }
    return 0;
}

int bl_sha_mutex_give()
{
    if (pdPASS != xSemaphoreGive(g_bl_sec_sha_mutex)) {
        blog_error("sha semphr give failed\\n");
        return -1;
    }
    return 0;
}

void bl_sha_init(bl_sha_ctx_t *ctx, const bl_sha_type_t type)
{
    const SEC_ENG_SHA_Type sha_type = (SEC_ENG_SHA_Type)type; // bl_sha_type_t is the same as SEC_ENG_SHA_Type in driver

    Sec_Eng_SHA256_Init((SEC_Eng_SHA256_Ctx *)&ctx->sha_ctx, BL_SHA_ID, sha_type, ctx->tmp, ctx->pad);
    Sec_Eng_SHA_Start(BL_SHA_ID);
}

int bl_sha_update(bl_sha_ctx_t *ctx, const uint8_t *input, uint32_t len)
{
    return Sec_Eng_SHA256_Update((SEC_Eng_SHA256_Ctx *)&ctx->sha_ctx, BL_SHA_ID, input, len);
}

int bl_sha_finish(bl_sha_ctx_t *ctx, uint8_t *hash)
{
    return Sec_Eng_SHA256_Finish((SEC_Eng_SHA256_Ctx *)&ctx->sha_ctx, BL_SHA_ID, hash);
}

static const uint8_t shaSrcBuf1[64] =
{
    '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
    '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
    '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
    '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1',
};

static void SHA_Compare_Data(const uint8_t *expected, const uint8_t *input, uint32_t len)
{
    int i = 0, is_failed = 0;

    for (i = 0; i < len; i++) {
        if (input[i] != expected[i]) {
            is_failed = 1;
            blog_print("%s[%02d], %02x %02x\r\n",
                input[i] ==expected[i] ? "S" : "F",
                i,
                input[i],
                expected[i]
            );
        }
    }
    if (is_failed) {
        blog_print("====== Failed %lu Bytes======\r\n", len);
    } else {
        blog_print("====== Success %lu Bytes=====\r\n", len);
    }
}

void sha256_test_case0(void)
{
    SEC_ENG_SHA_ID_Type shaId = SEC_ENG_SHA_ID0;
    sha256_link_item_t sha256_link = {
        .linkCfg.shaMode = SEC_ENG_SHA256,
        .linkCfg.shaHashSel = 0,
        .linkCfg.shaIntClr = 0,
        .linkCfg.shaIntSet = 1,
        .linkCfg.shaMsgLen = 1,
        .linkCfg.shaSrcAddr = 0x50020000,
    };
    static const uint8_t sha256_test_result[] = 
    {
        0x31, 0x38, 0xbb, 0x9b, 0xc7, 0x8d, 0xf2, 0x7c, 0x47, 0x3e, 0xcf, 0xd1, 0x41, 0x0f, 0x7b, 0xd4,
        0x5e, 0xba, 0xc1, 0xf5, 0x9c, 0xf3, 0xff, 0x9c, 0xfe, 0x4d, 0xb7, 0x7a, 0xab, 0x7a, 0xed, 0xd3, 
    };


#define SEC_SHA_IRQn (IRQ_NUM_BASE+14)

    bl_irq_register(SEC_SHA_IRQn, bl_sec_sha_IRQHandler);
    bl_irq_enable(SEC_SHA_IRQn);

    Sec_Eng_SHA_Enable_Link(shaId);
    Sec_Eng_SHA256_Link_Init(&sha256_link.ctx, shaId,
            (uint32_t)&sha256_link.linkCfg,
            sha256_link.tmp,
            sha256_link.pad
    );
    Sec_Eng_SHA256_Link_Update(&sha256_link.ctx, shaId,
            shaSrcBuf1,
            64
    );
    //FIXME Request to change driver API
    Sec_Eng_SHA256_Link_Finish(&sha256_link.ctx, shaId, (uint8_t*)sha256_link.linkCfg.result);
    Sec_Eng_SHA_Disable_Link(shaId);

    SHA_Compare_Data((const uint8_t*)sha256_link.linkCfg.result, sha256_test_result, sizeof(sha256_test_result));
}

int bl_sec_sha_test(void)
{
    puts("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\r\n");
    puts("^^^^^^^^^^^^^^^^^^^^^^^SHA256 TEST CASE^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\r\n");
    sha256_test_case0();
    puts("------------------------------------------------------------------------------------\r\n");

    return 0;
}
static void _clear_sha_int()
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t val;

    val = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    val = BL_SET_REG_BIT(val, SEC_ENG_SE_SHA_0_INT_CLR_1T);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, val);
}

void bl_sec_sha_IRQHandler(void)
{
    puts("--->>> SHA IRQ\r\n");
    _clear_sha_int();
}
