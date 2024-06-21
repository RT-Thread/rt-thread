/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef FSL_NBOOT_H_
#define FSL_NBOOT_H_

#include "fsl_common.h"

/*!
 * @addtogroup nboot
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/
/** @def NXPCLHASH_WA_SIZE_MAX
 *  @brief Define the max workarea size required for this component
 */
#define NXPCLHASH_WA_SIZE_MAX             (128U + 64U)
#define NBOOT_ROOT_CERT_COUNT             (4U)
#define NXPCLCSS_HASH_RTF_OUTPUT_SIZE_HAL ((size_t)32U) ///< Size of RTF appendix to hash output buffer, in bytes

#define NBOOT_KEYINFO_WORDLEN (23U)
#define NBOOT_CONTEXT_BYTELEN (192U + NXPCLHASH_WA_SIZE_MAX)
#define NBOOT_CONTEXT_WORDLEN (NBOOT_CONTEXT_BYTELEN / sizeof(uint32_t))
typedef int romapi_status_t;

/*!
 * @brief NBOOT type for the root key usage
 *
 * This type defines the NBOOT root key usage;
 * any other value means the root key is not valid (treat as if revoked).
 */
#define kNBOOT_RootKeyUsage_DebugCA_ImageCA_FwCA_ImageKey_FwKey (0x0U)
#define kNBOOT_RootKeyUsage_DebugCA                             (0x1U)
#define kNBOOT_RootKeyUsage_ImageCA_FwCA                        (0x2U)
#define kNBOOT_RootKeyUsage_DebugCA_ImageCA_FwCA                (0x3U)
#define kNBOOT_RootKeyUsage_ImageKey_FwKey                      (0x4U)
#define kNBOOT_RootKeyUsage_ImageKey                            (0x5U)
#define kNBOOT_RootKeyUsage_FwKey                               (0x6U)
#define kNBOOT_RootKeyUsage_Unused                              (0x7U)
typedef uint32_t nboot_root_key_usage_t;

/*!
 * @brief NBOOT type for the root key revocation
 *
 * This type defines the NBOOT root key revocation;
 * any other value means the root key is revoked.
 */
#define kNBOOT_RootKey_Enabled (0xAAU)
#define kNBOOT_RootKey_Revoked (0xBBU)
typedef uint32_t nboot_root_key_revocation_t;

/*!
 * @brief NBOOT type specifying the elliptic curve to be used
 *
 * This type defines the elliptic curve type and length
 */
#define kNBOOT_RootKey_Ecdsa_P256 (0x0000FE01U)
#define kNBOOT_RootKey_Ecdsa_P384 (0x0000FD02U)
typedef uint32_t nboot_root_key_type_and_length_t;

/*! @brief Enumeration for SoC Lifecycle. */
#define nboot_lc_nxpBlank       (0xFFFF0000U)
#define nboot_lc_nxpFab         (0xFFFE0001U)
#define nboot_lc_nxpDev         (0xFF0300FCU)
#define nboot_lc_nxpProvisioned (0xFFFC0003U)
#define nboot_lc_oemOpen        (0xFFFC0003U)
#define nboot_lc_oemSecureWorld (0xFFF80007U)
#define nboot_lc_oemClosed      (0xFFF0000FU)
#define nboot_lc_oemLocked      (0xFF3000CFU)
#define nboot_lc_oemFieldReturn (0xFFE0001FU)
#define nboot_lc_nxpFieldReturn (0xFF80007FU)
#define nboot_lc_shredded       (0xFF0000FFU)
typedef uint32_t nboot_soc_lifecycle_t;

/*! @brief Type for nboot status codes */
typedef uint32_t nboot_status_t;

/*! @brief Type for nboot protected status codes */
typedef uint64_t nboot_status_protected_t;

/*!
 * @brief nboot status codes.
 */
