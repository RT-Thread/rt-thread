/***************************************************************************//**
* \file cy_crypto_common.h
* \version 2.70
*
* \brief
*  This file provides common constants and parameters
*  for the Crypto driver.
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


#if !defined (CY_CRYPTO_COMMON_H)
#define CY_CRYPTO_COMMON_H

#include "cy_device.h"
#include "cy_device_headers.h"

#if defined (CY_IP_MXCRYPTO)

#include "cy_crypto_config.h"
#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include "cy_sysint.h"

/** Driver major version */
#define CY_CRYPTO_DRV_VERSION_MAJOR         2

/** Driver minor version */
#define CY_CRYPTO_DRV_VERSION_MINOR         70


/* Enable SHA functionality */
#if !defined(CPUSS_CRYPTO_SHA) && (defined(CPUSS_CRYPTO_SHA1) || defined(CPUSS_CRYPTO_SHA2))
    #define CPUSS_CRYPTO_SHA                (1)

    #if defined(CPUSS_CRYPTO_SHA2) && !defined(CPUSS_CRYPTO_SHA256)
    #define CPUSS_CRYPTO_SHA256             (1)
    #endif

    #if defined(CPUSS_CRYPTO_SHA2) && !defined(CPUSS_CRYPTO_SHA512)
    #define CPUSS_CRYPTO_SHA512             (1)
    #endif
#endif

#if !defined(CPUSS_CRYPTO_STR)
    #define CPUSS_CRYPTO_STR                (1)
#endif

#if !defined(CPUSS_CRYPTO_CHACHA) && defined(CY_CRYPTO_CFG_HW_V1_ENABLE)
#define CPUSS_CRYPTO_CHACHA (0)
#endif

/** \cond INTERNAL */

/* The width of the Crypto hardware registers values in bits. */
#define CY_CRYPTO_HW_REGS_WIDTH             (32UL)

/* Calculates the actual size in bytes of the bits value */
#define CY_CRYPTO_BYTE_SIZE_OF_BITS(x)      (uint32_t)(((uint32_t)(x) + 7U) >> 3U)

/* Calculates the actual size in 32-bit words of the bits value */
#define CY_CRYPTO_WORD_SIZE_OF_BITS(x)      (uint32_t)(((uint32_t)(x) + 31U) >> 5U)

/** \endcond */

/**
* \addtogroup group_crypto_cli_srv_macros
* \{
*/

/** Defines Crypto_Sync blocking execution type parameter */
#define CY_CRYPTO_SYNC_BLOCKING           (true)

/** Defines Crypto_Sync non-blocking execution type parameter */
#define CY_CRYPTO_SYNC_NON_BLOCKING       (false)

/** Defines the Crypto DES block size (in bytes). */
#define CY_CRYPTO_DES_BLOCK_SIZE          (8u)

/** Defines the Crypto DES key size (in bytes) */
#define CY_CRYPTO_DES_KEY_SIZE            (CY_CRYPTO_DES_BLOCK_SIZE)

/** Defines the Crypto TDES key size (in bytes) */
#define CY_CRYPTO_TDES_KEY_SIZE           (24u)


#if defined(CY_CRYPTO_CFG_AES_C)

/** Defines the Crypto AES block size (in bytes) */
#define CY_CRYPTO_AES_BLOCK_SIZE          (16u)

/** Defines the Crypto AES_128 key maximum size (in bytes) */
#define CY_CRYPTO_AES_128_KEY_SIZE        (16u)

/** Defines the Crypto AES_192 key maximum size (in bytes) */
#define CY_CRYPTO_AES_192_KEY_SIZE        (24u)

/** Defines the Crypto AES_256 key maximum size (in bytes) */
#define CY_CRYPTO_AES_256_KEY_SIZE        (32u)

/** Defines the Crypto AES key maximum size (in bytes) */
#define CY_CRYPTO_AES_MAX_KEY_SIZE        (CY_CRYPTO_AES_256_KEY_SIZE)

/** Defines the Crypto AES_256 key maximum size (in four-byte words) */
#define CY_CRYPTO_AES_MAX_KEY_SIZE_U32    (uint32_t)(CY_CRYPTO_AES_MAX_KEY_SIZE / 4UL)

/** Defines size of the AES block, in four-byte words */
#define CY_CRYPTO_AES_BLOCK_SIZE_U32      (uint32_t)(CY_CRYPTO_AES_BLOCK_SIZE / 4UL)

#endif /* defined(CY_CRYPTO_CFG_AES_C) */

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)

/* Defines for the SHA algorithm */
/** Block size for the SHA256 mode (in bytes)   */
#define CY_CRYPTO_SHA256_BLOCK_SIZE         (64u)
/** Pad size for the SHA256 mode (in bytes)   */
#define CY_CRYPTO_SHA256_PAD_SIZE           (56uL)

/** Block size for the SHA512 mode (in bytes)   */
#define CY_CRYPTO_SHA512_BLOCK_SIZE         (128u)
/** Pad size for the SHA512 mode (in bytes)   */
#define CY_CRYPTO_SHA512_PAD_SIZE           (112uL)

#if defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
    /** Hash size for the SHA384 mode (in bytes) */
    #define CY_CRYPTO_SHA384_DIGEST_SIZE        (48u)
    /** Hash size for the SHA512 mode (in bytes) */
    #define CY_CRYPTO_SHA512_DIGEST_SIZE        (64u)
    /** Hash size for the SHA512_224 mode (in bytes) */
    #define CY_CRYPTO_SHA512_224_DIGEST_SIZE    (28u)
    /** Hash size for the SHA512_256 mode (in bytes) */
    #define CY_CRYPTO_SHA512_256_DIGEST_SIZE    (32u)

/** \cond INTERNAL */
    /** Internal hash size for the SHA512_256 mode (in bytes) */
    #define CY_CRYPTO_SHA512_HASH_SIZE          (64u)
    /** Internal round mem size for the SHA512_256 mode (in bytes) */
    #define CY_CRYPTO_SHA512_ROUND_MEM_SIZE     (640uL)
/** \endcond */
#endif
#if defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
    /** Hash size for the SHA224 mode (in bytes) */
    #define CY_CRYPTO_SHA224_DIGEST_SIZE        (28u)
    /** Hash size for the SHA256 mode (in bytes) */
    #define CY_CRYPTO_SHA256_DIGEST_SIZE        (32u)

/** \cond INTERNAL */
    /** Internal hash size for the SHA256 mode (in bytes) */
    #define CY_CRYPTO_SHA256_HASH_SIZE          (32u)
    /** Internal round mem size for the SHA256 mode (in bytes) */
    #define CY_CRYPTO_SHA256_ROUND_MEM_SIZE     (256uL)
