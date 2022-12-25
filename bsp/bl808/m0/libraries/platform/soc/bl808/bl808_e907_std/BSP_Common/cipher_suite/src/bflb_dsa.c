#include "bflb_dsa.h"
#include "bflb_hash.h"
#include "stdint.h"
#include "bflb_platform.h"

//#define DSA_DBG                                   1
//#define DSA_DBG_DETAIL                            1

#if (defined(DSA_DBG)||defined(DSA_DBG_DETAIL))
uint32_t pka_tmp[64]={0};
#endif

/*
n=p*q;
F(n)=(p-1)*(q-1)
e*d%F(n)=1[e is public key and d is private key]
dP=d%(p-1)
dQ=d%(q-1)
m1=c^(dP)%p
m2=c^(dQ)%q
h=qInv*(m1-m2)%p
m=m2+h*q
m=c^d
*/
static SEC_ENG_PKA_REG_SIZE_Type bflb_dsa_get_reg_size(uint32_t size)
{
    switch(size){
    case 64:
        return SEC_ENG_PKA_REG_SIZE_8;
    case 128:
        return SEC_ENG_PKA_REG_SIZE_16;
    case 256:
        return SEC_ENG_PKA_REG_SIZE_32;
    case 512:
        return SEC_ENG_PKA_REG_SIZE_64;
    case 768:
        return SEC_ENG_PKA_REG_SIZE_96;
    case 1024:
        return SEC_ENG_PKA_REG_SIZE_128;
    case 1536:
        return SEC_ENG_PKA_REG_SIZE_192;
    case 2048:
        return SEC_ENG_PKA_REG_SIZE_256;
    case 3072:
        return SEC_ENG_PKA_REG_SIZE_384;
    case 4096:
        return SEC_ENG_PKA_REG_SIZE_512;
    default:
       return SEC_ENG_PKA_REG_SIZE_32;
    }
    return SEC_ENG_PKA_REG_SIZE_32;
}

/* c code:
number = 1
base = a
while b:
    if b & 1:
        number = number * base % c
    b >>= 1
    base = base * base % c
return number
*/
int32_t bflb_dsa_mexp_binary(uint32_t size,const uint32_t *a,const uint32_t *b,const uint32_t *c,uint32_t *r)
{
    uint32_t i,j,k;
    uint32_t tmp;
    uint32_t isOne=0;
    uint8_t *p=(uint8_t *)b;
    SEC_ENG_PKA_REG_SIZE_Type nregType=bflb_dsa_get_reg_size(size);
    SEC_ENG_PKA_REG_SIZE_Type lregType=bflb_dsa_get_reg_size(size*2);
    uint32_t dataSize=(size>>3)>>2;
#if 1
    uint8_t oneBuf[128] ALIGN4 ={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
            0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01};
#endif
    /* 0:c
     * 4:a
     * 5:number
     * 6&7:temp
     */

    /* base = a */
    Sec_Eng_PKA_Write_Data(nregType,4,(uint32_t *)a,dataSize,0);

    /* number = 1 */
    Sec_Eng_PKA_Write_Data(nregType,5,(uint32_t *)oneBuf,sizeof(oneBuf)/4,0);
    //Sec_Eng_PKA_Write_Immediate(nregType,5,0x01,1);
#ifdef DSA_DBG
    Sec_Eng_PKA_Read_Data(nregType,5,(uint32_t *)pka_tmp,dataSize);
    MSG("number:\r\n");
    bflb_platform_dump(pka_tmp,dataSize*4);
#endif

    Sec_Eng_PKA_Write_Data(nregType,0,(uint32_t *)c,dataSize,0);

    Sec_Eng_PKA_CREG(nregType,6,dataSize,1);
    Sec_Eng_PKA_CREG(nregType,7,dataSize,1);
#ifdef DSA_DBG
    Sec_Eng_PKA_Read_Data(nregType,4,(uint32_t *)pka_tmp,dataSize);
    MSG("base:\r\n");
    bflb_platform_dump(pka_tmp,dataSize*4);
#endif
    /* Remove zeros bytes*/
    k=0;
    while(p[k]==0&&k<(size>>3)){
       k++;
    }
    i=(size>>3)-1;
    for(;i>=k;i--){
       tmp=p[i];
       j=0;
       for(j=0;j<8;j++){
            isOne=tmp&(1<<j);
            if(isOne){
                /* number = number * base % c */
                Sec_Eng_PKA_LMUL(lregType,3,nregType,5,nregType,4,0);
                Sec_Eng_PKA_MREM(nregType,5,lregType,3,nregType,0,1);
#ifdef DSA_DBG
                Sec_Eng_PKA_Read_Data(nregType,5,(uint32_t *)pka_tmp,dataSize);
                MSG("number:\r\n");
                bflb_platform_dump(pka_tmp,dataSize/*dataSize*4*/);
#endif
            }
            /* base = base * base % c */
            Sec_Eng_PKA_LSQR(lregType,3,nregType,4,0);
            Sec_Eng_PKA_MREM(nregType,4,lregType,3,nregType,0,1);
#ifdef DSA_DBG
            Sec_Eng_PKA_Read_Data(nregType,4,(uint32_t *)pka_tmp,dataSize);
            MSG("base:\r\n");
            bflb_platform_dump(pka_tmp,dataSize/*dataSize*4*/);
#endif
       }
    }
    Sec_Eng_PKA_Read_Data(nregType,5,(uint32_t *)r,dataSize);
#ifdef DSA_DBG
    MSG("r:\r\n");
    bflb_platform_dump(r,dataSize*4);
#endif
    return 0;
}

