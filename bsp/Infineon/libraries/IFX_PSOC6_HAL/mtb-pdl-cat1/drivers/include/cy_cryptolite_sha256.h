/***************************************************************************//**
* \file cy_cryptolite_sha256.h
* \version 2.0
*
* \brief
*  This file provides common constants and parameters
*  for the Cryptolite SHA256 driver.
*
********************************************************************************
* Copyright 2020 Cypress Semiconductor Corporation
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
#if !defined (CY_CRYPTOLITE_SHA256_H)
#define CY_CRYPTOLITE_SHA256_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTOLITE)

#if defined(__cplusplus)
extern "C" {
#endif

#include "cy_cryptolite_common.h"

#if (CRYPTOLITE_SHA_PRESENT == 1)
#if defined(CY_CRYPTOLITE_CFG_SHA_C) && defined(CY_CRYPTOLITE_CFG_SHA2_256_ENABLED)

/** \cond INTERNAL */
/** PAD size for the SHA256(in bytes)    */
#define CY_CRYPTOLITE_SHA256_PAD_SIZE           (56uL)
/** \endcond */

/**
* \addtogroup group_cryptolite_macros
* \{
*/
/** Block size for the SHA256(in bytes)  */
#define CY_CRYPTOLITE_SHA256_BLOCK_SIZE         (64UL)

/** HASH size for the SHA256(in bytes)   */
#define CY_CRYPTOLITE_SHA256_HASH_SIZE          (32UL)

/** \} group_cryptolite_macros */


/**
* \addtogroup group_cryptolite_data_structures
* \{
*/

/** The structure for storing the SHA256 context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    uint32_t msgblock[CY_CRYPTOLITE_SHA256_BLOCK_SIZE / 4u];
    uint32_t hash[CY_CRYPTOLITE_SHA256_HASH_SIZE / 4u];
    uint32_t message_schedule[CY_CRYPTOLITE_SHA256_BLOCK_SIZE];
    uint8_t *message;
    uint32_t messageSize;
    uint32_t msgIdx;
    /** Operation data descriptors */
    cy_stc_cryptolite_descr_t message_schedule_struct;
    cy_stc_cryptolite_descr_t message_process_struct;
    /** \endcond */
} cy_stc_cryptolite_context_sha256_t;


/** \} group_cryptolite_data_structures */

/**
* \addtogroup group_cryptolite_lld_sha_functions
* \{
*/
/*******************************************************************************
* Function Name: Cy_Cryptolite_Sha256_Init
****************************************************************************//**
*
* The function to initialize the SHA256 operation.
*
* \param base
* The pointer to the Cryptolite instance.
*
* \param cfContext
* The pointer to the \ref cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Init(CRYPTOLITE_Type *base,
                                        cy_stc_cryptolite_context_sha256_t *cfContext);

/*******************************************************************************
* Function Name: Cy_Cryptolite_Sha256_Start
****************************************************************************//**
*
* Initializes the initial Hash vector.
*
* \param base
* The pointer to the CRYPTOLITE instance.
*
* \param cfContext
* The pointer to the \ref cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Start(CRYPTOLITE_Type *base,
                                        cy_stc_cryptolite_context_sha256_t *cfContext);

/*******************************************************************************
* Function Name: Cy_Cryptolite_Sha256_Update
****************************************************************************//**
*
* Performs the SHA256 calculation on one message.
*
* \param base
* The pointer to the CRYPTOLITE instance.
*
* \param message
* The SAHB mapped address pointer to the message whose Hash is being computed.
*
* \param messageSize
* The size of the message whose Hash is being computed.
*
* \param cfContext
* The pointer to the \ref cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
* \note There is no alignment or size restriction for message buffer, However providing
* a four byte aligned buffer with size in multiple of \ref CY_CRYPTOLITE_SHA256_BLOCK_SIZE,
* will result in best execution time.
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Update(CRYPTOLITE_Type *base,
                                                    uint8_t const *message,
                                                    uint32_t  messageSize,
                                                    cy_stc_cryptolite_context_sha256_t *cfContext);

/*******************************************************************************
* Function Name: Cy_Cryptolite_Sha256_Finish
****************************************************************************//**
*
* Completes the SHA256 calculation.
*
* \param base
* The pointer to the CRYPTOLITE instance.
*
* \param digest
* The SAHB mapped address pointer to the calculated Hash digest.
*
* \param cfContext
* The pointer to the \ref cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Finish(CRYPTOLITE_Type *base,
                               uint8_t *digest,
                               cy_stc_cryptolite_context_sha256_t *cfContext);

/*******************************************************************************
* Function Name: Cy_Cryptolite_Sha256_Free
****************************************************************************//**
*
* Clears the used memory and context data.
*
* \param base
* The pointer to the CRYPTOLITE instance.
*
* \param cfContext
* The pointer to the \ref cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Free(CRYPTOLITE_Type *base,
                                                    cy_stc_cryptolite_context_sha256_t *cfContext);

/*******************************************************************************
* Function Name: Cy_Cryptolite_Sha256_Run
****************************************************************************//**
*
* This function performs the SHA256 Hash function.
* Provide the required parameters and the pointer
* to the context structure when making this function call.
* It is independent of the previous Crypto state because it already contains
* preparation, calculation, and finalization steps.
*
* \param base
* The pointer to the CRYPTOLITE instance.
*
* \param message
* The SAHB mapped address pointer to a message whose hash value is being computed.
*
* \param messageSize
* The size of a message in bytes.
*
* \param digest
* The SAHB mapped address pointer to the hash digest.
*
* \param cfContext
* The pointer to the \ref cy_stc_cryptolite_context_sha256_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
* \note There is no alignment or size restriction for message buffer, However providing
* a four byte aligned buffer with size in multiple of \ref CY_CRYPTOLITE_SHA256_BLOCK_SIZE,
* will result in best execution time.
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Run(CRYPTOLITE_Type *base,
                                        uint8_t const *message,
                                        uint32_t  messageSize,
                                        uint8_t *digest,
                                        cy_stc_cryptolite_context_sha256_t *cfContext);

#endif /* #if (CY_CRYPTOLITE_CFG_SHA_C)*/
#endif /* #if CRYPTOLITE_SHA_PRESENT*/

/** \} group_cryptolite_lld_sha_functions */
#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTOLITE */

#endif /* #if !defined (CY_CRYPTOLITE_SHA256_H) */

/* [] END OF FILE */
