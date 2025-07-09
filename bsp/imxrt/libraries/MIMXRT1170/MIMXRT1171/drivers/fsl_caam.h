/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef FSL_CAAM_H_
#define FSL_CAAM_H_

#include "fsl_common.h"

/*!
 * @addtogroup caam_driver
 * @{
 */

/*! @brief CAAM status return codes. */
enum
{
    kStatus_CAAM_Again        = MAKE_STATUS(kStatusGroup_CAAM, 0), /*!< Non-blocking function shall be called again. */
    kStatus_CAAM_DataOverflow = MAKE_STATUS(kStatusGroup_CAAM, 1), /*!< Input data too big. */

};

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @name Driver version */
/*! @{ */
/*! @brief CAAM driver version.
 *
 * Current version: 2.4.0
 *
 * Change log:
 * - Version 2.0.0
 *   - Initial version
 * - Version 2.0.1
 *   - Add Job Ring 2 and 3.
 * - Version 2.0.2
 *   - Add Data and Instruction Synchronization Barrier in caam_input_ring_set_jobs_added()
 *     to make sure that the descriptor will be loaded into CAAM correctly.
 * - Version 2.0.3
 *   - Use MACRO instead of numbers in descriptor.
 *   - Correct descriptor size mask.
 * - Version 2.1.0
 *   - Add return codes check and handling.
 * - Version 2.1.1
 *   - Add DCACHE support.
 * - Version 2.1.2
 *   - Add data offset feature to provide support for mirrored (high-speed) memory.
 * - Version 2.1.3
 *   - Fix MISRA-2012 issues.
 * - Version 2.1.4
 *   - Fix MISRA-2012 issues.
 * - Version 2.1.5
 *   - Support EXTENDED data size for all AES, HASH and RNG operations.
 *   - Support multiple De-Initialization/Initialization of CAAM driver within one POR event.
 * - Version 2.1.6
 *   - Improve DCACHE handling. Requires CAAM used and cached memory set in write-trough mode.
 * - Version 2.2.0
 *   - Added API for Blob functions and CRC
 * - Version 2.2.1
 *   - Fixed AES-CCM decrypt failing with TAG length bigger than 8 byte.
 * - Version 2.2.2
 *   - Modify RNG to not reseed with each request.
 * - Version 2.2.3
 *   - Fix DCACHE invalidation in CAAM_HASH_Finish().
 * - Version 2.2.4
 *   - Fix issue where the outputSize parameter of CAAM_HASH_Finish() has impact on hash calculation.
 * - Version 2.3.0
 *   - Add support for SHA HMAC.
 * - Version 2.3.1
 *   - Modified function caam_aes_ccm_check_input_args() to allow payload be empty as is specified in NIST800-38C
 *     Section 5.3.
 * - Version 2.3.2
 *   - Fix MISRA-2012 issues.
 * - Version 2.4.0
 *   - Add new APIs for native asymmetric operations (RSA, ECC) instead of only accelerating mathematical primitives
 *     and support for black keys and blobs for both symmetric and asymmetric operations.
 */
#define FSL_CAAM_DRIVER_VERSION (MAKE_VERSION(2, 4, 0))
/*! @} */

/*! @brief CAAM callback function. */
typedef struct _caam_job_callback
{
    void (*JobCompleted)(void *userData); /*!< CAAM Job complete callback */
} caam_job_callback_t;

/*! @brief CAAM job ring selection. */
typedef enum _caam_job_ring_t
{
    kCAAM_JobRing0 = 0u, /*!< CAAM Job ring 0 */
    kCAAM_JobRing1 = 1u, /*!< CAAM Job ring 1 */
    kCAAM_JobRing2 = 2u, /*!< CAAM Job ring 2 */
    kCAAM_JobRing3 = 3u, /*!< CAAM Job ring 3 */
} caam_job_ring_t;

/*! @brief CAAM handle
 *  Specifies jobRing and optionally the user callback function.
 *  The user callback functions is invoked only if jobRing interrupt has been enabled by the user.
 *  By default the jobRing interrupt is disabled (default job complete test is polling CAAM output ring).
 */
typedef struct _caam_handle_t
{
    caam_job_ring_t jobRing;

    /* Callback functions */
    caam_job_callback_t callback; /*!< Callback function */
    void *userData;               /*!< Parameter for CAAM job complete callback */
} caam_handle_t;

/*! @brief CAAM driver wait mechanism
 */
typedef enum _caam_wait_mode
{
    kCAAM_Blocking    = 0u, /*!< CAAM_Wait blocking mode */
    kCAAM_Nonblocking = 1u, /*!< CAAM Wait non-blocking mode */
} caam_wait_mode_t;

/*! @brief Memory buffer to hold CAAM descriptor for AESA ECB job */
typedef uint32_t caam_desc_aes_ecb_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for AESA CBC job */
typedef uint32_t caam_desc_aes_cbc_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for AESA CTR job */
typedef uint32_t caam_desc_aes_ctr_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for AESA CCM job */
typedef uint32_t caam_desc_aes_ccm_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for AESA GCM job */
typedef uint32_t caam_desc_aes_gcm_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for MDHA job or AESA CMAC job */
typedef uint32_t caam_desc_hash_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for RNG jobs */
typedef uint32_t caam_desc_rng_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for DESA jobs */
typedef uint32_t caam_desc_cipher_des_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for PKHA jobs */
typedef uint32_t caam_desc_pkha_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for PKHA ECC jobs */
typedef uint32_t caam_desc_pkha_ecc_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for performing key blackening jobs */
typedef uint32_t caam_desc_key_black_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for performing generating dek blob jobs */
typedef uint32_t caam_desc_gen_enc_blob_t[64];
typedef uint32_t caam_desc_gen_dep_blob_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for performing generating dek blob jobs */
typedef uint32_t caam_desc_rsa_t[64];

/*! @brief Memory buffer to hold CAAM descriptor for performing generating dek blob jobs */
typedef uint32_t caam_desc_ecc_t[64];

typedef struct _caam_job_ring_interface
{
    uint32_t inputJobRing[4];
    uint32_t outputJobRing[8];
} caam_job_ring_interface_t;

/*! @brief CAAM RNG sample mode. Used by caam_config_t. */
typedef enum _caam_rng_sample_mode
{
    kCAAM_RNG_SampleModeVonNeumann = 0U, /*!< Use von Neumann data in both Entropy shifter and Statistical Checker. */
    kCAAM_RNG_SampleModeRaw        = 1U, /*!< Use raw data into both Entropy shifter and Statistical Checker. */
    kCAAM_RNG_SampleModeVonNeumannRaw =
        2U /*!< Use von Neumann data in Entropy shifter. Use raw data into Statistical Checker. */
} caam_rng_sample_mode_t;

/*! @brief CAAM RNG ring oscillator divide. Used by caam_config_t. */
typedef enum _caam_rng_ring_osc_div
{
    kCAAM_RNG_RingOscDiv0 = 0U, /*!< Ring oscillator with no divide */
    kCAAM_RNG_RingOscDiv2 = 1U, /*!< Ring oscillator divided-by-2. */
    kCAAM_RNG_RingOscDiv4 = 2U, /*!< Ring oscillator divided-by-4. */
    kCAAM_RNG_RingOscDiv8 = 3U  /*!< Ring oscillator divided-by-8. */
} caam_rng_ring_osc_div_t;

/*! @brief CAAM Private Blob. Used by caam_config_t. */
typedef enum _caam_priblob
{
    kCAAM_PrivSecureBootBlobs        = 0U, /*!< Private secure boot software blobs. */
    kCAAM_PrivProvisioningBlobsType1 = 1U, /*!< Private Provisioning Type 1 blobs. */
    kCAAM_PrivProvisioningBlobsType2 = 2U, /*!< Private Provisioning Type 2 blobs. */
    kCAAM_NormalOperationBlobs       = 3U, /*!< Normal operation blobs. */
} caam_priblob_t;

/*! @brief CAAM configuration structure. */
typedef struct _caam_config
{
    caam_job_ring_interface_t *jobRingInterface[4];
    caam_rng_sample_mode_t rngSampleMode;  /*!< RTMCTL Sample Mode. */
    caam_rng_ring_osc_div_t rngRingOscDiv; /*!< RTMCTL Oscillator Divide. */
    bool scfgrLockTrngProgramMode;         /*!< SCFGR Lock TRNG Program Mode. */
    bool scfgrEnableRandomDataBuffer;      /*!< SCFGR Enable random data buffer. */
    bool scfgrRandomRngStateHandle0;       /*!< SCFGR Random Number Generator State Handle 0. */
    bool scfgrRandomDpaResistance;         /*!< SCFGR Random Differential Power Analysis Resistance. */
    caam_priblob_t scfgrPriblob;           /*!< SCFGR Private Blob. */
} caam_config_t;

/*! @brief CAAM External Key Transfer command SRC (The source from which the key will be obtained) */
typedef enum _caam_ext_key_xfr_source
{
    kCAAM_ExtKeyXfr_KeyRegisterClass1 = 1U, /*!< The Class 1 Key Register is the source. */
    kCAAM_ExtKeyXfr_KeyRegisterClass2 = 2U, /*!< The Class 2 Key Register is the source. */
    kCAAM_ExtKeyXfr_PkhaRamE          = 3U, /*!< The PKHA E RAM is the source. */
} caam_ext_key_xfr_source_t;

typedef enum _caam_ecc_ecdsel
{
    kCAAM_ECDSEL_P_192           = 0x00u,
    kCAAM_ECDSEL_P_224           = 0x01u,
    kCAAM_ECDSEL_P_256           = 0x02u,
    kCAAM_ECDSEL_P_384           = 0x03u,
    kCAAM_ECDSEL_P_521           = 0x04u,
    kCAAM_ECDSEL_brainpoolP160r1 = 0x05u,
    kCAAM_ECDSEL_brainpoolP160t1 = 0x06u,
    kCAAM_ECDSEL_brainpoolP192r1 = 0x07u,
    kCAAM_ECDSEL_brainpoolP192t1 = 0x08u,
    kCAAM_ECDSEL_brainpoolP224r1 = 0x09u,
    kCAAM_ECDSEL_brainpoolP224t1 = 0x0Au,
    kCAAM_ECDSEL_brainpoolP256r1 = 0x0Bu,
    kCAAM_ECDSEL_brainpoolP256t1 = 0x0Cu,
    kCAAM_ECDSEL_brainpoolP320r1 = 0x0Du,
    kCAAM_ECDSEL_brainpoolP320t1 = 0x0Eu,
    kCAAM_ECDSEL_brainpoolP384r1 = 0x0Fu,
    kCAAM_ECDSEL_brainpoolP384t1 = 0x10u,
    kCAAM_ECDSEL_brainpoolP512r1 = 0x11u,
    kCAAM_ECDSEL_brainpoolP512t1 = 0x12u,
    kCAAM_ECDSEL_prime192v2      = 0x13u,
    kCAAM_ECDSEL_prime192v3      = 0x14u,
    kCAAM_ECDSEL_prime239v1      = 0x15u,
    kCAAM_ECDSEL_prime239v2      = 0x16u,
    kCAAM_ECDSEL_prime239v3      = 0x17u,
    kCAAM_ECDSEL_secp112r1       = 0x18u,
    kCAAM_ECDSEL_wtls8           = 0x19u,
    kCAAM_ECDSEL_wtls9           = 0x1Au,
    kCAAM_ECDSEL_secp160k1       = 0x1Bu,
    kCAAM_ECDSEL_secp160r1       = 0x1Cu,
    kCAAM_ECDSEL_secp160r2       = 0x1Du,
    kCAAM_ECDSEL_secp192k1       = 0x1Eu,
    kCAAM_ECDSEL_secp224k1       = 0x1Fu,
    kCAAM_ECDSEL_secp256k1       = 0x20u,
    kCAAM_ECDSEL_B_163           = 0x40u,
    kCAAM_ECDSEL_B_233           = 0x41u,
    kCAAM_ECDSEL_B_283           = 0x42u,
    kCAAM_ECDSEL_B_409           = 0x43u,
    kCAAM_ECDSEL_B_571           = 0x44u,
    kCAAM_ECDSEL_K_163           = 0x45u,
    kCAAM_ECDSEL_K_233           = 0x46u,
    kCAAM_ECDSEL_K_283           = 0x47u,
    kCAAM_ECDSEL_K_409           = 0x48u,
    kCAAM_ECDSEL_K_571           = 0x49u,
    kCAAM_ECDSEL_wtls1           = 0x4Au,
    kCAAM_ECDSEL_sect113r1       = 0x4Bu,
    kCAAM_ECDSEL_c2pnb163v1      = 0x4Cu,
    kCAAM_ECDSEL_c2pnb163v2      = 0x4Du,
    kCAAM_ECDSEL_c2pnb163v3      = 0x4Eu,
    kCAAM_ECDSEL_sect163r1       = 0x4Fu,
    kCAAM_ECDSEL_sect193r1       = 0x50u,
    kCAAM_ECDSEL_sect193r2       = 0x51u,
    kCAAM_ECDSEL_sect239k1       = 0x52u,
} caam_ecc_ecdsel_t;
/*! @} */ /* end of caam_driver */

/*******************************************************************************
 * AES Definitions
 *******************************************************************************/

/*!
 * @addtogroup caam_driver_aes
 * @{
 */

/*! AES block size in bytes */
#define CAAM_AES_BLOCK_SIZE 16

/*!
 *@}
 */ /* end of caam_driver_aes */

/*******************************************************************************
 * DES Definitions
 *******************************************************************************/
/*!
 * @addtogroup caam_driver_des
 * @{
 */

/*! @brief CAAM DES key size - 64 bits. */
#define CAAM_DES_KEY_SIZE 8U

/*! @brief CAAM DES IV size - 8 bytes */
#define CAAM_DES_IV_SIZE 8

/*! @brief CAAM blacken key size for ECB encryption */
#define CAAM_BLACKEN_ECB_SIZE(x) ((uint32_t)((x) + 15u) & ~15ul)

/*! @brief CAAM blacken key size for CCM encryption */
#define CAAM_BLACKEN_CCM_SIZE(x) (((uint32_t)((x) + 7u) & ~7ul) + 12u)

/*! @brief CAAM DSA public key length for EC domain */
#define CAAM_DSA_PUBLIC_KEY_LENGTH(domain)         \
    ((domain) == kCAAM_ECDSEL_P_192           ? 24u : \
     (domain) == kCAAM_ECDSEL_P_224           ? 28u : \
     (domain) == kCAAM_ECDSEL_P_256           ? 32u : \
     (domain) == kCAAM_ECDSEL_P_384           ? 48u : \
     (domain) == kCAAM_ECDSEL_P_521           ? 66u : \
     (domain) == kCAAM_ECDSEL_brainpoolP160r1 ? 20u : \
     (domain) == kCAAM_ECDSEL_brainpoolP160t1 ? 20u : \
     (domain) == kCAAM_ECDSEL_brainpoolP192r1 ? 24u : \
     (domain) == kCAAM_ECDSEL_brainpoolP192t1 ? 24u : \
     (domain) == kCAAM_ECDSEL_brainpoolP224r1 ? 28u : \
     (domain) == kCAAM_ECDSEL_brainpoolP224t1 ? 28u : \
     (domain) == kCAAM_ECDSEL_brainpoolP256r1 ? 32u : \
     (domain) == kCAAM_ECDSEL_brainpoolP256t1 ? 32u : \
     (domain) == kCAAM_ECDSEL_brainpoolP320r1 ? 40u : \
     (domain) == kCAAM_ECDSEL_brainpoolP320t1 ? 40u : \
     (domain) == kCAAM_ECDSEL_brainpoolP384r1 ? 48u : \
     (domain) == kCAAM_ECDSEL_brainpoolP384t1 ? 48u : \
     (domain) == kCAAM_ECDSEL_brainpoolP512r1 ? 64u : \
     (domain) == kCAAM_ECDSEL_brainpoolP512t1 ? 64u : \
     (domain) == kCAAM_ECDSEL_prime192v2      ? 24u : \
     (domain) == kCAAM_ECDSEL_prime192v3      ? 24u : \
     (domain) == kCAAM_ECDSEL_prime239v1      ? 30u : \
     (domain) == kCAAM_ECDSEL_prime239v2      ? 30u : \
     (domain) == kCAAM_ECDSEL_prime239v3      ? 30u : \
     (domain) == kCAAM_ECDSEL_secp112r1       ? 14u : \
     (domain) == kCAAM_ECDSEL_wtls8           ? 14u : \
     (domain) == kCAAM_ECDSEL_wtls9           ? 20u : \
     (domain) == kCAAM_ECDSEL_secp160k1       ? 20u : \
     (domain) == kCAAM_ECDSEL_secp160r1       ? 20u : \
     (domain) == kCAAM_ECDSEL_secp160r2       ? 20u : \
     (domain) == kCAAM_ECDSEL_secp192k1       ? 24u : \
     (domain) == kCAAM_ECDSEL_secp224k1       ? 28u : \
     (domain) == kCAAM_ECDSEL_secp256k1       ? 32u : \
     (domain) == kCAAM_ECDSEL_B_163           ? 21u : \
     (domain) == kCAAM_ECDSEL_B_233           ? 30u : \
     (domain) == kCAAM_ECDSEL_B_283           ? 36u : \
     (domain) == kCAAM_ECDSEL_B_409           ? 52u : \
     (domain) == kCAAM_ECDSEL_B_571           ? 72u : \
     (domain) == kCAAM_ECDSEL_K_163           ? 21u : \
     (domain) == kCAAM_ECDSEL_K_233           ? 30u : \
     (domain) == kCAAM_ECDSEL_K_283           ? 36u : \
     (domain) == kCAAM_ECDSEL_K_409           ? 52u : \
     (domain) == kCAAM_ECDSEL_K_571           ? 72u : \
     (domain) == kCAAM_ECDSEL_wtls1           ? 15u : \
     (domain) == kCAAM_ECDSEL_sect113r1       ? 15u : \
     (domain) == kCAAM_ECDSEL_c2pnb163v1      ? 21u : \
     (domain) == kCAAM_ECDSEL_c2pnb163v2      ? 21u : \
     (domain) == kCAAM_ECDSEL_c2pnb163v3      ? 21u : \
     (domain) == kCAAM_ECDSEL_sect163r1       ? 21u : \
     (domain) == kCAAM_ECDSEL_sect193r1       ? 25u : \
     (domain) == kCAAM_ECDSEL_sect193r2       ? 25u : \
     (domain) == kCAAM_ECDSEL_sect239k1       ? 25u : \
                                              0u)

