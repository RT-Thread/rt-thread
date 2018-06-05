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
 * @file     ck_rsa.c
 * @brief    CSI Source File for RSA Driver
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "drv_rsa.h"
#include "ck_rsa.h"

#define ERR_RSA(errno) (CSI_DRV_ERRNO_RSA_BASE | errno)
#define RSA_NULL_PARAM_CHK(para)                         \
        do {                                        \
            if (para == NULL) {                     \
                return ERR_RSA(EDRV_PARAMETER);   \
            }                                       \
        } while (0)


typedef struct {
    uint32_t base;
    uint32_t irq;
    rsa_event_cb_t cb;
    rsa_data_bits_e data_bit;
    rsa_endian_mode_e endian;
    rsa_padding_t padding;
    rsa_status_t status;
} ck_rsa_priv_t;

static ck_rsa_priv_t rsa_handle[CONFIG_RSA_NUM];

extern uint8_t modulus[];
static ck_rsa_reg_t *rsa_reg = NULL;
static uint32_t g_acc[RSA_KEY_WORD];
/* Driver Capabilities */
static const rsa_capabilities_t driver_capabilities = {
    .bits_192 = 1, /* 192bits modular mode */
    .bits_256 = 1, /* 256bits modular mode */
    .bits_512 = 1, /* 512bits modular mode */
    .bits_1024 = 1, /* 1024bits modular mode */
    .bits_2048 = 1  /* 2048bits modular mode */
};

//
// Functions
//

static uint32_t sw_exptmod_2_2m(const uint32_t *modulus, uint32_t words, uint32_t *tmp_c);
static uint32_t get_valid_bits(const uint32_t *addr, uint32_t wordsize);

static uint32_t g_acc[RSA_KEY_WORD];

static inline void rsa_clear_int(void)
{
    rsa_reg->rsa_isr = 0xffff;
    rsa_reg->rsa_imr = 0x0000;
}

static inline void rsa_setm_width(uint32_t width)
{
    rsa_reg->rsa_mwid = width;
}

static inline void rsa_setd_width(uint32_t width)
{
    rsa_reg->rsa_ckid = width;
}

static inline void rsa_setb_width(uint32_t width)
{
    rsa_reg->rsa_bwid = width;
}

static inline void rsa_cal_q(void)
{
    rsa_reg->rsa_ctrl = RAS_CALCULATE_Q;
}

static inline void rsa_opr_start(void)
{
    rsa_reg->rsa_ctrl = RSA_ENABLE_MODULE;
}

static inline void rsa_opr_reset(void)
{
    rsa_reg->rsa_ctrl = RSA_ENDIAN_MODE;
    rsa_reg->rsa_rst |= RSA_RESET;

    while (rsa_reg->rsa_rst);
}

static inline uint32_t rsa_loop_cnt(void)
{
    return rsa_reg->rsa_lp_cnt;
}

static inline uint32_t rsa_cal_q_done(void)
{
    return (rsa_reg->rsa_isr >> RSA_CAL_Q_DONE_OFFSET) & 0x1;
}

static inline uint32_t rsa_opr_done(void)
{
    return (rsa_reg->rsa_isr) & 0x1;
}

static inline uint32_t rsa_raise_exception(void)
{
    return (rsa_reg->rsa_isr) & 0x1E;
}

static inline uint32_t rsa_loadm(uint32_t *data, uint32_t length)
{
    uint32_t i;
    uint32_t baseaddr = (uint32_t)&rsa_reg->rsa_rfm;

    for (i = 0; i < length; i++) {
        *(volatile uint32_t *)baseaddr = data[i];
        baseaddr = baseaddr + 4;
    }

    return 0;
}

static void rsa_loadd(uint32_t *data, uint32_t length)
{
    uint32_t i;
    uint32_t baseaddr = (uint32_t)&rsa_reg->rsa_rfd;

    for (i = 0;  i < length; i++) {
        *(volatile uint32_t *)baseaddr = data[i];
        baseaddr = baseaddr + 4;
    }
}

static void rsa_loadc(uint32_t *data, uint32_t length)
{
    uint32_t i;
    uint32_t baseaddr = (uint32_t)&rsa_reg->rsa_rfc;

    for (i = 1; i < length + 1; i++) {
        *(volatile uint32_t *)baseaddr = data[i - 1];
        baseaddr = baseaddr + 4;
    }
}

static void rsa_loadb(uint32_t *data, uint32_t length)
{
    uint32_t i;
    uint32_t baseaddr = (uint32_t)&rsa_reg->rsa_rfb;

    for (i = 0; i < length; i++) {
        *(volatile uint32_t *)baseaddr = data[i];
        baseaddr = baseaddr + 4;
    }
}

static void rsa_read_r(uint32_t data[], uint32_t length)
{
    uint32_t i;
    uint32_t baseaddr = (uint32_t)&rsa_reg->rsa_rfr;

    for (i = 0; i < length; i++) {
        data[i] = *(uint32_t *)baseaddr;
        baseaddr = baseaddr + 4;
    }
}

