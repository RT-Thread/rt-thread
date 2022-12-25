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
#include <bl_sec.h>
#include "bl_sec_hw_common.h"
#include <bl_sec_aes.h>

#define AES_ID SEC_ENG_AES_ID0

int bl_sec_aes_init()
{
#ifdef BL616
    Sec_Eng_Group0_Request_AES_Access();
#endif
    Sec_Eng_AES_Enable_BE(AES_ID);
    return 0;
}

int bl_aes_acquire_hw()
{
    taskENTER_CRITICAL();
    return 0;
}

int bl_aes_release_hw()
{
    taskEXIT_CRITICAL();
    return 0;
}

int bl_aes_init(bl_sec_aes_t *aes)
{
    if (!aes) {
        return -1;
    }
#ifdef BL616
    if (bl_sec_is_cache_addr(aes)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)aes, sizeof(*aes));
        aes = bl_sec_get_no_cache_addr(aes);
    }
#endif
    memset(aes, 0, sizeof(*aes));
    aes->link_cfg.aesIntClr = 1;
    aes->link_cfg.aesBlockMode = SEC_ENG_AES_ECB;

    return 0;
}

int bl_aes_set_key(bl_sec_aes_t *aes, bl_sec_aes_op_t op, const uint8_t *key, size_t key_len)
{
    if (!(aes && key && (key_len == 16 || key_len == 24 || key_len == 32))) {
        return -1;
    }
    (void)op;

#ifdef BL616
    aes = bl_sec_get_no_cache_addr(aes);
#endif

    aes->link_cfg.aesDecKeySel = SEC_ENG_AES_USE_NEW;
    SEC_ENG_AES_Key_Type key_type;
    if (key_len == 16) {
        key_type = SEC_ENG_AES_KEY_128BITS;
    } else if (key_len == 24) {
        key_type = SEC_ENG_AES_KEY_192BITS;
    } else {
        key_type = SEC_ENG_AES_KEY_256BITS;
    }
    aes->link_cfg.aesMode = key_type;
    memcpy(&aes->link_cfg.aesKey0, key, key_len);

    return 0;
}

int bl_aes_transform(bl_sec_aes_t *aes, bl_sec_aes_op_t op, const uint8_t *input, uint8_t *output)
{
    const uint16_t n_blk = 1;
    if (!(aes && input && output)) {
        return -1;
    }

#ifdef BL616
    aes = bl_sec_get_no_cache_addr(aes);
    if (bl_sec_is_cache_addr(input)) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)input, 16);
    }
    if (bl_sec_is_cache_addr(output) && input != output) {
        L1C_DCache_Clean_Invalid_By_Addr((uintptr_t)output, 16);
    }
#endif
    aes->link_cfg.aesMsgLen = n_blk;
    if (op == BL_AES_ENCRYPT) {
        aes->link_cfg.aesDecEn = SEC_ENG_AES_ENCRYPTION;
    } else {
        aes->link_cfg.aesDecEn = SEC_ENG_AES_DECRYPTION;
    }

    Sec_Eng_AES_Enable_Link(AES_ID);
    Sec_Eng_AES_Link_Work(AES_ID, (uint32_t)&aes->link_cfg, input, n_blk << 4, output);
    Sec_Eng_AES_Disable_Link(AES_ID);

    return 0;
}


/*
 * Test cases
 */
#include <stdbool.h>
#include <stdlib.h>

bool tc_aes_ecb()
{
    const void *plaintext = "Bouffalo Lab Ltd";
    const void *keys[3] = {
        "0123456789ABCDEF",
        "0123456789ABCDEF01234567",
        "0123456789ABCDEF0123456789ABCDEF",
    };
    const uint8_t ciphertext[][16] = {
        {0x36, 0x6B, 0xE1, 0x1E, 0xB7, 0x89, 0x31, 0x23, 0xBD, 0x7A, 0x27, 0xAE, 0x46, 0xC4, 0x28, 0x7D},
        {0xBD, 0x1A, 0x22, 0xD1, 0x76, 0xC5, 0x8B, 0x53, 0x83, 0xE7, 0xB7, 0x26, 0xD6, 0x33, 0x2B, 0x61},
        {0xCC, 0xB7, 0x21, 0xB9, 0x7B, 0x18, 0x43, 0xA0, 0x5B, 0xA9, 0x2C, 0x55, 0xF1, 0x4D, 0x24, 0xF0},
    };
    const uint8_t keylen[3] = {16, 24, 32};

    uint8_t output[16];

    while (1) {
        bl_sec_aes_t *aes = malloc(sizeof(*aes));
        void *buf = malloc(16);

        if (!aes || !buf) {
            printf("Over\r\n");
            return true;
        }

        printf("Test addr %p\r\n", aes);
        for (int i = 0; i < 3; ++i) {
            // 3 key lengths
            for (int j = 0; j < 2; ++j) {
                // 2 data sources
                for (int k = 0; k < 2; ++k) {
                    // encrypt/decrypt
                    bl_sec_aes_op_t op = BL_AES_ENCRYPT;
                    if (k == 1) {
                        op = BL_AES_DECRYPT;
                    }
                    void *input = NULL;
                    if (j == 0) {
                        // input from flash
                        if (k == 0) {
                            input = (void *)plaintext;
                        } else {
                            input = (void *)ciphertext[i];
                        }
                    } else {
                        // input from ram
                        input = buf;
                        if (k == 0) {
                            memcpy(input, plaintext, 16);
                        } else {
                            memcpy(input, ciphertext[i], 16);
                        }
                    }

                    memset(output, 0, sizeof(output));
                    bl_aes_init(aes);
                    bl_aes_set_key(aes, op, keys[i], keylen[i]);
                    bl_aes_transform(aes, op, input, output);
                    const void *exp_result = ciphertext[i];
                    if (k == 1) {
                        exp_result = plaintext;
                    }
                    if (memcmp(output, exp_result, 16)) {
                        printf("AES-ECB (%d,%d,%d) failed\r\n", i, j, k);
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

#define MD(tc) {tc, #tc}
static struct {
    bool (*tc_fun)(void);
    const char *desc;
} tc[] = {
    MD(tc_aes_ecb),
};

int bl_sec_aes_mem_test(void)
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