/*! @brief CAAM ECC public key length for EC domain */
#define CAAM_ECC_PUBLIC_KEY_LENGTH(domain) (CAAM_DSA_PUBLIC_KEY_LENGTH(domain) * 2u)

/*! @brief CAAM ECC private key length for EC domain */
#define CAAM_ECC_PRIVATE_KEY_LENGTH(domain)        \
    ((domain) == kCAAM_ECDSEL_P_192           ? 24u : \
     (domain) == kCAAM_ECDSEL_P_224           ? 28u : \
     (domain) == kCAAM_ECDSEL_P_256           ? 32u : \
     (domain) == kCAAM_ECDSEL_P_384           ? 48u : \
     (domain) == kCAAM_ECDSEL_P_521           ? 66u : \
     (domain) == kCAAM_ECDSEL_brainpoolP160r1 ? 20u : \
     (domain) == kCAAM_ECDSEL_brainpoolP160t1 ? 20u : \
     (domain) == kCAAM_ECDSEL_brainpoolP192r1 ? 24u : \
     (domain) == kCAAM_ECDSEL_brainpoolP192t1 ? 24u : \
     (domain) == kCAAM_ECDSEL_brainpoolP224r1 ? 28u : \
     (domain) == kCAAM_ECDSEL_brainpoolP224t1 ? 28u : \
     (domain) == kCAAM_ECDSEL_brainpoolP256r1 ? 32u : \
     (domain) == kCAAM_ECDSEL_brainpoolP256t1 ? 32u : \
     (domain) == kCAAM_ECDSEL_brainpoolP320r1 ? 40u : \
     (domain) == kCAAM_ECDSEL_brainpoolP320t1 ? 40u : \
     (domain) == kCAAM_ECDSEL_brainpoolP384r1 ? 48u : \
     (domain) == kCAAM_ECDSEL_brainpoolP384t1 ? 48u : \
     (domain) == kCAAM_ECDSEL_brainpoolP512r1 ? 64u : \
     (domain) == kCAAM_ECDSEL_brainpoolP512t1 ? 64u : \
     (domain) == kCAAM_ECDSEL_prime192v2      ? 24u : \
     (domain) == kCAAM_ECDSEL_prime192v3      ? 24u : \
     (domain) == kCAAM_ECDSEL_prime239v1      ? 30u : \
     (domain) == kCAAM_ECDSEL_prime239v2      ? 30u : \
     (domain) == kCAAM_ECDSEL_prime239v3      ? 30u : \
     (domain) == kCAAM_ECDSEL_secp112r1       ? 14u : \
     (domain) == kCAAM_ECDSEL_wtls8           ? 15u : \
     (domain) == kCAAM_ECDSEL_wtls9           ? 21u : \
     (domain) == kCAAM_ECDSEL_secp160k1       ? 21u : \
     (domain) == kCAAM_ECDSEL_secp160r1       ? 21u : \
     (domain) == kCAAM_ECDSEL_secp160r2       ? 21u : \
     (domain) == kCAAM_ECDSEL_secp192k1       ? 24u : \
     (domain) == kCAAM_ECDSEL_secp224k1       ? 29u : \
     (domain) == kCAAM_ECDSEL_secp256k1       ? 32u : \
     (domain) == kCAAM_ECDSEL_B_163           ? 21u : \
     (domain) == kCAAM_ECDSEL_B_233           ? 30u : \
     (domain) == kCAAM_ECDSEL_B_283           ? 36u : \
     (domain) == kCAAM_ECDSEL_B_409           ? 52u : \
     (domain) == kCAAM_ECDSEL_B_571           ? 72u : \
     (domain) == kCAAM_ECDSEL_K_163           ? 21u : \
     (domain) == kCAAM_ECDSEL_K_233           ? 29u : \
     (domain) == kCAAM_ECDSEL_K_283           ? 36u : \
     (domain) == kCAAM_ECDSEL_K_409           ? 51u : \
     (domain) == kCAAM_ECDSEL_K_571           ? 72u : \
     (domain) == kCAAM_ECDSEL_wtls1           ? 14u : \
     (domain) == kCAAM_ECDSEL_sect113r1       ? 15u : \
     (domain) == kCAAM_ECDSEL_c2pnb163v1      ? 21u : \
     (domain) == kCAAM_ECDSEL_c2pnb163v2      ? 21u : \
     (domain) == kCAAM_ECDSEL_c2pnb163v3      ? 21u : \
     (domain) == kCAAM_ECDSEL_sect163r1       ? 21u : \
     (domain) == kCAAM_ECDSEL_sect193r1       ? 25u : \
     (domain) == kCAAM_ECDSEL_sect193r2       ? 25u : \
     (domain) == kCAAM_ECDSEL_sect239k1       ? 25u : \
                                              0u)

/*! @brief CAAM blacken key size for ECB encryption
 *
 * The second part of key size and buffer length needed for compution may differ.
 */
#define CAAM_ECC_SECOND_SIGN_BUFFER_SIZE(domain) ((CAAM_ECC_PRIVATE_KEY_LENGTH(domain) + 15u) & ~15u)

/*!
 *@}
 */ /* end of caam_driver_des */

/*******************************************************************************
 * HASH Definitions
 ******************************************************************************/
/*!
 * @addtogroup caam_driver_hash
 * @{
 */

/*! @brief Supported cryptographic block cipher functions for HASH creation */
typedef enum _caam_hash_algo_t
{
    kCAAM_XcbcMac = 0, /*!< XCBC-MAC (AES engine) */
    kCAAM_Cmac,        /*!< CMAC (AES engine) */
    kCAAM_Sha1,        /*!< SHA_1   (MDHA engine)  */
    kCAAM_Sha224,      /*!< SHA_224 (MDHA engine)  */
    kCAAM_Sha256,      /*!< SHA_256 (MDHA engine)  */
    kCAAM_Sha384,      /*!< SHA_384 (MDHA engine)  */
    kCAAM_Sha512,      /*!< SHA_512 (MDHA engine)  */
    kCAAM_HmacSha1,    /*!< HMAC_SHA_1   (MDHA engine)  */
    kCAAM_HmacSha224,  /*!< HMAC_SHA_224 (MDHA engine)  */
    kCAAM_HmacSha256,  /*!< HMAC_SHA_256 (MDHA engine)  */
    kCAAM_HmacSha384,  /*!< HMAC_SHA_384 (MDHA engine)  */
    kCAAM_HmacSha512,  /*!< HMAC_SHA_512 (MDHA engine)  */
} caam_hash_algo_t;

/*! @brief CAAM HASH Context size. */
#define CAAM_SHA_BLOCK_SIZE  128U                /*!< up to SHA-512 block size  */
#define CAAM_HASH_BLOCK_SIZE CAAM_SHA_BLOCK_SIZE /*!< CAAM hash block size  */

/*! @brief CAAM HASH Context size. */
#define CAAM_HASH_CTX_SIZE 83

/*! @brief Storage type used to save hash context. */
typedef uint32_t caam_hash_ctx_t[CAAM_HASH_CTX_SIZE];

/*!
 *@}
 */ /* end of caam_driver_hash */

/*******************************************************************************
 * CRC Definitions
 ******************************************************************************/
/*! @brief Supported CRC modes */
typedef enum _caam_crc_algo_t
{
    kCAAM_CrcIEEE,     /*!< IEE 802 CRC32 (CRCA engine)  */
    kCAAM_CrciSCSI,    /*!< iSCSI CRC32 (CRCA engine)  */
    kCAAM_CrcCUSTPOLY, /*!< Custom polynomial mode (CRCA engine)  */
} caam_crc_algo_t;

/*! @brief CAAM AAI CRC modes*/
typedef enum _caam_aai_crc_alg
{
    kCAAM_CRC_ModeIEEE802  = 0x01U << 4, /* IEE 802 mode */
    kCAAM_CRC_ModeIETF3385 = 0x02U << 4, /* iSCSI mode */
    kCAAM_CRC_ModeCUSTPOLY =
        0x04U << 4, /* Custom polynomial programmed into Key register. Can be 1-32bits. Must be left justified */
    kCAAM_CRC_ModeDefault = 0x0U << 4, /* Input data is bit-swapped, Out data is bit and byte swapped and complemented
                                          and init value is FFFFFFFFh*/
    kCAAM_CRC_ModeDIS = 0x10U << 4,    /* Turn off input bit-swapping */
    kCAAM_CRC_ModeDOS = 0x20U << 4,    /* Turn off output bit-swapping */
    kCAAM_CRC_ModeDOC = 0x40U << 4,    /* Turn of complementing CRC output data*/
    kCAAM_CRC_ModeIVZ = 0x80U << 4,    /* Initial value is zero */
} caam_aai_crc_alg_t;

/*! @brief Storage type used to save crc context. */
#define caam_crc_ctx_t caam_hash_ctx_t

/*******************************************************************************
 * RNG Definitions
 ******************************************************************************/
/*!
 * @addtogroup caam_driver_rng
 * @{
 */

/*! @brief CAAM RNG state handle */
typedef enum _caam_rng_state_handle
{
    kCAAM_RngStateHandle0 = 0u, /*!< CAAM RNG state handle 0 */
    kCAAM_RngStateHandle1 = 1u, /*!< CAAM RNG state handle 1 */
} caam_rng_state_handle_t;

/*! @brief Type of random data to generate */
typedef enum _caam_rng_random_type
{
    kCAAM_RngDataAny       = 0u, /*!< CAAM RNG any random data bytes */
    kCAAM_RngDataOddParity = 1u, /*!< CAAM RNG odd parity random data bytes */
    kCAAM_RngDataNonZero   = 2u, /*!< CAAM RNG non zero random data bytes */
} caam_rng_random_type_t;

/*! @brief 256-bit value used as optional additional entropy input */
typedef uint32_t caam_rng_generic256_t[256 / sizeof(uint32_t)];

/*! @brief CAAM RNG configuration */
typedef struct _caam_rng_user_config
{
    uint32_t autoReseedInterval; /*!< Automatic reseed internal. If set to zero, CAAM RNG will use hardware default
                                      interval of 10.000.000 generate requests. */
    caam_rng_generic256_t *personalString; /*!< NULL or pointer to optional personalization string */
} caam_rng_config_t;

/*!
 *@}
 */ /* end of caam_driver_rng */

/*******************************************************************************
 * BLLOBS Definitions
 ******************************************************************************/
/*!
 * @addtogroup caam_driver_blob
 * @{
 */

/*! @brief CAAM FIFOST types. */
typedef enum _caam_fifost_type
{
    kCAAM_FIFOST_Type_Ecb_Jkek = 0x24u, /*!< Key Register, encrypted using AES-ECB with the job
descriptor key encryption key. */
    kCAAM_FIFOST_Type_Ecb_Tkek = 0x25u, /*!< Key Register, encrypted using AES-ECB with the
trusted descriptor key encryption key. */
    kCAAM_FIFOST_Type_Ccm_Jkek = 0x14u, /*!< Key Register, encrypted using AES-CCM with the
job descriptor key encryption key. */
    kCAAM_FIFOST_Type_Ccm_Tkek = 0x15u, /*!< Key register, encrypted using AES-CCM with the
trusted descriptor key encryption key. */
} caam_fifost_type_t;

/*! @brief CAAM descriptor types. */
typedef enum _caam_desc_type
{
    kCAAM_Descriptor_Type_Ecb_Jkek = 0x0u, /*!< Key Register, encrypted using AES-ECB with the job
descriptor key encryption key. */
    kCAAM_Descriptor_Type_Ecb_Tkek = 0x2u, /*!< Key Register, encrypted using AES-ECB with the
trusted descriptor key encryption key. */
    kCAAM_Descriptor_Type_Ccm_Jkek = 0x1u, /*!< Key Register, encrypted using AES-CCM with the
job descriptor key encryption key. */
    kCAAM_Descriptor_Type_Ccm_Tkek = 0x3u, /*!< Key register, encrypted using AES-CCM with the
trusted descriptor key encryption key. */
} caam_desc_type_t;

/*! @brief CAAM key types. */
typedef enum _caam_key_type
{
    kCAAM_Key_Type_None     = 0x0ul,
    kCAAM_Key_Type_Ecb_Jkek = 0x80ul << 15, /*!< Key Register, encrypted using AES-ECB with the job
  descriptor key encryption key. */
    kCAAM_Key_Type_Ecb_Tkek = 0x81ul << 15, /*!< Key Register, encrypted using AES-ECB with the
  trusted descriptor key encryption key. */
    kCAAM_Key_Type_Ccm_Jkek = 0xA0ul << 15, /*!< Key Register, encrypted using AES-CCM with the
job descriptor key encryption key. */
    kCAAM_Key_Type_Ccm_Tkek = 0xA1ul << 15, /*!< Key register, encrypted using AES-CCM with the
trusted descriptor key encryption key. */
} caam_key_type_t;

/*! @brief CAAM ecc encryption types. */
typedef enum _caam_ecc_encryption_type
{
    kCAAM_Ecc_Encryption_Type_None     = 0x0u,
    kCAAM_Ecc_Encryption_Type_Ecb_Jkek = 0x1u << 2, /*!< Key Register, encrypted using AES-ECB with the job
        descriptor key encryption key. */
    kCAAM_Ecc_Encryption_Type_Ccm_Jkek = 0x5u << 2, /*!< Key Register, encrypted using AES-CCM with the
    job descriptor key encryption key. */
} caam_ecc_encryption_type_t;

/*! @brief CAAM rsa key encryption types. */
typedef enum _caam_rsa_key_type
{
    kCAAM_Rsa_Key_Type_None     = 0x0u,
    kCAAM_Rsa_Key_Type_Ecb_Jkek = 0x4u << 4, /*!< Key Register, encrypted using AES-ECB with the job
        descriptor key encryption key. */
    kCAAM_Rsa_Key_Type_Ccm_Jkek = 0x5u << 4, /*!< Key Register, encrypted using AES-CCM with the
    job descriptor key encryption key. */
} caam_rsa_key_type_t;