/** \endcond */
#endif
#if defined(CY_CRYPTO_CFG_SHA1_ENABLED)
    /** Hash size for the SHA1 mode (in bytes)   */
    #define CY_CRYPTO_SHA1_DIGEST_SIZE          (20u)
    /** Block size for the SHA1 mode (in bytes)  */
    #define CY_CRYPTO_SHA1_BLOCK_SIZE           (64u)

/** \cond INTERNAL */
    /** Internal hash size for the SHA1 mode (in bytes) */
    #define CY_CRYPTO_SHA1_HASH_SIZE            (20u)
    /** Internal round mem size for the SHA1 mode (in bytes) */
    #define CY_CRYPTO_SHA1_ROUND_MEM_SIZE       (320uL)
/** \endcond */
#endif

/** \cond INTERNAL */
#if defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
    #define CY_CRYPTO_SHA_MAX_DIGEST_SIZE       (CY_CRYPTO_SHA512_DIGEST_SIZE)
    #define CY_CRYPTO_SHA_MAX_BLOCK_SIZE        (CY_CRYPTO_SHA512_BLOCK_SIZE)
    #define CY_CRYPTO_SHA_MAX_HASH_SIZE         (CY_CRYPTO_SHA512_HASH_SIZE)
#elif defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
    #define CY_CRYPTO_SHA_MAX_DIGEST_SIZE       (CY_CRYPTO_SHA256_DIGEST_SIZE)
    #define CY_CRYPTO_SHA_MAX_BLOCK_SIZE        (CY_CRYPTO_SHA256_BLOCK_SIZE)
    #define CY_CRYPTO_SHA_MAX_HASH_SIZE         (CY_CRYPTO_SHA256_HASH_SIZE)
#elif defined(CY_CRYPTO_CFG_SHA1_ENABLED)
    #define CY_CRYPTO_SHA_MAX_DIGEST_SIZE       (CY_CRYPTO_SHA1_DIGEST_SIZE)
    #define CY_CRYPTO_SHA_MAX_BLOCK_SIZE        (CY_CRYPTO_SHA1_BLOCK_SIZE)
    #define CY_CRYPTO_SHA_MAX_HASH_SIZE         (CY_CRYPTO_SHA1_HASH_SIZE)
#else
    #define CY_CRYPTO_SHA_MAX_DIGEST_SIZE       (0u)
    #define CY_CRYPTO_SHA_MAX_BLOCK_SIZE        (0u)
    #define CY_CRYPTO_SHA_MAX_HASH_SIZE         (0u)
#endif

#if defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
    #define CY_CRYPTO_SHA_MAX_ROUND_MEM_SIZE    (CY_CRYPTO_SHA512_ROUND_MEM_SIZE)
#elif defined(CY_CRYPTO_CFG_SHA1_ENABLED)
    #define CY_CRYPTO_SHA_MAX_ROUND_MEM_SIZE    (CY_CRYPTO_SHA1_ROUND_MEM_SIZE)
#elif defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
    #define CY_CRYPTO_SHA_MAX_ROUND_MEM_SIZE    (CY_CRYPTO_SHA256_ROUND_MEM_SIZE)
#else
    #define CY_CRYPTO_SHA_MAX_ROUND_MEM_SIZE    (0u)
#endif
/** \endcond */

#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */


#if (CPUSS_CRYPTO_VU == 1) && defined(CY_CRYPTO_CFG_RSA_C)

/** \cond INTERNAL */
/** Processed message size for the RSA 1024Bit mode (in bytes) */
#define CY_CRYPTO_RSA1024_MESSAGE_SIZE      CY_CRYPTO_BYTE_SIZE_OF_BITS(1024u)
/** Processed message size for the RSA 1536Bit mode (in bytes) */
#define CY_CRYPTO_RSA1536_MESSAGE_SIZE      CY_CRYPTO_BYTE_SIZE_OF_BITS(1536u)
/** Processed message size for the RSA 2048Bit mode (in bytes) */
#define CY_CRYPTO_RSA2048_MESSAGE_SIZE      CY_CRYPTO_BYTE_SIZE_OF_BITS(2048u)
/** Processed message size for the RSA 3072Bit mode (in bytes) */
#define CY_CRYPTO_RSA3072_MESSAGE_SIZE      CY_CRYPTO_BYTE_SIZE_OF_BITS(3072u)
/** Processed message size for the RSA 4096Bit mode (in bytes) */
#define CY_CRYPTO_RSA4096_MESSAGE_SIZE      CY_CRYPTO_BYTE_SIZE_OF_BITS(4096u)
/** \endcond */

/**
* \addtogroup group_crypto_data_structures
* \{
*/

/**
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*
* The driver uses this structure to store and manipulate the RSA public key and
* additional coefficients to accelerate RSA calculation.
*
*  RSA key contained from two fields:
*  - n - modulus part of the key
*  - e - exponent part of the key.
*
* Other fields are accelerating coefficients and can be calculated by
* \ref Cy_Crypto_Rsa_CalcCoefs.
*
* \note The <b>modulus</b> and <b>exponent</b> values in the
* \ref cy_stc_crypto_rsa_pub_key_t must also be in little-endian order.<br>
* Use \ref Cy_Crypto_InvertEndianness function to convert to or from
* little-endian order.
*/
typedef struct
{
    /** \cond INTERNAL */
    /** The pointer to the modulus part of public key. */
    uint8_t *moduloPtr;
    /** The modulus length, in bits, maximum supported size is 2048Bit */
    uint32_t moduloLength;

    /** The pointer to the exponent part of public key */
    uint8_t *pubExpPtr;
    /** The exponent length, in bits, maximum supported size is 256Bit */
    uint32_t pubExpLength;

    /** The pointer to the Barrett coefficient. Memory for it should be
        allocated by user with size moduloLength + 1. */
    uint8_t *barretCoefPtr;

    /** The pointer to the binary inverse of the modulo. Memory for it
        should be allocated by user with size moduloLength. */
    uint8_t *inverseModuloPtr;

    /** The pointer to the (2^moduloLength mod modulo). Memory for it should
        be allocated by user with size moduloLength */
    uint8_t *rBarPtr;
/** \endcond */
} cy_stc_crypto_rsa_pub_key_t;

/** \} group_crypto_data_structures */

#endif /* (CPUSS_CRYPTO_VU == 1) && defined(CY_CRYPTO_CFG_RSA_C) */

/** Crypto Driver PDL ID */
#define CY_CRYPTO_ID                        CY_PDL_DRV_ID(0x0Cu)

/** \} group_crypto_cli_srv_macros */

/**
* \addtogroup group_crypto_config_structure
* \{
    The Crypto initialization configuration.
*   \note Should be the same for the Crypto Server and Crypto Client initialization.
*/

