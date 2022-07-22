/*!
 * @file        apm32f4xx_hash_sha1.c
 *
 * @brief       This file provides high level functions to compute the HASH SHA1 and
 *              HMAC SHA1 Digest of an input message.
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

/** @defgroup HASH_SHA1_Driver
  * @brief HASH SHA1 driver modules
  @{
*/

/** @defgroup HASH_SHA1_Functions
  @{
*/

/** @defgroup HASH_SHA1_Macros Macros
  @{
*/

/* HASH SHA1 timeout definition */
#define SHA1_BUSY_TIMEOUT    ((uint32_t) 0x00010000)

/**@} end of group HASH_SHA1_Macros */

/*!
 * @brief     Compute the HASH SHA1 digest
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
uint8_t HASH_ComputeSHA1(uint8_t* inBuffer, uint32_t lenBuffer,
                         uint8_t outBuffer[20])
{
    HASH_Config_T hashSHA1Config;
    HASH_MessageDigest_T hashSHA1MessageDigest;
    uint16_t nBufferBits = 0;
    uint32_t m = 0;
    uint32_t inBufferaddr  = (uint32_t)inBuffer;
    uint32_t outBufferaddr = (uint32_t)outBuffer;

    nBufferBits = (lenBuffer % 4)* 8;

    HASH_Reset();

    /* Configure the number of valid bits in last word of the data */
    hashSHA1Config.algoSelect = HASH_ALGO_SELECTION_SHA1;
    hashSHA1Config.algoMode = HASH_ALGO_MODE_HASH;
    hashSHA1Config.dataType = HASH_DATA_TYPE_8B;
    HASH_Config(&hashSHA1Config);
    HASH_ConfigLastWordValidBitsNbr(nBufferBits);

    /* Write the input block in the IN FIFO */
    for (m = 0; m < lenBuffer; m += 4)
    {
        HASH_WritesInputData(*(uint32_t*)inBufferaddr);
        inBufferaddr += 4;
    }

    /* Start the HASH processor */
    HASH_StartDigest();

    /* wait until the Busy flag is RESET */
    if (HASH_WaitForCompute(SHA1_BUSY_TIMEOUT) != 0)
    {
        return ERROR;
    }
    else
    {
        /* Read the message digest */
        HASH_ReadDigest(&hashSHA1MessageDigest);

        *(uint32_t*)(outBufferaddr)  = __REV(hashSHA1MessageDigest.Data[0]);

        outBufferaddr += 4;
        *(uint32_t*)(outBufferaddr)  = __REV(hashSHA1MessageDigest.Data[1]);

        outBufferaddr += 4;
        *(uint32_t*)(outBufferaddr)  = __REV(hashSHA1MessageDigest.Data[2]);

        outBufferaddr += 4;
        *(uint32_t*)(outBufferaddr)  = __REV(hashSHA1MessageDigest.Data[3]);

        outBufferaddr += 4;
        *(uint32_t*)(outBufferaddr)  = __REV(hashSHA1MessageDigest.Data[4]);
    }

    return SUCCESS;
}

/*!
 * @brief     Compute the HMAC SHA1 digest
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
uint8_t HMAC_ComputeSHA1(uint8_t* key, uint32_t lenkey, uint8_t* inBuffer,
                         uint32_t lenBuffer, uint8_t outBuffer[20])
{
    HASH_Config_T hmacSHA1Config;
    HASH_MessageDigest_T hashSHA1MessageDigest;
    uint16_t nBufferBits = 0;
    uint16_t nuValidKey = 0;
    uint32_t m = 0;
    uint32_t keyaddr    = (uint32_t)key;
    uint32_t inputaddr  = (uint32_t)inBuffer;
    uint32_t outputaddr = (uint32_t)outBuffer;

    nBufferBits = 8 * (lenBuffer % 4);
    nuValidKey = 8 * (lenkey % 4);

    HASH_Reset();

    /* HASH Configuration */
    hmacSHA1Config.algoSelect = HASH_ALGO_SELECTION_SHA1;
    hmacSHA1Config.algoMode = HASH_ALGO_MODE_HMAC;
    hmacSHA1Config.dataType = HASH_DATA_TYPE_8B;

    if (lenkey > 64)
    {
        hmacSHA1Config.hmacKeyType = HASH_HMAC_KEY_TYPE_LONGKEY;
    }
    else
    {
        hmacSHA1Config.hmacKeyType = HASH_HMAC_KEY_TYPE_SHORTKEY;
    }

    HASH_Config(&hmacSHA1Config);
    HASH_ConfigLastWordValidBitsNbr(nuValidKey);

    /* Write the key */
    for (m=0; m<lenkey; m+=4)
    {
        HASH_WritesInputData(*(uint32_t*)keyaddr);
        keyaddr+=4;
    }

    HASH_StartDigest();

    /* wait until the Busy flag is RESET */
    if (HASH_WaitForCompute(SHA1_BUSY_TIMEOUT) != 0)
    {
        return ERROR;
    }
    else
    {
        HASH_ConfigLastWordValidBitsNbr(nBufferBits);

        for (m=0; m<lenkey; m+=4)
        {
            HASH_WritesInputData(*(uint32_t*)inputaddr);
            inputaddr+=4;
        }

        HASH_StartDigest();

        /* wait until the Busy flag is RESET */
        if (HASH_WaitForCompute(SHA1_BUSY_TIMEOUT) != 0)
        {
            return ERROR;
        }
        else
        {
            HASH_ConfigLastWordValidBitsNbr(nuValidKey);
            /* Write the key */
            keyaddr = (uint32_t)key;

            for (m=0; m<lenkey; m+=4)
            {
                HASH_WritesInputData(*(uint32_t*)keyaddr);
                keyaddr+=4;
            }

            /* Start the HASH processor */
            HASH_StartDigest();

            /* wait until the Busy flag is RESET */
            if (HASH_WaitForCompute(SHA1_BUSY_TIMEOUT) != 0)
            {
                return ERROR;
            }
            else
            {
                /* Read the message digest */
                HASH_ReadDigest(&hashSHA1MessageDigest);
                *(uint32_t*)(outputaddr)  = __REV(hashSHA1MessageDigest.Data[0]);

                outputaddr+=4;
                *(uint32_t*)(outputaddr)  = __REV(hashSHA1MessageDigest.Data[1]);

                outputaddr+=4;
                *(uint32_t*)(outputaddr)  = __REV(hashSHA1MessageDigest.Data[2]);

                outputaddr+=4;
                *(uint32_t*)(outputaddr)  = __REV(hashSHA1MessageDigest.Data[3]);

                outputaddr+=4;
                *(uint32_t*)(outputaddr)  = __REV(hashSHA1MessageDigest.Data[4]);
            }
        }
    }

    return SUCCESS;
}

/**@} end of group HASH_SHA1_Functions */
/**@} end of group HASH_SHA1_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
