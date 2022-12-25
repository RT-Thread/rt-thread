#include "bflb_hash.h"

#ifndef BFLB_CRYPT_HARDWARE
#include "mbedtls/sha1.h"
#include "mbedtls/md.h"
#include "mbedtls/sha256.h"
#include "mbedtls/sha512.h"
uint8_t bflb_hash_get_type(uint8_t type)
{
    switch(type)
    {
        case BFLB_HASH_TYPE_SHA1:
            return MBEDTLS_MD_SHA1;
        case BFLB_HASH_TYPE_SHA224:
            return MBEDTLS_MD_SHA224;
        case BFLB_HASH_TYPE_SHA256:
            return MBEDTLS_MD_SHA256;
        case BFLB_HASH_TYPE_SHA384:
            return MBEDTLS_MD_SHA384;
        case BFLB_HASH_TYPE_SHA512:
            return MBEDTLS_MD_SHA512;
    }
    return MBEDTLS_MD_NONE;
}
#endif
static SEC_Eng_SHA256_Ctx shaCtx;
int32_t bflb_hash_init(bflb_hash_handle_t *hash_handle,uint8_t type)
{
    int32_t ret = BFLB_HASH_OK;


    switch(type)
    {
        case BFLB_HASH_TYPE_SHA1 :
        	ret=BFLB_HASH_ERROR;
        	bflb_hash_printe("unsupported type\r\n");
            break;
        case BFLB_HASH_TYPE_SHA224:
            Sec_Eng_SHA256_Init(&shaCtx,SEC_ENG_SHA_ID0,SEC_ENG_SHA224,(uint32_t *)hash_handle->hash_ctx.sha_buf,
                                                                (uint32_t *)hash_handle->sha_padding);
            break;
        case BFLB_HASH_TYPE_SHA256 :
            Sec_Eng_SHA256_Init(&shaCtx,SEC_ENG_SHA_ID0,SEC_ENG_SHA256,(uint32_t *)hash_handle->hash_ctx.sha_buf,
                                                                (uint32_t *)hash_handle->sha_padding);
            break;
        case BFLB_HASH_TYPE_SHA384:
        case BFLB_HASH_TYPE_SHA512:
        	ret=BFLB_HASH_ERROR;
        	bflb_hash_printe("unsupported type\r\n");
            break;
        default:
            bflb_hash_printe("unsupported type\r\n");
            ret=BFLB_HASH_ERROR;
            break;
            
    }
    if(ret==BFLB_HASH_OK){
        hash_handle->type=type;
    }
    return ret;
}

int32_t bflb_hash_start(bflb_hash_handle_t *hash_handle)
{
    int32_t ret = BFLB_HASH_OK;


  
    switch(hash_handle->type)
    {
        case BFLB_HASH_TYPE_SHA1:
            break;
        case BFLB_HASH_TYPE_SHA224:
        	 Sec_Eng_SHA_Start(SEC_ENG_SHA_ID0);
            break;
        case BFLB_HASH_TYPE_SHA256:
        	 Sec_Eng_SHA_Start(SEC_ENG_SHA_ID0);
            break;
        case BFLB_HASH_TYPE_SHA384:
            break;
        case BFLB_HASH_TYPE_SHA512:
            break;
        default:
            bflb_hash_printe("unsupported type\r\n");
            return BFLB_HASH_ERROR;
            
    }
    if(ret!=0){
    	bflb_hash_printe("hash start fail\r\n");
        ret=BFLB_HASH_ERROR;
    }
    return ret;
}

int32_t bflb_hash_update(bflb_hash_handle_t *hash_handle,const uint8_t *in,uint32_t len)
{
    int32_t ret = BFLB_HASH_OK;

    switch(hash_handle->type)
    {
        case BFLB_HASH_TYPE_SHA1:
            break;
	    case BFLB_HASH_TYPE_SHA224:
	    	Sec_Eng_SHA256_Update(&shaCtx,SEC_ENG_SHA_ID0,in, len);
	    	break;
        case BFLB_HASH_TYPE_SHA256:
        	Sec_Eng_SHA256_Update(&shaCtx,SEC_ENG_SHA_ID0,in, len);
            break;
        case BFLB_HASH_TYPE_SHA384:
            break;
        case BFLB_HASH_TYPE_SHA512:
            break;
        default:
            bflb_hash_printe("unsupported type\r\n");
            return BFLB_HASH_ERROR;
            
    }
    if(ret!=0){
    	bflb_hash_printe("hash update fail\r\n");
        ret=BFLB_HASH_ERROR;
    }

    return ret;
}

int32_t bflb_hash_finish(bflb_hash_handle_t *hash_handle,uint8_t *out)
{
    int32_t ret = BFLB_HASH_OK;

    switch(hash_handle->type)
    {
        case BFLB_HASH_TYPE_SHA1:
            break;
        case BFLB_HASH_TYPE_SHA224:
        	Sec_Eng_SHA256_Finish(&shaCtx,SEC_ENG_SHA_ID0,out);
        	break;
        case BFLB_HASH_TYPE_SHA256:
        	Sec_Eng_SHA256_Finish(&shaCtx,SEC_ENG_SHA_ID0,out);
            break;
        case BFLB_HASH_TYPE_SHA384:
            break;
        case BFLB_HASH_TYPE_SHA512:
            break;
        default:
            bflb_hash_printe("unsupported type\r\n");
            return BFLB_HASH_ERROR;
            
    }
    if(ret!=0){
    	bflb_hash_printe("hash finish fail\r\n");
        ret=BFLB_HASH_ERROR;
    }

    return ret;
}

int32_t bflb_hash_deinit(bflb_hash_handle_t *hash_handle)
{
    switch(hash_handle->type)
    {
        case BFLB_HASH_TYPE_SHA1:
            break;
        case BFLB_HASH_TYPE_SHA224:
        	break;
        case BFLB_HASH_TYPE_SHA256:
            break;
        case BFLB_HASH_TYPE_SHA384:
            break;
        case BFLB_HASH_TYPE_SHA512:
            break;
        default:
            bflb_hash_printe("unsupported type\r\n");
            return BFLB_HASH_ERROR;
            
    }
    memset(hash_handle,0,sizeof(bflb_hash_handle_t));

    return BFLB_HASH_OK;
}