/** The Crypto user callback function type.
    Callback is called at the end of Crypto calculation. */
typedef void (*cy_crypto_callback_ptr_t)(void);

/** The Crypto configuration structure. */
typedef struct
{
    /** Defines the IPC channel used for client-server data exchange */
    uint32_t ipcChannel;

    /** Specifies the IPC notifier channel (IPC interrupt structure number)
        to notify server that data for the operation is prepared */
    uint32_t acquireNotifierChannel;

    /** Specifies the IPC notifier channel (IPC interrupt structure number)
        to notify client that operation is complete and data is valid */
    uint32_t releaseNotifierChannel;

    /** Specifies the release notifier interrupt configuration. It used for
        internal purposes and user doesn't fill it. */
    cy_stc_sysint_t releaseNotifierConfig;

    /** User callback function.
        If this field is NOT NULL, it called when Crypto operation
        is complete. */
    cy_crypto_callback_ptr_t userCompleteCallback;

    /** Server-side user IRQ handler function, called when data for the
        operation is prepared to process.
        - If this field is NULL, server will use own interrupt handler
          to get data.
        - If this field is not NULL, server will call this interrupt handler.
          This interrupt handler must call the
          \ref Cy_Crypto_Server_GetDataHandler to get data to process.

          Note: In the second case user should process data separately and
          clear interrupt by calling \ref Cy_Crypto_Server_Process.
          This model is used in the
          multitasking environment. */
    cy_israddress userGetDataHandler;

    /** Server-side user IRQ handler function, called when a Crypto hardware
        error occurs (interrupt was raised).
        - If this field is NULL - server will use own interrupt handler
          for error processing.
        - If this field is not NULL - server will call this interrupt handler.
          This interrupt handler must call the
          \ref Cy_Crypto_Server_ErrorHandler to clear the interrupt. */
    cy_israddress userErrorHandler;

    /** Specifies the prepared data notifier interrupt configuration. It used
        for internal purposes and user doesn't fill it. */
    cy_stc_sysint_t acquireNotifierConfig;

    /** Specifies the hardware error processing interrupt configuration. It used
        for internal purposes and user doesn't fill it. */
    cy_stc_sysint_t cryptoErrorIntrConfig;

} cy_stc_crypto_config_t;

/** \} group_crypto_config_structure */

/**
* \addtogroup group_crypto_cli_data_structures
* \{
*/

/** Structure for storing a description of a Crypto hardware error  */
typedef struct
{
    /**
     Captures error description information for one of obtained hardware error:
      - for <b>INSTR_OPC_ERROR</b>: - violating the instruction.
      - for <b>INSTR_CC_ERROR</b> : - violating the instruction condition code.
      - for <b>BUS_ERROR</b>      : - violating the transfer address. */
    uint32_t errorStatus0;

    /**
     [31]     - "1" - Indicates that hardware error has occurred and
                ERROR_STATUS0 and ERROR_STATUS1 captured valid error-information.
     [26..24] - The error source:
                - "0": <b>INSTR_OPC_ERROR</b> - an instruction decoder error.
                - "1": <b>INSTR_CC_ERROR</b> - an instruction condition code-error.
                - "2": <b>BUS_ERROR</b> - a bus master interface AHB-Lite bus-error.
                    - [5..4] - violating the transfer, the size attribute
                        - "0": an 8-bit transfer;
                        - "1": 16 bits transfer;
                        - "2": 32-bit transfer.
                    - [0] - violating the transfer, read the attribute
                - "3": <b>TR_AP_DETECT_ERROR</b> - True Random Generator error.
     */
    uint32_t errorStatus1;
} cy_stc_crypto_hw_error_t;

/** \} group_crypto_cli_data_structures */


/** The Crypto library functionality level. */
typedef enum
{
    CY_CRYPTO_NO_LIBRARY    = 0x00u,
    CY_CRYPTO_BASE_LIBRARY  = 0x01u,
    CY_CRYPTO_EXTRA_LIBRARY = 0x02u,
    CY_CRYPTO_FULL_LIBRARY  = 0x03u,
} cy_en_crypto_lib_info_t;


/**
* \addtogroup group_crypto_enums
* \{
*/

#if (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C)
/** The key length options for the AES method. */
typedef enum
{
    CY_CRYPTO_KEY_AES_128   = 0x00u,   /**< The AES key size is 128 bits */
    CY_CRYPTO_KEY_AES_192   = 0x01u,   /**< The AES key size is 192 bits */
    CY_CRYPTO_KEY_AES_256   = 0x02u    /**< The AES key size is 256 bits */
} cy_en_crypto_aes_key_length_t;
#endif /* (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C) */

/** Defines the direction of the Crypto methods */
typedef enum
{
    /** The forward mode, plain text will be encrypted into cipher text */
    CY_CRYPTO_ENCRYPT   = 0x00u,
    /** The reverse mode, cipher text will be decrypted into plain text */
    CY_CRYPTO_DECRYPT   = 0x01u
} cy_en_crypto_dir_mode_t;

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)
/** Defines modes of SHA method */
typedef enum
{
#if (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED)
    CY_CRYPTO_MODE_SHA1          = 0x00u,   /**< Sets the SHA1 mode */
#endif /* (CPUSS_CRYPTO_SHA1 == 1) && defined(CY_CRYPTO_CFG_SHA1_ENABLED) */

#if (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED)
    CY_CRYPTO_MODE_SHA224        = 0x01u,   /**< Sets the SHA224 mode */
    CY_CRYPTO_MODE_SHA256        = 0x02u,   /**< Sets the SHA256 mode */
#endif /* (CPUSS_CRYPTO_SHA256 == 1) && defined(CY_CRYPTO_CFG_SHA2_256_ENABLED) */

#if (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED)
    CY_CRYPTO_MODE_SHA384        = 0x03u,   /**< Sets the SHA384 mode */
    CY_CRYPTO_MODE_SHA512        = 0x04u,   /**< Sets the SHA512 mode */
    CY_CRYPTO_MODE_SHA512_256    = 0x05u,   /**< Sets the SHA512/256 mode */
    CY_CRYPTO_MODE_SHA512_224    = 0x06u,   /**< Sets the SHA512/224 mode */
#endif /* (CPUSS_CRYPTO_SHA512 == 1) && defined(CY_CRYPTO_CFG_SHA2_512_ENABLED) */
    CY_CRYPTO_MODE_SHA_NONE    = 0x07u,   /**< Sets the SHA None mode */


} cy_en_crypto_sha_mode_t;
#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */

#if defined(CY_CRYPTO_CFG_RSA_C) && defined(CY_CRYPTO_CFG_RSA_VERIFY_ENABLED)
/** Signature verification status */
typedef enum
{
    CY_CRYPTO_RSA_VERIFY_SUCCESS = 0x00u,   /**< PKCS1-v1.5 verify SUCCESS */
    CY_CRYPTO_RSA_VERIFY_FAIL    = 0x01u    /**< PKCS1-v1.5 verify FAILED */
} cy_en_crypto_rsa_ver_result_t;
#endif /* defined(CY_CRYPTO_CFG_RSA_C) && defined(CY_CRYPTO_CFG_RSA_VERIFY_ENABLED) */

/** Errors of the Crypto block */
typedef enum
{
    /** Operation completed successfully. */
    CY_CRYPTO_SUCCESS             = 0x00u,

    /** A hardware error occurred, detailed information is in stc_crypto_hw_error_t. */
    CY_CRYPTO_HW_ERROR            = CY_CRYPTO_ID | CY_PDL_STATUS_ERROR   | 0x01u,

    /** The size of input data is not multiple of 16. */
    CY_CRYPTO_SIZE_NOT_X16        = CY_CRYPTO_ID | CY_PDL_STATUS_ERROR   | 0x02u,

    /** The key for the DES method is weak. */
    CY_CRYPTO_DES_WEAK_KEY        = CY_CRYPTO_ID | CY_PDL_STATUS_WARNING | 0x03u,

    /** Communication between the client and server via IPC is broken. */
    CY_CRYPTO_COMM_FAIL           = CY_CRYPTO_ID | CY_PDL_STATUS_ERROR   | 0x04u,

    /** The Crypto server is not started. */
    CY_CRYPTO_SERVER_NOT_STARTED  = CY_CRYPTO_ID | CY_PDL_STATUS_ERROR   | 0x06u,

    /** The Crypto server in process state. */
    CY_CRYPTO_SERVER_BUSY         = CY_CRYPTO_ID | CY_PDL_STATUS_INFO    | 0x07u,

    /** The Crypto driver is not initialized. */
    CY_CRYPTO_NOT_INITIALIZED     = CY_CRYPTO_ID | CY_PDL_STATUS_ERROR   | 0x08u,

    /** The Crypto hardware is not enabled. */
    CY_CRYPTO_HW_NOT_ENABLED      = CY_CRYPTO_ID | CY_PDL_STATUS_ERROR   | 0x09u,

    /** The Crypto operation is not supported. */
    CY_CRYPTO_NOT_SUPPORTED       = CY_CRYPTO_ID | CY_PDL_STATUS_ERROR   | 0x0Au,

    /** The Crypto operation parameters are incorrect. */
    CY_CRYPTO_BAD_PARAMS          = CY_CRYPTO_ID | CY_PDL_STATUS_ERROR   | 0x0Bu,

    /** The key for the DES method is weak. */
    CY_CRYPTO_TRNG_UNHEALTHY      = CY_CRYPTO_ID | CY_PDL_STATUS_WARNING | 0x0Cu

} cy_en_crypto_status_t;

/** \} group_crypto_enums */

/**
* \addtogroup group_crypto_lld_asymmetric_enums
* \{
*/

#if (CPUSS_CRYPTO_VU == 1) && defined (CY_CRYPTO_CFG_ECP_C)
/** List of supported elliptic curve IDs */
typedef enum {
    CY_CRYPTO_ECC_ECP_NONE = 0,
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED)
    CY_CRYPTO_ECC_ECP_SECP192R1,
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP192R1_ENABLED) */
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED)
    CY_CRYPTO_ECC_ECP_SECP224R1,
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP224R1_ENABLED) */
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED)
    CY_CRYPTO_ECC_ECP_SECP256R1,
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP256R1_ENABLED) */
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED)
    CY_CRYPTO_ECC_ECP_SECP384R1,
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP384R1_ENABLED) */
#if defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED)
    CY_CRYPTO_ECC_ECP_SECP521R1,
#endif /* defined(CY_CRYPTO_CFG_ECP_DP_SECP521R1_ENABLED) */
    /* Count of supported curves */
    CY_CRYPTO_ECC_ECP_CURVES_CNT
} cy_en_crypto_ecc_curve_id_t;

#endif /* (CPUSS_CRYPTO_VU == 1) && defined (CY_CRYPTO_CFG_ECP_C) */

/** \} group_crypto_lld_asymmetric_enums */

/** \cond INTERNAL */

/** Instruction to communicate between Client and Server */
typedef enum
{
    CY_CRYPTO_INSTR_UNKNOWN      = 0x00u,
    CY_CRYPTO_INSTR_ENABLE       = 0x01u,
    CY_CRYPTO_INSTR_DISABLE      = 0x02u,

#if (CPUSS_CRYPTO_PR == 1) && defined(CY_CRYPTO_CFG_PRNG_C)
    CY_CRYPTO_INSTR_PRNG_INIT    = 0x03u,
    CY_CRYPTO_INSTR_PRNG         = 0x04u,
#endif /* (CPUSS_CRYPTO_PR == 1) && defined(CY_CRYPTO_CFG_PRNG_C) */

#if (CPUSS_CRYPTO_TR == 1) && defined(CY_CRYPTO_CFG_TRNG_C)
    CY_CRYPTO_INSTR_TRNG_INIT    = 0x05u,
    CY_CRYPTO_INSTR_TRNG         = 0x06u,
#endif /* (CPUSS_CRYPTO_TR == 1) && defined(CY_CRYPTO_CFG_TRNG_C) */

#if (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C)
    CY_CRYPTO_INSTR_AES_INIT     = 0x07u,
    CY_CRYPTO_INSTR_AES_ECB      = 0x08u,

#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CBC)
    CY_CRYPTO_INSTR_AES_CBC      = 0x09u,
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CBC) */
#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CFB)
    CY_CRYPTO_INSTR_AES_CFB      = 0x0Au,
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CFB) */
#if defined(CY_CRYPTO_CFG_CIPHER_MODE_CTR)
    CY_CRYPTO_INSTR_AES_CTR      = 0x0Bu,
#endif /* defined(CY_CRYPTO_CFG_CIPHER_MODE_CTR) */
#endif /* (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C) */

#if (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_CMAC_C)
    CY_CRYPTO_INSTR_CMAC         = 0x0Cu,
#endif /* (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_CMAC_C) */

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)
    CY_CRYPTO_INSTR_SHA          = 0x0Du,
#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_HMAC_C)
    CY_CRYPTO_INSTR_HMAC         = 0x0Eu,
#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_HMAC_C) */

