/**
  ******************************************************************************
  * @file    bl808_sec_eng.h
  * @version V1.0
  * @date
  * @brief   This file is the standard driver header file
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
#ifndef __BL808_SEC_ENG_H__
#define __BL808_SEC_ENG_H__

#include "sec_eng_reg.h"
#include "bl808_common.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  SEC_ENG
 *  @{
 */

/** @defgroup  SEC_ENG_Public_Types
 *  @{
 */

/**
 *  @brief AES port type definition
 */
typedef enum {
    SEC_ENG_AES_ID0, /*!< AES0 port define */
} SEC_ENG_AES_ID_Type;

/**
 *  @brief SHA port type definition
 */
typedef enum {
    SEC_ENG_SHA_ID0, /*!< SHA0 port define */
} SEC_ENG_SHA_ID_Type;

/**
 *  @brief SHA type definition
 */
typedef enum {
    SEC_ENG_SHA256,     /*!< SHA type:SHA256 */
    SEC_ENG_SHA224,     /*!< SHA type:SHA224 */
    SEC_ENG_SHA1,       /*!< SHA type:SHA1 */
    SEC_ENG_SHA1_RSVD,  /*!< SHA type:SHA1 */
    SEC_ENG_SHA512,     /*!< SHA type:SHA512 */
    SEC_ENG_SHA384,     /*!< SHA type:SHA384 */
    SEC_ENG_SHA512T224, /*!< SHA type:SHA512T224 */
    SEC_ENG_SHA512T256, /*!< SHA type:SHA512T156 */
    SEC_ENG_MD5,        /*!< MD5 */
    SEC_ENG_CRC16,      /*!< CRC-16 */
    SEC_ENG_CRC32,      /*!< CRC-32 */
} SEC_ENG_SHA_Type;

/**
 *  @brief AES type definition
 */
typedef enum {
    SEC_ENG_AES_ECB, /*!< AES mode type:ECB */
    SEC_ENG_AES_CTR, /*!< AES mode type:CTR */
    SEC_ENG_AES_CBC, /*!< AES mode type:CBC */
    SEC_ENG_AES_XTS, /*!< AES mode type:XTS */
} SEC_ENG_AES_Type;

/**
 *  @brief AES XTS mode type definition
 */
typedef enum {
    SEC_ENG_AES_XTS_MODE1, /*!< AES xts mode type:mode1 */
    SEC_ENG_AES_XTS_MODE2, /*!< AES xts mode type:mode2 */
} SEC_ENG_AES_XTS_MODE_Type;

/**
 *  @brief AES KEY type definition
 */
typedef enum {
    SEC_ENG_AES_KEY_128BITS,        /*!< AES KEY type:128 bits */
    SEC_ENG_AES_KEY_256BITS,        /*!< AES KEY type:256 bits */
    SEC_ENG_AES_KEY_192BITS,        /*!< AES KEY type:192 bits */
    SEC_ENG_AES_DOUBLE_KEY_128BITS, /*!< AES double KEY type:128 bits */
} SEC_ENG_AES_Key_Type;

/**
 *  @brief AES CTR mode counter type definition
 */
typedef enum {
    SEC_ENG_AES_COUNTER_BYTE_4, /*!< AES CTR mode counter type:4 bytes */
    SEC_ENG_AES_COUNTER_BYTE_1, /*!< AES CTR mode counter type:1 byte */
    SEC_ENG_AES_COUNTER_BYTE_2, /*!< AES CTR mode counter type:2 bytes */
    SEC_ENG_AES_COUNTER_BYTE_3, /*!< AES CTR mode counter type:3 bytes */
} SEC_ENG_AES_Counter_Type;

/**
 *  @brief AES use new or old value type definition
 */
typedef enum {
    SEC_ENG_AES_USE_NEW, /*!< Use new value */
    SEC_ENG_AES_USE_OLD, /*!< Use old value same as last one */
} SEC_ENG_AES_ValueUsed_Type;

/**
 *  @brief AES KEY source type definition
 */
typedef enum {
    SEC_ENG_AES_KEY_SW, /*!< AES KEY from software */
    SEC_ENG_AES_KEY_HW, /*!< AES KEY from hardware */
} SEC_ENG_AES_Key_Src_Type;

/**
 *  @brief AES KEY source type definition
 */
typedef enum {
    SEC_ENG_AES_ENCRYPTION, /*!< AES encryption */
    SEC_ENG_AES_DECRYPTION, /*!< AES decryption */
} SEC_ENG_AES_EnDec_Type;

/**
 *  @brief AES PKA register size type definition
 */
typedef enum {
    SEC_ENG_PKA_REG_SIZE_8 = 1, /*!< Register size is  8 Bytes */
    SEC_ENG_PKA_REG_SIZE_16,    /*!< Register size is  16 Bytes */
    SEC_ENG_PKA_REG_SIZE_32,    /*!< Register size is  32 Bytes */
    SEC_ENG_PKA_REG_SIZE_64,    /*!< Register size is  64 Bytes */
    SEC_ENG_PKA_REG_SIZE_96,    /*!< Register size is  96 Bytes */
    SEC_ENG_PKA_REG_SIZE_128,   /*!< Register size is  128 Bytes */
    SEC_ENG_PKA_REG_SIZE_192,   /*!< Register size is  192 Bytes */
    SEC_ENG_PKA_REG_SIZE_256,   /*!< Register size is  256 Bytes */
    SEC_ENG_PKA_REG_SIZE_384,   /*!< Register size is  384 Bytes */
    SEC_ENG_PKA_REG_SIZE_512,   /*!< Register size is  512 Bytes */
} SEC_ENG_PKA_REG_SIZE_Type;