/*r=a^b%c*/
int32_t bflb_dsa_mexp_mont(uint32_t size,uint32_t *a,uint32_t *b,uint32_t *c,uint32_t *invR_c,uint32_t *primeN_c,uint32_t *r)
{
    SEC_ENG_PKA_REG_SIZE_Type nregType=bflb_dsa_get_reg_size(size);
    SEC_ENG_PKA_REG_SIZE_Type lregType=bflb_dsa_get_reg_size(size*2);
    uint32_t dataSize=(size>>3)>>2;

    /* 0:c
     * 1:NPrime_c
     * 2:invR_c
     * 4:a(mont domain)
     * 5:b
     * 6:a^b%c(mont domain)
     * 7:a^b%c(gf domain)
     * 10&11:2^size for GF2Mont*/
    Sec_Eng_PKA_Write_Data(nregType,0,(uint32_t *)c,dataSize,0);
    Sec_Eng_PKA_Write_Data(nregType,1,(uint32_t *)primeN_c,dataSize,1);
    Sec_Eng_PKA_Write_Data(nregType,2,(uint32_t *)invR_c,dataSize,1);

    /* change a into mont domain*/
    Sec_Eng_PKA_Write_Data(nregType,4,(uint32_t *)a,dataSize,0);
    Sec_Eng_PKA_CREG(nregType,10,dataSize,1);
    Sec_Eng_PKA_CREG(nregType,11,dataSize,1);
    Sec_Eng_PKA_GF2Mont(nregType,4,nregType,4,size,lregType,5,nregType,0);
#ifdef DSA_DBG
    Sec_Eng_PKA_Read_Data(nregType,4,(uint32_t *)pka_tmp,dataSize);
    MSG("GF2Mont Result of a:\r\n");
    bflb_platform_dump(pka_tmp,dataSize/*dataSize*4*/);
#endif

    Sec_Eng_PKA_Write_Data(nregType,5,(uint32_t *)b,dataSize,0);
    /* a^b%c*/
    Sec_Eng_PKA_MEXP(nregType,6,nregType,4,nregType,5,nregType,0,1);

    /* change result into gf domain*/
    Sec_Eng_PKA_CREG(nregType,10,dataSize,1);
    Sec_Eng_PKA_CREG(nregType,11,dataSize,1);
    /*index 2 is invertR*/
    Sec_Eng_PKA_Mont2GF(nregType,7, nregType,6, nregType, 2,lregType,5,nregType,0);
    Sec_Eng_PKA_Read_Data(nregType,7,(uint32_t *)r,dataSize);
#ifdef DSA_DBG
    MSG("r:\r\n");
    bflb_platform_dump(r,dataSize/*dataSize*4*/);
#endif
    return 0;
}

