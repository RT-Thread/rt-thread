/***************************************************************************//**
* \file cy_crypto_common.h
* \version 2.50
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

#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include "cy_sysint.h"

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

/** Driver major version */
#define CY_CRYPTO_DRV_VERSION_MAJOR         2

/** Driver minor version */
#define CY_CRYPTO_DRV_VERSION_MINOR         50

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

#if (CPUSS_CRYPTO_SHA == 1)

/* Defines for the SHA algorithm */
/** Hash size for the SHA1 mode (in bytes)   */
#define CY_CRYPTO_SHA1_DIGEST_SIZE          (20u)
/** Hash size for the SHA224 mode (in bytes) */
#define CY_CRYPTO_SHA224_DIGEST_SIZE        (28u)
/** Hash size for the SHA256 mode (in bytes) */
#define CY_CRYPTO_SHA256_DIGEST_SIZE        (32u)
/** Hash size for the SHA384 mode (in bytes) */
#define CY_CRYPTO_SHA384_DIGEST_SIZE        (48u)
/** Hash size for the SHA512 mode (in bytes) */
#define CY_CRYPTO_SHA512_DIGEST_SIZE        (64u)
/** Hash size for the SHA512_224 mode (in bytes) */
#define CY_CRYPTO_SHA512_224_DIGEST_SIZE    (28u)
/** Hash size for the SHA512_256 mode (in bytes) */
#define CY_CRYPTO_SHA512_256_DIGEST_SIZE    (32u)
/** The maximal Hash size for the SHA modes (in bytes). */
#define CY_CRYPTO_SHA_MAX_DIGEST_SIZE       (CY_CRYPTO_SHA512_DIGEST_SIZE)

/** Block size for the SHA1 mode (in bytes)   */
#define CY_CRYPTO_SHA1_BLOCK_SIZE           (64u)
/** Block size for the SHA256 mode (in bytes)   */
#define CY_CRYPTO_SHA256_BLOCK_SIZE         (64u)
/** Block size for the SHA512 mode (in bytes)   */
#define CY_CRYPTO_SHA512_BLOCK_SIZE         (128u)
/** Maximal block size for the SHA modes (in bytes)   */
#define CY_CRYPTO_SHA_MAX_BLOCK_SIZE        (CY_CRYPTO_SHA512_BLOCK_SIZE)

/** \cond INTERNAL */

#define CY_CRYPTO_SHA256_PAD_SIZE           (56uL)
#define CY_CRYPTO_SHA512_PAD_SIZE           (112uL)

#define CY_CRYPTO_SHA1_HASH_SIZE            (20u)
#define CY_CRYPTO_SHA256_HASH_SIZE          (32u)
#define CY_CRYPTO_SHA512_HASH_SIZE          (64u)
#define CY_CRYPTO_SHA_MAX_HASH_SIZE         (CY_CRYPTO_SHA512_HASH_SIZE)

#define CY_CRYPTO_SHA1_ROUND_MEM_SIZE       (320uL)
#define CY_CRYPTO_SHA256_ROUND_MEM_SIZE     (256uL)
#define CY_CRYPTO_SHA512_ROUND_MEM_SIZE     (640uL)
#define CY_CRYPTO_SHA_MAX_ROUND_MEM_SIZE    (CY_CRYPTO_SHA512_ROUND_MEM_SIZE)

/* The width of the Crypto hardware registers values in bits. */
#define CY_CRYPTO_HW_REGS_WIDTH             (32UL)

/* Calculates the actual size in bytes of the bits value */
#define CY_CRYPTO_BYTE_SIZE_OF_BITS(x)      (uint32_t)(((uint32_t)(x) + 7u) >> 3u)

/* Calculates the actual size in 32-bit words of the bits value */
#define CY_CRYPTO_WORD_SIZE_OF_BITS(x)      (uint32_t)(((uint32_t)(x) + 31u) >> 5u)

/** \endcond */

#endif /* #if (CPUSS_CRYPTO_SHA == 1) */


#if (CPUSS_CRYPTO_VU == 1)

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

