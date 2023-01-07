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
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <utils_bitmap_window.h>

int utils_bitmap_window_init(struct utils_bitmap_ctx *ctx, int ssn, int ssn_max)
{
    memset(ctx, 0, sizeof(struct utils_bitmap_ctx));
    ctx->ssn = ssn;
    ctx->ssn_duration = ssn_max + 1;//ssn start from 0

    return 0;
}

int utils_bitmap_window_bit_set(struct utils_bitmap_ctx *ctx, int bit_pos)
{
    int i;
    int pos_offset;

    if (bit_pos < ctx->ssn) {
        /*failed case*/
        if (ctx->ssn_duration - ctx->ssn + bit_pos + 1 > sizeof(ctx->bitmap) * 8) {
            printf("small ssn %d\r\n", bit_pos);
            return -INT_MAX;
        }
    }
    pos_offset = bit_pos + ctx->ssn_duration - ctx->ssn;
    if (pos_offset >= ctx->ssn_duration) {
        pos_offset -= ctx->ssn_duration;
    }

    if (ctx->bitmap.map64 & (1 << pos_offset)) {
        printf("Dup bit_pos %d with pos_offset %d\r\n", bit_pos, pos_offset);
        return -bit_pos;
    }
    ctx->bitmap.map64 |= (1 << pos_offset);//TODO use bytearray

    for (i = 0; i < sizeof(ctx->bitmap.bytes) * 8; i++) {
        if (ctx->bitmap.map64 & 0x1) {
            ctx->bitmap.map64 >>= 1;
            ctx->ssn += 1;
            if (ctx->ssn == ctx->ssn_duration) {
                ctx->ssn = 0;
            }
        }
    }
    return pos_offset;
}

uint64_t utils_bitmap_window_map_get(struct utils_bitmap_ctx *ctx)
{
    return ctx->bitmap.map64;
}

int utils_bitmap_window_ssn_get(struct utils_bitmap_ctx *ctx)
{
    return ctx->ssn;
}
