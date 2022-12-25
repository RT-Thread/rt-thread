#ifndef _BFLB_HASH_H
#define _BFLB_HASH_H

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "bflb_hash_port.h"
#include "bflb_platform.h"


#define bflb_hash_printf     bflb_platform_printf
#define bflb_hash_printe     bflb_platform_printf
#define bflb_hash_printd     bflb_platform_printf
#define bflb_hash_printw     bflb_platform_printf

#define BFLB_HASH_OK             0
#define BFLB_HASH_ERROR          -1

#define BFLB_HASH_TYPE_SHA1           0
#define BFLB_HASH_TYPE_SHA224       1
#define BFLB_HASH_TYPE_SHA256       2
#define BFLB_HASH_TYPE_SHA384       3
#define BFLB_HASH_TYPE_SHA512       4
   
typedef struct tag_bflb_hash_handle_t
{
    bflb_hash_ctx_t hash_ctx;
#ifdef BFLB_CRYPT_HARDWARE
    uint32_t sha_padding[64/4];			    //for sha finish compute, must located at OCRAM
#endif
    uint8_t type;
}bflb_hash_handle_t;

int32_t bflb_hash_init(bflb_hash_handle_t *hash_handle,uint8_t type);

uint8_t bflb_hash_get_type(uint8_t type);

int32_t bflb_hash_start(bflb_hash_handle_t *hash_handle);

int32_t bflb_hash_update(bflb_hash_handle_t *hash_handle,const uint8_t *in,uint32_t len);

int32_t bflb_hash_finish(bflb_hash_handle_t *hash_handle,uint8_t *out);

int32_t bflb_hash_deinit(bflb_hash_handle_t *hash_handle);

#endif