#if (CPUSS_CRYPTO_STR == 1)
    CY_CRYPTO_INSTR_MEM_CPY      = 0x0Fu,
    CY_CRYPTO_INSTR_MEM_SET      = 0x10u,
    CY_CRYPTO_INSTR_MEM_CMP      = 0x11u,
    CY_CRYPTO_INSTR_MEM_XOR      = 0x12u,
#endif /* #if (CPUSS_CRYPTO_STR == 1) */

#if (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C)
    CY_CRYPTO_INSTR_CRC_INIT     = 0x13u,
    CY_CRYPTO_INSTR_CRC          = 0x14u,
#endif /* (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C) */

#if (CPUSS_CRYPTO_DES == 1) && defined(CY_CRYPTO_CFG_DES_C)
    CY_CRYPTO_INSTR_DES          = 0x15u,
    CY_CRYPTO_INSTR_3DES         = 0x16u,
#endif /* (CPUSS_CRYPTO_DES == 1) && defined(CY_CRYPTO_CFG_DES_C) */

#if (CPUSS_CRYPTO_VU == 1) && defined(CY_CRYPTO_CFG_RSA_C)
    CY_CRYPTO_INSTR_RSA_PROC     = 0x17u,
    CY_CRYPTO_INSTR_RSA_COEF     = 0x18u,

#if defined(CY_CRYPTO_CFG_RSA_VERIFY_ENABLED)
#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)
    CY_CRYPTO_INSTR_RSA_VER      = 0x19u,
#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */
#endif /* defined(CY_CRYPTO_CFG_RSA_VERIFY_ENABLED) */

#endif /* (CPUSS_CRYPTO_VU == 1) && defined(CY_CRYPTO_CFG_RSA_C) */

    CY_CRYPTO_INSTR_SRV_INFO     = 0x55u,

#if (CPUSS_CRYPTO_VU == 1)
#if defined(CY_CRYPTO_CFG_RSA_C)
    CY_CRYPTO_INSTR_MEMBUF_SET   = 0x56u,
    CY_CRYPTO_INSTR_MEMBUF_ADDR  = 0x57u,
    CY_CRYPTO_INSTR_MEMBUF_SIZE  = 0x58u,
#endif /* defined(CY_CRYPTO_CFG_RSA_C) */

#if defined(CY_CRYPTO_CFG_ECP_C)
    CY_CRYPTO_INSTR_ECC_GET_DP   = 0x59u,
    CY_CRYPTO_INSTR_ECC_ECP_MUL  = 0x5Au,
#endif /* defined(CY_CRYPTO_CFG_ECP_C) */

#if defined(CY_CRYPTO_CFG_ECDSA_GENKEY_C)
    CY_CRYPTO_INSTR_ECP_GEN_PRIK = 0x5Bu,
    CY_CRYPTO_INSTR_ECP_GEN_PUBK = 0x5Cu,
#endif /* defined(CY_CRYPTO_CFG_ECDSA_GENKEY_C) */

#if defined(CY_CRYPTO_CFG_ECDSA_SIGN_C)
    CY_CRYPTO_INSTR_ECDSA_SIGN   = 0x5Du,
#endif /* defined(CY_CRYPTO_CFG_ECDSA_SIGN_C) */

#if defined(CY_CRYPTO_CFG_ECDSA_VERIFY_C)
    CY_CRYPTO_INSTR_ECDSA_VER    = 0x5Eu
#endif /* defined(CY_CRYPTO_CFG_ECDSA_VERIFY_C) */
#endif /* #if (CPUSS_CRYPTO_VU == 1) */

} cy_en_crypto_comm_instr_t;

/** \endcond */

/**
* \addtogroup group_crypto_data_structures
* \{
*/

#if (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C)

/** The structure for storing the AES state.
* All fields for this structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/

/* The structure to define used memory buffers */
typedef struct
{
    /** \cond INTERNAL */
    uint32_t key[CY_CRYPTO_AES_MAX_KEY_SIZE_U32];
    uint32_t keyInv[CY_CRYPTO_AES_MAX_KEY_SIZE_U32];
    uint32_t block0[CY_CRYPTO_AES_BLOCK_SIZE_U32];
    uint32_t block1[CY_CRYPTO_AES_BLOCK_SIZE_U32];
    uint32_t block2[CY_CRYPTO_AES_BLOCK_SIZE_U32];
    /** \endcond */
} cy_stc_crypto_aes_buffers_t;

typedef struct
{
    /** \cond INTERNAL */
    /** AES key length */
    cy_en_crypto_aes_key_length_t keyLength;
    /** Pointer to AES work buffers */
    cy_stc_crypto_aes_buffers_t *buffers;
    /** AES processed block index (for CMAC, SHA operations) */
    uint32_t blockIdx;
    /** \endcond */
} cy_stc_crypto_aes_state_t;
#endif /* (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C) */

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)

/** The structure for storing the SHA state.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    uint32_t mode;
    uint32_t modeHw;
    uint8_t *block;
    uint32_t blockSize;
    uint8_t *hash;
    uint32_t hashSize;
    uint8_t *roundMem;
    uint32_t roundMemSize;
    uint32_t messageSize;
    uint32_t digestSize;
    uint32_t blockIdx;
    uint8_t  const *initialHash;
    /** \endcond */
} cy_stc_crypto_sha_state_t;

#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_HMAC_C)

/** The structure for storing the HMAC state.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/

typedef struct
{
    /** \cond INTERNAL */
    /* Pointer to store the ipad */
    uint8_t *ipad;

    /* Pointer to store the opad */
    uint8_t *opad;

    /* Pointer to store the key */
    uint8_t *m0Key;

    /* Pointer to store the sha buffer */
    void* sha_buffer;

    /* Hash state*/
    cy_stc_crypto_sha_state_t hashState;
    /** \endcond */
} cy_stc_crypto_hmac_state_t;

#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_HMAC_C) */

#if (CPUSS_CRYPTO_VU == 1) && defined(CY_CRYPTO_CFG_ECP_C)
/** A point on a ECC curve */
typedef struct {
    /** The x co-ordinate */
    void *x;
    /** The y co-ordinate */
    void *y;
} cy_stc_crypto_ecc_point;

/** An ECC key type */
typedef enum cy_en_crypto_ecc_key_type {
   PK_PUBLIC     = 0u,
   PK_PRIVATE    = 1u
} cy_en_crypto_ecc_key_type_t;

/** An ECC key */
typedef struct {
    /** Type of key, PK_PRIVATE or PK_PUBLIC */
    cy_en_crypto_ecc_key_type_t type;
    /** See \ref cy_en_crypto_ecc_curve_id_t */
    cy_en_crypto_ecc_curve_id_t curveID;
    /** The public key */
    cy_stc_crypto_ecc_point pubkey;
    /** The private key */
    void *k;
} cy_stc_crypto_ecc_key;
#endif /* (CPUSS_CRYPTO_VU == 1) && defined(CY_CRYPTO_CFG_ECP_C) */

