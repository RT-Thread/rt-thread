#ifndef SUNXI_HAL_TWI_H
#define SUNXI_HAL_TWI_H

#include "hal_sem.h"
#include "hal_clk.h"
#include "sunxi_hal_common.h"
#include "hal_gpio.h"
#include "sunxi_hal_regulator.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CE_ALIGN_SIZE       (0x4)
#define CE_ROUND_UP(x,y)    ((((x) + ((y) - 1)) / (y)) * (y))

#define AES_KEYSIZE_128         128
#define AES_KEYSIZE_192         192
#define AES_KEYSIZE_256         256

#define AES_BLOCK_SIZE      (16)

/*define the ctx for aes requtest*/
typedef struct {
    uint8_t *src_buffer;
    uint32_t src_length;
    uint8_t *dst_buffer;
    uint32_t dst_length;
    uint8_t *iv;
    uint8_t *iv_next;
    uint8_t *key;
    uint32_t key_length;
    uint8_t padding[AES_BLOCK_SIZE];
    uint32_t padding_len;
    uint32_t dir;
    uint32_t mode;
    uint32_t bitwidth;
} crypto_aes_req_ctx_t;

/*define the ctx for hash requtest*/
#define SHA_MAX_DIGEST_SIZE     (64)
#define MD5_DIGEST_SIZE         (16)
#define SHA1_DIGEST_SIZE        (20)
#define SHA224_DIGEST_SIZE      (28)
#define SHA256_DIGEST_SIZE      (32)
#define SHA384_DIGEST_SIZE      (48)
#define SHA512_DIGEST_SIZE      (64)

#define MD5_BLOCK_SIZE          (64)
#define SHA1_BLOCK_SIZE         (64)
#define SHA224_BLOCK_SIZE       (64)
#define SHA256_BLOCK_SIZE       (64)
#define SHA384_BLOCK_SIZE       (128)
#define SHA512_BLOCK_SIZE       (128)

typedef struct {
    uint8_t *src_buffer;
    uint32_t src_length;
    uint8_t *dst_buffer;
    uint32_t dst_length;
    uint8_t md[SHA_MAX_DIGEST_SIZE];
    uint32_t md_size;
    uint8_t padding[SHA512_BLOCK_SIZE * 2];
    uint32_t padding_len;
    uint32_t type;
    uint32_t dir;
    uint32_t padding_mode;
} crypto_hash_req_ctx_t;

typedef struct {
    uint8_t *rng_buf;
    uint32_t rng_len;
    uint32_t mode;
    uint8_t *key;
    uint32_t key_len;
} crypto_rng_req_ctx_t;

/*define the ctx for rsa requtest*/
typedef struct {
    uint8_t *key_n;
    uint32_t n_len;
    uint8_t *key_e;
    uint32_t e_len;
    uint8_t *key_d;
    uint32_t d_len;
    uint8_t *src_buffer;
    uint32_t src_length;
    uint8_t *dst_buffer;
    uint32_t dst_length;
    uint32_t dir;
    uint32_t type;
    uint32_t bitwidth;
} crypto_rsa_req_ctx_t;

int do_aes_crypto(crypto_aes_req_ctx_t *req_ctx);
int sunxi_ce_init(void);
int sunxi_ce_uninit(void);
int do_hash_crypto(crypto_hash_req_ctx_t *req_ctx);
int do_rsa_crypto(crypto_rsa_req_ctx_t *req_ctx);
int do_rsa_crypto_new(crypto_rsa_req_ctx_t *req_ctx);
int do_rng_gen(crypto_rng_req_ctx_t *req_ctx);

#ifdef __cplusplus
}
#endif

#endif
