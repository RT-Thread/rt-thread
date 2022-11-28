/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <hal_cmd.h>
#include <hal_mem.h>
#include <sunxi_hal_ce.h>

#include "test_ce.h"

#define AES_MODE_ECB        (0)
#define AES_MODE_CBC        (1)
#define AES_MODE_CTR        (2)
#define AES_MODE_CTS        (3)
#define AES_MODE_OFB        (4)
#define AES_MODE_CFB        (5)

#define AES_DIR_ENCRYPT     (0)
#define AES_DIR_DECRYPT     (1)

#define HASH_METHOD_MD5     (16)
#define HASH_METHOD_SHA1    (17)
#define HASH_METHOD_SHA224  (18)
#define HASH_METHOD_SHA256  (19)
#define HASH_METHOD_SHA384  (20)
#define HASH_METHOD_SHA512  (21)

void ce_dump(char *str,unsigned char *data, int len, int align)
{
    int i = 0;
    if(str)
        printf("\n%s: ",str);
    for(i = 0; i<len; i++)
    {
        if((i%align) == 0)
        {
            printf("\n");
            printf("0x08%x: ", data + i * align);
        }
        printf("%02x ",*(data++));
    }
    printf("\n");
}

int aes_test(void)
{
    int ret = -1;
    int i = 0;
    int j = 0;
    int m = 0;
    uint8_t *enc_buffer = 0;
    uint32_t enc_len = 0;
    uint32_t blk_num = 0;
    uint8_t iv_next[AES_BLOCK_SIZE] = {0};
    uint8_t *(*aes_enc[])[5] = {aes_ecb, aes_cbc, aes_ctr, aes_cbc, aes_ofb, aes_cfb8};
    crypto_aes_req_ctx_t *aes_ctx = NULL;

    aes_ctx = (crypto_aes_req_ctx_t *)hal_malloc_align(sizeof(crypto_aes_req_ctx_t), CE_ALIGN_SIZE);
    if (aes_ctx == NULL) {
        printf (" malloc data buffer fail\n");
        return -1;
    }
    memset(aes_ctx, 0x0, sizeof(crypto_aes_req_ctx_t));

    aes_ctx->dst_buffer = (u8 *)hal_malloc_align(512, CE_ALIGN_SIZE);
    if (aes_ctx->dst_buffer == NULL) {
        printf (" malloc dest buffer fail\n");
        ret = -1;
        goto out;
    }

    for (m = AES_MODE_ECB; m < AES_MODE_CFB + 1; m++) {
        for (i = 0; i < sizeof(aes_key_len)/sizeof(aes_key_len[0]); i++) {
            for (j = 0; j < sizeof(aes_src)/sizeof(aes_src[0]); j++) {
                /* aes encrypt */
                aes_ctx->src_buffer = aes_src[j];
                aes_ctx->src_length = aes_src_len[j];
                aes_ctx->key = aes_key[i];
                aes_ctx->key_length = aes_key_len[i];
                if (m == AES_MODE_ECB)
                    aes_ctx->iv = NULL;
                else
                    aes_ctx->iv = aes_iv;
                if (m == AES_MODE_CTR) {
                    memset(iv_next, 0, AES_BLOCK_SIZE);
                    aes_ctx->iv_next = iv_next;
                } else
                    aes_ctx->iv_next = NULL;
                if (m == AES_MODE_CFB)
                    aes_ctx->bitwidth = 8;
                else
                    aes_ctx->bitwidth = 0;
                aes_ctx->mode = m;
                aes_ctx->dir = AES_DIR_ENCRYPT;
                aes_ctx->dst_length = CE_ROUND_UP(aes_ctx->src_length, AES_BLOCK_SIZE);

                printf("###############AES, mode: %d, ksize %d, src len %d, begin###############\n", m, aes_key_len[i], aes_src_len[j]);

                ret = do_aes_crypto(aes_ctx);
                if (ret < 0) {
                    printf ("aes encrypt fail %d\n", ret);
                    goto out;
                }

                // for ecb/cbc/cts, enc data len should be 16 bytes aligned
                if (m == AES_MODE_ECB || m == AES_MODE_CBC || m == AES_MODE_CTS)
                    enc_len = aes_ctx->dst_length;
                else
                    enc_len = aes_src_len[j];

                // openssl enc do not support cts, so create enc data manually.
                if (m == AES_MODE_CTS){
                    enc_buffer = (uint8_t *)hal_malloc(enc_len);
                    if (enc_buffer == NULL) {
                        printf ("malloc ctr buffer fail\n");
                        ret = -1;
                        goto out;
                    }

                    blk_num = enc_len / AES_BLOCK_SIZE;
                    if (blk_num > 1) {
                        if (blk_num > 2)
                            memcpy(enc_buffer, aes_enc[m - AES_MODE_ECB][i][j], (blk_num - 2) * AES_BLOCK_SIZE);
                        memcpy(enc_buffer + (blk_num - 2) * AES_BLOCK_SIZE,
                                aes_enc[m - AES_MODE_ECB][i][j] + (blk_num - 1) * AES_BLOCK_SIZE,
                                AES_BLOCK_SIZE);
                        memcpy(enc_buffer + (blk_num - 1) * AES_BLOCK_SIZE,
                                aes_enc[m - AES_MODE_ECB][i][j] + (blk_num - 2) * AES_BLOCK_SIZE,
                                AES_BLOCK_SIZE);
                    } else {
                        memcpy(enc_buffer, aes_enc[m - AES_MODE_ECB][i][j], enc_len);
                    }
                } else
                    enc_buffer = aes_enc[m - AES_MODE_ECB][i][j];

                if (memcmp(aes_ctx->dst_buffer, enc_buffer, enc_len) != 0) {
                    ce_dump("want data: ", enc_buffer, enc_len, 16);
                    ce_dump("calc data: ", aes_ctx->dst_buffer, enc_len, 16);
                    printf("###############AES ENC, mode: %d, ksize %d, src len %d, fail###############\n", m, aes_key_len[i], aes_src_len[j]);
                    ret = -1;
                    goto out;
                }

                /* aes decrypt */
                memset(aes_ctx->dst_buffer, 0x0, aes_ctx->dst_length);
                aes_ctx->dir = AES_DIR_DECRYPT;
                aes_ctx->src_buffer = enc_buffer;
                aes_ctx->src_length = enc_len;

                ret = do_aes_crypto(aes_ctx);
                if (ret < 0) {
                    printf("aes decrypt fail %d\n", ret);
                    goto out;
                }

                if (memcmp(aes_ctx->dst_buffer, aes_src[j], aes_src_len[j]) != 0) {
                    ce_dump("want data: ", aes_src[j], aes_src_len[j], 16);
                    ce_dump("calc data: ", aes_ctx->dst_buffer, aes_src_len[j], 16);
                    printf("###############AES DEC, mode: %d, ksize %d, src len %d, fail###############\n", m, aes_key_len[i], aes_src_len[j]);
                    ret = -1;
                    goto out;
                }

                if (m == AES_MODE_CTS) {
                    if (enc_buffer)
                        hal_free(enc_buffer);
                }

                printf("###############AES, mode: %d, ksize %d, src len %d, pass###############\n\n\n", m, aes_key_len[i], aes_src_len[j]);
            }
        }
    }

out:
    if (aes_ctx->dst_buffer != NULL) {
        hal_free_align(aes_ctx->dst_buffer);
    }
    if (m == AES_MODE_CTS) {
        if (enc_buffer)
            hal_free(enc_buffer);
    }

    hal_free_align(aes_ctx);

    return ret;
}

