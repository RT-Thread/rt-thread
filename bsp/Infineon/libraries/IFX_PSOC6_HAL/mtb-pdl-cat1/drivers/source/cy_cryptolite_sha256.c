/***************************************************************************//**
* \file cy_cryptolite_sha256.c
* \version 2.0
*
* \brief
*  Provides API implementation of the Cryptolite SHA256 PDL driver.
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

#if defined (CY_IP_MXCRYPTOLITE)

#include "cy_cryptolite_sha256.h"

#if defined(__cplusplus)
extern "C" {
#endif

#if (CRYPTOLITE_SHA_PRESENT == 1)
#if defined(CY_CRYPTOLITE_CFG_SHA_C) && defined(CY_CRYPTOLITE_CFG_SHA2_256_ENABLED)

/*Initial Hash*/
static const uint32_t sha256InitHash[] =
{
    0x6A09E667uL, 0xBB67AE85uL, 0x3C6EF372uL, 0xA54FF53AuL,
    0x510E527FuL, 0x9B05688CuL, 0x1F83D9ABuL, 0x5BE0CD19uL
};

/*****************************************************************************
* Cy_Cryptolite_Sha256_Process (for internal use)
******************************************************************************
*
* The function starts the hash calculation, blocks until finished.
*
*  base
* The pointer to the Cryptolite instance.
*
*  cfContext
* The pointer to the cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* return
* cy_en_cryptolite_status_t
*
*******************************************************************************/
static cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Process(CRYPTOLITE_Type *base,
                                        cy_stc_cryptolite_context_sha256_t *cfContext)
{
    if((REG_CRYPTOLITE_STATUS(base) & CRYPTOLITE_STATUS_BUSY_Msk) != 0UL)
    {
        return CY_CRYPTOLITE_HW_BUSY;
    }

    /*write to SHA DESCR REG starts process
      IP will block another write to SHA DESCR REG until its busy
      We poll for busy state and check for error before posting next
      descriptor */

    /*start message schedule*/
    REG_CRYPTOLITE_SHA_DESCR(base) = (uint32_t)&(cfContext->message_schedule_struct);
    while((REG_CRYPTOLITE_STATUS(base) & CRYPTOLITE_STATUS_BUSY_Msk) != 0UL){};
    if((REG_CRYPTOLITE_SHA_INTR_ERROR(base) & CRYPTOLITE_INTR_ERROR_BUS_ERROR_Msk) != 0UL)
    {
        REG_CRYPTOLITE_SHA_INTR_ERROR(base) = CRYPTOLITE_INTR_ERROR_BUS_ERROR_Msk;
        return CY_CRYPTOLITE_BUS_ERROR;
    }

    /*start process*/
    REG_CRYPTOLITE_SHA_DESCR(base) = (uint32_t)&(cfContext->message_process_struct);
    while((REG_CRYPTOLITE_STATUS(base) & CRYPTOLITE_STATUS_BUSY_Msk) != 0UL){};
    if((REG_CRYPTOLITE_SHA_INTR_ERROR(base) & CRYPTOLITE_INTR_ERROR_BUS_ERROR_Msk) != 0UL)
    {
        REG_CRYPTOLITE_SHA_INTR_ERROR(base) = CRYPTOLITE_INTR_ERROR_BUS_ERROR_Msk;
        return CY_CRYPTOLITE_BUS_ERROR;
    }

    return CY_CRYPTOLITE_SUCCESS;
}

/*****************************************************************************
* Cy_Cryptolite_Sha256_Process_aligned (for internal use)
******************************************************************************
*
* The function starts the hash calculation for 4 byte aligned data blocks
* until finished.
*
*  base
* The pointer to the Cryptolite instance.
*
*  cfContext
* The pointer to the cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
*  message
* The pointer to the message whose Hash is being computed.
*
*  messageSize
* The pointer to size of the message whose Hash is being computed.
* returns the remaining message size after process
*
* return
* cy_en_cryptolite_status_t
*
*******************************************************************************/
static cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Process_aligned(CRYPTOLITE_Type *base,
                                        cy_stc_cryptolite_context_sha256_t *cfContext,
                                        uint8_t const *message,
                                        uint32_t  *messageSize)
{
    cy_en_cryptolite_status_t err;

    /*point descriptor to message buffer*/
    cfContext->message_schedule_struct.data1 = (uint32_t)message;

    while(*messageSize >= CY_CRYPTOLITE_SHA256_BLOCK_SIZE)
    {
        err = Cy_Cryptolite_Sha256_Process(base, cfContext);
        if(CY_CRYPTOLITE_SUCCESS != err)
        {
            cfContext->message_schedule_struct.data1 = (uint32_t)cfContext->message;
            return err;
        }
        *messageSize-=CY_CRYPTOLITE_SHA256_BLOCK_SIZE;
        cfContext->messageSize+= CY_CRYPTOLITE_SHA256_BLOCK_SIZE;
        cfContext->message_schedule_struct.data1+= CY_CRYPTOLITE_SHA256_BLOCK_SIZE;
    }
    /*restore descriptor to context buffer*/
    cfContext->message_schedule_struct.data1 = (uint32_t)cfContext->message;

    return CY_CRYPTOLITE_SUCCESS;
}