/**
 *  @brief AES PKA register size type definition
 */
typedef enum {
    SEC_ENG_PKA_OP_PPSEL,                /*!< PKA operation type */
    SEC_ENG_PKA_OP_MOD2N = 0x11,         /*!< PKA operation type */
    SEC_ENG_PKA_OP_LDIV2N = 0x12,        /*!< PKA operation type */
    SEC_ENG_PKA_OP_LMUL2N = 0x13,        /*!< PKA operation type */
    SEC_ENG_PKA_OP_LDIV = 0x14,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_LSQR = 0x15,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_LMUL = 0x16,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_LSUB = 0x17,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_LADD = 0x18,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_LCMP = 0x19,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_MDIV2 = 0x21,         /*!< PKA operation type */
    SEC_ENG_PKA_OP_MINV = 0x22,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_MEXP = 0x23,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_MSQR = 0x24,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_MMUL = 0x25,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_MREM = 0x26,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_MSUB = 0x27,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_MADD = 0x28,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_RESIZE = 0x31,        /*!< PKA operation type */
    SEC_ENG_PKA_OP_MOVDAT = 0x32,        /*!< PKA operation type */
    SEC_ENG_PKA_OP_NLIR = 0x33,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_SLIR = 0x34,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_CLIR = 0x35,          /*!< PKA operation type */
    SEC_ENG_PKA_OP_CFLIRI_BUFFER = 0x36, /*!< PKA operation type */
    SEC_ENG_PKA_OP_CTLIRI_PLD = 0x37,    /*!< PKA operation type */
    SEC_ENG_PKA_OP_CFLIR_BUFFER = 0x38,  /*!< PKA operation type */
    SEC_ENG_PKA_OP_CTLIR_PLD = 0x39,     /*!< PKA operation type */
} SEC_ENG_PKA_OP_Type;

/**
 *  @brief Sec Eng Interrupt Type Def
 */
typedef enum {
    SEC_ENG_INT_TRNG, /*!< Sec Eng Trng Interrupt Type */
    SEC_ENG_INT_AES,  /*!< Sec Eng Aes Interrupt Type */
    SEC_ENG_INT_SHA,  /*!< Sec Eng Sha Interrupt Type */
    SEC_ENG_INT_PKA,  /*!< Sec Eng Pka Interrupt Type */
    SEC_ENG_INT_CDET, /*!< Sec Eng Cdet Interrupt Type */
    SEC_ENG_INT_GMAC, /*!< Sec Eng Gmac Interrupt Type */
    SEC_ENG_INT_ALL,  /*!< Sec Eng All Interrupt Types */
} SEC_ENG_INT_Type;

/**
 *  @brief SEC_ENG SHA256 context
 */
typedef struct
{
    uint32_t total[2];    /*!< Number of bytes processed */
    uint32_t *shaBuf;     /*!< Data not processed but in this temp buffer */
    uint32_t *shaPadding; /*!< Padding data */
    uint8_t shaFeed;      /*!< Sha has feed data */
} SEC_Eng_SHA256_Ctx;

/**
 *  @brief SEC_ENG SHA512 context
 */
typedef struct
{
    uint64_t total[2];    /*!< Number of bytes processed */
    uint64_t *shaBuf;     /*!< Data not processed but in this temp buffer */
    uint64_t *shaPadding; /*!< Padding data */
    uint8_t shaFeed;      /*!< Sha has feed data */
} SEC_Eng_SHA512_Ctx;

/**
 *  @brief SEC_ENG MD5 context
 */
typedef struct
{
    uint32_t total[2];    /*!< Number of bytes processed */
    uint32_t *md5Buf;     /*!< Data not processed but in this temp buffer */
    uint32_t *md5Padding; /*!< Padding data */
    uint8_t md5Feed;      /*!< md5 has feed data */
} SEC_Eng_MD5_Ctx;

/**
 *  @brief SEC_ENG SHA256 link mode context
 */
typedef struct
{
    uint32_t total[2];    /*!< Number of bytes processed */
    uint32_t *shaBuf;     /*!< Data not processed but in this temp buffer */
    uint32_t *shaPadding; /*!< Padding data */
    uint32_t linkAddr;    /*!< Link configure address */
} SEC_Eng_SHA256_Link_Ctx;

/**
 *  @brief SEC_ENG MD5 link mode context
 */
typedef struct
{
    uint64_t total[2];    /*!< Number of bytes processed */
    uint64_t *shaBuf;     /*!< Data not processed but in this temp buffer */
    uint64_t *shaPadding; /*!< Padding data */
    uint32_t linkAddr;    /*!< Link configure address */
} SEC_Eng_SHA512_Link_Ctx;

/**
 *  @brief SEC_ENG SHA256 link mode context
 */
typedef struct
{
    uint32_t total[2];    /*!< Number of bytes processed */
    uint32_t *md5Buf;     /*!< Data not processed but in this temp buffer */
    uint32_t *md5Padding; /*!< Padding data */
    uint32_t linkAddr;    /*!< Link configure address */
} SEC_Eng_MD5_Link_Ctx;

/**
 *  @brief SEC_ENG AES context
 */
typedef struct
{
    uint8_t aesFeed;       /*!< AES has feed data */
    SEC_ENG_AES_Type mode; /*!< AES mode */
} SEC_Eng_AES_Ctx;