#endif /* #if (CPUSS_CRYPTO_VU == 1) */


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
* \addtogroup group_crypto_data_structures
* \{
*/

#if (CPUSS_CRYPTO_VU == 1)

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

#endif /* #if (CPUSS_CRYPTO_VU == 1) */

/** \} group_crypto_data_structures */

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

#if (CPUSS_CRYPTO_AES == 1)
/** The key length options for the AES method. */
typedef enum
{
    CY_CRYPTO_KEY_AES_128   = 0x00u,   /**< The AES key size is 128 bits */
    CY_CRYPTO_KEY_AES_192   = 0x01u,   /**< The AES key size is 192 bits */
    CY_CRYPTO_KEY_AES_256   = 0x02u    /**< The AES key size is 256 bits */
} cy_en_crypto_aes_key_length_t;
#endif /* #if (CPUSS_CRYPTO_AES == 1) */

/** Defines the direction of the Crypto methods */
typedef enum
{
    /** The forward mode, plain text will be encrypted into cipher text */
    CY_CRYPTO_ENCRYPT   = 0x00u,
    /** The reverse mode, cipher text will be decrypted into plain text */
    CY_CRYPTO_DECRYPT   = 0x01u
} cy_en_crypto_dir_mode_t;

#if (CPUSS_CRYPTO_SHA == 1)
/** Defines modes of SHA method */
typedef enum
{
#if (CPUSS_CRYPTO_SHA1 == 1)
    CY_CRYPTO_MODE_SHA1          = 0x00u,   /**< Sets the SHA1 mode */
#endif /* #if (CPUSS_CRYPTO_SHA1 == 1) */

#if (CPUSS_CRYPTO_SHA256 == 1)
    CY_CRYPTO_MODE_SHA224        = 0x01u,   /**< Sets the SHA224 mode */
    CY_CRYPTO_MODE_SHA256        = 0x02u,   /**< Sets the SHA256 mode */
#endif /* #if (CPUSS_CRYPTO_SHA256 == 1) */

#if (CPUSS_CRYPTO_SHA512 == 1)
    CY_CRYPTO_MODE_SHA384        = 0x03u,   /**< Sets the SHA384 mode */
    CY_CRYPTO_MODE_SHA512        = 0x04u,   /**< Sets the SHA512 mode */
    CY_CRYPTO_MODE_SHA512_256    = 0x05u,   /**< Sets the SHA512/256 mode */
    CY_CRYPTO_MODE_SHA512_224    = 0x06u,   /**< Sets the SHA512/224 mode */
#endif /* #if (CPUSS_CRYPTO_SHA512 == 1) */

} cy_en_crypto_sha_mode_t;
#endif /* #if (CPUSS_CRYPTO_SHA == 1) */

/** Signature verification status */
typedef enum
{
    CY_CRYPTO_RSA_VERIFY_SUCCESS = 0x00u,   /**< PKCS1-v1.5 verify SUCCESS */
    CY_CRYPTO_RSA_VERIFY_FAIL    = 0x01u    /**< PKCS1-v1.5 verify FAILED */
} cy_en_crypto_rsa_ver_result_t;

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
    CY_CRYPTO_BAD_PARAMS          = CY_CRYPTO_ID | CY_PDL_STATUS_ERROR   | 0x0Bu

} cy_en_crypto_status_t;

/** \} group_crypto_enums */

/**
* \addtogroup group_crypto_lld_asymmetric_enums
* \{
*/

/** List of supported elliptic curve IDs */
typedef enum {
    CY_CRYPTO_ECC_ECP_NONE = 0,
    CY_CRYPTO_ECC_ECP_SECP192R1,
    CY_CRYPTO_ECC_ECP_SECP224R1,
    CY_CRYPTO_ECC_ECP_SECP256R1,
    CY_CRYPTO_ECC_ECP_SECP384R1,
    CY_CRYPTO_ECC_ECP_SECP521R1,
    /* Count of supported curves */
    CY_CRYPTO_ECC_ECP_CURVES_CNT
} cy_en_crypto_ecc_curve_id_t;

/** \} group_crypto_lld_asymmetric_enums */

/** \cond INTERNAL */