/*****************************************************************************
* Cy_Cryptolite_Sha256_Init
******************************************************************************
*
* The function to initialize the SHA256 operation.
*
*  base
* The pointer to the Cryptolite instance.
*
*  cfContext
* The pointer to the cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* return
* cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Init(CRYPTOLITE_Type *base,
                                        cy_stc_cryptolite_context_sha256_t *cfContext)
{
    /* Input parameters verification */
    if ((NULL == base) || (NULL == cfContext))
    {
        return CY_CRYPTOLITE_BAD_PARAMS;
    }

    cfContext->message = (uint8_t*)cfContext->msgblock;
    cfContext->message_schedule_struct.data0 = (uint32_t)CY_CRYPTOLITE_MSG_SCH_CTLWD;
    cfContext->message_schedule_struct.data1 = (uint32_t)cfContext->message;
    cfContext->message_schedule_struct.data2 = (uint32_t)cfContext->message_schedule;

    cfContext->message_process_struct.data0 = (uint32_t)CY_CRYPTOLITE_PROCESS_CTLWD;
    cfContext->message_process_struct.data1 = (uint32_t)cfContext->hash;
    cfContext->message_process_struct.data2 = (uint32_t)cfContext->message_schedule;

    return (CY_CRYPTOLITE_SUCCESS);
}

/*******************************************************************************
* Cy_Cryptolite_Sha256_Start
******************************************************************************
*
* Initializes the initial Hash vector.
*
*  base
* The pointer to the CRYPTOLITE instance.
*
*  cfContext
* The pointer to the cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* return
* cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Start(CRYPTOLITE_Type *base,
                                        cy_stc_cryptolite_context_sha256_t *cfContext)
{
    uint32_t i;
    /* Input parameters verification */
    if ((NULL == base) || (NULL == cfContext))
    {
        return CY_CRYPTOLITE_BAD_PARAMS;
    }

    /*check if IP is busy*/
    if ((REG_CRYPTOLITE_STATUS(base) & CRYPTOLITE_STATUS_BUSY_Msk) != 0UL)
    {
        return CY_CRYPTOLITE_HW_BUSY;
    }

    cfContext->msgIdx = 0U;
    cfContext->messageSize = 0U;

    /*copy initial hash*/
    for (i=0U; i < CY_CRYPTOLITE_SHA256_HASH_SIZE/4U; i++)
    {
        cfContext->hash[i] = sha256InitHash[i];
    }

    return CY_CRYPTOLITE_SUCCESS;
}

