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


#include <FreeRTOS.h>
#include <task.h>
#include "utils_log.h"
#include "stdio.h"

#include "utils_fec.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MSG_CNT     3      /* message-length polynomials count */
#define POLY_CNT    14     /* (FEC_ECC_LENGTH*2)-length polynomialc count */

typedef struct {
    uint8_t   _id;
    uint8_t   _size;    /* Size of reserved memory for this polynomial */
    uint16_t  _offset;  /* Offset in memory */
    uint8_t*  _memory;  /* Pointer to pointer to memory */
    uint8_t   length;
} blpoly_t;

typedef struct {
    blpoly_t g_polynoms[MSG_CNT + POLY_CNT];
    uint8_t g_stack_memory[MSG_CNT * FEC_MSG_LENGTH + POLY_CNT * FEC_ECC_LENGTH * 2];
    uint8_t g_generator_cache[FEC_ECC_LENGTH + 1];
    uint8_t g_generator_cached_flag;/* false */
} fec_context_t;

enum POLY_ID {
    ID_MSG_IN = 0,
    ID_MSG_OUT,
    ID_GENERATOR,
    ID_TPOLY1,
    ID_TPOLY2,

    ID_MSG_E,

    ID_TPOLY3,
    ID_TPOLY4,

    ID_SYNDROMES,
    ID_FORNEY,

    ID_ERASURES_LOC,
    ID_ERRORS_LOC,

    ID_ERASURES,
    ID_ERRORS,

    ID_COEF_POS,
    ID_ERR_EVAL
};