/**
 * dP=d%(p-1)
 * dQ=d%(q-1)
 * qInv=qp^(1-1):qInv*q%p=1
 * invR_p*r%p=1(r is 1024/2048/256)
 * invR_q*r%q=1(r is 1024/2048/256)
 */
int32_t bflb_dsa_decrypt_crt(uint32_t size,uint32_t *c,bflb_dsa_crt_cfg* crtCfg,uint32_t *d,uint32_t *r)
{
    /*
     * m1 = pow(c, dP, p)
     * m2 = pow(c, dQ, q)
     * h = (qInv * (m1 - m2)) % p
     * m = m2 + h * q
     * */
    SEC_ENG_PKA_REG_SIZE_Type nregType=bflb_dsa_get_reg_size(size);
    SEC_ENG_PKA_REG_SIZE_Type lregType=bflb_dsa_get_reg_size(size*2);
    uint32_t dataSize=(size>>3)>>2;
#if 0
    uint8_t  m1[64]={0x11,0xdd,0x19,0x7e,0x69,0x1a,0x40,0x0a,0x28,0xfc,0x3b,0x31,0x47,0xa2,0x6c,0x14,
                     0x4e,0xf6,0xb0,0xe6,0xcd,0x89,0x0b,0x4f,0x02,0xe4,0x86,0xe2,0xe5,0xbe,0xe1,0xaf,
                     0x91,0xd1,0x7b,0x59,0x8d,0xdc,0xb3,0x57,0x18,0xcb,0x80,0x05,0x1c,0xb5,0xa4,0x07,
                     0xde,0x31,0x94,0xa4,0x2f,0x45,0xc7,0x95,0x75,0x0f,0x91,0xf0,0x37,0x91,0x85,0xa5};
    uint8_t  m2[64]={0x63,0x89,0xa3,0xbb,0x64,0x63,0x87,0x4f,0x38,0xbd,0x9e,0x0e,0x93,0x29,0x58,0xee,
                     0xf8,0xe2,0x20,0x2d,0xe5,0x38,0x0a,0x7f,0x18,0x38,0x2f,0xa3,0xf5,0x48,0xf8,0xfd,
                     0xe5,0x78,0x4a,0x10,0x62,0x01,0x09,0x29,0xe3,0xe3,0x9f,0xad,0x9b,0xbe,0x20,0xd2,
                     0x68,0x90,0x57,0x97,0xfc,0x78,0xd5,0xdb,0x07,0x5b,0xfe,0x21,0x0a,0x2d,0x7f,0xc1};
#else
    uint32_t  m1[32];
    uint32_t  m2[32];
#endif
    /*
     * 4:m1
     * 5:m2
     * 6:qInv
     * 7:p
     * 8:q
     * 9:h
     * 10&11:qInv*(m1-m2)
     */
    bflb_dsa_mexp_mont(size,c,crtCfg->dP,crtCfg->p,crtCfg->invR_p,crtCfg->primeN_p,m1);
    bflb_dsa_mexp_mont(size,c,crtCfg->dQ,crtCfg->q,crtCfg->invR_q,crtCfg->primeN_q,m2);

    Sec_Eng_PKA_Write_Data(nregType,4,(uint32_t *)m1,dataSize,0);
    Sec_Eng_PKA_Write_Data(nregType,5,(uint32_t *)m2,dataSize,0);
    Sec_Eng_PKA_Write_Data(nregType,6,(uint32_t *)crtCfg->qInv,dataSize,0);
    Sec_Eng_PKA_Write_Data(nregType,7,(uint32_t *)crtCfg->p,dataSize,0);
    Sec_Eng_PKA_Write_Data(nregType,8,(uint32_t *)crtCfg->q,dataSize,0);

    /*(m1 - m2)%p*/
   Sec_Eng_PKA_MSUB(nregType,4,nregType,4,nregType,5,nregType,7,1);
#ifdef DSA_DBG
    Sec_Eng_PKA_Read_Data(nregType,4,(uint32_t *)pka_tmp,dataSize);
    MSG("m1 - m2:\r\n");
    bflb_platform_dump(pka_tmp,dataSize/*dataSize*4*/);
#endif
    /* (qInv * (m1 - m2)) % p*/
    Sec_Eng_PKA_CREG(nregType,10,dataSize,1);
    Sec_Eng_PKA_CREG(nregType,11,dataSize,1);
    Sec_Eng_PKA_LMUL(lregType,5,nregType,6,nregType,4,1);
#ifdef DSA_DBG
    Sec_Eng_PKA_Read_Data(lregType,5,(uint32_t *)pka_tmp,dataSize*2);
    MSG("qInv * (m1 - m2):\r\n");
    bflb_platform_dump(pka_tmp,dataSize/*dataSize*4*2*/);
#endif
    Sec_Eng_PKA_MREM(nregType,9,lregType,5,nregType,7,1);
#ifdef DSA_DBG
    Sec_Eng_PKA_Read_Data(nregType,9,(uint32_t *)pka_tmp,dataSize);
    MSG("h:\r\n");
    bflb_platform_dump(pka_tmp,dataSize*4);
#endif

    /* h*q */
    Sec_Eng_PKA_CREG(nregType,10,dataSize,1);
    Sec_Eng_PKA_CREG(nregType,11,dataSize,1);
    Sec_Eng_PKA_LMUL(lregType,5,nregType,9,nregType,8,1);
#ifdef DSA_DBG
    Sec_Eng_PKA_Read_Data(lregType,5,(uint32_t *)pka_tmp,dataSize*2);
    MSG("h*q:\r\n");
    bflb_platform_dump(pka_tmp,dataSize/*dataSize*4*2*/);
#endif
    /* m2 + h*q*/
    Sec_Eng_PKA_LADD(lregType,5,lregType,5,nregType,5,1);

    Sec_Eng_PKA_Read_Data(lregType,5,(uint32_t *)r,dataSize*2);
#ifdef DSA_DBG
    MSG("r:\r\n");
    bflb_platform_dump(r,dataSize*4*2);
#endif
    return 0;
}