static uint32_t rsa_exptmod_1024(const uint32_t *modulus, const uint32_t *exponent,
                                 const uint32_t *base, uint32_t *out)
{
#ifndef RSA_USING_MALLOC
#ifndef RSA_USING_ID2KEY
    uint32_t tmp_c[RSA_KEY_WORD];
#endif
    uint32_t ret = 0;

    if ((NULL == exponent) || (NULL == base) || (NULL == out)) {
        return 1;
    }

#ifndef RSA_USING_ID2KEY
    ret = sw_exptmod_2_2m(modulus, RSA_KEY_WORD, tmp_c);

    if (ret != 0) {
        return ret;
    }

#endif

    /* reset for safe */
    rsa_opr_reset();
    /* clear and disable int */
    rsa_clear_int();
    /* set m */
    rsa_setm_width(RSA_KEY_WORD >> 1);
    rsa_loadm((uint32_t *)modulus, RSA_KEY_WORD);
    /* set d */
    rsa_setd_width(get_valid_bits(exponent, RSA_KEY_WORD) - 1);
    rsa_loadd((uint32_t *)exponent, RSA_KEY_WORD);
    /* set b */
    rsa_setb_width(RSA_KEY_WORD >> 1);
    rsa_loadb((uint32_t *)base, RSA_KEY_WORD);
    /* set c */
#ifndef RSA_USING_ID2KEY
    rsa_loadc(tmp_c, RSA_KEY_WORD);
#else
    rsa_loadc(g_acc, RSA_KEY_WORD);
#endif

    rsa_cal_q();

    while (!rsa_cal_q_done() && (!rsa_raise_exception()));

    if (!rsa_raise_exception()) {
        rsa_opr_start();

        while ((!rsa_opr_done()) && (rsa_loop_cnt() < MAX_RSA_LP_CNT) && (!rsa_raise_exception()));

        if ((rsa_loop_cnt() >= MAX_RSA_LP_CNT)
            || rsa_raise_exception()) {
            ret = 1;
        } else {
            rsa_read_r(out, RSA_KEY_WORD);
        }
    } else {
        ret = 1;
    }

    rsa_opr_reset();

    return ret;
#else
    uint32_t ret;
    uint32_t *tmp_c = (uint32_t *)tee_malloc(RSA_KEY_BYTE);

    if (tmp_c == NULL) {
        return -1;
    }

    if ((NULL == modulus) || (NULL == exponent) || (NULL == base) || (NULL == out)) {
        return -1;
    }

#if 0
    ret = sw_exptmod_2_2m(modulus, RSA_KEY_WORD, tmp_c);

    if (ret != 0) {
        tee_free(tmp_c);
        return ret;
    }

#else
    memcpy(tmp_c, g_acc, RSA_KEY_BYTE);
#endif
    /* reset for safe */
    rsa_opr_reset();
    /* clear and disable int */
    rsa_clear_int();
    /* set m */
    rsa_setm_width(RSA_KEY_WORD >> 1);
    rsa_loadm((uint32_t *)modulus, RSA_KEY_WORD);
    /* set d */
    rsa_setd_width(get_valid_bits(exponent, RSA_KEY_WORD) - 1);
    rsa_loadd((uint32_t *)exponent, RSA_KEY_WORD);
    /* set b */
    rsa_setb_width(RSA_KEY_WORD >> 1);
    rsa_loadb((uint32_t *)base, RSA_KEY_WORD);
    /* set c */
    rsa_loadc(tmp_c, RSA_KEY_WORD);

    rsa_cal_q();

    while (!rsa_cal_q_done() && (!rsa_raise_exception()));

    if (!rsa_raise_exception()) {
        rsa_opr_start();

        while ((!rsa_opr_done()) && (rsa_loop_cnt() < MAX_RSA_LP_CNT) && (!rsa_raise_exception()));

        if ((rsa_loop_cnt() >= MAX_RSA_LP_CNT)
            || rsa_raise_exception()) {
            ret = 1;
        } else {
            rsa_read_r(out, RSA_KEY_WORD);
        }
    } else {
        ret = 1;
    }

    rsa_opr_reset();
    tee_free(tmp_c);

    return ret;
#endif
}

static uint32_t get_valid_bits(const uint32_t *addr, uint32_t wordsize)
{
    uint32_t i = 0;
    uint32_t j = 0;

    for (i = wordsize; i > 0; i--) {
        if (addr[i - 1]) {
            break;
        }
    }

    for (j = RSA_KEY_WORD; j > 0; j--) {
        if (addr[i - 1] & (0x1 << (j - 1))) {
            break;
        }
    }

    return ((i - 1) << 5) + j;
}

static uint32_t get_first_nonzero_words(uint32_t *a, uint32_t max_words)
{
    uint32_t i = 0;

    for (i = max_words; i > 0; i--) {
        if (a[i - 1]) {
            return i;
        }
    }

    return 0;
}

static uint32_t word_array_left_shift(uint32_t *a, uint32_t words,
                                      uint32_t shift_bits, uint32_t *r)
{
    uint32_t i = 0;
    uint32_t w = shift_bits >> 5;
    uint32_t b = shift_bits - (w << 5);

    for (i = 0; i < w; i++) {
        r[i] = 0;
    }

    uint32_t tmp = 0;

    for (i = 0; i < words; i++) {
        r[w + i] = (tmp | ((a[i] << b) & (~((0x1 << b) - 1))));
        tmp = ((a[i] >> (RSA_KEY_WORD - b)) & ((0x1 << b) - 1));
    }

    r[w + i] = tmp;

    return 0;
}