/* GF tables pre-calculated for 0x11d primitive polynomial */
const uint8_t code_exp[512] = {
    0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1d, 0x3a, 0x74, 0xe8, 0xcd, 0x87, 0x13, 0x26, 0x4c,
    0x98, 0x2d, 0x5a, 0xb4, 0x75, 0xea, 0xc9, 0x8f, 0x3, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc0, 0x9d,
    0x27, 0x4e, 0x9c, 0x25, 0x4a, 0x94, 0x35, 0x6a, 0xd4, 0xb5, 0x77, 0xee, 0xc1, 0x9f, 0x23, 0x46,
    0x8c, 0x5, 0xa, 0x14, 0x28, 0x50, 0xa0, 0x5d, 0xba, 0x69, 0xd2, 0xb9, 0x6f, 0xde, 0xa1, 0x5f,
    0xbe, 0x61, 0xc2, 0x99, 0x2f, 0x5e, 0xbc, 0x65, 0xca, 0x89, 0xf, 0x1e, 0x3c, 0x78, 0xf0, 0xfd,
    0xe7, 0xd3, 0xbb, 0x6b, 0xd6, 0xb1, 0x7f, 0xfe, 0xe1, 0xdf, 0xa3, 0x5b, 0xb6, 0x71, 0xe2, 0xd9,
    0xaf, 0x43, 0x86, 0x11, 0x22, 0x44, 0x88, 0xd, 0x1a, 0x34, 0x68, 0xd0, 0xbd, 0x67, 0xce, 0x81,
    0x1f, 0x3e, 0x7c, 0xf8, 0xed, 0xc7, 0x93, 0x3b, 0x76, 0xec, 0xc5, 0x97, 0x33, 0x66, 0xcc, 0x85,
    0x17, 0x2e, 0x5c, 0xb8, 0x6d, 0xda, 0xa9, 0x4f, 0x9e, 0x21, 0x42, 0x84, 0x15, 0x2a, 0x54, 0xa8,
    0x4d, 0x9a, 0x29, 0x52, 0xa4, 0x55, 0xaa, 0x49, 0x92, 0x39, 0x72, 0xe4, 0xd5, 0xb7, 0x73, 0xe6,
    0xd1, 0xbf, 0x63, 0xc6, 0x91, 0x3f, 0x7e, 0xfc, 0xe5, 0xd7, 0xb3, 0x7b, 0xf6, 0xf1, 0xff, 0xe3,
    0xdb, 0xab, 0x4b, 0x96, 0x31, 0x62, 0xc4, 0x95, 0x37, 0x6e, 0xdc, 0xa5, 0x57, 0xae, 0x41, 0x82,
    0x19, 0x32, 0x64, 0xc8, 0x8d, 0x7, 0xe, 0x1c, 0x38, 0x70, 0xe0, 0xdd, 0xa7, 0x53, 0xa6, 0x51,
    0xa2, 0x59, 0xb2, 0x79, 0xf2, 0xf9, 0xef, 0xc3, 0x9b, 0x2b, 0x56, 0xac, 0x45, 0x8a, 0x9, 0x12,
    0x24, 0x48, 0x90, 0x3d, 0x7a, 0xf4, 0xf5, 0xf7, 0xf3, 0xfb, 0xeb, 0xcb, 0x8b, 0xb, 0x16, 0x2c,
    0x58, 0xb0, 0x7d, 0xfa, 0xe9, 0xcf, 0x83, 0x1b, 0x36, 0x6c, 0xd8, 0xad, 0x47, 0x8e, 0x1, 0x2,
    0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x1d, 0x3a, 0x74, 0xe8, 0xcd, 0x87, 0x13, 0x26, 0x4c, 0x98,
    0x2d, 0x5a, 0xb4, 0x75, 0xea, 0xc9, 0x8f, 0x3, 0x6, 0xc, 0x18, 0x30, 0x60, 0xc0, 0x9d, 0x27,
    0x4e, 0x9c, 0x25, 0x4a, 0x94, 0x35, 0x6a, 0xd4, 0xb5, 0x77, 0xee, 0xc1, 0x9f, 0x23, 0x46, 0x8c,
    0x5, 0xa, 0x14, 0x28, 0x50, 0xa0, 0x5d, 0xba, 0x69, 0xd2, 0xb9, 0x6f, 0xde, 0xa1, 0x5f, 0xbe,
    0x61, 0xc2, 0x99, 0x2f, 0x5e, 0xbc, 0x65, 0xca, 0x89, 0xf, 0x1e, 0x3c, 0x78, 0xf0, 0xfd, 0xe7,
    0xd3, 0xbb, 0x6b, 0xd6, 0xb1, 0x7f, 0xfe, 0xe1, 0xdf, 0xa3, 0x5b, 0xb6, 0x71, 0xe2, 0xd9, 0xaf,
    0x43, 0x86, 0x11, 0x22, 0x44, 0x88, 0xd, 0x1a, 0x34, 0x68, 0xd0, 0xbd, 0x67, 0xce, 0x81, 0x1f,
    0x3e, 0x7c, 0xf8, 0xed, 0xc7, 0x93, 0x3b, 0x76, 0xec, 0xc5, 0x97, 0x33, 0x66, 0xcc, 0x85, 0x17,
    0x2e, 0x5c, 0xb8, 0x6d, 0xda, 0xa9, 0x4f, 0x9e, 0x21, 0x42, 0x84, 0x15, 0x2a, 0x54, 0xa8, 0x4d,
    0x9a, 0x29, 0x52, 0xa4, 0x55, 0xaa, 0x49, 0x92, 0x39, 0x72, 0xe4, 0xd5, 0xb7, 0x73, 0xe6, 0xd1,
    0xbf, 0x63, 0xc6, 0x91, 0x3f, 0x7e, 0xfc, 0xe5, 0xd7, 0xb3, 0x7b, 0xf6, 0xf1, 0xff, 0xe3, 0xdb,
    0xab, 0x4b, 0x96, 0x31, 0x62, 0xc4, 0x95, 0x37, 0x6e, 0xdc, 0xa5, 0x57, 0xae, 0x41, 0x82, 0x19,
    0x32, 0x64, 0xc8, 0x8d, 0x7, 0xe, 0x1c, 0x38, 0x70, 0xe0, 0xdd, 0xa7, 0x53, 0xa6, 0x51, 0xa2,
    0x59, 0xb2, 0x79, 0xf2, 0xf9, 0xef, 0xc3, 0x9b, 0x2b, 0x56, 0xac, 0x45, 0x8a, 0x9, 0x12, 0x24,
    0x48, 0x90, 0x3d, 0x7a, 0xf4, 0xf5, 0xf7, 0xf3, 0xfb, 0xeb, 0xcb, 0x8b, 0xb, 0x16, 0x2c, 0x58,
    0xb0, 0x7d, 0xfa, 0xe9, 0xcf, 0x83, 0x1b, 0x36, 0x6c, 0xd8, 0xad, 0x47, 0x8e, 0x1, 0x2
};

