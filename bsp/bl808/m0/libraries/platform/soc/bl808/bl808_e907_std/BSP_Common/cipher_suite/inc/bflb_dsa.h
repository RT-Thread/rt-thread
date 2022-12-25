#ifndef _BFLB_DSA_H
#define _BFLB_DSA_H

#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "bflb_ecdsa_port.h"
#include "bflb_platform.h"

#define BFLB_DSA_OK                     0
#define BFLB_DSA_ERROR                  -1

typedef struct tag_bflb_dsa_crt_cfg
{
    uint32_t *dP;
    uint32_t *dQ;
    uint32_t *qInv;
    uint32_t *p;
    uint32_t *invR_p;
    uint32_t *primeN_p;
    uint32_t *q;
    uint32_t *invR_q;
    uint32_t *primeN_q;
}bflb_dsa_crt_cfg;

typedef struct{
    uint32_t size;
    uint32_t crtSize;
    uint32_t *n;
    uint32_t *e;
    uint32_t *d;
    bflb_dsa_crt_cfg crtCfg;
}BFLB_DSA_Handle_t;

int32_t bflb_dsa_init(BFLB_DSA_Handle_t * handle,uint32_t size);
int32_t bflb_dsa_mexp_binary(uint32_t size,const uint32_t *a,const uint32_t *b,const uint32_t *c,uint32_t *r);
int32_t bflb_dsa_mexp_mont(uint32_t size,uint32_t *a,uint32_t *b,uint32_t *c,uint32_t *invR_c,uint32_t *primeN_c,uint32_t *r);
int32_t bflb_dsa_decrypt_crt(uint32_t size,uint32_t *c,bflb_dsa_crt_cfg *crtCfg,uint32_t *d,uint32_t *r);
int32_t bflb_dsa_sign(BFLB_DSA_Handle_t * handle,const uint32_t *hash,uint32_t hashLenInWord,uint32_t *s);
int32_t bflb_dsa_verify(BFLB_DSA_Handle_t * handle,const uint32_t *hash,uint32_t hashLenInWord,const uint32_t *s);

#endif
