/**
  ******************************************************************************
  * @file    bl808_sec_eng.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "string.h"
#include "bl808_sec_eng.h"
#include "bl808_tzc_sec.h"
#include "bl808_l1c.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SEC_ENG
 *  @{
 */

/** @defgroup  SEC_ENG_Private_Macros
 *  @{
 */
#define PUT_UINT32_BE(n, b, i)               \
    {                                        \
        (b)[(i)] = (uint8_t)((n) >> 24);     \
        (b)[(i) + 1] = (uint8_t)((n) >> 16); \
        (b)[(i) + 2] = (uint8_t)((n) >> 8);  \
        (b)[(i) + 3] = (uint8_t)((n));       \
    }
#define PUT_UINT32(n, b, i)                  \
    {                                        \
        (b)[(i) + 3] = (uint8_t)((n) >> 24); \
        (b)[(i) + 2] = (uint8_t)((n) >> 16); \
        (b)[(i) + 1] = (uint8_t)((n) >> 8);  \
        (b)[(i) + 0] = (uint8_t)((n));       \
    }
#define PUT_UINT64_BE(n, b, i)               \
    {                                        \
        (b)[(i)] = (uint8_t)((n) >> 56);     \
        (b)[(i) + 1] = (uint8_t)((n) >> 48); \
        (b)[(i) + 2] = (uint8_t)((n) >> 40); \
        (b)[(i) + 3] = (uint8_t)((n) >> 32); \
        (b)[(i) + 4] = (uint8_t)((n) >> 24); \
        (b)[(i) + 5] = (uint8_t)((n) >> 16); \
        (b)[(i) + 6] = (uint8_t)((n) >> 8);  \
        (b)[(i) + 7] = (uint8_t)((n));       \
    }
#define SEC_ENG_SHA_BUSY_TIMEOUT_COUNT  (100 * 320 * 1000)
#define SEC_ENG_AES_BUSY_TIMEOUT_COUNT  (100 * 320 * 1000)
#define SEC_ENG_TRNG_BUSY_TIMEOUT_COUNT (100 * 320 * 1000)
#define SEC_ENG_PKA_INT_TIMEOUT_COUNT   (100 * 320 * 1000)
#define SEC_ENG_GMAC_BUSY_TIMEOUT_COUNT (100 * 320 * 1000)

/*@} end of group SEC_ENG_Private_Macros */

/** @defgroup  SEC_ENG_Private_Types
 *  @{
 */
struct pka0_pld_cfg {
    union {
        struct
        {
            uint32_t size        : 12; /*[11: 0],       r/w,        0x0 */
            uint32_t d_reg_index : 8;  /*[19:12],        r/w,        0x0 */
            uint32_t d_reg_type  : 4;  /*[23:20],        r/w,        0x0 */
            uint32_t op          : 7;  /*[30:24],        r/w,        0x0 */
            uint32_t last_op     : 1;  /*[31:31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } value;
};

struct pka0_pldi_cfg {
    union {
        struct
        {
            uint32_t rsvd        : 12; /*[11: 0],       r/w,        0x0 */
            uint32_t d_reg_index : 8;  /*[19:12],        r/w,        0x0 */
            uint32_t d_reg_type  : 4;  /*[23:20],        r/w,        0x0 */
            uint32_t op          : 7;  /*[30:24],        r/w,        0x0 */
            uint32_t last_op     : 1;  /*[31:31],        r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } value;
};

struct pka0_common_op_first_cfg {
    union {
        struct
        {
            uint32_t s0_reg_idx  : 8; /*[7: 0],       r/w,        0x0 */
            uint32_t s0_reg_type : 4; /*[11:8],       r/w,        0x0 */
            uint32_t d_reg_idx   : 8; /*[19:12],      r/w,        0x0 */
            uint32_t d_reg_type  : 4; /*[23:20],      r/w,        0x0 */
            uint32_t op          : 7; /*[30:24],      r/w,        0x0 */
            uint32_t last_op     : 1; /*[31:31],      r/w,        0x0 */
        } BF;
        uint32_t WORD;
    } value;
};

struct pka0_common_op_snd_cfg_S1_only {
    union {
        struct
        {
            uint32_t reserved_0_11  : 12; /*[11: 0],       rsvd,       0x0 */
            uint32_t s1_reg_idx     : 8;  /*[19:12],       r/w,        0x0 */
            uint32_t s1_reg_type    : 4;  /*[23:20],       r/w,        0x0 */
            uint32_t reserved_24_31 : 8;  /*[31:24],       rsvd,       0x0 */
        } BF;
        uint32_t WORD;
    } value;
};

struct pka0_common_op_snd_cfg_S2_only {
    union {
        struct
        {
            uint32_t s2_reg_idx     : 8;  /*[7 : 0],       r/w,        0x0 */
            uint32_t s2_reg_type    : 4;  /*[11: 8],       r/w,        0x0 */
            uint32_t reserved_12_31 : 20; /*[31:12],       rsvd,       0x0 */
        } BF;
        uint32_t WORD;
    } value;
};

struct pka0_common_op_snd_cfg_S1_S2 {
    union {
        struct
        {
            uint32_t s2_reg_idx     : 8; /*[7 : 0],       r/w,        0x0 */
            uint32_t s2_reg_type    : 4; /*[11: 8],       r/w,        0x0 */
            uint32_t s1_reg_idx     : 8; /*[19:12],       r/w,        0x0 */
            uint32_t s1_reg_type    : 4; /*[23:20],       r/w,        0x0 */
            uint32_t reserved_24_31 : 8; /*[31:24],       rsvd,       0x0 */
        } BF;
        uint32_t WORD;
    } value;
};

struct pka0_bit_shift_op_cfg {
    union {
        struct
        {
            uint32_t bit_shift      : 15; /*[14: 0],       r/w,        0x0 */
            uint32_t reserved_24_31 : 17; /*[31:15],       rsvd,        0x0 */
        } BF;
        uint32_t WORD;
    } value;
};

/*@} end of group SEC_ENG_Private_Types */

/** @defgroup  SEC_ENG_Private_Variables
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *secEngIntCbfArra[SEC_ENG_INT_ALL] = { NULL };
#endif

/*@} end of group SEC_ENG_Private_Variables */

/** @defgroup  SEC_ENG_Global_Variables
 *  @{
 */

/*@} end of group SEC_ENG_Global_Variables */

/** @defgroup  SEC_ENG_Private_Fun_Declaration
 *  @{
 */

/*@} end of group SEC_ENG_Private_Fun_Declaration */

