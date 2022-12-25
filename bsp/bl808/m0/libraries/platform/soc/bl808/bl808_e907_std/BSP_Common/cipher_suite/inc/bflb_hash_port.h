#ifndef _BFLB_HASH_PORT_H
#define _BFLB_HASH_PORT_H

#ifndef BFLB_CRYPT_HARDWARE
#include "mbedtls/sha1.h"
#include "mbedtls/md.h"
#include "mbedtls/sha256.h"
#include "mbedtls/sha512.h"
#else
#include "bflb_bsp_driver_glue.h"
#endif

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef union tag_bflb_hash_ctx_t
{
#ifndef BFLB_CRYPT_HARDWARE
    mbedtls_sha1_context ctx_sha1;
    mbedtls_sha256_context ctx_sha256;
    mbedtls_sha512_context ctx_sha512;
#else
    uint32_t sha_buf[64/4];					//for sha finish compute, must located at OCRAM
#endif
}bflb_hash_ctx_t;


#endif
