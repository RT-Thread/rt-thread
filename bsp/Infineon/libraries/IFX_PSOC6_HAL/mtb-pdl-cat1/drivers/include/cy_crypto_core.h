/***************************************************************************//**
* \file cy_crypto_core.h
* \version 2.70
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
* \section group_crypto_lld_common_use_cases Common Use Cases
*
* \subsection group_crypto_lld_crypto_enable  Crypto Hardware Enable
*
* Use \ref Cy_Crypto_Core_Enable to enable the Crypto IP block, After this
* call, the Crypto driver is ready to execute crypto functions
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreStartCryptoUse
*
* \subsection group_crypto_lld_crypto_disable  Crypto Hardware Disable
*
* Use \ref Cy_Crypto_Core_Disable to disable the Crypto IP block and call
* \ref Cy_Crypto_Core_ClearVuRegisters to clear whole register file, After this
* call, No crypto function should be executed
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreStopCryptoUse
*
* \subsection group_crypto_lld_Use_TDES TDES encryption
*
* To encrypt a message using the TDES algorithm:
*
*   - Place three DES keys into an array,
*   - Call \ref Cy_Crypto_Core_Tdes with required parameters, including the array
*     of keys
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreTdesUse
*
* \subsection group_crypto_lld_Use_DES DES encryption
*
* To encrypt a message using the DES algorithm:
*   - Place DES key into an array,
*   - Call \ref Cy_Crypto_Core_Des with required parameters, including the key
*     array
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreDesUse
*
* \subsection group_crypto_lld_Use_AES AES encryption
*
* The Crypto driver provides a four AES encryption algorithms (ECB, CBC, CFB
* and CTR) that are used similarly.
*
* To encrypt a message using AES ECB algorithm (as example):
*   - Place AES key into array of appropriate size
*   - Use \ref Cy_Crypto_Core_Aes_Init to configure the operation
*   - Call \ref Cy_Crypto_Core_Aes_Ecb (\ref Cy_Crypto_Core_Aes_Cbc,
*     \ref Cy_Crypto_Core_Aes_Cfb or \ref Cy_Crypto_Core_Aes_Ctr) with appropriate
*     parameters to make an operation
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreAesEcbUse
*
* \subsection group_crypto_lld_Use_CRC CRC Calculation
*
* To calculate CRC of a data image:
*   - Use \ref Cy_Crypto_Core_Crc_CalcInit to set parameters for selected CRC mode,
*   - Call \ref Cy_Crypto_Core_Crc_Calc to calculate CRC for a data image.
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreCrcUse
*
* \subsection group_crypto_lld_Use_SHA SHA digest calculation
*
* To calculate a SHA digest of a message:
*   - Call \ref Cy_Crypto_Core_Sha with appropriate parameters to make an
*     operation
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreSha256Use
*
* \subsection group_crypto_lld_Use_RSA_VER RSA signature verification
*
* To verify the RSA signature of the data image:
*   - Fill RSA public key structure by RSA public key data
*   - Use \ref Cy_Crypto_Core_Sha to calculate SHA digest of the data image
*   - Use \ref Cy_Crypto_Core_Rsa_Proc to decrypt present encrypted signature
*   - Use \ref Cy_Crypto_Core_Rsa_Verify to verify the decrypted signature with
*     calculated SHA digest
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreRsaVerUse
*
* \section group_crypto_lld_rsa_considerations RSA Usage Considerations
*
* General RSA encryption and decryption is supported.
* \ref Cy_Crypto_Core_Rsa_Proc encrypts or decrypts data based on the parameters
* passed to the function. If you pass in plain text and a public key, the output
* is encrypted (cipher text). If you pass in cipher text and a private key, the
* output is decrypted (plain text).
*
* One parameter for this function call is a structure that defines the key:
* cy_stc_crypto_rsa_pub_key_t. The four modulus and exponent fields are
* mandatory. They represent the data for either the public or private key as
* appropriate.
*
* \note The <b>modulus</b> and <b>exponent</b> values in the
* \ref cy_stc_crypto_rsa_pub_key_t must be in little-endian order.<br>
* Use the \ref Cy_Crypto_Core_InvertEndianness function to convert to or from
* little-endian order.
*
* The remaining fields represent three pre-calculated coefficients that can
* reduce execution time by up to 5x. The fields are: coefficient for Barrett
* reduction, binary inverse of the modulus, and the result of
* (2^moduloLength mod modulo). These fields are optional, and can be set to NULL.
*
* Calculate these coefficients with \ref Cy_Crypto_Core_Rsa_Coef.
* Pass them in the address of the key structure with the modulus and exponent
* values for the key. The function returns the coefficients for the key in the
* key structure, replacing any previous values.
*
* The RSA functionality also implements functions to decrypt a signature using
* a public key. This signature must follow the RSASSA-PKCS-v1_5 standard.
* The signature must contain a SHA digest (hash).
* MD2, MD4, and MD5 message digests are not supported.
*
* An encrypted signature is stored as big-endian data. It must be inverted for
* RSA processing. To use the provided signature decryption, firmware must
*   -# Calculate the SHA digest of the data to be verified with
*      \ref Cy_Crypto_Core_Sha.
*   -# Ensure that the RSA signature is in little-endian format.
*      Use \ref Cy_Crypto_Core_InvertEndianness.
*   -# Decrypt the RSA signature with a public key, by calling
*      \ref Cy_Crypto_Core_Rsa_Proc.
*   -# Invert the byte order of the output, to return to big-endian format.
*      Use \ref Cy_Crypto_Core_InvertEndianness.
*   -# Call \ref Cy_Crypto_Core_Rsa_Verify (which requires data in big-endian format).
*
* \subsection group_crypto_lld_Use_CMAC CMAC calculation
*
* To calculate CMAC of a message:
*   - Place AES key into array of appropriate size
*   - Call \ref Cy_Crypto_Core_Cmac with appropriate parameters to make an
*     operation
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreCmacUse
*
* \subsection group_crypto_lld_Use_HMAC HMAC calculation
*
* To calculate HMAC of a message:
*   - Place HMAC key into array of appropriate size
*   - Call \ref Cy_Crypto_Core_Hmac with appropriate parameters to make an
*     operation
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreHmacUse
*
* \subsection group_crypto_lld_Use_PRNG Pseudo Random Number Generation
*
* To generate a pseudo random number:
*   - Use \ref Cy_Crypto_Core_Prng_Init to set required parameters,
*   - Call \ref Cy_Crypto_Core_Prng.
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCorePrngUse
*
* \subsection group_crypto_lld_Use_TRNG True Random Number Generation
*
* To generate a true random number:
*   - Call \ref Cy_Crypto_Core_Trng with needed parameters.
*
* Code example:
* \snippet crypto/snippet/main.c snippet_myCryptoCoreTrngUse
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