/** @defgroup  SEC_ENG_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  SHA256 initialization function
 *
 * @param  shaCtx: SHA256 context pointer
 * @param  shaNo: SHA ID type
 * @param  shaType: SHA type
 * @param  shaTmpBuf[16]: SHA temp buffer for store data that is less than 64 bytes
 * @param  padding[16]: SHA padding buffer for store padding data
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_SHA256_Init(SEC_Eng_SHA256_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, SEC_ENG_SHA_Type shaType, uint32_t shaTmpBuf[16], uint32_t padding[16])
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));
    CHECK_PARAM(IS_SEC_ENG_SHA_TYPE(shaType));

    /* Deal SHA control register to set SHA mode */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);

    if (shaType < 8) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE_EXT, 0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE, shaType);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE_EXT, shaType - 7);
    }

    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

    /* Clear context */
    ARCH_MemSet(shaCtx, 0, sizeof(SEC_Eng_SHA256_Ctx));

    /* Init temp buffer and padding buffer */
    shaCtx->shaBuf = shaTmpBuf;
    shaCtx->shaPadding = padding;
    ARCH_MemSet(shaCtx->shaPadding, 0, 64);
    ARCH_MemSet(shaCtx->shaPadding, 0x80, 1);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  SHA512 initialization function
 *
 * @param  shaCtx: SHA512 context pointer
 * @param  shaNo: SHA ID type
 * @param  shaType: SHA type
 * @param  shaTmpBuf[16]: SHA temp buffer for store data that is less that 128 bytes
 * @param  padding[16]: SHA padding buffer for store padding data
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_SHA512_Init(SEC_Eng_SHA512_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, SEC_ENG_SHA_Type shaType, uint64_t shaTmpBuf[16], uint64_t padding[16])
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));
    CHECK_PARAM(IS_SEC_ENG_SHA_TYPE(shaType));

    /* Deal SHA control register to set SHA mode */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);

    if (shaType < 8) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE_EXT, 0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE, shaType);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE_EXT, shaType - 7);
    }

    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

    /* Clear context */
    ARCH_MemSet(shaCtx, 0, sizeof(SEC_Eng_SHA512_Ctx));

    /* Init temp buffer and padding buffer */
    shaCtx->shaBuf = shaTmpBuf;
    shaCtx->shaPadding = padding;
    ARCH_MemSet(shaCtx->shaPadding, 0, 128);
    ARCH_MemSet(shaCtx->shaPadding, 0x80, 1);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  MD5 initialization function
 *
 * @param  md5Ctx: MD5 context pointer
 * @param  shaNo: SHA ID type
 * @param  shaType: SHA type
 * @param  md5TmpBuf[16]: MD5 temp buffer for store data that is less that 64 bytes
 * @param  padding[16]: MD5 padding buffer for store padding data
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_MD5_Init(SEC_Eng_MD5_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, SEC_ENG_SHA_Type shaType, uint32_t md5TmpBuf[16], uint32_t padding[16])
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));
    CHECK_PARAM(IS_SEC_ENG_SHA_TYPE(shaType));

    /* Deal SHA control register to set SHA mode */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);

    if (shaType < 8) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE_EXT, 0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE, shaType);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE_EXT, shaType - 7);
    }

    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

    /* Clear context */
    ARCH_MemSet(md5Ctx, 0, sizeof(SEC_Eng_MD5_Ctx));

    /* Init temp buffer and padding buffer */
    md5Ctx->md5Buf = md5TmpBuf;
    md5Ctx->md5Padding = padding;
    ARCH_MemSet(md5Ctx->md5Padding, 0, 64);
    ARCH_MemSet(md5Ctx->md5Padding, 0x80, 1);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  SHA start function
 *
 * @param  shaNo: SHA ID type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_SHA_Start(SEC_ENG_SHA_ID_Type shaNo)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Set SHA enable */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);

    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_EN);
    /* Hash sel 0 for new start */
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL);

    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  SHA256 update input data function
 *
 * @param  shaCtx: SHA256 context pointer
 * @param  shaNo: SHA ID type
 * @param  input: SHA input data pointer, and the address should be word align
 * @param  len: SHA input data length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_SHA256_Update(SEC_Eng_SHA256_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, const uint8_t *input, uint32_t len)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t fill;
    uint32_t left;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    if (len == 0) {
        return SUCCESS;
    }

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* SHA need set se_sha_sel to 1 to keep the last SHA state */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL, shaCtx->shaFeed);

    left = shaCtx->total[0] & 0x3F;
    fill = 64 - left;

    shaCtx->total[0] += (uint32_t)len;
    shaCtx->total[0] &= 0xFFFFFFFF;

    if (shaCtx->total[0] < (uint32_t)len) {
        shaCtx->total[1]++;
    }

    if (left && len >= fill) {
        ARCH_MemCpy_Fast((void *)((uint8_t *)shaCtx->shaBuf + left), input, fill);
        /* Set data source address */
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_MSA, (uintptr_t)shaCtx->shaBuf);

        /* Set data length */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MSG_LEN, 1);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        /* Trigger */
        tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        shaCtx->shaFeed = 1;
        input += fill;
        len -= fill;
        left = 0;
    }

    fill = len / 64;
    len = len % 64;

    if (fill > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* SHA need set se_sha_sel to 1 to keep the last sha state */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL, shaCtx->shaFeed);

        /* Fill data */
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_MSA, (uintptr_t)input);

        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MSG_LEN, fill);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        input += (fill * 64);
        shaCtx->shaFeed = 1;
    }

    if (len > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* Copy left data into temp buffer */
        ARCH_MemCpy_Fast((void *)((uint8_t *)shaCtx->shaBuf + left), input, len);
    }

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SHA512 update input data function
 *
 * @param  shaCtx: SHA512 context pointer
 * @param  shaNo: SHA ID type
 * @param  input: SHA input data pointer, and the address should be word align
 * @param  len: SHA input data length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_SHA512_Update(SEC_Eng_SHA512_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, const uint8_t *input, uint64_t len)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t fill;
    uint32_t left;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    if (len == 0) {
        return SUCCESS;
    }

    if ((((uintptr_t)input) & 0x07) != 0) {
        return ERROR;
    }

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* SHA need set se_sha_sel to 1 to keep the last SHA state */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL, shaCtx->shaFeed);

    left = shaCtx->total[0] & 0x7F;
    fill = 128 - left;

    shaCtx->total[0] += (uint64_t)len;

    if (shaCtx->total[0] < (uint64_t)len) {
        shaCtx->total[1]++;
    }

    if (left && len >= fill) {
        ARCH_MemCpy_Fast((void *)((uint8_t *)shaCtx->shaBuf + left), input, fill);
        /* Set data source address */
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_MSA, (uintptr_t)shaCtx->shaBuf);

        /* Set data length */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MSG_LEN, 1);

        /* Trigger */
        tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        shaCtx->shaFeed = 1;
        input += fill;
        len -= fill;
        left = 0;
    }

    fill = len / 128;
    len = len % 128;

    if (fill > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* SHA need set se_sha_sel to 1 to keep the last sha state */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL, shaCtx->shaFeed);

        /* Fill data */
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_MSA, (uintptr_t)input);

        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MSG_LEN, fill);
        tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        input += (fill * 128);
        shaCtx->shaFeed = 1;
    }

    if (len > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* Copy left data into temp buffer */
        ARCH_MemCpy_Fast((void *)((uint8_t *)shaCtx->shaBuf + left), input, len);
    }

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  MD5 update input data function
 *
 * @param  md5Ctx: MD5 context pointer
 * @param  shaNo: SHA ID type
 * @param  input: SHA input data pointer, and the address should be word align
 * @param  len: SHA input data length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_MD5_Update(SEC_Eng_MD5_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, const uint8_t *input, uint32_t len)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t fill;
    uint32_t left;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    if (len == 0) {
        return SUCCESS;
    }

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* SHA need set se_sha_sel to 1 to keep the last SHA state */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL, md5Ctx->md5Feed);

    left = md5Ctx->total[0] & 0x3F;
    fill = 64 - left;

    md5Ctx->total[0] += (uint32_t)len;
    md5Ctx->total[0] &= 0xFFFFFFFF;

    if (md5Ctx->total[0] < (uint32_t)len) {
        md5Ctx->total[1]++;
    }

    if (left && len >= fill) {
        ARCH_MemCpy_Fast((void *)((uint8_t *)md5Ctx->md5Buf + left), input, fill);

        /* Set data source address */
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_MSA, (uintptr_t)md5Ctx->md5Buf);

        /* Set data length */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MSG_LEN, 1);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        /* Trigger */
        tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        md5Ctx->md5Feed = 1;
        input += fill;
        len -= fill;
        left = 0;
    }

    fill = len / 64;
    len = len % 64;

    if (fill > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* SHA need set se_sha_sel to 1 to keep the last sha state */
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL, md5Ctx->md5Feed);

        /* Fill data */
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_MSA, (uintptr_t)input);

        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MSG_LEN, fill);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

        input += (fill * 64);
        md5Ctx->md5Feed = 1;
    }

    if (len > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* Copy left data into temp buffer */
        ARCH_MemCpy_Fast((void *)((uint8_t *)md5Ctx->md5Buf + left), input, len);
    }

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SHA256 finish to get output function
 *
 * @param  shaCtx: SHA256 context pointer
 * @param  shaNo: SHA ID type
 * @param  hash: SHA output data of SHA result
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_SHA256_Finish(SEC_Eng_SHA256_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint8_t *hash)
{
    uint32_t last, padn;
    uint32_t high, low;
    uint8_t shaMode;
    uint8_t msgLen[8];
    uint8_t *p = (uint8_t *)hash;
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    high = (shaCtx->total[0] >> 29) | (shaCtx->total[1] << 3);
    low = (shaCtx->total[0] << 3);

    PUT_UINT32_BE(high, msgLen, 0);
    PUT_UINT32_BE(low, msgLen, 4);

    last = shaCtx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    Sec_Eng_SHA256_Update(shaCtx, shaNo, (uint8_t *)shaCtx->shaPadding, padn);

    /* Wait for  shaPadding idle */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    ARCH_MemCpy_Fast(shaCtx->shaPadding, msgLen, 8);
    Sec_Eng_SHA256_Update(shaCtx, shaNo, (uint8_t *)shaCtx->shaPadding, 8);

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    shaMode = (SEC_ENG_SHA_Type)BL_GET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE);
    /* Copy SHA value */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_0);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_1);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_2);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_3);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_4);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);

    if (shaMode == SEC_ENG_SHA224 || shaMode == SEC_ENG_SHA256) {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_5);
        *p++ = (tmpVal & 0xff);
        *p++ = ((tmpVal >> 8) & 0xff);
        *p++ = ((tmpVal >> 16) & 0xff);
        *p++ = ((tmpVal >> 24) & 0xff);
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_6);
        *p++ = (tmpVal & 0xff);
        *p++ = ((tmpVal >> 8) & 0xff);
        *p++ = ((tmpVal >> 16) & 0xff);
        *p++ = ((tmpVal >> 24) & 0xff);

        if (shaMode == SEC_ENG_SHA256) {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_7);
            *p++ = (tmpVal & 0xff);
            *p++ = ((tmpVal >> 8) & 0xff);
            *p++ = ((tmpVal >> 16) & 0xff);
            *p++ = ((tmpVal >> 24) & 0xff);
        }
    }

    /* Disable SHA engine*/
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_EN);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SHA512 finish to get output function
 *
 * @param  shaCtx: SHA512 context pointer
 * @param  shaNo: SHA ID type
 * @param  hash: SHA output data of SHA result
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_SHA512_Finish(SEC_Eng_SHA512_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint8_t *hash)
{
    uint64_t last, padn;
    uint64_t high, low;
    uint8_t shaMode;
    uint8_t msgLen[16];
    uint8_t *p = (uint8_t *)hash;
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    high = (shaCtx->total[0] >> 61) | (shaCtx->total[1] << 3);
    low = (shaCtx->total[0] << 3);

    PUT_UINT64_BE(high, msgLen, 0);
    PUT_UINT64_BE(low, msgLen, 8);

    last = shaCtx->total[0] & 0x7F;
    padn = (last < 112) ? (112 - last) : (240 - last);

    Sec_Eng_SHA512_Update(shaCtx, shaNo, (uint8_t *)shaCtx->shaPadding, padn);

    /* Wait for  shaPadding idle */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    ARCH_MemCpy_Fast(shaCtx->shaPadding, msgLen, 16);
    Sec_Eng_SHA512_Update(shaCtx, shaNo, (uint8_t *)shaCtx->shaPadding, 16);

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    shaMode = (SEC_ENG_SHA_Type)BL_GET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_SHA_0_MODE);
    /* Copy SHA value */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_H_0);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_0);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_H_1);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_1);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_H_2);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_2);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_H_3);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);

    if (shaMode == SEC_ENG_SHA512T256 || shaMode == SEC_ENG_SHA384 || shaMode == SEC_ENG_SHA512) {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_3);
        *p++ = (tmpVal & 0xff);
        *p++ = ((tmpVal >> 8) & 0xff);
        *p++ = ((tmpVal >> 16) & 0xff);
        *p++ = ((tmpVal >> 24) & 0xff);

        if (shaMode == SEC_ENG_SHA384 || shaMode == SEC_ENG_SHA512) {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_H_4);
            *p++ = (tmpVal & 0xff);
            *p++ = ((tmpVal >> 8) & 0xff);
            *p++ = ((tmpVal >> 16) & 0xff);
            *p++ = ((tmpVal >> 24) & 0xff);
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_4);
            *p++ = (tmpVal & 0xff);
            *p++ = ((tmpVal >> 8) & 0xff);
            *p++ = ((tmpVal >> 16) & 0xff);
            *p++ = ((tmpVal >> 24) & 0xff);
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_H_5);
            *p++ = (tmpVal & 0xff);
            *p++ = ((tmpVal >> 8) & 0xff);
            *p++ = ((tmpVal >> 16) & 0xff);
            *p++ = ((tmpVal >> 24) & 0xff);
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_5);
            *p++ = (tmpVal & 0xff);
            *p++ = ((tmpVal >> 8) & 0xff);
            *p++ = ((tmpVal >> 16) & 0xff);
            *p++ = ((tmpVal >> 24) & 0xff);

            if (shaMode == SEC_ENG_SHA512) {
                tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_H_6);
                *p++ = (tmpVal & 0xff);
                *p++ = ((tmpVal >> 8) & 0xff);
                *p++ = ((tmpVal >> 16) & 0xff);
                *p++ = ((tmpVal >> 24) & 0xff);
                tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_6);
                *p++ = (tmpVal & 0xff);
                *p++ = ((tmpVal >> 8) & 0xff);
                *p++ = ((tmpVal >> 16) & 0xff);
                *p++ = ((tmpVal >> 24) & 0xff);
                tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_H_7);
                *p++ = (tmpVal & 0xff);
                *p++ = ((tmpVal >> 8) & 0xff);
                *p++ = ((tmpVal >> 16) & 0xff);
                *p++ = ((tmpVal >> 24) & 0xff);
                tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_7);
                *p++ = (tmpVal & 0xff);
                *p++ = ((tmpVal >> 8) & 0xff);
                *p++ = ((tmpVal >> 16) & 0xff);
                *p++ = ((tmpVal >> 24) & 0xff);
            }
        }
    }

    /* Disable SHA engine*/
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_EN);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  MD5 finish to get output function
 *
 * @param  md5Ctx: MD5 context pointer
 * @param  shaNo: SHA ID type
 * @param  hash: MD5 output data of SHA result
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_MD5_Finish(SEC_Eng_MD5_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, uint8_t *hash)
{
    uint32_t last, padn;
    uint32_t high, low;
    uint8_t msgLen[8];
    uint8_t *p = (uint8_t *)hash;
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    high = (md5Ctx->total[0] >> 29) | (md5Ctx->total[1] << 3);
    low = (md5Ctx->total[0] << 3);

    PUT_UINT32(low, msgLen, 0);
    PUT_UINT32(high, msgLen, 4);

    last = md5Ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    Sec_Eng_MD5_Update(md5Ctx, shaNo, (uint8_t *)md5Ctx->md5Padding, padn);

    /* Wait for  shaPadding idle */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    ARCH_MemCpy_Fast(md5Ctx->md5Padding, msgLen, 8);
    Sec_Eng_MD5_Update(md5Ctx, shaNo, (uint8_t *)md5Ctx->md5Padding, 8);

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);

    /* Copy SHA value */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_0);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_1);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_2);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_HASH_L_3);
    *p++ = (tmpVal & 0xff);
    *p++ = ((tmpVal >> 8) & 0xff);
    *p++ = ((tmpVal >> 16) & 0xff);
    *p++ = ((tmpVal >> 24) & 0xff);

    /* Disable SHA engine*/
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_HASH_SEL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_EN);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SHA enable link mode and set link config address
 *
 * @param  shaNo: SHA ID type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_SHA_Enable_Link(SEC_ENG_SHA_ID_Type shaNo)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Enable sha and enable link mode */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_EN);
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_LINK_MODE);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  SHA disable link mode
 *
 * @param  shaNo: SHA ID type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_SHA_Disable_Link(SEC_ENG_SHA_ID_Type shaNo)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Disable sha and disable link mode */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_LINK_MODE);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_EN);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  SHA256 link mode initialization function
 *
 * @param  shaCtx: SHA256 link mode context pointer
 * @param  shaNo: SHA ID type
 * @param  linkAddr: SHA link configure address
 * @param  shaTmpBuf[16]: SHA temp buffer for store data that is less than 64 bytes
 * @param  padding[16]: SHA padding buffer for store padding data
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_SHA256_Link_Init(SEC_Eng_SHA256_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr, uint32_t shaTmpBuf[16], uint32_t padding[16])
{
    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Clear context */
    ARCH_MemSet(shaCtx, 0, sizeof(SEC_Eng_SHA256_Link_Ctx));

    /* Init temp buffer,padding buffer and link address */
    shaCtx->shaBuf = shaTmpBuf;
    shaCtx->shaPadding = padding;
    ARCH_MemSet(shaCtx->shaPadding, 0, 64);
    ARCH_MemSet(shaCtx->shaPadding, 0x80, 1);
    shaCtx->linkAddr = linkAddr;

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  SHA512 link mode initialization function
 *
 * @param  shaCtx: SHA512 link mode context pointer
 * @param  shaNo: SHA ID type
 * @param  linkAddr: SHA link configure address
 * @param  shaTmpBuf[16]: SHA temp buffer for store data that is less than 128 bytes
 * @param  padding[16]: SHA padding buffer for store padding data
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_SHA512_Link_Init(SEC_Eng_SHA512_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr, uint64_t shaTmpBuf[16], uint64_t padding[16])
{
    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Clear context */
    ARCH_MemSet(shaCtx, 0, sizeof(SEC_Eng_SHA512_Link_Ctx));

    /* Init temp buffer,padding buffer and link address */
    shaCtx->shaBuf = shaTmpBuf;
    shaCtx->shaPadding = padding;
    ARCH_MemSet(shaCtx->shaPadding, 0, 128);
    ARCH_MemSet(shaCtx->shaPadding, 0x80, 1);
    shaCtx->linkAddr = linkAddr;

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  MD5 link mode initialization function
 *
 * @param  shaCtx: SHA256 link mode context pointer
 * @param  shaNo: SHA ID type
 * @param  linkAddr: MD5 link configure address
 * @param  shaTmpBuf[16]: MD5 temp buffer for store data that is less than 64 bytes
 * @param  padding[16]: MD5 padding buffer for store padding data
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_MD5_Link_Init(SEC_Eng_MD5_Link_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr, uint32_t md5TmpBuf[16], uint32_t padding[16])
{
    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Clear context */
    ARCH_MemSet(md5Ctx, 0, sizeof(SEC_Eng_MD5_Link_Ctx));

    /* Init temp buffer,padding buffer and link address */
    md5Ctx->md5Buf = md5TmpBuf;
    md5Ctx->md5Padding = padding;
    ARCH_MemSet(md5Ctx->md5Padding, 0, 64);
    ARCH_MemSet(md5Ctx->md5Padding, 0x80, 1);
    md5Ctx->linkAddr = linkAddr;

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_SHA_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  SHA256 link mode update input data function
 *
 * @param  shaCtx: SHA256 link mode context pointer
 * @param  shaNo: SHA ID type
 * @param  input: SHA input data pointer, and the address should be word align
 * @param  len: SHA input data length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_SHA256_Link_Update(SEC_Eng_SHA256_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, const uint8_t *input, uint32_t len)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t fill;
    uint32_t left;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    if (len == 0) {
        return SUCCESS;
    }

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Set link address */
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_LINK, shaCtx->linkAddr);

    left = shaCtx->total[0] & 0x3F;
    fill = 64 - left;

    shaCtx->total[0] += (uint32_t)len;
    shaCtx->total[0] &= 0xFFFFFFFF;

    if (shaCtx->total[0] < (uint32_t)len) {
        shaCtx->total[1]++;
    }

    if (left && len >= fill) {
        ARCH_MemCpy_Fast((void *)((uint8_t *)shaCtx->shaBuf + left), input, fill);
        /* Set data source address */
        *(uint32_t *)(uintptr_t)(shaCtx->linkAddr + 4) = (uint32_t)(uintptr_t)shaCtx->shaBuf;

        /* Set data length */
        *((uint16_t *)(uintptr_t)shaCtx->linkAddr + 1) = 1;

        /* Trigger */
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T));

        /* Choose accumulating last hash in the next time */
        *((uint32_t *)(uintptr_t)shaCtx->linkAddr) |= 0x40;
        input += fill;
        len -= fill;
        left = 0;
    }

    fill = len / 64;
    len = len % 64;

    if (fill > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* Fill data */
        *(uint32_t *)(uintptr_t)(shaCtx->linkAddr + 4) = (uint32_t)(uintptr_t)input;
        *((uint16_t *)(uintptr_t)shaCtx->linkAddr + 1) = fill;

        /* Trigger */
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T));

        input += (fill * 64);
        /* Choose accumulating last hash in the next time */
        *((uint32_t *)(uintptr_t)shaCtx->linkAddr) |= 0x40;
    }

    if (len > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* Copy left data into temp buffer */
        ARCH_MemCpy_Fast((void *)((uint8_t *)shaCtx->shaBuf + left), input, len);
    }

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SHA512 link mode update input data function
 *
 * @param  shaCtx: SHA512 link mode context pointer
 * @param  shaNo: SHA ID type
 * @param  input: SHA input data pointer, and the address should be word align
 * @param  len: SHA input data length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_SHA512_Link_Update(SEC_Eng_SHA512_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, const uint8_t *input, uint64_t len)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t fill;
    uint32_t left;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    if (len == 0) {
        return SUCCESS;
    }

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Set link address */
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_LINK, shaCtx->linkAddr);

    left = shaCtx->total[0] & 0x7F;
    fill = 128 - left;

    shaCtx->total[0] += (uint64_t)len;

    if (shaCtx->total[0] < (uint64_t)len) {
        shaCtx->total[1]++;
    }

    if (left && len >= fill) {
        ARCH_MemCpy_Fast((void *)((uint8_t *)shaCtx->shaBuf + left), input, fill);
        /* Set data source address */
        *(uint32_t *)(uintptr_t)(shaCtx->linkAddr + 4) = (uint32_t)(uintptr_t)shaCtx->shaBuf;

        /* Set data length */
        *((uint16_t *)(uintptr_t)shaCtx->linkAddr + 1) = 1;

        /* Trigger */
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T));

        /* Choose accumulating last hash in the next time */
        *((uint32_t *)(uintptr_t)shaCtx->linkAddr) |= 0x40;
        input += fill;
        len -= fill;
        left = 0;
    }

    fill = len / 128;
    len = len % 128;

    if (fill > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* Fill data */
        *(uint32_t *)(uintptr_t)(shaCtx->linkAddr + 4) = (uint32_t)(uintptr_t)input;
        *((uint16_t *)(uintptr_t)shaCtx->linkAddr + 1) = fill;

        /* Trigger */
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T));

        input += (fill * 128);
        /* Choose accumulating last hash in the next time */
        *((uint32_t *)(uintptr_t)shaCtx->linkAddr) |= 0x40;
    }

    if (len > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* Copy left data into temp buffer */
        ARCH_MemCpy_Fast((void *)((uint8_t *)shaCtx->shaBuf + left), input, len);
    }

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  MD5 link mode update input data function
 *
 * @param  md5Ctx: MD5 link mode context pointer
 * @param  shaNo: SHA ID type
 * @param  input: MD5 input data pointer, and the address should be word align
 * @param  len: MD5 input data length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_MD5_Link_Update(SEC_Eng_MD5_Link_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, const uint8_t *input, uint32_t len)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t fill;
    uint32_t left;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    if (len == 0) {
        return SUCCESS;
    }

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Set link address */
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_LINK, md5Ctx->linkAddr);

    left = md5Ctx->total[0] & 0x3F;
    fill = 64 - left;

    md5Ctx->total[0] += (uint32_t)len;
    md5Ctx->total[0] &= 0xFFFFFFFF;

    if (md5Ctx->total[0] < (uint32_t)len) {
        md5Ctx->total[1]++;
    }

    if (left && len >= fill) {
        ARCH_MemCpy_Fast((void *)((uint8_t *)md5Ctx->md5Buf + left), input, fill);

        /* Set data source address */
        *(uint32_t *)(uintptr_t)(md5Ctx->linkAddr + 4) = (uint32_t)(uintptr_t)md5Ctx->md5Buf;

        /* Set data length */
        *((uint16_t *)(uintptr_t)md5Ctx->linkAddr + 1) = 1;

        /* Trigger */
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T));

        /* Choose accumulating last hash in the next time */
        *((uint32_t *)(uintptr_t)md5Ctx->linkAddr) |= 0x40;
        input += fill;
        len -= fill;
        left = 0;
    }

    fill = len / 64;
    len = len % 64;

    if (fill > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* Fill data */
        *(uint32_t *)(uintptr_t)(md5Ctx->linkAddr + 4) = (uint32_t)(uintptr_t)input;
        *((uint16_t *)(uintptr_t)md5Ctx->linkAddr + 1) = fill;

        /* Trigger */
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T));

        input += (fill * 64);
        /* Choose accumulating last hash in the next time */
        *((uint32_t *)(uintptr_t)md5Ctx->linkAddr) |= 0x40;
    }

    if (len > 0) {
        /* Wait finished */
        timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

        do {
            tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
            timeoutCnt--;

            if (timeoutCnt == 0) {
                return TIMEOUT;
            }
        } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

        /* Copy left data into temp buffer */
        ARCH_MemCpy_Fast((void *)((uint8_t *)md5Ctx->md5Buf + left), input, len);
    }

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  CRC16 link mode work input data function
 *
 * @param  shaNo: SHA ID type
 * @param  linkAddr: CRC16 link mode address
 * @param  input: CRC16 input data pointer, and the address should be word align
 * @param  len: CRC16 input data length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_CRC16_Link_Work(SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr, const uint8_t *in, uint32_t len, uint8_t *out)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(shaNo));

    /* Link address should word align */
    if ((linkAddr & 0x03) != 0) {
        return ERROR;
    }

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Set link address */
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_LINK, linkAddr);

    /* Change source buffer address and destination buffer address */
    *(uint32_t *)(uintptr_t)(linkAddr + 4) = (uint32_t)(uintptr_t)in;

    /* Set data length, 16 bits per block */
    *((uint16_t *)(uintptr_t)linkAddr + 1) = len * 8 / 16;

    /* Trigger */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T));

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* CRC16 code len is 16 bits */
    ARCH_MemCpy_Fast(out, (uint8_t *)(uintptr_t)(linkAddr + 0x10), 2);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  CRC32 link mode work input data function
 *
 * @param  shaNo: SHA ID type
 * @param  linkAddr: CRC32 link mode address
 * @param  input: CRC32 input data pointer, and the address should be word align
 * @param  len: CRC32 input data length
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_CRC32_Link_Work(SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr, const uint8_t *in, uint32_t len, uint8_t *out)
{
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(shaNo));

    /* Link address should word align */
    if ((linkAddr & 0x03) != 0) {
        return ERROR;
    }

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Set link address */
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_LINK, linkAddr);

    /* Change source buffer address and destination buffer address */
    *(uint32_t *)(uintptr_t)(linkAddr + 4) = (uint32_t)(uintptr_t)in;

    /* Set data length , 32 bits per block*/
    *((uint16_t *)(uintptr_t)linkAddr + 1) = len * 8 / 32;

    /* Trigger */
    tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_TRIG_1T));

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* CRC32 code len is 32 bits */
    ARCH_MemCpy_Fast(out, (uint8_t *)(uintptr_t)(linkAddr + 0x10), 4);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SHA256 link mode finish to get output function
 *
 * @param  shaCtx: SHA256 link mode context pointer
 * @param  shaNo: SHA ID type
 * @param  hash: SHA output data of SHA result
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_SHA256_Link_Finish(SEC_Eng_SHA256_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint8_t *hash)
{
    uint32_t last, padn;
    uint32_t high, low;
    uint8_t msgLen[8];
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t shaMode = (*(uint32_t *)(uintptr_t)shaCtx->linkAddr) >> 2 & 0x7;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Set link address */
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_LINK, shaCtx->linkAddr);

    high = (shaCtx->total[0] >> 29) | (shaCtx->total[1] << 3);
    low = (shaCtx->total[0] << 3);

    PUT_UINT32_BE(high, msgLen, 0);
    PUT_UINT32_BE(low, msgLen, 4);

    last = shaCtx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    Sec_Eng_SHA256_Link_Update(shaCtx, shaNo, (uint8_t *)shaCtx->shaPadding, padn);

    /* Wait for shaPadding idle */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    Sec_Eng_SHA256_Link_Update(shaCtx, shaNo, msgLen, 8);

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Get result according to SHA mode,result is placed in (link address + offset:8) */
    switch (shaMode) {
        case 0:
            ARCH_MemCpy_Fast(hash, (uint8_t *)(uintptr_t)(shaCtx->linkAddr + 8), 32);
            break;

        case 1:
            ARCH_MemCpy_Fast(hash, (uint8_t *)(uintptr_t)(shaCtx->linkAddr + 8), 28);
            break;

        case 2:
            ARCH_MemCpy_Fast(hash, (uint8_t *)(uintptr_t)(shaCtx->linkAddr + 8), 20);
            break;

        case 3:
            ARCH_MemCpy_Fast(hash, (uint8_t *)(uintptr_t)(shaCtx->linkAddr + 8), 20);
            break;

        default:
            break;
    }

    /* Choose new hash in the next time */
    *((uint32_t *)(uintptr_t)shaCtx->linkAddr) &= ~0x40;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  SHA512 link mode finish to get output function
 *
 * @param  shaCtx: SHA512 link mode context pointer
 * @param  shaNo: SHA ID type
 * @param  hash: SHA output data of SHA result
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_SHA512_Link_Finish(SEC_Eng_SHA512_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint8_t *hash)
{
    uint64_t last, padn;
    uint64_t high, low;
    uint8_t msgLen[16];
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t shaMode = (*(uint32_t *)(uintptr_t)shaCtx->linkAddr) >> 2 & 0x7;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Set link address */
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_LINK, shaCtx->linkAddr);

    high = (shaCtx->total[0] >> 61) | (shaCtx->total[1] << 3);
    low = (shaCtx->total[0] << 3);

    PUT_UINT64_BE(high, msgLen, 0);
    PUT_UINT64_BE(low, msgLen, 8);

    last = shaCtx->total[0] & 0x7F;
    padn = (last < 112) ? (112 - last) : (240 - last);

    Sec_Eng_SHA512_Link_Update(shaCtx, shaNo, (uint8_t *)shaCtx->shaPadding, padn);

    /* Wait for shaPadding idle */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    Sec_Eng_SHA512_Link_Update(shaCtx, shaNo, msgLen, 16);

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Get result according to SHA mode,result is placed in (link address + offset:8) */
    switch (shaMode) {
        case 4:
            ARCH_MemCpy_Fast(hash, (uint8_t *)(uintptr_t)(shaCtx->linkAddr + 8), 64);
            break;

        case 5:
            ARCH_MemCpy_Fast(hash, (uint8_t *)(uintptr_t)(shaCtx->linkAddr + 8), 48);
            break;

        case 6:
            ARCH_MemCpy_Fast(hash, (uint8_t *)(uintptr_t)(shaCtx->linkAddr + 8), 28);
            break;

        case 7:
            ARCH_MemCpy_Fast(hash, (uint8_t *)(uintptr_t)(shaCtx->linkAddr + 8), 32);
            break;

        default:
            break;
    }

    /* Choose new hash in the next time */
    *((uint32_t *)(uintptr_t)shaCtx->linkAddr) &= ~0x40;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  MD5 link mode finish to get output function
 *
 * @param  md5Ctx: MD5 link mode context pointer
 * @param  shaNo: SHA ID type
 * @param  hash: MD5 output data of SHA result
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_MD5_Link_Finish(SEC_Eng_MD5_Link_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, uint8_t *hash)
{
    uint32_t last, padn;
    uint32_t high, low;
    uint8_t msgLen[8];
    uint32_t SHAx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_SHA_ID_TYPE(shaNo));

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    /* Set link address */
    BL_WR_REG(SHAx, SEC_ENG_SE_SHA_0_LINK, md5Ctx->linkAddr);

    high = (md5Ctx->total[0] >> 29) | (md5Ctx->total[1] << 3);
    low = (md5Ctx->total[0] << 3);

    PUT_UINT32(low, msgLen, 0);
    PUT_UINT32(high, msgLen, 4);

    last = md5Ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    Sec_Eng_MD5_Link_Update(md5Ctx, shaNo, (uint8_t *)md5Ctx->md5Padding, padn);

    /* Wait for shaPadding idle */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    Sec_Eng_MD5_Link_Update(md5Ctx, shaNo, msgLen, 8);

    /* Wait finished */
    timeoutCnt = SEC_ENG_SHA_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(SHAx, SEC_ENG_SE_SHA_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_BUSY));

    ARCH_MemCpy_Fast(hash, (uint8_t *)(uintptr_t)(md5Ctx->linkAddr + 8), 16);

    /* Choose new hash in the next time */
    *((uint32_t *)(uintptr_t)md5Ctx->linkAddr) &= ~0x40;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Group0 request SHA Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Request_SHA_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if ((tmpVal & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL_PROT, 0x02);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if ((tmpVal & 0x03) == 0x01) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group0 release SHA Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Release_SHA_Access(void)
{
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Group1 request SHA Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Request_SHA_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if ((tmpVal & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL_PROT, 0x04);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if ((tmpVal & 0x03) == 0x02) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group1 release SHA Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Release_SHA_Access(void)
{
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  AES initialization function
 *
 * @param  aesCtx: AES context pointer
 * @param  aesNo: AES ID type
 * @param  aesType: AES type:ECB,CTR,CBC
 * @param  keyType: AES key type:128,256,192
 * @param  enDecType: AES encryption or decryption
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_AES_Init(SEC_Eng_AES_Ctx *aesCtx, SEC_ENG_AES_ID_Type aesNo, SEC_ENG_AES_Type aesType, SEC_ENG_AES_Key_Type keyType, SEC_ENG_AES_EnDec_Type enDecType)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_AES_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));
    CHECK_PARAM(IS_SEC_ENG_AES_TYPE(aesType));
    CHECK_PARAM(IS_SEC_ENG_AES_KEY_TYPE(keyType));
    CHECK_PARAM(IS_SEC_ENG_AES_ENDEC_TYPE(enDecType));

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_AES_0_BUSY));

    /* Set AES mode type*/
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_BLOCK_MODE, aesType);

    /* Set AES key type */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_MODE, keyType);

    /* Set AES encryption or decryption */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_DEC_EN, enDecType);

    /* Clear dec_key_sel to select new key */
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_DEC_KEY_SEL);

    /* Clear aes iv sel to select new iv */
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_IV_SEL);

    /* Clear AES interrupt */
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_INT_CLR_1T);

    /* Enable AES */
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_EN);

    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, tmpVal);

    /* Clear AES context */
    memset(aesCtx, 0, sizeof(SEC_Eng_AES_Ctx));

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_AES_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_AES_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  AES enable function,set AES bigendian
 *
 * @param  aesNo: AES ID type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_AES_Enable_BE(SEC_ENG_AES_ID_Type aesNo)
{
    uint32_t AESx = SEC_ENG_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));

    /* set 0x0f to 0x1f for xts mode */
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_ENDIAN, 0x1f);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_AES_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_AES_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  AES enable function,set AES littleendian
 *
 * @param  aesNo: AES ID type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_AES_Enable_LE(SEC_ENG_AES_ID_Type aesNo)
{
    uint32_t AESx = SEC_ENG_BASE;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));

    /* set 0x00 to 0x0f for xts mode */
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_ENDIAN, 0x10);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_AES_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_AES_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  AES enable link mode
 *
 * @param  aesNo: AES ID type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_AES_Enable_Link(SEC_ENG_AES_ID_Type aesNo)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));

    /* Enable aes link mode */
    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_LINK_MODE));
}