/* r = a - b */
static uint32_t _word_array_sub(uint32_t *a, uint32_t a_words,
                                uint32_t *b, uint32_t b_words,
                                uint32_t *r)
{
    uint32_t i;
    uint64_t tmp = 0;
    uint32_t borrow = 0;

    for (i = 0; i < b_words; i++) {
        tmp = UINT32_TO_UINT64(a[i]) - UINT32_TO_UINT64(b[i]) - UINT32_TO_UINT64(borrow);
        r[i] = UINT64L_TO_UINT32(tmp);
        borrow = ((UINT64H_TO_UINT32(tmp) == 0) ? (0) : (0xffffffff - UINT64H_TO_UINT32(tmp) + 1));
    }

    for (i = b_words; i < a_words; i++) {
        tmp = UINT32_TO_UINT64(a[i]) - UINT32_TO_UINT64(borrow);
        r[i] = UINT64L_TO_UINT32(tmp);
        borrow = ((UINT64H_TO_UINT32(tmp) == 0) ? (0) : (0xffffffff - UINT64H_TO_UINT32(tmp) + 1));
    }

    if (borrow) {
        return -1;
    }

    return 0;
}

static uint32_t word_array_mod(uint32_t *a, uint32_t a_words,
                               uint32_t *b, uint32_t b_words,
                               uint32_t *r)
{
#ifndef RSA_USING_MALLOC
    uint32_t ret;
    bignum_t tmpa;
    bignum_t tmpb;

    memset(&tmpa, 0, sizeof(tmpa));
    memset(&tmpb, 0, sizeof(tmpa));

    uint32_t b_valid_bits = get_valid_bits(b, b_words);

    memcpy(tmpa.pdata, a, (a_words << 2));

    do {
        uint32_t tmpa_words = get_first_nonzero_words(tmpa.pdata, a_words);
        uint32_t tmpa_valid_bits = get_valid_bits(tmpa.pdata, tmpa_words);

        if (tmpa_valid_bits > b_valid_bits + 1) {
            memset(tmpb.pdata, 0, (a_words << 2));
            word_array_left_shift(b, b_words, tmpa_valid_bits - b_valid_bits - 1,
                                  tmpb.pdata);
            uint32_t tmpb_words = get_first_nonzero_words(tmpb.pdata, a_words);
            ret = _word_array_sub(tmpa.pdata, tmpa_words, tmpb.pdata, tmpb_words, tmpa.pdata);
        } else if (tmpa_words == b_words) {
            memcpy(r, tmpa.pdata, (tmpa_words << 2));
            ret = _word_array_sub(r, tmpa_words, b, b_words, tmpa.pdata);
        } else {
            ret = _word_array_sub(tmpa.pdata, tmpa_words, b, b_words, tmpa.pdata);
        }
    } while (ret == 0);

    return 0;

#else
    uint32_t ret;
    bignum_t *tmpa = tee_malloc(sizeof(bignum_t));
    bignum_t *tmpb = tee_malloc(sizeof(bignum_t));

    if ((tmpa == NULL) || (tmpb == NULL)) {
        return -1;
    }

    uint32_t b_valid_bits = get_valid_bits(b, b_words);

    memcpy(tmpa->pdata, a, (a_words << 2));

    do {
        uint32_t tmpa_words = get_first_nonzero_words(tmpa->pdata, a_words);
        uint32_t tmpa_valid_bits = get_valid_bits(tmpa->pdata, tmpa_words);

        if (tmpa_valid_bits > b_valid_bits + 1) {
            memset(tmpb->pdata, 0, (a_words << 2));
            word_array_left_shift(b, b_words, tmpa_valid_bits - b_valid_bits - 1,
                                  tmpb->pdata);
            uint32_t tmpb_words = get_first_nonzero_words(tmpb->pdata, a_words);
            ret = _word_array_sub(tmpa->pdata, tmpa_words, tmpb->pdata, tmpb_words, tmpa->pdata);
        } else if (tmpa_words == b_words) {
            memcpy(r, tmpa->pdata, (tmpa_words << 2));
            ret = _word_array_sub(r, tmpa_words, b, b_words, tmpa->pdata);
        } else {
            ret = _word_array_sub(tmpa->pdata, tmpa_words, b, b_words, tmpa->pdata);
        }
    } while (ret == 0);

    tee_free(tmpa);
    tee_free(tmpb);
    return 0;

#endif
}

