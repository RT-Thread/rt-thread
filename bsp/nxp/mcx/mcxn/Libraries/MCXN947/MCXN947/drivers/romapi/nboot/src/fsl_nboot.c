/*
 * Copyright 2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_nboot.h"
#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.nboot"
#endif

#define BOOTLOADER_API_TREE_POINTER ((bootloader_tree_t *)0x1303fc00U)

/**
 * @brief Image authentication operations.
 *
 * These abstract interface are used for image verification operations.
 */
typedef struct
{
    romapi_status_t (*romapi_rng_generate_random)(uint8_t *output, size_t outputByteLen);
    nboot_status_t (*nboot_context_init)(nboot_context_t *context);
    nboot_status_t (*nboot_context_deinit)(nboot_context_t *context);
    nboot_status_protected_t (*nboot_sb3_load_manifest)(nboot_context_t *context,
                                                        uint32_t *manifest,
                                                        nboot_sb3_load_manifest_parms_t *parms);
    nboot_status_protected_t (*nboot_sb3_load_block)(nboot_context_t *context, uint32_t *block);
    nboot_status_protected_t (*nboot_img_authenticate_ecdsa)(nboot_context_t *context,
                                                             uint8_t imageStartAddress[],
                                                             nboot_bool_t *isSignatureVerified,
                                                             nboot_img_auth_ecdsa_parms_t *parms);
    nboot_status_protected_t (*nboot_img_authenticate_cmac)(nboot_context_t *context,
                                                            uint8_t imageStartAddress[],
                                                            nboot_bool_t *isSignatureVerified,
                                                            nboot_img_authenticate_cmac_parms_t *parms);
} nboot_interface_t;

/*!
 * @brief Root of the bootloader API tree.
 *
 * An instance of this struct resides in read-only memory in the bootloader. It
 * provides a user application access to APIs exported by the bootloader.
 *
 * @note The order of existing fields must not be changed.
 */
typedef struct BootloaderTree
{
    void (*runBootloader)(void *arg);     /*!< Function to start the bootloader executing.*/
    const uint32_t version;               /*!< Bootloader version number.*/
    const char *copyright;                /*!< Copyright string.*/
    const uint32_t reserved0;             /*!< reserved*/
    const uint32_t flashDriver;           /*!< Internal Flash driver API.*/
    const uint32_t reserved1[5];          /*!< reserved*/
    const nboot_interface_t *nbootDriver; /*!< nBoot driver API */
    const uint32_t flexspiNorDriver;      /*!< FlexSPI NOR FLASH Driver API.*/
    const uint32_t efuseDriver;           /*!< eFuse driver API */
    const uint32_t iapAPIDriver;          /*!< IAP driver API */
} bootloader_tree_t;

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
status_t NBOOT_GenerateRandom(uint8_t *output, size_t outputByteLen)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->nbootDriver->romapi_rng_generate_random(output, outputByteLen);
}

/*!
 * @brief The function is used for initializing of the nboot context data structure.
 *        It should be called prior to any other calls of nboot API.
 *
 * @param nbootCtx Pointer to nboot_context_t structure.
 *
 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Error occured during operation
 */
nboot_status_t NBOOT_ContextInit(nboot_context_t *context)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->nbootDriver->nboot_context_init(context);
}

/*!
 * @brief The function is used to deinitialize nboot context data structure.
 * Its contents are overwritten with random data so that any sensitive data does not remain in memory.
 *
 * @param context Pointer to nboot_context_t structure.

 * @retval #kStatus_NBOOT_Success Operation successfully finished
 * @retval #kStatus_NBOOT_Fail Error occured during operation
 */
nboot_status_t NBOOT_ContextDeinit(nboot_context_t *context)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->nbootDriver->nboot_context_deinit(context);
}
/*!
 * @brief Verify NBOOT SB3.1 manifest (header message)
 *
 * This function verifies the NBOOT SB3.1 manifest (header message), initializes
 * the context and loads keys into the CSS key store so that they can be used by nboot_sb3_load_block
 * function. The NBOOT context has to be initialized by the function nboot_context_init before calling
 * this function. Please note that this API is intended to be used only by users who needs to split
 * FW update process (loading of SB3.1 file) to partial steps to customize whole operation.
 * For regular SB3.1 processing, please use API described in chapter SBloader APIs.
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
                                               nboot_sb3_load_manifest_parms_t *parms)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->nbootDriver->nboot_sb3_load_manifest(context, manifest, parms);
}

/*!
 * @brief Verify NBOOT SB3.1 block
 *
 * This function verifies and decrypts an NBOOT SB3.1 block. Decryption is performed in-place.
 * The NBOOT context has to be initialized by the function nboot_context_init before calling this function.
 * Please note that this API is intended to be used only by users who needs to split FW update process
 * (loading of SB3.1 file) to partial steps to customize whole operation. For regular SB3.1 processing,
 * please use API described in chapter SBloader APIs.
 *
 * @param context Pointer to nboot_context_t structure.
 * @param block Pointer to the input SB3.1 data block
 *
 * @retval #kStatus_NBOOT_Success successfully finished
 * @retval #kStatus_NBOOT_Fail occured during operation
 */
nboot_status_protected_t NBOOT_Sb3LoadBlock(nboot_context_t *context, uint32_t *block)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->nbootDriver->nboot_sb3_load_block(context, block);
}

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
                                                    nboot_img_auth_ecdsa_parms_t *parms)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->nbootDriver->nboot_img_authenticate_ecdsa(context, imageStartAddress,
                                                                                  isSignatureVerified, parms);
}

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
                                                   nboot_img_authenticate_cmac_parms_t *parms)
{
    assert(BOOTLOADER_API_TREE_POINTER);
    return BOOTLOADER_API_TREE_POINTER->nbootDriver->nboot_img_authenticate_cmac(context, imageStartAddress,
                                                                                 isSignatureVerified, parms);
}
