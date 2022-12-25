#ifndef _BFLB_ECDSA_PORT_H
#define _BFLB_ECDSA_PORT_H

#ifndef BFLB_PKA_HARDWARE
#include "mbedtls/ecdsa.h"
#include "mbedtls/md.h"
#include "mbedtls/asn1.h"
#else
#include "bflb_bsp_driver_glue.h"
#endif
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef union tag_bflb_ecdsa_ctx_t
{
#ifndef BFLB_PKA_HARDWARE
	mbedtls_ecdsa_context ctx_ecdsa;
#endif
}bflb_ecdsa_ctx_t;


#endif