/****************************************************************************/ /**
 * @brief  AES disable link mode
 *
 * @param  aesNo: AES ID type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_AES_Disable_Link(SEC_ENG_AES_ID_Type aesNo)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));

    /* Disable aes link mode */
    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_LINK_MODE));
}

/****************************************************************************/ /**
 * @brief  AES work in link mode
 *
 * @param  aesNo: AES ID type
 * @param  linkAddr: Address of config structure in link mode
 * @param  in: AES input data buffer to deal with
 * @param  len: AES input data length
 * @param  out: AES output data buffer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_AES_Link_Work(SEC_ENG_AES_ID_Type aesNo, uint32_t linkAddr, const uint8_t *in, uint32_t len, uint8_t *out)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_AES_BUSY_TIMEOUT_COUNT;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));

    /* Link address should word align */
    if ((linkAddr & 0x03) != 0 || len % 16 != 0) {
        return ERROR;
    }

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_AES_0_BUSY));

    /* Set link address */
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_LINK, linkAddr);

    /* Change source buffer address and destination buffer address */
    *(uint32_t *)(uintptr_t)(linkAddr + 4) = (uint32_t)(uintptr_t)in;
    *(uint32_t *)(uintptr_t)(linkAddr + 8) = (uint32_t)(uintptr_t)out;

    /* Set data length */
    *((uint16_t *)(uintptr_t)linkAddr + 1) = len / 16;

    /* Enable aes */
    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_EN));

    /* Start aes engine and wait finishing */
    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_TRIG_1T));

    __NOP();
    __NOP();
    timeoutCnt = SEC_ENG_AES_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_AES_0_BUSY));

    /* Disable aes */
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_EN));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  AES set hardware key source:efuse region for CPU0  or region efuse for CPU1
 *
 * @param  aesNo: AES ID type
 * @param  src: AES key source type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_AES_Set_Hw_Key_Src(SEC_ENG_AES_ID_Type aesNo, uint8_t src)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));

    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_SBOOT);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_SBOOT_KEY_SEL, src);

    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_SBOOT, tmpVal);
}