/*! @brief CAAM rsa encryption types. */
typedef enum _caam_rsa_encryption_type
{
    kCAAM_Rsa_Encryption_Type_None     = 0x00u,
    kCAAM_Rsa_Encryption_Type_Ecb_Jkek = 0x01u, /*!< Key Register, encrypted using AES-ECB with the job
      descriptor key encryption key. */
    kCAAM_Rsa_Encryption_Type_Ecb_Tkek = 0x05u, /*!< Key Register, encrypted using AES-ECB with the
     trusted descriptor key encryption key. */
    kCAAM_Rsa_Encryption_Type_Ccm_Jkek = 0x03u, /*!< Key Register, encrypted using AES-CCM with the
  job descriptor key encryption key. */
    kCAAM_Rsa_Encryption_Type_Ccm_Tkek = 0x07u, /*!< Key register, encrypted using AES-CCM with the
  trusted descriptor key encryption key. */
} caam_rsa_encryption_type_t;

typedef enum _caam_rsa_format_type
{
    kCAAM_Rsa_Format_Type_None  = 0x00u, /*!< No formatting */
    kCAAM_Rsa_Format_Type_PKCS1 = 0x01u, /*!< EME-PKCS1-v1_5 encryption decoding function */
} caam_rsa_format_type_t;

// #define KEYBLOB_USE_SECURE_MEMORY 1  // Define when secure memory mode is used

/*!
 *@}
 */ /* end of caam_driver_blob */

/*******************************************************************************
 * PKHA Definitions
 ******************************************************************************/
/*!
 * @addtogroup caam_driver_pkha
 * @{
 */
/*! PKHA ECC point structure */
typedef struct _caam_pkha_ecc_point_t
{
    uint8_t *X; /*!< X coordinate (affine) */
    uint8_t *Y; /*!< Y coordinate (affine) */
} caam_pkha_ecc_point_t;

/*! @brief Use of timing equalized version of a PKHA function. */
typedef enum _caam_pkha_timing_t
{
    kCAAM_PKHA_NoTimingEqualized = 0U, /*!< Normal version of a PKHA operation */
    kCAAM_PKHA_TimingEqualized   = 1U  /*!< Timing-equalized version of a PKHA operation  */
} caam_pkha_timing_t;

/*! @brief Integer vs binary polynomial arithmetic selection. */
typedef enum _caam_pkha_f2m_t
{
    kCAAM_PKHA_IntegerArith = 0U, /*!< Use integer arithmetic */
    kCAAM_PKHA_F2mArith     = 1U  /*!< Use binary polynomial arithmetic */
} caam_pkha_f2m_t;

/*! @brief Montgomery or normal PKHA input format. */
typedef enum _caam_pkha_montgomery_form_t
{
    kCAAM_PKHA_NormalValue      = 0U, /*!< PKHA number is normal integer */
    kCAAM_PKHA_MontgomeryFormat = 1U  /*!< PKHA number is in montgomery format */
} caam_pkha_montgomery_form_t;

/*!
 *@}
 */ /* end of caam_driver_pkha */

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @addtogroup caam_driver
 * @{
 */

/*!
 * @brief Initializes the CAAM driver.
 *
 * This function initializes the CAAM driver, including CAAM's internal RNG.
 * @param base CAAM peripheral base address
 * @param config Pointer to configuration structure.
 * @return kStatus_Success the CAAM Init has completed with zero termination status word
 * @return kStatus_Fail the CAAM Init has completed with non-zero termination status word
 */
status_t CAAM_Init(CAAM_Type *base, const caam_config_t *config);

/*!
 * @brief Deinitializes the CAAM driver.
 * This function deinitializes the CAAM driver.
 * @param base CAAM peripheral base address
 * @return kStatus_Success the CAAM Deinit has completed with zero termination status word
 * @return kStatus_Fail the CAAM Deinit has completed with non-zero termination status word
 */
status_t CAAM_Deinit(CAAM_Type *base);

/*!
 * @brief Gets the default configuration structure.
 *
 * This function initializes the CAAM configuration structure to a default value. The default
 * values are as follows.
 *   caamConfig->rngSampleMode = kCAAM_RNG_SampleModeVonNeumann;
 *   caamConfig->rngRingOscDiv = kCAAM_RNG_RingOscDiv4;
 *
 * @param[out] config Pointer to configuration structure.
 */
void CAAM_GetDefaultConfig(caam_config_t *config);

/*!
 * @brief Wait for a CAAM job to complete.
 *
 * This function polls CAAM output ring for a specific job.
 *
 * The CAAM job ring is specified by the jobRing field in the caam_handle_t structure.
 * The job to be waited is specified by it's descriptor address.
 *
 * This function has two modes, determined by the mode argument.
 * In blocking mode, the function polls the specified jobRing until the descriptor
 * is available in the CAAM output job ring.
 * In non-blocking mode, it polls the output ring once and returns status
 * immediately.
 *
 * The function can be called from multiple threads or interrupt service routines,
 * as internally it uses global critical section (global interrupt disable enable)
 * to protect it's operation against concurrent accesses.
 * The global interrupt is disabled only when the descriptor is found
 * in the output ring, for a very short time, to remove the descriptor from the output ring
 * safely.
 *
 * @param base CAAM peripheral base address
 * @param handle Data structure with CAAM jobRing used for this request
 * @param descriptor
 * @param mode Blocking and non-blocking mode. Zero is blocking. Non-zero is non-blocking.
 * @return kStatus_Success the CAAM job has completed with zero job termination status word
 * @return kStatus_Fail the CAAM job has completed with non-zero job termination status word
 * @return kStatus_Again In non-blocking mode, the job is not ready in the CAAM Output Ring
 */
status_t CAAM_Wait(CAAM_Type *base, caam_handle_t *handle, uint32_t *descriptor, caam_wait_mode_t mode);

/*!
 * @brief External Key Transfer.
 *
 * This function loads the given key source to an CAAM external destination via a private interface,
 * such as Inline Encryption Engine IEE Private Key bus.
 *
 * The CAAM job ring is specified by the jobRing field in the caam_handle_t structure.
 *
 * This function is blocking.
 *
 * @param base CAAM peripheral base address
 * @param handle Data structure with CAAM jobRing used for this request.
 * @param keySource The source from which the key will be obtained.
 * @param keySize Size of the key in bytes.
 * @return kStatus_Success the CAAM job has completed with zero job termination status word
 * @return kStatus_Fail the CAAM job has completed with non-zero job termination status word
 */
status_t CAAM_ExternalKeyTransfer(CAAM_Type *base,
                                  caam_handle_t *handle,
                                  caam_ext_key_xfr_source_t keySource,
                                  size_t keySize);

/*!
 *@}
 */ /* end of caam_driver */

/*******************************************************************************
 * AES API
 ******************************************************************************/

/*!
 * @addtogroup caam_driver_aes
 * @{
 */

/*!
 * @brief Encrypts AES using the ECB block mode.
 *
 * Encrypts AES using the ECB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @return Status from encrypt operation
 */
status_t CAAM_AES_EncryptEcb(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *plaintext,
                             uint8_t *ciphertext,
                             size_t size,
                             const uint8_t *key,
                             size_t keySize);

/*!
 * @brief Decrypts AES using ECB block mode.
 *
 * Decrypts AES using ECB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param key Input key.
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @return Status from decrypt operation
 */
status_t CAAM_AES_DecryptEcb(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *ciphertext,
                             uint8_t *plaintext,
                             size_t size,
                             const uint8_t *key,
                             size_t keySize);

/*!
 * @brief Encrypts AES using the ECB block mode using black key.
 *
 * Encrypts AES using the ECB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param blackKeyType Type of black key
 * @return Status from encrypt operation
 */
status_t CAAM_AES_EncryptEcbExtended(CAAM_Type *base,
                                     caam_handle_t *handle,
                                     const uint8_t *plaintext,
                                     uint8_t *ciphertext,
                                     size_t size,
                                     const uint8_t *key,
                                     size_t keySize,
                                     caam_key_type_t blackKeyType);

/*!
 * @brief Decrypts AES using ECB block mode using black key.
 *
 * Decrypts AES using ECB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param key Input key.
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param blackKeyType Type of black key
 * @return Status from decrypt operation
 */
status_t CAAM_AES_DecryptEcbExtended(CAAM_Type *base,
                                     caam_handle_t *handle,
                                     const uint8_t *ciphertext,
                                     uint8_t *plaintext,
                                     size_t size,
                                     const uint8_t *key,
                                     size_t keySize,
                                     caam_key_type_t blackKeyType);

/*!
 * @brief Encrypts AES using CBC block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @return Status from encrypt operation
 */
status_t CAAM_AES_EncryptCbc(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *plaintext,
                             uint8_t *ciphertext,
                             size_t size,
                             const uint8_t iv[CAAM_AES_BLOCK_SIZE],
                             const uint8_t *key,
                             size_t keySize);

/*!
 * @brief Decrypts AES using CBC block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @return Status from decrypt operation
 */
status_t CAAM_AES_DecryptCbc(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *ciphertext,
                             uint8_t *plaintext,
                             size_t size,
                             const uint8_t iv[CAAM_AES_BLOCK_SIZE],
                             const uint8_t *key,
                             size_t keySize);

/*!
 * @brief Encrypts AES using CBC block mode using black key.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param blackKeyType Type of black key
 * @return Status from encrypt operation
 */
status_t CAAM_AES_EncryptCbcExtended(CAAM_Type *base,
                                     caam_handle_t *handle,
                                     const uint8_t *plaintext,
                                     uint8_t *ciphertext,
                                     size_t size,
                                     const uint8_t iv[CAAM_AES_BLOCK_SIZE],
                                     const uint8_t *key,
                                     size_t keySize,
                                     caam_key_type_t blackKeyType);

/*!
 * @brief Decrypts AES using CBC block mode using black key.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param blackKeyType Type of black key
 * @return Status from decrypt operation
 */
status_t CAAM_AES_DecryptCbcExtended(CAAM_Type *base,
                                     caam_handle_t *handle,
                                     const uint8_t *ciphertext,
                                     uint8_t *plaintext,
                                     size_t size,
                                     const uint8_t iv[CAAM_AES_BLOCK_SIZE],
                                     const uint8_t *key,
                                     size_t keySize,
                                     caam_key_type_t blackKeyType);

/*!
 * @brief Encrypts or decrypts AES using CTR block mode.
 *
 * Encrypts or decrypts AES using CTR block mode.
 * AES CTR mode uses only forward AES cipher and same algorithm for encryption and decryption.
 * The only difference between encryption and decryption is that, for encryption, the input argument
 * is plain text and the output argument is cipher text. For decryption, the input argument is cipher text
 * and the output argument is plain text.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param input Input data for CTR block mode
 * @param[out] output Output data for CTR block mode
 * @param size Size of input and output data in bytes
 * @param[in,out] counter Input counter (updates on return)
 * @param key Input key to use for forward AES cipher
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] counterlast Output cipher of last counter, for chained CTR calls. NULL can be passed if chained calls are
 * not used.
 * @param[out] szLeft Output number of bytes in left unused in counterlast block. NULL can be passed if chained calls
 * are not used.
 * @return Status from encrypt operation
 */
status_t CAAM_AES_CryptCtr(CAAM_Type *base,
                           caam_handle_t *handle,
                           const uint8_t *input,
                           uint8_t *output,
                           size_t size,
                           uint8_t counter[CAAM_AES_BLOCK_SIZE],
                           const uint8_t *key,
                           size_t keySize,
                           uint8_t counterlast[CAAM_AES_BLOCK_SIZE],
                           size_t *szLeft);

/*!
 * @brief Encrypts or decrypts AES using CTR block mode using black key.
 *
 * Encrypts or decrypts AES using CTR block mode.
 * AES CTR mode uses only forward AES cipher and same algorithm for encryption and decryption.
 * The only difference between encryption and decryption is that, for encryption, the input argument
 * is plain text and the output argument is cipher text. For decryption, the input argument is cipher text
 * and the output argument is plain text.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param input Input data for CTR block mode
 * @param[out] output Output data for CTR block mode
 * @param size Size of input and output data in bytes
 * @param[in,out] counter Input counter (updates on return)
 * @param key Input key to use for forward AES cipher
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] counterlast Output cipher of last counter, for chained CTR calls. NULL can be passed if chained calls are
 * not used.
 * @param[out] szLeft Output number of bytes in left unused in counterlast block. NULL can be passed if chained calls
 * are not used.
 * @param blackKeyType Type of black key
 * @return Status from encrypt operation
 */
status_t CAAM_AES_CryptCtrExtended(CAAM_Type *base,
                                   caam_handle_t *handle,
                                   const uint8_t *input,
                                   uint8_t *output,
                                   size_t size,
                                   uint8_t counter[CAAM_AES_BLOCK_SIZE],
                                   const uint8_t *key,
                                   size_t keySize,
                                   uint8_t counterlast[CAAM_AES_BLOCK_SIZE],
                                   size_t *szLeft,
                                   caam_key_type_t blackKeyType);

/*!
 * @brief Encrypts AES and tags using CCM block mode.
 *
 * Encrypts AES and optionally tags using CCM block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text.
 * @param size Size of input and output data in bytes. Zero means authentication only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication skipped).
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] tag Generated output tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4, 6, 8, 10, 12, 14, or 16.
 * @return Status from encrypt operation
 */
status_t CAAM_AES_EncryptTagCcm(CAAM_Type *base,
                                caam_handle_t *handle,
                                const uint8_t *plaintext,
                                uint8_t *ciphertext,
                                size_t size,
                                const uint8_t *iv,
                                size_t ivSize,
                                const uint8_t *aad,
                                size_t aadSize,
                                const uint8_t *key,
                                size_t keySize,
                                uint8_t *tag,
                                size_t tagSize);

/*!
 * @brief Decrypts AES and authenticates using CCM block mode.
 *
 * Decrypts AES and optionally authenticates using CCM block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text.
 * @param size Size of input and output data in bytes. Zero means authentication data only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication data skipped).
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Received tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the received tag to compare with the computed tag, in bytes. Must be 4, 6, 8, 10, 12,
 *                14, or 16.
 * @return Status from decrypt operation
 */
status_t CAAM_AES_DecryptTagCcm(CAAM_Type *base,
                                caam_handle_t *handle,
                                const uint8_t *ciphertext,
                                uint8_t *plaintext,
                                size_t size,
                                const uint8_t *iv,
                                size_t ivSize,
                                const uint8_t *aad,
                                size_t aadSize,
                                const uint8_t *key,
                                size_t keySize,
                                const uint8_t *tag,
                                size_t tagSize);

/*!
 * @brief Encrypts AES and tags using CCM block mode using black key.
 *
 * Encrypts AES and optionally tags using CCM block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text.
 * @param size Size of input and output data in bytes. Zero means authentication only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication skipped).
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] tag Generated output tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4, 6, 8, 10, 12, 14, or 16.
 * @param blackKeyType Type of black key
 * @return Status from encrypt operation
 */
status_t CAAM_AES_EncryptTagCcmExtended(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        const uint8_t *plaintext,
                                        uint8_t *ciphertext,
                                        size_t size,
                                        const uint8_t *iv,
                                        size_t ivSize,
                                        const uint8_t *aad,
                                        size_t aadSize,
                                        const uint8_t *key,
                                        size_t keySize,
                                        uint8_t *tag,
                                        size_t tagSize,
                                        caam_key_type_t blackKeyType);

/*!
 * @brief Decrypts AES and authenticates using CCM block mode using black key.
 *
 * Decrypts AES and optionally authenticates using CCM block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text.
 * @param size Size of input and output data in bytes. Zero means authentication data only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication data skipped).
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Received tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the received tag to compare with the computed tag, in bytes. Must be 4, 6, 8, 10, 12,
 *                14, or 16.
 * @param blackKeyType Type of black key
 * @return Status from decrypt operation
 */
status_t CAAM_AES_DecryptTagCcmExtended(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        const uint8_t *ciphertext,
                                        uint8_t *plaintext,
                                        size_t size,
                                        const uint8_t *iv,
                                        size_t ivSize,
                                        const uint8_t *aad,
                                        size_t aadSize,
                                        const uint8_t *key,
                                        size_t keySize,
                                        const uint8_t *tag,
                                        size_t tagSize,
                                        caam_key_type_t blackKeyType);

/*!
 * @brief Encrypts AES and tags using GCM block mode.
 *
 * Encrypts AES and optionally tags using GCM block mode. If plaintext is NULL, only the GHASH is calculated and output
 * in the 'tag' field.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text.
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] tag Output hash tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4,8,12,13,14,15 or 16.
 * @return Status from encrypt operation
 */
status_t CAAM_AES_EncryptTagGcm(CAAM_Type *base,
                                caam_handle_t *handle,
                                const uint8_t *plaintext,
                                uint8_t *ciphertext,
                                size_t size,
                                const uint8_t *iv,
                                size_t ivSize,
                                const uint8_t *aad,
                                size_t aadSize,
                                const uint8_t *key,
                                size_t keySize,
                                uint8_t *tag,
                                size_t tagSize);

/*!
 * @brief Decrypts AES and authenticates using GCM block mode.
 *
 * Decrypts AES and optionally authenticates using GCM block mode. If ciphertext is NULL, only the GHASH is calculated
 * and compared with the received GHASH in 'tag' field.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text.
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Input hash tag to compare. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag, in bytes. Must be 4, 8, 12, 13, 14, 15, or 16.
 * @return Status from decrypt operation
 */
status_t CAAM_AES_DecryptTagGcm(CAAM_Type *base,
                                caam_handle_t *handle,
                                const uint8_t *ciphertext,
                                uint8_t *plaintext,
                                size_t size,
                                const uint8_t *iv,
                                size_t ivSize,
                                const uint8_t *aad,
                                size_t aadSize,
                                const uint8_t *key,
                                size_t keySize,
                                const uint8_t *tag,
                                size_t tagSize);

/*!
 * @brief Encrypts AES and tags using GCM block mode using black key.
 *
 * Encrypts AES and optionally tags using GCM block mode. If plaintext is NULL, only the GHASH is calculated and output
 * in the 'tag' field. Uses black key.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text.
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] tag Output hash tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4,8,12,13,14,15 or 16.
 * @param blackenKeyType Type of black key
 * @return Status from encrypt operation
 */
status_t CAAM_AES_EncryptTagGcmExtended(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        const uint8_t *plaintext,
                                        uint8_t *ciphertext,
                                        size_t size,
                                        const uint8_t *iv,
                                        size_t ivSize,
                                        const uint8_t *aad,
                                        size_t aadSize,
                                        const uint8_t *key,
                                        size_t keySize,
                                        uint8_t *tag,
                                        size_t tagSize,
                                        caam_key_type_t blackKeyType);

/*!
 * @brief Decrypts AES and authenticates using GCM block mode using black key.
 *
 * Decrypts AES and optionally authenticates using GCM block mode. If ciphertext is NULL, only the GHASH is calculated
 * and compared with the received GHASH in 'tag' field. Uses black key.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text.
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Input hash tag to compare. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag, in bytes. Must be 4, 8, 12, 13, 14, 15, or 16.
 * @param blackenKeyType Type of black key
 * @return Status from decrypt operation
 */
status_t CAAM_AES_DecryptTagGcmExtended(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        const uint8_t *ciphertext,
                                        uint8_t *plaintext,
                                        size_t size,
                                        const uint8_t *iv,
                                        size_t ivSize,
                                        const uint8_t *aad,
                                        size_t aadSize,
                                        const uint8_t *key,
                                        size_t keySize,
                                        const uint8_t *tag,
                                        size_t tagSize,
                                        caam_key_type_t blackKeyType);
/*!
 *@}
 */ /* end of caam_driver_aes */

/*!
 * @addtogroup caam_nonblocking_driver_aes
 * @{
 */
/*!
 * @brief Encrypts AES using the ECB block mode.
 *
 * Puts AES ECB encrypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param[out] ciphertext Output cipher text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @return Status from job descriptor push
 */
status_t CAAM_AES_EncryptEcbNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_aes_ecb_t descriptor,
                                        const uint8_t *plaintext,
                                        uint8_t *ciphertext,
                                        size_t size,
                                        const uint8_t *key,
                                        size_t keySize);