enum
{
    kStatus_NBOOT_Success                = 0x5A5A5A5AU, /*!< Operation completed successfully. */
    kStatus_NBOOT_Fail                   = 0x5A5AA5A5U, /*!< Operation failed. */
    kStatus_NBOOT_InvalidArgument        = 0x5A5AA5F0U, /*!< Invalid argument passed to the function. */
    kStatus_NBOOT_RequestTimeout         = 0x5A5AA5E1U, /*!< Operation timed out. */
    kStatus_NBOOT_KeyNotLoaded           = 0x5A5AA5E2U, /*!< The requested key is not loaded. */
    kStatus_NBOOT_AuthFail               = 0x5A5AA5E4U, /*!< Authentication failed. */
    kStatus_NBOOT_OperationNotAvaialable = 0x5A5AA5E5U, /*!< Operation not available on this HW. */
    kStatus_NBOOT_KeyNotAvailable        = 0x5A5AA5E6U, /*!< Key is not avaialble. */
    kStatus_NBOOT_IvCounterOverflow      = 0x5A5AA5E7U, /*!< Overflow of IV counter (PRINCE/IPED). */
    kStatus_NBOOT_SelftestFail           = 0x5A5AA5E8U, /*!< FIPS self-test failure. */
    kStatus_NBOOT_InvalidDataFormat      = 0x5A5AA5E9U, /*!< Invalid data format for example antipole */
    kStatus_NBOOT_IskCertUserDataTooBig =
        0x5A5AA5EAU, /*!< Size of User data in ISK certificate is greater than 96 bytes */
    kStatus_NBOOT_IskCertSignatureOffsetTooSmall =
        0x5A5AA5EBU,                        /*!< Signature offset in ISK certificate is smaller than expected */
    kStatus_NBOOT_MemcpyFail = 0x5A5A845AU, /*!< Unexpected error detected during nboot_memcpy() */
};

/*! @brief Data structure holding secure counter value used by nboot library */
typedef struct _nboot_secure_counter
{
    uint32_t sc;
    uint32_t scAp;
} nboot_secure_counter_t;

/*!
 * @brief NBOOT context type
 *
 * This type defines the NBOOT context
 *
 */
typedef struct _nboot_context
{
    uint32_t totalBlocks; /*!< holds number of SB3 blocks. Initialized by nboot_sb3_load_header(). */
    uint32_t processData; /*!< flag, initialized by nboot_sb3_load_header().
                             SB3 related flag set by NBOOT in case the nboot_sb3_load_block()
                             provides plain data to output buffer (for processing by ROM SB3 loader */
    uint32_t timeout;     /*!< timeout value for css operation. In case it is 0, infinite wait is performed */
    uint32_t keyinfo[NBOOT_KEYINFO_WORDLEN]; /*!< data for NBOOT key management. */
    uint32_t context[NBOOT_CONTEXT_WORDLEN]; /*!< work area for NBOOT lib. */
    uint32_t uuid[4];                        /*!< holds UUID value from NMPA */
    uint32_t prngReadyFlag; /*!< flag, used by nboot_rng_generate_lq_random() to determine whether CSS is ready to
                               generate rnd number */
    uint32_t multipartMacBuffer[1024 / sizeof(uint32_t)];
    uint32_t oemShareValidFlag; /*!< flag, used during TP to determine whether valid oemShare was set by
                                   nboot_tp_isp_gen_oem_master_share() */
    uint32_t oemShare[4]; /*!< buffer to store OEM_SHARE computed by nxpCLTrustProv_nboot_isp_gen_oem_master_share() */
    nboot_secure_counter_t secureCounter; /*!< Secure counter used by nboot */
    uint32_t rtf[NXPCLCSS_HASH_RTF_OUTPUT_SIZE_HAL / sizeof(uint32_t)];
    uint32_t imageHash[48 / sizeof(uint32_t)];
    uint32_t authStatus;
} nboot_context_t;

/*!
 * @brief NBOOT type for the root of trust parameters
 *
 * This type defines the NBOOT root of trust parameters
 *
 */
