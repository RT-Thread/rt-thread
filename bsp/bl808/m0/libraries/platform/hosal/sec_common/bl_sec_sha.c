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
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include <FreeRTOS.h>
#include <semphr.h>

#include <bl_irq.h>
#include <bl_sec.h>
#include "bl_sec_common.h"
#include "bl_sec_hw_common.h"

#include <blog.h>

#define BL_SHA_ID SEC_ENG_SHA_ID0 // this is the only valid value

#ifdef BL602
static bl_SEC_Eng_SHA_Link_Config_Type working_link_cfg __attribute__((section(".wifi_ram")));
#elif defined BL616
// Nothing
#else
#error "No support for this chip"
#endif

int bl_sec_sha_init()
{
#ifdef BL616
    Sec_Eng_Group0_Request_SHA_Access();
#endif
    Sec_Eng_SHA_Enable_Link(BL_SHA_ID);

    return 0;
}

int bl_sha_mutex_take()
{
    taskENTER_CRITICAL();
    return 0;
}

int bl_sha_mutex_give()
{
    taskEXIT_CRITICAL();
    return 0;
}

#ifdef BL602
static bool is_tcm_addr(void *addr)
{
    uintptr_t addr_masked = (uintptr_t)addr & 0x0FFFFFFFUL;

    // Checking upper boundary ought to be enough
    #define BL602_END_OF_DTCM 0x02020000UL
    if (addr_masked < BL602_END_OF_DTCM) {
        return true;
    }
    return false;
}
#endif

static int bl_to_drv_type(bl_sha_type_t type)
{
    const uint8_t map[] = {
        [BL_SHA1] = SEC_ENG_SHA1,
        [BL_SHA224] = SEC_ENG_SHA224,
        [BL_SHA256] = SEC_ENG_SHA256,
#ifdef MD5_CAPABLE
        [BL_MD5] = SEC_ENG_MD5,
#endif
#ifdef SHA512_CAPABLE
        [BL_SHA384] = SEC_ENG_SHA384,
        [BL_SHA512] = SEC_ENG_SHA512,
#endif
    };
    if (type < sizeof(map)) {
        return map[type];
    }
    return -1;
}


/*
 * SHA1/SHA224/SHA256
 */
int bl_sha_init(bl_sha_ctx_t *ctx, const bl_sha_type_t type)
{
    if (!(type == BL_SHA1 || type == BL_SHA224 || type == BL_SHA256)) {
        return -1;
    }
    const SEC_ENG_SHA_Type sha_type = (SEC_ENG_SHA_Type)bl_to_drv_type(type);

#ifdef BL616
    if (bl_sec_is_cache_addr(ctx)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)ctx, sizeof(*ctx));
        ctx = bl_sec_get_no_cache_addr(ctx);
    }
#endif
    memset(ctx, 0, sizeof(*ctx));
    ctx->type = type;
    SEC_Eng_SHA_Link_Config_Type *lc = (SEC_Eng_SHA_Link_Config_Type *)&ctx->link_cfg;
    lc->shaMode = sha_type;
    lc->shaIntSet = 1;
    lc->shaIntClr = 1;
    bl_SEC_Eng_SHA_Link_Config_Type *link_cfg = &ctx->link_cfg;
#ifdef BL602
    if (is_tcm_addr(ctx)) {
        link_cfg = &working_link_cfg;
    }
#endif
    Sec_Eng_SHA256_Link_Init((SEC_Eng_SHA256_Link_Ctx *)&ctx->ctx, BL_SHA_ID, (uint32_t)link_cfg, ctx->tmp, ctx->pad);
    return 0;
}

int bl_sha_clone(bl_sha_ctx_t *dst, const bl_sha_ctx_t *src)
{
    if (!(dst && src)) {
        return -1;
    }

#ifdef BL616
    if (bl_sec_is_cache_addr(dst)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)dst, sizeof(*dst));
    }
    if (bl_sec_is_cache_addr(src)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)src, sizeof(*src));
    }
    dst = bl_sec_get_no_cache_addr(dst);
    src = bl_sec_get_no_cache_addr(src);
