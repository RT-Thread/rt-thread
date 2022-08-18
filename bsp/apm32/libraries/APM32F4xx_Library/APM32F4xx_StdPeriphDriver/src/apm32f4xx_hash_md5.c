/*!
 * @file        apm32f4xx_hash_md5.c
 *
 * @brief       This file provides high level functions to compute the HASH MD5 and
 *              HMAC MD5 Digest of an input message.
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


#include "apm32f4xx_hash.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup HASH_MD5_Driver
  * @brief HASH MD5 driver modules
  @{
*/

/** @defgroup HASH_MD5_Functions
  @{
*/

/** @defgroup HASH_MD5_Macros Macros
  @{
*/

/* HASH MD5 timeout definition */
#define MD5_BUSY_TIMEOUT    ((uint32_t) 0x00010000)

/**@} end of group HASH_MD5_Macros*/

/*!
 * @brief     Compute the HASH MD5 digest
 *
 * @param     inBuffer: pointer to the input buffer to be treated
 *
 * @param     lenBuffer: length of the input buffer.
 *
 * @param     outBuffer: the returned digest.
 *
 * @retval    An ErrorStatus enumeration value:
 *            SUCCESS: digest computation done
 *            ERROR: digest computation failed
 *
 */
uint8_t HASH_ComputeMD5(uint8_t *inBuffer, uint32_t lenBuffer,
                        uint8_t outBuffer[16])
{
    HASH_Config_T hashMD5Config;
    HASH_MessageDigest_T hashMD5MessageDigest;
    uint16_t nuValidBits = 0;
    uint32_t m = 0;
    uint32_t inBufferaddr  = (uint32_t)inBuffer;
    uint32_t outBufferaddr = (uint32_t)outBuffer;

    nuValidBits = 8 * (lenBuffer % 4);

    HASH_Reset();

    /* HASH Configuration */
    hashMD5Config.algoSelect = HASH_ALGO_SELECTION_MD5;
    hashMD5Config.algoMode = HASH_ALGO_MODE_HASH;
    hashMD5Config.dataType = HASH_DATA_TYPE_8B;
    HASH_Config(&hashMD5Config);

    /* Configure the number of valid bits in last word of the data */
    HASH_ConfigLastWordValidBitsNbr(nuValidBits);

    /* Write the input block in the IN FIFO */
    for (m = 0; m < lenBuffer; m += 4)
    {
        HASH_WritesInputData(*(uint32_t *)inBufferaddr);
        inBufferaddr += 4;
    }

    /* Start the HASH processor */
    HASH_StartDigest();

    /* wait until the Busy flag is RESET */
    if (HASH_WaitForCompute(MD5_BUSY_TIMEOUT) != 0)
    {
        return ERROR;
    }
    else
    {
        /* Read the message digest */
        HASH_ReadDigest(&hashMD5MessageDigest);

        *(uint32_t *)(outBufferaddr)  = __REV(hashMD5MessageDigest.Data[0]);

        outBufferaddr += 4;
        *(uint32_t *)(outBufferaddr)  = __REV(hashMD5MessageDigest.Data[1]);

        outBufferaddr += 4;
        *(uint32_t *)(outBufferaddr)  = __REV(hashMD5MessageDigest.Data[2]);

        outBufferaddr += 4;
        *(uint32_t *)(outBufferaddr)  = __REV(hashMD5MessageDigest.Data[3]);
    }

    return SUCCESS;
}

/*!
 * @brief     Compute the HMAC MD5 digest
 *
 * @param     key: pointer to the Key used for HMAC
 *
 * @param     lenkey: length of the Key used for HMAC
 *
 * @param     inBuffer: pointer to the Input buffer to be treated
 *
 * @param     lenBuffer: length of the Input buffer
 *
 * @param     outBuffer: the returned digest
 *
 * @retval    An ErrorStatus enumeration value:
 *            SUCCESS: digest computation done
 *            ERROR: digest computation failed
 *
 */
