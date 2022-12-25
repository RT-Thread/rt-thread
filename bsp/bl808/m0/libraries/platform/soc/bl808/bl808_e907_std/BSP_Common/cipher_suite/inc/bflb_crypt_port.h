#ifndef _BFLB_AES_PORT_H
#define _BFLB_AES_PORT_H

#ifndef BFLB_CRYPT_HARDWARE
#include "mbedtls/aes.h"
#include "mbedtls/ccm.h"
#include "mbedtls/gcm.h"
#include "chacha.h"
#include "chacha20_poly1305.h"
#else
#include "bflb_bsp_driver_glue.h"
#endif

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define BFLB_CRYPT_KEY_SIZE_MAX   		32
#define BFLB_CRYPT_NONCE_SIZE_MAX       16
#define BFLB_CRYPT_BLK_SIZE       		16

#ifndef BFLB_CRYPT_HARDWARE
typedef union tag_bflb_crypt_ctx_t
{
    mbedtls_aes_context ctx_aes;
    mbedtls_ccm_context ctx_ccm;
    mbedtls_gcm_context ctx_gcm;
    ChaCha              ctx_chacha;
    ChaChaPoly1305      ctx_chachapoly1305;
}bflb_crypt_ctx_t;
#endif

typedef struct tag_bflb_crypt_cfg_t
{
#ifndef BFLB_CRYPT_HARDWARE
	uint8_t key[BFLB_CRYPT_KEY_SIZE_MAX];
	//for general cipher,iv is 16 bytes, but for GCM vector test, there is a 60 bytes test
	uint8_t iv_nonce[BFLB_CRYPT_NONCE_SIZE_MAX*4];
	uint8_t stream_block[BFLB_CRYPT_BLK_SIZE];
	uint8_t key_len;
	uint8_t nonce_len;
	uint8_t dir;
#else
#endif
    uint8_t type;
}bflb_crypt_cfg_t;



#ifndef BFLB_CRYPT_HARDWARE
#define BFLB_CRYPT_DIR_ENCRYPT    MBEDTLS_AES_ENCRYPT
#define BFLB_CRYPT_DIR_DECRYPT    MBEDTLS_AES_DECRYPT
#else
#define BFLB_CRYPT_DIR_ENCRYPT    1
#define BFLB_CRYPT_DIR_DECRYPT    2
#endif

#endif