int32_t bflb_dsa_init(BFLB_DSA_Handle_t * handle,uint32_t size)
{
    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();

    memset(handle,0,sizeof(BFLB_DSA_Handle_t));
    handle->size=size;
    handle->crtSize=(size>>1);

    return BFLB_DSA_OK;
}

int32_t bflb_dsa_sign(BFLB_DSA_Handle_t * handle,const uint32_t *hash,uint32_t hashLenInWord,uint32_t *s)
{
    uint32_t dsa_tmp[64]={0};

    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();

    memcpy(dsa_tmp+((handle->crtSize>>3)>>2)-hashLenInWord,hash,hashLenInWord*4);


    if(0==bflb_dsa_decrypt_crt(handle->crtSize,dsa_tmp,&handle->crtCfg,handle->d,s)){
        return BFLB_DSA_OK;
    }else{
        return BFLB_DSA_ERROR;
    }
}

/**
 */
int32_t bflb_dsa_verify(BFLB_DSA_Handle_t * handle,const uint32_t *hash,uint32_t hashLenInWord,const uint32_t *s)
{
    uint32_t dsa_tmp[64];
    uint8_t i=0;
    uint8_t resultOffset=0;

    Sec_Eng_PKA_Reset();
    Sec_Eng_PKA_BigEndian_Enable();

    if(0==bflb_dsa_mexp_binary(handle->size,s,handle->e,handle->n,dsa_tmp)){
        resultOffset=(handle->size>>5)-hashLenInWord;
        for(i=0;i<hashLenInWord;i++){
            if(dsa_tmp[resultOffset+i]!=hash[i]){
                return BFLB_DSA_ERROR;
            }
        }
        return BFLB_DSA_OK;
    }else{
        return BFLB_DSA_ERROR;
    }
}