int hash_test(void)
{
    int i = 0;
    int j = 0;
    uint8_t *dst_data = NULL;
    //uint32_t data_size = 512; SHA_MAX_DIGEST_SIZE
    uint32_t data_size = SHA_MAX_DIGEST_SIZE;
    uint32_t hash_length = 0;
    int ret = -1;
    uint8_t *(*hash_digest[]) = {hash_md5, hash_sha1, hash_sha224, hash_sha256, hash_sha384, hash_sha512};
    crypto_hash_req_ctx_t *hash_ctx = NULL;

    hash_ctx = (crypto_hash_req_ctx_t *)hal_malloc_align(sizeof(crypto_hash_req_ctx_t), CE_ALIGN_SIZE);
    if (hash_ctx == NULL) {
        printf (" malloc hash_ctx fail\n");
        ret = -1;
        goto out;
    }

    /*malloc dst buf*/
    dst_data = (u8 *)hal_malloc_align(data_size, CE_ALIGN_SIZE);
    if (dst_data == NULL) {
        printf (" malloc dst buffer fail\n");
        ret = -1;
        goto out;
    }

    for (i = HASH_METHOD_MD5; i < HASH_METHOD_SHA512 + 1; i++) {
        for (j = 0; j < sizeof(hash_src_len)/sizeof(hash_src_len[0]); j++) {
            hash_ctx->src_buffer = hash_src[j];
            hash_ctx->src_length = hash_src_len[j];
            memset(dst_data, 0x0, data_size);
            hash_ctx->dst_buffer = dst_data;
            hash_ctx->type = i;
            hash_ctx->md_size = 0;
            switch (i) {
                case HASH_METHOD_MD5:
                    hash_ctx->dst_length = MD5_DIGEST_SIZE;
                    hash_length = MD5_DIGEST_SIZE;
                    break;
                case HASH_METHOD_SHA1:
                    hash_ctx->dst_length = SHA1_DIGEST_SIZE;
                    hash_length = SHA1_DIGEST_SIZE;
                    break;
                case HASH_METHOD_SHA224:
                    hash_ctx->dst_length = SHA256_DIGEST_SIZE;
                    hash_length = SHA224_DIGEST_SIZE;
                    break;
                case HASH_METHOD_SHA256:
                    hash_ctx->dst_length = SHA256_DIGEST_SIZE;
                    hash_length = SHA256_DIGEST_SIZE;
                    break;
                case HASH_METHOD_SHA384:
                    hash_ctx->dst_length = SHA512_DIGEST_SIZE;
                    hash_length = SHA384_DIGEST_SIZE;
                    break;
                case HASH_METHOD_SHA512:
                    hash_ctx->dst_length = SHA512_DIGEST_SIZE;
                    hash_length = SHA512_DIGEST_SIZE;
                    break;
                default:
                    break;
            }

            printf("############hash type: %d, src len: %d, begin#############\n", i, hash_src_len[j]);

            ret = do_hash_crypto(hash_ctx);
            if (ret < 0) {
                printf ("do_hash_crypto fail\n");
                goto out;
            }

            if (memcmp(hash_ctx->dst_buffer, hash_digest[i - HASH_METHOD_MD5][j], hash_length) == 0) {
                printf("############hash type: %d, src len: %d, pass#############\n\n\n", i, hash_src_len[j]);
            } else {
                ce_dump("want digest: ", hash_digest[i - HASH_METHOD_MD5][j], hash_length, 16);
                ce_dump("calc digest: ", hash_ctx->dst_buffer, hash_length, 16);
                printf("############hash type: %d, src len: %d, fail#############\n\n\n", i, hash_src_len[j]);
                ret = -1;
                goto out;
            }
        }
    }

out:
    if (hash_ctx != NULL) {
        hal_free_align(hash_ctx);
    }

    if (dst_data != NULL) {
        hal_free_align(dst_data);
    }

    return ret;
}


