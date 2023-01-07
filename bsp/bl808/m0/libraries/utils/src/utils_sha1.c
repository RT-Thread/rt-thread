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

#ifdef UTILS_SHA1


#include <stdlib.h>
#include <string.h>
#include "iot_import.h"
#include "iotx_log.h"
#include "utils_sha1.h"

/* Implementation that should never be optimized out by the compiler */
static void utils_sha1_zeroize(void *v, size_t n)
{
    volatile unsigned char *p = v;
    while (n--) {
        *p++ = 0;
    }
}

/*
 * 32-bit integer manipulation macros (big endian)
 */
#ifndef IOT_SHA1_GET_UINT32_BE
#define IOT_SHA1_GET_UINT32_BE(n,b,i)                            \
    {                                                       \
        (n) = ( (uint32_t) (b)[(i)    ] << 24 )             \
              | ( (uint32_t) (b)[(i) + 1] << 16 )             \
              | ( (uint32_t) (b)[(i) + 2] <<  8 )             \
              | ( (uint32_t) (b)[(i) + 3]       );            \
    }
#endif

#ifndef IOT_SHA1_PUT_UINT32_BE
#define IOT_SHA1_PUT_UINT32_BE(n,b,i)                            \
    {                                                       \
        (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
        (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
        (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
        (b)[(i) + 3] = (unsigned char) ( (n)       );       \
    }
#endif

void utils_sha1_init(iot_sha1_context *ctx)
{
    memset(ctx, 0, sizeof(iot_sha1_context));
}

void utils_sha1_free(iot_sha1_context *ctx)
{
    if (ctx == NULL) {
        return;
    }

    utils_sha1_zeroize(ctx, sizeof(iot_sha1_context));
}

void utils_sha1_clone(iot_sha1_context *dst,
                      const iot_sha1_context *src)
{
    *dst = *src;
}

/*
 * SHA-1 context setup
 */
void utils_sha1_starts(iot_sha1_context *ctx)
{
    ctx->total[0] = 0;
    ctx->total[1] = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xC3D2E1F0;
}

void utils_sha1_process(iot_sha1_context *ctx, const unsigned char data[64])
{
    uint32_t temp, W[16], A, B, C, D, E;

    IOT_SHA1_GET_UINT32_BE(W[ 0], data,  0);
    IOT_SHA1_GET_UINT32_BE(W[ 1], data,  4);
    IOT_SHA1_GET_UINT32_BE(W[ 2], data,  8);
    IOT_SHA1_GET_UINT32_BE(W[ 3], data, 12);
    IOT_SHA1_GET_UINT32_BE(W[ 4], data, 16);
    IOT_SHA1_GET_UINT32_BE(W[ 5], data, 20);
    IOT_SHA1_GET_UINT32_BE(W[ 6], data, 24);
    IOT_SHA1_GET_UINT32_BE(W[ 7], data, 28);
    IOT_SHA1_GET_UINT32_BE(W[ 8], data, 32);
    IOT_SHA1_GET_UINT32_BE(W[ 9], data, 36);
    IOT_SHA1_GET_UINT32_BE(W[10], data, 40);
    IOT_SHA1_GET_UINT32_BE(W[11], data, 44);
    IOT_SHA1_GET_UINT32_BE(W[12], data, 48);
    IOT_SHA1_GET_UINT32_BE(W[13], data, 52);
    IOT_SHA1_GET_UINT32_BE(W[14], data, 56);
    IOT_SHA1_GET_UINT32_BE(W[15], data, 60);

#define S(x,n) ((x << n) | ((x & 0xFFFFFFFF) >> (32 - n)))

#define R(t)                                            \
    (                                                       \
            temp = W[( t -  3 ) & 0x0F] ^ W[( t - 8 ) & 0x0F] ^ \
                   W[( t - 14 ) & 0x0F] ^ W[  t       & 0x0F],  \
            ( W[t & 0x0F] = S(temp,1) )                         \
    )

#define P(a,b,c,d,e,x)                                  \
    {                                                       \
        e += S(a,5) + F(b,c,d) + K + x; b = S(b,30);        \
    }

    A = ctx->state[0];
    B = ctx->state[1];
    C = ctx->state[2];
    D = ctx->state[3];
    E = ctx->state[4];

#define F(x,y,z) (z ^ (x & (y ^ z)))
#define K 0x5A827999

    P(A, B, C, D, E, W[0]);
    P(E, A, B, C, D, W[1]);
    P(D, E, A, B, C, W[2]);
    P(C, D, E, A, B, W[3]);
    P(B, C, D, E, A, W[4]);
    P(A, B, C, D, E, W[5]);
    P(E, A, B, C, D, W[6]);
    P(D, E, A, B, C, W[7]);
    P(C, D, E, A, B, W[8]);
    P(B, C, D, E, A, W[9]);
    P(A, B, C, D, E, W[10]);
    P(E, A, B, C, D, W[11]);
    P(D, E, A, B, C, W[12]);
    P(C, D, E, A, B, W[13]);
    P(B, C, D, E, A, W[14]);
    P(A, B, C, D, E, W[15]);
    P(E, A, B, C, D, R(16));
    P(D, E, A, B, C, R(17));
    P(C, D, E, A, B, R(18));
    P(B, C, D, E, A, R(19));

#undef K
#undef F

#define F(x,y,z) (x ^ y ^ z)
#define K 0x6ED9EBA1

    P(A, B, C, D, E, R(20));
    P(E, A, B, C, D, R(21));
    P(D, E, A, B, C, R(22));
    P(C, D, E, A, B, R(23));
    P(B, C, D, E, A, R(24));
    P(A, B, C, D, E, R(25));
    P(E, A, B, C, D, R(26));
    P(D, E, A, B, C, R(27));
    P(C, D, E, A, B, R(28));
    P(B, C, D, E, A, R(29));
    P(A, B, C, D, E, R(30));
    P(E, A, B, C, D, R(31));
    P(D, E, A, B, C, R(32));
    P(C, D, E, A, B, R(33));
    P(B, C, D, E, A, R(34));
    P(A, B, C, D, E, R(35));
    P(E, A, B, C, D, R(36));
    P(D, E, A, B, C, R(37));
    P(C, D, E, A, B, R(38));
    P(B, C, D, E, A, R(39));

#undef K
#undef F

#define F(x,y,z) ((x & y) | (z & (x | y)))
#define K 0x8F1BBCDC

    P(A, B, C, D, E, R(40));
    P(E, A, B, C, D, R(41));
    P(D, E, A, B, C, R(42));
    P(C, D, E, A, B, R(43));
    P(B, C, D, E, A, R(44));
    P(A, B, C, D, E, R(45));
    P(E, A, B, C, D, R(46));
    P(D, E, A, B, C, R(47));
    P(C, D, E, A, B, R(48));
    P(B, C, D, E, A, R(49));
    P(A, B, C, D, E, R(50));
    P(E, A, B, C, D, R(51));
    P(D, E, A, B, C, R(52));
    P(C, D, E, A, B, R(53));
    P(B, C, D, E, A, R(54));
    P(A, B, C, D, E, R(55));
    P(E, A, B, C, D, R(56));
    P(D, E, A, B, C, R(57));
    P(C, D, E, A, B, R(58));
    P(B, C, D, E, A, R(59));

#undef K
#undef F

#define F(x,y,z) (x ^ y ^ z)
#define K 0xCA62C1D6

    P(A, B, C, D, E, R(60));
    P(E, A, B, C, D, R(61));
    P(D, E, A, B, C, R(62));
    P(C, D, E, A, B, R(63));
    P(B, C, D, E, A, R(64));
    P(A, B, C, D, E, R(65));
    P(E, A, B, C, D, R(66));
    P(D, E, A, B, C, R(67));
    P(C, D, E, A, B, R(68));
    P(B, C, D, E, A, R(69));
    P(A, B, C, D, E, R(70));
    P(E, A, B, C, D, R(71));
    P(D, E, A, B, C, R(72));
    P(C, D, E, A, B, R(73));
    P(B, C, D, E, A, R(74));
    P(A, B, C, D, E, R(75));
    P(E, A, B, C, D, R(76));
    P(D, E, A, B, C, R(77));
    P(C, D, E, A, B, R(78));
    P(B, C, D, E, A, R(79));

#undef K
#undef F

    ctx->state[0] += A;
    ctx->state[1] += B;
    ctx->state[2] += C;
    ctx->state[3] += D;
    ctx->state[4] += E;
}

/*
 * SHA-1 process buffer
 */
void utils_sha1_update(iot_sha1_context *ctx, const unsigned char *input, size_t ilen)
{
    size_t fill;
    uint32_t left;

    if (ilen == 0) {
        return;
    }

    left = ctx->total[0] & 0x3F;
    fill = 64 - left;

    ctx->total[0] += (uint32_t) ilen;
    ctx->total[0] &= 0xFFFFFFFF;

    if (ctx->total[0] < (uint32_t) ilen) {
        ctx->total[1]++;
    }

    if (left && ilen >= fill) {
        memcpy((void *)(ctx->buffer + left), input, fill);
        utils_sha1_process(ctx, ctx->buffer);
        input += fill;
        ilen  -= fill;
        left = 0;
    }

    while (ilen >= 64) {
        utils_sha1_process(ctx, input);
        input += 64;
        ilen  -= 64;
    }

    if (ilen > 0) {
        memcpy((void *)(ctx->buffer + left), input, ilen);
    }
}

static const unsigned char iot_sha1_padding[64] = {
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * SHA-1 final digest
 */
void utils_sha1_finish(iot_sha1_context *ctx, unsigned char output[20])
{
    uint32_t last, padn;
    uint32_t high, low;
    unsigned char msglen[8];

    high = (ctx->total[0] >> 29)
           | (ctx->total[1] <<  3);
    low  = (ctx->total[0] <<  3);

    IOT_SHA1_PUT_UINT32_BE(high, msglen, 0);
    IOT_SHA1_PUT_UINT32_BE(low,  msglen, 4);

    last = ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    utils_sha1_update(ctx, iot_sha1_padding, padn);
    utils_sha1_update(ctx, msglen, 8);

    IOT_SHA1_PUT_UINT32_BE(ctx->state[0], output,  0);
    IOT_SHA1_PUT_UINT32_BE(ctx->state[1], output,  4);
    IOT_SHA1_PUT_UINT32_BE(ctx->state[2], output,  8);
    IOT_SHA1_PUT_UINT32_BE(ctx->state[3], output, 12);
    IOT_SHA1_PUT_UINT32_BE(ctx->state[4], output, 16);
}


/*
 * output = SHA-1( input buffer )
 */
void utils_sha1(const unsigned char *input, size_t ilen, unsigned char output[20])
{
    iot_sha1_context ctx;

    utils_sha1_init(&ctx);
    utils_sha1_starts(&ctx);
    utils_sha1_update(&ctx, input, ilen);
    utils_sha1_finish(&ctx, output);
    utils_sha1_free(&ctx);
}

#endif