/*!
 * @brief Decrypts AES using ECB block mode.
 *
 * Puts AES ECB decrypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param key Input key.
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @return Status from job descriptor push
 */
status_t CAAM_AES_DecryptEcbNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_aes_ecb_t descriptor,
                                        const uint8_t *ciphertext,
                                        uint8_t *plaintext,
                                        size_t size,
                                        const uint8_t *key,
                                        size_t keySize);

/*!
 * @brief Encrypts AES using the ECB block mode using black key.
 *
 * Puts AES ECB encrypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plain text to encrypt
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param[out] ciphertext Output cipher text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param blackKeyType Type of black key
 * @return Status from job descriptor push
 */
status_t CAAM_AES_EncryptEcbNonBlockingExtended(CAAM_Type *base,
                                                caam_handle_t *handle,
                                                caam_desc_aes_ecb_t descriptor,
                                                const uint8_t *plaintext,
                                                uint8_t *ciphertext,
                                                size_t size,
                                                const uint8_t *key,
                                                size_t keySize,
                                                caam_key_type_t blackKeyType);

/*!
 * @brief Decrypts AES using ECB block mode using black key.
 *
 * Puts AES ECB decrypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param key Input key.
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param blackKeyType Type of black key
 * @return Status from job descriptor push
 */
status_t CAAM_AES_DecryptEcbNonBlockingExtended(CAAM_Type *base,
                                                caam_handle_t *handle,
                                                caam_desc_aes_ecb_t descriptor,
                                                const uint8_t *ciphertext,
                                                uint8_t *plaintext,
                                                size_t size,
                                                const uint8_t *key,
                                                size_t keySize,
                                                caam_key_type_t blackKeyType);

/*!
 * @brief Encrypts AES using CBC block mode.
 *
 * Puts AES CBC encrypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @return Status from job descriptor push
 */
status_t CAAM_AES_EncryptCbcNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_aes_cbc_t descriptor,
                                        const uint8_t *plaintext,
                                        uint8_t *ciphertext,
                                        size_t size,
                                        const uint8_t *iv,
                                        const uint8_t *key,
                                        size_t keySize);

/*!
 * @brief Decrypts AES using CBC block mode.
 *
 * Puts AES CBC decrypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @return Status from job descriptor push
 */
status_t CAAM_AES_DecryptCbcNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_aes_cbc_t descriptor,
                                        const uint8_t *ciphertext,
                                        uint8_t *plaintext,
                                        size_t size,
                                        const uint8_t *iv,
                                        const uint8_t *key,
                                        size_t keySize);

/*!
 * @brief Encrypts AES using CBC block mode using black key.
 *
 * Puts AES CBC encrypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param blackKeyType Type of black key
 * @return Status from job descriptor push
 */
status_t CAAM_AES_EncryptCbcNonBlockingExtended(CAAM_Type *base,
                                                caam_handle_t *handle,
                                                caam_desc_aes_cbc_t descriptor,
                                                const uint8_t *plaintext,
                                                uint8_t *ciphertext,
                                                size_t size,
                                                const uint8_t *iv,
                                                const uint8_t *key,
                                                size_t keySize,
                                                caam_key_type_t blackKeyType);

/*!
 * @brief Decrypts AES using CBC block mode using black key.
 *
 * Puts AES CBC decrypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text
 * @param size Size of input and output data in bytes. Must be multiple of 16 bytes.
 * @param iv Input initial vector to combine with the first input block.
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param blackKeyType Type of black key
 * @return Status from job descriptor push
 */
status_t CAAM_AES_DecryptCbcNonBlockingExtended(CAAM_Type *base,
                                                caam_handle_t *handle,
                                                caam_desc_aes_cbc_t descriptor,
                                                const uint8_t *ciphertext,
                                                uint8_t *plaintext,
                                                size_t size,
                                                const uint8_t *iv,
                                                const uint8_t *key,
                                                size_t keySize,
                                                caam_key_type_t blackKeyType);

/*!
 * @brief Encrypts or decrypts AES using CTR block mode.
 *
 * Encrypts or decrypts AES using CTR block mode.
 * AES CTR mode uses only forward AES cipher and same algorithm for encryption and decryption.
 * The only difference between encryption and decryption is that, for encryption, the input argument
 * is plain text and the output argument is cipher text. For decryption, the input argument is cipher text
 * and the output argument is plain text.
 *
 * Puts AES CTR crypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param input Input data for CTR block mode
 * @param[out] output Output data for CTR block mode
 * @param size Size of input and output data in bytes
 * @param[in,out] counter Input counter (updates on return)
 * @param key Input key to use for forward AES cipher
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] counterlast Output cipher of last counter, for chained CTR calls. NULL can be passed if chained calls are
 * not used.
 * @param[out] szLeft Output number of bytes in left unused in counterlast block. NULL can be passed if chained calls
 * are not used.
 * @return Status from job descriptor push
 */
status_t CAAM_AES_CryptCtrNonBlocking(CAAM_Type *base,
                                      caam_handle_t *handle,
                                      caam_desc_aes_ctr_t descriptor,
                                      const uint8_t *input,
                                      uint8_t *output,
                                      size_t size,
                                      uint8_t *counter,
                                      const uint8_t *key,
                                      size_t keySize,
                                      uint8_t *counterlast,
                                      size_t *szLeft);

/*!
 * @brief Encrypts or decrypts AES using CTR block mode using black key.
 *
 * Encrypts or decrypts AES using CTR block mode.
 * AES CTR mode uses only forward AES cipher and same algorithm for encryption and decryption.
 * The only difference between encryption and decryption is that, for encryption, the input argument
 * is plain text and the output argument is cipher text. For decryption, the input argument is cipher text
 * and the output argument is plain text.
 *
 * Puts AES CTR crypt descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param input Input data for CTR block mode
 * @param[out] output Output data for CTR block mode
 * @param size Size of input and output data in bytes
 * @param[in,out] counter Input counter (updates on return)
 * @param key Input key to use for forward AES cipher
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] counterlast Output cipher of last counter, for chained CTR calls. NULL can be passed if chained calls are
 * not used.
 * @param[out] szLeft Output number of bytes in left unused in counterlast block. NULL can be passed if chained calls
 * are not used.
 * @param blackKeyType Type of black key
 * @return Status from job descriptor push
 */
status_t CAAM_AES_CryptCtrNonBlockingExtended(CAAM_Type *base,
                                              caam_handle_t *handle,
                                              caam_desc_aes_ctr_t descriptor,
                                              const uint8_t *input,
                                              uint8_t *output,
                                              size_t size,
                                              uint8_t *counter,
                                              const uint8_t *key,
                                              size_t keySize,
                                              uint8_t *counterlast,
                                              size_t *szLeft,
                                              caam_key_type_t blackKeyType);

/*!
 * @brief Encrypts AES and tags using CCM block mode.
 *
 * Puts AES CCM encrypt and tag descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text.
 * @param size Size of input and output data in bytes. Zero means authentication only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication skipped).
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] tag Generated output tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4, 6, 8, 10, 12, 14, or 16.
 * @return Status from job descriptor push
 */
status_t CAAM_AES_EncryptTagCcmNonBlocking(CAAM_Type *base,
                                           caam_handle_t *handle,
                                           caam_desc_aes_ccm_t descriptor,
                                           const uint8_t *plaintext,
                                           uint8_t *ciphertext,
                                           size_t size,
                                           const uint8_t *iv,
                                           size_t ivSize,
                                           const uint8_t *aad,
                                           size_t aadSize,
                                           const uint8_t *key,
                                           size_t keySize,
                                           uint8_t *tag,
                                           size_t tagSize);

/*!
 * @brief Decrypts AES and authenticates using CCM block mode.
 *
 * Puts AES CCM decrypt and check tag descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text.
 * @param size Size of input and output data in bytes. Zero means authentication data only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication data skipped).
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Received tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the received tag to compare with the computed tag, in bytes. Must be 4, 6, 8, 10, 12,
 *                14, or 16.
 * @return Status from job descriptor push
 */

status_t CAAM_AES_DecryptTagCcmNonBlocking(CAAM_Type *base,
                                           caam_handle_t *handle,
                                           caam_desc_aes_ccm_t descriptor,
                                           const uint8_t *ciphertext,
                                           uint8_t *plaintext,
                                           size_t size,
                                           const uint8_t *iv,
                                           size_t ivSize,
                                           const uint8_t *aad,
                                           size_t aadSize,
                                           const uint8_t *key,
                                           size_t keySize,
                                           const uint8_t *tag,
                                           size_t tagSize);

/*!
 * @brief Encrypts AES and tags using CCM block mode using black key.
 *
 * Puts AES CCM encrypt and tag descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text.
 * @param size Size of input and output data in bytes. Zero means authentication only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication skipped).
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] tag Generated output tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4, 6, 8, 10, 12, 14, or 16.
 * @param blackKeyType Type of black key
 * @return Status from job descriptor push
 */
status_t CAAM_AES_EncryptTagCcmNonBlockingExtended(CAAM_Type *base,
                                                   caam_handle_t *handle,
                                                   caam_desc_aes_ccm_t descriptor,
                                                   const uint8_t *plaintext,
                                                   uint8_t *ciphertext,
                                                   size_t size,
                                                   const uint8_t *iv,
                                                   size_t ivSize,
                                                   const uint8_t *aad,
                                                   size_t aadSize,
                                                   const uint8_t *key,
                                                   size_t keySize,
                                                   uint8_t *tag,
                                                   size_t tagSize,
                                                   caam_key_type_t blackKeyType);

/*!
 * @brief Decrypts AES and authenticates using CCM block mode using black key.
 *
 * Puts AES CCM decrypt and check tag descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text.
 * @param size Size of input and output data in bytes. Zero means authentication data only.
 * @param iv Nonce
 * @param ivSize Length of the Nonce in bytes. Must be 7, 8, 9, 10, 11, 12, or 13.
 * @param aad Input additional authentication data. Can be NULL if aadSize is zero.
 * @param aadSize Input size in bytes of AAD. Zero means data mode only (authentication data skipped).
 * @param key Input key to use for decryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Received tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the received tag to compare with the computed tag, in bytes. Must be 4, 6, 8, 10, 12,
 *                14, or 16.
 * @param blackKeyType Type of black key
 * @return Status from job descriptor push
 */

status_t CAAM_AES_DecryptTagCcmNonBlockingExtended(CAAM_Type *base,
                                                   caam_handle_t *handle,
                                                   caam_desc_aes_ccm_t descriptor,
                                                   const uint8_t *ciphertext,
                                                   uint8_t *plaintext,
                                                   size_t size,
                                                   const uint8_t *iv,
                                                   size_t ivSize,
                                                   const uint8_t *aad,
                                                   size_t aadSize,
                                                   const uint8_t *key,
                                                   size_t keySize,
                                                   const uint8_t *tag,
                                                   size_t tagSize,
                                                   caam_key_type_t blackKeyType);

/*!
 * @brief Encrypts AES and tags using GCM block mode.
 *
 * Encrypts AES and optionally tags using GCM block mode. If plaintext is NULL, only the GHASH is calculated and output
 * in the 'tag' field.
 * Puts AES GCM encrypt and tag descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text.
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] tag Output hash tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4,8,12,13,14,15 or 16.
 * @return Status from job descriptor push
 */
status_t CAAM_AES_EncryptTagGcmNonBlocking(CAAM_Type *base,
                                           caam_handle_t *handle,
                                           caam_desc_aes_gcm_t descriptor,
                                           const uint8_t *plaintext,
                                           uint8_t *ciphertext,
                                           size_t size,
                                           const uint8_t *iv,
                                           size_t ivSize,
                                           const uint8_t *aad,
                                           size_t aadSize,
                                           const uint8_t *key,
                                           size_t keySize,
                                           uint8_t *tag,
                                           size_t tagSize);

/*!
 * @brief Decrypts AES and authenticates using GCM block mode.
 *
 * Decrypts AES and optionally authenticates using GCM block mode. If ciphertext is NULL, only the GHASH is calculated
 * and compared with the received GHASH in 'tag' field.
 * Puts AES GCM decrypt and check tag descriptor to CAAM input job ring.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text.
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Input hash tag to compare. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag, in bytes. Must be 4, 8, 12, 13, 14, 15, or 16.
 * @return Status from job descriptor push
 */
status_t CAAM_AES_DecryptTagGcmNonBlocking(CAAM_Type *base,
                                           caam_handle_t *handle,
                                           caam_desc_aes_gcm_t descriptor,
                                           const uint8_t *ciphertext,
                                           uint8_t *plaintext,
                                           size_t size,
                                           const uint8_t *iv,
                                           size_t ivSize,
                                           const uint8_t *aad,
                                           size_t aadSize,
                                           const uint8_t *key,
                                           size_t keySize,
                                           const uint8_t *tag,
                                           size_t tagSize);

