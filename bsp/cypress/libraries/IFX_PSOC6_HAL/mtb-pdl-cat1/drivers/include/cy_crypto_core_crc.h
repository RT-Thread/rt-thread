/***************************************************************************//**
* \file cy_crypto_core_crc.h
* \version 2.50
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

#if (CPUSS_CRYPTO_CRC == 1)

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
    cy_en_crypto_status_t tmpResult;

    if (CY_CRYPTO_V1)
    {
        tmpResult = Cy_Crypto_Core_V1_Crc_Init(base, polynomial, dataReverse, dataXor, remReverse, remXor);
    }
    else
    {
        tmpResult = Cy_Crypto_Core_V2_Crc_Init(base, polynomial, dataReverse, dataXor, remReverse, remXor);
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
    cy_en_crypto_status_t tmpResult;

    if (CY_CRYPTO_V1)
    {
        tmpResult = Cy_Crypto_Core_V1_Crc(base, crc, data, dataSize, lfsrInitState);
    }
    else
    {
        tmpResult = Cy_Crypto_Core_V2_Crc(base, crc, data, dataSize, lfsrInitState);
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
    cy_en_crypto_status_t tmpResult;

    if (CY_CRYPTO_V1)
    {
        tmpResult = Cy_Crypto_Core_V1_Crc_CalcInit(base, width, polynomial, dataReverse, dataXor,
                                                 remReverse, remXor, lfsrInitState);
    }
    else
    {
        tmpResult = Cy_Crypto_Core_V2_Crc_CalcInit(base, width, polynomial, dataReverse, dataXor,
                                                 remReverse, remXor, lfsrInitState);
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
    cy_en_crypto_status_t tmpResult;

    if (CY_CRYPTO_V1)
    {
        tmpResult = Cy_Crypto_Core_V1_Crc_CalcStart(base, width, lfsrInitState);
    }
    else
    {
        tmpResult = Cy_Crypto_Core_V2_Crc_CalcStart(base, width, lfsrInitState);
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
    cy_en_crypto_status_t tmpResult;

    if (CY_CRYPTO_V1)
    {
        tmpResult = Cy_Crypto_Core_V1_Crc_CalcPartial(base, data, dataSize);
    }
    else
    {
        tmpResult = Cy_Crypto_Core_V2_Crc_CalcPartial(base, data, dataSize);
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
    cy_en_crypto_status_t tmpResult;

    if (CY_CRYPTO_V1)
    {
        tmpResult = Cy_Crypto_Core_V1_Crc_CalcFinish(base, width, crc);
    }
    else
    {
        tmpResult = Cy_Crypto_Core_V2_Crc_CalcFinish(base, width, crc);
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
*******************************************************************************/
__STATIC_INLINE cy_en_crypto_status_t Cy_Crypto_Core_Crc_Calc(CRYPTO_Type *base,
                                                              uint32_t width, uint32_t *crc,
                                                              void const *data, uint32_t  dataSize)
{
    cy_en_crypto_status_t tmpResult;

    if (CY_CRYPTO_V1)
    {
        tmpResult = Cy_Crypto_Core_V1_Crc_Calc(base, width, crc, data, dataSize);
    }
    else
    {
        tmpResult = Cy_Crypto_Core_V2_Crc_Calc(base, width, crc, data, dataSize);
    }

    return tmpResult;
}

/** \} group_crypto_lld_crc_functions */

#endif /* #if (CPUSS_CRYPTO_CRC == 1) */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_CORE_CRC_H) */



/* [] END OF FILE */