/**
 *  @brief SEC_ENG SHA link config structure type definition
 */
typedef struct
{
    uint32_t            : 2;  /*!< [1:0]Reserved */
    uint32_t shaMode    : 3;  /*!< [4:2]Sha-256/sha-224/sha-1/sha-1/sha-512/sha-384/sha-512T224/sha-512T256 */
    uint32_t            : 1;  /*!< [5]Reserved */
    uint32_t shaHashSel : 1;  /*!< [6]New hash or accumulate last hash */
    uint32_t            : 2;  /*!< [8:7]Reserved */
    uint32_t shaIntClr  : 1;  /*!< [9]Clear interrupt */
    uint32_t shaIntSet  : 1;  /*!< [10]Set interrupt */
    uint32_t            : 1;  /*!< [11]Reserved */
    uint32_t shaModeExt : 2;  /*!< [13:12]Extention,0:sha 1:md5 2:crc16 3:crc32 */
    uint32_t            : 2;  /*!< [15:14]Reserved */
    uint32_t shaMsgLen  : 16; /*!< [31:16]Number of 512-bit block */
    uint32_t shaSrcAddr;      /*!< Message source address */
    uint32_t result[16];      /*!< Result of SHA */
} __attribute__((aligned(4))) SEC_Eng_SHA_Link_Config_Type;

/**
 *  @brief SEC_ENG SHA link config structure type definition
 */
typedef struct
{
    uint32_t            : 2;  /*!< [1:0]Reserved */
    uint32_t shaMode    : 3;  /*!< [4:2]Sha-256/sha-224/sha-1/sha-1/sha-512/sha-384/sha-512T224/sha-512T256 */
    uint32_t            : 1;  /*!< [5]Reserved */
    uint32_t shaHashSel : 1;  /*!< [6]New hash or accumulate last hash */
    uint32_t            : 2;  /*!< [8:7]Reserved */
    uint32_t shaIntClr  : 1;  /*!< [9]Clear interrupt */
    uint32_t shaIntSet  : 1;  /*!< [10]Set interrupt */
    uint32_t            : 1;  /*!< [11]Reserved */
    uint32_t shaModeExt : 2;  /*!< [13:12]Extention,0:sha 1:md5 2:crc16 3:crc32 */
    uint32_t            : 2;  /*!< [15:14]Reserved */
    uint32_t shaMsgLen  : 16; /*!< [31:16]Number of 512-bit block */
    uint32_t shaSrcAddr;      /*!< Message source address */
    uint32_t poly;            /*!< poly of CRC */
    uint32_t dout_inv : 1;    /*!< [0]dout inv of CRC */
    uint32_t dout_ref : 1;    /*!< [1]dout ref of CRC */
    uint32_t din_ref  : 1;    /*!< [2]din ref of CRC */
    uint32_t          : 29;   /*!< [31:3]Reserved */
    uint32_t ivAndHash;       /*!< CRC hash and also used as iv in 1st block */
} __attribute__((aligned(4))) SEC_Eng_CRC_Link_Config_Type;

/**
 *  @brief SEC_ENG AES link config structure type definition
 */
typedef struct
{
    uint32_t              : 3;  /*!< [2:0]Reserved */
    uint32_t aesMode      : 2;  /*!< [4:3]128-bit/256-bit/192-bit/128-bit-double key mode select */
    uint32_t aesDecEn     : 1;  /*!< [5]Encode or decode */
    uint32_t aesDecKeySel : 1;  /*!< [6]Use new key or use same key as last one */
    uint32_t aesHwKeyEn   : 1;  /*!< [7]Enable or disable using hardware hey */
    uint32_t              : 1;  /*!< [8]Reserved */
    uint32_t aesIntClr    : 1;  /*!< [9]Clear interrupt */
    uint32_t aesIntSet    : 1;  /*!< [10]Set interrupt */
    uint32_t              : 1;  /*!< [11]Reserved */
    uint32_t aesBlockMode : 2;  /*!< [13:12]ECB/CTR/CBC mode select */
    uint32_t aesIVSel     : 1;  /*!< [14]Use new iv or use same iv as last one */
    uint32_t aesXTS       : 1;  /*!< [15]XTS mode select */
    uint32_t aesMsgLen    : 16; /*!< [31:16]Number of 128-bit block */
    uint32_t aesSrcAddr;        /*!< Message source address */
    uint32_t aesDstAddr;        /*!< Message destination address */
    uint32_t aesIV0;            /*!< Big endian initial vector(MSB) */
    uint32_t aesIV1;            /*!< Big endian initial vector */
    uint32_t aesIV2;            /*!< Big endian initial vector */
    uint32_t aesIV3;            /*!< Big endian initial vector(LSB)(CTR mode:counter initial value) */
    uint32_t aesKey0;           /*!< Big endian aes key(aes-128/256 key MSB) */
    uint32_t aesKey1;           /*!< Big endian aes key */
    uint32_t aesKey2;           /*!< Big endian aes key */
    uint32_t aesKey3;           /*!< Big endian aes key(aes-128 key LSB) */
    uint32_t aesKey4;           /*!< Big endian aes key */
    uint32_t aesKey5;           /*!< Big endian aes key */
    uint32_t aesKey6;           /*!< Big endian aes key */
    uint32_t aesKey7;           /*!< Big endian aes key(aes-256 key LSB) */
} __attribute__((aligned(4))) SEC_Eng_AES_Link_Config_Type;

/**
 *  @brief SEC_ENG AES XTS mode1 link config structure type definition
 */