int rng_test(void)
{
    int ret = 0;
    int i = 0;
    uint8_t *rng_buf = NULL;
    uint32_t rng_size[] = {16, 31, 32, 8100};
    uint8_t key[24] = {
        0xa1, 0xb7, 0x78, 0xf7, 0xbf, 0x2c, 0xfa, 0xad, 0x6a, 0x46, 0x79, 0xc2, 0xd2, 0x9c, 0x45, 0x1f,
        0x3f, 0xcb, 0xef, 0xa5, 0x4e, 0x0e, 0xc3, 0x51
    };
    uint32_t key_len = 24;
    crypto_rng_req_ctx_t *rng_ctx = NULL;

    rng_ctx = (crypto_rng_req_ctx_t *)hal_malloc(sizeof(crypto_rng_req_ctx_t));
    if (rng_ctx == NULL) {
        printf (" malloc rng ctx fail\n");
        ret = -1;
        goto out;
    }

    /*malloc trng buf*/
    rng_buf = (u8 *)hal_malloc(8192);
    if (rng_buf == NULL) {
        printf ("malloc rng buffer fail\n");
        ret = -1;
        goto out;
    }

    /*TRNG test*/
    for (i = 0; i < sizeof(rng_size)/sizeof(uint32_t); i++) {
        printf("############TRNG, len: %d, begin#############\n", rng_size[i]);
        memset(rng_buf, 0, 8192);
        rng_ctx->rng_buf = rng_buf;
        rng_ctx->rng_len = rng_size[i];
        rng_ctx->mode = 0x30; /*CE_METHOD_TRNG*/
        rng_ctx->key = NULL;
        rng_ctx->key_len = 0;
        ret = do_rng_gen(rng_ctx);
        if (ret < 0) {
            printf("############TRNG, len: %d, fail#############\n\n\n", rng_size[i]);
            goto out;
        }
#if 0
        if (rng_size[i] < 100)
            ce_dump("trng:", rng_buf, rng_size[i], 16);
#endif
        printf("############TRNG, len: %d, pass#############\n\n\n", rng_size[i]);
    }

    /*PRNG test*/
    for (i = 0; i < sizeof(rng_size)/sizeof(uint32_t); i++) {
        printf("############PRNG, len: %d, begin#############\n", rng_size[i]);
        memset(rng_buf, 0, 8192);
        rng_ctx->rng_buf = rng_buf;
        rng_ctx->rng_len = rng_size[i];
        rng_ctx->mode = 0x31; /*CE_METHOD_PRNG*/
        rng_ctx->key = key;
        rng_ctx->key_len = key_len;
        ret = do_rng_gen(rng_ctx);
        if (ret < 0) {
            printf("############PRNG, len: %d, fail#############\n\n\n", rng_size[i]);
            goto out;
        }
#if 0
        if (rng_size[i] < 100)
            ce_dump("prng:", rng_buf, rng_size[i], 16);
#endif
        printf("############PRNG, len: %d, pass#############\n\n\n", rng_size[i]);
    }

out:
    if (rng_ctx)
        hal_free(rng_ctx);

    if (rng_buf)
        hal_free(rng_buf);

    return ret;
}

