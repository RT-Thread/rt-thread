/*!
 * @file        apm32f4xx_cryp_aes.c
 *
 * @brief       This file provides high level functions to encrypt and decrypt,
 *              Input message using AES in ECB/CBC/CTR modes.
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

#include "apm32f4xx_cryp.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup CRYP_AES_Driver
  * @brief CRYP AES driver modules
  @{
*/

/** @defgroup CRYP_AES_Functions
  @{
*/

/*!
 * @brief     Encrypt and decrypt using AES in EBC Mode
 *
 * @param     mode: Pointer to a CRYP_MODE_T structure.
 *            This parameter can be one of the following values:
 *                @arg CRYP_MODE_DECRYPT: Encryption
 *                @arg CRYP_MODE_ENCRYPT: Decryption
 *
 * @param     key:     Key used for AES algorithm.
 * @param     keysize: length of the Key, must be a 128, 192 or 256.
 * @param     input:   Input buffer.
 * @param     length:  length of the Input buffer, must be a multiple of 16.
 * @param     output:  Output buffer.
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t CRYP_AES_ECB(CRYP_MODE_T mode, uint8_t *key,    uint16_t keysize,
                       uint8_t *input, uint32_t length, uint8_t  *output)
{
    CRYP_Config_T    AES_crypConfig;
    CRYP_KeyConfig_T AES_keyConfig;

    uint32_t keyAddr    = (uint32_t)key;
    uint32_t inputAddr  = (uint32_t)input;
    uint32_t outputAddr = (uint32_t)output;

    uint32_t i = 0;
    uint32_t flag = 0;
    uint32_t status = SUCCESS;
    __IO uint32_t counter = 0;

    CRYP_ConfigKeyStructInit(&AES_keyConfig);

    switch(keysize)
    {
        case 128:
        AES_crypConfig.keySize = CRYP_KEYSIZE_128B;
        AES_keyConfig.key2Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Right = __REV(*(uint32_t*)(keyAddr));
        break;

        case 192:
        AES_crypConfig.keySize = CRYP_KEYSIZE_192B;
        AES_keyConfig.key1Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key1Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Right = __REV(*(uint32_t*)(keyAddr));
        break;

        case 256:
        AES_crypConfig.keySize = CRYP_KEYSIZE_256B;
        AES_keyConfig.key0Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key0Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key1Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key1Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Right = __REV(*(uint32_t*)(keyAddr));
        break;

        default:
        break;
    }

    if(mode == CRYP_MODE_DECRYPT)
    {
        CRYP_FlushFIFO();

        AES_crypConfig.algoDir  = CRYP_ALGODIR_DECRYPT;
        AES_crypConfig.algoMode = CRYP_ALGOMODE_AES_KEY;
        AES_crypConfig.dataType = CRYP_DATATYPE_32B;
        CRYP_Config(&AES_crypConfig);
        CRYP_ConfigKey(&AES_keyConfig);
        CRYP_Enable();

        counter = 0;
        do
        {
            flag = CRYP_ReadStatusFlag(CRYP_FLAG_BUSY);
            counter++;
        }
        while((counter != 0x00010000) && (flag != RESET));

        if(flag == SET)
        {
            status = ERROR;
        }
        else
        {
            AES_crypConfig.algoDir = CRYP_ALGODIR_DECRYPT;
        }
    }
    else
    {
        CRYP_ConfigKey(&AES_keyConfig);
        AES_crypConfig.algoDir = CRYP_ALGODIR_ENCRYPT;
    }

    AES_crypConfig.algoMode = CRYP_ALGOMODE_AES_ECB;
    AES_crypConfig.dataType = CRYP_DATATYPE_8B,
    CRYP_Config(&AES_crypConfig);

    CRYP_FlushFIFO();
    CRYP_Enable();

    if(CRYP_ReadCmdStatus() == DISABLE)
    {
        status = ERROR;
    }

    for(i=0; i<length; i+=16)
    {
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;

        counter = 0;
        do
        {
            flag = CRYP_ReadStatusFlag(CRYP_FLAG_BUSY);
            counter++;
        }
        while((counter != 0x00010000) && (flag != RESET));

        if(flag == SET)
        {
            status = ERROR;
        }
        else
        {
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
        }
    }
    CRYP_Disable();
    return status;
}

/*!
 * @brief     Encrypt and decrypt using AES in CBC Mode
 *
 * @param     mode: Pointer to a CRYP_MODE_T structure.
 *            This parameter can be one of the following values:
 *                @arg CRYP_MODE_DECRYPT: Encryption
 *                @arg CRYP_MODE_ENCRYPT: Decryption
 *
 * @param     key:     Key used for AES algorithm.
 * @param     keysize: length of the Key, must be a 128, 192 or 256.
 * @param     IV:      Initialisation Vectors used for AES algorithm.
 * @param     input:   Input buffer.
 * @param     length:  length of the Input buffer, must be a multiple of 16.
 * @param     output:  Output buffer.
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t CRYP_AES_CBC(CRYP_MODE_T mode, uint8_t *key,    uint16_t keysize,
                                       uint8_t IV[16],  uint8_t  *input,
                                       uint32_t length, uint8_t  *output)
{
    CRYP_Config_T    AES_crypConfig;
    CRYP_KeyConfig_T AES_keyConfig;
    CRYP_IVConfig_T  AES_IVConfig;

    uint32_t keyAddr    = (uint32_t)key;
    uint32_t inputAddr  = (uint32_t)input;
    uint32_t outputAddr = (uint32_t)output;
    uint32_t IVAddr     = (uint32_t)IV;

    uint32_t i = 0;
    uint32_t flag = 0;
    uint32_t status = SUCCESS;
    __IO uint32_t counter = 0;

    CRYP_ConfigKeyStructInit(&AES_keyConfig);

    switch(keysize)
    {
        case 128:
        AES_crypConfig.keySize = CRYP_KEYSIZE_128B;
        AES_keyConfig.key2Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Right = __REV(*(uint32_t*)(keyAddr));
        break;

        case 192:
        AES_crypConfig.keySize = CRYP_KEYSIZE_192B;
        AES_keyConfig.key1Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key1Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Right = __REV(*(uint32_t*)(keyAddr));
        break;

        case 256:
        AES_crypConfig.keySize = CRYP_KEYSIZE_256B;
        AES_keyConfig.key0Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key0Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key1Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key1Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Right = __REV(*(uint32_t*)(keyAddr));
        break;

        default:
        break;
    }

    AES_IVConfig.IV0Left  = __REV(*(uint32_t*)(IVAddr));
    keyAddr += 0x04;
    AES_IVConfig.IV0Right = __REV(*(uint32_t*)(IVAddr));
    keyAddr += 0x04;
    AES_IVConfig.IV1Left  = __REV(*(uint32_t*)(IVAddr));
    keyAddr += 0x04;
    AES_IVConfig.IV1Right = __REV(*(uint32_t*)(IVAddr));

    if(mode == CRYP_MODE_DECRYPT)
    {
        CRYP_FlushFIFO();

        AES_crypConfig.algoDir  = CRYP_ALGODIR_DECRYPT;
        AES_crypConfig.algoMode = CRYP_ALGOMODE_AES_KEY;
        AES_crypConfig.dataType = CRYP_DATATYPE_32B;
        CRYP_Config(&AES_crypConfig);
        CRYP_ConfigKey(&AES_keyConfig);
        CRYP_Enable();

        counter = 0;
        do
        {
            flag = CRYP_ReadStatusFlag(CRYP_FLAG_BUSY);
            counter++;
        }
        while((counter != 0x00010000) && (flag != RESET));

        if(flag == SET)
        {
            status = ERROR;
        }
        else
        {
            AES_crypConfig.algoDir = CRYP_ALGODIR_DECRYPT;
        }
    }
    else
    {
        CRYP_ConfigKey(&AES_keyConfig);
        AES_crypConfig.algoDir = CRYP_ALGODIR_ENCRYPT;
    }

    AES_crypConfig.algoMode = CRYP_ALGOMODE_AES_CBC;
    AES_crypConfig.dataType = CRYP_DATATYPE_8B,
    CRYP_Config(&AES_crypConfig);
    CRYP_ConfigIV(&AES_IVConfig);
    CRYP_FlushFIFO();
    CRYP_Enable();

    if(CRYP_ReadCmdStatus() == DISABLE)
    {
        status = ERROR;
    }

    for(i=0; i<length; i+=16)
    {
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;

        counter = 0;
        do
        {
            flag = CRYP_ReadStatusFlag(CRYP_FLAG_BUSY);
            counter++;
        }
        while((counter != 0x00010000) && (flag != RESET));

        if(flag == SET)
        {
            status = ERROR;
        }
        else
        {
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
        }
    }
    CRYP_Disable();
    return status;
}

/*!
 * @brief     Encrypt and decrypt using AES in CTR Mode
 *
 * @param     mode: Pointer to a CRYP_MODE_T structure.
 *            This parameter can be one of the following values:
 *                @arg CRYP_MODE_DECRYPT: Encryption
 *                @arg CRYP_MODE_ENCRYPT: Decryption
 *
 * @param     key:     Key used for AES algorithm.
 * @param     keysize: length of the Key, must be a 128, 192 or 256.
 * @param     IV:      Initialisation Vectors used for AES algorithm.
 * @param     input:   Input buffer.
 * @param     length:  length of the Input buffer, must be a multiple of 16.
 * @param     output:  Output buffer.
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t CRYP_AES_CTR(CRYP_MODE_T mode, uint8_t  *key,   uint16_t keysize,
                                       uint8_t  IV[16], uint8_t  *input,
                                       uint32_t length, uint8_t  *output)
{
    CRYP_Config_T    AES_crypConfig;
    CRYP_KeyConfig_T AES_keyConfig;
    CRYP_IVConfig_T  AES_IVConfig;

    uint32_t keyAddr    = (uint32_t)key;
    uint32_t inputAddr  = (uint32_t)input;
    uint32_t outputAddr = (uint32_t)output;
    uint32_t IVAddr     = (uint32_t)IV;

    uint32_t i = 0;
    uint32_t flag = 0;
    uint32_t status = SUCCESS;
    __IO uint32_t counter = 0;

    CRYP_ConfigKeyStructInit(&AES_keyConfig);

    switch(keysize)
    {
        case 128:
        AES_crypConfig.keySize = CRYP_KEYSIZE_128B;
        AES_keyConfig.key2Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Right = __REV(*(uint32_t*)(keyAddr));
        break;

        case 192:
        AES_crypConfig.keySize = CRYP_KEYSIZE_192B;
        AES_keyConfig.key1Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key1Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Right = __REV(*(uint32_t*)(keyAddr));
        break;

        case 256:
        AES_crypConfig.keySize = CRYP_KEYSIZE_256B;
        AES_keyConfig.key0Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key0Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key1Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key1Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key2Right = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Left  = __REV(*(uint32_t*)(keyAddr));
        keyAddr += 0x04;
        AES_keyConfig.key3Right = __REV(*(uint32_t*)(keyAddr));
        break;

        default:
        break;
    }

    AES_IVConfig.IV0Left  = __REV(*(uint32_t*)(IVAddr));
    keyAddr += 0x04;
    AES_IVConfig.IV0Right = __REV(*(uint32_t*)(IVAddr));
    keyAddr += 0x04;
    AES_IVConfig.IV1Left  = __REV(*(uint32_t*)(IVAddr));
    keyAddr += 0x04;
    AES_IVConfig.IV1Right = __REV(*(uint32_t*)(IVAddr));

    CRYP_ConfigKey(&AES_keyConfig);

    if(mode == CRYP_MODE_DECRYPT)
    {
        AES_crypConfig.algoDir  = CRYP_ALGODIR_DECRYPT;
    }
    else
    {
        AES_crypConfig.algoDir = CRYP_ALGODIR_ENCRYPT;
    }

    AES_crypConfig.algoMode = CRYP_ALGOMODE_AES_CTR;
    AES_crypConfig.dataType = CRYP_DATATYPE_8B,

    CRYP_Config(&AES_crypConfig);
    CRYP_ConfigIV(&AES_IVConfig);
    CRYP_FlushFIFO();
    CRYP_Enable();

    if(CRYP_ReadCmdStatus() == DISABLE)
    {
        status = ERROR;
    }

    for(i=0; i<length; i+=16)
    {
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;
        CRYP_InData(*(uint32_t*)(inputAddr));
        inputAddr += 0x04;

        counter = 0;
        do
        {
            flag = CRYP_ReadStatusFlag(CRYP_FLAG_BUSY);
            counter++;
        }
        while((counter != 0x00010000) && (flag != RESET));

        if(flag == SET)
        {
            status = ERROR;
        }
        else
        {
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
            *(uint32_t*)(outputAddr) = CRYP_OutData();
            outputAddr += 0x04;
        }
    }
    CRYP_Disable();
    return status;
}

/**@} end of group CRYP_AES_Functions */
/**@} end of group CRYP_AES_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