typedef struct _nboot_rot_auth_parms
{
    /* trusted information originated from CFPA */
    nboot_root_key_revocation_t soc_rootKeyRevocation[NBOOT_ROOT_CERT_COUNT]; /*!< Provided by caller based on NVM
                                                                                 information in CFPA: ROTKH_REVOKE */
    uint32_t soc_imageKeyRevocation; /*!< Provided by caller based on NVM information in CFPA: IMAGE_KEY_REVOKE */

    /* trusted information originated from CMPA */
    uint32_t soc_rkh[12]; /*!< Provided by caller based on NVM information in CMPA: ROTKH (hash of hashes) */
                          /*!< In case of kNBOOT_RootKey_Ecdsa_P384, sock_rkh[0..11] are used */
                          /*!< In case of kNBOOT_RootKey_Ecdsa_P256, sock_rkh[0..7] are used */

    uint32_t soc_numberOfRootKeys; /*!< unsigned int, between minimum = 1 and maximum = 4; */
    nboot_root_key_usage_t soc_rootKeyUsage[NBOOT_ROOT_CERT_COUNT]; /*!< CMPA */
    nboot_root_key_type_and_length_t
        soc_rootKeyTypeAndLength; /*!< static selection between ECDSA P-256 or ECDSA P-384 based root keys */

    /* trusted information originated from OTP fuses */
    nboot_soc_lifecycle_t soc_lifecycle;
} nboot_rot_auth_parms_t;

/*!
 * @brief manifest loading parameters
 *
 * This type defines the NBOOT SB3.1 manifest loading parameters
 *
 */
typedef struct _nboot_sb3_load_manifest_parms
{
    nboot_rot_auth_parms_t soc_RoTNVM;   /*!< trusted information originated from CFPA and NMPA */
    uint32_t soc_trustedFirmwareVersion; /*!< Provided by caller based on NVM information in CFPA: Secure_FW_Version */
    uint8_t pckBlob[48];
} nboot_sb3_load_manifest_parms_t;

/*!
 * @brief Data structure holding input arguments to POR secure boot (authentication) algorithm.
 * Shall be read from SoC trusted NVM or SoC fuses.
 */
typedef struct _nboot_img_auth_ecdsa_parms
{
    nboot_rot_auth_parms_t soc_RoTNVM;   /*!< trusted information originated from CFPA and NMPA */
    uint32_t soc_trustedFirmwareVersion; /*!< Provided by caller based on NVM information in CFPA: Secure_FW_Version */
} nboot_img_auth_ecdsa_parms_t;

/*! @brief Data structure holding input arguments for CMAC authentication */
typedef struct _nboot_cmac_authenticate_parms
{
    uint32_t expectedMAC[4]; /*!< expected MAC result */
} nboot_img_authenticate_cmac_parms_t;

/*!
 * @brief Boolean type for the NBOOT functions
 *
 * This type defines boolean values used by NBOOT functions that are not easily disturbed by Fault Attacks
 */
typedef enum _nboot_bool
{
    kNBOOT_TRUE                = 0x3C5AC33CU, /*!< Value for TRUE.  */
    kNBOOT_TRUE256             = 0x3C5AC35AU, /*!< Value for TRUE when P256 was used to sign the image.  */
    kNBOOT_TRUE384             = 0x3C5AC3A5U, /*!< Value for TRUE when P384 was used to sign the image.  */
    kNBOOT_FALSE               = 0x5AA55AA5U, /*!< Value for FALSE. */
    kNBOOT_OperationAllowed    = 0x3c5a33ccU,
    kNBOOT_OperationDisallowed = 0x5aa5cc33U,
} nboot_bool_t;

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief This API function is used to generate random number with specified length.
 *
 * @param output Pointer to random number buffer
 * @param outputByteLen length of generated random number in bytes. Length has to be in range <1, 2^16>
 *
 * @retval #kStatus_NBOOT_InvalidArgument Invalid input parameters (Input pointers points to NULL or length is invalid)
 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Error occured during operation
 */
status_t NBOOT_GenerateRandom(uint8_t *output, size_t outputByteLen);

/*!
 * @brief The function is used for initializing of the nboot context data structure.
 *        It should be called prior to any other calls of nboot API.
 *
 * @param nbootCtx Pointer to nboot_context_t structure.
 *
 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Error occured during operation
 */
nboot_status_t NBOOT_ContextInit(nboot_context_t *context);

/*!
 * @brief The function is used to deinitialize nboot context data structure.
 * Its contents are overwritten with random data so that any sensitive data does not remain in memory.
 *
 * @param context Pointer to nboot_context_t structure.

 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Error occured during operation
 */
