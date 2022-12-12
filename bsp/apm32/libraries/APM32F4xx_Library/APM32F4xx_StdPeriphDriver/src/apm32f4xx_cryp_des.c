/*!
 * @file        apm32f4xx_cryp_des.c
 *
 * @brief       This file provides high level functions to encrypt and decrypt,
 *              Input message using DES in ECB/CBC modes.
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

/** @defgroup CRYP_DES_Driver
  * @brief CRYP DES driver modules
  @{
*/

/** @defgroup CRYP_DES_Functions
  @{
*/

/*!
 * @brief     Encrypt and decrypt using DES in EBC Mode
 *
 * @param     mode: Pointer to a CRYP_MODE_T structure.
 *            This parameter can be one of the following values:
 *                @arg CRYP_MODE_DECRYPT: Encryption
 *                @arg CRYP_MODE_ENCRYPT: Decryption
 *
 * @param     key:    Key used for DES algorithm.
 * @param     input:  Input buffer.
 * @param     length: length of the Input buffer, must be a multiple of 8.
 * @param     output: Output buffer.
 *
 * @retval    SUCCESS or ERROR
 */
uint8_t CRYP_DES_ECB(CRYP_MODE_T mode, uint8_t key[8], uint8_t *input,
                     uint32_t length, uint8_t *output)
{
    CRYP_Config_T    DEC_crypConfig;
    CRYP_KeyConfig_T DEC_keyConfig;

    uint32_t keyAddr    = (uint32_t)key;
    uint32_t inputAddr  = (uint32_t)input;
    uint32_t outputAddr = (uint32_t)output;

    uint32_t i = 0;
    uint32_t flag = 0;
    uint32_t status = SUCCESS;
    __IO uint32_t counter = 0;

    CRYP_ConfigKeyStructInit(&DEC_keyConfig);

    if (mode == CRYP_MODE_ENCRYPT)
    {
        DEC_crypConfig.algoDir = CRYP_ALGODIR_ENCRYPT;
    }
    else
    {
        DEC_crypConfig.algoDir = CRYP_ALGODIR_DECRYPT;
    }
    DEC_crypConfig.algoMode = CRYP_ALGOMODE_DES_ECB;
    DEC_crypConfig.dataType = CRYP_DATATYPE_8B;
    CRYP_Config(&DEC_crypConfig);

    DEC_keyConfig.key1Left = __REV(*(uint32_t *)(keyAddr));
    keyAddr += 0x04;
    DEC_keyConfig.key1Right = __REV(*(uint32_t *)(keyAddr));
    CRYP_ConfigKey(&DEC_keyConfig);

    CRYP_FlushFIFO();
    CRYP_Enable();

    if (CRYP_ReadCmdStatus() == DISABLE)
    {
        status = ERROR;
    }
    else
    {
        for (i = 0; i < length; i += 8)
        {
            CRYP_InData(*(uint32_t *)(inputAddr));
            inputAddr += 0x04;
            CRYP_InData(*(uint32_t *)(inputAddr));
            inputAddr += 0x04;

            counter = 0;
            do
            {
                flag = CRYP_ReadStatusFlag(CRYP_FLAG_BUSY);
                counter++;
            }
            while ((counter != 0x00010000) && (flag != RESET));

            if (flag == SET)
            {
                status = ERROR;
            }
            else
            {
                *(uint32_t *)(outputAddr) = CRYP_OutData();
                outputAddr += 0x04;
                *(uint32_t *)(outputAddr) = CRYP_OutData();
                outputAddr += 0x04;
            }
        }
        CRYP_Disable();
    }
    return status;
}

/*!
 * @brief     Encrypt and decrypt using DES in CBC Mode
 *
 * @param     mode: Pointer to a CRYP_MODE_T structure.
 *            This parameter can be one of the following values:
 *                @arg CRYP_MODE_DECRYPT: Encryption
 *                @arg CRYP_MODE_ENCRYPT: Decryption
 *
 * @param     key:    Key used for DES algorithm.
 * @param     input:  Input buffer.
 * @param     IV:     Initialisation Vectors used for DES algorithm.
 * @param     length: length of the Input buffer, must be a multiple of 8.
 * @param     output: Output buffer.
 *
 * @retval    None
 */
uint8_t CRYP_DES_CBC(CRYP_MODE_T mode, uint8_t key[8],  uint8_t *input,
                     uint8_t IV[8], uint32_t length, uint8_t *output)
{
    CRYP_Config_T    DEC_crypConfig;
    CRYP_KeyConfig_T DEC_keyConfig;
    CRYP_IVConfig_T  DEC_IVConfig;

    uint32_t keyAddr    = (uint32_t)key;
    uint32_t inputAddr  = (uint32_t)input;
    uint32_t outputAddr = (uint32_t)output;
    uint32_t IVAddr     = (uint32_t)IV;

    uint32_t i = 0;
    uint32_t flag = 0;
    uint32_t status = SUCCESS;
    __IO uint32_t counter = 0;

    CRYP_ConfigKeyStructInit(&DEC_keyConfig);

    if (mode == CRYP_MODE_ENCRYPT)
    {
        DEC_crypConfig.algoDir = CRYP_ALGODIR_ENCRYPT;
    }
    else
    {
        DEC_crypConfig.algoDir = CRYP_ALGODIR_DECRYPT;
    }
    DEC_crypConfig.algoMode = CRYP_ALGOMODE_DES_CBC;
    DEC_crypConfig.dataType = CRYP_DATATYPE_8B;
    CRYP_Config(&DEC_crypConfig);

    DEC_keyConfig.key1Left = __REV(*(uint32_t *)(keyAddr));
    keyAddr += 0x04;
    DEC_keyConfig.key1Right = __REV(*(uint32_t *)(keyAddr));
    CRYP_ConfigKey(&DEC_keyConfig);

    DEC_IVConfig.IV0Left  = __REV(*(uint32_t *)(IVAddr));
    keyAddr += 0x04;
    DEC_IVConfig.IV0Right = __REV(*(uint32_t *)(IVAddr));
    CRYP_ConfigIV(&DEC_IVConfig);

    CRYP_FlushFIFO();
    CRYP_Enable();

    if (CRYP_ReadCmdStatus() == DISABLE)
    {
        status = ERROR;
    }
    else
    {
        for (i = 0; i < length; i += 8)
        {
            CRYP_InData(*(uint32_t *)(inputAddr));
            inputAddr += 0x04;
            CRYP_InData(*(uint32_t *)(inputAddr));
            inputAddr += 0x04;

            counter = 0;
            do
            {
                flag = CRYP_ReadStatusFlag(CRYP_FLAG_BUSY);
                counter++;
            }
            while ((counter != 0x00010000) && (flag != RESET));

            if (flag == SET)
            {
                status = ERROR;
            }
            else
            {
                *(uint32_t *)(outputAddr) = CRYP_OutData();
                outputAddr += 0x04;
                *(uint32_t *)(outputAddr) = CRYP_OutData();
                outputAddr += 0x04;
            }
        }
        CRYP_Disable();
    }
    return status;
}

/**@} end of group CRYP_DES_Functions */
/**@} end of group CRYP_DES_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