/****************************************************************************/ /**
 * @brief  AES set KEY and IV
 *
 * @param  aesNo: AES ID type
 * @param  keySrc: AES KEY type:SEC_ENG_AES_KEY_HW or SEC_ENG_AES_KEY_SW
 * @param  key: AES KEY pointer
 * @param  iv: AES IV pointer
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_AES_Set_Key_IV(SEC_ENG_AES_ID_Type aesNo, SEC_ENG_AES_Key_Src_Type keySrc, const uint8_t *key, const uint8_t *iv)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t keyType;
    uint32_t aesType;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));
    CHECK_PARAM(IS_SEC_ENG_AES_KEY_SRC_TYPE(keySrc));

    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
    aesType = BL_GET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_BLOCK_MODE);

    /* Set IV, XTS mode and other mode are different */
    if (aesType == (uint32_t)SEC_ENG_AES_XTS) {
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_0, BL_RDWD_FRM_BYTEP(iv));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_1, BL_RDWD_FRM_BYTEP(iv));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_2, BL_RDWD_FRM_BYTEP(iv));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_3, BL_RDWD_FRM_BYTEP(iv));
        iv += 4;
    } else {
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_3, __REV(BL_RDWD_FRM_BYTEP(iv)));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_2, __REV(BL_RDWD_FRM_BYTEP(iv)));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_1, __REV(BL_RDWD_FRM_BYTEP(iv)));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_0, __REV(BL_RDWD_FRM_BYTEP(iv)));
        iv += 4;
    }

    /* Select hardware key */
    if (keySrc == SEC_ENG_AES_KEY_HW) {
        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_HW_KEY_EN, SEC_ENG_AES_KEY_HW);
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, tmpVal);

        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_KEY_SEL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_KEY_SEL, *key);
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_SEL, tmpVal);

        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_1_KEY_SEL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_1_KEY_SEL, *key);
        BL_WR_REG(AESx, SEC_ENG_SE_AES_1_KEY_SEL, tmpVal);

        return;
    }

    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_7, __REV(BL_RDWD_FRM_BYTEP(key)));
    key += 4;
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_6, __REV(BL_RDWD_FRM_BYTEP(key)));
    key += 4;
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_5, __REV(BL_RDWD_FRM_BYTEP(key)));
    key += 4;
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_4, __REV(BL_RDWD_FRM_BYTEP(key)));
    key += 4;

    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
    keyType = BL_GET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_MODE);

    if (keyType == (uint32_t)SEC_ENG_AES_KEY_192BITS) {
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_3, __REV(BL_RDWD_FRM_BYTEP(key)));
        key += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_2, __REV(BL_RDWD_FRM_BYTEP(key)));
        key += 4;
    } else if (keyType == (uint32_t)SEC_ENG_AES_KEY_256BITS || keyType == (uint32_t)SEC_ENG_AES_DOUBLE_KEY_128BITS || aesType == (uint32_t)SEC_ENG_AES_XTS) {
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_3, __REV(BL_RDWD_FRM_BYTEP(key)));
        key += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_2, __REV(BL_RDWD_FRM_BYTEP(key)));
        key += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_1, __REV(BL_RDWD_FRM_BYTEP(key)));
        key += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_0, __REV(BL_RDWD_FRM_BYTEP(key)));
        key += 4;
    }

    /* Select software key */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_HW_KEY_EN, SEC_ENG_AES_KEY_SW);

    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  AES set KEY and IV with bigendian
 *
 * @param  aesNo: AES ID type
 * @param  keySrc: AES KEY type:SEC_ENG_AES_KEY_HW or SEC_ENG_AES_KEY_SW
 * @param  key: AES KEY pointer
 * @param  iv: AES IV pointer
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_AES_Set_Key_IV_BE(SEC_ENG_AES_ID_Type aesNo, SEC_ENG_AES_Key_Src_Type keySrc, const uint8_t *key, const uint8_t *iv)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t keyType;
    uint32_t aesType;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));
    CHECK_PARAM(IS_SEC_ENG_AES_KEY_SRC_TYPE(keySrc));

    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
    aesType = BL_GET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_BLOCK_MODE);

    /* Set IV, XTS mode and other mode are different */
    if (aesType == (uint32_t)SEC_ENG_AES_XTS) {
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_3, __REV(BL_RDWD_FRM_BYTEP(iv)));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_2, __REV(BL_RDWD_FRM_BYTEP(iv)));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_1, __REV(BL_RDWD_FRM_BYTEP(iv)));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_0, __REV(BL_RDWD_FRM_BYTEP(iv)));
        iv += 4;
    } else {
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_0, BL_RDWD_FRM_BYTEP(iv));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_1, BL_RDWD_FRM_BYTEP(iv));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_2, BL_RDWD_FRM_BYTEP(iv));
        iv += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_IV_3, BL_RDWD_FRM_BYTEP(iv));
        iv += 4;
    }

    /* Select hardware key */
    if (keySrc == SEC_ENG_AES_KEY_HW) {
        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_HW_KEY_EN, SEC_ENG_AES_KEY_HW);
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, tmpVal);

        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_KEY_SEL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_KEY_SEL, *key);
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_SEL, tmpVal);

        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_1_KEY_SEL);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_1_KEY_SEL, *key);
        BL_WR_REG(AESx, SEC_ENG_SE_AES_1_KEY_SEL, tmpVal);

        return;
    }

    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_0, BL_RDWD_FRM_BYTEP(key));
    key += 4;
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_1, BL_RDWD_FRM_BYTEP(key));
    key += 4;
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_2, BL_RDWD_FRM_BYTEP(key));
    key += 4;
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_3, BL_RDWD_FRM_BYTEP(key));
    key += 4;

    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
    keyType = BL_GET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_MODE);

    if (keyType == (uint32_t)SEC_ENG_AES_KEY_192BITS) {
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_4, BL_RDWD_FRM_BYTEP(key));
        key += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_5, BL_RDWD_FRM_BYTEP(key));
        key += 4;
    } else if (keyType == (uint32_t)SEC_ENG_AES_KEY_256BITS || keyType == (uint32_t)SEC_ENG_AES_DOUBLE_KEY_128BITS || aesType == (uint32_t)SEC_ENG_AES_XTS) {
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_4, BL_RDWD_FRM_BYTEP(key));
        key += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_5, BL_RDWD_FRM_BYTEP(key));
        key += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_6, BL_RDWD_FRM_BYTEP(key));
        key += 4;
        BL_WR_REG(AESx, SEC_ENG_SE_AES_0_KEY_7, BL_RDWD_FRM_BYTEP(key));
        key += 4;
    }

    /* Select software key */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_HW_KEY_EN, SEC_ENG_AES_KEY_SW);

    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  AES set counter byte type in CTR mode
 *
 * @param  aesNo: AES ID type
 * @param  counterType: AES counter type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_AES_Set_Counter_Byte(SEC_ENG_AES_ID_Type aesNo, SEC_ENG_AES_Counter_Type counterType)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_AES_ID_TYPE(aesNo));
    CHECK_PARAM(IS_SEC_ENG_AES_COUNTER_TYPE(counterType));

    /* Set counter type */
    tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_ENDIAN);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_ENDIAN, BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_CTR_LEN, counterType));
}