/*!
 * @brief Encrypts AES and tags using GCM block mode using black key.
 *
 * Encrypts AES and optionally tags using GCM block mode. If plaintext is NULL, only the GHASH is calculated and output
 * in the 'tag' field.
 * Puts AES GCM encrypt and tag descriptor to CAAM input job ring.
 * Uses black key.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param plaintext Input plain text to encrypt
 * @param[out] ciphertext Output cipher text.
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param[out] tag Output hash tag. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag to generate, in bytes. Must be 4,8,12,13,14,15 or 16.
 * @return Status from job descriptor push
 * @param blackenKeyType Type of black key
 */
status_t CAAM_AES_EncryptTagGcmNonBlockingExtended(CAAM_Type *base,
                                                   caam_handle_t *handle,
                                                   caam_desc_aes_gcm_t descriptor,
                                                   const uint8_t *plaintext,
                                                   uint8_t *ciphertext,
                                                   size_t size,
                                                   const uint8_t *iv,
                                                   size_t ivSize,
                                                   const uint8_t *aad,
                                                   size_t aadSize,
                                                   const uint8_t *key,
                                                   size_t keySize,
                                                   uint8_t *tag,
                                                   size_t tagSize,
                                                   caam_key_type_t blackKeyType);

/*!
 * @brief Decrypts AES and authenticates using GCM block mode using black key.
 *
 * Decrypts AES and optionally authenticates using GCM block mode. If ciphertext is NULL, only the GHASH is calculated
 * and compared with the received GHASH in 'tag' field.
 * Puts AES GCM decrypt and check tag descriptor to CAAM input job ring.
 * Uses black key.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param ciphertext Input cipher text to decrypt
 * @param[out] plaintext Output plain text.
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector
 * @param ivSize Size of the IV
 * @param aad Input additional authentication data
 * @param aadSize Input size in bytes of AAD
 * @param key Input key to use for encryption
 * @param keySize Size of the input key, in bytes. Must be 16, 24, or 32.
 * @param tag Input hash tag to compare. Set to NULL to skip tag processing.
 * @param tagSize Input size of the tag, in bytes. Must be 4, 8, 12, 13, 14, 15, or 16.
 * @param blackenKeyType Type of black key
 * @return Status from job descriptor push
 */
status_t CAAM_AES_DecryptTagGcmNonBlockingExtended(CAAM_Type *base,
                                                   caam_handle_t *handle,
                                                   caam_desc_aes_gcm_t descriptor,
                                                   const uint8_t *ciphertext,
                                                   uint8_t *plaintext,
                                                   size_t size,
                                                   const uint8_t *iv,
                                                   size_t ivSize,
                                                   const uint8_t *aad,
                                                   size_t aadSize,
                                                   const uint8_t *key,
                                                   size_t keySize,
                                                   const uint8_t *tag,
                                                   size_t tagSize,
                                                   caam_key_type_t blackKeyType);
/*!
 *@}
 */ /* end of caam_nonblocking_driver_aes */

/*******************************************************************************
 * HASH API
 ******************************************************************************/

/*!
 * @addtogroup caam_driver_hash
 * @{
 */
/*!
 * @brief Initialize HASH context
 *
 * This function initializes the HASH.
 * Key shall be supplied if the underlaying algoritm is AES XCBC-MAC or CMAC.
 * Key shall be NULL if the underlaying algoritm is SHA.
 *
 * For XCBC-MAC, the key length must be 16. For CMAC, the key length can be
 * the AES key lengths supported by AES engine. For MDHA the key length argument
 * is ignored.
 *
 * This functions is used to initialize the context for both blocking and non-blocking
 * CAAM_HASH API.
 * For blocking CAAM HASH API, the HASH context contains all information required for context switch,
 * such as running hash or MAC. For non-blocking CAAM HASH API, the HASH context is used
 * to hold SGT. Therefore, the HASH context cannot be shared between blocking and non-blocking HASH API.
 * With one HASH context, either use only blocking HASH API or only non-blocking HASH API.
 *
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request.
 * @param[out] ctx Output hash context
 * @param algo Underlaying algorithm to use for hash computation.
 * @param key Input key (NULL if underlaying algorithm is SHA)
 * @param keySize Size of input key in bytes
 * @return Status of initialization
 */
status_t CAAM_HASH_Init(CAAM_Type *base,
                        caam_handle_t *handle,
                        caam_hash_ctx_t *ctx,
                        caam_hash_algo_t algo,
                        const uint8_t *key,
                        size_t keySize);

/*!
 * @brief Add data to current HASH
 *
 * Add data to current HASH. This can be called repeatedly with an arbitrary amount of data to be
 * hashed. The functions blocks. If it returns kStatus_Success, the running hash or mac
 * has been updated (CAAM has processed the input data), so the memory at input pointer
 * can be released back to system. The context is updated with the running hash or mac
 * and with all necessary information to support possible context switch.
 *
 * @param[in,out] ctx HASH context
 * @param input Input data
 * @param inputSize Size of input data in bytes
 * @return Status of the hash update operation
 */
status_t CAAM_HASH_Update(caam_hash_ctx_t *ctx, const uint8_t *input, size_t inputSize);

/*!
 * @brief Finalize hashing
 *
 * Outputs the final hash (computed by CAAM_HASH_Update()) and erases the context.
 *
 * @param[in,out] ctx Input hash context
 * @param[out] output Output hash data
 * @param[out] outputSize Output parameter storing the size of the output hash in bytes
 * @return Status of the hash finish operation
 */
status_t CAAM_HASH_Finish(caam_hash_ctx_t *ctx, uint8_t *output, size_t *outputSize);

/*!
 * @brief Create HASH on given data
 *
 * Perform the full keyed XCBC-MAC/CMAC or SHA in one function call.
 *
 * Key shall be supplied if the underlaying algoritm is AES XCBC-MAC or CMAC.
 * Key shall be NULL if the underlaying algoritm is SHA.
 *
 * For XCBC-MAC, the key length must be 16. For CMAC, the key length can be
 * the AES key lengths supported by AES engine. For MDHA the key length argument
 * is ignored.
 *
 * The function is blocking.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request.
 * @param algo Underlaying algorithm to use for hash computation.
 * @param input Input data
 * @param inputSize Size of input data in bytes
 * @param key Input key (NULL if underlaying algorithm is SHA)
 * @param keySize Size of input key in bytes
 * @param[out] output Output hash data
 * @param[out] outputSize Output parameter storing the size of the output hash in bytes
 * @return Status of the one call hash operation.
 */
status_t CAAM_HASH(CAAM_Type *base,
                   caam_handle_t *handle,
                   caam_hash_algo_t algo,
                   const uint8_t *input,
                   size_t inputSize,
                   const uint8_t *key,
                   size_t keySize,
                   uint8_t *output,
                   size_t *outputSize);
/*!
 *@}
 */ /* end of caam_driver_hash */

/*!
 * @addtogroup caam_nonblocking_driver_hash
 * @{
 */

/*!
 * @brief Add input address and size to input data table
 *
 * Add data input pointer to a table maintained internally in the context.
 * Each call of this function creates one entry in the table.
 * The entry consists of the input pointer and inputSize.
 * All entries created by one or multiple calls of this function can be processed
 * in one call to CAAM_HASH_FinishNonBlocking() function.
 * Individual entries can point to non-continuous data in the memory.
 * The processing will occur in the order in which the CAAM_HASH_UpdateNonBlocking()
 * have been called.
 *
 * Memory pointers will be later accessed by CAAM (at time of CAAM_HASH_FinishNonBlocking()),
 * so the memory must stay valid
 * until CAAM_HASH_FinishNonBlocking() has been called and CAAM completes the processing.
 *
 * @param[in,out] ctx HASH context
 * @param input Input data
 * @param inputSize Size of input data in bytes
 * @return Status of the hash update operation
 */
status_t CAAM_HASH_UpdateNonBlocking(caam_hash_ctx_t *ctx, const uint8_t *input, size_t inputSize);

/*!
 * @brief Finalize hashing
 *
 * The actual algorithm is computed with all input data, the memory pointers
 * are accessed by CAAM after the function returns.
 * The input data chunks have been specified by prior calls to CAAM_HASH_UpdateNonBlocking().
 * The function schedules the request at CAAM, then returns.
 * After a while, when the CAAM completes processing of the input data chunks,
 * the result is written to the output[] array, outputSize is written and the context
 * is cleared.
 *
 * @param[in,out] ctx Input hash context
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param[out] output Output hash data
 * @param[out] outputSize Output parameter storing the size of the output hash in bytes
 * @return Status of the hash finish operation
 */
status_t CAAM_HASH_FinishNonBlocking(caam_hash_ctx_t *ctx,
                                     caam_desc_hash_t descriptor,
                                     uint8_t *output,
                                     size_t *outputSize);

/*!
 * @brief Create HASH on given data
 *
 * Perform the full keyed XCBC-MAC/CMAC or SHA in one function call.
 *
 * Key shall be supplied if the underlaying algoritm is AES XCBC-MAC or CMAC.
 * Key shall be NULL if the underlaying algoritm is SHA.
 *
 * For XCBC-MAC, the key length must be 16. For CMAC, the key length can be
 * the AES key lengths supported by AES engine. For MDHA the key length argument
 * is ignored.
 *
 * The function is non-blocking. The request is scheduled at CAAM.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param algo Underlaying algorithm to use for hash computation.
 * @param input Input data
 * @param inputSize Size of input data in bytes
 * @param key Input key (NULL if underlaying algorithm is SHA)
 * @param keySize Size of input key in bytes
 * @param[out] output Output hash data
 * @param[out] outputSize Output parameter storing the size of the output hash in bytes
 * @return Status of the one call hash operation.
 */
status_t CAAM_HASH_NonBlocking(CAAM_Type *base,
                               caam_handle_t *handle,
                               caam_desc_hash_t descriptor,
                               caam_hash_algo_t algo,
                               const uint8_t *input,
                               size_t inputSize,
                               const uint8_t *key,
                               size_t keySize,
                               uint8_t *output,
                               size_t *outputSize);

/*!
 *@}
 */ /* end of caam_nonblocking_driver_hash */

/*******************************************************************************
 * HMAC API
 ******************************************************************************/

/*!
 * @addtogroup caam_driver_hmac
 * @{
 */
/*!
 * @brief Initialize HMAC context
 *
 * This function initializes the HMAC.
 *
 * For XCBC-MAC, the key length must be 16. For CMAC, the key length can be
 * the AES key lengths supported by AES engine. For MDHA the key length argument
 * is ignored.
 *
 * This functions is used to initialize the context for both blocking and non-blocking
 * CAAM_HMAC API.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request.
 * @param[out] ctx Output HMAC context
 * @param algo Underlaying algorithm to use for HMAC computation.
 * @param key Input key
 * @param keySize Size of input key in bytes
 * @return Status of initialization
 */
status_t CAAM_HMAC_Init(CAAM_Type *base,
                        caam_handle_t *handle,
                        caam_hash_ctx_t *ctx,
                        caam_hash_algo_t algo,
                        const uint8_t *key,
                        size_t keySize);

/*!
 * @brief Create Message Authentication Code (MAC) on given data
 *
 * Perform the full keyed XCBC-MAC/CMAC, or HMAC-SHA in one function call.
 *
 * Key shall be supplied if the underlaying algoritm is AES XCBC-MAC, CMAC, or SHA HMAC.
 *
 * For XCBC-MAC, the key length must be 16. For CMAC, the key length can be
 * the AES key lengths supported by AES engine. For HMAC, the key can have
 * any size.
 *
 * \param base CAAM peripheral base address
 * \param handle Handle used for this request.
 * \param algo Underlaying algorithm to use for MAC computation.
 * \param input Input data
 * \param inputSize Size of input data in bytes
 * \param key Input key
 * \param keySize Size of input key in bytes
 * \param[out] output Output MAC data
 * \param[out] outputSize Output parameter storing the size of the output MAC in bytes
 * \return Status of the one call hash operation.
 */
status_t CAAM_HMAC(CAAM_Type *base,
                   caam_handle_t *handle,
                   caam_hash_algo_t algo,
                   const uint8_t *input,
                   size_t inputSize,
                   const uint8_t *key,
                   size_t keySize,
                   uint8_t *output,
                   size_t *outputSize);
/*!
 *@}
 */ /* end of caam_driver_hmac */

/*!
 * @addtogroup caam_nonblocking_driver_hmac
 * @{
 */
/*!
 * @brief Create Message Authentication Code (MAC) on given data
 *
 * Perform the full keyed XCBC-MAC/CMAC, or HMAC-SHA in one function call.
 *
 * Key shall be supplied if the underlaying algoritm is AES XCBC-MAC, CMAC, or SHA HMAC.
 *
 * For XCBC-MAC, the key length must be 16. For CMAC, the key length can be
 * the AES key lengths supported by AES engine. For HMAC, the key can have
 * any size, however the function will block if the supplied key is bigger than
 * the block size of the underlying hashing algorithm (e.g. >64 bytes for SHA256).
 *
 * The function is not blocking with the exception of supplying large key sizes.
 * In that case the function will block until the large key is hashed down with the
 * supplied hashing algorithm (as per FIPS 198-1), after which operation is resumed
 * to calling non-blocking HMAC.
 *
 * \param base CAAM peripheral base address
 * \param handle Handle used for this request.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * \param algo Underlaying algorithm to use for MAC computation.
 * \param input Input data
 * \param inputSize Size of input data in bytes
 * \param key Input key
 * \param keySize Size of input key in bytes
 * \param[out] output Output MAC data
 * \param[out] outputSize Output parameter storing the size of the output MAC in bytes
 * \return Status of the one call hash operation.
 */
status_t CAAM_HMAC_NonBlocking(CAAM_Type *base,
                               caam_handle_t *handle,
                               caam_desc_hash_t descriptor,
                               caam_hash_algo_t algo,
                               const uint8_t *input,
                               size_t inputSize,
                               const uint8_t *key,
                               size_t keySize,
                               uint8_t *output,
                               size_t *outputSize);
/*!
 *@}
 */ /* end of caam_nonblocking_driver_hmac */

/*******************************************************************************
 * CRC API
 ******************************************************************************/

/*!
 * @addtogroup caam_driver_crc
 * @{
 */
/*!
 * @brief Initialize CRC context
 *
 * This function initializes the CRC context.
 * polynomial shall be supplied if the underlaying algoritm is kCAAM_CrcCUSTPOLY.
 * polynomial shall be NULL if the underlaying algoritm is kCAAM_CrcIEEE or kCAAM_CrciSCSI.
 *
 * This functions is used to initialize the context for CAAM_CRC API
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request.
 * @param[out] ctx Output crc context
 * @param algo Underlaying algorithm to use for CRC computation
 * @param polynomial CRC polynomial (NULL if underlaying algorithm is kCAAM_CrcIEEE or kCAAM_CrciSCSI)
 * @param polynomialSize Size of polynomial in bytes (0u if underlaying algorithm is kCAAM_CrcIEEE or kCAAM_CrciSCSI)
 * @param mode Specify how CRC engine manipulates its input and output data
 * @return Status of initialization
 */
status_t CAAM_CRC_Init(CAAM_Type *base,
                       caam_handle_t *handle,
                       caam_crc_ctx_t *ctx,
                       caam_crc_algo_t algo,
                       const uint8_t *polynomial,
                       size_t polynomialSize,
                       caam_aai_crc_alg_t mode);

/*!
 * @brief Add data to current CRC
 *
 * Add data to current CRC. This can be called repeatedly. The functions blocks. If it returns kStatus_Success, the
 * running CRC has been updated (CAAM has processed the input data), so the memory at input pointer can be released back
 * to system. The context is updated with the running CRC and with all necessary information to support possible context
 * switch.
 *
 * @param[in,out] ctx CRC context
 * @param input Input data
 * @param inputSize Size of input data in bytes
 * @return Status of the crc update operation
 */
status_t CAAM_CRC_Update(caam_crc_ctx_t *ctx, const uint8_t *input, size_t inputSize);

/*!
 * @brief Finalize CRC
 *
 * Outputs the final CRC (computed by CAAM_CRC_Update()) and erases the context.
 *
 * @param[in,out] ctx Input crc context
 * @param[out] output Output crc data
 * @param[out] outputSize Output parameter storing the size of the output crc in bytes
 * @return Status of the crc finish operation
 */
status_t CAAM_CRC_Finish(caam_crc_ctx_t *ctx, uint8_t *output, size_t *outputSize);