typedef struct
{
    uint32_t              : 3;  /*!< [2:0]Reserved */
    uint32_t aesMode      : 2;  /*!< [4:3]128-bit/256-bit/192-bit/128-bit-double key mode select */
    uint32_t aesDecEn     : 1;  /*!< [5]Encode or decode */
    uint32_t aesDecKeySel : 1;  /*!< [6]Use new key or use same key as last one */
    uint32_t aesHwKeyEn   : 1;  /*!< [7]Enable or disable using hardware hey */
    uint32_t              : 1;  /*!< [8]Reserved */
    uint32_t aesIntClr    : 1;  /*!< [9]Clear interrupt */
    uint32_t aesIntSet    : 1;  /*!< [10]Set interrupt */
    uint32_t              : 1;  /*!< [11]Reserved */
    uint32_t aesBlockMode : 2;  /*!< [13:12]ECB/CTR/CBC mode select */
    uint32_t aesIVSel     : 1;  /*!< [14]Use new iv or use same iv as last one */
    uint32_t aesXTS       : 1;  /*!< [15]XTS mode select */
    uint32_t aesMsgLen    : 16; /*!< [31:16]Number of 128-bit block */
    uint32_t aesSrcAddr;        /*!< Message source address */
    uint32_t aesDstAddr;        /*!< Message destination address */
    uint32_t aesIV0;            /*!< Big endian initial vector(MSB) */
    uint32_t aesIV1;            /*!< Big endian initial vector */
    uint32_t aesIV2;            /*!< Big endian initial vector */
    uint32_t aesIV3;            /*!< Big endian initial vector(LSB)(CTR mode:counter initial value) */
    uint32_t aesKey10;          /*!< Big endian aes key1(aes-128/256 key MSB) */
    uint32_t aesKey11;          /*!< Big endian aes key1 */
    uint32_t aesKey12;          /*!< Big endian aes key1 */
    uint32_t aesKey13;          /*!< Big endian aes key1(aes-128 key LSB) */
    uint32_t aesKey14;          /*!< Big endian aes key1 */
    uint32_t aesKey15;          /*!< Big endian aes key1 */
    uint32_t aesKey16;          /*!< Big endian aes key1 */
    uint32_t aesKey17;          /*!< Big endian aes key1(aes-256 key LSB) */
    uint32_t            : 16;   /*!< [15:0]Reserved */
    uint32_t aesUnitLen : 16;   /*!< [31:16]Big endian aes unit len */
    uint32_t aesKey20;          /*!< Big endian aes key2(aes-128/256 key MSB) */
    uint32_t aesKey21;          /*!< Big endian aes key2 */
    uint32_t aesKey22;          /*!< Big endian aes key2 */
    uint32_t aesKey23;          /*!< Big endian aes key2(aes-128 key LSB) */
    uint32_t aesKey24;          /*!< Big endian aes key2 */
    uint32_t aesKey25;          /*!< Big endian aes key2 */
    uint32_t aesKey26;          /*!< Big endian aes key2 */
    uint32_t aesKey27;          /*!< Big endian aes key2(aes-256 key LSB) */
} __attribute__((aligned(4))) SEC_Eng_AES_XTS_Mode1_Link_Config_Type;

/**
 *  @brief SEC_ENG GMAC link config structure type definition
 */
typedef struct
{
    uint32_t            : 9;  /*!< [8:0]reserved */
    uint32_t gmacIntClr : 1;  /*!< [9]Clear interrupt */
    uint32_t gmacIntSet : 1;  /*!< [10]Set interrupt */
    uint32_t            : 5;  /*!< [15:11]reserved */
    uint32_t gmacMsgLen : 16; /*!< [31:16]Number of 128-bit block */
    uint32_t gmacSrcAddr;     /*!< Message source address */
    uint32_t gmacKey0;        /*!< GMAC key */
    uint32_t gmacKey1;        /*!< GMAC key */
    uint32_t gmacKey2;        /*!< GMAC key */
    uint32_t gmacKey3;        /*!< GMAC key */
    uint32_t result[4];       /*!< Result of GMAC */
} __attribute__((aligned(4))) SEC_Eng_GMAC_Link_Config_Type;

/**
 *  @brief SEC_ENG PKA status type definition
 */
typedef struct
{
    uint16_t primeFail   : 1; /*!< [0]Prime fail */
    uint16_t errUnknown  : 1; /*!< [1]Err unknown opc */
    uint16_t errOverflow : 1; /*!< [2]Err opq overflow */
    uint16_t errSrc2     : 1; /*!< [3]Err invalid src2 */
    uint16_t errSrc1     : 1; /*!< [4]Err invalid src1 */
    uint16_t errSrc0     : 1; /*!< [5]Err invalid src0 */
    uint16_t errDiv0     : 1; /*!< [6]Err div by 0 */
    uint16_t errFull     : 1; /*!< [7]Err cam full */
    uint16_t lastOpc     : 1; /*!< [8]Last opc */
    uint16_t opqFull     : 1; /*!< [9]Opq full */
    uint16_t cmdIndex    : 5; /*!< [14:10]Cmd err index */
    uint16_t errCmd      : 1; /*!< [15]Err cmd */
} SEC_Eng_PKA_Status_Type;

/*@} end of group SEC_ENG_Public_Types */

/** @defgroup  SEC_ENG_Public_Constants
 *  @{
 */

/** @defgroup  SEC_ENG_AES_ID_TYPE
 *  @{
 */