/****************************************************************************/ /**
 * @brief  AES encrypt or decrypt input data
 *
 * @param  aesCtx: AES context pointer
 * @param  aesNo: AES ID type
 * @param  in: AES input data buffer to deal with
 * @param  len: AES input data length
 * @param  out: AES output data buffer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_AES_Crypt(SEC_Eng_AES_Ctx *aesCtx, SEC_ENG_AES_ID_Type aesNo, const uint8_t *in, uint32_t len, uint8_t *out)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_AES_BUSY_TIMEOUT_COUNT;

    if (len % 16 != 0) {
        return ERROR;
    }

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_AES_0_BUSY));

    /* Clear trigger */
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_TRIG_1T);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, tmpVal);

    /* Set input and output address */
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_MSA, (uintptr_t)in);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_MDA, (uintptr_t)out);

    /* Set message length */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_MSG_LEN, len / 16);

    if (aesCtx->mode == SEC_ENG_AES_CTR) {
        tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_DEC_KEY_SEL);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_DEC_KEY_SEL);
    }

    /* Set IV sel:0 for new, 1 for last */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_AES_0_IV_SEL, aesCtx->aesFeed);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, tmpVal);

    /* Trigger AES Engine */
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_TRIG_1T);
    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, tmpVal);

    /* Wait finished */
    timeoutCnt = SEC_ENG_AES_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_AES_0_BUSY));

    aesCtx->aesFeed = 1;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  AES finish function, clean register
 *
 * @param  aesNo: AES ID type
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_AES_Finish(SEC_ENG_AES_ID_Type aesNo)
{
    uint32_t AESx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_AES_BUSY_TIMEOUT_COUNT;

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(AESx, SEC_ENG_SE_AES_0_CTRL);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_AES_0_BUSY));

    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_EN);

    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_DEC_KEY_SEL);

    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_IV_SEL);

    BL_WR_REG(AESx, SEC_ENG_SE_AES_0_CTRL, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Group0 request access for AES
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Request_AES_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if (((tmpVal >> 2) & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL_PROT, 0x02);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if (((tmpVal >> 2) & 0x03) == 0x01) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group0 release AES Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Release_AES_Access(void)
{
    /* SHA control idle, write to request*/
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Group1 request AES Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Request_AES_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if (((tmpVal >> 2) & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL_PROT, 0x04);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if (((tmpVal >> 2) & 0x03) == 0x02) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group1 release AES Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Release_AES_Access(void)
{
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  TRNG enable TRNG interrupt
 *
 * @param  None
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Trng_Enable(void)
{
    uint32_t TRNGx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_TRNG_BUSY_TIMEOUT_COUNT;

    tmpVal = BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0);

    /* FIXME:default reseed number is 0x1ff, to verify, use 0xa to speed up */
    //tmpVal=BL_SET_REG_BITS_VAL(tmpVal,SEC_ENG_SE_TRNG_0_RESEED_N,0x1ff);

    /* No interrupt as default */
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_EN);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_CLR_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);

    /* busy will be set to 1 after trigger, the gap is 1T */
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    do {
        tmpVal = BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_TRNG_0_BUSY));

    /* Clear trng interrupt */
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_CLR_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_TRNG_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_TRNG_IRQHandler);
#endif

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  TRNG enable TRNG interrupt
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_Trng_Int_Enable(void)
{
    uint32_t TRNGx = SEC_ENG_BASE;
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0);

    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_MASK);

    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TRNG disable TRNG interrupt
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_Trng_Int_Disable(void)
{
    uint32_t TRNGx = SEC_ENG_BASE;
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0);

    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_MASK);

    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TRNG get random data out
 *
 * @param  data[32]: TRNG output data
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Trng_Read(uint8_t data[32])
{
    uint8_t *p = (uint8_t *)data;
    uint32_t TRNGx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_TRNG_BUSY_TIMEOUT_COUNT;

    tmpVal = BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0);

    /* Trigger */
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_TRIG_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);

    /* busy will be set to 1 after trigger, the gap is 1T */
    __NOP();
    __NOP();
    __NOP();
    __NOP();

    do {
        tmpVal = BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_TRNG_0_BUSY));

    /* copy trng value */
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_0));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_1));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_2));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_3));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_4));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_5));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_6));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_7));
    p += 4;

    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_TRIG_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);

    /* Clear data */
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_DOUT_CLR_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);

    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_DOUT_CLR_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  TRNG get random data out
 *
 * @param  data: TRNG output data buffer
 *
 * @param  len: total length to get in bytes
 *
 * @return SUCCESS
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Trng_Get_Random(uint8_t *data, uint32_t len)
{
    uint8_t tmpBuf[32];
    uint32_t readLen = 0;
    uint32_t i = 0, cnt = 0;

    while (readLen < len) {
        if (Sec_Eng_Trng_Read(tmpBuf) != SUCCESS) {
            return -1;
        }

        cnt = len - readLen;

        if (cnt > sizeof(tmpBuf)) {
            cnt = sizeof(tmpBuf);
        }

        for (i = 0; i < cnt; i++) {
            data[readLen + i] = tmpBuf[i];
        }

        readLen += cnt;
    }

    return 0;
}