static uint32_t sw_exptmod_2_2m(const uint32_t *modulus, uint32_t words, uint32_t *tmp_c)
{
#ifndef RSA_USING_MALLOC
    bignum_t tmp;

    memset(&tmp, 0, sizeof(bignum_t));

    uint32_t m_valid_bits = (words << 5);

    uint32_t data1 = 0x1;
    word_array_left_shift(&data1, 1, (m_valid_bits << 1), tmp.pdata);
    tmp.words = get_first_nonzero_words(tmp.pdata, words * 2 + 1);

    uint32_t ret = word_array_mod(tmp.pdata, tmp.words,
                         (uint32_t *)modulus, words, tmp_c);

    if (ret != 0) {
        return ret;
    }

    return 0;
#else

    bignum_t *tmp = tee_malloc(sizeof(bignum_t));

    if (tmp == NULL) {
        return -1;
    }

    uint32_t m_valid_bits = (words << 5);

    uint32_t data1 = 0x1;
    word_array_left_shift(&data1, 1, (m_valid_bits << 1), tmp->pdata);
    tmp->words = get_first_nonzero_words(tmp->pdata, words * 2 + 1);

    uint32_t ret = word_array_mod(tmp->pdata, tmp->words,
                         (uint32_t *)modulus, words, tmp_c);

    if (ret != 0) {
        tee_free(tmp);
        return ret;
    }

    tee_free(tmp);
    return 0;
#endif
}

static void convert_byte_array(uint8_t *in, uint8_t *out, uint32_t len)
{
    uint32_t idx, round = len >> 1;

    for (idx = 0; idx < round; idx++) {
        uint8_t tmp = *(in + idx);
        *(out + idx) = *(in + len - 1 - idx);
        *(out + len - 1 - idx) = tmp;
    }

    if (len & 0x1) {
        *(out + round) = *(in + round);
    }
}

static void convert_buf_to_bndata(const uint8_t *src, uint32_t src_bytes,
                                  uint32_t *dst, uint32_t dst_words)
{
    memset(dst, 0, dst_words << 2);
    convert_byte_array((uint8_t *)src, (uint8_t *)dst, src_bytes);
}

static void convert_bndata_to_buf(const uint32_t *src, uint32_t src_words,
                                  uint8_t *dst, uint32_t dst_bytes)
{
    memset(dst, 0, dst_bytes);
    convert_byte_array((uint8_t *)src, (uint8_t *)dst, dst_bytes);
}

static const uint8_t der_sha1_t[] = {
    0x30, 0x21,
    0x30, 0x09,
    0x06, 0x05, 0x2b, 0x0e, 0x03, 0x02, 0x1a,
    0x05, 0x00,
    0x04, 0x14
};

static const uint8_t der_md5_t[] = {
    0x30, 0x20, /* type Sequence, length 0x20 (32) */
    0x30, 0x0c, /* type Sequence, length 0x09 */
    0x06, 0x08, /* type OID, length 0x05 */
    0x2a, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x02, 0x05, /* id-md5 */
    0x05, 0x00, /* NULL */
    0x04, 0x10  /* Octet string, length 0x10 (16), followed by md5 hash */
};

static uint32_t RSA_padding_add_PKCS1_sha1_emsa_1024(const uint8_t *dgst,
        uint8_t *out,
        uint32_t *outlen,
        uint32_t type)

{
    uint8_t *der;
    uint32_t der_len;
    uint32_t hashlen;

    if (type == MD5_PADDING) {
        der     = (uint8_t *)der_md5_t;
        der_len = sizeof(der_md5_t);
        hashlen = MD5_HASH_SZ;
    } else if (type == SHA1_PADDING) {
        der     = (uint8_t *)der_sha1_t;
        der_len = sizeof(der_sha1_t);
        hashlen = SHA1_HASH_SZ;
    } else {
        der     = (uint8_t *)der_md5_t;
        der_len = sizeof(der_md5_t);
        hashlen = MD5_HASH_SZ;
    }

    uint32_t modulus_len = 1024 >> 3;

    if (*outlen < modulus_len) {
        *outlen = modulus_len;
        return -1;
    }


    uint8_t *p = (uint8_t *)out;

    *(p++) = 0x00;
    *(p++) = 0x01;

    /* pad out with 0xff data */
    uint32_t pslen = modulus_len - 3 - der_len - hashlen;

    uint32_t i;
    for (i = 0; i < pslen; i++) {
        p[i] = 0xff; /* PS */
    }

    p += pslen;
    *(p++) = 0x0;

    for (i = 0; i < der_len; i++) {
        p[i] = der[i];
    }

    p += der_len;

    for (i = 0; i < hashlen; i++) {
        p[i] = dgst[i];
    }

    *outlen = modulus_len;
    return 0;
}

