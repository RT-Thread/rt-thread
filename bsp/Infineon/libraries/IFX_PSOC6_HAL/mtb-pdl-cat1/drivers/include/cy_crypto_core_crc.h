/***************************************************************************//**
* \file cy_crypto_core_crc.h
* \version 2.70
*
* \brief
*  This file provides the headers for CRC API
*  in the Crypto driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/


#if !defined (CY_CRYPTO_CORE_CRC_H)
#define CY_CRYPTO_CORE_CRC_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_common.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C)

#include "cy_crypto_core_crc_v1.h"
#include "cy_crypto_core_crc_v2.h"

typedef cy_en_crypto_status_t (*cy_crypto_crc_init_func_t)(CRYPTO_Type *base,
                                        uint32_t polynomial,
                                        uint32_t dataReverse,
                                        uint32_t dataXor,
                                        uint32_t remReverse,
                                        uint32_t remXor);

typedef cy_en_crypto_status_t (*cy_crypto_crc_func_t)(CRYPTO_Type *base,
                                        uint32_t *crc,
                                        void      const *data,
                                        uint32_t  dataSize,
                                        uint32_t  lfsrInitState);

/**
* \addtogroup group_crypto_lld_crc_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Crc_Init
****************************************************************************//**
*
* Initializes the CRC calculation.
*
* Call to initialize this encryption technique before using any associated
* functions. You must initialize this technique again after using any other
* encryption technique.
*
* Below is the table with known polynomials with different parameters and their
* calculated CRCs from the string <b>"123456789"</b>:
* | Name               | Width | Poly       | Init       | Data Rev | Data XOR | Rem Rev | Rem XOR    | Expected CRC |
* |:-------------------|:-----:|:----------:|:----------:|:--------:|:--------:|:-------:|:----------:|:------------:|
* | CRC-3 / ROHC       |     3 |        0x3 |        0x7 |        1 |        0 |       1 |        0x0 |          0x6 |
* | CRC-4 / ITU        |     4 |        0x3 |        0x0 |        1 |        0 |       1 |        0x0 |          0x7 |
* | CRC-5 / EPC        |     5 |        0x9 |        0x9 |        0 |        0 |       0 |        0x0 |          0x0 |
* | CRC-5 / ITU        |     5 |       0x15 |        0x0 |        1 |        0 |       1 |        0x0 |          0x7 |
* | CRC-5 / USB        |     5 |        0x5 |       0x1F |        1 |        0 |       1 |       0x1F |         0x19 |
* | CRC-6 / CDMA2000-A |     6 |       0x27 |       0x3F |        0 |        0 |       0 |        0x0 |          0xD |
* | CRC-6 / CDMA2000-B |     6 |        0x7 |       0x3F |        0 |        0 |       0 |        0x0 |         0x3B |
* | CRC-6 / DARC       |     6 |       0x19 |        0x0 |        1 |        0 |       1 |        0x0 |         0x26 |
* | CRC-6 / ITU        |     6 |        0x3 |        0x0 |        1 |        0 |       1 |        0x0 |          0x6 |
* | CRC-7              |     7 |        0x9 |        0x0 |        0 |        0 |       0 |        0x0 |         0x75 |
* | CRC-7 / ROHC       |     7 |       0x4F |       0x7F |        1 |        0 |       1 |        0x0 |         0x53 |
* | CRC-8              |     8 |        0x7 |        0x0 |        0 |        0 |       0 |        0x0 |         0xF4 |
* | CRC-8 / CDMA2000   |     8 |       0x9B |       0xFF |        0 |        0 |       0 |        0x0 |         0xDA |
* | CRC-8 / DARC       |     8 |       0x39 |        0x0 |        1 |        0 |       1 |        0x0 |         0x15 |
* | CRC-8 / DVB-S2     |     8 |       0xD5 |        0x0 |        0 |        0 |       0 |        0x0 |         0xBC |
* | CRC-8 / EBU        |     8 |       0x1D |       0xFF |        1 |        0 |       1 |        0x0 |         0x97 |
* | CRC-8 / I-CODE     |     8 |       0x1D |       0xFD |        0 |        0 |       0 |        0x0 |         0x7E |
* | CRC-8 / ITU        |     8 |        0x7 |        0x0 |        0 |        0 |       0 |       0x55 |         0xA1 |
* | CRC-8 / MAXIM      |     8 |       0x31 |        0x0 |        1 |        0 |       1 |        0x0 |         0xA1 |
* | CRC-8 / ROHC       |     8 |        0x7 |       0xFF |        1 |        0 |       1 |        0x0 |         0xD0 |
* | CRC-8 / WCDMA      |     8 |       0x9B |        0x0 |        1 |        0 |       1 |        0x0 |         0x25 |
* | CRC-10             |    10 |      0x233 |        0x0 |        0 |        0 |       0 |        0x0 |        0x199 |
* | CRC-10 / CDMA2000  |    10 |      0x3D9 |      0x3FF |        0 |        0 |       0 |        0x0 |        0x233 |
* | CRC-11             |    11 |      0x385 |       0x1A |        0 |        0 |       0 |        0x0 |        0x5A3 |
* | CRC-12 / 3GPP      |    12 |      0x80F |        0x0 |        0 |        0 |       1 |        0x0 |        0xDAF |
* | CRC-12 / CDMA2000  |    12 |      0xF13 |      0xFFF |        0 |        0 |       0 |        0x0 |        0xD4D |
* | CRC-12 / DECT      |    12 |      0x80F |        0x0 |        0 |        0 |       0 |        0x0 |        0xF5B |
* | CRC-13 / BBC       |    13 |     0x1CF5 |        0x0 |        0 |        0 |       0 |        0x0 |        0x4FA |
* | CRC-14 / DARC      |    14 |      0x805 |        0x0 |        1 |        0 |       1 |        0x0 |        0x82D |
* | CRC-15             |    15 |     0x4599 |        0x0 |        0 |        0 |       0 |        0x0 |        0x59E |
* | CRC-15 / MPT1327   |    15 |     0x6815 |        0x0 |        0 |        0 |       0 |        0x1 |       0x2566 |
* | CRC-24             |    24 |  0x0864CFB | 0x00B704CE |        0 |        0 |       0 |        0x0 |     0x21CF02 |
* | CRC-24 / FLEXRAY-A |    24 |  0x05D6DCB | 0x00FEDCBA |        0 |        0 |       0 |        0x0 |     0x7979BD |
* | CRC-24 / FLEXRAY-B |    24 |  0x05D6DCB | 0x00ABCDEF |        0 |        0 |       0 |        0x0 |     0x1F23B8 |
* | CRC-31 / PHILIPS   |    31 |  0x4C11DB7 | 0x7FFFFFFF |        0 |        0 |       0 | 0x7FFFFFFF |    0xCE9E46C |
* | CRC-16 / ARC       |    16 |     0x8005 |     0x0000 |        1 |        0 |       1 |     0x0000 |       0xBB3D |
* | CRC-16 / AUG-CCITT |    16 |     0x1021 |     0x1D0F |        0 |        0 |       0 |     0x0000 |       0xE5CC |
* | CRC-16 / BUYPASS   |    16 |     0x8005 |     0x0000 |        0 |        0 |       0 |     0x0000 |       0xFEE8 |
* | CRC-16 / CCITT-0   |    16 |     0x1021 |     0xFFFF |        0 |        0 |       0 |     0x0000 |       0x29B1 |
* | CRC-16 / CDMA2000  |    16 |     0xC867 |     0xFFFF |        0 |        0 |       0 |     0x0000 |       0x4C06 |
* | CRC-16 / DDS-110   |    16 |     0x8005 |     0x800D |        0 |        0 |       0 |     0x0000 |       0x9ECF |
* | CRC-16 / DECT-R    |    16 |     0x0589 |     0x0000 |        0 |        0 |       0 |     0x0001 |       0x007E |
* | CRC-16 / DECT-X    |    16 |     0x0589 |     0x0000 |        0 |        0 |       0 |     0x0000 |       0x007F |
* | CRC-16 / DNP       |    16 |     0x3D65 |     0x0000 |        1 |        0 |       1 |     0xFFFF |       0xEA82 |
* | CRC-16 / EN-13757  |    16 |     0x3D65 |     0x0000 |        0 |        0 |       0 |     0xFFFF |       0xC2B7 |
* | CRC-16 / GENIBUS   |    16 |     0x1021 |     0xFFFF |        0 |        0 |       0 |     0xFFFF |       0xD64E |
* | CRC-16 / MAXIM     |    16 |     0x8005 |     0x0000 |        1 |        0 |       1 |     0xFFFF |       0x44C2 |
* | CRC-16 / MCRF4XX   |    16 |     0x1021 |     0xFFFF |        1 |        0 |       1 |     0x0000 |       0x6F91 |
* | CRC-16 / RIELLO    |    16 |     0x1021 |     0xB2AA |        1 |        0 |       1 |     0x0000 |       0x63D0 |
* | CRC-16 / T10-DIF   |    16 |     0x8BB7 |     0x0000 |        0 |        0 |       0 |     0x0000 |       0xD0DB |
* | CRC-16 / TELEDISK  |    16 |     0xA097 |     0x0000 |        0 |        0 |       0 |     0x0000 |       0x0FB3 |
* | CRC-16 / TMS37157  |    16 |     0x1021 |     0x89EC |        1 |        0 |       1 |     0x0000 |       0x26B1 |
* | CRC-16 / USB       |    16 |     0x8005 |     0xFFFF |        1 |        0 |       1 |     0xFFFF |       0xB4C8 |
* | CRC-A              |    16 |     0x1021 |     0xC6C6 |        1 |        0 |       1 |     0x0000 |       0xBF05 |
* | CRC-16 / KERMIT    |    16 |     0x1021 |     0x0000 |        1 |        0 |       1 |     0x0000 |       0x2189 |
* | CRC-16 / MODBUS    |    16 |     0x8005 |     0xFFFF |        1 |        0 |       1 |     0x0000 |       0x4B37 |
* | CRC-16 / X-25      |    16 |     0x1021 |     0xFFFF |        1 |        0 |       1 |     0xFFFF |       0x906E |
* | CRC-16 / XMODEM    |    16 |     0x1021 |     0x0000 |        0 |        0 |       0 |     0x0000 |       0x31C3 |
* | CRC-32             |    32 | 0x04C11DB7 | 0xFFFFFFFF |        1 |        0 |       1 | 0xFFFFFFFF |   0xCBF43926 |
* | CRC-32 / BZIP2     |    32 | 0x04C11DB7 | 0xFFFFFFFF |        0 |        0 |       0 | 0xFFFFFFFF |   0xFC891918 |
* | CRC-32C            |    32 | 0x1EDC6F41 | 0xFFFFFFFF |        1 |        0 |       1 | 0xFFFFFFFF |   0xE3069283 |
* | CRC-32D            |    32 | 0xA833982B | 0xFFFFFFFF |        1 |        0 |       1 | 0xFFFFFFFF |   0x87315576 |
* | CRC-32 / MPEG-2    |    32 | 0x04C11DB7 | 0xFFFFFFFF |        0 |        0 |       0 | 0x00000000 |   0x0376E6E7 |
* | CRC-32 / POSIX     |    32 | 0x04C11DB7 | 0x00000000 |        0 |        0 |       0 | 0xFFFFFFFF |   0x765E7680 |
* | CRC-32Q            |    32 | 0x814141AB | 0x00000000 |        0 |        0 |       0 | 0x00000000 |   0x3010BF7F |
* | CRC-32 / JAMCRC    |    32 | 0x04C11DB7 | 0xFFFFFFFF |        1 |        0 |       1 | 0x00000000 |   0x340BC6D9 |
* | CRC-32 / XFER      |    32 | 0x000000AF | 0x00000000 |        0 |        0 |       0 | 0x00000000 |   0xBD0BE338 |
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param polynomial
* The polynomial (specified using 32 bits) used in the computing CRC.
*
* \param dataReverse
* The order in which data bytes are processed. 0 - MSB first; 1- LSB first.
*
* \param dataXor
* The byte mask for XORing data.
*
* \param remReverse
* A remainder reverse: 0 means the remainder is not reversed. 1 means reversed.
*
* \param remXor
* Specifies the mask with which the LFSR32 register is XORed to produce a remainder.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Crc_Init(CRYPTO_Type *base,
                                        uint32_t polynomial,
                                        uint32_t dataReverse,
                                        uint32_t dataXor,
                                        uint32_t remReverse,
                                        uint32_t remXor)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Crc_Init(base, polynomial, dataReverse, dataXor, remReverse, remXor);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Crc_Init(base, polynomial, dataReverse, dataXor, remReverse, remXor);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Crc
****************************************************************************//**
*
* Performs the CRC calculation on a message.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param crc
* The pointer to a computed CRC value. Must be 4-byte aligned.
*
* \param data
* The pointer to the message whose CRC is being computed.
*
* \param dataSize
* The size of a message in bytes.
*
* \param lfsrInitState
* The initial state of the LFSR.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Crc(CRYPTO_Type *base,
                                        uint32_t *crc,
                                        void      const *data,
                                        uint32_t  dataSize,
                                        uint32_t  lfsrInitState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Crc(base, crc, data, dataSize, lfsrInitState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Crc(base, crc, data, dataSize, lfsrInitState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Crc_CalcInit
****************************************************************************//**
*
* Initializes the CRC calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param width
* The CRC width in bits.
*
* \param polynomial
* The polynomial (specified using 32 bits) used in the computing CRC.
*
* \param dataReverse
* The order in which data bytes are processed. 0 - MSB first; 1 - LSB first.
*
* \param dataXor
* The byte mask for XORing data
*
* \param remReverse
* A remainder reverse: 0 means the remainder is not reversed. 1 means reversed.
*
* \param remXor
* Specifies the mask with which the LFSR32 register is XORed to produce a remainder.
*
* \param lfsrInitState
* The initial state of the LFSR.
*
* \return
* \ref cy_en_crypto_status_t
*
* \funcusage
* \snippet crypto/snippet/main.c snippet_myCryptoCoreCrcUse
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Crc_CalcInit(CRYPTO_Type *base,
                                        uint32_t width,
                                        uint32_t polynomial,
                                        uint32_t dataReverse,
                                        uint32_t dataXor,
                                        uint32_t remReverse,
                                        uint32_t remXor,
                                        uint32_t lfsrInitState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Crc_CalcInit(base, width, polynomial, dataReverse, dataXor,
                                                 remReverse, remXor, lfsrInitState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Crc_CalcInit(base, width, polynomial, dataReverse, dataXor,
                                                 remReverse, remXor, lfsrInitState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Crc_CalcStart
****************************************************************************//**
*
* Prepares the CRC calculation by setting an initial seed value.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param width
* The CRC width in bits.
*
* \param lfsrInitState
* The initial state of the LFSR.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Crc_CalcStart(CRYPTO_Type *base,
                                                                   uint32_t width, uint32_t  lfsrInitState)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Crc_CalcStart(base, width, lfsrInitState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Crc_CalcStart(base, width, lfsrInitState);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Crc_CalcPartial
****************************************************************************//**
*
* Performs the CRC calculation of a message part.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param data
* The pointer to the message whose CRC is being computed.
*
* \param dataSize
* The size of a message in bytes.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Crc_CalcPartial(CRYPTO_Type *base,
                                                                     void const *data, uint32_t  dataSize)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Crc_CalcPartial(base, data, dataSize);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Crc_CalcPartial(base, data, dataSize);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Crc_CalcFinish
****************************************************************************//**
*
* Finalizes the CRC calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param width
* The CRC width in bits.
*
* \param crc
* The pointer to a computed CRC value. Must be 4-byte aligned.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Crc_CalcFinish(CRYPTO_Type *base, uint32_t width, uint32_t *crc)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Crc_CalcFinish(base, width, crc);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Crc_CalcFinish(base, width, crc);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_Crc_Calc
****************************************************************************//**
*
* Performs the CRC calculation on a message.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param width
* The CRC width in bits.
*
* \param crc
* The pointer to a computed CRC value. Must be 4-byte aligned.
*
* \param data
* The pointer to the message whose CRC is being computed.
*
* \param dataSize
* The size of a message in bytes.
*
* \return
* \ref cy_en_crypto_status_t
*
* \funcusage
* \snippet crypto/snippet/main.c snippet_myCryptoCoreCrcUse
*
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Crc_Calc(CRYPTO_Type *base,
                                                              uint32_t width, uint32_t *crc,
                                                              void const *data, uint32_t  dataSize)
{
    cy_en_crypto_status_t tmpResult = CY_CRYPTO_NOT_SUPPORTED;

    if (CY_CRYPTO_V1)
    {
        #if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
        tmpResult = Cy_Crypto_Core_V1_Crc_Calc(base, width, crc, data, dataSize);
        #endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */
    }
    else
    {
        #if defined(CY_CRYPTO_CFG_HW_V2_ENABLE)
        tmpResult = Cy_Crypto_Core_V2_Crc_Calc(base, width, crc, data, dataSize);
        #endif /* defined(CY_CRYPTO_CFG_HW_V2_ENABLE) */
    }

    return tmpResult;
}

/** \} group_crypto_lld_crc_functions */

#endif /* (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_CORE_CRC_H) */



/* [] END OF FILE */
