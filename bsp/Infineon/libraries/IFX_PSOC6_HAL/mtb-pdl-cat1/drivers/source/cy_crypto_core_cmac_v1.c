/***************************************************************************//**
* \file cy_crypto_core_cmac_v1.c
* \version 2.70
*
* \brief
*  This file provides the source code to the API for the CMAC method
*  in the Crypto block driver.
*
*  Implementation is done in accordance with information from this weblink:
*  nvlpubs.nist.gov/nistpubs/Legacy/SP/nistspecialpublication800-38b.pdf
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

#include "cy_device.h"

#if defined(CY_IP_MXCRYPTO)

#include "cy_crypto_core_cmac_v1.h"

#if defined(CY_CRYPTO_CFG_HW_V1_ENABLE)

#if defined(__cplusplus)
extern "C" {
#endif

#if (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_CMAC_C)

#include "cy_crypto_core_aes_v1.h"
#include "cy_crypto_core_hw_v1.h"
#include "cy_crypto_core_mem_v1.h"
#include "cy_syslib.h"

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 2, \
'Pointer type conversion is intentional');

static void Cy_Crypto_Core_V1_Cmac_CalcSubKey(uint8_t *srcDstPtr);

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Cmac_CalcSubKey
****************************************************************************//**
*
* Calculates the sub-key for the CMAC algorithm
* according to the NIST publication 800-38B, page 7.
*
* \param srcDstPtr
* The pointer to the source data for sub-key calculation, see 800-38B.
*
*******************************************************************************/
static void Cy_Crypto_Core_V1_Cmac_CalcSubKey(uint8_t *srcDstPtr)
{
    int32_t i;
    uint32_t c;
    uint32_t msb = 0UL;

    for (i = (int32_t)((int32_t)CY_CRYPTO_AES_BLOCK_SIZE - 1); i >= 0; i--)
    {
        c = (uint32_t)srcDstPtr[i];
        c = (c << 1U) | msb;
        srcDstPtr[i] = (uint8_t) c;
        msb = (c >> 8U) & 1UL;
    }

    if (0UL != msb)
    {
        /* Just one byte is valuable, the rest are zeros */
        srcDstPtr[(uint8_t)(CY_CRYPTO_AES_BLOCK_SIZE - 1U)] ^= CY_CRYPTO_CMAC_RB;
    }
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Cmac_Init
****************************************************************************//**
*
* The function for initialization of CMAC operation.
*
* \param cmacState
* The pointer to the structure which stores the CMAC context.
*
* \param temp
* The pointer to the temporary memory needed for CMAC calculation,
* the max needed - 128 Bytes.
*
* \param block
* The pointer to the temporary storage for block, the max needed - 128 Bytes.
*
* \param k
* The pointer to the sub-key.

*******************************************************************************/
void Cy_Crypto_Core_V1_Cmac_Init(cy_stc_crypto_v1_cmac_state_t* cmacState,
                                uint32_t* temp,
                                uint32_t* block,
                                uint32_t* k)
{
    cmacState->block = block;
    cmacState->temp  = temp;
    cmacState->k     = k;
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Cmac_Start
****************************************************************************//**
*
* Starts CMAC calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param aesState
* The pointer to the structure which stores the AES context.
*
* \param cmacState
* The pointer to the structure which stores the CMAC context.
*
*******************************************************************************/
void Cy_Crypto_Core_V1_Cmac_Start(CRYPTO_Type *base,
                               cy_stc_crypto_aes_state_t  *aesState,
                               cy_stc_crypto_v1_cmac_state_t *cmacState)
{
    uint32_t *kTmp    = cmacState->k;
    uint32_t *tempTmp = cmacState->temp;

    /* Calculate the K1 sub-key */
    Cy_Crypto_Core_V1_MemSet(base, (void*)tempTmp, 0U, CY_CRYPTO_AES_BLOCK_SIZE);

    Cy_Crypto_Core_V1_Aes_ProcessBlock(base, aesState, CY_CRYPTO_ENCRYPT, kTmp, tempTmp);

    Cy_Crypto_Core_V1_Cmac_CalcSubKey((uint8_t*)kTmp);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Cmac_Update
****************************************************************************//**
*
* Calculates CMAC on a message.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param aesState
* The pointer to the structure which stores the AES context.
*
* \param cmacState
* The pointer to the structure which stores the CMAC context.
*
* \param message
* The pointer to the message whose CMAC is being computed.
*
* \param messageSize
* The size of the message whose CMAC is being computed.
*
*******************************************************************************/
void Cy_Crypto_Core_V1_Cmac_Update(CRYPTO_Type *base,
                                cy_stc_crypto_aes_state_t  *aesState,
                                cy_stc_crypto_v1_cmac_state_t *cmacState,
                                uint8_t  const *message,
                                uint32_t messageSize)
{
    uint32_t *blockBuff = cmacState->block;
    uint32_t *tempBuff  = cmacState->temp;

    /* Clear the argument for XOR for the first block */
    Cy_Crypto_Core_V1_MemSet(base, (void* )tempBuff, 0x00U, CY_CRYPTO_AES_BLOCK_SIZE);

    /* Process all blocks except last */
    while (messageSize > CY_CRYPTO_AES_BLOCK_SIZE)
    {
        /* Copy the source message block */
        Cy_Crypto_Core_V1_MemCpy(base, blockBuff, message, CY_CRYPTO_AES_BLOCK_SIZE);

        Cy_Crypto_Core_V1_Aes_Xor(base, aesState, blockBuff, blockBuff, tempBuff);
        Cy_Crypto_Core_V1_Aes_ProcessBlock(base,
                                        aesState, CY_CRYPTO_ENCRYPT, tempBuff, blockBuff);

        /* in bytes */
        message     += CY_CRYPTO_AES_BLOCK_SIZE;
        messageSize -= CY_CRYPTO_AES_BLOCK_SIZE;
    }

    /* The calculation size of the last block */
    aesState->blockIdx = messageSize;

    /* Copy the last block to the block */
    Cy_Crypto_Core_V1_MemCpy(base, (void*)blockBuff, (void*)message, (uint16_t)aesState->blockIdx);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Cmac_Finish
****************************************************************************//**
*
* Completes CMAC calculation.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param aesState
* the pointer to the structure which stores the AES context.
*
* \param cmacState
* The pointer to the structure which stores the CMAC context.
*
* \param cmac
* The pointer to the computed CMAC value.
*
*******************************************************************************/
void Cy_Crypto_Core_V1_Cmac_Finish(CRYPTO_Type *base,
                                cy_stc_crypto_aes_state_t  *aesState,
                                cy_stc_crypto_v1_cmac_state_t *cmacState,
                                uint8_t* cmac)
{
    uint32_t *blockBuff   = cmacState->block;
    uint32_t *tempBuff    = cmacState->temp;
    uint32_t *kPtrTmp     = cmacState->k;
    uint32_t  blockIdxTmp = aesState->blockIdx;
    uint32_t  copySize;

    if (blockIdxTmp < CY_CRYPTO_AES_BLOCK_SIZE)
    {
        /* Calculate the K2 sub-key */
        Cy_Crypto_Core_V1_Cmac_CalcSubKey((uint8_t* )kPtrTmp);

        /* Appended '1' bit to the end of message, followed by '0' */
        *((uint8_t* )blockBuff + blockIdxTmp) = 0x80U;

        /* Write zeros into the rest of the message */
        copySize = CY_CRYPTO_AES_BLOCK_SIZE - 1u - blockIdxTmp;
        Cy_Crypto_Core_V1_MemSet(base, ((uint8_t* )blockBuff + blockIdxTmp + 1), 0x00U, (uint16_t)copySize);
    }

    Cy_Crypto_Core_V1_Aes_Xor(base, aesState, blockBuff, blockBuff, tempBuff);
    Cy_Crypto_Core_V1_Aes_Xor(base, aesState, blockBuff, blockBuff, kPtrTmp);

    Cy_Crypto_Core_V1_Aes_ProcessBlock(base, aesState, CY_CRYPTO_ENCRYPT, tempBuff, blockBuff);

    /* Copy the result to the cmac */
    Cy_Crypto_Core_V1_MemCpy(base, cmac, tempBuff, CY_CRYPTO_AES_BLOCK_SIZE);
}

/*******************************************************************************
* Function Name: Cy_Crypto_Core_V1_Cmac
****************************************************************************//**
*
* Performs CMAC(Cipher-based Message Authentication Code) operation
* on a message to produce message authentication code using AES.
*
* \param base
* The pointer to the CRYPTO instance.
*
* \param message
* The pointer to a source plain text. Must be 4-byte aligned.
*
* \param messageSize
* The size of a source plain text.
*
* \param key
* The pointer to the encryption key. Must be 4-byte aligned.
*
* \param keyLength
* \ref cy_en_crypto_aes_key_length_t
*
* \param cmac
* The pointer to the calculated CMAC.
*
* \param aesState
* The pointer to the AES state structure allocated by the user. The user
* must not modify anything in this structure.
*
* \return
* \ref cy_en_crypto_status_t
*
*******************************************************************************/
cy_en_crypto_status_t Cy_Crypto_Core_V1_Cmac(CRYPTO_Type *base,
                                          uint8_t  const *message,
                                          uint32_t messageSize,
                                          uint8_t  const *key,
                                          cy_en_crypto_aes_key_length_t keyLength,
                                          uint8_t *cmac,
                                          cy_stc_crypto_aes_state_t *aesState)
{
    cy_stc_crypto_aes_buffers_t  *aesBuffers = (cy_stc_crypto_aes_buffers_t *)(Cy_Crypto_Core_GetVuMemoryAddress(base));
    cy_stc_crypto_v1_cmac_buffers_t *cmacBuffers =
        (cy_stc_crypto_v1_cmac_buffers_t *)((uint8_t*)aesBuffers + sizeof(cy_stc_crypto_aes_buffers_t));

    uint32_t *myBlock = (uint32_t*)(&cmacBuffers->block0);
    uint32_t *myTemp  = (uint32_t*)(&cmacBuffers->block1);
    uint32_t *myK     = (uint32_t*)(&cmacBuffers->k);
    cy_stc_crypto_v1_cmac_state_t *myCmacState = &cmacBuffers->cmacState;

    (void)Cy_Crypto_Core_V1_Aes_Init(base, key, keyLength, aesState, aesBuffers);

    Cy_Crypto_Core_V1_Cmac_Init  (myCmacState, myTemp, myBlock, myK);
    Cy_Crypto_Core_V1_Cmac_Start (base, aesState, myCmacState);
    Cy_Crypto_Core_V1_Cmac_Update(base, aesState, myCmacState, message, messageSize);
    Cy_Crypto_Core_V1_Cmac_Finish(base, aesState, myCmacState, cmac);

    return (CY_CRYPTO_SUCCESS);
}

CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#endif /* (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_CMAC_C) */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_CRYPTO_CFG_HW_V1_ENABLE) */

#endif /* defined(CY_IP_MXCRYPTO) */


/* [] END OF FILE */
