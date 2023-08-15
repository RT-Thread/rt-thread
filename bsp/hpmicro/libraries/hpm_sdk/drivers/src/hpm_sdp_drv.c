/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */
#include "hpm_sdp_drv.h"
#include "hpm_soc_feature.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/**
 * AES Key source definition
 */
#define AES_KEY_SRC_SDP_START_IDX 0U
#define AES128_KEY_SRC_SDP_END_IDX 0xFU
#define AES256_KEY_SRC_SDP_END_IDX 0x7U
#define AES_KEY_SRC_KEYMAN_START_IDX 0x20U
#define AES128_KEY_SRC_KEYMAN_END_IDX 0x2FU
#define AES256_KEY_SRC_KEYMAN_END_IDX 0x2FU
#define AES_KEY_SRC_UNIQUE_KEY_START_IDX 0x3EU
#define AES_KEY_SRC_OTP_KEY_START_IDX 0x3FU

#define AES_256_KEY_SIZE_IN_WORDS (8U)
#define AES_256_KEY_SIZE_IN_BYTES (32U)

#define CRC32_DIGEST_SIZE_IN_BYTES (4U)
#define SHA1_DIGEST_SIZE_IN_BYTES  (20U)
#define SHA256_DIGEST_SIZE_IN_BYTES (32U)

#define AES_CTR_BLOCK_UNIT (16U)

typedef enum {
    sdp_state_hash_init, sdp_state_hash_update,
} sdp_hash_alg_state_t;

#define AES_BLOCK_SIZE (16U)
#define HASH_BLOCK_SIZE (64U)
#define HASH_DIGEST_SIZE_MAX (32)

#define SDP_CRYPTO_ALG_IDX_AES128 (0U)
#define SDP_CRYPTO_ALG_IDX_AES256 (1U)
#define SDP_CRYPTO_ALG_IDX_SM4 (8U)

typedef struct {
    union {
        uint32_t words[HASH_BLOCK_SIZE / sizeof(uint32_t)];
        uint8_t bytes[HASH_BLOCK_SIZE];
    } block;
    uint32_t blk_size;
    uint32_t full_msg_size;
    uint32_t running_hash[HASH_DIGEST_SIZE_MAX / sizeof(uint32_t)];
    sdp_hash_alg_t alg;
    sdp_hash_alg_state_t state;
    bool hash_init;
    bool hash_finish;
} sdp_hash_internal_ctx_t;

/***********************************************************************************************************************
 * Prototypes
 **********************************************************************************************************************/
static void sdp_hash_internal_engine_init(SDP_Type *base, sdp_hash_ctx_t *hash_ctx);

static hpm_stat_t sdp_hash_process_message(SDP_Type *base, sdp_hash_ctx_t *ctx, const uint8_t *msg, uint32_t msg_size);

static hpm_stat_t sdp_hash_internal_update(SDP_Type *base, sdp_hash_ctx_t *ctx, const uint8_t *msg, uint32_t msg_size);

static hpm_stat_t sdp_hash_finalize(SDP_Type *base, sdp_hash_ctx_t *hash_ctx);

static inline void sdp_clear_error_status(SDP_Type *base)
{
    base->STA = 0xFFFFFFFFUL;
}

static void sdp_increment_bn(uint8_t *big_num, uint32_t bytes);

static void uint32_to_be(uint8_t *dst, uint32_t len, uint32_t num);

static hpm_stat_t aes_ccm_auth_crypt(SDP_Type *base,
                                     sdp_aes_ctx_t *aes_ctx,
                                     sdp_aes_op_t op,
                                     uint32_t input_len,
                                     const uint8_t *iv,
                                     uint32_t iv_len,
                                     const uint8_t *aad,
                                     uint32_t aad_len,
                                     const uint8_t *input,
                                     uint8_t *output,
                                     uint8_t *mac,
                                     uint32_t mac_len);

static void aes_ccm_format_b0(uint8_t *block,
                              const uint8_t *iv,
                              uint32_t iv_len,
                              uint32_t mac_len,
                              uint32_t aad_len,
                              uint32_t input_len);

static void aes_ccm_format_ctr0(uint8_t *ctr, const uint8_t *iv, uint8_t iv_len);

static uint8_t sdp_constant_time_cmp(const void *dst, const void *src, uint32_t len);

/***********************************************************************************************************************
 * Codes
 **********************************************************************************************************************/