/** \} group_crypto_data_structures */

/*************************************************************
*  Structures used for communication between Client and Server
***************************************************************/

/**
* \addtogroup group_crypto_srv_data_structures
* \{
*/

/** The structure for storing the crypto server context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    /** IPC communication channel number */
    uint32_t ipcChannel;
    /** IPC acquire interrupt channel number */
    uint32_t acquireNotifierChannel;
    /** IPC release interrupt channel number */
    cy_israddress   getDataHandlerPtr;
    /** Crypto hardware errors interrupt handler */
    cy_israddress   errorHandlerPtr;
    /** Acquire notifier interrupt configuration */
    cy_stc_sysint_t acquireNotifierConfig;
    /** Crypto hardware errors interrupt configuration */
    cy_stc_sysint_t cryptoErrorIntrConfig;
    /** Hardware error occurrence flag */
    bool            isHwErrorOccured;
    /** Hardware processing errors */
    cy_stc_crypto_hw_error_t hwErrorStatus;
    /** \endcond */
} cy_stc_crypto_server_context_t;

/** \} group_crypto_srv_data_structures */

/**
* \addtogroup group_crypto_cli_data_structures
* \{
*/

/** The structure for storing the crypto client context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
#if (CY_CPU_CORTEX_M7) && defined (ENABLE_CM7_DATA_CACHE)
CY_ALIGN(__SCB_DCACHE_LINE_SIZE) typedef struct
#else
typedef struct
#endif
{
    /** \cond INTERNAL */
    /** Operation instruction code */
    cy_en_crypto_comm_instr_t instr;
    /** Response from executed crypto function */
    cy_en_crypto_status_t resp;
    /** Hardware processing errors */
    cy_stc_crypto_hw_error_t hwErrorStatus;
    /** IPC communication channel number */
    uint32_t ipcChannel;
    /** IPC acquire interrupt channel number */
    uint32_t acquireNotifierChannel;
    /** IPC release interrupt channel number */
    uint32_t releaseNotifierChannel;
    /** User callback for Crypto HW calculation complete event */
    cy_crypto_callback_ptr_t userCompleteCallback;
    /** Release notifier interrupt configuration */
    cy_stc_sysint_t releaseNotifierConfig;
    /** Pointer to the crypto function specific context data */
    void *xdata;
    /** \endcond */
} cy_stc_crypto_context_t;


#if (CPUSS_CRYPTO_DES == 1) && defined(CY_CRYPTO_CFG_DES_C)
/** The structure for storing the DES context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    /**  Operation direction (Encrypt / Decrypt) */
    cy_en_crypto_dir_mode_t dirMode;
    /**  Pointer to key data */
    uint32_t *key;
    /**  Pointer to data destination block */
    uint32_t *dst;
    /**  Pointer to data source block */
    uint32_t *src;
    /** \endcond */
} cy_stc_crypto_context_des_t;
#endif /* (CPUSS_CRYPTO_DES == 1) && defined(CY_CRYPTO_CFG_DES_C) */

#if (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C)
/** The structure for storing the AES context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    /** AES state data */
    cy_stc_crypto_aes_state_t aesState;
    /** Operation direction (Encrypt / Decrypt) */
    cy_en_crypto_dir_mode_t dirMode;
    /** AES key length */
    cy_en_crypto_aes_key_length_t keyLength;
    /** Pointer to AES key */
    uint32_t *key;
    /** Operation data size */
    uint32_t srcSize;
    /** Size of the last non-complete block (for CTR mode only) */
    uint32_t *srcOffset;
    /** Initialization vector, in the CTR mode is used as nonceCounter */
    uint32_t *ivPtr;
    /** AES processed block pointer (for CTR mode only) */
    uint32_t *streamBlock;
    /** Pointer to data destination block */
    uint32_t *dst;
    /** Pointer to data source block */
    uint32_t *src;
    /** \endcond */
} cy_stc_crypto_context_aes_t;
#endif /* (CPUSS_CRYPTO_AES == 1) && defined(CY_CRYPTO_CFG_AES_C) */

#if (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)
/** The structure for storing the SHA context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    /** Pointer to data source block */
    uint32_t *message;
    /** Operation data size */
    uint32_t  messageSize;
    /** Pointer to data destination block */
    uint32_t *dst;
    /** SHA mode */
    cy_en_crypto_sha_mode_t mode;
    /** Pointer to key data (for HMAC only) */
    uint32_t *key;
    /** Key data length (for HMAC only) */
    uint32_t  keyLength;
    /** \endcond */
} cy_stc_crypto_context_sha_t;
#endif /* (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */

#if (CPUSS_CRYPTO_PR == 1) && defined(CY_CRYPTO_CFG_PRNG_C)
/** The structure for storing the PRNG context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    uint32_t lfsr32InitState;             /**< lfsr32 initialization data */
    uint32_t lfsr31InitState;             /**< lfsr31 initialization data */
    uint32_t lfsr29InitState;             /**< lfsr29 initialization data */
    uint32_t max;                         /**< Maximum of the generated value */
    uint32_t *prngNum;                    /**< Pointer to generated value */
    /** \endcond */
} cy_stc_crypto_context_prng_t;
#endif /* (CPUSS_CRYPTO_PR == 1) && defined(CY_CRYPTO_CFG_PRNG_C) */

#if (CPUSS_CRYPTO_TR == 1) && defined(CY_CRYPTO_CFG_TRNG_C)
/** \cond INTERNAL */
#define CY_CRYPTO_TR_RO_ENABLE           (1U)
#define CY_CRYPTO_TR_RO_DISABLE          (0U)
/** \endcond */

/** \cond INTERNAL */
typedef enum
{
    /** "Selection of the ring oscillator (RO) source: */
    CY_CRYPTO_TR_SRC_RO11 = 0,  /**< "0": fixed RO 11 bit. */
    CY_CRYPTO_TR_SRC_RO15,      /**< "1": fixed RO 15 bit. */
    CY_CRYPTO_TR_SRC_GARO15,    /**< "2": fixed Galois RO 15 bit. */
    CY_CRYPTO_TR_SRC_GARO31,    /**< "3": flexible Galois RO 31 bit. */
    CY_CRYPTO_TR_SRC_FIRO15,    /**< "4": fixed Fibonacci RO 15 bit. */
    CY_CRYPTO_TR_SRC_FIRO31     /**< "5": flexible Fibonacci RO 31 bit. */
} cy_en_crypto_trng_ro_sel_t;
/** \endcond */

/******************************************
 * Configuration structure
 ******************************************/