/****************************************************************************/ /**
 * @brief  TRNG Interrupt Read Trigger
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_Trng_Int_Read_Trigger(void)
{
    uint32_t TRNGx = SEC_ENG_BASE;
    uint32_t tmpVal;

    Sec_Eng_Trng_Int_Enable();

    tmpVal = BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0);
    /* Trigger */
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_TRIG_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  TRNG get random data out with Interrupt
 *
 * @param  data[32]: TRNG output data
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_Trng_Int_Read(uint8_t data[32])
{
    uint8_t *p = (uint8_t *)data;
    uint32_t TRNGx = SEC_ENG_BASE;
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0);

    /* copy trng value */
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_0));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_1));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_2));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_3));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_4));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_5));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_6));
    p += 4;
    BL_WRWD_TO_BYTEP(p, BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_DOUT_7));
    p += 4;

    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_TRIG_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);

    /* Clear data */
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_DOUT_CLR_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);

    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_DOUT_CLR_1T);
    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Disable TRNG
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_Trng_Disable(void)
{
    uint32_t TRNGx = SEC_ENG_BASE;
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0);

    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_EN);
    //tmpVal=BL_CLR_REG_BIT(tmpVal,SEC_ENG_SE_TRNG_0_RESEED_N);
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_CLR_1T);

    BL_WR_REG(TRNGx, SEC_ENG_SE_TRNG_0_CTRL_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Group0 request TRNG Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Request_Trng_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if (((tmpVal >> 4) & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_PROT, 0x02);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if (((tmpVal >> 4) & 0x03) == 0x01) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group0 release TRNG Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Release_Trng_Access(void)
{
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Group1 request TRNG Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Request_Trng_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if (((tmpVal >> 4) & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_PROT, 0x04);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if (((tmpVal >> 4) & 0x03) == 0x02) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group1 release TRNG Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Release_Trng_Access(void)
{
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  PKA Reset
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_Reset(void)
{
    uint8_t val;

    //Disable sec engine
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, 0);

    //Enable sec engine
    val = 1 << 3;
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, val);
}

/****************************************************************************/ /**
 * @brief  PKA Enable big endian
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_BigEndian_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_PKA_0_ENDIAN);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_PKA_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_PKA_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  PKA Enable little endian
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LittleEndian_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_PKA_0_ENDIAN);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_PKA_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_PKA_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  PKA get status function
 *
 * @param  status: Structure pointer of PKA status type
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_GetStatus(SEC_Eng_PKA_Status_Type *status)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);
    *(uint16_t *)status = (uint16_t)BL_GET_REG_BITS_VAL(tmpVal, SEC_ENG_SE_PKA_0_STATUS);
}

/****************************************************************************/ /**
 * @brief  PKA clear interrupt
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_Clear_Int(void)
{
    uint32_t ctrl;

    ctrl = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);
    ctrl = BL_SET_REG_BIT(ctrl, SEC_ENG_SE_PKA_0_INT_CLR_1T);

    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, ctrl);

    ctrl = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);
    ctrl = BL_CLR_REG_BIT(ctrl, SEC_ENG_SE_PKA_0_INT_CLR_1T);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, ctrl);
}

/****************************************************************************/ /**
 * @brief  PKA get Register size according to Register type
 *
 * @param  reg_type: PKA Register type
 *
 * @return Register size
 *
*******************************************************************************/
static uint16_t Sec_Eng_PKA_Get_Reg_Size(SEC_ENG_PKA_REG_SIZE_Type reg_type)
{
    switch (reg_type) {
        case SEC_ENG_PKA_REG_SIZE_8:
            return 8;

        case SEC_ENG_PKA_REG_SIZE_16:
            return 16;

        case SEC_ENG_PKA_REG_SIZE_32:
            return 32;

        case SEC_ENG_PKA_REG_SIZE_64:
            return 64;

        case SEC_ENG_PKA_REG_SIZE_96:
            return 96;

        case SEC_ENG_PKA_REG_SIZE_128:
            return 128;

        case SEC_ENG_PKA_REG_SIZE_192:
            return 192;

        case SEC_ENG_PKA_REG_SIZE_256:
            return 256;

        case SEC_ENG_PKA_REG_SIZE_384:
            return 384;

        case SEC_ENG_PKA_REG_SIZE_512:
            return 512;

        default:
            return 0;
    }
}

/****************************************************************************/ /**
 * @brief  PKA set pre-load register configuration
 *
 * @param  size: Data size in word to write
 * @param  regIndex: Register index
 * @param  regType: Register type
 * @param  op: PKA operation
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
static void Sec_Eng_PKA_Write_Pld_Cfg(uint16_t size, uint8_t regIndex, SEC_ENG_PKA_REG_SIZE_Type regType, SEC_ENG_PKA_OP_Type op, uint8_t lastOp)
{
    struct pka0_pld_cfg cfg;

    cfg.value.BF.size = size;
    cfg.value.BF.d_reg_index = regIndex;
    cfg.value.BF.d_reg_type = regType;
    cfg.value.BF.op = op;
    cfg.value.BF.last_op = lastOp;

    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, cfg.value.WORD);
}

/****************************************************************************/ /**
 * @brief  PKA write common operation first configuration
 *
 * @param  s0RegIndex: Register index
 * @param  s0RegType: Register type
 * @param  dRegIndex: Result Register index
 * @param  dRegType: Result Register type
 * @param  op: PKA operation
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
static void Sec_Eng_PKA_Write_Common_OP_First_Cfg(uint8_t s0RegIndex, uint8_t s0RegType, uint8_t dRegIndex, uint8_t dRegType,
                                                  uint8_t op, uint8_t lastOp)
{
    struct pka0_common_op_first_cfg cfg;

    cfg.value.BF.s0_reg_idx = s0RegIndex;
    cfg.value.BF.s0_reg_type = s0RegType;

    if (op != SEC_ENG_PKA_OP_LCMP) {
        cfg.value.BF.d_reg_idx = dRegIndex;
        cfg.value.BF.d_reg_type = dRegType;
    }

    cfg.value.BF.op = op;
    cfg.value.BF.last_op = lastOp;

    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, cfg.value.WORD);
}

/****************************************************************************/ /**
 * @brief  PKA write common operation second configuration1
 *
 * @param  s1RegIndex: Register index
 * @param  s1RegType: Register type
 *
 * @return None
 *
*******************************************************************************/
static void Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1(uint8_t s1RegIndex, uint8_t s1RegType)
{
    struct pka0_common_op_snd_cfg_S1_only cfg;

    cfg.value.BF.s1_reg_idx = s1RegIndex;
    cfg.value.BF.s1_reg_type = s1RegType;

    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, cfg.value.WORD);
}

/****************************************************************************/ /**
 * @brief  PKA write common operation second configuration2
 *
 * @param  s2RegIndex: Register index
 * @param  s2RegType: Register type
 *
 * @return None
 *
*******************************************************************************/
static void Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S2(uint8_t s2RegIndex, uint8_t s2RegType)
{
    struct pka0_common_op_snd_cfg_S2_only cfg;

    cfg.value.BF.s2_reg_idx = s2RegIndex;
    cfg.value.BF.s2_reg_type = s2RegType;

    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, cfg.value.WORD);
}

/****************************************************************************/ /**
 * @brief  PKA write common operation second configuration1 and configuration 2
 *
 * @param  s1RegIndex: Configuration 1 Register index
 * @param  s1RegType: Configuration 1 Register type
 * @param  s2RegIndex: Configuration 2 Register index
 * @param  s2RegType: Configuration 3 Register type
 *
 * @return None
 *
*******************************************************************************/
static void Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1_S2(uint8_t s1RegIndex, uint8_t s1RegType, uint8_t s2RegIndex, uint8_t s2RegType)
{
    struct pka0_common_op_snd_cfg_S1_S2 cfg;

    cfg.value.BF.s1_reg_idx = s1RegIndex;
    cfg.value.BF.s1_reg_type = s1RegType;
    cfg.value.BF.s2_reg_idx = s2RegIndex;
    cfg.value.BF.s2_reg_type = s2RegType;

    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, cfg.value.WORD);
}