static uint32_t RSA_padding_check_PKCS1_type_emsa(const uint8_t *dgst,
        const uint8_t *in,
        const uint32_t inlen,
        uint8_t *is_valid,
        uint32_t type)
{
    uint8_t *der;
    uint32_t der_len;
    uint32_t hashlen;

    if (type == MD5_PADDING) {
        der     = (uint8_t *)der_md5_t;
        der_len = sizeof(der_md5_t);
        hashlen = MD5_HASH_SZ;
    } else if (type == SHA1_PADDING) {
        der     = (uint8_t *)der_sha1_t;
        der_len = sizeof(der_sha1_t);
        hashlen = SHA1_HASH_SZ;
    } else {
        der     = (uint8_t *)der_md5_t;
        der_len = sizeof(der_md5_t);
        hashlen = MD5_HASH_SZ;
    }

    uint32_t modulus_len = RSA_KEY_LEN >> 3;

    if (inlen != modulus_len) {
        return -1;
    }

    *is_valid = 0;

    uint32_t pslen = modulus_len - 3 - der_len - hashlen;
    const uint8_t *p = in;
    p++;

    uint32_t ret;
    if (*(p) != 0x01) {
        ret = -1;
        goto _verify_fail;
    }

    p++;

    /* scan PS */
    uint32_t i;
    for (i = 0; i < pslen; i++) {
        if (*(p + i) != 0xff) {
            ret = -1;
            goto _verify_fail;
        }
    }

    p += pslen;

    if ((*p) != 0x00) {
        ret = -1;
        goto _verify_fail;
    }

    p++;

    /* scan t */
    for (i = 0; i < der_len; i++) {
        if (*(p + i) != der[i]) {
            ret = -1;
            goto _verify_fail;
        }
    }

    p += der_len;

    for (i = 0; i < hashlen; i++) {
        if (*(p + i) != dgst[i]) {
            ret = -1;
            goto _verify_fail;
        }
    }

    *is_valid = 1;
    ret = 0;

_verify_fail:

    return ret;
}

static uint32_t RSA_ES_padding_add_PKCS1_emsa_1024(const uint8_t *dgst,
        uint32_t dgstlen,
        uint8_t *out,
        uint32_t *outlen,
        uint32_t padding)

{
    uint32_t modulus_len = RSA_KEY_LEN >> 3;

    if (*outlen < modulus_len) {
        *outlen = modulus_len;
        return 1;
    }

    uint8_t *p = (uint8_t *)out;

    *(p++) = 0x00;
    *(p++) = 0x02;

    /* pad out with 0xff data */
    uint32_t pslen = modulus_len - 3 - dgstlen;

    uint32_t i;
    for (i = 0; i < pslen; i++) {
        p[i] = 0xff; /* PS */
    }

    p += pslen;
    *(p++) = 0x0;

    for (i = 0; i < dgstlen; i++) {
        p[i] = dgst[i];
    }

    *outlen = modulus_len;

    return 0;
}

static uint32_t RSA_ES_padding_check_PKCS1_type_emsa(uint8_t *out, uint32_t *out_size,
        uint8_t *src, uint32_t src_size, uint32_t padding)
{

    uint32_t modulus_len = RSA_KEY_LEN >> 3;

    if (src_size < modulus_len) {
        return 1;
    }

    uint8_t *p = (uint8_t *)src;
    uint8_t *p_src = p;
    *(p++) = 0x00;

    if (padding == PKCS1_PADDING) {
        if (*(p++) != 0x02) {
            return 1;
        }
    } else {
        if (*(p++) != 0x01) {
            return 1;
        }
    }

    uint32_t pslen = src_size - 2;

    while (pslen--) {
        if (*(p++) == 0x0) {
            break;
        }
    }

    if (padding == PKCS1_PADDING) {
        *out_size = pslen;
    } else {
        *out_size = modulus_len;
    }

    uint32_t i;
    for (i = 0; i < *out_size; i++) {

        if (padding == PKCS1_PADDING) {
            out[i] = p[i];
        } else {
            out[i] = p_src[i];
        }
    }

    return 0;
}

int rsa_encrypt(uint8_t *n, uint8_t *e,
                uint8_t *src, uint32_t src_size,
                uint8_t *out, uint32_t *out_size,
                uint32_t padding)
{
    uint32_t ret;
    uint32_t tmp_n[RSA_KEY_WORD];
    uint32_t tmp_e[RSA_KEY_WORD];
    uint32_t tmp_src_padded[RSA_KEY_WORD];
    uint32_t tmp_out[RSA_KEY_WORD];

    uint32_t keywords = RSA_KEY_WORD;
    uint32_t keybytes = RSA_KEY_BYTE;

    convert_buf_to_bndata(n, keybytes, tmp_n, keywords);
    convert_buf_to_bndata(e, keybytes, tmp_e, keywords);

    uint32_t tmp_src_padded_len = keybytes;

    if (padding == PKCS1_PADDING) {
        ret = RSA_ES_padding_add_PKCS1_emsa_1024((const uint8_t *)src, src_size,
                (uint8_t *)tmp_src_padded,
                &tmp_src_padded_len, padding);

        if (ret != 0) {
            return ret;
        }

        convert_byte_array((uint8_t *)tmp_src_padded, (uint8_t *)tmp_src_padded, tmp_src_padded_len);
    } else {
        convert_byte_array((uint8_t *)src, (uint8_t *)tmp_src_padded, tmp_src_padded_len);
    }

    ret = rsa_exptmod_1024(tmp_n, tmp_e, tmp_src_padded, tmp_out);

    if (ret != 0) {
        return ret;
    }

    convert_bndata_to_buf(tmp_out, keywords, out, keybytes);
    *out_size = keybytes;

    return ret;
}