hpm_stat_t sdp_wait_done(SDP_Type *base)
{
    hpm_stat_t status;
    uint32_t sdp_sta;
    do {
        sdp_sta = base->STA;
        if (IS_HPM_BITMASK_SET(sdp_sta, SDP_STA_ERRSET_MASK)) {
            status = status_sdp_error_setup;
        } else if (IS_HPM_BITMASK_SET(sdp_sta, SDP_STA_ERRPKT_MASK)) {
            status = status_sdp_error_packet;
        } else if (IS_HPM_BITMASK_SET(sdp_sta, SDP_STA_ERRSRC_MASK)) {
            status = status_sdp_error_src;
        } else if (IS_HPM_BITMASK_SET(sdp_sta, SDP_STA_ERRDST_MASK)) {
            status = status_sdp_error_dst;
        } else if (IS_HPM_BITMASK_SET(sdp_sta, SDP_STA_ERRHAS_MASK)) {
            status = status_sdp_error_hash;
        } else if (IS_HPM_BITMASK_SET(sdp_sta, SDP_STA_ERRCHAIN_MASK)) {
            status = status_sdp_error_chain;
        } else {
            status = status_success;
        }
    } while (IS_HPM_BITMASK_CLR(sdp_sta, SDP_STA_PKTCNT0_MASK));

    return status;
}

hpm_stat_t sdp_init(SDP_Type *base)
{
    hpm_stat_t status = status_invalid_argument;
    if (base != NULL) {
        base->SDPCR &= ~(SDP_SDPCR_CLKGAT_MASK | SDP_SDPCR_SFTRST_MASK);

        status = status_success;
    }

    return status;
}

hpm_stat_t sdp_deinit(SDP_Type *base)
{
    hpm_stat_t status = status_invalid_argument;
    if (base != NULL) {
        base->SDPCR |= SDP_SDPCR_CLKGAT_MASK;
        status = status_success;
    }
    return status;
}

hpm_stat_t sdp_aes_set_key(SDP_Type *base,
                           sdp_aes_ctx_t *aes_ctx,
                           const uint8_t *key,
                           sdp_aes_key_bits_t key_bits,
                           uint32_t key_idx)
{
    union {
        uint32_t words[AES_256_KEY_SIZE_IN_WORDS];
        uint8_t bytes[AES_256_KEY_SIZE_IN_BYTES];
    } aes_key;

    assert((base != NULL) && (aes_ctx != NULL) && (key_bits <= sdp_aes_keybits_256));

    hpm_stat_t status = status_invalid_argument;
    do {
        aes_ctx->crypto_algo = sdp_crypto_alg_aes;

        if (IS_HPM_BITMASK_SET(base->SDPCR, SDP_SDPCR_CIPDIS_MASK)) {
            status = status_sdp_no_crypto_support;
            break;
        }

        HPM_BREAK_IF((key_bits != sdp_aes_keybits_128) && (key_bits != sdp_aes_keybits_256));

        aes_ctx->key_bits = key_bits;

        uint32_t key128_idx = key_idx;
        if (key_bits == sdp_aes_keybits_256) {
            if (key_idx <= AES256_KEY_SRC_SDP_END_IDX) {
                (void) memcpy(aes_key.bytes, key, 32);
                key128_idx = key_idx * 2U;
                uint32_t idx = 0;
                for (uint32_t i = 0; i < 2; i++) {
                    base->KEYADDR = SDP_KEYADDR_INDEX_SET(key128_idx + i);
                    for (uint32_t j = 0; j < 4; j++) {
                        base->KEYDAT = aes_key.words[idx++];
                    }
                }
            } else if ((key_idx >= AES_KEY_SRC_KEYMAN_START_IDX) && (key_idx <= AES256_KEY_SRC_KEYMAN_END_IDX)) {
                key128_idx = (key_idx - AES_KEY_SRC_KEYMAN_START_IDX) * 2U + AES_KEY_SRC_KEYMAN_START_IDX;
            }
        } else {
            if (key_idx <= AES128_KEY_SRC_SDP_END_IDX) {
                (void) memcpy(aes_key.bytes, key, 16);
                base->KEYADDR = SDP_KEYADDR_INDEX_SET(key_idx);
                for (uint32_t j = 0; j < 4; j++) {
                    base->KEYDAT = aes_key.words[j];
                }
            }
        }

        aes_ctx->key_idx = key128_idx;
        aes_ctx->key_bits = key_bits;
        status = status_success;

    } while (false);

    return status;
}

#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
hpm_stat_t sdp_sm4_set_key(SDP_Type *base,
                           sdp_sm4_ctx_t *sm4_ctx,
                           const uint8_t *key,
                           sdp_sm4_key_bits_t key_bits,
                           uint32_t key_idx)
{
    hpm_stat_t status = status_invalid_argument;
    if (key_bits != sdp_sm4_keybits_128) {
        return status;
    }
    status = sdp_aes_set_key(base, sm4_ctx, key, (sdp_aes_key_bits_t) key_bits, key_idx);
    if (status != status_success) {
        return status;
    }
    sm4_ctx->crypto_algo = sdp_crypto_alg_sm4;

    return status;
}
#endif

