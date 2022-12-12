/*!
 * @file        apm32f4xx_cryp.h
 *
 * @brief       This file contains all the functions prototypes for the CRYP firmware library
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Define to prevent recursive inclusion */
#ifndef __APM32F4XX_CRYP_H
#define __APM32F4XX_CRYP_H

#ifdef __cplusplus
  extern "C" {
#endif

/* Includes */
#include "apm32f4xx.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @addtogroup CRYP_Driver
  @{
*/

/** @defgroup CRYP_Enumerations
  @{
*/

/**
 * @brief CRYP Algorithm Direction
 */
typedef enum
{
    CRYP_ALGODIR_ENCRYPT,   /*!< Encryption */
    CRYP_ALGODIR_DECRYPT    /*!< Decryption */
} CRYP_ALGODIR_T;

/**
 * @brief CRYP Algorithm Mode
 */
typedef enum
{
    CRYP_ALGOMODE_TDES_ECB = 0x00,  /*!< TDES ECB Mode */
    CRYP_ALGOMODE_TDES_CBC = 0x01,  /*!< TDES CBC Mode */
    CRYP_ALGOMODE_DES_ECB  = 0x02,  /*!< DES ECB Mode */
    CRYP_ALGOMODE_DES_CBC  = 0x03,  /*!< DES CBC Mode */
    CRYP_ALGOMODE_AES_ECB  = 0x04,  /*!< AES ECB Mode */
    CRYP_ALGOMODE_AES_CBC  = 0x05,  /*!< AES CBC Mode */
    CRYP_ALGOMODE_AES_CTR  = 0x06,  /*!< AES CTR Mode */
    CRYP_ALGOMODE_AES_KEY  = 0x07   /*!< AES KEY Mode */
} CRYP_ALGOMODE_T;

/**
 * @brief CRYP Data Type
 */
typedef enum
{
    CRYP_DATATYPE_32B,  /*!< 32-bit data */
    CRYP_DATATYPE_16B,  /*!< 16-bit or half-word data */
    CRYP_DATATYPE_8B,   /*!< 8-bit or byte data */
    CRYP_DATATYPE_1B    /*!< bit or bits */
} CRYP_DATATYPE_T;

/**
 * @brief CRYP Key Size (only AES)
 */
typedef enum
{
    CRYP_KEYSIZE_128B,  /*!< 128-bit key size */
    CRYP_KEYSIZE_192B,  /*!< 192-bit key size */
    CRYP_KEYSIZE_256B   /*!< 256-bit key size */
} CRYP_KEYSIZE_T;

/**
  * @brief CRYP flag
  */
typedef enum
{
    CRYP_FLAG_IFEMPT   =  0x01, /*!< Input FIFO Empty */
    CRYP_FLAG_IFFULL   =  0x02, /*!< Input FIFO not Full */
    CRYP_FLAG_OFEMPT   =  0x04, /*!< Output FIFO not Empty */
    CRYP_FLAG_OFFULL   =  0x08, /*!< Output FIFO Full */
    CRYP_FLAG_BUSY     =  0x10, /*!< Busy Bit */
    CRYP_FLAG_INISTS   =  0x21, /*!< Input FIFO Service Raw Interrupt Status */
    CRYP_FLAG_OUTISTS  =  0x22  /*!< Output FIFO Service Raw Interrupt Status */
} CRYP_FLAG_T;

/**
 * @brief CRYP interrupt
 */
typedef enum
{
    CRYP_INT_IN  = 0x01,    /*!< Input FIFO interrupt */
    CRYP_INT_OUT = 0x02     /*!< Output FIFO interrupt */
} CRYP_INT_T;

/**
 * @brief CRYP Encryption/Decryption_mode
 */
typedef enum
{
    CRYP_MODE_DECRYPT  = 0x00,  /*!< Encryption */
    CRYP_MODE_ENCRYPT  = 0x01   /*!< Decryption */
} CRYP_MODE_T;

/**
 * @brief CRYP DMA transfer request
 */
typedef enum
{
    CRYP_DMAREQ_DATAIN  =  0x01,    /*!< DMA Input Enable */
    CRYP_DMAREQ_DATAOUT =  0x02     /*!< DMA Output Enable */
} CRYP_DMAREQ_T;

/**@} end of group CRYP_Enumerations*/

/** @addtogroup CRYP_Structure Data Structure
  @{
*/

/**
 * @brief CRYP Config structure definition
 */
typedef struct
{
    CRYP_ALGODIR_T      algoDir;    /*!< Algorithm Direction Select */
    CRYP_ALGOMODE_T     algoMode;   /*!< Algorithm Mode Select */
    CRYP_DATATYPE_T     dataType;   /*!< Data Type Select */
    CRYP_KEYSIZE_T      keySize;    /*!< Key Size Select */
} CRYP_Config_T;

/**
 * @brief   CRYP KeyConfig structure definition
 */
typedef struct
{
    uint32_t          key0Left;     /*!< key0 left */
    uint32_t          key0Right;    /*!< key0 right */
    uint32_t          key1Left;     /*!< key1 left */
    uint32_t          key1Right;    /*!< key1 right */
    uint32_t          key2Left;     /*!< key2 left */
    uint32_t          key2Right;    /*!< key2 right */
    uint32_t          key3Left;     /*!< key3 left */
    uint32_t          key3Right;    /*!< key3 right */
} CRYP_KeyConfig_T;

/**
 * @brief   CRYP Initialization Vectors (IV) structure definition
 */
typedef struct
{
    uint32_t          IV0Left;      /*!< Initialization Vector0 left */
    uint32_t          IV0Right;     /*!< Initialization Vector0 right */
    uint32_t          IV1Left;      /*!< Initialization Vector1 left */
    uint32_t          IV1Right;     /*!< Initialization Vector1 right */
} CRYP_IVConfig_T;

/**
 * @brief  CRYP context swapping structure definition
 */
typedef struct
{
    /* Current Configuration */
    uint32_t    curCTRL;    /*!< Current Configuration */
    /* IV */
    uint32_t    IV0L;       /*!< Initialization Vector0 left */
    uint32_t    IV0R;       /*!< Initialization Vector0 right */
    uint32_t    IV1L;       /*!< Initialization Vector1 left */
    uint32_t    IV1R;       /*!< Initialization Vector1 right */
    /* KEY */
    uint32_t    K0L;        /*!< key0 left */
    uint32_t    K0R;        /*!< key0 right */
    uint32_t    K1L;        /*!< key1 left */
    uint32_t    K1R;        /*!< key1 right */
    uint32_t    K2L;        /*!< key2 left */
    uint32_t    K2R;        /*!< key2 right */
    uint32_t    K3L;        /*!< key3 left */
    uint32_t    K3R;        /*!< key3 right */
} CRYP_Context_T;

/**@} end of group CRYP_Structure*/

/** @defgroup CRYP_Functions
  @{
*/

/* CRYP Configuration */
void CRYP_Reset(void);
void CRYP_Config(CRYP_Config_T* crypConfig);
void CRYP_ConfigStructInit(CRYP_Config_T* crypConfig);
void CRYP_ConfigKey(CRYP_KeyConfig_T* keyConfig);
void CRYP_ConfigKeyStructInit(CRYP_KeyConfig_T* keyConfig);
void CRYP_ConfigIV(CRYP_IVConfig_T* IVConfig);
void CRYP_ConfigIVStructInit(CRYP_IVConfig_T* IVConfig);
void CRYP_Enable(void);
void CRYP_Disable(void);
void CRYP_FlushFIFO(void);

/* CRYP Data processing */
void CRYP_InData(uint32_t Data);
uint32_t CRYP_OutData(void);

/* CRYP Context swapping */
uint32_t CRYP_SaveContext(CRYP_Context_T* context, CRYP_KeyConfig_T* keyConfig);
void CRYP_RestoreContext(CRYP_Context_T* context);

/* CRYP DMA */
void CRYP_EnableDMA(CRYP_DMAREQ_T dmaReq);
void CRYP_DisableDMA(CRYP_DMAREQ_T dmaReq);

/* CRYP Interrupt and flag */
void CRYP_EnableInterrupt(uint8_t interrupt);
void CRYP_DisableInterrupt(uint8_t interrupt);
uint8_t CRYP_ReadIntFlag(CRYP_INT_T flag);
uint8_t CRYP_ReadStatusFlag(CRYP_FLAG_T flag);
uint8_t CRYP_ReadCmdStatus(void);

/* High Level AES */
uint8_t CRYP_AES_ECB(CRYP_MODE_T mode, uint8_t *key,    uint16_t keysize,
                       uint8_t *input, uint32_t length, uint8_t  *output);

uint8_t CRYP_AES_CBC(CRYP_MODE_T mode, uint8_t *key,    uint16_t keysize,
                                       uint8_t IV[16],  uint8_t  *input,
                                       uint32_t length, uint8_t  *output);

uint8_t CRYP_AES_CTR(CRYP_MODE_T mode, uint8_t  *key,   uint16_t keysize,
                                       uint8_t  IV[16], uint8_t  *input,
                                       uint32_t length, uint8_t  *output);

/* High Level DES */
uint8_t CRYP_DES_ECB(CRYP_MODE_T mode, uint8_t key[8], uint8_t *input,
                                      uint32_t length, uint8_t *output);

uint8_t CRYP_DES_CBC(CRYP_MODE_T mode, uint8_t key[8],  uint8_t *input,
                        uint8_t IV[8], uint32_t length, uint8_t *output);

/* High Level TDES */
uint8_t CRYP_TDES_ECB(CRYP_MODE_T mode, uint8_t key[24], uint8_t *input,
                                       uint32_t length,  uint8_t *output);

uint8_t CRYP_TDES_CBC(CRYP_MODE_T mode,uint8_t key[24], uint8_t *input,
                        uint8_t IV[8], uint32_t length, uint8_t *output);

#ifdef __cplusplus
}
#endif

#endif /* __APM32F4XX_CRYP_H */

/**@} end of group CRYP_Enumerations */
/**@} end of group CRYP_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
