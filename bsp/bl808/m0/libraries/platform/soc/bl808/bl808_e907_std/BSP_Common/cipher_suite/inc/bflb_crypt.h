#ifndef _BFLB_CRYPT_H
#define _BFLB_CRYPT_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "bflb_crypt_port.h"
#include "bflb_platform.h"


#define bflb_crypt_printf     		bflb_platform_printf
#define bflb_crypt_printe		 	bflb_platform_printf
#define bflb_crypt_printd    	    bflb_platform_printf
#define bflb_crypt_printw     		bflb_platform_printf


#define BFLB_CRYPT_OK             0
#define BFLB_CRYPT_ERROR          -1

#define BFLB_CRYPT_TYPE_AES_ECB                 0
#define BFLB_CRYPT_TYPE_AES_CBC                 1
#define BFLB_CRYPT_TYPE_AES_CTR                 2
#define BFLB_CRYPT_TYPE_CHACHA                  3
#define BFLB_CRYPT_TYPE_AES_CCM                 4
#define BFLB_CRYPT_TYPE_AES_GCM                 5
#define BFLB_CRYPT_TYPE_CHACHAPOLY1305          6

typedef struct tag_bflb_crypt_handle_t
{
#ifndef BFLB_CRYPT_HARDWARE
    bflb_crypt_ctx_t crypt_ctx;
#endif
    bflb_crypt_cfg_t crypt_cfg;
}bflb_crypt_handle_t;

int32_t bflb_crypt_init(bflb_crypt_handle_t *crypt_handle,uint8_t type);

int32_t bflb_crypt_setkey(bflb_crypt_handle_t *aes_handle,const uint8_t *key,
		uint8_t keytype,uint8_t key_len,const uint8_t *nonce,uint8_t nonce_len,uint8_t dir);

int32_t bflb_crypt_setadd(bflb_crypt_handle_t *aes_handle,const uint8_t *add,
		uint8_t len,uint8_t dir);

int32_t bflb_crypt_update(bflb_crypt_handle_t *aes_handle,const uint8_t *in,
		uint32_t len,uint8_t *out);

int32_t bflb_crypt_encrypt(bflb_crypt_handle_t *aes_handle,const uint8_t *in,
		uint32_t len,size_t offset,uint8_t *out);

int32_t bflb_crypt_encrypt_tag(bflb_crypt_handle_t *aes_handle,const uint8_t *in,
		uint32_t in_len,const uint8_t *add,uint32_t add_len,size_t offset,
		uint8_t *out,uint8_t *tag,uint8_t tag_len);

int32_t bflb_crypt_auth_decrypt(bflb_crypt_handle_t *aes_handle,const uint8_t *in,
		uint32_t in_len,const uint8_t *add,uint32_t add_len,size_t offset,
		uint8_t *out,const uint8_t *tag,uint8_t tag_len);

int32_t bflb_crypt_decrypt(bflb_crypt_handle_t *aes_handle,const uint8_t *in,
		uint32_t len,size_t offset,uint8_t *out);

int32_t bflb_crypt_finish(bflb_crypt_handle_t *aes_handle,uint8_t *tag,uint32_t len);

int32_t bflb_crypt_deinit(bflb_crypt_handle_t *aes_handle);
#endif