/*!
 * @brief Create CRC on given data
 *
 * Perform CRC in one function call.
 *
 * Polynomial shall be supplied if underlaying algorithm is kCAAM_CrcCUSTPOLY.
 * Polynomial shall be NULL if underlaying algorithm is kCAAM_CrcIEEE or kCAAM_CrciSCSI.
 *
 *
 * The function is blocking.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request.
 * @param algo Underlaying algorithm to use for crc computation.
 * @param mode Specify how CRC engine manipulates its input and output data.
 * @param input Input data
 * @param inputSize Size of input data in bytes
 * @param polynomial CRC polynomial (NULL if underlaying algorithm is kCAAM_CrcIEEE or kCAAM_CrciSCSI)
 * @param polynomialSize Size of input polynomial in bytes (0U if underlaying algorithm is kCAAM_CrcIEEE or
 * kCAAM_CrciSCSI)
 * @param[out] output Output crc data
 * @param[out] outputSize Output parameter storing the size of the output crc in bytes
 * @return Status of the one call crc operation.
 */
status_t CAAM_CRC(CAAM_Type *base,
                  caam_handle_t *handle,
                  caam_crc_algo_t algo,
                  caam_aai_crc_alg_t mode,
                  const uint8_t *input,
                  size_t inputSize,
                  const uint8_t *polynomial,
                  size_t polynomialSize,
                  uint8_t *output,
                  size_t *outputSize);

/*!
 * @brief Create CRC on given data
 *
 * Perform CRC in one function call.
 *
 * Polynomial shall be supplied if underlaying algorithm is kCAAM_CrcCUSTPOLY.
 * Polynomial shall be NULL if underlaying algorithm is kCAAM_CrcIEEE or kCAAM_CrciSCSI.
 *
 * The function is non-blocking. The request is scheduled at CAAM.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request.
 * @param[out] descriptor Memory for the CAAM descriptor.
 * @param algo Underlaying algorithm to use for crc computation.
 * @param mode Specify how CRC engine manipulates its input and output data.
 * @param input Input data
 * @param inputSize Size of input data in bytes
 * @param polynomial CRC polynomial (NULL if underlaying algorithm is kCAAM_CrcIEEE or kCAAM_CrciSCSI)
 * @param polynomialSize Size of input polynomial in bytes (0U if underlaying algorithm is kCAAM_CrcIEEE or
 * kCAAM_CrciSCSI)
 * @param[out] output Output crc data
 * @param[out] outputSize Output parameter storing the size of the output crc in bytes
 * @return Status of the one call crc operation.
 */
status_t CAAM_CRC_NonBlocking(CAAM_Type *base,
                              caam_handle_t *handle,
                              caam_desc_hash_t descriptor,
                              caam_crc_algo_t algo,
                              caam_aai_crc_alg_t mode,
                              const uint8_t *input,
                              size_t inputSize,
                              const uint8_t *polynomial,
                              size_t polynomialSize,
                              uint8_t *output,
                              size_t *outputSize);

/*!
 *@}
 */ /* end of caam_driver_crc */
/*******************************************************************************
 * RNG API
 ******************************************************************************/

/*!
 * @addtogroup caam_driver_rng
 * @{
 */

/*!
 * @brief Initializes user configuration structure to default.
 *
 * This function initializes the configure structure to default value. the default
 * value are:
 * @code
 *     config->autoReseedInterval = 0;
 *     config->personalString = NULL;
 * @endcode
 *
 * @param config   User configuration structure.
 * @return status of the request
 */
status_t CAAM_RNG_GetDefaultConfig(caam_rng_config_t *config);

/*!
 * @brief Instantiate the CAAM RNG state handle
 *
 * This function instantiates CAAM RNG state handle.
 * The function is blocking and returns after CAAM has processed the request.
 *
 * @param base CAAM peripheral base address
 * @param handle CAAM jobRing used for this request
 * @param stateHandle RNG state handle to instantiate
 * @param config Pointer to configuration structure.
 * @return Status of the request
 */
status_t CAAM_RNG_Init(CAAM_Type *base,
                       caam_handle_t *handle,
                       caam_rng_state_handle_t stateHandle,
                       const caam_rng_config_t *config);

/*!
 * @brief Uninstantiate the CAAM RNG state handle
 *
 * This function uninstantiates CAAM RNG state handle.
 * The function is blocking and returns after CAAM has processed the request.
 *
 * @param base CAAM peripheral base address
 * @param handle jobRing used for this request.
 * @param stateHandle RNG state handle to uninstantiate
 * @return Status of the request
 */
status_t CAAM_RNG_Deinit(CAAM_Type *base, caam_handle_t *handle, caam_rng_state_handle_t stateHandle);

/*!
 * @brief Generate Secure Key
 *
 * This function generates random data writes it to Secure Key registers.
 * The function is blocking and returns after CAAM has processed the request.
 * RNG state handle 0 is always used.
 *
 * @param base CAAM peripheral base address
 * @param handle jobRing used for this request
 * @param additionalEntropy NULL or Pointer to optional 256-bit additional entropy.
 * @return Status of the request
 */
status_t CAAM_RNG_GenerateSecureKey(CAAM_Type *base, caam_handle_t *handle, caam_rng_generic256_t additionalEntropy);

/*!
 * @brief Reseed the CAAM RNG state handle
 *
 * This function reseeds the CAAM RNG state handle.
 * For a state handle in nondeterministic mode, the DRNG is seeded with 384 bits of
 * entropy from the TRNG and an optional 256-bit additional input from the descriptor
 * via the Class 1 Context Register.
 *
 * The function is blocking and returns after CAAM has processed the request.
 *
 * @param base CAAM peripheral base address
 * @param handle jobRing used for this request
 * @param stateHandle RNG state handle to reseed
 * @param additionalEntropy NULL or Pointer to optional 256-bit additional entropy.
 * @return Status of the request
 */
status_t CAAM_RNG_Reseed(CAAM_Type *base,
                         caam_handle_t *handle,
                         caam_rng_state_handle_t stateHandle,
                         caam_rng_generic256_t additionalEntropy);

/*!
 * @brief Get random data
 *
 * This function gets random data from CAAM RNG.
 *
 * The function is blocking and returns after CAAM has generated the requested data or an error occurred.
 *
 * @param base CAAM peripheral base address
 * @param handle jobRing used for this request
 * @param stateHandle RNG state handle used to generate random data
 * @param[out] data Pointer address used to store random data
 * @param dataSize Size of the buffer pointed by the data parameter
 * @param dataType Type of random data to be generated
 * @param additionalEntropy NULL or Pointer to optional 256-bit additional entropy.
 * @return Status of the request
 */
status_t CAAM_RNG_GetRandomData(CAAM_Type *base,
                                caam_handle_t *handle,
                                caam_rng_state_handle_t stateHandle,
                                uint8_t *data,
                                size_t dataSize,
                                caam_rng_random_type_t dataType,
                                caam_rng_generic256_t additionalEntropy);

/*!
 *@}
 */ /* end of caam_driver_rng */

/*!
 * @addtogroup caam_nonblocking_driver_rng
 * @{
 */

/*!
 * @brief Request random data
 *
 * This function schedules the request for random data from CAAM RNG.
 * Memory at memory pointers will be accessed by CAAM shortly after this function
 * returns, according to actual CAAM schedule.
 *
 * @param base CAAM peripheral base address
 * @param handle RNG handle used for this request
 * @param stateHandle RNG state handle used to generate random data
 * @param[out] descriptor memory for CAAM commands
 * @param[out] data Pointer address used to store random data
 * @param dataSize Size of the buffer pointed by the data parameter, in bytes.
 * @param dataType Type of random data to be generated.
 * @param additionalEntropy NULL or Pointer to optional 256-bit additional entropy.
 * @return status of the request
 */
status_t CAAM_RNG_GetRandomDataNonBlocking(CAAM_Type *base,
                                           caam_handle_t *handle,
                                           caam_rng_state_handle_t stateHandle,
                                           caam_desc_rng_t descriptor,
                                           void *data,
                                           size_t dataSize,
                                           caam_rng_random_type_t dataType,
                                           caam_rng_generic256_t additionalEntropy);

/*!
 *@}
 */ /* end of caam_nonblocking_driver_rng */

/*******************************************************************************
 * Black key API
 ******************************************************************************/
/*!
 * @addtogroup caam_driver_black
 * @{
 */

/*!
 * @brief Return size of blacken key based on encryption type and data to encrypt size
 *
 * @param fifostType Type of AES-CBC or AEC-CCM to encrypt plaintext
 * @param dataSize Size of data to be encrypted
 *
 * @return size_t Size of blacken key.
 */
size_t CAAM_BLACK_KeyBlackenSize(caam_fifost_type_t fifostType, size_t dataSize);

/*!
 * @brief Construct a black key
 *
 * This function constructs a job descriptor capable of performing
 * a key blackening operation on a plaintext secure memory resident object.
 *
 * @param base CAAM peripheral base address
 * @param handle jobRing used for this request
 * @param data Pointer address uses to pointed the plaintext.
 * @param dataSize Size of the buffer pointed by the data parameter
 * @param fifostType Type of AES-CBC or AEC-CCM to encrypt plaintext
 * @param[out] blackdata Pointer address uses to pointed the black key
 * @return Status of the request
 */
status_t CAAM_BLACK_GetKeyBlacken(CAAM_Type *base,
                                  caam_handle_t *handle,
                                  const uint8_t *data,
                                  size_t dataSize,
                                  caam_fifost_type_t fifostType,
                                  uint8_t *blackdata);

/*!
 *@}
 */ /* end of caam_driver_black */

/*******************************************************************************
 * Key blob API
 ******************************************************************************/
/*!
 * @addtogroup caam_driver_blob
 * @{
 */
/*!
 * @brief Construct a encrypted Red Blob
 *
 * This function constructs a job descriptor capable of performing
 * a encrypted blob operation on a plaintext object.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param keyModifier Address of the random key modifier generated by RNG
 * @param keyModifierSize Size of keyModifier buffer in bytes
 * @param data Data adress
 * @param dataSize Size of the buffer pointed by the data parameter
 * @param[out] blob_data Output blob data adress
 * @return Status of the request
 */
status_t CAAM_RedBlob_Encapsule(CAAM_Type *base,
                                caam_handle_t *handle,
                                const uint8_t *keyModifier,
                                size_t keyModifierSize,
                                const uint8_t *data,
                                size_t dataSize,
                                uint8_t *blob_data);

/*! @brief Decrypt red blob
 *
 * This function constructs a job descriptor capable of performing
 * decrypting red blob .
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param keyModifier Address of the random key modifier generated by RNG
 * @param keyModifierSize Size of keyModifier buffer in bytes
 * @param blob_data Address of blob data
 * @param[out] data Output data adress.
 * @param dataSize Size of the buffer pointed by the data parameter in bytes
 * @return Status of the request
 */
status_t CAAM_RedBlob_Decapsule(CAAM_Type *base,
                                caam_handle_t *handle,
                                const uint8_t *keyModifier,
                                size_t keyModifierSize,
                                const uint8_t *blob_data,
                                uint8_t *data,
                                size_t dataSize);

/*!
 * @brief Construct a encrypted  Black Blob
 *
 * This function constructs a job descriptor capable of performing
 * a encrypted blob operation on a plaintext object.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param keyModifier Address of the random key modifier generated by RNG
 * @param keyModifierSize Size of keyModifier buffer in bytes
 * @param data Data adress
 * @param dataSize Size of the buffer pointed by the data parameter
 * @param[out] blob_data Output blob data adress
 * @param blackKeyType  Type of black key see enum caam_desc_type_t for more info
 * @return Status of the request
 */
status_t CAAM_BlackBlob_Encapsule(CAAM_Type *base,
                                  caam_handle_t *handle,
                                  const uint8_t *keyModifier,
                                  size_t keyModifierSize,
                                  const uint8_t *data,
                                  size_t dataSize,
                                  uint8_t *blob_data,
                                  caam_desc_type_t blackKeyType);

/*! @brief Construct a decrypted black blob
 *
 * This function constructs a job descriptor capable of performing
 * decrypting black blob.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param keyModifier Address of the random key modifier generated by RNG
 * @param keyModifierSize Size of keyModifier buffer in bytes
 * @param blob_data Address of blob data
 * @param[out] data Output data adress.
 * @param dataSize Size of the buffer pointed by the data parameter in bytes
 * @param blackKeyType   Type of black key see enum caam_desc_type_t for more info
 * @return Status of the request
 */
status_t CAAM_BlackBlob_Decapsule(CAAM_Type *base,
                                  caam_handle_t *handle,
                                  const uint8_t *keyModifier,
                                  size_t keyModifierSize,
                                  const uint8_t *blob_data,
                                  uint8_t *data,
                                  size_t dataSize,
                                  caam_desc_type_t blackKeyType);

/*!
 *@}
 */ /* end of caam_driver_blob */

/*******************************************************************************
 * DES API
 ******************************************************************************/

/*!
 * @addtogroup caam_driver_des
 * @{
 */

/*!
 * @brief Encrypts DES using ECB block mode.
 *
 * Encrypts DES using ECB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key Input key to use for encryption
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES_EncryptEcb(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *plaintext,
                             uint8_t *ciphertext,
                             size_t size,
                             const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts DES using ECB block mode.
 *
 * Decrypts DES using ECB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key Input key to use for decryption
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES_DecryptEcb(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *ciphertext,
                             uint8_t *plaintext,
                             size_t size,
                             const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts DES using CBC block mode.
 *
 * Encrypts DES using CBC block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Ouput ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key Input key to use for encryption
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES_EncryptCbc(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *plaintext,
                             uint8_t *ciphertext,
                             size_t size,
                             const uint8_t iv[CAAM_DES_IV_SIZE],
                             const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts DES using CBC block mode.
 *
 * Decrypts DES using CBC block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key Input key to use for decryption
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES_DecryptCbc(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *ciphertext,
                             uint8_t *plaintext,
                             size_t size,
                             const uint8_t iv[CAAM_DES_IV_SIZE],
                             const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts DES using CFB block mode.
 *
 * Encrypts DES using CFB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param size Size of input data in bytes
 * @param iv Input initial block.
 * @param key Input key to use for encryption
 * @param[out] ciphertext Output ciphertext
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES_EncryptCfb(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *plaintext,
                             uint8_t *ciphertext,
                             size_t size,
                             const uint8_t iv[CAAM_DES_IV_SIZE],
                             const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts DES using CFB block mode.
 *
 * Decrypts DES using CFB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input initial block.
 * @param key Input key to use for decryption
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES_DecryptCfb(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *ciphertext,
                             uint8_t *plaintext,
                             size_t size,
                             const uint8_t iv[CAAM_DES_IV_SIZE],
                             const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts DES using OFB block mode.
 *
 * Encrypts DES using OFB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key Input key to use for encryption
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES_EncryptOfb(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *plaintext,
                             uint8_t *ciphertext,
                             size_t size,
                             const uint8_t iv[CAAM_DES_IV_SIZE],
                             const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts DES using OFB block mode.
 *
 * Decrypts DES using OFB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key Input key to use for decryption
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES_DecryptOfb(CAAM_Type *base,
                             caam_handle_t *handle,
                             const uint8_t *ciphertext,
                             uint8_t *plaintext,
                             size_t size,
                             const uint8_t iv[CAAM_DES_IV_SIZE],
                             const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using ECB block mode with two keys.
 *
 * Encrypts triple DES using ECB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES2_EncryptEcb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *plaintext,
                              uint8_t *ciphertext,
                              size_t size,
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using ECB block mode with two keys.
 *
 * Decrypts triple DES using ECB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES2_DecryptEcb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *ciphertext,
                              uint8_t *plaintext,
                              size_t size,
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using CBC block mode with two keys.
 *
 * Encrypts triple DES using CBC block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES2_EncryptCbc(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *plaintext,
                              uint8_t *ciphertext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using CBC block mode with two keys.
 *
 * Decrypts triple DES using CBC block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES2_DecryptCbc(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *ciphertext,
                              uint8_t *plaintext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using CFB block mode with two keys.
 *
 * Encrypts triple DES using CFB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input initial block.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES2_EncryptCfb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *plaintext,
                              uint8_t *ciphertext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using CFB block mode with two keys.
 *
 * Decrypts triple DES using CFB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input initial block.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES2_DecryptCfb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *ciphertext,
                              uint8_t *plaintext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using OFB block mode with two keys.
 *
 * Encrypts triple DES using OFB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES2_EncryptOfb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *plaintext,
                              uint8_t *ciphertext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using OFB block mode with two keys.
 *
 * Decrypts triple DES using OFB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES2_DecryptOfb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *ciphertext,
                              uint8_t *plaintext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using ECB block mode with three keys.
 *
 * Encrypts triple DES using ECB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES3_EncryptEcb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *plaintext,
                              uint8_t *ciphertext,
                              size_t size,
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE],
                              const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using ECB block mode with three keys.
 *
 * Decrypts triple DES using ECB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES3_DecryptEcb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *ciphertext,
                              uint8_t *plaintext,
                              size_t size,
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE],
                              const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using CBC block mode with three keys.
 *
 * Encrypts triple DES using CBC block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES3_EncryptCbc(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *plaintext,
                              uint8_t *ciphertext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE],
                              const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using CBC block mode with three keys.
 *
 * Decrypts triple DES using CBC block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES3_DecryptCbc(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *ciphertext,
                              uint8_t *plaintext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE],
                              const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using CFB block mode with three keys.
 *
 * Encrypts triple DES using CFB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and ouput data in bytes
 * @param iv Input initial block.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES3_EncryptCfb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *plaintext,
                              uint8_t *ciphertext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE],
                              const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using CFB block mode with three keys.
 *
 * Decrypts triple DES using CFB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input data in bytes
 * @param iv Input initial block.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES3_DecryptCfb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *ciphertext,
                              uint8_t *plaintext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE],
                              const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using OFB block mode with three keys.
 *
 * Encrypts triple DES using OFB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES3_EncryptOfb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *plaintext,
                              uint8_t *ciphertext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE],
                              const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using OFB block mode with three keys.
 *
 * Decrypts triple DES using OFB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from encrypt/decrypt operation
 */
