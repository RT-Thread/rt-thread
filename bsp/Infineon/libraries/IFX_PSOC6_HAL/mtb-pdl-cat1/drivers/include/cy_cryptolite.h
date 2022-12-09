/***************************************************************************//**
* \file cy_cryptolite.h
* \version 1.0.0
*
* \brief
*  This file provides common constants and parameters
*  for the Cryptolite driver.
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
/**
* \addtogroup group_cryptolite
* \{
* \note IP Supported: CRYPTO
* \note Device Categories: CAT1B. Please refer <a href="usergroup1.html">Device Catalog</a>.
*
* The Cryptolite driver provides a public API to perform SHA256 hash
* calculation, using a cryptolite hardware IP block to accelerate operation.
*
* The functions and other declarations used in this driver are in cy_cryptolite.h.
* You can also include cy_pdl.h to get access to all functions and declarations in the PDL.
*
* The Cryptolite driver supports only SHA256.
*
* \section group_cryptolite_configuration_considerations Configuration Considerations
*
* Firmware sets up a cryptographic operation by passing in the required data as
* parameters in the function call.
*
* Cryptolite SHA256 function require a context. A context is a data
* structure that the driver uses for its operations. Firmware declares a
* context (allocates memory) but does not write or read the values in that
* context. In effect, the context is a scratch pad you provide to the driver.
* The driver uses the context to store and manipulate data during cryptographic
* operations. The Cryptolite driver header file declare all the required structures
* for context.
*
* Note: Cryptolite works only with SAHB mapped address, User must map any CBUS mapped
*       address to SAHB address before using the API.
*
* \section group_cryptolite_definitions Definitions
*
* <table class="doxtable">
*   <tr>
*     <th>Term</th>
*     <th>Definition</th>
*   </tr>
*
*   <tr>
*     <td>Secure Hash Algorithm (SHA)</td>
*     <td>A cryptographic hash function.
*     This function takes a message of an arbitrary length and reduces it to a
*     fixed-length residue or message digest after performing a series of
*     mathematically defined operations that practically guarantee that any
*     change in the message will change the hash value. It is used for message
*     authentication by transmitting a message with a hash value appended to it
*     and recalculating the message hash value using the same algorithm at the
*     recipient's end. If the hashes differ, then the message is corrupted.
*     For more information see [Secure Hash standard description]
*     (https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf).
*     </td>
*   </tr>
*
* </table>
*
* \defgroup group_cryptolite_macros Macros
* \defgroup group_cryptolite_functions Functions
* \defgroup group_cryptolite_data_structures Data Structures
* \defgroup group_cryptolite_enums Enumerated Types
*/

#if !defined (CY_CRYPTOLITE_H)
#define CY_CRYPTOLITE_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTOLITE)

#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include "cy_sysint.h"
#include "cy_cryptolite_hw.h"

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

/** Driver major version */
#define CY_CRYPTOLITE_DRV_VERSION_MAJOR         1

/** Driver minor version */
#define CY_CRYPTOLITE_DRV_VERSION_MINOR         0

/** Cryptolite Driver PDL ID */
#define CY_CRYPTOLITE_ID                        CY_PDL_DRV_ID(0x74u)
/** \} group_cryptolite_macros */

/**
* \addtogroup group_cryptolite_enums
* \{
*/

/** Errors of the Cryptolite block */
typedef enum
{
    /** Operation completed successfully. */
    CY_CRYPTOLITE_SUCCESS             = 0x00u,

    /** The Crypto operation parameters are incorrect. */
    CY_CRYPTOLITE_BAD_PARAMS          = CY_CRYPTOLITE_ID | CY_PDL_STATUS_ERROR   | 0x01u,

    /** The Crypto HW is busy. */
    CY_CRYPTOLITE_HW_BUSY             = CY_CRYPTOLITE_ID | CY_PDL_STATUS_ERROR   | 0x02u,

    /** The Crypto AHB bus error. */
    CY_CRYPTOLITE_BUS_ERROR           = CY_CRYPTOLITE_ID | CY_PDL_STATUS_ERROR   | 0x03u

} cy_en_cryptolite_status_t;

/** \} group_cryptolite_enums */

/**
* \addtogroup group_cryptolite_data_structures
* \{
*/

/** \cond INTERNAL */
/** The cryptolite SHA256 IP descriptor structure.
* All fields for the structure are internal. Firmware never reads or
* writes these values.
*/
typedef struct sha_struct_t {
   uint32_t data0;
   uint32_t data1;
   uint32_t data2;
} cy_stc_cryptolite_sha_descr_t;
/** \endcond */

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
    cy_stc_cryptolite_sha_descr_t message_schedule_struct;
    cy_stc_cryptolite_sha_descr_t message_process_struct;
    /** \endcond */
} cy_stc_cryptolite_context_sha_t;


/** \} group_cryptolite_data_structures */

/**
* \addtogroup group_cryptolite_functions
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
* The pointer to the \ref cy_stc_cryptolite_context_sha_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Init(CRYPTO_Type *base,
                                        cy_stc_cryptolite_context_sha_t *cfContext);

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
* The pointer to the \ref cy_stc_cryptolite_context_sha_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Start(CRYPTO_Type *base,
                                        cy_stc_cryptolite_context_sha_t *cfContext);

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
* The pointer to the \ref cy_stc_cryptolite_context_sha_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
* \note There is no alignment or size restriction for message buffer, However providing
* a four byte aligned buffer with size in multiple of \ref CY_CRYPTOLITE_SHA256_BLOCK_SIZE,
* will result in best execution time.
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Update(CRYPTO_Type *base,
                                                    uint8_t const *message,
                                                    uint32_t  messageSize,
                                                    cy_stc_cryptolite_context_sha_t *cfContext);

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
* The pointer to the \ref cy_stc_cryptolite_context_sha_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Finish(CRYPTO_Type *base,
                               uint8_t *digest,
                               cy_stc_cryptolite_context_sha_t *cfContext);

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
* The pointer to the \ref cy_stc_cryptolite_context_sha_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Free(CRYPTO_Type *base,
                                                    cy_stc_cryptolite_context_sha_t *cfContext);

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
* The pointer to the \ref cy_stc_cryptolite_context_sha_t structure that stores all
* internal variables for Cryptolite driver.
*
* \return
* \ref cy_en_cryptolite_status_t
*
* \note There is no alignment or size restriction for message buffer, However providing
* a four byte aligned buffer with size in multiple of \ref CY_CRYPTOLITE_SHA256_BLOCK_SIZE,
* will result in best execution time.
*******************************************************************************/
cy_en_cryptolite_status_t Cy_Cryptolite_Sha256_Run(CRYPTO_Type *base,
                                        uint8_t const *message,
                                        uint32_t  messageSize,
                                        uint8_t *digest,
                                        cy_stc_cryptolite_context_sha_t *cfContext);

/** \} group_cryptolite_functions */
#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTOLITE */

#endif /* #if !defined (CY_CRYPTOLITE_H) */
/** \} group_cryptolite */

/* [] END OF FILE */