int rsa_decrypt(uint8_t *n, uint8_t *d,
                uint8_t *src, uint32_t src_size,
                uint8_t *out, uint32_t *out_size,
                uint32_t padding)
{
    uint32_t ret;
    uint32_t tmp_n[RSA_KEY_WORD];
    uint32_t tmp_d[RSA_KEY_WORD];
    uint32_t tmp_dst_padded[RSA_KEY_WORD];
    uint32_t tmp_sig[RSA_KEY_WORD];

    uint32_t keywords = RSA_KEY_WORD;
    uint32_t keybytes = RSA_KEY_BYTE;

    convert_buf_to_bndata(n, keybytes, tmp_n, keywords);
    convert_buf_to_bndata(d, keybytes, tmp_d, keywords);
    convert_buf_to_bndata(src, src_size, tmp_sig, keywords);

    ret = rsa_exptmod_1024(tmp_n, tmp_d, tmp_sig, tmp_dst_padded);
    \

    if (ret != 0) {
        return ret;
    }

    convert_byte_array((uint8_t *)tmp_dst_padded,
                       (uint8_t *)tmp_dst_padded, keybytes);

    ret = RSA_ES_padding_check_PKCS1_type_emsa(out, out_size,
            (uint8_t *)tmp_dst_padded,
            keybytes, padding);

    return ret;
}

int rsa_sign(uint8_t *n, uint8_t *d,
             uint8_t *src, uint32_t src_size,
             uint8_t *signature, uint32_t *sig_size, uint32_t type)
{
    uint32_t ret;
    uint32_t tmp_n[RSA_KEY_WORD];
    uint32_t tmp_d[RSA_KEY_WORD];
    uint32_t tmp_src_padded[RSA_KEY_WORD];
    uint32_t tmp_sig[RSA_KEY_WORD];

    uint32_t keywords = RSA_KEY_WORD;
    uint32_t keybytes = RSA_KEY_BYTE;

    convert_buf_to_bndata(n, keybytes, tmp_n, keywords);
    convert_buf_to_bndata(d, keybytes, tmp_d, keywords);

    uint32_t tmp_src_padded_len = keybytes;
    ret = RSA_padding_add_PKCS1_sha1_emsa_1024((const uint8_t *)src,
            (uint8_t *)tmp_src_padded,
            &tmp_src_padded_len, type);

    if (ret != 0) {
        return ret;
    }

    convert_byte_array((uint8_t *)tmp_src_padded, (uint8_t *)tmp_src_padded, keybytes);

    ret = rsa_exptmod_1024(tmp_n, tmp_d, tmp_src_padded, tmp_sig);

    if (ret != 0) {
        return ret;
    }

    convert_bndata_to_buf(tmp_sig, keywords, signature, keybytes);
    *sig_size = RSA_KEY_BYTE;

    return 0;
}

int rsa_verify(uint8_t *n, uint8_t *e,
               uint8_t *src, uint32_t src_size,
               uint8_t *signature, uint32_t sig_size,
               uint8_t *result, uint32_t type)
{
    uint32_t ret;
    uint32_t tmp_n[RSA_KEY_WORD];
    uint32_t tmp_e[RSA_KEY_WORD];
    uint32_t tmp_dst_padded[RSA_KEY_WORD];
    uint32_t tmp_sig[RSA_KEY_WORD];

    *result = 0;

    uint32_t keywords = RSA_KEY_WORD;
    uint32_t keybytes = RSA_KEY_BYTE;

    convert_buf_to_bndata(n, keybytes, tmp_n, keywords);
    convert_buf_to_bndata(e, keybytes, tmp_e, keywords);
    convert_buf_to_bndata(signature, sig_size, tmp_sig, keywords);

    ret = rsa_exptmod_1024(tmp_n, tmp_e, tmp_sig, tmp_dst_padded);

    if (ret != 0) {
        return ret;
    }

    convert_byte_array((uint8_t *)tmp_dst_padded,
                       (uint8_t *)tmp_dst_padded, keybytes);
    ret = RSA_padding_check_PKCS1_type_emsa(src,
                                            (const uint8_t *)tmp_dst_padded,
                                            keybytes,
                                            result,
                                            type);

    return ret;
}

int rsa_sw_exptmod_2_2m(uint8_t *modulus)
{
    uint32_t tmp_n[RSA_KEY_WORD];

    uint32_t keywords = RSA_KEY_WORD;
    uint32_t keybytes = RSA_KEY_BYTE;

    convert_buf_to_bndata(modulus, keybytes, tmp_n, keywords);

    sw_exptmod_2_2m(tmp_n, RSA_KEY_WORD, g_acc);

    return 0;
}

int32_t __attribute__((weak)) target_get_rsa_count(void)
{
    return 0;
}

int32_t __attribute__((weak)) target_get_rsa(int32_t idx, uint32_t *base, uint32_t *irq)
{
    return NULL;
}

/**
  \brief       get rsa handle count.
  \return      rsa handle count
*/
int32_t csi_rsa_get_instance_count(void)
{
    return target_get_rsa_count();
}