const uint8_t code_log[256] = {
    0x0, 0x0, 0x1, 0x19, 0x2, 0x32, 0x1a, 0xc6, 0x3, 0xdf, 0x33, 0xee, 0x1b, 0x68, 0xc7, 0x4b, 0x4,
    0x64, 0xe0, 0xe, 0x34, 0x8d, 0xef, 0x81, 0x1c, 0xc1, 0x69, 0xf8, 0xc8, 0x8, 0x4c, 0x71, 0x5,
    0x8a, 0x65, 0x2f, 0xe1, 0x24, 0xf, 0x21, 0x35, 0x93, 0x8e, 0xda, 0xf0, 0x12, 0x82, 0x45, 0x1d,
    0xb5, 0xc2, 0x7d, 0x6a, 0x27, 0xf9, 0xb9, 0xc9, 0x9a, 0x9, 0x78, 0x4d, 0xe4, 0x72, 0xa6, 0x6,
    0xbf, 0x8b, 0x62, 0x66, 0xdd, 0x30, 0xfd, 0xe2, 0x98, 0x25, 0xb3, 0x10, 0x91, 0x22, 0x88, 0x36,
    0xd0, 0x94, 0xce, 0x8f, 0x96, 0xdb, 0xbd, 0xf1, 0xd2, 0x13, 0x5c, 0x83, 0x38, 0x46, 0x40, 0x1e,
    0x42, 0xb6, 0xa3, 0xc3, 0x48, 0x7e, 0x6e, 0x6b, 0x3a, 0x28, 0x54, 0xfa, 0x85, 0xba, 0x3d, 0xca,
    0x5e, 0x9b, 0x9f, 0xa, 0x15, 0x79, 0x2b, 0x4e, 0xd4, 0xe5, 0xac, 0x73, 0xf3, 0xa7, 0x57, 0x7,
    0x70, 0xc0, 0xf7, 0x8c, 0x80, 0x63, 0xd, 0x67, 0x4a, 0xde, 0xed, 0x31, 0xc5, 0xfe, 0x18, 0xe3,
    0xa5, 0x99, 0x77, 0x26, 0xb8, 0xb4, 0x7c, 0x11, 0x44, 0x92, 0xd9, 0x23, 0x20, 0x89, 0x2e, 0x37,
    0x3f, 0xd1, 0x5b, 0x95, 0xbc, 0xcf, 0xcd, 0x90, 0x87, 0x97, 0xb2, 0xdc, 0xfc, 0xbe, 0x61, 0xf2,
    0x56, 0xd3, 0xab, 0x14, 0x2a, 0x5d, 0x9e, 0x84, 0x3c, 0x39, 0x53, 0x47, 0x6d, 0x41, 0xa2, 0x1f,
    0x2d, 0x43, 0xd8, 0xb7, 0x7b, 0xa4, 0x76, 0xc4, 0x17, 0x49, 0xec, 0x7f, 0xc, 0x6f, 0xf6, 0x6c,
    0xa1, 0x3b, 0x52, 0x29, 0x9d, 0x55, 0xaa, 0xfb, 0x60, 0x86, 0xb1, 0xbb, 0xcc, 0x3e, 0x5a, 0xcb,
    0x59, 0x5f, 0xb0, 0x9c, 0xa9, 0xa0, 0x51, 0xb, 0xf5, 0x16, 0xeb, 0x7a, 0x75, 0x2c, 0xd7, 0x4f,
    0xae, 0xd5, 0xe9, 0xe6, 0xe7, 0xad, 0xe8, 0x74, 0xd6, 0xf4, 0xea, 0xa8, 0x50, 0x58, 0xaf
};

void poly_init(blpoly_t *dev, uint8_t id, uint16_t offset, uint8_t size, uint8_t *memory_ptr)
{
    bl_assert(memory_ptr && dev);

    dev->_id = id;
    dev->_size = size;
    dev->_offset = offset;
    dev->_memory = memory_ptr;
    dev->length = 0;
}

uint8_t *poly_ptr(blpoly_t *dev)
{
    bl_assert(dev);

    return (dev->_memory + dev->_offset);
}

void poly_reset(blpoly_t *dev)
{
    bl_assert(dev->_memory && dev);

    memset(poly_ptr(dev), 0, dev->_size);
}

void poly_set(blpoly_t *dev, uint8_t* src, uint8_t len, uint8_t offset)/* offset=0 */
{
    bl_assert(src && len <= dev->_size - offset);

    memcpy(poly_ptr(dev)+offset, src, len * sizeof(uint8_t));

    dev->length = len + offset;
}

uint8_t *poly_at(blpoly_t *dev, uint8_t i)
{
    uint8_t *pt;

    bl_assert(dev);

    pt = poly_ptr(dev);

    return (pt + i);
}

uint8_t poly_get_size(blpoly_t *dev)
{
    bl_assert(dev);

    return dev->_size;
}

uint8_t poly_get_id(blpoly_t *dev)
{
    bl_assert(dev);

    return dev->_id;
}

void poly_copy(blpoly_t *dev, blpoly_t *src)
{
    bl_assert(dev && src);

    dev->length = ((dev->length) > (src->length) ? (dev->length) : (src->length));
    poly_set(dev, poly_ptr(src), dev->length, 0);
}

uint8_t poly_append(blpoly_t *dev, uint8_t num)
{
    uint8_t *pt;
    bl_assert(dev->length + 1 < dev->_size);

    pt = poly_ptr(dev);
    pt[dev->length++] = num;

    return 1;/* true */
}