hpm_stat_t sdp_aes_crypt_ecb(SDP_Type *base,
                             sdp_aes_ctx_t *aes_ctx,
                             sdp_aes_op_t op,
                             uint32_t len,
                             const uint8_t *in,
                             uint8_t *out)
{
    assert((base != NULL) && (aes_ctx != NULL));

    hpm_stat_t status;

    base->SDPCR = SDP_SDPCR_CIPHEN_MASK;
#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->SDPCR |= HPM_BITSMASK(1, 8);
    base->PKTCTL = SDP_PKT_CTRL_DERSEMA_MASK;
    base->PKTSRC = (uint32_t) in;
    base->PKTDST = (uint32_t) out;
    base->PKTBUF = len;
#else
    sdp_pkt_struct_t *pkt_desc = &aes_ctx->sdp_pkt;
    pkt_desc->next_cmd = NULL;
    pkt_desc->pkt_ctrl.PKT_CTRL = SDP_PKT_CTRL_DERSEMA_MASK;
    pkt_desc->src_addr = (uint32_t) in;
    pkt_desc->dst_addr = (uint32_t) out;
    pkt_desc->buf_size = len;

#endif
    sdp_clear_error_status(base);

    if (aes_ctx->crypto_algo == sdp_crypto_alg_aes) {
        if (aes_ctx->key_bits == sdp_aes_keybits_128) {
            base->MODCTRL =
                SDP_MODCTRL_AESALG_SET(SDP_CRYPTO_ALG_IDX_AES128) | SDP_MODCTRL_AESKS_SET(aes_ctx->key_idx) |
                    SDP_MODCTRL_AESDIR_SET(op);
        } else {
            base->MODCTRL =
                SDP_MODCTRL_AESALG_SET(SDP_CRYPTO_ALG_IDX_AES256) | SDP_MODCTRL_AESKS_SET(aes_ctx->key_idx) |
                    SDP_MODCTRL_AESDIR_SET(op);
        }
    }
#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
    else if (aes_ctx->crypto_algo == sdp_crypto_alg_sm4) {
        base->MODCTRL = SDP_MODCTRL_AESALG_SET(SDP_CRYPTO_ALG_IDX_SM4) | SDP_MODCTRL_AESKS_SET(aes_ctx->key_idx) |
            SDP_MODCTRL_AESDIR_SET(op);
    }
#endif
    else {
        return status_sdp_invalid_alg;
    }

#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->CMDPTR = 0;
#else
    base->CMDPTR = (uint32_t) pkt_desc;
#endif
    base->PKTCNT = 1U;

    status = sdp_wait_done(base);

    return status;
}

hpm_stat_t sdp_aes_crypt_cbc(SDP_Type *base,
                             sdp_aes_ctx_t *aes_ctx,
                             sdp_aes_op_t op,
                             uint32_t length,
                             const uint8_t iv[16],
                             const uint8_t *input,
                             uint8_t *output)
{
    assert((base != NULL) && (aes_ctx != NULL));
    assert((op <= sdp_aes_op_decrypt) && (input != NULL) && (output != NULL));

    hpm_stat_t status;

    base->SDPCR = SDP_SDPCR_CIPHEN_MASK;
#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->SDPCR |= HPM_BITSMASK(1, 8);
    base->PKTCTL = SDP_PKT_CTRL_DERSEMA_MASK | SDP_PKT_CTRL_CIPHIV_MASK;
    base->PKTSRC = (uint32_t) input;
    base->PKTDST = (uint32_t) output;
    base->PKTBUF = length;
#else
    sdp_pkt_struct_t *pkt_desc = &aes_ctx->sdp_pkt;
    pkt_desc->next_cmd = NULL;
    pkt_desc->pkt_ctrl.PKT_CTRL = SDP_PKT_CTRL_DERSEMA_MASK | SDP_PKT_CTRL_CIPHIV_MASK;
    pkt_desc->src_addr = (uint32_t) input;
    pkt_desc->dst_addr = (uint32_t) output;
    pkt_desc->buf_size = length;
#endif

    sdp_clear_error_status(base);

    if (aes_ctx->crypto_algo == sdp_crypto_alg_aes) {
        if (aes_ctx->key_bits == sdp_aes_keybits_128) {
            base->MODCTRL =
                SDP_MODCTRL_AESALG_SET(SDP_CRYPTO_ALG_IDX_AES128) | SDP_MODCTRL_AESKS_SET(aes_ctx->key_idx) |
                    SDP_MODCTRL_AESDIR_SET(op) | SDP_MODCTRL_AESMOD_SET(1);
        } else {
            base->MODCTRL =
                SDP_MODCTRL_AESALG_SET(SDP_CRYPTO_ALG_IDX_AES256) | SDP_MODCTRL_AESKS_SET(aes_ctx->key_idx) |
                    SDP_MODCTRL_AESDIR_SET(op) | SDP_MODCTRL_AESMOD_SET(1);
        }
    }
#if defined(SDP_HAS_SM4_SUPPORT) && (SDP_HAS_SM4_SUPPORT == 1)
    else if (aes_ctx->crypto_algo == sdp_crypto_alg_sm4) {
        base->MODCTRL = SDP_MODCTRL_AESALG_SET(SDP_CRYPTO_ALG_IDX_SM4) | SDP_MODCTRL_AESKS_SET(aes_ctx->key_idx) |
            SDP_MODCTRL_AESDIR_SET(op) | SDP_MODCTRL_AESMOD_SET(1);
    }
#endif
    else {
        return status_sdp_invalid_alg;
    }

    /* Set IV, copy the IV to the context first in case the IV address is not 32-bit aligned */
    uint32_t iv_32[4];
    (void) memcpy(iv_32, iv, 16);
    for (uint32_t i = 0; i < 4; i++) {
        base->CIPHIV[i] = iv_32[i];
    }
    (void) memset(iv_32, 0, sizeof(iv_32));
#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->CMDPTR = 0;
#else
    base->CMDPTR = (uint32_t) pkt_desc;
#endif
    base->PKTCNT = 1U;

    status = sdp_wait_done(base);

    return status;
}