/** Instruction to communicate between Client and Server */
typedef enum
{
    CY_CRYPTO_INSTR_UNKNOWN      = 0x00u,
    CY_CRYPTO_INSTR_ENABLE       = 0x01u,
    CY_CRYPTO_INSTR_DISABLE      = 0x02u,

#if (CPUSS_CRYPTO_PR == 1)
    CY_CRYPTO_INSTR_PRNG_INIT    = 0x03u,
    CY_CRYPTO_INSTR_PRNG         = 0x04u,
#endif /* #if (CPUSS_CRYPTO_PR == 1) */

#if (CPUSS_CRYPTO_TR == 1)
    CY_CRYPTO_INSTR_TRNG_INIT    = 0x05u,
    CY_CRYPTO_INSTR_TRNG         = 0x06u,
#endif /* #if (CPUSS_CRYPTO_PR == 1) */

#if (CPUSS_CRYPTO_AES == 1)
    CY_CRYPTO_INSTR_AES_INIT     = 0x07u,
    CY_CRYPTO_INSTR_AES_ECB      = 0x08u,
    CY_CRYPTO_INSTR_AES_CBC      = 0x09u,
    CY_CRYPTO_INSTR_AES_CFB      = 0x0Au,
    CY_CRYPTO_INSTR_AES_CTR      = 0x0Bu,
    CY_CRYPTO_INSTR_CMAC         = 0x0Cu,
#endif /* #if (CPUSS_CRYPTO_AES == 1) */

#if (CPUSS_CRYPTO_SHA == 1)
    CY_CRYPTO_INSTR_SHA          = 0x0Du,
#endif /* #if (CPUSS_CRYPTO_SHA == 1) */

#if (CPUSS_CRYPTO_SHA == 1)
    CY_CRYPTO_INSTR_HMAC         = 0x0Eu,
#endif /* #if (CPUSS_CRYPTO_SHA == 1) */

#if (CPUSS_CRYPTO_STR == 1)
    CY_CRYPTO_INSTR_MEM_CPY      = 0x0Fu,
    CY_CRYPTO_INSTR_MEM_SET      = 0x10u,
    CY_CRYPTO_INSTR_MEM_CMP      = 0x11u,
    CY_CRYPTO_INSTR_MEM_XOR      = 0x12u,
#endif /* #if (CPUSS_CRYPTO_STR == 1) */

#if (CPUSS_CRYPTO_CRC == 1)
    CY_CRYPTO_INSTR_CRC_INIT     = 0x13u,
    CY_CRYPTO_INSTR_CRC          = 0x14u,
#endif /* #if (CPUSS_CRYPTO_CRC == 1) */

#if (CPUSS_CRYPTO_DES == 1)
    CY_CRYPTO_INSTR_DES          = 0x15u,
    CY_CRYPTO_INSTR_3DES         = 0x16u,
#endif /* #if (CPUSS_CRYPTO_DES == 1) */

#if (CPUSS_CRYPTO_VU == 1)
    CY_CRYPTO_INSTR_RSA_PROC     = 0x17u,
    CY_CRYPTO_INSTR_RSA_COEF     = 0x18u,
#endif /* #if (CPUSS_CRYPTO_VU == 1) */

#if (CPUSS_CRYPTO_SHA == 1)
    CY_CRYPTO_INSTR_RSA_VER      = 0x19u,
#endif /* #if (CPUSS_CRYPTO_SHA == 1) */

    CY_CRYPTO_INSTR_SRV_INFO     = 0x55u,

#if (CPUSS_CRYPTO_VU == 1)
    CY_CRYPTO_INSTR_MEMBUF_SET   = 0x56u,
    CY_CRYPTO_INSTR_MEMBUF_ADDR  = 0x57u,
    CY_CRYPTO_INSTR_MEMBUF_SIZE  = 0x58u,

    CY_CRYPTO_INSTR_ECC_GET_DP   = 0x59u,
    CY_CRYPTO_INSTR_ECC_ECP_MUL  = 0x5Au,
    CY_CRYPTO_INSTR_ECP_GEN_PRIK = 0x5Bu,
    CY_CRYPTO_INSTR_ECP_GEN_PUBK = 0x5Cu,

    CY_CRYPTO_INSTR_ECDSA_SIGN   = 0x5Du,
    CY_CRYPTO_INSTR_ECDSA_VER    = 0x5Eu
#endif /* #if (CPUSS_CRYPTO_VU == 1) */

} cy_en_crypto_comm_instr_t;

/** \endcond */

/**
* \addtogroup group_crypto_data_structures
* \{
*/

#if (CPUSS_CRYPTO_AES == 1)

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
#endif /* #if (CPUSS_CRYPTO_AES == 1) */

#if (CPUSS_CRYPTO_SHA == 1)

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

#endif /* (CPUSS_CRYPTO_SHA == 1) */

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
typedef struct
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


#if (CPUSS_CRYPTO_DES == 1)
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
#endif /* #if (CPUSS_CRYPTO_DES == 1) */

#if (CPUSS_CRYPTO_AES == 1)
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
#endif /* #if (CPUSS_CRYPTO_AES == 1) */

#if (CPUSS_CRYPTO_SHA == 1)

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
#endif /* #if (CPUSS_CRYPTO_SHA == 1) */

#if (CPUSS_CRYPTO_PR == 1)
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
#endif /* #if (CPUSS_CRYPTO_PR == 1) */

#if (CPUSS_CRYPTO_TR == 1)
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
#endif /* #if (CPUSS_CRYPTO_TR == 1) */

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

#if (CPUSS_CRYPTO_CRC == 1)
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
#endif /* #if (CPUSS_CRYPTO_CRC == 1) */

#if (CPUSS_CRYPTO_VU == 1)

#if (CPUSS_CRYPTO_SHA == 1)
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
#endif /* #if (CPUSS_CRYPTO_SHA == 1) */

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
#endif /* #if (CPUSS_CRYPTO_VU == 1) */

/** \} group_crypto_cli_data_structures */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCRYPTO */

#endif /* #if !defined (CY_CRYPTO_COMMON_H) */


/* [] END OF FILE */