/*******************************************************************************
* Cy_Cryptolite_Sha256_Update
********************************************************************************
*
* Performs the SHA256 calculation on one message.
*
*  base
* The pointer to the CRYPTOLITE instance.
*
*  cfContext
* The pointer to the cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
*  message
* The pointer to the message whose Hash is being computed.
*
*  messageSize
* The size of the message whose Hash is being computed.
*
* return
* cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Update(CRYPTOLITE_Type *base,
                                        uint8_t const *message,
                                        uint32_t  messageSize,
                                        cy_stc_cryptolite_context_sha256_t *cfContext)
{
    cy_en_cryptolite_status_t err = CY_CRYPTOLITE_BAD_PARAMS;
    uint32_t readIdx = 0U;
    uint32_t idx = 0U;
    uint32_t msg_add = (uint32)message;
    uint32_t lmessageSize;

    if (0UL == messageSize)
    {
        return CY_CRYPTOLITE_SUCCESS;
    }

    /* Input parameters verification */
    if ((NULL == base) || (NULL == cfContext) || (NULL == message))
    {
        return err;
    }

    /*check if IP is busy*/
    if ((REG_CRYPTOLITE_STATUS(base) & CRYPTOLITE_STATUS_BUSY_Msk) != 0UL)
    {
        return CY_CRYPTOLITE_HW_BUSY;
    }

    lmessageSize = messageSize;

    /*Check for 4 byte aligned buffer and process*/
    if((msg_add & 0x3UL) == 0UL)
    {
        /*Check for fragmented message and size*/
        if (cfContext->msgIdx == 0UL && messageSize >= CY_CRYPTOLITE_SHA256_BLOCK_SIZE)
        {
            err = Cy_Cryptolite_Sha256_Process_aligned(base, cfContext, message, &lmessageSize);
            if(CY_CRYPTOLITE_SUCCESS != err)
            {
                return err;
            }
            readIdx = messageSize - lmessageSize;
        }
    }

    while((cfContext->msgIdx + lmessageSize) >= CY_CRYPTOLITE_SHA256_BLOCK_SIZE)
    {
        uint32_t tocopy = CY_CRYPTOLITE_SHA256_BLOCK_SIZE - cfContext->msgIdx;
        /* Create a message block */
        for ( idx = 0; idx < tocopy; idx++ )
        {
            cfContext->message[cfContext->msgIdx] = message[readIdx++];
            cfContext->msgIdx++;
        }
        /* calculate message schedule and process */
        err = Cy_Cryptolite_Sha256_Process(base, cfContext);
        if(CY_CRYPTOLITE_SUCCESS != err)
        {
            return err;
        }
        lmessageSize-= tocopy;
        cfContext->messageSize+= CY_CRYPTOLITE_SHA256_BLOCK_SIZE;
        cfContext->msgIdx = 0U;
    }
    /* Copy message fragment*/
    for ( idx = 0; idx < lmessageSize; idx++ )
    {
        cfContext->message[cfContext->msgIdx] = message[readIdx++];
        cfContext->msgIdx++;
    }

    return CY_CRYPTOLITE_SUCCESS;
}

/*******************************************************************************
* Cy_Cryptolite_Sha256_Finish
******************************************************************************
*
* Completes the SHA256 calculation.
*
*  base
* The pointer to the CRYPTOLITE instance.
*
*  cfContext
* the pointer to the cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
*  digest
* The pointer to the calculated Hash digest.
*
* return
* cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Finish(CRYPTOLITE_Type *base,
                                    uint8_t *digest,
                                    cy_stc_cryptolite_context_sha256_t *cfContext)
{
    cy_en_cryptolite_status_t err = CY_CRYPTOLITE_SUCCESS;
    uint8_t *hashptr;
    uint32_t idx;
    uint64_t totalMessageSizeInBits;

    /* Input parameters verification */
    if ((NULL == base) || (NULL == cfContext) || (NULL == digest))
    {
        return err;
    }

    /*check if IP is busy*/
    if ((REG_CRYPTOLITE_STATUS(base) & CRYPTOLITE_STATUS_BUSY_Msk) != 0UL)
    {
        return CY_CRYPTOLITE_HW_BUSY;
    }

    totalMessageSizeInBits = ((uint64_t)(cfContext->messageSize) + (uint64_t)(cfContext->msgIdx)) * 8U;
    /*Append one bit to end and clear rest of block*/
    cfContext->message[cfContext->msgIdx] = 0x80U;
    idx = cfContext->msgIdx + 1U;

    for ( ; idx < CY_CRYPTOLITE_SHA256_BLOCK_SIZE; idx++ )
    {
        cfContext->message[idx] = 0U;
    }

    /*if message size is more than pad size process the block*/
    if (cfContext->msgIdx >= CY_CRYPTOLITE_SHA256_PAD_SIZE)
    {
        err = Cy_Cryptolite_Sha256_Process(base, cfContext);
        if(CY_CRYPTOLITE_SUCCESS != err)
        {
            return err;
        }
        /*clear the message block to finish*/
        for ( idx = 0; idx < CY_CRYPTOLITE_SHA256_PAD_SIZE; idx++ )
        {
            cfContext->message[idx] = 0U;
        }
    }

    /*append total message size in bits from 57 to 64 bytes */
    cfContext->message[CY_CRYPTOLITE_SHA256_BLOCK_SIZE - 1UL] = (uint8_t)totalMessageSizeInBits;
    cfContext->message[CY_CRYPTOLITE_SHA256_BLOCK_SIZE - 2UL] = (uint8_t)(totalMessageSizeInBits >> 8);
    cfContext->message[CY_CRYPTOLITE_SHA256_BLOCK_SIZE - 3UL] = (uint8_t)(totalMessageSizeInBits >> 16);
    cfContext->message[CY_CRYPTOLITE_SHA256_BLOCK_SIZE - 4UL] = (uint8_t)(totalMessageSizeInBits >> 24);
    cfContext->message[CY_CRYPTOLITE_SHA256_BLOCK_SIZE - 5UL] = (uint8_t)(totalMessageSizeInBits >> 32);
    cfContext->message[CY_CRYPTOLITE_SHA256_BLOCK_SIZE - 6UL] = (uint8_t)(totalMessageSizeInBits >> 40);
    cfContext->message[CY_CRYPTOLITE_SHA256_BLOCK_SIZE - 7UL] = (uint8_t)(totalMessageSizeInBits >> 48);
    cfContext->message[CY_CRYPTOLITE_SHA256_BLOCK_SIZE - 8UL] = (uint8_t)(totalMessageSizeInBits >> 56);

    /*Process the last block*/
    err = Cy_Cryptolite_Sha256_Process(base, cfContext);
    if(CY_CRYPTOLITE_SUCCESS != err)
    {
        return err;
    }

    /* This implementation uses little endian ordering and SHA uses big endian,
       reverse all the bytes in 32bit word when copying the final output hash.*/
    idx = (uint32_t)(CY_CRYPTOLITE_SHA256_HASH_SIZE / 4UL);
    hashptr = (uint8_t*)cfContext->hash;

    for( ; idx != 0U; idx--)
    {
        *(digest)   = *(hashptr+3);
        *(digest+1) = *(hashptr+2);
        *(digest+2) = *(hashptr+1);
        *(digest+3) = *(hashptr);

        digest  += 4U;
        hashptr += 4U;
    }

    return CY_CRYPTOLITE_SUCCESS;
}