/*
 * In the AES-CTR algorithm, all the numbers are represented in big-endian format, namely, LSB is in last byte
 */
static void sdp_increment_bn(uint8_t *big_num, uint32_t bytes)
{
    for (uint32_t i = bytes - 1; i > 0u; i--) {
        big_num[i]++;
        if (big_num[i] != 0) {
            break;
        }
    }
}

hpm_stat_t sdp_aes_crypt_ctr(SDP_Type *base,
                             sdp_aes_ctx_t *aes_ctx,
                             uint8_t *nonce_counter,
                             uint8_t *input,
                             uint8_t *output,
                             uint32_t length)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        HPM_BREAK_IF(
            (base == NULL) || (aes_ctx == NULL) || (nonce_counter == NULL) || (input == NULL) || (output == NULL));

        uint32_t calc_len;
        uint8_t *cipher_nonce = (uint8_t *) &aes_ctx->buf3;
        while (length > 0) {
            calc_len = (length < 16U) ? length : 16U;
            status = sdp_aes_crypt_ecb(base, aes_ctx, sdp_aes_op_encrypt, 16, nonce_counter, cipher_nonce);
            HPM_BREAK_IF(status != status_success);
            uint8_t tmp;
            for (uint32_t i = 0; i < calc_len; i++) {
                tmp = *input++;
                *output++ = (uint8_t) (tmp ^ cipher_nonce[i]);
            }

            length -= calc_len;
            /* Increment counter, (128-bit big-endian */
            sdp_increment_bn(nonce_counter, AES_CTR_BLOCK_UNIT);
        }

    } while (false);

    return status;
}

static void uint32_to_be(uint8_t *dst, uint32_t len, uint32_t num)
{
    uint32_t i = 0;

    (void) memset(dst, 0, len);

    while (num > 0) {
        dst[len - 1 - i] = num & 0xFF;
        num >>= 8;
        i++;
    }
}

/*
 * See section A2.1 in NIST Special Publication 800-38C
 * q + n = 15
 * n - nonce / iv
 * byte0 = FLAG
 * bit[2:0] - (q-1)
 * bit[5:3] - (t-2/2
 * bit[6] - adata
 * bit[7] - reserved
 *
 * byte (1... 15-q) nonce
 * byte (16-q...15) input length
 *
 */
static void aes_ccm_format_b0(uint8_t *block,
                              const uint8_t *iv,
                              uint32_t iv_len,
                              uint32_t mac_len,
                              uint32_t aad_len,
                              uint32_t input_len)
{
    uint8_t q = 15U - iv_len;
    block[0] = 0;
    block[0] |= (aad_len > 0) ? (1U << 6) : 0U;
    block[0] |= ((mac_len - 2U) / 2U) << 3;
    block[0] |= q - 1U;

    (void) memcpy(block + 1U, iv, iv_len);

    uint32_to_be(block + 1U + iv_len, q, input_len);

}

/*
 * See section A2.3 in NIST Special Publication 800-38C
 *  q + n = 15
 *  n - nonce/iv
 *  byte 0 = FLAG
 *  bit[2:0] : (q - 1)
 *  bit[5:3] : 0
 *  bit[7:6] : 0
 *
 *  byte (1...15-q) nonce
 *  byte (16-q ...15) i
 */
static void aes_ccm_format_ctr0(uint8_t *ctr, const uint8_t *iv, uint8_t iv_len)
{
    uint8_t q = 15U - iv_len;
    (void) memset(ctr, 0, 16);
    ctr[0] |= q - 1U;
    (void) memcpy(ctr + 1U, iv, iv_len);
}