/*****************************************************/
uint8_t gf_add(uint8_t x, uint8_t y)
{
    return x + y;
}

uint8_t gf_sub(uint8_t x, uint8_t y)
{
    return x^y;
}

uint8_t gf_mul(uint16_t x, uint16_t y)
{
    if (x == 0 || y == 0) {
        return 0;
    }

    return code_exp[code_log[x] + code_log[y]];
}

uint8_t gf_div(uint8_t x, uint8_t y)
{
    bl_assert(y != 0);

    if (x == 0) {
        return 0;
    }
    return code_exp[(code_log[x] + 255 - code_log[y]) % 255];
}

uint8_t gf_pow(uint8_t x, intmax_t power)
{
    intmax_t i = code_log[x];

    i *= power;
    i %= 255;

    if (i < 0) {
        i = i + 255;
    }

    return code_exp[i];
}

uint8_t gf_inverse(uint8_t x)
{
    return code_exp[255 - code_log[x]]; /* == div(1, x); */
}

/* POLYNOMIALS OPERATIONS */
void poly_scale(blpoly_t *p, blpoly_t *newp, uint16_t x)
{
    uint16_t i;

    newp->length = p->length;
    for (i = 0; i < p->length; i++)
    {
        *poly_at(newp, i) = gf_mul(*poly_at(p, i), x);
    }
}

void poly_add(blpoly_t *p, blpoly_t *q, blpoly_t *newp)
{
    uint8_t i;

    newp->length = ((p->length) > (q->length) ? (p->length) : (q->length));
    memset(poly_ptr(newp), 0, newp->length * sizeof(uint8_t));

    for (i = 0; i < p->length; i++)
    {
        *poly_at(newp, i + newp->length - p->length) = *poly_at(p, i);
    }

    for (i = 0; i < q->length; i++)
    {
        *poly_at(newp, i + newp->length - q->length) ^= *poly_at(q, i);
    }
}

void poly_mul(blpoly_t *p, blpoly_t *q, blpoly_t *newp)
{
    uint8_t i,j;

    newp->length = p->length + q->length - 1;
    memset(poly_ptr(newp), 0, newp->length * sizeof(uint8_t));
    /* Compute the polynomial multiplication (just like the outer product of two vectors,
     * we multiply each coefficients of p with all coefficients of q) */
    for (j = 0; j < q->length; j++) {
        for (i = 0; i < p->length; i++) {
            *poly_at(newp, i+j) ^= gf_mul(*poly_at(p, i), *poly_at(q, j)); /* == r[i + j] = gf_add(r[i+j], gf_mul(p[i], q[j])) */
        }
    }
}

void poly_div(blpoly_t *p, blpoly_t *q, blpoly_t *newp)
{
    uint8_t coef;
    unsigned long sep;
    long i;

    if (poly_ptr(p) != poly_ptr(newp)) {
        memcpy(poly_ptr(newp), poly_ptr(p), p->length*sizeof(uint8_t));
    }

    newp->length = p->length;

    for (i = 0; i < (p->length-(q->length-1)); i++) {
        coef = *poly_at(newp, i);
        if (coef != 0) {
            for (uint8_t j = 1; j < q->length; j++) {
                if (*poly_at(q, j) != 0) {
                    *poly_at(newp, i+j) ^= gf_mul(*poly_at(q, j), coef);
                }
            }
        }
    }

    sep = p->length-(q->length-1);
    memmove(poly_ptr(newp), poly_ptr(newp)+sep, (newp->length-sep) * sizeof(uint8_t));
    newp->length = newp->length-sep;
}

int8_t poly_eval(blpoly_t *p, uint16_t x)
{
    uint8_t y = *poly_at(p, 0);

    for (uint8_t i = 1; i < p->length; i++)
    {
        y = gf_mul(y, x) ^ (*poly_at(p, i));
    }
    return y;
}

/*****************************************************/
void generator_poly(fec_context_t *context)
{
    uint8_t i;
    blpoly_t *gen = context->g_polynoms + ID_GENERATOR;
    blpoly_t *mulp = context->g_polynoms + ID_TPOLY1;
    blpoly_t *temp = context->g_polynoms + ID_TPOLY2;

    *poly_at(gen, 0) = 1;
    gen->length = 1;

    mulp->length = 2;

    for (i = 0; i < FEC_ECC_LENGTH; i++)
    {
        *poly_at(mulp, 0) = 1;
        *poly_at(mulp, 1) = gf_pow(2, i);

        poly_mul(gen, mulp, temp);
        poly_copy(gen, temp);
    }
}