/** \cond INTERNAL */
typedef enum
{
    /** "Selection of the bitstream: */
    CY_CRYPTO_TRMON_BS_DAS = 0, /**< "0": DAS bitstream. */
    CY_CRYPTO_TRMON_BS_RED,     /**< "1": RED bitstream. */
    CY_CRYPTO_TRMON_BS_TR,      /**< "2": TR bitstream.  */
    CY_CRYPTO_TRMON_BS_UNDEF    /**< "3": Undefined.     */
} cy_en_crypto_trng_bs_sel_t;
/** \endcond */

/** The structure for storing the TRNG configuration.
*/
typedef struct
{
    /** \cond INTERNAL */
    /**
     * "Specifies the clock divider that is used to sample oscillator data.
     * This clock divider is wrt. "clk_sys".
     * "0": sample clock is "clk_sys".
     * "1": sample clock is "clk_sys"/2.
     *
     * "255": sample clock is "clk_sys"/256. */
    uint8_t sampleClockDiv;
    /**
     * "Specifies the clock divider that is used to produce reduced bits.
     * "0": 1 reduced bit is produced for each sample.
     * "1": 1 reduced bit is produced for each 2 samples.
     *
     * "255": 1 reduced bit is produced for each 256 samples. */
    uint8_t reducedClockDiv;
    /**
     * Specifies an initialization delay: number of removed/dropped samples
     * before reduced bits are generated. This field should be programmed
     * in the range [1, 255]. After starting the oscillators,
     * at least the first 2 samples should be removed/dropped to clear the state
     * of internal synchronizers. In addition, it is advised to drop
     * at least the second 2 samples from the oscillators (to circumvent
     * the semi-predictable oscillator startup behavior).
     *
     * This result in the default field value of "3".
     * Field encoding is as follows:
     * "0": 1 sample is dropped.
     * "1": 2 samples are dropped.
     *
     * "255": 256 samples are dropped.
     *
     * The TR_INITIALIZED interrupt cause is set to '1', when
     * the initialization delay is passed. */
    uint8_t initDelay;
    /**
     * "Specifies if the "von Neumann corrector" is disabled or enabled:
     * '0': disabled.
     * '1': enabled.
     * The "von Neumann corrector" post-processes the reduced bits
     * to remove a '0' or '1' bias. The corrector operates on reduced bit pairs
     * ("oldest bit, newest bit"):
     * "00": no bit is produced.
     * "01": '0' bit is produced (oldest bit).
     * "10": '1' bit is produced (oldest bit).
     * "11": no bit is produced.
     * Note that the corrector produces bits at a random pace and at a frequency
     * that is 1/4 of the reduced bit frequency (reduced bits are processed
     * in pairs, and half of the pairs do NOT produce a bit). */
    bool    vnCorrectorEnable;
    /**
     * Specifies if TRNG functionality is stopped on an adaptive proportion
     * test detection (when HW sets INTR.TR_AP_DETECT to '1'):
     * '0': Functionality is NOT stopped.
     * '1': Functionality is stopped (TR_CTL1 fields are set to '0' by HW). */
    bool    stopOnAPDetect;
    /**
     * Specifies if TRNG functionality is stopped on a repetition
     * count test detection (when HW sets INTR.TR_RC_DETECT to '1'):
     * '0': Functionality is NOT stopped.
     * '1': Functionality is stopped (TR_CTL1 fields are set to '0' by HW). */
    bool    stopOnRCDetect;

    /**
     * FW sets this field to '1' to enable the ring oscillator with 11 inverters.
     */
    bool    ro11Enable;
    /**
     * FW sets this field to '1' to enable the ring oscillator with 15 inverters.
     */
    bool    ro15Enable;
    /**
     * FW sets this field to '1' to enable the fixed Galois ring oscillator
     * with 15 inverters. */
    bool    garo15Enable;
    /**
     * FW sets this field to '1' to enable the programmable Galois ring
     * oscillator with up to 31 inverters. The TR_GARO_CTL register specifies
     * the programmable polynomial. */
    bool    garo31Enable;
    /**
     * FW sets this field to '1' to enable the fixed Fibonacci ring oscillator
     * with 15 inverters. */
    bool    firo15Enable;
    /**
     * FW sets this field to '1' to enable the programmable Fibonacci ring
     * oscillator with up to 31 inverters. The TR_FIRO_CTL register specifies
     * the programmable polynomial. */
    bool    firo31Enable;

    /**
     * Polynomial for programmable Galois ring oscillator.
     * The polynomial is represented WITHOUT
     * the high order bit (this bit is always assumed '1').
     * The polynomial should be aligned such that the more
     * significant bits (bit 30 and down) contain the polynomial
     * and the less significant bits (bit 0 and up) contain padding '0's. */
    uint32_t garo31Poly;

    /**
     * Polynomial for programmable Fibonacci ring oscillator.
     * The polynomial is represented WITHOUT
     * the high order bit (this bit is always assumed '1').
     * The polynomial should be aligned such that the more
     * significant bits (bit 30 and down) contain the polynomial
     * and the less significant bits (bit 0 and up) contain padding '0's. */
    uint32_t firo31Poly;

    /**
     * Selection of the bitstream:
     * "0": DAS bitstream.
     * "1": RED bitstream.
     * "2": TR bitstream.
     * "3": Undefined.  */
    cy_en_crypto_trng_bs_sel_t monBitStreamSelect;

    /**
     * Cutoff count (legal range is [1, 255]):
     * "0": Illegal.
     * "1": 1 repetition.
     * ..
     * "255": 255 repetitions. */
    uint8_t monCutoffCount8;

    /**
     * Cutoff count (legal range is [1, 65535]).
     * "0": Illegal.
     * "1": 1 occurrence.
     * ...
     * "65535": 65535 occurrences. */
    uint16_t monCutoffCount16;
    /**
     * Window size (minus 1) :
     * "0": 1 bit.
     * ...
     * "65535": 65536 bits. */
    uint16_t monWindowSize;
    /** \endcond */
} cy_stc_crypto_trng_config_t;

/** The structure for storing the TRNG context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    /**
     The polynomial for the programmable Galois ring oscillator (TR_GARO_CTL).
     The polynomial is represented WITHOUT the high order bit (this bit is
     always assumed '1').
     The polynomial should be aligned so that more significant bits
     (bit 30 and down) contain the polynomial and less significant bits
     (bit 0 and up) contain padding '0's. */
    uint32_t GAROPol;

    /**
     The polynomial for the programmable Fibonacci ring oscillator(TR_FIRO_CTL).
     The polynomial is represented WITHOUT the high order bit (this bit is
     always assumed '1').
     The polynomial should be aligned so that more significant bits
     (bit 30 and down) contain the polynomial and less significant bits
     (bit 0 and up) contain padding '0's. */
    uint32_t FIROPol;
    /** Maximum of the generated value */
    uint32_t max;
    /** Pointer to generated value */
    uint32_t *trngNum;
    /** \endcond */
} cy_stc_crypto_context_trng_t;
#endif /* (CPUSS_CRYPTO_TR == 1) && defined(CY_CRYPTO_CFG_TRNG_C) */