/**
  \brief       Initialize RSA Interface. 1. Initializes the resources needed for the RSA interface 2.registers event callback function
  \param[in]   idx  must not exceed return value of csi_rsa_get_instance_count()
  \param[in]   cb_event  Pointer to \ref rsa_event_cb_t
  \return      pointer to rsa handle
*/
rsa_handle_t csi_rsa_initialize(int32_t idx, rsa_event_cb_t cb_event)
{
    if (idx < 0 || idx >= CONFIG_RSA_NUM) {
        return NULL;
    }

    /* obtain the rsa information */
    uint32_t base = 0u;
    uint32_t irq;
    int32_t real_idx = target_get_rsa(idx, &base, &irq);

    if (real_idx != idx) {
        return NULL;
    }

    ck_rsa_priv_t *rsa_priv = &rsa_handle[idx];

    rsa_priv->base = base;
    rsa_priv->irq  = irq;

    /* initialize the rsa context */
    rsa_priv->cb = cb_event;
    rsa_priv->data_bit = RSA_DATA_BITS_1024;
    rsa_priv->endian = RSA_ENDIAN_MODE_LITTLE;
    rsa_priv->padding.padding_type = RSA_PADDING_MODE_PKCS1;
    rsa_priv->padding.hash_type = RSA_HASH_TYPE_SHA1;
    rsa_priv->status.busy = 0;

    return (rsa_handle_t)rsa_priv;
}

/**
  \brief       De-initialize RSA Interface. stops operation and releases the software resources used by the interface
  \param[in]   handle  rsa handle to operate.
  \return      error code
*/
int32_t csi_rsa_uninitialize(rsa_handle_t handle)
{
    RSA_NULL_PARAM_CHK(handle);

    ck_rsa_priv_t *rsa_priv = handle;
    rsa_priv->cb = NULL;

    return 0;
}

/**
  \brief       Get driver capabilities.
  \param[in]   handle rsa handle to operate.
  \return      \ref rsa_capabilities_t
*/
rsa_capabilities_t csi_rsa_get_capabilities(rsa_handle_t handle)
{
    return driver_capabilities;
}

/**
  \brief       config rsa mode.
  \param[in]   handle  rsa handle to operate.
  \param[in]   data_bits \ref rsa_data_bits_e
  \param[in]   endian    \ref rsa_endian_mode_e
  \return      error code
*/
int32_t csi_rsa_config(rsa_handle_t handle,
                       rsa_data_bits_e data_bits,
                       rsa_endian_mode_e endian
                      )
{
    RSA_NULL_PARAM_CHK(handle);

    ck_rsa_priv_t *rsa_priv = handle;
    rsa_reg = (ck_rsa_reg_t *)(rsa_priv->base);

    /* config the data bits */
    switch (data_bits) {
        case RSA_DATA_BITS_192:
        case RSA_DATA_BITS_256:
        case RSA_DATA_BITS_512:
        case RSA_DATA_BITS_2048:
            return ERR_RSA(EDRV_UNSUPPORTED);

        case RSA_DATA_BITS_1024:
            rsa_priv->data_bit = data_bits;
            break;

        default:
            return ERR_RSA(EDRV_PARAMETER);
    }

    /* config the endian mode */
    if (endian == RSA_ENDIAN_MODE_LITTLE) {
        rsa_priv->endian = endian;
    } else if (endian == RSA_ENDIAN_MODE_BIG) {
        return ERR_RSA(EDRV_UNSUPPORTED);
    } else {
        return ERR_RSA(EDRV_PARAMETER);
    }

    return 0;
}

/**
  \brief       encrypt
  \param[in]   handle  rsa handle to operate.
  \param[in]   n         Pointer to the public modulus
  \param[in]   e         Pointer to the public exponent
  \param[in]   src       Pointer to the source data.
  \param[in]   src_size  the source data len
  \param[out]  out       Pointer to the result buffer
  \param[out]  out_size  the result size
  \param[in]   padding   \ref  rsa_padding_t
  \return      error code
*/
int32_t csi_rsa_encrypt(rsa_handle_t handle, void *n, void *e, void *src, int32_t src_size, void *out, uint32_t *out_size, rsa_padding_t padding)
{
    RSA_NULL_PARAM_CHK(handle);
    RSA_NULL_PARAM_CHK(n);
    RSA_NULL_PARAM_CHK(e);
    RSA_NULL_PARAM_CHK(src);
    RSA_NULL_PARAM_CHK(out);
    RSA_NULL_PARAM_CHK(out_size);
    if (src_size <= 0 || (padding.padding_type != RSA_PADDING_MODE_PKCS1 && padding.padding_type != RSA_PADDING_MODE_NO)) {
        return ERR_RSA(EDRV_PARAMETER);
    }

    ck_rsa_priv_t *rsa_priv = handle;
    rsa_priv->status.busy = 1U;
    rsa_encrypt((uint8_t *)n, (uint8_t *)e, (uint8_t *)src, (uint32_t)src_size, (uint8_t *)out, (uint32_t *)out_size, (uint32_t)(padding.padding_type));
    rsa_priv->status.busy = 0U;

    if (rsa_priv->cb) {
        rsa_priv->cb(RSA_EVENT_ENCRYPT_COMPLETE);
    }

    return 0;
}