/*******************************************************************************
* Cy_Cryptolite_Sha256_Free
******************************************************************************
*
* Clears the used memory and context data.
*
*  base
* The pointer to the CRYPTOLITE instance.
*
*  cfContext
* the pointer to the cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* return
* cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Free(CRYPTOLITE_Type *base,
                                    cy_stc_cryptolite_context_sha256_t *cfContext)
{
    uint32_t idx;
    (void)base;

    /* Input parameters verification */
    if (NULL == cfContext)
    {
        return CY_CRYPTOLITE_BAD_PARAMS;
    }

    /* Clear the context memory */
    for ( idx = 0; idx < CY_CRYPTOLITE_SHA256_BLOCK_SIZE; idx++ )
    {
        cfContext->message[idx] = 0U;
        cfContext->message_schedule[idx] = 0U;
    }
    for ( idx = 0; idx < CY_CRYPTOLITE_SHA256_HASH_SIZE/4U ; idx++ )
    {
        cfContext->hash[idx] = 0U;
    }

    return CY_CRYPTOLITE_SUCCESS;
}

/*******************************************************************************
* Cy_Cryptolite_Sha256_Run
******************************************************************************
*
* This function performs the SHA256 Hash function.
* Provide the required parameters and the pointer
* to the context structure when making this function call.
* It is independent of the previous Crypto state because it already contains
* preparation, calculation, and finalization steps.
*
*  base
* The pointer to the CRYPTOLITE instance.
*
*  cfContext
* the pointer to the cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
*  message
* The pointer to a message whose hash value is being computed.
*
*  messageSize
* The size of a message in bytes.
*
*  digest
* The pointer to the hash digest.
*
* return
* cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Run(CRYPTOLITE_Type *base,
                                        uint8_t const *message,
                                        uint32_t  messageSize,
                                        uint8_t *digest,
                                        cy_stc_cryptolite_context_sha256_t *cfContext)
{
    cy_en_cryptolite_status_t err = CY_CRYPTOLITE_BAD_PARAMS;
    /* Input parameters verification */
    if ((NULL == base) || (NULL == cfContext) || (NULL == digest) || ((NULL == message) && (0UL == messageSize)))
    {
        return err;
    }

    err = Cy_Cryptolite_Sha256_Init (base, cfContext);

    if (CY_CRYPTOLITE_SUCCESS == err)
    {
        err = Cy_Cryptolite_Sha256_Start (base, cfContext);
    }
    if (CY_CRYPTOLITE_SUCCESS == err)
    {
        err = Cy_Cryptolite_Sha256_Update (base, message, messageSize, cfContext);
    }
    if (CY_CRYPTOLITE_SUCCESS == err)
    {
        err = Cy_Cryptolite_Sha256_Finish (base, digest, cfContext);
    }
    if (CY_CRYPTOLITE_SUCCESS == err)
    {
        err = Cy_Cryptolite_Sha256_Free (base, cfContext);
    }

    return (err);
}

#endif
#endif

#if defined(__cplusplus)
}
#endif


#endif /* CY_IP_MXCRYPTOLITE */


/* [] END OF FILE */