#if (CPUSS_CRYPTO_STR == 1)
/** The structure for storing the string context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    void const *src0;         /**<  Pointer to 1-st string source */
    void const *src1;         /**<  Pointer to 2-nd string source */
    void       *dst;          /**<  Pointer to string destination */
    uint32_t   dataSize;      /**<  Operation data size */
    uint32_t   data;          /**<  Operation data value (for memory setting) */
    /** \endcond */
} cy_stc_crypto_context_str_t;
#endif /* #if (CPUSS_CRYPTO_STR == 1) */

#if (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C)
/** The structure for storing the CRC context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    void*    data;                  /**<  Pointer to data source block */
    uint32_t dataSize;              /**<  Operation data size */
    uint32_t *crc;                  /**<  Pointer to CRC destination variable */
    uint32_t polynomial;            /**<  Polynomial for CRC calculate */
    uint32_t lfsrInitState;         /**<  CRC calculation initial value */
    uint32_t dataReverse;           /**<  Input data reverse flag */
    uint32_t dataXor;               /**<  Input data  XOR flag */
    uint32_t remReverse;            /**<  Output data reverse flag */
    uint32_t remXor;                /**<  Output data XOR flag */
    /** \endcond */
} cy_stc_crypto_context_crc_t;
#endif /* (CPUSS_CRYPTO_CRC == 1) && defined(CY_CRYPTO_CFG_CRC_C) */

#if (CPUSS_CRYPTO_VU == 1)
#if defined(CY_CRYPTO_CFG_RSA_C)
/** The structure for storing the RSA context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    /** Pointer to key data */
    cy_stc_crypto_rsa_pub_key_t const *key;
    /** Pointer to data source block */
    uint32_t const *message;
    /** Operation data size */
    uint32_t messageSize;
    /** Pointer to data destination block */
    uint32_t *result;
    /** \endcond */
} cy_stc_crypto_context_rsa_t;

#if defined(CY_CRYPTO_CFG_RSA_VERIFY_ENABLED) && (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C)
/** The structure for storing the RSA verification context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in the function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    /** Pointer to verification result /ref cy_en_crypto_rsa_ver_result_t */
    cy_en_crypto_rsa_ver_result_t *verResult;
    /** SHA digest type, used with SHA calculation of the message */
    cy_en_crypto_sha_mode_t digestType;
    /** SHA digest of the message, calculated with digestType */
    uint32_t const *hash;
    /** Previously decrypted RSA signature */
    uint32_t const *decryptedSignature;
    /** Length of the decrypted RSA signature */
    uint32_t decryptedSignatureLength;
    /** \endcond */
} cy_stc_crypto_context_rsa_ver_t;
#endif /* defined(CY_CRYPTO_CFG_RSA_VERIFY_ENABLED) && (CPUSS_CRYPTO_SHA == 1) && defined(CY_CRYPTO_CFG_SHA_C) */
#endif /* defined(CY_CRYPTO_CFG_RSA_C) */

#if defined(CY_CRYPTO_CFG_ECDSA_C)
/** The structure for storing the ECC operations context.
* All fields for the context structure are internal. Firmware never reads or
* writes these values. Firmware allocates the structure and provides the
* address of the structure to the driver in function calls. Firmware must
* ensure that the defined instance of this structure remains in scope
* while the drive is in use.
*/
typedef struct
{
    /** \cond INTERNAL */
    /** Elliptic curve ID */
    cy_en_crypto_ecc_curve_id_t curveID;
    /** Pointer to key data */
    const cy_stc_crypto_ecc_key *key;
    /** Operation data length */
    uint32_t datalen;
    /** Pointer to the first  source data block */
    const uint8_t *src0;
    /** Pointer to the second source data block */
    const uint8_t *src1;
    /** Pointer to the third  source data block */
    const uint8_t *src2;
    /** Pointer to the first  destination data block */
    uint8_t *dst0;
    /** Pointer to the second destination data block */
    uint8_t *dst1;
    /** \endcond */
} cy_stc_crypto_context_ecc_t;
#endif /* defined(CY_CRYPTO_CFG_ECDSA_C) */
#endif /* #if (CPUSS_CRYPTO_VU == 1) */


#if defined(CY_CRYPTO_CFG_CHACHA_ENABLED) && (CPUSS_CRYPTO_CHACHA == 1)

/** Defines the chacha state size (in bytes) */
#define CHACHA_STATE_SIZE 64u

/** Defines the chacha key stream size (in bytes) */
#define CHACHA_KEYSTREAM_SIZE 64u

/** Defines the chacha state block size (in bytes) */
#define CHACHA_BLOCK_SIZE 64u

/** \cond INTERNAL */

/** Defines the chacha key size (in bytes) */
#define CHACHA_KEY_SIZE 32u

/** Defines the chacha nonce size (in bytes) */
#define CHACHA_NONCE_SIZE 12u

/** Defines the chacha counter size (in bytes) */
#define CHACHA_COUNTER_SIZE 4u

/** Defines the chacha const size (in bytes) */
#define CHACHA_CONST_SIZE 16u
/** \endcond */

typedef struct
{
    /** \cond INTERNAL */

    /** buffer to store the constant*/
    uint32_t constant[CHACHA_CONST_SIZE/4u];

    /** buffer to store the chacha key*/
    uint8_t key[CHACHA_KEY_SIZE];

    /** To store the counter*/
    uint32_t counter;

    /** buffer to store the nonce*/
    uint8_t nonce[CHACHA_NONCE_SIZE];
    /** \endcond */
}cy_stc_crypto_v2_chacha_input_buffer;

typedef struct
{
    /** \cond INTERNAL */
    /** The pointer to store chacha state */
    cy_stc_crypto_v2_chacha_input_buffer *state;
    /** The pointer to chacha key stream */
    uint8_t *key;
    /** To store the chacha key bytes used */
    uint8_t keyIndexUsed;
     /** To store the rounds for the chacha operation*/
    uint8_t round;
    /** \endcond */
} cy_stc_crypto_chacha_state_t;

#endif

/** \} group_crypto_cli_data_structures */

#if defined(__cplusplus)
}
#endif

#endif /* defined(CY_IP_MXCRYPTO) */

#endif /* #if !defined (CY_CRYPTO_COMMON_H) */


/* [] END OF FILE */