#endif
    *dst = *src;
    dst->ctx.shaBuf = dst->tmp;
    dst->ctx.shaPadding = dst->pad;
    dst->ctx.linkAddr = (uint32_t)&dst->link_cfg;
#ifdef BL602
    if (is_tcm_addr(dst)) {
        dst->ctx.linkAddr = (uint32_t)&working_link_cfg;
    }
#endif
    return 0;
}

int bl_sha_update(bl_sha_ctx_t *ctx, const uint8_t *input, uint32_t len)
{
#ifdef BL602
    if (is_tcm_addr(ctx)) {
        ARCH_MemCpy_Fast(&working_link_cfg, &ctx->link_cfg, sizeof(working_link_cfg));
    }
#elif defined BL616
    ctx = bl_sec_get_no_cache_addr(ctx);
    if (bl_sec_is_cache_addr(input)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)input, len);
    }
#endif
    Sec_Eng_SHA256_Link_Update((SEC_Eng_SHA256_Link_Ctx *)&ctx->ctx, BL_SHA_ID, input, len);
#ifdef BL602
    if (is_tcm_addr(ctx)) {
        ARCH_MemCpy_Fast(&ctx->link_cfg, &working_link_cfg, sizeof(working_link_cfg));
    }
#endif
    return 0;
}

int bl_sha_finish(bl_sha_ctx_t *ctx, uint8_t *hash)
{
#ifdef BL602
    if (is_tcm_addr(ctx)) {
        ARCH_MemCpy_Fast(&working_link_cfg, &ctx->link_cfg, sizeof(working_link_cfg));
    }
#elif defined BL616
    ctx = bl_sec_get_no_cache_addr(ctx);
#endif
    Sec_Eng_SHA256_Link_Finish((SEC_Eng_SHA256_Link_Ctx *)&ctx->ctx, BL_SHA_ID, hash);
    return 0;
}


/*
 * SHA384/SHA512
 */
#ifdef SHA512_CAPABLE
int bl_sha512_init(bl_sha512_ctx_t *ctx, const bl_sha_type_t type)
{
    if (!(type == BL_SHA384 || type == BL_SHA512)) {
        return -1;
    }
    const SEC_ENG_SHA_Type sha_type = (SEC_ENG_SHA_Type)bl_to_drv_type(type);

#ifdef BL616
    if (bl_sec_is_cache_addr(ctx)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)ctx, sizeof(*ctx));
        ctx = bl_sec_get_no_cache_addr(ctx);
    }
#endif
    memset(ctx, 0, sizeof(*ctx));
    ctx->type = type;
    SEC_Eng_SHA_Link_Config_Type *lc = (SEC_Eng_SHA_Link_Config_Type *)&ctx->link_cfg;
    lc->shaMode = sha_type;
    lc->shaIntSet = 1;
    lc->shaIntClr = 1;
    bl_SEC_Eng_SHA_Link_Config_Type *link_cfg = &ctx->link_cfg;
    Sec_Eng_SHA512_Link_Init((SEC_Eng_SHA512_Link_Ctx *)&ctx->ctx, BL_SHA_ID, (uint32_t)link_cfg, ctx->tmp, ctx->pad);
    return 0;
}

int bl_sha512_clone(bl_sha512_ctx_t *dst, const bl_sha512_ctx_t *src)
{
    if (!(dst && src)) {
        return -1;
    }

#ifdef BL616
    if (bl_sec_is_cache_addr(dst)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)dst, sizeof(*dst));
    }
    if (bl_sec_is_cache_addr(src)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)src, sizeof(*src));
    }
    dst = bl_sec_get_no_cache_addr(dst);
    src = bl_sec_get_no_cache_addr(src);
#endif
    *dst = *src;
    dst->ctx.shaBuf = dst->tmp;
    dst->ctx.shaPadding = dst->pad;
    dst->ctx.linkAddr = (uint32_t)&dst->link_cfg;
    return 0;
}