#define IS_SEC_ENG_AES_ID_TYPE(type) (((type) == SEC_ENG_AES_ID0))

/** @defgroup  SEC_ENG_SHA_ID_TYPE
 *  @{
 */
#define IS_SEC_ENG_SHA_ID_TYPE(type) (((type) == SEC_ENG_SHA_ID0))

/** @defgroup  SEC_ENG_SHA_TYPE
 *  @{
 */
#define IS_SEC_ENG_SHA_TYPE(type) (((type) == SEC_ENG_SHA256) ||     \
                                   ((type) == SEC_ENG_SHA224) ||     \
                                   ((type) == SEC_ENG_SHA1) ||       \
                                   ((type) == SEC_ENG_SHA1_RSVD) ||  \
                                   ((type) == SEC_ENG_SHA512) ||     \
                                   ((type) == SEC_ENG_SHA384) ||     \
                                   ((type) == SEC_ENG_SHA512T224) || \
                                   ((type) == SEC_ENG_SHA512T256) || \
                                   ((type) == SEC_ENG_MD5) ||        \
                                   ((type) == SEC_ENG_CRC16) ||      \
                                   ((type) == SEC_ENG_CRC32))

/** @defgroup  SEC_ENG_AES_TYPE
 *  @{
 */
#define IS_SEC_ENG_AES_TYPE(type) (((type) == SEC_ENG_AES_ECB) || \
                                   ((type) == SEC_ENG_AES_CTR) || \
                                   ((type) == SEC_ENG_AES_CBC) || \
                                   ((type) == SEC_ENG_AES_XTS))

/** @defgroup  SEC_ENG_AES_XTS_MODE_TYPE
 *  @{
 */
#define IS_SEC_ENG_AES_XTS_MODE_TYPE(type) (((type) == SEC_ENG_AES_XTS_MODE1) || \
                                            ((type) == SEC_ENG_AES_XTS_MODE2))

/** @defgroup  SEC_ENG_AES_KEY_TYPE
 *  @{
 */
#define IS_SEC_ENG_AES_KEY_TYPE(type) (((type) == SEC_ENG_AES_KEY_128BITS) || \
                                       ((type) == SEC_ENG_AES_KEY_256BITS) || \
                                       ((type) == SEC_ENG_AES_KEY_192BITS) || \
                                       ((type) == SEC_ENG_AES_DOUBLE_KEY_128BITS))

/** @defgroup  SEC_ENG_AES_COUNTER_TYPE
 *  @{
 */
#define IS_SEC_ENG_AES_COUNTER_TYPE(type) (((type) == SEC_ENG_AES_COUNTER_BYTE_4) || \
                                           ((type) == SEC_ENG_AES_COUNTER_BYTE_1) || \
                                           ((type) == SEC_ENG_AES_COUNTER_BYTE_2) || \
                                           ((type) == SEC_ENG_AES_COUNTER_BYTE_3))

/** @defgroup  SEC_ENG_AES_VALUEUSED_TYPE
 *  @{
 */
#define IS_SEC_ENG_AES_VALUEUSED_TYPE(type) (((type) == SEC_ENG_AES_USE_NEW) || \
                                             ((type) == SEC_ENG_AES_USE_OLD))

/** @defgroup  SEC_ENG_AES_KEY_SRC_TYPE
 *  @{
 */
#define IS_SEC_ENG_AES_KEY_SRC_TYPE(type) (((type) == SEC_ENG_AES_KEY_SW) || \
                                           ((type) == SEC_ENG_AES_KEY_HW))

/** @defgroup  SEC_ENG_AES_ENDEC_TYPE
 *  @{
 */
#define IS_SEC_ENG_AES_ENDEC_TYPE(type) (((type) == SEC_ENG_AES_ENCRYPTION) || \
                                         ((type) == SEC_ENG_AES_DECRYPTION))

/** @defgroup  SEC_ENG_PKA_REG_SIZE_TYPE
 *  @{
 */
#define IS_SEC_ENG_PKA_REG_SIZE_TYPE(type) (((type) == SEC_ENG_PKA_REG_SIZE_8) ||   \
                                            ((type) == SEC_ENG_PKA_REG_SIZE_16) ||  \
                                            ((type) == SEC_ENG_PKA_REG_SIZE_32) ||  \
                                            ((type) == SEC_ENG_PKA_REG_SIZE_64) ||  \
                                            ((type) == SEC_ENG_PKA_REG_SIZE_96) ||  \
                                            ((type) == SEC_ENG_PKA_REG_SIZE_128) || \
                                            ((type) == SEC_ENG_PKA_REG_SIZE_192) || \
                                            ((type) == SEC_ENG_PKA_REG_SIZE_256) || \
                                            ((type) == SEC_ENG_PKA_REG_SIZE_384) || \
                                            ((type) == SEC_ENG_PKA_REG_SIZE_512))

/** @defgroup  SEC_ENG_PKA_OP_TYPE
 *  @{
 */