/****************************************************************************/ /**
 * @brief  PKA wait for complete interrupt
 *
 * @param  None
 *
 * @return SUCCESS
 *
*******************************************************************************/
static BL_Err_Type Sec_Eng_PKA_Wait_ISR(void)
{
    uint32_t pka0_ctrl;
    uint32_t timeoutCnt = SEC_ENG_PKA_INT_TIMEOUT_COUNT;

    do {
        pka0_ctrl = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (!BL_GET_REG_BITS_VAL(pka0_ctrl, SEC_ENG_SE_PKA_0_INT));

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  PKA read block data from register
 *
 * @param  dest: Pointer to buffer address
 * @param  src: Pointer to register address
 * @param  len: Data len in word
 *
 * @return None
 *
*******************************************************************************/
#ifdef ARCH_ARM
#ifndef __GNUC__
__ASM void Sec_Eng_PKA_Read_Block(uint32_t *dest, const uint32_t *src, uint32_t len)
{
    PUSH{ R3 - R6, LR } Start0
        CMP R2,
# 4 BLT Finish0
        LDR R3,
        [R1] LDR R4, [R1] LDR R5, [R1] LDR R6, [R1] STMIA R0 !, { R3 - R6 } SUBS R2, R2, #4 B Start0 Finish0 POP
    {
        R3 - R6, PC
    }
}
#else
void Sec_Eng_PKA_Read_Block(uint32_t *dest, const uint32_t *src, uint32_t len)
{
    __asm__ __volatile__("push {r3-r6,lr}\n\t"
                         "Start0 :"
                         "cmp   r2,#4\n\t"
                         "blt   Finish0\n\t"
                         "ldr   r3,[r1]\n\t"
                         "ldr   r4,[r1]\n\t"
                         "ldr   r5,[r1]\n\t"
                         "ldr   r6,[r1]\n\t"
                         "stmia r0!,{r3-r6}\n\t"
                         "sub   r2,r2,#4\n\t"
                         "b     Start0\n\t"
                         "Finish0 :"
                         "pop   {r3-r6,pc}\n\t");
}
#endif
#endif
#ifdef ARCH_RISCV
void Sec_Eng_PKA_Read_Block(uint32_t *dest, const uint32_t *src, uint32_t len)
{
    uint32_t wrLen = len - len % 4;
    uint32_t i;

    for (i = 0; i < wrLen; i++) {
        dest[i] = *src;
    }
}
#endif

/****************************************************************************/ /**
 * @brief  PKA Write block data to register
 *
 * @param  dest: Pointer to register address
 * @param  src: Pointer to buffer address
 * @param  len: Data len in word
 *
 * @return None
 *
*******************************************************************************/
#ifdef ARCH_ARM
#ifndef __GNUC__
__ASM void Sec_Eng_PKA_Write_Block(uint32_t *dest, const uint32_t *src, uint32_t len)
{
    PUSH{ R3 - R6, LR } Start1
        CMP R2,
# 4 BLT Finish1
        LDMIA R1 !,
        { R3 - R6 } STR R3, [R0] STR R4, [R0] STR R5, [R0] STR R6, [R0] SUBS R2, R2, #4 B Start1 Finish1 POP
    {
        R3 - R6, PC
    }
}
#else
void Sec_Eng_PKA_Write_Block(uint32_t *dest, const uint32_t *src, uint32_t len)
{
    __asm__ __volatile__("push {r3-r6,lr}\n\t"
                         "Start1 :"
                         "cmp   r2,#4\n\t"
                         "blt   Finish1\n\t"
                         "ldmia r1!,{r3-r6}\n\t"
                         "str   r3,[r0]\n\t"
                         "str   r4,[r0]\n\t"
                         "str   r5,[r0]\n\t"
                         "str   r6,[r0]\n\t"
                         "sub   r2,r2,#4\n\t"
                         "b     Start1\n\t"
                         "Finish1 :"
                         "pop   {r3-r6,pc}\n\t");
}
#endif
#endif
#ifdef ARCH_RISCV
void Sec_Eng_PKA_Write_Block(uint32_t *dest, const uint32_t *src, uint32_t len)
{
    uint32_t wrLen = len - len % 4;
    uint32_t i;

    for (i = 0; i < wrLen; i++) {
        *dest = src[i];
    }
}
#endif

/****************************************************************************/ /**
 * @brief  PKA get result
 *
 * @param  result: Pointer to store result
 * @param  retSize: Result length in word
 * @param  regLen: register length in byte
 *
 * @return None
 *
*******************************************************************************/
static void Sec_Eng_PKA_Get_Result(uint32_t *result, uint8_t retSize, uint16_t regLen)
{
    uint32_t ret_data = 0x00;
    int index = 0x00;

    /* Wait for the result */
    Sec_Eng_PKA_Wait_ISR();
    Sec_Eng_PKA_Clear_Int();
    Sec_Eng_PKA_Read_Block(result, (uint32_t *)(SEC_ENG_BASE + SEC_ENG_SE_PKA_0_RW_OFFSET), retSize);
    index = retSize - (retSize % 4);

    while (index < retSize) {
        ret_data = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW);
        result[index] = ret_data;
        index++;
    }
}

/****************************************************************************/ /**
 * @brief  PKA load data to register
 *
 * @param  regType: Register type
 * @param  regIndex: Register index
 * @param  data: Data buffer
 * @param  size: Data length in word
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_Type regType, uint8_t regIndex, const uint32_t *data, uint16_t size, uint8_t lastOp)
{
    int index = 0x00;
    uint16_t regLen = Sec_Eng_PKA_Get_Reg_Size(regType);

    Sec_Eng_PKA_Write_Pld_Cfg(size, regIndex, regType, SEC_ENG_PKA_OP_CTLIR_PLD, lastOp);

    if (size > regLen / 4) {
        size = regLen / 4;
    }

    Sec_Eng_PKA_Write_Block((uint32_t *)(SEC_ENG_BASE + SEC_ENG_SE_PKA_0_RW_OFFSET), data, size);
    index = size - (size % 4);

    while (index < size) {
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, data[index]);
        index++;
    }
}

/****************************************************************************/ /**
 * @brief  PKA read data from register
 *
 * @param  regType: Register type
 * @param  regIdx: Register index
 * @param  result: Data buffer
 * @param  retSize: Data length in word
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_Read_Data(SEC_ENG_PKA_REG_SIZE_Type regType, uint8_t regIdx, uint32_t *result, uint8_t retSize)
{
    uint16_t regSize;
    uint32_t dummyData = 0;

    regSize = Sec_Eng_PKA_Get_Reg_Size(regType);

    if (retSize > regSize / 4) {
        result = NULL;
        return;
    }

    Sec_Eng_PKA_Write_Pld_Cfg(retSize, regIdx, regType, SEC_ENG_PKA_OP_CFLIR_BUFFER, 1);

    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, dummyData);

    Sec_Eng_PKA_Get_Result(result, retSize, regSize);
}

/****************************************************************************/ /**
 * @brief  PKA clear register
 *
 * @param  dRegType: Register type
 * @param  dRegIdx: Register index
 * @param  size: Data length in word
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_CREG(SEC_ENG_PKA_REG_SIZE_Type dRegType, uint8_t dRegIdx, uint8_t size, uint8_t lastOp)
{
    uint32_t dummyData = 0;

    Sec_Eng_PKA_Write_Pld_Cfg(size, dRegIdx, dRegType, SEC_ENG_PKA_OP_CLIR, lastOp);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, dummyData);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA load data to register
 *
 * @param  regType: regType: Register type
 * @param  regIndex: regIndex: Register index
 * @param  data: data: Data buffer
 * @param  lastOp: size: Data length in word
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_Write_Immediate(SEC_ENG_PKA_REG_SIZE_Type regType, uint8_t regIndex, uint32_t data, uint8_t lastOp)
{
    struct pka0_pldi_cfg cfg;

    cfg.value.BF.rsvd = 0;
    cfg.value.BF.d_reg_index = regIndex;
    cfg.value.BF.d_reg_type = regType;
    cfg.value.BF.op = SEC_ENG_PKA_OP_SLIR;
    cfg.value.BF.last_op = lastOp;

    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, cfg.value.WORD);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, data);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA negative source data:D = (1 << SIZE{S0})-S0
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source Register type
 * @param  s0RegIdx: Source Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_NREG(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t lastOp)
{
    uint32_t dummyData = 0;

    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_NLIR, lastOp);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, dummyData);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA move data:D = S0
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source Register type
 * @param  s0RegIdx: Source Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_Move_Data(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t lastOp)
{
    uint32_t dummyData = 0;

    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_MOVDAT, lastOp);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, dummyData);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA resize data:D = S0, D.Size = S0.Size
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source Register type
 * @param  s0RegIdx: Source Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_RESIZE(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t lastOp)
{
    uint32_t dummyData = 0;

    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_RESIZE, lastOp);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, dummyData);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA mod add:D = (S0 + S1) mod S2
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s1RegType: Source 1 Register type
 * @param  s1RegIdx: Source 1 Register index
 * @param  s2RegType: Source 2 Register type
 * @param  s2RegIdx: Source 2 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_MADD(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType, uint8_t s1RegIdx, uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_MADD, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1_S2(s1RegIdx, s1RegType, s2RegIdx, s2RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA mod sub:D = (S0 - S1) mod S2
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s1RegType: Source 1 Register type
 * @param  s1RegIdx: Source 1 Register index
 * @param  s2RegType: Source 2 Register type
 * @param  s2RegIdx: Source 2 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_MSUB(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType, uint8_t s1RegIdx, uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_MSUB, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1_S2(s1RegIdx, s1RegType, s2RegIdx, s2RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA mod :D = S0 mod S2
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s2RegType: Source 2 Register type
 * @param  s2RegIdx: Source 2 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_MREM(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_MREM, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S2(s2RegIdx, s2RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA mod mul:D = (S0 * S1) mod S2
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s1RegType: Source 1 Register type
 * @param  s1RegIdx: Source 1 Register index
 * @param  s2RegType: Source 2 Register type
 * @param  s2RegIdx: Source 2 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_MMUL(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType, uint8_t s1RegIdx, uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_MMUL, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1_S2(s1RegIdx, s1RegType, s2RegIdx, s2RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA mod sqr:D = (S0 ^ 2) mod S2
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s2RegType: Source 2 Register type
 * @param  s2RegIdx: Source 2 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_MSQR(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_MSQR, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S2(s2RegIdx, s2RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA mod exp:D = (S0 ^ S1) mod S2
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s1RegType: Source 1 Register type
 * @param  s1RegIdx: Source 1 Register index
 * @param  s2RegType: Source 2 Register type
 * @param  s2RegIdx: Source 2 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_MEXP(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType, uint8_t s1RegIdx, uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_MEXP, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1_S2(s1RegIdx, s1RegType, s2RegIdx, s2RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA mod exp:D = (S0 ^ (S2-2) ) mod S2
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s2RegType: Source 2 Register type
 * @param  s2RegIdx: Source 2 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_MINV(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_MINV, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S2(s2RegIdx, s2RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA Report COUT to 1 when S0 < S1
 *
 * @param  cout: Compare result
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s1RegType: Source 1 Register type
 * @param  s1RegIdx: Source 1 Register index
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LCMP(uint8_t *cout, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t s1RegType, uint8_t s1RegIdx)
{
    uint32_t pka0_ctrl = 0x00;

    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, 0, 0, SEC_ENG_PKA_OP_LCMP, 1);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1(s1RegIdx, s1RegType);

    Sec_Eng_PKA_Wait_ISR();
    Sec_Eng_PKA_Clear_Int();
    pka0_ctrl = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);

    *cout = (pka0_ctrl & SEC_ENG_PKA_STATUS_LAST_OPC_MASK) >> SEC_ENG_PKA_STATUS_LAST_OPC_OFFSET;
}

/****************************************************************************/ /**
 * @brief  PKA add:D = S0 + S1
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s1RegType: Source 1 Register type
 * @param  s1RegIdx: Source 1 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LADD(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType, uint8_t s1RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_LADD, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1(s1RegIdx, s1RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA sub:D = S0 - S1
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s1RegType: Source 1 Register type
 * @param  s1RegIdx: Source 1 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LSUB(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType, uint8_t s1RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_LSUB, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1(s1RegIdx, s1RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA mul:D = S0 * S1
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s1RegType: Source 1 Register type
 * @param  s1RegIdx: Source 1 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LMUL(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType, uint8_t s1RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_LMUL, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S1(s1RegIdx, s1RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA sqr:D = S0^2
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LSQR(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t lastOp)
{
    uint32_t dummyData = 0;

    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_LSQR, lastOp);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, dummyData);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA div:D = S0 / S2
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  s2RegType: Source 2 Register type
 * @param  s2RegIdx: Source 2 Register index
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LDIV(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp)
{
    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_LDIV, lastOp);
    Sec_Eng_PKA_Write_Common_OP_Snd_Cfg_S2(s2RegIdx, s2RegType);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA shift:D = S0 << BIT SHIFT
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  bit_shift: Bits to shift
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LMUL2N(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                        uint16_t bit_shift, uint8_t lastOp)
{
    struct pka0_bit_shift_op_cfg cfg;

    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_LMUL2N, 0);

    cfg.value.BF.bit_shift = bit_shift;
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, cfg.value.WORD);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA shift:D = S0 >> BIT SHIFT
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  bit_shift: Bits to shift
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LDIV2N(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                        uint16_t bit_shift, uint8_t lastOp)
{
    struct pka0_bit_shift_op_cfg cfg;

    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_LDIV2N, 0);

    cfg.value.BF.bit_shift = bit_shift;
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, cfg.value.WORD);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA mod 2N:D = S0 % ((1 << BIT SHIFT)-1)
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  s0RegType: Source 0 Register type
 * @param  s0RegIdx: Source 0 Register index
 * @param  bit_shift: Bits to shift
 * @param  lastOp: Last operation
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_LMOD2N(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                        uint16_t bit_shift, uint8_t lastOp)
{
    struct pka0_bit_shift_op_cfg cfg;

    Sec_Eng_PKA_Write_Common_OP_First_Cfg(s0RegIdx, s0RegType, dRegIdx, dRegType, SEC_ENG_PKA_OP_MOD2N, lastOp);

    cfg.value.BF.bit_shift = bit_shift;
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_RW, cfg.value.WORD);

    if (lastOp) {
        Sec_Eng_PKA_Wait_ISR();
        Sec_Eng_PKA_Clear_Int();
    }
}

/****************************************************************************/ /**
 * @brief  PKA GF to Mont  filed 2N:d = (a<<size) % p
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  sRegType: Source Register type
 * @param  sRegIdx: Source Register index
 * @param  size: Bits to shift
 * @param  tRegType: Temp Register type
 * @param  tRegIdx: Temp Register index
 * @param  pRegType: Mod P Register type
 * @param  pRegIdx: Mod P Register index
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_GF2Mont(uint8_t dRegType, uint8_t dRegIdx, uint8_t sRegType, uint8_t sRegIdx, uint32_t size,
                         uint8_t tRegType, uint8_t tRegIdx, uint8_t pRegType, uint8_t pRegIdx)
{
    Sec_Eng_PKA_LMUL2N(tRegType, tRegIdx, sRegType, sRegIdx, size, 0);
    Sec_Eng_PKA_MREM(dRegType, dRegIdx, tRegType, tRegIdx, pRegType, pRegIdx, 1);
}

/****************************************************************************/ /**
 * @brief  PKA GF to Mont  filed 2N:d = (a * inv_r) % p
 *
 * @param  dRegType: Destination Register type
 * @param  dRegIdx: Destination Register index
 * @param  aRegType: Source Register type
 * @param  aRegIdx: Source Register index
 * @param  invrRegType: Invert R Register type
 * @param  invrRegIdx: Invert R Register index
 * @param  tRegType: Temp Register type
 * @param  tRegIdx: Temp Register index
 * @param  pRegType: Mod P Register type
 * @param  pRegIdx: Mod P Register index
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_PKA_Mont2GF(uint8_t dRegType, uint8_t dRegIdx, uint8_t aRegType, uint8_t aRegIdx, uint8_t invrRegType, uint8_t invrRegIdx,
                         uint8_t tRegType, uint8_t tRegIdx, uint8_t pRegType, uint8_t pRegIdx)
{
    Sec_Eng_PKA_LMUL(tRegType, tRegIdx, aRegType, aRegIdx, invrRegType, invrRegIdx, 0);
    Sec_Eng_PKA_MREM(dRegType, dRegIdx, tRegType, tRegIdx, pRegType, pRegIdx, 1);
}

/****************************************************************************/ /**
 * @brief  Group0 request PKA Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Request_PKA_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if (((tmpVal >> 6) & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_PROT, 0x02);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if (((tmpVal >> 6) & 0x03) == 0x01) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group0 release PKA Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Release_PKA_Access(void)
{
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Group1 request PKA Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Request_PKA_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if (((tmpVal >> 6) & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_PROT, 0x04);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if (((tmpVal >> 6) & 0x03) == 0x02) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group1 release PKA Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Release_PKA_Access(void)
{
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Set gmac little endian
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_GMAC_Enable_LE(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_T_ENDIAN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_H_ENDIAN);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_X_ENDIAN);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_GMAC_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_GMAC_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  Set gmac big endian
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_GMAC_Enable_BE(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_T_ENDIAN);
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_H_ENDIAN);
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_X_ENDIAN);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, tmpVal);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(SEC_ENG_ID0_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_GMAC_IRQHandler);
    Interrupt_Handler_Register(SEC_ENG_ID1_SHA_AES_TRNG_PKA_GMAC_IRQn, SEC_GMAC_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  GMAC enable link mode
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_GMAC_Enable_Link(void)
{
    uint32_t tmpVal;

    /* Enable gmac link mode */
    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_EN));
}

/****************************************************************************/ /**
 * @brief  GMAC disable link mode
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Sec_Eng_GMAC_Disable_Link(void)
{
    uint32_t tmpVal;

    /* Disable gmac link mode */
    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_EN));
}