int bl_sha512_update(bl_sha512_ctx_t *ctx, const uint8_t *input, uint32_t len)
{
#ifdef BL616
    ctx = bl_sec_get_no_cache_addr(ctx);
    if (bl_sec_is_cache_addr(input)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)input, len);
    }
#endif
    Sec_Eng_SHA512_Link_Update((SEC_Eng_SHA512_Link_Ctx *)&ctx->ctx, BL_SHA_ID, input, len);
    return 0;
}

int bl_sha512_finish(bl_sha512_ctx_t *ctx, uint8_t *hash)
{
#ifdef BL616
    ctx = bl_sec_get_no_cache_addr(ctx);
#endif
    Sec_Eng_SHA512_Link_Finish((SEC_Eng_SHA512_Link_Ctx *)&ctx->ctx, BL_SHA_ID, hash);
    return 0;
}
#endif // SHA512_CAPABLE


/*
 * Test cases
 */
#include <stdlib.h>

static const char tc_hash_input[] = "The quick brown fox jumps over the lazy dog";
bool tc_sha1()
{
    int i;
    const bl_sha_type_t types[] = {BL_SHA1, BL_SHA224, BL_SHA256};
    uint8_t result[32];
    const uint8_t expected_results[][32] = {
        {0x2f, 0xd4, 0xe1, 0xc6, 0x7a, 0x2d, 0x28, 0xfc, 0xed, 0x84, 0x9e, 0xe1, 0xbb, 0x76, 0xe7, 0x39, 0x1b, 0x93, 0xeb, 0x12, },
        {0x73, 0x0e, 0x10, 0x9b, 0xd7, 0xa8, 0xa3, 0x2b, 0x1c, 0xb9, 0xd9, 0xa0, 0x9a, 0xa2, 0x32, 0x5d, 0x24, 0x30, 0x58, 0x7d, 0xdb, 0xc0, 0xc3, 0x8b, 0xad, 0x91, 0x15, 0x25, },
        {0xd7, 0xa8, 0xfb, 0xb3, 0x07, 0xd7, 0x80, 0x94, 0x69, 0xca, 0x9a, 0xbc, 0xb0, 0x08, 0x2e, 0x4f, 0x8d, 0x56, 0x51, 0xe4, 0x6d, 0x3c, 0xdb, 0x76, 0x2d, 0x02, 0xd0, 0xbf, 0x37, 0xc9, 0xe5, 0x92, },
    };

    const uint8_t z_2047_expected[][32] = {
		{0xe3, 0x59, 0x9e, 0xf5, 0x8f, 0x6c, 0x1b, 0x77, 0x66, 0xf0, 0x45, 0x31, 0xb5, 0x01, 0xec, 0x24, 0x97, 0xb2, 0xa8, 0x2e, },
		{0xe6, 0xdb, 0x06, 0x25, 0xba, 0xb0, 0x0a, 0x65, 0xeb, 0x25, 0xeb, 0xcb, 0xe6, 0xd5, 0xc3, 0xb6, 0x6b, 0x04, 0xad, 0x12, 0xc8, 0x91, 0x25, 0xa3, 0x4e, 0x10, 0xfe, 0x6c, },
		{0xa6, 0xb4, 0xc4, 0x6a, 0xa0, 0xaa, 0xce, 0x53, 0x8f, 0x48, 0x4c, 0x2c, 0x7d, 0x3c, 0x96, 0x4b, 0x2c, 0x10, 0xb1, 0x95, 0x9b, 0xe4, 0xf9, 0xc6, 0x57, 0xa2, 0x7b, 0x37, 0xb6, 0xe7, 0x00, 0xe5, },
    };

    while (1) {
        uint8_t *in_buf;
        bl_sha_ctx_t *ctx;

        for (int i = 0; i < 1; ++i) {
            in_buf = malloc(2047);
            ctx = malloc(sizeof(*ctx));
            if (!in_buf || !ctx) {
                printf("Over!\r\n");
                while (1) {
                }
            }
        }
        printf("Test addr %p\r\n", ctx);
        for (int j = 0; j < 1 * 1000; ++j) {
            for (i = 0; i < sizeof(types) / sizeof(types[0]); ++i) {
                size_t len = sizeof(tc_hash_input) - 1;
                memcpy(in_buf, tc_hash_input, len);
                bl_sha_init(ctx, types[i]);
                bl_sha_update(ctx, in_buf, len);
                memset(result, 0, sizeof(result));
                bl_sha_finish(ctx, result);
                if (memcmp(result, expected_results[i], 32) != 0) {
                    printf("SHA1 #%d failed\r\n", i);
                    return false;
                }

                // input from flash
                bl_sha_init(ctx, types[i]);
                bl_sha_update(ctx, (void *)tc_hash_input, len);
                memset(result, 0, sizeof(result));
                bl_sha_finish(ctx, result);
                if (memcmp(result, expected_results[i], 32) != 0) {
                    printf("SHA1 input from flash #%d failed\r\n", i);
                    return false;
                }

                // 2047 Zs
                size_t left = 2047;
                memset(in_buf, 'Z', 2047);
                bl_sha_init(ctx, types[i]);
                while (left > 0) {
                    size_t l = (bl_rand() & 0xFFU) + 1;
                    if (l > left) {
                        l = left;
                    }
                    bl_sha_update(ctx, in_buf + (2047 - left), l);
                    left -= l;
                }
                memset(result, 0, sizeof(result));
                bl_sha_finish(ctx, result);
                if (memcmp(result, z_2047_expected[i], 32) != 0) {
                    printf("SHA 2047-Z #%d failed\r\n", i);
                    return false;
                }
            }
        }
    }
    return true;
}