static hpm_stat_t aes_ccm_auth_crypt(SDP_Type *base,
                                     sdp_aes_ctx_t *aes_ctx,
                                     sdp_aes_op_t op,
                                     uint32_t input_len,
                                     const uint8_t *iv,
                                     uint32_t iv_len,
                                     const uint8_t *aad,
                                     uint32_t aad_len,
                                     const uint8_t *input,
                                     uint8_t *output,
                                     uint8_t *tag,
                                     uint32_t tag_len)
{
    hpm_stat_t status = status_invalid_argument;

    do {
        HPM_BREAK_IF((base == NULL) || (aes_ctx == NULL) || (input == NULL) || (output == NULL) || (tag == NULL));


        /*See section A.1 in NIST Special Publication 800-38C */

        /* Valid Tlen is 4, 6, 8, 10, 12, 14, 16 */
        HPM_BREAK_IF((tag_len % 2U != 0U) || (tag_len / 2U < 2) || (tag_len / 2U > 8));
        /* Valid Nonce length is 7, 8, 9, 10, 11, 12, 13 */
        HPM_BREAK_IF((iv_len < 7U) || (iv_len > 13U));

        /* Note, this API supports maximum 2^32 - 1 bytes of data, so the valid q value should be 2, 3, or 4  */
        uint8_t *b = (uint8_t *) &aes_ctx->buf0;
        uint8_t *y = (uint8_t *) &aes_ctx->buf1;
        uint8_t *ctr = (uint8_t *) &aes_ctx->buf2;
        uint32_t i = 0;

        /* Format B0 */
        aes_ccm_format_b0(b, iv, iv_len, tag_len, aad_len, input_len);

        /* Calculate Y0 */
        sdp_aes_crypt_ecb(base, aes_ctx, sdp_aes_op_encrypt, 16, b, y);


        /*
         * Follow A2.2.2 in NIST Special Publication 800-38C, only supports up to 2^32 bytes
         */
        if (aad_len > 0U) {
            uint32_t calc_len = 0U;
            const uint8_t *aad_src = aad;
            uint32_t remaining_len = aad_len;
            (void) memset(b, 0, 16);
            /* format B1
             * Follow A2.2.2 in NIST Special Publication 800-38C, only supports up to 2^32 bytes
             */
            if (aad_len < ((1UL << 16) - (1U << 8))) {
                uint32_to_be(b, 2, aad_len);
                calc_len = MIN(remaining_len, 14U);
                (void) memcpy(&b[2], aad_src, calc_len);
            } else {
                b[0] = 0xFFU;
                b[1] = 0xFEU;
                uint32_to_be(&b[6], 4, calc_len);
                calc_len = 10U;
                (void) memcpy(&b[2], aad_src, calc_len);
            }
            aad_src += calc_len;
            remaining_len -= calc_len;
            /* Calculate Y(i) = CIPHk(B(i) ^ Y(i-1)) */
            ++i;
            sdp_aes_crypt_cbc(base, aes_ctx, sdp_aes_op_encrypt, 16, b, y, y);

            while (remaining_len > 0U) {
                calc_len = MIN(remaining_len, 16U);
                (void) memcpy(b, aad_src, calc_len);
                if (calc_len < 16U) {
                    (void) memset(&b[calc_len], 0, 16U - calc_len);
                }
                aad_src += calc_len;
                remaining_len -= calc_len;
                /* Calculate Y(i) = CIPHk(B(i) ^ Y(i-1)) */
                ++i;
                sdp_aes_crypt_cbc(base, aes_ctx, sdp_aes_op_encrypt, 16, b, y, y);
            }
        }

        aes_ccm_format_ctr0(ctr, iv, iv_len);
        i = 0;
        /* Encryption/Decryption starts from CTR1 */
        sdp_increment_bn(ctr, 16);
        ++i;
        /* Continue CBC-MAC calculation + Encryption/Decryption */
        uint32_t remaining_len = input_len;
        uint8_t *src = (uint8_t *) input;
        uint8_t *dst = output;
        while (remaining_len > 0U) {
            uint32_t calc_len = MIN(remaining_len, 16U);
            if (op == sdp_aes_op_encrypt) {
                (void) memcpy(b, src, calc_len);
                if (calc_len < 16U) {
                    (void) memset(&b[calc_len], 0, 16U - calc_len);
                }
                /* Calculate Y(i) = CIPHk(B(i) ^ Y(i-1)) */
                sdp_aes_crypt_cbc(base, aes_ctx, sdp_aes_op_encrypt, 16, b, y, y);
            }
            sdp_aes_crypt_ctr(base, aes_ctx, ctr, src, dst, calc_len);
            if (op == sdp_aes_op_decrypt) {
                (void) memcpy(b, dst, calc_len);
                if (calc_len < 16U) {
                    (void) memset(&b[calc_len], 0, 16U - calc_len);
                }
                /* Calculate Y(i) = CIPHk(B(i) ^ Y(i-1)) */
                sdp_aes_crypt_cbc(base, aes_ctx, sdp_aes_op_encrypt, 16, b, y, y);
            }
            src += calc_len;
            dst += calc_len;
            remaining_len -= calc_len;
            ++i;
        }

        /* Get CTR0 */
        aes_ccm_format_ctr0(ctr, iv, iv_len);
        /* Get MAC */
        sdp_aes_crypt_ctr(base, aes_ctx, ctr, y, b, 16);
        /* Copy mac to the destination */
        (void) memcpy(tag, b, tag_len);

        /* Wipe-out temporary data */
        (void) memset(b, 0, 16U);
        (void) memset(y, 0, 16);
        (void) memset(ctr, 0, 16);

        status = status_success;

    } while (false);
    return status;
}