/****************************************************************************/ /**
 * @brief  GMAC work in link mode
 *
 * @param  linkAddr: Address of config structure in link mode
 * @param  in: GMAC input data buffer to deal with
 * @param  len: GMAC input data length
 * @param  out: GMAC output data buffer
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_GMAC_Link_Work(uint32_t linkAddr, const uint8_t *in, uint32_t len, uint8_t *out)
{
    uint32_t GMACx = SEC_ENG_BASE;
    uint32_t tmpVal;
    uint32_t timeoutCnt = SEC_ENG_GMAC_BUSY_TIMEOUT_COUNT;

    /* Link address should word align */
    if ((linkAddr & 0x03) != 0 || len % 16 != 0) {
        return ERROR;
    }

    /* Wait finished */
    do {
        tmpVal = BL_RD_REG(GMACx, SEC_ENG_SE_GMAC_0_CTRL_0);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_GMAC_0_BUSY));

    /* Set link address */
    BL_WR_REG(GMACx, SEC_ENG_SE_GMAC_0_LCA, linkAddr);

    /* Change source buffer address */
    *(uint32_t *)(uintptr_t)(linkAddr + 4) = (uint32_t)(uintptr_t)in;

    /* Set data length */
    *((uint16_t *)(uintptr_t)linkAddr + 1) = len / 16;

    /* Start gmac engine and wait finishing */
    tmpVal = BL_RD_REG(GMACx, SEC_ENG_SE_GMAC_0_CTRL_0);
    BL_WR_REG(GMACx, SEC_ENG_SE_GMAC_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_TRIG_1T));
    timeoutCnt = SEC_ENG_GMAC_BUSY_TIMEOUT_COUNT;

    do {
        tmpVal = BL_RD_REG(GMACx, SEC_ENG_SE_GMAC_0_CTRL_0);
        timeoutCnt--;

        if (timeoutCnt == 0) {
            return TIMEOUT;
        }
    } while (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_GMAC_0_BUSY));

    /* Get result */
    ARCH_MemCpy_Fast(out, (uint8_t *)(uintptr_t)(linkAddr + 0x18), 16);

    return SUCCESS;
}

#ifndef BFLB_USE_HAL_DRIVER
/****************************************************************************/ /**
 * @brief  Sec Eng Interrupt Handler
 *
 * @param  intType: IRQ Type
 *
 * @return None
 *
*******************************************************************************/
static void SEC_Eng_IntHandler(SEC_ENG_INT_Type intType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_INT_TYPE(intType));

    switch (intType) {
        case SEC_ENG_INT_TRNG:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_TRNG_0_INT)) {
                /* Clear interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_CLR_1T));

                /* Call the callback function */
                if (secEngIntCbfArra[SEC_ENG_INT_TRNG] != NULL) {
                    secEngIntCbfArra[SEC_ENG_INT_TRNG]();
                }
            }

            break;

        case SEC_ENG_INT_AES:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_AES_0_INT)) {
                /* Clear interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_INT_CLR_1T));

                /* Call the callback function */
                if (secEngIntCbfArra[SEC_ENG_INT_AES] != NULL) {
                    secEngIntCbfArra[SEC_ENG_INT_AES]();
                }
            }

            break;

        case SEC_ENG_INT_SHA:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_INT)) {
                /* Clear interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_INT_CLR_1T));

                /* Call the callback function */
                if (secEngIntCbfArra[SEC_ENG_INT_SHA] != NULL) {
                    secEngIntCbfArra[SEC_ENG_INT_SHA]();
                }
            }

            break;

        case SEC_ENG_INT_PKA:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_PKA_0_INT)) {
                /* Clear interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_PKA_0_INT_CLR_1T));

                /* Call the callback function */
                if (secEngIntCbfArra[SEC_ENG_INT_PKA] != NULL) {
                    secEngIntCbfArra[SEC_ENG_INT_PKA]();
                }
            }

            break;

        case SEC_ENG_INT_CDET:

            /* Call the callback function */
            if (secEngIntCbfArra[SEC_ENG_INT_CDET] != NULL) {
                secEngIntCbfArra[SEC_ENG_INT_CDET]();
            }

            break;

        case SEC_ENG_INT_GMAC:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_GMAC_0_INT)) {
                /* Clear interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_INT_CLR_1T));

                /* Call the callback function */
                if (secEngIntCbfArra[SEC_ENG_INT_GMAC] != NULL) {
                    secEngIntCbfArra[SEC_ENG_INT_GMAC]();
                }
            }

            break;

        default:
            break;
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Group0 request GMAC Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Request_GMAC_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if (((tmpVal >> 10) & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_PROT, 0x02);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if (((tmpVal >> 10) & 0x03) == 0x01) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group0 release GMAC Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group0_Release_GMAC_Access(void)
{
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Group1 request GMAC Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Request_GMAC_Access(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

    if (((tmpVal >> 10) & 0x03) == 0x03) {
        /* SHA control idle, write to request*/
        BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_PROT, 0x04);

        /* Check request result */
        tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_CTRL_PROT_RD);

        if (((tmpVal >> 10) & 0x03) == 0x02) {
            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  Group1 release GMAC Access
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type Sec_Eng_Group1_Release_GMAC_Access(void)
{
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_PROT, 0x06);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Sec Eng Interrupt Mask or Unmask
 *
 * @param  intType: Sec Eng Interrupt Type
 * @param  intMask: MASK or UNMASK
 *
 * @return None
 *
*******************************************************************************/
void SEC_Eng_IntMask(SEC_ENG_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_INT_TYPE(intType));

    switch (intType) {
        case SEC_ENG_INT_TRNG:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0);

            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_MASK));
            } else {
                /* MASK(Disable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_MASK));
            }

            break;

        case SEC_ENG_INT_AES:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL);

            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_INT_MASK));
            } else {
                /* MASK(Disable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_INT_MASK));
            }

            break;

        case SEC_ENG_INT_SHA:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL);

            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_INT_MASK));
            } else {
                /* MASK(Disable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_INT_MASK));
            }

            break;

        case SEC_ENG_INT_PKA:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);

            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_PKA_0_INT_MASK));
            } else {
                /* MASK(Disable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_PKA_0_INT_MASK));
            }

            break;

        case SEC_ENG_INT_CDET:
            break;

        case SEC_ENG_INT_GMAC:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);

            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_INT_MASK));
            } else {
                /* MASK(Disable) this interrupt */
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_INT_MASK));
            }

            break;

        case SEC_ENG_INT_ALL:
            if (intMask == UNMASK) {
                /* UNMASK(Enable) this interrupt */
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_MASK));
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_INT_MASK));
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_INT_MASK));
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_PKA_0_INT_MASK));
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_INT_MASK));
            } else {
                /* MASK(Disable) this interrupt */
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_MASK));
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_INT_MASK));
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_INT_MASK));
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_PKA_0_INT_MASK));
                tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);
                BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_INT_MASK));
            }

            break;

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  Sec Eng Interrupt clear
 *
 * @param  intType: Sec Eng Interrupt Type
 *
 * @return None
 *
*******************************************************************************/
void SEC_Eng_ClrIntStatus(SEC_ENG_INT_Type intType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_INT_TYPE(intType));

    switch (intType) {
        case SEC_ENG_INT_AES:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL);
            BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_AES_0_INT_CLR_1T));
            break;

        case SEC_ENG_INT_SHA:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL);
            BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_SHA_0_INT_CLR_1T));
            break;

        case SEC_ENG_INT_TRNG:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0);
            BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_INT_CLR_1T));
            break;

        case SEC_ENG_INT_PKA:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);
            BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_PKA_0_INT_CLR_1T));
            break;

        case SEC_ENG_INT_CDET:
            break;

        case SEC_ENG_INT_GMAC:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);
            BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0, BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_GMAC_0_INT_CLR_1T));
            break;

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  Sec Eng Interrupt callback function install
 *
 * @param  intType: Sec Eng Interrupt Type
 * @param  cbFun: Pointer to interrupt callback function. The type should be void (*fn)(void)
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void SEC_Eng_Int_Callback_Install(SEC_ENG_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_INT_TYPE(intType));

    secEngIntCbfArra[intType] = cbFun;
}
#endif

/****************************************************************************/ /**
 * @brief  Sec Eng get interrupt status
 *
 * @param  intType: Sec Eng Interrupt Type
 *
 * @return status of interrupt
 *
*******************************************************************************/
BL_Sts_Type SEC_Eng_GetIntStatus(SEC_ENG_INT_Type intType)
{
    uint32_t tmpVal;
    BL_Sts_Type status = RESET;

    /* Check the parameters */
    CHECK_PARAM(IS_SEC_ENG_INT_TYPE(intType));

    switch (intType) {
        case SEC_ENG_INT_AES:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_AES_0_CTRL);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_AES_0_INT)) {
                status = SET;
            }

            break;

        case SEC_ENG_INT_SHA:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_SHA_0_CTRL);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_SHA_0_INT)) {
                status = SET;
            }

            break;

        case SEC_ENG_INT_TRNG:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_0);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_TRNG_0_INT)) {
                status = SET;
            }

            break;

        case SEC_ENG_INT_PKA:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_PKA_0_CTRL_0);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_PKA_0_INT)) {
                status = SET;
            }

            break;

        case SEC_ENG_INT_CDET:
            break;

        case SEC_ENG_INT_GMAC:
            tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_GMAC_0_CTRL_0);

            if (BL_IS_REG_BIT_SET(tmpVal, SEC_ENG_SE_GMAC_0_INT)) {
                status = SET;
            }

            break;

        default:
            break;
    }

    return status;
}

#ifndef BFLB_USE_HAL_DRIVER
/****************************************************************************/ /**
 * @brief  Sec Eng Trng IRQ Handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SEC_TRNG_IRQHandler(void)
{
    SEC_Eng_IntHandler(SEC_ENG_INT_TRNG);
}

/****************************************************************************/ /**
 * @brief  Sec Eng Pka IRQ Handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SEC_PKA_IRQHandler(void)
{
    SEC_Eng_IntHandler(SEC_ENG_INT_PKA);
}

/****************************************************************************/ /**
 * @brief  Sec Eng Aes IRQ Handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SEC_AES_IRQHandler(void)
{
    SEC_Eng_IntHandler(SEC_ENG_INT_AES);
}

/****************************************************************************/ /**
 * @brief  Sec Eng Sha IRQ Handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SEC_SHA_IRQHandler(void)
{
    SEC_Eng_IntHandler(SEC_ENG_INT_SHA);
}

/****************************************************************************/ /**
 * @brief  Sec Eng Cdet IRQ Handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SEC_CDET_IRQHandler(void)
{
    SEC_Eng_IntHandler(SEC_ENG_INT_CDET);
}

/****************************************************************************/ /**
 * @brief  Sec Eng Gmac IRQ Handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void SEC_GMAC_IRQHandler(void)
{
    SEC_Eng_IntHandler(SEC_ENG_INT_GMAC);
}
#endif

/****************************************************************************/ /**
 * @brief  turn on sec ring
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION SEC_Eng_Turn_On_Sec_Ring(void)
{
    uint32_t tmpVal = 0;

    /* Turn-on Sec Ring Oscillation */
    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_3);
    tmpVal = BL_SET_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_ROSC_EN);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_3, tmpVal);
}

/****************************************************************************/ /**
 * @brief  turn off sec ring
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ATTR_TCM_SECTION SEC_Eng_Turn_Off_Sec_Ring(void)
{
    uint32_t tmpVal = 0;

    /* Turn-off Sec Ring Oscillation */
    tmpVal = BL_RD_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_3);
    tmpVal = BL_CLR_REG_BIT(tmpVal, SEC_ENG_SE_TRNG_0_ROSC_EN);
    BL_WR_REG(SEC_ENG_BASE, SEC_ENG_SE_TRNG_0_CTRL_3, tmpVal);
}

/*@} end of group SEC_ENG_Public_Functions */

/*@} end of group SEC_ENG */

/*@} end of group BL808_Peripheral_Driver */