#ifdef SHA512_CAPABLE
bool tc_sha512()
{
    int i;
    const bl_sha_type_t types[] = {
        BL_SHA384, BL_SHA512,
    };
    uint8_t result[64];
    const uint8_t expected_results[][64] = {
        {0xca, 0x73, 0x7f, 0x10, 0x14, 0xa4, 0x8f, 0x4c, 0x0b, 0x6d, 0xd4, 0x3c, 0xb1, 0x77, 0xb0, 0xaf, 0xd9, 0xe5, 0x16, 0x93, 0x67, 0x54, 0x4c, 0x49, 0x40, 0x11, 0xe3, 0x31, 0x7d, 0xbf, 0x9a, 0x50, 0x9c, 0xb1, 0xe5, 0xdc, 0x1e, 0x85, 0xa9, 0x41, 0xbb, 0xee, 0x3d, 0x7f, 0x2a, 0xfb, 0xc9, 0xb1, },
        {0x07, 0xe5, 0x47, 0xd9, 0x58, 0x6f, 0x6a, 0x73, 0xf7, 0x3f, 0xba, 0xc0, 0x43, 0x5e, 0xd7, 0x69, 0x51, 0x21, 0x8f, 0xb7, 0xd0, 0xc8, 0xd7, 0x88, 0xa3, 0x09, 0xd7, 0x85, 0x43, 0x6b, 0xbb, 0x64, 0x2e, 0x93, 0xa2, 0x52, 0xa9, 0x54, 0xf2, 0x39, 0x12, 0x54, 0x7d, 0x1e, 0x8a, 0x3b, 0x5e, 0xd6, 0xe1, 0xbf, 0xd7, 0x09, 0x78, 0x21, 0x23, 0x3f, 0xa0, 0x53, 0x8f, 0x3d, 0xb8, 0x54, 0xfe, 0xe6, },
    };

    const uint8_t z_2047_expected[][64] = {
        {0x34, 0x1e, 0x3b, 0xd8, 0xf2, 0x3e, 0xc0, 0x3a, 0x26, 0x8a, 0x1d, 0x16, 0xc3, 0xe9, 0xf8, 0x0c, 0xeb, 0x5a, 0xd0, 0xe5, 0xf9, 0x79, 0x88, 0xa6, 0x2d, 0x39, 0x0b, 0x0e, 0x18, 0xb3, 0x1c, 0x42, 0x2c, 0xa0, 0x93, 0x72, 0x5a, 0x05, 0x94, 0x11, 0x3e, 0x65, 0x36, 0x16, 0x36, 0xcf, 0xe3, 0x24, },
        {0x62, 0x8e, 0x01, 0x46, 0x09, 0x53, 0x24, 0x5e, 0x40, 0x84, 0xe9, 0x06, 0x5b, 0x04, 0x7a, 0x92, 0xf5, 0xf6, 0x72, 0x7f, 0xfb, 0x93, 0x96, 0x35, 0x92, 0xed, 0xc9, 0x3b, 0xea, 0x62, 0x01, 0xf5, 0x66, 0x43, 0xf4, 0x9e, 0x70, 0xdf, 0x3c, 0x2a, 0x25, 0x19, 0xa6, 0xbc, 0x98, 0x36, 0xfe, 0x85, 0x05, 0xd1, 0x99, 0x76, 0x6d, 0x02, 0x35, 0xc5, 0x64, 0xbb, 0x16, 0x1f, 0x9b, 0x60, 0x99, 0x07, },
    };
    while (1) {
        uint8_t *in_buf;
        bl_sha512_ctx_t *ctx;

        for (int i = 0; i < 1; ++i) {
            in_buf = malloc(2047);
            ctx = malloc(sizeof(*ctx));
            if (!in_buf || !ctx) {
                printf("Over!\r\n");
                while (1) {
                }
            }
        }
        printf("Test addr %p\r\n", ctx);
        for (int j = 0; j < 1 * 1000; ++j) {
            for (i = 0; i < sizeof(types) / sizeof(types[0]); ++i) {
                size_t len = sizeof(tc_hash_input) - 1;
                memcpy(in_buf, tc_hash_input, len);
                bl_sha512_init(ctx, types[i]);
                bl_sha512_update(ctx, in_buf, len);
                memset(result, 0, sizeof(result));
                bl_sha512_finish(ctx, result);
                if (memcmp(result, expected_results[i], 64) != 0) {
                    printf("SHA512 #%d failed\r\n", i);
                    return false;
                }

                // input from flash
                bl_sha512_init(ctx, types[i]);
                bl_sha512_update(ctx, (void *)tc_hash_input, len);
                memset(result, 0, sizeof(result));
                bl_sha512_finish(ctx, result);
                if (memcmp(result, expected_results[i], 64) != 0) {
                    printf("SHA512 input from flash #%d failed\r\n", i);
                    return false;
                }

                // 2047 Zs
                size_t left = 2047;
                memset(in_buf, 'Z', 2047);
                bl_sha512_init(ctx, types[i]);
                while (left > 0) {
                    size_t l = (bl_rand() & 0xFFU) + 1;
                    if (l > left) {
                        l = left;
                    }
                    bl_sha512_update(ctx, in_buf + (2047 - left), l);
                    left -= l;
                }
                memset(result, 0, sizeof(result));
                bl_sha512_finish(ctx, result);
                if (memcmp(result, z_2047_expected[i], 64) != 0) {
                    printf("SHA 2047-Z #%d failed\r\n", i);
                    return false;
                }
            }
        }
    }
    return true;
}
#endif

#define MD(tc) {tc, #tc}
static struct {
    bool (*tc_fun)(void);
    const char *desc;
} tc[] = {
    MD(tc_sha1),
#ifdef SHA512_CAPABLE
    MD(tc_sha512),
#endif
};

int bl_sec_sha_test(void)
{
    for (int i = 0; i < sizeof(tc) / sizeof(tc[0]); ++i) {
        printf("Running test case %s\r\n", tc[i].desc);
        if (tc[i].tc_fun()) {
            printf("\t\tPassed\r\n");
        } else {
            printf("\t\tFailed\r\n");
        }
    }
    return 0;
}