hpm_stat_t sdp_aes_ccm_generate_encrypt(SDP_Type *base,
                                        sdp_aes_ctx_t *aes_ctx,
                                        uint32_t input_len,
                                        const uint8_t *iv,
                                        uint32_t iv_len,
                                        const uint8_t *aad,
                                        uint32_t aad_len,
                                        const uint8_t *input,
                                        uint8_t *output,
                                        uint8_t *tag,
                                        uint32_t tag_len)
{
    return aes_ccm_auth_crypt(base,
                              aes_ctx,
                              sdp_aes_op_encrypt,
                              input_len,
                              iv,
                              iv_len,
                              aad,
                              aad_len,
                              input,
                              output,
                              tag,
                              tag_len);
}

static uint8_t sdp_constant_time_cmp(const void *dst, const void *src, uint32_t len)
{
    uint8_t result = 0U;

    const uint8_t *dst_8 = (const uint8_t *) dst;
    const uint8_t *src_8 = (const uint8_t *) src;

    while (len-- > 0U) {
        result |= *dst_8 ^ *src_8;
        ++dst_8;
        ++src_8;

    }
    return result;
}

hpm_stat_t sdp_aes_ccm_decrypt_verify(SDP_Type *base,
                                      sdp_aes_ctx_t *aes_ctx,
                                      uint32_t input_len,
                                      const uint8_t *iv,
                                      uint32_t iv_len,
                                      const uint8_t *aad,
                                      uint32_t aad_len,
                                      const uint8_t *input,
                                      uint8_t *output,
                                      const uint8_t *tag,
                                      uint32_t tag_len)
{
    hpm_stat_t status;

    do {

        uint32_t calc_mac[4];

        status = aes_ccm_auth_crypt(base,
                                    aes_ctx,
                                    sdp_aes_op_decrypt,
                                    input_len,
                                    iv,
                                    iv_len,
                                    aad,
                                    aad_len,
                                    input,
                                    output,
                                    (uint8_t *) &calc_mac,
                                    tag_len);
        HPM_BREAK_IF(status != status_success);
        if (sdp_constant_time_cmp(calc_mac, tag, tag_len) != 0U) {
            status = status_sdp_error_invalid_mac;
        } else {
            status = status_success;
        }

    } while (false);

    return status;
}

hpm_stat_t sdp_hash_init(SDP_Type *base, sdp_hash_ctx_t *hash_ctx, sdp_hash_alg_t alg)
{
    hpm_stat_t status = status_invalid_argument;
    do {
        if (IS_HPM_BITMASK_SET(base->SDPCR, SDP_SDPCR_HASDIS_MASK)) {
            status = status_sdp_no_hash_support;
            break;
        }

        /* Initialize the SDP HASH context */
        sdp_hash_internal_ctx_t *ctx_internal = (sdp_hash_internal_ctx_t *) &hash_ctx->internal;
        (void) memset(ctx_internal, 0, sizeof(*ctx_internal));
        ctx_internal->alg = alg;
        ctx_internal->blk_size = 0;
        ctx_internal->state = sdp_state_hash_init;
        ctx_internal->full_msg_size = 0;

        status = status_success;

    } while (false);

    return status;
}

static void sdp_hash_internal_engine_init(SDP_Type *base, sdp_hash_ctx_t *hash_ctx)
{
    sdp_hash_internal_ctx_t *ctx_internal = (sdp_hash_internal_ctx_t *) &hash_ctx->internal;

    ctx_internal->hash_init = true;
    ctx_internal->hash_finish = false;
}

