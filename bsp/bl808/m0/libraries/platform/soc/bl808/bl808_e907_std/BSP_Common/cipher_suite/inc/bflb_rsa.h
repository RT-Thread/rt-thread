#ifndef _BFLB_RSA_H
#define _BFLB_RSA_H

#include "bflb_rsa_port.h"
#include "bflb_platform.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define bflb_rsa_printf     bflb_platform_printf
#define bflb_rsa_printe     bflb_platform_printf
#define bflb_rsa_printd     bflb_platform_printf
#define bflb_rsa_printw     bflb_platform_printf


#define BFLB_RSA_OK             0
#define BFLB_RSA_ERROR          -1

enum BFLB_RSA_PARA
{
    BFLB_RSA_PARA_N,
    BFLB_RSA_PARA_E,
    BFLB_RSA_PARA_D,
    BFLB_RSA_PARA_P,
    BFLB_RSA_PARA_Q,
    BFLB_RSA_PARA_DP,
    BFLB_RSA_PARA_DQ,
    BFLB_RSA_PARA_QP,
};
   
typedef struct tag_bflb_rsa_handle_t
{
    bflb_rsa_ctx_t rsa_ctx;
}bflb_rsa_handle_t;

int32_t bflb_rsa_init(bflb_rsa_handle_t *rsa_handle,int padding,int hashtype );
int32_t bflb_rsa_set_parameter(bflb_rsa_handle_t *rsa_handle,int type,uint8_t *value,
                                uint32_t len );
int32_t bflb_rsa_check_private(bflb_rsa_handle_t *rsa_handle);
int32_t bflb_rsa_sign( bflb_rsa_handle_t *rsa_handle,const uint8_t *hash,
                            uint8_t hashlen,uint8_t hashtype,uint8_t *sig,uint32_t *slen);
int32_t bflb_rsa_verify( bflb_rsa_handle_t *rsa_handle,const uint8_t *hash,
                            uint8_t hashlen,uint8_t hashtype,const uint8_t *sig,uint32_t slen);
                            
int32_t bflb_rsa_deinit( bflb_rsa_handle_t *rsa_handle);

#endif