status_t CAAM_DES3_DecryptOfb(CAAM_Type *base,
                              caam_handle_t *handle,
                              const uint8_t *ciphertext,
                              uint8_t *plaintext,
                              size_t size,
                              const uint8_t iv[CAAM_DES_IV_SIZE],
                              const uint8_t key1[CAAM_DES_KEY_SIZE],
                              const uint8_t key2[CAAM_DES_KEY_SIZE],
                              const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 *@}
 */ /* end of caam_driver_des */

/*!
 * @addtogroup caam_nonblocking_driver_des
 * @{
 */

/*!
 * @brief Encrypts DES using ECB block mode.
 *
 * Encrypts DES using ECB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key Input key to use for encryption
 * @return Status from descriptor push
 */
status_t CAAM_DES_EncryptEcbNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_cipher_des_t descriptor,
                                        const uint8_t *plaintext,
                                        uint8_t *ciphertext,
                                        size_t size,
                                        const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts DES using ECB block mode.
 *
 * Decrypts DES using ECB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key Input key to use for decryption
 * @return Status from descriptor push
 */
status_t CAAM_DES_DecryptEcbNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_cipher_des_t descriptor,
                                        const uint8_t *ciphertext,
                                        uint8_t *plaintext,
                                        size_t size,
                                        const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts DES using CBC block mode.
 *
 * Encrypts DES using CBC block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Ouput ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key Input key to use for encryption
 * @return Status from descriptor push
 */
status_t CAAM_DES_EncryptCbcNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_cipher_des_t descriptor,
                                        const uint8_t *plaintext,
                                        uint8_t *ciphertext,
                                        size_t size,
                                        const uint8_t iv[CAAM_DES_IV_SIZE],
                                        const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts DES using CBC block mode.
 *
 * Decrypts DES using CBC block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key Input key to use for decryption
 * @return Status from descriptor push
 */
status_t CAAM_DES_DecryptCbcNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_cipher_des_t descriptor,
                                        const uint8_t *ciphertext,
                                        uint8_t *plaintext,
                                        size_t size,
                                        const uint8_t iv[CAAM_DES_IV_SIZE],
                                        const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts DES using CFB block mode.
 *
 * Encrypts DES using CFB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param size Size of input data in bytes
 * @param iv Input initial block.
 * @param key Input key to use for encryption
 * @param[out] ciphertext Output ciphertext
 * @return Status from descriptor push
 */
status_t CAAM_DES_EncryptCfbNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_cipher_des_t descriptor,
                                        const uint8_t *plaintext,
                                        uint8_t *ciphertext,
                                        size_t size,
                                        const uint8_t iv[CAAM_DES_IV_SIZE],
                                        const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts DES using CFB block mode.
 *
 * Decrypts DES using CFB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input initial block.
 * @param key Input key to use for decryption
 * @return Status from descriptor push
 */
status_t CAAM_DES_DecryptCfbNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_cipher_des_t descriptor,
                                        const uint8_t *ciphertext,
                                        uint8_t *plaintext,
                                        size_t size,
                                        const uint8_t iv[CAAM_DES_IV_SIZE],
                                        const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts DES using OFB block mode.
 *
 * Encrypts DES using OFB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key Input key to use for encryption
 * @return Status from descriptor push
 */
status_t CAAM_DES_EncryptOfbNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_cipher_des_t descriptor,
                                        const uint8_t *plaintext,
                                        uint8_t *ciphertext,
                                        size_t size,
                                        const uint8_t iv[CAAM_DES_IV_SIZE],
                                        const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts DES using OFB block mode.
 *
 * Decrypts DES using OFB block mode.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key Input key to use for decryption
 * @return Status from descriptor push
 */
status_t CAAM_DES_DecryptOfbNonBlocking(CAAM_Type *base,
                                        caam_handle_t *handle,
                                        caam_desc_cipher_des_t descriptor,
                                        const uint8_t *ciphertext,
                                        uint8_t *plaintext,
                                        size_t size,
                                        const uint8_t iv[CAAM_DES_IV_SIZE],
                                        const uint8_t key[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using ECB block mode with two keys.
 *
 * Encrypts triple DES using ECB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES2_EncryptEcbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *plaintext,
                                         uint8_t *ciphertext,
                                         size_t size,
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using ECB block mode with two keys.
 *
 * Decrypts triple DES using ECB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES2_DecryptEcbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *ciphertext,
                                         uint8_t *plaintext,
                                         size_t size,
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using CBC block mode with two keys.
 *
 * Encrypts triple DES using CBC block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES2_EncryptCbcNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *plaintext,
                                         uint8_t *ciphertext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using CBC block mode with two keys.
 *
 * Decrypts triple DES using CBC block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES2_DecryptCbcNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *ciphertext,
                                         uint8_t *plaintext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using CFB block mode with two keys.
 *
 * Encrypts triple DES using CFB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input initial block.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES2_EncryptCfbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *plaintext,
                                         uint8_t *ciphertext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using CFB block mode with two keys.
 *
 * Decrypts triple DES using CFB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input initial block.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES2_DecryptCfbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *ciphertext,
                                         uint8_t *plaintext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using OFB block mode with two keys.
 *
 * Encrypts triple DES using OFB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES2_EncryptOfbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *plaintext,
                                         uint8_t *ciphertext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using OFB block mode with two keys.
 *
 * Decrypts triple DES using OFB block mode with two keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES2_DecryptOfbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *ciphertext,
                                         uint8_t *plaintext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using ECB block mode with three keys.
 *
 * Encrypts triple DES using ECB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES3_EncryptEcbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *plaintext,
                                         uint8_t *ciphertext,
                                         size_t size,
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE],
                                         const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using ECB block mode with three keys.
 *
 * Decrypts triple DES using ECB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes. Must be multiple of 8 bytes.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES3_DecryptEcbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *ciphertext,
                                         uint8_t *plaintext,
                                         size_t size,
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE],
                                         const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using CBC block mode with three keys.
 *
 * Encrypts triple DES using CBC block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES3_EncryptCbcNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *plaintext,
                                         uint8_t *ciphertext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE],
                                         const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using CBC block mode with three keys.
 *
 * Decrypts triple DES using CBC block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input initial vector to combine with the first plaintext block.
 *           The iv does not need to be secret, but it must be unpredictable.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES3_DecryptCbcNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *ciphertext,
                                         uint8_t *plaintext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE],
                                         const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using CFB block mode with three keys.
 *
 * Encrypts triple DES using CFB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and ouput data in bytes
 * @param iv Input initial block.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES3_EncryptCfbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *plaintext,
                                         uint8_t *ciphertext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE],
                                         const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using CFB block mode with three keys.
 *
 * Decrypts triple DES using CFB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input data in bytes
 * @param iv Input initial block.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES3_DecryptCfbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *ciphertext,
                                         uint8_t *plaintext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE],
                                         const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Encrypts triple DES using OFB block mode with three keys.
 *
 * Encrypts triple DES using OFB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param plaintext Input plaintext to encrypt
 * @param[out] ciphertext Output ciphertext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES3_EncryptOfbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *plaintext,
                                         uint8_t *ciphertext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE],
                                         const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 * @brief Decrypts triple DES using OFB block mode with three keys.
 *
 * Decrypts triple DES using OFB block mode with three keys.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param[out] descriptor memory for CAAM commands
 * @param ciphertext Input ciphertext to decrypt
 * @param[out] plaintext Output plaintext
 * @param size Size of input and output data in bytes
 * @param iv Input unique input vector. The OFB mode requires that the IV be unique
 *           for each execution of the mode under the given key.
 * @param key1 First input key for key bundle
 * @param key2 Second input key for key bundle
 * @param key3 Third input key for key bundle
 * @return Status from descriptor push
 */
status_t CAAM_DES3_DecryptOfbNonBlocking(CAAM_Type *base,
                                         caam_handle_t *handle,
                                         caam_desc_cipher_des_t descriptor,
                                         const uint8_t *ciphertext,
                                         uint8_t *plaintext,
                                         size_t size,
                                         const uint8_t iv[CAAM_DES_IV_SIZE],
                                         const uint8_t key1[CAAM_DES_KEY_SIZE],
                                         const uint8_t key2[CAAM_DES_KEY_SIZE],
                                         const uint8_t key3[CAAM_DES_KEY_SIZE]);

/*!
 *@}
 */ /* end of caam_nonblocking_driver_des */

/*!
 * @addtogroup caam_driver_pkha
 * @{
 */

int CAAM_PKHA_CompareBigNum(const uint8_t *a, size_t sizeA, const uint8_t *b, size_t sizeB);

/*!
 * @brief Converts from integer to Montgomery format.
 *
 * This function computes R2 mod N and optionally converts A or B into Montgomery format of A or B.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param N modulus
 * @param sizeN size of N in bytes
 * @param[in,out] A The first input in non-Montgomery format. Output Montgomery format of the first input.
 * @param[in,out] sizeA pointer to size variable. On input it holds size of input A in bytes. On output it holds size of
 *                Montgomery format of A in bytes.
 * @param[in,out] B Second input in non-Montgomery format. Output Montgomery format of the second input.
 * @param[in,out] sizeB pointer to size variable. On input it holds size of input B in bytes. On output it holds size of
 *                Montgomery format of B in bytes.
 * @param[out] R2 Output Montgomery factor R2 mod N.
 * @param[out] sizeR2 pointer to size variable. On output it holds size of Montgomery factor R2 mod N in bytes.
 * @param equalTime Run the function time equalized or no timing equalization.
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @return Operation status.
 */
status_t CAAM_PKHA_NormalToMontgomery(CAAM_Type *base,
                                      caam_handle_t *handle,
                                      const uint8_t *N,
                                      size_t sizeN,
                                      uint8_t *A,
                                      size_t *sizeA,
                                      uint8_t *B,
                                      size_t *sizeB,
                                      uint8_t *R2,
                                      size_t *sizeR2,
                                      caam_pkha_timing_t equalTime,
                                      caam_pkha_f2m_t arithType);

/*!
 * @brief Converts from Montgomery format to int.
 *
 * This function converts Montgomery format of A or B into int A or B.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param N modulus.
 * @param sizeN size of N modulus in bytes.
 * @param[in,out] A Input first number in Montgomery format. Output is non-Montgomery format.
 * @param[in,out] sizeA pointer to size variable. On input it holds size of the input A in bytes. On output it holds
 * size of non-Montgomery A in bytes.
 * @param[in,out] B Input first number in Montgomery format. Output is non-Montgomery format.
 * @param[in,out] sizeB pointer to size variable. On input it holds size of the input B in bytes. On output it holds
 * size of non-Montgomery B in bytes.
 * @param equalTime Run the function time equalized or no timing equalization.
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @return Operation status.
 */
status_t CAAM_PKHA_MontgomeryToNormal(CAAM_Type *base,
                                      caam_handle_t *handle,
                                      const uint8_t *N,
                                      size_t sizeN,
                                      uint8_t *A,
                                      size_t *sizeA,
                                      uint8_t *B,
                                      size_t *sizeB,
                                      caam_pkha_timing_t equalTime,
                                      caam_pkha_f2m_t arithType);

/*!
 * @brief Performs modular addition - (A + B) mod N.
 *
 * This function performs modular addition of (A + B) mod N, with either
 * integer or binary polynomial (F2m) inputs.  In the F2m form, this function is
 * equivalent to a bitwise XOR and it is functionally the same as subtraction.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A first addend (integer or binary polynomial)
 * @param sizeA Size of A in bytes
 * @param B second addend (integer or binary polynomial)
 * @param sizeB Size of B in bytes
 * @param N modulus.
 * @param sizeN Size of N in bytes.
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @return Operation status.
 */
status_t CAAM_PKHA_ModAdd(CAAM_Type *base,
                          caam_handle_t *handle,
                          const uint8_t *A,
                          size_t sizeA,
                          const uint8_t *B,
                          size_t sizeB,
                          const uint8_t *N,
                          size_t sizeN,
                          uint8_t *result,
                          size_t *resultSize,
                          caam_pkha_f2m_t arithType);

/*!
 * @brief Performs modular subtraction - (A - B) mod N.
 *
 * This function performs modular subtraction of (A - B) mod N with
 * integer inputs.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A first addend (integer or binary polynomial)
 * @param sizeA Size of A in bytes
 * @param B second addend (integer or binary polynomial)
 * @param sizeB Size of B in bytes
 * @param N modulus
 * @param sizeN Size of N in bytes
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @return Operation status.
 */
status_t CAAM_PKHA_ModSub1(CAAM_Type *base,
                           caam_handle_t *handle,
                           const uint8_t *A,
                           size_t sizeA,
                           const uint8_t *B,
                           size_t sizeB,
                           const uint8_t *N,
                           size_t sizeN,
                           uint8_t *result,
                           size_t *resultSize);

/*!
 * @brief Performs modular subtraction - (B - A) mod N.
 *
 * This function performs modular subtraction of (B - A) mod N,
 * with integer inputs.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A first addend (integer or binary polynomial)
 * @param sizeA Size of A in bytes
 * @param B second addend (integer or binary polynomial)
 * @param sizeB Size of B in bytes
 * @param N modulus
 * @param sizeN Size of N in bytes
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @return Operation status.
 */
status_t CAAM_PKHA_ModSub2(CAAM_Type *base,
                           caam_handle_t *handle,
                           const uint8_t *A,
                           size_t sizeA,
                           const uint8_t *B,
                           size_t sizeB,
                           const uint8_t *N,
                           size_t sizeN,
                           uint8_t *result,
                           size_t *resultSize);

/*!
 * @brief Performs modular multiplication - (A x B) mod N.
 *
 * This function performs modular multiplication with either integer or
 * binary polynomial (F2m) inputs.  It can optionally specify whether inputs
 * and/or outputs will be in Montgomery form or not.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A first addend (integer or binary polynomial)
 * @param sizeA Size of A in bytes
 * @param B second addend (integer or binary polynomial)
 * @param sizeB Size of B in bytes
 * @param N modulus.
 * @param sizeN Size of N in bytes
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @param montIn Format of inputs
 * @param montOut Format of output
 * @param equalTime Run the function time equalized or no timing equalization. This argument is ignored for F2m modular
 * multiplication.
 * @return Operation status.
 */
status_t CAAM_PKHA_ModMul(CAAM_Type *base,
                          caam_handle_t *handle,
                          const uint8_t *A,
                          size_t sizeA,
                          const uint8_t *B,
                          size_t sizeB,
                          const uint8_t *N,
                          size_t sizeN,
                          uint8_t *result,
                          size_t *resultSize,
                          caam_pkha_f2m_t arithType,
                          caam_pkha_montgomery_form_t montIn,
                          caam_pkha_montgomery_form_t montOut,
                          caam_pkha_timing_t equalTime);

