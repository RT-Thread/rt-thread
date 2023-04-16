/***************************************************************************//**
* \file cy_cryptolite.h
* \version 2.0
*
* \brief
*  This file provides interface header
*  for the Cryptolite PDL driver.
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
* \note IP Supported: CRYPTOLITE
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
* \section group_cryptolite_sha256_configuration_considerations Configuration Considerations
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
* \section group_cryptolite_sha256_definitions Definitions
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
* \section group_cryptolite_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>2.0</td>
*     <td>Renamed the sha256 context structure from  cy_stc_cryptolite_context_sha_t to cy_stc_cryptolite_context_sha256_t </td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial Version</td>
*     <td></td>
*   </tr>
* </table>
*   \defgroup group_cryptolite_lld_sha Hash operations (SHA)
*   \{
*     \defgroup group_cryptolite_lld_sha_functions Functions
*   \}
* \defgroup group_cryptolite_data_structures Common Data Structures
* \defgroup group_cryptolite_enums Common Enumerated Types
* \defgroup group_cryptolite_macros Macros
*/

#if !defined (CY_CRYPTOLITE_H)
#define CY_CRYPTOLITE_H

#include "cy_device.h"

#if defined (CY_IP_MXCRYPTOLITE)

#include "cy_cryptolite_sha256.h"

#endif /* CY_IP_MXCRYPTOLITE */

#endif /* #if !defined (CY_CRYPTOLITE_H) */
/** \} group_cryptolite */

/* [] END OF FILE */