uint8_t HMAC_ComputeMD5(uint8_t *key, uint32_t keylen, uint8_t *inBuffer,
                        uint32_t lenBuffer, uint8_t outBuffer[16])
{
    HASH_Config_T hmacMD5Config;
    HASH_MessageDigest_T hmacMD5MessageDigest;
    uint16_t nuValidBits = 0;
    uint16_t nuValidKey = 0;
    uint32_t m = 0;
    uint32_t keyaddr    = (uint32_t)key;
    uint32_t inBufferaddr  = (uint32_t)inBuffer;
    uint32_t outBufferaddr = (uint32_t)outBuffer;

    nuValidBits = 8 * (lenBuffer % 4);
    nuValidKey = 8 * (keylen % 4);

    HASH_Reset();

    /* HASH Configuration */
    hmacMD5Config.algoSelect = HASH_ALGO_SELECTION_MD5;
    hmacMD5Config.algoMode = HASH_ALGO_MODE_HMAC;
    hmacMD5Config.dataType = HASH_DATA_TYPE_8B;

    if (keylen > 64)
    {
        hmacMD5Config.hmacKeyType = HASH_HMAC_KEY_TYPE_LONGKEY;
    }
    else
    {
        hmacMD5Config.hmacKeyType = HASH_HMAC_KEY_TYPE_SHORTKEY;
    }

    HASH_Config(&hmacMD5Config);
    HASH_ConfigLastWordValidBitsNbr(nuValidKey);

    for (m = 0; m < keylen; m += 4)
    {
        HASH_WritesInputData(*(uint32_t *)keyaddr);
        keyaddr += 4;
    }

    /* Start the HASH processor */
    HASH_StartDigest();

    /* wait until the Busy flag is RESET */
    if (HASH_WaitForCompute(MD5_BUSY_TIMEOUT) != 0)
    {
        return ERROR;
    }
    else
    {
        /* Configure the number of valid bits in last word of the input data */
        HASH_ConfigLastWordValidBitsNbr(nuValidBits);

        /* Write the input block in the IN FIFO */
        for (m = 0; m < lenBuffer; m += 4)
        {
            HASH_WritesInputData(*(uint32_t *)inBufferaddr);
            inBufferaddr += 4;
        }

        /* Start the HASH processor */
        HASH_StartDigest();

        /* wait until the Busy flag is RESET */
        if (HASH_WaitForCompute(MD5_BUSY_TIMEOUT) != 0)
        {
            return ERROR;
        }
        else
        {
            HASH_ConfigLastWordValidBitsNbr(nuValidKey);
            keyaddr = (uint32_t)key;

            for (m = 0; m < keylen; m += 4)
            {
                HASH_WritesInputData(*(uint32_t *)keyaddr);
                keyaddr += 4;
            }

            /* Start the HASH processor */
            HASH_StartDigest();

            /* wait until the Busy flag is RESET */
            if (HASH_WaitForCompute(MD5_BUSY_TIMEOUT) != 0)
            {
                return ERROR;
            }
            else
            {
                /* Read the message digest */
                HASH_ReadDigest(&hmacMD5MessageDigest);

                *(uint32_t *)(outBufferaddr)  = __REV(hmacMD5MessageDigest.Data[0]);

                outBufferaddr += 4;
                *(uint32_t *)(outBufferaddr)  = __REV(hmacMD5MessageDigest.Data[1]);

                outBufferaddr += 4;
                *(uint32_t *)(outBufferaddr)  = __REV(hmacMD5MessageDigest.Data[2]);

                outBufferaddr += 4;
                *(uint32_t *)(outBufferaddr)  = __REV(hmacMD5MessageDigest.Data[3]);
            }
        }
    }

    return SUCCESS;
}

/**@} end of group HASH_MD5_Functions */
/**@} end of group HASH_MD5_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