void calc_syndromes(fec_context_t *context, blpoly_t *msg)
{
    uint8_t i;
    blpoly_t *synd = &context->g_polynoms[ID_SYNDROMES];

    synd->length = FEC_ECC_LENGTH + 1;
    *poly_at(synd, 0) = 0;

    for (i = 1; i < FEC_ECC_LENGTH + 1; i++)
    {
        *poly_at(synd, i) = poly_eval(msg, gf_pow(2, i - 1));
    }
}

void find_errata_locator(fec_context_t *context, blpoly_t *epos)
{
    blpoly_t *errata_loc = &context->g_polynoms[ID_ERASURES_LOC];
    blpoly_t *mulp = &context->g_polynoms[ID_TPOLY1];
    blpoly_t *addp = &context->g_polynoms[ID_TPOLY2];
    blpoly_t *apol = &context->g_polynoms[ID_TPOLY3];
    blpoly_t *temp = &context->g_polynoms[ID_TPOLY4];

    errata_loc->length = 1;
    *poly_at(errata_loc, 0) = 1;

    mulp->length = 1;
    addp->length = 2;

    for (uint8_t i = 0; i < epos->length; i++)
    {
        *poly_at(mulp, 0) = 1;
        *poly_at(addp, 0) = gf_pow(2, *poly_at(epos           , i));
        *poly_at(addp, 1) = 0;

        poly_add(mulp, addp, apol);
        poly_mul(errata_loc, apol, temp);

        poly_copy(errata_loc, temp);
    }
}

void find_error_evaluator(fec_context_t *context, blpoly_t *synd, blpoly_t *errata_loc, blpoly_t *dst, uint8_t ecclen)
{
    blpoly_t *mulp = &context->g_polynoms[ID_TPOLY1];
    poly_mul(synd, errata_loc, mulp);

    blpoly_t *divisor = &context->g_polynoms[ID_TPOLY2];
    divisor->length = ecclen + 2;

    poly_reset(divisor);
    *poly_at(divisor, 0) = 1;

    poly_div(mulp, divisor, dst);
}

void correct_errata(fec_context_t *context, blpoly_t *synd, blpoly_t *err_pos, blpoly_t *msg_in)
{
    uint8_t i;
    int8_t s_i;
    int16_t l;
    uint8_t Xi_inv;
    uint8_t err_loc_prime;
    uint8_t y;
    uint8_t j;

    blpoly_t *c_pos     = &context->g_polynoms[ID_COEF_POS];
    blpoly_t *corrected = &context->g_polynoms[ID_MSG_OUT];
    blpoly_t *errata_loc = &context->g_polynoms[ID_ERASURES_LOC];
    blpoly_t *rsynd = &context->g_polynoms[ID_TPOLY3];
    blpoly_t *re_eval = &context->g_polynoms[ID_TPOLY4];
    blpoly_t *e_eval = &context->g_polynoms[ID_ERR_EVAL];
    blpoly_t *X = &context->g_polynoms[ID_TPOLY1]; /* this will store errors positions */
    blpoly_t *E = &context->g_polynoms[ID_MSG_E];
    blpoly_t *err_loc_prime_temp = &context->g_polynoms[ID_TPOLY2];

    c_pos->length = err_pos->length;

    for (i = 0; i < err_pos->length; i++)
        *poly_at(c_pos, i) = msg_in->length - 1 - *poly_at(err_pos, i);

    /* uses t_poly 1, 2, 3, 4 */
    find_errata_locator(context, c_pos);


    /* reversing syndromes */
    rsynd->length = synd->length;

    for (s_i = synd->length-1, j = 0; s_i >= 0; s_i--, j++)
    {
        *poly_at(rsynd, j) = *poly_at(synd, s_i);
    }

    /* getting reversed error evaluator polynomial */

    /* uses T_POLY 1, 2 */
    find_error_evaluator(context, rsynd, errata_loc, re_eval, errata_loc->length-1);

    /* reversing it back */
    e_eval->length = re_eval->length;
    for (s_i = re_eval->length-1, j = 0; s_i >= 0; s_i--, j++)
    {
        *poly_at(e_eval, j) = *poly_at(re_eval, s_i);
    }


    X->length = 0;

    for (i = 0; i < c_pos->length; i++)
    {
        l = 255 - *poly_at(c_pos, i);
        poly_append(X, gf_pow(2, -l));
    }

    /* Magnitude polynomial
        Shit just got real */
    poly_reset(E);
    E->length = msg_in->length;


    for (i = 0; i < X->length; i++) {
        Xi_inv = gf_inverse(*poly_at(X, i));

        err_loc_prime_temp->length = 0;
        for (j = 0; j < X->length; j++) {
            if (j != i) {
                poly_append(err_loc_prime_temp, gf_sub(1, gf_mul(Xi_inv, *poly_at(X, j))));
            }
        }

        err_loc_prime = 1;
        for (j = 0; j < err_loc_prime_temp->length; j++) {
            err_loc_prime = gf_mul(err_loc_prime, *poly_at(err_loc_prime_temp, j));
        }

        y = poly_eval(re_eval, Xi_inv);
        y = gf_mul(gf_pow(*poly_at(X, i), 1), y);

        *poly_at(E, *poly_at(err_pos, i)) = gf_div(y, err_loc_prime);
    }

    poly_add(msg_in, E, corrected);
}

