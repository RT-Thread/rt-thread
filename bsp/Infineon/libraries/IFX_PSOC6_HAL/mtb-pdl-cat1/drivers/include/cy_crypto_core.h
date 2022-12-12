/***************************************************************************//**
* \file cy_crypto_core.h
* \version 2.50
*
* \brief
*  This file provides common constants and parameters
*  for the Crypto driver core interface.
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
* \addtogroup group_crypto_lld_api
* \{
*   Use the low-level API for direct access to the Crypto hardware.
*
*   The functions and other declarations used in this part of the driver are in
*   cy_crypto_core.h. You can also include cy_pdl.h to get
*   access to all functions and declarations in the PDL.
*
*   Firmware initializes and starts the Crypto operations. The firmware then
*   provides the configuration data required for the desired cryptographic
*   technique.
*
*   \defgroup group_crypto_lld_hw Control and Status
*   \{
*     \defgroup group_crypto_lld_hw_functions Functions
*   \}
*   \defgroup group_crypto_lld_symmetric Symmetric Key Algorithms (AES, DES, TDES)
*   \{
*     \defgroup group_crypto_lld_symmetric_functions Functions
*   \}
*   \defgroup group_crypto_lld_asymmetric Asymmetric Key Algorithms (RSA, ECP, ECDSA)
*   \{
*       \defgroup group_crypto_lld_asymmetric_functions Functions
*       \defgroup group_crypto_lld_asymmetric_enums Enumerated Types
*   \}
*   \defgroup group_crypto_lld_sha Hash Operations (SHA)
*   \{
*     \defgroup group_crypto_lld_sha_functions Functions
*   \}
*   \defgroup group_crypto_lld_mac Message Authentication Code (CMAC, HMAC)
*   \{
*     \defgroup group_crypto_lld_mac_functions Functions
*   \}
*   \defgroup group_crypto_lld_crc Cyclic Redundancy Code (CRC)
*   \{
*     \defgroup group_crypto_lld_crc_functions Functions
*   \}
*   \defgroup group_crypto_lld_rng Random Number Generation (TRNG, PRNG)
*   \{
*     \defgroup group_crypto_lld_rng_functions Functions
*   \}
*   \defgroup group_crypto_lld_vu Vector Unit (VU)
*   \{
*     \defgroup group_crypto_lld_vu_functions Functions
*   \}
*   \defgroup group_crypto_lld_mem Memory Streaming Functions
*   \{
*     \defgroup group_crypto_lld_mem_functions Functions
*   \}
* \} */

#if !defined (CY_CRYPTO_CORE_H)
#define CY_CRYPTO_CORE_H

#include "cy_crypto_core_aes.h"
#include "cy_crypto_core_crc.h"
#include "cy_crypto_core_cmac.h"
#include "cy_crypto_core_des.h"
#include "cy_crypto_core_ecc.h"
#include "cy_crypto_core_ecc_nist_p.h"
#include "cy_crypto_core_hmac.h"
#include "cy_crypto_core_hw.h"
#include "cy_crypto_core_prng.h"
#include "cy_crypto_core_mem.h"
#include "cy_crypto_core_rsa.h"
#include "cy_crypto_core_sha.h"
#include "cy_crypto_core_trng.h"
#include "cy_crypto_core_vu.h"

#endif /* #if !defined (CY_CRYPTO_CORE_H) */

/* [] END OF FILE */