#define IS_SEC_ENG_PKA_OP_TYPE(type) (((type) == SEC_ENG_PKA_OP_PPSEL) ||         \
                                      ((type) == SEC_ENG_PKA_OP_MOD2N) ||         \
                                      ((type) == SEC_ENG_PKA_OP_LDIV2N) ||        \
                                      ((type) == SEC_ENG_PKA_OP_LMUL2N) ||        \
                                      ((type) == SEC_ENG_PKA_OP_LDIV) ||          \
                                      ((type) == SEC_ENG_PKA_OP_LSQR) ||          \
                                      ((type) == SEC_ENG_PKA_OP_LMUL) ||          \
                                      ((type) == SEC_ENG_PKA_OP_LSUB) ||          \
                                      ((type) == SEC_ENG_PKA_OP_LADD) ||          \
                                      ((type) == SEC_ENG_PKA_OP_LCMP) ||          \
                                      ((type) == SEC_ENG_PKA_OP_MDIV2) ||         \
                                      ((type) == SEC_ENG_PKA_OP_MINV) ||          \
                                      ((type) == SEC_ENG_PKA_OP_MEXP) ||          \
                                      ((type) == SEC_ENG_PKA_OP_MSQR) ||          \
                                      ((type) == SEC_ENG_PKA_OP_MMUL) ||          \
                                      ((type) == SEC_ENG_PKA_OP_MREM) ||          \
                                      ((type) == SEC_ENG_PKA_OP_MSUB) ||          \
                                      ((type) == SEC_ENG_PKA_OP_MADD) ||          \
                                      ((type) == SEC_ENG_PKA_OP_RESIZE) ||        \
                                      ((type) == SEC_ENG_PKA_OP_MOVDAT) ||        \
                                      ((type) == SEC_ENG_PKA_OP_NLIR) ||          \
                                      ((type) == SEC_ENG_PKA_OP_SLIR) ||          \
                                      ((type) == SEC_ENG_PKA_OP_CLIR) ||          \
                                      ((type) == SEC_ENG_PKA_OP_CFLIRI_BUFFER) || \
                                      ((type) == SEC_ENG_PKA_OP_CTLIRI_PLD) ||    \
                                      ((type) == SEC_ENG_PKA_OP_CFLIR_BUFFER) ||  \
                                      ((type) == SEC_ENG_PKA_OP_CTLIR_PLD))

/** @defgroup  SEC_ENG_INT_TYPE
 *  @{
 */
#define IS_SEC_ENG_INT_TYPE(type) (((type) == SEC_ENG_INT_TRNG) || \
                                   ((type) == SEC_ENG_INT_AES) ||  \
                                   ((type) == SEC_ENG_INT_SHA) ||  \
                                   ((type) == SEC_ENG_INT_PKA) ||  \
                                   ((type) == SEC_ENG_INT_CDET) || \
                                   ((type) == SEC_ENG_INT_GMAC) || \
                                   ((type) == SEC_ENG_INT_ALL))

/*@} end of group SEC_ENG_Public_Constants */

/** @defgroup  SEC_ENG_Public_Macros
 *  @{
 */
#define SEC_ENG_PKA_STATUS_LAST_OPC_OFFSET 24
#define SEC_ENG_PKA_STATUS_LAST_OPC_MASK   0x01000000

/*@} end of group SEC_ENG_Public_Macros */