uint8_t find_error_locator(fec_context_t *context, blpoly_t *synd, blpoly_t *erase_loc, unsigned long erase_count)
{
    uint8_t i;
    uint8_t synd_shift = 0;
    uint8_t K = 0;
    uint8_t delta = 0;
    uint8_t index;
    uint8_t j;
    uint32_t shift = 0;
    uint32_t errs;

    blpoly_t *error_loc = &context->g_polynoms[ID_ERRORS_LOC];
    blpoly_t *err_loc   = &context->g_polynoms[ID_TPOLY1];
    blpoly_t *old_loc   = &context->g_polynoms[ID_TPOLY2];
    blpoly_t *temp      = &context->g_polynoms[ID_TPOLY3];
    blpoly_t *temp2     = &context->g_polynoms[ID_TPOLY4];

    if (erase_loc != NULL) {
        poly_copy(err_loc, erase_loc);
        poly_copy(old_loc, erase_loc);
    } else {
        err_loc->length = 1;
        old_loc->length = 1;
        *poly_at(err_loc, 0)  = 1;
        *poly_at(old_loc, 0)  = 1;
    }


    if (synd->length > FEC_ECC_LENGTH) {
        synd_shift = synd->length - FEC_ECC_LENGTH;
    }

    for (i = 0; i < FEC_ECC_LENGTH - erase_count; i++)
    {
        if (erase_loc != NULL) {
            K = erase_count + i + synd_shift;
        } else {
            K = i + synd_shift;
        }

        delta = *poly_at(synd, K);
        for (j = 1; j < err_loc->length; j++) {
            index = err_loc->length - j - 1;
            delta ^= gf_mul(*poly_at(err_loc, index), *poly_at(synd, K-j));
        }

        poly_append(old_loc, 0);

        if (delta != 0) {
            if (old_loc->length > err_loc->length) {
                poly_scale(old_loc, temp, delta);
                poly_scale(err_loc, old_loc, gf_inverse(delta));
                poly_copy(err_loc, temp);
            }
            poly_scale(old_loc, temp, delta);
            poly_add(err_loc, temp, temp2);
            poly_copy(err_loc, temp2);
        }
    }

    while(err_loc->length && *poly_at(err_loc, shift) == 0) shift++;

    errs = err_loc->length - shift - 1;
    if (((errs - erase_count) * 2 + erase_count) > FEC_ECC_LENGTH) {
        return 0;/* false */ /* Error count is greater then we can fix! */
    }

    memcpy(poly_ptr(error_loc), poly_ptr(err_loc) + shift, (err_loc->length - shift) * sizeof(uint8_t));
    error_loc->length = (err_loc->length - shift);
    return 1;/* true */
}

uint8_t find_errors(fec_context_t *context, blpoly_t *error_loc, unsigned long msg_in_size)
{
    uint8_t i;

    blpoly_t *err = &context->g_polynoms[ID_ERRORS];
    uint8_t errs = error_loc->length - 1;

    err->length = 0;

    for (i = 0; i < msg_in_size; i++)
    {
        if (poly_eval(error_loc, gf_pow(2, i)) == 0)
        {
            poly_append(err, msg_in_size - 1 - i);
        }
    }

    /* Sanity check:
        * the number of err/errata positions found
        * should be exactly the same as the length of the errata locator polynomial */
    if (err->length != errs) {
        /* couldn't find error locations */
        return 0;/* false */
    }

    return 1;/* true */
}