static hpm_stat_t sdp_hash_internal_update(SDP_Type *base, sdp_hash_ctx_t *ctx, const uint8_t *msg, uint32_t msg_size)
{
    sdp_hash_internal_ctx_t *ctx_internal = (sdp_hash_internal_ctx_t *) &ctx->internal;
    sdp_pkt_struct_t *pkt_desc = (sdp_pkt_struct_t *) &ctx->sdp_pkt;

    pkt_desc->next_cmd = NULL;
    uint32_t pkt_ctrl = SDP_PKT_CTRL_DERSEMA_MASK;
    if (ctx_internal->hash_init) {
        pkt_ctrl |= SDP_PKT_CTRL_HASHINIT_MASK;
        ctx_internal->hash_init = false;
    }
    if (ctx_internal->hash_finish) {
        pkt_ctrl |= SDP_PKT_CTRL_HASHFINISH_MASK;
        ctx_internal->hash_finish = false;
    }

    base->SDPCR = SDP_SDPCR_HASHEN_MASK;
#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->SDPCR |= HPM_BITSMASK(1, 8);
    base->NPKTPTR = 0UL;
    base->PKTCTL = pkt_ctrl;
    base->PKTSRC = (uint32_t) msg;
    base->PKTDST = (uint32_t) 0;
    base->PKTBUF = msg_size;
#else
    pkt_desc->pkt_ctrl.PKT_CTRL = pkt_ctrl;
    pkt_desc->src_addr = (uint32_t) msg;
    pkt_desc->dst_addr = 0;
    pkt_desc->buf_size = msg_size;
    pkt_desc->reserved[0] = 0;
    pkt_desc->reserved[1] = 0;
    pkt_desc->reserved[2] = 0;
#endif

    sdp_clear_error_status(base);
    base->MODCTRL = SDP_MODCTRL_HASALG_SET(ctx_internal->alg);
#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->CMDPTR = 0;
#else
    base->CMDPTR = (uint32_t) pkt_desc;
#endif
    base->PKTCNT = 1;

    hpm_stat_t status = sdp_wait_done(base);

    return status;
}

static hpm_stat_t sdp_hash_process_message(SDP_Type *base, sdp_hash_ctx_t *ctx, const uint8_t *msg, uint32_t msg_size)
{
    hpm_stat_t status = status_invalid_argument;

    sdp_hash_internal_ctx_t *ctx_internal = (sdp_hash_internal_ctx_t *) &ctx->internal;
    /* If there is partially filled internal buffer, fill it to full block */
    if (ctx_internal->blk_size > 0U) {
        uint32_t size_to_copy = HASH_BLOCK_SIZE - ctx_internal->blk_size;
        (void) memcpy(&ctx_internal->block.bytes[ctx_internal->blk_size], msg, size_to_copy);
        msg += size_to_copy;
        msg_size -= size_to_copy;

        /* process the full internal block */
        status = sdp_hash_internal_update(base, ctx, &ctx_internal->block.bytes[0], HASH_BLOCK_SIZE);
        if (status != status_success) {
            return status;
        }
    }

    /* Process all full blocks in message */
    uint32_t full_blk_size = (msg_size >> 6) << 6;
    if (full_blk_size > 0U) {
        status = sdp_hash_internal_update(base, ctx, msg, full_blk_size);
        if (status != status_success) {
            return status;
        }
        msg += full_blk_size;
        msg_size -= full_blk_size;
    }

    (void) memcpy(&ctx_internal->block.bytes[0], msg, msg_size);
    ctx_internal->blk_size = msg_size;

    return status;
}

hpm_stat_t sdp_hash_update(SDP_Type *base, sdp_hash_ctx_t *hash_ctx, const uint8_t *data, uint32_t length)
{
    assert((base != NULL) && (hash_ctx != NULL) && (data != NULL));
    hpm_stat_t status = status_invalid_argument;
    do {
        if (length == 0) {
            status = status_success;
            break;
        }

        sdp_hash_internal_ctx_t *ctx_internal = (sdp_hash_internal_ctx_t *) &hash_ctx->internal;
        uint32_t block_size = HASH_BLOCK_SIZE;
        ctx_internal->full_msg_size += length;
        /* If the data is still less than HASH_BLOCK_SIZE, keep them only in the buffer */
        if ((ctx_internal->blk_size + length) <= block_size) {
            (void) memcpy(&ctx_internal->block.bytes[0] + ctx_internal->blk_size, data, length);
            ctx_internal->blk_size += length;
            status = status_success;
            break;
        } else {
            if (ctx_internal->state != sdp_state_hash_update) {
                sdp_hash_internal_engine_init(base, hash_ctx);
                ctx_internal->state = sdp_state_hash_update;
            }
        }

        /* Process input data */
        status = sdp_hash_process_message(base, hash_ctx, data, length);
    } while (false);

    return status;
}

static hpm_stat_t sdp_hash_finalize(SDP_Type *base, sdp_hash_ctx_t *hash_ctx)
{
    sdp_hash_internal_ctx_t *ctx_internal = (sdp_hash_internal_ctx_t *) &hash_ctx->internal;
    hpm_stat_t status;
    ctx_internal->hash_finish = true;

    status = sdp_hash_internal_update(base, hash_ctx, &ctx_internal->block.bytes[0], ctx_internal->blk_size);

    return status;
}