/**
  \brief       decrypt
  \param[in]   handle  rsa handle to operate.
  \param[in]   n         Pointer to the public modulus
  \param[in]   d         Pointer to the privte exponent
  \param[in]   src       Pointer to the source data.
  \param[in]   src_size  the source data len
  \param[out]  out       Pointer to the result buffer
  \param[out]  out_size  the result size
  \param[in]   padding   \ref rsa_padding_t
  \return      error code
*/
int32_t csi_rsa_decrypt(rsa_handle_t handle, void *n, void *d, void *src, uint32_t src_size, void *out, uint32_t *out_size, rsa_padding_t padding)
{
    RSA_NULL_PARAM_CHK(handle);
    RSA_NULL_PARAM_CHK(n);
    RSA_NULL_PARAM_CHK(d);
    RSA_NULL_PARAM_CHK(src);
    RSA_NULL_PARAM_CHK(out);
    RSA_NULL_PARAM_CHK(out_size);
    if (src_size <= 0 || (padding.padding_type != RSA_PADDING_MODE_PKCS1 && padding.padding_type != RSA_PADDING_MODE_NO)) {
        return ERR_RSA(EDRV_PARAMETER);
    }

    ck_rsa_priv_t *rsa_priv = handle;
    rsa_priv->status.busy = 1U;
    rsa_decrypt((uint8_t *)n, (uint8_t *)d, (uint8_t *)src, (uint32_t)src_size, (uint8_t *)out, (uint32_t *)out_size, (uint32_t)(padding.padding_type));
    rsa_priv->status.busy = 0U;

    if (rsa_priv->cb) {
        rsa_priv->cb(RSA_EVENT_DECRYPT_COMPLETE);
    }

    return 0;
}

/**
  \brief       rsa sign
  \param[in]   handle  rsa handle to operate.
  \param[in]   n         Pointer to the public modulus
  \param[in]   d         Pointer to the privte exponent
  \param[in]   src       Pointer to the source data.
  \param[in]   src_size  the source data len
  \param[out]  signature Pointer to the signature
  \param[out]  sig_size  the signature size
  \param[in]   padding   \ref rsa_padding_t
  \return      error code
*/
int32_t csi_rsa_sign(rsa_handle_t handle, void *n, void *d, void *src, uint32_t src_size, void *signature, void *sig_size, rsa_padding_t padding)
{
    RSA_NULL_PARAM_CHK(handle);
    RSA_NULL_PARAM_CHK(n);
    RSA_NULL_PARAM_CHK(d);
    RSA_NULL_PARAM_CHK(src);
    RSA_NULL_PARAM_CHK(signature);
    RSA_NULL_PARAM_CHK(sig_size);
    if (src_size <= 0 || (padding.hash_type != RSA_HASH_TYPE_MD5 && padding.hash_type != RSA_HASH_TYPE_SHA1)) {
        return ERR_RSA(EDRV_PARAMETER);
    }

    ck_rsa_priv_t *rsa_priv = handle;
    rsa_priv->status.busy = 1U;
    rsa_sign((uint8_t *)n, (uint8_t *)d, (uint8_t *)src, (uint32_t)src_size, (uint8_t *)signature, (uint32_t *)sig_size, (uint32_t)(padding.hash_type));
    rsa_priv->status.busy = 0U;

    if (rsa_priv->cb) {
        rsa_priv->cb(RSA_EVENT_SIGN_COMPLETE);
    }

    return 0;
}

/**
  \brief       rsa verify
  \param[in]   handle  rsa handle to operate.
  \param[in]   n         Pointer to the public modulus
  \param[in]   e         Pointer to the public exponent
  \param[in]   src       Pointer to the source data.
  \param[in]   src_size  the source data len
  \param[in]   signature Pointer to the signature
  \param[in]   sig_size  the signature size
  \param[out]  result    Pointer to the result
  \param[in]   padding   \ref rsa_padding_t
  \return      error code
*/
int32_t csi_rsa_verify(rsa_handle_t handle, void *n, void *e, void *src, uint32_t src_size, void *signature, uint32_t sig_size, void *result, rsa_padding_t padding)
{
    RSA_NULL_PARAM_CHK(handle);
    RSA_NULL_PARAM_CHK(n);
    RSA_NULL_PARAM_CHK(e);
    RSA_NULL_PARAM_CHK(src);
    RSA_NULL_PARAM_CHK(signature);
    RSA_NULL_PARAM_CHK(result);
    if (src_size <= 0 || sig_size <= 0 || (padding.hash_type != RSA_HASH_TYPE_MD5 && padding.hash_type != RSA_HASH_TYPE_SHA1)) {
        return ERR_RSA(EDRV_PARAMETER);
    }

    ck_rsa_priv_t *rsa_priv = handle;
    rsa_priv->status.busy = 1U;
    rsa_verify((uint8_t *)n, (uint8_t *)e, (uint8_t *)src, (uint32_t)src_size, (uint8_t *)signature, sig_size, (uint8_t *)result, (uint32_t)(padding.hash_type));
    rsa_priv->status.busy = 0U;

    if (rsa_priv->cb) {
        rsa_priv->cb(RSA_EVENT_VERIFY_COMPLETE);
    }

    return 0;
}

/**
  \brief       Get RSA status.
  \param[in]   handle  rsa handle to operate.
  \return      RSA status \ref rsa_status_t
*/
rsa_status_t csi_rsa_get_status(rsa_handle_t handle)
{
    ck_rsa_priv_t *rsa_priv = handle;
    return rsa_priv->status;
}