void calc_forney_syndromes(fec_context_t *context, blpoly_t *synd, blpoly_t *erasures_pos, unsigned long msg_in_size)
{
    uint8_t i;
    uint8_t x;
    uint8_t j;

    blpoly_t *erase_pos_reversed = &context->g_polynoms[ID_TPOLY1];
    blpoly_t *forney_synd = &context->g_polynoms[ID_FORNEY];

    erase_pos_reversed->length = 0;

    for (i = 0; i < erasures_pos->length; i++)
    {
        poly_append(erase_pos_reversed, msg_in_size - 1 - *poly_at(erasures_pos, i));
    }

    poly_reset(forney_synd);
    poly_set(forney_synd, poly_ptr(synd)+1, synd->length-1, 0);

    for (i = 0; i < erasures_pos->length; i++)
    {
        x = gf_pow(2, *poly_at(erase_pos_reversed, i));
        for (j = 0; j < forney_synd->length - 1; j++)
        {
            *poly_at(forney_synd, j) = gf_mul(*poly_at(forney_synd, j), x) ^ *poly_at(forney_synd, j+1);
        }
    }
}

void reedsolomon_init(void *context)
{
    fec_context_t *p = (fec_context_t *)context;
    uint16_t offset = 0;
    uint8_t i;
    uint8_t enc_len = FEC_MSG_LENGTH + FEC_ECC_LENGTH;
    uint8_t poly_len = FEC_ECC_LENGTH * 2;

    bl_assert(p);

    log_info("reedsolomon_init.\r\n");

    poly_init(&p->g_polynoms[0], ID_MSG_IN, offset, enc_len, p->g_stack_memory);
    offset += enc_len;

    poly_init(&p->g_polynoms[1], ID_MSG_OUT, offset, enc_len, p->g_stack_memory);
    offset += enc_len;

    for (i = ID_GENERATOR; i < ID_MSG_E; i++)
    {
        poly_init(&p->g_polynoms[i], i, offset, poly_len, p->g_stack_memory);
        offset += poly_len;
    }

    poly_init(&p->g_polynoms[5], ID_MSG_E, offset, enc_len, p->g_stack_memory);
    offset += enc_len;

    for (i = ID_TPOLY3; i < ID_ERR_EVAL+2; i++)
    {
        poly_init(&p->g_polynoms[i], i, offset, poly_len, p->g_stack_memory);
        offset += poly_len;
    }
}

void encode_block(fec_context_t *context, void *src, void *dst)
{
    /* Generator cache, it dosn't change for one template parameters */

    uint8_t coef = 0; /* cache */
    uint8_t i;
    uint32_t j;

    uint8_t* src_ptr = (uint8_t*) src;
    uint8_t* dst_ptr = (uint8_t*) dst;

    blpoly_t *msg_in  = &context->g_polynoms[ID_MSG_IN];
    blpoly_t *msg_out = &context->g_polynoms[ID_MSG_OUT];
    blpoly_t *gen     = &context->g_polynoms[ID_GENERATOR];

    bl_assert(FEC_MSG_LENGTH + FEC_ECC_LENGTH < 256);

    poly_reset(msg_in);
    poly_reset(msg_out);

    if (context->g_generator_cached_flag) {
        poly_set(gen, context->g_generator_cache, (FEC_ECC_LENGTH + 1), 0);
    } else {
        generator_poly(context);
        memcpy(context->g_generator_cache, poly_ptr(gen), gen->length);
        context->g_generator_cached_flag = 1;/* true */
    }

    /* Copying input message to internal polynomial */
    poly_set(msg_in, src_ptr, FEC_MSG_LENGTH, 0);
    poly_set(msg_out, src_ptr, FEC_MSG_LENGTH, 0);
    msg_out->length = msg_in->length + FEC_ECC_LENGTH;

    /* Here all the magic happens */

    for (i = 0; i < FEC_MSG_LENGTH; i++) {
        coef = *poly_at(msg_out, i);
        if (coef != 0) {
            for (j = 1; j < gen->length; j++) {
                *poly_at(msg_out, i+j) ^= gf_mul(*poly_at(gen, j), coef);
            }
        }
    }

    /* Copying ECC to the output buffer */
    memcpy(dst_ptr, poly_ptr(msg_out)+FEC_MSG_LENGTH, FEC_ECC_LENGTH * sizeof(uint8_t));

}

void reedsolomon_encode(void *context, void* src, void* dst)
{
    fec_context_t *p = (fec_context_t *)context;
    uint8_t* dst_ptr = (uint8_t*) dst;

    /* Copying message to the output buffer */
    memcpy(dst_ptr, src, FEC_MSG_LENGTH * sizeof(uint8_t));

    /* Calling EncodeBlock to write ecc to out[ut buffer */
    encode_block(p, src, dst_ptr+FEC_MSG_LENGTH);
}