hpm_stat_t sdp_hash_finish(SDP_Type *base, sdp_hash_ctx_t *hash_ctx, uint8_t *digest)
{
    assert((base != NULL) && (hash_ctx != NULL) && (digest != NULL));

    hpm_stat_t status = status_invalid_argument;
    do {
        sdp_hash_internal_ctx_t *ctx_internal = (sdp_hash_internal_ctx_t *) &hash_ctx->internal;
        if (ctx_internal->state == sdp_state_hash_init) {
            sdp_hash_internal_engine_init(base, hash_ctx);
        }
        status = sdp_hash_finalize(base, hash_ctx);
        HPM_BREAK_IF(status != status_success);

        uint32_t copy_bytes = 0;
        uint32_t digest_words = 0;
        switch (ctx_internal->alg) {
        case sdp_hash_alg_crc32:
            copy_bytes = CRC32_DIGEST_SIZE_IN_BYTES;
            ctx_internal->running_hash[0] = base->HASWRD[0];
            break;
        case sdp_hash_alg_sha1:
            copy_bytes = SHA1_DIGEST_SIZE_IN_BYTES;
            digest_words = copy_bytes / sizeof(uint32_t);
            for (uint32_t i = 0; i < digest_words; i++) {
                ctx_internal->running_hash[i] = base->HASWRD[i];
            }
            break;
        case sdp_hash_alg_sha256:
#if defined(SDP_HAS_SM3_SUPPORT) && (SDP_HAS_SM3_SUPPORT == 1)
        case sdp_hash_alg_sm3:
#endif
            copy_bytes = SHA256_DIGEST_SIZE_IN_BYTES;
            digest_words = copy_bytes / sizeof(uint32_t);
            for (uint32_t i = 0; i < digest_words; i++) {
                ctx_internal->running_hash[i] = base->HASWRD[i];
            }
            break;
        default:
            /* Never reach here */
            break;
        }
        (void) memcpy(digest, ctx_internal->running_hash, copy_bytes);
    } while (false);

    return status;
}

hpm_stat_t sdp_memcpy(SDP_Type *base, sdp_dma_ctx_t *dma_ctx, void *dst, const void *src, uint32_t length)
{
    hpm_stat_t status = status_invalid_argument;

    if (length == 0) {
        status = status_success;
        return status;
    }

    base->SDPCR = SDP_SDPCR_MCPEN_MASK;
#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->SDPCR |= HPM_BITSMASK(1, 8);
    base->NPKTPTR = 0;
    base->PKTCTL = SDP_PKT_CTRL_DERSEMA_MASK | SDP_PKTCTL_PKTTAG_SET(1);
    base->PKTSRC = (uint32_t) src;
    base->PKTDST = (uint32_t) dst;
    base->PKTBUF = length;
#else
    sdp_pkt_struct_t *pkt_desc = &dma_ctx->sdp_pkt;
    pkt_desc->next_cmd = NULL;
    pkt_desc->pkt_ctrl.PKT_CTRL = SDP_PKT_CTRL_DERSEMA_MASK;
    pkt_desc->src_addr = (uint32_t) src;
    pkt_desc->dst_addr = (uint32_t) dst;
    pkt_desc->buf_size = length;
#endif

    sdp_clear_error_status(base);

    base->MODCTRL = 0;
#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->CMDPTR = 0;
#else
    base->CMDPTR = (uint32_t) pkt_desc;
#endif
    base->PKTCNT = 1;

    status = sdp_wait_done(base);

    return status;
}

hpm_stat_t sdp_memset(SDP_Type *base, sdp_dma_ctx_t *sdp_ctx, void *dst, uint8_t pattern, uint32_t length)
{
    hpm_stat_t status;

    uint32_t
        pattern_32 = (pattern) | ((uint32_t) pattern << 8) | ((uint32_t) pattern << 16) | ((uint32_t) pattern << 24);

    base->SDPCR = SDP_SDPCR_CONFEN_MASK;
#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->SDPCR |= HPM_BITSMASK(1, 8);
    base->PKTCTL = SDP_PKT_CTRL_DERSEMA_MASK;
    base->PKTSRC = (uint32_t) pattern_32;
    base->PKTDST = (uint32_t) dst;
    base->PKTBUF = length;
#else
    sdp_pkt_struct_t *pkt_desc = &sdp_ctx->sdp_pkt;
    pkt_desc->next_cmd = NULL;
    pkt_desc->pkt_ctrl.PKT_CTRL = SDP_PKT_CTRL_DERSEMA_MASK;
    pkt_desc->src_addr = pattern_32;
    pkt_desc->dst_addr = (uint32_t) dst;
    pkt_desc->buf_size = length;
#endif

    sdp_clear_error_status(base);
    base->MODCTRL = 0;
#if defined(SDP_REGISTER_DESCRIPTOR_COUNT) && SDP_REGISTER_DESCRIPTOR_COUNT
    base->CMDPTR = 0;
#else
    base->CMDPTR = (uint32_t) pkt_desc;
#endif
    base->PKTCNT = 1;

    status = sdp_wait_done(base);

    return status;
}