nboot_status_t NBOOT_ContextDeinit(nboot_context_t *context);

/*!
 * @brief Verify NBOOT SB3.1 manifest (header message)
 *
 * This function verifies the NBOOT SB3.1 manifest (header message), initializes
 * the context and loads keys into the CSS key store so that they can be used by nboot_sb3_load_block
 * function. The NBOOT context has to be initialized by the function nboot_context_init before calling
 * this function. Please note that this API is intended to be used only by users who needs to split
 * FW update process (loading of SB3.1 file) to partial steps to customize whole operation.
 * For regular SB3.1 processing, please use API described in chapter ��SBloader APIs��.
 *
 * @param nbootCtx Pointer to nboot_context_t structure.
 * @param manifest Pointer to the input manifest buffer
 * @param params additional input parameters. Please refer to nboot_sb3_load_manifest_parms_t definition for details.
 *
 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Error occured during operation
 */
nboot_status_protected_t NBOOT_Sb3LoadManifest(nboot_context_t *context,
                                               uint32_t *manifest,
                                               nboot_sb3_load_manifest_parms_t *parms);

/*!
 * @brief Verify NBOOT SB3.1 block
 *
 * This function verifies and decrypts an NBOOT SB3.1 block. Decryption is performed in-place.
 * The NBOOT context has to be initialized by the function nboot_context_init before calling this function.
 * Please note that this API is intended to be used only by users who needs to split FW update process
 * (loading of SB3.1 file) to partial steps to customize whole operation. For regular SB3.1 processing,
 * please use API described in chapter ��SBloader APIs��.
 *
 * @param context Pointer to nboot_context_t structure.
 * @param block Pointer to the input SB3.1 data block
 *
 * @retval #kStatus_NBOOT_Success successfully finished
 * @retval #kStatus_NBOOT_Fail occured during operation
 */
nboot_status_protected_t NBOOT_Sb3LoadBlock(nboot_context_t *context, uint32_t *block);

/*!
 * @brief This function authenticates image with asymmetric cryptography.
 *        The NBOOT context has to be initialized by the function nboot_context_init
 *        before calling this function.
 *
 * @param context Pointer to nboot_context_t structure.
 * @param imageStartAddress Pointer to start of the image in memory.
 * @param isSignatureVerified Pointer to memory holding function call result.
 *                            After the function returns, the value will be set to kNBOOT_TRUE when the image is
 * authentic. Any other value means the authentication does not pass.
 *
 * @param parms Pointer to a data structure in trusted memory, holding input parameters for the algorithm.
 *              The data structure shall be correctly filled before the function call.
 *
 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Returned in all other cases. Doesn't always mean invalid image,
 *         it could also mean transient error caused by short time environmental conditions.
 */
nboot_status_protected_t NBOOT_ImgAuthenticateEcdsa(nboot_context_t *context,
                                                    uint8_t imageStartAddress[],
                                                    nboot_bool_t *isSignatureVerified,
                                                    nboot_img_auth_ecdsa_parms_t *parms);

/*!
 * @brief This function calculates the CMAC over the given image and compares it to the expected value.
 * To be more resistant against SPA, it is recommended that imageStartAddress is word aligned.
 * The NBOOT context has to be initialized by the nboot_context_init() before calling this function.
 *
 * @param context Pointer to nboot_context_t structure.
 * @param imageStartAddress Pointer to start of the image in memory.
 * @param isSignatureVerified Pointer to memory holding function call result.
                              After the function returns, the value will be set to
 * @param parms Pointer to a data structure in trusted memory, holding the reference MAC.
                The data structure shall be correctly filled before the function call.
 *
 * @retval kStatus_NBOOT_Success
 * @retval kStatus_NBOOT_Fail
 */
nboot_status_protected_t NBOOT_ImgAuthenticateCmac(nboot_context_t *context,
                                                   uint8_t imageStartAddress[],
                                                   nboot_bool_t *isSignatureVerified,
                                                   nboot_img_authenticate_cmac_parms_t *parms);

#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* FSL_NBOOT_H_ */