/** @defgroup  SEC_ENG_Public_Functions
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
void SEC_GMAC_IRQHandler(void);
void SEC_CDET_IRQHandler(void);
void SEC_TRNG_IRQHandler(void);
void SEC_PKA_IRQHandler(void);
void SEC_AES_IRQHandler(void);
void SEC_SHA_IRQHandler(void);
#endif
void Sec_Eng_SHA256_Init(SEC_Eng_SHA256_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, SEC_ENG_SHA_Type shaType,
                         uint32_t shaTmpBuf[16], uint32_t padding[16]);
void Sec_Eng_SHA512_Init(SEC_Eng_SHA512_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, SEC_ENG_SHA_Type shaType,
                         uint64_t shaTmpBuf[16], uint64_t padding[16]);
void Sec_Eng_MD5_Init(SEC_Eng_MD5_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, SEC_ENG_SHA_Type shaType,
                      uint32_t md5TmpBuf[16], uint32_t padding[16]);
void Sec_Eng_SHA_Start(SEC_ENG_SHA_ID_Type shaNo);
BL_Err_Type Sec_Eng_SHA256_Update(SEC_Eng_SHA256_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, const uint8_t *input,
                                  uint32_t len);
BL_Err_Type Sec_Eng_SHA512_Update(SEC_Eng_SHA512_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, const uint8_t *input,
                                  uint64_t len);
BL_Err_Type Sec_Eng_MD5_Update(SEC_Eng_MD5_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, const uint8_t *input,
                               uint32_t len);
BL_Err_Type Sec_Eng_SHA256_Finish(SEC_Eng_SHA256_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint8_t *hash);
BL_Err_Type Sec_Eng_SHA512_Finish(SEC_Eng_SHA512_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint8_t *hash);
BL_Err_Type Sec_Eng_MD5_Finish(SEC_Eng_MD5_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, uint8_t *hash);
void Sec_Eng_SHA_Enable_Link(SEC_ENG_SHA_ID_Type shaNo);
void Sec_Eng_SHA_Disable_Link(SEC_ENG_SHA_ID_Type shaNo);
void Sec_Eng_SHA256_Link_Init(SEC_Eng_SHA256_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr,
                              uint32_t shaTmpBuf[16], uint32_t padding[16]);
void Sec_Eng_SHA512_Link_Init(SEC_Eng_SHA512_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr,
                              uint64_t shaTmpBuf[16], uint64_t padding[16]);
void Sec_Eng_MD5_Link_Init(SEC_Eng_MD5_Link_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr,
                           uint32_t md5TmpBuf[16], uint32_t padding[16]);
void Sec_Eng_Set_MD5_Din(SEC_ENG_AES_ID_Type aesNo);
void Sec_Eng_Set_MD5_Din_Be(SEC_ENG_AES_ID_Type aesNo);
void Sec_Eng_Set_MD5_Dout(SEC_ENG_AES_ID_Type aesNo);
void Sec_Eng_Set_MD5_Dout_BE(SEC_ENG_AES_ID_Type aesNo);
BL_Err_Type Sec_Eng_SHA256_Link_Update(SEC_Eng_SHA256_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo,
                                       const uint8_t *input, uint32_t len);
BL_Err_Type Sec_Eng_SHA512_Link_Update(SEC_Eng_SHA512_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo,
                                       const uint8_t *input, uint64_t len);
BL_Err_Type Sec_Eng_MD5_Link_Update(SEC_Eng_MD5_Link_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo,
                                    const uint8_t *input, uint32_t len);
BL_Err_Type Sec_Eng_SHA256_Link_Finish(SEC_Eng_SHA256_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo,
                                       uint8_t *hash);
BL_Err_Type Sec_Eng_SHA512_Link_Finish(SEC_Eng_SHA512_Link_Ctx *shaCtx, SEC_ENG_SHA_ID_Type shaNo,
                                       uint8_t *hash);
BL_Err_Type Sec_Eng_MD5_Link_Finish(SEC_Eng_MD5_Link_Ctx *md5Ctx, SEC_ENG_SHA_ID_Type shaNo,
                                    uint8_t *hash);
BL_Err_Type Sec_Eng_Group0_Request_SHA_Access(void);
BL_Err_Type Sec_Eng_Group0_Release_SHA_Access(void);
BL_Err_Type Sec_Eng_Group1_Request_SHA_Access(void);
BL_Err_Type Sec_Eng_Group1_Release_SHA_Access(void);
BL_Err_Type Sec_Eng_AES_Init(SEC_Eng_AES_Ctx *aesCtx, SEC_ENG_AES_ID_Type aesNo, SEC_ENG_AES_Type aesType,
                             SEC_ENG_AES_Key_Type keyType, SEC_ENG_AES_EnDec_Type enDecType);
void Sec_Eng_AES_Enable_LE(SEC_ENG_AES_ID_Type aesNo);
void Sec_Eng_AES_Enable_BE(SEC_ENG_AES_ID_Type aesNo);
void Sec_Eng_AES_Enable_Link(SEC_ENG_AES_ID_Type aesNo);
void Sec_Eng_AES_Disable_Link(SEC_ENG_AES_ID_Type aesNo);
BL_Err_Type Sec_Eng_CRC16_Link_Work(SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr, const uint8_t *in, uint32_t len,
                                    uint8_t *out);
BL_Err_Type Sec_Eng_CRC32_Link_Work(SEC_ENG_SHA_ID_Type shaNo, uint32_t linkAddr, const uint8_t *in, uint32_t len,
                                    uint8_t *out);
BL_Err_Type Sec_Eng_AES_Link_Work(SEC_ENG_AES_ID_Type aesNo, uint32_t linkAddr, const uint8_t *in, uint32_t len,
                                  uint8_t *out);
void Sec_Eng_AES_Set_Hw_Key_Src(SEC_ENG_AES_ID_Type aesNo, uint8_t src);
void Sec_Eng_AES_Set_Key_IV(SEC_ENG_AES_ID_Type aesNo, SEC_ENG_AES_Key_Src_Type keySrc, const uint8_t *key,
                            const uint8_t *iv);
void Sec_Eng_AES_Set_Key_IV_BE(SEC_ENG_AES_ID_Type aesNo, SEC_ENG_AES_Key_Src_Type keySrc, const uint8_t *key,
                               const uint8_t *iv);
void Sec_Eng_AES_Set_Counter_Byte(SEC_ENG_AES_ID_Type aesNo, SEC_ENG_AES_Counter_Type counterType);
BL_Err_Type Sec_Eng_AES_Crypt(SEC_Eng_AES_Ctx *aesCtx, SEC_ENG_AES_ID_Type aesNo, const uint8_t *in, uint32_t len,
                              uint8_t *out);
BL_Err_Type Sec_Eng_AES_Finish(SEC_ENG_AES_ID_Type aesNo);
BL_Err_Type Sec_Eng_Group0_Request_AES_Access(void);
BL_Err_Type Sec_Eng_Group0_Release_AES_Access(void);
BL_Err_Type Sec_Eng_Group1_Request_AES_Access(void);
BL_Err_Type Sec_Eng_Group1_Release_AES_Access(void);
BL_Err_Type Sec_Eng_Trng_Enable(void);
void Sec_Eng_Trng_Int_Enable(void);
void Sec_Eng_Trng_Int_Disable(void);
BL_Err_Type Sec_Eng_Trng_Read(uint8_t data[32]);
BL_Err_Type Sec_Eng_Trng_Get_Random(uint8_t *data, uint32_t len);
void Sec_Eng_Trng_Int_Read_Trigger(void);
void Sec_Eng_Trng_Int_Read(uint8_t data[32]);
void Sec_Eng_Trng_Disable(void);
BL_Err_Type Sec_Eng_Group0_Request_Trng_Access(void);
BL_Err_Type Sec_Eng_Group0_Release_Trng_Access(void);
BL_Err_Type Sec_Eng_Group1_Request_Trng_Access(void);
BL_Err_Type Sec_Eng_Group1_Release_Trng_Access(void);
void Sec_Eng_PKA_Reset(void);
void Sec_Eng_PKA_BigEndian_Enable(void);
void Sec_Eng_PKA_LittleEndian_Enable(void);
void Sec_Eng_PKA_GetStatus(SEC_Eng_PKA_Status_Type *status);
void Sec_Eng_PKA_Write_Data(SEC_ENG_PKA_REG_SIZE_Type regType, uint8_t regIndex, const uint32_t *data, uint16_t size,
                            uint8_t lastOp);
void Sec_Eng_PKA_Read_Data(SEC_ENG_PKA_REG_SIZE_Type regType, uint8_t regIdx, uint32_t *result, uint8_t retSize);
void Sec_Eng_PKA_CREG(SEC_ENG_PKA_REG_SIZE_Type dRegType, uint8_t dRegIdx, uint8_t size, uint8_t lastOp);
void Sec_Eng_PKA_Write_Immediate(SEC_ENG_PKA_REG_SIZE_Type regType, uint8_t regIndex, uint32_t data, uint8_t lastOp);
void Sec_Eng_PKA_NREG(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_Move_Data(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_RESIZE(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_MADD(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType,
                      uint8_t s1RegIdx, uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_MSUB(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType,
                      uint8_t s1RegIdx, uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_MREM(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s2RegType,
                      uint8_t s2RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_MMUL(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType,
                      uint8_t s1RegIdx, uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_MSQR(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s2RegType,
                      uint8_t s2RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_MEXP(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType,
                      uint8_t s1RegIdx, uint8_t s2RegType, uint8_t s2RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_MINV(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s2RegType,
                      uint8_t s2RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_MINV(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s2RegType,
                      uint8_t s2RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_LCMP(uint8_t *cout, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t s1RegType, uint8_t s1RegIdx);
void Sec_Eng_PKA_LADD(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType,
                      uint8_t s1RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_LSUB(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType,
                      uint8_t s1RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_LMUL(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s1RegType,
                      uint8_t s1RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_LSQR(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_LDIV(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                      uint8_t s2RegType,
                      uint8_t s2RegIdx, uint8_t lastOp);
void Sec_Eng_PKA_LMUL2N(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                        uint16_t bit_shift,
                        uint8_t lastOp);
void Sec_Eng_PKA_LDIV2N(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                        uint16_t bit_shift,
                        uint8_t lastOp);
void Sec_Eng_PKA_LMOD2N(uint8_t dRegType, uint8_t dRegIdx, uint8_t s0RegType, uint8_t s0RegIdx,
                        uint16_t bit_shift,
                        uint8_t lastOp);
void Sec_Eng_PKA_GF2Mont(uint8_t dRegType, uint8_t dRegIdx, uint8_t sRegType, uint8_t sRegIdx, uint32_t size,
                         uint8_t tRegType, uint8_t tRegIdx, uint8_t pRegType, uint8_t pRegIdx);
void Sec_Eng_PKA_Mont2GF(uint8_t dRegType, uint8_t dRegIdx, uint8_t aRegType, uint8_t aRegIdx, uint8_t invrRegType,
                         uint8_t invrRegIdx,
                         uint8_t tRegType, uint8_t tRegIdx, uint8_t pRegType, uint8_t pRegIdx);
BL_Err_Type Sec_Eng_Group0_Request_PKA_Access(void);
BL_Err_Type Sec_Eng_Group0_Release_PKA_Access(void);
BL_Err_Type Sec_Eng_Group1_Request_PKA_Access(void);
BL_Err_Type Sec_Eng_Group1_Release_PKA_Access(void);
void Sec_Eng_GMAC_Enable_LE(void);
void Sec_Eng_GMAC_Enable_BE(void);
void Sec_Eng_GMAC_Enable_Link(void);
void Sec_Eng_GMAC_Disable_Link(void);
BL_Err_Type Sec_Eng_GMAC_Link_Work(uint32_t linkAddr, const uint8_t *in, uint32_t len, uint8_t *out);
BL_Err_Type Sec_Eng_Group0_Request_GMAC_Access(void);
BL_Err_Type Sec_Eng_Group0_Release_GMAC_Access(void);
BL_Err_Type Sec_Eng_Group1_Request_GMAC_Access(void);
BL_Err_Type Sec_Eng_Group1_Release_GMAC_Access(void);
void SEC_Eng_IntMask(SEC_ENG_INT_Type intType, BL_Mask_Type intMask);
void SEC_Eng_ClrIntStatus(SEC_ENG_INT_Type intType);
void SEC_Eng_Int_Callback_Install(SEC_ENG_INT_Type intType, intCallback_Type *cbFun);
BL_Sts_Type SEC_Eng_GetIntStatus(SEC_ENG_INT_Type intType);
/*----------*/
void SEC_Eng_Turn_On_Sec_Ring(void);
void SEC_Eng_Turn_Off_Sec_Ring(void);
void Sec_Eng_PKA_Clear_Int(void);
void Sec_Eng_PKA_Read_Block(uint32_t *dest, const uint32_t *src, uint32_t len);
void Sec_Eng_PKA_Read_Block(uint32_t *dest, const uint32_t *src, uint32_t len);
void Sec_Eng_PKA_Write_Block(uint32_t *dest, const uint32_t *src, uint32_t len);
void Sec_Eng_PKA_Write_Block(uint32_t *dest, const uint32_t *src, uint32_t len);
/*----------*/;

/*@} end of group SEC_ENG_Public_Functions */

/*@} end of group SEC_ENG */

/*@} end of group BL808_Peripheral_Driver */

#endif /* __BL808_SEC_ENG_H__ */