char decode_block(fec_context_t *context, void* src, const void* ecc, void* dst, uint8_t* erase_pos, unsigned long erase_count)
{
    uint8_t i, j;
    int8_t s_i;
    bl_assert(FEC_MSG_LENGTH + FEC_ECC_LENGTH < 256);

    uint8_t *src_ptr = (uint8_t*) src;
    uint8_t *ecc_ptr = (uint8_t*) ecc;
    uint8_t *dst_ptr = (uint8_t*) dst;

    uint8_t src_len = FEC_MSG_LENGTH + FEC_ECC_LENGTH;
    uint8_t dst_len = FEC_MSG_LENGTH;

    uint8_t ok;

    blpoly_t *msg_in  = &context->g_polynoms[ID_MSG_IN];
    blpoly_t *msg_out = &context->g_polynoms[ID_MSG_OUT];
    blpoly_t *epos    = &context->g_polynoms[ID_ERASURES];
    blpoly_t *synd   = &context->g_polynoms[ID_SYNDROMES];
    blpoly_t *eloc   = &context->g_polynoms[ID_ERRORS_LOC];
    blpoly_t *reloc  = &context->g_polynoms[ID_TPOLY1];
    blpoly_t *err    = &context->g_polynoms[ID_ERRORS];
    blpoly_t *forney = &context->g_polynoms[ID_FORNEY];

    uint8_t has_errors;

    /* Copying message to polynomials memory */
    poly_set(msg_in, src_ptr, FEC_MSG_LENGTH, 0);
    poly_set(msg_in, ecc_ptr, FEC_ECC_LENGTH, FEC_MSG_LENGTH);
    poly_copy(msg_out, msg_in);

    /* Copying known errors to polynomial */
    if (erase_pos == NULL) {
        epos->length = 0;
    } else {
        poly_set(epos, erase_pos, (uint8_t)erase_count, 0);
        for (i = 0; i < epos->length; i++){
            *poly_at(msg_in, *poly_at(epos, i)) = 0;
        }
    }

    /* Too many errors */
    if (epos->length > FEC_ECC_LENGTH) return 1;


    /* Calculating syndrome */
    calc_syndromes(context, msg_in);

    /* Checking for errors */
    has_errors = 0;/* false */
    for (i = 0; i < synd->length; i++) {
        if (*poly_at(synd, i) != 0) {
            has_errors = 1;/* true */
            break;
        }
    }

    /* Going to exit if no errors */
    if (!has_errors) {
        goto return_corrected_msg;
    }

    calc_forney_syndromes(context, synd, epos, src_len);
    find_error_locator(context, forney, NULL, epos->length);

    /*
        Reversing syndrome
        TODO optimize through special Poly flag
    */
    reloc->length = eloc->length;

    for (s_i = eloc->length-1, j = 0; s_i >= 0; s_i--, j++) {
        *poly_at(reloc, j) = *poly_at(eloc, s_i);
    }

    /* Fing errors */
    ok = find_errors(context, reloc, src_len);
    if (!ok) {
        return 1;
    }

    /* Error happened while finding errors (so helpfull :D) */
    if (err->length == 0) {
        return 1;
    }

    /* Adding found errors with known */
    for (uint8_t i = 0; i < err->length; i++) {
        poly_append(epos, *poly_at(err, i));
    }

    /* Correcting errors */
    correct_errata(context, synd, epos, msg_in);

return_corrected_msg:
    /* Wrighting corrected message to output buffer */
    msg_out->length = dst_len;
    memcpy(dst_ptr, poly_ptr(msg_out), msg_out->length * sizeof(uint8_t));
    return 0;
}

/*
    old:
        reedsolomon_decode(void *context, void* src, void* dst, uint8_t* erase_pos, uint32_t erase_count)
        return decode_block(p, src, ecc_ptr, dst, erase_pos, erase_count);
*/
char reedsolomon_decode(void *context, void* src, void* dst)
{
    fec_context_t *p = (fec_context_t *)context;
    uint8_t *src_ptr = (uint8_t*) src;
    uint8_t *ecc_ptr = src_ptr + FEC_MSG_LENGTH;

    return decode_block(p, src, ecc_ptr, dst, 0, 0);
}

/* which compiles with no warnings, and produces no code. */
#define BUILD_BUG_ON(condition) ((void)sizeof(char [1 - 2 * !!(condition)]))
int reedsolomon_getmemsize(void)
{
    /*
        which compiles with no warnings, and produces no code.
        err ? too waste mem ? pleas set fec_t.dummy size to (sizeof(fec_context_t)/sizeof(int) + 1)!
    */
    BUILD_BUG_ON((sizeof(fec_t) - sizeof(fec_context_t) > 512) ||
                (sizeof(fec_t) - sizeof(fec_context_t) < 0));

    log_info("sizeof(fec_t) = %d   sizeof(fec_context_t) = %d\r\n", sizeof(fec_t), sizeof(fec_context_t));
    return (int)sizeof(fec_context_t);
}

#ifdef __cplusplus
}
#endif