/*!
 * @brief Performs modular exponentiation - (A^E) mod N.
 *
 * This function performs modular exponentiation with either integer or
 * binary polynomial (F2m) inputs.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A first addend (integer or binary polynomial)
 * @param sizeA Size of A in bytes
 * @param N modulus
 * @param sizeN Size of N in bytes
 * @param E exponent
 * @param sizeE Size of E in bytes
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @param montIn Format of A input (normal or Montgomery)
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @param equalTime Run the function time equalized or no timing equalization.
 * @return Operation status.
 */
status_t CAAM_PKHA_ModExp(CAAM_Type *base,
                          caam_handle_t *handle,
                          const uint8_t *A,
                          size_t sizeA,
                          const uint8_t *N,
                          size_t sizeN,
                          const uint8_t *E,
                          size_t sizeE,
                          uint8_t *result,
                          size_t *resultSize,
                          caam_pkha_f2m_t arithType,
                          caam_pkha_montgomery_form_t montIn,
                          caam_pkha_timing_t equalTime);

/*!
 * @brief Performs modular reduction - (A) mod N.
 *
 * This function performs modular reduction with either integer or
 * binary polynomial (F2m) inputs.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A first addend (integer or binary polynomial)
 * @param sizeA Size of A in bytes
 * @param N modulus
 * @param sizeN Size of N in bytes
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @return Operation status.
 */
status_t CAAM_PKHA_ModRed(CAAM_Type *base,
                          caam_handle_t *handle,
                          const uint8_t *A,
                          size_t sizeA,
                          const uint8_t *N,
                          size_t sizeN,
                          uint8_t *result,
                          size_t *resultSize,
                          caam_pkha_f2m_t arithType);

/*!
 * @brief Performs modular inversion - (A^-1) mod N.
 *
 * This function performs modular inversion with either integer or
 * binary polynomial (F2m) inputs.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A first addend (integer or binary polynomial)
 * @param sizeA Size of A in bytes
 * @param N modulus
 * @param sizeN Size of N in bytes
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @return Operation status.
 */
status_t CAAM_PKHA_ModInv(CAAM_Type *base,
                          caam_handle_t *handle,
                          const uint8_t *A,
                          size_t sizeA,
                          const uint8_t *N,
                          size_t sizeN,
                          uint8_t *result,
                          size_t *resultSize,
                          caam_pkha_f2m_t arithType);

/*!
 * @brief Computes integer Montgomery factor R^2 mod N.
 *
 * This function computes a constant to assist in converting operands
 * into the Montgomery residue system representation.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param N modulus
 * @param sizeN Size of N in bytes
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @return Operation status.
 */
status_t CAAM_PKHA_ModR2(CAAM_Type *base,
                         caam_handle_t *handle,
                         const uint8_t *N,
                         size_t sizeN,
                         uint8_t *result,
                         size_t *resultSize,
                         caam_pkha_f2m_t arithType);

/*!
 * @brief Calculates the greatest common divisor - GCD (A, N).
 *
 * This function calculates the greatest common divisor of two inputs with
 * either integer or binary polynomial (F2m) inputs.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A first value (must be smaller than or equal to N)
 * @param sizeA Size of A in bytes
 * @param N second value (must be non-zero)
 * @param sizeN Size of N in bytes
 * @param[out] result Output array to store result of operation
 * @param[out] resultSize Output size of operation in bytes
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @return Operation status.
 */
status_t CAAM_PKHA_ModGcd(CAAM_Type *base,
                          caam_handle_t *handle,
                          const uint8_t *A,
                          size_t sizeA,
                          const uint8_t *N,
                          size_t sizeN,
                          uint8_t *result,
                          size_t *resultSize,
                          caam_pkha_f2m_t arithType);

/*!
 * @brief Executes Miller-Rabin primality test.
 *
 * This function calculates whether or not a candidate prime number is likely
 * to be a prime.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A initial random seed
 * @param sizeA Size of A in bytes
 * @param B number of trial runs
 * @param sizeB Size of B in bytes
 * @param N candidate prime integer
 * @param sizeN Size of N in bytes
 * @param[out] res True if the value is likely prime or false otherwise
 * @return Operation status.
 */
status_t CAAM_PKHA_PrimalityTest(CAAM_Type *base,
                                 caam_handle_t *handle,
                                 const uint8_t *A,
                                 size_t sizeA,
                                 const uint8_t *B,
                                 size_t sizeB,
                                 const uint8_t *N,
                                 size_t sizeN,
                                 bool *res);

/*!
 * @brief Adds elliptic curve points - A + B.
 *
 * This function performs ECC point addition over a prime field (Fp) or binary field (F2m) using
 * affine coordinates.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A Left-hand point
 * @param B Right-hand point
 * @param N Prime modulus of the field
 * @param R2modN NULL (the function computes R2modN internally) or pointer to pre-computed R2modN (obtained from
 *               CAAM_PKHA_ModR2() function).
 * @param aCurveParam A parameter from curve equation
 * @param bCurveParam B parameter from curve equation (constant)
 * @param size Size in bytes of curve points and parameters
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @param[out] result Result point
 * @return Operation status.
 */
status_t CAAM_PKHA_ECC_PointAdd(CAAM_Type *base,
                                caam_handle_t *handle,
                                const caam_pkha_ecc_point_t *A,
                                const caam_pkha_ecc_point_t *B,
                                const uint8_t *N,
                                const uint8_t *R2modN,
                                const uint8_t *aCurveParam,
                                const uint8_t *bCurveParam,
                                size_t size,
                                caam_pkha_f2m_t arithType,
                                caam_pkha_ecc_point_t *result);

/*!
 * @brief Doubles elliptic curve points - B + B.
 *
 * This function performs ECC point doubling over a prime field (Fp) or binary field (F2m) using
 * affine coordinates.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param B Point to double
 * @param N Prime modulus of the field
 * @param aCurveParam A parameter from curve equation
 * @param bCurveParam B parameter from curve equation (constant)
 * @param size Size in bytes of curve points and parameters
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @param[out] result Result point
 * @return Operation status.
 */
status_t CAAM_PKHA_ECC_PointDouble(CAAM_Type *base,
                                   caam_handle_t *handle,
                                   const caam_pkha_ecc_point_t *B,
                                   const uint8_t *N,
                                   const uint8_t *aCurveParam,
                                   const uint8_t *bCurveParam,
                                   size_t size,
                                   caam_pkha_f2m_t arithType,
                                   caam_pkha_ecc_point_t *result);

/*!
 * @brief Multiplies an elliptic curve point by a scalar - E x (A0, A1).
 *
 * This function performs ECC point multiplication to multiply an ECC point by
 * a scalar integer multiplier over a prime field (Fp) or a binary field (F2m).
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param A Point as multiplicand
 * @param E Scalar multiple
 * @param sizeE The size of E, in bytes
 * @param N Modulus, a prime number for the Fp field or Irreducible polynomial for F2m field.
 * @param R2modN NULL (the function computes R2modN internally) or pointer to pre-computed R2modN (obtained from
 *        CAAM_PKHA_ModR2() function).
 * @param aCurveParam A parameter from curve equation
 * @param bCurveParam B parameter from curve equation (C parameter for operation over F2m).
 * @param size Size in bytes of curve points and parameters
 * @param equalTime Run the function time equalized or no timing equalization.
 * @param arithType Type of arithmetic to perform (integer or F2m)
 * @param[out] result Result point
 * @return Operation status.
 */
status_t CAAM_PKHA_ECC_PointMul(CAAM_Type *base,
                                caam_handle_t *handle,
                                const caam_pkha_ecc_point_t *A,
                                const uint8_t *E,
                                size_t sizeE,
                                const uint8_t *N,
                                const uint8_t *R2modN,
                                const uint8_t *aCurveParam,
                                const uint8_t *bCurveParam,
                                size_t size,
                                caam_pkha_timing_t equalTime,
                                caam_pkha_f2m_t arithType,
                                caam_pkha_ecc_point_t *result);

/*!
 *@}
 */ /* end of caam_driver_pkha */

/*******************************************************************************
 * ECC
 ******************************************************************************/

/*!
 * @addtogroup caam_driver_ecc
 * @{
 */

/*!
 * @brief Return size of private key based on encryption type and ecliptic curve domain
 *
 * @param encryptKeyType Type of key encryption.
 * @param ecdsel Elliptic curve domain selection
 *
 * @return size_t Size of private key.
 */
size_t CAAM_ECC_PrivateKeySize(caam_ecc_encryption_type_t encryptKeyType, caam_ecc_ecdsel_t ecdsel);

/*!
 * @brief Generates public and private key for ECC.
 *
 * The buffer size of privKey can be determined using CAAM_ECC_PRIVATE_KEY_LENGTH.
 * The buffer size of pubKey can be determined using CAAM_ECC_PUBLIC_KEY_LENGTH.
 * For encrypted privKey, the buffer size can be determined using CAAM_BLACKEN_ECB_SIZE
 * or CAAM_BLACKEN_CCM_SIZE macros.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param ecdsel Elliptic curve domain selection
 * @param encryptKeyType Type of key encryption
 * @param[out] privKey Private key
 * @param[out] pubKey Public key
 * @return Operation status.
 */
status_t CAAM_ECC_KeyPair(CAAM_Type *base,
                          caam_handle_t *handle,
                          caam_ecc_ecdsel_t ecdsel,
                          caam_ecc_encryption_type_t encryptKeyType,
                          uint8_t *privKey,
                          uint8_t *pubKey);

/*!
 * @brief Generates signature using ECC.
 *
 * The buffer size of signFirst can be determined using CAAM_ECC_PRIVATE_KEY_LENGTH.
 * ! The buffer size of signSecond can be determined using CAAM_ECC_SECOND_SIGN_BUFFER_SIZE.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param privKey Private key
 * @param data Hashed data
 * @param dataSize Hashed data length
 * @param ecdsel Elliptic curve domain selection
 * @param encryptKeyType Type of key encryption
 * @param[out] signFirst First part of the signature
 * @param[out] signSecond Second part of the signature
 * @return Operation status.
 */
status_t CAAM_ECC_Sign(CAAM_Type *base,
                       caam_handle_t *handle,
                       const uint8_t *privKey,
                       const uint8_t *data,
                       size_t dataSize,
                       caam_ecc_ecdsel_t ecdsel,
                       caam_ecc_encryption_type_t encryptKeyType,
                       uint8_t *signFirst,
                       uint8_t *signSecond);

/*!
 * @brief Verify ECC signature using public key
 *
 * The buffer size of tmp can be determined using CAAM_ECC_PUBLIC_KEY_LENGTH.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param pubKey Public key
 * @param data Hashed data
 * @param dataSize Hashed data length
 * @param signFirst First part of the signature
 * @param signSecond Second part of the signature
 * @param ecdsel Elliptic curve domain selection
 * @param[in,out] tmp Temporary storage for intermediate results
 * @return Operation status.
 */
status_t CAAM_ECC_VerifyPublicKey(CAAM_Type *base,
                                  caam_handle_t *handle,
                                  const uint8_t *pubKey,
                                  const uint8_t *data,
                                  size_t dataSize,
                                  const uint8_t *signFirst,
                                  const uint8_t *signSecond,
                                  caam_ecc_ecdsel_t ecdsel,
                                  uint8_t *tmp);

/*!
 * @brief Verify ECC signature using private key
 *
 * Faster that verifying using public key.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param privKey Private key
 * @param data Hashed data
 * @param dataSize Hashed data length
 * @param signFirst First part of the signature
 * @param signSecond Second part of the signature
 * @param ecdsel Elliptic curve domain selection
 * @param encryptKeyType Type of key encryption
 * @return Operation status.
 */
status_t CAAM_ECC_VerifyPrivateKey(CAAM_Type *base,
                                   caam_handle_t *handle,
                                   const uint8_t *privKey,
                                   const uint8_t *data,
                                   size_t dataSize,
                                   const uint8_t *signFirst,
                                   const uint8_t *signSecond,
                                   caam_ecc_ecdsel_t ecdsel,
                                   caam_ecc_encryption_type_t encryptKeyType);
/*!
 *@}
 */ /* end of caam_driver_ecc */

/*******************************************************************************
 * RSA
 ******************************************************************************/

/*!
 * @addtogroup caam_driver_rsa
 * @{
 */

/*!
 * @brief Return size for private key buffer based on encryption type and ecliptic curve domain
 *
 * @param prvKeyType Type of private key
 * @param privExponentSize Expected length of private exponent without encryption padding.
 *
 * @return size_t Size for private key buffer.
 */
size_t CAAM_RSA_PrivateExponentSize(caam_rsa_key_type_t prvKeyType, uint32_t privExponentSize);

/*!
 * @brief Generates RSA key.
 *
 * Generates modulus N and private exponent D give prime numbers P and Q and public exponent E.
 * Public key is {E,N}. Private key is {D,N}.
 *
 * ! privExponentSize value may differ for different P abd Q with same bit length.
 * For encrypted privExponent, the buffer size can be determined using CAAM_BLACKEN_ECB_SIZE
 * or CAAM_BLACKEN_CCM_SIZE macros.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param primeP Prime number P
 * @param primeQ Prime number Q
 * @param primesSize Byte length of primeP or primeQ (primeP and primeQ must have the same byte length)
 * @param pubExponent Public exponent E
 * @param pubExponentSize  Byte length of pubExponent
 * @param prvKeyType Type of private key
 * @param[out] modulus Buffer for calculated modulus N
 * @param modulusSize Byte length of modulus buffer
 * @param[out] privExponent Buffer for calculated private exponent D
 * @param[out] privExponentSize Byte length of calculated private exponent.
 * @return Operation status.
 */
status_t CAAM_RSA_KeyPair(CAAM_Type *base,
                          caam_handle_t *handle,
                          const uint8_t *primeP,
                          const uint8_t *primeQ,
                          uint32_t primesSize,
                          const uint8_t *pubExponent,
                          uint32_t pubExponentSize,
                          caam_rsa_key_type_t prvKeyType,
                          uint8_t *modulus,
                          uint32_t modulusSize,
                          uint8_t *privExponent,
                          size_t *privExponentSize);

/*!
 * @brief Performs the RSA public key primitive.
 *
 * Performs the RSA public key primitive which can be used when encrypting a secret or verifying a signature.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param plainText Input data
 * @param plainTextize Byte length of the input data
 * @param modulus Modulus N
 * @param modulusSize Byte length of modulus
 * @param pubExponent Public exponent E
 * @param pubExponentSize  Byte length of pubExponent
 * @param dataOutType Type of encryption of output data
 * @param[out] cipherText Buffer for RSA encrypted data
 * @return Operation status
 */
status_t CAAM_RSA_Encrypt(CAAM_Type *base,
                          caam_handle_t *handle,
                          const uint8_t *plainText,
                          uint32_t plainTextSize,
                          const uint8_t *modulus,
                          uint32_t modulusSize,
                          const uint8_t *pubExponent,
                          uint32_t pubExponentSize,
                          caam_rsa_encryption_type_t dataOutType,
                          caam_rsa_format_type_t format,
                          uint8_t *cipherText);

/*!
 * @brief Performs the RSA private key primitive.
 *
 * Performs the RSA private key primitive which can be used when decrypting a secret or creating a siganture.
 *
 * @param base CAAM peripheral base address
 * @param handle Handle used for this request. Specifies jobRing.
 * @param cipherText Input data
 * @param modulus Moulus N
 * @param modulusSize Byte length of modulus
 * @param privExponent Private exponent D
 * @param privExponentSize Byte length of privExponent
 * @param prvKeyType Type of private key encryption
 * @param dataOutType Type of encryption of output data
 * @param[out] plainText Buffer for RSA encrypted data
 * @param[out] rsaDecSize Returned output size
 * @return Operation status
 */
status_t CAAM_RSA_Decrypt(CAAM_Type *base,
                          caam_handle_t *handle,
                          const uint8_t *cipherText,
                          const uint8_t *modulus,
                          uint32_t modulusSize,
                          const uint8_t *privExponent,
                          uint32_t privExponentSize,
                          caam_rsa_encryption_type_t prvKeyType,
                          caam_rsa_encryption_type_t dataOutType,
                          caam_rsa_format_type_t format,
                          uint8_t *plainText,
                          size_t *rsaDecSize);

/*!
 *@}
 */ /* end of caam_driver_rsa */

#if defined(__cplusplus)
}
#endif

#endif /* FSL_CAAM_H_ */