int rsa_test(void)
{
    int ret = 0;
    int i = 0;
    uint8_t dst_buffer[256] = {0};
    crypto_rsa_req_ctx_t *rsa_ctx = NULL;

    rsa_ctx = (crypto_rsa_req_ctx_t *)hal_malloc_align(sizeof(crypto_rsa_req_ctx_t), CE_ALIGN_SIZE);
    if (rsa_ctx == NULL) {
        printf (" malloc rsa ctx fail\n");
        return -1;
    }

    /*rsa enc and dec*/
    for (i = 0; i < sizeof(rsa_bitwidth)/sizeof(rsa_bitwidth[0]); i ++) {
        /* enc with public key*/
        printf("############RSA ENC/DEC, len: %d, begin#############\n", rsa_bitwidth[i]);
        memset(dst_buffer, 0, 256);
        memset(rsa_ctx, 0, sizeof(crypto_rsa_req_ctx_t));

        rsa_ctx->key_n = rsa_keyn[i];
        rsa_ctx->n_len = rsa_bitwidth[i] / 8;
        rsa_ctx->key_e = rsa_keye[i];
        rsa_ctx->e_len = rsa_bitwidth[i] / 8;
        rsa_ctx->key_d = 0;
        rsa_ctx->d_len = 0;

        rsa_ctx->src_buffer = rsa_src[i];
        rsa_ctx->src_length = rsa_bitwidth[i] / 8;
        rsa_ctx->dst_buffer = dst_buffer;
        rsa_ctx->dst_length = rsa_bitwidth[i] / 8;

        rsa_ctx->dir = 0;
        rsa_ctx->type = 0x20; /*CE_METHOD_RSA*/
        rsa_ctx->bitwidth = rsa_bitwidth[i];

        ret = do_rsa_crypto(rsa_ctx);
        if (ret < 0) {
            printf ("do rsa crypto failed: %d\n", ret);
            goto out;
        }

        ret = memcmp(rsa_ctx->dst_buffer, rsa_enc[i], rsa_bitwidth[i] / 8);
        if (ret) {
            printf("rsa encrypt failed\n");
            ce_dump("want data: ", rsa_enc[i], rsa_bitwidth[i] / 8, 16);
            ce_dump("calc data: ", rsa_ctx->dst_buffer, rsa_ctx->dst_length, 16);
            printf("############RSA ENC, len: %d, fail#############\n\n\n", rsa_bitwidth[i]);
            goto out;
        }

        /* dec with private key */
        memset(dst_buffer, 0, 256);
        memset(rsa_ctx, 0, sizeof(crypto_rsa_req_ctx_t));

        rsa_ctx->key_n = rsa_keyn[i];
        rsa_ctx->n_len = rsa_bitwidth[i] / 8;
        rsa_ctx->key_e = 0;
        rsa_ctx->e_len = 0;
        rsa_ctx->key_d = rsa_keyd[i];
        rsa_ctx->d_len = rsa_bitwidth[i] / 8;

        rsa_ctx->src_buffer = rsa_enc[i];
        rsa_ctx->src_length = rsa_bitwidth[i] / 8;
        rsa_ctx->dst_buffer = dst_buffer;
        rsa_ctx->dst_length = rsa_bitwidth[i] / 8;

        rsa_ctx->dir = 0;
        rsa_ctx->type = 0x20; /*CE_METHOD_RSA*/
        rsa_ctx->bitwidth = rsa_bitwidth[i];

        ret = do_rsa_crypto(rsa_ctx);
        if (ret < 0) {
            printf ("do rsa crypto failed: %d\n", ret);
            goto out;
        }

        ret = memcmp(rsa_ctx->dst_buffer, rsa_src[i], rsa_bitwidth[i] / 8);
        if (ret) {
            printf("rsa decrypt failed\n");
            ce_dump("want data: ", rsa_src[i], rsa_bitwidth[i] / 8, 16);
            ce_dump("calc data: ", rsa_ctx->dst_buffer, rsa_ctx->dst_length, 16);
            printf("############RSA DEC, len: %d, fail#############\n\n\n", rsa_bitwidth[i]);
            goto out;
        }

        printf("############RSA ENC/DEC, len: %d, pass#############\n\n\n", rsa_bitwidth[i]);
    }

    /* rsa sign/verify sha256 value */
    for (i = 0; i < sizeof(rsa_bitwidth)/sizeof(rsa_bitwidth[0]); i ++) {
        /* sign with private key */
        printf("############RSA SIGN/VERIFY SHA256, len: %d, begin#############\n", rsa_bitwidth[i]);
        memset(dst_buffer, 0, 256);
        memset(rsa_ctx, 0, sizeof(crypto_rsa_req_ctx_t));

        rsa_ctx->key_n = rsa_keyn[i];
        rsa_ctx->n_len = rsa_bitwidth[i] / 8;
        rsa_ctx->key_e = 0;
        rsa_ctx->e_len = 0;
        rsa_ctx->key_d = rsa_keyd[i];
        rsa_ctx->d_len = rsa_bitwidth[i] / 8;

        rsa_ctx->src_buffer = rsa_sha256_raw[i];
        rsa_ctx->src_length = rsa_bitwidth[i] / 8;
        rsa_ctx->dst_buffer = dst_buffer;
        rsa_ctx->dst_length = rsa_bitwidth[i] / 8;

        rsa_ctx->dir = 0;
        rsa_ctx->type = 0x20; /*CE_METHOD_RSA*/
        rsa_ctx->bitwidth = rsa_bitwidth[i];

        ret = do_rsa_crypto(rsa_ctx);
        if (ret < 0) {
            printf ("do rsa crypto failed: %d\n", ret);
            goto out;
        }

        ret = memcmp(rsa_ctx->dst_buffer, rsa_sha256_sign[i], rsa_bitwidth[i] / 8);
        if (ret) {
            printf("rsa encrypt failed\n");
            ce_dump("want data: ", rsa_sha256_sign[i], rsa_bitwidth[i] / 8, 16);
            ce_dump("calc data: ", rsa_ctx->dst_buffer, rsa_ctx->dst_length, 16);
            printf("############RSA SIGN SHA256, len: %d, fail#############\n\n\n", rsa_bitwidth[i]);
            //goto out;
        }

        /* verify with public key */
        memset(dst_buffer, 0, 256);
        memset(rsa_ctx, 0, sizeof(crypto_rsa_req_ctx_t));

        rsa_ctx->key_n = rsa_keyn[i];
        rsa_ctx->n_len = rsa_bitwidth[i] / 8;
        rsa_ctx->key_e = rsa_keye[i];
        rsa_ctx->e_len = rsa_bitwidth[i] / 8;
        rsa_ctx->key_d = 0;
        rsa_ctx->d_len = 0;

        rsa_ctx->src_buffer = rsa_sha256_sign[i];
        rsa_ctx->src_length = rsa_bitwidth[i] / 8;
        rsa_ctx->dst_buffer = dst_buffer;
        rsa_ctx->dst_length = 256 / 8;

        rsa_ctx->dir = 0;
        rsa_ctx->type = 0x20; /*CE_METHOD_RSA*/
        rsa_ctx->bitwidth = rsa_bitwidth[i];

        ret = do_rsa_crypto(rsa_ctx);
        if (ret < 0) {
            printf ("do rsa crypto failed: %d\n", ret);
            goto out;
        }

        ret = memcmp(rsa_ctx->dst_buffer, rsa_sha256[i], 256 / 8);
        if (ret) {
            printf("rsa decrypt failed\n");
            ce_dump("want data: ", rsa_sha256[i], 256 / 8, 16);
            ce_dump("calc data: ", rsa_ctx->dst_buffer, rsa_ctx->dst_length, 16);
            printf("############RSA VERIFY SHA256, len: %d, fail#############\n\n\n", rsa_bitwidth[i]);
            goto out;
        }

        printf("############RSA SIGN/VERIFY SHA256, len: %d, pass#############\n\n\n", rsa_bitwidth[i]);
    }

    /* rsa sign/verify */
    for (i = 0; i < sizeof(rsa_bitwidth)/sizeof(rsa_bitwidth[0]); i ++) {
        /* sign with private key */
        printf("############RSA SIGN/VERIFY, len: %d, begin#############\n", rsa_bitwidth[i]);
        memset(dst_buffer, 0, 256);
        memset(rsa_ctx, 0, sizeof(crypto_rsa_req_ctx_t));

        rsa_ctx->key_n = rsa_keyn[i];
        rsa_ctx->n_len = rsa_bitwidth[i] / 8;
        rsa_ctx->key_e = 0;
        rsa_ctx->e_len = 0;
        rsa_ctx->key_d = rsa_keyd[i];
        rsa_ctx->d_len = rsa_bitwidth[i] / 8;

        rsa_ctx->src_buffer = rsa_sign_raw[i];
        rsa_ctx->src_length = rsa_bitwidth[i] / 8;
        rsa_ctx->dst_buffer = dst_buffer;
        rsa_ctx->dst_length = rsa_bitwidth[i] / 8;

        rsa_ctx->dir = 0;
        rsa_ctx->type = 0x20; /*CE_METHOD_RSA*/
        rsa_ctx->bitwidth = rsa_bitwidth[i];

        ret = do_rsa_crypto(rsa_ctx);
        if (ret < 0) {
            printf ("do rsa crypto failed: %d\n", ret);
            goto out;
        }

        ret = memcmp(rsa_ctx->dst_buffer, rsa_signature[i], rsa_bitwidth[i] / 8);
        if (ret) {
            printf("rsa encrypt failed\n");
            ce_dump("want data: ", rsa_signature[i], rsa_bitwidth[i] / 8, 16);
            ce_dump("calc data: ", rsa_ctx->dst_buffer, rsa_ctx->dst_length, 16);
            printf("############RSA SIGN, len: %d, fail#############\n\n\n", rsa_bitwidth[i]);
            //goto out;
        }

        /* verify with public key */
        memset(dst_buffer, 0, 256);
        memset(rsa_ctx, 0, sizeof(crypto_rsa_req_ctx_t));

        rsa_ctx->key_n = rsa_keyn[i];
        rsa_ctx->n_len = rsa_bitwidth[i] / 8;
        rsa_ctx->key_e = rsa_keye[i];
        rsa_ctx->e_len = rsa_bitwidth[i] / 8;
        rsa_ctx->key_d = 0;
        rsa_ctx->d_len = 0;

        rsa_ctx->src_buffer = rsa_signature[i];
        rsa_ctx->src_length = rsa_bitwidth[i] / 8;
        rsa_ctx->dst_buffer = dst_buffer;
        rsa_ctx->dst_length = 256 / 8;

        rsa_ctx->dir = 0;
        rsa_ctx->type = 0x20; /*CE_METHOD_RSA*/
        rsa_ctx->bitwidth = rsa_bitwidth[i];

        ret = do_rsa_crypto(rsa_ctx);
        if (ret < 0) {
            printf ("do rsa crypto failed: %d\n", ret);
            goto out;
        }

        ret = memcmp(rsa_ctx->dst_buffer, rsa_sha256[i], 256 / 8);
        if (ret) {
            printf("rsa decrypt failed\n");
            ce_dump("want data: ", rsa_sha256[i], 256 / 8, 16);
            ce_dump("calc data: ", rsa_ctx->dst_buffer, rsa_ctx->dst_length, 16);
            printf("############RSA VERIFY, len: %d, fail#############\n\n\n", rsa_bitwidth[i]);
            goto out;
        }

        printf("############RSA SIGN/VERIFY, len: %d, pass#############\n\n\n", rsa_bitwidth[i]);
    }

out:
    if (rsa_ctx)
        hal_free_align(rsa_ctx);

    return ret;
}

int cmd_test_ce(int argc, const char *argv[])
{
    int ret = 0;

    if (argc != 2) {
        printf("Parameter number Error!\n");
        printf("Usage: hal_ce <aes|hash|rsa|rng>\n");
        return -1;
    }

    sunxi_ce_init();

    if (strcmp(argv[1], "aes") == 0)
        ret = aes_test();
    else if (strcmp(argv[1], "hash") == 0)
        ret = hash_test();
    else if (strcmp(argv[1], "rsa") == 0)
        ret = rsa_test();
    else if (strcmp(argv[1], "rng") == 0)
        ret = rng_test();
    else {
        printf("Parameter Error!\n");
        printf("Usage: hal_ce <aes|hash|rsa|rng>\n");
        ret = -1;
    }

    sunxi_ce_uninit();

    return ret;
}

FINSH_FUNCTION_EXPORT_CMD(cmd_test_ce, hal_ce, tina rtos ce test demo)
